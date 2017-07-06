
#include "crossapp_specifics.hpp"
#include "CrossApp.h"
#include <typeinfo>
#include "js_bindings_config.h"
#include "jsb_crossapp_auto.hpp"
#include "jsapi.h"

using namespace CrossApp;

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
    JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
    if (JS_EvaluateScript(cx, thisObj, string, (unsigned int)strlen(string), "(string)", 1, &out) == true) {
        return out.get();
    }
    return JSVAL_VOID;
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

bool js_forceGC(JSContext *cx, uint32_t argc, jsval *vp) {
    JSRuntime *rt = JS_GetRuntime(cx);
    JS_GC(rt);
    return true;
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
    JS_DefineFunction(cx, tmpObj, "retain", js_crossapp_retain, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "release", js_crossapp_release, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
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

