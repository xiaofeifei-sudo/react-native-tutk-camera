#ifndef __INFO_H_
#define __INFO_H_

/*请求的无线模块的动作类型*/
enum REQUEST_TYPE{
	REQ_UNKNOWN = 0,
	REQ_PAIR,
	REQ_EXPAIR,
	REQ_DELONE,
	REQ_DEPAIR,
	REQ_RDPAIR,
};

/*请求无限模块的动作指令*/
#define REQUEST_PAIR	"+MSGYJTPAIR\r" //配对
#define REQUEST_EXPAIR	"+MSGYJTEXPAIR\r" //退出配对
#define REQUEST_DELONE	"+MSGYJTDELONE=" //删除一个配对
#define REQUEST_DEPAIR	"+MSGYJTDEPAIR\r" //删除全部配对
#define REQUEST_RDPAIR	"+MSGYJTRDPAIR\r" //读取配对信息

#define PRO_END '\r'

/*传感器报警数据类型*/
enum RETURN_TYPE{
    RET_ALL_INFO=-1,
	RET_UNKNOWN = 0,
	RET_WARN,
	RET_SOS,
	RET_RSET,
	RET_RDIS,
	RET_LVOL,
	RET_BEAT,
	RET_REPT,
	RET_PAIR,
	RET_TOPAIR,
	RET_NORMAL //无线模块正常应答
};

/*传感器报警数据头*/
#define RETURN_YJT			"AT+YJT\r"
#define RETURN_YJTWARN		"AT+YJTWARN=" //门磁报警
#define RETURN_YJTSOS		"AT+YJTSOS=" //SOS报警
#define RETURN_YJTRSET		"AT+YJTRSET=" //布防
#define RETURN_YJTRDIS		"AT+YJTRDIS=" //撤防
#define RETURN_YJTLVOL		"AT+YJTLVOL=" //低压
#define RETURN_YJTBEAT		"AT+YJTBEAT=" //心跳包
#define RETURN_YJTREPT		"AT+YJTREPT=" //其他通用包
#define RETURN_YJTPAIR		"AT+YJTPAIR=" //配对返回
#define RETURN_YJTTOPAIR	"AT+YJTTOPAIR=" //查询配对返回


/*传感器ID长度*/
#define SENSOR_ID_LEN 14

/*传感器类型*/
enum SENSOR_TYPE{
	ST_LOCAL	= 0X00,	//无线模块
	ST_DOOR		= 0x01, //门磁
	ST_INFRARED = 0x02, //红外
	ST_SMOKE	= 0x03, //烟感
	ST_GAS		= 0x04, //气感
	ST_ALARM	= 0x05, //报警
	ST_SWITCH	= 0x06, //开关
	ST_REMOTER	= 0x07, //遥控
	ST_MAINUNIT	= 0xE1, //主机
	ST_ELECTRIAL= 0xE2  //家电
};


/*传感器控制码,暂未用上*/
enum CTRL_ID{
	CI_WARN		= 0x01, //告警
	CI_LVOL		= 0x02, //低电
	CI_BEAT		= 0x03, //心跳
	CI_PING		= 0x04, //ping
	CI_RSET		= 0x05, //设防
	CI_RDIS		= 0x06, //撤防
	CI_SOS		= 0x07, //紧急求助
	CI_PAIR		= 0x08, //对码
	CI_SCMD		= 0x10, //终端下发命令
	CI_REPORT	= 0x80, //上报执行状况
	CI_SUCCESS	= 0x64, //成功
	CI_WATER	= 0x11, //水浸
	CI_SHAKE	= 0x12, //震动
	CI_FAILURE	= 0xC8, //失败
	CI_ERROR	= 0xEE, //错误
	CI_UNEFFECT = 0xFF  //命令无效
};


#endif
