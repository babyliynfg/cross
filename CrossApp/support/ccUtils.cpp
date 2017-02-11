
#include "ccUtils.h"
#include <iostream>
#include <cstdlib>

namespace CrossApp {

CC_DLL unsigned long ccNextPOT(unsigned long x)
{
    x = x - 1;
    x = x | (x >> 1);
    x = x | (x >> 2);
    x = x | (x >> 4);
    x = x | (x >> 8);
    x = x | (x >>16);
    return x + 1;
}

CC_DLL std::vector<std::string> Parse2StrVector(const std::string& str, const std::string& strDelimiter, bool bIncludeEmptyStr)
{
	std::vector<std::string> strVector;

	size_t pos = 0;
	if (!str.empty())
	{
		size_t first = str.find(strDelimiter);
		while (first != std::string::npos)
		{
			std::string cszStrTemp = str.substr(pos, first - pos);
			if (!cszStrTemp.empty() || bIncludeEmptyStr)
				strVector.push_back(cszStrTemp);

			pos = first + strDelimiter.size();
			first = str.find(strDelimiter, pos);
		}
		std::string cszStrTemp = str.substr(pos, str.size() - pos);
		if (!cszStrTemp.empty() || bIncludeEmptyStr)
			strVector.push_back(cszStrTemp);
	}
	return strVector;
}
    
CC_DLL long hex2Int(const std::string& hexStr)
{
    char *offset;
    if(hexStr.length() > 2)
    {
        if(hexStr[0] == '0' && hexStr[1] == 'x')
        {
            return strtol(hexStr.c_str(), &offset, 0);
        }
    }
    return strtol(hexStr.c_str(), &offset, 16);
}

}