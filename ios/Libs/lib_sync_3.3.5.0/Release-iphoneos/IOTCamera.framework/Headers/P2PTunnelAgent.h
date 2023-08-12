/*! \file P2PTunnelAgent.h
This file describes P2PTunnel module APIs for agent.

\copyright Copyright (c) 2010 by Throughtek Co., Ltd. All Rights Reserved.
*/

#ifndef _P2PTUNNELAGENT_H_
#define _P2PTUNNELAGENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "P2PTunnelCommon.h"

/**
 * \details The prototype of authenticating connect informations, used by a tunnel agent
 *			to be notified when connection start.
 *
 * \param cszAccount [out] The account input by user
 * \param nAccountMaxLength [in] Max size of cszAccount
 * \param cszPassword [out] The password input by user
 * \param nPasswordMaxLength [in] Max size of cszPassword
 * \param pArg [in] Tunnel agent pass user data
 *
 * \attention Set empty string "" to cszPassword meas reject this tunnel connection
 */
typedef void (__stdcall *tunnelAgentAuthCB)(char *cszAccount, uint32_t nAccountMaxLength, char *cszPassword, uint32_t nPasswordMaxLength, const void *pArg);

/**
 * \brief Initialize P2PTunnel module in a tunnel agent
 *
 * \details This function is used by a tunnel agent to initialize P2PTunnel
 *			module and shall be called before any P2PTunnel module related
 *			function is invoked.
 *
 * \param nMaxConnection [in] Specify max number of tunnel agents that
 *				can connect to tunnel servers
 *
 * \return #TUNNEL_ER_NoERROR if initializing successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_ALREADY_INITIALIZED P2PTunnel module is already initialized
 *			- #TUNNEL_ER_FAIL_CREATE_THREAD Failed to create thread
 *			- #IOTC_ER_FAIL_RESOLVE_HOSTNAME Cannot resolve masters' host name
 *			- #IOTC_ER_ALREADY_INITIALIZED IOTC module is already initialized
 *			- #IOTC_ER_MASTER_TOO_FEW Two masters are required as parameters at minimum
 *			- #IOTC_ER_FAIL_CREATE_MUTEX Fails to create Mutexs
 *			- #IOTC_ER_FAIL_CREATE_THREAD Fails to create threads
 *			- #RDT_ER_ALREADY_INITIALIZED RDT module is already initialized
 *			- #RDT_ER_FAIL_CREATE_MUTEX Fails to create Mutexs
 *
 * \see P2PTunnelAgentDeInitialize()
 *
 * \attention This function can't be called simultaneously from multiple threads.
 */
TUNNEL_API int32_t P2PTunnelAgentInitialize(uint32_t nMaxConnection);

/**
 * \brief Deinitialize P2PTunnel module in a tunnel agent
 *
 * \details This function will deinitialize P2PTunnel module in a tunnel agent
 *
 * \return #TUNNEL_ER_NoERROR if deinitialize successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED the P2PTunnel module is not initialized yet.
 *
 * \see P2PTunnelAgentInitialize()
 *
 * \attention Must call P2PTunnelAgent_Disconnect() before calling this function,
 *				otherwise resource in P2PTunnel module will not be freed and connection
 *				will not be closed (the remote site will have connection timeout event
 *				eventually).
 *
 *\attention This function can't be called simultaneously from multiple threads.
 */
TUNNEL_API int32_t P2PTunnelAgentDeInitialize(void);

/**
 * \brief Used by an agent to get a free session ID.
 *
 * \datails This function is for an agent to get a free session ID used for a parameter of P2PTunnelAgent_Connect_Parallel_Ex().
 *
 * \return Tunnel Session ID if return value >= 0
 * \return Error code if return value < 0
 *                      - #TUNNEL_ER_NO_FREE_SESSION Current tunnel session are full.
 *
 */
TUNNEL_API int32_t P2PTunnelAgent_GetFreeSession(void);

