//
//  CGNode.cpp
//  CrossApp
//
//  Created by Li Yuanfeng on 16-7-12.
//  Copyright (c) 2014Âπ?http://9miao.com All rights reserved.
//

#include "CGNode.h"
#include "basics/CAPointExtension.h"
#include "basics/CACamera.h"
#include "basics/CAApplication.h"
#include "basics/CAScheduler.h"
#include "dispatcher/CATouch.h"
#include "CCEGLView.h"
#include "platform/CADensityDpi.h"
#include "game/actions/CGActionManager.h"
#include "renderer/CCGLProgram.h"
#include "renderer/CCGLProgramState.h"
#include "renderer/CCMaterial.h"
#include "math/TransformUtils.h"
#include "ccMacros.h"
#include <stdarg.h>

NS_CC_BEGIN;

static int s_globalOrderOfArrival = 1;

static std::map<int, CGNode*> s_pMap;

std::map<int, CGNode*>& CGNode::getInstanceMap()
{
    return s_pMap;
}

CGNode::CGNode(void)
: m_fRotationX(0.0f)
, m_fRotationY(0.0f)
, m_fRotationZ_X(0.0f)
, m_fRotationZ_Y(0.0f)
, m_fScaleX(1.0f)
, m_fScaleY(1.0f)
, m_fScaleZ(1.0f)
, m_fSkewX(0.0f)
, m_fSkewY(0.0f)
, m_obAnchorPointInPoints(DPointZero)
, m_obAnchorPoint(DPointZero)
, m_obPosition(DPointZero)
, m_obNormalizedPosition(DPointZero)
, m_fPositionZ(0.0f)
, m_bUsingNormalizedPosition(false)
, m_bNormalizedPositionDirty(false)
, m_obContentSize(DSizeZero)
, m_bContentSizeDirty(true)
, m_bTransformDirty(true)
, m_bInverseDirty(true)
, m_pAdditionalTransform(nullptr)
, m_bAdditionalTransformDirty(false)
, m_bTransformUpdated(true)
, m_nZOrder(0)
, m_pParent(nullptr)
, m_uOrderOfArrival(0)
, m_pGlProgramState(nullptr)
, m_bRunning(false)
, m_bVisible(true)
, m_bReorderChildDirty(false)
, _displayedAlpha(1.0f)
, _realAlpha(1.0f)
, _displayedColor(CAColor4B::WHITE)
, _realColor(CAColor4B::WHITE)
, m_bDisplayRange(true)
, m_pSuperviewCAView(nullptr)
, m_pCAView(nullptr)
, m_iCameraMask(1)
, m_pApplication(CAApplication::getApplication())
, m_obOnEnterCallback(nullptr)
, m_obOnEnterTransitionDidFinishCallback(nullptr)
, m_obOnExitCallback(nullptr)
, m_obOnExitTransitionDidStartCallback(nullptr)
{
    memset((void*)&m_sQuad, 0, sizeof(m_sQuad));
    
    m_tTransform = m_tInverse = Mat4::IDENTITY;
    
    this->updateRotationQuat();
    
    s_pMap[m_u__ID] = this;
//    CCLog("CGNode = %ld\n", s_pMap.size());
}

CGNode::~CGNode(void)
{
    CC_SAFE_RELEASE_NULL(m_pGlProgramState);
    
    CAApplication::getApplication()->getActionManager()->removeAllActionsFromTarget(this);
    
    if(!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
        {
            var->setParent(nullptr);
        }
        m_obChildren.clear();
    }
    
    if (m_pAdditionalTransform)
    {
        delete [] m_pAdditionalTransform;
    }
    
    if (m_pCAView)
    {
        m_pCAView->m_pParentCGNode = NULL;
        m_pCAView->release();
    }
    
    s_pMap.erase(m_u__ID);
//    CCLog("~CGNode = %ld\n", s_pMap.size());
}

