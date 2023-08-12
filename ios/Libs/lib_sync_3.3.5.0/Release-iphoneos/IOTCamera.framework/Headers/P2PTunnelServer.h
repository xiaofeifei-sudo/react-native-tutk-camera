/*! \file P2PTunnelServer.h
This file describes P2PTunnel module APIs for agent.

\copyright Copyright (c) 2010 by Throughtek Co., Ltd. All Rights Reserved.
*/

#ifndef _P2PTUNNELSERVER_H_
#define _P2PTUNNELSERVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "P2PTunnelCommon.h"

/**
 * \details P2PTunnel session info, containing all the information when a P2PTunnel session is
 *  established between a tunnel server and a tunnel agent. Users can get this information
 *  through use P2PTunnelServer_GetSessionInfo() to register a call back function tunnelSessionInfoCB
 */
typedef struct st_P2PTunnelSessionInfo {
    int32_t nSID; //!< P2PTunnel session index
    uint8_t nMode; //!< 0: P2P mode, 1: Relay mode, 2: LAN mode
    uint8_t nNatType; //!< The remote NAT type
    char szRemoteIP[16]; //!< The IP address of remote site used during this P2PTunnel session
    uint16_t nRemotePort; //!< The port number of remote site used during this P2PTunnel session
    uint32_t nVersion; //!< The remote P2PTunnel API version.
    int32_t nAuthDataLen; //!< How many byte of the authentication data.
    void *pAuthData; //!< The authentication data buffer, it will be freed by API automatically.
} sP2PTunnelSessionInfo;

/**
 * \details P2PTunnel session info, containing all the information when a P2PTunnel session is
 *  established between a tunnel server and a tunnel agent. Users can get this information
 *  through use P2PTunnelServer_Start_Ex() to register a call back function tunnelSessionInfoExCB
 */
typedef struct st_P2PTunnelSessionInfoEx {
    int32_t nSID;         //!< P2PTunnel session index
    uint8_t nMode;        //!< 0: P2P mode, 1: Relay mode, 2: LAN mode
    uint8_t nNatType;     //!< The remote NAT type
    char szRemoteIP[16];  //!< The IP address of remote site used during this P2PTunnel session
    uint16_t nRemotePort; //!< The port number of remote site used during this P2PTunnel session
    uint32_t nVersion;    //!< The remote P2PTunnel API version.
} sP2PTunnelSessionInfoEx;

/**
 * \details The prototype of getting tunnel session information function,
 * 			used by a tunnel server to be notified after tunnel session is established.
 *
 * \param sSessionInfo [out] About remote session information
 * \param pArg [out] Tunnel server pass user data
 *
 *
 * \return User define value.
 *			- if value == 0, it means a tunnel server passes tunnel agent authentication
 *			- if value < 0, it means a tunnel server rejects tunnel agent authentication
 *				and P2PTunnel module will send the value back to tunnel agent
 *				for tell the reason why this tunnel server rejects connection.
 *
 */
typedef int32_t (__stdcall *tunnelSessionInfoCB)(sP2PTunnelSessionInfo *sSessionInfo, void *pArg);

/**
 * \details The prototype of getting tunnel session information function,
 * 			used by a tunnel server to be notified after tunnel session is established.
 *
 * \param sSessionInfo [out] About remote session information
 * \param pArg [out] Tunnel server pass user data
 *
 */
typedef void (__stdcall *tunnelSessionInfoExCB)(sP2PTunnelSessionInfoEx *sSessionInfo, const void *pArg);

/**
 * \details The prototype of authenticating connect informations, used by a tunnel server
 *			to be notified when connection start.
 *
 * \param cszAccount [in] Account from tunnel agent
 * \param cszPassword [out] The password input by user
 * \param nPasswordMaxLength [in] Max size of cszPassword
 * \param pArg [in] Tunnel server pass user data
 *
 * \attention Set empty string "" to cszPassword meas reject this tunnel connection
 */
typedef void (__stdcall *tunnelServerAuthCB)(const char *cszAccount, char *cszPassword, uint32_t nPasswordMaxLength, const void *pArg);

