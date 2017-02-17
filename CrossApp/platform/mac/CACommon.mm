
#include "platform/CACommon.h"
#include <stdarg.h>
#include <stdio.h>

NS_CC_BEGIN

void CCLog(const char * pszFormat, ...)
{
    printf("CrossApp: ");
    char szBuf[kMaxLogLen];

    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
    fflush(stdout);
}

NS_CC_END
