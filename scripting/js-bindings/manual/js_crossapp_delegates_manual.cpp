//
//  js_crossapp_delegates_manual.cpp
//  HelloJavacript
//
//  Created by zhanglei on 16/7/6.
//
//


#include "js_crossapp_delegates_manual.hpp"
#include "crossapp_specifics.hpp"
#include "jsb_crossapp_auto.hpp"
#include "CrossAppExt.h"
#include "CrossApp.h"
typedef CAMap<std::string,CAObject*> CADelegateMap;

//JSB_TextFieldDelegate
class JSB_TextFieldDelegate :public CAObject , public CATextFieldDelegate
{
public:
    JSB_TextFieldDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_TextFieldDelegate()
    {
        _JSDelegate = nullptr;
    }
    
    virtual bool textFieldShouldBeginEditing(CATextField* sender) override
    {
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        bool bRet = false;
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textFieldShouldBeginEditing", 1, &arg,&retval);
        if(retval.isBoolean())
        {
            bRet = retval.toBoolean();
        } 
        
        return bRet;
    }
    
    //If the sender doesn't want to detach from the IME, return true;
    virtual bool textFieldShouldEndEditing(CATextField* sender) override
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        bool bRet = false;
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textFieldShouldEndEditing", 1, &arg,&retval);
        if(retval.isBoolean())
        {
            bRet = retval.toBoolean();
        }
        
        return bRet;
    }
    
    //
    virtual void textFieldShouldReturn(CATextField* sender) override
    {
        js_proxy_t * p = jsb_get_native_proxy(sender);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textFieldShouldReturn", 1, &arg);
    }
    
    virtual void keyBoardHeight(CATextField* sender, int height) override
    {
        jsval args[2];
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        
        args[1] = int32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), height);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "keyBoardHeight",2, args);

    }
    
    //Warning!!! Warning!!! Warning!!!  This method is not on the OpenGL thread.
    virtual bool textFieldShouldChangeCharacters(CATextField* sender,
                                                 unsigned int location,
                                                 unsigned int length,
                                                 const std::string& changedText) override
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        bool bRet = false;
        
        jsval args[4];
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), location);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), length);
        args[3] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), changedText);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textFieldShouldChangeCharacters", 1, args,&retval);
        if(retval.isBoolean())
        {
            bRet = retval.toBoolean();
        }
        
        return bRet;
    }
    
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CATextField_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CATextField* cobj = (CrossApp::CATextField *)(proxy ? proxy->ptr : NULL);
    
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_TextFieldDelegate* nativeDelegate = new (std::nothrow) JSB_TextFieldDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JS_SetProperty(cx, obj, "_delegate", args.get(0));
        
        cobj->setUserObject(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
};

//JSB_TextViewDelegate
class JSB_TextViewDelegate:public CAObject, public CATextViewDelegate
{
public:
    JSB_TextViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_TextViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    
    virtual bool textViewShouldBeginEditing(CATextView* sender) override
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        bool bRet = false;
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textViewShouldBeginEditing", 1, &arg,&retval);
        if(retval.isBoolean())
        {
            bRet = retval.toBoolean();
        }
        
        return bRet;
    }
    
    //If the sender doesn't want to detach from the IME, return true;
    virtual bool textViewShouldEndEditing(CATextView* sender) override
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        bool bRet = false;
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textViewShouldEndEditing", 1, &arg,&retval);
        if(retval.isBoolean())
        {
            bRet = retval.toBoolean();
        }
        
        return bRet;
    }
    
    //
    virtual void textViewShouldReturn(CATextView* sender) override
    {
        js_proxy_t * p = jsb_get_native_proxy(sender);
        if (!p) return;
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textViewShouldReturn", 1, &arg);
    }
    
    //
    virtual void keyBoardHeight(CATextView* sender, int height) override
    {
        jsval args[2];
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        
        args[1] = int32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), height);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "keyBoardHeight",2, args);
    }
    
    //Warning!!! Warning!!! Warning!!!  This method is not on the OpenGL thread.
    virtual bool textViewShouldChangeCharacters(CATextView* sender,
                                                unsigned int location,
                                                unsigned int length,
                                                const std::string& changedText) override
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        bool bRet = false;
        
        jsval args[4];
        
        js_proxy_t * p = jsb_get_native_proxy(sender);
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), location);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), length);
        args[3] = std_string_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), changedText);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "textViewShouldChangeCharacters", 4, args,&retval);
        if(retval.isBoolean())
        {
            bRet = retval.toBoolean();
        }
        
        return bRet;
    }
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CATextView_setDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CATextView* cobj = (CrossApp::CATextView *)(proxy ? proxy->ptr : NULL);
    
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_TextViewDelegate* nativeDelegate = new (std::nothrow) JSB_TextViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JS_SetProperty(cx, obj, "_delegate", args.get(0));
        
        cobj->setUserObject(nativeDelegate);
        cobj->setDelegate(nativeDelegate);
        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
};

