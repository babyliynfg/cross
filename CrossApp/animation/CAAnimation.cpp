//
//  CAAnimation.cpp
//  CrossApp
//
//  Created by 栗元峰 on 15/4/29.
//  Copyright (c) 2015年 9秒社区. All rights reserved.
//

#include "CAAnimation.h"
#include "basics/CASTLContainer.h"
#include <set>
NS_CC_BEGIN

namespace CAAnimation
{
    struct Info
    {
        CAAnimation::Model model;
        std::string animationID;
        float delay{0.0f};
        CAAnimation::Callback callback{nullptr};
    };

    struct CC_DLL Animation : public CAObject
    {
        void startAnimation(const CAAnimation::Callback& callback, const std::string& animationID, float totalTime, float interval, float delay);
        
        void end();
        
        Info info;
    };
    
    static std::map<std::string, Animation*> _map;
    
    void Animation::startAnimation(const CAAnimation::Callback& callback, const std::string& animationID, float totalTime, float interval, float delay)
    {
        info.model.total = totalTime;
        info.model.dt = interval;
        info.delay = delay;
        info.callback = callback;
        info.animationID = animationID;
        CAScheduler::getScheduler()->schedule([&](float dt)
        {
            if (info.delay > 0)
            {
                info.delay -= dt;
                return;
            }
            
            if (info.delay < 0)
            {
                dt += info.delay;
                info.delay = 0.0f;
            }
            
            info.model.dt = dt;
            info.model.now += dt;
            info.model.now = MIN(info.model.now, info.model.total);
            
            if (info.model.now == info.model.total)
            {
                this->end();
            }
            else if (info.callback)
            {
                info.callback(info.model);
            }

        }, "update", this, 0);
    }
    
    void Animation::end()
    {
        info.model.end = true;
        _map.erase(info.animationID);
        CAScheduler::getScheduler()->unschedule("update", this);
        if (info.callback)
        {
            info.callback(info.model);
        }
        this->release();
    }
    
    bool isSchedule(const std::string& animationID)
    {
        return _map.find(animationID) != _map.end();
    }
    
    void schedule(const CAAnimation::Callback& callback, const std::string& animationID, float totalTime)
    {
        schedule(callback, animationID, totalTime, 0, 0.0f);
    }
    
    void schedule(const CAAnimation::Callback& callback, const std::string& animationID, float totalTime, float interval)
    {
        schedule(callback, animationID, totalTime, interval, 0.0f);
    }
    
    void schedule(const CAAnimation::Callback& callback, const std::string& animationID, float totalTime, float interval, float delay)
    {
        CC_RETURN_IF(_map.find(animationID) != _map.end());
        Animation* obj = new Animation();
        obj->startAnimation(callback, animationID, totalTime, interval, delay);
        _map.insert(std::make_pair(animationID, obj));
    }

    void unschedule(const std::string& animationID)
    {
        CC_RETURN_IF(_map.find(animationID) == _map.end());
        _map.at(animationID)->end();
    }

}
NS_CC_END
