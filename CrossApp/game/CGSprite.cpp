//
//  CGSprite.cpp
//  CrossApp
//
//  Created by Li Yuanfeng on 16-7-19.
//  Copyright (c) 2014Âπ?http://9miao.com All rights reserved.
//

#include "CGSpriteBatchNode.h"
#include "game/actions/CGAnimation.h"
#include "game/actions/CGAnimationCache.h"
#include "ccConfig.h"
#include "CGSprite.h"
#include "CGSpriteFrame.h"
#include "CGSpriteFrameCache.h"
#include "images/CAImageCache.h"
#include "view/CADrawingPrimitives.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "support/CAPointExtension.h"
#include "math/CAAffineTransform.h"
#include "math/TransformUtils.h"
#include "math/CAAffineTransform.h"
#include "support/CAProfiling.h"
#include "ccMacros.h"
#include <string.h>
#include "view/CAView.h"
NS_CC_BEGIN

static int spriteCount = 0;

CGSprite::CGSprite(void)
: m_bShouldBeHidden(false)
, m_pobImage(NULL)
{
    // clean the Quad
    memset(&m_sQuad, 0, sizeof(m_sQuad));
    
    // Atlas: Color
    CAColor4B tmpColor = CAColor_white;
    m_sQuad.bl.colors = tmpColor;
    m_sQuad.br.colors = tmpColor;
    m_sQuad.tl.colors = tmpColor;
    m_sQuad.tr.colors = tmpColor;
    
    m_pobBatchNode = NULL;
    
    m_bRecursiveDirty = false;
    setDirty(false);
    
    m_bOpacityModifyRGB = true;
    
    m_sBlendFunc.src = CC_BLEND_SRC;
    m_sBlendFunc.dst = CC_BLEND_DST;
    
    m_bFlipX = m_bFlipY = false;
    
    // default transform anchor: center
    setAnchorPoint(DPoint(0.5f, 0.5f));
    
    // zwoptex default values
    m_obOffsetPosition = DPointZero;
    
    m_bHasChildren = false;
    
    
    //CCLog("CGSprite = %d\n", ++spriteCount);
}

CGSprite::~CGSprite(void)
{
    CC_SAFE_RELEASE(m_pobImage);
    //CCLog("~CGSprite = %d\n", --spriteCount);
}

