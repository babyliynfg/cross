
#include "crossapp_specifics.hpp"
#include "CrossApp.h"
#include <typeinfo>
#include "js_bindings_config.h"
#include "jsb_crossapp_auto.hpp"


using namespace CrossApp;

schedFunc_proxy_t *_schedFunc_target_ht = NULL;
schedTarget_proxy_t *_schedObj_target_ht = NULL;

JSTouchDelegate::TouchDelegateMap JSTouchDelegate::sTouchDelegateMap;

JSTouchDelegate::JSTouchDelegate()
{
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    _obj.construct(cx);
}

JSTouchDelegate::~JSTouchDelegate()
{
//    CCLOG("In the destructor of JSTouchDelegate.");
    _obj.destroyIfConstructed();
}

void JSTouchDelegate::setDelegateForJSObject(JSObject* pJSObj, JSTouchDelegate* pDelegate)
{
    CCAssert(sTouchDelegateMap.find(pJSObj) == sTouchDelegateMap.end(),
             "pJSObj can't be found in sTouchDelegateMap.");
    sTouchDelegateMap.insert(TouchDelegatePair(pJSObj, pDelegate));
}

JSTouchDelegate* JSTouchDelegate::getDelegateForJSObject(JSObject* pJSObj)
{
    JSTouchDelegate* pRet = NULL;
    TouchDelegateMap::iterator iter = sTouchDelegateMap.find(pJSObj);
    if (iter != sTouchDelegateMap.end())
    {
        pRet = iter->second;
    }
    return pRet;
}

void JSTouchDelegate::removeDelegateForJSObject(JSObject* pJSObj)
{
    TouchDelegateMap::iterator iter = sTouchDelegateMap.find(pJSObj);
    CCAssert(iter != sTouchDelegateMap.end(), "pJSObj can't be found in sTouchDelegateMap!");
    sTouchDelegateMap.erase(pJSObj);
}

void JSTouchDelegate::setJSObject(JS::HandleObject obj)
{
    _obj.ref() = obj;
}

bool JSTouchDelegate::onTouchBegan(CATouch *touch, CAEvent *event)
{
    CC_UNUSED_PARAM(event); 
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue retval(cx);
    bool bRet = false;
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHBEGAN, touch, _obj.ref(), &retval);
    
    if(retval.isBoolean())
    {
        bRet = retval.toBoolean();
    } 

    return bRet;
};
// optional

void JSTouchDelegate::onTouchMoved(CATouch *touch, CAEvent *event)
{
    CC_UNUSED_PARAM(event);

    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHMOVED, touch, _obj.ref());
}

void JSTouchDelegate::onTouchEnded(CATouch *touch, CAEvent *event)
{
    CC_UNUSED_PARAM(event);

    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHENDED, touch, _obj.ref());
}

void JSTouchDelegate::onTouchCancelled(CATouch *touch, CAEvent *event)
{
    CC_UNUSED_PARAM(event);
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHCANCELLED, touch, _obj.ref());
}

void JSTouchDelegate::mouseMoved(CATouch* pTouch, CAEvent* pEvent)
{
    CC_UNUSED_PARAM(pEvent);

}
void JSTouchDelegate::mouseMovedOutSide(CATouch* pTouch, CAEvent* pEvent)
{
    CC_UNUSED_PARAM(pEvent);

}
void JSTouchDelegate::mouseScrollWheel(CATouch* pTouch, float off_x, float off_y, CAEvent* pEvent)
{
    CC_UNUSED_PARAM(pEvent);

}