//JSB_TableViewDelegate
#define KEY_TABLEVIEW_DATA_SOURCE  "TableViewDataSource"
#define KEY_TABLEVIEW_DELEGATE     "TableViewDelegate"
class JSB_TableViewDelegate: public CAObject,public CATableViewDelegate
{
public:
    JSB_TableViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_TableViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    
    void tableViewDidSelectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) override
    {
        jsval args[3];
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), section);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), row);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewDidSelectRowAtIndexPath", 3, args);
    }
    
    void tableViewDidDeselectRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row) override
    {
        jsval args[3];
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), section);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), row);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewDidDeselectRowAtIndexPath", 3, args);
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CATableView_setTableViewDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CATableView * cobj = (CATableView *)(proxy ? proxy->ptr : NULL);
    
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_TableViewDelegate* nativeDelegate = new (std::nothrow) JSB_TableViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JS_SetProperty(cx, obj, "_delegate", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_TABLEVIEW_DELEGATE,nativeDelegate);
        
        cobj->setTableViewDelegate(nativeDelegate);
        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
};

class JSB_TableViewDataSource: public CAObject,public CATableViewDataSource
{
public:
    JSB_TableViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_TableViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    void setJSDataSource(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    //Necessary
    virtual CATableViewCell* tableCellAtIndex(CATableView* table, const DSize& cellSize, unsigned int section, unsigned int row)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CATableViewCell* tableViewCell = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[4];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, cellSize);
        args[2] = uint32_to_jsval(cx, section);
        args[3] = uint32_to_jsval(cx, row);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableCellAtIndex", 4, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                tableViewCell = (CATableViewCell*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( tableViewCell, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        return tableViewCell;
    }
    
    //Necessary
    virtual unsigned int tableViewHeightForRowAtIndexPath(CATableView* table, unsigned int section, unsigned int row)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        args[2] = uint32_to_jsval(cx, row);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewHeightForRowAtIndexPath",3, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CATableView* table, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfRowsInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual unsigned int numberOfSections(CATableView* table)
    {
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
    
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[1];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfSections",1, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        
        return 1;
    }
    
    virtual CAView* tableViewSectionViewForHeaderInSection(CATableView* table, const DSize& viewSize, unsigned int section)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        args[2] = uint32_to_jsval(cx, section);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewSectionViewForHeaderInSection", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int tableViewHeightForHeaderInSection(CATableView* table, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewHeightForHeaderInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return 0;
    }
    
    virtual CAView* tableViewSectionViewForFooterInSection(CATableView* table, const DSize& viewSize, unsigned int section)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        args[2] = uint32_to_jsval(cx, section);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewSectionViewForFooterInSection", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int tableViewHeightForFooterInSection(CATableView* table, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(table);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewHeightForFooterInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        
        return 0;
    }
    
    virtual void tableViewWillDisplayCellAtIndex(CATableView* table, CATableViewCell* cell, unsigned int section, unsigned int row)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        
        js_proxy_t * p1 = jsb_get_native_proxy(table);
        js_proxy_t * p2 = jsb_get_native_proxy(cell);
        jsval args[4];
        args[0] = OBJECT_TO_JSVAL(p1->obj);
        args[1] = OBJECT_TO_JSVAL(p2->obj);
        args[2] = uint32_to_jsval(cx, section);
        args[3] = uint32_to_jsval(cx, row);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "tableViewHeightForFooterInSection",4, args);
    }
    
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CATableView_setTableViewDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CATableView * cobj = (CrossApp::CATableView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_TableViewDataSource* pNativeSource = new (std::nothrow) JSB_TableViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setJSDataSource(jsdata);
        
        JS_SetProperty(cx, obj, "m_pTableViewDataSource", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_TABLEVIEW_DATA_SOURCE,pNativeSource);
        
        cobj->setTableViewDataSource(pNativeSource);
        
        pNativeSource->release();
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return false;
};