CGNode * CGNode::create(void)
{
    CGNode * pRet = new CGNode();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CGNode::init()
{
    return true;
}

float CGNode::getSkewX()
{
    return m_fSkewX;
}

void CGNode::setSkewX(float newSkewX)
{
    if (m_fSkewX != newSkewX)
    {
        m_fSkewX = newSkewX;
        this->updateDraw();
    }
}

float CGNode::getSkewY()
{
    return m_fSkewY;
}

void CGNode::setSkewY(float newSkewY)
{
    if (m_fSkewY != newSkewY)
    {
        m_fSkewY = newSkewY;
        this->updateDraw();
    }
}

int CGNode::getZOrder()
{
    return m_nZOrder;
}

void CGNode::_setZOrder(int z)
{
    m_nZOrder = z;
}

void CGNode::setZOrder(int z)
{
    if (m_pParent)
    {
        m_pParent->reorderChild(this, z);
    }
    else
    {
        this->_setZOrder(z);
    }
}

float CGNode::getRotationZ()
{
    CCAssert(m_fRotationZ_X == m_fRotationZ_Y, "CGNode#rotation. m_fRotationZ_X != m_fRotationZ_Y. Don't know which one to return");
    return m_fRotationZ_X;
}

void CGNode::setRotationZ(float newRotation)
{
    if (m_fRotationZ_X != newRotation || m_fRotationZ_Y != newRotation)
    {
        m_fRotationZ_X = m_fRotationZ_Y = newRotation;
        this->updateRotationQuat();
        this->updateDraw();
    }
}

float CGNode::getRotationX()
{
    return m_fRotationX;
}

void CGNode::setRotationX(float fRotationX)
{
    if (m_fRotationX != fRotationX)
    {
        m_fRotationX = fRotationX;
        this->updateRotationQuat();
        this->updateDraw();
    }
}

float CGNode::getRotationY()
{
    return m_fRotationY;
}

void CGNode::setRotationY(float fRotationY)
{
    if (m_fRotationY != fRotationY)
    {
        m_fRotationY = fRotationY;
        this->updateRotationQuat();
        this->updateDraw();
    }
}

DPoint3D CGNode::getRotation3D() const
{
    CCAssert(m_fRotationZ_X == m_fRotationZ_Y, "CGNode#rotation. m_fRotationZ_X != m_fRotationZ_Y. Don't know which one to return");
    return DPoint3D(m_fRotationX, m_fRotationY, m_fRotationZ_X);
}

void CGNode::setRotation3D(const DPoint3D& rotation)
{
    if (rotation.x != m_fRotationX || rotation.y != m_fRotationY || rotation.z != m_fRotationZ_X)
    {
        m_fRotationX = rotation.x;
        m_fRotationY = rotation.y;
        m_fRotationZ_Y = m_fRotationZ_X = rotation.z;
        this->updateRotationQuat();
        this->updateDraw();
    }
}

void CGNode::setRotationQuat(const Quaternion& quat)
{
    m_obRotationQuat = quat;
    updateRotation3D();
    this->updateDraw();
}

Quaternion CGNode::getRotationQuat() const
{
    return m_obRotationQuat;
}

void CGNode::updateRotationQuat()
{
    float halfRadx = CC_DEGREES_TO_RADIANS(m_fRotationX / 2.f);
    float halfRady = CC_DEGREES_TO_RADIANS(m_fRotationY / 2.f);
    float halfRadz = m_fRotationZ_X == m_fRotationZ_Y ? -CC_DEGREES_TO_RADIANS(m_fRotationZ_X / 2.f) : 0;
    
    float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);
    
    m_obRotationQuat.x = sinhalfRadx * coshalfRady * coshalfRadz - coshalfRadx * sinhalfRady * sinhalfRadz;
    m_obRotationQuat.y = coshalfRadx * sinhalfRady * coshalfRadz + sinhalfRadx * coshalfRady * sinhalfRadz;
    m_obRotationQuat.z = coshalfRadx * coshalfRady * sinhalfRadz - sinhalfRadx * sinhalfRady * coshalfRadz;
    m_obRotationQuat.w = coshalfRadx * coshalfRady * coshalfRadz + sinhalfRadx * sinhalfRady * sinhalfRadz;
}

void CGNode::updateRotation3D()
{
    //convert quaternion to Euler angle
    float x = m_obRotationQuat.x, y = m_obRotationQuat.y, z = m_obRotationQuat.z, w = m_obRotationQuat.w;
    m_fRotationX = atan2f(2.f * (w * x + y * z), 1.f - 2.f * (x * x + y * y));
    float sy = 2.f * (w * y - z * x);
    sy = clampf(sy, -1, 1);
    m_fRotationY = asinf(sy);
    m_fRotationZ_X = atan2f(2.f * (w * z + x * y), 1.f - 2.f * (y * y + z * z));
    
    m_fRotationX = CC_RADIANS_TO_DEGREES(m_fRotationX);
    m_fRotationY = CC_RADIANS_TO_DEGREES(m_fRotationY);
    m_fRotationZ_X = m_fRotationZ_Y = -CC_RADIANS_TO_DEGREES(m_fRotationZ_X);
}

float CGNode::getScale(void)
{
    CCAssert( m_fScaleX == m_fScaleY, "CGNode#scale. ScaleX != ScaleY. Don't know which one to return");
    return m_fScaleX;
}

void CGNode::setScale(float scale)
{
    this->setScale(scale, scale, scale);
}

void CGNode::setScale(float fScaleX, float fScaleY, float fScaleZ)
{
    this->setScaleX(fScaleX);
    this->setScaleY(fScaleY);
    this->setScaleZ(fScaleY);
}

float CGNode::getScaleX()
{
    return m_fScaleX;
}

void CGNode::setScaleX(float newScaleX)
{
    if (m_fScaleX != newScaleX)
    {
        m_fScaleX = newScaleX;
        this->updateDraw();
    }
}

float CGNode::getScaleY()
{
    return m_fScaleY;
}

void CGNode::setScaleY(float newScaleY)
{
    if (m_fScaleY != newScaleY)
    {
        m_fScaleY = newScaleY;
        this->updateDraw();
    }
}

float CGNode::getScaleZ() const
{
    return m_fScaleZ;
}

void CGNode::setScaleZ(float scaleZ)
{
    if (m_fScaleZ != scaleZ)
    {
        m_fScaleZ = scaleZ;
        this->updateDraw();
    }
}

/// scaleY getter


const CAVector<CGNode*>& CGNode::getChildren()
{
    return m_obChildren;
}

unsigned int CGNode::getChildrenCount() const
{
    return (unsigned int)m_obChildren.size();
}

bool CGNode::isVisible()
{
    return m_bVisible;
}

void CGNode::setVisible(bool var)
{
    m_bVisible = var;
    this->updateDraw();
}

