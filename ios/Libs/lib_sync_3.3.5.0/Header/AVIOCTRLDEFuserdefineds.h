/*
 * AVIOCTRLDEFuserdefineds.h
 *	Define AVIOCTRL Message Type and Context
 *  Created on: 2013-10-29
 *  Author: JK-HZX
 *
 */
#ifndef _AVIOCTRL_DEFINE_USER_DEFINED_H_
#define _AVIOCTRL_DEFINE_USER_DEFINED_H_
/////////////////////////////////////////////////////////////////////////////////
/////////////////// Message Type Define//////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*my uid:DRX9B77YJ8V6AGPMS7EJ
 *aide uid list
 *FL8T9HRY5C2RVM6PWFPJ //hejh-ak-new-white
D7C9ANR69M27VNPPSFCJ  //hejh-ak-old-black
FF4TBHR6CCK7VMPPWFC1 //zhang
DB8T9HRECM27BM6PWFCJ //zhang
 **/
//int  SERVTYPE_STREAM_SERVER = 0;//16
//[bit0-bit17]:0-valid, 1-invalid, [bit18-bit32]::1-valid, 0-invalid,
//18-upgrade_onliine, 19-ptz-support, 20-restore-factory, 21-reboot, 22-ircut, 23, audio-two-channle
//24-playback-control-forward, 25-record-support-audio 26:osd-name-set,
#include "IOTCamera//AVIOCTRLDEFs.h"
// AVIOCTRL Message Type
typedef enum
{
    //for aide
    // 设置door senser & open
    IOTYPE_USER_IPCAM_GET_DOOR_STAUTS_REQ       = 0x512,
    IOTYPE_USER_IPCAM_GET_DOOR_STATUS_RESP      = 0x513,
    IOTYPE_USER_IPCAM_SET_DOOR_STAUTS_REQ       = 0x514,
    IOTYPE_USER_IPCAM_SET_DOOR_STATUS_RESP      = 0x515,

    //TUTK PROTOCL
    IOTYPE_PRESET_SETPRESET_REQ                 = 0x440,
    IOTYPE_PRESET_SETPRESET_RESP                = 0x441,
    IOTYPE_PRESET_GETPRESET_REQ                 = 0x442,
    IOTYPE_PRESET_GETPRESET_RESP                = 0x443,
    IOTYPE_CRUISEMODE_CRUISE_START              = 0x0600,
    IOTYPE_CRUISEMODE_CRUISE_STOP               = 0x0601,

    //for wayde
    IOTYPE_USER_IPCAM_USER_WAYDEA_REQ           = 0x602,
    IOTYPE_USER_IPCAM_USER_WAYDEA_RESP          = 0x603,

    //是否启用Door  密码模式
    IOTYPE_USER_IPCAM_GET_DOORPASSWORDMODE_REQ  =0x516,
    IOTYPE_USER_IPCAM_GET_DOORPASSWORDMODE_RESP =0x517,
    IOTYPE_USER_IPCAM_SET_DOORPASSWORDMODE_REQ  =0x518,
    IOTYPE_USER_IPCAM_SET_DOORPASSWORDMODE_RESP =0x519,
    //设置Door 密码
    IOTYPE_USER_IPCAM_SET_DOORPASSWORD_REQ      =0x520,
    IOTYPE_USER_IPCAM_SET_DOORPASSWORD_RESP     =0x521,
    //////////////end of aide
//    //设置同步app时间
//    IOTYPE_USER_IPCAM_SET_SYNC_TIME_REQ         = 0x816,
//    IOTYPE_USER_IPCAM_SET_SYNC_TIME_RESP        = 0x817,

    IOTYPE_USER_IPCAM_GETDEVINFO_REQ 			= 0x2000,
    IOTYPE_USER_IPCAM_GETDEVINFO_RESP			= 0x2001,

    IOTYPE_USER_IPCAM_SET_DEVNAME_REQ			= 0x2002,
    IOTYPE_USER_IPCAM_SET_DEVNAME_RESP			= 0x2003,
    IOTYPE_USER_IPCAM_GET_DEVNAME_REQ			= 0x2004,
    IOTYPE_USER_IPCAM_GET_DEVNAME_RESP			= 0x2005,

    IOTYPE_USER_IPCAM_SET_DATETIME_REQ			= 0x2006,
    IOTYPE_USER_IPCAM_SET_DATETIME_RESP			= 0x2007,
    IOTYPE_USER_IPCAM_GET_DATETIME_REQ			= 0x2008,
    IOTYPE_USER_IPCAM_GET_DATETIME_RESP			= 0x2009,

    IOTYPE_USER_IPCAM_DEVRESET_REQ 				= 0x200A,
    IOTYPE_USER_IPCAM_DEVRESET_RESP				= 0x200B,

    IOTYPE_USER_IPCAM_DEVREBOOT_REQ 			= 0x200C,
    IOTYPE_USER_IPCAM_DEVREBOOT_RESP			= 0x200D,

    IOTYPE_USER_IPCAM_SET_IPV4NET_REQ			= 0x200E,
    IOTYPE_USER_IPCAM_SET_IPV4NET_RESP			= 0x200F,
    IOTYPE_USER_IPCAM_GET_IPV4NET_REQ			= 0x2010,
    IOTYPE_USER_IPCAM_GET_IPV4NET_RESP			= 0x2011,

    IOTYPE_USER_IPCAM_SET_FTP_REQ				= 0x2012,
    IOTYPE_USER_IPCAM_SET_FTP_RESP				= 0x2013,
    IOTYPE_USER_IPCAM_GET_FTP_REQ				= 0x2014,
    IOTYPE_USER_IPCAM_GET_FTP_RESP				= 0x2015,

    IOTYPE_USER_IPCAM_SET_EMAIL_REQ				= 0x2016,
    IOTYPE_USER_IPCAM_SET_EMAIL_RESP			= 0x2017,
    IOTYPE_USER_IPCAM_GET_EMAIL_REQ				= 0x2018,
    IOTYPE_USER_IPCAM_GET_EMAIL_RESP			= 0x2019,

    IOTYPE_USER_IPCAM_SET_PTZ_REQ				= 0x201A,
    IOTYPE_USER_IPCAM_SET_PTZ_RESP				= 0x201B,
    IOTYPE_USER_IPCAM_GET_PTZ_REQ				= 0x201C,
    IOTYPE_USER_IPCAM_GET_PTZ_RESP				= 0x201D,

    IOTYPE_USER_IPCAM_SET_ALARM_REQ				= 0x201E,
    IOTYPE_USER_IPCAM_SET_ALARM_RESP			= 0x201F,
    IOTYPE_USER_IPCAM_GET_ALARM_REQ				= 0x2020,
    IOTYPE_USER_IPCAM_GET_ALARM_RESP			= 0x2021,

    IOTYPE_USER_IPCAM_SET_VRPROGRAM_REQ			= 0x2022,
    IOTYPE_USER_IPCAM_SET_VRPROGRAM_RESP		= 0x2023,
    IOTYPE_USER_IPCAM_GET_VRPROGRAM_REQ			= 0x2024,
    IOTYPE_USER_IPCAM_GET_VRPROGRAM_RESP		= 0x2025,

    IOTYPE_USER_IPCAM_SET_VIDEO_REQ				= 0x2026,
    IOTYPE_USER_IPCAM_SET_VIDEO_RESP			= 0x2027,
    IOTYPE_USER_IPCAM_GET_VIDEO_REQ				= 0x2028,
    IOTYPE_USER_IPCAM_GET_VIDEO_RESP			= 0x2029,

    IOTYPE_USER_IPCAM_SET_VIDEOFRAME_REQ		= 0x202A,
    IOTYPE_USER_IPCAM_SET_VIDEOFRAME_RESP		= 0x202B,
    IOTYPE_USER_IPCAM_GET_VIDEOFRAME_REQ		= 0x202C,
    IOTYPE_USER_IPCAM_GET_VIDEOFRAME_RESP		= 0x202D,

    IOTYPE_USER_IPCAM_SET_VIDEOOSD_REQ			= 0x202E,
    IOTYPE_USER_IPCAM_SET_VIDEOOSD_RESP			= 0x202F,
    IOTYPE_USER_IPCAM_GET_VIDEOOSD_REQ			= 0x2030,
    IOTYPE_USER_IPCAM_GET_VIDEOOSD_RESP			= 0x2031,

    IOTYPE_USER_IPCAM_SET_AUDIO_REQ				= 0x2032,
    IOTYPE_USER_IPCAM_SET_AUDIO_RESP			= 0x2033,
    IOTYPE_USER_IPCAM_GET_AUDIO_REQ				= 0x2034,
    IOTYPE_USER_IPCAM_GET_AUDIO_RESP			= 0x2035,

    IOTYPE_USER_IPCAM_SET_PTZSPEED_REQ			= 0x2036,
    IOTYPE_USER_IPCAM_SET_PTZSPEED_RESP			= 0x2037,
    IOTYPE_USER_IPCAM_GET_PTZSPEED_REQ			= 0x2038,
    IOTYPE_USER_IPCAM_GET_PTZSPEED_RESP			= 0x2039,

    IOTYPE_USER_IPCAM_SET_PTZPRESET_REQ			= 0x203A,
    IOTYPE_USER_IPCAM_SET_PTZPRESET_RESP		= 0x203B,
    IOTYPE_USER_IPCAM_GET_PTZPRESET_REQ			= 0x203C,
    IOTYPE_USER_IPCAM_GET_PTZPRESET_RESP		= 0x203D,

    IOTYPE_USER_IPCAM_SET_CAMERA_REQ			= 0x203E,
    IOTYPE_USER_IPCAM_SET_CAMERA_RESP			= 0x203F,
    IOTYPE_USER_IPCAM_GET_CAMERA_REQ			= 0x2040,
    IOTYPE_USER_IPCAM_GET_CAMERA_RESP			= 0x2041,
    IOTYPE_USER_IPCAM_DOWNLOAD_FILE_REQ         = 0x2042,
    IOTYPE_USER_IPCAM_DOWNLOAD_FILE_RESP        = 0x2043,
    IOTYPE_USER_IPCAM_GET_EXTERNAL_DEVICES_REQ  = 0x2044,
    IOTYPE_USER_IPCAM_GET_EXTERNAL_DEVICES_RESP = 0x2045,

    IOTYPE_USER_IPCAM_SET_UPGRDEONLIN_REQ		= 0x2046,
    IOTYPE_USER_IPCAM_SET_UPGRADEONLIN_RESP		= 0x2047,
    IOTYPE_USER_IPCAM_SET_IRCUT_REQ		        = 0x2048,
    IOTYPE_USER_IPCAM_SET_IRCUT_RESP		    = 0x2049,
    IOTYPE_USER_IPCAM_GET_MAC_REQ		        = 0x2050,
    IOTYPE_USER_IPCAM_GET_MAC_RESP   		    = 0x2051,
    IOTYPE_USER_IPCAM_SET_TIME_REQ		        = 0x2052,
    IOTYPE_USER_IPCAM_SET_TIME_RESP   		    = 0x2053,
    IOTYPE_USER_IPCAM_EDIT_FILES_REQ		    = 0x2054,
    IOTYPE_USER_IPCAM_EDIT_FILES_RESP   		= 0x2055,
    IOTYPE_USER_IPCAM_THIRDPART_SETTING_REQ	    = 0x2056,
    IOTYPE_USER_IPCAM_THIRDPART_SETTING_RESP 	= 0x2057,
    IOTYPE_USER_IPCAM_WIFI_AP_SETTING_REQ       =0x2058,
    IOTYPE_USER_IPCAM_WIFI_AP_SETTING_RESP      =0x2059,
    IOTYPE_USER_IPCAM_WIFI_AP_GETTING_REQ       =0x2060,
    IOTYPE_USER_IPCAM_WIFI_AP_GETTING_RESP      =0x2061,
    IOTYPE_USER_IPCAM_CAR_RUNMODE_GETTING_REQ   =0x2062,
    IOTYPE_USER_IPCAM_CAR_RUNMODE_GETTING_RESP  =0x2063,

    IOTYPE_USER_IPCAM_433_START_PAIR_REQ        =0x2064,
    IOTYPE_USER_IPCAM_433_START_PAIR_RESP       =0x2065,
    IOTYPE_USER_IPCAM_433_STOP_PAIR_REQ         =0x2066,
    IOTYPE_USER_IPCAM_433_STOP_PAIR_RESP        =0x2067,
    IOTYPE_USER_IPCAM_433_GETDIVICES_LIST_REQ   =0x2068,
    IOTYPE_USER_IPCAM_433_GETDIVICES_LIST_RESP  =0x2069,
    IOTYPE_USER_IPCAM_433_DELETED_DEVICE_REQ    =0x2070,
    IOTYPE_USER_IPCAM_433_DELETED_DEVICE_RESP   =0x2071,
    IOTYPE_USER_IPCAM_DEVICE_USER_EVENT_REPORT  =0x2072,
    IOTYPE_USER_IPCAM_433_SET_ALIAS_REQ         =0x2074,
    IOTYPE_USER_IPCAM_433_SET_ALIAS_RESP        =0x2075,
    IOTYPE_USER_IPCAM_SET_SPEAKER_SWITCH_REQ    =0x2076,
    IOTYPE_USER_IPCAM_SET_SPEAKER_SWITCH_RESP   =0x2077,
    IOTYPE_USER_IPCAM_GET_SPEAKER_SWITCH_REQ    =0x2078,
    IOTYPE_USER_IPCAM_GET_SPEAKER_SWITCH_RESP   =0x2079,
    IOTYPE_USER_IPCAM_SET_ARM_TIME_REQ          =0x207A,
    IOTYPE_USER_IPCAM_SET_ARM_TIME_RESP         =0x207B,
    IOTYPE_USER_IPCAM_GET_ARM_TIME_REQ          =0x207C,
    IOTYPE_USER_IPCAM_GET_ARM_TIME_RESP         =0x207D,
    IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_REQ     =0x207E,
    IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_RESP    =0x207F,

    IOTYPE_USER_IPCAM_VIDEO_AVAILABLE_REQ        =0x2080,
    IOTYPE_USER_IPCAM_VIDEO_AVAILABLE_RESP       =0x2081,
    IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_REQ     =0x2082,
    IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_RESP    =0x2083,
    IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_REQ     =0x2084,
    IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_RESP    =0x2085,
    IOTYPE_USER_IPCAM_PETS_GET_SOUND_LIST_REQ    =0x2086,
    IOTYPE_USER_IPCAM_PETS_GET_SOUND_LIST_RESP   =0x2087,
    IOTYPE_USER_IPCAM_PETS_SET_SOUND_ALIASE_REQ  =0x2088,
    IOTYPE_USER_IPCAM_PETS_SET_SOUND_ALIASE_RESP =0x2089,
    IOTYPE_USER_IPCAM_PETS_AUDIO_FILE_SEND_REQ   =0x208A,
    IOTYPE_USER_IPCAM_PETS_AUDIO_FILE_SEND_RESP  =0x208B,
    IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_REQ  =0x208C,
    IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_RESP  =0x208D,

    IOTYPE_USER_IPCAM_SAFEBOX_POWER_SETTING_REQ   =0x209A,
    IOTYPE_USER_IPCAM_SAFEBOX_POWER_SETTING_RESP  =0x209B,
    IOTYPE_USER_IPCAM_SAFEBOX_POWER_GETTING_REQ   =0x209C,
    IOTYPE_USER_IPCAM_SAFEBOX_POWER_GETTING_RESP  =0x209D,

    /// for recording settings
    IOTYPE_USER_IPCAM_RECORD_SETTING_REQ          =0x209E,
    IOTYPE_USER_IPCAM_RECORD_SETTING_RESP         =0x209F,
    IOTYPE_USER_IPCAM_RECORD_GETTING_REQ          =0x20A0,
    IOTYPE_USER_IPCAM_RECORD_GETTING_RESP         =0x20A1,

    /// for audio settings
    IOTYPE_USER_IPCAM_AUDIO_PLAY_VOLUME_SETTING_REQ   =0x20A2,
    IOTYPE_USER_IPCAM_AUDIO_PLAY_VOLUME_SETTING_RESP  =0x20A3,
    IOTYPE_USER_IPCAM_AUDIO_CAP_VOLUME_SETTING_REQ    =0x20A4,
    IOTYPE_USER_IPCAM_AUDIO_CAP_VOLUME_SETTING_RESP   =0x20A5,

    /// for pets attation info
    IOTYPE_USER_IPCAM_PETSDEVICE_INFO_GETTING_REQ     =0x20A6,
    IOTYPE_USER_IPCAM_PETSDEVICE_INFO_GETTING_RESP    =0x20A7,
    IOTYPE_USER_IPCAM_MANUL_RECORD_SETTING_REQ        =0x20A8,
    IOTYPE_USER_IPCAM_MANUL_RECORD_SETTING_RESP       =0x20A9,
    IOTYPE_USER_IPCAM_MANUL_RECORD_GETTING_REQ        =0x20AA,
    IOTYPE_USER_IPCAM_MANUL_RECORD_GETTING_RESP       =0x20AB,
    IOTYPE_USER_IPCAM_GET_BOX_EVENT_REQ           =0x20AC,
    IOTYPE_USER_IPCAM_GET_BOX_EVENT_RESP          =0x20AD,
    IOTYPE_USER_IPCAM_GET_BOX_USERCODE_REQ        =0x20AE,
    IOTYPE_USER_IPCAM_GET_BOX_USERCODE_RESP       =0x20AF,
    IOTYPE_USER_IPCAM_LONGTIME_RECORD_SETTING_REQ =0x20B0, // 设置关键帧录像功能
    IOTYPE_USER_IPCAM_LONGTIME_RECORD_SETTING_RESP=0x20B1,
    IOTYPE_USER_IPCAM_EDIT_EVENTS_REQ		      =0x20B2, // 保险柜事件编辑
    IOTYPE_USER_IPCAM_EDIT_EVENTS_RESP   		  =0x20B3,
    IOTYPE_USER_IPCAM_GETTING_DYMIC_REQ		      =0x20B4, // 获取动态变化参数
    IOTYPE_USER_IPCAM_GETTING_DYMIC_RESP   		  =0x20B5,
    IOTYPE_USER_IPCAM_SETTING_ALARM_AUDIO_REQ	  =0x20B6, // 设置报警声音
    IOTYPE_USER_IPCAM_SETTING_ALARM_AUDIO_RESP    =0x20B7,
    IOTYPE_USER_IPCAM_433_EDITDIVICES_LIST_REQ    =0x20B8,
    IOTYPE_USER_IPCAM_433_EDITDIVICES_LIST_RESP   =0x20B9,
    IOTYPE_USER_IPCAM_SETTING_PLAYMUSIC_REQ 	  =0x20BA, // 设置音乐播放控制
    IOTYPE_USER_IPCAM_SETTING_PLAYMUSIC_RESP      =0x20BB,
    IOTYPE_USER_IPCAM_GETTING_PRESET_NAMELIST_REQ 	  =0x20BC, //
    IOTYPE_USER_IPCAM_GETTING_PRESET_NAMELIST_RESP    =0x20BD,
    IOTYPE_USER_IPCAM_GET_TEMPTURE_EVENT_REQ          =0x20BE,
    IOTYPE_USER_IPCAM_GET_TEMPTURE_EVENT_RESP         =0x20BF,
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_REQ    =0x20C0,
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_RESP   =0x20C1,
    IOTYPE_USER_IPCAM_EDIT_INSTORE_EVENT_REQ          =0x20C2,
    IOTYPE_USER_IPCAM_EDIT_INSTORE_EVENT_RESP         =0x20C3,
    IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_REQ	  = 0x20C4,
    IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_RESP 	  = 0x20C5,
    IOTYPE_USER_IPCAM_CAMERA_LENS_SETTING_REQ	      = 0x20C6,
    IOTYPE_USER_IPCAM_CAMERA_LENS_SETTING_RESP 	      = 0x20C7,
    IOTYPE_USER_IPCAM_VIDEO_ENABLE_SETTING_REQ	      = 0x20C8,
    IOTYPE_USER_IPCAM_VIDEO_ENABLE_SETTING_RESP	      = 0x20C9,
    IOTYPE_USER_IPCAM_LOGIN_USER_SETTING_REQ	      = 0x20CA,
    IOTYPE_USER_IPCAM_LOGIN_USER_SETTING_RESP	      = 0x20CB,
    IOTYPE_USER_IPCAM_CHANGED_DOWNLOAD_REQ            = 0x20CD,
    IOTYPE_USER_IPCAM_CHANGED_DOWNLOAD_RESP 	      = 0x20CE,
    IOTYPE_USER_IPCAM_CHANGED_FTP_SETTING_REQ         = 0x20CF,
    IOTYPE_USER_IPCAM_CHANGED_FETP_SETTING_RESP 	  = 0x20D0,
    IOTYPE_USER_IPCAM_CHANGED_RTMP_SETTING_REQ        = 0x20D1,
    IOTYPE_USER_IPCAM_CHANGED_RTMP_SETTING_RESP 	  = 0x20D2,
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_REQ2    =0x20D3,
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_RESP2   =0x20D4,
    IOTYPE_USER_IPCAM_PETS_GET_PLAY_DOG_SOUND_LIST_REQ       =0x20D5,
    IOTYPE_USER_IPCAM_PETS_GET_PLAY_DOG_SOUND_LIST_RESP      =0x20D6,
    IOTYPE_USER_IPCAM_PETS_SET_PLAY_DOG_SOUND_LIST_REQ       =0x20D7,
    IOTYPE_USER_IPCAM_PETS_SET_PLAY_DOG_SOUND_LIST_RESP      =0x20D8,

    IOTYPE_USER_IPCAM_GET_CUR_WIFI_SIGNAL_REQ       =0x20E9,
    IOTYPE_USER_IPCAM_GET_CUR_WIFI_SIGNAL_RESP      =0x20EA,
    
    IOTYPE_MKOWL_IS_FEED_AFTER_MOVE_REQ          =0x20ED,
    IOTYPE_MKOWL_IS_FEED_AFTER_MOVE_RESP         =0x20EE,
    IOTYPE_MKOWL_SET_FREE_WALKING_PARAM_REQ      =0x20EF,
    IOTYPE_MKOWL_SET_FREE_WALKING_PARAM_RESP     =0x20F0,
    IOTYPE_MKOWL_SET_DRIVING_MODE_PARAM_REQ      =0x20F1,
    IOTYPE_MKOWL_SET_DRIVING_MODE_PARAM_RESP     =0x20F2,
    IOTYPE_MKOWL_CTRL_BONE_MOTION_PARAM_REQ      =0x20F3,
    IOTYPE_MKOWL_CTRL_BONE_MOTION_PARAM_RESP     =0x20F4,
    IOTYPE_MKOWL_SET_MOVE_SPEED_REQ              =0x20F5,
    IOTYPE_MKOWL_SET_MOVE_SPEED_RESP             =0x20F6,
    IOTYPE_MKOWL_SET_FEED_COPYS_REQ              =0x20F7,
    IOTYPE_MKOWL_SET_FEED_COPYS_RESP             =0x20F8,
    IOTYPE_MKOWL_SET_ONETIME_WAYPOINTS_REQ       =0x20F9,
    IOTYPE_MKOWL_SET_ONETIME_WAYPOINTS_RESP      =0x20FA,
    IOTYPE_MKOWL_SET_CRUISE_WAY_REQ              =0x20FB,
    IOTYPE_MKOWL_SET_CRUISE_WAY_RESP             =0x20FC,
    
    IOTYPE_MKOWL_CTRL_SPORT_MODE_REQ             =0x20FF,
    IOTYPE_MKOWL_CTRL_SPORT_MODE_RESP            =0x2100,
    IOTYPE_MKOWL_PLAY_AFTER_CONFIG_NET_REQ       =0x2101,
    IOTYPE_MKOWL_PLAY_AFTER_CONFIG_NET_RESP      =0x2102,
    
    IOTYPE_MKOWL_OBSTACLE_AVOIDANCE_REQ                        =0x2103,
    IOTYPE_MKOWL_OBSTACLE_AVOIDANCE_RESP                        =0x2104,
    IOTYPE_MKOWL_HAS_CRUISE_PATH_REQ                            =0x2105,
    IOTYPE_MKOWL_HAS_CRUISE_PATH_RESP                        =0x2106,
    IOTYPE_MKOWL_START_ONCE_CRUISE_REQ                        =0x2107,
    IOTYPE_MKOWL_START_ONCE_CRUISE_RESP                        =0x2108,
    IOTYPE_MKOWL_GET_CURRENT_SPORT_STATUS_REQ                    =0x2109,
    IOTYPE_MKOWL_GET_CURRENT_SPORT_STATUS_RESP                =0x210A,
    IOTYPE_MKOWL_POWER_OFF_PIR_REQ                            =0x210B,
    IOTYPE_MKOWL_POWER_OFF_PIR_RESP                            =0x210C,

    IOTYPE_USER_IPCAM_DEVICE_GET_PETS_FEEDNUM_REQ    =0x5009,
    IOTYPE_USER_IPCAM_DEVICE_GET_PETS_FEEDNUM_RESP   =0x500A,
    
    //	查询所有ZIGBEE设备
    BOYUN_ZIGBEE_LIST_DEVICES_REQ                    = 0x6001,
    BOYUN_ZIGBEE_LIST_DEVICES_RESP                   = 0x6002,
    //	湿度
    BOYUN_ZIGBEE_SENSOR_GET_HUMIDITY_REQ             = 0x6003,
    BOYUN_ZIGBEE_SENSOR_GET_HUMIDITY_RESP            = 0x6004,
    //	亮度
    BOYUN_ZIGBEE_SENSOR_GET_BRIGHTNESS_REQ           = 0x6005,
    BOYUN_ZIGBEE_SENSOR_GET_BRIGHTNESS_RESP          = 0x6006,
    //	空气质量
    BOYUN_ZIGBEE_SENSOR_GET_AIR_QUALITY_REQ          = 0x6007,
    BOYUN_ZIGBEE_SENSOR_GET_AIR_QUALITY_RESP         = 0x6008,
    //	温度
    BOYUN_ZIGBEE_SENSOR_GET_TEMPERATURE_REQ          = 0x6009,
    BOYUN_ZIGBEE_SENSOR_GET_TEMPERATURE_RESP         = 0x600A,
    //  可燃气体浓度 150---8000
    BOYUN_ZIGBEE_SENSOR_GET_KAD_VALUE_REQ            = 0x600B,
    BOYUN_ZIGBEE_SENSOR_GET_KAD_VALUE_RESP           = 0x600C,
    //  甲醛 HCHO 0---256
    BOYUN_ZIGBEE_SENSOR_GET_HCHO_REQ                 = 0x600D,
    BOYUN_ZIGBEE_SENSOR_GET_HCHO_RESP                = 0x600E,
    //  粉尘浓度 TSP 0--550
    BOYUN_ZIGBEE_SENSOR_GET_TSP_REQ                  = 0x600F,
    BOYUN_ZIGBEE_SENSOR_GET_TSP_RESP                 = 0x6010,
    //  家用燃气 1：正常，2：故障，3：报警
    BOYUN_ZIGBEE_SENSOR_GET_KAD_STATE_REQ            = 0x6011,
    BOYUN_ZIGBEE_SENSOR_GET_KAD_STATE_RESP           = 0x6012,
    //  遥控器 1：SOS，2：视频，3：设防，4：撤防
    BOYUN_ZIGBEE_SENSOR_GET_CONTROL_STATE_REQ        = 0x6013,
    BOYUN_ZIGBEE_SENSOR_GET_CONTROL_STATE_RESP       = 0x6014,
  //  设置控制器状态 1：发送SOS，2：视频，3：布放，4：撤防
    BOYUN_ZIGBEE_SENSOR_SET_CONTROL_STATE_REQ      = 0x6015,
    BOYUN_ZIGBEE_SENSOR_SET_CONTROL_STATE_RESP     = 0x6016,
    //使Zigbee摄像机进入组网模式
    BOYUN_ZIGBEE_PERMIT_JOIN_REQ                = 0x6017,
    BOYUN_ZIGBEE_PERMIT_JOIN_RESP              = 0x6018,
    //查询刚刚申请入网的设备
    BOYUN_ZIGBEE_LIST_LATEST_JOIN_REQ         = 0x6019,
    BOYUN_ZIGBEE_LIST_LATEST_JOIN_RESP        = 0x601A,
    //删除已经入网的zigbee设备
    BOYUN_ZIGBEE_SENSOR_DELETE_DEVICE_REQ      = 0x601B,
    BOYUN_ZIGBEE_SENSOR_DELETE_DEVICE_RESP     = 0x601C,

    ZONTEK_ZIGBEE_TAKE_CARE_TIME_REQ			= 0x601D,
    ZONTEK_ZIGBEE_TAKE_CARE_TIME_RESP			= 0x601E,
    ZONTEK_ZIGBEE_IR_FEED_SETTING_REQ			= 0x601F,
    ZONTEK_ZIGBEE_IR_FEED_SETTING_RESP			= 0x6020,
    ZONTEK_ZIGBEE_WARNNING_PUSH_REQ			    = 0x6021,
    ZONTEK_ZIGBEE_WARNNING_PUSH_RESP			= 0x6022,
    ZONTEK_ZIGBEE_SMART_VOICE_SWITCH_REQ		= 0x6023,
    ZONTEK_ZIGBEE_SMART_VOICE_SWITCH_RESP		= 0x6024,
    ZONTEK_ZIGBEE_STATUS_LIGHT_SWITCH_REQ		= 0x6025,
    ZONTEK_ZIGBEE_STATUS_LIGHT_SWITCH_RESP		= 0x6026,
    ZONTEK_ZIGBEE_VOICE_TIP_SETTING_REQ		    = 0x6027,
    ZONTEK_ZIGBEE_VOICE_TIP_SETTING_RESP		= 0x6028,

    //获取设备地理位置
    IOTYPE_USER_IPCAM_GET_DEVICE_ADDR_LOCALTION_REQ     = 0x6029,
    IOTYPE_USER_IPCAM_GET_DEVICE_ADDR_LOCALTION_RESP    = 0x602A,
    //定时录像设置，以当天时间的秒数为单位
    IOTYPE_USER_IPCAM_SET_SCHEDULE_REOCRD_SEC_REQ     	= 0x602B,
    IOTYPE_USER_IPCAM_SET_SCHEDULE_REOCRD_SEC_RESP     	= 0x602C,

    IOTYPE_USER_IPCAM_SET_IRLED_REQ		        		= 0x602D,
    IOTYPE_USER_IPCAM_SET_IRLED_RESP		        	= 0x602E,

    IOTYPE_USER_GET_HI_BATTERY_CAPACITY_REQ		    	= 0x602F,
    IOTYPE_USER_GET_HI_BATTERY_CAPACITY_RESP		    	= 0x6030,

    IOTYPE_USER_GET_AXP_BATTERY_CAPACITY_REQ		    	= 0x6031,
    IOTYPE_USER_GET_AXP_BATTERY_CAPACITY_RESP		    	= 0x6032,

    IOTYPE_USER_SWITCH_PIR_REQ					= 0x6033,
    IOTYPE_USER_SWITCH_PIR_RESP					= 0x6034,

    GANSU_CHECK_SENSOR_STATUS_REQ				= 0x6035,
    GANSU_CHECK_SENSOR_STATUS_RESP				= 0x6036,
    GANSU_GET_NETWORK_STATUS_REQ					= 0x6037,
    GANSU_GET_NETWORK_STATUS_RESP				= 0x6038,

    GEPAI_GET_DOOR_STATUS_REQ					= 0x6039,
    GEPAI_GET_DOOR_STATUS_RESP					= 0x603A,
    GEPAI_GET_DOOR_POWER_REQ						= 0x603B,
    GEPAI_GET_DOOR_POWER_RESP					= 0x603C,
    GEPAI_GET_NET_STATUS_REQ						= 0x603D,
    GEPAI_GET_NET_STATUS_RESP					= 0x603E,
    GEPAI_GET_BATTERY_CAP_REQ					= 0x603F,
    GEPAI_GET_BATTERY_CAP_RESP					= 0x6040,
    GEPAI_GET_HUMIDITY_REQ						= 0x6041,
    GEPAI_GET_HUMIDITY_RESP						= 0x6042,
    GEPAI_SET_DYNAMIC_ENCRYPT_REQ				= 0x6043,
    GEPAI_SET_DYNAMIC_ENCRYPT_RESP				= 0x6044,
    GEPAI_SET_DOOR_POWER_REQ						= 0x6045,
    GEPAI_SET_DOOR_POWER_RESP					= 0x6046,
    GEPAI_SET_DISTURB_TIME_REQ					= 0x6047,
    GEPAI_SET_DISTURB_TIME_RESP					= 0x6048,

    PI_SOFT_VR_ENCRYPT_REQ                       = 0x6049,
    PI_SOFT_VR_ENCRYPT_RESP                   	= 0x6050,

    
    IOTYPE_RECORD_SETTING_REQ                    = 0x6062,
    IOTYPE_RECORD_SETTING_RESP                    = 0x6063,


    //AP模式配网 APP查询失败记录
    IOTYPE_USER_IPCAM_AP_GETWIFI_ERROR_REQ      = 0x0348,
    //AP模式配网 APP查询失败记录返回
    IOTYPE_USER_IPCAM_AP_GETWIFI_ERROR_RESP     = 0x0349,
    
    
    //设备同步手机时间
    IOTYPE_USER_IPCAM_SET_TIME_SYNC_REQ    = 0x0816,
    IOTYPE_USER_IPCAM_SET_TIME_SYNC_RESP   = 0x0817,
    
    //童锁设置与获取
    IOTYPE_USER_SET_CHILDREN_LOCK_REQ            = 0x5037,
    IOTYPE_USER_SET_CHILDREN_LOCK_RESP            = 0x5038,
    IOTYPE_USER_GET_CHILDREN_LOCK_REQ            = 0x5039,
    IOTYPE_USER_GET_CHILDREN_LOCK_RESP            = 0x503A,
    
    ///信号强度
    IOTYPE_USER_IPCAM_GET_WIFI_SIGNAL_REQ      = 0x5029,
    IOTYPE_USER_IPCAM_GET_WIFI_SIGNAL_RESP     = 0x5030,
    

}ENUM_AVIOCTRL_UD_MSGTYPE;


