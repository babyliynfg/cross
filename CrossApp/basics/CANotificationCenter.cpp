

#include "CANotificationCenter.h"
#include "CAValue.h"
#include "basics/CAApplication.h"
NS_CC_BEGIN

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
    return CAApplication::getApplication()->getNotificationCenter();
}

bool CANotificationCenter::observerExisted(CAObject *target, const std::string& name)
{
    if (m_observers.find(target) != m_observers.end())
    {
        for (auto & observer : m_observers.at(target))
        {
            CC_CONTINUE_IF(!observer);
            
            if (observer->name == name)
                return true;
        }
    }

    return false;
}

void CANotificationCenter::insertList(CAObject *target)
{
    if (m_observers.find(target) == m_observers.end())
    {
        m_observers.insert(std::make_pair(target, CAList<Observer*>()));
    }
}

void CANotificationCenter::addObserver(const CANotificationCenter::Callback& callback, CAObject *target, const std::string& name)
{
    CC_RETURN_IF(this->observerExisted(target, name));

    Observer *observer = new Observer(callback, target, name);
    if (observer)
    {
        this->insertList(target);
        m_observers.at(target).pushBack(observer);
        observer->release();
    }
}

void CANotificationCenter::removeObserver(CAObject *target, const std::string& name)
{
    if (m_observers.find(target) != m_observers.end())
    {
        CAList<Observer*>& observers = m_observers.at(target);
        for (auto itr = observers.begin(); itr != observers.end();)
        {
            Observer* observer = *itr;
            CC_CONTINUE_IF(!observer);
            
            if (observer->name == name)
            {
                itr = observers.erase(itr);
                break;
            }
            else
            {
                ++itr;
            }
        }
    }
}

int CANotificationCenter::removeAllObservers(CAObject *target)
{
	int size = 0;
    
    if (m_observers.find(target) != m_observers.end())
    {
        size = (int)m_observers.size();
        m_observers.erase(target);
    }

	return size;
}

void CANotificationCenter::registerScriptObserver(CAObject *target, const std::string& name, int handler)
{
    
    CC_RETURN_IF(this->observerExisted(target, name));
    
    Observer *observer = new Observer(nullptr, target, name);
    if (observer)
    {
        this->insertList(target);
        observer->handler = handler;
        m_observers.at(target).pushBack(observer);
        observer->release();
    }
}

void CANotificationCenter::unregisterScriptObserver(CAObject *target, const std::string& name)
{        
    if (m_observers.find(target) != m_observers.end())
    {
        CAList<Observer*>& observers = m_observers.at(target);
        for (auto itr = observers.begin(); itr != observers.end();)
        {
            Observer* observer = *itr;
            CC_CONTINUE_IF(!observer);
            
            if (observer->name == name)
            {
                itr = observers.erase(itr);
                break;
            }
            else
            {
                ++itr;
            }
        }
    }
}

void CANotificationCenter::postNotification(const std::string& name, CAObject *object)
{
    std::map<CAObject*, CAList<Observer*>> observersCopy = std::map<CAObject*, CAList<Observer*>>(m_observers);
    
    for (auto pair : observersCopy)
    {
        const CAList<Observer*>& observers = pair.second;
        for (auto observer : observers)
        {
            if (observer->name == name && observer->handler == 0)
            {
                observer->performSelector(object);
                break;
            }
        }
    }
}

void CANotificationCenter::postNotification(const std::string& name)
{
    this->postNotification(name, nullptr);
}

void CANotificationCenter::postNotificationWithIntValue(const std::string& name, int value)
{
    CAValue v = CAValue(value);
    this->postNotification(name, &v);
}

void CANotificationCenter::postNotificationWithFloatValue(const std::string& name, float value)
{
    CAValue v = CAValue(value);
    this->postNotification(name, &v);
}

void CANotificationCenter::postNotificationWithDoubleValue(const std::string& name, double value)
{
    CAValue v = CAValue(value);
    this->postNotification(name, &v);
}

void CANotificationCenter::postNotificationWithStringValue(const std::string& name, const std::string& value)
{
    CAValue v = CAValue(value);
    this->postNotification(name, &v);
}

int CANotificationCenter::getObserverHandlerByName(const std::string& name)
{
    if (name.empty())
    {
        return -1;
    }
    
    for (auto pair : m_observers)
    {
        const CAList<Observer*>& observers = pair.second;
        for (auto observer : observers)
        {
            if (observer->name == name)
            {
                return observer->handler;
                break;
            }
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
    if (callback)
    {
        callback(obj);
    }
}

NS_CC_END