const DPoint& CGNode::getAnchorPointInPoints()
{
    return m_obAnchorPointInPoints;
}

const DPoint& CGNode::getAnchorPoint()
{
    return m_obAnchorPoint;
}

void CGNode::setAnchorPoint(const DPoint& anchorPoint)
{
    if( ! anchorPoint.equals(m_obAnchorPoint))
    {
        m_obAnchorPoint = anchorPoint;
        m_obAnchorPointInPoints = ccpCompMult(m_obContentSize, anchorPoint);
        this->updateDraw();
    }
}

const DPoint& CGNode::getNormalizedPosition() const
{
    return m_obNormalizedPosition;
}

void CGNode::setNormalizedPosition(const DPoint& position)
{
    if ( ! position.equals(m_obNormalizedPosition))
    {
        m_obNormalizedPosition = position;
        m_bUsingNormalizedPosition = true;
        m_bNormalizedPositionDirty = true;
        this->updateDraw();
    }
}

const DPoint& CGNode::getPosition()
{
    return m_obPosition;
}

void CGNode::setPosition(const DPoint& position)
{
    if( ! position.equals(m_obPosition))
    {
        m_obPosition = position;
        m_bUsingNormalizedPosition = false;
        this->updateDraw();
    }
}

float CGNode::getPositionX() const
{
    return m_obPosition.x;
}

void CGNode::setPositionX(float x)
{
    setPosition(DPoint(x, m_obPosition.y));
}

float CGNode::getPositionY() const
{
    return  m_obPosition.y;
}

void CGNode::setPositionY(float y)
{
    setPosition(DPoint(m_obPosition.x, y));
}

float CGNode::getPositionZ() const
{
    return m_fPositionZ;
}

void CGNode::setPositionZ(float positionZ)
{
    if (positionZ != m_fPositionZ)
    {
        m_fPositionZ = positionZ;
        this->updateDraw();
    }
}


void CGNode::setPosition3D(const DPoint3D& position)
{
    setPositionZ(position.z);
    setPosition(DPoint(position.x, position.y));
}

DPoint3D CGNode::getPosition3D() const
{
    return DPoint3D(m_obPosition.x, m_obPosition.y, m_fPositionZ);
}

const DSize& CGNode::getContentSize()
{
    return m_obContentSize;
}

void CGNode::setContentSize(const DSize & contentSize)
{
    if (!contentSize.equals(m_obContentSize))
    {
        m_obContentSize = contentSize;
        m_obAnchorPointInPoints.x = m_obContentSize.width * m_obAnchorPoint.x;
        m_obAnchorPointInPoints.y = m_obContentSize.height * m_obAnchorPoint.y;
        
        if (m_pCAView)
        {
            m_pCAView->reViewlayout(m_obContentSize);
        }
        this->updateDraw();
    }
}

bool CGNode::isRunning()
{
    return m_bRunning;
}

CGNode * CGNode::getParent()
{
    return m_pParent;
}

void CGNode::setParent(CrossApp::CGNode * Parent)
{
    m_pParent = Parent;
}

unsigned int CGNode::getOrderOfArrival()
{
    return m_uOrderOfArrival;
}

void CGNode::setOrderOfArrival(unsigned int uOrderOfArrival)
{
    m_uOrderOfArrival = uOrderOfArrival;
}

GLProgram* CGNode::getShaderProgram()
{
    return m_pGlProgramState ? m_pGlProgramState->getGLProgram() : nullptr;
}

void CGNode::setShaderProgram(GLProgram *glProgram)
{
    if (m_pGlProgramState == nullptr || (m_pGlProgramState && m_pGlProgramState->getGLProgram() != glProgram))
    {
        this->setGLProgramState(GLProgramState::getOrCreateWithGLProgram(glProgram));
    }
}

GLProgramState* CGNode::getGLProgramState()
{
    return m_pGlProgramState;
}

void CGNode::setGLProgramState(GLProgramState* glProgramState)
{
    if (glProgramState != m_pGlProgramState)
    {
        CC_SAFE_RETAIN(glProgramState);
        CC_SAFE_RELEASE(m_pGlProgramState);
        m_pGlProgramState = glProgramState;
        
        
        if (m_pGlProgramState)
            m_pGlProgramState->setBinding(this);
    }
}

DRect CGNode::boundingBox()
{
    DRect rect = DRect(0, 0, m_obContentSize.width, m_obContentSize.height);
    rect = RectApplyAffineTransform(rect, getNodeToParentAffineTransform());
    rect.origin.y += rect.size.height;
    if (this->m_pParent)
    {
        rect.origin.y = this->m_pParent->m_obContentSize.height - rect.origin.y;
    }
    else
    {
        rect.origin.y = CAApplication::getApplication()->getWinSize().height - rect.origin.y;
    }
    return rect;
}

const char* CGNode::description()
{
    return crossapp_format_string("<CGNode | TextTag = %s | Tag = %d >", m_sTextTag.c_str(), m_nTag).c_str();
}

void CGNode::updateDraw()
{
    m_bContentSizeDirty = m_bTransformUpdated = m_bTransformDirty = m_bInverseDirty = true;
    CGNode* v = this->getParent();
    while (v && v == v->getParent())
    {
        CC_RETURN_IF(v && !v->isVisible());
    }
    CAApplication::getApplication()->updateDraw();
}

