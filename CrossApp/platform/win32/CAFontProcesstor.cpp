

#include "CAFontProcesstor.h"

NS_CC_BEGIN

CAImage* imageForRichText(const std::vector<CARichLabel::Element>& elements, DSize& dimensions, CATextAlignment textAlignment)
{
    
    return  nullptr;
}


CAImage* CAFontProcesstor::imageForText(const std::string& text, const CAFont& font, DSize& dimensions, CATextAlignment textAlignment)
{
    
    
    
    
    unsigned char *bytes = nullptr;
    ssize_t length = 0;
    unsigned int pixelsWide = 0;
    unsigned int pixelsHigh = 0;
    
    CAData* data = new CAData();
    data->fastSet(bytes, length);
    CAImage* image = CAImage::createWithRawDataNoCache(data, CAImage::PixelFormat::RGBA8888, pixelsWide, pixelsHigh);
    data->release();
    
    return image;
}

float CAFontProcesstor::heightForFont(const CAFont& font)
{
    
    return 0;
}

float CAFontProcesstor::heightForTextAtWidth(const std::string& text, const CAFont& font, float width)
{
    
    return 0;
}

float CAFontProcesstor::widthForTextAtOneLine(const std::string& text, const CAFont& font)
{
    
    return 0;
}
NS_CC_END
