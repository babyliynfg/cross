

#include "CAFontProcesstor.h"
#include "images/CAImage.h"
#import <UIKit/UIKit.h>

#if !defined(CC_TARGET_OS_TVOS)
#import<CoreMotion/CoreMotion.h>
#endif
#import<CoreFoundation/CoreFoundation.h>
#import <CoreText/CoreText.h>

#import <AudioToolbox/AudioToolbox.h>

static id _createSystemFont( const std::string& fontName, int size)
{
    NSString * fntName      = [NSString stringWithUTF8String:fontName.c_str()];
    // On iOS custom fonts must be listed beforehand in the App info.plist (in order to be usable) and referenced only the by the font family name itself when
    // calling [UIFont fontWithName]. Therefore even if the developer adds 'SomeFont.ttf' or 'fonts/SomeFont.ttf' to the App .plist, the font must
    // be referenced as 'SomeFont' when calling [UIFont fontWithName]. Hence we strip out the folder path components and the extension here in order to get just
    // the font family name itself. This stripping step is required especially for references to user fonts stored in CCB files; CCB files appear to store
    // the '.ttf' extensions when referring to custom fonts.
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    
    // create the font
    id font = [UIFont fontWithName:fntName size:size];
    
    if (!font)
    {
        font = [UIFont systemFontOfSize:size];
    }
    return font;
}

NSTextAlignment _calculateTextAlignment(CrossApp::CATextAlignment alignment)
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

CGSize _calculateStringSize(NSAttributedString *str, id font, CGSize constrainSize, bool enableWrap, int fontSize)
{
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize.width > 0 ? constrainSize.width
    : CGFLOAT_MAX;
    textRect.height = constrainSize.height > 0 ? constrainSize.height
    : CGFLOAT_MAX;

    CGSize dim;
    dim = [str boundingRectWithSize:CGSizeMake(textRect.width, textRect.height)
                            options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesDeviceMetrics)
                            context:nil].size;
    
    dim.width = ceilf(dim.width);
    if (dim.height < fontSize * 1.8f)
    {
        dim.height = ceilf(dim.height * 1.1f);
    }
    else
    {
        dim.height = ceilf(dim.height);
    }
    
    return dim;
}

NS_CC_BEGIN
namespace CAFontProcesstor
{
    
    CAImage* imageForText(const std::string& text, const CAFont& font, DSize& dim)
    {
        CAImage* ret = nullptr;
        do
        {
            CC_BREAK_IF(text.empty());
            
            id iosfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!iosfont);

            NSString * str          = [NSString stringWithUTF8String:text.c_str()];
            CC_BREAK_IF(!str);

            // color
            UIColor* foregroundColor = [UIColor colorWithRed:font.color.r / 255.f
                                                       green:font.color.g / 255.f
                                                        blue:font.color.b / 255.f
                                                       alpha:font.color.a / 255.f];
            
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            // adjust text rect according to overflow
            NSMutableDictionary* tokenAttributesDict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                        foregroundColor,NSForegroundColorAttributeName,
                                                        iosfont,
                                                        NSFontAttributeName,
                                                        paragraphStyle, NSParagraphStyleAttributeName, nil];
            
            NSAttributedString *stringWithAttributes = [[[NSAttributedString alloc] initWithString:str attributes:tokenAttributesDict] autorelease];
            
            int shrinkFontSize = font.fontSize;
            CGSize dimensions = _calculateStringSize(stringWithAttributes, iosfont, CGSizeMake(dim.width, dim.height), font.wordWrap, font.fontSize);

            NSInteger POTWide = dimensions.width;
            NSInteger POTHigh = dimensions.height;
            
            CGRect textRect = CGRectMake(0, 0, dimensions.width, dimensions.height);
            
            ssize_t length = POTWide * POTHigh * 4;
            unsigned char *bytes = (unsigned char*)malloc(sizeof(unsigned char) * length);
            memset(bytes, 0, length);
            
