//
//  CAButton.h
//  CrossApp
//
//  Created by Li Yuanfeng on 14-3-23.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//


#ifndef __CAButton__
#define __CAButton__

#include <iostream>
#include "CAControl.h"
NS_CC_BEGIN

class CAImageView;
class CALabel;

class CC_DLL CAButton : public CAControl
{
    
public:

    enum class Event
    {
        TouchDown,
        TouchDownRepeat,
        TouchMoved,
        TouchMovedOutSide,
        TouchUpInSide,
        TouchUpOutSide,
        TouchLongPress,
        TouchCancelled
    };
    
    enum class Type : int
    {
        Custom = 0,
        SquareRect,
        RoundedRect,
    };
    
public:
    
    CAButton(const CAButton::Type& buttonType);
    
    virtual ~CAButton(void);
    
    virtual void onExitTransitionDidStart();
    
    virtual void onEnterTransitionDidFinish();
    
    static CAButton* create(const CAButton::Type& buttonType);
    
    static CAButton* createWithFrame(const DRect& rect, const CAButton::Type& buttonType);
    
    static CAButton* createWithCenter(const DRect& rect, const CAButton::Type& buttonType);
    
    static CAButton* createWithLayout(const DLayout& layout, const CAButton::Type& buttonType);
    
public:
    
    virtual bool init();
    
    void setBackgroundViewForState(CAControl::State state, CAView *var);
    
    CAView* getBackgroundViewForState(CAControl::State state);
    
    void setImageForState(CAControl::State state, CAImage* var);
    
    CAImage* getImageForState(CAControl::State state);
    
    void setTitleForState(CAControl::State state, const std::string& var);
    
    const std::string& getTitleForState(CAControl::State state);
    
    void setImageColorForState(CAControl::State state, const CAColor4B& var);
    
    void setTitleColorForState(CAControl::State state, const CAColor4B& var);
    
    void setTitleFontName(const std::string& var);
    
    void setImageOffset(const DSize& offset);
    
    void setImageSize(const DSize& size);
    
    void setTitleOffset(const DSize& offset);
    
    void setTitleLabelSize(const DSize& size);
    
    void setTitleFontSize(float fontSize);
    
    void setTitleBold(bool bold);
    
    void setTitleTextAlignment(const CATextAlignment& var);
 
    void addTarget(const std::function<void(CAButton*)>& function, CAButton::Event event);

    void setControlState(CAControl::State state);
    
public:
    
	void interruptTouchState();

public:
    
    virtual bool ccTouchBegan(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchMoved(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchEnded(CATouch *pTouch, CAEvent *pEvent);
    
    virtual void ccTouchCancelled(CATouch *pTouch, CAEvent *pEvent);
    
protected:

    CAButton::Type m_eButtonType;
    
    CAControl::State m_eState;
    
    CAMap<CAControl::State, CAImage*> m_mImages;
    
    std::map<CAControl::State, CAColor4B> m_mImageColors;
    
    std::map<CAControl::State, std::string> m_mTitles;
    
    std::map<CAControl::State, CAColor4B> m_mTitleColors;

    CAMap<CAControl::State, CAView*> m_mBackgroundViews;
    
    CAImageView* m_pImageView;
    
    CALabel* m_pLabel;
    
    std::string m_sTitleFontName;
    
    float m_fTitleFontSize;
    
    bool m_bTitleBold;
        
    DSize m_pTitleLabelSize;
    
    bool m_bDefineTitleLabelSize;
    
    DSize m_pImageSize;
    
    bool m_bDefineImageSize;
    
    DSize m_pTitleOffset;
    
    bool m_bDefineTitleOffset;
    
    DSize m_pImageOffset;
    
    bool m_bDefineImageOffset;
    
    std::map<CAButton::Event, std::function<void(CAButton*)>> m_mFunctions;
    
    bool m_bTouchClick;
    
protected:
    
    void updateWithPreferredSize();
    
    void setContentSize(const DSize & var);

    void setBackgroundViewSquareRect();
    
    void setBackgroundViewRoundedRect();
    
    void callBackFunction(CAButton::Event event);
};

#define setBackGroundViewForState(state, var) setBackgroundViewForState(state, var)
#define getBackGroundViewForState(state, var) getBackgroundViewForState(state, var)
NS_CC_END

#endif /* defined(__CAButton__) */
