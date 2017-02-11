

#ifndef __SUPPORT_BASE64_H__
#define __SUPPORT_BASE64_H__

#include "platform/CCPlatformMacros.h"
#include <string>

namespace CrossApp
{

    static inline bool isBase64(unsigned char c)
    {
        return (isalnum(c) || (c == '+') || (c == '/'));
    }
    
    int CC_DLL base64Decode(const unsigned char *in, unsigned int inLength, unsigned char **out);

    int CC_DLL base64Encode(const unsigned char *in, unsigned int inLength, char **out);
    
}//namespace   CrossApp 


#endif // __SUPPORT_BASE64_H__