/**
 * \brief Connect to a tunnel server
 *
 * \details This function used by a tunnel agent to connect the tunnel server
 *			with specified UID
 *
 * \param cszUID [in] The UID of that tunnel server to be connected
 * \param cpAuthData [in] Send authentication data to tunnel server for connection.
 * \param nAuthDataLength [in] The length of the byte buffer. It cannot be larger than
 *			#MAX_AUTH_DATA_LEN
 * \param pnErrFromDeviceCB [out] The reason why tunnel server rejects this connection.
 *			It's returned from tunnelSessionInfoCB of the tunnel server.
 *
 * \return Tunnel Session ID if return value >= 0
 * \return #TUNNEL_ER_NoERROR if connect successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED P2PModule has not been initialized in that tunnel agent
 *			- #TUNNEL_ER_AUTH_FAILED The tunnel agent failed to connect to tunnel server
 *					because authentication data is illegal.
 *			- #TUNNEL_ER_UID_UNLICENSE This UID is illegal or does not support P2PTunnel function
 *			- #TUNNEL_ER_UID_NO_PERMISSION This UID not support P2PModule and TCP relay function
 *			- #TUNNEL_ER_UID_NOT_SUPPORT_RELAY This UID can't setup connection through relay
 *			- #TUNNEL_ER_DEVICE_NOT_ONLINE The specified tunnel server does not login to IOTC server yet
 *			- #TUNNEL_ER_DEVICE_NOT_LISTENING The specified tunnel server is not listening for connection,
 *					it maybe busy at establishing connection with other tunnel agent
 *			- #TUNNEL_ER_NETWORK_UNREACHABLE Internet is not available or firewall blocks connection
 *			- #TUNNEL_ER_FAILED_SETUP_CONNECTION Can't connect to the tunnel server although it is online
 *					and listening for connection, it maybe caused by internet unstable situation
 *			- #TUNNEL_ER_HANDSHAKE_FAILED Create connection fail
 *			- #TUNNEL_ER_LOCAL_NOT_SUPPORT_DTLS Tunnel server just allow DTLS connection
 *
 */
TUNNEL_API_DEPRECATED int32_t P2PTunnelAgent_Connect(const char *cszUID, const void *cpAuthData, int32_t nAuthDataLength, int32_t *pnErrFromDeviceCB);

/**
 * \brief Connect to a tunnel server with DTLS mode
 *
 * \details This function used by a tunnel agent to connect the tunnel server
 *			with specified UID
 *
 * \param cszUID [in] The UID of that tunnel server to be connected
 * \param pfxTunnelAgentAuthFn [in] The function pointer of authenticate account function
 * \param pArg [in] User can give data pointer to pass to pfxTunnelAgentAuthFn when this
 *             call back function is triggered. Can be NULL.
 *
 * \return Tunnel Session ID if return value >= 0
 * \return #TUNNEL_ER_NoERROR if connect successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED P2PModule has not been initialized in that tunnel agent
 *			- #TUNNEL_ER_AUTH_FAILED The tunnel agent failed to connect to tunnel server
 *					because authentication data is illegal.
 *			- #TUNNEL_ER_UID_UNLICENSE This UID is illegal or does not support P2PTunnel function
 *			- #TUNNEL_ER_UID_NO_PERMISSION This UID not support P2PModule and TCP relay function
 *			- #TUNNEL_ER_UID_NOT_SUPPORT_RELAY This UID can't setup connection through relay
 *			- #TUNNEL_ER_DEVICE_NOT_ONLINE The specified tunnel server does not login to IOTC server yet
 *			- #TUNNEL_ER_DEVICE_NOT_LISTENING The specified tunnel server is not listening for connection,
 *					it maybe busy at establishing connection with other tunnel agent
 *			- #TUNNEL_ER_NETWORK_UNREACHABLE Internet is not available or firewall blocks connection
 *			- #TUNNEL_ER_FAILED_SETUP_CONNECTION Can't connect to the tunnel server although it is online
 *					and listening for connection, it maybe caused by internet unstable situation
 *			- #TUNNEL_ER_HANDSHAKE_FAILED Create connection fail
 *			- #TUNNEL_ER_REMOTE_NOT_SUPPORT_DTLS Remote not support DTLS
 *			- #TUNNEL_ER_EXCEED_MAX_SESSION The number of sessions exceeds a limited quantity.
 *
 */
TUNNEL_API int32_t P2PTunnelAgent_Connect_Ex(const char *cszUID, tunnelAgentAuthCB pfxTunnelAgentAuthFn, const void *pArg);

