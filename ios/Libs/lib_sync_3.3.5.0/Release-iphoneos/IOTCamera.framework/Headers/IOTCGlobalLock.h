/*! \file IOTCGlobalLock.h
Due to power consumption concern, device will enter sleep mode and all. 
IOTC module will be disconnected. It needs a way to keep login and wake IOTC up.

\copyright Copyright (c) 2010 by Throughtek Co., Ltd. All Rights Reserved.*/


#ifndef __IOTC_GLOBAL_LOCK_H__
#define __IOTC_GLOBAL_LOCK_H__


#ifdef _WIN32
	#if defined P2PAPI_EXPORTS
		#define P2PAPI_API __declspec(dllexport)
	#else
		#define P2PAPI_API __declspec(dllimport)
	#endif
#else
	#define P2PAPI_API
#endif


#ifdef __cplusplus
extern "C" {
#endif

P2PAPI_API int IOTC_GlobalLock_Lock();

P2PAPI_API int IOTC_GlobalLock_Unlock();


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif // __IOTC_GLOBAL_LOCK_H__
