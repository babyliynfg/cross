//
//  CACamera.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//

#include "CAImagePickerController.h"
#include "basics/CAApplication.h"
#include "CATouchDispatcher.h"
#import <UIKit/UIKit.h>
#import <EAGLView.h>

@interface __picker_callback: NSObject <UINavigationControllerDelegate, UIImagePickerControllerDelegate>
{
    CrossApp::CAImagePickerController* _target;
}

- (id)init:(CrossApp::CAImagePickerController*)target;

- (void) image: (UIImage *) image didFinishSavingWithError: (NSError *)error contextInfo: (void *) contextInfo;

@property (nonatomic) std::function<void(CrossApp::CAImage*)> callback;
@property (nonatomic) std::function<void(bool)> finishCallback;
@end

@implementation __picker_callback


- (id)init:(CrossApp::CAImagePickerController*)target
{
    if ([super init] == nil)
    {
        return nil;
    }
    _target = target;
    
    return self;
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info
{
    NSString *imageType;
    if (picker.allowsEditing)
    {
        imageType = [NSString stringWithFormat:@"UIImagePickerControllerEditedImage"];
    }
    else
    {
        imageType = [NSString stringWithFormat:@"UIImagePickerControllerOriginalImage"];
    }
    UIImage *image = [info objectForKey:imageType];
    
    NSData *data = UIImageJPEGRepresentation([self fixOrientation:image], 1.0f);
    void* _data = malloc([data length]);
    [data getBytes:_data];
    
    CrossApp::CAImage *__image = new CrossApp::CAImage();
    __image->initWithImageData((unsigned char*)_data, data.length);
    if (self.callback)
    {
        self.callback(__image);
    }
    CC_SAFE_RELEASE(__image);
    free(_data);
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    if (self.callback)
    {
        self.callback(nullptr);
    }
}


- (void) image: (UIImage *) image didFinishSavingWithError: (NSError *)error contextInfo: (void *) contextInfo
{
    bool ok = true;
    
    self.finishCallback(ok);
}


- (UIImage *)fixOrientation:(UIImage *)srcImg
{
    if (srcImg.imageOrientation == UIImageOrientationUp) return srcImg;
    CGAffineTransform transform = CGAffineTransformIdentity;
    switch (srcImg.imageOrientation) {
        case UIImageOrientationDown:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, srcImg.size.width, srcImg.size.height);
            transform = CGAffineTransformRotate(transform, M_PI);
            break;
            
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
            transform = CGAffineTransformTranslate(transform, srcImg.size.width, 0);
            transform = CGAffineTransformRotate(transform, M_PI_2);
            break;
            
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, 0, srcImg.size.height);
            transform = CGAffineTransformRotate(transform, -M_PI_2);
            break;
        case UIImageOrientationUp:
        case UIImageOrientationUpMirrored:
            break;
    }
    
    switch (srcImg.imageOrientation) {
        case UIImageOrientationUpMirrored:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, srcImg.size.width, 0);
            transform = CGAffineTransformScale(transform, -1, 1);
            break;
            
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, srcImg.size.height, 0);
            transform = CGAffineTransformScale(transform, -1, 1);
            break;
        case UIImageOrientationUp:
        case UIImageOrientationDown:
        case UIImageOrientationLeft:
        case UIImageOrientationRight:
            break;
    }
    
    CGContextRef ctx = CGBitmapContextCreate(NULL, srcImg.size.width, srcImg.size.height,
                                             CGImageGetBitsPerComponent(srcImg.CGImage), 0,
                                             CGImageGetColorSpace(srcImg.CGImage),
                                             CGImageGetBitmapInfo(srcImg.CGImage));
    CGContextConcatCTM(ctx, transform);
    switch (srcImg.imageOrientation) {
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            CGContextDrawImage(ctx, CGRectMake(0,0,srcImg.size.height,srcImg.size.width), srcImg.CGImage);
            break;
            
        default:
            CGContextDrawImage(ctx, CGRectMake(0,0,srcImg.size.width,srcImg.size.height), srcImg.CGImage);
            break;
    }
    
    CGImageRef cgimg = CGBitmapContextCreateImage(ctx);
    UIImage *img = [UIImage imageWithCGImage:cgimg];
    CGContextRelease(ctx);
    CGImageRelease(cgimg);
    return img;
}

@end


NS_CC_BEGIN

UIImagePickerController* convert(void* var)
{
    return (UIImagePickerController*)var;
}


CAImagePickerController::CAImagePickerController(SourceType type)
: m_eSourceType(type)
, m_pSavedImage(nullptr)
{
    m_pOriginal = [[UIImagePickerController alloc] init];
    __picker_callback* c = [[__picker_callback alloc] init:this];
    [convert(m_pOriginal) setDelegate:c];
    
    switch (m_eSourceType)
    {
        case SourceType::PhotoLibrary:
        {
            convert(m_pOriginal).sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        }
            break;
        case SourceType::CameraDeviceRear:
        {
            convert(m_pOriginal).sourceType = UIImagePickerControllerSourceTypeCamera;
            convert(m_pOriginal).cameraDevice = UIImagePickerControllerCameraDeviceRear;
            convert(m_pOriginal).cameraCaptureMode = UIImagePickerControllerCameraCaptureModeVideo;
        }
            break;
        case SourceType::CameraDeviceFront:
        {
            convert(m_pOriginal).sourceType = UIImagePickerControllerSourceTypeCamera;
            convert(m_pOriginal).cameraDevice = UIImagePickerControllerCameraDeviceFront;
        }
            break;
        case SourceType::SavedPhotosAlbum:
        {
            convert(m_pOriginal).sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
        }
            break;
        default:
            break;
    }
}