CGNode* CGNode::getChildByTag(int aTag)
{
    CCAssert( aTag != TagInvalid, "Invalid tag");
    
    if(!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
        {
            if (var->m_nTag == aTag)
            {
                return var;
            }
        }
    }
    return NULL;
}

CGNode* CGNode::getChildByTextTag(const std::string& textTag)
{
    CCAssert( !textTag.empty(), "Invalid tag");
    
    if(!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
        {
            if (var->m_sTextTag.compare(textTag) == 0)
            {
                return var;
            }
        }
    }
    return NULL;
}

void CGNode::addChild(CGNode* child)
{
    this->insertChild(child, child->getZOrder());
}

void CGNode::insertChild(CGNode* child, int z)
{
    CCAssert(child != NULL, "Argument must be non-nil");
    CCAssert(child->m_pParent == NULL, "child already added. It can't be added again");
    
    m_bReorderChildDirty = true;
    m_obChildren.pushBack(child);
    child->_setZOrder(z);
    
    child->setParent(this);
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    
    if(m_bRunning)
    {
       child->onEnter();
       child->onEnterTransitionDidFinish();
    }
}

void CGNode::removeFromParent()
{
    if (m_pParent != NULL)
    {
        m_pParent->removeChild(this);
    }
}

void CGNode::removeChild(CGNode* child)
{
    if (m_obChildren.contains(child))
    {
        this->detachChild(child);
    }
}

void CGNode::removeChildByTag(int tag)
{
    CCAssert( tag != TagInvalid, "Invalid tag");
    
    CGNode* child = this->getChildByTag(tag);
    
    if (child)
    {
        this->removeChild(child);
    }
}

void CGNode::removeChildByTextTag(const std::string& textTag)
{
    CCAssert( !textTag.empty(), "Invalid tag");
    
    CGNode* child = this->getChildByTextTag(textTag);
    
    if (child)
    {
        this->removeChild(child);
    }
}

void CGNode::removeAllChildren()
{
    if (!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
        {
            if(m_bRunning)
            {
                var->onExitTransitionDidStart();
                var->onExit();
            }
            var->setParent(nullptr);
        }
        m_obChildren.clear();
    }
}


void CGNode::detachChild(CGNode* child)
{
    if (m_bRunning)
    {
       child->onExitTransitionDidStart();
       child->onExit();
    }
    
    child->setParent(nullptr);
    
    m_obChildren.eraseObject(child);
    
    this->updateDraw();
}

void CGNode::reorderChild(CGNode* child, int zOrder)
{
    if (zOrder == child->getZOrder())
    {
        return;
    }
    
    CCAssert(child != NULL, "Child must be non-nil");
    m_bReorderChildDirty = true;
    child->setOrderOfArrival(s_globalOrderOfArrival++);
    child->_setZOrder(zOrder);
    this->updateDraw();
}

void CGNode::sortAllChildren()
{
    if (m_bReorderChildDirty && !m_obChildren.empty())
    {
        std::sort(m_obChildren.begin(), m_obChildren.end(), compareChildrenZOrder);
        m_bReorderChildDirty = false;
    }
}

void CGNode::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags)
{
}

uint32_t CGNode::processParentFlags(const Mat4& parentTransform, uint32_t parentFlags)
{
    if(m_bUsingNormalizedPosition)
    {
        if ((parentFlags & FLAGS_CONTENT_SIZE_DIRTY) || m_bNormalizedPositionDirty)
        {
            auto& s = m_pParent->getContentSize();
            m_obPosition.x = m_obNormalizedPosition.x * s.width;
            m_obPosition.y = m_obNormalizedPosition.y * s.height;
            m_bTransformUpdated = m_bTransformDirty = m_bInverseDirty = true;
            m_bNormalizedPositionDirty = false;
        }
    }
    
    if (!isVisitableByVisitingCamera())
        return parentFlags;
    
    uint32_t flags = parentFlags;
    flags |= (m_bTransformUpdated ? FLAGS_TRANSFORM_DIRTY : 0);
    flags |= (m_bContentSizeDirty ? FLAGS_CONTENT_SIZE_DIRTY : 0);
    
    
    //if(flags & FLAGS_DIRTY_MASK)
        m_tModelViewTransform = this->transform(parentTransform);
    
    m_bTransformUpdated = false;
    m_bContentSizeDirty = false;
    
    return flags;
}

bool CGNode::isVisitableByVisitingCamera() const
{
    auto camera = CACamera::getVisitingCamera();
    bool visibleByCamera = camera ? ((unsigned short)camera->getCameraFlag() & m_iCameraMask) != 0 : true;
    return visibleByCamera;
}

