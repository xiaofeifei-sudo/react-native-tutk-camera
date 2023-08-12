//
//  JKFeedModel.m
//  demo
//
//  Created by mac on 2021/9/15.
//  Copyright © 2021 mac. All rights reserved.
//

#import "JKFeedModel.h"

@implementation JKFeedModel

- (id)copyWithZone:(NSZone *)zone {
    
    /*
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
     ///10-big大食量, 5-small小食量 2-unkown 未知
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
     */
    JKFeedModel * model = [[JKFeedModel alloc] init];
    model.audioindex = self.audioindex;
    model.devid = self.devid;
    model.feedname = self.feedname;
    model.feedtime = self.feedtime;
    model.feedtype = self.feedtype;
    model.feedweight = self.feedweight;
    model.feeddeal = self.feeddeal;
    model.gofeed = self.gofeed;
    model.index = self.index;
    model.lattic = self.lattic;
    model.isMealInfoChanged = self.isMealInfoChanged;
    model.feedYear = self.feedYear;
    model.feedMonth = self.feedMonth;
    model.feedDay = self.feedDay;
    model.weekday = self.weekday;
    model.hour = self.hour;
    model.minute = self.minute;
    model.timestamp = self.timestamp;

    return model;
}


#pragma mark ===============注册一个不为空的===============
+ (JKFeedModel *)initNotEmpty{
    JKFeedModel * model = [[JKFeedModel alloc] init];
    if (self) {
        NSDate *nowDate = [NSDate date];
        NSCalendar *calendar = [NSCalendar currentCalendar];
        NSUInteger unitFlags = NSCalendarUnitYear | //年
        NSCalendarUnitMonth | //月份
        NSCalendarUnitDay | //日
        NSCalendarUnitHour |  //小时
        NSCalendarUnitMinute |  //分钟
        NSCalendarUnitSecond;  // 秒
        NSDateComponents *dateComponent = [calendar components:unitFlags fromDate:nowDate];
        
        NSInteger year = [dateComponent year];
        NSInteger month = [dateComponent month];
        NSInteger hour = [dateComponent hour];
        NSInteger minute = [dateComponent minute];
        
        model.feedYear = (int)year - 1960;
        model.feedMonth = (int)month;
        model.hour = (int)hour;
        model.minute = (int)minute;
        model.feedweight = @"10";
        model.feeddeal = @"1";
        
        model.audioindex = @"0";
        model.feedname = @"";
        if (hour < 10) {
            if (minute < 10) {
                model.feedtime = [NSString stringWithFormat:@"0%d:0%d",(int)hour,(int)minute];
            }else {
                model.feedtime = [NSString stringWithFormat:@"0%d:%d",(int)hour,(int)minute];
            }
        }else {
            if (minute < 10) {
                model.feedtime = [NSString stringWithFormat:@"%d:0%d",(int)hour,(int)minute];
            }else {
                model.feedtime = [NSString stringWithFormat:@"%d:%d",(int)hour,(int)minute];
            }
        }
        
        model.feedtype = @"1";
        model.gofeed = @"1";
        model.lattic = @"5";
        model.timestamp = hour*60 + minute;
        return model;

    }
    return model;
}


- (void)mySetTimestamp {
    if (self.feedtime.length != 0 && self.feedtime != nil) {
     
        self.timestamp = self.hour*60 + self.minute;

        self.feedtime = [NSString stringWithFormat:@"%02d:%02d", self.hour, self.minute];
        
    }else {
        NSArray *array = [self.feedtime componentsSeparatedByString:@":"];
        if (array.count == 2) {
            self.timestamp = [array.firstObject intValue]*60 + [array.lastObject intValue];
        }else {
            self.timestamp = 0;
        }
    }

}


@end
