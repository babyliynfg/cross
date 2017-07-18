

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
    
    void setUrl(const std::string& uri);// 网络url地址
    
    void setFilePath(const std::string& uri);// 本地路径
    
    void play(); // 播放
    
    void pause(); // 暂停
    
    void stop(); // 停止
  
    float getDuration();
    
    float getCurrentTime();
    
    void setCurrentTime(float current); // 跳转到指定的时间
    
    CC_LISTENING_FUNCTION(void(float current, float duratuon), PeriodicTime); // 监听播放进度
    
    CC_LISTENING_FUNCTION(void(float current, float duratuon), LoadedTime); // 监听缓冲进度
    
    CC_LISTENING_FUNCTION(void(), DidPlayToEndTime); // 监听播放完毕
    
    CC_LISTENING_FUNCTION(void(), TimeJumped); // 监听快进或者慢进或者跳过某段播放
    
    
    
protected:

    void setImage(CAImage* image) override;
    
    void updateImageRect() override;
    
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
