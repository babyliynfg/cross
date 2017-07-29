

#ifndef __CAAVPlayerView_H__
#define __CAAVPlayerView_H__

#include "CAView.h"

NS_CC_BEGIN


class CC_DLL CAAVPlayerImpl;
class CC_DLL CAAVPlayerView;

class CC_DLL CAAVPlayer : public CAObject
{

public:

    CAAVPlayer();
    
    virtual ~CAAVPlayer();
    
    static CAAVPlayer *createWithUrl(const std::string& uri);       // 网络url地址
    
    static CAAVPlayer *createWithFilePath(const std::string& uri);  // 本地路径
    
    bool initWithUrl(const std::string& uri);                       // 网络url地址
    
    bool initWithFilePath(const std::string& uri);                  // 本地路径
    
    void play();                                                    // 播放

    void pause();                                                   // 暂停
    
    void stop();                                                    // 停止
  
    float getDuration();                                            // 获取媒体总时间
    
    float getCurrentTime();                                         // 获取媒体当前时间
    
    void setCurrentTime(float current);                             // 跳转到指定的时间
    
    const DSize& getPresentationSize();                             // 获取媒体分辨率
    
public:
    
    CC_LISTENING_FUNCTION(void(float current, float duration), PeriodicTime);   // 监听播放进度
    
    CC_LISTENING_FUNCTION(void(float current, float duration), LoadedTime);     // 监听缓冲进度
    
    CC_LISTENING_FUNCTION(void(), DidPlayToEndTime);                            // 监听播放完毕
    
    CC_LISTENING_FUNCTION(void(), TimeJumped);                                  // 监听快进或者慢进或者跳过某段播放
    
    typedef std::string PlayBufferLoadingState;
    static const std::string PlaybackBufferEmpty;                               //缓冲为空，正在缓冲
    static const std::string PlaybackLikelyToKeepUp;                            //缓冲达到可播放
    CC_LISTENING_FUNCTION(void(const PlayBufferLoadingState&), PlayBufferLoadingState);    // 监听缓冲状态
    
    typedef std::string PlayState;
    static const std::string PlayStatePause;                                    //暂停
    static const std::string PlayStatePlaying;                                  //播放中
    static const std::string PlayStatePlayback;                                 //回放中
    CC_LISTENING_FUNCTION(void(const PlayState&), PlayState);                 // 监听播放状态

protected:
    
    void onImage(const std::function<void(CAImage*)>& function);
        
    CAAVPlayerImpl* m_pImpl;
    
    friend class CAAVPlayerImpl;
    
    friend class CAAVPlayerView;
};


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
    
    CAAVPlayer* getPlayer();
    
    void setPlayer(CAAVPlayer* player);
    
protected:
    
    void setImage(CAImage* image) override;
    
    void updateImageRect() override;
    
private:
    
    float m_fX;
    
    float m_fY;
    
    float m_fWidth;
    
    float m_fHeight;
    
    CAAVPlayer* m_pPlayer;
};


NS_CC_END

#endif // __CAAVPlayerView_H__