/**
 * \brief Use the existed IOTC session to request P2PTunnel connection
 *
 * \details In order to use the same iotc session with other modules, please make sure you
 *          use different channel id for each module, for example, you can use channel 0 for
 *          AV connections and channel 1 for P2PTunnel connections
 *
 * \param SID [in] Base on which IOTC session id you want to build P2PTunnel connection
 * \param CHID [in] Base on which IOTC channel id you want to build P2PTunnel connection
 * \param cpAuthData [in] Send authentication data to tunnel server for connection.
 * \param nAuthDataLength [in] The length of the byte buffer. It cannot be larger than
 *                      #MAX_AUTH_DATA_LEN
 * \param pnErrFromDeviceCB [out] The reason why tunnel server rejects this connection.
 *                      It's returned from tunnelSessionInfoCB of the tunnel server.
 *
 * \return Tunnel Session ID if return value >= 0
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED if P2PTunnel is not initialized
 *			- #TUNNEL_ER_INVALID_ARG if cpAuthData, nAuthDataLength is invalid or CHID is out of range
 *			- #TUNNEL_ER_CONNECTION_CANCELLED if connection is canceled
 *			- #TUNNEL_ER_FAIL_CREATE_THREAD if not be able to create internal threads
 *			- #TUNNEL_ER_OPERATION_IS_INVALID if P2PTunnelSetConnectionOption is not set as TUNNEL_CONNECT_MANUAL mode
 *                          or call this function with IOTC server
 *			- #TUNNEL_ER_INVALID_SID if IOTC session id is invalid
 *			- #TUNNEL_ER_HANDSHAKE_FAILED if P2PTunnel handshake failed
 *			- #TUNNEL_ER_LOCAL_NOT_SUPPORT_DTLS Tunnel server just allow DTLS connection
 *
 * \see P2PTunnelSetConnectionOption(), P2PTunnelServer_Listen()
 *
 * \attention Must be called after P2PTunnelSetConnectionOption is set as TUNNEL_CONNECT_MANUAL mode
 *
 */
TUNNEL_API_DEPRECATED int32_t P2PTunnelAgent_Attach_Connect(const int32_t SID, const int32_t CHID, const void *cpAuthData, int32_t nAuthDataLength, int32_t *pnErrFromDeviceCB);

/**
 * \brief Use the existed IOTC session to request P2PTunnel connection with DTLS mode
 *
 * \details In order to use the same iotc session with other modules, please make sure you
 *          use different channel id for each module, for example, you can use channel 0 for
 *          AV connections and channel 1 for P2PTunnel connections
 *
 * \param SID [in] Base on which IOTC session id you want to build P2PTunnel connection
 * \param CHID [in] Base on which IOTC channel id you want to build P2PTunnel connection
 * \param pfxTunnelAgentAuthFn [in] The function pointer of authenticate account function
 *                                  if IOTC session is crate by Nebula, this param can be NULL.
 * \param pArg [in] User can give data pointer to pass to pfxTunnelAgentAuthFn when this
 *             call back function is triggered. Can be NULL.
 *
 * \return Tunnel Session ID if return value >= 0
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_NOT_INITIALIZED if P2PTunnel is not initialized
 *			- #TUNNEL_ER_INVALID_ARG if cpAuthData, nAuthDataLength is invalid or CHID is out of range
 *			- #TUNNEL_ER_CONNECTION_CANCELLED if connection is canceled
 *			- #TUNNEL_ER_FAIL_CREATE_THREAD if not be able to create internal threads
 *			- #TUNNEL_ER_OPERATION_IS_INVALID if P2PTunnelSetConnectionOption is not set as TUNNEL_CONNECT_MANUAL mode
 *                          or call this function with IOTC server
 *			- #TUNNEL_ER_INVALID_SID if IOTC session id is invalid
 *			- #TUNNEL_ER_HANDSHAKE_FAILED if P2PTunnel handshake failed
 *			- #TUNNEL_ER_REMOTE_NOT_SUPPORT_DTLS Remote not support DTLS
 *
 * \see P2PTunnelSetConnectionOption(), P2PTunnelServer_Listen()
 *
 * \attention (1) Must be called after P2PTunnelSetConnectionOption is set as TUNNEL_CONNECT_MANUAL mode
 *            (2) If IOTC session is created by Nebula, pfxTunnelAgentAuthFn will NOT invoke when this API called.
 *
 */
