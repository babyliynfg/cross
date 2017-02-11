//
//  CAAddress.h
//  iBook
//
//  Created by lh on 14-5-6.
//
//

#import <Foundation/Foundation.h>
#import <AddressBook/AddressBook.h>
#import <AddressBookUI/AddressBookUI.h>
#include "../CADevice.h"

@interface CAAddress : NSObject
{
    CrossApp::CAPersonListDelegate* _personListDelegate;
}

-(void)getAddressBook;

-(void)addDelegate:(CrossApp::CAPersonListDelegate*)delegate;

@end
