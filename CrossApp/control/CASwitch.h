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
    
    enum class Type : int
    {
        SquareRect,
        RoundedRect,
    };
    
    CASwitch(const CASwitch::Type& type);
    virtual ~CASwitch();
    
    static CASwitch* create(const CASwitch::Type& type);
    static CASwitch* createWithFrame(const DRect& rect, const CASwitch::Type& type);
    static CASwitch* createWithCenter(const DRect& rect, const CASwitch::Type& type);
    static CASwitch* createWithLayout(const DLayout& layout, const CASwitch::Type& type);
    
    void setTarget(const std::function<void(bool on)>& function);

    bool init();

public:
    
	CC_SYNTHESIZE_READONLY(CAImage*, m_onImage, OnImage);
	CC_SYNTHESIZE_READONLY(CAImage*, m_offImage, OffImage);
	CC_SYNTHESIZE_READONLY(CAImage*, m_thumbTintImage, ThumbTintImage);
    
    CC_SYNTHESIZE_IS_READONLY(bool, m_bIsOn, On);
    
    bool isOn();
    void setIsOn(bool on, bool animated);
    void setOnImage(CAImage* onImage);
    void setOffImage(CAImage* offImage);
    void setThumbTintImage(CAImage* thumbTintImage);
    
public:
    
    virtual void onExitTransitionDidStart();
    virtual void onEnterTransitionDidFinish();
    
    bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
    void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
protected:
    void updateSwitchState(bool animated);
    void setContentSize(const DSize& var);
    
protected:
    
    CASwitch::Type m_eType;
    
    bool m_bPrevIsOn;
    
    CAImageView *m_pOnImageView;
    CAImageView *m_pOffImageView;
    CAImageView *m_pThumbTintImageView;
    
    std::function<void(bool on)> m_function{nullptr};
};

NS_CC_END

#endif /*defined(CrossApp_CASwitch_h)*/