TUNNEL_API int32_t P2PTunnelAgent_Attach_Connect_Ex(int32_t SID, int32_t CHID, tunnelAgentAuthCB pfxTunnelAgentAuthFn, const void *pArg);

/**
 * \brief Connect to a tunnel server and bind to a specified session ID.
 *
 * \details This function is for a tunnel agent to connect a device by specifying the UID
 *                      of that device, and bind to a free session ID from P2PTunnelAgent_GetFreeSession().
 *                      If connection is established with the help of IOTC servers, the TUNNEL_ER_NoERROR will
 *                      be returned in this function and then device and client can communicate for the other
 *                      later by using this tunnel session ID. If this function is called by multiple threads,
 *                      the connections will be processed concurrently.
 *
 * \param cszUID [in] The UID of that tunnel server to be connected
 * \param SID [in] The SID got from P2PTunnelAgent_GetFreeSession() the connection should bind to.
 * \param cpAuthData [in] Send authentication data to tunnel server for connection.
 * \param nAuthDataLength [in] The length of the byte buffer. It cannot be larger than
 *                      #MAX_AUTH_DATA_LEN
 * \param pnErrFromDeviceCB [out] The reason why tunnel server rejects this connection.
 *                      It's returned from tunnelSessionInfoCB of the tunnel server.
 *
 * \return Tunnel session ID if return value >= 0 and equal to the input parameter SID.
 * \return #TUNNEL_ER_NoERROR if connect successfully
 * \return Error code if return value < 0
 *                      - #TUNNEL_ER_NOT_INITIALIZED P2PModule has not been initialized in that tunnel agent
 *                      - #TUNNEL_ER_AUTH_FAILED The tunnel agent failed to connect to tunnel server
 *                                      because authentication data is illegal.
 *                      - #TUNNEL_ER_UID_UNLICENSE This UID is illegal or does not support P2PTunnel function
 *                      - #TUNNEL_ER_UID_NO_PERMISSION This UID not support P2PModule and TCP relay function
 *                      - #TUNNEL_ER_UID_NOT_SUPPORT_RELAY This UID can't setup connection through relay
 *                      - #TUNNEL_ER_DEVICE_NOT_ONLINE The specified tunnel server does not login to IOTC server yet
 *                      - #TUNNEL_ER_DEVICE_NOT_LISTENING The specified tunnel server is not listening for connection,
 *                                      it maybe busy at establishing connection with other tunnel agent
 *                      - #TUNNEL_ER_NETWORK_UNREACHABLE Internet is not available or firewall blocks connection
 *                      - #TUNNEL_ER_FAILED_SETUP_CONNECTION Can't connect to the tunnel server although it is online
 *                                      and listening for connection, it maybe caused by internet unstable situation
 *			- #TUNNEL_ER_LOCAL_NOT_SUPPORT_DTLS Tunnel server just allow DTLS connection
 *
 */
TUNNEL_API_DEPRECATED int32_t P2PTunnelAgent_Connect_Parallel(const char *cszUID, const int32_t SID, const void *cpAuthData, int32_t nAuthDataLength, int32_t *pnErrFromDeviceCB);

