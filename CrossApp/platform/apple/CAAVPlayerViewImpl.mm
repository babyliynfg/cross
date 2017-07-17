

#include "../CAAVPlayerViewImpl.h"
#include "view/CAAVPlayerView.h"
#include "images/CAImage.h"
#include "basics/CAApplication.h"
#include "basics/CAScheduler.h"
#import "EAGLView.h"
#import <QuartzCore/QuartzCore.h>
#import <AVFoundation/AVFoundation.h>
#import <AVKit/AVKit.h>

#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
#import <Cocoa/Cocoa.h>
#else
#import <UIKit/UIKit.h>
#endif



#define NATIVE_IMPL (NativeAVPlayer*)m_pNativeImpl

const char* ANIMATION_ID = "__AVPlayerLayer_play__";

static AVPlayerLayer* s_pAVPlayerLayer = nil;

static void playerLayer_play(AVPlayer* player, const std::function<void()>& callback)
{
    if (s_pAVPlayerLayer)
    {
        [s_pAVPlayerLayer.player pause];
        CrossApp::CAScheduler::getScheduler()->unschedule(ANIMATION_ID, CrossApp::CAApplication::getApplication());
    }
    
    const CGSize& size = s_pAVPlayerLayer.player.currentItem.presentationSize;
    
    if (s_pAVPlayerLayer == nil)
    {
        s_pAVPlayerLayer = [AVPlayerLayer playerLayerWithPlayer:player];
        [s_pAVPlayerLayer setVideoGravity:AVLayerVideoGravityResizeAspect];
        [s_pAVPlayerLayer setHidden:YES];
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        [s_pAVPlayerLayer setBackgroundColor:[NSColor blackColor].CGColor];
        NSWindow* window = [[NSApplication sharedApplication] mainWindow];
        if (window.contentView.layer == nil)
        {
            window.contentView.layer = [CALayer layer];
        }
        
        [window.contentView.layer addSublayer:s_pAVPlayerLayer];
#else
        [s_pAVPlayerLayer setBackgroundColor:[UIColor blackColor].CGColor];
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.layer addSublayer:s_pAVPlayerLayer];
#endif
        
        
    }
    else
    {
        [s_pAVPlayerLayer setPlayer:player];
    }
    
    [s_pAVPlayerLayer setPosition:CGPointMake(size.width/2, size.height/2)];
    [s_pAVPlayerLayer setBounds:CGRectMake(0, 0, size.width, size.height)];
    
    [player play];
    
    CrossApp::CAScheduler::getScheduler()->schedule([=](float dt)
    {
        callback();
    }, ANIMATION_ID, CrossApp::CAApplication::getApplication(), 0);
}

static void playerLayer_pause(AVPlayer* player)
{
    if (s_pAVPlayerLayer && player && s_pAVPlayerLayer.player == player)
    {
        [s_pAVPlayerLayer.player pause];
        CrossApp::CAScheduler::getScheduler()->unschedule(ANIMATION_ID, CrossApp::CAApplication::getApplication());
    }
}

static CrossApp::CAImage* get_first_frame_image_with_filePath(NSURL* url)
{
    CrossApp::CAImage* image = nullptr;
    
    do
    {
        AVURLAsset *asset = [[[AVURLAsset alloc] initWithURL:url options:nil] autorelease];
        AVAssetImageGenerator *assetGen = [[[AVAssetImageGenerator alloc] initWithAsset:asset] autorelease];
        
        assetGen.appliesPreferredTrackTransform = YES;
        CMTime time = CMTimeMakeWithSeconds(0.0, 600);
        NSError *error = nil;
        CMTime actualTime;
        CGImageRef videoImage = [assetGen copyCGImageAtTime:time actualTime:&actualTime error:&error];
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        NSSize size = NSMakeSize(CGImageGetWidth(videoImage), CGImageGetHeight(videoImage));
        NSImage* nsImage = [[NSImage alloc] initWithCGImage:videoImage size:size];
        NSData* nsData = [nsImage TIFFRepresentationUsingCompression:NSTIFFCompressionNone factor:1];
#else
        UIImage* uiImage = [UIImage imageWithCGImage:videoImage];
        NSData *nsData = UIImagePNGRepresentation(uiImage);
#endif
        
        ssize_t length = [nsData length];
        
        unsigned char* data = (unsigned char*)malloc(length);
        [nsData getBytes:data length:length];
        
        CrossApp::CAData* cross_data = new CrossApp::CAData();
        cross_data->fastSet(data, length);
        
        image = CrossApp::CAImage::createWithImageDataNoCache(cross_data);
        
        cross_data->release();
        CGImageRelease(videoImage);
        
    } while (0);
    
    return image;
}

