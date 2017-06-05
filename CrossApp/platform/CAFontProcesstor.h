
#ifndef __CAFontProcesstor_H__
#define __CAFontProcesstor_H__

#include "CAFontProcesstor.h"
#include "CADensityDpi.h"
NS_CC_BEGIN

class CAImage;
namespace CAFontProcesstor
{
    
    CAImage* imageForText(const std::string& text, const CAFont& font, DSize& dimensions);
    
    float heightForFont(const CAFont& font);
    
    float heightForTextAtWidth(const std::string& text, const CAFont& font, float width);
    
    float widthForTextAtOneLine(const std::string& text, const CAFont& font);
    
}
NS_CC_END
#endif // __CAFontProcesstor_H__
