//
//  CALabel.cpp
//  project
//
//  Created by lh on 14-5-12.
//
//

#include "CALabel.h"
#include "ccMacros.h"
#include <locale>
#include <cstdlib>
#include "renderer/CCGLProgramState.h"
#include "platform/CAClipboard.h"
#include "basics/CAApplication.h"
#include "support/ccUTF8.h"
#include "CAFontProcesstor.h"

NS_CC_BEGIN


CALabel::CALabel()
:m_nNumberOfLine(0)
,m_nText("")
,m_cLabelSize(DSizeZero)
,pTextHeight(0)
,m_bFitFlag(false)
,m_bUpdateImage(false)
,m_iLineSpacing(0)
,m_bEnableCopy(false)
{
    m_obContentSize = DSizeZero;
}

CALabel::~CALabel()
{
    
}

bool CALabel::init()
{
    if (!CAView::init())
    {
        return false;
    }
    
    this->setTouchBeganCallback([=](CATouch *pTouch, CAEvent *pEvent)
    {
        CAScheduler::getScheduler()->scheduleOnce([&](float de)
        {
            if (m_bEnableCopy)
            {
                CATextToolBarView *pToolBar = CATextToolBarView::create();
                pToolBar->addButton(UTF8("\u590d\u5236"), std::bind(&CALabel::copySelectText, this));
                pToolBar->show();
            }
        }, "function", this, 1.0f);
        return true;
    });
    
    this->setTouchMovedCallback([=](CATouch *pTouch, CAEvent *pEvent)
    {
        CAScheduler::getScheduler()->unschedule("function", this);
    });
    
    this->setTouchEndedCallback([=](CATouch *pTouch, CAEvent *pEvent)
    {
        CAScheduler::getScheduler()->unschedule("function", this);
    });
    
    this->setTouchCancelledCallback([=](CATouch *pTouch, CAEvent *pEvent)
    {
        CAScheduler::getScheduler()->unschedule("function", this);
    });
    
    
    return true;
}

CALabel *CALabel::create()
{
    CALabel *label = new CALabel();
    if (label && label->init())
    {
        label->autorelease();
        return label;
    }
    CC_SAFE_DELETE(label);
    return NULL;
}

CALabel *CALabel::createWithFrame(const DRect& rect)
{
    CALabel *label = new CALabel();
    if (label && label->initWithFrame(rect))
    {
        label->autorelease();
        return label;
    }
    CC_SAFE_DELETE(label);
    return NULL;
}

CALabel* CALabel::createWithCenter(const DRect &rect)
{
    CALabel *label = new CALabel();
    if (label && label->initWithCenter(rect))
    {
        label->autorelease();
        return label;
    }
    
    CC_SAFE_DELETE(label);
    return NULL;
}

CALabel* CALabel::createWithLayout(const CrossApp::DLayout &layout)
{
    CALabel *label = new CALabel();
    if (label && label->initWithLayout(layout))
    {
        label->autorelease();
        return label;
    }
    
    CC_SAFE_DELETE(label);
    return NULL;
}

void CALabel::updateImageDraw()
{
    m_bUpdateImage = true;
    this->updateDraw();
}

void CALabel::updateImage()
{
    int fontHeight = CAFontProcesstor::heightForFont(m_obFont);
	int defaultLineSpace = fontHeight / 4;
 
    unsigned int linenumber = (int)m_obContentSize.height / fontHeight;

    DSize size = DSizeZero;
    if (m_bFitFlag)
    {
        float width = CAFontProcesstor::widthForTextAtOneLine(m_nText, m_obFont);
        if (width > m_obContentSize.width)
        {
            if (m_nNumberOfLine > 1)
            {
				size = DSize(m_obContentSize.width, (defaultLineSpace + m_iLineSpacing + fontHeight) * m_nNumberOfLine);
            }
            else if (m_nNumberOfLine == 1)
            {
				size = DSize(width, fontHeight);
            }
            else
            {
                size.width = m_obContentSize.width;
                size.height = CAFontProcesstor::heightForTextAtWidth(m_nText, m_obFont, size.width);
            }
        }
        else
        {
            size.height = fontHeight;
			size.width = width;
        }
    }
    else
    {
        if (linenumber == 0)
		{
			size = m_obContentSize;
		}
		else
		{
			if (m_nNumberOfLine > 0)
			{
				size = DSize(m_obContentSize.width, (defaultLineSpace + m_iLineSpacing + fontHeight) * MIN(m_nNumberOfLine, linenumber));
			}
			else
			{
				size = DSize(m_obContentSize.width, (defaultLineSpace + m_iLineSpacing + fontHeight) * linenumber);
			}
		}
    }
    
    CAImage* image = CAFontProcesstor::imageForText(m_nText, m_obFont, size);


    this->setImage(image);
	CC_RETURN_IF(image == NULL);
    m_cLabelSize = size;

    DRect rect = DRectZero;
    rect.size.width = m_obContentSize.width;
    rect.size.height = size.height;
    
    float width = m_bFitFlag ? image->getContentSize().width : MIN(m_obContentSize.width, image->getContentSize().width);
    
    rect.size.width = width;

    switch (m_obFont.verticalTextAlignment)
    {
        case CAVerticalTextAlignment::Top:
            pTextHeight = 0;
            break;
            
        case CAVerticalTextAlignment::Center:
            pTextHeight = (m_obContentSize.height - rect.size.height) / 2;
            break;
            
        case CAVerticalTextAlignment::Bottom:
            pTextHeight = m_obContentSize.height - rect.size.height;
            break;
            
        default:
            break;
    }

    if (m_bFitFlag)
    {
        if (!size.equals(m_obContentSize))
        {
            if (m_eLayoutType == 0)
            {
                DRect rect = this->getFrame();
                rect.size = size;
                this->setFrame(rect);
            }
            else if (m_eLayoutType == 1)
            {
                DRect rect = this->getCenter();
                rect.size = size;
                this->setCenter(rect);
            }
        }
    }
    this->setImageRect(rect);
}