/**
 * \brief Connect to a tunnel server and bind to a specified session ID with DTLS mode.
 *
 * \details This function is for a tunnel agent to connect a device by specifying the UID
 *                      of that device, and bind to a free session ID from P2PTunnelAgent_GetFreeSession().
 *                      If connection is established with the help of IOTC servers, the TUNNEL_ER_NoERROR will
 *                      be returned in this function and then device and client can communicate for the other
 *                      later by using this tunnel session ID. If this function is called by multiple threads,
 *                      the connections will be processed concurrently.
 *
 * \param cszUID [in] The UID of that tunnel server to be connected
 * \param SID [in] The SID got from P2PTunnelAgent_GetFreeSession() the connection should bind to.
 * \param pfxTunnelAgentAuthFn [in] The function pointer of authenticate account function
 *                                  if IOTC session is crate by Nebula, this param can be NULL.
 * \param pArg [in] User can give data pointer to pass to pfxTunnelAgentAuthFn when this
 *             call back function is triggered. Can be NULL.
 *
 * \return Tunnel session ID if return value >= 0 and equal to the input parameter SID.
 * \return #TUNNEL_ER_NoERROR if connect successfully
 * \return Error code if return value < 0
 *                      - #TUNNEL_ER_NOT_INITIALIZED P2PModule has not been initialized in that tunnel agent
 *                      - #TUNNEL_ER_AUTH_FAILED The tunnel agent failed to connect to tunnel server
 *                                      because authentication data is illegal.
 *                      - #TUNNEL_ER_UID_UNLICENSE This UID is illegal or does not support P2PTunnel function
 *                      - #TUNNEL_ER_UID_NO_PERMISSION This UID not support P2PModule and TCP relay function
 *                      - #TUNNEL_ER_UID_NOT_SUPPORT_RELAY This UID can't setup connection through relay
 *                      - #TUNNEL_ER_DEVICE_NOT_ONLINE The specified tunnel server does not login to IOTC server yet
 *                      - #TUNNEL_ER_DEVICE_NOT_LISTENING The specified tunnel server is not listening for connection,
 *                                      it maybe busy at establishing connection with other tunnel agent
 *                      - #TUNNEL_ER_NETWORK_UNREACHABLE Internet is not available or firewall blocks connection
 *                      - #TUNNEL_ER_FAILED_SETUP_CONNECTION Can't connect to the tunnel server although it is online
 *                                      and listening for connection, it maybe caused by internet unstable situation
 *			            - #TUNNEL_ER_REMOTE_NOT_SUPPORT_DTLS Remote not support DTLS
 *
 * \attention If IOTC session is created by Nebula, pfxTunnelAgentAuthFn will NOT invoke when this API called.
 *
 */
TUNNEL_API int32_t P2PTunnelAgent_Connect_Parallel_Ex(const char *cszUID, int32_t SID, tunnelAgentAuthCB pfxTunnelAgentAuthFn, const void *pArg);

/**
 * \brief Disconnect to a tunnel server
 *
 * \details This function used by a tunnel agent to disconnect to a tunnel server
 *          gracefully
 *
 * \param nSessionID [in] Which session ID of the P2PTunnel session to be disconnect
 *
 * \return - #TUNNEL_ER_NoERROR if connect successfully
 *			- #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 */
TUNNEL_API int32_t P2PTunnelAgent_Disconnect(int32_t nSessionID);

/**
 * \brief Abort the connection with a tunnel server
 *
 * \details This function used by a tunnel agent to disconnect to a tunnel server
 *          directly
 *
 * \param nSessionID [in] Which session ID of the P2PTunnel session to be disconnect
 *
 * \return - #TUNNEL_ER_NoERROR if connect successfully
 *			- #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 */
TUNNEL_API int32_t P2PTunnelAgent_Abort(int32_t nSessionID);

/**
 * \brief Start port mapping service
 *
 * \details This function used by a tunnel agent to start port mapping service
 *			provided by P2PTunnel module. The tunnel agent specifies the local port
 *			in local host through which a tunnel is created with the remote port defined
 *			in the tunnel server.
 *
 * \param nSessionID [in] Which session ID of the P2PTunnel session to process the port mapping service
 * \param nLocalPort [in] The local port used to create a tunnel with the tunnel server
 * \param nRemotePort [in] The remote port defined in the tunnel server to create a tunnel
 *
 * \return The port mapping index if return value >= 0
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_EXCEED_MAX_SERVICE Exceed the max number of port mapping service
 *			- #TUNNEL_ER_BIND_LOCAL_SERVICE Failed to bind local port since it is used by the other services
 *			- #TUNNEL_ER_LISTEN_LOCAL_SERVICE Failed to listen local port since it is used by the other services
 *			- #TUNNEL_ER_OS_RESOURCE_LACK Failed to malloc memory
 *			- #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 */
TUNNEL_API int32_t P2PTunnelAgent_PortMapping(int32_t nSessionID, uint16_t nLocalPort, uint16_t nRemotePort);

/**
 * \brief Stop port mapping service
 *
 * \details This function used by a tunnel agent to stop port mapping service
 *			on a given port mapping index which is started by P2PTunnelAgent_PortMapping()
 *
 * \param nPortMappingIdx [in] The port mapping index started in P2PTunnelAgent_PortMapping()
 *
 * \attention If not call P2PTunnelAgent_StopPortMapping local port can't be used until OS release it.
 */
