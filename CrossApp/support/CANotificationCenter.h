

#ifndef __CANotificationCenter_H__
#define __CANotificationCenter_H__

#include "basics/CAObject.h"
#include "basics/CASTLContainer.h"

NS_CC_BEGIN

/**
 * @js NA
 * @lua NA
 */
class CC_DLL CANotificationObserver : public CAObject
{
public:

    CANotificationObserver(CAObject *target,
                           SEL_CallFuncO selector,
                           const std::string& name,
                           CAObject *obj);
    
    ~CANotificationObserver();
    
    void performSelector(CAObject *obj);
    
    CC_PROPERTY_READONLY(CAObject *, m_target, Target);
    
    CC_PROPERTY_READONLY(SEL_CallFuncO, m_selector, Selector);
    
    CC_PROPERTY_READONLY_PASS_BY_REF(std::string, m_name, Name);
    
    CC_PROPERTY_READONLY(CAObject *, m_object, Object);
    
    CC_PROPERTY(int, m_nHandler,Handler);
};

/**
 * @js NA
 */
class CC_DLL CANotificationCenter : public CAObject
{
public:

    CANotificationCenter();

    ~CANotificationCenter();
    
    static CANotificationCenter *getInstance();
    
    static void destroyInstance();
    
    CC_DEPRECATED_ATTRIBUTE static CANotificationCenter *sharedNotificationCenter(void)
    {
        return CANotificationCenter::getInstance();
    }
    
    CC_DEPRECATED_ATTRIBUTE static void purgeNotificationCenter(void)
    {
        CANotificationCenter::destroyInstance();
    }

    void addObserver(CAObject *target, 
                     SEL_CallFuncO selector,
                     const std::string& name,
                     CAObject *obj);

    void removeObserver(CAObject *target,const std::string& name);

    int removeAllObservers(CAObject *target);

    void registerScriptObserver(CAObject *target, int handler, const std::string& name);

    void unregisterScriptObserver(CAObject *target, const std::string& name);

    void postNotification(const std::string& name);

    void postNotification(const std::string& name, CAObject *object);

    inline int getScriptHandler() { return m_scriptHandler; };

    int getObserverHandlerByName(const std::string& name);
    
private:

    bool observerExisted(CAObject *target, const std::string& name);

    CAList<CANotificationObserver*> m_observers;
    
    int     m_scriptHandler;
};



NS_CC_END

#endif//__CANotificationCenter_H__
