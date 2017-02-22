

#include "../CAAlertViewImpl.h"
#include "jni/Java_org_CrossApp_lib_CrossAppHelper.h"

NS_CC_BEGIN


void __show_alertView(const std::string& title, const std::string& message, const std::vector<std::string>& buttonTitles, const std::function<void(int)>& callback)
{
    
    showDialogJNI(message.c_str(), title.c_str());
}

NS_CC_END
