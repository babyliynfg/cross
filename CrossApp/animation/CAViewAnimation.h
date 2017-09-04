//
//  CAViewAnimation.h
//  CrossApp
//
//  Created by 栗元峰 on 15-1-23.
//  Copyright (c) 2015年 http://www.9miao.com All rights reserved.
//

#ifndef __CrossApp__CAViewAnimation__
#define __CrossApp__CAViewAnimation__

#include "view/CAView.h"
#include "view/CAImageView.h"
#include "view/CAScale9ImageView.h"
NS_CC_BEGIN

class CC_DLL CAViewAnimation: public CAObject
{
public:
    
    enum class Curve : int
    {
        Linear = 0,
        EaseOut,          // slow at end
        EaseIn,           // slow at beginning
        EaseInOut         // slow at beginning and end
    };

private:
        struct Module : public CAObject
        {
            std::string                 animationID;
            CAMap<CAView*, CAObject*>   animations;
            float                       duration{0.2f};
            float                       delay{0.0f};
            float                       repeatCount{1.0f};
            bool                        repeatAutoreverses{false};
            float                       time{0.0f};
            CAViewAnimation::Curve      curve{CAViewAnimation::Curve::Linear};
            std::function<void()>       willStartFunction{nullptr};
            std::function<void()>       didStopFunction{nullptr};
            bool                        alreadyRunning{false};
        };
        
public:
        
    static void beginAnimations(const std::string& animationID);
    
    static void commitAnimations();
    
    static void setAnimationDuration(float duration);// default(0.2)
    
    static void setAnimationDelay(float delay);// default(0)
    
    static void setAnimationCurve(CAViewAnimation::Curve curve);// default(CAViewAnimation::Curve::Linear)
    
    static void setAnimationRepeatCount(float repeatCount);// default(1.0)
    
    static void setAnimationRepeatAutoreverses(bool repeatAutoreverses);// default(false)
    
    static void setAnimationWillStartSelector(const std::function<void()>& function);

    static void setAnimationDidStopSelector(const std::function<void()>& function);
    
    static void removeAnimations(const std::string& animationID);
    
    static void removeAnimationsWithView(CAView* view);

    static void removeAllAnimations();
        
    static void setAnimationsEnabled(bool enabled);
    
    static bool areAnimationsEnabled();

    static bool areBeginAnimations();
    
    static bool areBeginAnimationsWithID(const std::string& animationID);
        
protected:

    static CAViewAnimation* getInstance();
    
    static void destroyInstance();
        
    CAViewAnimation();
    
    virtual ~CAViewAnimation();

    void setPoint(const DPoint& point, CAView* view);
    
    void setContentSize(const DSize& size, CAView* view);
    
    void setScaleX(float scaleX, CAView* view);
    
    void setScaleY(float scaleY, CAView* view);
    
    void setZOrder(int zOrder, CAView* view);
    
    void setPointZ(float PointZ, CAView* view);
    
    void setSkewX(float skewX, CAView* view);
    
    void setSkewY(float skewY, CAView* view);
    
    void setRotation(float rotation, CAView* view);
    
    void setRotationX(float rotationX, CAView* view);
    
    void setRotationY(float rotationY, CAView* view);
    
    void setColor(const CAColor4B& color, CAView* view);
    
    void setAlpha(float alpha, CAView* view);
    
    void setImageRect(const DRect& imageRect, CAView* view);
        
    void setFlipX(bool flipX, CAView* view);
    
    void setFlipY(bool flipY, CAView* view);
    
    void allocCAViewModel(CAView* view);
    
    void update(float dt);
    
    bool m_bAnimationsEnabled;
    
    bool m_bBeginAnimations;
    
    CADeque<CAViewAnimation::Module*> m_vWillModules;
        
    CAVector<CAViewAnimation::Module*> m_vModules;
        
    friend class CAView;
    
    friend class CAImageView;
    
    friend class CAScale9ImageView;
        
    friend class CAApplication;
};

NS_CC_END
#endif /* defined(__CrossApp__CAViewAnimation__) */
