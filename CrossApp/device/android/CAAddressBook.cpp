//
//  CAAddressBook.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//
#include "CAAddressBook.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "basics/CAApplication.h"


NS_CC_BEGIN

extern "C"
{
    void JAVAGetAddressBook()
    {
        JniMethodInfo jmi;
        if(JniHelper::getStaticMethodInfo(jmi, "org/CrossApp/lib/CrossAppDevice", "getPersonList", "()V"))
        {
            jmi.env->CallStaticVoidMethod(jmi.classID, jmi.methodID);
            jmi.env->DeleteLocalRef(jmi.classID);
        }
    }
}

CAAddressBook::CAAddressBook()
{
}

CAAddressBook::~CAAddressBook()
{
}

std::function<void(const std::vector<CAAddressBook::Date>&)> _callBack;

void getAddressBook(const std::function<void(const std::vector<CAAddressBook::Date>&)>& callback)
{
    _callBack = callback;
    
    JAVAGetAddressBook();
}

extern "C"
{
    JNIEXPORT void JNICALL Java_org_CrossApp_lib_CrossAppPersonList_getPersonList(JNIEnv *env,jobject obj,jstring arg1)
    {
        const char *sPersonList = env->GetStringUTFChars(arg1,false);
        
        CSJson::Reader read;
        CSJson::Value root;
        
        if (read.parse(sPersonList, root))
        {
            CSJson::Value personlist;
            personlist = root["person"];
            
            for (int i=0; i<personlist.size(); i++)
            {
                CSJson::Value person;
                person = personlist[i];
                CAAddressBookRecord addrec;
                
                addrec.fullname = person["name"].asString();
                
                CSJson::Value phonelist = person["phone"];
                
                for (int i=0; i<1; i++)
                {
                    addrec.phoneNumber = phonelist[i].asString();
                }
                
                addrec.email = person["email"].asString();
                
                addrec.street = person["address_street"].asString();
                
                addrec.province = person["address_region"].asString();
                
                addrec.city = person["address_city"].asString();
                
                addrec.nickname = person["nickname"].asString();
                
                addrec.zip = person["address_postCode"].asString();
                
                _addressBookArr.push_back(addrec);
                
            }
        }
        
        if(_callBack)
        {
            _callBack(_addressBookArr);
        }
    }
}

NS_CC_END
