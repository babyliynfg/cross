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
#include "basics/CAValue.h"
NS_CC_BEGIN



class CC_DLL CAMotionManager : public CAObject
{
public:
    
    /**
     *  @       "x"         double
     *  @       "y"         double
     *  @       "z"         double
     *  @       "timestamp" float
     */
    typedef std::function<void(const CAValueMap&)> Callback;
public:

    CAMotionManager();
    
    virtual ~CAMotionManager();
    
    static CAMotionManager* getInstance();
    
    void startGyroscope(const CrossApp::CAMotionManager::Callback& callback);
    
    void setGyroInterval(float interval);
    
    void stopGyroscope();

private:
    
    void* m_pMotionManager{nullptr};
    
    CAValueMap m_obData;
    
    CAMotionManager::Callback m_callback{nullptr};
};

NS_CC_END
#endif /* CAGyroscope_h */
