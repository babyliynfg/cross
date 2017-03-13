
#include "CCEGLView.h"
#include "EAGLView.h"
#include "CAApplicationCaller.h"
#include "CCSet.h"
#include "CATouch.h"
#include "CATouchDispatcher.h"
#include "basics/CAApplication.h"
#include "basics/CACamera.h"
#import "EAGLView.h"

NS_CC_BEGIN

CCEGLView* CCEGLView::s_sharedView = NULL;

CCEGLView* CCEGLView::sharedOpenGLView(void)
{
    if (!s_sharedView)
    {
        s_sharedView = new CCEGLView();
    }
    return s_sharedView;
}

CCEGLView::CCEGLView(void)
{

}

CCEGLView::~CCEGLView(void)
{
    s_sharedView = NULL;
}

void CCEGLView::setFrameSize(float width, float height)
{
    CCEGLViewProtocol::setFrameSize(width, height);
    
    if (width / height > 1.25f)
    {
        this->setStatusBarOrientation(CAInterfaceOrientation::Landscape);
    }
    else
    {
        this->setStatusBarOrientation(CAInterfaceOrientation::Portrait);
    }
}

bool CCEGLView::isOpenGLReady(void)
{
    return [EAGLView sharedEGLView] != NULL;
}

bool CCEGLView::setContentScaleFactor(float contentScaleFactor)
{
    return false;
}

void CCEGLView::end(void)
{
    [[CAApplicationCaller sharedCAApplicationCaller] end];
    
    // destroy EAGLView
    [[EAGLView sharedEGLView] removeFromSuperview];
    
    delete this;
}

void CCEGLView::swapBuffers()
{
	[[EAGLView sharedEGLView] swapBuffers];
}

void CCEGLView::setIMEKeyboardState(bool bOpen)
{
    if (bOpen)
    {
        [[EAGLView sharedEGLView] becomeFirstResponder];
    }
    else
    {
        [[EAGLView sharedEGLView] resignFirstResponder];
    }
}

void CCEGLView::setViewPortInPoints(float x , float y , float w , float h)
{
    float frameZoomFactor = [[EAGLView sharedEGLView] frameZoomFactor];
    
    experimental::Viewport vp((float)(x * m_fScale * frameZoomFactor + m_obViewPortRect.origin.x * frameZoomFactor),
                              (float)(y * m_fScale * frameZoomFactor + m_obViewPortRect.origin.y * frameZoomFactor),
                              (float)(w * m_fScale * frameZoomFactor),
                              (float)(h * m_fScale * frameZoomFactor));
    
    CACamera::setDefaultViewport(vp);
}

void CCEGLView::setScissorInPoints(float x , float y , float w , float h)
{
    float frameZoomFactor = [[EAGLView sharedEGLView] frameZoomFactor];
    
    glScissor((GLint)(x * m_fScale * frameZoomFactor + m_obViewPortRect.origin.x * frameZoomFactor),
              (GLint)(y * m_fScale * frameZoomFactor + m_obViewPortRect.origin.y * frameZoomFactor),
              (GLsizei)ceilf(w * m_fScale * frameZoomFactor),
              (GLsizei)ceilf(h * m_fScale * frameZoomFactor));
}

void CCEGLView::setMultiTouchMask(bool mask)
{
	//EAGLView *glView = [EAGLView sharedEGLView];
	//glView.multipleTouchEnabled = mask ? YES : NO;
}

NS_CC_END // end of namespace CossApp;
