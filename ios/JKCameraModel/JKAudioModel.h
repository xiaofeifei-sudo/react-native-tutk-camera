//
//  JKAudioModel.h
//  demo
//
//  Created by mac on 2021/9/15.
//  Copyright © 2021 mac. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JKAudioModel : NSObject
///1、2、3用于排序
@property (nonatomic, assign) NSUInteger ID;
///sound10.wav (None)   sound0.wav ~ sound4.wav
@property (nonatomic, strong) NSString *fileName;
///"invalid":invalid  "":invalid
@property (nonatomic, strong) NSString *alias;
///录音时长
@property (nonatomic, assign) NSUInteger playTime;
///创建时间戳
@property (nonatomic, assign) NSUInteger createTime;
///录像时长 00:05
@property (nonatomic, strong) NSString *playTimeString;
///创建时间 2021/09/15
@property (nonatomic, strong) NSString *createTimeString;

@end

NS_ASSUME_NONNULL_END
