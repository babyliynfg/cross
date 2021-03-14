//
//  CAScanQRcode.cpp
//  CrossApp
//
//  Created by mac on 2021/3/12.
//  Copyright © 2021 CrossApp. All rights reserved.
//

#import "CAScanQRcodeView.h"
#import <Foundation/Foundation.h>
#include "control/CABar.h"
#include "basics/CAApplication.h"
#include "dispatcher/CATouchDispatcher.h"
#include "platform/CADensityDpi.h"

#include "view/CAWindow.h"
#include "EAGLView.h"

#define SCANVIEW_EdgeTop 200.0
#define SCANVIEW_EdgeLeft 50.0

#define TINTCOLOR_ALPHA 0.2  //浅色透明度
#define DARKCOLOR_ALPHA 0.5  //深色透明度

static CAScanQRcodeView *_scanQRcodeView = nil;

@implementation CAScanQRcodeView

+ (id)show:(const std::function<void (const std::string &)> &)block
{
    if (_scanQRcodeView == nil)
    {
        CrossApp::CAApplication::getApplication()->pause();
        CrossApp::CAApplication::getApplication()->getTouchDispatcher()->setDispatchEventsFalse();
        
        EAGLView* eaglview = [EAGLView sharedEGLView];
        _scanQRcodeView = [[[CAScanQRcodeView alloc] initWithFrame:eaglview.bounds callback:block] autorelease];
        [eaglview addSubview:_scanQRcodeView];
    }
    
    return _scanQRcodeView;
}

- (id)initWithFrame:(CGRect) rect callback:(const std::function<void(const std::string&)>&) block
{
    self = [super initWithFrame:rect];
    if (self) {
        
        _block = block;

        _scanViewRect = self.bounds;
        //初始化扫描界面
        [self setScanView];
        
        _readerView = [[[ZBarReaderView alloc] init] autorelease];
        _readerView.frame = self.bounds;
        _readerView.tracksSymbols = NO;
        _readerView.readerDelegate = self;
        [_readerView addSubview:_scanView];
        //关闭闪光灯
        _readerView.torchMode = 0;
        
        [self addSubview:_readerView];
        
        //扫描区域
        [_readerView start];
        
        [self createTimer];
        
        int top = CrossApp::CABar::get_top_clearance(CrossApp::CAApplication::getApplication()->getRootWindow());
        float y = top / 2 + 20;
        
        UIButton *btn_closed = nil;
        btn_closed = [UIButton buttonWithType:UIButtonTypeCustom];
        [btn_closed setBackgroundImage:[UIImage imageNamed:@"source_material/btn_left_white.png"] forState:UIControlStateNormal];
        [btn_closed setFrame:CGRectMake(30, y, 24, 24)];
        [self addSubview: btn_closed];
        [btn_closed addTarget:self action:@selector(closed) forControlEvents:UIControlEventTouchUpInside];
                
        
        [self setCenter:CGPointMake(self.bounds.size.width * 0.5, self.bounds.size.height * 1.5)];
        [UIView animateWithDuration:0.3 delay:0 options:UIViewAnimationOptionCurveEaseOut animations:^{
            [self setCenter:CGPointMake(self.bounds.size.width * 0.5, self.bounds.size.height * 0.5)];
        } completion:^(BOOL finished){}];
    }
    return self;
}

- (void) closed
{
    [self setCenter:CGPointMake(self.bounds.size.width * 0.5, self.bounds.size.height * 0.5)];
    [UIView animateWithDuration:0.3 delay:0 options:UIViewAnimationOptionCurveEaseOut animations:^{
        [self setCenter:CGPointMake(self.bounds.size.width * 0.5, self.bounds.size.height * 1.5)];
    } completion:^(BOOL finished){
        if (finished == YES)
        {
            [self removeFromSuperview];
            _scanQRcodeView = nil;
            CrossApp::CAApplication::getApplication()->getTouchDispatcher()->setDispatchEventsTrue();
            CrossApp::CAApplication::getApplication()->resume();
        }
    }];
    
}

- (void)runAnimationFrom:(CGPoint) from to:(CGPoint) to
{
    
    
    //创建动画对象
    CABasicAnimation *basicAni = [CABasicAnimation animation];

    //设置动画属性
    basicAni.keyPath = @"position";

    //设置动画的起始位置。也就是动画从哪里到哪里
    basicAni.fromValue = [NSValue valueWithCGPoint:from];

    //动画结束后，layer所在的位置
    basicAni.toValue = [NSValue valueWithCGPoint:to];

    //动画持续时间
    basicAni.duration = 0.25;

    //动画填充模式
    basicAni.fillMode = kCAFillModeForwards;

    //动画完成不删除
    basicAni.removedOnCompletion = NO;

    //xcode8.0之后需要遵守代理协议
    basicAni.delegate = self;

    //把动画添加到要作用的Layer上面
    [self.layer addAnimation:basicAni forKey:nil];
    
}

