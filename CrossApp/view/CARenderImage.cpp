

#include "CARenderImage.h"
#include "basics/CAApplication.h"
#include "platform/platform.h"
#include "renderer/CCRenderer.h"
#include "renderer/ccGLStateCache.h"
#include "support/ccUtils.h"
#include "images/CAImageCache.h"
#include "platform/CAFileUtils.h"
#include "CCGL.h"
#include "support/CANotificationCenter.h"
#include "ccTypes.h"
#include "CCEGLView.h"
#include <string>
#include "basics/CACamera.h"
#include "basics/CAConfiguration.h"

NS_CC_BEGIN

// implementation CARenderImage
CARenderImage::CARenderImage()
: m_pImageView(nullptr)
, m_pImage(nullptr)
, m_pImageCopy(nullptr)
, m_uFBO(0)
, m_uOldFBO(0)
, m_uDepthRenderBufffer(0)
, m_ePixelFormat(CAImage::PixelFormat::RGBA8888)
, m_uClearFlags(0)
, m_sClearColor(ccc4f(0,0,0,1))
, m_fClearDepth(0.0f)
, m_nClearStencil(0)
, m_bAutoDraw(false)
, m_uPixelsWide(0)
, m_uPixelsHigh(0)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // Listen this event to save render Image before come to background.
    // Then it can be restored after coming to foreground on Android.
    CANotificationCenter::getInstance()->addObserver(this,
                                                     callfuncO_selector(CARenderImage::listenToBackground),
                                                     EVENT_COME_TO_BACKGROUND,
                                                     NULL);
    
    CANotificationCenter::getInstance()->addObserver(this,
                                                     callfuncO_selector(CARenderImage::listenToForeground),
                                                     EVENT_COME_TO_FOREGROUND, // this is misspelt
                                                     NULL);
#endif

}

CARenderImage::~CARenderImage()
{
    CC_SAFE_RELEASE(m_pImageView);
    CC_SAFE_RELEASE(m_pImage);
    CC_SAFE_RELEASE(m_pImageCopy);
    glDeleteFramebuffers(1, &m_uFBO);
    if (m_uDepthRenderBufffer)
    {
        glDeleteRenderbuffers(1, &m_uDepthRenderBufffer);
    }
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    CANotificationCenter::getInstance()->removeObserver(this, EVENT_COME_TO_BACKGROUND);
    CANotificationCenter::getInstance()->removeObserver(this, EVENT_COME_TO_FOREGROUND);
#endif

}

void CARenderImage::listenToBackground(CrossApp::CAObject *obj)
{

}

void CARenderImage::listenToForeground(CrossApp::CAObject *obj)
{
// -- regenerate frame buffer object and attach the texture
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_uOldFBO);
    
    glGenFramebuffers(1, &m_uFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);
    
//    m_pImage->setAliasTexParameters();
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pImage->getName(), 0);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uOldFBO);

}

CAImageView * CARenderImage::getImageView()
{
    return m_pImageView;
}

void CARenderImage::setImageView(CAImageView* var)
{
    CC_SAFE_RELEASE(m_pImageView);
    m_pImageView = var;
    CC_SAFE_RETAIN(m_pImageView);
}

unsigned int CARenderImage::getClearFlags() const
{
    return m_uClearFlags;
}

void CARenderImage::setClearFlags(unsigned int uClearFlags)
{
    m_uClearFlags = uClearFlags;
}

const CAColor4F& CARenderImage::getClearColor() const
{
    return m_sClearColor;
}

void CARenderImage::setClearColor(const CAColor4F &clearColor)
{
    m_sClearColor = clearColor;
}

float CARenderImage::getClearDepth() const
{
    return m_fClearDepth;
}

void CARenderImage::setClearDepth(float fClearDepth)
{
    m_fClearDepth = fClearDepth;
}

int CARenderImage::getClearStencil() const
{
    return m_nClearStencil;
}

void CARenderImage::setClearStencil(float fClearStencil)
{
    m_nClearStencil = fClearStencil;
}

bool CARenderImage::isAutoDraw() const
{
    return m_bAutoDraw;
}

void CARenderImage::setAutoDraw(bool bAutoDraw)
{
    m_bAutoDraw = bAutoDraw;
}

