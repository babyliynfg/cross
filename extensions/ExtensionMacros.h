

#ifndef __EXTENSIONMARCROS_H__
#define __EXTENSIONMARCROS_H__

#define NS_CC_EXT_BEGIN                     namespace extension {
#define NS_CC_EXT_END                       }
#define USING_NS_CC_EXT                     using namespace extension


#if defined(_WIN32) || defined(_WINRT) || defined(_WP8)
#define CC_EXT_DLL  __declspec(dllexport)
#else
#define CC_EXT_DLL
#endif

#endif

