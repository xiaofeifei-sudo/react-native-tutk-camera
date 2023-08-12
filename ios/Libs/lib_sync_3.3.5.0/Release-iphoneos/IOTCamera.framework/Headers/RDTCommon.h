/*! \file RDTCommon.h
This file describes all the APIs of the RDT module in IOTC platform.

\copyright Copyright (c) 2010 by Throughtek Co., Ltd. All Rights Reserved.
 */

#ifndef _RDTCOMMON_H_
#define _RDTCOMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "TUTKGlobalAPIs.h"


/* ============================================================================
 * Platform Dependant Macro Definition
 * ============================================================================
 */

#ifdef _WIN32
    #ifdef IOTC_STATIC_LIB
        #define RDTAPI_API
    #elif defined RDTAPI_EXPORTS
        #define RDTAPI_API __declspec(dllexport)
    #else
        #define RDTAPI_API __declspec(dllimport)
    #endif
#else
    #define RDTAPI_API
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define RDTAPI_API_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
    #ifdef IOTC_STATIC_LIB
        #define RDTAPI_API_DEPRECATED __declspec(deprecated)
    #elif defined P2PAPI_EXPORTS
        #define RDTAPI_API_DEPRECATED __declspec(deprecated, dllexport)
    #else
        #define RDTAPI_API_DEPRECATED __declspec(deprecated, dllimport)
    #endif
#else
    #define RDTAPI_API_DEPRECATED
#endif

#ifndef _WIN32
    #define __stdcall
#endif


/* ============================================================================
 * Generic Macro Definition
 * ============================================================================
 */

#define MAX_DEFAULT_RDT_CHANNEL_NUMBER				128

/* ============================================================================
 * Error Code Declaration
 * ============================================================================
 */
/** The function is performed successfully. */
#define		RDT_ER_NoERROR							 0

/** RDT module is not initialized yet. Please use RDT_Initialize() for initialization. */
#define		RDT_ER_NOT_INITIALIZED					-10000

/** RDT module is already initialized. It is not necessary to re-initialize. */
#define		RDT_ER_ALREADY_INITIALIZED				-10001

/** The number of RDT channels has reached maximum.
 * Please use RDT_Set_Max_Channel_Number() to set up the max number of RDT channels.
 * By default, the maximum channel number is #MAX_DEFAULT_RDT_CHANNEL_NUMBER. */
#define		RDT_ER_EXCEED_MAX_CHANNEL				-10002

/** Insufficient memory for allocation */
#define		RDT_ER_MEM_INSUFF						-10003

/** RDT module fails to create threads. Please check if OS has ability to
 * create threads for RDT module. */
#define		RDT_ER_FAIL_CREATE_THREAD				-10004

/** RDT module fails to create Mutexs when doing initialization. Please check
 * if OS has sufficient Mutexs for RDT module. */
#define		RDT_ER_FAIL_CREATE_MUTEX				-10005

/** RDT channel has been destroyed. Probably caused by local or remote site
 * calls RDT_Destroy(), or remote site has closed IOTC session. */
#define		RDT_ER_RDT_DESTROYED					-10006

/** The specified timeout has expired during the execution of some RDT module service.
 * For most cases, it is caused by slow response of remote site or network connection issues */
#define		RDT_ER_TIMEOUT							-10007

/** The specified RDT channel ID is valid */
#define		RDT_ER_INVALID_RDT_ID					-10008

/** The remote site has finished sending data, then destroy the RDT channel.
 * The local site will get this error code by RDT_Read() when there is no more
 * data from this RDT channel. */
#define		RDT_ER_RCV_DATA_END						-10009

/** The remote site want to abort the RDT channel immediately and don't care data transmission.
 * The local site will get this error code by RDT_Read(), RDT_Write(), RDT_Destroy() for handling
 * this RDT channel to close. */
#define		RDT_ER_REMOTE_ABORT						-10010