void CARenderImage::setKeepMatrix(bool keepMatrix)
{
    m_bKeepMatrix = keepMatrix;
}

CARenderImage * CARenderImage::create(int w, int h, CAImage::PixelFormat eFormat)
{
    CARenderImage *pRet = new CARenderImage();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CARenderImage * CARenderImage::create(int w ,int h, CAImage::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    CARenderImage *pRet = new CARenderImage();

    if(pRet && pRet->initWithWidthAndHeight(w, h, eFormat, uDepthStencilFormat))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

CARenderImage * CARenderImage::create(int w, int h)
{
    CARenderImage *pRet = new CARenderImage();

    if(pRet && pRet->initWithWidthAndHeight(w, h, CAImage::PixelFormat::RGBA8888, 0))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool CARenderImage::initWithWidthAndHeight(int w, int h, CAImage::PixelFormat eFormat)
{
    return initWithWidthAndHeight(w, h, eFormat, 0);
}

bool CARenderImage::initWithWidthAndHeight(int w, int h, CAImage::PixelFormat eFormat, GLuint uDepthStencilFormat)
{
    CCAssert(eFormat != CAImage::PixelFormat::A8, "only RGB and RGBA formats are valid for a render texture");

    bool bRet = false;
    unsigned char *data = NULL;
    do 
    {
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_uOldFBO);

        // textures must be power of two squared
        int powW = 0;
        int powH = 0;
        
        if (CAConfiguration::getInstance()->supportsNPOT())
        {
            powW = w;
            powH = h;
        }
        else
        {
            powW = ccNextPOT(w);
            powH = ccNextPOT(h);
        }
        
        auto dataLen = powW * powH * 4;
        data = (unsigned char *)malloc(dataLen);
        CC_BREAK_IF(! data);

        memset(data, 0, dataLen);
        m_ePixelFormat = eFormat;
        m_uPixelsWide = powW;
        m_uPixelsHigh = powH;
        
        m_pImage = new (std::nothrow) CAImage();
        m_pImage->initWithRawData(data, m_ePixelFormat, m_uPixelsWide, m_uPixelsHigh);
        
        GLint oldRBO;
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRBO);
        
        if (CAConfiguration::getInstance()->checkForGLExtension("GL_QCOM"))
        {
            m_pImageCopy = new (std::nothrow) CAImage();
            m_pImageCopy->initWithRawData(data, m_ePixelFormat, m_uPixelsWide, m_uPixelsHigh);
        }
        
        // generate FBO
        glGenFramebuffers(1, &m_uFBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);

        // associate Image with FBO
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pImage->getName(), 0);

        if (uDepthStencilFormat != 0)
        {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            if(CAConfiguration::getInstance()->supportsOESPackedDepthStencil())
            {
                //create and attach depth buffer
                glGenRenderbuffers(1, &m_uDepthRenderBufffer);
                glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderBufffer);
                glRenderbufferStorage(GL_RENDERBUFFER, uDepthStencilFormat, (GLsizei)powW, (GLsizei)powH);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);
                
                // if depth format is the one with stencil part, bind same render buffer as stencil attachment
                if (uDepthStencilFormat == GL_DEPTH24_STENCIL8)
                {
                    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);
                }
            }
            else
            {
                
                glGenRenderbuffers(1, &m_uDepthRenderBufffer);
                glGenRenderbuffers(1, &m_uDepthRenderBufffer);
                glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderBufffer);
                
                if(CAConfiguration::getInstance()->supportsOESDepth24())
                {
                    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24_OES, (GLsizei)powW, (GLsizei)powH);
                }
                else
                {
                    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, (GLsizei)powW, (GLsizei)powH);
                }
                
                glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderBufffer);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8,  (GLsizei)powW, (GLsizei)powH);
                
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                          GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);
            }
#else
            
            
            //create and attach depth buffer
            glGenRenderbuffers(1, &m_uDepthRenderBufffer);
            glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderBufffer);
            glRenderbufferStorage(GL_RENDERBUFFER, uDepthStencilFormat, (GLsizei)powW, (GLsizei)powH);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);

            // if depth format is the one with stencil part, bind same render buffer as stencil attachment
            if (uDepthStencilFormat == GL_DEPTH24_STENCIL8)
            {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderBufffer);
            }