/////////////////////////////////////////////////////////////////////////////////
/////////////////// Type ENUM Define ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////


/*
 ///信号强度
 IOTYPE_USER_IPCAM_GET_WIFI_SIGNAL_REQ      = 0x5029,
 IOTYPE_USER_IPCAM_GET_WIFI_SIGNAL_RESP     = 0x5030,
 */
///信号强度
typedef struct
{
    char reserved[4];
}SmsgAVIoctrlGetWiFiSignalReq;

typedef struct
{
    int signal;//设备连接的wifi信号0-100%
}SmsgAVIoctrlGetWiFiSignalResp;

/*
 IOTYPE_USER_SET_CHILDREN_LOCK_REQ            = 0x5037,
 IOTYPE_USER_SET_CHILDREN_LOCK_RESP            = 0x5038,
 */
typedef struct
{
    char lockEnable;                 // 0：关闭；1：开启；
    char reserved[4];
}SMsgAVIoctrlSetLockReq, SMsgAVIoctrlGetLockReq;

/*
 IOTYPE_USER_GET_CHILDREN_LOCK_REQ            = 0x5039,
 IOTYPE_USER_GET_CHILDREN_LOCK_RESP            = 0x503A,
 */
typedef struct
{
    int result;         // 0: success; otherwise: failed.
    char lockEnable;                 // 0：关闭；1：开启；
    char reserved[4];
}SMsgAVIoctrlSetLockResp, SMsgAVIoctrlGetLockResp;


typedef struct
{
    unsigned char reserved[4];            //（保留）
}SMsgAVIoctrlAPGetWiFiErrorReq;

typedef struct
{
    int result;                       //结果（0:无失败记录 1:有失败记录）
    char mac[20];
    char ssid[32];                    // 下发的WiFi ssid
    unsigned int error;               //错误类型
}SMsgAVIoctrlAPGetWiFiErrorResq;

//Camera params Type
typedef enum
{
    AVIOTC_CAMERA_BRIGHT    	= 0x00,		//bright
    AVIOTC_CAMERA_CONTRAST    	= 0x01,		//contrast
    AVIOTC_CAMERA_SATURATION	= 0x02,		//saturation
    AVIOTC_CAMERA_CHROMA    	= 0x03,		//chroma,
    AVIOTC_CAMERA_MESSAGE_PUSH_ENABLE 	= 0x10		//enable push
}ENUM_CAMERA_PARAMS;

//External devices params Type
typedef enum
{
    AVIOTC_EXTERNAL_DEVICES_ALL                 = 0x00,		//All external devices
    AVIOTC_EXTERNAL_DEVICES_TEMPERATURE         = 0x01,		//Temperature
    AVIOTC_EXTERNAL_DEVICES_RELATIVE_HUMIDITY   = 0x02,		//Relative humidity
    AVIOTC_EXTERNAL_DEVICES_FORMALDEHYDE        = 0x03,		//Formaldehyde
    AVIOTC_EXTERNAL_DEVICES_PARTICULATE_MATTER25= 0x04		//Particulate matter 2.5
}ENUM_EXTERNAL_DEVICES_PARAMS;

/////////////////////////////////////////////////////////////////////////////
///////////////////////// Message Body Define ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/*
    IOTYPE_USER_IPCAM_GETDEVINFO_RESP			= 0x2001,
    ** @struct SMsgAVIoctrlDevInfoResp
*/
typedef struct
{
    char devid[24];		//ID
    char sysversion[16];	//
    char devname[16];		//
    char alarmstatus;				//ENUM_ALARM_STATUS
    char sdstatus;					//SDENUM_SD_STATUS
    char model[16];		//
    char vendor[16];		//
    unsigned int version;			//
    unsigned int channel;			//
    unsigned int total;				// MBytes, total space size for sdcard
    unsigned int free;				// MBytes , free space size for sdcard
    char reserved[8];
}SMsgAVIoctrlDevInfoResp;

/*
    IOTYPE_USER_IPCAM_SET_DEVNAME_REQ			= 0x2002,
    IOTYPE_USER_IPCAM_GET_DEVNAME_RESP			= 0x2005,
    ** @struct SMsgAVIoctrlSetDevnameReq, SMsgAVIoctrlGetDevnameResp
*/
typedef struct
{
    char devname[16];		//
    char reserved[4];
}SMsgAVIoctrlSetDevnameReq, SMsgAVIoctrlGetDevnameResp;

/*
    IOTYPE_USER_IPCAM_SET_DEVNAME_RESP			= 0x2003,
    ** @struct SMsgAVIoctrlSetDevnameResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetDevnameResp;

/*
    IOTYPE_USER_IPCAM_SET_DATETIME_REQ			= 0x2006,
    IOTYPE_USER_IPCAM_GET_DATETIME_RESP			= 0x2009,
    ** @struct SMsgAVIoctrlSetDatetimeReq, SMsgAVIoctrlGetDatetimeResp
*/
typedef struct
{
    int timezone;    			//
    char synctype;				//0PC 1NTP
    unsigned int synctime;				//PC
    char syncNtpDns[64];	//NTP
    char reserved[4];
}SMsgAVIoctrlSetDatetimeReq, SMsgAVIoctrlGetDatetimeResp;