TUNNEL_API void P2PTunnelAgent_StopPortMapping(uint32_t nPortMappingIdx);

/**
 * \brief Stop port mapping service
 *
 * \details This function used by a tunnel agent to stop multiple port mapping service
 *			on an integer array set of given port mapping index which is started by P2PTunnelAgent_PortMapping()
 *
 * \param indexArray [in] An integer array of the port mapping index in P2PTunnelAgent_PortMapping()
 *        indexNum is the number of the port mapping index in indexArray
 *
 * \return Error code if return value < 0
 *          - #TUNNEL_ER_NoERROR if connect successfully
 *	        - #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 *
 * \attention If not call P2PTunnelAgent_StopPortMapping local port can't be used until OS release it.
 */
TUNNEL_API int32_t P2PTunnelAgent_StopPortMapping_byIndexArray(uint32_t *indexArray, uint32_t indexNum);

/**
 * \brief Used by a tunnel agent to get the tunnel status
 *
 * \details This function will set a callback function pointer in P2PTunnel
 *			module for a tunnel agent to get the tunnel status from given callback
 *			function. Whenever tunnel status changes, P2PTunnel module will invoke
 *			the given callback function to notify tunnel agent with corresponding
 *			status.
 *
 * \param pfxTunnelStatusFn [in] The function pointer to getting tunnel status function
 * \param pArg [in] User can give data pointer to pass to pfxSessionInfoFn when this
 *			call back function is triggered. Can be NULL.
 */
TUNNEL_API void P2PTunnelAgent_GetStatus(tunnelStatusCB pfxTunnelStatusFn, void *pArg);

/**
 * \brief It's to stop the progressing of connection.
 *
 * \details This API is for a client to stop connecting to a device.
 * 			We can use it to stop connecting when client blocks in P2PTunnelAgent_Connect_Ex().
 *
 * \param cszUID [in] The UID of that tunnel server
 *
 * \return 0 if success
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_AGENT_NOT_CONNECTING Tunnel Agent isn't connecting.
 *
 */
TUNNEL_API int32_t P2PTunnelAgent_Connect_Stop (const char* cszUID);

/**
 * \brief It's to stop the progressing of connection.
 *
 * \details This API is for a client to stop connecting to a device.
 *                      We can use it to stop connecting when client blocks in P2PTunnelAgent_Connect_Parallel_Ex().
 *
 * \param cszUID [in] The UID of that tunnel server
 * \param nSessionID [in] Session ID
 * \return 0 if success
 * \return Error code if return value < 0
 *                      - #TUNNEL_ER_AGENT_NOT_CONNECTING Tunnel Agent isn't connecting.
 *
 */
TUNNEL_API int32_t P2PTunnelAgent_Connect_Stop_Parallel(const char* cszUID, const int32_t nSessionID);

/**
 * \brief It's to stop the progressing of attach.
 *
 * \details This API is for a manually agnet to stop connecting to a device.
 *                      We can use it to stop connecting when client blocks in P2PTunnelAgent_Attach_Connect() or P2PTunnelAgent_Attach_Connect_Ex().
 *
 * \param nIOTCSessionID [in] Session ID
 * \param nIOTCChannelID [in] Channel ID
 * \return TUNNEL_ER_NoERROR if stop successfully
 * \return Error code if return value < 0
 *                      - #TUNNEL_ER_OPERATION_IS_INVALID if P2PTunnelSetConnectionOption is not set as TUNNEL_CONNECT_MANUAL mode
 *                          or call this function with IOTC server
 *                      - #TUNNEL_ER_INVALID_ARG The Channel ID is not in valid range.
 *                      - #TUNNEL_ER_INVALID_SID The invalid session ID.
 *                      - #TUNNEL_ER_AGENT_NOT_CONNECTING Tunnel Agent isn't connecting.
 *
 * \see P2PTunnelAgent_Attach_Connect(), P2PTunnelAgent_Attach_Connect_Ex()
 */
TUNNEL_API int32_t P2PTunnelAgent_Attach_Connect_Stop(int32_t nIOTCSessionID, int32_t nIOTCChannelID);

#ifdef __cplusplus
}
#endif

#endif /* _P2PTUNNELAGENT_H_ */
