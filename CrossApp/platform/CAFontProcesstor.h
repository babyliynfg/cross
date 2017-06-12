
#ifndef __CAFontProcesstor_H__
#define __CAFontProcesstor_H__

#include "CAFontProcesstor.h"
#include "CADensityDpi.h"
#include "view/CARichLabel.h"
NS_CC_BEGIN

class CAImage;
namespace CAFontProcesstor
{
    CAImage* imageForRichText(const std::vector<CARichLabel::Element>& elements, DSize& dimensions, CATextAlignment textAlignment);
    
    CAImage* imageForText(const std::string& text, const CAFont& font, DSize& dimensions, CATextAlignment textAlignment);
    
    float heightForFont(const CAFont& font);
    
    float heightForTextAtWidth(const std::string& text, const CAFont& font, float width);
    
    float widthForTextAtOneLine(const std::string& text, const CAFont& font);
}
NS_CC_END
#endif // __CAFontProcesstor_H__
