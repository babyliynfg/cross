//
//  CAGyroscope.mm
//  CrossApp
//
//  Created by 秦乐 on 2017/2/20.
//  Copyright © 2017年 . All rights reserved.
//

#include "CAMotionManager.h"
#include "basics/CAScheduler.h"
#import <CoreMotion/CoreMotion.h>
#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <UIKit/UIKit.h>

NS_CC_BEGIN

CMMotionManager* convert(void* var)
{
    return (CMMotionManager*)var;
}

CAMotionManager::CAMotionManager()
{
    m_pMotionManager = [[CMMotionManager alloc] init];
    
    convert(m_pMotionManager).gyroUpdateInterval = 0.001f;
}

CAMotionManager::~CAMotionManager()
{
    [convert(m_pMotionManager) release];
}

void CAMotionManager::startGyroscope(const CAMotionManager::Callback& callback)
{
    if ([convert(m_pMotionManager) isGyroAvailable] == NO)
    {
        NSLog(@"Gyro is not available.");
        return;
    }
    
    m_callback = callback;
    
    this->retain();
    
    [convert(m_pMotionManager) startGyroUpdatesToQueue:[NSOperationQueue mainQueue] withHandler:^(CMGyroData *gyroData, NSError *error) {
        
        m_obData.x = gyroData.rotationRate.x;
        m_obData.y = gyroData.rotationRate.y;
        m_obData.z = gyroData.rotationRate.z;
        m_obData.timestamp = convert(m_pMotionManager).gyroUpdateInterval;
        
        CAScheduler::getScheduler()->performFunctionInUIThread( [&]()
        {
            if (m_callback)
            {
                m_callback(m_obData);
            }
        });
    }];
}

void CAMotionManager::setGyroInterval(float interval)
{
    convert(m_pMotionManager).gyroUpdateInterval = interval;
}

void CAMotionManager::stopGyroscope()
{
   [convert(m_pMotionManager) stopGyroUpdates];
    this->autorelease();
}

NS_CC_END