/*
    IOTYPE_USER_IPCAM_SET_DATETIME_RESP			= 0x2007,
    ** @struct SMsgAVIoctrlSetDatetimeResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetDatetimeResp;


/*
    IOTYPE_USER_IPCAM_DEVRESET_RESP				= 0x200B,
    ** @struct SMsgAVIoctrlSetDevResetResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetDevResetResp;

/*
    IOTYPE_USER_IPCAM_DEVREBOOT_RESP			= 0x200D,
    ** @struct SMsgAVIoctrlSetDevRebootResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetDevRebootResp;

/*
    IOTYPE_USER_IPCAM_SET_IPV4NET_REQ			= 0x200E,
    IOTYPE_USER_IPCAM_GET_IPV4NET_RESP			= 0x2011,
    ** @struct SMsgAVIoctrlSetIpv4netReq, SMsgAVIoctrlGetIpv4netResp
*/
typedef struct
{
    char dhcpip;    //IP
                    //0 1
    char ip[16];
    char mask[16];
    char gateway[16];
    char dhcpdns;   	//DNS
                        //0 1
    char dns1[16];
    char dns2[16];
}SMsgAVIoctrlSetIpv4netReq, SMsgAVIoctrlGetIpv4netResp;

/*
    IOTYPE_USER_IPCAM_SET_IPV4NET_RESP			= 0x200F,
    ** @struct SMsgAVIoctrlSetIpv4netResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetIpv4netResp;

/*
    IOTYPE_USER_IPCAM_SET_FTP_REQ				= 0x2012,
    IOTYPE_USER_IPCAM_GET_FTP_RESP				= 0x2015,
    ** @struct SMsgAVIoctrlSetFtpReq, SMsgAVIoctrlGetFtpResp
*/
typedef struct
{
    char ftpserver[64];	//FTPIP
    unsigned int ftpport;			//FTP
    char ftpuser[64];		//FTP
    char ftppwd[64];		//FTP
    char mode;    					//FTP
                                    //0PORT 1PASV
    char ftpdir[64];		//FTP
    char ftpuploadinterval;	//FTP
}SMsgAVIoctrlSetFtpReq, SMsgAVIoctrlGetFtpResp;


/*
    IOTYPE_USER_IPCAM_SET_FTP_RESP				= 0x2013,
    ** @struct SMsgAVIoctrlSetFtpResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetFtpResp;

/*
    IOTYPE_USER_IPCAM_SET_EMAIL_REQ				= 0x2016,
    IOTYPE_USER_IPCAM_GET_EMAIL_RESP			= 0x2019,
    ** @struct SMsgAVIoctrlSetEmailReq, SMsgAVIoctrlGetEmailResp
*/
typedef struct
{
    char sender[64];		//EMAIL
    char receiver1[64];	//EMAIL1
    char receiver2[64];	//EMAIL2
    char receiver3[64];	//EMAIL3
    char receiver4[64];	//EMAIL4
    char smtpserver[64];	//SMTP
    unsigned int smtpport;			//SMTP
    char securityprotocol;			//
                                    //0 1TLS 2STARTTLS
    char checkout;					//
                                    //0 1
    char smtpuser[64];		//SMTP
    char smtppwd[64];		//SMTP
    char addexternalip;   			//IP
                                    //0 1
}SMsgAVIoctrlSetEmailReq, SMsgAVIoctrlGetEmailResp;

/*
    IOTYPE_USER_IPCAM_SET_EMAIL_RESP			= 0x2017,
    ** @struct SMsgAVIoctrlSetEmailResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetEmailResp;

/*
    IOTYPE_USER_IPCAM_SET_PTZ_REQ				= 0x201A,
    IOTYPE_USER_IPCAM_GET_PTZ_RESP				= 0x201D,
    ** @struct SMsgAVIoctrlSetPtzReq, SMsgAVIoctrlGetPtzResp
*/
typedef struct
{
    char ptzDisppreset;				//
                                    //0 1
    unsigned int presetOnstart;		//
    unsigned int ptzPatrolRate;		//PTZ
    unsigned int ptzPatrolUpRate;		//
    unsigned int ptzPatrolRightRate;	//
    char ledMode;					//
                                    //0 1 2
}SMsgAVIoctrlSetPtzReq, SMsgAVIoctrlGetPtzResp;

/*
    IOTYPE_USER_IPCAM_SET_PTZ_RESP				= 0x201B,
    ** @struct SMsgAVIoctrlSetPtzResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetPtzResp;

/*
    IOTYPE_USER_IPCAM_SET_ALARM_REQ				= 0x201E,
    IOTYPE_USER_IPCAM_GET_ALARM_RESP			= 0x2021,
    ** @struct SMsgAVIoctrlSetAlarmReq, SMsgAVIoctrlGetAlarmResp
*/
typedef struct
{
    char alarmMotionArmed;			//
                                    //0 1
    unsigned int alarmMotionSensitivity;	 	//
    unsigned int alarmToPreset;			 		//
    char alarmInputArmed;			//
                                    //0 1
    char alarmIoinLevel;			//
                                    //0 1
    char alarmIOlinkage;			//IO
                                    //0 1
    char alarmIOoutLevel;			//IO
                                    //0 1
    char alarmMail;					//
                                    //0 1
    char alarmUploadInterval;		//FTP
                                    //0 1
    char scheduleEnable;			//
                                    //0 1
    int scheduleSun0;				//00:0008:00
    int scheduleSun1;				//08:0016:00
    int scheduleSun2;				//16:0024:00
    int scheduleMon0;				//00:0008:00
    int scheduleMon1;				//08:0016:00
    int scheduleMon2;				//16:0024:00
    int scheduleTue0;				//00:0008:00
    int scheduleTue1;				//08:0016:00
    int scheduleTue2;				//16:0024:00
    int scheduleWeb0;				//00:0008:00
    int scheduleWeb1;				//08:0016:00
    int scheduleWeb2;				//16:0024:00
    int scheduleThu0;				//00:0008:00
    int scheduleThu1;				//08:0016:00
    int scheduleThu2;				//16:0024:00
    int scheduleFri0;				//00:0008:00
    int scheduleFri1;				//08:0016:00
    int scheduleFri2;				//16:0024:00
    int scheduleSat0;				//00:0008:00
    int scheduleSat1;				//08:0016:00
    int scheduleSat2;				//16:0024:00
}SMsgAVIoctrlSetAlarmReq, SMsgAVIoctrlGetAlarmResp;

/*
    IOTYPE_USER_IPCAM_SET_ALARM_RESP			= 0x201F,
    ** @struct SMsgAVIoctrlSetAlarmResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetAlarmResp;

/*
    IOTYPE_USER_IPCAM_SET_VRPROGRAM_REQ			= 0x2022,
    IOTYPE_USER_IPCAM_GET_VRPROGRAM_RESP		= 0x2025,
    ** @struct SMsgAVIoctrlSetVRProgramReq, SMsgAVIoctrlGetVRProgramResp
*/
typedef struct
{
    char recordSdStatus;				//SD
                                        //0
                                        //1SD
    char recordCoverEnable;				//SD
                                        //0 1
    char recordGpioEnable;				//GPIO
                                        //0 1
    char recordMotionEnable;			//
                                        //0 1
}SMsgAVIoctrlSetVRProgramReq, SMsgAVIoctrlGetVRProgramResp;

/*
    IOTYPE_USER_IPCAM_SET_VRPROGRAM_RESP		= 0x2023,
    ** @struct SMsgAVIoctrlSetVRProgramResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetVRProgramResp;

/*
    IOTYPE_USER_IPCAM_SET_VIDEO_REQ				= 0x2026,
    IOTYPE_USER_IPCAM_GET_VIDEO_RESP			= 0x2029,
    ** @struct SMsgAVIoctrlSetVideoInfoReq, SMsgAVIoctrlGetVideoInfoResp
*/
typedef struct
{
    char encMediaSize; 			//
                                //01280*720 1:640*480 2320*240
    char encRatemode; 			//
                                //0CBR 1VBR
    int encKeyframe; 			//
    int encBitrate; 			//
    int encQuant; 				//
    int framerate; 					//
    char osdEnable; 				// OSD
                                    //0 1
    char reserved[4];
}SMsgAVIoctrlSetVideoInfoReq, SMsgAVIoctrlGetVideoInfoResp;

/*
    IOTYPE_USER_IPCAM_SET_VIDEO_RESP			= 0x2027,
    ** @struct SMsgAVIoctrlSetVideoInfoResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetVideoInfoResp;

/*
    IOTYPE_USER_IPCAM_SET_VIDEOFRAME_REQ		= 0x202A,
    IOTYPE_USER_IPCAM_GET_VIDEOFRAME_RESP		= 0x202D,
    ** @struct SMsgAVIoctrlSetVideoFrameReq, SMsgAVIoctrlGetVideoFrameResp
*/
typedef struct
{
    int framerate; 					//
    char reserved[4];
}SMsgAVIoctrlSetVideoFrameReq, SMsgAVIoctrlGetVideoFrameResp;

/*
    IOTYPE_USER_IPCAM_SET_VIDEOFRAME_RESP		= 0x202B,
    ** @struct SMsgAVIoctrlSetVideoFrameResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetVideoFrameResp;

/*
    IOTYPE_USER_IPCAM_SET_VIDEOOSD_REQ			= 0x202E,
    IOTYPE_USER_IPCAM_GET_VIDEOOSD_RESP			= 0x2031,
    ** @struct SMsgAVIoctrlSetVideoOSDReq, SMsgAVIoctrlGetVideoOSDResp
*/
typedef struct
{
    char osdEnable; 				// OSD
                                    //0 1
    char reserved[4];
}SMsgAVIoctrlSetVideoOSDReq, SMsgAVIoctrlGetVideoOSDResp;

typedef struct
{
    char reserved[4];
}SMsgAVIoctrlGetVideoOSDReq;


/*
    IOTYPE_USER_IPCAM_SET_VIDEOOSD_RESP			= 0x202F,
    ** @struct SMsgAVIoctrlSetVideoOSDResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetVideoOSDResp;

/*
    IOTYPE_USER_IPCAM_SET_AUDIO_REQ				= 0x2032,
    IOTYPE_USER_IPCAM_GET_AUDIO_RESP			= 0x2035,
    ** @struct SMsgAVIoctrlSetAudioInfoReq, SMsgAVIoctrlGetAudioInfoResp
*/
typedef struct
{
    char audioEnable; 				//
                                    //0 1
    int audioInput; 				//
    int audioCompressedFormat; 		//
    int audioSamplingRate; 			//
    char reserved[4];
}SMsgAVIoctrlSetAudioInfoReq, SMsgAVIoctrlGetAudioInfoResp;

/*
    IOTYPE_USER_IPCAM_SET_AUDIO_RESP			= 0x2033,
    ** @struct SMsgAVIoctrlSetAudioInfoResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetAudioInfoResp;

/*
    IOTYPE_USER_IPCAM_SET_PTZSPEED_REQ			= 0x2036,
    IOTYPE_USER_IPCAM_GET_PTZSPEED_RESP			= 0x2039,
    ** @struct SMsgAVIoctrlSetPtzSpeedReq, SMsgAVIoctrlGetPtzSpeedResp
*/
typedef struct
{
    int speed; 					//
    char reserved[4];
}SMsgAVIoctrlSetPtzSpeedReq, SMsgAVIoctrlGetPtzSpeedResp;

/*
    IOTYPE_USER_IPCAM_SET_PTZSPEED_RESP			= 0x2037,
    ** @struct SMsgAVIoctrlSetPtzSpeedResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetPtzSpeedResp;

/*
    IOTYPE_USER_IPCAM_SET_PTZPRESET_REQ			= 0x203A,
    IOTYPE_USER_IPCAM_GET_PTZPRESET_RESP		= 0x203D,
    ** @struct SMsgAVIoctrlSetPtzPresetReq, SMsgAVIoctrlGetPtzPresetResp
*/
typedef struct
{
    int preset; 					//
    char settype; 					//
                                    //0
                                    //1
    char reserved[3];
}SMsgAVIoctrlSetPtzPresetReq, SMsgAVIoctrlGetPtzPresetResp;

/*
    IOTYPE_USER_IPCAM_SET_PTZPRESET_RESP		= 0x203B,
    ** @struct SMsgAVIoctrlSetPtzPresetResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetPtzPresetResp;


/*
    IOTYPE_USER_IPCAM_SET_CAMERA_REQ			= 0x203E,
    IOTYPE_USER_IPCAM_GET_CAMERA_RESP			= 0x2041,
    ** @struct SMsgAVIoctrlSetCameraParamsReq, SMsgAVIoctrlGetCameraParamsResp
*/
typedef struct
{
    char params; 					//	ENUM_CAMERA_PARAMS					                                 //ENUM_CAMERA_PARAMS
    int value; 						//
    char reserved[4];
}SMsgAVIoctrlSetCameraParamsReq, SMsgAVIoctrlGetCameraParamsResp;