void CGNode::visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags)
{
    // quick return if not visible. children won't be drawn.
    CC_RETURN_IF(!m_bVisible);
    
    uint32_t flags = processParentFlags(parentTransform, parentFlags);
    
    // IMPORTANT:
    // To ease the migration to v3.0, we still support the Mat4 stack,
    // but it is deprecated and your code should not rely on it
    m_pApplication->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    m_pApplication->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, m_tModelViewTransform);
    
    bool visibleByCamera = isVisitableByVisitingCamera();
    
    m_bScissorRestored = false;
    
    if (m_bDisplayRange == false)
    {
        m_obBeforeDrawCommand.init(0);
        m_obBeforeDrawCommand.func = [&](){
            
            Mat4 tm = Mat4::IDENTITY;
            tm.m[12] = m_obContentSize.width;
            tm.m[13] = m_obContentSize.height;
            
            Mat4 max;
            Mat4::multiply(m_tModelViewTransform, tm, &max);
            
            float minX = m_tModelViewTransform.m[12];
            float minY = m_tModelViewTransform.m[13];
            float maxX = ceilf(max.m[12] + 0.5f);
            float maxY = ceilf(max.m[13] + 0.5f);
            
            auto glview = m_pApplication->getOpenGLView();
            m_bScissorRestored = glview->isScissorEnabled();
            if (m_bScissorRestored)
            {
                m_obSupviewScissorRect = glview->getScissorRect();
                
                float x1 = MAX(minX, m_obSupviewScissorRect.getMinX());
                float y1 = MAX(minY, m_obSupviewScissorRect.getMinY());
                float x2 = MIN(maxX, m_obSupviewScissorRect.getMaxX());
                float y2 = MIN(maxY, m_obSupviewScissorRect.getMaxY());
                float width = MAX(x2-x1, 0);
                float height = MAX(y2-y1, 0);
                glview->setScissorInPoints(x1, y1, width, height);
            }
            else
            {
                glEnable(GL_SCISSOR_TEST);
                glview->setScissorInPoints(minX, minY, (maxX - minX), (maxY - minY));
            }
            
        };
        m_pApplication->getRenderer()->addCommand(&m_obBeforeDrawCommand);
    }
    
    if(!m_obChildren.empty())
    {
        sortAllChildren();
        // draw children zOrder < 0
        int i = 0;
        for( ; i < m_obChildren.size(); i++ )
        {
            auto node = m_obChildren.at(i);
            
            if (node && node->getZOrder() < 0)
                node->visit(renderer, m_tModelViewTransform, flags);
            else
                break;
        }
        // self draw
        if (visibleByCamera)
            this->draw(renderer, m_tModelViewTransform, flags);
        
        for(auto it=m_obChildren.begin()+i; it != m_obChildren.end(); ++it)
            (*it)->visit(renderer, m_tModelViewTransform, flags);
    }
    else if (visibleByCamera)
    {
        this->draw(renderer, m_tModelViewTransform, flags);
    }
    
    if (m_pCAView)
    {
        m_pCAView->visit(renderer, m_tModelViewTransform, flags);
    }
    
    if (m_bDisplayRange == false)
    {
        m_obAfterDrawCommand.init(0);
        m_obAfterDrawCommand.func = [&](){
            
            if (m_bScissorRestored)
            {
                auto glview = m_pApplication->getOpenGLView();
                glview->setScissorInPoints(m_obSupviewScissorRect.origin.x,
                                           m_obSupviewScissorRect.origin.y,
                                           m_obSupviewScissorRect.size.width,
                                           m_obSupviewScissorRect.size.height);
            }
            else
            {
                glDisable(GL_SCISSOR_TEST);
            }
        };
        m_pApplication->getRenderer()->addCommand(&m_obAfterDrawCommand);
    }
    
    m_pApplication->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);

}

void CGNode::visitEve(void)
{
    for (auto& var : m_obChildren)
        var->visitEve();
    
    if (m_pCAView)
    {
        m_pCAView->visitEve();
    }
}

CGNode* CGNode::copy()
{
    CGNode* view = NULL;

    return view;
}

void CGNode::onEnter()
{
    m_bRunning = true;
    CAScheduler::getScheduler()->resumeTarget(this);
    CAApplication::getApplication()->getActionManager()->resumeTarget(this);
    
    if (!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
            var->onEnter();
    }
    
    if (m_pCAView)
    {
        m_pCAView->reViewlayout(m_obContentSize);
        m_pCAView->onEnter();
    }
    
    if (m_obOnEnterCallback)
    {
        m_obOnEnterCallback();
    }
}

void CGNode::onEnterTransitionDidFinish()
{
    if (!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
            var->onEnterTransitionDidFinish();
    }
    
    if (m_pCAView)
    {
        m_pCAView->onEnterTransitionDidFinish();
    }
    
    if (m_obOnEnterTransitionDidFinishCallback)
    {
        m_obOnEnterTransitionDidFinishCallback();
    }
}

void CGNode::onExitTransitionDidStart()
{
    if (!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
            var->onExitTransitionDidStart();
    }
    
    if (m_pCAView)
    {
        m_pCAView->onExitTransitionDidStart();
    }
    
    if (m_obOnExitTransitionDidStartCallback)
    {
        m_obOnExitTransitionDidStartCallback();
    }
}

void CGNode::onExit()
{
    m_bRunning = false;
    CAScheduler::getScheduler()->pauseTarget(this);
    CAApplication::getApplication()->getActionManager()->pauseTarget(this);
    
    if (!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
            var->onExit();
    }
    
    if (m_pCAView)
    {
        m_pCAView->onExit();
    }
    
    if (m_obOnExitCallback)
    {
        m_obOnExitCallback();
    }
}

void CGNode::update(float fDelta)
{
    
}

AffineTransform CGNode::getNodeToParentAffineTransform() const
{
    AffineTransform ret;
    GLToCGAffine(getNodeToParentTransform().m, &ret);
    
    return ret;
}


