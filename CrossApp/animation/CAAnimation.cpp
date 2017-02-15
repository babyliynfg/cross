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
        void startAnimation(const CAAnimation::Callback& callback, float totalTime, float interval, float delay);
        
        void update(float dt);
        
        void end();
        
        Info m_obInfo;
    };
    
    static std::map<std::string, Animation> _map;
    
    void Animation::startAnimation(const CAAnimation::Callback& callback, float totalTime, float interval, float delay)
    {
        m_obInfo.model.total = totalTime;
        m_obInfo.model.dt = interval;
        m_obInfo.delay = delay;
        m_obInfo.callback = callback;
        CAScheduler::getScheduler()->scheduleUpdate(this, CAScheduler::PRIORITY_SYSTEM, false);
    }
    
    void Animation::update(float dt)
    {
        if (m_obInfo.delay > 0)
        {
            m_obInfo.delay -= dt;
            return;
        }
        
        if (m_obInfo.delay < 0)
        {
            dt += m_obInfo.delay;
            m_obInfo.delay = 0.0f;
        }
        
        m_obInfo.model.dt = dt;
        m_obInfo.model.now += dt;
        m_obInfo.model.now = MIN(m_obInfo.model.now, m_obInfo.model.total);
        
        if (m_obInfo.model.now >= m_obInfo.model.total)
        {
            this->retain();
            _map.erase(m_obInfo.animationID);
            this->end();
            this->release();
        }
        else if (m_obInfo.callback)
        {
            m_obInfo.callback(m_obInfo.model);
        }
    }
    
    void Animation::end()
    {
        CAScheduler::getScheduler()->unscheduleUpdate(this);
        if (m_obInfo.callback)
        {
            m_obInfo.callback(m_obInfo.model);
        }
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
        Animation obj;
        obj.startAnimation(callback, totalTime, interval, delay);
        _map.insert(std::make_pair(animationID, obj));
    }

    void unschedule(const std::string& animationID)
    {
        CC_RETURN_IF(_map.find(animationID) == _map.end());
        _map.at(animationID).end();
        _map.erase(animationID);
    }

}
NS_CC_END
