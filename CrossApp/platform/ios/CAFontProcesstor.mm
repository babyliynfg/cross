

#include "CAFontProcesstor.h"
#include "images/CAImage.h"
#import <UIKit/UIKit.h>

#if !defined(CC_TARGET_OS_TVOS)
#import<CoreMotion/CoreMotion.h>
#endif
#import<CoreFoundation/CoreFoundation.h>
#import <CoreText/CoreText.h>

#import <AudioToolbox/AudioToolbox.h>

static id _createSystemFont(const CrossApp::CAFont& font)
{
    NSString * fntName      = [NSString stringWithUTF8String:font.fontName.c_str()];
    // On iOS custom fonts must be listed beforehand in the App info.plist (in order to be usable) and referenced only the by the font family name itself when
    // calling [UIFont fontWithName]. Therefore even if the developer adds 'SomeFont.ttf' or 'fonts/SomeFont.ttf' to the App .plist, the font must
    // be referenced as 'SomeFont' when calling [UIFont fontWithName]. Hence we strip out the folder path components and the extension here in order to get just
    // the font family name itself. This stripping step is required especially for references to user fonts stored in CCB files; CCB files appear to store
    // the '.ttf' extensions when referring to custom fonts.
    fntName = [[fntName lastPathComponent] stringByDeletingPathExtension];
    
    // create the font
    UIFont* iosFont = [UIFont fontWithName:fntName size:font.fontSize];
    
    if (!iosFont)
    {
        iosFont = [UIFont systemFontOfSize:font.fontSize];
    }
    
    if (font.bold || font.italics)
    {
        NSString* fontName = [NSString stringWithFormat:@"%@", iosFont.fontName];
        
        
//        if (font.bold)
//        {
//            fontName = [fontName stringByAppendingString:@"-Bold"];
//            
//            if (font.italics)
//            {
//                fontName = [fontName stringByAppendingString:@"Oblique"];
//            }
//        }
//        else
//        {
//            if (font.italics)
//            {
//                fontName = [fontName stringByAppendingString:@"-Oblique"];
//            }
//        }

        iosFont = [UIFont fontWithName:fontName size:font.fontSize];

    }
    
    return iosFont;
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

CGRect _calculateStringRect(NSAttributedString *str, id font, CGSize constrainSize, bool enableWrap, float fontSize)
{
    CGSize textRect = CGSizeZero;
    textRect.width = constrainSize.width > 0 ? constrainSize.width
    : CGFLOAT_MAX;
    textRect.height = constrainSize.height > 0 ? constrainSize.height
    : CGFLOAT_MAX;

    CGRect dim;
    dim.origin = CGPointZero;
    dim.size = [str boundingRectWithSize:CGSizeMake(textRect.width, textRect.height)
                            options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingTruncatesLastVisibleLine)
                            context:nil].size;
    
    dim.size.width = ceilf(dim.size.width);
    dim.size.height = ceilf(dim.size.height);
    
    return dim;
}

