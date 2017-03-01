//
//  CAAddressBook.cpp
//  CrossApp
//
//  Created by 秦乐 on 2017/2/21.
//  Copyright © 2017年 cocos2d-x. All rights reserved.
//
#include "../CAAddressBook.h"
#include "support/Json/CSContentJsonDictionary.h"

NS_CC_BEGIN

CAAddressBook::CAAddressBook()
{
}

CAAddressBook::~CAAddressBook()
{
}

std::function<void(const std::vector<CAAddressBook::Date>&)> _bookCallBack;

std::vector<CAAddressBook::Date> _addressBookVec;

void CAAddressBook::getAddressBook(const std::function<void(const std::vector<CAAddressBook::Date>&)>& callback)
{
    _bookCallBack = callback;
}

NS_CC_END
