

#ifndef __CAKEYPAD_DISPATCHER_H__
#define __CAKEYPAD_DISPATCHER_H__

#include "CAKeypadDelegate.h"
#include "basics/CASTLContainer.h"

NS_CC_BEGIN


class CC_DLL CAKeypadDispatcher : public CAObject
{
public:
    
    enum class KeypadMSGType
    {
        BackClicked = 1,
        MenuClicked,
    };
    
public:
    
    CAKeypadDispatcher();
    
    ~CAKeypadDispatcher();

    void addDelegate(CAKeypadDelegate* pDelegate);

    void removeDelegate(CAKeypadDelegate* pDelegate);

    void forceAddDelegate(CAKeypadDelegate* pDelegate);

    void forceRemoveDelegate(CAKeypadDelegate* pDelegate);

    bool dispatchKeypadMSG(KeypadMSGType nMsgType);

protected:

    CAVector<CAObject*> m_vDelegates;
    bool m_bLocked;
    bool m_bToAdd;
    bool m_bToRemove;

    std::vector<CAKeypadDelegate*> m_vHandlersToAdd;
    std::vector<CAKeypadDelegate*> m_vHandlersToRemove;
};

// end of input group
/// @} 

NS_CC_END

#endif //__CCKEYPAD_DISPATCHER_H__