/**
 * \brief Initialize P2PTunnel module in a tunnel server
 *
 * \details This function is used by a tunnel server to initialize P2PTunnel
 *			module and shall be called before any P2PTunnel module related
 *			function is invoked.
 *
 * \param nMaxAgentConnection [in] Specify max number of tunnel agents that
 *				can connect to this tunnel server
 *
 * \return #TUNNEL_ER_NoERROR if initializing successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_ALREADY_INITIALIZED P2PTunnel module is already initialized
 *			- #IOTC_ER_FAIL_RESOLVE_HOSTNAME Cannot resolve masters' host name
 *			- #IOTC_ER_ALREADY_INITIALIZED IOTC module is already initialized
 *			- #IOTC_ER_MASTER_TOO_FEW Two masters are required as parameters at minimum
 *			- #IOTC_ER_FAIL_CREATE_MUTEX Fails to create Mutexs
 *			- #IOTC_ER_FAIL_CREATE_THREAD Fails to create threads
 *			- #RDT_ER_ALREADY_INITIALIZED RDT module is already initialized
 *			- #RDT_ER_FAIL_CREATE_MUTEX Fails to create Mutexs
 *			- #TUTK_ER_NO_LICENSE_KEY Need to call TUTK_SDK_Set_License_Key() before all module start/initialize.
 *
 * \see P2PTunnelServerDeInitialize(), TUTK_SDK_Set_License_Key()
 *
 * \attention This function can't be called simultaneously from multiple threads.
 */
TUNNEL_API int32_t P2PTunnelServerInitialize(uint32_t nMaxAgentConnection);

/**
 * \brief Deinitialize P2PTunnel module in a tunnel server
 *
 * \details This function will deinitialize P2PTunnel module in a tunnel server
 *
 * \return #TUNNEL_ER_NoERROR if deinitialize successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED the P2PTunnel module is not initialized yet.
 *
 * \see P2PTunnelServerInitialize()
 *
 * \attention Must call P2PTunnelServer_Stop() before calling this function,
 *	 		otherwise resource in P2PTunnel module will not be freed.
 *
 * \attention This function can't be called simultaneously from multiple threads.
 */
TUNNEL_API int32_t P2PTunnelServerDeInitialize(void);

/**
 * \brief Use the existed iotc session to listen incoming P2PTunnel connection
 *
 * \details In order to use the same iotc session with other modules, please make sure you
 *          use different channel id for each module, for example, you can use channel 0 for
 *          AV connections and channel 1 for P2PTunnel connections
 *
 * \param SID [in] Base on which IOTC session id you want to build P2PTunnel connection
 * \param CHID [in] Base on which IOTC channel id you want to build P2PTunnel connection
 *
 * \return #TUNNEL_ER_NoERROR if deinitialize successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_INVALID_ARG if the channel id is out of range
 *			- #TUNNEL_ER_OPERATION_IS_INVALID if P2PTunnelSetConnectionOption is not set as TUNNEL_CONNECT_MANUAL mode and call P2PTunnelServer_Start_Ex
 *                          or call this function with IOTC client
 *			- #TUNNEL_ER_INVALID_SID if IOTC session id is invalid
 *			- #TUNNEL_ER_HANDSHAKE_FAILED if P2PTunnel handshake failed
 *			- #TUNNEL_ER_REMOTE_NOT_SUPPORT_DTLS Remote not support DTLS
 *
 * \see P2PTunnelSetConnectionOption(), P2PTunnelAgent_Attach_Connect()
 *
 * \attention (1) Must be called after P2PTunnelSetConnectionOption is set as TUNNEL_CONNECT_MANUAL mode
 *            (2) Must be called after P2PTunnelServer_Start_Ex
 *
 */
TUNNEL_API int32_t P2PTunnelServer_Listen(const int32_t SID, const int32_t CHID);

/**
 * \brief Start a tunnel server
 *
 * \details This function will start a tunnel server with given UID
 *
 * \param cszUID [in] The UID of that tunnel server
 *
 * \return #TUNNEL_ER_NoERROR if start successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED P2PModule has not been initialized in that tunnel server
 *			- #TUNNEL_ER_FAIL_CREATE_THREAD Failed to create thread
 *			- #TUNNEL_ER_UID_NO_PERMISSION This UID not support P2PModule and TCP relay function
 *			- #TUNNEL_ER_UID_UNLICENSE This UID is not licensed or expired
 */
