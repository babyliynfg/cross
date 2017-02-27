//
//  CASwitch.h
//  CrossApp
//
//  Created by juguanhui on 14-5-29.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#ifndef CrossApp_CASwitch_h
#define CrossApp_CASwitch_h

#include "CAControl.h"
#include "view/CAScale9ImageView.h"
NS_CC_BEGIN

class CAImageView;
class CAImage;

class CC_DLL CASwitch : public CAControl 
{
public:
    
    CASwitch();
    virtual ~CASwitch();
    
    static CASwitch* create();
    static CASwitch* createWithFrame(const DRect& rect);
    static CASwitch* createWithCenter(const DRect& rect);
    static CASwitch* createWithLayout(const DLayout& layout);
    
    void setTarget(const std::function<void(bool on)>& function);

    bool init();

public:
    
	CC_SYNTHESIZE_READONLY(CAImage*, m_onImage, OnImage);
	CC_SYNTHESIZE_READONLY(CAImage*, m_offImage, OffImage);
	CC_SYNTHESIZE_READONLY(CAImage*, m_thumbTintImage, ThumbTintImage);
    
    CC_SYNTHESIZE_IS_READONLY(bool, m_bIsOn, On);
	CC_SYNTHESIZE_IS_READONLY(bool, m_bTouchClick, TouchClick);
    
    bool isOn();
    void setIsOn(bool on, bool animated);
    void setOnImage(CAImage* onImage);
    void setOffImage(CAImage* offImage);
    void setThumbTintImage(CAImage* thumbTintImage);
    
public:
    
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
protected:
    void updateSwitchState(bool animated, bool callback);
    void setContentSize(const DSize & var);
    
protected:
    
    CAImageView *m_pOnImageView;
    CAImageView *m_pOffImageView;
    CAImageView *m_pThumbTintImageView;
    
    std::function<void(bool on)> m_function{nullptr};
};

NS_CC_END

#endif /*defined(CrossApp_CASwitch_h)*/