//JSTouch
bool js_crossapp_JSTouchView_addTouchView(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1 || argc == 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

        JSTouchView *touch = new JSTouchView();

        int priority = 1;
        if (argc == 2)
        {
            priority = args.get(1).toInt32();
        }

        JS::RootedObject jsobj(cx, args.get(0).toObjectOrNull());
        touch->setJSObject(jsobj);
        JSTouchView::setTouchViewForJSObject(jsobj, touch);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_crossapp_JSTouchView_removeTouchView(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JSObject* jsobj = args.get(0).toObjectOrNull();
        JSTouchView* pDelegate = JSTouchView::getTouchViewForJSObject(jsobj);
        if (pDelegate)
        {
            JSTouchView::removeTouchViewForJSObject(jsobj);
            pDelegate->removeFromSuperview();
        }

        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
//JSTouchViewController
bool js_crossapp_JSTouchViewController_addTouchViewController(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1 || argc == 2)
    {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        JSTouchViewController *touch = new JSTouchViewController();
        
        int priority = 1;
        if (argc == 2)
        {
            priority = args.get(1).toInt32();
        }
        
        JS::RootedObject jsobj(cx, args.get(0).toObjectOrNull());
        touch->setJSObject(jsobj);
        JSTouchViewController::setTouchViewControllerForJSObject(jsobj, touch);
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_crossapp_JSTouchViewController_removeTouchViewController(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 1) {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JSObject* jsobj = args.get(0).toObjectOrNull();
        JSTouchViewController* pDelegate = JSTouchViewController::getTouchViewControllerForJSObject(jsobj);
        if (pDelegate)
        {
            JSTouchViewController::removeTouchViewControllerForJSObject(jsobj);
            pDelegate->removeFromSuperview();
        }
        
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
//JSKeypadDelegate
bool js_crossapp_addKeypadDelegate(JSContext *cx, uint32_t argc, jsval *vp){
    if(argc ==1){
         JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JSKeypadDelegate *keypadDelegate = new JSKeypadDelegate();
        JS::RootedObject jsobj(cx, args.get(0).toObjectOrNull());
        keypadDelegate->setJSObject(jsobj);
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_crossapp_removeKeypadDelegate(JSContext *cx, uint32_t argc, jsval *vp){
    if (argc == 1) {
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        JSObject* jsobj = args.get(0).toObjectOrNull();
        JSKeypadDelegate* pDelegate = JSKeypadDelegate::getJSKeypadDelegateForJSObject(jsobj);
        if (pDelegate)
        {
            JSKeypadDelegate::removeJSKeypadDelegate(jsobj);
        }
        
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

JSObject* getObjectFromNamespace(JSContext* cx, JS::HandleObject ns, const char *name) {
    JS::RootedValue out(cx);
    bool ok = true;
    if (JS_GetProperty(cx, ns, name, &out) == true) {
        JS::RootedObject obj(cx);
        ok &= JS_ValueToObject(cx, out, &obj);
        JSB_PRECONDITION2(ok, cx, NULL, "Error processing arguments");
    }
    return NULL;
}

jsval anonEvaluate(JSContext *cx, JS::HandleObject thisObj, const char* string) {
    JS::RootedValue out(cx);
    //JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    if (JS_EvaluateScript(cx, thisObj, string, (unsigned int)strlen(string), "(string)", 1, &out) == true) {
        return out.get();
    }
    return JSVAL_VOID;
}

JSCallbackWrapper::JSCallbackWrapper()
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    _jsCallback.construct(cx, JS::NullHandleValue);
    _jsThisObj.construct(cx, JS::NullHandleValue);
    _extraData.construct(cx, JS::NullHandleValue);

}

JSCallbackWrapper::~JSCallbackWrapper()
{
    _jsCallback.destroyIfConstructed();
    _jsThisObj.destroyIfConstructed();
    _extraData.destroyIfConstructed();
}

void JSCallbackWrapper::setJSCallbackFunc(JS::HandleValue func) {
    if (!func.isNullOrUndefined())
        _jsCallback.ref() = func;
}

void JSCallbackWrapper::setJSCallbackThis(JS::HandleValue thisObj) {
    if (!thisObj.isNullOrUndefined())
        _jsThisObj.ref() = thisObj;
}

void JSCallbackWrapper::setJSExtraData(JS::HandleValue data) {
    if (!data.isNullOrUndefined())
        _extraData.ref() = data;
}

const jsval JSCallbackWrapper::getJSCallbackFunc() const
{
    return _jsCallback.ref().get();
}

const jsval JSCallbackWrapper::getJSCallbackThis() const
{
    return _jsThisObj.ref().get();
}

const jsval JSCallbackWrapper::getJSExtraData() const
{
    return _extraData.ref().get();
}

JSScheduleWrapper::JSScheduleWrapper()
: _pTarget(NULL)
, _priority(0)
, _isUpdateSchedule(false)
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    _pPureJSTarget.construct(cx);
}

JSScheduleWrapper::~JSScheduleWrapper()
{
    _pPureJSTarget.destroyIfConstructed();
}

void JSScheduleWrapper::setTargetForSchedule(JS::HandleValue sched, JSScheduleWrapper *target) {
    do {
        JSObject* jsfunc = sched.toObjectOrNull();
        auto targetArray = getTargetForSchedule(sched);
        if (NULL == targetArray) {
            targetArray = new CrossApp::CAVector<CAObject*>();
            targetArray->init();
            schedFunc_proxy_t *p = (schedFunc_proxy_t *)malloc(sizeof(schedFunc_proxy_t));
            CCAssert(p, "");
            p->jsfuncObj = jsfunc;
            p->targets = targetArray;
            HASH_ADD_PTR(_schedFunc_target_ht, jsfuncObj, p);
        }

        CCAssert(!targetArray->contains(target), "The target was already added.");

        targetArray->pushBack(target);
    } while(0);
}

CrossApp::CAVector<CAObject*> * JSScheduleWrapper::getTargetForSchedule(JS::HandleValue sched) {
    schedFunc_proxy_t *t = NULL;
    JSObject *o = sched.toObjectOrNull();
    HASH_FIND_PTR(_schedFunc_target_ht, &o, t);
    return t != NULL ? t->targets : NULL;
}


void JSScheduleWrapper::setTargetForJSObject(JS::HandleObject jsTargetObj, JSScheduleWrapper *target)
{
    auto targetArray = getTargetForJSObject(jsTargetObj);
    if (NULL == targetArray) {
        targetArray = new CrossApp::CAVector<CAObject*>();
        targetArray->init();
        schedTarget_proxy_t *p = (schedTarget_proxy_t *)malloc(sizeof(schedTarget_proxy_t));
        CCAssert(p, "");
        p->jsTargetObj = jsTargetObj;
        p->targets = targetArray;
        HASH_ADD_PTR(_schedObj_target_ht, jsTargetObj, p);
    }
    
    CCAssert(!targetArray->contains(target), "The target was already added.");
    targetArray->pushBack(target);
}

CrossApp::CAVector<CAObject*> * JSScheduleWrapper::getTargetForJSObject(JS::HandleObject jsTargetObj)
{
    schedTarget_proxy_t *t = NULL;
    HASH_FIND_PTR(_schedObj_target_ht, &jsTargetObj.get(), t);
    return t != NULL ? t->targets : NULL;
}

void JSScheduleWrapper::removeAllTargets()
{
    CCLOG("removeAllTargets begin");
    dump();
    
    {
        schedFunc_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
            current->targets->clear();
            current->targets->release();
            HASH_DEL(_schedFunc_target_ht, current);
            free(current);
        }
    }
    
    {
        schedTarget_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedObj_target_ht, current, tmp) {
            current->targets->clear();
            current->targets->release();
            HASH_DEL(_schedObj_target_ht, current);
            free(current);
        }
    }
    
    dump();
    CCLOG("removeAllTargets end");
}

void JSScheduleWrapper::removeAllTargetsForMinPriority(int minPriority)
{
    CCLOG("removeAllTargetsForPriority begin");
    dump();
    
    {
        schedFunc_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
            std::vector<CAObject*> objectsNeedToBeReleased;
            auto targets = current->targets;
            CAObject* pObj = NULL;
            if(targets && targets->size() > 0)
            {
                for(int i = 0;i < targets->size(); i++)
                {
                    pObj = targets->at(i);
                    JSScheduleWrapper* wrapper = static_cast<JSScheduleWrapper*>(pObj);
                    bool isUpdateSchedule = wrapper->isUpdateSchedule();
                    if (!isUpdateSchedule || (isUpdateSchedule && wrapper->getPriority() >= minPriority))
                    {
                        objectsNeedToBeReleased.push_back(pObj);
                    }
                }
            }
            std::vector<CAObject*>::iterator iter = objectsNeedToBeReleased.begin();
            for (; iter != objectsNeedToBeReleased.end(); ++iter)
            {
                targets->eraseObject(*iter, true);
            }
            
            if (targets->size() == 0)
            {
                HASH_DEL(_schedFunc_target_ht, current);
                targets->release();
                free(current);
            }
        }
    }
    
    {
        schedTarget_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedObj_target_ht, current, tmp) {
            std::vector<CAObject*> objectsNeedToBeReleased;
            auto targets = current->targets;
            CAObject* pObj = NULL;
            if(targets && targets->size() > 0)
            {
                for(int i = 0;i < targets->size(); i++)
                {
                    pObj = targets->at(i);
                    JSScheduleWrapper* wrapper = static_cast<JSScheduleWrapper*>(pObj);
                    bool isUpdateSchedule = wrapper->isUpdateSchedule();
                    if (!isUpdateSchedule || (isUpdateSchedule && wrapper->getPriority() >= minPriority))
                    {
                        CCLOG("isUpdateSchedule2:%d", isUpdateSchedule);
                        objectsNeedToBeReleased.push_back(pObj);
                    }
                }
            }
            
            auto iter = objectsNeedToBeReleased.begin();
            for (; iter != objectsNeedToBeReleased.end(); ++iter)
            {
                targets->eraseObject(*iter, true);
            }
            
            if (targets->size() == 0)
            {
                HASH_DEL(_schedObj_target_ht, current);
                targets->release();
                free(current);
            }
        }
    }
    
    dump();
    CCLOG("removeAllTargetsForPriority end");
}

void JSScheduleWrapper::removeAllTargetsForJSObject(JS::HandleObject jsTargetObj)
{
    CCLOG("removeAllTargetsForNatiaveNode begin");
    dump();
    CAVector<CAObject*>* removeNativeTargets = NULL;
    schedTarget_proxy_t *t = NULL;
    HASH_FIND_PTR(_schedObj_target_ht, &jsTargetObj.get(), t);
    if (t != NULL) {
        removeNativeTargets = t->targets;
        HASH_DEL(_schedObj_target_ht, t);
    }

    if (removeNativeTargets == NULL) return;

    schedFunc_proxy_t *current, *tmp;
    HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
        std::vector<CAObject*> objectsNeedToBeReleased;
        auto targets = current->targets;
        CAObject* pObj = NULL;
//        CCARRAY_FOREACH(targets, pObj)
        if(targets && targets->size() > 0)
        {
            for(int i = 0;i < targets->size(); i++)
            {
                pObj = targets->at(i);
                if (removeNativeTargets->contains(pObj))
                {
                    objectsNeedToBeReleased.push_back(pObj);
                }
            }
        }
        auto iter = objectsNeedToBeReleased.begin();
        for (; iter != objectsNeedToBeReleased.end(); ++iter)
        {
            targets->eraseObject(*iter, true);
        }

        if (targets->size() == 0)
        {
            HASH_DEL(_schedFunc_target_ht, current);
            targets->release();
            free(current);
        }  
    }

    removeNativeTargets->clear();
    removeNativeTargets->release();
    free(t);
    dump();
    CCLOG("removeAllTargetsForNatiaveNode end");
}