/** The local site called RDT_Abort() so the RDT channel is already not available. */
#define		RDT_ER_LOCAL_ABORT						-10011

/** The specific IOTC session and channel ID is used now so can't use the same resource.
 *  You can choose other IOTC channel for RDT use or wait RDT_Abort() to release resource automatically. */
#define		RDT_ER_CHANNEL_OCCUPIED					-10012

/** This is a lite UID and it does not support RDT module. */
#define		RDT_ER_NO_PERMISSION					-10013

/** The arguments passed to a function is invalid. */
#define		RDT_ER_INVALID_ARG						-10014

/** The local site called RDT_Create_Exit() so the RDT channel exit creating. */
#define		RDT_ER_LOCAL_EXIT						-10015

/** The remote site called RDT_Create_Exit() so the RDT channel exit creating. */
#define		RDT_ER_REMOTE_EXIT						-10016

/** The RDT write buffer is full. Try again after min 1ms  this Error code only return when RDT_Set_Max_SendBuff_Size is be set. */
#define		RDT_ER_SEND_BUFFER_FULL					-10017

/** All RDT connection should call RDT_Abort or RDT_Destroy before doing RDT_Deinitialize  */
#define		RDT_ER_UNCLOSED_CONNECTION_DETECTED		-10018

/** RDT module is currently deinitializing. It is not necessary to re-deinitialize. */
#define     RDT_ER_DEINITIALIZING                   -10019

/** RDT fails to initialize DTLS module. */
#define     RDT_ER_FAIL_INITIALIZE_DTLS             -10020

/** RDT fails to create safe channel */
#define     RDT_ER_CREATE_DTLS_FAIL                 -10021

/** The API operation is invalid */
#define     RDT_ER_OPERATION_IS_INVALID             -10022

/** Remote RDT not support DTLS*/
#define     RDT_ER_REMOTE_NOT_SUPPORT_DTLS          -10023

/** Remote RDT need connect with DTLS*/
#define     RDT_ER_LOCAL_NOT_SUPPORT_DTLS           -10024


/* ============================================================================
 * Structure Definition
 * ============================================================================
 */

/**
 * \details RDT channel status, containing the current status of a RDT channel created
 *  between a RDT server and a RDT client. Users can use RDT_Status_Check()
 *  to get RDT status.
 */
struct st_RDT_Status {
    uint16_t Timeout;  //!< The remaining time, in unit of second, to keep the RDT channel alive
    uint16_t TimeoutThreshold; //!< RDT channel will be terminated if timeout exceeds this threshold, in unit of seconds
    uint32_t BufSizeInSendQueue; //!< The size, in unit of byte, of buffer remaining in the sending queue in the local site
    uint32_t BufSizeInRecvQueue; //!< The size, in unit of byte, of buffer remaining in the receiving queue in the local site
};


/* ============================================================================
 * Function Declaration
 * ============================================================================
 */

/**
 * \brief Get the version of RDT module
 *
 * \details This function returns the version of RDT module
 *
 * \return The version of RDT module from high byte to low byte, for example, 0x01020304
 *			means the version is 1.2.3.4
 *
 * \see IOTC_Get_Version(), avGetAVApiVer()
 */
RDTAPI_API_DEPRECATED int32_t RDT_GetRDTApiVer();

/**
 * \brief Get the version of RDT module
 *
 * \details This function returns the version of RDT module
 */
RDTAPI_API const char* RDT_GetRDTApiVersionString(void);

/**
 * \brief Set the max number of RDT channels
 *
 * \details This function set the max number of allowable RDT channels.
 *			The max number of RDT channels limits the max number of
 *			RDT channels that a RDT server can establish with multiple RDT clients
 *			from RDT server's point of view, while it limits the max number
 *			of RDT channels that a RDT client can establish with multiple RDT servers
 *			from RDT client's point of view. A RDT server or a RDT
 *			client could use this function to reduce the number of RDT channels
 *			in order to save some memory usage.
 *
 * \param nMaxChannelNum [in] The max number of RDT channels
 *
 * \attention	(1) This function is optional if users do not want to change the
 *				default max number of RDT channels. However, if users really
 *				wants to change it, this function shall be called before
 *				RDT_Initialize(). <br><br>
 *				(2) The default maximum RDT channel number is #MAX_DEFAULT_RDT_CHANNEL_NUMBER
 *				in all platforms.
 */
