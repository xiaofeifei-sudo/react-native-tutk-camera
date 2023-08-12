//
//  JKFeedModel.h
//  demo
//
//  Created by mac on 2021/9/15.
//  Copyright © 2021 mac. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface JKFeedModel : NSObject

///音频
@property (nonatomic ,strong)NSString * audioindex;
///设备id
@property (nonatomic ,strong)NSString * devid;
///喂食标签
@property (nonatomic ,strong)NSString * feedname;
///喂食时间
@property (nonatomic ,strong)NSString * feedtime;
///喂食类型
@property (nonatomic ,strong)NSString * feedtype;
///喂食重量
@property (nonatomic ,strong)NSString * feedweight;
///喂食分数 跟重量相差10倍
@property (nonatomic ,strong)NSString * feeddeal;
///喂食开关
@property (nonatomic ,strong)NSString * gofeed;
///
@property (nonatomic ,strong)NSString * index;
///10-big大食量, /*5-small小食量 2-unkown 未知*/
@property (nonatomic ,strong)NSString * lattic;
/// 0-not changed(没有变化)， 1－changed（变化了） 用于设置参数的时候控制是否发送给单片机
@property (nonatomic ,assign)NSInteger isMealInfoChanged;

@property (nonatomic ,assign)NSInteger feedYear;

@property (nonatomic ,assign)NSInteger feedMonth;

@property (nonatomic ,assign)NSInteger feedDay;

@property (nonatomic, strong)NSString *weekday;//周期

@property (nonatomic ,assign)NSInteger hour;

@property (nonatomic ,assign)NSInteger minute;
///时间，用于排序
@property (nonatomic ,assign)NSInteger timestamp;
/////时间，用于展示 07:00
//@property (nonatomic ,strong)NSString * feedtimeString;

- (void)mySetTimestamp;

@end

NS_ASSUME_NONNULL_END