#define KEY_COLLECTIONVIEW_DATA_SOURCE  "CollectionViewDataSource"
#define KEY_COLLECTIONVIEW_DELEGATE     "CollectionViewDelegate"

//JSB_CollectionViewDelegate
class JSB_CollectionViewDelegate: public CAObject,public CACollectionViewDelegate
{
public:
    JSB_CollectionViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_CollectionViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    
    virtual void collectionViewDidSelectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item)
    {
        jsval args[4];
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), section);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), row);
        args[3] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), item);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewDidSelectCellAtIndexPath", 4, args);
    
    }
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CACollectionView *collectionView, unsigned int section, unsigned int row, unsigned int item)
    {
        jsval args[4];
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), section);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), row);
        args[3] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), item);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewDidDeselectCellAtIndexPath", 4, args);
    
    }
    
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CACollectionView_setCollectionViewDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CACollectionView * cobj = (CACollectionView *)(proxy ? proxy->ptr : NULL);
    
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_CollectionViewDelegate* nativeDelegate = new (std::nothrow) JSB_CollectionViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JS_SetProperty(cx, obj, "m_pCollectionViewDelegate", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_COLLECTIONVIEW_DELEGATE,nativeDelegate);
        cobj->setCollectionViewDelegate(nativeDelegate);
        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
};

class JSB_CollectionViewDataSource: public CAObject,public CACollectionViewDataSource
{
public:
    JSB_CollectionViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_CollectionViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    void setJSDataSource(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    
    //Necessary
    virtual CACollectionViewCell* collectionCellAtIndex(CACollectionView *collectionView, const DSize& cellSize, unsigned int section, unsigned int row, unsigned int item)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CACollectionViewCell* collectionCell = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[5];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, cellSize);
        args[2] = uint32_to_jsval(cx, section);
        args[3] = uint32_to_jsval(cx, row);
        args[4] = uint32_to_jsval(cx, item);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionCellAtIndex", 5, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                collectionCell = (CACollectionViewCell*)(proxy ? proxy->ptr : NULL);
//                JSB_PRECONDITION2( collectionCell, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        return collectionCell;
    }
    
    //Necessary
    virtual unsigned int collectionViewHeightForRowAtIndexPath(CACollectionView* collectionView, unsigned int section, unsigned int row)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        args[2] = uint32_to_jsval(cx, row);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewHeightForRowAtIndexPath",3, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    //Necessary
    virtual unsigned int numberOfItemsInRowsInSection(CACollectionView *collectionView, unsigned int section, unsigned int row)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        args[2] = uint32_to_jsval(cx, row);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfItemsInRowsInSection",3, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    //Necessary
    virtual unsigned int numberOfRowsInSection(CACollectionView *collectionView, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfRowsInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual unsigned int numberOfSections(CACollectionView *collectionView)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[1];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfSections",1, args,&retval);
        unsigned index = 1;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual CAView* collectionViewSectionViewForHeaderInSection(CACollectionView *collectionView, const DSize& viewSize, unsigned int section)
    {
        
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        args[2] = uint32_to_jsval(cx, section);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewSectionViewForHeaderInSection", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int collectionViewHeightForHeaderInSection(CACollectionView *collectionView, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewHeightForHeaderInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return 0;
    }
    
    virtual CAView* collectionViewSectionViewForFooterInSection(CACollectionView *collectionView, const DSize& viewSize, unsigned int section)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        args[2] = uint32_to_jsval(cx, section);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewSectionViewForFooterInSection", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int collectionViewHeightForFooterInSection(CACollectionView *collectionView, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewHeightForFooterInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return 0;
    }
    
    virtual void collectionViewWillDisplayCellAtIndex(CACollectionView* table, CACollectionViewCell* cell, unsigned int section, unsigned int row, unsigned int item)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        
        js_proxy_t * p1 = jsb_get_native_proxy(table);
        js_proxy_t * p2 = jsb_get_native_proxy(cell);
        jsval args[5];
        args[0] = OBJECT_TO_JSVAL(p1->obj);
        args[1] = OBJECT_TO_JSVAL(p2->obj);
        args[2] = uint32_to_jsval(cx, section);
        args[3] = uint32_to_jsval(cx, row);
        args[4] = uint32_to_jsval(cx, item);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewWillDisplayCellAtIndex",5, args);
        
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CACollectionView_setCollectionViewDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CACollectionView * cobj = (CrossApp::CACollectionView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_CollectionViewDataSource* pNativeSource = new (std::nothrow) JSB_CollectionViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setJSDataSource(jsdata);
        
        JS_SetProperty(cx, obj, "m_pCollectionViewDataSource", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_COLLECTIONVIEW_DATA_SOURCE,pNativeSource);
        
        cobj->setCollectionViewDataSource(pNativeSource);
        
//        pNativeSource->release();
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

//JSB_WaterfallViewDelegate
#define KEY_WATERFALLVIEW_DATA_SOURCE  "WaterfallViewDataSource"
#define KEY_WATERFALLVIEW_DELEGATE     "WaterfallViewDelegate"
class JSB_WaterfallViewDelegate: public CAObject,public CAWaterfallViewDelegate
{
public:
    JSB_WaterfallViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_WaterfallViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    virtual void waterfallViewDidSelectCellAtIndexPath(CAWaterfallView *waterfallView, unsigned int itemIndex)
    {
        jsval args[2];
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), itemIndex);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewDidSelectCellAtIndexPath", 2, args);
    }
    
    virtual void waterfallViewDidDeselectCellAtIndexPath(CAWaterfallView *waterfallView, unsigned int itemIndex)
    {
        jsval args[2];
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), itemIndex);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewDidDeselectCellAtIndexPath", 2, args);
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CAWaterfallView_setWaterfallViewDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CAWaterfallView * cobj = (CAWaterfallView *)(proxy ? proxy->ptr : NULL);
    
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_WaterfallViewDelegate* nativeDelegate = new (std::nothrow) JSB_WaterfallViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JS_SetProperty(cx, obj, "_delegate", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_WATERFALLVIEW_DELEGATE,nativeDelegate);
        cobj->setWaterfallViewDelegate(nativeDelegate);
        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
};