RDTAPI_API	void RDT_Set_Max_Channel_Number(uint32_t nMaxChannelNum);

/**
 * \brief Initialize RDT module
 *
 * \details This function is used by RDT servers or RDT clients to initialize RDT
 *			module and shall be called before any RDT module related function
 *			is invoked, except RDT_Set_Max_Channel_Number().
 *
 * \return The actual maximum number of allowable RDT channels if initializing successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_ALREADY_INITIALIZED RDT module is already initialized
 *			- #RDT_ER_FAIL_CREATE_MUTEX Fails to create Mutexs
 *			- #TUTK_ER_NO_LICENSE_KEY Need to call TUTK_SDK_Set_License_Key() before all module start/initialize.
 *			- #RDT_ER_FAIL_INITIALIZE_DTLS Fails to initialize DTLS mode
 *
 * \see IOTC_Initialize(), IOTC_Initialize2(), RDT_DeInitialize(), TUTK_SDK_Set_License_Key()
 *
 * \attention IOTC module is needed to be initialized before initializing RDT module.
 *				That is, please invoke IOTC_Initialize() or IOTC_Initialize2()
 *				before this function.
 */
RDTAPI_API	int32_t RDT_Initialize();

/**
 * \brief Deinitialize RDT module
 *
 * \details This function will deinitialize RDT module.
 *
 * \return #RDT_ER_NoERROR if deinitialize successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED if RDT module is not initialized yet.
 *			- #RDT_ER_UNCLOSED_CONNECTION_DETECTED if RDT connections are not closed
 *
 * \see RDT_Initialize()
 *
 * \attention (1) RDT module shall be deinitialized before IOTC module is
 *				deinitialized.
 *			  (2) All RDT connection should call RDT_Abort or RDT_Destroy
 *				before doing RDT_Deinitialize
 *
 */
RDTAPI_API	int32_t RDT_DeInitialize();

/**
 * \brief Create a RDT channel
 *
 * \details This function will create a RDT channel based on specified IOTC channel
 *
 * \param nIOTCSessionID [in] The session ID of the IOTC session to create RDT channel
 * \param nTimeout [in] The timeout for this function in unit of million-second.
 *			Specify it as 0 will make this function block forever until a RDT
 *			channel is successfully created or error happens
 * \param nIOTCChannelID [in] The channel ID of the IOTC channel to create RDT channel
 *
 * \return RDT channel ID if return value >= 0
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
 *			- #RDT_ER_EXCEED_MAX_CHANNEL The number of RDT channels has reached maximum
 *			- #RDT_ER_MEM_INSUFF Insufficient memory for allocation
 *			- #RDT_ER_FAIL_CREATE_MUTEX Fails to create Mutex
 *			- #RDT_ER_FAIL_CREATE_THREAD Fails to create threads
 *			- #RDT_ER_RDT_DESTROYED RDT has been destroyed, probably caused
 *				by disconnection from remote site
 *			- #IOTC_ER_NOT_INITIALIZED The IOTC module is not initialized yet
 *			- #IOTC_ER_INVALID_SID The specified IOTC session ID is not valid
 *			- #IOTC_ER_SESSION_CLOSE_BY_REMOTE The IOTC session of specified
 *				session ID has been closed by remote site
 *			- #IOTC_ER_REMOTE_TIMEOUT_DISCONNECT The timeout defined by #IOTC_SESSION_ALIVE_TIMEOUT
 *				expires because	remote site has no response
 *			- #RDT_ER_TIMEOUT The timeout specified by nTimeout expires before
 *				RDT creation is performed completely
 *			- #RDT_ER_CHANNEL_OCCUPIED The specific IOTC session and channel ID not available,
 *				it means the resource not release yet. If caused by RDT_Abort() called must wait
 *				a minute for the resource release automatically.
 *			- #RDT_ER_REMOTE_EXIT Remote site exit this RDT channel connection
 *			- #RDT_ER_INVALID_ARG Invalid Argument
 *			- #RDT_ER_LOCAL_NOT_SUPPORT_DTLS Remote site just allow DTLS connection
 *
 * \see RDT_Destroy() and RDT_Abort()
 *
 * \attention (1) The IOTC channel of specified channel ID will be turned on automatically
 *				by RDT_Create()
 *				(2) This function will need 288 bytes stack size.
 *
 */
