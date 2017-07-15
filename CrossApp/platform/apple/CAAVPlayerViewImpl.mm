

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
        s_pAVPlayerLayer.videoGravity = AVLayerVideoGravityResizeAspect;
        s_pAVPlayerLayer.hidden = YES;
        
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        NSWindow* window = [[NSApplication sharedApplication] mainWindow];
        if (window.contentView.layer == nil)
        {
            window.contentView.layer = [CALayer layer];
        }
        
        [window.contentView.layer addSublayer:s_pAVPlayerLayer];
#else
        UIWindow* window = [[UIApplication sharedApplication] keyWindow];
        [window.layer addSublayer:s_pAVPlayerLayer];
#endif
        
        
    }
    else
    {
        [s_pAVPlayerLayer setPlayer:player];
    }
    
    s_pAVPlayerLayer.position = CGPointMake(size.width/2, size.height/2);
    s_pAVPlayerLayer.bounds = CGRectMake(0, 0, size.width, size.height);
    
    [player play];
    
    NSLog(@"%lld", player.currentItem.duration.value);
    
    
    
    
    
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

@interface NativeAVPlayer : NSObject <AVPlayerItemOutputPullDelegate>
{
    AVPlayerItemVideoOutput* _videoOutPut;
    std::function<void(CrossApp::CAImage*)> _function;
    
    AVPlayer* _player;
    
    id observer;
}
@property (nonatomic, assign, setter=onPeriodicTime:) std::function<void(float)> periodicTime;

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
    if (_player)
    {
        [self pause];
        [_player release];
    }
    
    NSURL* videoURL = [NSURL URLWithString:[NSString stringWithUTF8String:url.c_str()]];
    
    //初始化播放地址
    AVPlayerItem* item = [AVPlayerItem playerItemWithURL:videoURL];
    //添加输出流
    [item addOutput:_videoOutPut];
    
    _player = [[AVPlayer playerWithPlayerItem:item] retain];
}

- (void)setFilePath:(std::string)filePath
{
    if (_player)
    {
        [self pause];
        [_player release];
    }
    
    std::string resource;
    std::string type;
    size_t pos = filePath.find_last_of(".");
    resource = filePath.substr(0, pos);
    type = filePath.substr(pos + 1, filePath.length() - pos - 1);
    
    
    NSString *path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:resource.c_str()]
                                                   ofType:[NSString stringWithUTF8String:type.c_str()]];
    NSURL* videoURL = [NSURL fileURLWithPath:path];
    
    //初始化播放地址
    AVPlayerItem* item = [AVPlayerItem playerItemWithURL:videoURL];
    //添加输出流
    [item addOutput:_videoOutPut];
    
    _player = [[AVPlayer playerWithPlayerItem:item] retain];

/**************获取第一帧图片******************/
    
    AVURLAsset *asset = [[AVURLAsset alloc] initWithURL:videoURL options:nil];
    AVAssetImageGenerator *assetGen = [[AVAssetImageGenerator alloc] initWithAsset:asset];
    
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
    
    CrossApp::CAImage* image = CrossApp::CAImage::createWithImageDataNoCache(cross_data);
    
    if (_function)
    {
        _function(image);
    }
    cross_data->release();
    CGImageRelease(videoImage);
/********************************/
}

- (void)play
{
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
                self.periodicTime(current);
            }
            
            if (current >= duratuon)
            {
                [self pause];
            }
        });
        
    }];
    
    playerLayer_play(_player, [=]
    {
        [self outputMediaData];
    });
}

- (void)pause;
{
    [_player removeTimeObserver:observer];
    observer = nil;
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

- (void)dealloc
{
    [self pause];
    [_player release];
    [_videoOutPut release];
    [super dealloc];
}

@end


NS_CC_BEGIN
CAAVPlayerViewImpl::CAAVPlayerViewImpl(CAAVPlayerView* playerView)
: m_pPlayerView(playerView)
{
    m_pNativeImpl = [[NativeAVPlayer alloc] initWithCallback:[&](CAImage* image)
    {
        m_pPlayerView->setImage(image);
    }];
    
    [NATIVE_IMPL onPeriodicTime:[&](float currTime)
    {
        if (m_pPlayerView->m_obPeriodicTime)
        {
            m_pPlayerView->m_obPeriodicTime(currTime);
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
