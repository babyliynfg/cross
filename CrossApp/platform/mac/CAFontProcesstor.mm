

#include "CAFontProcesstor.h"
#include "images/CAImage.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

static NSTextAlignment _calculateTextAlignment(CrossApp::CATextAlignment alignment)
{
    NSTextAlignment nsAlignment;
    switch (alignment)
    {
        case CrossApp::CATextAlignment::Right:
            nsAlignment = NSTextAlignmentRight;
        case CrossApp::CATextAlignment::Center:
            nsAlignment = NSTextAlignmentCenter;
            break;
        case CrossApp::CATextAlignment::Left:
        default:
            nsAlignment = NSTextAlignmentLeft;
            break;
    }
    
    return nsAlignment;
}

static CGFloat _calculateTextDrawStartWidth(CrossApp::CATextAlignment alignment, CGSize realDimensions, CGSize dimensions)
{
    CGFloat xPadding = 0;
    switch (alignment)
    {
        case CrossApp::CATextAlignment::Right:
            xPadding = dimensions.width - realDimensions.width;
            break;
        case CrossApp::CATextAlignment::Center:
            xPadding = (dimensions.width - realDimensions.width) / 2.0f;
            break;
        case CrossApp::CATextAlignment::Left:
        default:
            break;
    }
    return xPadding;
}

static CGFloat _calculateTextDrawStartHeight(CrossApp::CAVerticalTextAlignment vAlignment, CGSize realDimensions, CGSize dimensions)
{
    float startH = 0;
    switch (vAlignment)
    {
        case CrossApp::CAVerticalTextAlignment::Bottom:
            startH = dimensions.height - realDimensions.height;
            break;
        case CrossApp::CAVerticalTextAlignment::Center:
            startH = (dimensions.height - realDimensions.height) / 2;
            break;
        case CrossApp::CAVerticalTextAlignment::Top:
        default:
            break;
    }
    return startH;
}

static NSAttributedString* __attributedStringWithFontSize(NSMutableAttributedString* attributedString, CGFloat fontSize)
{
    {
        [attributedString beginEditing];
        
        [attributedString enumerateAttribute:NSFontAttributeName inRange:NSMakeRange(0, attributedString.length) options:0 usingBlock:^(id value, NSRange range, BOOL *stop) {
            
            NSFont* font = value;
            font = [[NSFontManager sharedFontManager] convertFont:font toSize:fontSize];
            
            [attributedString removeAttribute:NSFontAttributeName range:range];
            [attributedString addAttribute:NSFontAttributeName value:font range:range];
        }];
        
        [attributedString endEditing];
    }
    
    return [[attributedString copy] autorelease];
}

static NSSize _calculateStringSize(NSAttributedString *str, id font, CGSize constrainSize, bool enableWrap, int overflow)
{
    NSSize textRect = NSZeroSize;
    textRect.width = constrainSize.width > 0 ? constrainSize.width
    : CGFLOAT_MAX;
    textRect.height = constrainSize.height > 0 ? constrainSize.height
    : CGFLOAT_MAX;
    
    if (overflow == 1)
    {
        if (!enableWrap)
        {
            textRect.width = CGFLOAT_MAX;
            textRect.height = CGFLOAT_MAX;
        }
        else
        {
            textRect.height = CGFLOAT_MAX;
        }
    }
    
    NSSize dim;
#ifdef __MAC_10_11
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) context:nil].size;
#else
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
#else
    dim = [str boundingRectWithSize:textRect options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
    
    
    dim.width = ceilf(dim.width);
    dim.height = ceilf(dim.height);
    
    return dim;
}

static NSFont* _createSystemFont(const std::string& fontName, unsigned int size)
{
    NSString * fntName = [NSString stringWithUTF8String:fontName.c_str()];
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    
    CGFloat fontSize = size;
    
    // font
    NSFont *font = [[NSFontManager sharedFontManager]
                    fontWithFamily:fntName
                    traits:NSUnboldFontMask | NSUnitalicFontMask
                    weight:0
                    size:fontSize];
    
    if (font == nil) {
        font = [[NSFontManager sharedFontManager]
                fontWithFamily:@"Arial"
                traits:NSUnboldFontMask | NSUnitalicFontMask
                weight:0
                size:fontSize];
    }
    return font;
}

NS_CC_BEGIN
namespace CAFontProcesstor
{
    