#endif
        }
//        // check if it worked (probably worth doing :) )
        CCAssert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Could not attach Image to framebuffer");

        m_pImage->setAliasTexParameters();

        CAImageView* imageView = CAImageView::createWithFrame(DRect(0, 0, m_uPixelsWide, m_uPixelsHigh));
        imageView->setImage(m_pImage);
        imageView->setBlendFunc(BlendFunc_alpha_premultiplied);
        imageView->setOpacityModifyRGB(true);
        imageView->setFlipY(true);
        this->addSubview(imageView);
        this->setImageView(imageView);
        
        glBindRenderbuffer(GL_RENDERBUFFER, oldRBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_uOldFBO);
        
        // Diabled by default.
        m_bAutoDraw = false;

        bRet = true;
    } while (0);
    
    CC_SAFE_FREE(data);
    
    return bRet;
}

void CARenderImage::printscreenWithView(CAView* view)
{
    this->printscreenWithView(view, DPointZero);
}

void CARenderImage::printscreenWithView(CAView* view, DPoint offset)
{
    this->printscreenWithView(view, offset, ccc4(0, 0, 0, 0));
}

void CARenderImage::printscreenWithView(CAView* view, const CAColor4B& backgroundColor)
{
    this->printscreenWithView(view, DPointZero, backgroundColor);
}

void CARenderImage::printscreenWithView(CAView* view, DPoint offset, const CAColor4B& backgroundColor)
{
    CC_RETURN_IF(view == NULL);
    
    DPoint point = DPointZero;
    if (view->getSuperview())
    {
        point.y = view->getSuperview()->m_obContentSize.height;
    }
    else
    {
        point.y = CAApplication::getApplication()->getWinSize().height;
    }
    point.y -= view->m_obContentSize.height;
    point.y += offset.y;
    point.x -= offset.x;
    
    DPoint originalPoint = view->m_obPoint;
    DPoint originalAnchorPoint = view->getAnchorPoint();
    float originalRotationX = view->getRotationX();
    
    view->setRotationX(originalRotationX + 180);
    view->setAnchorPoint(DPoint(0.0f, 1.0f));
    view->setPoint(point);
    
    m_pApplication->getRenderer()->clean();
    experimental::FrameBuffer::clearAllFBOs();
    
    this->beginWithClear(backgroundColor);
    view->visitEve();
    view->visit();
    this->end();
    m_pApplication->getRenderer()->render();
    
    view->setRotationX(originalRotationX);
    view->setAnchorPoint(originalAnchorPoint);
    view->setPoint(originalPoint);
}

