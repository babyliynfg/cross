
#include "crossapp_specifics.hpp"
#include "CrossApp.h"
#include <typeinfo>
#include "js_bindings_config.h"
#include "jsb_crossapp_auto.hpp"
#include "jsapi.h"

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
    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    tmpObj = tmpVal.toObjectOrNull();
    JS_DefineFunction(cx, ccObj, "addTouchView", js_crossapp_JSTouchView_addTouchView, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeTouchView", js_crossapp_JSTouchView_removeTouchView, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, ccObj, "addTouchViewController", js_crossapp_JSTouchViewController_addTouchViewController, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeTouchViewController", js_crossapp_JSTouchViewController_removeTouchViewController, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    
    JS_DefineFunction(cx, ccObj, "addKeypadDelegate", js_crossapp_addKeypadDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, ccObj, "removeKeypadDelegate", js_crossapp_removeKeypadDelegate, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    get_or_create_js_obj(cx, global, "console", &tmpObj);
    JS_DefineFunction(cx, tmpObj, "log", js_console_log, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, global, "garbageCollect", js_forceGC, 1, JSPROP_READONLY | JSPROP_PERMANENT);
}

void js_add_object_reference(JS::HandleValue owner, JS::HandleValue target)
{
    if (target.isPrimitive())
    {
        return;
    }
    
    ScriptingCore *engine = ScriptingCore::getInstance();
    JSContext *cx = engine->getGlobalContext();
    JS::RootedObject global(cx, engine->getGlobalObject());
    JS::RootedObject jsbObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    JS::RootedValue retval(cx);
    jsval valArr[2];
    valArr[0] = owner;
    valArr[1] = target;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    engine->executeFunctionWithOwner(jsbVal, "registerNativeRef", args, &retval);
}
void js_remove_object_reference(JS::HandleValue owner, JS::HandleValue target)
{
    if (target.isPrimitive())
    {
        return;
    }
    ScriptingCore *engine = ScriptingCore::getInstance();
    JSContext *cx = engine->getGlobalContext();
    JS::RootedObject ownerObj(cx, owner.toObjectOrNull());
    JS::RootedObject targetObj(cx, target.toObjectOrNull());
    js_proxy_t *pOwner = jsb_get_js_proxy(ownerObj);
    js_proxy_t *pTarget = jsb_get_js_proxy(targetObj);
    if (!pOwner || !pTarget)
    {
        return;
    }
    
    JS::RootedObject global(cx, engine->getGlobalObject());
    JS::RootedObject jsbObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    JS::RootedValue retval(cx);
    jsval valArr[2];
    valArr[0] = owner;
    valArr[1] = target;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    engine->executeFunctionWithOwner(jsbVal, "unregisterNativeRef", args, &retval);
}
void js_add_object_root(JS::HandleValue target)
{
    if (target.isPrimitive())
    {
        return;
    }
    
    ScriptingCore *engine = ScriptingCore::getInstance();
    JSContext *cx = engine->getGlobalContext();
    JS::RootedObject global(cx, engine->getGlobalObject());
    JS::RootedObject jsbObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    JS::RootedObject root(cx);
    get_or_create_js_obj(cx, jsbObj, "jsb._root", &root);
    JS::RootedValue valRoot(cx, OBJECT_TO_JSVAL(root));
    
    JS::RootedValue retval(cx);
    jsval valArr[2];
    valArr[0] = valRoot;
    valArr[1] = target;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    engine->executeFunctionWithOwner(jsbVal, "registerNativeRef", args, &retval);
}
void js_remove_object_root(JS::HandleValue target)
{
    if (target.isPrimitive())
    {
        return;
    }
    ScriptingCore *engine = ScriptingCore::getInstance();
    JSContext *cx = engine->getGlobalContext();
    JS::RootedObject targetObj(cx, target.toObjectOrNull());
    js_proxy_t *pTarget = jsb_get_js_proxy(targetObj);
    if (!pTarget)
    {
        return;
    }
    
    JS::RootedObject global(cx, engine->getGlobalObject());
    JS::RootedObject jsbObj(cx);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);
    JS::RootedValue jsbVal(cx, OBJECT_TO_JSVAL(jsbObj));
    if (jsbVal.isNullOrUndefined())
    {
        return;
    }
    
    JS::RootedObject root(cx);
    get_or_create_js_obj(cx, jsbObj, "_root", &root);
    JS::RootedValue valRoot(cx, OBJECT_TO_JSVAL(root));
    
    JS::RootedValue retval(cx);
    jsval valArr[2];
    valArr[0] = valRoot;
    valArr[1] = target;
    
    JS::HandleValueArray args = JS::HandleValueArray::fromMarkedLocation(2, valArr);
    engine->executeFunctionWithOwner(jsbVal, "unregisterNativeRef", args, &retval);
}

