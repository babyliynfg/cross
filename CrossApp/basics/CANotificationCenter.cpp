

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

bool CANotificationCenter::observerExisted(const std::string& name, CAObject *target)
{
    for (auto & observer : m_observers)
    {
        CC_CONTINUE_IF(!observer);
        
        if (observer->name == name && observer->target == target)
            return true;
    }
    return false;
}

void CANotificationCenter::addObserver(const std::string& name, CAObject *target, const CANotificationCenter::Callback& callback)
{
    CC_RETURN_IF(this->observerExisted(name, target));
    
    Observer *observer = new Observer(name, target, callback);
    if (observer)
    {
        m_observers.pushBack(observer);
        observer->release();
    }
}

void CANotificationCenter::removeObserver(const std::string& name, CAObject *target)
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

void CANotificationCenter::registerScriptObserver(const std::string& name, CAObject *target, int handler)
{
    
    CC_RETURN_IF(this->observerExisted(name, target));
    
    Observer *observer = new Observer(name, target, nullptr);
    if (observer)
    {
        observer->handler = handler;
        m_observers.pushBack(observer);
        observer->release();
    }
}

void CANotificationCenter::unregisterScriptObserver(const std::string& name, CAObject *target)
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


CANotificationCenter::Observer::Observer(const std::string& name, CAObject *target, const CANotificationCenter::Callback& callback)
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