void CARenderImage::begin()
{
    CAApplication* application = CAApplication::getApplication();
    CCASSERT(nullptr != application, "CAApplication is null when setting matrix stack");
    
    application->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    m_tProjectionMatrix = application->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
    application->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    m_tTransformMatrix = application->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

    if(!m_bKeepMatrix)
    {
        application->setProjection(application->getProjection());
        
        const DSize texSize = DSize((float)m_uPixelsWide, (float)m_uPixelsHigh);
        
        // Calculate the adjustment ratios based on the old and new projections
        DSize size = application->getWinSize();
        
        float widthRatio = size.width / texSize.width;
        float heightRatio = size.height / texSize.height;
        
        Mat4 orthoMatrix;
        Mat4::createOrthographicOffCenter((float)-1.0 / widthRatio, (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1, 1, &orthoMatrix);
        application->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
    }
    
    m_obGroupCommand.init(0);
    
    Renderer *renderer =  application->getRenderer();
    renderer->addCommand(&m_obGroupCommand);
    renderer->pushGroup(m_obGroupCommand.getRenderQueueID());
    
    m_obBeginCommand.init(0);
    m_obBeginCommand.func = std::bind(&CARenderImage::onBegin, this);
    
    application->getRenderer()->addCommand(&m_obBeginCommand);

}

void CARenderImage::beginWithClear(const CAColor4B& backgroundColor)
{
    beginWithClear(backgroundColor, 0, 0, GL_COLOR_BUFFER_BIT);
}

void CARenderImage::beginWithClear(const CAColor4B& backgroundColor, float depthValue)
{
    beginWithClear(backgroundColor, depthValue, 0, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void CARenderImage::beginWithClear(const CAColor4B& backgroundColor, float depthValue, int stencilValue)
{
    beginWithClear(backgroundColor, depthValue, stencilValue, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
}

void CARenderImage::beginWithClear(const CAColor4B& backgroundColor, float depthValue, int stencilValue, GLbitfield flags)
{
    setClearColor(ccc4FFromccc4B(backgroundColor));
    
    setClearDepth(depthValue);
    
    setClearStencil(stencilValue);
    
    setClearFlags(flags);
    
    this->begin();
    
    //clear screen
    m_obBeginWithClearCommand.init(0);
    m_obBeginWithClearCommand.func = std::bind(&CARenderImage::onClear, this);
    CAApplication::getApplication()->getRenderer()->addCommand(&m_obBeginWithClearCommand);
}

void CARenderImage::end()
{
    m_obEndCommand.init(0);
    m_obEndCommand.func = std::bind(&CARenderImage::onEnd, this);
    
    CAApplication* application = CAApplication::getApplication();
    CCASSERT(nullptr != application, "CAApplication is null when setting matrix stack");
    
    Renderer *renderer = application->getRenderer();
    renderer->addCommand(&m_obEndCommand);
    renderer->popGroup();
    
    application->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    application->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    
}

void CARenderImage::clear(const CAColor4B& backgroundColor)
{
    this->beginWithClear(backgroundColor);
    this->end();
}

void CARenderImage::clearDepth(float depthValue)
{
    setClearDepth(depthValue);
    
    this->begin();
    
    m_tClearDepthCommand.init(0);
    m_tClearDepthCommand.func = std::bind(&CARenderImage::onClearDepth, this);
    
    CAApplication::getApplication()->getRenderer()->addCommand(&m_tClearDepthCommand);
    
    this->end();
}

void CARenderImage::clearStencil(int stencilValue)
{
    // save old stencil value
    int stencilClearValue;
    glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &stencilClearValue);

    glClearStencil(stencilValue);
    glClear(GL_STENCIL_BUFFER_BIT);

    // restore clear color
    glClearStencil(stencilClearValue);
}

void CARenderImage::onBegin()
{
    //
    CAApplication *application = CAApplication::getApplication();
    
    m_tOldProjMatrix = application->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
    application->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, m_tProjectionMatrix);
    
    m_tOldProjMatrix = application->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    application->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, m_tTransformMatrix);
    
    if(!m_bKeepMatrix)
    {
        application->setProjection(application->getProjection());
        const DSize texSize = DSize((float)m_uPixelsWide, (float)m_uPixelsHigh);
        
        // Calculate the adjustment ratios based on the old and new projections
        DSize size = application->getWinSize();
        float widthRatio = size.width / texSize.width;
        float heightRatio = size.height / texSize.height;
        
        Mat4 orthoMatrix;
        Mat4::createOrthographicOffCenter((float)-1.0 / widthRatio, (float)1.0 / widthRatio, (float)-1.0 / heightRatio, (float)1.0 / heightRatio, -1, 1, &orthoMatrix);
        application->multiplyMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, orthoMatrix);
    }
    
    //calculate viewport
    {
        glViewport(0, 0, (GLsizei)m_uPixelsWide, (GLsizei)m_uPixelsHigh);
    }
    
    // Adjust the orthographic projection and viewport
    
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &m_uOldFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_uFBO);
    
    // TODO: move this to configuration, so we don't check it every time
    /*  Certain Qualcomm Adreno GPU's will retain data in memory after a frame buffer switch which corrupts the render to the texture. The solution is to clear the frame buffer before rendering to the texture. However, calling glClear has the unintended result of clearing the current texture. Create a temporary texture to overcome this. At the end of RenderTexture::begin(), switch the attached texture to the second one, call glClear, and then switch back to the original texture. This solution is unnecessary for other devices as they don't have the same issue with switching frame buffers.
     */
    char* glExtensions = (char *)glGetString(GL_EXTENSIONS);
    if (glExtensions && strstr(glExtensions, "GL_QCOM"))
    {
        // -- bind a temporary texture so we can clear the render buffer without losing our texture
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pImageCopy->getName(), 0);
        CHECK_GL_ERROR_DEBUG();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_pImage->getName(), 0);
    }
}