/*
    IOTYPE_USER_IPCAM_SET_CAMERA_RESP		= 0x203F,
    ** @struct SMsgAVIoctrlSetCameraParamsResp
*/
typedef struct
{
    int result; 		// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlSetCameraParamsResp;

/*
    IOTYPE_USER_IPCAM_GET_CAMERA_REQ			= 0x2040,
    ** @struct SMsgAVIoctrlGetCameraParamsReq
*/
typedef struct
{
    char params; 					//
    char reserved[3];
}SMsgAVIoctrlGetCameraParamsReq;

/*
    IOTYPE_USER_IPCAM_DOWNLOAD_FILE_REQ			= 0x2042,
    ** @struct SMsgAVIoctrlDownloadFileReq
*/
typedef struct
{
    int fileNum;                    //文件的个数
    char reserved[4];
}SMsgAVIoctrlDownloadFileReq;

/*
    IOTYPE_USER_IPCAM_DOWNLOAD_FILE_RESP		= 0x2043,
    ** @struct SMsgAVIoctrlDownloadFileResp
*/
typedef struct
{
    int result; 				// 0: success; otherwise: failed.
    char reserved[4];
}SMsgAVIoctrlDownloadFileResp;

/////////////for nide compney
typedef struct
{
    unsigned int channel;                       // camera index
}SMsgAVIoctrlGetDoorStatusReq,SMsgAVIoctrlGetDoorPasswordModeReq;


//IOTYPE_USER_IPCAM_GET_DOOR_STATUS_RESP      = 0x513,
//IOTYPE_USER_IPCAM_SET_DOOR_STAUTS_REQ       = 0x514,
//IOTYPE_USER_IPCAM_SET_DOOR_STATUS_RESP      = 0x515,
typedef struct
{
    unsigned int channel;                       // camera index
    int door1 ;                                 // 大門, 0:close, 1:open
    int door2 ;                                 // 小門, 0:close, 1:open
    char passwd[32];                            // reserved, not used
}SMsgAVIoctrlGetDoorStatusResp, SMsgAVIoctrlSetDoorStatusResp, SMsgAVIoctrlSetDoorStatusReq;

typedef struct
{
    unsigned int channel;                       // camera index
    int door1 ;                                 // 大門, 0:close, 1:open
    int door2 ;                                 // 小門, 0:close, 1:open
}door_resp;

typedef struct
{
   int type ;
   door_resp aide_doors;
}aide_door_command_struct;

//IOTYPE_USER_IPCAM_GET_DOORPASSWORDMODE_REQ
//IOTYPE_USER_IPCAM_GET_DOORPASSWORDMODE_RESP =0x517,
//IOTYPE_USER_IPCAM_SET_DOORPASSWORDMODE_REQ =0x518,
//IOTYPE_USER_IPCAM_SET_DOORPASSWORDMODE_RESP =0x519,
typedef struct
{
    unsigned  int  channel; // Camera Index
    int state;//0禁用1 启用
} SMsgAVIoctrlSetDoorPasswordModeResp,SMsgAVIoctrlSetDoorPasswordModeReq;

typedef struct
{
    unsigned  int  channel; // Camera Index
    int state;//0禁用1 启用
    char passwd[32];
} SMsgAVIoctrlGetDoorPasswordModeResp;

/////////////////////////////////////////////////////////////////////////
//for wayde tech product
//IOTYPE_USER_WAYDEA_REQ = 0x600,
//IOTYPE_USER_WAYDEA_RESP = 0x601
typedef struct
{
    unsigned int channel;	//Camera Index, for avapi usage
    unsigned char start; 	// start byte : always 0xF5
    unsigned char iid ;   	// 识别码 : 0x8B
    unsigned char fnCmd; 	//功能命令
    unsigned char high;  	//遥控地址高位
    unsigned char low;   	//遥控地址低位
    unsigned char deviceID;	//设备号
    unsigned char checkSum; // start xor iid xor fnCmd xor high xor low xordeviceID
    unsigned char reserved[1];
}SMsgAVIoctrlWayDeaReq;

typedef struct
{
    unsigned int channel;	//Camera Index, for avapi usage
    unsigned char fnCmd; 	//功能命令
    unsigned char status; 	// 0:异常 ; 1:成功
    unsigned char reserved[2];
}SMsgAVIoctrlWayDeaResp;

/*
 IOTYPE_USER_IPCAM_GET_EXTERNAL_DEVICES_REQ  = 0x2044,
 IOTYPE_USER_IPCAM_GET_EXTERNAL_DEVICES_RESP = 0x2045
 ** @struct SMsgAVIoctrlGetCameraExternalDevicesParamsReq
            SMsgAVIoctrlGetCameraExternalDevicesParamsResp
 */
typedef struct
{
    char params; 					// ENUM_EXTERNAL_DEVICES_PARAMS
    char reserved[3];
}SMsgAVIoctrlGetCameraExternalDevicesParamsReq;

typedef struct
{
    char params; 					// ENUM_EXTERNAL_DEVICES_PARAMS
    char reserved[3];
    float value; 				    //
} SMsgAVIoctrlGetCameraExternalDevicesParamsResp;

/*
    IOTYPE_USER_IPCAM_SET_UPGRDEONLIN_REQ		= 0x2046,
    IOTYPE_USER_IPCAM_SET_UPGRADEONLIN_RESP		= 0x2047
    ** @struct SMsgAVIoctrlSetUpgradeOnlineReq, SMsgAVIoctrlUpgradeOnlineResp
*/
#ifndef BUILD_FOR_MIPSEL  //just for app use
typedef enum upgrade_online_type
{
    UPGRADE_ONLINE_TYPE_CHECK, //检查版本
    UPGRADE_ONLINE_TYPE_SYS,   //升级系统固件
    UPGRADE_ONLINE_TYPE_UI,    //升级ui固件
    UPGRADE_ONLINE_TYPE_SYS_UI,//NOT SUPPORT NOW,
    UPGRADE_ONLINE_TYPE_SET_SERVER_PATH,// SUPPORT  for beijing ipc NOW,
    UPGRADE_ONLINE_TYPE_GET_NOTES_PATH// SUPPORT NOW 获取历史升级记录
}enum_upgrade_type;
#endif

typedef struct
{
    int  type;  //enum enum_upgrade_type
    char reserved[4];
}SMsgAVIoctrlSetUpgradeOnlineReq;


typedef struct
{
    int  type;  //enum enum_upgrade_type
    int  result; //for type=UPGRADE_ONLINE_TYPE_CHECK, 0-noversion, 1-sys, 2-ui, 3-sys&ui
                 //for type=others, resut-0/ok, 1/error
    char current_ui_version[16];
    char current_sys_version[16];
    char latest_ui_version[16];
    char latest_sys_version[16];
    char reserved[4];
}SMsgAVIoctrlUpgradeOnlineResp;

//just for check version notes 获取历史升级记录返回
typedef struct
{
    int  type;  //enum enum_upgrade_type
    int  result; //for type=UPGRADE_ONLINE_TYPE_GET_NOTES_PATH, 0-noversion, 1-sys, 2-ui, 3-sys&ui
                 //for type=others, resut-0/ok, 1/error
    char version_realease_notes[68]; //for versio paths , example: "images/hisi/noptz_model_o95/"
                                     //realease_notes.txt
}SMsgAVIoctrlUpgradeOnlineResp2;

/*
    IOTYPE_USER_IPCAM_SET_IRCUT_REQ		    = 0x2048,
    IOTYPE_USER_IPCAM_SET_IRCUT_RESP		= 0x2049
    ** @struct SMsgAVIoctrlSetUpgradeOnlineReq, SMsgAVIoctrlUpgradeOnlineResp
*/
typedef enum day_night_mode
{
    DAY_MODE,
    NIGHT_MODE,
    AUTO,
    MANUL
}enum_day_night_mode;

typedef struct
{
    int  type;  //enum enum_day_night_mode
    char result; //0-ok, other failed
                 //for others, resut-0/ok, 1/error
    char reserved[3];// when type=MANULLY,reserved[0] for night_mode_begin, reserved[1] for night_mode_end:
                    //example reserved[0]=19, reserved[1]=7, must be(reserved[0]>reserved[1]):
}SMsgAVIoctrlSetIrcutModeReq, SMsgAVIoctrlSetIrcutModeResp;

/*
//IOTYPE_USER_IPCAM_GET_MAC_REQ		        = 0x2050,
//IOTYPE_USER_IPCAM_GET_MAC_RESP   		    = 0x2051
*/

typedef struct
{
    unsigned int channel;	//Camera Index, for avapi usage
    char  type;  //0-wifi, 1-eth0 default is wifi unless wifi is not exiset 3-wifi&eth0
    char  reserved[3];  //not used
}SMsgAVIoctrlGetMacReq;
typedef struct
{
    unsigned int channel;	//Camera Index, for avapi usage
    int  type;  //0-wifi, 1-eth0 default is wifi unless wifi is not exiset 3-wifi&eth0
    char mac_wifi[18]; //
    char mac_eth[18];  //
    char reserved[4];  //not used
}SMsgAVIoctrlGetMacResp;


/*
 *
    IOTYPE_USER_IPCAM_SET_TIME_REQ		        = 0x2052,
    IOTYPE_USER_IPCAM_SET_TIME_RESP   		    = 0x2053
 **/
typedef struct
{
    unsigned int time_second_0zone_;
    short diff_zone_minites_;//x-zone-0-zone  8shiqu==480
    short reserver_;
}SMsgAVIoctrlSetTimeReq;

typedef struct
{
    unsigned int channel;	//Camera Index, for avapi usage
    char  result;
    char  reserved[3];  //not used
}SMsgAVIoctrlSetTimeResp;

/*
 *
    IOTYPE_USER_IPCAM_SET_SYNC_TIME_REQ         = 0x816,
    IOTYPE_USER_IPCAM_SET_SYNC_TIME_RESP        = 0x817,
 **/
//typedef struct
//{
//    unsigned short year;
//    unsigned char  month;
//    unsigned char  day;
//    unsigned char  hour;
//    unsigned char  minute;
//    unsigned char  second;
//    unsigned char  nIsSupportSync;
//    int  nGMTOffset; //diff_zone_minites_
//}SMsgAVIoctrlSetTimeSyncAppReq;
//
//typedef struct
//{
//    int  result;
//    char  reserved[4];  //not used
//}SMsgAVIoctrlSetTimeSyncAppResp;

/**
 设备同步手机时间
 IOTYPE_USER_IPCAM_SET_TIME_SYNC_REQ    = 0x0816
 **@struct SMsgAVIoctrlTimeSyncReq
 */
typedef struct
{
    unsigned short year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    unsigned char nIsSupportSync; //1 supported; 0 unsupported
    unsigned int nGMTOffset; //the offset between GMT in seconds
} SMsgAVIoctrlTimeSyncReq;


/**
 IOTYPE_USER_IPCAM_SET_TIME_SYNC_RESP   = 0x0817
 @struct SMsgAVIoctrlTimeSyncResp
 */
typedef struct
{
    unsigned int result;    // return 0 if success, otherwise failed
    unsigned char reserved[4];
} SMsgAVIoctrlTimeSyncResp;



typedef enum THIRD_PART_FUNCTION
{
    THIRD_PART_SET_LED_STATUS,  //led 灯
    THIRD_PART_GET_LED_STATUS,
    THIRD_PART_SET_ALARMED_STATUS, //布撤防
    THIRD_PART_GET_ALARMED_STATUS,
    THIRD_PART_SET_WARNING_STATUS, //设置警告
    THIRD_PART_GET_WARNING_STATUS,
    THIRD_PART_SET_PUSH_ENABLE,   //设置推送使能，邦迅实时连接使能
    THIRD_PART_GET_PUSH_ENABLE,
    THIRD_PART_SET_PIR_ENABLE,   //设置PIR 使能
    THIRD_PART_GET_PIR_ENABLE,
    THIRD_PART_SET_WIFI_CHANNEL, //设置WIFI-CHANNEL
    THIRD_PART_GET_WIFI_CHANNEL,
    THIRD_PART_SET_CRYING_ALARMED, //设置哭声触发通知
    THIRD_PART_GET_CRYING_ALARMED,
    THIRD_PART_SET_DOOR_MOVED_ALARMED, //设置防拆开关
    THIRD_PART_GET_DOOR_MOVED_ALARMED
}ENUM_THIRD_PART_FUNCTION;



//IOTYPE_USER_IPCAM_THIRDPART_SETTING_REQ	    = 0x2056,
//IOTYPE_USER_IPCAM_THIRDPART_SETTING_RESP 	= 0x2057,
typedef struct
{
    unsigned int command_types_; //ENUM_THIRD_PART_FUNCTION
    int    value1_;             //setting_value [0/1]
    char   reserved[8];  //not used
}SMsgAVIoctrlThirdpartReq;

typedef struct
{
    unsigned int command_types_; //ENUM_THIRD_PART_FUNCTION
    int  result_;                //0-ok, orthers-failed
    int  value_;                 //return setting value, when result_==0
}SMsgAVIoctrlThirdpartResp;


/*
IOTYPE_USER_IPCAM_WIFI_AP_SETTING_REQ  (0x2058)
IOTYPE_USER_IPCAM_WIFI_AP_SETTING_RESP  (0x2059)
*/
typedef struct
{
    char    ap_name_[32];
    char    ap_passwd_[32];
    char    reserved[8];  //not used
}SmsgAVIoctrlWifiApSettingReq;

typedef struct
{
    char    reserved[4];  //not used
}SmsgAVIoctrlWifiApGettingReq;

/*
IOTYPE_USER_IPCAM_WIFI_AP_GETTING_REQ  (0x2060)
IOTYPE_USER_IPCAM_WIFI_AP_GETTING_RESP  (0x2061)
*/
typedef struct
{
    int  result_;                //0-ok, orthers-failed
    char reserver_[8];            //
}SMsgAVIoctrlWifiApSettingResp;

typedef struct
{
    char    ap_name_[32];
    char    ap_passwd_[32];
    char    reserved[8];  //not used
}SmsgAVIoctrlWifiApGettingResp;

/*
IOTYPE_USER_IPCAM_CAR_RUNMODE_GETTING_REQ  (0x2062)
IOTYPE_USER_IPCAM_CAR_RUNMODE_GETTING_RESP  (0x2063)
*/
typedef struct
{
    char    reserved[4];  //not used
}SmsgAVIoctrlCarRunModeGettingReq;

typedef struct
{
    unsigned char run_mode_;//1-forard, 2-backward, 3-stopped
    char    reserved[3];  //not used
}SMsgAVIoctrlCarRunModeGettingResp;


// Event Type
typedef enum
{
    USER_EVENT_ALL					= 0x00,	// all event type(general APP-->IPCamera)
    USER_EVENT_MOTIONDECT			= 0x01,	// motion detect start//==s==
    USER_EVENT_VIDEOLOST			= 0x02,	// video lost alarm
    USER_EVENT_IOALARM				= 0x03, // io alarmin start //---s--

    USER_EVENT_MOTIONPASS			= 0x04, // motion detect end  //==e==
    USER_EVENT_VIDEORESUME			= 0x05,	// video resume
    USER_EVENT_IOALARMPASS			= 0x06, // IO alarmin end   //---e--

    USER_EVENT_EXPT_REBOOT			= 0x10, // system exception reboot
    USER_EVENT_SDFAULT				= 0x11, // sd record exception
    USER_EVENT_DOOR_BELL			= 0x12,  // door bell
    USER_EVENT_PIR_WARNING      	= 0x13,  // pir (door alarm)
    USER_EVENT_ALARM_DOOR_WINDOW    = 0X14,  // for door window
    USER_EVENT_ALARM_INFRARED       = 0X15,  // for infrared
    USER_EVENT_ALARM_SMOKING        = 0X16,  // for smoking warning
    USER_EVENT_ALARM_AIR            = 0X17,  // for air warning
    USER_EVENT_ALARM_WHISTLE        = 0X18,  // for whistile warning (Siren)
    USER_EVENT_ALARM_SWITCH         = 0X19,  // for switch warning ()
    USER_EVENT_ALARM_REMOTE         = 0X1A,   // for remote control warning
    USER_EVENT_ALARM_GAS			   = 0X1B,   // for gas warning
    USER_EVENT_ALARM_DOOR_LOWVOL		= 0X1C,   // for door low power warning
    USER_EVENT_ALARM_SMOK_LOWVOL		= 0X1D,   // for smok low power warning
    USER_EVENT_ALARM_IRDA_LOWVOL		= 0X1E,   // for 红外探测 low power warning
    USER_EVENT_ALARM_AIR_LOWVOL		= 0X1F,   // for air low power warning
    USER_EVENT_ALARM_SWITCH_LOWVOL	= 0X20,   // for 开关低电量 warning
    USER_EVENT_ALARM_WHISTLE_LOWVOL	= 0X21,   // for 警笛低电量 warning
    USER_EVENT_ALARM_DOOR_OFFLINE	= 0X22,   // for door离线 warning
    USER_EVENT_ALARM_SMOK_OFFLINE	= 0X23,   // for 烟感离线 warning
    USER_EVENT_ALARM_IRDA_OFFLINE	= 0X24,   // for 红外探测离线 warning
    USER_EVENT_ALARM_AIR_OFFLINE		= 0X25,   // for air离线 warning
    USER_EVENT_ALARM_SWITCH_OFFLINE	= 0X26,   // for 开关离线 warning
    USER_EVENT_ALARM_WHISTLE_OFFLINE	= 0X27,   // for 警笛离线 warning
    USER_EVENT_ALARM_GAS_OFFLINE		= 0X28,   // for gas离线 warning

    USER_EVENT_ALARM_ARMED          = 0X30,   // for armed  手机布防 away 模式
    USER_EVENT_ALARM_DISARM         = 0X31,    // fo disarmed, 手机撤防模式
    USER_EVENT_FEED_PETS_TIMER_FEED  = 0X32,    // for pets  timer feed success
    USER_EVENT_FEED_PETS_MANUL_FEED  = 0X33,    // for pets  manul feed success
    USER_EVENT_FEED_PETS_FEED_WARNING= 0X34,    // for pets alarm food warning
    USER_EVENT_FEED_PETS_NO_FOOD_WARING= 0X35,    // for pets alarm food warning,    // for pets feed failed
    USER_EVENT_FEED_PETS_OUT_FOOD_WARING= 0X36,    // for pets feed failed
    USER_EVENT_SAFEBOX_DOOR_OPENED= 0X37,    // for safebox door opened
    USER_EVENT_SAFEBOX_DOOR_ERROR = 0X38,    // for safebox door passwd-error, or safebox being moving,
    USER_EVENT_SAFEBOX_HOSTAGE    = 0X39,     // for SAFEBOX Hostage
    USER_EVENT_P2P_ONLIE  = 0X3A,             // for p2p online
    USER_EVENT_P2P_OFFLINE= 0X3B,             // for p2p offline
    USER_EVENT_ACCOUNT_LOGIN_OHTRER_LOCATION= 0X3C,    // login in orther loacaltion
    USER_EVENT_MUSIC_PLAYING_STATUS_CHANGED= 0X3D,     // 音乐播放状态变化提醒
    USER_EVENT_BABY_CRING_NOTIFY= 0X3E,                //婴儿哭声提醒
    USER_EVENT_DEVICE_PASSWD_CHANGED= 0X3F,     //设备密码修改提醒
    USER_EVENT_DEVICE_TEMPTURE_ALARMED= 0X40,     //温度告警提醒
    USER_EVENT_DEVICE_HUMIDITY_ALARMED= 0X41,     //湿度告警提醒
    USER_EVENT_FEED_PETS_FEED_OK      = 0X42,    // for pets  feed success
    USER_EVENT_FEED_PETS_FEED_FAILED  = 0X43,    // for pets  feed failed
    USER_EVENT_FEED_PETS_FEED_MOTOR_ERROR  = 0X44, //电机卡住了
    USER_EVENT_SNAP_SHOT_EVENT    = 0XEF,    // for sanp shot-BOGUANG
    USER_EVENT_RECORD_START       = 0XF0,    // for BOGUANG START RECORD
    USER_EVENT_RECORD_STOP        = 0XF1,    // for BOGUANG STOP RECORD,
    USER_EVENT_WARING_BLUE_BOOTTH = 0XF2,    // for BLUETOOLTH ALARMMING
    USER_EVENT_LOW_POWER          = 0XF3,     // for BATTERY LOW POWER
    USER_EVENT_ARMED_HOME_MODE    = 0XF4,     // for HOME-ALARMED -LAJITONG
    USER_EVENT_ARMED_DOOR_MOVED   = 0XF5,     // for door moved
    USER_EVENT_PETWANT_PIR_DETECT = 0XF6,     // for pet pir  detect notify
    USER_EVENT_ARMED_DISALAM_MODE_AUTO  = 0XF7,     // for DISALAM-ALARMED -LAJITONG
    USER_EVENT_ARMED_ALARM_MODE_AUTO    = 0XF8,     // for ALARM-ALARMED -LAJITONG
    USER_EVENT_ARMED_HOME_MODE_AUTO     = 0XF9,      // for HOME-ALARMED -LAJITONG
    USER_EVENT_NOTIFY_VIDEO_DISABLE     = 0XFA,      // for HOME-ALARMED -LAJITONG
    USER_EVENT_NOTIFY_VIDEO_ENABLED     = 0XFB,     // for ALARM-ALARMED -LAJITONG
    USER_EVENT_PM25_WARING              = 0XFC,      //  FOR PM2.5 WARING
    USER_EVENT_SOS_WARING               = 0XFD,      // for SOS KEY WARING    
    USER_EVENT_EVENT_DETECT_NOTIFY_SERVER = 0XFE,      // FOR MOTION NOT NOTIFY PHONE (maxkin n8)

    USER_EVENT_SYSTEM_SETTING_SYNC      = 0X1FF,      //  //同步系统喂食定时列表信息
    USER_EVENT_SYSTEM_SETTING_SOUNDINFO_SYNC      = 0X200,     //同步系统喂食音频信息
    USER_EVENT_PLAYMUSIC_START          = 0X201,     //音乐播放开启
    USER_EVENT_PLAYMUSIC_STOPED         = 0X202,     // 音乐播放关闭

    USER_EVENT_SAFEBOX_SHOCK				= 0X203,     // for SAFEBOX震动报警
}ENUM_USER_EVENTTYPE;

#if defined BUILD_FOR_GANSU_CAM || (defined SUPPORT_433ONEDEVICE_ALARMED)
#define USER_433_ALARM 1
#endif
////////////////////for 433 wifi defines 433 无线模块
typedef struct
{
    unsigned short device_type_;//defines in info.h enum SENSOR_TYPE
    unsigned short device_vender_;
    unsigned char key_[16];     //such as 0600D654600797
    char    aliase_[16];
#ifdef USER_433_ALARM
    unsigned  char device_alarmed;//1-yes, othter no
    unsigned  char alarm_ptz_preset;//0,1-16
    unsigned  char device_closed;//1-yes, othter no
    unsigned  char reserv[1];
#endif
}struct_433_device_p2p;

typedef struct
{
    int num_;
    struct_433_device_p2p devices_array_[20];//suppport 20 devices
}struct_433_devicelist_p2p;


/*
IOTYPE_USER_IPCAM_433_START_PAIR_REQ        =0x2064,
IOTYPE_USER_IPCAM_433_START_PAIR_RESP       =0x2065,
*/
/// 开始配对对码
typedef struct
{
    unsigned short pair_device_type_;////defines in info.h enum SENSOR_TYPE
    char    reserved[2];  //not used
}SmsgAVIoctrlStartPairReq;

typedef struct
{
    unsigned short result_;//0-ok, orther failed
    unsigned char  reserved[2];//
    struct_433_device_p2p   device_info_;  //if result is ok, it is valid
}SmsgAVIoctrlStartPairResp;

/*
 *
IOTYPE_USER_IPCAM_433_STOP_PAIR_REQ         =0x2066,
IOTYPE_USER_IPCAM_433_STOP_PAIR_RESP        =0x2067,
 **/
/// 退出对码
typedef struct
{
    char    reserved[4];  //not used
}SmsgAVIoctrlStopPairReq;

typedef struct
{
    int     result_; //0-ok, orther failed
    char    reserved[4];  //not used
}SmsgAVIoctrlStopPairResp;

/*
 *
IOTYPE_USER_IPCAM_433_GETDIVICES_LIST_REQ   =0x2068,
IOTYPE_USER_IPCAM_433_GETDIVICES_LIST_RESP  =0x2069
 **/
/// 获取433对码所有设备列表
typedef struct
{
    char    reserved[4];  //not used
}SmsgAVIoctrlGetAllDevicesReq;

typedef struct
{
    int     result_; //0-ok, orther failed
    struct_433_devicelist_p2p devices_;//if result is ok,this is valid
}SmsgAVIoctrlGetAllDevicesResp;

//IOTYPE_USER_IPCAM_GETTING_PRESET_NAMELIST_REQ 	  =0x20BC, //
//IOTYPE_USER_IPCAM_GETTING_PRESET_NAMELIST_RESP      =0x20BD
/// 获取PRESET所有设备列表
typedef struct  ptz_preset_info_p2p
{
    int index;//0-15
    int is_valid;//0-invalid, 1-valid
    char preset_name[32];
}struct_ptz_preset_info_p2p;

typedef enum PRESET_TYPE
{
    PRESET_TYPE_GET = 0, //get all preset list name
    PRESET_TYPE_SET = 1, //set all preset list name
    PRESET_TYPE_SET_ONE = 2  //set one preset list name
}enum_preset_type;

typedef struct
{
    int     command_type;//enum_preset_type
    struct_ptz_preset_info_p2p name_list[16];//if(type==PRESET_TYPE_SET_ONE, name_list[0]is valid to be set
}SmsgAVIoctrlGetAllPresetNameReq;

typedef struct
{
    int     command_type;//enum_preset_type
    int     result; //0-ok, orther failed
    struct_ptz_preset_info_p2p name_list[16];//if result is ok,this is valid,list 16 preset pos
}SmsgAVIoctrlGetAllPresetNameResp;

/*
 *
    IOTYPE_USER_IPCAM_433_EDITDIVICES_LIST_REQ    =0x20B8,
    IOTYPE_USER_IPCAM_433_EDITDIVICES_LIST_RESP   =0x20B9
 **/
typedef enum EDIT_433_LIST_TYPE
{
    EDIT_433_LIST_TYPE_GET_ALARM_INFO = 0,/// get alarm info
    EDIT_433_LIST_TYPE_SET_ALARM_TYPE,/// set alarm info
    EDIT_433_LIST_TYPE_SET_CLOSE_TYPE,/// set close device info
    EDIT_433_LIST_TYPE_SAVE_USER_DEFINED_TYPE/// save user device info
}enum_edit_433_list_type;

/// 编辑433批量对码的设备列表
typedef struct
{
    int     type;//refrence to enum_edit_433_list_type
    int     alarm_type;//0-disable, 1-onekey-alarm , 2-home-alarm, 3-store-alarm, 4-use-defined, 5-invalid
    struct_433_devicelist_p2p devices_;//if result is ok,this is valid（just alarm_type= 4 & 5 is valid, or type=2/3）
    char    reserved[4];  //not used
}SmsgAVIoctrlEditAllDevicesReq;

typedef struct
{
    int     type;//refrence to enum_edit_433_list_type
    int     result;//0-ok, -1 failed
    int     alarm_type;//0-disable, 1-onekey-alarm , 2-home-alarm, 3-store-alarm, 4-use-defined, 5-invalid
    struct_433_devicelist_p2p devices_;//if result is ok,this is valid
    char    reserved[4];  //not used
}SmsgAVIoctrlEditAllDevicesResp;

/*
 *    IOTYPE_USER_IPCAM_433_DELETED_DEVICE_REQ    =0x2070,
    IOTYPE_USER_IPCAM_433_DELETED_DEVICE_RESP   =0x2071
    */
///  删除433设备
typedef struct
{
    int     num_; //only support 1, or 16(means delete all)
    char    device_id[16];
    char    reserved[4];  //not used
}SmsgAVIoctrlDeleteDevicesReq;

typedef struct
{
    int     result_; //0-ok, orther failed
    char    reserved[4];  //not used
}SmsgAVIoctrlDeleteDevicesResp;

/*
IOTYPE_USER_IPCAM_DEVICE_USER_EVENT_REPORT	= 0x2072,	// Device USER Event Report Msg
*/
/** @struct SMsgAVIoctrlUserEvent
 */
typedef struct
{
    STimeDay stTime;
    unsigned int time; 	// UTC Time
    unsigned int  channel; 	// Camera Index
    unsigned int  event; 	// Event Type
    unsigned char key_id[16]; //sensor's id
    unsigned char event_device_name[16];//device_name
    unsigned char pic_name[32];//device_name
    unsigned char feed_type; //2-manul feed, 1-timer feed, 3-feed-alarm-waring
    unsigned char alarm_reson;//0x01-feed failed, 2-no food warning, when feed_type==3 this varible is valid
    unsigned short feed_weight;//feed food weight , when feed_type==1 or feed_type=2  this varible is valid
} SMsgAVIoctrlUserEvent;

typedef struct
{
    STimeDay stTime;
    unsigned int time; 	// UTC Time
    unsigned int  channel; 	// Camera Index
    unsigned int  event; 	// Event Type
    unsigned char key_id[16]; //sensor's id
    unsigned char pic_name[32];//device_name
    unsigned char alarm_info[216];//device_name
} SMsgAVIoctrlLongUserEvent;


/*
 *    IOTYPE_USER_IPCAM_433_SET_ALIAS_REQ       =0x2074,
    IOTYPE_USER_IPCAM_433_SET_ALIAS_RESP        =0x2075
 */
///  设置433设备的别名
typedef struct
{
    char    device_id[16];
    char    device_alias[16];
    unsigned char is_alarmed;//1-alarm, 0-disablealarm
    unsigned char ptz_preset;//ptz preset
    unsigned char device_closed;//1-yes, othter no
    char    reserved[1];  //not used
}SmsgAVIoctrlSet433DevicesAliasReq;

typedef struct
{
    int     result_; //0-ok, orther failed
    char    reserved[4];  //not used
}SmsgAVIoctrlSet433DevicesAliasResp;

/*
 *    IOTYPE_USER_IPCAM_SET_SPEAKER_SWITCH_REQ       =0x2076,
 IOTYPE_USER_IPCAM_SET_SPEAKER_SWITCH_RESP        =0x2077
 */
///  设置室内喇叭开关
typedef struct
{
    int     type;   // reserved
    int     status; // 0-off, 1-on
    int     time;   // status==1 -> 10\30\60\120\180\...(seconds)
    char    reserved[4];  //not used
}SmsgAVIoctrlSetSpeakerSwitchReq;

typedef struct
{
    int     result; //0-ok, orther failed
    char    reserved[4];  //not used
}SmsgAVIoctrlSetSpeakerSwitchResp;

/*
 *    IOTYPE_USER_IPCAM_GET_SPEAKER_SWITCH_REQ       =0x2078,
 IOTYPE_USER_IPCAM_GET_SPEAKER_SWITCH_RESP        =0x2079
 */
///  获取室内喇叭开关
typedef struct
{
    int     type;   // reserved
    char    reserved[4];  //not used
}SmsgAVIoctrlGetSpeakerSwitchReq;

typedef struct
{
    int     result; //0-ok, orther failed
    int     type;   // reserved
    int     status; // 0-off, 1-on
    int     time;   // status==1 -> ...(seconds)
    char    reserved[4];  //not used
}SmsgAVIoctrlGetSpeakerSwitchResp;

/*
 */
/** @struct SMsgAVIoctrlUserArmTime
 */

#if 1
typedef struct
{
    unsigned char    number;         //编号，便于管理删除
    unsigned char    week[7];           //week[0]-星期天，week[1－星期一，week[2－星期二，week[3－星期三..week[6-星期六,==1表示星期几有效
    unsigned char    begin_hour;     // 0~23
    unsigned char    begin_minute;   // 0~59
    unsigned char    is_armed;       //1-armed, 0-disarm,2-home-armed
    unsigned char    enabled;        //1-enable, 0-disabled
    unsigned char    end_hour;      // 0~23 //reserverd[2] used for petwant
    unsigned char    end_minute;     // 0~59
    unsigned char    reserverd[2];   //reserved not use now
} SMsgAVIoctrlUserArmTime;
#else
typedef struct
{
    int     number;         //编号，便于管理删除
    char    week[8];        //week[0] 星期tian 0-no, 1-yes
    char    begin_hour;     // 0~23
    char    begin_minute;   // 0~59
    char    end_hour;       // 0~23
    char    end_minute;     // 0~59
    char    reserved[4];    //not used
} SMsgAVIoctrlUserArmTime;
#endif

/*
 */
/** @struct SMsgAVIoctrlUserArmTimeList
 */
typedef struct
{
    int num;
    SMsgAVIoctrlUserArmTime arm_time[60];//suppport 60 arm_time
} SMsgAVIoctrlUserArmTimeList;

/*
 *    IOTYPE_USER_IPCAM_SET_ARM_TIME_REQ       =0x207A,
 IOTYPE_USER_IPCAM_SET_ARM_TIME_RESP        =0x207B
 */
///  增加或删除布防时间
typedef struct
{
    int     type;   // 0-delete, 1-add
    SMsgAVIoctrlUserArmTime userArmTime;
    char    reserved[4];  //not used
}SmsgAVIoctrlSetArmTimeReq;

typedef struct
{
    int     result; //0-ok, orther failed
    char    reserved[4];  //not used
}SmsgAVIoctrlSetArmTimeResp;

/*
 *    IOTYPE_USER_IPCAM_GET_ARM_TIME_REQ       =0x207C,
 IOTYPE_USER_IPCAM_GET_ARM_TIME_RESP        =0x207D
 */
///  获取布防时间
typedef struct
{
    int     type;   // reserved
    char    reserved[4];  //not used
}SmsgAVIoctrlGetArmTimeReq;

typedef struct
{
    int     result; //0-ok, orther failed
    int     type;   // reserved
    SMsgAVIoctrlUserArmTimeList arm_time_list;
    char    reserved[4];  //not used
}SmsgAVIoctrlGetArmTimeResp;

#ifdef BUILD_FOR_JINJIA_IPC
#define TTY_MAX_DATA_SIZE 912
#elif defined BUILD_FOR_GEKA_IPC
#define TTY_MAX_DATA_SIZE 256
#elif defined BUILD_FOR_MAXKIN_IPC
#define TTY_MAX_DATA_SIZE 256
#elif defined BUILD_FOR_LONG_SERIAL_DATA
#define TTY_MAX_DATA_SIZE 256
#else
#define TTY_MAX_DATA_SIZE 64

#endif
/*
IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_REQ     =0x207E,
IOTYPE_USER_IPCAM_TRANSFER_TTY_DATA_RESP    =0x207F*/

typedef struct
{
    unsigned short type;     //not use now
    unsigned short length;   //data length
    unsigned char  data[TTY_MAX_DATA_SIZE];        //commnunicate data
}SmsgAVIoctrlTtyDataReq;

typedef struct
{
    int     result; //0-ok, orther failed
    int     data_length;//recive data length
    char    reserved[4];  //not used
}SmsgAVIoctrlTtyDataResp;

typedef struct
{
    int     result; //0-ok, orther failed
    int     data_length;//recive data length
    unsigned char  data[TTY_MAX_DATA_SIZE];        //commnunicate data
}SmsgAVIoctrlTtyDataResp2;
//typedef struct
//{
//    int     result; //0-ok, orther failed
//    int     number;//number of arrays
//    int     data_length;//recive data length
//    char    data[5][28];  //not used
//}SmsgAVIoctrlTtyDataResp2;

/*
IOTYPE_USER_IPCAM_VIDEO_AVAILABLE_REQ        =0x2080,
IOTYPE_USER_IPCAM_VIDEO_AVAILABLE_RESP       =0x2081,
*/
typedef struct
{
    unsigned int  device_type;     //not use now
    unsigned int  device_vender;
    unsigned char check_data[28];  //commnunicate data
}SmsgAVIoctrlCheckVideoValidReq;

typedef struct
{
    int     result; //0-ok, orther failed
    char    reserved[4];  //not used
}SmsgAVIoctrlCheckVideoValidReqsp;

/*
IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_REQ     =0x2082,
IOTYPE_USER_IPCAM_PETS_SET_LOCALTION_RESP    =0x2083,
*/
/*
IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_REQ     =0x2084,
IOTYPE_USER_IPCAM_PETS_GET_LOCALTION_RESP    =0x2085,
*/
typedef struct
{
    unsigned int  type;     //0-get localton, 1-setlocaltion
    unsigned char localtion_string[64];
}SmsgAVIoctrlSetLocationReq;

typedef struct
{
    int     result; //0-ok, orther failed
    unsigned char localtion_string[64];
}SmsgAVIoctrlSetLocationResp;


/*
    //获取设备地理位置 curl  http://api.map.baidu.com/location/ip?ak=nDjSiIrs6SqyUG87wAGOmchS71iNKZfo&coor=bd09ll
    //{"address":"CN|\u5e7f\u4e1c|\u5e7f\u5dde|None|CHINANET|0|0","content":{"address_detail":{"province":"\u5e7f\u4e1c\u7701","city":"\u5e7f\u5dde\u5e02","district":"","street":"","street_number":"","city_code":257},"address":"\u5e7f\u4e1c\u7701\u5e7f\u5dde\u5e02","point":{"y":"2629614.08","x":"12613487.11"}},"status":0}
[1]+  Done                    curl http://api.map.baidu.com/location/ip?ak=nDjSiIrs6SqyUG87wAGOmchS71iNKZfo
    IOTYPE_USER_IPCAM_GET_DEVICE_ADDR_LOCALTION_REQ      = 0x601D,
    IOTYPE_USER_IPCAM_GET_DEVICE_ADDR_LOCALTION_RESP     = 0x601E
*/
typedef struct
{
    unsigned int  type;     //0-get localton, 1-setlocaltion
    unsigned char reserv[16];
}SmsgAVIoctrlGetAddrLocationnReq;

typedef struct
{
    int     result; //0-ok, orther failed
    unsigned char localtion_string[512];
}SmsgAVIoctrlGetAddrLocationnResp;

/*
IOTYPE_USER_IPCAM_PETS_GET_SOUND_LIST_REQ       =0x2086,
IOTYPE_USER_IPCAM_PETS_GET_SOUND_LIST_RESP      =0x2087,
*/
typedef struct
{
    unsigned char sound_name[32];
    unsigned char sound_aliase[64];
    unsigned int play_time; 	// play Time
    unsigned int creat_time; 	// UTC Time
}struct_sound_info_p2p;

typedef struct
{
    int num_;
    struct_sound_info_p2p sound_array_[5];//suppport 5 sounds
}struct_sound_info_list_p2p;

typedef struct
{
    unsigned int  type;     //not used
    unsigned char reserver[4];
}SmsgAVIoctrlGetSoundListReq;

typedef struct
{
    int     result; //0-ok, orther failed
    struct_sound_info_list_p2p sound_lists;
}SmsgAVIoctrlGetSoundListResp;


/*
    IOTYPE_USER_IPCAM_PETS_GET_PLAY_DOG_SOUND_LIST_REQ       =0x20D5,
    IOTYPE_USER_IPCAM_PETS_GET_PLAY_DOG_SOUND_LIST_RESP      =0x20D6,
*/
typedef struct
{
    int feed_pets_sound_index; //0-default, 1-user defined  (0-狗叫声音 , 1-用户自定义，2－ 猫叫声音)
    struct_sound_info_p2p sound_array_[2];//suppport 5 sounds
}struct_play_dog_sound_info_list_p2p;

typedef struct
{
    unsigned int  cmd_type;     //0-get, 1-set
    unsigned char reserver[4];
}SmsgAVIoctrlGetPlayDogSoundListReq;

typedef struct
{
    int     result; //0-ok, orther failed
    struct_play_dog_sound_info_list_p2p sound_lists;
}SmsgAVIoctrlGetPlayDogSoundListResp;


//IOTYPE_USER_IPCAM_PETS_SET_PLAY_DOG_SOUND_LIST_REQ       =0x20D7,
//IOTYPE_USER_IPCAM_PETS_SET_PLAY_DOG_SOUND_LIST_RESP      =0x20D8,

typedef struct
{
    struct_play_dog_sound_info_list_p2p sound_lists;
    unsigned char reserver[4];
}SmsgAVIoctrlSetPlayDogSoundListReq;

typedef struct
{
    int     result; //0-ok, orther failed
    struct_play_dog_sound_info_list_p2p sound_lists;
}SmsgAVIoctrlSetPlayDogSoundListResp;

//设置宠物6餐喂食参数
//IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_REQ  =0x208C,
//IOTYPE_USER_IPCAM_PETS_SET_SIXED_MEAL_LIST_RESP  =0x208D
typedef enum SET_SIX_MEAL_TYPE
{
    SET_SIX_MEAL_TYPE_GET=0,
    SET_SIX_MEAL_TYPE_SET=1
}ENUM_SET_SIX_MEAL_TYPE;

typedef struct
{
    int  meal_id_;//1-6   餐数索引
    char tty_meal_info[14];//串口通信设置参数
    char one_meal_weight;//0-big大食量, 1-small小食量 2-unkown 未知
    char is_meal_info_changed;// 0-not changed(没有变化)， 1－changed（变化了） 用于设置参数的时候控制是否发送给单片机
    char meal_aliase_[40];//餐名称
}pets_meal_info_p2p;

typedef struct
{
    int num_;//defalut =6
    pets_meal_info_p2p device_meal_list_[6];
}struct_multiy_meal_list_p2p;

typedef struct
{
    unsigned int  cmd_type;     //0-get
    unsigned char reserver[4];
}SmsgAVIoctrlGetMeaListReq;

typedef struct
{
    unsigned int  cmd_type;     //1-set
    struct_multiy_meal_list_p2p meal_list_info; //获取的时候
}SmsgAVIoctrlSetMeaListReq;

typedef struct
{
    int  result; //0-ok, 1-failed,2-timeout, orther failed
    unsigned int  cmd_type;     //0-get, 1-set
    struct_multiy_meal_list_p2p meal_list_info;
}SmsgAVIoctrlSetMeaListResp, SmsgAVIoctrlGetMeaListResp;

/*
IOTYPE_USER_IPCAM_PETS_SET_SOUND_ALIASE_REQ     =0x2088,
IOTYPE_USER_IPCAM_PETS_SET_SOUND_ALIASE_RESP    =0x2089,
*/
typedef struct
{
    unsigned int  type;     //0-set alise, 1-restory default, 2-try listen
    struct_sound_info_p2p sound_info;
}SmsgAVIoctrlSetSoundAliaseReq;

typedef struct
{
    int     result; //0-ok, orther failed
    unsigned char reserver[4];
}SmsgAVIoctrlSetSoundAliaseResp;

/*
IOTYPE_USER_IPCAM_PETS_AUDIO_FILE_SEND_REQ      =0x208A,
IOTYPE_USER_IPCAM_PETS_AUDIO_FILE_SEND_RESP     =0x208B,
*/
typedef struct
{
    unsigned char file_name[32];
    unsigned char file_location[128];
    unsigned int  file_size;
}struct_transfer_file_info;

typedef struct
{
    unsigned int  type; //0-send, orther unkown
    struct_sound_info_p2p sound_info;
    struct_transfer_file_info file_info;
}SmsgAVIoctrlTranferFileReq;

typedef struct
{
    int     result; //0-transfer ok, 1-transfering-begin, -1-tranfer-failed
    unsigned char reserver[4];
}SmsgAVIoctrlTranferFileResp;

//IOTYPE_USER_IPCAM_SAFEBOX_POWER_SETTING_REQ      =0x209A,
//IOTYPE_USER_IPCAM_SAFEBOX_POWER_SETTING_RESP     =0x209B,
//IOTYPE_USER_IPCAM_SAFEBOX_POWER_GETTING_REQ      =0x209C,
//IOTYPE_USER_IPCAM_SAFEBOX_POWER_GETTING_RESP     =0x209D
typedef struct
{
    int     type; //0-get, 1-set, other invalid
    int     enable;   //1-enable, 0-disable
    int     power_on; //1 poweron, 0 poweroff
    char    user[64];
    unsigned char reserver[4];
}SmsgAVIoctrlGetSafeboxPowerReq;

typedef struct
{
    int     result; //0-ok, other failed
    int     enable;   //1-enable, 0-disable
    int     power_on; //1 poweron, 0 poweroff
    unsigned char reserver[4];
}SmsgAVIoctrlGetSafeboxPowerResp;

//IOTYPE_USER_IPCAM_RECORD_GETTING_REQ          =0x20A0,
//IOTYPE_USER_IPCAM_RECORD_GETTING_RESP         =0x20A1
typedef struct mount_nfs_info_p2p
{
    unsigned char instrore_type; //0-sdcard, 1-nfs
    unsigned char mount_status;   //1-ok, -1,failed, 0-other error
    unsigned char mount_error;   //0-noerror, 1-errors
    char     mount_error_string[64];//error-string
    char strore_path[256];//mount path
}store_info_p2p;

typedef struct
{
    unsigned char type; //not use now
    unsigned char reserver[3];
}SmsgAVIoctrlGetRecordInfoReq;

typedef struct
{
    unsigned char result;//0-ok, 1-failed
    unsigned char instore_type;   //1-nfs, 0-sdcard
    unsigned char record_stream;  //0-main-stream, 1-sub-stream
    unsigned char record_minite_timer;//timer record mintes
    unsigned int record_second_motion;//motion record seconds
    store_info_p2p instore_info;//only when instore_type==1,is valid
}SmsgAVIoctrlGetRecordInfoResp;


//IOTYPE_USER_IPCAM_RECORD_SETTING_REQ          =0x209E,
//IOTYPE_USER_IPCAM_RECORD_SETTING_RESP         =0x209F,
typedef struct
{
    unsigned char type; //not use now
    unsigned char instore_type;   //1-nfs, 0-sdcard,if this value changed, should set need_reboot=1
    unsigned char record_stream;  //0-main-stream, 1-sub-stream, if this value changed, should set need_reboot=2
    unsigned char record_minite_timer;//timer record mintes
    unsigned int record_second_motion;//motion record seconds
    unsigned char need_reboot;   //1-reboot, 0-not reboot ,2-restart-process //someof settings need reboot
    unsigned char reserver[3];
}SmsgAVIoctrlSetRecordInfoReq;

typedef struct
{
    unsigned char result; ////0-ok, 1-failed
    unsigned char reserver[3];
}SmsgAVIoctrlSetRecordInfoResp;

typedef struct
{
#define RECORD_TYPE_MOTION_EN		(1<<0)
#define RECORD_TYPE_SCHEDULE_EN		(1<<1)
    char cmdDir;	//APP->DEV, 0:get; 1:set | DEV->APP, 0:sucessful, other:wrong.
    char type;	//录像类型：移动侦测录像，定时录像
    char recordLimitTime;	//每个录像文件的时长，以分钟为单位
    char curScheduleIndex;	//总共可以设置5个定时记录，目前大部分只设置1个
    int startRecordTime;	//定时录像的开始时间，返回当前时间的秒数。如20:10:05,则是20*60*60+10*60+5
    int stopRecordTime;		//定时录像的停止时间, 同上
}SmsgAVIoctrlSetRecordScheduleTimeReq;

typedef struct
{
    unsigned char result; ////0-ok, 1-failed
    unsigned char reserver[3];
}SmsgAVIoctrlNormalResp;


//IOTYPE_USER_IPCAM_AUDIO_PLAY_VOLUME_SETTING_REQ   =0x20A2,
//IOTYPE_USER_IPCAM_AUDIO_PLAY_VOLUME_SETTING_RESP  =0x20A3,
//IOTYPE_USER_IPCAM_AUDIO_CAP_VOLUME_SETTING_REQ    =0x20A4,
//IOTYPE_USER_IPCAM_AUDIO_CAP_VOLUME_SETTING_RESP   =0x20A5
typedef struct
{
    unsigned int command_types_; //0-get, 1-set
    int    value_;             //setting_value [0/1] //setting_value [1-35]，注意声音最大是value=1, 最小可以是40为静音，数值越大声音越小
    char   reserved[8];  //not used
}SMsgAVIoctrlSetPlayVolumeReq, SMsgAVIoctrlSetCpVolumeReq;

typedef struct
{
    unsigned int command_types_; //0-get, 1-set
    int  result_;                //0-ok, orthers-failed
    int  value_;                 //return setting value, when result_==0   //return setting value, when result_==0  & command_types_==1
    //  之前设计此协议的时候，设置type=0时候，没有返回value，需要app用get获取一下实际喇叭大小数值
}SMsgAVIoctrlSetPlayVolumeResp, SMsgAVIoctrlSetCpVolumeResp;


/// for pets attation info
//IOTYPE_USER_IPCAM_PETSDEVICE_INFO_GETTING_REQ     =0x20A6,
//IOTYPE_USER_IPCAM_PETSDEVICE_INFO_GETTING_RESP    =0x20A7,
typedef struct
{
    unsigned char type; //not use now
    unsigned char reserver[3];
}SmsgAVIoctrlGetPetsDeviceInfoReq;

typedef struct
{
    unsigned char result;//0-ok, 1-failed
    unsigned char device_name[31];
    unsigned char device_model[16];
    unsigned char device_capacity[16];
    unsigned char device_weight[16];
    unsigned char device_volume[16];
    unsigned char sensor_special[16];
}SmsgAVIoctrlGetPetsDeviceInfoResp;

//IOTYPE_USER_IPCAM_MANUL_RECORD_SETTING_REQ        =0x20A8,
//IOTYPE_USER_IPCAM_MANUL_RECORD_SETTING_RESP       =0x20A9
typedef struct
{
    unsigned char type; //0-start record, 1-stop record, 2-start snap
    unsigned char reserver[3];
}SmsgAVIoctrlSetManulRecordReq;

typedef struct
{
    unsigned char type;
    unsigned char result; //for type==0, 0-ok is recording, 1-failed(no record-disk),2-operator-timeout 3-orther failed, 4-sdcard full
                          //for type==1, 0-ok is stop now,  1-failed(not stop),2-operator-timeout 3-orther failed,
                          //for type==2, 0-ok, 1-failed(no record-disk),2-orther failed, 4-sdcard full
    unsigned char reserver[2];
}SmsgAVIoctrlSetManulRecordResp;

//IOTYPE_USER_IPCAM_MANUL_RECORD_GETTING_REQ        =0x20AA,
//IOTYPE_USER_IPCAM_MANUL_RECORD_GETTING_RESP       =0x20AB
typedef struct
{
    unsigned char type; //not used
    unsigned char reserver[3];
}SmsgAVIoctrlGetManulRecordReq;

typedef struct
{
    unsigned char type;
    unsigned char result; //1-isrecording, 0-stop recording
    unsigned char reserver[2];
}SmsgAVIoctrlGetManulRecordResp;


/*
    IOTYPE_USER_IPCAM_EDIT_FILES_REQ		    = 0x2054,
    IOTYPE_USER_IPCAM_EDIT_FILES_RESP   		= 0x2055
** @struct SMsgAVIoctrlEditfile
*/

// FILE_EDIT  Command
typedef enum
{
    FILE_EDIT_REMOVE			= 0x10,
    FILE_EDIT_DOWN  			= 0x11,
    FILE_EDIT_DOWN_SNAPSHOT  	= 0x12
}ENUM_FILE_EDIT;

typedef struct file_times
{
    unsigned int Param;		// command param, that the user defined
    STimeDay stTimeDay;		// Event time from ListEvent
}struct_file_times;

typedef struct
{
    unsigned int channel;	// Camera Index
    unsigned int command;	// command. refer to ENUM_FILE_EDIT
    unsigned int Param;		// command param, that the user defined
    STimeDay stTimeDay;		// Event time from ListEvent
    unsigned int reserved_; //reserverd
} SMsgAVIoctrlEditfileReq;

typedef struct
{
    unsigned int command;	// command. refer to ENUM_FILE_EDIT
    unsigned int result; 	// Depends on command
                            //	result>=0  ok
                            //	result <0  error
    unsigned int reserved_; //
} SMsgAVIoctrlEditfileResp; // only for edit files

typedef struct
{
    unsigned int command;	// command. refer to ENUM_FILE_EDIT
    unsigned int result; 	// Depends on command
                            //	result>=0  ok
                            //			-1	file not exist
                            //			-2	exceed max allow client amount
    unsigned char file_path[100];// for edit file name
    unsigned char file_name[24];// for edit file name
    unsigned int  reserverd_;
} SMsgAVIoctrlEditfileResp2; // only for edit file download

/*
    IOTYPE_USER_IPCAM_GET_BOX_EVENT_REQ        =0x20AC,
    IOTYPE_USER_IPCAM_GET_BOX_EVENT_RESP       =0x20AD
*/
typedef struct
{
    unsigned int channel; 		// Camera Index-not user now
    int  stStartTime; 		    // Search event from ...1970 to now time
    int  stEndTime;	  		    // ... to (search event)
    unsigned char event;  		// event type, not user now
    unsigned char status; 		//if status=10 menas delete, orthers means get lists
    unsigned char reserved[2];
}SMsgAVIoctrlListBoxEventReq;


typedef struct
{
    int      stTime;
    unsigned char user_code;  //user code, form user code list
    unsigned char event_type; //1-door opened
    unsigned char reserved[2];
}SAvBoxEvent;

typedef struct
{
    unsigned int  channel;		// Camera Index
    unsigned int  total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
                                // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    SAvBoxEvent stEvent[0];		// The first memory address of the events in this package
}SMsgAVIoctrlListBoxEventResp;

//IOTYPE_USER_IPCAM_GET_BOX_USERCODE_REQ        =0x20AE,
//IOTYPE_USER_IPCAM_GET_BOX_USERCODE_RESP       =0x20AF
typedef struct
{
    unsigned int channel; 		// Camera Index-not user now
    unsigned char reserved[4];
}SMsgAVIoctrlListBoxUserReq;

typedef struct user_name_p2p
{
    int user_code;
    char name[64];
}struct_user_name_p2p;

typedef struct
{
    int num; //total user, <=10
    struct_user_name_p2p name_[10];
}SMsgAVIoctrlListBoxUserResp;


//IOTYPE_USER_IPCAM_LONGTIME_RECORD_SETTING_REQ =0x20B0,
//IOTYPE_USER_IPCAM_LONGTIME_RECORD_SETTING_RESP=0x20B1
typedef struct
{
    unsigned int command_types_; //0-get, 1-set
    int    only_keyframe;      //setting_value [0/1],1-enable, 0-disable
    int    total_keyframe;     //number of record keyframe, defalult 300-not used now
    char   reserved[4];  //not used
}SMsgAVIoctrlSetLongRecordReq;

typedef struct
{
    unsigned int command_types_; //0-get, 1-set
    int    result_;                //0-ok, orthers-failed
    int    only_keyframe;      //setting_value [0/1],1-enable, 0-disable
    int    total_keyframe;     //number of record keyframe, defalult 300-not used now
}SMsgAVIoctrlSetLongRecordResp;



/*
    IOTYPE_USER_IPCAM_EDIT_EVENTS_REQ		      =0x20B2,
    IOTYPE_USER_IPCAM_EDIT_EVENTS_RESP   		  =0x20B3
** @struct SMsgAVIoctrlEditfile
*/

// FILE_EDIT  Command
typedef enum
{
    EVENT_EDIT_REMOVE			= 0x10,
    EVENT_EDIT_REMOVE_ALL	    = 0x11
}ENUM_EVENT_EDIT;

typedef struct
{
    unsigned int command;	// command. refer to ENUM_EVENT_EDIT
    SAvBoxEvent  edit_event;
} SMsgAVIoctrlEditEventReq;

typedef struct
{
    unsigned int command;	// command. refer to ENUM_EVENT_EDIT
    unsigned int result; 	// Depends on command
                            //	result>=0  ok
                            //	result <0  error
    unsigned int reserved_; //
} SMsgAVIoctrlEditEventResp; // only for edit files

/*
    IOTYPE_USER_IPCAM_GETTING_DYMIC_REQ		      =0x20B4,
    IOTYPE_USER_IPCAM_GETTING_DYMIC_RESP   		  =0x20B5
** @struct SMsgAVIoctrlEditfile
*/

// DYMIC_TYPE  Command
typedef enum
{
    DYMIC_TYPE_BATTERAY		= 0x0, //batteray
    DYMIC_TYPE_TEMPTURE		= 0x1, //tempture
    DYMIC_TYPE_HUMDITY		= 0x2, //humdity
    DYMIC_TYPE_ENVARIMENT	= 0x3  //envoriment noise
}DYMIC_TYPE;

typedef struct
{
    unsigned int command;	// command. refer to DYMIC_TYPE
    unsigned char reserver[4];
} SMsgAVIoctrlDymicValueReq;

typedef struct
{
    unsigned int command;	// command. refer to DYMIC_TYPE
    unsigned int value; 	// Depends on command
    unsigned int reserved_; //精度于数，比如温度是27.34, 则reserved_＝34
} SMsgAVIoctrlDymicValueResp;


//IOTYPE_USER_IPCAM_SETTING_ALARM_AUDIO_REQ	  =0x20B6,
//IOTYPE_USER_IPCAM_SETTING_ALARM_AUDIO_RESP    =0x20B7

#define MAX_ALARM_AUDIO_NUM 10
// DYMIC_TYPE  Command
typedef enum
{
    ALARM_AUDIO_GETING_INFO		= 0x0,
    ALARM_AUDIO_SETING_INFO		= 0x1,
    ALARM_AUDIO_LISTEN_INFO		= 0x2
}ALARM_AUDIO_SETTING_TYPE;
typedef struct
{
    unsigned  int command_type;// SEE ALARM_AUDIO_SETTING_TYPE
    unsigned  int enable_alarm_audio; // 0-disable, 1-enable
    unsigned  int alarm_audio_channel; //setting_value [0-MAX_ALARM_AUDIO_NUM]
    char   reserved[4];  //not used
}SMsgAVIoctrlSetAlarmAudioReq;

typedef struct
{
    unsigned  int command_type;       ////SEE ALARM_AUDIO_SETTING_TYPE
    unsigned  int result;             //0-ok orther failed
    unsigned  int enable_alarm_audio; // 0-disable, 1-enable
    unsigned  int alarm_audio_channel; //setting_value [0-MAX_ALARM_AUDIO_NUM]
    unsigned  int  alarm_audio_num;    //[0-MAX_ALARM_AUDIO_NUM]
    char      sound_alarm_audio_list[MAX_ALARM_AUDIO_NUM][16];// user to be externed
}SMsgAVIoctrlSetAlarmAudioResp;


//IOTYPE_USER_IPCAM_SETTING_PLAYMUSIC_REQ 	  =0x20BA, // 设置音乐播放控制
//IOTYPE_USER_IPCAM_SETTING_PLAYMUSIC_RESP      =0x20BB

#define MAX_BABY_AUDIO_NUM 10
// DYMIC_TYPE  Command
typedef enum
{
    BABY_AUDIO_GETING_INFO		= 0x0,//获取状态
    BABY_AUDIO_SETING_INFO		= 0x1,//设置状态
    BABY_AUDIO_LISTEN_INFO		= 0x2,//试听声音,
    BABY_AUDIO_LISTEN_MODE		= 0x3 //设置播放模式
}BABY_AUDIO_SETTING_TYPE;

typedef struct
{
    unsigned  int  command_type;// SEE BABY_AUDIO_SETTING_TYPE 命令类型
    unsigned  int  enable_alarm_audio; // 0-disable, 1-enable， 是否使能产生事件时候播放声音
    unsigned  int  music_audio_channel; //setting_value [0-MAX_BABY_AUDIO_NUM], 当前设置的播放歌曲条目,(等于－1时候表示操作当前歌曲，如果不存在则为第一首)
    unsigned  char operator_command;//0-start, 1-stop, 2-paused for type=BABY_AUDIO_LISTEN_INFO
                                    //1-单曲循环 2-随机播放 3-顺序播放 0-全部循环播放 for type=BABY_AUDIO_LISTEN_MODE
                                    //0-停止  1-开始 2－暂停 for type=BABY_AUDIO_SETING_INFO
    char   reserved[3];  //not used
}SMsgAVIoctrlSetBabyAudioReq;

typedef struct
{
    unsigned  int command_type;       ////SEE ALARM_AUDIO_SETTING_TYPE, 同请求的命令类型相同
    unsigned  int result;             //0-ok orther failed 操作结果
    unsigned  int enable_alarm_audio; // 0-disable, 1-enable 是否使能产生事件时候播放声音
    unsigned  short music_audio_channel; //setting_value [0-MAX_BABY_AUDIO_NUM],当前设置的播放歌曲条目
    unsigned  short play_status;      //音乐播放状态,0-stoped, 1-playing, 2-paused
    unsigned  short music_play_mode;  //1-单曲循环 2-随机播放 3-顺序播放 0-全部循环播放
    unsigned  short music_audio_num;    //[0-MAX_BABY_AUDIO_NUM],总的音乐条数
    char      sound_music_audio_list[MAX_BABY_AUDIO_NUM][32];// user to be externed
}SMsgAVIoctrlSetBabyAudioResp;

typedef struct
{
    unsigned int command;	// command. refer to DYMIC_TYPE
    unsigned char reserver[4];
} SMsgAVIoctrlSetOperatorAuthReq;

typedef struct
{
    unsigned int command;	// command. refer to DYMIC_TYPE
    unsigned int value; 	// Depends on command
    unsigned int reserved_; //
} SMsgAVIoctrlSetOperatorAuthResp;

/*

    IOTYPE_USER_IPCAM_GET_TEMPTURE_EVENT_REQ        =0x20BE,
    IOTYPE_USER_IPCAM_GET_TEMPTURE_EVENT_RESP       =0x20BF,
*/
typedef struct
{
    unsigned int channel; 		// Camera Index-not user now
    int  stStartTime; 		    // Search event from ...1970 to now time
    int  stEndTime;	  		    // ... to (search event)
    unsigned char event;  		// event type, not user now
    unsigned char status; 		//if status=10 menas delete, orthers means get lists
    unsigned char reserved[2];
}SMsgAVIoctrlListTemptureEventReq;

typedef struct
{
    int      stTime;
    unsigned char tempture_high;
    unsigned char tempture_low;
    unsigned char humidity_high;
    unsigned char reserved[1];
}STemptureEvent;

typedef struct
{
    unsigned int  channel;		// Camera Index
    unsigned int  total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
                                // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    STemptureEvent stEvent[0];		// The first memory address of the events in this package
}SMsgAVIoctrlListTemptureEventResp;



typedef enum EVENT_LIST_TYPE
{
    ENUM_EVENT_LIST_TYPE_ALL_TYPES=0,     //defalut
    ENUM_EVENT_LIST_TYPE_VIDEO_CONTROL_TYPES=0x15, //in case to conflit 视频使能事件类型
}ENUM_EVENT_LIST_TYPE;


/*
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_REQ        =0x20C0,
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_RESP       =0x20C1
*/
typedef struct
{
    unsigned int channel; 		// Camera Index-not user now
    int  stStartTime; 		    // Search event from ...1970 to now time
    int  stEndTime;	  		    // ... to (search event), -1 means all event
    unsigned char event;  		// event type, not user now, but used for 马来垃圾桶项目ENUM_EVENT_LIST_TYPE,
                                //start use on 20180115可以指定所有的事件类型（ENUM_USER_EVENTTYPE），0-表示全部类型
    unsigned char status; 		//if status=10 menas delete, orthers means get lists
    unsigned char reserved[2];  //获取事件类型指定条数
}SMsgAVIoctrlListDeviceInstoreEventReq;

typedef struct
{
    int      stTime;
    unsigned short feed_weight;
    unsigned short  event_type; //event type
#ifdef SUPPORT_EVENT_SNAP
    char     pic_name[24];     //picture20151201121212.jpg
#endif
#ifdef SUPPORT_EVENT_STRING
    char     extern_info[216];     //event strings, such as user_name,
#endif
}SDevicenInstoreEvent;

typedef struct
{
    unsigned int  channel;		// Camera Index
    unsigned int  total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
                                // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    SDevicenInstoreEvent stEvent[0];		// The first memory address of the events in this package
}SMsgAVIoctrlListDeviceInstoreEventResp;


/*
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_REQ2    =0x20D3,
    IOTYPE_USER_IPCAM_GET_DEVICE_INSTORE_EVENT_RESP2   =0x20D4,
*/
typedef struct
{
    unsigned int channel; 		// Camera Index-not user now
    int  stStartTime; 		    // Search event from ...1970 to now time
    int  stEndTime;	  		    // ... to (search event), -1 means all event
    unsigned char event;  		// 可以指定所有的事件类型（ENUM_USER_EVENTTYPE），0-表示全部类型
    unsigned char status; 		//if status=10 menas delete, orthers means get lists
    unsigned char reserved[2];  //reserved
    unsigned int  get_max_num;  /// 获取事件类型指定条数或者最大条数
}SMsgAVIoctrlListDeviceInstoreEventReq2;

typedef struct
{
    unsigned int  channel;		// Camera Index
    unsigned int  total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
                                // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    SDevicenInstoreEvent stEvent[0];		// The first memory address of the events in this package
}SMsgAVIoctrlListDeviceInstoreEventResp2;

/*
 *    IOTYPE_USER_IPCAM_EDIT_INSTORE_EVENT_REQ          =0x20C2,
    IOTYPE_USER_IPCAM_EDIT_INSTORE_EVENT_RESP         =0x20C3
 */
typedef enum
{
    EDIT_DEVICE_EVENT_TYPE_PETS_ALARM_EVENT    = 0X01,
    EDIT_DEVICE_EVENT_TYPE_TEMPTURE_LIST       = 0X02,
    EDIT_DEVICE_EVENT_TYPE_SAFEBOX_ALARM_EVENT = 0X03
}EDIT_DEVICE_EVENT_VENDOR_TYPE;

typedef enum
{
    EDIT_DEVICE_EVENT_EDIT_TYPE_DELETE    = 0X01,//delete
    EDIT_DEVICE_EVENT_EDIT_TYPE_CHANGED   = 0X02, //changed
    EDIT_DEVICE_EVENT_EDIT_TYPE_DELETE_ALL= 0X03  //DELETE ALL
}EDIT_DEVICE_EVENT_EDIT_TYPE;

typedef union
{
   SDevicenInstoreEvent pets_alarm_event;
   STemptureEvent       tempture_info_event; //not use now
   SAvBoxEvent          box_alarm_event;     //not use now
}myevent_unit;

typedef struct
{
    unsigned int command_type; //EDIT_DEVICE_EVENT_VENDOR_TYPE
    unsigned int edit_type; //EDIT_DEVICE_EVENT_EDIT_TYPE
    unsigned int number; //<=20
    myevent_unit union_event[20];
}SMsgAVIoctrlListEditInstoreEventReq;

typedef struct
{
    unsigned int command_type;
    unsigned int edit_type;//
    unsigned int result;//0-ok, orther failed
    unsigned int number; //<=20
}SMsgAVIoctrlListEditInstoreEventResp;


/*\
    IOTYPE_USER_IPCAM_CAMERA_LENS_SETTING_REQ	      = 0x20C6,
    IOTYPE_USER_IPCAM_CAMERA_LENS_SETTING_RESP 	      = 0x20C7,
 */
typedef enum COMMAND_TYPE_CAMERA_LENS_TYPE
{
    COMMAND_TYPE_CAMERA_LENS_TYPE_APERTURE_ADD = 0,//光圈+
    COMMAND_TYPE_CAMERA_LENS_TYPE_APERTURE_SUB ,   //光圈－
    COMMAND_TYPE_CAMERA_LENS_TYPE_FOCUS_ADD ,      //焦距+
    COMMAND_TYPE_CAMERA_LENS_TYPE_FOCUS_SUB        //焦距－
}ENUM_CAMRA_LENS_SETTING_TYPE;

typedef struct
{
    unsigned int command_type; ////ENUM_CAMRA_LENS_SETTING_TYPE
    unsigned char reserver[8];//not used now
}SMsgAVIoctrlCameraLensReq;

typedef struct
{
    unsigned int command_type; ///ENUM_CAMRA_LENS_SETTING_TYPE
    unsigned int result;       //0-ok, orther failed
    unsigned char reserver[4];//not used now
}SMsgAVIoctrlCameraLensResp;

//IOTYPE_PRESET_SETPRESET_REQ                 = 0x440,
//IOTYPE_PRESET_SETPRESET_RESP                = 0x441,
typedef struct
{
    unsigned int channel;             // AvServer Index
    unsigned int nPresetIdx;        // 設定至預置點index        數值範圍 0~3(表示預置點1~4)

}SMsgAVIoctrlSetPresetReq;

typedef struct
{
    int result;	// 回傳值	0: success; otherwise: failed
    unsigned char reserved[4];
}SMsgAVIoctrlSetPresetResp;

//IOTYPE_PRESET_GETPRESET_REQ                 = 0x442,
//IOTYPE_PRESET_GETPRESET_RESP                = 0x443,
typedef struct
{
    unsigned int channel;             // AvServer Index
    unsigned int nPresetIdx;        // 載入預置點index        數值範圍 0~3(表示預置點1~4)
}SMsgAVIoctrlGetPresetReq;

typedef struct
{
    unsigned int channel;             // AvServer Index
    unsigned int nPresetIdx;        // 設定至預置點index        數值範圍 0~3(表示預置點1~4)

}SMsgAVIoctrlGetPresetResp;

//IOTYPE_CRUISEMODE_CRUISE_START              = 0x0600,
//IOTYPE_CRUISEMODE_CRUISE_STOP               = 0x0601,
typedef enum CRUISE_MODE
{
    AVIOCTRL_CRUISEMODE_VERTICAL   = 0x00,
    AVIOCTRL_CRUISEMODE_HORIZONTAL = 0x01
}ENUM_CRUISE_MODE;

typedef struct
{
    unsigned int channel;       // Camera Index
    unsigned char mode;        // refer to ENUM_CRUISE_MODE
    unsigned char reserved[3];
}SMsgAVIoctrlCruiseStart;

typedef struct
{
    unsigned int channel; // Camera Index
    unsigned char reserved[4];
} SMsgAVIoctrlCruiseStop;

//IOTYPE_USER_IPCAM_VIDEO_ENABLE_SETTING_REQ	      = 0x20C8,
//IOTYPE_USER_IPCAM_VIDEO_ENABLE_SETTING_RESP	      = 0x20C9,
typedef struct
{
    unsigned int command_type; ////0-GET, 1-SET
    unsigned char video_enabled; //1-enable, 0-diabled
    unsigned char reserver[3];
}SMsgAVIoctrlSetVideoEnabledreq;

typedef struct
{
    unsigned int command_type; ////0-GET, 1-SET
    unsigned char result;      //0-ok, orther failed
    unsigned char video_enabled; //1-enable, 0-diabled
    unsigned char reserver[2];
}SMsgAVIoctrlSetVideoEnabledresp;

//IOTYPE_USER_IPCAM_LOGIN_USER_SETTING_REQ	      = 0x20CA,
//IOTYPE_USER_IPCAM_LOGIN_USER_SETTING_RESP	      = 0x20CB,
typedef struct
{
    unsigned int command_type; ////0-GET, 1-SET
    char username[64]; //1-enable, 0-diabled
    char user_type;    //1-adminstrator, 2-other types, 3-unknow
    unsigned char reserver[3];
}SMsgAVIoctrlSetLoginUsernameReq;

typedef struct
{
    unsigned int command_type; ////0-GET, 1-SET
    char username[64]; //1-enable, 0-diabled
    unsigned char result;      //0-ok, orther failed
    unsigned char user_type;    //1-adminstrator, 2-other types, 3-unknow
    unsigned char reserver[2];
}SMsgAVIoctrlSetLoginUsernameResp;


/*\
 *    IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_REQ	  = 0x20C4,
    IOTYPE_USER_IPCAM_PUSHSERVER_ADDR_SETTING_RESP 	  = 0x20C5
 */
typedef struct
{
    unsigned int command_type; ////0-GET, 1-SET
    char   ip_addrs[24];         //ipaddr
    unsigned int   ip_port;      //port
    char   server_push_path[20]; //server push addr
}SMsgAVIoctrlPushserverAddrReq;

typedef struct
{
    unsigned int command_type; ////0-GET, 1-SET
    int    result;                //0-ok, orthers-failed
    char   ip_addrs[24];         //ipaddr
    unsigned int   ip_port;      //port
    char   server_push_path[20]; //server push addr
}SMsgAVIoctrlPushserverAddrResp;


/*\
 *    IOTYPE_USER_IPCAM_CHANGED_DOWNLOAD_REQ      = 0x20CD,
    IOTYPE_USER_IPCAM_CHANGED_DOWNLOAD_RESP 	  = 0x20CE
 */
typedef enum CHANGED_STATUS
{
    CHANGED_STAUTS_RDT_UNKNOW = 0,
    CHANGED_STAUTS_RDT_STOP  = 1,
    CHANGED_STAUTS_RDT_FORCE_STOP  = 2,
}ENUM_CHANGED_STATUS;

typedef struct
{
    unsigned int command_type; //ENUM CHANGED STATUS
    unsigned char flag_string[16];   //
}SMsgAVIoctrlChangedRdtReq;

typedef struct
{
    int result;//0-ok
    unsigned int command_type; //ENUM CHANGED STATUS
    unsigned char flag_string[16]; //
}SMsgAVIoctrlChangedRdtResp;



/*
 IOTYPE_USER_IPCAM_GET_CUR_WIFI_SIGNAL_REQ       =0x20E9,
 IOTYPE_USER_IPCAM_GET_CUR_WIFI_SIGNAL_RESP      =0x20EA,
 */
//获取当前连接 wifi 的信号强度
typedef struct {
    char reserved[4];
}SMsgGetCurWifiSinnalReq;

typedef struct {
    char ssid[32];
    char signal_level; //-34(-34dBm)
    char result; //0:ok; -1:error
    char reserved[2];
} SmsgGetCurWifiSinnalResp;





/*
 IOTYPE_MKOWL_IS_FEED_AFTER_MOVE_REQ      =0x20ED;
 IOTYPE_MKOWL_IS_FEED_AFTER_MOVE_RESP     =0x20EE;
 */
//猫头鹰运动完是否喂食
//typedef struct {
//    int dir;               //0:Get; 1:Set
//    int is_feed;           //0:no feed; 1:feed
//    char reserved[4];
//
//}SMsgMkOwlSetFeeWalkingParamReq;
//
//typedef struct {
//    int dir;               //0:Get; 1:Set
//    int is_feed;           //0:no feed; 1:feed
//    int result;            //0:ok; -1:error
//    char reserved[4];
//
//}SmsgMkOwlSetFeeWalkingParamResp;

typedef struct {
    int dir; //0:Get; 1:Set
    int feed_copys; //0: 运动完后不喂食; 1~n:运动完后喂食的份数;
    char reserved[4];
}SMsgMkOwlFeedAfterMoveReq;

typedef struct {
    int dir; //0:Get; 1:Set
    int feed_copys; //0: 运动完后不喂食; 1~n:运动完后喂食的份数;
    int result; //0:ok; -1:error
    char reserved[4];
}SMsgMkOwlFeedAfterMoveResp;


/*
 IOTYPE_MKOWL_SET_FREE_WALKING_PARAM_REQ      =0x20EF;
 IOTYPE_MKOWL_SET_FREE_WALKING_PARAM_RESP     =0x20F0;
 */
//猫头鹰自由行走参数
typedef struct {
    int is_bone_ctrl;        //0:just owl move; 1:both owl and bone
    int angle;
    int mileage;
    char flag;          //{bit 0: 1-forword;0-backword}, {bit 1: 1-new way;0-old way}
    char reserved[3];
    
}SMsgSetFeeWalkingParamReq;

typedef struct {
    int result; //0:ok; -1:error
    char reserved[4];
    
}SmsgSetFeeWalkingParamResp;


/*
 IOTYPE_MKOWL_SET_DRIVING_MODE_PARAM_REQ      =0x20F1;
 IOTYPE_MKOWL_SET_DRIVING_MODE_PARAM_RESP     =0x20F2;
 */
//猫头鹰固定驾驶参数
typedef enum {
    MK_BONE_MOVE_MODE_ROLL,           //骨头打滚
    MK_BONE_MOVE_MODE_TURN,           //骨头转身
    MK_BONE_MOVE_MODE_SWING,          //骨头摇摆
    MK_BONE_MOVE_MODE_ROTATE,         //骨头旋转
    MK_BONE_MOVE_MODE_FORWORD,        //骨头前翻
    MK_BONE_MOVE_MODE_BACKWORD,       //骨头后翻
    MK_BONE_MOVE_MODE_RISE,           //骨头抬头
    MK_BONE_MOVE_MODE_NOD,            //骨头点头
    MK_BONE_MOVE_MODE_JUMP,           //骨头跳动
    MK_OWL_MOVE_SWING_FORWORD,        //猫头鹰摇摆前进
    MK_OWL_MOVE_SWING_BACKWORD,       //猫头鹰摇摆后退
    MK_OWL_MOVE_TURN_CW,              //猫头鹰顺时针旋转
    MK_OWL_MOVE_TURN_ANTI_CW,         //猫头鹰逆时针旋转
    MK_OWL_MOVE_NOD,                  //猫头鹰点头
    
}ENUM_MK_MOVE_MODE;

typedef struct {
    int mode; //参考:ENUM_MK_MOVE_MODE，猫头鹰只有 5 种模式
    char reserved[4];
    
}SMsgMkWolSetDrivingModeParamReq;

typedef struct {
    int result; //0:ok; -1:error
    int mode; //参考:ENUM_MK_MOVE_MODE;
    char reserved[4];
    
}SMsgMkWolSetDrivingModeParamResp;


/*
 IOTYPE_MKOWL_CTRL_BONE_MOTION_PARAM_REQ      =0x20F3;
 IOTYPE_MKOWL_CTRL_BONE_MOTION_PARAM_RESP     =0x20F4;
 */
//控制骨头运动模式
typedef struct {
    int mode; //参考:ENUM_MK_MOVE_MODE，骨头支持全部的 9 种模式;
    char reserved[4];
    
}SMsgMkWolCtrlBoneMotionParamReq;

typedef struct {
    int result; //0:ok; -1:error
    int mode; //参考:ENUM_MK_MOVE_MODE
    char reserved[4];
}SMsgMkWolCtrlBoneMotionParamResp;


/*
 IOTYPE_MKOWL_SET_MOVE_SPEED_REQ      =0x20F5;
 IOTYPE_MKOWL_SET_MOVE_SPEED_RESP     =0x20F6;
 */
//猫头鹰获取/设置运动速度
typedef enum {
    MK_MOVE_SPEED_SLOW,
    MK_MOVE_SPEED_MID,
    MK_MOVE_SPEED_FAST,
}ENUM_MK_MOVE_SPEED;

typedef struct {
    int dir; //0:Get; 1:Set
    int speed; //参考:ENUM_MK_MOVE_SPEED
    char reserved[4];
}SMsgMkWolSetMoveSpeedReq;

typedef struct {
    int dir;    //0:Get; 1:Set
    int result;    //0:ok; -1:error
    int speed;     //参考:ENUM_MK_MOVE_SPEED
    char reserved[4];
}SMsgMkWolSetMoveSpeedResp;


/*
 IOTYPE_MKOWL_SET_FEED_COPYS_REQ      =0x20F7;
 IOTYPE_MKOWL_SET_FEED_COPYS_RESP     =0x20F8;
 */
//猫头鹰设置喂食份数
typedef struct {
    int dir; //0:Get; 1:Set
    int feed_copies;
    char reserved[4];
}SMsgMkWolCtrlFeedCopysParamReq;

typedef struct {
    int dir; //0:Get; 1:Set
    int result;  //0:ok; -1:error
    int feed_copies;
    char reserved[4];
}SMsgMkWolCtrlFeedCopysParamResp;


/*
 IOTYPE_MKOWL_SET_ONETIME_WAYPOINTS_REQ      =0x20F9;
 IOTYPE_MKOWL_SET_ONETIME_WAYPOINTS_RESP     =0x20FA;
 */
//猫头鹰按app指定路线运动
typedef struct {
    char total_index;
    char cur_index;
    char point_num;
    char reserved[1];
    char data[100];  //每个点包含 4 个字节:前两个字节是偏转角度，后两个字节是行走距离,每次传输 25 个点
    
}SMsgMkWolSetOnetimeWaypointsReq;

typedef struct {
    int result; //0:ok; -1:error
    char reserved[4];
    
}SMsgMkWolSetOnetimeWaypointsResp;

/*
 IOTYPE_MKOWL_SET_CRUISE_WAY_REQ          =0x20FB,
 IOTYPE_MKOWL_SET_CRUISE_WAY_RESP         =0x20FC,
 */
//猫头鹰巡航路径
typedef enum {
    MK_WOL_CRUISE_WAY_START,
    MK_WOL_CRUISE_WAY_SAVE,
    MK_WOL_CRUISE_WAY_DEL,
}ENUM_MK_SET_CRUISE_EAY;

typedef struct {
    int cmd;
}SMsgMkWolSetCruiseWayReq;

typedef struct {
    int result; //0:ok; -1:error
    char reserved[4];
}SmsgMkWolSetCruiseWayResp;


/*
 IOTYPE_MKOWL_CTRL_SPORT_MODE_REQ           =0x20FF,
 IOTYPE_MKOWL_CTRL_SPORT_MODE_RESP          =0x2100,
*/

enum {
    MK_SPORT_MODE_NONE = 0, //停止所有特殊模式
    MK_SPORT_MODE_TOUCH_MOVE, //触摸设备随机运动模式
    MK_SPORT_MODE_MOTION_TRACK, //移动跟踪模式
};

typedef struct {
    int dir;    //0:Get; 1:Set
    char mode;
    char rever[3];
}SMsgMkWolCtrlSportModeReq;

typedef struct {
    int dir;    //0:Get; 1:Set
    int result;     //0:success; -1:error
    char mode;
    char rever[3];
}SmsgMkWolCtrlSportModeResp;

/*
 IOTYPE_MKOWL_PLAY_AFTER_CONFIG_NET_REQ         =0x2101,
 IOTYPE_MKOWL_PLAY_AFTER_CONFIG_NET_RESP        =0x2102,
 */
typedef struct {
    int rever;
}SMsgMkWolPlayAfterConfigNetReq;

typedef struct {
    int rever;
    int result; //0:success; -1:error
}SMsgMkWolPlayAfterConfigNetResp;

/*
 IOTYPE_MKOWL_OBSTACLE_AVOIDANCE_REQ                        =0x2103,
 IOTYPE_MKOWL_OBSTACLE_AVOIDANCE_RESP                        =0x2104,
 */
typedef struct
{
    int dir;                //0:Get; 1:Set
    int is_avoid;        //0:off; 1:on
    char reserved[4];
}SMsgMkOwlIsObstacleAvoidReq;

typedef struct
{
    int dir;                //0:Get; 1:Set
    int is_avoid;        //0:off; 1:on
    int result;            //0:ok; -1:error
    char reserved[4];
}SMsgMkOwlIsObstacleAvoidResp;

/*
 IOTYPE_MKOWL_HAS_CRUISE_PATH_REQ                            =0x2105,
 IOTYPE_MKOWL_HAS_CRUISE_PATH_RESP                        =0x2106,
 */
typedef struct
{
    int reserved;
}SMsgMkOwlHasCruisePathReq;

typedef struct
{
    int result;            //0:ok; -1:error
    char has_path;        //0:none, 1:客户已设置路径
    char reserved[3];
}SMsgMkOwlHasCruisePathResp;


/*
 IOTYPE_MKOWL_START_ONCE_CRUISE_REQ                        =0x2107,
 IOTYPE_MKOWL_START_ONCE_CRUISE_RESP                        =0x2108,
 */
typedef struct
{
    int reserved;    //不管什么值，都会触发一次巡航行走
}SMsgMkOwlStartOnceCruiseReq;

typedef struct
{
    int result;            //0:ok; -1:error
    char reserved[4];
}SMsgMkOwlStartOnceCruiseResp;

/*
 IOTYPE_MKOWL_GET_CURRENT_SPORT_STATUS_REQ                    =0x2109,
 IOTYPE_MKOWL_GET_CURRENT_SPORT_STATUS_RESP                =0x210A,
 
 enum{
 MK_OWL_DEVICE_STATUS_IDLE = 0,            //用户没有控制
 MK_OWL_DEVICE_STATUS_FREE_WALKING,        //自由行走模式
 MK_OWL_DEVICE_STATUS_SPECIAL_ACT,        //驾驶模式
 MK_OWL_DEVICE_STATUS_CRUISE_PLAN,        //巡航计划
 MK_OWL_DEVICE_STATUS_CURVE_WALKING,        //曲线行走
 MK_OWL_DEVICE_STATUS_TRACK,                //移动跟踪模式
 MK_OWL_DEVICE_STATUS_TOUCH,                //触碰运动模式
 MK_OWL_DEVICE_STATUS_FEED,                //正在喂食
 };
 */
typedef struct
{
    int reserved;
}SMsgMkOwlGetCurSportStatReq;

typedef struct
{
    int result;            //0:ok; -1:error
    char status;
    char reserved[3];
}SMsgMkOwlGetCurSportStatResp;

/*
 IOTYPE_MKOWL_POWER_OFF_PIR_REQ                            =0x210B,
 IOTYPE_MKOWL_POWER_OFF_PIR_RESP                            =0x210C,
 */
typedef struct {
    int dir;        //0:Get; 1:Set
    char is_on;     //0:关闭 PIR, 1:PIR 能唤醒系统
    char reserved[3];
    
    
}SMsgMkOwlPowerOffPirReq;

typedef struct {
    int result;     //0:ok; -1:error
    int dir;        //0:Get; 1:Set
    char is_on;     //0:关闭 PIR, 1:PIR 能唤醒系统
    char reserved[3];
}SMsgMkOwlPowerOffPirResp;





/// 远程回放,录像获取和设置，从源文件移过来的 AVIOCTRLDEFs.h
// AVIOCTRL Play Record Command
typedef enum
{
    AVIOCTRL_RECORD_PLAY_PAUSE			= 0x00,
    AVIOCTRL_RECORD_PLAY_STOP			= 0x01,
    AVIOCTRL_RECORD_PLAY_STEPFORWARD	= 0x02, //now, APP no use
    AVIOCTRL_RECORD_PLAY_STEPBACKWARD	= 0x03, //now, APP no use
    AVIOCTRL_RECORD_PLAY_FORWARD		= 0x04, //now, APP no use
    AVIOCTRL_RECORD_PLAY_BACKWARD		= 0x05, //now, APP no use
    AVIOCTRL_RECORD_PLAY_SEEKTIME		= 0x06, //now, APP no use
    AVIOCTRL_RECORD_PLAY_END			= 0x07,
    AVIOCTRL_RECORD_PLAY_START			= 0x10,
    AVIOCTRL_RECORD_PLAY_ENABLE_AUDIO	= 0x11,//defalult is on
    AVIOCTRL_RECORD_PLAY_ENABLE_VIDEO	= 0x12,//defalult is on
    AVIOCTRL_RECORD_PLAY_NORMAL     	= 0x13 //defalult is on
}ENUM_PLAYCONTROL;
/*
IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL 	= 0x031A,
** @struct SMsgAVIoctrlPlayRecord
*/
typedef struct
{
    unsigned int channel;	// Camera Index
    unsigned int command;	// play record command. refer to ENUM_PLAYCONTROL
    unsigned int Param;		// command param, that the user defined
    STimeDay stTimeDay;		// Event time from ListEvent
    unsigned int reserved_;//commond is
                            // 1 play-start:file-total-ms-length, 60s, reserved_=60*1000;
                            // 2 play-seek:file-seek-ops persend, %50, reserved_=50,
                            // 0x11 , enable for audio
                            // 0x12 , enable for video
} SMsgAVIoctrlPlayRecord;

/*
IOTYPE_USER_IPCAM_RECORD_PLAYCONTROL_RESP 	= 0x031B,
** @struct SMsgAVIoctrlPlayRecordResp
*/
typedef struct
{
    unsigned int command;	// Play record command. refer to ENUM_PLAYCONTROL
    unsigned int result; 	// Depends on command
                            // when is AVIOCTRL_RECORD_PLAY_START:
                            //	result>=0   real channel no used by device for playback
                            //	result <0	error
                            //			-1	playback error
                            //			-2	exceed max allow client amount
    unsigned int reserved_; //commond is
                              // 1 play-start:file-total-ms-length, 60s, reserved_=60*1000;
                              // 2 play-seek:file-seek-ops persend, %50, reserved_=50,
} SMsgAVIoctrlPlayRecordResp; // only for play record start command

// AVIOCTRL Record Type
typedef enum
{
    AVIOTC_RECORDTYPE_OFF				= 0x00,
    AVIOTC_RECORDTYPE_FULLTIME			= 0x01,
    AVIOTC_RECORDTYPE_ALARM				= 0x02,
    AVIOTC_RECORDTYPE_MANUAL			= 0x03,
    AVIOTC_RECORDTYPE_ONLY_KEYFRAME		= 0x04
}ENUM_RECORD_TYPE;

/*
IOTYPE_USER_IPCAM_GETRECORD_REQ			= 0x0312,
** @struct SMsgAVIoctrlGetRecordReq
*/
typedef struct
{
    unsigned int channel; // Camera Index
    unsigned char reserved[4];
}SMsgAVIoctrlGetRecordReq;

/*
IOTYPE_USER_IPCAM_SETRECORD_REQ			= 0x0310,
IOTYPE_USER_IPCAM_GETRECORD_RESP		= 0x0313,
** @struct SMsgAVIoctrlSetRecordReq, SMsgAVIoctrlGetRecordResq
*/
typedef struct
{
    unsigned int channel;		// Camera Index
    unsigned int recordType;	// Refer to ENUM_RECORD_TYPE
    unsigned char record_extern_flag; //if this flag==99, blow setting is valid
    unsigned char record_stream; //minites, not for alarm-record
    unsigned short record_time_minite; //minites, not for alarm-record
//    unsigned char reserved[1];
}SMsgAVIoctrlSetRecordReq, SMsgAVIoctrlGetRecordResq;

/*
IOTYPE_USER_IPCAM_SETRECORD_RESP		= 0x0311,
** @struct SMsgAVIoctrlSetRecordResp
*/
typedef struct
{
    int result;	// 0: success; otherwise: failed.
    unsigned char reserved[4];
}SMsgAVIoctrlSetRecordResp;
/// endof 远程回放

/*
IOTYPE_USER_IPCAM_LISTEVENT_REQ			= 0x0318,
** @struct SMsgAVIoctrlListEventReq
*/
typedef struct
{
    unsigned int channel; 		// Camera Index
    STimeDay stStartTime; 		// Search event from ...
    STimeDay stEndTime;	  		// ... to (search event)
    unsigned char event;  		// event type, refer to ENUM_EVENTTYPE
    unsigned char status; 		// 0x00: Recording file exists, Event unreaded
                                // 0x01: Recording file exists, Event readed
                                // 0x02: No Recording file in the event
    unsigned char reserved[2];
}SMsgAVIoctrlListEventReq;


typedef struct
{
    STimeDay stTime;
    unsigned char event;
    unsigned char status;	// 0x00: Recording file exists, Event unreaded
                            // 0x01: Recording file exists, Event readed
                            // 0x02: No Recording file in the event
    unsigned short time_lenght_second;//
    //unsigned char reserved[2];
}SAvEvent;

/*
IOTYPE_USER_IPCAM_LISTEVENT_RESP		= 0x0319,
** @struct SMsgAVIoctrlListEventResp
*/
typedef struct
{
    unsigned int  channel;		// Camera Index
    unsigned int  total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
                                // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    SAvEvent stEvent[0];		// The first memory address of the events in this package
}SMsgAVIoctrlListEventResp;


typedef struct
{
    int deviceId; //设备编号
    char deviceMac[64]; //mac地址
    int online; //在线状态
    int electricity; //百分比（从1-100）
    int deviceType; //参考SDK文档
}SBoyunZigbeeDevice;

/*
    BOYUN_ZIGBEE_LIST_DEVICES_RESP     = 0x6004,
** @struct SMsgBoyunZigbeeListDevicesResp
*/
typedef struct
{
    unsigned int  total;		// Total event amount in this search session
    unsigned char index;		// package index, 0,1,2...;
                                // because avSendIOCtrl() send package up to 1024 bytes one time, you may want split search results to serveral package to send.
    unsigned char endflag;		// end flag; endFlag = 1 means this package is the last one.
    unsigned char count;		// how much events in this package
    unsigned char reserved[1];
    SBoyunZigbeeDevice stEvent[0];		// The first memory address of the events in this package
}SBoyunZigbeeListDevicesResp;

/*
    BOYUN_ZIGBEE_SENSOR_GET_HUMIDITY_REQ      = 0x6003,
    BOYUN_ZIGBEE_SENSOR_GET_BRIGHTNESS_REQ      = 0x6005,
    BOYUN_ZIGBEE_SENSOR_GET_AIR_QUALITY_REQ      = 0x6007,
    BOYUN_ZIGBEE_SENSOR_GET_TEMPERATURE_REQ      = 0x6009,
    BOYUN_ZIGBEE_SENSOR_GET_KAD_VALUE_REQ      = 0x600B,
    BOYUN_ZIGBEE_SENSOR_GET_HCHO_REQ      		= 0x600D,
    BOYUN_ZIGBEE_SENSOR_GET_TSP_REQ      		= 0x600F,
    BOYUN_ZIGBEE_SENSOR_GET_KAD_STATE_REQ      = 0x6011,
    BOYUN_ZIGBEE_SENSOR_GET_CONTROL_STATE_REQ      = 0x6013,
    BOYUN_ZIGBEE_SENSOR_DELETE_DEVICE_REQ      = 0x601B,
** @struct SZigbeeDeviceStateRequest
*/
typedef struct
{
    int deviceId;
    char deviceMac[64];
}SBoyunZigbeeDeviceStateRequest;

typedef struct
{
    int deviceId;
    char deviceMac[64];
    int value;
}SBoyunZigbeeNumberStateResponse;

/*
    //设置控制器状态
    BOYUN_ZIGBEE_SENSOR_SET_CONTROL_STATE_REQ      = 0x6015,
** @struct SZigbeeDeviceStateRequest
*/
typedef struct
{
    int deviceId;
    char deviceMac[64];
    int controlState; // 1：发送SOS，2：视频，3：布放，4：撤防
}SBoyunZigbeeSetControlStateRequest;

/*
    BOYUN_ZIGBEE_SENSOR_SET_CONTROL_STATE_RESP     = 0x6016,
*/
typedef struct
{
    int result; //0 设置成功， -1 设置失败
}SBoyunZigbeeSetControlStateResponse;

/*
    Ê¹ZigbeeÉãÏñ»úœøÈë×éÍøÄ£Êœ, ÇëÇóÌåÎª¿Õ
    BOYUN_ZIGBEE_PERMIT_JOIN_REQ:      = 0x6017,
*/

/*
    BOYUN_ZIGBEE_PERMIT_JOIN_RESP     = 0x6018,
  @struct SMsgBoyunZigbeePermitJoinResp
*/
typedef struct
{
    int result; //0 ¿ªÆô×éÍø³É¹Š£¬ -1 ¿ªÆô×éÍøÊ§°Ü
}SMsgBoyunZigbeePermitJoinResp;
/*
    BOYUN_ZIGBEE_SENSOR_GET_HUMIDITY_RESP     = 0x6004,
** @struct SZigbeeHumidityResponse
*/
typedef SBoyunZigbeeNumberStateResponse SBoyunZigbeeHumidityResponse;

/*
    BOYUN_ZIGBEE_SENSOR_GET_BRIGHTNESS_RESP     = 0x6006,
** @struct SZigbeeBrightnessResponse
*/
typedef SBoyunZigbeeNumberStateResponse SBoyunZigbeeBrightnessResponse;

/*
    BOYUN_ZIGBEE_SENSOR_GET_AIR_QUALITY_RESP     = 0x6008,
** @struct SZigbeeAirQualityResponse
*/
typedef SBoyunZigbeeNumberStateResponse SBoyunZigbeeAirQualityResponse;

/*
    BOYUN_ZIGBEE_SENSOR_GET_TEMPERATURE_RESP     = 0x600A,
** @struct SZigbeeTemperatureResponse
*/
typedef SBoyunZigbeeNumberStateResponse SBoyunZigbeeTemperatureResponse;
/*
    BOYUN_ZIGBEE_SENSOR_DELETE_DEVICE_RESP     = 0x601C,
    value: 0 success, 1 failed
** @struct SZigbeeTemperatureResponse
*/
typedef SBoyunZigbeeNumberStateResponse SBoyunZigbeeDeleteDeviceResponse;

typedef struct {
#define	ZONTEK_TAKECARE_TIME_TYPE_ALLTIME	1
#define	ZONTEK_TAKECARE_TIME_TYPE_NONE		2
#define	ZONTEK_TAKECARE_TIME_TYPE_DAY		3
#define	ZONTEK_TAKECARE_TIME_TYPE_NIGHT		4
#define	ZONTEK_TAKECARE_TIME_TYPE_USER		5
    char cmdDir;		//APP->DEV, 0:get; 1:set | DEV->APP, 0:get, 1:set, -1:wrong.
    char type;
	char isSaveRecordFile;
    char reserved[1];
    short startRecordTime;
	short stopRecordTime;
}SZonTekTakecareTime;

typedef struct {
#define	ZONTEK_IRFREE_AUTO_SWITCH		1
#define	ZONTEK_IRFREE_MANUAL_ON			2
#define	ZONTEK_IRFREE_MANUAL_OFF		3
	char cmdDir;
	char IRFreeMode;
	char reserved[2];
}SZonTekIRFreeCtrl;

typedef	struct {
#define	ZONTEK_PUSH_MODE_PICTURE		1
#define	ZONTEK_PUSH_MODE_VIDEO			2
#define	ZONTEK_PUSH_MODE_MESSAGE		3
	char cmdDir;
	char warnPushMode;
	char reserved[2];
}SZonTekWarningPushCtrl;

typedef	struct {
#define	ZONTEK_SMARTVOICE_ON	1
#define	ZONTEK_SMARTVOICE_OFF	2
	char cmdDir;
	char smartVoiceMode;
	char reserved[2];
}SZonTekSmartVoiceCtrl;

typedef	struct {
#define	ZONTEK_STATUS_LED_OFF	0
#define	ZONTEK_STATUS_LED_AUTO	1
    char cmdDir;
	char statusLedMode;
	char reserved[2];
}SZonTekStatusLedCtrl;

typedef	struct {
#define	ZONTEK_STATUS_VOICE_TIP_DEV_ONLINE			(1 << 1)
#define	ZONTEK_STATUS_VOICE_TIP_DEV_OFFLINE			(1 << 2)
#define	ZONTEK_STATUS_VOICE_TIP_USER_LOGIN			(1 << 3)
#define	ZONTEK_STATUS_VOICE_TIP_HOUSEKEEPER_ONLINE	(1 << 4)
#define	ZONTEK_STATUS_VOICE_TIP_HOUSEKEEPER_OFFLINE	(1 << 5)
	char cmdDir;
    char reserved[1];
    short statusVoiceTipMode;
}SZonTekStatusVoiceTipCtrl;

typedef struct {
#define    IRLED_AUTO    1
#define    IRLED_OFF    0
#define    IRLED_ON        1
    char cmdDir; //APP->DEV, 0:get; 1:set | DEV->APP, 0:get, 1:set, -1:wrong.
    char isAuto; // 如果是0 ，ledlevel 有效
    char ledLevel;  //#define    IRLED_OFF    0
    //#define    IRLED_ON        1
    char reserved[1];
}SIRLedCtrl;

typedef struct {
    char cmdDir;		//APP->DEV, 0:get; 1:set | DEV->APP, 0:get, 1:set, -1:wrong.
    char remain;		//返回的百分比：0～100
    char reserved[2];
}SBatteryCapacity;





/*
 IOTYPE_USER_GET_HI_BATTERY_CAPACITY_REQ    = 0x602F,
 IOTYPE_USER_GET_HI_BATTERY_CAPACITY_RESP   = 0x6030,
 */
typedef struct {
    char result; //0:ok, -1:error
    char remain; //返回的百分比:0~100
    char is_usb_plugin; //是否接入 usb 充电, 0 为 usb 供电;1 为电池供电;
    char reserved[1];
}SBatteryCapacity2;
//注:IOTYPE_USER_GET_HI_BATTERY_CAPACITY_REQ 请求命令时，忽略参数;参数只对 RESP 有效;



//IOTYPE_USER_SWITCH_PIR_REQ					= 0x6033,
//IOTYPE_USER_SWITCH_PIR_RESP					= 0x6034,
typedef struct {
#define	PIR_OFF		0
#define	PIR_ON		1
    char cmdDir;
    char pirON;
    char reserved[2];
}SPIRSwitch;

//GANSU_CHECK_SENSOR_STATUS_REQ				= 0x6035,
//GANSU_CHECK_SENSOR_STATUS_RESP				= 0x6036,
typedef struct {
    int type;	//传感器类型
    char devId[16];
    char alias[16];
    int status;
}SSensorStatus433;

typedef struct {
    int num;
    SSensorStatus433 devStat[0];
}SGetSensorStatusResp;

//GANSU_GET_NETWORK_STATUS_REQ				= 0x6037,
//GANSU_GET_NETWORK_STATUS_RESP				= 0x6038,
typedef struct {
#define	CUR_USING_NET_DEV_LAN	0x0
#define	CUR_USING_NET_DEV_WIFI	0x1
#define	CUR_USING_NET_DEV_4G		0x2
    int dev;
    int status;
}SGetNetStatusResp;

//IOTYPE_USER_IPCAM_CHANGED_FTP_SETTING_REQ         = 0x20CF,
//IOTYPE_USER_IPCAM_CHANGED_FETP_SETTING_RESP 	  = 0x20D0,
typedef struct
{
    unsigned char cmd_type;//0-get获取参数, 1-set设置参数
    unsigned char alarm_upload_pic_enable;//报警上传图片 1使能，0－禁用
    unsigned char alarm_upload_record_enable;//报警上传录像 1使能，0－禁用
    unsigned char reserverd;// 预留使用
    unsigned int ftpport;			//FTP 端口 21
    char ftpserver[64];	//FTPIP 服务器地址， 192.168.9.99
    char ftpuser[32];		//FTP 用户名abc
    char ftppwd[32];		//FTP  密码123
    char ftpdir[64];		//FTP 服务器存储路径， 默认为 "/"/
}SMsgAVIoctrlSetFtpInfoReq;

typedef struct
{
    unsigned char result;// 预留使用
    unsigned char cmd_type;//0-get获取参数, 1-set设置参数
    unsigned char alarm_upload_pic_enable;//报警上传图片 1使能，0－禁用
    unsigned char alarm_upload_record_enable;//报警上传录像 1使能，0－禁用
    unsigned int ftpport;			//FTP 端口 21
    char ftpserver[64];	//FTPIP 服务器地址， 192.168.9.99
    char ftpuser[32];		//FTP 用户名abc
    char ftppwd[32];		//FTP  密码123
    char ftpdir[64];		//FTP 服务器存储路径， 默认为 "/"
}SMsgAVIoctrlSetFtpInfoResp;

//GEPAI_GET_DOOR_STATUS_REQ					= 0x6037,
//GEPAI_GET_DOOR_STATUS_RESP					= 0x6038,
typedef struct
{
    int dir;		//1 for set; 0 for get.
    int param;
    int param_h;
}SMsgAVIoctrlGepaiCmdReq;

typedef struct
{
    int result;
    int retParam;
    int retParam_h;
}SMsgAVIoctrlGepaiCmdResp;

//PI_SOFT_VR_ENCRYPT_REQ              = 0x6049,
//PI_SOFT_VR_ENCRYPT_RESP             = 0x6050,
typedef struct {
    int len; //For respon, If len > 0, means OK.
    char data[512];
}SPISortEncryptReq, SPISortEncryptResp;


//IOTYPE_USER_IPCAM_CHANGED_RTMP_SETTING_REQ         = 0x20D1,
//IOTYPE_USER_IPCAM_CHANGED_RTMP_SETTING_RESP 	  = 0x20D2,
typedef enum rtmp_cofig_type
{
    RTMP_RTMP_UNKNOW = 0, //未知
    RTMP_GET_RTMP_CONF,   //获取
    RTMP_SET_RTMP_CONF    //设置
}enum_rtmp_cofig_type;

//参考设置例子
//struct_rtmp_conf rtmp_server_conf = {1, "114.55.129.66", "/live/test000"};
typedef struct rtmp_push_server_infop2p
{
    int  rtmp_enable; //0-disable, 1-enable, 2-rtsp-mode
    char rtmp_server_ip[24];
    char rtmp_server_path[128];
}struct_rtmp_conf_p2p;

typedef struct
{
    unsigned int  req_type;// enum_rtmp_cofig_type
    unsigned int  rtmp_stream_channel;//0-main stream, 1-sub stream-
    struct_rtmp_conf_p2p rtmp_config;
}struct_rtmp_operator_manul_req_p2p;

typedef struct
{
    unsigned int  result; //0-ok, orther error
    unsigned int  req_type;// enum_rtmp_cofig_type
    unsigned int  rtmp_stream_channel;//0-main stream, 1-sub stream-
    struct_rtmp_conf_p2p rtmp_config;
}struct_rtmp_operator_manul_resp_p2p;



//IOTYPE_RECORD_SETTING_REQ                    = 0x6062,
//IOTYPE_RECORD_SETTING_RESP                    = 0x6063,

typedef struct {
    int result;
    char cmdDir;    //1 for set; 0 for get.
    char recordStream;    //0:HD  1:sd
    char isRecover;        //0:disable     1:enable
    char reserve[5];
}SMsgAVIoctrlSuserRecordSetReq, SMsgAVIoctrlSuserRecordSetResp;



//IOTYPE_USER_IPCAM_DEVICE_GET_PETS_FEEDNUM_REQ    =0x5009,
//IOTYPE_USER_IPCAM_DEVICE_GET_PETS_FEEDNUM_RESP   =0x500A,
typedef struct
{
    int command_type;//0-get, 1-set
    int max_feed_num;//set num of feed total meial num,  4<=max_feed_num<=10
}SmsgAVIoctrlGetMaxFeederNumReq;
typedef struct
{
    int command_type;//0-get, 1-set
    int result;      //0-ok, orther failed
    int max_feed_num;//num of feed total meial num 4<=max_feed_num<=10
}SmsgAVIoctrlGetMaxFeederNumResp;

#endif
