#include "CAFont.h"
#include "platform/CAFTFontCache.h"

NS_CC_BEGIN

CAFont::CAFont(const CAFont& other)
: fontSize(other.fontSize)
, fontName(other.fontName)
, color(other.color)
, italics(other.italics)
, bold(other.bold)
, underLine(other.underLine)
, deleteLine(other.deleteLine)
, wordWrap(other.wordWrap)
, textAlignment(other.textAlignment)
, verticalTextAlignment(other.verticalTextAlignment)
, shadow(other.shadow)
, stroke(other.stroke)
{

}

CAFont& CAFont::operator= (const CAFont& other)
{
    this->fontSize              = other.fontSize;
    this->fontName              = other.fontName;
    this->color                 = other.color;
    this->italics               = other.italics;
    this->bold                  = other.bold;
    this->underLine             = other.underLine;
    this->deleteLine            = other.deleteLine;
    this->wordWrap              = other.wordWrap;
    this->textAlignment         = other.textAlignment;
    this->verticalTextAlignment = other.verticalTextAlignment;
    this->shadow                = other.shadow;
    this->stroke                = other.stroke;
    return *this;
}

NS_CC_END