void JSScheduleWrapper::removeTargetForJSObject(JS::HandleObject jsTargetObj, JSScheduleWrapper* target)
{
    CCLOG("removeTargetForJSObject begin");
    dump();
    schedTarget_proxy_t *t = NULL;
    HASH_FIND_PTR(_schedObj_target_ht, &jsTargetObj.get(), t);
    if (t != NULL) {
        t->targets->eraseObject(target);
        if (t->targets->size() == 0)
        {
            t->targets->release();
            HASH_DEL(_schedObj_target_ht, t);
            free(t);
        }
    }

    schedFunc_proxy_t *current, *tmp, *removed=NULL;

    HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
        auto targets = current->targets;
        CAObject* pObj = NULL;
        
//        CCARRAY_FOREACH(targets, pObj)
        if(targets && targets->size() > 0)
        {
            for(int i = 0;i < targets->size(); i++)
            {
                pObj = targets->at(i);
                JSScheduleWrapper* pOneTarget = static_cast<JSScheduleWrapper*>(pObj);
                if (pOneTarget == target)
                {
                    removed = current;
                    break;
                }
            }
        }
        if (removed) break;
    }

    if (removed)
    {
        removed->targets->eraseObject(target);
        if (removed->targets->size() == 0)
        {
            removed->targets->release();
            HASH_DEL(_schedFunc_target_ht, removed);
            free(removed);
        }  
    }
    dump();
    CCLOG("removeTargetForJSObject end");
}