void CARenderImage::onEnd()
{
    CAApplication *application = CAApplication::getApplication();
    
    glBindFramebuffer(GL_FRAMEBUFFER, m_uOldFBO);
    
    // restore viewport
    application->setViewport();
    const auto& vp = CACamera::getDefaultViewport();
    glViewport(vp._left, vp._bottom, vp._width, vp._height);
    //
    application->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION, m_tOldProjMatrix);
    application->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, m_tOldProjMatrix);
    
}

void CARenderImage::onClear()
{
    // save clear color
    GLfloat oldClearColor[4] = {0.0f};
    GLfloat oldDepthClearValue = 0.0f;
    GLint oldStencilClearValue = 0;
    
    // backup and set
    if (m_uClearFlags & GL_COLOR_BUFFER_BIT)
    {
        glGetFloatv(GL_COLOR_CLEAR_VALUE, oldClearColor);
        glClearColor(m_sClearColor.r, m_sClearColor.g, m_sClearColor.b, m_sClearColor.a);
    }
    
    if (m_uClearFlags & GL_DEPTH_BUFFER_BIT)
    {
        glGetFloatv(GL_DEPTH_CLEAR_VALUE, &oldDepthClearValue);
        glClearDepth(m_fClearDepth);
    }
    
    if (m_uClearFlags & GL_STENCIL_BUFFER_BIT)
    {
        glGetIntegerv(GL_STENCIL_CLEAR_VALUE, &oldStencilClearValue);
        glClearStencil(m_nClearStencil);
    }
    
    // clear
    glClear(m_uClearFlags);
    
    // restore
    if (m_uClearFlags & GL_COLOR_BUFFER_BIT)
    {
        glClearColor(oldClearColor[0], oldClearColor[1], oldClearColor[2], oldClearColor[3]);
    }
    if (m_uClearFlags & GL_DEPTH_BUFFER_BIT)
    {
        glClearDepth(oldDepthClearValue);
    }
    if (m_uClearFlags & GL_STENCIL_BUFFER_BIT)
    {
        glClearStencil(oldStencilClearValue);
    }
}

void CARenderImage::onClearDepth()
{
    //! save old depth value
    GLfloat depthClearValue;
    glGetFloatv(GL_DEPTH_CLEAR_VALUE, &depthClearValue);
    
    glClearDepth(m_uClearFlags);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    // restore clear color
    glClearDepth(depthClearValue);
}

void CARenderImage::visitEve()
{
    CAView::visitEve();
    if (m_pImageView)
    {
        m_pImageView->visitEve();
    }
}

void CARenderImage::visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    CC_RETURN_IF(!m_bVisible);
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    CAApplication* application = CAApplication::getApplication();

    application->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    application->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, m_tModelViewTransform);
    
    m_pImageView->visit(renderer, m_tModelViewTransform, flags);
    if (isVisitableByVisitingCamera())
    {
        draw(renderer, m_tModelViewTransform, flags);
    }
    
    application->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void CARenderImage::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    if( m_bAutoDraw)
    {
        //Begin will create a render group using new render target
        begin();
        
        //clear screen
        m_obClearCommand.init(0);
        m_obClearCommand.func = std::bind(&CARenderImage::onClear, this);
        renderer->addCommand(&m_obClearCommand);
        
        //! make sure all children are drawn
        sortAllSubviews();
        
        for (auto& subview : m_obSubviews)
        {
            CC_CONTINUE_IF(subview == m_pImageView);
            subview->visit(renderer, transform, flags);
        }

        //End will pop the current render group
        end();
	}
}

bool CARenderImage::saveToFile(const char *szFilePath)
{
    bool bRet = false;
    if (m_pImageView->getImage())
    {
        bRet = m_pImageView->getImage()->saveToFile(szFilePath);
    }
    return bRet;
}


void CARenderImage::setContentSize(const DSize& contentSize)
{
    CAView::setContentSize(DSize(m_uPixelsWide, m_uPixelsHigh));
}
NS_CC_END
