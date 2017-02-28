//
//  CAAlertView.h
//  CrossApp
//
//  Created by Zhujian on 14-6-10.
//  Copyright (c) 2014 http://www.9miao.com All rights reserved.
//


#ifndef __CAAlertView__
#define __CAAlertView__

#include "basics/CAObject.h"
#include "basics/CASTLContainer.h"
#include <functional>

NS_CC_BEGIN

class CC_DLL CAAlertView : public CAObject
{
public:
    
    static CAAlertView* create(const char* title, const char* message, const char* buttonTitle, ...);
    static CAAlertView* create(const std::string& title, const std::string& message);
    static CAAlertView* create(const std::string& title, const std::string& message, const std::vector<std::string>& buttonTitles);
    
    void addButtonTitle(const std::string& buttonTitle);
    void setButtonTitles(const std::vector<std::string>& buttonTitles);
    
    void show();
    void show(const std::function<void(int)>& callback);
    
private:
    
    CAAlertView(const std::string& title, const std::string& message);
    
private:
    
    std::string m_sTitle;
    std::string m_sMessage;
    std::vector<std::string> m_vButtonTitles;
    std::function<void(int)> m_callback;
};

NS_CC_END

#endif /* defined(__CAAlertView__) */
