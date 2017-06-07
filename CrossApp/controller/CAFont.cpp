#include "CAFont.h"
#include "platform/CAFTFontCache.h"

NS_CC_BEGIN

CAFont::CAFont(const CAFont& other)
: bold(other.bold)
, underLine(other.underLine)
, deleteLine(other.deleteLine)
, italics(other.italics)
, italicsValue(other.italicsValue)
, wordWrap(other.wordWrap)
, fontSize(other.fontSize)
, fontName(other.fontName)
, color(other.color)
, textAlignment(other.textAlignment)
, verticalTextAlignment(other.verticalTextAlignment)
, shadow(other.shadow)
, stroke(other.stroke)
{

}

CAFont& CAFont::operator= (const CAFont& other)
{
    this->bold                  = other.bold;
    this->underLine             = other.underLine;
    this->deleteLine            = other.deleteLine;
    this->italics               = other.italics;
    this->italicsValue          = other.italicsValue;
    this->wordWrap              = other.wordWrap;
    this->fontSize              = other.fontSize;
    this->fontName              = other.fontName;
    this->color                 = other.color;
    this->textAlignment         = other.textAlignment;
    this->verticalTextAlignment = other.verticalTextAlignment;
    this->shadow                = other.shadow;
    this->stroke                = other.stroke;
    return *this;
}

NS_CC_END