void CALabel::updateImageRect()
{
    GLfloat x1,x2,y1,y2;
    x1 = 0;
    y1 = 0;
    y1 = m_obContentSize.height - m_obRect.size.height - y1;
    y1 = y1 - pTextHeight;
    x2 = x1 + m_obRect.size.width;
    x2 = MAX(x1, x2);
    y2 = y1 + m_obRect.size.height;
    y2 = MAX(y1, y2);
    m_sQuad.bl.vertices = DPoint3D(x1, y1, m_fPointZ);
    m_sQuad.br.vertices = DPoint3D(x2, y1, m_fPointZ);
    m_sQuad.tl.vertices = DPoint3D(x1, y2, m_fPointZ);
    m_sQuad.tr.vertices = DPoint3D(x2, y2, m_fPointZ);
}

void CALabel::copySelectText()
{
	CAClipboard::setText(m_nText);
}

void CALabel::sizeToFit()
{
    m_bFitFlag = true;
    if(m_nText.empty())
    {
        return;
    }
    this->updateImageDraw();
}

void CALabel::unsizeToFit()
{
    m_bFitFlag = false;
}

void CALabel::setText(const string& var)
{
    CC_RETURN_IF(m_nText.compare(var) == 0);
    m_nText = var;
    this->updateImageDraw();
}

void CALabel::setTextAlignment(const CATextAlignment& var)
{
    m_obFont.textAlignment = var;
    if(m_nText.empty())
    {
        return;
    }
   this->updateImageDraw();
}

const string& CALabel::getText()
{
    return m_nText;
}

unsigned int CALabel::getNumberOfLine()
{
    return m_nNumberOfLine;
}

void CALabel::setNumberOfLine(unsigned int var)
{
    m_nNumberOfLine = var;
    if(m_nText.empty())
    {
        return;
    }
    this->updateImageDraw();
}

void CALabel::setFont(const CrossApp::CAFont &var)
{
    m_obFont = var;
    if(m_nText.empty())
    {
        return;
    }
    this->updateImageDraw();
}

const CAFont& CALabel::getFont()
{
    return m_obFont;
}

void CALabel::setFontSize(unsigned int var)
{
    m_obFont.fontSize = var;
    if(m_nText.empty())
    {
        return;
    }
    this->updateImageDraw();
}

unsigned int CALabel::getFontSize()
{
    return m_obFont.fontSize;
}

void CALabel::setFontName(const string& var)
{
    m_obFont.fontName = var;
    if(m_nText.empty())
    {
        return;
    }
    this->updateImageDraw();
}

const std::string& CALabel::getFontName()
{
    return m_obFont.fontName;
}

void CALabel::setBold(bool var)
{
    m_obFont.bold = var;
    this->updateImageDraw();
}

bool CALabel::isBold()
{
    return m_obFont.bold;
}

void CALabel::setUnderLine(bool var)
{
    m_obFont.underLine = var;
    this->updateImageDraw();
}

bool CALabel::isUnderLine()
{
    return m_obFont.underLine;
}

void CALabel::setDeleteLine(bool var)
{
    m_obFont.deleteLine = var;
    this->updateImageDraw();
}

bool CALabel::isDeleteLine()
{
    return m_obFont.deleteLine;
}


void CALabel::setItalics(bool var)
{
    m_obFont.italics = var;
    this->updateImageDraw();
}

bool CALabel::isItalics()
{
    return m_obFont.italics;
}

const CAColor4B& CALabel::getColor(void)
{
    return m_obFont.color;
}

void CALabel::setColor(const CAColor4B& color)
{
    m_obFont.color = color;
    updateImage();
    CAView::setColor(CAColor4B(255, 255, 255, color.a));
}

void CALabel::setLineSpacing(int var)
{
    CC_RETURN_IF(m_iLineSpacing == var);
	m_iLineSpacing = var;
	this->updateImageDraw();
}

int CALabel::getLineSpacing()
{
	return m_iLineSpacing;
}

void CALabel::setWordWrap(bool var)
{
	m_obFont.wordWrap = var;
	this->updateImageDraw();
}

void CALabel::setVerticalTextAlignmet(const CAVerticalTextAlignment& var)
{
    m_obFont.verticalTextAlignment = var;
    if(m_nText.empty())
    {
        return;
    }
    this->updateImageDraw();
}

void CALabel::setContentSize(const CrossApp::DSize &var)
{
    DSize size = var;
    size.width = MAX(size.width, m_obFont.fontSize);
    size.height = MAX(size.height, m_obFont.fontSize);
    
    if (!m_obContentSize.equals(size))
    {
        CAView::setContentSize(size);
        this->updateImageDraw();
    }
}

void CALabel::visitEve()
{
    if (m_bUpdateImage)
    {
        m_bUpdateImage = false;
        this->updateImage();
    }
    CAView::visitEve();
}

NS_CC_END
