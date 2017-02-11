//
//  CGNode.h
//  CrossApp
//
//  Created by Li Yuanfeng on 16-7-12.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#ifndef __CGNode__
#define __CGNode__

#include <iostream>
#include "ccMacros.h"
#include "CCGL.h"
#include "ccTypes.h"
#include "basics/CASTLContainer.h"
#include <map>
#include "math/TransformUtils.h"
#include "math/CAAffineTransform.h"
#include "math/CAMath.h"
#include "math/TransformUtils.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCGLProgramStateCache.h"
#include "renderer/ccGLStateCache.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCRenderState.h"
#include "renderer/CCFrameBuffer.h"

NS_CC_BEGIN

class CACamera;
class DPoint;
class CATouch;
class CAView;
class Action;
class ActionManager;

class CC_DLL CGNode :public CAObject
{
    
public:
    
    static CGNode * create(void);

    CGNode();
    
    virtual ~CGNode();
    
    virtual bool init();

    const char* description(void);
    
    virtual void setZOrder(int zOrder);
    
    virtual void _setZOrder(int z);
    
    virtual int getZOrder();

    virtual void setScaleX(float fScaleX);
    
    virtual float getScaleX();
    
    virtual void setScaleY(float fScaleY);
    
    virtual float getScaleY();
    
    virtual void setScaleZ(float scaleZ);
    
    virtual float getScaleZ() const;
    
    virtual void setScale(float scale);
    
    virtual float getScale();
    
    virtual void setScale(float fScaleX, float fScaleY, float fScaleZ);
    
    virtual void setSkewX(float fSkewX);
    
    virtual float getSkewX();
    
    virtual void setSkewY(float fSkewY);
    
    virtual float getSkewY();
    
    void setAnchorPoint(const DPoint& anchorPoint);
    
    const DPoint& getAnchorPoint();
    
    const DPoint& getAnchorPointInPoints();

    virtual void setVisible(bool visible);
    
    virtual bool isVisible();
    
    virtual void setRotationZ(float fRotation);
    
    virtual float getRotationZ();
    
    virtual void setRotationX(float fRotaionX);
    
    virtual float getRotationX();
    
    virtual void setRotationY(float fRotationY);
    
    virtual float getRotationY();
    
    virtual void setRotation3D(const DPoint3D& rotation);

    virtual DPoint3D getRotation3D() const;

    virtual void setRotationQuat(const Quaternion& quat);

    virtual Quaternion getRotationQuat() const;
    
    virtual void setPosition(const DPoint &point);
    
    virtual const DPoint& getPosition();
    
    virtual void setNormalizedPosition(const DPoint &position);

    virtual const DPoint& getNormalizedPosition() const;

    virtual void  setPositionX(float x);

    virtual float getPositionX(void) const;

    virtual void  setPositionY(float y);

    virtual float getPositionY(void) const;

    virtual void setPositionZ(float positionZ);

    virtual float getPositionZ() const;
    
    virtual void setPosition3D(const DPoint3D& position);
    
    virtual DPoint3D getPosition3D() const;
    
    virtual const DSize& getContentSize();
    
    virtual void setContentSize(const DSize& contentSize);

    virtual void addChild(CGNode* child);
     
    virtual void insertChild(CGNode* child, int z);
    
    virtual CGNode * getChildByTag(int tag);
    
    virtual CGNode * getChildByTextTag(const std::string& textTag);
    
    virtual const CAVector<CGNode*>& getChildren();
    
    virtual unsigned int getChildrenCount() const;
    
    virtual void setParent(CGNode* Parent);
    
    virtual CGNode* getParent();
    
    virtual void removeFromParent();
    
    virtual void removeChild(CGNode* child);
    
    virtual void removeChildByTag(int tag);
    
    virtual void removeChildByTextTag(const std::string& textTag);
    
    virtual void removeAllChildren();
    
    virtual void reorderChild(CGNode* child, int zOrder);
    
    virtual void sortAllChildren();
    
    virtual bool isRunning();
    
    virtual void onEnter();
    
    virtual void onEnterTransitionDidFinish();
    
    virtual void onExit();
    
    virtual void onExitTransitionDidStart();
    
    virtual Action* runAction(Action* action);
    
    void stopAllActions();
    
