#include "CAVideoPlayerRender.h"

NS_CC_EXT_BEGIN

#pragma mark - shaders
static GLuint compileShader(GLenum type, const char* sources)
{
    GLint status;
    
    GLuint shader = glCreateShader(type);
    if (shader == 0 || shader == GL_INVALID_ENUM) {
        CCLog("Failed to create shader %d", type);
        return 0;
    }
    
    glShaderSource(shader, 1, &sources, NULL);
    glCompileShader(shader);
    
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        glDeleteShader(shader);
        CCLog("Failed to compile shader:\n");
        return 0;
    }
    
    return shader;
}

#pragma mark - Frame Render


VPFrameRenderRGB::VPFrameRenderRGB()
{
    _texture = 0;
    _uniformSampler = 0;
    _key = "CAVideoPlayerRenderRGB";
}

VPFrameRenderRGB::~VPFrameRenderRGB()
{
    if (_texture) {
        glDeleteTextures(1, &_texture);
        _texture = 0;
    }
}

bool VPFrameRenderRGB::isValid()
{
    return (_texture != 0);
}

const char* VPFrameRenderRGB::fragmentShader()
{
    return "";
}

void VPFrameRenderRGB::resolveUniforms(GLuint program)
{
    _uniformSampler = glGetUniformLocation(program, "s_texture");
}

void VPFrameRenderRGB::setFrame(VPVideoFrame* frame)
{
    VPVideoFrameRGB *rgbFrame = (VPVideoFrameRGB *)frame;
    
    CCAssert((rgbFrame->getDataLength() == rgbFrame->getWidth() * rgbFrame->getHeight() * 3), "");
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if (0 == _texture)
        glGenTextures(1, &_texture);
    
    glBindTexture(GL_TEXTURE_2D, _texture);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 frame->getWidth(),
                 frame->getHeight(),
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 rgbFrame->getData());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

bool VPFrameRenderRGB::prepareRender()
{
    if (_texture == 0) {
        return false;
    }
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texture);
    glUniform1i(_uniformSampler, 0);
    
    return true;
}



VPFrameRenderYUV::VPFrameRenderYUV()
{
    for (int i=0; i<3; i++) {
        _textures[i] = 0;
        _uniformSamplers[i] = 0;
    }
    
    _key = "CAVideoPlayerRenderYUV";
}

VPFrameRenderYUV::~VPFrameRenderYUV()
{
    if (_textures[0])
        glDeleteTextures(3, _textures);
}

bool VPFrameRenderYUV::isValid()
{
    return (_textures[0] != 0);
}

const char* VPFrameRenderYUV::fragmentShader()
{
    return "";
}

void VPFrameRenderYUV::resolveUniforms(GLuint program)
{
    _uniformSamplers[0] = glGetUniformLocation(program, "s_texture_y");
    _uniformSamplers[1] = glGetUniformLocation(program, "s_texture_u");
    _uniformSamplers[2] = glGetUniformLocation(program, "s_texture_v");
}

void VPFrameRenderYUV::setFrame(VPVideoFrame* frame)
{
    VPVideoFrameYUV *yuvFrame = (VPVideoFrameYUV *)frame;
    
    CCAssert((yuvFrame->getLumaLength() == yuvFrame->getWidth() * yuvFrame->getHeight()), "");
    CCAssert((yuvFrame->getChromaBLength() == (yuvFrame->getWidth() * yuvFrame->getHeight())/4), "");
    CCAssert((yuvFrame->getChromaRLength() == (yuvFrame->getWidth() * yuvFrame->getHeight())/4), "");
    
    const unsigned int frameWidth = frame->getWidth();
    const unsigned int frameHeight = frame->getHeight();
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    if (0 == _textures[0])
        glGenTextures(3, _textures);
    
    const char *pixels[3] = { yuvFrame->getLuma(), yuvFrame->getChromaB(), yuvFrame->getChromaR() };
    const unsigned int widths[3]  = { frameWidth, frameWidth / 2, frameWidth / 2 };
    const unsigned int heights[3] = { frameHeight, frameHeight / 2, frameHeight / 2 };
    
    for (int i = 0; i < 3; ++i) {
        
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     GL_LUMINANCE,
                     widths[i],
                     heights[i],
                     0,
                     GL_LUMINANCE,
                     GL_UNSIGNED_BYTE,
                     pixels[i]);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}

bool VPFrameRenderYUV::prepareRender()
{
    if (_textures[0] == 0)
        return false;
    
    for (int i = 0; i < 3; ++i) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glUniform1i(_uniformSamplers[i], i);
    }
    
    return true;
}

VPFrameRender::VPFrameRender()
{
    _vertices[0] = -1.0f;  // x0
    _vertices[1] = -1.0f;  // y0
    _vertices[2] =  1.0f;  // ..
    _vertices[3] = -1.0f;
    _vertices[4] = -1.0f;
    _vertices[5] =  1.0f;
    _vertices[6] =  1.0f;  // x3
    _vertices[7] =  1.0f;  // y3
}

VPFrameRender::~VPFrameRender()
{
}

bool VPFrameRender::loadShaders()
{

    return true;
}

const char* VPFrameRender::key()
{
	return _key.c_str();
}

void VPFrameRender::draw(VPVideoFrame *frame, long offset)
{

}

DRect VPFrameRender::updateVertices(float width, float height, float screen_w, float screen_h)
{
    const bool fit      = true;
    const float dH      = (float)screen_h / height;
    const float dW      = (float)screen_w / width;
    const float dd      = fit ? MIN(dH, dW) : MAX(dH, dW);
    const float h       = (height * dd / (float)screen_h);
    float w       = (width  * dd / (float)screen_w );

    _vertices[0] = - w;
    _vertices[1] = - h;
    _vertices[2] =   w;
    _vertices[3] = - h;
    _vertices[4] = - w;
    _vertices[5] =   h;
    _vertices[6] =   w;
    _vertices[7] =   h;
    
    return DRect((screen_w - w * screen_w)/2, (screen_h - screen_h * h)/2, w * screen_w, screen_h * h);
}

NS_CC_EXT_END
