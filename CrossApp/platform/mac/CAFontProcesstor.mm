

#include "CAFontProcesstor.h"
NS_CC_BEGIN
namespace CAFontProcesstor
{
    
    CAImage* imageForText(const std::string& text, const CAFont& font, const DSize& dimensions)
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
    
    float heightForFont(const CAFont& font)
    {
    
        return 0;
    }
    
    float heightForTextAtWidth(const std::string& text, const CAFont& font, float width)
    {
        
        return 0;
    }
    
    float widthForTextAtOneLine(const std::string& text, const CAFont& font)
    {
        
        return 0;
    }
    
}
NS_CC_END