RDTAPI_API_DEPRECATED int32_t RDT_Create(int32_t nIOTCSessionID, int32_t nTimeout, uint8_t nIOTCChannelID);

/**
 * \brief Exit the process of a specific RDT channel create
 *
 * \details This function will create a RDT channel based on specified IOTC channel
 *
 * \param nIOTCSessionID [in] The session ID argument passed to call RDT_Create()
 * \param nIOTCChannelID [in] The channel ID argument passed to call RDT_Create()
 *
 * \return RDT_ER_NoERROR if function called successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_INVALID_ARG RDT nIOTCSessionID or nIOTCChannelID is valid
 *			- #RDT_ER_INVALID_RDT_ID can't find related RDT channel ID via nIOTCSessionID and nIOTCChannelID
 *
 * \see RDT_Server_Create() RDT_Client_Create()
 *
 * \attention It will send exit message to remote but old version can't recognize it,
 *				so must wait until timeout for RDT_Server_Create() or RDT_Client_Create() return.
 *
 */
RDTAPI_API	int32_t RDT_Create_Exit(int32_t nIOTCSessionID, uint8_t nIOTCChannelID);

/**
 * \brief Destroy a RDT channel
 *
 * \details This function will destroy the RDT channel specified by a channel ID
 *
 * \param nRDTChannelID [in] The channel ID of the RDT channel to destroy
 *
 * \return RDT_ER_NoERROR if destroying successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED RDT is not initialized yet
 *			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
 *			- #RDT_ER_REMOTE_ABORT Remote site abort this RDT channel connection so
 *				the data may not send/receive to/from remote site completely.
 *
 * \see RDT_Server_Create() RDT_Client_Create()
 *
 * \attention The IOTC channel containing RDT channel will be turned off after the RDT
 *				channel is destroyed. It will block until remote site call RDT_Destroy()
 				or IOTC session disconnected.
 */
RDTAPI_API	int32_t RDT_Destroy(int32_t nRDTChannelID);

/**
 * \brief Abort a RDT channel
 *
 * \details This function will abort the RDT channel connection specified by a channel ID
 *
 * \param nRDTChannelID [in] The channel ID of the RDT channel to abort
 *
 * \return RDT_ER_NoERROR if abort successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED RDT is not initialized yet
 *			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
 *
 * \see RDT_Server_Create() RDT_Client_Create()
 *
 * \attention It will ignore all data received or not send yet,
 				force to abort the RDT channel connection.
 */
RDTAPI_API	int32_t RDT_Abort(int32_t nRDTChannelID);

/**
* \brief Set max send queue buffer size
*
* \details Limit the send queue buffer size, when the buffer is full RDT_Write will return RDT_ER_SEND_BUFFER_FULL
*
* \param nRDTChannelID [in] The channel ID of the RDT channel
*
* \param nMaxSendBufferSize [in] The maximum size of send queue buffer
*
*/
RDTAPI_API	int32_t RDT_Set_Max_SendBuffer_Size(int32_t nRDTChannelID, int32_t nMaxSendBufferSize);

