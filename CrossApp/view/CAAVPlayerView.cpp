
#include "CAAVPlayerView.h"
#include "CAAVPlayerViewImpl.h"
#include "images/CAImageCache.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCRenderState.h"
#include "animation/CAViewAnimation.h"
#include "basics/CAScheduler.h"
NS_CC_BEGIN

CAAVPlayerView::CAAVPlayerView()
: m_fX(0)
, m_fY(0)
, m_fWidth(0)
, m_fHeight(0)
, m_pImpl(nullptr)
{

}

CAAVPlayerView::~CAAVPlayerView()
{
    CC_SAFE_DELETE(m_pImpl);
}

CAAVPlayerView* CAAVPlayerView::createWithFrame(const DRect& rect)
{
    CAAVPlayerView * pRet = new CAAVPlayerView();
    if (pRet && pRet->initWithFrame(rect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CAAVPlayerView* CAAVPlayerView::createWithCenter(const DRect& rect)
{
    CAAVPlayerView * pRet = new CAAVPlayerView();
    if (pRet && pRet->initWithCenter(rect))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CAAVPlayerView* CAAVPlayerView::createWithLayout(const CrossApp::DLayout &layout)
{
    CAAVPlayerView * pRet = new CAAVPlayerView();
    if (pRet && pRet->initWithLayout(layout))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}


CAAVPlayerView *CAAVPlayerView::create()
{
    CAAVPlayerView *pRet = new CAAVPlayerView();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool CAAVPlayerView::init()
{
    m_pImpl = new CAAVPlayerViewImpl(this);
    return true;
}

void CAAVPlayerView::setUrl(const std::string& uri)
{
    m_pImpl->setUrl(uri);
}

void CAAVPlayerView::setFilePath(const std::string& uri)
{
    m_pImpl->setFilePath(uri);
}

void CAAVPlayerView::play()
{
    m_pImpl->play();
}

void CAAVPlayerView::pause()
{
    m_pImpl->pause();
}

void CAAVPlayerView::stop()
{
    m_pImpl->stop();
}

float CAAVPlayerView::getDuration()
{
    return m_pImpl->getDuration();
}

float CAAVPlayerView::getCurrentTime()
{
    return m_pImpl->getCurrentTime();
}

void CAAVPlayerView::setCurrentTime(float current)
{
    m_pImpl->setCurrentTime(current);
}

void CAAVPlayerView::setImage(CAImage* image)
{
    CAView::setImage(image);
    if (image)
    {
        DRect rect = DRectZero;
        rect.size = image->getContentSize();
        this->setImageRect(rect);
    }
}

void CAAVPlayerView::updateImageRect()
{
    GLfloat x1,x2,y1,y2;
    x1 = 0;
    y1 = 0;
    x2 = m_obContentSize.width;
    y2 = m_obContentSize.height;
    
    if (m_pobImage)
    {
        GLfloat scaleX = m_obContentSize.width / m_pobImage->getContentSize().width;
        GLfloat scaleY = m_obContentSize.height / m_pobImage->getContentSize().height;
        GLfloat scale = MIN(scaleX, scaleY);
        GLfloat width = m_pobImage->getContentSize().width * scale;
        GLfloat height = m_pobImage->getContentSize().height * scale;
        x1 = (m_obContentSize.width - width) / 2;
        y1 = (m_obContentSize.height - height) / 2;
        x2 = x1 + width;
        y2 = y1 + height;
    }
    
    m_sQuad.bl.vertices = DPoint3D(x1, y1, m_fPointZ);
    m_sQuad.br.vertices = DPoint3D(x2, y1, m_fPointZ);
    m_sQuad.tl.vertices = DPoint3D(x1, y2, m_fPointZ);
    m_sQuad.tr.vertices = DPoint3D(x2, y2, m_fPointZ);
}


NS_CC_END
