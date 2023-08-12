//
//  JKEventSectionModel.m
//  mode
//
//  Created by mac on 2022/1/8.
//  Copyright © 2022 mac. All rights reserved.
//

#import "JKEventSectionModel.h"

@implementation JKEventSectionModel

+ (NSMutableArray *)handleDataIntoModels:(NSArray *)dataArr {
    
    NSMutableArray * outDataArr = [[NSMutableArray alloc] init];
    //如果请求到的数据为空，则直接返回
    if (dataArr.count == 0)
        return [[NSMutableArray alloc] init];

    NSMutableArray *timeArr = [NSMutableArray array];
    //首先把原数组中数据的日期取出来放入timeArr
    [dataArr enumerateObjectsUsingBlock:^(JKEventModel * model, NSUInteger idx, BOOL *stop) {
        //这里只是根据日期判断，所以去掉时间字符串
        [timeArr addObject:model.date];
    }];
    
    //日期去重
    NSSet *set = [NSSet setWithArray:timeArr];
    NSArray *userArray = [set allObjects];
    
    //重新降序排序
    NSSortDescriptor *sd1 = [NSSortDescriptor sortDescriptorWithKey:nil ascending:NO];//yes升序排列，no,降序排列
    NSArray * descendingDateArr = [userArray sortedArrayUsingDescriptors:[NSArray arrayWithObjects:sd1, nil]];
    
    //此时得到的descendingDateArr就是按照时间降序排好的日期数组
    //根据日期数组的个数，生成对应数量的外层model，外层model的detailModelArr置为空数组，放置子model（每一行显示的数据model）
    [descendingDateArr enumerateObjectsUsingBlock:^(id  _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
        JKEventSectionModel * skmodel = [[JKEventSectionModel alloc] init];
        skmodel.modelArray = [[NSMutableArray alloc] init];
        
        [outDataArr addObject:skmodel];
    }];

    //遍历未经处理的数组，取其中每个数据的日期，看与降序排列的日期数组相比，若日期匹配就把这个数据装到对应的外层model中
    [dataArr enumerateObjectsUsingBlock:^(JKEventModel *model, NSUInteger idx, BOOL * _Nonnull stop) {
        for (NSString *str in descendingDateArr) {
       
            if([str isEqualToString:model.date]) {
                JKEventSectionModel * skmodel = [outDataArr objectAtIndex:[descendingDateArr indexOfObject:str]];
                skmodel.date = model.date;
                [skmodel.modelArray addObject:model];
            }
        }
    }];
    //每天时间降序排列
    for (JKEventSectionModel *model in outDataArr) {
        [model.modelArray sortUsingComparator:^NSComparisonResult(id  _Nonnull obj1, id  _Nonnull obj2) {
            JKEventModel * model1 = (JKEventModel *)obj1;
            JKEventModel * model2 = (JKEventModel *)obj2;
            if (model1.eventTime < model2.eventTime) {
                return NSOrderedDescending;//降序
            }else{
                return NSOrderedAscending;//升序
            }
        }];
        
    }

    return outDataArr;
}

@end