Mat4 CGNode::getNodeToParentTransform(CGNode* ancestor) const
{
    Mat4 t(this->getNodeToParentTransform());
    
    CGNode *p = m_pParent;
    if (p)
    {
        while (p)
        {
            t = p->getNodeToParentTransform() * t;
            CC_BREAK_IF(!p->getParent());
            p = p->getParent();
            CC_BREAK_IF(p == ancestor);
        }
        
        if (p && p != ancestor)
        {
            if (CAView *s = p->m_pSuperviewCAView)
            {
                t = s->getViewToSuperviewTransform(nullptr) * t;
            }
        }
    }
    else
    {
        if (CAView *s = m_pSuperviewCAView)
        {
            t = s->getViewToSuperviewTransform(nullptr) * t;
        }
    }

    return t;
}

AffineTransform CGNode::getNodeToParentAffineTransform(CGNode* ancestor) const
{
    AffineTransform t(this->getNodeToParentAffineTransform());
    
    CGNode *p = m_pParent;
    if (p)
    {
        while (p)
        {
            t = AffineTransformConcat(t, p->getNodeToParentAffineTransform());
            CC_BREAK_IF(!p->getParent());
            p = p->getParent();
            CC_BREAK_IF(p == ancestor);
        }
        
        if (p && p != ancestor)
        {
            if (CAView *s = p->m_pSuperviewCAView)
            {
                t = AffineTransformConcat(t, s->getViewToSuperviewAffineTransform(nullptr));
            }
        }
    }
    else
    {
        if (CAView *s = m_pSuperviewCAView)
        {
            t = AffineTransformConcat(t, s->getViewToSuperviewAffineTransform(nullptr));
        }
    }
    
    return t;
}

const Mat4& CGNode::getNodeToParentTransform() const
{
    if (m_bTransformDirty)
    {
        DSize size;
        if (this->m_pParent)
        {
            size = this->m_pParent->m_obContentSize;
        }
        else if (this->m_pSuperviewCAView)
        {
            size = this->m_pSuperviewCAView->m_obContentSize;
        }
        else
        {
            size = CAApplication::getApplication()->getWinSize();
        }
        
        float x, y;
        if (m_bUsingNormalizedPosition)
        {
            
            x = m_obNormalizedPosition.x * size.width;
            y = (1 - m_obNormalizedPosition.y) * size.height;
        }
        else
        {
            x = m_obPosition.x;
            y = size.height - m_obPosition.y;
        }
        float z = m_fPositionZ;
        
        bool needsSkewMatrix = ( m_fSkewX || m_fSkewY );
        
        
        DPoint anchorPoint(m_obAnchorPointInPoints.x * m_fScaleX, (m_obContentSize.height - m_obAnchorPointInPoints.y) * m_fScaleY);
        
        if (! needsSkewMatrix && !anchorPoint.equals(DSizeZero))
        {
            x += -anchorPoint.x;
            y += -anchorPoint.y;
        }
        
        Mat4 translation;
        Mat4::createTranslation(x + anchorPoint.x, y + anchorPoint.y, z, &translation);
        Mat4::createRotation(m_obRotationQuat, &m_tTransform);
        
        if (m_fRotationZ_X != m_fRotationZ_Y)
        {
            // Rotation values
            // Change rotation code to handle X and Y
            // If we skew with the exact same value for both x and y then we're simply just rotating
            float radiansX = -CC_DEGREES_TO_RADIANS(m_fRotationZ_X);
            float radiansY = -CC_DEGREES_TO_RADIANS(m_fRotationZ_Y);
            float cx = cosf(radiansX);
            float sx = sinf(radiansX);
            float cy = cosf(radiansY);
            float sy = sinf(radiansY);
            
            float m0 = m_tTransform.m[0], m1 = m_tTransform.m[1], m4 = m_tTransform.m[4], m5 = m_tTransform.m[5], m8 = m_tTransform.m[8], m9 = m_tTransform.m[9];
            
            m_tTransform.m[0] = cy * m0 - sx * m1, m_tTransform.m[4] = cy * m4 - sx * m5, m_tTransform.m[8] = cy * m8 - sx * m9;
            m_tTransform.m[1] = sy * m0 + cx * m1, m_tTransform.m[5] = sy * m4 + cx * m5, m_tTransform.m[9] = sy * m8 + cx * m9;
        }
        
        m_tTransform = translation * m_tTransform;
        m_tTransform.translate(-anchorPoint.x, -anchorPoint.y, 0);
        
        
        if (m_fScaleX != 1.f)
        {
            m_tTransform.m[0] *= m_fScaleX, m_tTransform.m[1] *= m_fScaleX, m_tTransform.m[2] *= m_fScaleX;
        }
        if (m_fScaleY != 1.f)
        {
            m_tTransform.m[4] *= m_fScaleY, m_tTransform.m[5] *= m_fScaleY, m_tTransform.m[6] *= m_fScaleY;
        }
        if (m_fScaleZ != 1.f)
        {
            m_tTransform.m[8] *= m_fScaleZ, m_tTransform.m[9] *= m_fScaleZ, m_tTransform.m[10] *= m_fScaleZ;
        }
        
        if (needsSkewMatrix)
        {
            float skewMatArray[16] =
            {
                1, (float)tanf(CC_DEGREES_TO_RADIANS(m_fSkewY)), 0, 0,
                (float)tanf(CC_DEGREES_TO_RADIANS(m_fSkewX)), 1, 0, 0,
                0,  0,  1, 0,
                0,  0,  0, 1
            };
            Mat4 skewMatrix(skewMatArray);
            
            m_tTransform = m_tTransform * skewMatrix;
            
            if (!m_obAnchorPointInPoints.equals(DSizeZero))
            {
                DPoint anchorPoint(m_obAnchorPointInPoints.x * m_fScaleX, (m_obContentSize.height - m_obAnchorPointInPoints.y) * m_fScaleY);
                m_tTransform.m[12] += m_tTransform.m[0] * -anchorPoint.x + m_tTransform.m[4] * -anchorPoint.y;
                m_tTransform.m[13] += m_tTransform.m[1] * -anchorPoint.x + m_tTransform.m[5] * -anchorPoint.y;
            }
        }
    }

    if (m_pAdditionalTransform)
    {
        if (m_bTransformDirty)
        {
            m_pAdditionalTransform[1] = m_tTransform;
        }
        
        if (m_bTransformUpdated)
        {
            m_tTransform = m_pAdditionalTransform[1] * m_pAdditionalTransform[0];
        }
    }
    m_bTransformDirty = m_bAdditionalTransformDirty = false;
    
    return m_tTransform;
}

