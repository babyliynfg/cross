//
//  CATableView.h
//  CrossApp
//
//  Created by Li Yuanfeng on 16-4-20.
//  Copyright (c) 2014 http://9miao.com All rights reserved.
//

#ifndef __CrossApp_CACell__
#define __CrossApp_CACell__

#include <iostream>
#include "control/CAControl.h"

NS_CC_BEGIN

class CAUIEditorParser;
class CC_DLL CACell: public CAControl
{

public:
    
    CACell();
    
    virtual ~CACell();
    
    static CACell* create(const std::string& reuseIdentifier);
    
    virtual bool initWithReuseIdentifier(const std::string& reuseIdentifier);
    
    CC_SYNTHESIZE_READONLY(CAView*, m_pContentView, ContentView);
    
    CC_PROPERTY(CAView*, m_pBackgroundView, BackgroundView);

    CC_SYNTHESIZE_PASS_BY_REF(std::string, m_sReuseIdentifier, ReuseIdentifier);

    CC_SYNTHESIZE_IS(bool, m_bControlStateEffect, ControlStateEffect);
    
    CC_SYNTHESIZE_IS(bool, m_bAllowsSelected, AllowsSelected);

    CAView* getViewWithID(const std::string &tag);
    
    void setControlState(CAControl::State var);
    
    CAControl::State getControlState();
    
    void setControlStateNormal();
    
    void setControlStateHighlighted();
    
    void setControlStateSelected();
    
    void setControlStateDisabled();
    
public:
    
    virtual void mouseMoved(CATouch* pTouch, CAEvent* pEvent);
    
    virtual void mouseMovedOutSide(CATouch* pTouch, CAEvent* pEvent);
    
protected:

    virtual void normalCell();
    
    virtual void highlightedCell();
    
    virtual void selectedCell();
    
    virtual void disabledCell();

    virtual void recoveryCell(){};
    
    void resetCell();
    
    void parser();
    
private:

    using CAView::init;
    
    using CAView::initWithCenter;
    
    using CAView::initWithFrame;
    
    using CAView::initWithLayout;
    
    CAUIEditorParser* m_pParser;
    
    CAControl::State m_eState;
};

NS_CC_END;

#endif /* defined(__CrossApp_CACell__) */