class JSB_WaterfallViewDataSource: public CAObject,public CAWaterfallViewDataSource
{
public:
    JSB_WaterfallViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_WaterfallViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    void setJSDataSource(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    //Necessary
    virtual CAWaterfallViewCell* waterfallCellAtIndex(CAWaterfallView *waterfallView, const DSize& cellSize, unsigned int itemIndex)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAWaterfallViewCell* waterfallCell = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, cellSize);
        args[2] = uint32_to_jsval(cx, itemIndex);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallCellAtIndex", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                waterfallCell = (CAWaterfallViewCell*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( waterfallCell, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        return waterfallCell;
    }
    //Necessary
    virtual unsigned int waterfallViewHeightForItemAtIndex(CAWaterfallView *waterfallView, unsigned int itemIndex)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, itemIndex);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewHeightForItemAtIndex",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    //Necessary
    virtual unsigned int numberOfItems(CAWaterfallView *waterfallView)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfItems",1, &arg,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual CAView* waterfallViewSectionViewForHeader(CAWaterfallView *waterfallView, const DSize& viewSize)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewSectionViewForHeader", 2, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int waterfallViewHeightForHeader(CAWaterfallView *waterfallView)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewHeightForHeader",1, &arg,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual CAView* waterfallViewSectionViewForFooter(CAWaterfallView *waterfallView, const DSize& viewSize)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewSectionViewForFooter", 2, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int waterfallViewHeightForFooter(CAWaterfallView *waterfallView)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(waterfallView);
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewHeightForFooter",1, &arg,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual void waterfallViewWillDisplayCellAtIndex(CAWaterfallView* waterfallView, CAWaterfallViewCell* cell, unsigned int itemIndex)
    {
        jsval args[3];
        js_proxy_t * p1 = jsb_get_native_proxy(waterfallView);
        if (!p1) return;
        
        js_proxy_t * p2 = jsb_get_native_proxy(cell);
        if (!p2) return;
        args[0] = OBJECT_TO_JSVAL(p1->obj);
        args[1] = OBJECT_TO_JSVAL(p2->obj);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), itemIndex);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "waterfallViewWillDisplayCellAtIndex", 3, args);
    }
    
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CAWaterfallView_setWaterfallViewDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAWaterfallView * cobj = (CrossApp::CAWaterfallView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_WaterfallViewDataSource* pNativeSource = new (std::nothrow) JSB_WaterfallViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setJSDataSource(jsdata);
        
        JS_SetProperty(cx, obj, "m_pWaterfallViewDataSource", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_WATERFALLVIEW_DATA_SOURCE,pNativeSource);
        
        cobj->setWaterfallViewDataSource(pNativeSource);
        
        pNativeSource->release();
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}


