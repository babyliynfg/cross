//
//  CAScanQRcode.cpp
//  CrossApp
//
//  Created by mac on 2021/3/12.
//  Copyright © 2021 CrossApp. All rights reserved.
//

#ifndef CAScanQRcodeView_h
#define CAScanQRcodeView_h
#import <UIKit/UIKit.h>
#import "platform/ios/zbar/ZBarSDK.h"
#include <string>
#include <functional>
@interface CAScanQRcodeView : UIView <ZBarReaderViewDelegate>
{
    CGRect rect;
    UIView *_QrCodeline;
    NSTimer *_timer;
    
    //设置扫描画面
    UIView *_scanView;
    ZBarReaderView *_readerView;
    
    std::function<void(const std::string&)> _block;
}

- (id)init:(const std::function<void(const std::string&)>&) block;

@end

#endif /* CAScanQRcodeView_h */
