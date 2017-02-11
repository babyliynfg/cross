
#include "renderer/CCFrameBuffer.h"
#include "renderer/CCRenderer.h"
#include "basics/CAApplication.h"

NS_CC_BEGIN
namespace experimental{
FrameBuffer* FrameBuffer::_defaultFBO = nullptr;
std::set<FrameBuffer*> FrameBuffer::_frameBuffers;

Viewport::Viewport(float left, float bottom, float width, float height)
: _left(left)
, _bottom(bottom)
, _width(width)
, _height(height)
{
}

Viewport::Viewport()
{
    _left = _bottom = 0.f;
    _width = _height = 1.0f;
}

RenderTargetBase::RenderTargetBase()
{
    
}

RenderTargetBase::~RenderTargetBase()
{
    
}

bool RenderTargetBase::init(unsigned int width, unsigned int height)
{
    _width = width;
    _height = height;
    return true;
}

RenderTarget* RenderTarget::create(unsigned int width, unsigned int height, CAImage::PixelFormat format/* = CAImage::PixelFormat_RGBA8888*/)
{
    auto result = new (std::nothrow) RenderTarget();
    if(result && result->init(width, height,format))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool RenderTarget::init(unsigned int width, unsigned int height, CAImage::PixelFormat format)
{
    if(!RenderTargetBase::init(width, height))
    {
        return false;
    }
    _image = new (std::nothrow) CAImage();
    if(nullptr == _image) return false;
    //TODO: FIX me, get the correct bit depth for pixelformat
    auto dataLen = width * height * 4;
    unsigned char* data = (unsigned char*)malloc(dataLen);
    if( nullptr == data) return false;
    
    memset(data, 0, dataLen);
    if(_image->initWithRawData(data, format, width, height))
    {
        _image->autorelease();
        CC_SAFE_RETAIN(_image);
        free(data);
    }
    else
    {
        CC_SAFE_DELETE(_image);
        free(data);
        return false;
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _rebuildTextureListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        auto dataLen = _width * _height * 4;
        auto data = malloc(dataLen);
        _texture->initWithData(data, dataLen,_texture->getPixelFormat(), _width, _height, Size(_width, _height));
        free(data);
        CCLOG("RenderTarget Texture recreated is %d", _texture->getName());
    });
    
    CAApplication::getApplication()->getEventDispatcher()->addEventListenerWithFixedPriority(_rebuildTextureListener, -1);
#endif
    return true;
}

RenderTarget::RenderTarget()
: _image(nullptr)
{
    _type = Type::CAImage;
}

RenderTarget::~RenderTarget()
{
    CC_SAFE_RELEASE_NULL(_image);
}

RenderTargetRenderBuffer::RenderTargetRenderBuffer()
: _colorBuffer(0)
, _format(GL_RGBA4)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _reBuildRenderBufferListener(nullptr)
#endif
{
    _type = Type::RenderBuffer;
}

RenderTargetRenderBuffer::~RenderTargetRenderBuffer()
{
    if(glIsRenderbuffer(_colorBuffer))
    {
        glDeleteRenderbuffers(1, &_colorBuffer);
        _colorBuffer = 0;
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    CAApplication::getApplication()->getEventDispatcher()->removeEventListener(_reBuildRenderBufferListener);
#endif
}

bool RenderTargetRenderBuffer::init(unsigned int width, unsigned int height)
{
    if(!RenderTargetBase::init(width, height)) return false;
    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    //generate depthStencil
    glGenRenderbuffers(1, &_colorBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
    //todo: this could have a param
    glRenderbufferStorage(GL_RENDERBUFFER, _format, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _reBuildRenderBufferListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        /** listen the event that renderer was recreated on Android/WP8 */
        GLint oldRenderBuffer(0);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
        
        glGenRenderbuffers(1, &_colorBuffer);
        //generate depthStencil
        glBindRenderbuffer(GL_RENDERBUFFER, _colorBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, _format, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
        CCLOG("RenderTargetRenderBuffer recreated, _colorBuffer is %d", _colorBuffer);
    });
    
    CAApplication::getApplication()->getEventDispatcher()->addEventListenerWithFixedPriority(_reBuildRenderBufferListener, -1);
#endif
    
    return true;
}


RenderTargetRenderBuffer* RenderTargetRenderBuffer::create(unsigned int width, unsigned int height)
{
    auto result = new (std::nothrow) RenderTargetRenderBuffer();
    
    if(result && result->init(width, height))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

RenderTargetDepthStencil::RenderTargetDepthStencil()
: _depthStencilBuffer(0)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _reBuildDepthStencilListener(nullptr)
#endif
{
    _type = Type::RenderBuffer;
}

RenderTargetDepthStencil::~RenderTargetDepthStencil()
{
    if(glIsRenderbuffer(_depthStencilBuffer))
    {
        glDeleteRenderbuffers(1, &_depthStencilBuffer);
        _depthStencilBuffer = 0;
    }
#if CC_ENABLE_CACHE_TEXTURE_DATA
    CAApplication::getApplication()->getEventDispatcher()->removeEventListener(_reBuildDepthStencilListener);
#endif
}

bool RenderTargetDepthStencil::init(unsigned int width, unsigned int height)
{
    if(!RenderTargetBase::init(width, height)) return false;
    GLint oldRenderBuffer(0);
    glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
    
    //generate depthStencil
    glGenRenderbuffers(1, &_depthStencilBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _reBuildDepthStencilListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        /** listen the event that renderer was recreated on Android/WP8 */
        GLint oldRenderBuffer(0);
        glGetIntegerv(GL_RENDERBUFFER_BINDING, &oldRenderBuffer);
        
        glGenRenderbuffers(1, &_depthStencilBuffer);
        //generate depthStencil
        glBindRenderbuffer(GL_RENDERBUFFER, _depthStencilBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
        glBindRenderbuffer(GL_RENDERBUFFER, oldRenderBuffer);
        CCLOG("RenderTargetDepthStencil recreated, _depthStencilBuffer is %d", _depthStencilBuffer);
    });
    
    CAApplication::getApplication()->getEventDispatcher()->addEventListenerWithFixedPriority(_reBuildDepthStencilListener, -1);
#endif
    
    return true;
}


RenderTargetDepthStencil* RenderTargetDepthStencil::create(unsigned int width, unsigned int height)
{
    auto result = new (std::nothrow) RenderTargetDepthStencil();
    
    if(result && result->init(width, height))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool FrameBuffer::initWithGLView(CCEGLViewProtocol* view)
{
    if(view == nullptr)
    {
        return false;
    }
    GLint fbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &fbo);
    _fbo = fbo;
    return true;
}

FrameBuffer* FrameBuffer::getOrCreateDefaultFBO(CCEGLViewProtocol* view)
{
    if(nullptr == _defaultFBO)
    {
        auto result = new (std::nothrow) FrameBuffer();
        
        if(result && result->initWithGLView(view))
        {
            result->autorelease();
            result->_isDefault = true;
        }
        else
        {
            CC_SAFE_DELETE(result);
        }
        
        _defaultFBO = result;
    }
    
    return _defaultFBO;
}

    
void FrameBuffer::applyDefaultFBO()
{
    if(_defaultFBO)
    {
        _defaultFBO->applyFBO();
    }
}

void FrameBuffer::clearAllFBOs()
{
    for (auto fbo : _frameBuffers)
    {
        fbo->clearFBO();
    }
}

FrameBuffer* FrameBuffer::create(uint8_t fid, unsigned int width, unsigned int height)
{
    auto result = new (std::nothrow) FrameBuffer();
    if(result && result->init(fid, width, height))
    {
        result->autorelease();
        return result;
    }
    else
    {
        CC_SAFE_DELETE(result);
        return nullptr;
    }
}

bool FrameBuffer::init(uint8_t fid, unsigned int width, unsigned int height)
{
    _fid = fid;
    _width = width;
    _height = height;
    
    GLint oldfbo;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldfbo);

    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, oldfbo);
    
//    _rt = RenderTarget::create(width, height);
//    if(nullptr == _rt) return false;
    
#if CC_ENABLE_CACHE_TEXTURE_DATA
    _dirtyFBOListener = EventListenerCustom::create(EVENT_RENDERER_RECREATED, [this](EventCustom* event){
        if(isDefaultFBO()) return;
        GLint oldfbo;
        glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldfbo);

        glGenFramebuffers(1, &_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, oldfbo);
        CCLOG("Recreate FrameBufferObject _fbo is %d", _fbo);
        _fboBindingDirty = true;
    });
    
    CAApplication::getApplication()->getEventDispatcher()->addEventListenerWithFixedPriority(_dirtyFBOListener, -1);
#endif
    return true;
}

FrameBuffer::FrameBuffer()
: _clearColor(ccc4f(1, 1, 1, 1))
, _clearDepth(1.0)
, _clearStencil(0)
, _fbo(0)
, _previousFBO(0)
, _rt(nullptr)
, _rtDepthStencil(nullptr)
, _fboBindingDirty(true)
, _isDefault(false)
#if CC_ENABLE_CACHE_TEXTURE_DATA
, _dirtyFBOListener(nullptr)
#endif
{
    _frameBuffers.insert(this);
}

FrameBuffer::~FrameBuffer()
{
    {
        CC_SAFE_RELEASE_NULL(_rt);
        CC_SAFE_RELEASE_NULL(_rtDepthStencil);
        glDeleteFramebuffers(1, &_fbo);
        _fbo = 0;
        _frameBuffers.erase(this);
#if CC_ENABLE_CACHE_TEXTURE_DATA
        CAApplication::getApplication()->getEventDispatcher()->removeEventListener(_dirtyFBOListener);
#endif
        if (isDefaultFBO())
            _defaultFBO = nullptr;
    }
}

void FrameBuffer::clearFBO()
{
    applyFBO();
    glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    glClearDepth(_clearDepth);
    glClearStencil(_clearStencil);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    restoreFBO();
}

void FrameBuffer::attachRenderTarget(RenderTargetBase* rt)
{
    if(isDefaultFBO())
    {
        CCLOG("Can not apply render target to default FBO");
        return;
    }
    CC_ASSERT(rt);
    if(rt->getWidth() != _width || rt->getHeight() != _height)
    {
        CCLOG("Error, attach a render target with different size, Skip.");
        return;
    }
    CC_SAFE_RETAIN(rt);
    CC_SAFE_RELEASE(_rt);
    _rt = rt;
    _fboBindingDirty = true;
}

void FrameBuffer::applyFBO()
{
    CHECK_GL_ERROR_DEBUG();
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, (GLint*)&_previousFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
//    CCASSERT(_fbo==0 || _fbo != _previousFBO, "calling applyFBO without restoring the previous one");
    CHECK_GL_ERROR_DEBUG();
    if(_fboBindingDirty && !isDefaultFBO())
    {
        CHECK_GL_ERROR_DEBUG();
        if(RenderTargetBase::Type::CAImage == _rt->getType())
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _rt->getImage()->getName(), 0);
        else
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _rt->getBuffer());
        CHECK_GL_ERROR_DEBUG();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, nullptr == _rtDepthStencil ? 0 : _rtDepthStencil->getBuffer());
        CHECK_GL_ERROR_DEBUG();
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, nullptr == _rtDepthStencil ? 0 : _rtDepthStencil->getBuffer());
        CHECK_GL_ERROR_DEBUG();
        CCLOG("FBO is %d _fbo %d color, %d ds", _fbo, RenderTargetBase::Type::CAImage == _rt->getType() ? _rt->getImage()->getName() : _rt->getBuffer(), nullptr == _rtDepthStencil ? 0 : _rtDepthStencil->getBuffer());
        _fboBindingDirty = false;
    }
    if(GL_FRAMEBUFFER_COMPLETE != glCheckFramebufferStatus(GL_FRAMEBUFFER))
    {
        CCLOG("FrameBuffer Status Error %d", (int)glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    CHECK_GL_ERROR_DEBUG();
}

void FrameBuffer::restoreFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, _previousFBO);
}

void FrameBuffer::attachDepthStencilTarget(RenderTargetDepthStencil* rt)
{
    if(isDefaultFBO())
    {
        CCLOG("Can not apply depth stencil target to default FBO");
        return;
    }
    
    if(nullptr != rt && (rt->getWidth() != _width || rt->getHeight() != _height))
    {
        CCLOG("Error, attach a render target Depth stencil with different size, Skip.");
        return;
    }
    CC_SAFE_RETAIN(rt);
    CC_SAFE_RELEASE(_rtDepthStencil);
    _rtDepthStencil = rt;
    _fboBindingDirty = true;
}
} //end of namespace experimental
NS_CC_END
