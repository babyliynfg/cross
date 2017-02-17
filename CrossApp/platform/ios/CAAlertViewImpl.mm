

#include "../CAAlertViewImpl.h"
#import <UIKit/UIAlert.h>

@interface __alertView_callback: NSObject <UIAlertViewDelegate>
{
    std::function<void(int)> _callback;
}

- (id)init:(std::function<void(int)>)callback;

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex;

@end

@implementation __alertView_callback


- (id)init:(std::function<void(int)>)callback
{
    if ([super init] == nil)
    {
        return nil;
    }
    _callback = callback;
    
    return self;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (_callback != nullptr)
    {
        _callback((int)buttonIndex);
    }
    
    [self release];
}
@end

NS_CC_BEGIN


void __show_alertView(const std::string& title, const std::string& message, const std::vector<std::string>& buttonTitles, const std::function<void(int)>& callback)
{
    __alertView_callback* delegate = [[__alertView_callback alloc] init:callback];
    
    NSString * t = (!title.empty()) ? [NSString stringWithUTF8String : title.c_str()] : nil;
    NSString * m = (!message.empty()) ? [NSString stringWithUTF8String : message.c_str()] : nil;
    UIAlertView * messageBox = [[UIAlertView alloc] initWithTitle: t
                                                          message: m
                                                         delegate: delegate
                                                cancelButtonTitle: nil
                                                otherButtonTitles: nil];
    
    for (auto& buttonTitle : buttonTitles)
    {
        [messageBox addButtonWithTitle:[NSString stringWithUTF8String:buttonTitle.c_str()]];
    }
    
    [messageBox show];
    [messageBox autorelease];
}

NS_CC_END
