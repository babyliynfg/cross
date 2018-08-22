//
//  NSString+PeopleNameGetLetter.m
//  CrossApp
//
//  Created by Kevin on 2018/8/22.
//  Copyright © 2018年 cocos2d-x. All rights reserved.
//

#import "NSString+PeopleNameGetLetter.h"

@implementation NSString (PeopleNameGetLetter)


//获取拼音首字母(传入汉字字符串, 返回大写拼音首字母)
- (NSString *)firstLetter
{
    //转成了可变字符串
    NSMutableString *str = [NSMutableString stringWithString:self];
    //先转换为带声调的拼音
    CFStringTransform((CFMutableStringRef)str,NULL, kCFStringTransformMandarinLatin,NO);
    //再转换为不带声调的拼音
    CFStringTransform((CFMutableStringRef)str,NULL, kCFStringTransformStripDiacritics,NO);
    //转化为大写拼音
    NSString *pinYin = [str capitalizedString];
    //获取并返回首字母
    return [pinYin substringToIndex:1];
}

@end