    CAImage* imageForText(const std::string& text, const CAFont& font, DSize& dim)
    {
        CAImage* ret = nullptr;
        do {
            CC_BREAK_IF(text.empty());
            NSString * string  = [NSString stringWithUTF8String:text.c_str()];
            CC_BREAK_IF(!string);
            
            id nsfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!nsfont);
            
            // color
            NSColor* foregroundColor = [NSColor colorWithDeviceRed:font.color.r/255.0
                                                             green:font.color.g/255.0
                                                              blue:font.color.b/255.0
                                                             alpha:font.color.a/255.0];

            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);

            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            // attribute
            NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                                 foregroundColor,
                                                 NSForegroundColorAttributeName,
                                                 nsfont,
                                                 NSFontAttributeName,
                                                 paragraphStyle,
                                                 NSParagraphStyleAttributeName,
                                                 nil];
            
            NSAttributedString *stringWithAttributes = [[[NSAttributedString alloc] initWithString:string attributes:tokenAttributesDict] autorelease];
            
            NSSize dimensions = _calculateStringSize(stringWithAttributes, nsfont, CGSizeMake(dim.width, dim.height), font.wordWrap, 0);

            // Mac crashes if the width or height is 0
            CC_BREAK_IF(dimensions.width <= 0 || dimensions.height <= 0);
            
            dim = DSize(dimensions.width, dimensions.height);
            

            NSInteger POTWide = dimensions.width;
            NSInteger POTHigh = dimensions.height;
            
            NSRect textRect = NSMakeRect(0,
                                         0,
                                         dimensions.width,
                                         dimensions.height);
            
            
            [[NSGraphicsContext currentContext] setShouldAntialias:NO];
            
            NSImage *image = [[NSImage alloc] initWithSize:NSMakeSize(POTWide, POTHigh)];
            [image lockFocus];
            // patch for mac retina display and lableTTF
            [[NSAffineTransform transform] set];
            [stringWithAttributes drawInRect:textRect];
            NSBitmapImageRep *bitmap = [[NSBitmapImageRep alloc] initWithFocusedViewRect:NSMakeRect (0.0f, 0.0f, POTWide, POTHigh)];
            [image unlockFocus];
            
            unsigned int pixelsWide = static_cast<unsigned int>(POTWide);
            unsigned int pixelsHigh = static_cast<unsigned int>(POTHigh);
            
            ssize_t length = pixelsWide * pixelsHigh * 4;
            unsigned char *bytes = (unsigned char*)malloc(sizeof(unsigned char) * length);
            memcpy(bytes, (unsigned char*) [bitmap bitmapData], length);

            [bitmap release];
            [image release];
            
            CAData* data = new CAData();
            data->fastSet(bytes, length);
            ret = CAImage::createWithRawDataNoCache(data, CAImage::PixelFormat::RGBA8888, pixelsWide, pixelsHigh);
            data->release();
        } while (0);

        
        return ret;
    }
    
    float heightForFont(const CAFont& font)
    {
        float ret = 0;
        do
        {
            id nsfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!nsfont);
            
            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            // attribute
            NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                                 [NSColor whiteColor],
                                                 NSForegroundColorAttributeName,
                                                 nsfont,
                                                 NSFontAttributeName,
                                                 paragraphStyle,
                                                 NSParagraphStyleAttributeName,
                                                 nil];
            
            NSAttributedString* str = [[[NSAttributedString alloc] initWithString:@"A" attributes:tokenAttributesDict] autorelease];
            NSSize textSize = NSMakeSize(CGFLOAT_MAX, 0);
            NSSize dim;
#ifdef __MAC_10_11
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) context:nil].size;
#else
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
#else
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
            
            ret = ceilf(dim.height);
            
        } while (0);
        
        
        return ret;
    }
    
    float heightForTextAtWidth(const std::string& text, const CAFont& font, float width)
    {
        float ret = 0;
        do
        {
            CC_BREAK_IF(text.empty());
            NSString* string = [NSString stringWithUTF8String:text.c_str()];
            CC_BREAK_IF(!string);
            
            id nsfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!nsfont);
            
            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            // attribute
            NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                                 [NSColor whiteColor],
                                                 NSForegroundColorAttributeName,
                                                 nsfont,
                                                 NSFontAttributeName,
                                                 paragraphStyle,
                                                 NSParagraphStyleAttributeName,
                                                 nil];
            
            NSAttributedString* str = [[[NSAttributedString alloc] initWithString:string attributes:tokenAttributesDict] autorelease];
            NSSize textSize = NSMakeSize(width, 0);
            NSSize dim;
#ifdef __MAC_10_11
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) context:nil].size;
#else
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
#else
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
            
            ret = ceilf(dim.height);
            
        } while (0);
        
        
        return ret;
        
        
        return ret;
    }
    
    float widthForTextAtOneLine(const std::string& text, const CAFont& font)
    {
        float ret = 0;
        do
        {
            CC_BREAK_IF(text.empty());
            NSString* string = [NSString stringWithUTF8String:text.c_str()];
            CC_BREAK_IF(!string);
            
            id nsfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!nsfont);
            
            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            // attribute
            NSDictionary* tokenAttributesDict = [NSDictionary dictionaryWithObjectsAndKeys:
                                                 [NSColor whiteColor],
                                                 NSForegroundColorAttributeName,
                                                 nsfont,
                                                 NSFontAttributeName,
                                                 paragraphStyle,
                                                 NSParagraphStyleAttributeName,
                                                 nil];
            
            NSAttributedString* str = [[[NSAttributedString alloc] initWithString:string attributes:tokenAttributesDict] autorelease];
            NSSize textSize = NSMakeSize(CGFLOAT_MAX, 0);
            NSSize dim;
#ifdef __MAC_10_11
#if __MAC_OS_X_VERSION_MAX_ALLOWED >= __MAC_10_11
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin) context:nil].size;
#else
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
#else
            dim = [str boundingRectWithSize:textSize options:(NSStringDrawingOptions)(NSStringDrawingUsesLineFragmentOrigin)].size;
#endif
            
            ret = ceilf(dim.width);
            
        } while (0);
        return ret;
    }
    
}
NS_CC_END
