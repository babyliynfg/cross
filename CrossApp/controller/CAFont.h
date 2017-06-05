#ifndef CAFont_h__
#define CAFont_h__

#include "ccTypes.h"
#include "basics/CAObject.h"

using std::string;

NS_CC_BEGIN


enum class CAVerticalTextAlignment
{
    Top,
    Center,
    Bottom,
};

enum class CATextAlignment
{
    Left,
    Center,
    Right,
};

class CC_DLL CAFontShadow
{
public:

    bool   shadowEnabled;
    DSize  shadowOffset;
    float  shadowBlur;
    float  shadowOpacity;
    
public:
    
    CAFontShadow()
    : shadowEnabled(false)
    , shadowBlur(0)
    , shadowOpacity(0)
    {}
};

class CC_DLL CAFontStroke
{
public:

    bool        strokeEnabled;
    CAColor4B   strokeColor;
    float       strokeSize;
    
public:
    
    CAFontStroke()
    : strokeEnabled(false)
    , strokeColor(CAColor4B::BLACK)
    , strokeSize(0)
    {}
    
};

class CC_DLL CAFont
{
public:

    bool                    bold;
    
    bool                    underLine;
    
    bool                    deleteLine;
    
    bool                    italics;
    
    bool                    wordWrap;
    
    std::string             fontName;
    
    unsigned int            fontSize;
    
    CAColor4B               color;
    
    CATextAlignment         textAlignment;
    
    CAVerticalTextAlignment verticalTextAlignment;
    
    CAFontShadow            shadow;
    
    CAFontStroke            stroke;
    
public:
    
    CAFont()
    : fontSize(24)
    , fontName("")
    , color(CAColor4B::BLACK)
    , italics(false)
    , bold(false)
    , underLine(false)
    , deleteLine(false)
    , wordWrap(false)
    , textAlignment(CATextAlignment::Left)
    , verticalTextAlignment(CAVerticalTextAlignment::Top)
    {
        
    }
    
    CAFont(const CAFont& other);
    
    CAFont& operator= (const CAFont& other);
};


#define g_CAFontCache CAFontCache::sharedStyleCache()

NS_CC_END

#endif // CAFont_h__