//JSB_AutoCollectionViewDelegate
#define KEY_AUTOCOLLECTIONVIEW_DATA_SOURCE  "AutoCollectionViewDataSource"
#define KEY_AUTOCOLLECTIONVIEW_DELEGATE     "AutoCollectionViewDelegate"

class JSB_AutoCollectionViewDelegate: public CAObject,public CAAutoCollectionViewDelegate
{
public:
    JSB_AutoCollectionViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_AutoCollectionViewDelegate()
    {
        _JSDelegate = nullptr;
    }
    void setJSDelegate(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    virtual void collectionViewDidSelectCellAtIndexPath(CAAutoCollectionView *collectionView, unsigned int section, unsigned int item)
    {
        jsval args[3];
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), section);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), item);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewDidSelectCellAtIndexPath", 3, args);
    }
    
    virtual void collectionViewDidDeselectCellAtIndexPath(CAAutoCollectionView *collectionView, unsigned int section, unsigned int item)
    {
        jsval args[3];
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        if (!p) return;
        
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), section);
        args[2] = uint32_to_jsval(ScriptingCore::getInstance()->getGlobalContext(), item);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewDidDeselectCellAtIndexPath", 3, args);
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CAAutoCollectionView_setCollectionViewDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CAAutoCollectionView * cobj = (CAAutoCollectionView *)(proxy ? proxy->ptr : NULL);
    
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    
    if (argc == 1)
    {
        // save the delegate
        JS::RootedObject jsDelegate(cx, args.get(0).toObjectOrNull());
        JSB_AutoCollectionViewDelegate* nativeDelegate = new (std::nothrow) JSB_AutoCollectionViewDelegate();
        nativeDelegate->setJSDelegate(jsDelegate);
        
        JS_SetProperty(cx, obj, "_delegate", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_AUTOCOLLECTIONVIEW_DELEGATE,nativeDelegate);
        cobj->setCollectionViewDelegate(nativeDelegate);
//        nativeDelegate->release();
        
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
};

