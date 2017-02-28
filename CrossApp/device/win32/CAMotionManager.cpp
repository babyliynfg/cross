//
//  CAGyroscope.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/20.
//  Copyright © 2017年 . All rights reserved.
//

#include "../CAMotionManager.h"
#include "basics/CAApplication.h"

NS_CC_BEGIN

CAMotionManager::CAMotionManager()
{
}

CAMotionManager::~CAMotionManager()
{
}


std::function<void(const CAMotionManager::Date&)> _callBack;

void CAMotionManager::startGyroscope(const std::function<void(const CAMotionManager::Date&)>& callback)
{
    _callBack = callback;
}

void CAMotionManager::setGyroInterval(float interval)
{
}

void CAMotionManager::stopGyroscope()
{
}

NS_CC_END

