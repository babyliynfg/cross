#include "CARichLabel.h"
#include "ccMacros.h"
#include "CAFontProcesstor.h"
#include "device/CADevice.h"
NS_CC_BEGIN

CARichLabel::Element::Element(const std::string& text, const CAFont& font)
: text(text)
, font(font)
{

}

///////////////////////////////////////////////////
CARichLabel::CARichLabel()
: m_bUpdateImage(false)
, m_eTextAlignment(CATextAlignment::Left)
, m_eVerticalTextAlignment(CAVerticalTextAlignment::Top)
, m_iNumberOfLine(0)
, m_obPadding(DSizeZero)
, m_obLabelSize(DSizeZero)
{
}

CARichLabel::~CARichLabel()
{
}

CARichLabel* CARichLabel::create()
{
	CARichLabel *label = new CARichLabel();
	if (label && label->init())
	{
		label->autorelease();
		return label;
	}
	CC_SAFE_DELETE(label);
	return NULL;
}

CARichLabel* CARichLabel::createWithFrame(const DRect& rect)
{
	CARichLabel *label = new CARichLabel();
	if (label && label->initWithFrame(rect))
	{
		label->autorelease();
		return label;
	}
	CC_SAFE_DELETE(label);
	return NULL;
}

CARichLabel* CARichLabel::createWithCenter(const DRect& rect)
{
	CARichLabel *label = new CARichLabel();
	if (label && label->initWithCenter(rect))
	{
		label->autorelease();
		return label;
	}

	CC_SAFE_DELETE(label);
	return NULL;
}

CARichLabel* CARichLabel::createWithLayout(const DLayout& layout)
{
    CARichLabel *label = new CARichLabel();
    if (label && label->initWithLayout(layout))
    {
        label->autorelease();
        return label;
    }
    
    CC_SAFE_DELETE(label);
    return NULL;
}

void CARichLabel::setContentSize(const CrossApp::DSize &var)
{
	if (!m_obContentSize.equals(var))
	{
		CAView::setContentSize(var);
		this->updateImageDraw();
	}
}

void CARichLabel::updateImageRect()
{
	GLfloat x1, x2, y1, y2;
	x1 = 0;
	y1 = 0;
	y1 = m_obContentSize.height - m_obRect.size.height - y1;
	y1 = y1 - 0;
	x2 = x1 + m_obRect.size.width;
	x2 = MAX(x1, x2);
	y2 = y1 + m_obRect.size.height;
	y2 = MAX(y1, y2);
	m_sQuad.bl.vertices = DPoint3D(x1, y1, m_fPointZ);
	m_sQuad.br.vertices = DPoint3D(x2, y1, m_fPointZ);
	m_sQuad.tl.vertices = DPoint3D(x1, y2, m_fPointZ);
	m_sQuad.tr.vertices = DPoint3D(x2, y2, m_fPointZ);
}

void CARichLabel::updateImageDraw()
{
	m_bUpdateImage = true;
	this->updateDraw();
}

void CARichLabel::updateImage()
{
	int fontHeight = 0;
	int defaultLineSpace = fontHeight / 5;

	DSize size;
	unsigned int linenumber = (int)m_obContentSize.height / fontHeight;
	if (linenumber == 0)
	{
		size = m_obContentSize;
	}
	else
	{
		size = DSize(m_obContentSize.width, (defaultLineSpace + fontHeight) * (linenumber+1));
	}

	CAImage* image = nullptr;
	this->setImage(image);
    if (image)
    {
        DRect rect = DRectZero;
        rect.size.width = MIN(m_obContentSize.width, image->getContentSize().width);
        rect.size.height = m_obContentSize.height;
        
        this->setImageRect(rect);
    }
}

void CARichLabel::visitEve()
{
    CAView::visitEve();
	if (m_bUpdateImage)
	{
		m_bUpdateImage = false;
		this->updateImage();
	}
}

void CARichLabel::appendText(const std::string& text, const CAFont& font)
{
    m_vElements.push_back(Element(text, font));
    this->updateImageDraw();
}

void CARichLabel::clear()
{
    m_vElements.clear();
    updateImageDraw();
}

void CARichLabel::setVerticalTextAlignmet(const CAVerticalTextAlignment& var)
{
    m_eVerticalTextAlignment = var;
}

void CARichLabel::setTextAlignment(const CATextAlignment& var)
{
    m_eTextAlignment = var;
}

void CARichLabel::setNumberOfLine(unsigned int var)
{
    m_iNumberOfLine = var;
}

const DSize& CARichLabel::getLabelSize()
{
    return m_obLabelSize;
}

NS_CC_END