    void stopAction(Action* action);
    
    void stopActionByTag(int tag);
    
    void stopAllActionsByTag(int tag);
    
    void stopActionsByFlags(unsigned int flags);
    
    Action* getActionByTag(int tag);
    
    size_t getNumberOfRunningActions() const;
    
    virtual CACamera* getCamera();
    
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    virtual void draw() final;
    
    virtual void visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags);
    virtual void visit() final;
    
    virtual void visitEve(void);
    
    virtual DRect boundingBox();
    
    virtual CGNode* copy();

public:
    
    //check whether this camera mask is visible by the current visiting camera
    bool isVisitableByVisitingCamera() const;
    Mat4 transform(const Mat4 &parentTransform);
    uint32_t processParentFlags(const Mat4& parentTransform, uint32_t parentFlags);
    
    virtual void updateTransform();
    
    virtual const Mat4& getNodeToParentTransform() const;
    virtual AffineTransform getNodeToParentAffineTransform() const;
    
    virtual Mat4 getNodeToParentTransform(CGNode* ancestor) const;
    
    virtual AffineTransform getNodeToParentAffineTransform(CGNode* ancestor) const;
    
    virtual void setViewToParentTransform(const Mat4& transform);
    
    virtual const Mat4& getParentToNodeTransform() const;
    virtual AffineTransform getParentToNodeAffineTransform() const;
    
    
    virtual Mat4 getNodeToWorldTransform() const;
    virtual AffineTransform getNodeToWorldAffineTransform() const;
    
    virtual Mat4 getWorldToViewTransform() const;
    virtual AffineTransform getWorldToViewAffineTransform() const;
    
    void setAdditionalTransform(Mat4* additionalTransform);
    void setAdditionalTransform(const AffineTransform& additionalTransform);
    
    DRect convertRectToNodeSpace(const DRect& worldRect);
    
    DRect convertRectToWorldSpace(const DRect& nodeRect);
    
    DPoint convertToNodeSpace(const DPoint& worldPoint);
    
    DPoint convertToWorldSpace(const DPoint& nodePoint);
    
    DSize convertToNodeSize(const DSize& worldSize);
    
    DSize convertToWorldSize(const DSize& nodeSize);
    
    DPoint convertTouchToNodeSpace(CATouch * touch);
    
    virtual void setOrderOfArrival(unsigned int uOrderOfArrival);
    
    virtual unsigned int getOrderOfArrival();
    
    GLProgramState *getGLProgramState();
    
    virtual void setGLProgramState(GLProgramState *glProgramState);
    
    virtual void setShaderProgram(GLProgram *pShaderProgram);
    
    virtual GLProgram* getShaderProgram();
    
public:
    
    virtual bool isDisplayRange();
    
    virtual void setDisplayRange(bool value);
    
    virtual float getAlpha();
    
    virtual void setAlpha(float alpha);
    
    virtual float getDisplayedAlpha();
    
    virtual void updateDisplayedAlpha(float parentAlpha);
    
    virtual const CAColor4B& getColor(void);
    
    virtual const CAColor4B& getDisplayedColor();
    
    virtual void setColor(const CAColor4B& color);
    
    virtual void updateDisplayedColor(const CAColor4B& superviewColor);
    
    inline void setBlendFunc(BlendFunc blendFunc) { m_sBlendFunc = blendFunc; }
    
    inline BlendFunc getBlendFunc(void) { return m_sBlendFunc; }
    
    virtual void update(float fDelta);

    inline ccV3F_C4B_T2F_Quad getQuad(void) { return m_sQuad; }

    virtual CAView* getCAView();
    
    virtual void setCAView(CAView* var);
    
    void setOnEnterCallback(const std::function<void()>& callback) { m_obOnEnterCallback = callback; }

    const std::function<void()>& getOnEnterCallback() const { return m_obOnEnterCallback; }

    void setOnExitCallback(const std::function<void()>& callback) { m_obOnExitCallback = callback; }

    const std::function<void()>& getOnExitCallback() const { return m_obOnExitCallback; }

    void setonEnterTransitionDidFinishCallback(const std::function<void()>& callback) { m_obOnEnterTransitionDidFinishCallback = callback; }

    const std::function<void()>& getonEnterTransitionDidFinishCallback() const { return m_obOnEnterTransitionDidFinishCallback; }

    void setonExitTransitionDidStartCallback(const std::function<void()>& callback) { m_obOnExitTransitionDidStartCallback = callback; }

    const std::function<void()>& getonExitTransitionDidStartCallback() const { return m_obOnExitTransitionDidStartCallback; }

    unsigned short getCameraMask() const { return m_iCameraMask; }

    virtual void setCameraMask(unsigned short mask, bool applySubview = true);
    