            // draw text
            CGColorSpaceRef colorSpace  = CGColorSpaceCreateDeviceRGB();
            CGContextRef context        = CGBitmapContextCreate(bytes,
                                                                POTWide,
                                                                POTHigh,
                                                                8,
                                                                POTWide * 4,
                                                                colorSpace,
                                                                kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
            if (!context)
            {
                CGColorSpaceRelease(colorSpace);
                CC_SAFE_FREE(bytes);
                break;
            }
            
            // text color
            CGContextSetRGBFillColor(context,
                                     font.color.r / 255.f,
                                     font.color.g / 255.f,
                                     font.color.b / 255.f,
                                     font.color.r / 255.f);
            
            // move Y rendering to the top of the image
            CGContextTranslateCTM(context, 0.0f, POTHigh);
            
            //NOTE: NSString draws in UIKit referential i.e. renders upside-down compared to CGBitmapContext referential
            CGContextScaleCTM(context, 1.0f, -1.0f);
            // store the current context
            UIGraphicsPushContext(context);
            
            CGColorSpaceRelease(colorSpace);
            
            CGContextSetShouldSubpixelQuantizeFonts(context, false);
            
            CGContextBeginTransparencyLayerWithRect(context, textRect, NULL);
            
            
            if (font.stroke.strokeEnabled)
            {
                CGContextSetTextDrawingMode(context, kCGTextStroke);
                UIColor *strokeColor = [UIColor colorWithRed:font.stroke.strokeColor.r / 255.f
                                                       green:font.stroke.strokeColor.g / 255.f
                                                        blue:font.stroke.strokeColor.b / 255.f
                                                       alpha:font.stroke.strokeColor.a / 255.f];
                
                
                NSMutableDictionary* tokenAttributesDict2 = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                             foregroundColor,NSForegroundColorAttributeName,
                                                             iosfont, NSFontAttributeName,
                                                             paragraphStyle, NSParagraphStyleAttributeName, nil];
                [tokenAttributesDict2 setObject:[NSNumber numberWithFloat: font.stroke.strokeSize / shrinkFontSize * 100]
                                         forKey:NSStrokeWidthAttributeName];
                [tokenAttributesDict2 setObject:strokeColor forKey:NSStrokeColorAttributeName];
                
                NSAttributedString *strokeString =[[[NSAttributedString alloc] initWithString:str attributes:tokenAttributesDict2] autorelease];
                
                [strokeString drawInRect:textRect];
                
            }
            
            CGContextSetTextDrawingMode(context, kCGTextFill);
            
            // actually draw the text in the context
            [stringWithAttributes drawInRect:textRect];
            
            CGContextEndTransparencyLayer(context);
            
            // pop the context
            UIGraphicsPopContext();
            
            // release the context
            CGContextRelease(context);
            
            unsigned int pixelsWide = static_cast<unsigned int>(POTWide);
            unsigned int pixelsHigh = static_cast<unsigned int>(POTHigh);

            dim = DSize(pixelsWide, pixelsHigh);
            
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
            id iosfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!iosfont);
            
            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            NSMutableDictionary* tokenAttributesDict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                        [UIColor whiteColor],
                                                        NSForegroundColorAttributeName,
                                                        iosfont,
                                                        NSFontAttributeName,
                                                        paragraphStyle, NSParagraphStyleAttributeName, nil];
            
            NSAttributedString* str = [[[NSAttributedString alloc] initWithString:@"A" attributes:tokenAttributesDict] autorelease];
            CGSize textSize = CGSizeMake(CGFLOAT_MAX, 0);
            CGSize dim;
            dim = [str boundingRectWithSize:CGSizeMake(textSize.width, textSize.height)
                                    options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesDeviceMetrics)
                                    context:nil].size;
            
            dim.width = ceilf(dim.width);
            dim.height = ceilf(dim.height * 1.1f);
            
            ret = dim.height;
            
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
            
            id iosfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!iosfont);
            
            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            NSMutableDictionary* tokenAttributesDict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                        [UIColor whiteColor],
                                                        NSForegroundColorAttributeName,
                                                        iosfont,
                                                        NSFontAttributeName,
                                                        paragraphStyle, NSParagraphStyleAttributeName, nil];
            
            NSAttributedString* str = [[[NSAttributedString alloc] initWithString:string attributes:tokenAttributesDict] autorelease];
            CGSize textSize = CGSizeMake(width, 0);
            CGSize dim;
            dim = [str boundingRectWithSize:CGSizeMake(textSize.width, textSize.height)
                                    options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesDeviceMetrics)
                                    context:nil].size;
            
            dim.width = ceilf(dim.width);
            if (dim.height < font.fontSize * 1.8f)
            {
                dim.height = ceilf(dim.height * 1.1f);
            }
            else
            {
                dim.height = ceilf(dim.height);
            }
            ret = dim.height;
            
        } while (0);
        
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
            
            id iosfont = _createSystemFont(font.fontName, font.fontSize);
            CC_BREAK_IF(!iosfont);
            
            // alignment
            NSTextAlignment textAlign = _calculateTextAlignment(font.textAlignment);
            
            NSMutableParagraphStyle *paragraphStyle = [[[NSMutableParagraphStyle alloc] init] autorelease];
            paragraphStyle.lineBreakMode = NSLineBreakByWordWrapping;
            [paragraphStyle setAlignment:textAlign];
            
            NSMutableDictionary* tokenAttributesDict = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                        [UIColor whiteColor],
                                                        NSForegroundColorAttributeName,
                                                        iosfont,
                                                        NSFontAttributeName,
                                                        paragraphStyle, NSParagraphStyleAttributeName, nil];
            
            NSAttributedString* str = [[[NSAttributedString alloc] initWithString:string attributes:tokenAttributesDict] autorelease];
            CGSize textSize = CGSizeMake(CGFLOAT_MAX, font.fontSize * 1.5f);
            CGSize dim;
            dim = [str boundingRectWithSize:CGSizeMake(textSize.width, textSize.height)
                                    options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesDeviceMetrics)
                                    context:nil].size;
            
            dim.width = ceilf(dim.width);

            ret = dim.width;
            
        } while (0);
        
        return ret;
    }
    
}
NS_CC_END
