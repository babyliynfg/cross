

#include "CANotificationCenter.h"

NS_CC_BEGIN

static CANotificationCenter *s_sharedNotifCenter = NULL;

CANotificationCenter::CANotificationCenter()
: m_scriptHandler(0)
{

}

CANotificationCenter::~CANotificationCenter()
{
    m_observers.clear();
}

CANotificationCenter *CANotificationCenter::getInstance(void)
{
    if (!s_sharedNotifCenter)
    {
        s_sharedNotifCenter = new (std::nothrow) CANotificationCenter();
    }
    return s_sharedNotifCenter;
}

void CANotificationCenter::destroyInstance(void)
{
    CC_SAFE_RELEASE_NULL(s_sharedNotifCenter);
}

bool CANotificationCenter::observerExisted(CAObject *target, const std::string& name)
{
    for (auto & observer : m_observers)
    {
        CC_CONTINUE_IF(!observer);
        
        if (observer->name == name && observer->target == target)
            return true;
    }
    return false;
}

void CANotificationCenter::addObserver(const CANotificationCenter::Callback& callback, CAObject *target, const std::string& name)
{
    CC_RETURN_IF(this->observerExisted(target, name));
    
    Observer *observer = new Observer(callback, target, name);
    if (observer)
    {
        m_observers.pushBack(observer);
        observer->release();
    }
}

void CANotificationCenter::removeObserver(CAObject *target, const std::string& name)
{
    for (auto itr=m_observers.begin(); itr!=m_observers.end();)
    {
        Observer* observer = *itr;
        CC_CONTINUE_IF(!observer);
        
        if (observer->name == name && observer->target == target)
        {
            itr = m_observers.erase(itr);
			break;
        }
        else
        {
            ++itr;
        }
    }
}

int CANotificationCenter::removeAllObservers(CAObject *target)
{
	int size = 0;
    for (auto itr=m_observers.begin(); itr!=m_observers.end();)
    {
        Observer* observer = *itr;
        CC_CONTINUE_IF(!observer);

        if (observer->target == target)
        {
			itr = m_observers.erase(itr);
			++size;
        }
		else
		{
			++itr;
		}
    }

	return size;
}

void CANotificationCenter::registerScriptObserver(CAObject *target, const std::string& name, int handler)
{
    
    CC_RETURN_IF(this->observerExisted(target, name));
    
    Observer *observer = new Observer(nullptr, target, name);
    if (observer)
    {
        observer->handler = handler;
        m_observers.pushBack(observer);
        observer->release();
    }
}

void CANotificationCenter::unregisterScriptObserver(CAObject *target, const std::string& name)
{        
    for (auto itr=m_observers.begin(); itr!=m_observers.end();)
    {
        Observer* observer = *itr;
        CC_CONTINUE_IF(!observer);
            
        if (observer->name == name && observer->target == target)
        {
            itr = m_observers.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}

void CANotificationCenter::postNotification(const std::string& name, CAObject *object)
{
    auto ObserversCopy = CAList<Observer*>(m_observers);
    
    for (auto observer : m_observers)
    {
        CC_CONTINUE_IF(!observer);
        
        if (observer->name == name)
        {
            if (0 == observer->handler)
            {
                observer->performSelector(object);
            }
        }
    }
}

void CANotificationCenter::postNotification(const std::string& name)
{
    this->postNotification(name, NULL);
}

int CANotificationCenter::getObserverHandlerByName(const std::string& name)
{
    if (name.empty())
    {
        return -1;
    }
    
    for (auto observer : m_observers)
    {
        CC_CONTINUE_IF(!observer);
        
        if (observer->name == name)
        {
            return observer->handler;
        }
    }
    
    return -1;
}


CANotificationCenter::Observer::Observer(const CANotificationCenter::Callback& callback, CAObject *target, const std::string& name)
:name(name)
,target(target)
,callback(callback)
{
    
}

void CANotificationCenter::Observer::performSelector(CAObject *obj)
{
    if (callback && obj)
    {
        callback(obj);
    }
}

NS_CC_END
