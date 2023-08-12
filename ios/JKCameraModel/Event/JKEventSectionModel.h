//
//  JKEventSectionModel.h
//  demo
//
//  Created by mac on 2022/1/8.
//  Copyright © 2022 mac. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JKEventModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface JKEventSectionModel : NSObject
///日期
@property (nonatomic, strong) NSString *date;
///是否选中，0未选中。1选中
@property (nonatomic ,strong) NSMutableArray <JKEventModel *>*modelArray;

+ (NSMutableArray *)handleDataIntoModels:(NSArray *)dataArr;


@end

NS_ASSUME_NONNULL_END