CAImagePickerController::~CAImagePickerController()
{
    [convert(m_pOriginal).delegate release];
    [convert(m_pOriginal) release];
    
    CC_SAFE_RELEASE(m_pSavedImage);
}

CAImagePickerController* CAImagePickerController::create(SourceType type)
{
    CAImagePickerController* var = new CAImagePickerController(type);
    if (var && var->init())
    {
        var->autorelease();
        return var;
    }
    CC_SAFE_DELETE(var);
    return nullptr;
}

bool CAImagePickerController::init()
{
    return true;
}

void CAImagePickerController::open(const std::function<void(CrossApp::CAImage*)>& callback)
{
    switch (m_eSourceType)
    {
        case SourceType::CameraDeviceRear:
        {
            BOOL isCamera = [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceRear];
            CC_RETURN_IF(!isCamera);
        }
            break;
        case SourceType::CameraDeviceFront:
        {
            BOOL isCamera = [UIImagePickerController isCameraDeviceAvailable:UIImagePickerControllerCameraDeviceFront];
            CC_RETURN_IF(!isCamera);
        }
            break;
        case SourceType::SavedPhotosAlbum:
        {
            CCAssert(false, "");
            return;
        }
            break;
        default:
            break;
    }

    this->retain();

    __picker_callback* c = ((__picker_callback*)convert(m_pOriginal).delegate);

    c.callback = [=](CAImage* image)
    {
        if (callback && image)
        {
            callback(image);
        }

        [UIView animateWithDuration:0.3 delay: 0 options:UIViewAnimationOptionCurveEaseOut animations:
        ^{
            CGRect rect = convert(m_pOriginal).view.frame;
            rect.origin.y = rect.size.height;
            [convert(m_pOriginal).view setFrame:rect];
        }
        completion:^(BOOL finished)
        {
            CAApplication::getApplication()->getTouchDispatcher()->setDispatchEvents(true);
            [convert(m_pOriginal).view removeFromSuperview];
            this->release();
        }];
        
        
    };
    
    CAApplication::getApplication()->getTouchDispatcher()->setDispatchEvents(false);
    [[EAGLView sharedEGLView] addSubview:convert(m_pOriginal).view];
    
    CGRect rect = convert(m_pOriginal).view.frame;
    rect.origin.y = rect.size.height;
    [convert(m_pOriginal).view setFrame:rect];
    
    [UIView animateWithDuration:0.3 delay: 0 options:UIViewAnimationOptionCurveEaseOut animations:
    ^{
        CGRect rect = convert(m_pOriginal).view.frame;
        rect.origin.y = 0;
        [convert(m_pOriginal).view setFrame:rect];
    } completion:nil];
}

void CAImagePickerController::writeImageToPhoto(CAImage* image, const std::function<void(bool)>& finishCallback, const std::string &imageName)
{
    CC_SAFE_RETAIN(image);
    CC_SAFE_RELEASE(m_pSavedImage);
    m_pSavedImage = image;
    
    CC_RETURN_IF(image == nullptr);
    
    this->retain();
    
    CAImage::PixelFormat pixelFormat = image->getPixelFormat();
    
    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    
    UIImage *newImage = NULL;
    CGImageRef imageRef = NULL;
    CGDataProviderRef provider = NULL;
    
    if (pixelFormat == CAImage::PixelFormat::RGBA8888 || pixelFormat == CAImage::PixelFormat::RGBA4444)
    {
        provider = CGDataProviderCreateWithData(NULL, image->getData(), 4*(image->getPixelsWide())*image->getPixelsHigh(), NULL);
        
        imageRef = CGImageCreate(image->getPixelsWide(), image->getPixelsHigh(), 8, 32, 4*(image->getPixelsWide()), colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);
        
        newImage = [UIImage imageWithCGImage:imageRef];
    }
    else
    {
        provider = CGDataProviderCreateWithData(NULL, image->getData(), 3*(image->getPixelsWide())*image->getPixelsHigh(), NULL);
        
        imageRef = CGImageCreate(image->getPixelsWide(), image->getPixelsHigh(), 8, 24, 3*(image->getPixelsWide()), colorSpaceRef, kCGBitmapByteOrderDefault, provider, NULL, NO, kCGRenderingIntentDefault);
        
        newImage = [UIImage imageWithCGImage:imageRef];
    }
    
    CFRelease(imageRef);
    CGColorSpaceRelease(colorSpaceRef);
    CGDataProviderRelease(provider);
    
    if (newImage == nil)
    {
        NSLog(@"Save image have some error");
    }
    
    __picker_callback* c = ((__picker_callback*)convert(m_pOriginal).delegate);
    
    c.finishCallback = [=](bool ok)
    {
        if (finishCallback)
        {
            finishCallback(ok);
        }
    
        this->release();
    };
    
    UIImageWriteToSavedPhotosAlbum(newImage, c, @selector(image: didFinishSavingWithError: contextInfo: ), nil);
}

NS_CC_END