void JSScheduleWrapper::dump()
{
#if COCOS2D_DEBUG > 1
    CCLOG("\n---------JSScheduleWrapper dump begin--------------\n");
    CCLOG("target hash count = %d, func hash count = %d", HASH_COUNT(_schedObj_target_ht), HASH_COUNT(_schedFunc_target_ht));
    schedTarget_proxy_t *current, *tmp;
    int nativeTargetsCount = 0;
    HASH_ITER(hh, _schedObj_target_ht, current, tmp) {
        Ref* pObj = NULL;
        CCARRAY_FOREACH(current->targets, pObj)
        {
            CCLOG("js target ( %p ), native target[%d]=( %p )", current->jsTargetObj, nativeTargetsCount, pObj);
            nativeTargetsCount++;
        }
    }

    CCLOG("\n-----------------------------\n");

    schedFunc_proxy_t *current_func, *tmp_func;
    int jsfuncTargetCount = 0;
    HASH_ITER(hh, _schedFunc_target_ht, current_func, tmp_func) {
        Ref* pObj = NULL;
        CCARRAY_FOREACH(current_func->targets, pObj)
        {
            CCLOG("js func ( %p ), native target[%d]=( %p )", current_func->jsfuncObj, jsfuncTargetCount, pObj);
            jsfuncTargetCount++;
        }
    }
    CCAssert(nativeTargetsCount == jsfuncTargetCount, "nativeTargetsCount should be equal to jsfuncTargetCount.");
    CCLOG("\n---------JSScheduleWrapper dump end--------------\n");
#endif
}

void JSScheduleWrapper::scheduleFunc(float dt)
{
    jsval data = DOUBLE_TO_JSVAL(dt);

    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET

    JS::RootedValue callback(cx, getJSCallbackFunc());
    if(!callback.isNullOrUndefined()) {
        JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(1, &data);
        JS::RootedValue retval(cx);
        JS::RootedObject callbackTarget(cx, getJSCallbackThis().toObjectOrNull());
        JS_CallFunctionValue(cx, callbackTarget, callback, args, &retval);
    }
}

void JSScheduleWrapper::update(float dt)
{
    jsval data = DOUBLE_TO_JSVAL(dt);
    
    ScriptingCore::getInstance()->executeFunctionWithOwner(getJSCallbackThis(), "update", 1, &data);
}

CAObject* JSScheduleWrapper::getTarget()
{
    return _pTarget;
}

void JSScheduleWrapper::setTarget(CAObject* pTarget)
{
    _pTarget = pTarget;
}

void JSScheduleWrapper::setPureJSTarget(JS::HandleObject pPureJSTarget)
{
    _pPureJSTarget.ref() = pPureJSTarget;
}

JSObject* JSScheduleWrapper::getPureJSTarget()
{
    return _pPureJSTarget.ref().get();
}

void JSScheduleWrapper::setPriority(int priority)
{
    _priority = priority;
}

int  JSScheduleWrapper::getPriority()
{
    return _priority;
}

void JSScheduleWrapper::setUpdateSchedule(bool isUpdateSchedule)
{
    _isUpdateSchedule = isUpdateSchedule;
}

bool JSScheduleWrapper::isUpdateSchedule()
{
    return _isUpdateSchedule;
}

//JSTouchView
JSTouchView::TouchViewMap JSTouchView::sTouchViewMap;


