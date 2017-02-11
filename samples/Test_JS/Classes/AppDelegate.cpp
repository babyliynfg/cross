#include "AppDelegate.h"
#include "ScriptingCore.h"
#include "jsb_crossapp_auto.hpp"
#include "crossapp_specifics.hpp"
#include "js_crossapp_delegates_manual.hpp"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{
    
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CAApplication* pDirector = CAApplication::getApplication();
    
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    
    ScriptingCore* sc = ScriptingCore::getInstance();
  
    sc->addRegisterCallback(register_all_crossapp);
    sc->addRegisterCallback(register_crossapp_js_core);
    sc->addRegisterCallback(register_all_crossapp_delegates_manual);

    sc->start();

    
    sc->runScript("script/jsb_boot.js");
    
    sc->enableDebugger();
    sc->runScript("script/jsb_crossapp.js");
    
    CCScriptEngineManager::sharedManager()->setScriptEngine(sc);
    sc->runScript("js/main.js");

    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CAApplication::getApplication()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CAApplication::getApplication()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