@interface NativeAVPlayer : NSObject <AVPlayerItemOutputPullDelegate>
{
    AVPlayerItemVideoOutput* _videoOutPut;
    std::function<void(CrossApp::CAImage*)> _function;
    
    AVPlayer* _player;
    
    id observer;
}
@property (nonatomic, assign, setter=onPeriodicTime:) std::function<void(float, float)> periodicTime;
@property (nonatomic, assign, setter=onLoadedTime:) std::function<void(float, float)> loadedTime;

- (id)initWithCallback:(std::function<void(CrossApp::CAImage*)>)function;
- (void)setUrl:(std::string)url;
- (void)setFilePath:(std::string)filePath;
- (void)play;
- (void)pause;
- (float)getDuration;
- (float)getCurrentTime;
- (void)setCurrentTime:(float)current;

- (void)outputMediaData;
- (void)dealloc;
@end

@implementation NativeAVPlayer

- (id)initWithCallback:(std::function<void(CrossApp::CAImage*)>)function
{
    if (![super init])
    {
        return nil;
    }
    _function = function;
    
    //初始化输出流
    _videoOutPut = [[AVPlayerItemVideoOutput alloc] init];
    return self;
}

- (void)setUrl:(std::string)url
{
    [self setup:[NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]] load:NO];
}

- (void)setFilePath:(std::string)filePath
{
    std::string resource;
    std::string type;
    size_t pos = filePath.find_last_of(".");
    resource = filePath.substr(0, pos);
    type = filePath.substr(pos + 1, filePath.length() - pos - 1);
    
    NSString *path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:resource.c_str()]
                                                   ofType:[NSString stringWithUTF8String:type.c_str()]];
    
    [self setup:[NSURL fileURLWithPath:path] load:YES];
}

- (void)setup:(NSURL*)videoURL load:(BOOL)load
{
    if (_player)
    {
        [self pause];
        [_player.currentItem removeOutput:_videoOutPut];
        [_player.currentItem removeObserver:self forKeyPath:@"status"];
        [_player.currentItem removeObserver:self forKeyPath:@"loadedTimeRanges"];
        [_player.currentItem removeObserver:self forKeyPath:@"playbackBufferEmpty"];
        [_player.currentItem removeObserver:self forKeyPath:@"playbackLikelyToKeepUp"];
        [_player removeObserver:self forKeyPath:@"rate"];
    }
    
    //初始化播放地址
    AVPlayerItem* item = [AVPlayerItem playerItemWithURL:videoURL];

    if (_player == nil)
    {
        _player = [[AVPlayer playerWithPlayerItem:item] retain];
    }
    else
    {
        [_player replaceCurrentItemWithPlayerItem:item];
    }
    
    //添加输出流
    [_player.currentItem addOutput:_videoOutPut];
    
    //需要时时显示播放的进度
    //根据播放的帧数、速率，进行时间的异步(在子线程中完成)获取
    observer = [_player addPeriodicTimeObserverForInterval:CMTimeMake(1.0, 1.0) queue:dispatch_get_global_queue(0, 0) usingBlock:^(CMTime time) {
        //获取时间
        //获取当前播放时间(根据帧数和播放速率，视频资源的总长度得到的CMTime)
        float current = CMTimeGetSeconds(_player.currentItem.currentTime);
        //        //总时间
        float duratuon = CMTimeGetSeconds(_player.currentItem.duration);
        //        //CMTimeGetSeconds 将描述视频时间的结构体转化为float（秒）
        
        //        //回到主线程刷新UI
        dispatch_async(dispatch_get_main_queue(), ^{
            //要考虑到代码的健壮性
            /*1、在向对象发送消息前，要判断对象是否为空
             *2、一些值(数组、控制中的属性值)是否越界的判断
             *3、是否对各种异常情况进行了处理(照片、定位 用户允许、不允许)
             *4、数据存储，对nil的判断或处理
             *5、对硬件功能支持情况的判断等
             */
            if (self.periodicTime)
            {
                self.periodicTime(current, duratuon);
            }
            
            if (current >= duratuon)
            {
                [self pause];
            }
        });
        
    }];
    
    [_player.currentItem.asset loadValuesAsynchronouslyForKeys:@[@"duration"] completionHandler:^{
        NSError *error = nil;
        AVKeyValueStatus tracksStatus = [_player.currentItem.asset statusOfValueForKey:@"duration" error:&error];
        switch (tracksStatus) {
            case AVKeyValueStatusLoaded:
            {
                dispatch_async(dispatch_get_main_queue(), ^{
                    if (!CMTIME_IS_INDEFINITE(_player.currentItem.asset.duration)) {
                        CGFloat second = _player.currentItem.asset.duration.value / _player.currentItem.asset.duration.timescale;
                        NSLog(@"loadValuesAsynchronouslyForKeys %f", second);
                    }
                });
            }
                break;
            case AVKeyValueStatusFailed:
            {
                NSLog(@"AVKeyValueStatusFailed失败,请检查网络,或查看plist中是否添加App Transport Security Settings");
            }
                break;
            case AVKeyValueStatusCancelled:
            {
                NSLog(@"AVKeyValueStatusCancelled取消");
            }
                break;
            case AVKeyValueStatusUnknown:
            {
                NSLog(@"AVKeyValueStatusUnknown未知");
            }
                break;
            case AVKeyValueStatusLoading:
            {
                NSLog(@"AVKeyValueStatusLoading正在加载");
            }
                break;
        }
    }];

    
    //监听状态属性
    [_player.currentItem addObserver:self forKeyPath:@"status" options:NSKeyValueObservingOptionNew context:nil];
    //监听网络加载情况属性
    [_player.currentItem addObserver:self forKeyPath:@"loadedTimeRanges" options:NSKeyValueObservingOptionNew context:nil];
    //监听播放的区域缓存是否为空
    [_player.currentItem addObserver:self forKeyPath:@"playbackBufferEmpty" options:NSKeyValueObservingOptionNew context:nil];
    //缓存可以播放的时候调用
    [_player.currentItem addObserver:self forKeyPath:@"playbackLikelyToKeepUp" options:NSKeyValueObservingOptionNew context:nil];
    //监听暂停或者播放中
    [_player addObserver:self forKeyPath:@"rate" options:NSKeyValueObservingOptionNew context:nil];
    
    /**************获取第一帧图片******************/
    if (load && _function)
    {
        CrossApp::CAImage* image = get_first_frame_image_with_filePath(videoURL);
        _function(image);
    }
}