NS_CC_BEGIN
CAImage* CAFontProcesstor::imageForText(const std::string& text, const CAFont& font, DSize& dim)
{
    CAImage* ret = nullptr;
    do
    {
        CC_BREAK_IF(text.empty());
        
        id iosfont = _createSystemFont(font);
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
                                                    foregroundColor,    NSForegroundColorAttributeName,
                                                    iosfont,            NSFontAttributeName,
                                                    paragraphStyle,     NSParagraphStyleAttributeName,
                                                    nil];
        
        
        if (font.color == CAColor4B::CLEAR && font.stroke.strokeEnabled)
        {
            foregroundColor = [UIColor colorWithRed:font.stroke.strokeColor.r / 255.f
                                                   green:font.stroke.strokeColor.g / 255.f
                                                    blue:font.stroke.strokeColor.b / 255.f
                                                   alpha:font.stroke.strokeColor.a / 255.f];
            

            [tokenAttributesDict setObject:@(font.stroke.strokeSize) forKey:NSStrokeWidthAttributeName];
            [tokenAttributesDict setObject:foregroundColor forKey:NSStrokeColorAttributeName];
        }
        
        if (font.italics) [tokenAttributesDict setObject:@(font.italicsValue) forKey:NSObliquenessAttributeName];
        if (font.underLine) [tokenAttributesDict setObject:@(NSUnderlineStyleSingle) forKey:NSUnderlineStyleAttributeName];
        if (font.deleteLine) [tokenAttributesDict setObject:@(NSUnderlineStyleSingle) forKey:NSStrikethroughStyleAttributeName];

        NSAttributedString *stringWithAttributes = [[[NSAttributedString alloc] initWithString:str attributes:tokenAttributesDict] autorelease];
        
        int shrinkFontSize = font.fontSize;
        CGRect textRect = _calculateStringRect(stringWithAttributes, iosfont, CGSizeMake(dim.width, dim.height), font.wordWrap, font.fontSize);
        
        if (font.italics)
        {
            float increase = shrinkFontSize * font.italicsValue * 0.5f;
            if (font.italicsValue > 0)
            {
                textRect.size.width += increase;
            }
            else if (font.italicsValue < 0)
            {
                textRect.size.width -= increase;
                textRect.origin.x -= increase;
            }
        }

        NSInteger POTWide = textRect.size.width;
        NSInteger POTHigh = textRect.size.height;
        
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
        
        if (font.bold)
        {
            CGContextSetTextDrawingMode(context, kCGTextStroke);

            NSMutableDictionary* tokenAttributesDict2 = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                         foregroundColor,NSForegroundColorAttributeName,
                                                         iosfont, NSFontAttributeName,
                                                         paragraphStyle, NSParagraphStyleAttributeName,
                                                         nil];
            
            if (font.italics) [tokenAttributesDict2 setObject:@(font.italicsValue) forKey:NSObliquenessAttributeName];
            
            [tokenAttributesDict2 setObject:@(shrinkFontSize / 10.f) forKey:NSStrokeWidthAttributeName];
            [tokenAttributesDict2 setObject:foregroundColor forKey:NSStrokeColorAttributeName];
            
            NSAttributedString *strokeString = [[[NSAttributedString alloc] initWithString:str attributes:tokenAttributesDict2] autorelease];
            
            [strokeString drawInRect:textRect];
        }
        
        if (font.shadow.shadowEnabled)
        {
            CGContextSetTextDrawingMode(context, kCGTextStroke);
            
            NSMutableDictionary* tokenAttributesDict2 = [NSMutableDictionary dictionaryWithObjectsAndKeys:
                                                         foregroundColor,NSForegroundColorAttributeName,
                                                         iosfont, NSFontAttributeName,
                                                         paragraphStyle, NSParagraphStyleAttributeName, nil];
            
            if (font.italics) [tokenAttributesDict2 setObject:@(font.italicsValue) forKey:NSObliquenessAttributeName];
            
            NSShadow* shadow = [[[NSShadow alloc] init] autorelease];
            
            [shadow setShadowOffset:CGSizeMake(font.shadow.shadowOffset.width, font.shadow.shadowOffset.height)];
            [shadow setShadowBlurRadius:font.shadow.shadowBlur];
            
            UIColor* shadowColor = [UIColor colorWithRed:font.shadow.shadowColor.r / 255.f
                                                   green:font.shadow.shadowColor.g / 255.f
                                                    blue:font.shadow.shadowColor.b / 255.f
                                                   alpha:font.shadow.shadowColor.a / 255.f];
            
            [shadow setShadowColor:shadowColor];
            
            [tokenAttributesDict2 setObject:shadow forKey:NSShadowAttributeName];
            
            NSAttributedString *strokeString =[[[NSAttributedString alloc] initWithString:str attributes:tokenAttributesDict2] autorelease];
            
            [strokeString drawInRect:textRect];
            
        }
        
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
            
            if (font.italics) [tokenAttributesDict2 setObject:@(font.italicsValue) forKey:NSObliquenessAttributeName];
            
            [tokenAttributesDict2 setObject:@(font.stroke.strokeSize) forKey:NSStrokeWidthAttributeName];
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

float CAFontProcesstor::heightForFont(const CAFont& font)
{
    float ret = 0;
    do
    {
        id iosfont = _createSystemFont(font);
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
                                options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingTruncatesLastVisibleLine)
                                context:nil].size;
        
        dim.width = ceilf(dim.width);
        dim.height = ceilf(dim.height);
        
        ret = dim.height;
        
    } while (0);
    
    return ret;
}

float CAFontProcesstor::heightForTextAtWidth(const std::string& text, const CAFont& font, float width)
{
    float ret = 0;
    do
    {
        CC_BREAK_IF(text.empty());
        
        NSString* string = [NSString stringWithUTF8String:text.c_str()];
        CC_BREAK_IF(!string);
        
        id iosfont = _createSystemFont(font);
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
                                options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingTruncatesLastVisibleLine)
                                context:nil].size;
        
        dim.width = ceilf(dim.width);
        dim.height = ceilf(dim.height);
        
        ret = dim.height;
        
    } while (0);
    
    return ret;
}

float CAFontProcesstor::widthForTextAtOneLine(const std::string& text, const CAFont& font)
{
    float ret = 0;
    do
    {
        CC_BREAK_IF(text.empty());
        
        NSString* string = [NSString stringWithUTF8String:text.c_str()];
        CC_BREAK_IF(!string);
        
        id iosfont = _createSystemFont(font);
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
                                options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingTruncatesLastVisibleLine)
                                context:nil].size;
        
        dim.width = ceilf(dim.width);
        
        ret = dim.width;
        
    } while (0);
    
    return ret;
}
NS_CC_END