class JSB_AutoCollectionViewDataSource: public CAObject,public CAAutoCollectionViewDataSource
{
public:
    JSB_AutoCollectionViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_AutoCollectionViewDataSource()
    {
        _JSDelegate = nullptr;
    }
    void setJSDataSource(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    //Necessary
    virtual CACollectionViewCell* collectionCellAtIndex(CAAutoCollectionView *collectionView, const DSize& cellSize, unsigned int section, unsigned int item)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CACollectionViewCell* collectionCell = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[4];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, cellSize);
        args[2] = uint32_to_jsval(cx, section);
        args[3] = uint32_to_jsval(cx, item);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionCellAtIndex", 4, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                collectionCell = (CACollectionViewCell*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( collectionCell, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        return collectionCell;
    }
    
    //Necessary
    virtual DSize collectionViewSizeForItemAtIndexPath(CAAutoCollectionView* collectionView, unsigned int section, unsigned int item)
    {
        DSize size = DSizeZero;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        args[2] = uint32_to_jsval(cx, item);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewSizeForItemAtIndexPath",3, args,&retval);

        if (ok) {
            bool isSucceed = jsval_to_dsize(cx, retval, &size);
            if (isSucceed) return size;
        }

        return DSizeZero;
    }
    
    //Necessary
    virtual unsigned int numberOfItemsInSection(CAAutoCollectionView *collectionView, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "numberOfItemsInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual unsigned int numberOfSections(CAAutoCollectionView *collectionView)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        
        jsval arg = OBJECT_TO_JSVAL(p->obj);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewHeightForHeaderInSection",1, &arg,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        
        return 1;
    }
    
    virtual CAView* collectionViewSectionViewForHeaderInSection(CAAutoCollectionView *collectionView, const DSize& viewSize, unsigned int section)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        args[2] = uint32_to_jsval(cx, section);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewSectionViewForHeaderInSection", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;

    }
    
    virtual unsigned int collectionViewHeightForHeaderInSection(CAAutoCollectionView *collectionView, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewHeightForHeaderInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual CAView* collectionViewSectionViewForFooterInSection(CAAutoCollectionView *collectionView, const DSize& viewSize, unsigned int section)
    {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        
        CAView* view = NULL;
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[3];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = dsize_to_jsval(cx, viewSize);
        args[2] = uint32_to_jsval(cx, section);
        
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewSectionViewForFooterInSection", 3, args,&retval);
        if (ok) {
            do {
                js_proxy_t *proxy;
                JS::RootedObject tmpObj(cx,retval.toObjectOrNull());
                proxy = jsb_get_js_proxy(tmpObj);
                view = (CAView*)(proxy ? proxy->ptr : NULL);
                JSB_PRECONDITION2( view, cx, NULL, "Invalid Native Object");
            } while (0);
        }
        
        return view;
    }
    
    virtual unsigned int collectionViewHeightForFooterInSection(CAAutoCollectionView *collectionView, unsigned int section)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        js_proxy_t * p = jsb_get_native_proxy(collectionView);
        jsval args[2];
        args[0] = OBJECT_TO_JSVAL(p->obj);
        args[1] = uint32_to_jsval(cx, section);
        
        bool ok =ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewHeightForFooterInSection",2, args,&retval);
        unsigned index = 0;
        if (ok) {
            bool isSucceed = jsval_to_uint(cx, retval, &index);
            if (isSucceed) return index;
        }
        return index;
    }
    
    virtual void collectionViewWillDisplayCellAtIndex(CAAutoCollectionView* table, CACollectionViewCell* cell, unsigned int section, unsigned int item)
    {
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        
        js_proxy_t * p1 = jsb_get_native_proxy(table);
        js_proxy_t * p2 = jsb_get_native_proxy(cell);
        jsval args[4];
        args[0] = OBJECT_TO_JSVAL(p1->obj);
        args[1] = OBJECT_TO_JSVAL(p2->obj);
        args[2] = uint32_to_jsval(cx, section);
        args[3] = uint32_to_jsval(cx, item);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "collectionViewWillDisplayCellAtIndex",4, args);
    }
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CAAutoCollectionView_setCollectionViewDataSource(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CAAutoCollectionView * cobj = (CrossApp::CAAutoCollectionView *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc == 1)
    {
        JSB_AutoCollectionViewDataSource* pNativeSource = new (std::nothrow) JSB_AutoCollectionViewDataSource();
        JS::RootedObject jsdata(cx, args.get(0).toObjectOrNull());
        pNativeSource->setJSDataSource(jsdata);
        
        JS_SetProperty(cx, obj, "m_pCollectionViewDataSource", args.get(0));
        
        CAMap<std::string,CAObject*>* userDict = static_cast<CAMap<std::string,CAObject*>*>(cobj->getUserObject());
        if (NULL == userDict)
        {
            userDict = new (std::nothrow) CAMap<std::string,CAObject*>();
            cobj->setUserObject(userDict);
            userDict->release();
        }
        
        userDict->insert(KEY_AUTOCOLLECTIONVIEW_DATA_SOURCE,pNativeSource);
        
        cobj->setCollectionViewDataSource(pNativeSource);
        
        pNativeSource->release();
        
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "wrong number of arguments");
    return false;
}

#define KEY_DOWNLOAD_MANAGER_DELEGATE  "DownloadManagerDelegate"

class JSB_DownloadManagerDelegate : public CAObject,public CADownloadManagerDelegate
{
public:
    JSB_DownloadManagerDelegate()
    {
        _JSDelegate = nullptr;
    }
    virtual ~JSB_DownloadManagerDelegate()
    {
        _JSDelegate = nullptr;
    }
    void setJSDataSource(JS::HandleObject pJSDelegate)
    {
        _JSDelegate = pJSDelegate;
    }
    virtual void onError(unsigned long download_id, CADownloadManager::ErrorCode errorCode){
        
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        jsval args[2];
        
        args[0] = long_to_jsval(cx, download_id);
        args[1] = uint32_to_jsval(cx, errorCode);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "onError", 2, args);
    };
    
    virtual void onProgress(unsigned long download_id, int percent, unsigned long nowDownloaded, unsigned long totalToDownloaded){
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        jsval args[4];
        
        args[0] = long_to_jsval(cx, download_id);
        args[1] = uint32_to_jsval(cx, percent);
        args[2] = long_to_jsval(cx, nowDownloaded);
        args[3] = long_to_jsval(cx, totalToDownloaded);
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "onProgress", 4, args);
    };
    
    virtual void onPauseDownload(unsigned long download_id){
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        jsval args[1];
        args[0] = long_to_jsval(cx, download_id);

        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "onPauseDownload", 1, args);
    };
    
    virtual void onResumeDownload(unsigned long download_id){
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        jsval args[1];
        args[0] = long_to_jsval(cx, download_id);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "onResumeDownload", 1, args);
    };
    
    virtual void onSuccess(unsigned long download_id){
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JS::RootedValue retval(cx);
        
        jsval args[1];
        args[0] = long_to_jsval(cx, download_id);
        
        ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(_JSDelegate), "onSuccess", 1, args);
    };