- (void)play
{
    playerLayer_play(_player, [=]
    {
        [self outputMediaData];
    });
}

- (void)pause;
{
    playerLayer_pause(_player);
}

- (float)getDuration
{
    return CMTimeGetSeconds(_player.currentItem.duration);
}

- (float)getCurrentTime
{
    return CMTimeGetSeconds(_player.currentItem.currentTime);
}

- (void)setCurrentTime:(float)current
{
    CMTime dur = _player.currentItem.duration;
    //CMTimeMultiplyByFloat64 将总时长，当前进度，转化成为CMTime
    //seekToTime 跳转到指定的时间
    [_player seekToTime:CMTimeMultiplyByFloat64(dur, current)];
}

- (void)outputMediaData;
{
    CMTime itemTime = _player.currentItem.currentTime;
    CVPixelBufferRef pixelBuffer = [_videoOutPut copyPixelBufferForItemTime:itemTime itemTimeForDisplay:nil];
    
    do
    {
        CC_BREAK_IF(pixelBuffer == nil);
        
        CIImage *ciImage = [CIImage imageWithCVPixelBuffer:pixelBuffer];
        CVPixelBufferRelease(pixelBuffer);
        
        CGFloat width = CVPixelBufferGetWidth(pixelBuffer);
        CGFloat height = CVPixelBufferGetHeight(pixelBuffer);
        
        CIContext *temporaryContext = [CIContext contextWithOptions:nil];
        CGImageRef videoImage = [temporaryContext createCGImage:ciImage fromRect:CGRectMake(0, 0, width, height)];
        
        
        CGDataProviderRef provider = CGImageGetDataProvider(videoImage);
        CFDataRef ref = CGDataProviderCopyData(provider);
        CGImageRelease(videoImage);
        
        ssize_t length = (ssize_t)CFDataGetLength(ref);
        unsigned char* data = (unsigned char*)CFDataGetBytePtr(ref);
        
        
        CrossApp::CAData* cross_data = new CrossApp::CAData();
        cross_data->copy(data, length);
        CFRelease(ref);
        
        CrossApp::CAImage* image = CrossApp::CAImage::createWithRawDataNoCache(cross_data, CrossApp::CAImage::PixelFormat::RGBA8888, (unsigned int)width, (unsigned int)height);
        
        if (_function)
        {
            _function(image);
        }
        cross_data->release();

    } while (0);
    
}