TUNNEL_API_DEPRECATED int32_t P2PTunnelServer_Start(const char *cszUID);

/**
 * \brief Start a tunnel server with DTLS mode
 *
 * \details This function will start a tunnel server with given UID
 *
 * \param cszUID [in] The UID of that tunnel server
 * \param pfxTunnelServerAuthFn [in] The function pointer of authenticate account function
 * \param pfxSessionInfoExFn [in]  The function pointer to get tunnel session information function. Can be NULL.
 * \param pArg [in] User can give data pointer to pass to pfxTunnelServerAuthFn and pfxSessionInfoExFn when this
 *             call back function is triggered. Can be NULL.
 *
 * \return #TUNNEL_ER_NoERROR if start successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED P2PModule has not been initialized in that tunnel server
 *			- #TUNNEL_ER_FAIL_CREATE_THREAD Failed to create thread
 *			- #TUNNEL_ER_UID_NO_PERMISSION This UID not support P2PModule and TCP relay function
 *			- #TUNNEL_ER_UID_UNLICENSE This UID is not licensed or expired
 */
TUNNEL_API int32_t P2PTunnelServer_Start_Ex(const char *cszUID, tunnelServerAuthCB pfxTunnelServerAuthFn, tunnelSessionInfoExCB pfxSessionInfoExFn, const void *pArg);

/**
 * \brief Used by a tunnel server to get the tunnel status
 *
 * \details This function will set a callback function pointer in P2PTunnel
 *			module for a tunnel server to get the tunnel status from given callback
 *			function. Whenever tunnel status changes, P2PTunnel module will invoke
 *			the given callback function to notify tunnel server with corresponding
 *			status.
 *
 * \param pfxTunnelStatusFn [in] The function pointer to get tunnel status function
 * \param pArg [in] User can give data pointer to pass to pfxSessionInfoFn when this
 *			call back function is triggered. Can be NULL.
 */
TUNNEL_API void P2PTunnelServer_GetStatus(tunnelStatusCB pfxTunnelStatusFn, void *pArg);

/**
 * \brief Used by a tunnel server to get the tunnel session information
 *
 * \details This function will set a callback function pointer in P2PTunnel
 *			module for a tunnel server to get the tunnel session information from
 *			given callback function. Whenever tunnel agent try to establish session with tunnel server
 *			successfully, P2PTunnel module will invoke the given callback function to notify
 *			tunnel server and pass information through sP2PTunnelSessionInfo data struct.
 *
 * \param pfxSessionInfoFn [in] The function pointer to get tunnel session information function
 * \param pArg [in] User can give data pointer to pass to pfxSessionInfoFn when this
 *			call back function is triggered. Can be NULL.
 *
 * \return #TUNNEL_ER_NoERROR if register successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_AGENT_NOT_SUPPORT Tunnel agent not support this function call
 */
TUNNEL_API_DEPRECATED int32_t P2PTunnelServer_GetSessionInfo(tunnelSessionInfoCB pfxSessionInfoFn, void *pArg);

/**
 * \brief Stop a tunnel server
 *
 * \details This function will stop a tunnel server
 *
 */
TUNNEL_API void P2PTunnelServer_Stop(void);

/**
 * \brief Used by a tunnel server to disconnect a tunnel session
 *
 * \details This function will disconnect a tunnel session anytime after tunnel session
 *			established and it can be called anywhere.
 *
 * \param nSessionID [in] Which session ID of the P2PTunnel session established
 *
 * \return #TUNNEL_ER_NoERROR if disconnect P2PTunnel session successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_AGENT_NOT_SUPPORT Tunnel agent not support this function call
 *			- #TUNNEL_ER_INVALID_SID The session ID already disconnected or not yet established
 *			- #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 */
TUNNEL_API int32_t P2PTunnelServer_Disconnect(int32_t nSessionID);

#ifdef __cplusplus
}
#endif

#endif /* _P2PTUNNELSERVER_H_ */
