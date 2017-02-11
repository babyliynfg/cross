/*
 * Copyright (c) 2012 Zynga Inc.
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
    CCLOGINFO("In the destructor of JSTouchDelegate.");
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

// cc.CallFunc.create( func, this, [data])
// cc.CallFunc.create( func )
//static bool js_callFunc(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    if (argc >= 1 && argc <= 3) {
//        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//
//        std::shared_ptr<JSCallbackWrapper> tmpCobj(new JSCallbackWrapper());
//        
//        JS::RootedValue callback(cx, args.get(0));
//        tmpCobj->setJSCallbackFunc(callback);
//        if(argc >= 2) {
//            JS::RootedValue thisObj(cx, args.get(1));
//            tmpCobj->setJSCallbackThis(thisObj);
//        }
//        if(argc >= 3) {
//            JS::RootedValue data(cx, args.get(2));
//            tmpCobj->setJSExtraData(data);
//        }
//        
//        CallFuncN *ret = CallFuncN::create([=](Node* sender){
//            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
//            
//            JS::RootedValue jsvalThis(cx, tmpCobj->getJSCallbackThis());
//            JS::RootedObject thisObj(cx, jsvalThis.toObjectOrNull());
//            JS::RootedValue jsvalCallback(cx, tmpCobj->getJSCallbackFunc());
//            JS::RootedValue jsvalExtraData(cx, tmpCobj->getJSExtraData());
//            
//            JS::RootedValue senderVal(cx);
//            if (sender)
//            {
//                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Node>(cx, sender);
//                senderVal.set(OBJECT_TO_JSVAL(proxy->obj));
//            }
//            else
//            {
//                senderVal.set(JS::NullValue());
//            }
//            
//            if (!jsvalCallback.isNullOrUndefined())
//            {
//                JS::RootedValue retval(cx);
//                
//                jsval valArr[2];
//                valArr[0] = senderVal;
//                valArr[1] = jsvalExtraData;
//
//                JS::HandleValueArray callArgs = JS::HandleValueArray::fromMarkedLocation(2, valArr);
//                JS_CallFunctionValue(cx, thisObj, jsvalCallback, callArgs, &retval);
//            }
//        });
//        
//        js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::CallFunc>(cx, ret);
//        args.rval().set(OBJECT_TO_JSVAL(proxy->obj));
//        
//        return true;
//    }
//    JS_ReportError(cx, "Invalid number of arguments");
//    return false;
//}

// callFunc.initWithFunction( func, this, [data])
// callFunc.initWithFunction( func )
//bool js_crossapp_CallFunc_initWithFunction(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    if (argc >= 1 && argc <= 3) {
//        JSObject *obj = JS_THIS_OBJECT(cx, vp);
//        js_proxy_t *proxy = jsb_get_js_proxy(obj);
//        CallFuncN *action = (cocos2d::CallFuncN *)(proxy ? proxy->ptr : NULL);
//        JSB_PRECONDITION2(action, cx, false, "Invalid Native Object");
//        
//        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//
//        std::shared_ptr<JSCallbackWrapper> tmpCobj(new JSCallbackWrapper());
//    
//        JS::RootedValue callback(cx, args.get(0));
//        tmpCobj->setJSCallbackFunc(callback);
//        if(argc >= 2) {
//            JS::RootedValue thisObj(cx, args.get(1));
//            tmpCobj->setJSCallbackThis(thisObj);
//        }
//        if(argc >= 3) {
//            JS::RootedValue data(cx, args.get(2));
//            tmpCobj->setJSExtraData(data);
//        }
//        
//        action->initWithFunction([=](Node* sender){
//            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
//            
//            JS::RootedValue jsvalThis(cx, tmpCobj->getJSCallbackThis());
//            JS::RootedObject thisObj(cx, jsvalThis.toObjectOrNull());
//            JS::RootedValue jsvalCallback(cx, tmpCobj->getJSCallbackFunc());
//            JS::RootedValue jsvalExtraData(cx, tmpCobj->getJSExtraData());
//            
//            JS::RootedValue senderVal(cx);
//            if (sender)
//            {
//                js_proxy_t *senderProxy = js_get_or_create_proxy<cocos2d::Node>(cx, sender);
//                senderVal.set(OBJECT_TO_JSVAL(senderProxy->obj));
//            }
//            else
//            {
//                senderVal.set(JS::NullValue());
//            }
//            
//            if (!jsvalCallback.isNullOrUndefined())
//            {
//                JS::RootedValue retval(cx);
//                
//                jsval valArr[2];
//                valArr[0] = senderVal;
//                valArr[1] = jsvalExtraData;
//                
//                JS::HandleValueArray callArgs = JS::HandleValueArray::fromMarkedLocation(2, valArr);
//                JS_CallFunctionValue(cx, thisObj, jsvalCallback, callArgs, &retval);
//            }
//        });
//        return true;
//    }
//    JS_ReportError(cx, "Invalid number of arguments");
//    return false;
//}

JSControlCallback::JSControlCallback()
{
    auto cx = ScriptingCore::getInstance()->getGlobalContext();
    _obj.construct(cx,JS::NullHandleValue);
    _jsCallback.construct(cx, JS::NullHandleValue);
    
};
JSControlCallback::~JSControlCallback()
{
    CCLOGINFO("In the destructor of JSControlCallback.");
    _obj.destroyIfConstructed();
    _jsCallback.destroyIfConstructed();
}

SEL_CAControl JSControlCallback::getTarget(JS::HandleValue obj,JS::HandleValue fun)
{
    _obj.ref() = obj;
    _jsCallback.ref() = fun;
    
    return CAControl_selector(JSControlCallback::callbackJSFun);
}

 SEL_CAAlertBtnEvent JSControlCallback::getAlertViewTarger(JS::HandleValue obj,JS::HandleValue fun)
{
    _obj.ref() = obj;
    _jsCallback.ref() = fun;
    
    return CAAlertView_selector(JSControlCallback::callAlertViewTarget);
}

SEL_CASegmentedControl JSControlCallback::getCASegmentedTarget(JS::HandleValue obj,JS::HandleValue fun)
{
    _obj.ref() = obj;
    _jsCallback.ref() = fun;
        return CASegmentedControl_selector(JSControlCallback::callbackJSSegmented);
}

SEL_CAViewAnimation0 JSControlCallback::getViewAnimation0(JS::HandleValue obj,JS::HandleValue fun)
{
    _obj.ref() = obj;
    _jsCallback.ref() = fun;
    return CAViewAnimation0_selector(JSControlCallback::callbackJSViewAnimation0);
}


SEL_CAViewAnimation2 JSControlCallback::getViewAnimation2(JS::HandleValue obj,JS::HandleValue fun)
{
    _obj.ref() = obj;
    _jsCallback.ref() = fun;
    return CAViewAnimation2_selector(JSControlCallback::callbackJSViewAnimation2);
}

void JSControlCallback::callbackJSFun(CAControl* control, DPoint point)
{
     JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue outval(cx);
    js_proxy_t * p = jsb_get_native_proxy(control);
    jsval args[2];
    if(p){
        args[0] = OBJECT_TO_JSVAL(p->obj);
    }
    args[1] = dpoint_to_jsval(cx, point);
    
    
    JS::RootedValue callback(cx, _jsCallback.ref().get());
    
    if(!callback.isNullOrUndefined()) {
        JS::RootedObject thisObj(cx, _obj.ref().get().toObjectOrNull());
        JS_CallFunctionValue(cx,thisObj,callback, JS::HandleValueArray::fromMarkedLocation(2, args), &outval);
    }
}

void JSControlCallback::callbackJSSegmented(CASegmentedControl* control, int index)
{
    
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue outval(cx);
    js_proxy_t * p = jsb_get_native_proxy(control);
    jsval args[2];
    args[0] = OBJECT_TO_JSVAL(p->obj);
    args[1] = INT_TO_JSVAL(index);
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    JS::RootedValue callback(cx, _jsCallback.ref().get());
    
    if(!callback.isNullOrUndefined()) {
        JS::RootedObject thisObj(cx, _obj.ref().get().toObjectOrNull());
        JS_CallFunctionValue(cx,thisObj,callback, JS::HandleValueArray::fromMarkedLocation(2, args), &outval);
    }

}

void JSControlCallback::callbackJSViewAnimation0()
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue outval(cx);
    
     JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    JS::RootedValue callback(cx, _jsCallback.ref().get());
    
    if(!callback.isNullOrUndefined()) {
        JS::RootedObject thisObj(cx, _obj.ref().get().toObjectOrNull());
        JS_CallFunctionValue(cx,thisObj,callback, JS::HandleValueArray::fromMarkedLocation(0, NULL), &outval);
    }
}

void JSControlCallback::callbackJSViewAnimation2(const std::string& id, void* v)
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue outval(cx);
    jsval args[2];
    args[0] = std_string_to_jsval(cx, id);
 // args[1] = getJSObject(cx, v);
    args[1] = JSVAL_NULL;
    
     JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    JS::RootedValue callback(cx, _jsCallback.ref().get());
    
    if(!callback.isNullOrUndefined()) {
        JS::RootedObject thisObj(cx, _obj.ref().get().toObjectOrNull());
        JS_CallFunctionValue(cx,thisObj,callback, JS::HandleValueArray::fromMarkedLocation(2, args), &outval);
    }
}

void JSControlCallback::callAlertViewTarget(int index)
{
    JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedValue outval(cx);
    jsval arg = INT_TO_JSVAL(index);

    JS::RootedValue callback(cx, _jsCallback.ref().get());
    
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    
    if(!callback.isNullOrUndefined()) {
        JS::RootedObject thisObj(cx, _obj.ref().get().toObjectOrNull());
        JS_CallFunctionValue(cx,thisObj,callback, JS::HandleValueArray::fromMarkedLocation(1, &arg), &outval);
    }
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
            assert(p);
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
        assert(p);
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
    CCLOGINFO("removeAllTargets begin");
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
    CCLOGINFO("removeAllTargets end");
}

void JSScheduleWrapper::removeAllTargetsForMinPriority(int minPriority)
{
    CCLOGINFO("removeAllTargetsForPriority begin");
    dump();
    
    {
        schedFunc_proxy_t *current, *tmp;
        HASH_ITER(hh, _schedFunc_target_ht, current, tmp) {
            std::vector<CAObject*> objectsNeedToBeReleased;
            auto targets = current->targets;
            CAObject* pObj = NULL;
//            CCARRAY_FOREACH(targets, pObj)
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
//            CCARRAY_FOREACH(targets, pObj)
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
    CCLOGINFO("removeAllTargetsForPriority end");
}

void JSScheduleWrapper::removeAllTargetsForJSObject(JS::HandleObject jsTargetObj)
{
    CCLOGINFO("removeAllTargetsForNatiaveNode begin");
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
    CCLOGINFO("removeAllTargetsForNatiaveNode end");
}

void JSScheduleWrapper::removeTargetForJSObject(JS::HandleObject jsTargetObj, JSScheduleWrapper* target)
{
    CCLOGINFO("removeTargetForJSObject begin");
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
    CCLOGINFO("removeTargetForJSObject end");
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
    CCLOGINFO("In the destructor of JSTouchView.");
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
    CCLOGINFO("In the destructor of JSTouchViewController.");
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
    CCLOGINFO("In the destructor of ~JSKeypadDelegate.");
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

////mouse
//void JSTouchView::mouseMoved(CATouch* pTouch, CAEvent* pEvent){
//     CC_UNUSED_PARAM(pEvent);
//}
//void JSTouchView::mouseMovedOutSide(CATouch* pTouch, CAEvent* pEvent)
//{
//     CC_UNUSED_PARAM(pEvent);
//}
//void JSTouchView::mouseScrollWheel(CATouch* pTouch, float off_x, float off_y, CAEvent* pEvent)
//{
//     CC_UNUSED_PARAM(pEvent);
//}



bool js_crossapp_CAButton_addTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAButton* cobj = (CrossApp::CAButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CAButton_addTarget : Invalid Native Object");
    if (argc == 3) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        CrossApp::CAControlEvents arg0;
        
        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg0);
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAButton_addTarget : Error processing arguments");
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->addTarget(callback, callback->getTarget(jsobj, jsval), arg0);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAButton_addTarget : wrong number of arguments: %d, was expecting %d", argc, 3);
    return false;
}

bool js_crossapp_CAButton_removeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAButton* cobj = (CrossApp::CAButton *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CAButton_removeTarget : Invalid Native Object");
    if (argc == 3) {
        
        CrossApp::CAControlEvents arg0;
        
        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg0);
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAButton_removeTarget : Error processing arguments");
        
        cobj->removeTarget(NULL, NULL, arg0);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAButton_removeTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
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
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CASlider_addTarget : Error processing arguments");
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->addTarget(callback, callback->getTarget(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASlider_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_crossapp_CASlider_removeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CASlider* cobj = (CrossApp::CASlider *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASlider_removeTarget : Invalid Native Object");
    if (argc == 2) {
        
        cobj->removeTarget(NULL, NULL);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASlider_removeTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
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
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->addTarget(callback, callback->getTarget(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAStepper_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_crossapp_CAStepper_removeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAStepper* cobj = (CrossApp::CAStepper *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CAStepper_removeTarget : Invalid Native Object");
    if (argc == 2) {
        
        cobj->removeTarget(NULL, NULL);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAStepper_removeTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
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
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->addTarget(callback, callback->getTarget(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASwitch_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_crossapp_CASwitch_removeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CASwitch* cobj = (CrossApp::CASwitch *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASwitch_removeTarget : Invalid Native Object");
    if (argc == 2) {
        
        cobj->removeTarget(NULL, NULL);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASwitch_removeTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
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
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->addTarget(callback, callback->getTarget(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAPageControl_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_crossapp_CAPageControl_removeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAPageControl* cobj = (CrossApp::CAPageControl *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASlider_addTarget : Invalid Native Object");
    if (argc == 2) {
        
        cobj->removeTarget(NULL, NULL);
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAPageControl_removeTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
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
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->addTarget(callback, callback->getCASegmentedTarget(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CASegmentedControl_addTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

bool js_crossapp_CAAlertView_createWithText(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc >= 3) {
        std::string jsTitle;
        ok &= jsval_to_std_string(cx, args.get(0), &jsTitle);
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAAlertView_createWithText : Error processing arguments");
        
        std::string jsAlertMsg;
        ok &= jsval_to_std_string(cx, args.get(1), &jsAlertMsg);
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAAlertView_createWithText : Error processing arguments");

        std::string jsBtnText;
        ok &= jsval_to_std_string(cx, args.get(1), &jsBtnText);
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAAlertView_createWithText : Error processing arguments");
        
        
        CrossApp::CAAlertView* ret = CrossApp::CAAlertView::createWithText(jsTitle.c_str(),jsAlertMsg.c_str(),jsBtnText.c_str(),NULL);
        
        if (argc > 3) {
            while (ok) {
                std::string jsNextBtnText;
                ok &= jsval_to_std_string(cx, args.get(0), &jsNextBtnText);
//                JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAAlertView_createWithText : Error processing arguments");
                if (ok) {
                    ret->addButton(jsNextBtnText.c_str());
                }
                
            }
           
        }
        
        jsval jsret = JSVAL_NULL;
        do {
            if (ret) {
                js_proxy_t *jsProxy = js_get_or_create_proxy<CrossApp::CAAlertView>(cx, (CrossApp::CAAlertView*)ret);
                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_crossapp_CAAlertView_create : wrong number of arguments");
    return false;
}


bool js_crossapp_CAAlertView_setTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAAlertView* cobj = (CrossApp::CAAlertView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CAAlertView_setTarget : Invalid Native Object");
    
    if (argc == 2) {
        
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAButton_addTarget : Error processing arguments");
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->setTarget(callback, callback->getAlertViewTarger(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CAAlertView_setTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
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
        
        JSControlCallback* callback = new JSControlCallback();
        
        cobj->setTarget(callback, callback->getTarget(jsobj, jsval));
        
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CABarButtonItem_setTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
    
}


//bool js_crossapp_CASegmentedControl_removeTarget(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    CrossApp::CASegmentedControl* cobj = (CrossApp::CASegmentedControl *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CASegmentedControl_removeTarget : Invalid Native Object");
//    if (argc == 2) {
//        
//        cobj->removeTarget(NULL, NULL);
//        
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_CASegmentedControl_removeTarget : wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}

//CAViewAnimation
bool js_crossapp_CAViewAnimation_setAnimationWillStartSelector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
         JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAViewAnimation_setAnimationWillStartSelector0 : Error processing arguments");
        
        JSControlCallback* callback = new JSControlCallback();
       
        CrossApp::CAViewAnimation::setAnimationWillStartSelector(callback, callback->getViewAnimation0(jsobj, jsval));
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_crossapp_CAViewAnimation_setAnimationWillStartSelector0 : wrong number of arguments");
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
        
        JSControlCallback* callback = new JSControlCallback();
        
        CrossApp::CAViewAnimation::setAnimationWillStartSelector(callback, callback->getViewAnimation2(jsobj, jsval));
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2 : wrong number of arguments");
    return false;
}


bool js_crossapp_CAViewAnimation_setAnimationDidStopSelector(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAViewAnimation_setAnimationDidStopSelector_0 : Error processing arguments");
        
        JSControlCallback* callback = new JSControlCallback();
        
        CrossApp::CAViewAnimation::setAnimationDidStopSelector(callback, callback->getViewAnimation0(jsobj, jsval));
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_crossapp_CAViewAnimation_setAnimationDidStopSelector_0 : wrong number of arguments");
    return false;
}

bool js_crossapp_CAViewAnimation_setAnimationDidStopSelector_2(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    if (argc == 2) {
        JS::RootedValue jsobj(cx, args.get(0));
        
        JS::RootedValue jsval(cx, args.get(1));
        
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CAViewAnimation_setAnimationDidStopSelector_2 : Error processing arguments");
        
        JSControlCallback* callback = new JSControlCallback();
        
        CrossApp::CAViewAnimation::setAnimationDidStopSelector(callback, callback->getViewAnimation2(jsobj, jsval));
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_crossapp_CAViewAnimation_setAnimationDidStopSelector_2 : wrong number of arguments");
    return false;
}

bool js_crossapp_CCScheduler_unscheduleAllSelectorsForTarget(JSContext *cx, uint32_t argc, jsval *vp)
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
//bool js_CCScheduler_scheduleUpdateForTarget(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    if (argc >= 1) {
//        bool ok = true;
//        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//        
//        JSObject *obj = JS_THIS_OBJECT(cx, vp);
//        js_proxy_t *proxy = jsb_get_js_proxy(obj);
//        CrossApp::CAScheduler *sched = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
//        
//        JSScheduleWrapper *tmpCObj = NULL;
//        
//        JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
//        proxy = jsb_get_js_proxy(tmpObj);
//        bool isPureJSTarget = proxy ? false : true;
//        
//        bool isFoundUpdate = false;
//        ok = JS_HasProperty(cx, tmpObj, "update", &isFoundUpdate);
//        JS::RootedValue jsUpdateFunc(cx);
//        if (ok && isFoundUpdate) {
//            ok = JS_GetProperty(cx, tmpObj, "update", &jsUpdateFunc);
//        }
//        
//        // if no 'update' property, return true directly.
//        if (!ok) {
//            args.rval().setUndefined();
//            return true;
//        }
//        
//        int arg1 = 0;
//        if (argc >= 2) {
//            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
//        }
//
//        bool paused = false;
//        
//        if( argc >= 3 ) {
//            paused = JS::ToBoolean(JS::RootedValue(cx, args.get(2)));
//        }
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        bool bFound = false;
//        auto pTargetArr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
//        CAObject* pObj = NULL;
//        CCARRAY_FOREACH(pTargetArr, pObj)
//        {
//            JSScheduleWrapper* pTarget = static_cast<JSScheduleWrapper*>(pObj);
//            if (jsUpdateFunc == pTarget->getJSCallbackFunc())
//            {
//                tmpCObj = pTarget;
//                bFound = true;
//                break;
//            }
//        }
//        
//        if (!bFound)
//        {
//            tmpCObj = new JSScheduleWrapper();
//            tmpCObj->autorelease();
//            tmpCObj->setJSCallbackThis(args.get(0));
//            tmpCObj->setJSCallbackFunc(jsUpdateFunc);
//            tmpCObj->setUpdateSchedule(true);
//            if (isPureJSTarget) {
//                tmpCObj->setPureJSTarget(tmpObj);
//            }
//            
//            JSScheduleWrapper::setTargetForSchedule(jsUpdateFunc, tmpCObj);
//            JSScheduleWrapper::setTargetForJSObject(tmpObj, tmpCObj);
//        }
//        tmpCObj->setPriority(arg1);
//        sched->scheduleUpdate(tmpCObj, arg1, paused);
//        
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments");
//    return false;
//}
//

//bool js_CCScheduler_unscheduleUpdateForTarget(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    CrossApp::CAScheduler * cobj = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//    
//    if (argc == 1) {
//        do {
//            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
//            
//            CrossApp::CAVector<CAObject*> *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
//            // If there aren't any targets, just return true.
//            // Otherwise, the for loop will break immediately.
//            // It will lead to logic errors.
//            // For details to reproduce it, please refer to SchedulerTest/SchedulerUpdate.
//            if(! arr) return true;
//            
//            JSScheduleWrapper* wrapper = NULL;
//            for(ssize_t i = 0; i < arr->count(); ++i) {
//                wrapper = (JSScheduleWrapper*)arr->getObjectAtIndex(i);
//                if(wrapper && wrapper->isUpdateSchedule()) {
//                    cobj->unscheduleUpdate(wrapper);
//                    CCAssert(args.get(0) == wrapper->getJSCallbackThis(), "Wrong target object.");
//                    JSScheduleWrapper::removeTargetForJSObject(tmpObj, wrapper);
//                    break;
//                }
//            }
//        } while (0);
//        
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
bool js_CCScheduler_scheduleCallbackForTarget(JSContext *cx, uint32_t argc, jsval *vp)
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
//        CCARRAY_FOREACH(pTargetArr, pObj)
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

//bool js_CCScheduler_schedule(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    if (argc >= 2) {
//        bool ok = true;
//        JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//        
//        JS::RootedObject obj(cx);
//        obj = args.thisv().toObjectOrNull();
//        js_proxy_t *proxy = jsb_get_js_proxy(obj);
//        CrossApp::CAScheduler *sched = ( CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
//        
//        std::function<void (float)> callback;
//        JS::RootedObject targetObj(cx);
//        do {
//            JS::RootedValue callbackVal(cx);
//            if (JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
//            {
//                callbackVal.set(args.get(0));
//                targetObj.set(args.get(1).toObjectOrNull());
//            }
//            else if (JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION)
//            {
//                targetObj.set(args.get(0).toObjectOrNull());
//                callbackVal.set(args.get(1));
//            }
//            else
//            {
//                ok = false;
//                callback = nullptr;
//                break;
//            }
//            
//            std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, targetObj, callbackVal));
//            auto lambda = [=](float larg0) -> void {
//                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
//                jsval largv[1];
//                largv[0] = DOUBLE_TO_JSVAL(larg0);
//                JS::RootedValue rval(cx);
//                bool invokeOk = func->invoke(1, &largv[0], &rval);
//                if (!invokeOk && JS_IsExceptionPending(cx)) {
//                    JS_ReportPendingException(cx);
//                }
//            };
//            callback = lambda;
//        } while(0);
//        
//        double interval = 0;
//        if( argc >= 3 ) {
//            ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(2)), &interval );
//        }
//        
//        //
//        // repeat
//        //
//        double repeat = -1;
//        if( argc >= 4 ) {
//            ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(3)), &repeat );
//        }
//        
//        //
//        // delay
//        //
//        double delay = 0;
//        if( argc >= 5 ) {
//            ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(4)), &delay );
//        }
//        
//        //
//        // paused
//        //
//        bool paused = false;
//        if( argc >= 6 ) {
//            paused = JS::ToBoolean(JS::RootedValue(cx,  args.get(5)));
//        }
//        
//        //
//        // key
//        //
//        std::string key;
//        if ( argc >= 7 ) {
//            jsval_to_std_string(cx, args.get(6), &key);
//        }
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
////        sched->schedule(callback, targetObj, interval, repeat, delay, paused, key);
//        CAScheduler::getScheduler()->schedule(callback, targetObj, interval, repeat, delay);
//        
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments");
//    return false;
//
//}

bool js_CCScheduler_unscheduleCallbackForTarget(JSContext *cx, uint32_t argc, jsval *vp)
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

bool js_crossapp_CCScheduler_unscheduleAll(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAScheduler* cobj = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 0) {
        cobj->unscheduleAll();
        JSScheduleWrapper::removeAllTargets();
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


bool js_crossapp_CCScheduler_pauseTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAScheduler *sched = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
    
    if (argc == 1) {
        do {
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            CrossApp::CAVector<CAObject*> *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            if(! arr) return true;
            for(ssize_t i = 0; i < arr->size(); ++i) {
                if(arr->at(i)) {
                    sched->pauseTarget(arr->at(i));
                }
            }

        } while (0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_crossapp_CCScheduler_resumeTarget(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAScheduler *sched = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
    
    if (argc == 1) {
        do {
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            auto arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            if(! arr) return true;
            for(ssize_t i = 0; i < arr->size(); ++i) {
                if(arr->at(i)) {
                    sched->resumeTarget(arr->at(i));
                }
            }
            
        } while (0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

bool js_crossapp_CCScheduler_isTargetPaused(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAScheduler* cobj = (CrossApp::CAScheduler *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1) {
        bool ret = false;
        do {
            JS::RootedObject tmpObj(cx, args.get(0).toObjectOrNull());
            CrossApp::CAVector<CAObject*> *arr = JSScheduleWrapper::getTargetForJSObject(tmpObj);
            if(! arr) return true;
            for(ssize_t i = 0; i < arr->size(); ++i) {
                if(arr->at(i)) {
                    ret = cobj->isTargetPaused(arr->at(i)) ? true : false;
                    // break directly since all targets have the same `pause` status.
                    break;
                }
            }
        } while (0);
//        JS_SET_RVAL(cx, vp, BOOLEAN_TO_JSVAL(ret));
        args.rval().set(BOOLEAN_TO_JSVAL(ret));
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

//bool js_crossapp_Node_cleanup(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    CrossApp::CAView* cobj = (CrossApp::CAView *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_cleanup : Invalid Native Object");
//    
//    ScriptingCore::getInstance()->setCalledFromScript(true);
//    cobj->cleanup();
//    args.rval().setUndefined();
//    return true;
//}

//bool js_crossapp_CCNode_setPosition(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    bool ok = true;
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//    
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        cobj->setPosition(arg0);
//        args.rval().setUndefined();
//        return true;
//    } if (argc == 2) {
//        double x;
//        ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(0)), &x );
//        double y;
//        ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(1)), &y );
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        cobj->setPosition(Point(x,y));
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_CCNode_setContentSize(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    bool ok = true;
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//    
//    if (argc == 1) {
//        cocos2d::Size arg0;
//        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        cobj->setContentSize(arg0);
//        args.rval().setUndefined();
//        return true;
//    } if (argc == 2) {
//        double width;
//        ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(0)), &width );
//        double height;
//        ok &= JS::ToNumber(cx, JS::RootedValue(cx, args.get(1)), &height );
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        cobj->setContentSize(Size(width,height));
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_CCNode_setAnchorPoint(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    bool ok = true;
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//    
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        cobj->setAnchorPoint(arg0);
//        args.rval().setUndefined();
//        return true;
//    } if (argc == 2) {
//        double x;
//        ok &= JS::ToNumber(cx, args.get(0), &x );
//        double y;
//        ok &= JS::ToNumber(cx, args.get(1), &y );
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        cobj->setAnchorPoint(Point(x,y));
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_CCNode_setColor(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_setColor : Invalid Native Object");
//    if (argc == 1) {
//        cocos2d::Color3B arg0;
//        ok &= jsval_to_cccolor3b(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Node_setColor : Error processing arguments");
//        cobj->setColor(arg0);
//        
////        int32_t alpha;
////		ok &= jsval_cccolor_to_opacity(cx, args.get(0), &alpha);
////        if (ok) {
////            cobj->setOpacity(alpha);
////        }
//        args.rval().setUndefined();
//		return true;
//	}
//    
//    JS_ReportError(cx, "js_crossapp_Node_setColor : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_CCNode_pause(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_pause : Invalid Native Object");
//    if (argc == 0) {
//        do {
////            JSObject *tmpObj = obj;
//
//            __Array *arr = JSScheduleWrapper::getTargetForJSObject(obj);
//            if(arr){
//                JSScheduleWrapper* wrapper = NULL;
//                for(ssize_t i = 0; i < arr->count(); ++i) {
//                    wrapper = (JSScheduleWrapper*)arr->getObjectAtIndex(i);
//                    if(wrapper) {
//                        cobj->getScheduler()->pauseTarget(wrapper);
//                    }
//                }
//            }
//        } while (0);
//
//        cobj->pause();
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_Node_pause : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//bool js_crossapp_CCNode_resume(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_resume : Invalid Native Object");
//    if (argc == 0) {
//        do {
////            JSObject *tmpObj = obj;
//
//            __Array *arr = JSScheduleWrapper::getTargetForJSObject(obj);
//            if(arr){
//                JSScheduleWrapper* wrapper = NULL;
//                for(ssize_t i = 0; i < arr->count(); ++i) {
//                    wrapper = (JSScheduleWrapper*)arr->getObjectAtIndex(i);
//                    if(wrapper) {
//                        cobj->getScheduler()->resumeTarget(wrapper);
//                    }
//                }
//            }
//        } while (0);
//
//        cobj->resume();
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_Node_resume : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//bool js_crossapp_CCNode_convertToWorldSpace(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CCNode_convertToWorldSpace : Invalid Native Object");
//    cocos2d::Vec2 arg0;
//    if (argc == 1) {
//        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CCNode_convertToWorldSpace : Error processing arguments");
//    }
//    else if (argc != 0) {
//        JS_ReportError(cx, "js_crossapp_CCNode_convertToWorldSpace : wrong number of arguments: %d, was expecting 0 or 1", argc);
//        return false;
//    }
//    
//    cocos2d::Vec2 ret = cobj->convertToWorldSpace(arg0);
//    jsval jsret = JSVAL_NULL;
//    jsret = vector2_to_jsval(cx, ret);
//    args.rval().set(jsret);
//    return true;
//}
//
//bool js_crossapp_CCNode_convertToWorldSpaceAR(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Node* cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CCNode_convertToWorldSpaceAR : Invalid Native Object");
//    cocos2d::Vec2 arg0;
//    if (argc == 1) {
//        ok &= jsval_to_vector2(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CCNode_convertToWorldSpaceAR : Error processing arguments");
//    }
//    else if (argc != 0) {
//        JS_ReportError(cx, "js_crossapp_CCNode_convertToWorldSpaceAR : wrong number of arguments: %d, was expecting 0 or 1", argc);
//        return false;
//    }
//    
//    cocos2d::Vec2 ret = cobj->convertToWorldSpaceAR(arg0);
//    jsval jsret = JSVAL_NULL;
//    jsret = vector2_to_jsval(cx, ret);
//    args.rval().set(jsret);
//    return true;
//}
//
//bool js_crossapp_CCTMXLayer_getTiles(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::TMXLayer* cobj = (cocos2d::TMXLayer *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    if (argc == 0) {
//        uint32_t* ret = cobj->getTiles();
//        Size size = cobj->getLayerSize();
//        int count = size.width * size.height;
//        JSObject* array = JS_NewUint32Array(cx, count);
//        if (NULL == array) {
//            JS_ReportError(cx, "Can't allocate enough memory.");
//            return false;
//        }
//        uint32_t* bufdata = (uint32_t*)JS_GetArrayBufferViewData(array);
//        memcpy(bufdata, ret, count*sizeof(int32_t));
//
//        args.rval().set(OBJECT_TO_JSVAL(array));
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//
//// Actions
//
//bool js_crossapp_ActionInterval_repeat(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::ActionInterval* cobj = (cocos2d::ActionInterval *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_ActionInterval_repeat : Invalid Native Object");
//
//    if (argc == 1)
//    {
//        double times;
//        if( ! JS::ToNumber(cx, args.get(0), &times) ) {
//            return false;
//        }
//        int timesInt = (int)times;
//        if (timesInt <= 0) {
//            JS_ReportError(cx, "js_crossapp_ActionInterval_repeat : Repeat times must be greater than 0");
//        }
//        
//        cocos2d::Repeat* action = cocos2d::Repeat::create(cobj, timesInt);
//        // Unbind current proxy binding
//        JS::RemoveObjectRoot(cx, &proxy->obj);
//        jsb_remove_proxy(jsb_get_native_proxy(cobj), proxy);
//        // Rebind js obj with new action
//        js_proxy_t* newProxy = jsb_new_proxy(action, obj);
//        JS::AddNamedObjectRoot(cx, &newProxy->obj, "cocos2d::Repeat");
//
//        args.rval().set(OBJECT_TO_JSVAL(obj));
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_ActionInterval_repeat : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ActionInterval_repeatForever(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::ActionInterval* cobj = (cocos2d::ActionInterval *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_ActionInterval_repeatForever : Invalid Native Object");
//    
//    if (argc == 0) {
//        cocos2d::RepeatForever* action = cocos2d::RepeatForever::create(cobj);
//        // Unbind current proxy binding
//        JS::RemoveObjectRoot(cx, &proxy->obj);
//        jsb_remove_proxy(jsb_get_native_proxy(cobj), proxy);
//        // Rebind js obj with new action
//        js_proxy_t* newProxy = jsb_new_proxy(action, obj);
//        JS::AddNamedObjectRoot(cx, &newProxy->obj, "cocos2d::RepeatForever");
//
//        args.rval().set(OBJECT_TO_JSVAL(obj));
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_ActionInterval_repeatForever : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//bool js_crossapp_ActionInterval_speed(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::ActionInterval* cobj = (cocos2d::ActionInterval *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_ActionInterval_speed : Invalid Native Object");
//
//    if (argc == 1)
//    {
//        double speed;
//        if( ! JS::ToNumber(cx, args.get(0), &speed) ) {
//            return false;
//        }
//        if (speed < 0) {
//            JS_ReportError(cx, "js_crossapp_ActionInterval_speed : Speed must not be negative");
//            return false;
//        }
//        
//        cocos2d::Speed* action = cocos2d::Speed::create(cobj, speed);
//        // Unbind current proxy binding
//        JS::RemoveObjectRoot(cx, &proxy->obj);
//        jsb_remove_proxy(jsb_get_native_proxy(cobj), proxy);
//        // Rebind js obj with new action
//        js_proxy_t* newProxy = jsb_new_proxy(action, obj);
//        JS::AddNamedObjectRoot(cx, &newProxy->obj, "cocos2d::Speed");
//
//        args.rval().set(OBJECT_TO_JSVAL(obj));
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_ActionInterval_speed : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//enum ACTION_TAG {
//    EASE_IN = 0,
//    EASE_OUT,
//    EASE_INOUT,
//    EASE_EXPONENTIAL_IN,
//    EASE_EXPONENTIAL_OUT,
//    EASE_EXPONENTIAL_INOUT,
//    EASE_SINE_IN,
//    EASE_SINE_OUT,
//    EASE_SINE_INOUT,
//    EASE_ELASTIC_IN,
//    EASE_ELASTIC_OUT,
//    EASE_ELASTIC_INOUT,
//    EASE_BOUNCE_IN,
//    EASE_BOUNCE_OUT,
//    EASE_BOUNCE_INOUT,
//    EASE_BACK_IN,
//    EASE_BACK_OUT,
//    EASE_BACK_INOUT,
//    
//    EASE_BEZIER_ACTION,
//    EASE_QUADRATIC_IN,
//    EASE_QUADRATIC_OUT,
//    EASE_QUADRATIC_INOUT,
//    EASE_QUARTIC_IN,
//    EASE_QUARTIC_OUT,
//    EASE_QUARTIC_INOUT,
//    EASE_QUINTIC_IN,
//    EASE_QUINTIC_OUT,
//    EASE_QUINTIC_INOUT,
//    EASE_CIRCLE_IN,
//    EASE_CIRCLE_OUT,
//    EASE_CIRCLE_INOUT,
//    EASE_CUBIC_IN,
//    EASE_CUBIC_OUT,
//    EASE_CUBIC_INOUT
//};
//
//bool js_crossapp_ActionInterval_easing(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::ActionInterval* cobj = (cocos2d::ActionInterval *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_ActionInterval_easing : Invalid Native Object");
//    
//    cocos2d::ActionInterval* currentAction = cobj;
//    JS::RootedObject tmp(cx);
//    JS::RootedValue jsTag(cx);
//    JS::RootedValue jsParam(cx);
//    double tag;
//    double parameter;
//
//    for (int i = 0; i < argc; i++)
//    {
////        jsval vpi = argv[i];
//        JS::RootedValue vpi(cx, args.get(i));
//        bool ok = vpi.isObject() &&
//            JS_ValueToObject(cx, vpi, &tmp) &&
//            JS_GetProperty(cx, tmp, "tag", &jsTag) &&
//            JS::ToNumber(cx, jsTag, &tag);
//        JS_GetProperty(cx, tmp, "param", &jsParam) && JS::ToNumber(cx, jsParam, &parameter);
//        bool hasParam = (parameter == parameter);
//        if (!ok) continue;
//
//        cocos2d::ActionEase* action;
//        ok = true;
//        if (tag == EASE_IN)
//        {
//            if (!hasParam) ok = false;
//            action = cocos2d::EaseIn::create(currentAction, parameter);
//        }
//        else if (tag == EASE_OUT)
//        {
//            if (!hasParam) ok = false;
//            action = cocos2d::EaseOut::create(currentAction, parameter);
//        }
//        else if (tag == EASE_INOUT)
//        {
//            if (!hasParam) ok = false;
//            action = cocos2d::EaseInOut::create(currentAction, parameter);
//        }
//        else if (tag == EASE_EXPONENTIAL_IN)
//            action = cocos2d::EaseExponentialIn::create(currentAction);
//        else if (tag == EASE_EXPONENTIAL_OUT)
//            action = cocos2d::EaseExponentialOut::create(currentAction);
//        else if (tag == EASE_EXPONENTIAL_INOUT)
//            action = cocos2d::EaseExponentialInOut::create(currentAction);
//        else if (tag == EASE_SINE_IN)
//            action = cocos2d::EaseSineIn::create(currentAction);
//        else if (tag == EASE_SINE_OUT)
//            action = cocos2d::EaseSineOut::create(currentAction);
//        else if (tag == EASE_SINE_INOUT)
//            action = cocos2d::EaseSineInOut::create(currentAction);
//        else if (tag == EASE_ELASTIC_IN)
//        {
//            if (!hasParam) parameter = 0.3;
//            action = cocos2d::EaseElasticIn::create(currentAction, parameter);
//        }
//        else if (tag == EASE_ELASTIC_OUT)
//        {
//            if (!hasParam) parameter = 0.3;
//            action = cocos2d::EaseElasticOut::create(currentAction, parameter);
//        }
//        else if (tag == EASE_ELASTIC_INOUT)
//        {
//            if (!hasParam) parameter = 0.3;
//            action = cocos2d::EaseElasticInOut::create(currentAction, parameter);
//        }
//        else if (tag == EASE_BOUNCE_IN)
//            action = cocos2d::EaseBounceIn::create(currentAction);
//        else if (tag == EASE_BOUNCE_OUT)
//            action = cocos2d::EaseBounceOut::create(currentAction);
//        else if (tag == EASE_BOUNCE_INOUT)
//            action = cocos2d::EaseBounceInOut::create(currentAction);
//        else if (tag == EASE_BACK_IN)
//            action = cocos2d::EaseBackIn::create(currentAction);
//        else if (tag == EASE_BACK_OUT)
//            action = cocos2d::EaseBackOut::create(currentAction);
//        else if (tag == EASE_BACK_INOUT)
//            action = cocos2d::EaseBackInOut::create(currentAction);
//        
//        else if (tag == EASE_QUADRATIC_IN)
//            action = cocos2d::EaseQuadraticActionIn::create(currentAction);
//        else if (tag == EASE_QUADRATIC_OUT)
//            action = cocos2d::EaseQuadraticActionOut::create(currentAction);
//        else if (tag == EASE_QUADRATIC_INOUT)
//            action = cocos2d::EaseQuadraticActionInOut::create(currentAction);
//        else if (tag == EASE_QUARTIC_IN)
//            action = cocos2d::EaseQuarticActionIn::create(currentAction);
//        else if (tag == EASE_QUARTIC_OUT)
//            action = cocos2d::EaseQuarticActionOut::create(currentAction);
//        else if (tag == EASE_QUARTIC_INOUT)
//            action = cocos2d::EaseQuarticActionInOut::create(currentAction);
//        else if (tag == EASE_QUINTIC_IN)
//            action = cocos2d::EaseQuinticActionIn::create(currentAction);
//        else if (tag == EASE_QUINTIC_OUT)
//            action = cocos2d::EaseQuinticActionOut::create(currentAction);
//        else if (tag == EASE_QUINTIC_INOUT)
//            action = cocos2d::EaseQuinticActionInOut::create(currentAction);
//        else if (tag == EASE_CIRCLE_IN)
//            action = cocos2d::EaseCircleActionIn::create(currentAction);
//        else if (tag == EASE_CIRCLE_OUT)
//            action = cocos2d::EaseCircleActionOut::create(currentAction);
//        else if (tag == EASE_CIRCLE_INOUT)
//            action = cocos2d::EaseCircleActionInOut::create(currentAction);
//        else if (tag == EASE_CUBIC_IN)
//            action = cocos2d::EaseCubicActionIn::create(currentAction);
//        else if (tag == EASE_CUBIC_OUT)
//            action = cocos2d::EaseCubicActionOut::create(currentAction);
//        else if (tag == EASE_CUBIC_INOUT)
//            action = cocos2d::EaseCubicActionInOut::create(currentAction);
//        else if (tag == EASE_BEZIER_ACTION)
//        {
//            JS::RootedValue jsParam2(cx);
//            JS::RootedValue jsParam3(cx);
//            JS::RootedValue jsParam4(cx);
//            double parameter2, parameter3, parameter4;
//            ok &= JS_GetProperty(cx, tmp, "param2", &jsParam2);
//            ok &= JS::ToNumber(cx, jsParam2, &parameter2);
//            ok &= JS_GetProperty(cx, tmp, "param3", &jsParam3);
//            ok &= JS::ToNumber(cx, jsParam3, &parameter3);
//            ok &= JS_GetProperty(cx, tmp, "param4", &jsParam4);
//            ok &= JS::ToNumber(cx, jsParam4, &parameter4);
//            if (!ok) continue;
//            
//            action = cocos2d::EaseBezierAction::create(currentAction);
//            ((EaseBezierAction *)action)->setBezierParamer(parameter, parameter2, parameter3, parameter4);
//        }
//        else
//            continue;
//        
//        if (!ok || !action) {
//            JS_ReportError(cx, "js_crossapp_ActionInterval_easing : Invalid action: At least one action was expecting parameter");
//            return false;
//        }
//        
//        currentAction = action;
//    }
//    
//    // Unbind current proxy binding
//    JS::RemoveObjectRoot(cx, &proxy->obj);
//    jsb_remove_proxy(jsb_get_native_proxy(cobj), proxy);
//    // Rebind js obj with new action
//    js_proxy_t* newProxy = jsb_new_proxy(currentAction, obj);
//    JS::AddNamedObjectRoot(cx, &newProxy->obj, "cocos2d::EaseAction");
//    args.rval().set(OBJECT_TO_JSVAL(obj));
//    return true;
//}
//
//
//template<class T>
//bool js_BezierActions_create(JSContext *cx, uint32_t argc, jsval *vp) {
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//
//    if (argc == 2) {
//        double t;
//        if( ! JS::ToNumber(cx, args.get(0), &t) ) {
//            return false;
//        }
//        
//        int num;
//        Point *arr;
//        jsval_to_ccarray_of_CCPoint(cx, args.get(1), &arr, &num);
//        
//        ccBezierConfig config;
//        config.controlPoint_1 = arr[0];
//        config.controlPoint_2 = arr[1];
//        config.endPosition = arr[2];
//        
//        T* ret =  T::create(t, config);
//        
//        delete [] arr;
//
//        jsval jsret;
//        do {
//            if (ret) {
//                js_proxy_t *p = jsb_get_native_proxy(ret);
//                if (p) {
//                    jsret = OBJECT_TO_JSVAL(p->obj);
//                } else {
//                    // create a new js obj of that class
//                    js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, ret);
//                    jsret = OBJECT_TO_JSVAL(proxy->obj);
//                }
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//template<class T>
//bool js_BezierActions_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    T* cobj = (T *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Bezier_initWithDuration : Invalid Native Object");
//    if (argc == 2) {
//        double arg0;
//        cocos2d::_ccBezierConfig arg1;
//        ok &= JS::ToNumber( cx, JS::RootedValue(cx, args.get(0)), &arg0);
//
//        int num;
//        cocos2d::Vec2 *arr;
//        jsval_to_ccarray_of_CCPoint(cx, args.get(1), &arr, &num);
//
//        arg1.controlPoint_1 = arr[0];
//        arg1.controlPoint_2 = arr[1];
//        arg1.endPosition = arr[2];
//
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Bezier_initWithDuration : Error processing arguments");
//        bool ret = cobj->initWithDuration(arg0, arg1);
//        delete [] arr;
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_BezierTo_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//template<class T>
//bool js_CardinalSplineActions_create(JSContext *cx, uint32_t argc, jsval *vp) {
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    
//    if (argc == 3) {
//        double dur;
//        ok &= JS::ToNumber(cx, args.get(0), &dur);
//        
//        int num;
//        Point *arr;
//        ok &= jsval_to_ccarray_of_CCPoint(cx, args.get(1), &arr, &num);
//        
//        double ten;
//        ok &= JS::ToNumber(cx, args.get(2), &ten);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        PointArray *points = PointArray::create(num);
//        
//        for( int i=0; i < num;i++) {
//            points->addControlPoint(arr[i]);
//        }
//        
//        T *ret = T::create(dur, points, ten);
//        
//        delete [] arr;
//        
//        jsval jsret;
//        do {
//            if (ret) {
//                js_proxy_t *p = jsb_get_native_proxy(ret);
//                if (p) {
//                    jsret = OBJECT_TO_JSVAL(p->obj);
//                } else {
//                    // create a new js obj of that class
//                    js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, ret);
//                    jsret = OBJECT_TO_JSVAL(proxy->obj);
//                }
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//template<class T>
//bool js_CatmullRomActions_create(JSContext *cx, uint32_t argc, jsval *vp) {
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    
//    if (argc == 2) {
//        double dur;
//        ok &= JS::ToNumber(cx, args.get(0), &dur);
//        
//        int num;
//        Point *arr;
//        ok &= jsval_to_ccarray_of_CCPoint(cx, args.get(1), &arr, &num);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        PointArray *points = PointArray::create(num);
//        
//        for( int i=0; i < num;i++) {
//            points->addControlPoint(arr[i]);
//        }
//        
//        T *ret = T::create(dur, points);
//        
//        delete [] arr;
//        
//        jsval jsret;
//        do {
//            if (ret) {
//                js_proxy_t *p = jsb_get_native_proxy(ret);
//                if (p) {
//                    jsret = OBJECT_TO_JSVAL(p->obj);
//                } else {
//                    // create a new js obj of that class
//                    js_proxy_t *proxy = js_get_or_create_proxy<T>(cx, ret);
//                    jsret = OBJECT_TO_JSVAL(proxy->obj);
//                }
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//template<class T>
//bool js_CatmullRomActions_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    T* cobj = (T *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CatmullRom_initWithDuration : Invalid Native Object");
//    if (argc == 2) {
//        double arg0;
//        ok &= JS::ToNumber( cx, JS::RootedValue(cx, args.get(0)), &arg0);
//
//        int num;
//        Point *arr;
//        ok &= jsval_to_ccarray_of_CCPoint(cx, args.get(1), &arr, &num);
//                
//        cocos2d::PointArray* arg1 = cocos2d::PointArray::create(num);        
//        for( int i=0; i < num;i++) {
//            arg1->addControlPoint(arr[i]);
//        }
//               
//        
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CatmullRom_initWithDuration : Error processing arguments");
//        bool ret = cobj->initWithDuration(arg0, arg1);
//        delete [] arr;
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_CatmullRom_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//
//bool JSB_CCBezierBy_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_BezierActions_create<cocos2d::BezierBy>(cx, argc, vp);
//}
//
//bool JSB_CCBezierTo_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_BezierActions_create<cocos2d::BezierTo>(cx, argc, vp);
//}
//
//bool JSB_CCBezierBy_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    return js_BezierActions_initWithDuration<cocos2d::BezierBy>(cx, argc, vp);
//}
//
//bool JSB_CCBezierTo_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    return js_BezierActions_initWithDuration<cocos2d::BezierTo>(cx, argc, vp);
//}
//
//bool JSB_CCCardinalSplineBy_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_CardinalSplineActions_create<cocos2d::CardinalSplineBy>(cx, argc, vp);
//}
//
//bool JSB_CCCardinalSplineTo_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_CardinalSplineActions_create<cocos2d::CardinalSplineTo>(cx, argc, vp);
//}
//
//bool js_crossapp_CardinalSplineTo_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::CardinalSplineTo* cobj = (cocos2d::CardinalSplineTo *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CardinalSplineTo_initWithDuration : Invalid Native Object");
//    if (argc == 3) {
//        double arg0;
//        
//        double arg2;
//        ok &= JS::ToNumber( cx, JS::RootedValue(cx, args.get(0)), &arg0);
//        
//        int num;
//        Point *arr;
//        ok &= jsval_to_ccarray_of_CCPoint(cx, args.get(1), &arr, &num);
//        cocos2d::PointArray* arg1 = PointArray::create(num);
//        for( int i=0; i < num;i++) {
//            arg1->addControlPoint(arr[i]);
//        }
//
//        ok &= JS::ToNumber( cx, JS::RootedValue(cx, args.get(2)), &arg2);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CardinalSplineTo_initWithDuration : Error processing arguments");
//        bool ret = cobj->initWithDuration(arg0, arg1, arg2);
//        
//        delete [] arr;
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_CardinalSplineTo_initWithDuration : wrong number of arguments: %d, was expecting %d", argc, 3);
//    return false;
//}
//
//bool JSB_CCCatmullRomBy_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_CatmullRomActions_create<cocos2d::CatmullRomBy>(cx, argc, vp);
//}
//
//bool JSB_CCCatmullRomTo_actionWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_CatmullRomActions_create<cocos2d::CatmullRomTo>(cx, argc, vp);
//}
//
//bool JSB_CatmullRomBy_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_CatmullRomActions_initWithDuration<cocos2d::CatmullRomBy>(cx, argc, vp);
//}
//
//bool JSB_CatmullRomTo_initWithDuration(JSContext *cx, uint32_t argc, jsval *vp) {
//    return js_CatmullRomActions_initWithDuration<cocos2d::CatmullRomTo>(cx, argc, vp);
//}
//
//bool js_crossapp_ccGLEnableVertexAttribs(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    bool ok = true;
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    
//    if (argc == 1) {
//        unsigned int arg0;
//        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        GL::enableVertexAttribs(arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//
//
//bool js_crossapp_ccpAdd(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    bool ok = true;
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0 + arg1;
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpDistanceSQ(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    bool ok = true;
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        float ret = arg0.getDistanceSq(arg1);
//        
//        jsval jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpDistance(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    bool ok = true;
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        float ret = arg0.getDistance(arg1);
//        
//        jsval jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpClamp(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 3) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        cocos2d::Point arg2;
//        ok &= jsval_to_ccpoint(cx, args.get(2), &arg2);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0.getClampPoint(arg1, arg2);
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpLengthSQ(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        float ret = arg0.getLengthSq();
//
//        jsval jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpLength(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        float ret = arg0.getLength();
//
//        jsval jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpNeg(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = -arg0;
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpSub(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0 - arg1;
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpMult(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        
//        double arg1;
//        ok &= JS::ToNumber(cx, args.get(1), &arg1);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0 * arg1;
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccpMidpoint(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0.getMidpoint(arg1);
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//
//bool js_crossapp_ccpDot(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        float ret = arg0.dot(arg1);
//        
//        jsval jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccpCross(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        float ret = arg0.cross(arg1);
//        
//        jsval jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccpPerp(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0.getPerp();
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//
//bool js_crossapp_ccpRPerp(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0.getRPerp();
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//
//bool js_crossapp_ccpProject(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0.project(arg1);
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccpRotate(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 2) {
//        cocos2d::Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        cocos2d::Point arg1;
//        ok &= jsval_to_ccpoint(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        Point ret = arg0.rotate(arg1);
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//        
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccpNormalize(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        cocos2d::Vec2 ret;
//        ok &= jsval_to_vector2(cx, args.get(0), &ret);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        ret.normalize();
//        
//        jsval jsret = ccpoint_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccobbGetCorners(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 1)
//    {
//        cocos2d::OBB obb;
//        bool ok = jsval_to_obb(cx, args.get(0), &obb);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        cocos2d::Vec3 verts[8];
//        obb.getCorners(verts);
//
//        JS::RootedObject array(cx, JS_NewArrayObject(cx, 8));
//        for(int i = 0; i < 8; ++i)
//        {
//            JS::RootedValue vec(cx, vector3_to_jsval(cx, verts[i]));
//            ok &= JS_SetElement(cx, array, i, vec);
//            if(!ok)
//                break;
//        }
//
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        args.rval().set(OBJECT_TO_JSVAL(array));
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccobbIntersects(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 2)
//    {
//        cocos2d::OBB obb1, obb2;
//        bool ok = jsval_to_obb(cx, args.get(0), &obb1);
//        ok &= jsval_to_obb(cx, args.get(1), &obb2);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        bool ret = obb1.intersects(obb2);
//
//        args.rval().set(BOOLEAN_TO_JSVAL(ret));
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccrayIntersectsObb(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 2)
//    {
//        cocos2d::Ray ray;
//        cocos2d::OBB obb;
//
//        bool ok = jsval_to_ray(cx, args.get(0), &ray);
//        ok &= jsval_to_obb(cx, args.get(1), &obb);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        bool ret = ray.intersects(obb);
//
//        args.rval().set(BOOLEAN_TO_JSVAL(ret));
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccmat4CreateTranslation(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 1)
//    {
//        cocos2d::Vec3 arg0;
//        bool ok = jsval_to_vector3(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        cocos2d::Mat4 ret;
//        cocos2d::Mat4::createTranslation(arg0, &ret);
//        jsval jsret = matrix_to_jsval(cx, ret);
//
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccmat4CreateRotation(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 1)
//    {
//        cocos2d::Quaternion arg0;
//        bool ok = jsval_to_quaternion(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        cocos2d::Mat4 ret;
//        cocos2d::Mat4::createRotation(arg0, &ret);
//        jsval jsret = matrix_to_jsval(cx, ret);
//
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccmat4Multiply(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 2)
//    {
//        cocos2d::Mat4 arg0;
//        cocos2d::Mat4 arg1;
//        bool ok = jsval_to_matrix(cx, args.get(0), &arg0);
//        ok &= jsval_to_matrix(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        cocos2d::Mat4 ret = arg0 * arg1;
//        jsval jsret = matrix_to_jsval(cx, ret);
//
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccmat4MultiplyVec3(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 2)
//    {
//        cocos2d::Mat4 arg0;
//        cocos2d::Vec3 arg1;
//        bool ok = jsval_to_matrix(cx, args.get(0), &arg0);
//        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        cocos2d::Vec3 ret = arg0 * arg1;
//        jsval jsret = vector3_to_jsval(cx, ret);
//
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_ccmat4GetInversed(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 1)
//    {
//        cocos2d::Mat4 arg0;
//        bool ok = jsval_to_matrix(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        jsval jsret = matrix_to_jsval(cx, arg0.getInversed());
//        
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_ccmat4TransformVector(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc >= 2)
//    {
//        cocos2d::Mat4 arg0;
//        cocos2d::Vec4 arg1;
//        cocos2d::Vec4 ret;
//        bool ok = jsval_to_matrix(cx, args.get(0), &arg0);
//        ok &= jsval_to_vector4(cx, args.get(1), &arg1);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        arg0.transformVector(arg1, &ret);
//        jsval jsret = vector4_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    else if (argc >= 5)
//    {
//        cocos2d::Mat4 arg0;
//        double arg1 = 0.0,arg2 = 0.0,arg3 = 0.0, arg4 = 0.0;
//        cocos2d::Vec3 ret;
//        
//        bool ok = jsval_to_matrix(cx, args.get(0), &arg0) &&
//                  JS::ToNumber(cx, args.get(1), &arg1) &&
//                  JS::ToNumber(cx, args.get(2), &arg2) &&
//                  JS::ToNumber(cx, args.get(3), &arg3) &&
//                  JS::ToNumber(cx, args.get(4), &arg4);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        arg0.transformVector(arg1, arg2, arg3, arg4, &ret);
//        jsval jsret = vector3_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
//    return false;
//}
//
//bool js_crossapp_ccmat4TransformPoint(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc >= 2)
//    {
//        cocos2d::Mat4 arg0;
//        cocos2d::Vec3 arg1;
//        cocos2d::Vec3 ret;
//        bool ok = jsval_to_matrix(cx, args.get(0), &arg0);
//        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        arg0.transformPoint(arg1, &ret);
//        jsval jsret = vector3_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
//    return false;
//}
//
//bool js_crossapp_ccquatMultiply(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if(argc == 2)
//    {
//        cocos2d::Quaternion arg0;
//        cocos2d::Quaternion arg1;
//        bool ok = jsval_to_quaternion(cx, args.get(0), &arg0);
//        ok &= jsval_to_quaternion(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        cocos2d::Quaternion ret = arg0 * arg1;
//        jsval jsret = quaternion_to_jsval(cx, ret);
//
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_Sprite_create(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    
//    do {
//        if (argc == 1) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cocos2d::Sprite* ret = cocos2d::Sprite::create(arg0);
//            jsval jsret = JSVAL_NULL;
//            do {
//                if (ret) {
//                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
//                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//                } else {
//                    jsret = JSVAL_NULL;
//                }
//            } while (0);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while (0);
//    
//    do {
//        if (argc == 0) {
//            cocos2d::Sprite* ret = cocos2d::Sprite::create();
//            jsval jsret = JSVAL_NULL;
//            do {
//                if (ret) {
//                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
//                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//                } else {
//                    jsret = JSVAL_NULL;
//                }
//            } while (0);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while (0);
//    
//    do {
//        if (argc == 2) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cocos2d::Rect arg1;
//            ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
//            if (!ok) { ok = true; break; }
//            cocos2d::Sprite* ret = cocos2d::Sprite::create(arg0, arg1);
//            jsval jsret = JSVAL_NULL;
//            do {
//                if (ret) {
//                    js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, (cocos2d::Sprite*)ret);
//                    jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//                } else {
//                    jsret = JSVAL_NULL;
//                }
//            } while (0);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while (0);
//    JS_ReportError(cx, "js_crossapp_Sprite_create : wrong number of arguments");
//    return false;
//}
//
//bool js_crossapp_Sprite_initWithPolygon(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Sprite* cobj = (cocos2d::Sprite *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Sprite_initWithPolygon : Invalid Native Object");
//    if (argc == 1) {
//        cocos2d::PolygonInfo *arg0;
//        do {
//            if (args.get(0).isNull()) { arg0 = nullptr; break; }
//            if (!args.get(0).isObject()) { ok = false; break; }
//            js_proxy_t *jsProxy;
//            JSObject *tmpObj = args.get(0).toObjectOrNull();
//            jsProxy = jsb_get_js_proxy(tmpObj);
//            arg0 = (cocos2d::PolygonInfo*)(jsProxy ? jsProxy->ptr : NULL);
//            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
//        } while (0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Sprite_initWithPolygon : Error processing arguments");
//        bool ret = cobj->initWithPolygon(*arg0);
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_Sprite_initWithPolygon : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_Sprite_setPolygonInfo(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Sprite* cobj = (cocos2d::Sprite *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Sprite_setPolygonInfo : Invalid Native Object");
//    if (argc == 1) {
//        cocos2d::PolygonInfo *arg0;
//        do {
//            if (args.get(0).isNull()) { arg0 = nullptr; break; }
//            if (!args.get(0).isObject()) { ok = false; break; }
//            js_proxy_t *jsProxy;
//            JSObject *tmpObj = args.get(0).toObjectOrNull();
//            jsProxy = jsb_get_js_proxy(tmpObj);
//            arg0 = (cocos2d::PolygonInfo*)(jsProxy ? jsProxy->ptr : NULL);
//            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
//        } while (0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Sprite_setPolygonInfo : Error processing arguments");
//        cobj->setPolygonInfo(*arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_Sprite_setPolygonInfo : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_Sprite_textureLoaded(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    Sprite* cobj = (Sprite*)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj);
//    
//    bool ret = false;
//    if( cobj->getTexture() )
//        ret = true;
//
//    args.rval().set(BOOLEAN_TO_JSVAL(ret));
//    return true;
//}
//
//bool js_crossapp_CCTexture2D_setTexParameters(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    Texture2D* cobj = (Texture2D*)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//
//    if (argc == 4)
//    {
//        bool ok = true;
//
//        GLuint arg0, arg1, arg2, arg3;
//
//        ok &= jsval_to_uint32(cx, args.get(0), &arg0);
//        ok &= jsval_to_uint32(cx, args.get(1), &arg1);
//        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
//        ok &= jsval_to_uint32(cx, args.get(3), &arg3);
//
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        Texture2D::TexParams param = { arg0, arg1, arg2, arg3 };
//
//        cobj->setTexParameters(param);
//
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 4);
//    return false;       
//}
//
//bool js_crossapp_CCMenu_alignItemsInRows(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
//    bool ok = true;
//    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
//    Menu* cobj = (Menu*)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//
//    ValueVector items;
//    ok &= jsvals_variadic_to_ccvaluevector(cx, args.array(), argc, &items);
//    if (ok)
//    {
//        cobj->alignItemsInRowsWithArray(items);
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "Error in js_crossapp_CCMenu_alignItemsInRows");
//    return false;
//}
//
//bool js_crossapp_CCMenu_alignItemsInColumns(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject jsthis(cx, args.thisv().toObjectOrNull());
//    bool ok = true;
//    js_proxy_t *proxy = jsb_get_js_proxy(jsthis);
//    Menu* cobj = (Menu*)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//
//
//    ValueVector items;
//    ok &= jsvals_variadic_to_ccvaluevector(cx, args.array(), argc, &items);
//    if (ok)
//    {
//        cobj->alignItemsInColumnsWithArray(items);
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "Error in js_crossapp_CCMenu_alignItemsInColumns");
//    return false;
//}
//
//bool js_crossapp_CCLayer_init(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Layer* cobj = (cocos2d::Layer *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CCLayer_init : Invalid Native Object");
//    if (argc == 0) {
//        bool ret = cobj->init();
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_CCLayer_init : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//
//// TMXLayer
//bool js_crossapp_CCTMXLayer_getTileFlagsAt(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj;
//    TMXLayer* cobj;
//    obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cobj = (TMXLayer*)(proxy ? proxy->ptr : NULL);
//    TEST_NATIVE_OBJECT(cx, cobj)
//    if (argc == 1)
//    {
//        TMXTileFlags flags;
//        Point arg0;
//        ok &= jsval_to_ccpoint(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->getTileGIDAt(arg0, &flags);
//
//        args.rval().set(UINT_TO_JSVAL((uint32_t)flags));
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//static bool jsval_to_string_vector(JSContext* cx, jsval v, std::vector<std::string>& ret) {
//    JS::RootedObject jsobj(cx);
//    bool ok = JS_ValueToObject( cx, JS::RootedValue(cx, v), &jsobj );
//    JSB_PRECONDITION2( ok, cx, false, "Error converting value to object");
//    JSB_PRECONDITION2( jsobj && JS_IsArrayObject( cx, jsobj),  cx, false, "Object must be an array");
//    
//    uint32_t len = 0;
//    JS_GetArrayLength(cx, jsobj, &len);
//
//    for (uint32_t i=0; i < len; i++) {
//        JS::RootedValue elt(cx);
//        if (JS_GetElement(cx, jsobj, i, &elt)) {
//            
//            if (elt.isString())
//            {
//                JSStringWrapper str(elt.toString());
//                ret.push_back(str.get());
//            }
//        }
//    }
//
//    return true;
//}
//
//
//static jsval string_vector_to_jsval(JSContext* cx, const std::vector<std::string>& arr) {
//    
//    JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
//    
//    int i = 0;
//    for(std::vector<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); ++iter, ++i) {
//        JS::RootedValue arrElement(cx, std_string_to_jsval(cx, *iter));
//        if(!JS_SetElement(cx, jsretArr, i, arrElement)) {
//            break;
//        }
//    }
//    return OBJECT_TO_JSVAL(jsretArr);
//}
//
//bool js_crossapp_CCFileUtils_setSearchResolutionsOrder(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    
//    if (argc == 1) {
//        std::vector<std::string> arg0;
//        ok &= jsval_to_string_vector(cx, args.get(0), arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->setSearchResolutionsOrder(arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_CCFileUtils_setSearchPaths(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    
//    if (argc == 1) {
//        std::vector<std::string> arg0;
//        ok &= jsval_to_string_vector(cx, args.get(0), arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->setSearchPaths(arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//bool js_crossapp_CCFileUtils_getSearchPaths(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    
//    if (argc == 0) {
//        std::vector<std::string> ret = cobj->getSearchPaths();
//        jsval jsret;
//        jsret = string_vector_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//bool js_crossapp_CCFileUtils_getDataFromFile(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    
//    if (argc == 1) {
//        std::string arg0;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//
//        Data data = cobj->getDataFromFile(arg0);
//        do
//        {
//            if (!data.isNull())
//            {
//                uint32_t size = static_cast<uint32_t>(data.getSize());
//                JSObject* array = JS_NewUint8Array(cx, size);
//                if (nullptr == array)
//                    break;
//
//                uint8_t* bufdata = (uint8_t*)JS_GetArrayBufferViewData(array);
//                memcpy(bufdata, data.getBytes(), size*sizeof(uint8_t));
//
//                args.rval().set(OBJECT_TO_JSVAL(array));
//                return true;
//            }
//        } while(false);
//        
//        JS_ReportError(cx, "get file(%s) data fails", arg0.c_str());
//        return false;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 3);
//    return false;
//}
//
//bool js_crossapp_CCFileUtils_writeDataToFile(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CCFileUtils_writeDataToFile : Invalid Native Object");
//    if (argc == 2) {
//        Data arg0;
//        std::string arg1;
//
//        // copy bytes from UInit8Array
//        JSObject &obj0 = args.get(0).toObject();
//        if( JS_IsUint8Array(&obj0) ) {
//            uint32_t len = JS_GetArrayBufferViewByteLength(&obj0);
//            uint8_t* bufdata = (uint8_t*)JS_GetArrayBufferViewData(&obj0);
//            arg0.copy(bufdata, len);
//        } else {
//            ok = false;
//        }
//        
//        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CCFileUtils_writeDataToFile : Error processing arguments");
//        bool ret = cobj->writeDataToFile(arg0, arg1);
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_CCFileUtils_writeDataToFile : wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//bool js_crossapp_CCFileUtils_getSearchResolutionsOrder(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    
//    if (argc == 0) {
//        std::vector<std::string> ret = cobj->getSearchResolutionsOrder();
//        jsval jsret;
//        jsret = string_vector_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//static bool js_crossapp_FileUtils_createDictionaryWithContentsOfFile(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::FileUtils* cobj = (cocos2d::FileUtils *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    if (argc == 1) {
//        std::string arg0;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cocos2d::ValueMap ret = FileUtils::getInstance()->getValueMapFromFile(arg0.c_str());
//        jsval jsret;
//        jsret = ccvaluemap_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_CCGLProgram_setUniformLocationWith4f(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::GLProgram* cobj = (cocos2d::GLProgram *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    int arg0;
//    double arg1;
//    double arg2;
//    double arg3;
//    double arg4;
//    ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
//    ok &= JS::ToNumber(cx, args.get(1), &arg1);
//    
//    if(argc == 2) {
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->setUniformLocationWith1f(arg0, arg1);
//    }
//    if (argc == 3) {
//        ok &= JS::ToNumber(cx, args.get(2), &arg2);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->setUniformLocationWith2f(arg0, arg1, arg2);
//    }
//    if(argc == 4) {
//        ok &= JS::ToNumber(cx, args.get(2), &arg2);
//        ok &= JS::ToNumber(cx, args.get(3), &arg3);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->setUniformLocationWith3f(arg0, arg1, arg2, arg3);
//    }
//    if(argc == 5) {
//        ok &= JS::ToNumber(cx, args.get(2), &arg2);
//        ok &= JS::ToNumber(cx, args.get(3), &arg3);
//        ok &= JS::ToNumber(cx, args.get(4), &arg4);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        cobj->setUniformLocationWith4f(arg0, arg1, arg2, arg3, arg4);
//    }
//    
//    args.rval().setUndefined();
//    return true;
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 5);
//    return false;
//}
//
//bool js_crossapp_CCGLProgram_setUniformLocationWithMatrixfvUnion(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::GLProgram* cobj = (cocos2d::GLProgram *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    
//    if (argc == 4) {
//        GLint arg0;
//        std::vector<float> arg1;
//        unsigned int arg2;
//        int fvType;
//        ok &= jsval_to_int32(cx, args.get(0), (int *)&arg0);
//        ok &= jsval_to_std_vector_float(cx, args.get(1), &arg1);
//        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
//        ok &= jsval_to_int32(cx, args.get(3), (int *)&fvType);
//        
//        // fvType defined in jsb_cocos2d.js
//        switch(fvType)
//        {
//            case 2:
//                cobj->setUniformLocationWithMatrix2fv(arg0, (GLfloat *)&arg1[0], arg2);
//                break;
//            case 3:
//                cobj->setUniformLocationWithMatrix3fv(arg0, (GLfloat *)&arg1[0], arg2);
//                break;
//            case 4:
//                cobj->setUniformLocationWithMatrix4fv(arg0, (GLfloat *)&arg1[0], arg2);
//                break;
//        }
//        
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 4);
//    return false;
//}
//
//bool js_crossapp_CCGLProgram_create(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if(argc != 2) {
//        JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//        return false;
//    }
//    
//    const char *arg0, *arg1;
//    std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
//    std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
//
//    GLProgram* ret = new GLProgram();
//    ret->autorelease();
//    
//    ret->initWithFilenames(arg0, arg1);
//    
//    jsval jsret;
//    do {
//        if (ret) {
//            js_proxy_t *p = jsb_get_native_proxy(ret);
//            if (p) {
//                jsret = OBJECT_TO_JSVAL(p->obj);
//            } else {
//                // create a new js obj of that class
//                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::GLProgram>(cx, ret);
//                jsret = OBJECT_TO_JSVAL(proxy->obj);
//            }
//        } else {
//            jsret = JSVAL_NULL;
//        }
//    } while (0);
//    args.rval().set(jsret);
//    return true;
//
//}
//
//
//bool js_crossapp_CCGLProgram_createWithString(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if(argc != 2) {
//        JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
//        return false;
//    }
//    
//    const char *arg0, *arg1;
//    std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
//    std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
//    
//    GLProgram* ret = new GLProgram();
//    ret->initWithByteArrays(arg0, arg1);
//    
//    jsval jsret;
//    do {
//        if (ret) {
//            js_proxy_t *p = jsb_get_native_proxy(ret);
//            if (p) {
//                jsret = OBJECT_TO_JSVAL(p->obj);
//            } else {
//                // create a new js obj of that class
//                js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::GLProgram>(cx, ret);
//                jsret = OBJECT_TO_JSVAL(proxy->obj);
//            }
//        } else {
//            jsret = JSVAL_NULL;
//        }
//    } while (0);
//    args.rval().set(jsret);
//    return true;
//    
//}
//
//bool js_crossapp_CCGLProgram_getProgram(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::GLProgram* cobj = (cocos2d::GLProgram *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
//    if (argc == 0) {
//        GLuint ret = cobj->getProgram();
//        args.rval().set(UINT_TO_JSVAL((uint32_t)ret));
//        return true;
//    }
//    
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//bool js_crossapp_GLProgramState_setVertexAttribPointer(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::GLProgramState* cobj = (cocos2d::GLProgramState *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_GLProgramState_setVertexAttribPointer : Invalid Native Object");
//    if (argc == 6) {
//        std::string arg0;
//        int arg1;
//        unsigned int arg2;
//        uint16_t arg3;
//        int arg4;
//        long arg5;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
//        ok &= jsval_to_uint32(cx, args.get(2), &arg2);
//        ok &= jsval_to_uint16(cx, args.get(3), &arg3);
//        ok &= jsval_to_int32(cx, args.get(4), (int32_t *)&arg4);
//        ok &= jsval_to_long(cx, args.get(5), &arg5);
//
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_GLProgramState_setVertexAttribPointer : Error processing arguments");
//        cobj->setVertexAttribPointer(arg0, arg1, arg2, arg3, arg4, (GLvoid*)arg5);
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_GLProgramState_setVertexAttribPointer : wrong number of arguments: %d, was expecting %d", argc, 6);
//    return false;
//}
//
//bool js_crossapp_GLProgramState_setUniformVec4(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t* proxy = jsb_get_js_proxy(obj);
//    cocos2d::GLProgramState* cobj = (cocos2d::GLProgramState *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_GLProgramState_setUniformVec4 : Invalid Native Object");
//    bool ok = true;
//    if(argc == 2)
//    {
//        do {
//            if (argc == 2) {
//                std::string arg0;
//                ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//                if (!ok) { ok = true; break; }
//                cocos2d::Vec4 arg1;
//                ok &= jsval_to_vector4(cx, args.get(1), &arg1);
//                if (!ok) { ok = true; break; }
//                cobj->setUniformVec4(arg0, arg1);
//                args.rval().setUndefined();
//                return true;
//            }
//        } while(0);
//
//        do {
//            if (argc == 2) {
//                int arg0;
//                ok &= jsval_to_int(cx, args.get(0), &arg0);
//                if (!ok) { ok = true; break; }
//                cocos2d::Vec4 arg1;
//                ok &= jsval_to_vector4(cx, args.get(1), &arg1);
//                if (!ok) { ok = true; break; }
//                cobj->setUniformVec4(arg0, arg1);
//                args.rval().setUndefined();
//                return true;
//            }
//        } while(0);
//    }
//    JS_ReportError(cx, "js_crossapp_GLProgramState_setUniformVec4 : wrong number of arguments: %d, was expecting %d", argc, 2);
//    return false;
//}
//
//#define js_crossapp_CCCamera_getXYZ(funcName) \
//    bool ok = true;                                                                                                  \
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);                                                                               \
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);                                                                            \
//    cocos2d::Camera* cobj = (cocos2d::Camera *)(proxy ? proxy->ptr : NULL);                                           \
//    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");                                                      \
//    if (argc == 0) {                                                                                                      \
//        float x;                                                                                                          \
//        float y;                                                                                                          \
//        float z;                                                                                                          \
//        cobj->funcName(&x, &y, &z);                                                                                       \
//        JSObject* tmp = JS_NewObject(cx, NULL, NULL, NULL);                                                               \
//                                                                                                                          \
//        do                                                                                                                \
//        {                                                                                                                 \
//            if (NULL == tmp) break;                                                                                       \
//                                                                                                                          \
//            ok = JS_DefineProperty(cx, tmp, "x", DOUBLE_TO_JSVAL(x), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&  \
//            JS_DefineProperty(cx, tmp, "y", DOUBLE_TO_JSVAL(y), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT) &&       \
//            JS_DefineProperty(cx, tmp, "z", DOUBLE_TO_JSVAL(z), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);         \
//                                                                                                                          \
//            if (ok) {                                                                                                     \
//                JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(tmp));                                                                \
//                return true;                                                                                           \
//            }                                                                                                             \
//        } while (false);                                                                                                  \
//                                                                                                                          \
//        JS_SET_RVAL(cx, vp, JSVAL_NULL);                                                                                  \
//        return true;                                                                                                   \
//    }                                                                                                                     \
//                                                                                                                          \
//    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);                                       \
//    return false;
//
//
//
//bool js_crossapp_SpriteBatchNode_getDescendants(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::SpriteBatchNode* cobj = (cocos2d::SpriteBatchNode *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_SpriteBatchNode_getDescendants : Invalid Native Object");
//    if (argc == 0) {
//        std::vector<Sprite*> ret = cobj->getDescendants();
//        
//        JS::RootedObject jsretArr(cx, JS_NewArrayObject(cx, 0));
//        size_t vSize = ret.size();
//        JS::RootedValue jsret(cx);
//        for (size_t i = 0; i < vSize; i++)
//        {
//            proxy = js_get_or_create_proxy<cocos2d::Sprite>(cx, ret[i]);
//            jsret = OBJECT_TO_JSVAL(proxy->obj);
//            JS_SetElement(cx, jsretArr, static_cast<uint32_t>(i), jsret);
//        }
//        args.rval().set(OBJECT_TO_JSVAL(jsretArr));
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_SpriteBatchNode_getDescendants : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//bool js_crossapp_NodeGrid_setGrid(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::NodeGrid* cobj = (cocos2d::NodeGrid *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_NodeGrid_setGrid : Invalid Native Object");
//    if (argc == 1) {
//        cocos2d::GridBase* arg0;
//        do {
//            if(args.get(0).isNull()) { arg0 = nullptr; break;}
//            if (!args.get(0).isObject()) { ok = false; break; }
//            JSObject *tmpObj = args.get(0).toObjectOrNull();
//            proxy = jsb_get_js_proxy(tmpObj);
//            arg0 = (cocos2d::GridBase*)(proxy ? proxy->ptr : NULL);
//            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
//        } while (0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_NodeGrid_setGrid : Error processing arguments");
//        cobj->setGrid(arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_NodeGrid_setGrid : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//// cc.PlistParser.getInstance()
//bool js_PlistParser_getInstance(JSContext *cx, unsigned argc, JS::Value *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    __JSPlistDelegator* delegator = __JSPlistDelegator::getInstance();
//    SAXParser* parser = delegator->getParser();
//    
//    jsval jsret;
//    if (parser) {
//        js_proxy_t *p = jsb_get_native_proxy(parser);
//        if (p) {
//            jsret = OBJECT_TO_JSVAL(p->obj);
//        } else {
//            // create a new js obj of that class
//            js_proxy_t *proxy = js_get_or_create_proxy<SAXParser>(cx, parser);
//            jsret = OBJECT_TO_JSVAL(proxy->obj);
//        }
//    } else {
//        jsret = JSVAL_NULL;
//    }
//    args.rval().set(jsret);
//    
//    return true;
//}
//// cc.PlistParser.getInstance().parse(text)
//bool js_PlistParser_parse(JSContext *cx, unsigned argc, JS::Value *vp) {
//    __JSPlistDelegator* delegator = __JSPlistDelegator::getInstance();
//    
//    bool ok = true;
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    if (argc == 1) {
//        std::string arg0;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
//        
//        std::string parsedStr = delegator->parseText(arg0);
//        std::replace(parsedStr.begin(), parsedStr.end(), '\n', ' ');
//        
//        jsval strVal = std_string_to_jsval(cx, parsedStr);
//        // create a new js obj of the parsed string
//        JS::RootedValue outVal(cx);
//
//        //JS_GetStringCharsZ was removed in SpiderMonkey 33
//        //ok = JS_ParseJSON(cx, JS_GetStringCharsZ(cx, strVal), static_cast<uint32_t>(JS_GetStringEncodingLength(JSVAL_TO_STRING(strVal))), &outVal);
//        ok = JS_ParseJSON(cx, JS::RootedString(cx, strVal.toString()), &outVal);
//        
//        if (ok)
//            args.rval().set(outVal);
//        else {
//            args.rval().setUndefined();
//            JS_ReportError(cx, "js_PlistParser_parse : parse error");
//        }
//        return true;
//    }
//    JS_ReportError(cx, "js_PlistParser_parse : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//cocos2d::SAXParser* __JSPlistDelegator::getParser() {
//    return &_parser;
//}
//
//std::string __JSPlistDelegator::parse(const std::string& path) {
//    _result.clear();
//    
//    SAXParser parser;
//    if (false != parser.init("UTF-8") )
//    {
//        parser.setDelegator(this);
//        parser.parse(FileUtils::getInstance()->fullPathForFilename(path).c_str());
//    }
//    
//    return _result;
//}
//
//__JSPlistDelegator::~__JSPlistDelegator(){
//    CCLOGINFO("deallocing __JSSAXDelegator: %p", this);
//}
//
//std::string __JSPlistDelegator::parseText(const std::string& text){
//     _result.clear();
//    
//    SAXParser parser;
//    if (false != parser.init("UTF-8") )
//    {
//        parser.setDelegator(this);
//        parser.parse(text.c_str(), text.size());
//    }
//    
//    return _result;
//}
//
//void __JSPlistDelegator::startElement(void *ctx, const char *name, const char **atts) {
//    _isStoringCharacters = true;
//    _currentValue.clear();
//    
//    std::string elementName = (char*)name;
//    
//    int end = (int)_result.size() - 1;
//    if(end >= 0 && _result[end] != '{' && _result[end] != '[' && _result[end] != ':') {
//        _result += ",";
//    }
//    
//    if (elementName == "dict") {
//        _result += "{";
//    }
//    else if (elementName == "array") {
//        _result += "[";
//    }
//}
//
//void __JSPlistDelegator::endElement(void *ctx, const char *name) {
//    _isStoringCharacters = false;
//    std::string elementName = (char*)name;
//    
//    if (elementName == "dict") {
//        _result += "}";
//    }
//    else if (elementName == "array") {
//        _result += "]";
//    }
//    else if (elementName == "key") {
//        _result += "\"" + _currentValue + "\":";
//    }
//    else if (elementName == "string") {
//        _result += "\"" + _currentValue + "\"";
//    }
//    else if (elementName == "false" || elementName == "true") {
//        _result += elementName;
//    }
//    else if (elementName == "real" || elementName == "integer") {
//        _result += _currentValue;
//    }
//}
//
//void __JSPlistDelegator::textHandler(void *ctx, const char *ch, int len) {
//    CC_UNUSED_PARAM(ctx);
//    std::string text((char*)ch, 0, len);
//    
//    if (_isStoringCharacters)
//    {
//        _currentValue += text;
//    }
//}
//
//bool jsval_to_TTFConfig(JSContext *cx, jsval v, TTFConfig* ret) {
//    JS::RootedObject tmp(cx);
//    JS::RootedValue js_fontFilePath(cx);
//    JS::RootedValue js_fontSize(cx);
//    JS::RootedValue js_outlineSize(cx);
//    JS::RootedValue js_glyphs(cx);
//    JS::RootedValue js_customGlyphs(cx);
//    JS::RootedValue js_distanceFieldEnable(cx);
//
//    std::string fontFilePath,customGlyphs;
//    double fontSize, glyphs, outlineSize;
//
//    bool ok = v.isObject() &&
//        JS_ValueToObject(cx, JS::RootedValue(cx, v), &tmp) &&
//        JS_GetProperty(cx, tmp, "fontFilePath", &js_fontFilePath) &&
//        JS_GetProperty(cx, tmp, "fontSize", &js_fontSize) &&
//        JS_GetProperty(cx, tmp, "outlineSize", &js_outlineSize) &&
//        JS_GetProperty(cx, tmp, "glyphs", &js_glyphs) &&
//        JS_GetProperty(cx, tmp, "customGlyphs", &js_customGlyphs) &&
//        JS_GetProperty(cx, tmp, "distanceFieldEnable", &js_distanceFieldEnable) &&
//        JS::ToNumber(cx, js_fontSize, &fontSize) &&
//        JS::ToNumber(cx, js_outlineSize, &outlineSize) &&
//        JS::ToNumber(cx, js_glyphs, &glyphs) &&
//        jsval_to_std_string(cx,js_fontFilePath,&ret->fontFilePath) &&
//        jsval_to_std_string(cx,js_customGlyphs,&customGlyphs);
//    bool distanceFieldEnable = JS::ToBoolean(js_distanceFieldEnable);
//
//    JSB_PRECONDITION3(ok, cx, false, "Error processing arguments");
//
//    ret->fontSize = (int)fontSize;
//    ret->outlineSize = (int)outlineSize;
//    ret->glyphs = GlyphCollection((int)glyphs);
//    ret->distanceFieldEnabled = distanceFieldEnable;
//    if(ret->glyphs == GlyphCollection::CUSTOM && customGlyphs.length() > 0)
//        ret->customGlyphs = customGlyphs.c_str();
//    else
//        ret->customGlyphs = nullptr;
//
//    return true;
//}
//
//bool js_crossapp_Label_createWithTTF(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    if (argc < 2)
//        return false;
//
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//
//    TTFConfig ttfConfig("");
//    std::string text;
//
//    ok &= jsval_to_TTFConfig(cx, args.get(0), &ttfConfig);
//    ok &= jsval_to_std_string(cx, args.get(1), &text);
//
//    cocos2d::Label* ret = nullptr;
//
//    if (argc == 2) {
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Label_createWithTTF : Error processing arguments");
//        ret = cocos2d::Label::createWithTTF(ttfConfig, text);
//        jsval jsret = JSVAL_NULL;
//        if (ret) {
//            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Label>(cx, (cocos2d::Label*)ret);
//            jsret = OBJECT_TO_JSVAL(proxy->obj);
//        }
//        args.rval().set(jsret);
//        return true;
//    }
//    if (argc == 3) {
//        int arg2;
//        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Label_createWithTTF : Error processing arguments");
//        TextHAlignment alignment = TextHAlignment(arg2);
//        ret = cocos2d::Label::createWithTTF(ttfConfig, text, alignment);
//        jsval jsret = JSVAL_NULL;
//        if (ret) {
//            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Label>(cx, (cocos2d::Label*)ret);
//            jsret = OBJECT_TO_JSVAL(proxy->obj);
//        }
//        args.rval().set(jsret);
//        return true;
//    }
//    if (argc == 4) {
//        int arg2,arg3;
//        ok &= jsval_to_int32(cx, args.get(2), (int32_t *)&arg2);
//        ok &= jsval_to_int32(cx, args.get(3), (int32_t *)&arg3);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Label_createWithTTF : Error processing arguments");
//        TextHAlignment alignment = TextHAlignment(arg2);
//        ret = cocos2d::Label::createWithTTF(ttfConfig, text, alignment, arg3);
//        jsval jsret = JSVAL_NULL;
//        if (ret) {
//            js_proxy_t *proxy = js_get_or_create_proxy<cocos2d::Label>(cx, (cocos2d::Label*)ret);
//            jsret = OBJECT_TO_JSVAL(proxy->obj);
//        }
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_Label_createWithTTF : wrong number of arguments");
//    return false;
//}
//
//bool js_crossapp_Label_setTTFConfig(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JSObject *obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Label* cobj = (cocos2d::Label *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Label_setTTFConfig : Invalid Native Object");
//
//    if (argc == 1) {
//        TTFConfig ttfConfig("");
//        do {
//            if (!args.get(0).isObject()) { ok = false; break; }
//            ok &= jsval_to_TTFConfig(cx, args.get(0), &ttfConfig);
//        } while (0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Label_setTTFConfig : Error processing arguments");
//        cobj->setTTFConfig(ttfConfig);
//        args.rval().setUndefined();
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_Label_setTTFConfig : wrong number of arguments");
//    return false;
//}
//
//bool js_crossapp_RenderTexture_saveToFile(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    
//    JSObject *obj = NULL;
//    cocos2d::RenderTexture* cobj = NULL;
//    obj = JS_THIS_OBJECT(cx, vp);
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cobj = (cocos2d::RenderTexture *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_RenderTexture_saveToFile : Invalid Native Object");
//    do {
//        if (argc == 2) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cocos2d::Image::Format arg1;
//            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
//            if (!ok) { ok = true; break; }
//            bool ret = cobj->saveToFile(arg0, arg1);
//            jsval jsret = JSVAL_NULL;
//            jsret = BOOLEAN_TO_JSVAL(ret);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while(0);
//    
//    do {
//        if (argc == 3) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cocos2d::Image::Format arg1;
//            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
//            if (!ok) { ok = true; break; }
//            bool arg2;
//            arg2 = JS::ToBoolean(JS::RootedValue(cx, args.get(2)));
//            bool ret = cobj->saveToFile(arg0, arg1, arg2);
//            jsval jsret = JSVAL_NULL;
//            jsret = BOOLEAN_TO_JSVAL(ret);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while(0);
//    
//    do {
//        if (argc == 4) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cocos2d::Image::Format arg1;
//            ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
//            if (!ok) { ok = true; break; }
//            bool arg2;
//            arg2 = JS::ToBoolean(JS::RootedValue(cx, args.get(2)));
//            std::function<void (cocos2d::RenderTexture *, const std::basic_string<char> &)> arg3;
//            do {
//                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(3)));
//                auto lambda = [=](cocos2d::RenderTexture* larg0, const std::string& larg1) -> void {
//                    jsval largv[2];
//                    do {
//                        if (larg0) {
//                            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::RenderTexture>(cx, (cocos2d::RenderTexture*)larg0);
//                            largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
//                        } else {
//                            largv[0] = JSVAL_NULL;
//                        }
//                    } while (0);
//                    do {
//                        largv[1] = std_string_to_jsval(cx, larg1);
//                    } while (0);
//                    JS::RootedValue rval(cx);
//                    bool invokeOk = func->invoke(2, largv, &rval);
//                    if (!invokeOk && JS_IsExceptionPending(cx)) {
//                        JS_ReportPendingException(cx);
//                    }
//                };
//                arg3 = lambda;
//            } while(0)
//                ;
//            if (!ok) { ok = true; break; }
//            bool ret = cobj->saveToFile(arg0, arg1, arg2, arg3);
//            jsval jsret = JSVAL_NULL;
//            jsret = BOOLEAN_TO_JSVAL(ret);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while(0);
//    
//    do {
//        if (argc == 1) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            bool ret = cobj->saveToFile(arg0);
//            jsval jsret = JSVAL_NULL;
//            jsret = BOOLEAN_TO_JSVAL(ret);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while(0);
//    
//    do {
//        if (argc == 2) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            bool arg1;
//            arg1 = JS::ToBoolean(JS::RootedValue(cx, args.get(1)));
//            bool ret = cobj->saveToFile(arg0, arg1);
//            jsval jsret = JSVAL_NULL;
//            jsret = BOOLEAN_TO_JSVAL(ret);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while(0);
//    
//    do {
//        if (argc == 3) {
//            std::string arg0;
//            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            bool arg1;
//            arg1 = JS::ToBoolean(JS::RootedValue(cx, args.get(1)));
//            std::function<void (cocos2d::RenderTexture *, const std::basic_string<char> &)> arg2;
//            do {
//                std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, JS_THIS_OBJECT(cx, vp), args.get(2)));
//                auto lambda = [=](cocos2d::RenderTexture* larg0, const std::string& larg1) -> void {
//                    jsval largv[2];
//                    do {
//                        if (larg0) {
//                            js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::RenderTexture>(cx, (cocos2d::RenderTexture*)larg0);
//                            largv[0] = OBJECT_TO_JSVAL(jsProxy->obj);
//                        } else {
//                            largv[0] = JSVAL_NULL;
//                        }
//                    } while (0);
//                    do {
//                        largv[1] = std_string_to_jsval(cx, larg1);
//                    } while (0);
//                    JS::RootedValue rval(cx);
//                    bool invokeOk = func->invoke(2, largv, &rval);
//                    if (!invokeOk && JS_IsExceptionPending(cx)) {
//                        JS_ReportPendingException(cx);
//                    }
//                };
//                arg2 = lambda;
//            } while(0)
//                ;
//            if (!ok) { ok = true; break; }
//            bool ret = cobj->saveToFile(arg0, arg1, arg2);
//            jsval jsret = JSVAL_NULL;
//            jsret = BOOLEAN_TO_JSVAL(ret);
//            args.rval().set(jsret);
//            return true;
//        }
//    } while(0);
//    
//    JS_ReportError(cx, "js_crossapp_RenderTexture_saveToFile : wrong number of arguments");
//    return false;
//}
//
//bool js_crossapp_Camera_unproject(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Camera* cobj = (cocos2d::Camera *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Camera_unproject : Invalid Native Object");
//    if (argc >= 2) {
//        cocos2d::Size arg0;
//        cocos2d::Vec3 arg1;
//        cocos2d::Vec3 ret;
//        ok &= jsval_to_ccsize(cx, args.get(0), &arg0);
//        ok &= jsval_to_vector3(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Camera_unproject : Error processing arguments");
//        cobj->unproject(arg0, &arg1, &ret);
//        args.rval().set(vector3_to_jsval(cx, ret));
//        return true;
//    }
//    else if (argc == 1)
//    {
//        cocos2d::Vec3 arg0;
//        ok &= jsval_to_vector3(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Camera_unproject : Error processing arguments");
//        cocos2d::Vec3 ret = cobj->unproject(arg0);
//        args.rval().set(vector3_to_jsval(cx, ret));
//        return true;
//    }
//    JS_ReportError(cx, "js_crossapp_Camera_unproject : wrong number of arguments: %d, was expecting %d", argc, 3);
//    return false;
//}
//
//bool js_crossapp_Camera_isVisibleInFrustum(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Camera* cobj = (cocos2d::Camera *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Camera_isVisibleInFrustum : Invalid Native Object");
//    if (argc == 1) {
//         cocos2d::Vec3  min;
//        JS::RootedValue jsmin(cx);
//        ok &= JS_GetProperty(cx, JS::RootedObject(cx, args.get(0).toObjectOrNull()), "min", &jsmin);
//        ok &= jsval_to_vector3(cx, jsmin, &min);
//
//        cocos2d::Vec3 max;
//        JS::RootedValue jsmax(cx);
//        ok &= JS_GetProperty(cx, JS::RootedObject(cx, args.get(0).toObjectOrNull()), "max", &jsmax);
//        ok &= jsval_to_vector3(cx, jsmax, &max);
//
//        cocos2d::AABB aabb(min, max);
//
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Camera_isVisibleInFrustum : Error processing arguments");
//        bool ret = cobj->isVisibleInFrustum(&aabb);
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//
//    JS_ReportError(cx, "js_crossapp_Camera_isVisibleInFrustum : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//bool js_crossapp_Node_setAdditionalTransform(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//
//    JS::RootedObject obj(cx);
//    cocos2d::Node* cobj = NULL;
//    obj = args.thisv().toObjectOrNull();
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cobj = (cocos2d::Node *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Node_setAdditionalTransform : Invalid Native Object");
//
//    do {
//        if (argc == 1) {
//            cocos2d::Mat4 arg0;
//            ok &= jsval_to_matrix(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cobj->setAdditionalTransform(&arg0);
//            args.rval().setUndefined();
//            return true;
//        }
//    } while(0);
//
//    do {
//        if (argc == 1) {
//            cocos2d::AffineTransform arg0;
//            ok &= jsval_to_ccaffinetransform(cx, args.get(0), &arg0);
//            if (!ok) { ok = true; break; }
//            cobj->setAdditionalTransform(arg0);
//            args.rval().setUndefined();
//            return true;
//        }
//    } while(0);
//
//    JS_ReportError(cx, "js_crossapp_Node_setAdditionalTransform : wrong number of arguments");
//    return false;
//}
//
//bool js_crossapp_ClippingNode_init(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::ClippingNode* cobj = (cocos2d::ClippingNode *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_ClippingNode_init : Invalid Native Object");
//    if (argc == 0) {
//        bool ret = cobj->init();
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    if (argc == 1) {
//        cocos2d::Node* arg0;
//        do {
//            if (!args.get(0).isObject()) { ok = false; break; }
//            js_proxy_t *jsProxy;
//            JSObject *tmpObj = args.get(0).toObjectOrNull();
//            jsProxy = jsb_get_js_proxy(tmpObj);
//            arg0 = (cocos2d::Node*)(jsProxy ? jsProxy->ptr : NULL);
//            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
//        } while (0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_ClippingNode_init : Error processing arguments");
//        bool ret = cobj->init(arg0);
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_ClippingNode_init : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//
//// EventKeyboard class bindings, need manual bind for transform key codes
//
//JSClass  *jsb_cocos2d_EventKeyboard_class;
//JSObject *jsb_cocos2d_EventKeyboard_prototype;
//
//bool js_crossapp_EventKeyboard_constructor(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    
//    cocos2d::EventKeyboard::KeyCode arg0;
//    ScriptingCore *core = ScriptingCore::getInstance();
//    JS::RootedValue retVal(cx);
//    core->executeFunctionWithOwner(OBJECT_TO_JSVAL(core->getGlobalObject()), "parseKeyCode", args, &retVal);
//    ok &= jsval_to_int32(cx, retVal, (int32_t *)&arg0);
//    
//    bool arg1;
//    arg1 = JS::ToBoolean(JS::RootedValue(cx, args.get(1)));
//    
//    JSB_PRECONDITION2(ok, cx, false, "js_crossapp_EventKeyboard_constructor : Error processing arguments");
//    
//    cocos2d::EventKeyboard* cobj = new (std::nothrow) cocos2d::EventKeyboard(arg0, arg1);
//    cocos2d::Ref *_ccobj = dynamic_cast<cocos2d::Ref *>(cobj);
//    if (_ccobj) {
//        _ccobj->autorelease();
//    }
//    TypeTest<cocos2d::EventKeyboard> t;
//    js_type_class_t *typeClass = nullptr;
//    std::string typeName = t.s_name();
//    auto typeMapIter = _js_global_type_map.find(typeName);
//    CCAssert(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
//    typeClass = typeMapIter->second;
//    CCAssert(typeClass, "The value is null.");
//    JSObject *obj = JS_NewObject(cx, typeClass->jsclass, JS::RootedObject(cx, typeClass->proto), JS::RootedObject(cx, typeClass->parentProto));
//    args.rval().set( OBJECT_TO_JSVAL(obj));
//    // link the native object with the javascript object
//    js_proxy_t* p = jsb_new_proxy(cobj, obj);
//    JS::AddNamedObjectRoot(cx, &p->obj, "cocos2d::EventKeyboard");
//    return true;
//}
//
//
//extern JSObject *jsb_cocos2d_Event_prototype;
//
//void js_cocos2d_EventKeyboard_finalize(JSFreeOp *fop, JSObject *obj) {
//    CCLOGINFO("jsbindings: finalizing JS object %p (EventKeyboard)", obj);
//}
//
//static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    args.rval().set(BOOLEAN_TO_JSVAL(true));
//    return true;
//}
//
//void js_register_crossapp_EventKeyboard(JSContext *cx, JS::HandleObject global) {
//    jsb_cocos2d_EventKeyboard_class = (JSClass *)calloc(1, sizeof(JSClass));
//    jsb_cocos2d_EventKeyboard_class->name = "EventKeyboard";
//    jsb_cocos2d_EventKeyboard_class->addProperty = JS_PropertyStub;
//    jsb_cocos2d_EventKeyboard_class->delProperty = JS_DeletePropertyStub;
//    jsb_cocos2d_EventKeyboard_class->getProperty = JS_PropertyStub;
//    jsb_cocos2d_EventKeyboard_class->setProperty = JS_StrictPropertyStub;
//    jsb_cocos2d_EventKeyboard_class->enumerate = JS_EnumerateStub;
//    jsb_cocos2d_EventKeyboard_class->resolve = JS_ResolveStub;
//    jsb_cocos2d_EventKeyboard_class->convert = JS_ConvertStub;
//    jsb_cocos2d_EventKeyboard_class->finalize = js_cocos2d_EventKeyboard_finalize;
//    jsb_cocos2d_EventKeyboard_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
//    
//    static JSPropertySpec properties[] = {
//        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_ENUMERATE | JSPROP_PERMANENT),
//        JS_PS_END
//    };
//    
//    static JSFunctionSpec funcs[] = {
//        JS_FS_END
//    };
//    
//    JSFunctionSpec *st_funcs = NULL;
//    
//    jsb_cocos2d_EventKeyboard_prototype = JS_InitClass(
//                                                       cx, global,
//                                                       JS::RootedObject(cx, jsb_cocos2d_Event_prototype),
//                                                       jsb_cocos2d_EventKeyboard_class,
//                                                       js_crossapp_EventKeyboard_constructor, 0, // constructor
//                                                       properties,
//                                                       funcs,
//                                                       NULL, // no static properties
//                                                       st_funcs);
//    // make the class enumerable in the registered namespace
//    //  bool found;
//    //FIXME: Removed in Firefox v27
//    //  JS_SetPropertyAttributes(cx, global, "EventKeyboard", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
//    
//    // add the proto and JSClass to the type->js info hash table
//    TypeTest<cocos2d::EventKeyboard> t;
//    js_type_class_t *p;
//    std::string typeName = t.s_name();
//    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
//    {
//        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
//        p->jsclass = jsb_cocos2d_EventKeyboard_class;
//        p->proto = jsb_cocos2d_EventKeyboard_prototype;
//        p->parentProto = jsb_cocos2d_Event_prototype;
//        _js_global_type_map.insert(std::make_pair(typeName, p));
//    }
//}
//
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

//#if CC_ENABLE_BULLET_INTEGRATION && CC_USE_3D_PHYSICS
//
//#include "physics3d/CCPhysics3D.h"
//
//bool js_crossapp_Scene_setPhysics3DDebugCamera(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Scene* cobj = (cocos2d::Scene *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Scene_setPhysics3DDebugCamera : Invalid Native Object");
//    if (argc == 1)
//    {
//        cocos2d::Camera* arg0;
//        do
//        {
//            if (!args.get(0).isObject()) { ok = false; break; }
//            js_proxy_t *jsProxy;
//            JSObject *tmpObj = args.get(0).toObjectOrNull();
//            jsProxy = jsb_get_js_proxy(tmpObj);
//            arg0 = (cocos2d::Camera*)(jsProxy ? jsProxy->ptr : NULL);
//            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
//        } while (0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Scene_setPhysics3DDebugCamera : Error processing arguments");
//        cobj->setPhysics3DDebugCamera(arg0);
//        args.rval().setUndefined();
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_Scene_setPhysics3DDebugCamera : wrong number of arguments: %d, was expecting %d", argc, 1);
//    return false;
//}
//bool js_crossapp_Scene_initWithPhysics(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Scene* cobj = (cocos2d::Scene *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Scene_initWithPhysics : Invalid Native Object");
//    if (argc == 0)
//    {
//        bool ret = cobj->initWithPhysics();
//        jsval jsret = JSVAL_NULL;
//        jsret = BOOLEAN_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_Scene_initWithPhysics : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//bool js_crossapp_Scene_getPhysics3DWorld(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::Scene* cobj = (cocos2d::Scene *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_Scene_getPhysics3DWorld : Invalid Native Object");
//    if (argc == 0)
//    {
//        cocos2d::Physics3DWorld* ret = cobj->getPhysics3DWorld();
//        jsval jsret = JSVAL_NULL;
//        do
//        {
//            if (ret)
//            {
//                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::Physics3DWorld>(cx, (cocos2d::Physics3DWorld*)ret);
//                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//            } else
//            {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_Scene_getPhysics3DWorld : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//#endif //CC_ENABLE_BULLET_INTEGRATION && CC_USE_3D_PHYSICS
//#if CC_USE_NAVMESH
//bool js_crossapp_Scene_setNavMeshDebugCamera(JSContext *cx, uint32_t argc, jsval *vp)
//{
//	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//	bool ok = true;
//	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//	js_proxy_t *proxy = jsb_get_js_proxy(obj);
//	cocos2d::Scene* cobj = (cocos2d::Scene *)(proxy ? proxy->ptr : NULL);
//	JSB_PRECONDITION2(cobj, cx, false, "js_crossapp_Scene_setNavMeshDebugCamera : Invalid Native Object");
//	if (argc == 1) {
//		cocos2d::Camera* arg0;
//		do {
//			if (args.get(0).isNull()) { arg0 = nullptr; break; }
//			if (!args.get(0).isObject()) { ok = false; break; }
//			js_proxy_t *jsProxy;
//			JSObject *tmpObj = args.get(0).toObjectOrNull();
//			jsProxy = jsb_get_js_proxy(tmpObj);
//			arg0 = (cocos2d::Camera*)(jsProxy ? jsProxy->ptr : NULL);
//			JSB_PRECONDITION2(arg0, cx, false, "Invalid Native Object");
//		} while (0);
//		JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Scene_setNavMeshDebugCamera : Error processing arguments");
//		cobj->setNavMeshDebugCamera(arg0);
//		args.rval().setUndefined();
//		return true;
//	}
//
//	JS_ReportError(cx, "js_crossapp_Scene_setNavMeshDebugCamera : wrong number of arguments: %d, was expecting %d", argc, 1);
//	return false;
//}
//bool js_crossapp_Scene_setNavMesh(JSContext *cx, uint32_t argc, jsval *vp)
//{
//	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//	bool ok = true;
//	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//	js_proxy_t *proxy = jsb_get_js_proxy(obj);
//	cocos2d::Scene* cobj = (cocos2d::Scene *)(proxy ? proxy->ptr : NULL);
//	JSB_PRECONDITION2(cobj, cx, false, "js_crossapp_Scene_setNavMesh : Invalid Native Object");
//	if (argc == 1) {
//		cocos2d::NavMesh* arg0;
//		do {
//			if (args.get(0).isNull()) { arg0 = nullptr; break; }
//			if (!args.get(0).isObject()) { ok = false; break; }
//			js_proxy_t *jsProxy;
//			JSObject *tmpObj = args.get(0).toObjectOrNull();
//			jsProxy = jsb_get_js_proxy(tmpObj);
//			arg0 = (cocos2d::NavMesh*)(jsProxy ? jsProxy->ptr : NULL);
//			JSB_PRECONDITION2(arg0, cx, false, "Invalid Native Object");
//		} while (0);
//		JSB_PRECONDITION2(ok, cx, false, "js_crossapp_Scene_setNavMesh : Error processing arguments");
//		cobj->setNavMesh(arg0);
//		args.rval().setUndefined();
//		return true;
//	}
//
//	JS_ReportError(cx, "js_crossapp_Scene_setNavMesh : wrong number of arguments: %d, was expecting %d", argc, 1);
//	return false;
//}
//bool js_crossapp_Scene_getNavMesh(JSContext *cx, uint32_t argc, jsval *vp)
//{
//	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//	js_proxy_t *proxy = jsb_get_js_proxy(obj);
//	cocos2d::Scene* cobj = (cocos2d::Scene *)(proxy ? proxy->ptr : NULL);
//	JSB_PRECONDITION2(cobj, cx, false, "js_crossapp_Scene_getNavMesh : Invalid Native Object");
//	if (argc == 0) {
//		cocos2d::NavMesh* ret = cobj->getNavMesh();
//		jsval jsret = JSVAL_NULL;
//		do {
//			if (ret) {
//				js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::NavMesh>(cx, (cocos2d::NavMesh*)ret);
//				jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//			}
//			else {
//				jsret = JSVAL_NULL;
//			}
//		} while (0);
//		args.rval().set(jsret);
//		return true;
//	}
//
//	JS_ReportError(cx, "js_crossapp_Scene_getNavMesh : wrong number of arguments: %d, was expecting %d", argc, 0);
//	return false;
//}
//#endif //CC_USE_NAVMESH
//
//JSClass  *jsb_cocos2d_PolygonInfo_class;
//JSObject *jsb_cocos2d_PolygonInfo_prototype;
//
//bool js_crossapp_PolygonInfo_getArea(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_PolygonInfo_getArea : Invalid Native Object");
//    if (argc == 0)
//    {
//        const float ret = cobj->getArea();
//        jsval jsret = JSVAL_NULL;
//        jsret = DOUBLE_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_PolygonInfo_getArea : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//bool js_crossapp_PolygonInfo_getTriaglesCount(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_PolygonInfo_getTriaglesCount : Invalid Native Object");
//    if (argc == 0)
//    {
//        const unsigned int ret = cobj->getTriaglesCount();
//        jsval jsret = JSVAL_NULL;
//        jsret = uint32_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_PolygonInfo_getTriaglesCount : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//bool js_crossapp_PolygonInfo_getVertCount(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_PolygonInfo_getVertCount : Invalid Native Object");
//    if (argc == 0)
//    {
//        const unsigned int ret = cobj->getVertCount();
//        jsval jsret = JSVAL_NULL;
//        jsret = uint32_to_jsval(cx, ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_PolygonInfo_getVertCount : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//
//// PolygonInfo.rect
//bool js_get_PolygonInfo_rect(JSContext* cx, uint32_t argc, jsval* vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    if (cobj)
//    {
//        jsval ret = ccrect_to_jsval(cx, cobj->rect);
//        
//        if (ret != JSVAL_NULL)
//        {
//            args.rval().set(ret);
//            return true;
//        }
//        CCLOGERROR("js_get_PolygonInfo_rect : Fail to retrieve property from PolygonInfo.");
//        return false;
//    }
//    JS_ReportError(cx, "js_get_PolygonInfo_rect : Invalid native object.");
//    return false;
//}
//bool js_set_PolygonInfo_rect(JSContext* cx, uint32_t argc, jsval* vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    if (cobj)
//    {
//        JS::RootedValue jsrect(cx, args.get(0));
//        jsval_to_ccrect(cx, jsrect, &cobj->rect);
//        return true;
//    }
//    JS_ReportError(cx, "js_set_PolygonInfo_rect : Invalid native object.");
//    return false;
//}
//
//// PolygonInfo.filename
//bool js_get_PolygonInfo_filename(JSContext* cx, uint32_t argc, jsval* vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    if (cobj)
//    {
//        jsval ret = std_string_to_jsval(cx, cobj->filename);
//        
//        if (ret != JSVAL_NULL)
//        {
//            args.rval().set(ret);
//            return true;
//        }
//        CCLOGERROR("js_get_PolygonInfo_filename : Fail to retrieve property from PolygonInfo.");
//        return false;
//    }
//    JS_ReportError(cx, "js_get_PolygonInfo_filename : Invalid native object.");
//    return false;
//}
//bool js_set_PolygonInfo_filename(JSContext* cx, uint32_t argc, jsval* vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::PolygonInfo* cobj = (cocos2d::PolygonInfo *)(proxy ? proxy->ptr : NULL);
//    if (cobj)
//    {
//        JS::RootedValue jsstr(cx, args.get(0));
//        jsval_to_std_string(cx, jsstr, &cobj->filename);
//        return true;
//    }
//    JS_ReportError(cx, "js_set_PolygonInfo_filename : Invalid native object.");
//    return false;
//}
//
//bool js_crossapp_PolygonInfo_constructor(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    cocos2d::PolygonInfo* cobj = new (std::nothrow) cocos2d::PolygonInfo();
//    TypeTest<cocos2d::PolygonInfo> t;
//    js_type_class_t *typeClass = nullptr;
//    std::string typeName = t.s_name();
//    auto typeMapIter = _js_global_type_map.find(typeName);
//    CCAssert(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
//    typeClass = typeMapIter->second;
//    CCAssert(typeClass, "The value is null.");
//    JS::RootedObject proto(cx, typeClass->proto.get());
//    JS::RootedObject parent(cx, typeClass->parentProto.get());
//    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
//    args.rval().set(OBJECT_TO_JSVAL(obj));
//    // link the native object with the javascript object
//    jsb_new_proxy(cobj, obj);
//    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
//        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
//    return true;
//}
//
//void js_cocos2d_PolygonInfo_finalize(JSFreeOp *fop, JSObject *obj) {
//    CCLOGINFO("jsbindings: finalizing JS object %p (PolygonInfo)", obj);
//    js_proxy_t* nproxy;
//    js_proxy_t* jsproxy;
//    jsproxy = jsb_get_js_proxy(obj);
//    if (jsproxy)
//    {
//        nproxy = jsb_get_native_proxy(jsproxy->ptr);
//        
//        cocos2d::PolygonInfo *nobj = static_cast<cocos2d::PolygonInfo *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
//        
//        jsb_remove_proxy(nproxy, jsproxy);
//    }
//}
//
//void js_register_crossapp_PolygonInfo(JSContext *cx, JS::HandleObject global)
//{
//    jsb_cocos2d_PolygonInfo_class = (JSClass *)calloc(1, sizeof(JSClass));
//    jsb_cocos2d_PolygonInfo_class->name = "PolygonInfo";
//    jsb_cocos2d_PolygonInfo_class->addProperty = JS_PropertyStub;
//    jsb_cocos2d_PolygonInfo_class->delProperty = JS_DeletePropertyStub;
//    jsb_cocos2d_PolygonInfo_class->getProperty = JS_PropertyStub;
//    jsb_cocos2d_PolygonInfo_class->setProperty = JS_StrictPropertyStub;
//    jsb_cocos2d_PolygonInfo_class->enumerate = JS_EnumerateStub;
//    jsb_cocos2d_PolygonInfo_class->resolve = JS_ResolveStub;
//    jsb_cocos2d_PolygonInfo_class->convert = JS_ConvertStub;
//    jsb_cocos2d_PolygonInfo_class->finalize = js_cocos2d_PolygonInfo_finalize;
//    jsb_cocos2d_PolygonInfo_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
//    
//    static JSPropertySpec properties[] =
//    {
//        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_PSGS("rect", js_get_PolygonInfo_rect, js_set_PolygonInfo_rect, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_PSGS("filename", js_get_PolygonInfo_filename, js_set_PolygonInfo_filename, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_PS_END
//    };
//    
//    static JSFunctionSpec funcs[] =
//    {
//        JS_FN("getArea", js_crossapp_PolygonInfo_getArea, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getTriaglesCount", js_crossapp_PolygonInfo_getTriaglesCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FN("getVertCount", js_crossapp_PolygonInfo_getVertCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FS_END
//    };
//    
//    JSFunctionSpec *st_funcs = NULL;
//    
//    jsb_cocos2d_PolygonInfo_prototype = JS_InitClass(
//                                                     cx, global,
//                                                     JS::NullPtr(), // parent proto
//                                                     jsb_cocos2d_PolygonInfo_class,
//                                                     js_crossapp_PolygonInfo_constructor, 0, // constructor
//                                                     properties,
//                                                     funcs,
//                                                     NULL, // no static properties
//                                                     st_funcs);
//    
//    // add the proto and JSClass to the type->js info hash table
//    TypeTest<cocos2d::PolygonInfo> t;
//    js_type_class_t *p;
//    std::string typeName = t.s_name();
//    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
//    {
//        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
//        p->jsclass = jsb_cocos2d_PolygonInfo_class;
//        p->proto = jsb_cocos2d_PolygonInfo_prototype;
//        p->parentProto = NULL;
//        _js_global_type_map.insert(std::make_pair(typeName, p));
//    }
//}
//
//JSClass  *jsb_cocos2d_AutoPolygon_class;
//JSObject *jsb_cocos2d_AutoPolygon_prototype;
//
//bool js_crossapp_AutoPolygon_generatePolygon(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    if (argc == 1) {
//        std::string arg0;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_AutoPolygon_generatePolygon : Error processing arguments");
//        cocos2d::PolygonInfo* ret = new cocos2d::PolygonInfo(cocos2d::AutoPolygon::generatePolygon(arg0));
//        jsval jsret = JSVAL_NULL;
//        do {
//            if (ret) {
//                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PolygonInfo>(cx, ret);
//                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//    }
//    if (argc == 2) {
//        std::string arg0;
//        cocos2d::Rect arg1;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_AutoPolygon_generatePolygon : Error processing arguments");
//        cocos2d::PolygonInfo* ret = new cocos2d::PolygonInfo(cocos2d::AutoPolygon::generatePolygon(arg0, arg1));
//        jsval jsret = JSVAL_NULL;
//        do {
//            if (ret) {
//                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PolygonInfo>(cx, ret);
//                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//    }
//    if (argc == 3) {
//        std::string arg0;
//        cocos2d::Rect arg1;
//        double arg2;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
//        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_AutoPolygon_generatePolygon : Error processing arguments");
//        cocos2d::PolygonInfo* ret = new cocos2d::PolygonInfo(cocos2d::AutoPolygon::generatePolygon(arg0, arg1, arg2));
//        jsval jsret = JSVAL_NULL;
//        do {
//            if (ret) {
//                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PolygonInfo>(cx, ret);
//                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//    }
//    if (argc == 4) {
//        std::string arg0;
//        cocos2d::Rect arg1;
//        double arg2;
//        double arg3;
//        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//        ok &= jsval_to_ccrect(cx, args.get(1), &arg1);
//        ok &= JS::ToNumber( cx, args.get(2), &arg2) && !isnan(arg2);
//        ok &= JS::ToNumber( cx, args.get(3), &arg3) && !isnan(arg3);
//        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_AutoPolygon_generatePolygon : Error processing arguments");
//        cocos2d::PolygonInfo* ret = new cocos2d::PolygonInfo(cocos2d::AutoPolygon::generatePolygon(arg0, arg1, arg2, arg3));
//        jsval jsret = JSVAL_NULL;
//        do {
//            if (ret) {
//                js_proxy_t *jsProxy = js_get_or_create_proxy<cocos2d::PolygonInfo>(cx, ret);
//                jsret = OBJECT_TO_JSVAL(jsProxy->obj);
//            } else {
//                jsret = JSVAL_NULL;
//            }
//        } while (0);
//        args.rval().set(jsret);
//        return true;
//    }
//    JS_ReportError(cx, "js_crossapp_AutoPolygon_generatePolygon : wrong number of arguments");
//    return false;
//}
//
//bool js_crossapp_AutoPolygon_constructor(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    bool ok = true;
//    std::string arg0;
//    ok &= jsval_to_std_string(cx, args.get(0), &arg0);
//    JSB_PRECONDITION2(ok, cx, false, "js_crossapp_AutoPolygon_constructor : Error processing arguments");
//    cocos2d::AutoPolygon* cobj = new (std::nothrow) cocos2d::AutoPolygon(arg0);
//    TypeTest<cocos2d::AutoPolygon> t;
//    js_type_class_t *typeClass = nullptr;
//    std::string typeName = t.s_name();
//    auto typeMapIter = _js_global_type_map.find(typeName);
//    CCAssert(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
//    typeClass = typeMapIter->second;
//    CCAssert(typeClass, "The value is null.");
//    JS::RootedObject proto(cx, typeClass->proto.get());
//    JS::RootedObject parent(cx, typeClass->parentProto.get());
//    JS::RootedObject obj(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
//    args.rval().set(OBJECT_TO_JSVAL(obj));
//    // link the native object with the javascript object
//    jsb_new_proxy(cobj, obj);
//    if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
//        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
//    return true;
//}
//
//void js_cocos2d_AutoPolygon_finalize(JSFreeOp *fop, JSObject *obj) {
//    CCLOGINFO("jsbindings: finalizing JS object %p (AutoPolygon)", obj);
//    js_proxy_t* nproxy;
//    js_proxy_t* jsproxy;
//    jsproxy = jsb_get_js_proxy(obj);
//    if (jsproxy) {
//        nproxy = jsb_get_native_proxy(jsproxy->ptr);
//        
//        cocos2d::AutoPolygon *nobj = static_cast<cocos2d::AutoPolygon *>(nproxy->ptr);
//        if (nobj)
//            delete nobj;
//        
//        jsb_remove_proxy(nproxy, jsproxy);
//    }
//}
//
//void js_register_crossapp_AutoPolygon(JSContext *cx, JS::HandleObject global) {
//    jsb_cocos2d_AutoPolygon_class = (JSClass *)calloc(1, sizeof(JSClass));
//    jsb_cocos2d_AutoPolygon_class->name = "AutoPolygon";
//    jsb_cocos2d_AutoPolygon_class->addProperty = JS_PropertyStub;
//    jsb_cocos2d_AutoPolygon_class->delProperty = JS_DeletePropertyStub;
//    jsb_cocos2d_AutoPolygon_class->getProperty = JS_PropertyStub;
//    jsb_cocos2d_AutoPolygon_class->setProperty = JS_StrictPropertyStub;
//    jsb_cocos2d_AutoPolygon_class->enumerate = JS_EnumerateStub;
//    jsb_cocos2d_AutoPolygon_class->resolve = JS_ResolveStub;
//    jsb_cocos2d_AutoPolygon_class->convert = JS_ConvertStub;
//    jsb_cocos2d_AutoPolygon_class->finalize = js_cocos2d_AutoPolygon_finalize;
//    jsb_cocos2d_AutoPolygon_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
//    
//    static JSPropertySpec properties[] = {
//        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_PS_END
//    };
//    
//    static JSFunctionSpec funcs[] = {
//        JS_FS_END
//    };
//    
//    static JSFunctionSpec st_funcs[] = {
//        JS_FN("generatePolygon", js_crossapp_AutoPolygon_generatePolygon, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
//        JS_FS_END
//    };
//    
//    jsb_cocos2d_AutoPolygon_prototype = JS_InitClass(
//                                                     cx, global,
//                                                     JS::NullPtr(), // parent proto
//                                                     jsb_cocos2d_AutoPolygon_class,
//                                                     js_crossapp_AutoPolygon_constructor, 0, // constructor
//                                                     properties,
//                                                     funcs,
//                                                     NULL, // no static properties
//                                                     st_funcs);
//    // make the class enumerable in the registered namespace
//    //  bool found;
//    //FIXME: Removed in Firefox v27
//    //  JS_SetPropertyAttributes(cx, global, "AutoPolygon", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
//    
//    // add the proto and JSClass to the type->js info hash table
//    TypeTest<cocos2d::AutoPolygon> t;
//    js_type_class_t *p;
//    std::string typeName = t.s_name();
//    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
//    {
//        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
//        p->jsclass = jsb_cocos2d_AutoPolygon_class;
//        p->proto = jsb_cocos2d_AutoPolygon_prototype;
//        p->parentProto = NULL;
//        _js_global_type_map.insert(std::make_pair(typeName, p));
//    }
//}
//
//bool js_crossapp_ComponentJS_getScriptObject(JSContext *cx, uint32_t argc, jsval *vp)
//{
//    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
//    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
//    js_proxy_t *proxy = jsb_get_js_proxy(obj);
//    cocos2d::ComponentJS* cobj = (cocos2d::ComponentJS *)(proxy ? proxy->ptr : NULL);
//    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_ComponentJS_getScriptObject : Invalid Native Object");
//    if (argc == 0) {
//        JSObject* ret = static_cast<JSObject*>(cobj->getScriptObject());
//        jsval jsret = OBJECT_TO_JSVAL(ret);
//        args.rval().set(jsret);
//        return true;
//    }
//    
//    JS_ReportError(cx, "js_crossapp_ComponentJS_getScriptObject : wrong number of arguments: %d, was expecting %d", argc, 0);
//    return false;
//}
//



void register_crossapp_js_core(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    JS::RootedObject jsbObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "ca", &ccObj);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
//    
//    js_register_crossapp_PolygonInfo(cx, jsbObj);
//    js_register_crossapp_AutoPolygon(cx, jsbObj);
//
//    JS_GetProperty(cx, ccObj, "PlistParser", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "getInstance", js_PlistParser_getInstance, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS::RootedObject proto(cx, jsb_cocos2d_SAXParser_prototype);
//    JS_DefineFunction(cx, proto, "parse", js_PlistParser_parse, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "Label", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "createWithTTF", js_crossapp_Label_createWithTTF, 4, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_Label_prototype);
//    JS_DefineFunction(cx, tmpObj, "setTTFConfig", js_crossapp_Label_setTTFConfig, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//
//    tmpObj.set(jsb_cocos2d_NodeGrid_prototype);
//    JS_DefineFunction(cx, tmpObj, "setGrid", js_crossapp_NodeGrid_setGrid, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    
    tmpObj.set(jsb_CrossApp_CAView_prototype);
    JS_DefineFunction(cx, tmpObj, "onEnter", js_crossapp_Node_onEnter, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "onExit", js_crossapp_Node_onExit, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "onEnterTransitionDidFinish", js_crossapp_Node_onEnterTransitionDidFinish, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "onExitTransitionDidStart", js_crossapp_Node_onExitTransitionDidStart, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
    
//    tmpObj.set(jsb_cocos2d_Node_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "onEnter", js_crossapp_Node_onEnter, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "onExit", js_crossapp_Node_onExit, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "onEnterTransitionDidFinish", js_crossapp_Node_onEnterTransitionDidFinish, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "onExitTransitionDidStart", js_crossapp_Node_onExitTransitionDidStart, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "cleanup", js_crossapp_Node_cleanup, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "schedule", js_CCNode_schedule, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "scheduleOnce", js_CCNode_scheduleOnce, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "scheduleUpdateWithPriority", js_crossapp_CCNode_scheduleUpdateWithPriority, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "unscheduleUpdate", js_crossapp_CCNode_unscheduleUpdate, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "scheduleUpdate", js_crossapp_CCNode_scheduleUpdate, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "unschedule", js_CCNode_unschedule, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "unscheduleAllCallbacks", js_crossapp_CCNode_unscheduleAllSelectors, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setPosition", js_crossapp_CCNode_setPosition, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setContentSize", js_crossapp_CCNode_setContentSize, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setAnchorPoint", js_crossapp_CCNode_setAnchorPoint, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setColor", js_crossapp_CCNode_setColor, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "pause", js_crossapp_CCNode_pause, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "resume", js_crossapp_CCNode_resume, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "convertToWorldSpace", js_crossapp_CCNode_convertToWorldSpace, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "convertToWorldSpaceAR", js_crossapp_CCNode_convertToWorldSpaceAR, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setAdditionalTransform", js_crossapp_Node_setAdditionalTransform, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_EventListener_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_Touch_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_EventTouch_prototype);
//    JS_DefineFunction(cx, tmpObj, "getTouches", js_crossapp_EventTouch_getTouches, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setTouches", js_crossapp_EventTouch_setTouches, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_GLProgram_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setUniformLocationF32", js_crossapp_CCGLProgram_setUniformLocationWith4f, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "getProgram", js_crossapp_CCGLProgram_getProgram, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setUniformLocationWithMatrixfvUnion", js_crossapp_CCGLProgram_setUniformLocationWithMatrixfvUnion, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_GLProgramState_prototype);
//    JS_DefineFunction(cx, tmpObj, "setVertexAttribPointer", js_crossapp_GLProgramState_setVertexAttribPointer, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setUniformVec4", js_crossapp_GLProgramState_setUniformVec4, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    tmpObj.set(jsb_CrossApp_CAScheduler_prototype);
    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "resumeTarget", js_crossapp_CCScheduler_resumeTarget, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "pauseTarget", js_crossapp_CCScheduler_pauseTarget, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "scheduleUpdateForTarget", js_CCScheduler_scheduleUpdateForTarget, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "unscheduleUpdate", js_CCScheduler_unscheduleUpdateForTarget, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "schedule", js_CCScheduler_scheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "scheduleCallbackForTarget", js_CCScheduler_scheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unschedule", js_CCScheduler_unscheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unscheduleCallbackForTarget", js_CCScheduler_unscheduleCallbackForTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unscheduleAllForTarget", js_crossapp_CCScheduler_unscheduleAllSelectorsForTarget, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "unscheduleAllCallbacks", js_crossapp_CCScheduler_unscheduleAll, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "unscheduleAllCallbacksWithMinPriority", js_crossapp_CCScheduler_unscheduleAllCallbacksWithMinPriority, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "isTargetPaused", js_crossapp_CCScheduler_isTargetPaused, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_ActionManager_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_TMXLayer_prototype);
//    JS_DefineFunction(cx, tmpObj, "getTileFlagsAt", js_crossapp_CCTMXLayer_getTileFlagsAt, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_Texture2D_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setTexParameters", js_crossapp_CCTexture2D_setTexParameters, 4, JSPROP_ENUMERATE  | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_Menu_prototype);
//    JS_DefineFunction(cx, tmpObj, "alignItemsInRows", js_crossapp_CCMenu_alignItemsInRows, 1, JSPROP_ENUMERATE  | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "alignItemsInColumns", js_crossapp_CCMenu_alignItemsInColumns, 1, JSPROP_ENUMERATE  | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_Layer_prototype);
//    JS_DefineFunction(cx, tmpObj, "init", js_crossapp_CCLayer_init, 0, JSPROP_ENUMERATE  | JSPROP_PERMANENT);

//    tmpObj.set(jsb_cocos2d_FileUtils_prototype);
//    JS_DefineFunction(cx, tmpObj, "setSearchResolutionsOrder", js_crossapp_CCFileUtils_setSearchResolutionsOrder, 1, JSPROP_PERMANENT );
//    JS_DefineFunction(cx, tmpObj, "setSearchPaths", js_crossapp_CCFileUtils_setSearchPaths, 1, JSPROP_PERMANENT );
//    JS_DefineFunction(cx, tmpObj, "getSearchPaths", js_crossapp_CCFileUtils_getSearchPaths, 0, JSPROP_PERMANENT );
//    JS_DefineFunction(cx, tmpObj, "getSearchResolutionsOrder", js_crossapp_CCFileUtils_getSearchResolutionsOrder, 0, JSPROP_PERMANENT );
//    JS_DefineFunction(cx, tmpObj, "createDictionaryWithContentsOfFile", js_crossapp_FileUtils_createDictionaryWithContentsOfFile, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "getDataFromFile", js_crossapp_CCFileUtils_getDataFromFile, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "writeDataToFile", js_crossapp_CCFileUtils_writeDataToFile, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);

//    JS_GetProperty(cx, ccObj, "EventListenerTouchOneByOne", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_EventListenerTouchOneByOne_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "EventListenerTouchAllAtOnce", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_EventListenerTouchAllAtOnce_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "EventListenerMouse", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_EventListenerMouse_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "EventListenerKeyboard", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_EventListenerKeyboard_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "EventListenerFocus", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_EventListenerFocus_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
    
//    JS_GetProperty(cx, ccObj, "BezierBy", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", JSB_CCBezierBy_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_BezierBy_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithDuration", JSB_CCBezierBy_initWithDuration, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "BezierTo", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", JSB_CCBezierTo_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_BezierTo_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithDuration", JSB_CCBezierTo_initWithDuration, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "CardinalSplineBy", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCardinalSplineBy_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "CardinalSplineTo", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCardinalSplineTo_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_CardinalSplineTo_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithDuration", js_crossapp_CardinalSplineTo_initWithDuration, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
//    JS_GetProperty(cx, ccObj, "CatmullRomBy", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCatmullRomBy_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_CatmullRomBy_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithDuration", JSB_CatmullRomBy_initWithDuration, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "CatmullRomTo", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", JSB_CCCatmullRomTo_actionWithDuration, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_CatmullRomTo_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithDuration", JSB_CatmullRomBy_initWithDuration, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//
//    JS_GetProperty(cx, ccObj, "Sprite", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_Sprite_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_Sprite_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithPolygon", js_crossapp_Sprite_initWithPolygon, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setPolygonInfo", js_crossapp_Sprite_setPolygonInfo, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "textureLoaded", js_crossapp_Sprite_textureLoaded, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_SpriteBatchNode_prototype);
//    JS_DefineFunction(cx, tmpObj, "getDescendants", js_crossapp_SpriteBatchNode_getDescendants, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_Action_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_Animation_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_SpriteFrame_prototype);
//    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_MenuItem_prototype);
//    JS_DefineFunction(cx, tmpObj, "setCallback", js_crossapp_MenuItem_setCallback, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_TMXLayer_prototype);
//    JS_DefineFunction(cx, tmpObj, "getTiles", js_crossapp_CCTMXLayer_getTiles, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_ActionInterval_prototype);
//    JS_DefineFunction(cx, tmpObj, "repeat", js_crossapp_ActionInterval_repeat, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "repeatForever", js_crossapp_ActionInterval_repeatForever, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "_speed", js_crossapp_ActionInterval_speed, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "easing", js_crossapp_ActionInterval_easing, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_RenderTexture_prototype);
//    JS_DefineFunction(cx, tmpObj, "saveToFile", js_crossapp_RenderTexture_saveToFile, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "Menu", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "_create", js_crossapp_CCMenu_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "MenuItem", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCMenuItem_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "MenuItemSprite", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCMenuItemSprite_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "MenuItemLabel", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCMenuItemLabel_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "MenuItemAtlasFont", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCMenuItemAtlasFont_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "MenuItemFont", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCMenuItemFont_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "MenuItemToggle", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "_create", js_crossapp_CCMenuItemToggle_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "Sequence", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCSequence_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_GetProperty(cx, ccObj, "Spawn", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCSpawn_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    //JS_GetProperty(cx, ccObj, "Animation", &tmpVal);
//    //tmpObj = tmpVal.toObjectOrNull();
//    //JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCAnimation_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_Scene_prototype);
//    JS_DefineFunction(cx, tmpObj, "init", js_crossapp_CCScene_init, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE);
//    JS_GetProperty(cx, ccObj, "LayerMultiplex", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCLayerMultiplex_create, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    
//    JS_GetProperty(cx, ccObj, "CallFunc", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_callFunc, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    tmpObj.set(jsb_cocos2d_CallFuncN_prototype);
//    JS_DefineFunction(cx, tmpObj, "initWithFunction", js_crossapp_CallFunc_initWithFunction, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
//    JS_GetProperty(cx, ccObj, "GLProgram", &tmpVal);
//    tmpObj = tmpVal.toObjectOrNull();
//    JS_DefineFunction(cx, tmpObj, "create", js_crossapp_CCGLProgram_create, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "createWithString", js_crossapp_CCGLProgram_createWithString, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//
//    tmpObj.set(jsb_cocos2d_Camera_prototype);
//    JS_DefineFunction(cx, tmpObj, "unproject", js_crossapp_Camera_unproject, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "isVisibleInFrustum", js_crossapp_Camera_isVisibleInFrustum, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_ClippingNode_prototype);
//    JS_DefineFunction(cx, tmpObj, "init", js_crossapp_ClippingNode_init, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    
//    tmpObj.set(jsb_cocos2d_ComponentJS_prototype);
//    JS_DefineFunction(cx, tmpObj, "getScriptObject", js_crossapp_ComponentJS_getScriptObject, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CAButton_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CAButton_addTarget, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "removeTarget", js_crossapp_CAButton_removeTarget, 3, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CASlider_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CASlider_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "removeTarget", js_crossapp_CASlider_removeTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CAStepper_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CAStepper_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "removeTarget", js_crossapp_CAStepper_removeTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CASwitch_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CASwitch_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "removeTarget", js_crossapp_CASwitch_removeTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CAPageControl_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CAPageControl_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "removeTarget", js_crossapp_CAPageControl_removeTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CASegmentedControl_prototype);
    JS_DefineFunction(cx, tmpObj, "addTarget", js_crossapp_CASegmentedControl_addTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "removeTarget", js_crossapp_CASegmentedControl_removeTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CAAlertView_prototype);
    JS_DefineFunction(cx, tmpObj, "createWithText", js_crossapp_CAAlertView_createWithText, 4, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, tmpObj, "setTarget", js_crossapp_CAAlertView_setTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    

    
    tmpObj.set(jsb_CrossApp_CABarButtonItem_prototype);
    JS_DefineFunction(cx, tmpObj, "setTarget", js_crossapp_CABarButtonItem_setTarget, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    
//    tmpObj.set(jsb_CrossApp_CAViewAnimation_prototype);
    //    JS_DefineFunction(cx, tmpObj, "setAnimationWillStartSelector", js_crossapp_CAViewAnimation_setAnimationWillStartSelector_0, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    //    JS_DefineFunction(cx, tmpObj, "setAnimationWillStartSelector_two", js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "setAnimationDidStopSelector", js_crossapp_CAViewAnimation_setAnimationDidStopSelector, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    //    JS_DefineFunction(cx, tmpObj, "setAnimationDidStopSelector_two", js_crossapp_CAViewAnimation_setAnimationDidStopSelector_2, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    JS_GetProperty(cx, ccObj, "CAViewAnimation", &tmpVal);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, tmpObj, "setAnimationWillStartSelector", js_crossapp_CAViewAnimation_setAnimationWillStartSelector, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setAnimationWillStartSelector_2", js_crossapp_CAViewAnimation_setAnimationWillStartSelector_2, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setAnimationDidStopSelector", js_crossapp_CAViewAnimation_setAnimationDidStopSelector, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setAnimationDidStopSelector_2", js_crossapp_CAViewAnimation_setAnimationDidStopSelector_2, 2, JSPROP_READONLY | JSPROP_PERMANENT);
    
//
//    JS_DefineFunction(cx, ccObj, "glEnableVertexAttribs", js_crossapp_ccGLEnableVertexAttribs, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pAdd", js_crossapp_ccpAdd, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pDistanceSQ", js_crossapp_ccpDistanceSQ, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pDistance", js_crossapp_ccpDistance, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pSub", js_crossapp_ccpSub, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pNeg", js_crossapp_ccpNeg, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pMult", js_crossapp_ccpMult, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pMidpoint", js_crossapp_ccpMidpoint, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pDot", js_crossapp_ccpDot, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pCross", js_crossapp_ccpCross, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pPerp", js_crossapp_ccpPerp, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pRPerp", js_crossapp_ccpRPerp, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pProject", js_crossapp_ccpProject, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pRotate", js_crossapp_ccpRotate, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pNormalize", js_crossapp_ccpNormalize, 0, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pClamp", js_crossapp_ccpClamp, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pLengthSQ", js_crossapp_ccpLengthSQ, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "pLength", js_crossapp_ccpLength, 1, JSPROP_READONLY | JSPROP_PERMANENT);


//    JS_DefineFunction(cx, ccObj, "registerTargetedDelegate", js_crossapp_JSTouchDelegate_registerTargetedDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "registerStandardDelegate", js_crossapp_JSTouchDelegate_registerStandardDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, ccObj, "unregisterTouchDelegate", js_crossapp_JSTouchDelegate_unregisterTouchDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    
    
    JS_DefineFunction(cx, ccObj, "addTouchView", js_crossapp_JSTouchView_addTouchView, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeTouchView", js_crossapp_JSTouchView_removeTouchView, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, ccObj, "addTouchViewController", js_crossapp_JSTouchViewController_addTouchViewController, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeTouchViewController", js_crossapp_JSTouchViewController_removeTouchViewController, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, ccObj, "addKeypadDelegate", js_crossapp_addKeypadDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeKeypadDelegate", js_crossapp_removeKeypadDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);

    
    
//    get_or_create_js_obj(cx, ccObj, "math", &tmpObj);
//    JS_DefineFunction(cx, tmpObj, "obbGetCorners", js_crossapp_ccobbGetCorners, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "obbIntersectsObb", js_crossapp_ccobbIntersects, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "rayIntersectsObb", js_crossapp_ccrayIntersectsObb, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4CreateTranslation", js_crossapp_ccmat4CreateTranslation, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4CreateRotation", js_crossapp_ccmat4CreateRotation, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4Multiply", js_crossapp_ccmat4Multiply, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4MultiplyVec3", js_crossapp_ccmat4MultiplyVec3, 2, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4GetInversed", js_crossapp_ccmat4GetInversed, 1, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4TransformVector", js_crossapp_ccmat4TransformVector, 3, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "mat4TransformPoint", js_crossapp_ccmat4TransformPoint, 3, JSPROP_READONLY | JSPROP_PERMANENT);
//    JS_DefineFunction(cx, tmpObj, "quatMultiply", js_crossapp_ccquatMultiply, 2, JSPROP_READONLY | JSPROP_PERMANENT);

//    js_register_crossapp_EventKeyboard(cx, ccObj);

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


