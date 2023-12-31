/*! \file RDTClient.h
This file describes RDT module APIs for client.

\copyright Copyright (c) 2010 by Throughtek Co., Ltd. All Rights Reserved.
*/

#ifndef _RDTCLIENT_H_
#define _RDTCLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "RDTCommon.h"

/**
 * \details The prototype of authenticating connect informations, used by a RDT agent
 *			to be notified when connection start.
 *
 * \param cszAccount [out] The account input by user
 * \param nAccountMaxLength [in] Max size of cszAccount
 * \param cszPassword [out] The password input by user
 * \param nPasswordMaxLength [in] Max size of cszPassword
 * \param pArg [in] RDT agent pass user data
 *
 * \attention Set empty string "" to cszPassword meas reject this tunnel connection
 */
typedef void(__stdcall *rdtClientAuthCb)(char *cszAccount, uint32_t nAccountMaxLength, char *cszPassword, uint32_t nPasswordMaxLength, const void *pArg);

/**
 * \brief Create a RDT client
 *
 * \details This function will create a RDT client based on specified IOTC channel with DTLS
 *
 * \param nIOTCSessionID [in] The session ID of the IOTC session to create RDT channel
 * \param nIOTCChannelID [in] The channel ID of the IOTC channel to create RDT channel
 * \param pfxClientAuthFn [in] The function pointer of authenticate account function
 *                             if IOTC session is crate by Nebula, this param can be NULL.
 * \param pArg [in] User can give data pointer to pass to pfxClientAuthFn when this
 *             call back function is triggered. Can be NULL.
 * \param nTimeoutMs [in] The timeout for this function in unit of million-second.
 *			Specify it as 0 will make this function block forever until a RDT
 *			channel is successfully created or error happens
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
 *			- #RDT_ER_TIMEOUT The timeout specified by nTimeoutMs expires before
 *				RDT creation is performed completely
 *			- #RDT_ER_CHANNEL_OCCUPIED The specific IOTC session and channel ID not available,
 *				it means the resource not release yet. If caused by RDT_Abort() called must wait
 *				a minute for the resource release automatically.
 *			- #RDT_ER_REMOTE_EXIT Remote site exit this RDT channel connection
 *			- #RDT_ER_LOCAL_EXIT Force return after RDT_Create_Exit()
 *			- #RDT_ER_CREATE_DTLS_FAIL Create DTLS connection error
 *			- #RDT_ER_OPERATION_IS_INVALID RDT client create by IOTC server
 *			- #RDT_ER_REMOTE_NOT_SUPPORT_DTLS Remote not support DTLS
 *			- #RDT_ER_INVALID_ARG Invalid Argument
 *
 * \see RDT_Destroy() and RDT_Abort() RDT_Create_Exit()
 *
 * \attention (1) The IOTC channel of specified channel ID will be turned on automatically
 *				by RDT_Client_Create()
 *            (2) If IOTC session is created by Nebula, pfxServerAuthFn will NOT invoke when
 *              this API called.
 *
 */
RDTAPI_API int32_t RDT_Client_Create(int32_t nIOTCSessionID, uint8_t nIOTCChannelID, rdtClientAuthCb pfxClientAuthFn, const void *pArg, int32_t nTimeoutMs);

#ifdef __cplusplus
}
#endif

#endif /* _RDTCLIENT_H_ */