void CGNode::setViewToParentTransform(const Mat4& transform)
{
    m_tTransform = transform;
    m_bTransformDirty = false;
    m_bTransformUpdated = true;
}

void CGNode::setAdditionalTransform(const AffineTransform& additionalTransform)
{
    Mat4 tmp;
    CGAffineToGL(additionalTransform, tmp.m);
    setAdditionalTransform(&tmp);
}

void CGNode::setAdditionalTransform(Mat4* additionalTransform)
{
    if (additionalTransform == nullptr)
    {
        delete [] m_pAdditionalTransform;
        m_pAdditionalTransform = nullptr;
    }
    else
    {
        if (!m_pAdditionalTransform)
        {
            m_pAdditionalTransform = new Mat4[2];
            
            m_pAdditionalTransform[1] = m_tTransform;
        }
        
        m_pAdditionalTransform[0] = *additionalTransform;
    }
    m_bTransformUpdated = m_bAdditionalTransformDirty = m_bInverseDirty = true;
}


AffineTransform CGNode::getParentToNodeAffineTransform() const
{
    AffineTransform ret;
    
    GLToCGAffine(getParentToNodeTransform().m, &ret);
    return ret;
}

const Mat4& CGNode::getParentToNodeTransform() const
{
    if ( m_bInverseDirty )
    {
        m_tInverse = getNodeToParentTransform().getInversed();
        m_bInverseDirty = false;
    }
    
    return m_tInverse;
}

AffineTransform CGNode::getNodeToWorldAffineTransform() const
{
    return this->getNodeToParentAffineTransform(nullptr);
}

Mat4 CGNode::getNodeToWorldTransform() const
{
    return this->getNodeToParentTransform(nullptr);
}

AffineTransform CGNode::getWorldToViewAffineTransform() const
{
    return AffineTransformInvert(this->getNodeToWorldAffineTransform());
}

Mat4 CGNode::getWorldToViewTransform() const
{
    return getNodeToWorldTransform().getInversed();
}

Mat4 CGNode::transform(const Mat4& parentTransform)
{
    return parentTransform * this->getNodeToParentTransform();
}

void CGNode::updateTransform()
{
    for (const auto& var : m_obChildren)
        var->updateTransform();
}

DRect CGNode::convertRectToNodeSpace(const CrossApp::DRect &worldRect)
{
    DRect ret = worldRect;
    ret.origin = this->convertToNodeSpace(ret.origin);
    ret.size = this->convertToNodeSize(ret.size);
    return ret;
}

DRect CGNode::convertRectToWorldSpace(const CrossApp::DRect &nodeRect)
{
    DRect ret = nodeRect;
    ret.origin = this->convertToWorldSpace(ret.origin);
    ret.size = this->convertToWorldSize(ret.size);
    return ret;
}

DPoint CGNode::convertToNodeSpace(const DPoint& worldPoint)
{
    Mat4 tmp = getWorldToViewTransform();
    DPoint3D vec3(worldPoint.x, CAApplication::getApplication()->getWinSize().height - worldPoint.y, 0);
    DPoint3D ret;
    tmp.transformPoint(vec3,&ret);
    return DPoint(ret.x, m_obContentSize.height - ret.y);
}

DPoint CGNode::convertToWorldSpace(const DPoint& nodePoint)
{
    Mat4 tmp = getNodeToWorldTransform();
    DPoint3D vec3(nodePoint.x, m_obContentSize.height - nodePoint.y, 0);
    DPoint3D ret;
    tmp.transformPoint(vec3,&ret);
    return DPoint(ret.x, CAApplication::getApplication()->getWinSize().height - ret.y);
}

DSize CGNode::convertToNodeSize(const DSize& worldSize)
{
    DSize ret = worldSize;
    for (CGNode* v = this; v; v = v->m_pParent)
    {
        ret.width /= v->m_fScaleX;
        ret.height /= v->m_fScaleY;
    }
    return ret;
}

DSize CGNode::convertToWorldSize(const DSize& nodeSize)
{
    DSize ret = nodeSize;
    for (CGNode* v = this; v; v = v->m_pParent)
    {
        ret.width *= v->m_fScaleX;
        ret.height *= v->m_fScaleY;
    }
    return ret;
}

