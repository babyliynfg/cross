#ifndef __CGSpriteBatchNode_H__
#define __CGSpriteBatchNode_H__

#include "CGNode.h"
#include "ccMacros.h"
#include "dispatcher/CAProtocols.h"
#include "images/CAImageCache.h"
#include "renderer/CCBatchCommand.h"

NS_CC_BEGIN

#define kDefaultSpriteBatchCapacity   29

class CGSprite;

class CC_DLL CGSpriteBatchNode : public CGNode, public CAImageProtocol
{
public:

    CGSpriteBatchNode();

    virtual ~CGSpriteBatchNode();

    inline CAImageAtlas* getImageAtlas(void) { return m_pobImageAtlas; }
    
    inline void setImageAtlas(CAImageAtlas* ImageAtlas) 
    { 
        if (ImageAtlas != m_pobImageAtlas)
        {
            CC_SAFE_RETAIN(ImageAtlas);
            CC_SAFE_RELEASE(m_pobImageAtlas);
            m_pobImageAtlas = ImageAtlas;
        }
    }

    inline const CAVector<CGSprite*>& getDescendants(void) { return m_obDescendants; }

    static CGSpriteBatchNode* createWithImage(CAImage* image, unsigned int capacity);
    
    static CGSpriteBatchNode* createWithImage(CAImage* image)
    {
        return CGSpriteBatchNode::createWithImage(image, kDefaultSpriteBatchCapacity);
    }

    static CGSpriteBatchNode* create(const std::string& fileImage, unsigned int capacity);
    
    static CGSpriteBatchNode* create(const std::string& fileImage)
    {
        return CGSpriteBatchNode::create(fileImage, kDefaultSpriteBatchCapacity);
    }

    bool initWithImage(CAImage *image, unsigned int capacity);

    bool initWithFile(const std::string& fileImage, unsigned int capacity);
    
    bool init() override;

    void increaseAtlasCapacity();

    void removeChildAtIndex(unsigned int index);

    void appendChild(CGSprite* sprite);
    void removeSpriteFromAtlas(CGSprite *sprite);

    ssize_t rebuildIndexInOrder(CGSprite *parent, ssize_t index);
    ssize_t highestAtlasIndexInChild(CGSprite *sprite);
    ssize_t lowestAtlasIndexInChild(CGSprite *sprite);
    ssize_t atlasIndexForChild(CGSprite *sprite, int z);

    void reorderBatch(bool reorder);
    
    virtual CAImage* getImage(void) override;
    
    virtual void setImage(CAImage *image) override;
    
    virtual void setBlendFunc(BlendFunc blendFunc);

    virtual BlendFunc getBlendFunc(void);

    virtual void insertChild(CGNode* child, int z) override;

    virtual void addChild(CGNode* child) override;
    
    virtual void removeChild(CGNode* child) override;

    virtual void removeAllChildren() override;
    
    virtual void sortAllChildren() override;
    
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

    virtual void visit(Renderer *renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;
    
protected:

    void insertQuadFromSprite(CGSprite *sprite, ssize_t index);

    void updateQuadFromSprite(CGSprite *sprite, ssize_t index);

    CGSpriteBatchNode * addSpriteWithoutQuad(CGSprite*child, ssize_t z, int aTag);

    void updateAtlasIndex(CGSprite* sprite, ssize_t* curIndex);
    
    void swap(ssize_t oldIndex, ssize_t newIndex);
    
    virtual void updateBlendFunc() override;

protected:
    
    CAImageAtlas *m_pobImageAtlas;
    
    CAVector<CGSprite*> m_obDescendants;
    
    BatchCommand m_obBatchCommand;
};

// end of sprite_nodes group
/// @}

NS_CC_END

#endif // __CGSpriteBatchNode_H__