public:
    
    virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);
    
protected:
    
    void detachChild(CGNode *Child);
    
    virtual void updateDraw();
    
    virtual void updateColor(void);
    
    virtual void updateBlendFunc(void);
    
    void updateRotationQuat();
    
    void updateRotation3D();
    
protected:
        
    float                       m_fSkewX;
    float                       m_fSkewY;
    
    float                       m_fRotationX;
    float                       m_fRotationY;
    float                       m_fRotationZ_X;             ///< rotation angle on Z-axis, component X
    float                       m_fRotationZ_Y;             ///< rotation angle on Z-axis, component Y
    Quaternion                  m_obRotationQuat;      ///rotation using quaternion, if _rotationZ_X == _rotationZ_Y, _rotationQuat = RotationZ_X * RotationY * RotationX, else _rotationQuat = RotationY * RotationX
    
    float                       m_fScaleX;
    float                       m_fScaleY;
    float                       m_fScaleZ;

    DPoint                      m_obAnchorPointInPoints;
    DPoint                      m_obAnchorPoint;
    
    DPoint                      m_obPosition;
    float                       m_fPositionZ;
    DPoint                      m_obNormalizedPosition;
    bool                        m_bUsingNormalizedPosition;
    bool                        m_bNormalizedPositionDirty;
    
    DSize                       m_obContentSize;
    bool                        m_bContentSizeDirty;
    
    CACamera*                   m_pCamera;
    
    int                         m_nZOrder;
    
    CAVector<CGNode*>           m_obChildren;
    CGNode*                     m_pParent;
    
    
    // "cache" variables are allowed to be mutable
    mutable Mat4                m_tTransform;      ///< transform
    mutable bool                m_bTransformDirty;   ///< transform dirty flag
    mutable Mat4                m_tInverse;        ///< inverse transform
    mutable bool                m_bInverseDirty;     ///< inverse transform dirty flag
    mutable Mat4                m_tAdditionalTransform; ///< transform
    bool                        m_bUseAdditionalTransform;   ///< The flag to check whether the additional transform is dirty
    bool                        m_bTransformUpdated;         ///< Whether or not the Transform object was updated since the last
    
    Mat4                        m_tModelViewTransform;       ///< ModelView transform of the Node.
    Mat4                        m_tTransformToBatch;
    
    unsigned int                m_uOrderOfArrival;
    
    GLProgramState              *m_pGlProgramState;
    
    bool                        m_bRunning;
    
    bool                        m_bVisible;

    float                       _displayedAlpha;
    float                       _realAlpha;
    CAColor4B                   _displayedColor;
    CAColor4B                   _realColor;
    
    unsigned short              m_iCameraMask;
    
    std::function<void()>       m_obOnEnterCallback;
    std::function<void()>       m_obOnExitCallback;
    std::function<void()>       m_obOnEnterTransitionDidFinishCallback;
    std::function<void()>       m_obOnExitTransitionDidStartCallback;
    
    bool                        m_bDisplayRange;

    bool                        m_bHasChildren;

    bool                        m_bReorderChildDirty;
    
    ccV3F_C4B_T2F_Quad          m_sQuad;
    
    BlendFunc                   m_sBlendFunc;
    
    CAView*                     m_pCAView;
    CAView*                     m_pSuperviewCAView;
    
    CAApplication*              m_pApplication;
    
    friend class                CAView;
    
public:
    
    static std::map<int, CGNode*>& getInstanceMap();
};

static bool compareChildrenZOrder(CGNode* one, CGNode* two)
{
    if (one->getZOrder() < two->getZOrder())
    {
        return true;
    }
    else if (one->getZOrder() == two->getZOrder())
    {
        return (bool)(one->getOrderOfArrival() < two->getOrderOfArrival());
    }
    return false;
}

NS_CC_END


#endif