JSTouchView::JSTouchView()
{
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    _obj.construct(cx);
}
JSTouchView::~JSTouchView()
{
    CCLOG("In the destructor of JSTouchView.");
    _obj.destroyIfConstructed();
}
void JSTouchView::setTouchViewForJSObject(JSObject* pJSObj, JSTouchView* pTouchView)
{
    CCAssert(sTouchViewMap.find(pJSObj) == sTouchViewMap.end(),
             "pJSObj can't be found in sTouchViewMap.");
    sTouchViewMap.insert(TouchViewPair(pJSObj, pTouchView));
}

JSTouchView* JSTouchView::getTouchViewForJSObject(JSObject* pJSObj)
{
    JSTouchView* pRet = NULL;
    TouchViewMap::iterator iter = sTouchViewMap.find(pJSObj);
    if (iter != sTouchViewMap.end())
    {
        pRet = iter->second;
    }
    return pRet;
}

void JSTouchView::removeTouchViewForJSObject(JSObject* pJSObj)
{
    TouchViewMap::iterator iter = sTouchViewMap.find(pJSObj);
    CCAssert(iter != sTouchViewMap.end(), "pJSObj can't be found in sTouchViewMap!");
    sTouchViewMap.erase(pJSObj);
}
void JSTouchView::setJSObject(JS::HandleObject obj)
{
    _obj.ref() = obj;
    
    CrossApp::CAView* arg1 = nullptr;
    js_proxy_t *jsProxy;
    jsProxy = jsb_get_js_proxy(obj);
    arg1 = (CrossApp::CAView*)(jsProxy ? jsProxy->ptr : NULL);
    CAView* superView =arg1->getSuperview();

    CCAssert( superView != NULL, "superview must be non-nil");
    superView->insertSubview(this,superView->getZOrder());
}

DRect JSTouchView::getBounds() const{

    auto cx = ScriptingCore::getInstance()->getGlobalContext();
     JS::RootedValue jsBounds(cx);

    CrossApp::CAView* arg1 = nullptr;
    js_proxy_t *jsProxy;
    jsProxy = jsb_get_js_proxy(_obj.ref());
    arg1 = (CrossApp::CAView*)(jsProxy ? jsProxy->ptr : NULL);
    
    CCAssert(arg1!= NULL,"CAView must be non-nil");

    return arg1->getBounds();

}
bool JSTouchView::ccTouchBegan(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    
    CC_UNUSED_PARAM(event);
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue retval(cx);
    bool bRet = false;
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHBEGAN, touch, _obj.ref(), &retval);
    
    if(retval.isBoolean())
    {
        bRet = retval.toBoolean();
    }
    
    return bRet;
}
void JSTouchView::ccTouchMoved(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHMOVED, touch, _obj.ref());
}
void JSTouchView::ccTouchEnded(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHENDED, touch, _obj.ref());
}
void JSTouchView::ccTouchCancelled(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHCANCELLED, touch, _obj.ref());
}

//JSTouchViewController
JSTouchViewController::TouchViewControllerMap JSTouchViewController::sTouchViewControllerMap;

JSTouchViewController::JSTouchViewController(){
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    _obj.construct(cx);
}
JSTouchViewController::~JSTouchViewController(){
    CCLOG("In the destructor of JSTouchViewController.");
    _obj.destroyIfConstructed();
}

void JSTouchViewController::setTouchViewControllerForJSObject(JSObject* pJSObj, JSTouchViewController* pTouchView){
    CCAssert(sTouchViewControllerMap.find(pJSObj) == sTouchViewControllerMap.end(),
             "pJSObj can't be found in sTouchViewControllerMap.");
    sTouchViewControllerMap.insert(TouchViewControllerPair(pJSObj, pTouchView));
}

JSTouchViewController* JSTouchViewController::getTouchViewControllerForJSObject(JSObject* pJSObj){
    JSTouchViewController* pRet = NULL;
    TouchViewControllerMap::iterator iter = sTouchViewControllerMap.find(pJSObj);
    if (iter != sTouchViewControllerMap.end())
    {
        pRet = iter->second;
    }
    return pRet;
}

void JSTouchViewController::removeTouchViewControllerForJSObject(JSObject* pJSObj){
    TouchViewControllerMap::iterator iter = sTouchViewControllerMap.find(pJSObj);
    CCAssert(iter != sTouchViewControllerMap.end(), "pJSObj can't be found in sTouchViewControllerMap!");
    sTouchViewControllerMap.erase(pJSObj);
}

void JSTouchViewController::setJSObject(JS::HandleObject obj){
    _obj.ref() = obj;
    
    CrossApp::CAViewController* arg1 = nullptr;
    js_proxy_t *jsProxy;
    jsProxy = jsb_get_js_proxy(obj);
    arg1 = (CrossApp::CAViewController*)(jsProxy ? jsProxy->ptr : NULL);
    CCAssert( arg1 != NULL, "CATouchViewController must be non-nil");
    
    CrossApp::CAView* view  = arg1->getView();
    CrossApp::CAView* superView = view->getSuperview();
    superView->insertSubview(this,superView->getZOrder());
    
}
DRect JSTouchViewController::getBounds() const{
    
    CrossApp::CAViewController* arg1 = nullptr;
    js_proxy_t *jsProxy;
    jsProxy = jsb_get_js_proxy(_obj.ref());
    arg1 = (CrossApp::CAViewController*)(jsProxy ? jsProxy->ptr : NULL);
    CCAssert( arg1 != NULL, "CATouchViewController must be non-nil");
    
    CrossApp::CAView* view  = arg1->getView();
    
    return view->getBounds();
    
}