-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context
{
    if ([keyPath isEqualToString:@"status"])
    {
        AVPlayerItemStatus itemStatus = (AVPlayerItemStatus)[[change objectForKey:NSKeyValueChangeNewKey] integerValue];
        
        switch (itemStatus) {
            case AVPlayerItemStatusUnknown:
            {
                NSLog(@"AVPlayerItemStatusUnknown");
            }
                break;
            case AVPlayerItemStatusReadyToPlay:
            {
                NSLog(@"AVPlayerItemStatusReadyToPlay");
            }
                break;
            case AVPlayerItemStatusFailed:
            {
                NSLog(@"AVPlayerItemStatusFailed");
            }
                break;
            default:
                break;
        }
    }
    else if ([keyPath isEqualToString:@"loadedTimeRanges"])
    {  //监听播放器的下载进度
        NSArray *loadedTimeRanges = [_player.currentItem loadedTimeRanges];
        CMTimeRange timeRange = [loadedTimeRanges.firstObject CMTimeRangeValue];// 获取缓冲区域
        float startSeconds = CMTimeGetSeconds(timeRange.start);
        float durationSeconds = CMTimeGetSeconds(timeRange.duration);
        float timeInterval = startSeconds + durationSeconds;// 计算缓冲总进度
        float totalDuration = CMTimeGetSeconds(_player.currentItem.duration);
        
        if (self.loadedTime)
        {
            self.loadedTime(timeInterval, totalDuration);
        }
    }
    else if ([keyPath isEqualToString:@"playbackBufferEmpty"])
    { //监听播放器在缓冲数据的状态
//        _status = SBPlayerStatusBuffering;
//        if (!self.activityIndeView.isAnimating) {
//            [self.activityIndeView startAnimating];
//        }
    }
    else if ([keyPath isEqualToString:@"playbackLikelyToKeepUp"])
    {
        NSLog(@"缓冲达到可播放");
    }
    else if ([keyPath isEqualToString:@"rate"])
    {//当rate==0时为暂停,rate==1时为播放,当rate等于负数时为回放
        
        NSInteger rate = [[change objectForKey:NSKeyValueChangeNewKey] integerValue];
        
        if (rate == 0)
        {
            NSLog(@"暂停");
        }
        else if (rate == 1)
        {
            NSLog(@"播放");
        }
        else if (rate < 0)
        {
            NSLog(@"回放");
        }
    }
    
}

- (void)dealloc
{
    [self pause];
    [_player removeTimeObserver:observer];
    [_player release];
    [_videoOutPut release];
    [super dealloc];
}

@end


NS_CC_BEGIN

CAImage* CAAVPlayerViewImpl::getFirstFrameImageWithFilePath(const std::string& filePath)
{
    if (filePath.length() == 0)
    {
        return nullptr;
    }
    
    std::string resource;
    std::string type;
    size_t pos = filePath.find_last_of(".");
    resource = filePath.substr(0, pos);
    type = filePath.substr(pos + 1, filePath.length() - pos - 1);
    
    NSString *path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:resource.c_str()]
                                                     ofType:[NSString stringWithUTF8String:type.c_str()]];
    
    NSURL* url = [NSURL fileURLWithPath:path];
    
    return get_first_frame_image_with_filePath(url);
}

CAAVPlayerViewImpl::CAAVPlayerViewImpl(CAAVPlayerView* playerView)
: m_pPlayerView(playerView)
{
    m_pNativeImpl = [[NativeAVPlayer alloc] initWithCallback:[&](CAImage* image)
    {
        m_pPlayerView->setImage(image);
    }];
    
    [NATIVE_IMPL onPeriodicTime:[&](float currTime, float duratuon)
    {
        if (m_pPlayerView->m_obPeriodicTime)
        {
            m_pPlayerView->m_obPeriodicTime(currTime, duratuon);
        }
    }];
    
    [NATIVE_IMPL onLoadedTime:[&](float currTime, float duratuon)
     {
         if (m_pPlayerView->m_obLoadedTime)
         {
             m_pPlayerView->m_obLoadedTime(currTime, duratuon);
         }
     }];
}

CAAVPlayerViewImpl::~CAAVPlayerViewImpl()
{
    [NATIVE_IMPL release];
}

void CAAVPlayerViewImpl::setUrl(const std::string& url)
{
    [NATIVE_IMPL setUrl:url];
}

void CAAVPlayerViewImpl::setFilePath(const std::string& filePath)
{
    [NATIVE_IMPL setFilePath:filePath];
}

void CAAVPlayerViewImpl::play()
{
    [NATIVE_IMPL play];
}

void CAAVPlayerViewImpl::pause()
{
    [NATIVE_IMPL pause];
}

float CAAVPlayerViewImpl::getDuration()
{
    return [NATIVE_IMPL getDuration];
}

float CAAVPlayerViewImpl::getCurrentTime()
{
    return [NATIVE_IMPL getCurrentTime];
}


NS_CC_END
