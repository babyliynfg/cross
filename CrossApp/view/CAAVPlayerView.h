

#ifndef __CAAVPlayerView_H__
#define __CAAVPlayerView_H__

#include "CAView.h"
NS_CC_BEGIN

class CC_DLL CAAVPlayerViewImpl;
class CC_DLL CAAVPlayerView : public CAView
{

public:

    CAAVPlayerView();
    
    virtual ~CAAVPlayerView();
    
    static CAAVPlayerView *create(void);
    
    static CAAVPlayerView* createWithFrame(const DRect& rect);
    
    static CAAVPlayerView* createWithCenter(const DRect& rect);
    
    static CAAVPlayerView* createWithLayout(const DLayout& layout);
    
    bool init() override;
    
    void setUrl(const std::string& url);
    
    void setFilePath(const std::string& filePath);
    
    void play();
    
    void pause();
  
    float getDuration();
    
    float getCurrentTime();
    
    CC_LISTENING_FUNCTION(void(float current, float duratuon), PeriodicTime);
    
    CC_LISTENING_FUNCTION(void(float current, float duratuon), LoadedTime);
    
protected:

    virtual void setImage(CAImage* image) override;
    
    virtual void updateImageRect() override;
    
private:
    
    float m_fX;
    
    float m_fY;
    
    float m_fWidth;
    
    float m_fHeight;
    
    CAAVPlayerViewImpl* m_pImpl;
    
    friend class CAAVPlayerViewImpl;
};

NS_CC_END

#endif // __CAAVPlayerView_H__