CGSprite* CGSprite::createWithImage(CAImage *image)
{
    CGSprite *pobSprite = new CGSprite();
    if (pobSprite && pobSprite->initWithImage(image))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CGSprite* CGSprite::createWithImage(CAImage *image, const DRect& rect)
{
    CGSprite *pobSprite = new CGSprite();
    if (pobSprite && pobSprite->initWithImage(image, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CGSprite* CGSprite::create(const std::string& pszFileName)
{
    CGSprite *pobSprite = new CGSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CGSprite* CGSprite::create(const std::string& pszFileName, const DRect& rect)
{
    CGSprite *pobSprite = new CGSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CGSprite* CGSprite::createWithSpriteFrame(CGSpriteFrame *pSpriteFrame)
{
    CGSprite *pobSprite = new CGSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

CGSprite* CGSprite::createWithSpriteFrameName(const std::string& pszSpriteFrameName)
{
    CGSpriteFrame *pFrame = CGSpriteFrameCache::getInstance()->getSpriteFrameByName(pszSpriteFrameName);
    
#if CROSSAPP_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName.c_str());
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

CGSprite* CGSprite::create()
{
    CGSprite *pSprite = new CGSprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

bool CGSprite::init(void)
{
    return initWithImage(NULL, DRectZero);
}

// designated initializer
bool CGSprite::initWithImage(CAImage *image, const DRect& rect, bool rotated)
{
    if (CGNode::init())
    {
        this->setImage(image);
        this->setImageRect(rect, rotated, rect.size);
        this->setBatchNode(NULL);
        
        return true;
    }
    else
    {
        return false;
    }
}

bool CGSprite::initWithImage(CAImage *image, const DRect& rect)
{
    return initWithImage(image, rect, false);
}

bool CGSprite::initWithImage(CAImage *image)
{
    CCAssert(image != NULL, "Invalid texture for sprite");
    
    DRect rect = DRectZero;
    rect.size = image->getContentSize();
    
    return initWithImage(image, rect);
}

bool CGSprite::initWithFile(const std::string& pszFilename)
{
    CAImage *image = CAImage::create(pszFilename);
    if (image)
    {
        DRect rect = DRectZero;
        rect.size = image->getContentSize();
        return initWithImage(image, rect);
    }

    return false;
}

bool CGSprite::initWithFile(const std::string& pszFilename, const DRect& rect)
{
    CAImage *image = CAImage::create(pszFilename);
    if (image)
    {
        return initWithImage(image, rect);
    }

    return false;
}

bool CGSprite::initWithSpriteFrame(CGSpriteFrame *pSpriteFrame)
{
    CCAssert(pSpriteFrame != NULL, "");
    
    bool bRet = this->initWithImage(pSpriteFrame->getImage(), pSpriteFrame->getRect());
    this->setSpriteFrame(pSpriteFrame);
    
    return bRet;
}

bool CGSprite::initWithSpriteFrameName(const std::string& pszSpriteFrameName)
{

    CGSpriteFrame *pFrame = CGSpriteFrameCache::getInstance()->getSpriteFrameByName(pszSpriteFrameName);
    return initWithSpriteFrame(pFrame);
}

void CGSprite::setImageRect(const DRect& rect)
{
    this->setImageRect(rect, false, rect.size);
}


void CGSprite::setImageRect(const DRect& rect, bool rotated, const DSize& untrimmedSize)
{
    m_bRectRotated = rotated;
    
    this->setContentSize(untrimmedSize);
    this->setVertexRect(rect);
    this->setImageCoords(rect);
    
    DPoint relativeOffset = m_obUnflippedOffsetPositionFromCenter;
    
    // issue #732
    if (m_bFlipX)
    {
        relativeOffset.x = -relativeOffset.x;
    }
    if (m_bFlipY)
    {
        relativeOffset.y = -relativeOffset.y;
    }
    
    m_obOffsetPosition.x = relativeOffset.x + (m_obContentSize.width - m_obRect.size.width) / 2;
    m_obOffsetPosition.y = relativeOffset.y + (m_obContentSize.height - m_obRect.size.height) / 2;
    
    // rendering using batch node
    if (m_pobBatchNode)
    {
        setDirty(true);
    }
    else
    {
        float x1 = 0 + m_obOffsetPosition.x;
        float y1 = 0 + m_obOffsetPosition.y;
        float x2 = x1 + m_obRect.size.width;
        float y2 = y1 + m_obRect.size.height;
        
        // Don't update Z.
        m_sQuad.bl.vertices = DPoint3D(x1, y1, 0);
        m_sQuad.br.vertices = DPoint3D(x2, y1, 0);
        m_sQuad.tl.vertices = DPoint3D(x1, y2, 0);
        m_sQuad.tr.vertices = DPoint3D(x2, y2, 0);
    }
    
    this->updateDraw();
}

void CGSprite::setVertexRect(const DRect& rect)
{
    m_obRect = rect;
}

void CGSprite::setImageCoords(const DRect& _rect)
{
    DRect rect = _rect;
    
    CAImage *tex = m_pobBatchNode ? m_pobImageAtlas->getImage() : m_pobImage;
    if (! tex)
    {
        return;
    }
    
    float atlasWidth = (float)tex->getPixelsWide();
    float atlasHeight = (float)tex->getPixelsHigh();
    
    float left, right, top, bottom;
    
    if (m_bRectRotated)
    {
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        left    = (2*rect.origin.x+1)/(2*atlasWidth);
        right    = left+(rect.size.height*2-2)/(2*atlasWidth);
        top        = (2*rect.origin.y+1)/(2*atlasHeight);
        bottom    = top+(rect.size.width*2-2)/(2*atlasHeight);
#else
        left    = rect.origin.x/atlasWidth;
        right    = (rect.origin.x+rect.size.height) / atlasWidth;
        top        = rect.origin.y/atlasHeight;
        bottom    = (rect.origin.y+rect.size.width) / atlasHeight;
#endif // CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        
        if (m_bFlipX)
        {
            CC_SWAP(top, bottom, float);
        }
        
        if (m_bFlipY)
        {
            CC_SWAP(left, right, float);
        }
        
        m_sQuad.bl.texCoords.u = left;
        m_sQuad.bl.texCoords.v = top;
        m_sQuad.br.texCoords.u = left;
        m_sQuad.br.texCoords.v = bottom;
        m_sQuad.tl.texCoords.u = right;
        m_sQuad.tl.texCoords.v = top;
        m_sQuad.tr.texCoords.u = right;
        m_sQuad.tr.texCoords.v = bottom;
    }
    else
    {
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        left    = (2*rect.origin.x+1)/(2*atlasWidth);
        right    = left + (rect.size.width*2-2)/(2*atlasWidth);
        top        = (2*rect.origin.y+1)/(2*atlasHeight);
        bottom    = top + (rect.size.height*2-2)/(2*atlasHeight);
#else
        left    = rect.origin.x/atlasWidth;
        right    = (rect.origin.x + rect.size.width) / atlasWidth;
        top        = rect.origin.y/atlasHeight;
        bottom    = (rect.origin.y + rect.size.height) / atlasHeight;
#endif // ! CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        
        if(m_bFlipX)
        {
            CC_SWAP(left,right,float);
        }
        
        if(m_bFlipY)
        {
            CC_SWAP(top,bottom,float);
        }
        
        m_sQuad.bl.texCoords.u = left;
        m_sQuad.bl.texCoords.v = bottom;
        m_sQuad.br.texCoords.u = right;
        m_sQuad.br.texCoords.v = bottom;
        m_sQuad.tl.texCoords.u = left;
        m_sQuad.tl.texCoords.v = top;
        m_sQuad.tr.texCoords.u = right;
        m_sQuad.tr.texCoords.v = top;
    }
}

void CGSprite::updateTransform(void)
{
    if(isDirty())
    {
        if(!m_bVisible || (m_pParent && m_pParent != m_pobBatchNode && ((CGSprite*)m_pParent)->m_bShouldBeHidden))
        {
            m_sQuad.br.vertices = m_sQuad.tl.vertices = m_sQuad.tr.vertices = m_sQuad.bl.vertices = DPoint3D(0,0,0);
            m_bShouldBeHidden = true;
        }
        else
        {
            m_bShouldBeHidden = false;
            
            if( !m_pParent || m_pParent == m_pobBatchNode)
            {
                m_tTransformToBatch = getNodeToParentTransform();
            }
            else
            {
                const Mat4 &nodeToParent = getNodeToParentTransform();
                Mat4 &parentTransform = static_cast<CGSprite*>(m_pParent)->m_tTransformToBatch;
                m_tTransformToBatch = parentTransform * nodeToParent;
            }
            
            DSize size = m_obRect.size;

            float x1 = m_obOffsetPosition.x;
            float y1 = m_obOffsetPosition.y;
            
            float x2 = x1 + size.width;
            float y2 = y1 + size.height;
            
            float x = m_tTransformToBatch.m[12];
            float y = m_tTransformToBatch.m[13];
            
            float cr = m_tTransformToBatch.m[0];
            float sr = m_tTransformToBatch.m[1];
            float cr2 = m_tTransformToBatch.m[5];
            float sr2 = -m_tTransformToBatch.m[4];
            float ax = x1 * cr - y1 * sr2 + x;
            float ay = x1 * sr + y1 * cr2 + y;
            
            float bx = x2 * cr - y1 * sr2 + x;
            float by = x2 * sr + y1 * cr2 + y;
            
            float cx = x2 * cr - y2 * sr2 + x;
            float cy = x2 * sr + y2 * cr2 + y;
            
            float dx = x1 * cr - y2 * sr2 + x;
            float dy = x1 * sr + y2 * cr2 + y;
            
            m_sQuad.bl.vertices = DPoint3D(RENDER_IN_SUBPIXEL(ax), RENDER_IN_SUBPIXEL(ay), m_fPositionZ);
            m_sQuad.br.vertices = DPoint3D(RENDER_IN_SUBPIXEL(bx), RENDER_IN_SUBPIXEL(by), m_fPositionZ);
            m_sQuad.tl.vertices = DPoint3D(RENDER_IN_SUBPIXEL(dx), RENDER_IN_SUBPIXEL(dy), m_fPositionZ);
            m_sQuad.tr.vertices = DPoint3D(RENDER_IN_SUBPIXEL(cx), RENDER_IN_SUBPIXEL(cy), m_fPositionZ);
            this->setImageCoords(m_obRect);
        }
        
        if (m_pobImageAtlas)
        {
            m_pobImageAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
        }
        
        m_bRecursiveDirty = false;
        setDirty(false);
    }
    CGNode::updateTransform();
}


void CGSprite::insertChild(CGNode *pChild, int zOrder)
{
    
    if (m_pobBatchNode)
    {
        CGSprite* pChildSprite = dynamic_cast<CGSprite*>(pChild);
        m_pobBatchNode->appendChild(pChildSprite);
        if (!m_bReorderChildDirty)
        {
            setReorderChildDirtyRecursively();
        }
    }
    
    CGNode::insertChild(pChild, zOrder);
    m_bHasChildren = true;
}

void CGSprite::reorderChild(CGNode *pChild, int zOrder)
{
    if (zOrder != pChild->getZOrder())
    {
        if( m_pobBatchNode && ! m_bReorderChildDirty)
        {
            setReorderChildDirtyRecursively();
            m_pobBatchNode->reorderBatch(true);
        }
        
        CGNode::reorderChild(pChild, zOrder);
    }
}

void CGSprite::removeChild(CGNode *pChild)
{
    if (m_pobBatchNode)
    {
        m_pobBatchNode->removeSpriteFromAtlas((CGSprite*)(pChild));
    }
    
    CGNode::removeChild(pChild);
    
}

void CGSprite::sortAllChildren()
{
    if (m_bReorderChildDirty && !m_obChildren.empty())
    {
        std::sort(m_obChildren.begin(), m_obChildren.end(), compareChildrenZOrder);
        
        if (m_pobBatchNode)
        {
            for (auto& var : m_obChildren)
            {
                if(m_bRunning)
                {
                    var->sortAllChildren();
                }
            }
        }
        m_bReorderChildDirty = false;
    }
}

//
// CGNode property overloads
// used only when parent is CGSpriteBatchNode
//

void CGSprite::setReorderChildDirtyRecursively(void)
{
    //only set parents flag the first time
    if ( ! m_bReorderChildDirty )
    {
        m_bReorderChildDirty = true;
        CGNode* pNode = (CGNode*)m_pParent;
        while (pNode && pNode != m_pobBatchNode)
        {
            ((CGSprite*)pNode)->setReorderChildDirtyRecursively();
            pNode=pNode->getParent();
        }
    }
}


void CGSprite::setDirtyRecursively(bool bValue)
{
    m_bRecursiveDirty = bValue;
    setDirty(bValue);
    // recursively set dirty
    if (m_bHasChildren)
    {
        if (!m_obChildren.empty())
        {
            for (auto& var : m_obChildren)
            {
                CGSprite* pChild = (CGSprite*)var;
                pChild->setDirtyRecursively(bValue);
            }
            
        }
    }
}

void CGSprite::setFlipX(bool bFlipX)
{
    if (m_bFlipX != bFlipX)
    {
        m_bFlipX = bFlipX;
        setImageRect(m_obRect, m_bRectRotated, m_obContentSize);
    }
}

bool CGSprite::isFlipX(void)
{
    return m_bFlipX;
}

void CGSprite::setFlipY(bool bFlipY)
{
    if (m_bFlipY != bFlipY)
    {
        m_bFlipY = bFlipY;
        setImageRect(m_obRect, m_bRectRotated, m_obContentSize);
    }
}

bool CGSprite::isFlipY(void)
{
    return m_bFlipY;
}

//
// RGBA protocol
//

void CGSprite::updateColor(void)
{
    CAColor4B color4 = _displayedColor;
    color4.a = color4.a * _displayedAlpha;
    
    if (m_bOpacityModifyRGB)
    {
        color4.r = color4.r * color4.a / 255.0f;
        color4.g = color4.g * color4.a / 255.0f;
        color4.b = color4.b * color4.a / 255.0f;
    }
    
    m_sQuad.bl.colors = color4;
    m_sQuad.br.colors = color4;
    m_sQuad.tl.colors = color4;
    m_sQuad.tr.colors = color4;
    
    if (m_pobBatchNode && m_pobImage)
    {
        if (m_uAtlasIndex != UINT_NONE)
        {
            m_pobImageAtlas->updateQuad(&m_sQuad, m_uAtlasIndex);
        }
        else
        {
            setDirty(true);
        }
    }
    
    this->updateDraw();
}

void CGSprite::setOpacityModifyRGB(bool modify)
{
    if (m_bOpacityModifyRGB != modify)
    {
        m_bOpacityModifyRGB = modify;
        updateColor();
    }
}

bool CGSprite::isOpacityModifyRGB(void)
{
    return m_bOpacityModifyRGB;
}

void CGSprite::updateDraw()
{
    CGNode::updateDraw();
    SET_DIRTY_RECURSIVELY(m_pobBatchNode);
}

void CGSprite::setSpriteFrame(CGSpriteFrame *pNewFrame)
{
    m_obUnflippedOffsetPositionFromCenter = pNewFrame->getOffset();
    
    m_bRectRotated = pNewFrame->isRotated();
    
    this->setImage(pNewFrame->getImage());
    
    this->setImageRect(pNewFrame->getRect(), m_bRectRotated, pNewFrame->getOriginalSize());
}

void CGSprite::setDisplayFrameWithAnimationName(const std::string& animationName, int frameIndex)
{
    CCAssert(!animationName.empty(), "CGSprite#setDisplayFrameWithAnimationName. animationName must not be NULL");
    
    Animation *a = AnimationCache::getInstance()->getAnimation(animationName);
    
    CCAssert(a, "CGSprite#setDisplayFrameWithAnimationName: Frame not found");
    
    AnimationFrame* frame = a->getFrames().at(frameIndex);
    
    CCAssert(frame, "CGSprite#setDisplayFrame. Invalid frame");
    
    this->setSpriteFrame(frame->getSpriteFrame());
}

bool CGSprite::isFrameDisplayed(CGSpriteFrame *pFrame)
{
    DRect r = pFrame->getRect();
    
    return (r.equals(m_obRect) &&
            pFrame->getImage()->getName() == m_pobImage->getName() &&
            pFrame->getOffset().equals(m_obUnflippedOffsetPositionFromCenter));
}

CGSpriteFrame* CGSprite::getSpriteFrame(void)
{
    return CGSpriteFrame::createWithImage(m_pobImage,
                                            m_obRect,
                                            m_bRectRotated,
                                            m_obUnflippedOffsetPositionFromCenter,
                                            m_obContentSize);
}

CGSpriteBatchNode* CGSprite::getBatchNode(void)
{
    return m_pobBatchNode;
}

void CGSprite::setBatchNode(CGSpriteBatchNode *pobSpriteBatchNode)
{
    m_pobBatchNode = pobSpriteBatchNode; // weak reference
    
    if( ! m_pobBatchNode )
    {
        m_uAtlasIndex = UINT_NONE;
        setImageAtlas(NULL);
        m_bRecursiveDirty = false;
        setDirty(false);
        
        float x1 = m_obOffsetPosition.x;
        float y1 = m_obOffsetPosition.y;
        float x2 = x1 + m_obRect.size.width;
        float y2 = y1 + m_obRect.size.height;
        m_sQuad.bl.vertices = DPoint3D( x1, y1, 0 );
        m_sQuad.br.vertices = DPoint3D( x2, y1, 0 );
        m_sQuad.tl.vertices = DPoint3D( x1, y2, 0 );
        m_sQuad.tr.vertices = DPoint3D( x2, y2, 0 );
        
    }
    else
    {
        m_tTransformToBatch = Mat4::IDENTITY;
        setImageAtlas(m_pobBatchNode->getImageAtlas()); // weak ref
    }
}

// Texture protocol

void CGSprite::updateBlendFunc(void)
{
    CCAssert (! m_pobBatchNode, "CGSprite: updateBlendFunc doesn't work when the sprite is rendered using a CGSpriteBatchNode");
    
    if (!m_pobImage || !m_pobImage->hasPremultipliedAlpha())
    {
        m_sBlendFunc.src = GL_SRC_ALPHA;
        m_sBlendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
        setOpacityModifyRGB(false);
    }
    else
    {
        m_sBlendFunc.src = CC_BLEND_SRC;
        m_sBlendFunc.dst = CC_BLEND_DST;
        setOpacityModifyRGB(true);
    }
}

void CGSprite::setImage(CAImage *image)
{
    if (!m_pobBatchNode && image != m_pobImage)
    {
        CC_SAFE_RETAIN(image);
        CC_SAFE_RELEASE(m_pobImage);
        m_pobImage = image;
        DRect rect = DRectZero;
        if (image)
        {
            rect.size = image->getContentSize();
        }
        this->setImageRect(rect);
        this->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
        this->updateBlendFunc();
        this->updateDraw();
    }
}

CAImage* CGSprite::getImage()
{
    return m_pobImage;
}

void CGSprite::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    CC_RETURN_IF(!m_pobImage);
    

    {
//        m_obTrianglesCommand.init(m_nZOrder,
//                               m_pobImage->getName(),
//                               getGLProgramState(),
//                               m_sBlendFunc,
//                               _polyInfo.triangles,
//                               transform,
//                               flags);
        
        renderer->addCommand(&m_obTrianglesCommand);
        
#if CC_SPRITE_DEBUG_DRAW
        _debugDrawNode->clear();
        auto count = _polyInfo.triangles.indexCount/3;
        auto indices = _polyInfo.triangles.indices;
        auto verts = _polyInfo.triangles.verts;
        for(ssize_t i = 0; i < count; i++)
        {
            //draw 3 lines
            Vec3 from =verts[indices[i*3]].vertices;
            Vec3 to = verts[indices[i*3+1]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::WHITE);
            
            from =verts[indices[i*3+1]].vertices;
            to = verts[indices[i*3+2]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::WHITE);
            
            from =verts[indices[i*3+2]].vertices;
            to = verts[indices[i*3]].vertices;
            _debugDrawNode->drawLine(Vec2(from.x, from.y), Vec2(to.x,to.y), Color4F::WHITE);
        }
#endif //CC_SPRITE_DEBUG_DRAW
    }
}


NS_CC_END
