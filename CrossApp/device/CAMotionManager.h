//
//  CAMotionManager.h
//  CrossApp
//
//  Created by 秦乐 on 2017/2/20.
//  Copyright © 2017年 . All rights reserved.
//

#ifndef CAMotionManager_h
#define CAMotionManager_h

#include "basics/CAObject.h"
#include <iostream>
#include <functional>
NS_CC_BEGIN

class CC_DLL CAMotionManager : public CAObject
{
public:
    
    struct Date
    {
        double x{0.f};
        double y{0.f};
        double z{0.f};
        float timestamp{0.f};
    };
    
    typedef std::function<void(const CAMotionManager::Date&)> Callback;
    
public:
    
    CREATE_FUNC(CAMotionManager);
    
    void startGyroscope(const std::function<void(const CAMotionManager::Date&)>& callback);
    
    void setGyroInterval(float interval);
    
    void stopGyroscope();

private:
    
    CAMotionManager();
    
    virtual ~CAMotionManager();
    
private:
    
    void* m_pMotionManager{nullptr};
    
    CAMotionManager::Date m_obData;
    
    CAMotionManager::Callback m_callback{nullptr};
};

NS_CC_END
#endif /* CAGyroscope_h */
