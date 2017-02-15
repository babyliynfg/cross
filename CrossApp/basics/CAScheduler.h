

#ifndef __CASCHEDULER_H__
#define __CASCHEDULER_H__

#include <functional>
#include <mutex>
#include <set>

#include "basics/CAObject.h"
#include "basics/CASTLContainer.h"
#include "support/data_support/uthash.h"

NS_CC_BEGIN

class CAApplication;
struct _listEntry;
struct _hashSelectorEntry;
struct _hashUpdateEntry;

class CC_DLL CAScheduler : public CAObject
{
public:
    
    typedef std::function<void(float)> Callback;
    
    static const int PRIORITY_SYSTEM;
    
    static const int PRIORITY_NON_SYSTEM_MIN;

    static CAScheduler* getScheduler();
    
    void scheduleOnce(const CAScheduler::Callback& callback, const std::string& name, float delay, bool paused = false);
    void scheduleOnce(SEL_Schedule selector, CAObject *target, float delay, bool paused = false);
    
    void schedule(const CAScheduler::Callback& callback, const std::string& name, float interval, bool paused = false);
    void schedule(SEL_Schedule selector, CAObject *target, float interval, bool paused = false);
    
    void schedule(const CAScheduler::Callback& callback, const std::string& name, float interval, unsigned int repeat, float delay, bool paused = false);
    void schedule(SEL_Schedule selector, CAObject *target, float interval, unsigned int repeat, float delay, bool paused = false);

    void unschedule(const std::string& name);
    void unschedule(SEL_Schedule selector, CAObject *target);
    
    void unscheduleAllForName(const std::string& name);
    void unscheduleAllForTarget(CAObject* target);
    
    void unscheduleAll();

    bool isScheduled(SEL_Schedule selector, CAObject *target);

    void pauseName(const std::string& name);
    void pauseTarget(CAObject *target);

    void resumeName(const std::string& name);
    void resumeTarget(CAObject *target);
    
    bool isNamePaused(const std::string& name);
    bool isTargetPaused(CAObject *target);


    void scheduleUpdate(CAObject *target, int priority, bool paused);
    void unscheduleUpdate(CAObject *target);
    void unscheduleAllWithMinPriority(int minPriority);
    
    void pauseAllTargetsWithMinPriority(int minPriority);
    void resumeAllTargetsWithMinPriority(int minPriority);

    void pauseAll();
    void resumeAll();
    
    void performFunctionInUIThread( const std::function<void()> &function);
    
    inline float getTimeScale() { return _timeScale; }
    
    inline void setTimeScale(float timeScale) { _timeScale = timeScale; }
    
    void update(float dt);

private:
    
    CAScheduler();
    
    virtual ~CAScheduler();

public:

    unsigned int scheduleScriptFunc(unsigned int nHandler, float fInterval, bool bPaused);
    
    void unscheduleScriptEntry(unsigned int uScheduleScriptEntryID);
    
protected:

    void schedulePerFrame(const CAScheduler::Callback& callback, CAObject *target, int priority, bool paused);
    
    void removeHashElement(struct _hashSelectorEntry *element);
    void removeUpdateFromHash(struct _listEntry *entry);

    void priorityIn(struct _listEntry **list, const CAScheduler::Callback& callback, const std::string& name, int priority, bool paused);
    void appendIn(struct _listEntry **list, const CAScheduler::Callback& callback, const std::string& name, bool paused);
    
    
    float _timeScale;

    struct _listEntry *_updatesNegList;        // list of priority < 0
    struct _listEntry *_updates0List;            // list priority == 0
    struct _listEntry *_updatesPosList;        // list priority > 0
    struct _hashUpdateEntry *_hashForUpdates; // hash used to fetch quickly the list entries for pause,delete,etc

    struct _hashSelectorEntry *_hashForTimers;
    struct _hashSelectorEntry *_currentTarget;
    bool _currentTargetSalvaged;

    bool _updateHashLocked;

    std::vector<std::function<void()> > _functionsToPerform;
    std::mutex _performMutex;
    CAVector<CAObject*> m_obScriptHandlerEntries;
    
    friend class CAApplication;
};

NS_CC_END

#endif // __CASCHEDULER_H__
