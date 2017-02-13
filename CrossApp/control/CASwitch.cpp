//
//  CASwitch.cpp
//  CrossApp 
//
//  Created by juguanhui on 14-5-29.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#include "CASwitch.h"
#include "view/CAImageView.h"
#include "dispatcher/CATouch.h"
#include "view/CAScale9ImageView.h"
#include "support/CAPointExtension.h"
#include "view/CARenderImage.h"
#include "basics/CAApplication.h"
#include "animation/CAViewAnimation.h"
#include "support/CAThemeManager.h"
#include "support/ccUtils.h"
NS_CC_BEGIN

CASwitch::CASwitch()
    : CAControl()
    , m_onImage(NULL)
    , m_offImage(NULL)
    , m_thumbTintImage(NULL)
    , m_bIsOn(false)
    , m_pOnImageView(NULL)
    , m_pOffImageView(NULL)
    , m_pThumbTintImageView(NULL)
{
    const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CASwitch");
    this->setOnImage(CAImage::create(map.at("onImage")));
    this->setOffImage(CAImage::create(map.at("offImage")));
    this->setThumbTintImage(CAImage::create(map.at("thumbTintImage")));
}

CASwitch::~CASwitch()
{
    CC_SAFE_RELEASE_NULL(m_onImage);
	CC_SAFE_RELEASE_NULL(m_offImage);
	CC_SAFE_RELEASE_NULL(m_thumbTintImage);
}

CASwitch* CASwitch::create()
{
    CASwitch* switchControl = new CASwitch();
    
    if (switchControl && switchControl->init())
    {
        switchControl->autorelease();
        return switchControl;
    }
    
    CC_SAFE_DELETE(switchControl);
    return NULL;
}

CASwitch* CASwitch::createWithFrame(const DRect& rect)
{
    CASwitch* switchControl = new CASwitch();
    
    if (switchControl && switchControl->initWithFrame(rect))
    {
        switchControl->autorelease();
        return switchControl;
    }
    
    CC_SAFE_DELETE(switchControl);
    return NULL;
}

CASwitch* CASwitch::createWithCenter(const DRect& rect)
{
    CASwitch* switchControl = new CASwitch();
    
    if (switchControl && switchControl->initWithCenter(rect))
    {
        switchControl->autorelease();
        return switchControl;
    }
    
    CC_SAFE_DELETE(switchControl);
    return NULL;
}

CASwitch* CASwitch::createWithLayout(const CrossApp::DLayout &layout)
{
    CASwitch* switchControl = new CASwitch();
    
    if (switchControl && switchControl->initWithLayout(layout))
    {
        switchControl->autorelease();
        return switchControl;
    }
    
    CC_SAFE_DELETE(switchControl);
    return NULL;
}

bool CASwitch::init()
{
    if (!CAControl::init())
    {
        return false;
    }
    this->setColor(CAColor_clear);

    m_pOnImageView = CAImageView::createWithImage(m_onImage);
    this->addSubview(m_pOnImageView);

    m_pOffImageView = CAImageView::createWithImage(m_offImage);
    this->addSubview(m_pOffImageView);
    
    m_pThumbTintImageView = CAImageView::createWithImage(m_thumbTintImage);
    this->addSubview(m_pThumbTintImageView);
 
    return true;
}

void CASwitch::onExitTransitionDidStart()
{
    CAControl::onExitTransitionDidStart();
}

void CASwitch::onEnterTransitionDidFinish()
{
    CAControl::onEnterTransitionDidFinish();
    this->updateSwitchState(false, false);
}

void CASwitch::setIsOn(bool on, bool animated)
{
    if (m_bIsOn != on)
    {
        m_bIsOn = on;
        CC_RETURN_IF(!m_bRunning);
        this->updateSwitchState(animated, false);
    }
}

void CASwitch::setOnImage(CAImage* onImage)
{
    if (m_onImage != onImage)
    {
        CC_SAFE_RETAIN(onImage);
        CC_SAFE_RELEASE(m_onImage);
        m_onImage = onImage;
        if (m_pOnImageView)
        {
            m_pOnImageView->setImage(m_onImage);
        }
    }
}

void CASwitch::setOffImage(CAImage* offImage)
{
    if (m_offImage != offImage)
    {
        CC_SAFE_RETAIN(offImage);
        CC_SAFE_RELEASE(m_offImage);
        m_offImage = offImage;
        if (m_pOffImageView)
        {
            m_pOffImageView->setImage(m_offImage);
        }
    }
}

