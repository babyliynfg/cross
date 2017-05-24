//
//  JSViewController.cpp
//  JavaScriptTest
//
//  Created by lihui on 14-8-15.
//
//

#include "JSViewController.h"
#include "script_support/CCScriptSupport.h"
JSViewController::JSViewController()
{
    CrossApp::CCLog("JSViewController()");
}

JSViewController::~JSViewController()
{
    CrossApp::CCLog("JSViewController::~JSViewController()");
}
void JSViewController::viewDidLoad()
{
//     CrossApp::CAScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, 1);
}

void JSViewController::viewDidUnload()
{
//    CrossApp::CAScriptEngineManager::sharedManager()->getScriptEngine()->executeNodeEvent(this, 2);
}