bool JSTouchViewController::ccTouchBegan(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue retval(cx);
    bool bRet = false;
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHBEGAN, touch, _obj.ref(), &retval);
    
    if(retval.isBoolean())
    {
        bRet = retval.toBoolean();
    }
    
    return bRet;
}
void JSTouchViewController::ccTouchMoved(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHMOVED, touch, _obj.ref());
}
void JSTouchViewController::ccTouchEnded(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHENDED, touch, _obj.ref());
}
void JSTouchViewController::ccTouchCancelled(CrossApp::CATouch *touch, CrossApp::CAEvent *event){
    CC_UNUSED_PARAM(event);
    ScriptingCore::getInstance()->executeCustomTouchEvent(CCTOUCHCANCELLED, touch, _obj.ref());
}

//JSKeypadDelegate
JSKeypadDelegate::JSKeypadDelegateMap JSKeypadDelegate::sJSKeypadDelegateMap;

JSKeypadDelegate::JSKeypadDelegate(){
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    _obj.construct(cx);
}
JSKeypadDelegate::~JSKeypadDelegate(){
    CCLOG("In the destructor of ~JSKeypadDelegate.");
    _obj.destroyIfConstructed();
}

void JSKeypadDelegate::setJSKeypadDelegateForJSObject(JSObject* pJSObj, JSKeypadDelegate* pTouchView){
    CCAssert(sJSKeypadDelegateMap.find(pJSObj) == sJSKeypadDelegateMap.end(),
             "pJSObj can't be found in sTouchViewControllerMap.");
    sJSKeypadDelegateMap.insert(JSKeypadDelegatePair(pJSObj, pTouchView));
}

JSKeypadDelegate* JSKeypadDelegate::getJSKeypadDelegateForJSObject(JSObject* pJSObj){
    JSKeypadDelegate* pRet = NULL;
    JSKeypadDelegateMap::iterator iter = sJSKeypadDelegateMap.find(pJSObj);
    if (iter != sJSKeypadDelegateMap.end())
    {
        pRet = iter->second;
    }
    return pRet;
}

void JSKeypadDelegate::removeJSKeypadDelegate(JSObject* pJSObj){
    JSKeypadDelegateMap::iterator iter = sJSKeypadDelegateMap.find(pJSObj);
    CCAssert(iter != sJSKeypadDelegateMap.end(), "pJSObj can't be found in sJSKeypadDelegateMap!");
    sJSKeypadDelegateMap.erase(pJSObj);
}

void JSKeypadDelegate::setJSObject(JS::HandleObject obj){
    _obj.ref() = obj;
}

void JSKeypadDelegate::keyBackClicked() {
    ScriptingCore::getInstance()->executeCustomKeyBackClicked( _obj.ref());
}

void JSKeypadDelegate::keyMenuClicked() {
     ScriptingCore::getInstance()->executeCustomKeyMenuClicked(_obj.ref());
}

