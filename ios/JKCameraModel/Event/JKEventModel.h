//
//  JKEventModel.h
//  demo
//
//  Created by mac on 2021/9/15.
//  Copyright © 2021 mac. All rights reserved.
//

#define EVENT_UNREADED 0
#define EVENT_READED 1
#define EVENT_NORECORD 2

#import "AVIOCTRLDEFuserdefineds.h"

@interface JKEventModel : NSObject {
    
}
///日期
@property (nonatomic, strong) NSString *date;
///时间格式字符串
@property (nonatomic, strong) NSString *timeStr;
///是否选中，0未选中。1选中
@property (nonatomic ,assign) BOOL isSelection;
///设备ID
@property (nonatomic, strong) NSString *devid;
///事件类型
@property (nonatomic, assign) int eventType;
///事件类型
@property (nonatomic, strong) NSString *eventTypeStr;
///时间戳
@property (nonatomic, assign) long eventTime;
///事件状态
@property (nonatomic, assign) int eventStatus;



@property (nonatomic, strong) NSString *eventPicn;
///重量
@property (nonatomic, assign) int weight;

#pragma mark ===============获取事件名称===============
+ (NSString *)getEventTypeName:(int)eventType;
#pragma mark ===============获取事件结构体===============
+ (STimeDay)getTimeDay:(long)time;

- (id)initWithEventType:(int)eventType EventTime:(long)eventTime EventStatus:(int)status;

- (id)initWithEventType:(int)eventType EventTime:(long)eventTime EventStatus:(int)status EventPicn:(NSString *)eventPicn;

@end