void CASwitch::setThumbTintImage(CAImage* thumbTintImage)
{
    if (m_thumbTintImage != thumbTintImage)
    {
        CC_SAFE_RETAIN(thumbTintImage);
        CC_SAFE_RELEASE(m_thumbTintImage);
        m_thumbTintImage = thumbTintImage;
        if (m_pThumbTintImageView)
        {
            m_pThumbTintImageView->setImage(m_thumbTintImage);
        }
    }
}

void CASwitch::updateSwitchState(bool animated, bool callfunced)
{
    DPoint point = m_obContentSize/2;
    m_pOnImageView->setCenterOrigin(point);
    m_pOffImageView->setCenterOrigin(point);
    if (animated)
    {
        CAViewAnimation::beginAnimations("", NULL);
        CAViewAnimation::setAnimationDuration(0.2f);
        if (m_bIsOn)
        {
            CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseIn);
            m_pOffImageView->setAlpha(0.0f);
            m_pOnImageView->setAlpha(1.0f);
        }
        else
        {
            CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseOut);
            m_pOffImageView->setAlpha(1.0f);
            m_pOnImageView->setAlpha(0.0f);
        }
        CAViewAnimation::commitAnimations();
        if (m_pThumbTintImageView)
        {
            DPoint point = DPointZero;
            point.x = m_bIsOn ? (m_obContentSize.width - m_pThumbTintImageView->getBounds().size.width) : 0;
            
            if (callfunced)
            {
                CAViewAnimation::beginAnimations("", NULL);
                CAViewAnimation::setAnimationDuration(0.2f);
                CAViewAnimation::setAnimationCurve(CAViewAnimationCurveEaseOut);
                CAViewAnimation::setAnimationDidStopSelector(this, CAViewAnimation0_selector(CASwitch::updateValueChanged));
                m_pThumbTintImageView->setFrameOrigin(point);
                CAViewAnimation::commitAnimations();
            }
        }
    }
    else
    {
        m_pOffImageView->setAlpha(m_bIsOn ? 0.0f : 1.0f);
        m_pOnImageView->setAlpha(m_bIsOn? 1.0f : 0.0f);
        if (m_pThumbTintImageView)
        {
            DPoint point = DPointZero;
            point.x = m_bIsOn ? (m_obContentSize.width - m_pThumbTintImageView->getBounds().size.width) : 0;
            m_pThumbTintImageView->setFrameOrigin(point);
            if (callfunced)
            {
                updateValueChanged();
            }
        }
    }
}

void CASwitch::updateValueChanged()
{
    m_function(this, m_bIsOn);
}

bool CASwitch::ccTouchBegan(CATouch *pTouch, CAEvent *pEvent)
{
    DPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
	m_bTouchClick = true;
    
    
    return m_bTouchClick;
}

void CASwitch::ccTouchEnded(CrossApp::CATouch *pTouch, CrossApp::CAEvent *pEvent)
{
    if (!this->isTouchClick())
        return;
    
    DPoint point = pTouch->getLocation();
    point = this->convertToNodeSpace(point);
    
    if (getBounds().containsPoint(point))
    {
        this->setControlState(CAControl::State::Normal);
        m_bIsOn = !m_bIsOn;
        this->updateSwitchState(true, true);
    }
}

void CASwitch::setTarget(const std::function<void (CASwitch*, bool on)>& function)
{
    m_function = function;
}


void CASwitch::setContentSize(const DSize & var)
{
    DSize size = var;
    if (m_bRecSpe)
    {
        const CAThemeManager::stringMap& map = CAApplication::getApplication()->getThemeManager()->getThemeMap("CASwitch");
        int h = atoi(map.at("height").c_str());
        int w = atoi(map.at("width").c_str());
        size.height = (h == 0) ? size.height : h;
        size.width  = (w == 0) ? size.width : w;
    }
    CAControl::setContentSize(size);
    DRect bounds = this->getBounds();
    m_pOnImageView->setFrame(bounds);
    m_pOffImageView->setFrame(bounds);
    m_pThumbTintImageView->setFrame(DRect(0, 0, bounds.size.height, bounds.size.height));
    this->updateSwitchState(false, false);
}

NS_CC_END