DPoint CGNode::convertTouchToNodeSpace(CATouch *touch)
{
    DPoint point = touch->getLocation();
    return this->convertToNodeSpace(point);
}

bool CGNode::isDisplayRange()
{
    return m_bDisplayRange;
}

void CGNode::setDisplayRange(bool value)
{
    m_bDisplayRange = value;
}

float CGNode::getAlpha(void)
{
    return _realAlpha;
}

float CGNode::getDisplayedAlpha(void)
{
    return _displayedAlpha;
}

void CGNode::setAlpha(float alpha)
{
    alpha = MIN(alpha, 1.0f);
    alpha = MAX(alpha, 0.0f);
    
    _realAlpha = alpha;
    
    float parentAlpha = m_pParent ? m_pParent->getDisplayedAlpha() : 1.0f;
    
    this->updateDisplayedAlpha(parentAlpha);
}

void CGNode::updateDisplayedAlpha(float parentAlpha)
{
    _displayedAlpha = _realAlpha * parentAlpha;
    
    if (!m_obChildren.empty())
    {
        for (auto& var : m_obChildren)
            var->updateDisplayedAlpha(_displayedAlpha);
    }
    
    this->updateColor();
}

const CAColor4B& CGNode::getColor(void)
{
    return _realColor;
}

const CAColor4B& CGNode::getDisplayedColor()
{
    return _displayedColor;
}

void CGNode::setColor(const CAColor4B& color)
{
    _realColor = color;
    _displayedColor = color;
    this->updateColor();
}

void CGNode::updateDisplayedColor(const CAColor4B& superviewColor)
{
    _displayedColor.r = _realColor.r * superviewColor.r/255.0;
    _displayedColor.g = _realColor.g * superviewColor.g/255.0;
    _displayedColor.b = _realColor.b * superviewColor.b/255.0;
    _displayedColor.a = _realColor.a * superviewColor.a/255.0;
    
    updateColor();
}

void CGNode::updateColor(void)
{
    CAColor4B color4 = _displayedColor;
    color4.a = color4.a * _displayedAlpha;

    m_sQuad.bl.colors = color4;
    m_sQuad.br.colors = color4;
    m_sQuad.tl.colors = color4;
    m_sQuad.tr.colors = color4;

    this->updateDraw();
}

void CGNode::updateBlendFunc(void)
{
    m_sBlendFunc.src = CC_BLEND_SRC;
    m_sBlendFunc.dst = CC_BLEND_DST;
}


Action * CGNode::runAction(Action* action)
{
    CCAssert( action != nullptr, "Argument must be non-nil");
    CAApplication::getApplication()->getActionManager()->addAction(action, this, !m_bRunning);
    return action;
}

void CGNode::stopAllActions()
{
    CAApplication::getApplication()->getActionManager()->removeAllActionsFromTarget(this);
}

void CGNode::stopAction(Action* action)
{
    CAApplication::getApplication()->getActionManager()->removeAction(action);
}

void CGNode::stopActionByTag(int tag)
{
    CCAssert( tag != Action::INVALID_TAG, "Invalid tag");
    CAApplication::getApplication()->getActionManager()->removeActionByTag(tag, this);
}

void CGNode::stopAllActionsByTag(int tag)
{
    CCAssert( tag != Action::INVALID_TAG, "Invalid tag");
    CAApplication::getApplication()->getActionManager()->removeAllActionsByTag(tag, this);
}

void CGNode::stopActionsByFlags(unsigned int flags)
{
    if (flags > 0)
    {
        CAApplication::getApplication()->getActionManager()->removeActionsByFlags(flags, this);
    }
}

Action * CGNode::getActionByTag(int tag)
{
    CCAssert( tag != Action::INVALID_TAG, "Invalid tag");
    return CAApplication::getApplication()->getActionManager()->getActionByTag(tag, this);
}

size_t CGNode::getNumberOfRunningActions() const
{
    return CAApplication::getApplication()->getActionManager()->getNumberOfRunningActionsInTarget(this);
}


bool CGNode::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
    return false;
}

void CGNode::ccTouchMoved(CATouch *pTouch, CAEvent *pEvent)
{
}

void CGNode::ccTouchEnded(CATouch *pTouch, CAEvent *pEvent)
{
}

void CGNode::ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent)
{
}

void CGNode::setCameraMask(unsigned short mask, bool applySubiew)
{
    m_iCameraMask = mask;
    if (applySubiew)
    {
        for (const auto& child : m_obChildren)
        {
            child->setCameraMask(mask, applySubiew);
        }
    }
}

CAView* CGNode::getCAView()
{
    return m_pCAView;
}

void CGNode::setCAView(CrossApp::CAView *var)
{
    if (m_bRunning && m_pCAView && m_pCAView->isRunning())
    {
        m_pCAView->m_pParentCGNode = NULL;
        m_pCAView->onExitTransitionDidStart();
        m_pCAView->onExit();
    }
    
    CC_SAFE_RETAIN(var);
    CC_SAFE_RELEASE(m_pCAView);
    m_pCAView = var;
    m_pCAView->m_pParentCGNode = this;
    
    if (m_bRunning && m_pCAView && !m_pCAView->isRunning())
    {
        m_pCAView->onEnter();
        m_pCAView->onEnterTransitionDidFinish();
    }
    
    CAApplication::getApplication()->updateDraw();
}

NS_CC_END;