/**
 * \brief Flush data in an RDT channel
 *
 * \details Called by a RDT server or a RDT client to flush data in the buffer,
 *          otherwise RDT may wait until data can fill out the whole packet
 *
 * \param nRDTChannelID [in] The channel ID of the RDT channel to write data
 *
 * \return RDT_ER_NoERROR if flush successfully
 * \return Error code if return value < 0
 *          - #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
 *          - #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
 *          - #RDT_ER_RDT_DESTROYED RDT module has been destroyed, probably caused
 *              by disconnection from remote site
 *          - #IOTC_ER_NOT_INITIALIZED The IOTC module is not initialized yet
 *          - #IOTC_ER_INVALID_SID The specified IOTC session ID is not valid
 *          - #IOTC_ER_SESSION_CLOSE_BY_REMOTE The IOTC session of specified
 *              session ID has been closed by remote site
 *          - #IOTC_ER_REMOTE_TIMEOUT_DISCONNECT The timeout defined by #IOTC_SESSION_ALIVE_TIMEOUT
 *              expires because remote site has no response
 *          - #RDT_ER_REMOTE_ABORT Remote site abort this RDT channel connection
 *          - #RDT_ER_LOCAL_ABORT Local site abort this RDT channel connection
 *
 */
RDTAPI_API  int32_t RDT_Flush(int32_t nRDTChannelID);

/**
 * \brief Write data through a RDT channel
 *
 * \details Called by a RDT server or a RDT client to write data through
 *			a specified RDT channel to the other. RDT_Write might not send
 *			small size data directly, if you need to write small size data
 *			directly you can call RDT_Flush after RDT_Write
 *
 * \param nRDTChannelID [in] The channel ID of the RDT channel to write data
 * \param cabBuf [in] The array of byte buffer containing the data to write
 * \param nBufSize [in] The length of the byte buffer
 *
 * \return The actual length of buffer to be written if write successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
 *			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
 *			- #RDT_ER_RDT_DESTROYED RDT module has been destroyed, probably caused
 *				by disconnection from remote site
 *			- #IOTC_ER_NOT_INITIALIZED The IOTC module is not initialized yet
 *			- #IOTC_ER_INVALID_SID The specified IOTC session ID is not valid
 *			- #IOTC_ER_SESSION_CLOSE_BY_REMOTE The IOTC session of specified
 *				session ID has been closed by remote site
 *			- #IOTC_ER_REMOTE_TIMEOUT_DISCONNECT The timeout defined by #IOTC_SESSION_ALIVE_TIMEOUT
 *				expires because	remote site has no response
 *			- #RDT_ER_REMOTE_ABORT Remote site abort this RDT channel connection
 *			- #RDT_ER_LOCAL_ABORT Local site abort this RDT channel connection
 *			- #RDT_ER_SEND_BUFFER_FULL the buffer size is full, the max buffer size is set by
 *				RDT_Set_Max_SendBuffer_Size()
 *
 * \see RDT_Read() RDT_Set_Max_SendBuffer_Size()
 *
 * \attention This function will need 5088 bytes stack size.
 *
 */
RDTAPI_API	int32_t RDT_Write(int32_t nRDTChannelID, const char *cabBuf, int32_t nBufSize);

/**
 * \brief Read data through a RDT channel
 *
 * \details Called by a RDT server or a RDT client to read data through
 *			a specified RDT channel from the other.
 *
 * \param nRDTChannelID [in] The channel ID of the RDT channel to read data
 * \param abBuf [out] The array of byte buffer to receive read result
 * \param nBufSize [in] The maximum length of the byte buffer
 * \param nTimeout [in] The timeout for this function in unit of million-second
 *
 * \return The actual length of read result stored in abBuf if read successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
 *			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
 *			- #RDT_ER_RDT_DESTROYED RDT module has been destroyed, probably caused
 *				by disconnection from remote site
 *			- #RDT_ER_TIMEOUT The timeout specified by nTimeout expires before
 *				read process is performed completely
 *			- #RDT_ER_RCV_DATA_END No more data can be read from the RDT channel
 *				and this RDT channel has been destroyed by the remote site
 *			- #RDT_ER_REMOTE_ABORT Remote site abort this RDT channel connection
 *			- #RDT_ER_LOCAL_ABORT Local site abort this RDT channel connection
 *			- #RDT_ER_REMOTE_EXIT Remote site exit this RDT channel connection
 *			- #RDT_ER_INVALID_ARG nBufSize or nTimeout argument is wrong
 *
 * \see RDT_Write()
 *
 * \attention This function will need 292 bytes stack size.
 *
 */