private:
    JS::Heap<JSObject*> _JSDelegate;
};

static bool js_crossapp_CADownloadManager_setDownloadManagerDelegate(JSContext *cx, uint32_t argc, jsval *vp)
{
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    CrossApp::CADownloadManager* cobj = (CrossApp::CADownloadManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_crossapp_CADownloadManager_setDownloadManagerDelegate : Invalid Native Object");
    if (argc == 1) {
        JSB_DownloadManagerDelegate* arg0 =  new (std::nothrow) JSB_DownloadManagerDelegate();;
        do {
            if (args.get(0).isNull()) { arg0 = nullptr; break; }
            if (!args.get(0).isObject()) { ok = false; break; }
            js_proxy_t *jsProxy;
            JSObject *tmpObj = args.get(0).toObjectOrNull();
            jsProxy = jsb_get_js_proxy(tmpObj);
            arg0 = (JSB_DownloadManagerDelegate*)(jsProxy ? jsProxy->ptr : NULL);
            JSB_PRECONDITION2( arg0, cx, false, "Invalid Native Object");
        } while (0);
        JSB_PRECONDITION2(ok, cx, false, "js_crossapp_CADownloadManager_setDownloadManagerDelegate : Error processing arguments");
        cobj->setDownloadManagerDelegate(arg0);
        args.rval().setUndefined();
        return true;
    }
    
    JS_ReportError(cx, "js_crossapp_CADownloadManager_setDownloadManagerDelegate : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}


void register_all_crossapp_delegates_manual(JSContext* cx, JS::HandleObject global)
{
    JS::RootedObject ccObj(cx);
    JS::RootedObject jsbObj(cx);
    JS::RootedValue tmpVal(cx);
    JS::RootedObject tmpObj(cx);
    get_or_create_js_obj(cx, global, "ca", &ccObj);
    get_or_create_js_obj(cx, global, "jsb", &jsbObj);


    tmpObj.set(jsb_CrossApp_CATableView_prototype);
    JS_DefineFunction(cx, tmpObj, "setTableViewDelegate", js_crossapp_CATableView_setTableViewDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setTableViewDataSource", js_crossapp_CATableView_setTableViewDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CACollectionView_prototype);
    JS_DefineFunction(cx, tmpObj, "setCollectionViewDelegate", js_crossapp_CACollectionView_setCollectionViewDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setCollectionViewDataSource", js_crossapp_CACollectionView_setCollectionViewDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CAWaterfallView_prototype);
    JS_DefineFunction(cx, tmpObj, "setWaterfallViewDelegate", js_crossapp_CAWaterfallView_setWaterfallViewDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setWaterfallViewDataSource", js_crossapp_CAWaterfallView_setWaterfallViewDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    tmpObj.set(jsb_CrossApp_CAAutoCollectionView_prototype);
    JS_DefineFunction(cx, tmpObj, "setCollectionViewDelegate", js_crossapp_CAAutoCollectionView_setCollectionViewDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    JS_DefineFunction(cx, tmpObj, "setCollectionViewDataSource", js_crossapp_CAAutoCollectionView_setCollectionViewDataSource, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CATextField_prototype);
    JS_DefineFunction(cx, tmpObj, "setDelegate", js_crossapp_CATextField_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CATextView_prototype);
    JS_DefineFunction(cx, tmpObj, "setDelegate", js_crossapp_CATextView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
    tmpObj.set(jsb_CrossApp_CATextView_prototype);
    JS_DefineFunction(cx, tmpObj, "setDelegate", js_crossapp_CATextView_setDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

    tmpObj.set(jsb_CrossApp_CADownloadManager_prototype);
    JS_DefineFunction(cx, tmpObj, "setDownloadManagerDelegate", js_crossapp_CADownloadManager_setDownloadManagerDelegate, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    
}