bool js_crossapp_CASlider_addTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CASlider* cobj = (CrossApp::CASlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASlider_addTarget : Invalid Native Object");
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsvalue(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CASlider_addTarget : Error processing arguments");
        
        auto function = [&jsobj,&jsvalue](float value)
        {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            
            JSContext* jscontext = ScriptingCore::getInstance()->getGlobalContext();
            JS::RootedValue outval(jscontext);
            jsval jsret[1];
            jsret[0] = int32_to_jsval(jscontext,int(value));
            JS::RootedValue callback(jscontext, jsvalue.get());
            
            if(!callback.isNullOrUndefined()) {
                JS::RootedObject thisObj(jscontext, jsobj.get().toObjectOrNull());
                JS_CallFunctionValue(jscontext,thisObj,callback, JS::HandleValueArray::fromMarkedLocation(1, jsret), &outval);
            }
        };
        cobj->setTarget(function);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASlider_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_crossapp_CAStepper_addTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAStepper* cobj = (CrossApp::CAStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CAStepper_addTarget : Invalid Native Object");
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAStepper_addTarget : Error processing arguments");

        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAStepper_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_crossapp_CASwitch_addTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CASwitch* cobj = (CrossApp::CASwitch *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASwitch_addTarget : Invalid Native Object");
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CASwitch_addTarget : Error processing arguments");

        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASwitch_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_crossapp_CAPageControl_addTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAPageControl* cobj = (CrossApp::CAPageControl *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CAPageControl_addTarget : Invalid Native Object");
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAPageControl_addTarget : Error processing arguments");

        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAPageControl_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_crossapp_CASegmentedControl_addTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CASegmentedControl* cobj = (CrossApp::CASegmentedControl *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASegmentedControl_addTarget : Invalid Native Object");
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAButton_addTarget : Error processing arguments");

        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASegmentedControl_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}


bool js_crossapp_CABarButtonItem_setTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CABarButtonItem* cobj = (CrossApp::CABarButtonItem *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CABarButtonItem_setTarget : Invalid Native Object");
    
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CABarButtonItem_setTarget : Error processing arguments");

        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CABarButtonItem_setTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
    
}

bool js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2 : Error processing arguments");

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2 : wrong number of arguments");
    return false;
}

bool js_crossapp_CAScheduler_unscheduleAllSelectorsForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAScheduler* cobj = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 1) {
        do {
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            
            CrossApp::CAVector<CAObject*> *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            // If there aren't any targets, just return true.
            // Otherwise, the for loop will break immediately.
            // It will lead to logic errors.
            // For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
            if(! arr) return true;
            
            JSScheduleWrapper* wrapper = NULL;
            for(ssize_t i = 0; i < arr->size(); ++i) {
                wrapper = (JSScheduleWrapper*)arr->at(i);
                if(wrapper) {
                    cobj->unscheduleAllForTarget(wrapper);
                }
            }
            JSScheduleWrapper::removeAllTargetsForJSObject(tmpObj);
            
        } while (0);
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_CAScheduler_scheduleCallbackForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc >= 2) {
        bool ok = true;
        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
        
        JS::RootedObject obj(cx);
        obj = args.thisv().toObjectOrNull();
        js_proxy_t *proxy = jsb_get_js_proxy(obj);
        CrossApp::CAScheduler *sched = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
        
        JSScheduleWrapper *tmpCObj = NULL;
        
        JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
        proxy = jsb_get_js_proxy(tmpObj);
        bool isPureJSTarget = proxy ? false : true;
        
        double interval = 0;
        if( argc >= 3 ) {
            ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(2)), &interval );
        }
        
        //
        // repeat
        //
        double repeat = kCCRepeatForever;
        if( argc >= 4 ) {
            ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(3)), &repeat );
        }
        
        //
        // delay
        //
        double delay = 0;
        if( argc >= 5 ) {
            ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(4)), &delay );
        }
        
        bool paused = false;
        
        if( argc >= 6 ) {
            paused = JS::ToBoolean(JS::RootedValue(cx,  args.get(5)));
        }
        
        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
        
        bool bFound = false;
        auto pTargetArr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
        CAObject* pObj = NULL;
        if(pTargetArr && pTargetArr->size() > 0)
        {
            for(int i = 0;i < pTargetArr->size(); i++)
            {
                pObj = pTargetArr->at(i);
                JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
                if (args.get(1) == pTarget->getJSCallbackFunc())
                {
                    tmpCObj = pTarget;
                    bFound = true;
                    break;
                }
            }
        }
        
        if (!bFound)
        {
            tmpCObj = new JSScheduleWrapper();
            tmpCObj->autorelease();
            tmpCObj->setJSCallbackThis(args.get(0));
            tmpCObj->setJSCallbackFunc(args.get(1));
            if (isPureJSTarget) {
                tmpCObj->setPureJSTarget(tmpObj);
            }
            
            JSScheduleWrapper::setTargetForSchedule(args.get(1), tmpCObj);
            JSScheduleWrapper::setTargetForJSObject(tmpObj, tmpCObj);
        }
        
        CAScheduler::getScheduler()->schedule(schedule_selector(JSScheduleWrapper::scheduleFunc), tmpCObj, interval, repeat, delay, paused);
        
        args.rval().setUndefined();
        
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

