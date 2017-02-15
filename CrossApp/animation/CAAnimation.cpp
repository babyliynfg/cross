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
        std::function<void(const CAAnimation::Model&)> function{nullptr};
    };

    struct CC_DLL Animation : public CAObject
    {
        void startAnimation(float totalTime, float interval, float delay, const std::function<void(const CAAnimation::Model&)>& function);
        
        void update(float dt);
        
        void end();
        
        Info m_obInfo;
    };
    
    static CADeque<Animation*> _deque;
    
    void Animation::startAnimation(float totalTime, float interval, float delay, const std::function<void(const CAAnimation::Model&)>& function)
    {
        m_obInfo.model.total = totalTime;
        m_obInfo.model.dt = interval;
        m_obInfo.delay = delay;
        m_obInfo.function = function;
        CAScheduler::schedule(schedule_selector(Animation::update), this, interval);
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
            _deque.eraseObject(this);
            this->end();
            this->release();
        }
        else if (m_obInfo.function)
        {
            m_obInfo.function(m_obInfo.model);
        }
    }
    
    void Animation::end()
    {
        CAScheduler::unscheduleAllForTarget(this);
        if (m_obInfo.function)
        {
            m_obInfo.function(m_obInfo.model);
        }
    }
    
    bool isSchedule(const std::string& animationID)
    {
        bool ret = false;
        for (auto& var : _deque)
        {
            if (var->m_obInfo.animationID.compare(animationID) == 0)
            {
                ret = true;
                break;
            }
        }
        return ret;
    }
    
    void schedule(const std::string& animationID, float totalTime, const std::function<void(const CAAnimation::Model&)>& function)
    {
        schedule(animationID, totalTime, 0, 0.0f, function);
    }
    
    void schedule(const std::string& animationID, float totalTime, float interval, const std::function<void(const CAAnimation::Model&)>& function)
    {
        schedule(animationID, totalTime, interval, 0.0f, function);
    }
    
    void schedule(const std::string& animationID, float totalTime, float interval, float delay, const std::function<void(const CAAnimation::Model&)>& function)
    {
        Animation* obj = new Animation();
        _deque.pushBack(obj);
        obj->startAnimation(totalTime, interval, delay, function);
        obj->release();
    }

    void unschedule(const std::string& animationID)
    {
        for (auto itr = _deque.begin(); itr!=_deque.end();)
        {
            Animation* var = *itr;
            if (var->m_obInfo.animationID.compare(animationID) == 0)
            {
                var->retain();
                itr = _deque.erase(itr);
                var->end();
                var->release();
                break;
            }
            else
            {
                ++itr;
            }
        }
    }

}
NS_CC_END