- (UIImage *)createImageWithColor:(UIColor *)color
{
    //设置长宽
    CGRect rect = CGRectMake(0.0f, 0.0f, 44.0f, 44.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *resultImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return resultImage;
}

#pragma mark -- ZBarReaderViewDelegate
-(void)readerView:(ZBarReaderView *)readerView didReadSymbols:(ZBarSymbolSet *)symbols fromImage:(UIImage *)image
{
    const zbar_symbol_t *symbol = zbar_symbol_set_first_symbol(symbols.zbarSymbolSet);
    NSString *symbolStr = [NSString stringWithUTF8String: zbar_symbol_get_data(symbol)];
    
    if (_block) _block([symbolStr UTF8String]);
    
    [self closed];
}

//二维码的扫描区域
- (void)setScanView
{
    _scanView = [[UIView alloc] initWithFrame:_scanViewRect];
    _scanView.backgroundColor = [UIColor clearColor];
    
    //    //最上部view
    UIView* upView = [[UIView alloc] initWithFrame:CGRectMake(0,0, _scanViewRect.size.width, SCANVIEW_EdgeTop)];
    upView.alpha =TINTCOLOR_ALPHA;
    upView.backgroundColor = [UIColor blackColor];
    [_scanView addSubview:upView];
    
    //左侧的view
    UIView *leftView = [[UIView alloc] initWithFrame:CGRectMake(0, SCANVIEW_EdgeTop, SCANVIEW_EdgeLeft, _scanViewRect.size.width - 2 * SCANVIEW_EdgeLeft)];
    leftView.alpha =TINTCOLOR_ALPHA;
    leftView.backgroundColor = [UIColor blackColor];
    [_scanView addSubview:leftView];
    
    /******************中间扫描区域****************************/
    UIView *scanCropView = [[UIView alloc] initWithFrame:CGRectMake(SCANVIEW_EdgeLeft, SCANVIEW_EdgeTop, _scanViewRect.size.width - 2 * SCANVIEW_EdgeLeft, _scanViewRect.size.width - 2 * SCANVIEW_EdgeLeft)];
    
    scanCropView.layer.borderColor=[UIColor greenColor].CGColor;
    scanCropView.layer.borderWidth=2.0;
    
    scanCropView.backgroundColor=[UIColor clearColor];
    [_scanView addSubview:scanCropView];
    
    
    //右侧的view
    UIView *rightView = [[UIView alloc] initWithFrame:CGRectMake(_scanViewRect.size.width - SCANVIEW_EdgeLeft, SCANVIEW_EdgeTop, SCANVIEW_EdgeLeft, _scanViewRect.size.width - 2 * SCANVIEW_EdgeLeft)];
    rightView.alpha =TINTCOLOR_ALPHA;
    rightView.backgroundColor = [UIColor blackColor];
    [_scanView addSubview:rightView];
    
    
    //底部view
    UIView *downView = [[UIView alloc] initWithFrame:CGRectMake(0, _scanViewRect.size.width - 2 * SCANVIEW_EdgeLeft+SCANVIEW_EdgeTop, _scanViewRect.size.width, _scanViewRect.size.height - (_scanViewRect.size.width-2*SCANVIEW_EdgeLeft+SCANVIEW_EdgeTop))];
    //downView.alpha = TINTCOLOR_ALPHA;
    downView.backgroundColor = [[UIColor blackColor] colorWithAlphaComponent:TINTCOLOR_ALPHA];
    [_scanView addSubview:downView];
    
    //用于说明的label
    UILabel *labIntroudction = [[UILabel alloc] init];
    labIntroudction.backgroundColor = [UIColor clearColor];
    labIntroudction.frame = CGRectMake(0,5, _scanViewRect.size.width,20);
    labIntroudction.numberOfLines = 1;
    labIntroudction.font = [UIFont systemFontOfSize:15.0];
    labIntroudction.textAlignment = NSTextAlignmentCenter;
    labIntroudction.textColor = [UIColor whiteColor];
    labIntroudction.text = @"将二维码对准方框，即可自动扫描";
    [downView addSubview:labIntroudction];
    
    //画中间的基准线
    _QrCodeline = [[UIView alloc] initWithFrame:CGRectMake(SCANVIEW_EdgeLeft, SCANVIEW_EdgeTop, _scanViewRect.size.width - 2 * SCANVIEW_EdgeLeft, 2)];
    _QrCodeline.backgroundColor = [UIColor greenColor];
    [_scanView addSubview:_QrCodeline];
}

- (void)viewWillDisappear
{
    if (_readerView.torchMode == 1) {
        _readerView.torchMode = 0;
    }
    [self stopTimer];
    
    [_readerView stop];
    
}

//二维码的横线移动
- (void)moveUpAndDownLine
{
    CGFloat Y=_QrCodeline.frame.origin.y;
    //CGRectMake(SCANVIEW_EdgeLeft, SCANVIEW_EdgeTop, VIEW_WIDTH-2*SCANVIEW_EdgeLeft, 1)]
    if (_scanViewRect.size.width-2*SCANVIEW_EdgeLeft+SCANVIEW_EdgeTop == Y)
    {
        
        [UIView beginAnimations:@"moveUpAndDownLine" context:nil];
        [UIView setAnimationDuration:1];
        _QrCodeline.frame=CGRectMake(SCANVIEW_EdgeLeft, SCANVIEW_EdgeTop, _scanViewRect.size.width-2*SCANVIEW_EdgeLeft,1);
        [UIView commitAnimations];
    }
    else if(SCANVIEW_EdgeTop == Y)
    {
        [UIView beginAnimations:@"moveUpAndDownLine" context:nil];
        [UIView setAnimationDuration:1];
        _QrCodeline.frame=CGRectMake(SCANVIEW_EdgeLeft, _scanViewRect.size.width-2*SCANVIEW_EdgeLeft+SCANVIEW_EdgeTop, _scanViewRect.size.width-2*SCANVIEW_EdgeLeft,1);
        [UIView commitAnimations];
    }
    
}

- (void)createTimer
{
    //创建一个时间计数
    _timer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(moveUpAndDownLine) userInfo:nil repeats:YES];
}

- (void)stopTimer
{
    if ([_timer isValid] == YES) {
        [_timer invalidate];
        _timer =nil;
    }
}

- (void)dealloc
{
    [super dealloc];
}

@end


