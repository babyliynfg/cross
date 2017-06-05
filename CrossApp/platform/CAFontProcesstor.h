
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "CAFontProcesstor.h"
#include "images/CAImage.h"
#include "CADensityDpi.h"
NS_CC_BEGIN
namespace CAFontProcesstor
{
    
    CAImage* imageForText(const std::string& text, const CAFont& font, DSize& dimensions);
    
    float heightForFont(const CAFont& font);
    
    float heightForTextAtWidth(const std::string& text, const CAFont& font, float width);
    
    float widthForTextAtOneLine(const std::string& text, const CAFont& font);
    
}
NS_CC_END
#endif // __PLATFORM_H__
