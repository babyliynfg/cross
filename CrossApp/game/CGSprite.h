//
//  CGSprite.h
//  CrossApp
//
//  Created by Li Yuanfeng on 16-7-19.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#ifndef __CGSPRITE_H__
#define __CGSPRITE_H__

#include "CGNode.h"
#include "dispatcher/CAProtocols.h"
#include "images/CAImageCache.h"
#include "ccTypes.h"
#include <string>
#include "renderer/CCTrianglesCommand.h"

NS_CC_BEGIN

class CGSpriteBatchNode;
class CGSpriteFrame;
class CGAnimation;

class CC_DLL CGSprite : public CGNode, public CAImageProtocol
{
public:

    static CGSprite* create();

    static CGSprite* create(const std::string& pszFileName);

    static CGSprite* create(const std::string& pszFileName, const DRect& rect);

    static CGSprite* createWithImage(CAImage *image);

    static CGSprite* createWithImage(CAImage *image, const DRect& rect);

    static CGSprite* createWithSpriteFrame(CGSpriteFrame *pSpriteFrame);

    static CGSprite* createWithSpriteFrameName(const std::string& pszSpriteFrameName);
    
    CGSprite(void);

    virtual ~CGSprite(void);

    virtual bool init() override;

    virtual bool initWithImage(CAImage *image);

    virtual bool initWithImage(CAImage *image, const DRect& rect);

    virtual bool initWithImage(CAImage *image, const DRect& rect, bool rotated);

    virtual bool initWithSpriteFrame(CGSpriteFrame *pSpriteFrame);

    virtual bool initWithSpriteFrameName(const std::string& pszSpriteFrameName);

    virtual bool initWithFile(const std::string& pszFilename);

    virtual bool initWithFile(const std::string& pszFilename, const DRect& rect);

    virtual void setImage(CAImage *image) override;
    
    virtual CAImage* getImage() override;
  
    virtual void insertChild(CGNode* child, int z) override;
    
    virtual void removeChild(CGNode* child) override;
    
    virtual void reorderChild(CGNode *pChild, int zOrder) override;
    
    virtual void sortAllChildren() override;

    virtual void setOpacityModifyRGB(bool modify) override;
    
    virtual bool isOpacityModifyRGB() const override;
    
    virtual void updateTransform(void) override;

    virtual CGSpriteBatchNode* getBatchNode(void);

    virtual void setBatchNode(CGSpriteBatchNode *pobSpriteBatchNode);

    virtual void setImageRect(const DRect& rect);
 
    virtual void setImageRect(const DRect& rect, bool rotated, const DSize& untrimmedSize);

    virtual void setVertexRect(const DRect& rect);

    virtual void setSpriteFrame(CGSpriteFrame *pNewFrame);

    virtual bool isFrameDisplayed(CGSpriteFrame *pFrame);

    virtual CGSpriteFrame* getSpriteFrame(void);

    virtual void setDisplayFrameWithAnimationName(const std::string& animationName, int frameIndex);

    inline virtual bool isDirty(void) { return m_bDirty; }

    inline virtual void setDirty(bool bDirty) { m_bDirty = bDirty; }

    inline ccV3F_C4B_T2F_Quad getQuad(void) { return m_sQuad; }

    inline bool isTextureRectRotated(void) { return m_bRectRotated; }

    inline unsigned int getAtlasIndex(void) { return m_uAtlasIndex; }

    inline void setAtlasIndex(ssize_t uAtlasIndex) { m_uAtlasIndex = uAtlasIndex; }

    inline const DRect& getImageRect(void) { return m_obRect; }

    inline CAImageAtlas* getImageAtlas(void) { return m_pobImageAtlas; }

    inline void setImageAtlas(CAImageAtlas *pobTextureAtlas) { m_pobImageAtlas = pobTextureAtlas; }

    inline const DPoint& getOffsetPosition(void) { return m_obOffsetPosition; }

    bool isFlipX(void);

    void setFlipX(bool bFlipX);

    bool isFlipY(void);

    void setFlipY(bool bFlipY);
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
protected:
    
    virtual void updateDraw() override;
    
    virtual void updateColor(void) override;
    
    virtual void updateBlendFunc(void) override;
    
    virtual void setImageCoords(const DRect& rect);

    virtual void setReorderChildDirtyRecursively(void);
    
    virtual void setDirtyRecursively(bool bValue);
    
    bool                        m_bInsideBounds;
    CAImageAtlas*               m_pobImageAtlas;
    CAImage*                    m_pobImage;
    ssize_t                     m_uAtlasIndex;
    CGSpriteBatchNode*          m_pobBatchNode;
    
    TrianglesCommand            m_obTrianglesCommand;
    TrianglesCommand::Triangles m_obTriangles;
    
    bool                        m_bDirty;               /// Whether the sprite needs to be updated
    bool                        m_bRecursiveDirty;      /// Whether all of the sprite's children needs to be updated
    bool                        m_bHasChildren;         /// Whether the sprite contains children
    bool                        m_bShouldBeHidden;      /// should not be drawn because one of the ancestors is not
    
    Mat4                        m_tTransformToBatch;
    //
    // Shared data
    //
    
    // texture
    DRect m_obRect;                            /// Retangle of CAImage
    bool   m_bRectRotated;                      /// Whether the texture is rotated
    
    // Offset Position (used by Zwoptex)
    DPoint m_obOffsetPosition;
    DPoint m_obUnflippedOffsetPositionFromCenter;
    
    // vertex coords, texture coords and color info
    ccV3F_C4B_T2F_Quad m_sQuad;
    
    // opacity and RGB protocol
    bool m_bOpacityModifyRGB;
    
    // image is flipped
    bool m_bFlipX;                              /// Whether the sprite is flipped horizaontally or not.
    bool m_bFlipY;                              /// Whether the sprite is flipped vertically or not.
};


// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __SPITE_NODE_CGSprite_H__