RDTAPI_API	int32_t RDT_Read(int32_t nRDTChannelID, char *abBuf, int32_t nBufSize, int32_t nTimeout);

/**
 * \brief Get status of a RDT channel
 *
 * \details A RDT server or a RDT client may use this function to get the
 *			status of a specified RDT channel
 *
 * \param nRDTChannelID [in] The channel ID of the RDT channel to get status
 * \param psRDT_Status [out] The status of specified RDT channel
 *
 * \return #RDT_ER_NoERROR if getting the RDT status successfully
 * \return Error code if return value < 0
 *			- #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
 *			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
 */
RDTAPI_API	int32_t RDT_Status_Check(int32_t nRDTChannelID, struct st_RDT_Status *psRDT_Status);

/**
 * \brief Set path of log file
 *
 * \details Set the absolute path of log file
 *
 * \param path [in] The path of log file, NULL = disable Log
 *
 * \param nMaxSize [in] The maximum size of log file in Bytes, 0 = unlimit
 *
 */
RDTAPI_API	void RDT_Set_Log_Path(const char *path, int32_t nMaxSize);

/**
 * \brief Set Attribute of log file
 *
 * \param logAttr [in] See #LogAttr
 *
 * \return #RDT_ER_NoERROR on success.
 * \return The value < 0
 *			- #RDT_ER_INVALID_ARG   Invalid input argument.
 */
RDTAPI_API int32_t RDT_Set_Log_Attr(LogAttr logAttr);

/**
* \brief Set the max number of pending ACKs of the RDT channel
*
* \details This function is related to the frequency of sending RDT ACK, set 0 to
*       nMaxNumber if you want to force RDT to send ACK immediately, it might
*       consume more CPU resource and network bandwidth, but it might improve
*       the performance of RDT data transmission; 0 is the default value
*       of nMaxNumber, we suggest not to use the number bigger than 80
*
* \param nRDTChannelID [in] The channel ID of the RDT channel to get status
* \param nMaxNumber [in] The max pending number of RDT ACK of the RDT channel
*
* \return #RDT_ER_NoERROR if getting the RDT status successfully
* \return Error code if return value < 0
*			- #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
*			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
*
* \attention Please invoke this function after RDT channel is created. This
*           function will work only when the remote RDT version is equal
*           or bigger than 2.1.0
*
*/
RDTAPI_API	int32_t RDT_Set_Max_Pending_ACK_Number(int32_t nRDTChannelID, uint32_t nMaxNumber);

/**
* \brief Set the max packet data size of a single RDT packet.
*
* \details This function can set the max packet data size of a RDT packet.
* 		   By default, the max data size of RDT is 1280. For some situation, the
* 		   MTU size might be smaller than default value. User can adjust the max
* 		   RDT packet data size by this function.
*
* \param nMaxSize [in] The max packet size of a single RDT packet.
*
* \return #RDT_ER_NoERROR if setting successfully
* \return Error code if return value < 0
*			- #RDT_ER_INVALID_ARG	The arg is invalid or bigger than 1280 or smaller than 100.
*
* \attention (1) The max packet size must be smaller than 1280.
* 			 (2) The min packet size must be bigger than 100.
*            (3) Use this function before RDT_Initialize().
*/
RDTAPI_API int32_t RDT_Set_MaxPacketDataSize(uint32_t nMaxSize);

#ifdef __cplusplus
}
#endif

#endif /* _RDTCOMMON_H_ */