bool js_CAScheduler_unscheduleCallbackForTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAScheduler* cobj = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
    TEST_NATIVE_OBJECT(cx, cobj)
    
    if (argc == 2) {
        do {
   
                JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
                
                CrossApp::CAVector<CAObject*> *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
                // If there aren't any targets, just return true.
                // Otherwise, the for loop will break immediately.
                // It will lead to logic errors.
                // For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
                if(! arr) return true;
                
                JSScheduleWrapper* wrapper = NULL;
                for(ssize_t i = 0; i < arr->size(); ++i) {
                    wrapper = (JSScheduleWrapper*)arr->at(i);
                    if(wrapper && wrapper->getJSCallbackFunc() == args.get(1)) {
                        cobj->unschedule(schedule_selector(JSScheduleWrapper::scheduleFunc), wrapper);
                        JSScheduleWrapper::removeTargetForJSObject(tmpObj, wrapper);
                        break;
                    }
                
            }
        } while (0);
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_forceGC(JSContext *cx, uint32_t argc, jsval *vp) {
    JSRuntime *rt = JS_GetRuntime(cx);
    JS_GC(rt);
    return true;
}

bool js_crossapp_retain(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAObject* cobj = (CrossApp::CAObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_retain : Invalid Native Object");
    
    cobj->retain();
    args.rval().setUndefined();
    return true;
}

bool js_crossapp_release(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAObject* cobj = (CrossApp::CAObject *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_release : Invalid Native Object");
    
    cobj->release();
    args.rval().setUndefined();
    return true;
}

bool js_crossapp_Node_onEnter(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAView* cobj = (CrossApp::CAView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_onEnter : Invalid Native Object");
    
    ScriptingCore::getInstance()->setCalledFromScript(true);
    cobj->onEnter();
    args.rval().setUndefined();
    return true;
}

bool js_crossapp_Node_onExit(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAView* cobj = (CrossApp::CAView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_onExit : Invalid Native Object");
    
    ScriptingCore::getInstance()->setCalledFromScript(true);
    cobj->onExit();
    args.rval().setUndefined();
    return true;
}

bool js_crossapp_Node_onEnterTransitionDidFinish(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAView* cobj = (CrossApp::CAView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_onEnterTransitionDidFinish : Invalid Native Object");
    
    ScriptingCore::getInstance()->setCalledFromScript(true);
    cobj->onEnterTransitionDidFinish();
    args.rval().setUndefined();
    return true;
}

bool js_crossapp_Node_onExitTransitionDidStart(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAView* cobj = (CrossApp::CAView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_onExitTransitionDidStart : Invalid Native Object");
    
    ScriptingCore::getInstance()->setCalledFromScript(true);
    cobj->onExitTransitionDidStart();
    args.rval().setUndefined();
    return true;
}

// console.log("Message");
bool js_console_log(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        std::string msg;
        bool ok = jsval_to_std_string(cx, args.get(0), &msg);
        JSB_PRECONDITION2(ok, cx, false, "js_console_log : Error processing arguments");
        
        CCLog("%s", msg.c_str());
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_console_log : wrong number of arguments");
    return false;
}

void get_or_create_js_obj(JSContext* cx, JS::HandleObject obj, const std::string &name, JS::MutableHandleObject jsObj)
{
    JS::RootedValue nsval(cx);
    JS_GetProperty(cx, obj, name.c_str(), &nsval);
    if (nsval == JSVAL_VOID) {
        jsObj.set(JS_NewObject(cx, NULL, JS::NullPtr(), JS::NullPtr()));
        nsval = OBJECT_TO_JSVAL(jsObj);
        JS_SetProperty(cx, obj, name.c_str(), nsval);
    } else {
        jsObj.set(nsval.toObjectOrNull());
    }
}

void register_crossapp_js_core(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    JS::RootedObject jsbObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "ca", &ccObj);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    
    tmpObj.set(jsb_CrossApp_CAView_prototype);
    JS_DefineFunction(cx, tmpObj, "onEnter", js_crossapp_Node_onEnter, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "onExit", js_crossapp_Node_onExit, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "onEnterTransitionDidFinish", js_crossapp_Node_onEnterTransitionDidFinish, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "onExitTransitionDidStart", js_crossapp_Node_onExitTransitionDidStart, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CAScheduler_prototype);
    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "schedule", js_CAScheduler_scheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "scheduleCallbackForTarget", js_CAScheduler_scheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unschedule", js_CAScheduler_unscheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unscheduleCallbackForTarget", js_CAScheduler_unscheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unscheduleAllForTarget", js_crossapp_CAScheduler_unscheduleAllSelectorsForTarget, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CAButton_prototype);
    tmpObj.set(jsb_CrossApp_CASlider_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CASlider_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CAStepper_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CAStepper_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CASwitch_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CASwitch_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CAPageControl_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CAPageControl_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CASegmentedControl_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CASegmentedControl_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj.set(jsb_CrossApp_CAAlertView_prototype);
    tmpObj.set(jsb_CrossApp_CABarButtonItem_prototype);
    JS_DefineFunction(cx, tmpObj, "setTarget", js_crossapp_CABarButtonItem_setTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_GetProperty(cx, ccObj, "CAViewAnimation", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "setAnimationWillStartSelector_2", js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "addTouchView", js_crossapp_JSTouchView_addTouchView, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeTouchView", js_crossapp_JSTouchView_removeTouchView, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, ccObj, "addTouchViewController", js_crossapp_JSTouchViewController_addTouchViewController, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeTouchViewController", js_crossapp_JSTouchViewController_removeTouchViewController, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, ccObj, "addKeypadDelegate", js_crossapp_addKeypadDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeKeypadDelegate", js_crossapp_removeKeypadDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    get_or_create_js_obj(cx, global, "console", &tmpObj);
    JS_DefineFunction(cx, tmpObj, "log", js_console_log, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, global, "garbageCollect", js_forceGC, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
#if CC_ENABLE_BULLET_INTEGRATION && CC_USE_3D_PHYSICS
    tmpObj.set(jsb_cocos2d_Scene_prototype);
    JS_DefineFunction(cx, tmpObj, "setPhysics3DDebugCamera", js_crossapp_Scene_setPhysics3DDebugCamera, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "initWithPhysics", js_crossapp_Scene_initWithPhysics, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "getPhysics3DWorld", js_crossapp_Scene_getPhysics3DWorld, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
#endif //CC_ENABLE_BULLET_INTEGRATION && CC_USE_3D_PHYSICS

#if CC_USE_NAVMESH
	tmpObj.set(jsb_cocos2d_Scene_prototype);
	JS_DefineFunction(cx, tmpObj, "getNavMesh", js_crossapp_Scene_getNavMesh, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, tmpObj, "setNavMeshDebugCamera", js_crossapp_Scene_setNavMeshDebugCamera, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, tmpObj, "setNavMesh", js_crossapp_Scene_setNavMesh, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
#endif //CC_USE_NAVMESH
}


