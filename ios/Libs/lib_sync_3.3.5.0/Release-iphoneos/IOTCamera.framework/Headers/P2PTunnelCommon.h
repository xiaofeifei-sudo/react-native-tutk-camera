/*! \file P2PTunnelCommon.h
This file describes common P2PTunnel module APIs of server and agent.

* \attention P2PTunnel module can't be used with IOTC and RDT module at the same process.

\copyright Copyright (c) 2012 by Throughtek Co., Ltd. All Rights Reserved.
*/

#ifndef _P2PTUNNELCOMMON_H_
#define _P2PTUNNELCOMMON_H_


#include "TUTKGlobalAPIs.h"


/* ============================================================================
 * Platform Dependant Macro Definition
 * ============================================================================
 */

#ifdef _WIN32
    #ifdef IOTC_STATIC_LIB
        #define TUNNEL_API
    #elif defined P2PAPI_EXPORTS
        #define TUNNEL_API __declspec(dllexport)
    #else
        #define TUNNEL_API __declspec(dllimport)
    #endif
#else
    #define TUNNEL_API
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define TUNNEL_API_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
    #ifdef IOTC_STATIC_LIB
        #define TUNNEL_API_DEPRECATED __declspec(deprecated)
    #elif defined P2PAPI_EXPORTS
        #define TUNNEL_API_DEPRECATED __declspec(deprecated, dllexport)
    #else
        #define TUNNEL_API_DEPRECATED __declspec(deprecated, dllimport)
    #endif
#else
    #define TUNNEL_API_DEPRECATED
#endif

#ifndef _WIN32
    #define __stdcall
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* ============================================================================
 * Generic Macro Definition
 * ============================================================================
 */

/** The maximum number of port mapping service in P2PTunnel module */
#define 	TUNNEL_MAX_PORT_MAPPING_SERVICE_NUMBER 			256

/** The maximum size, in byte, of the authentication data used in P2PTunnelAgent_Connect() */
#define		MAX_AUTH_DATA_LEN		1000

/* ============================================================================
 * Error Code Declaration
 * ============================================================================
 */

/** The function is performed successfully. */
#define		TUNNEL_ER_NoERROR								0

/** P2PTunnel module is not initialized yet. Please use P2PTunnelServerInitialize() or
 * P2PTunnelAgentInitialize() for initialization. */
#define		TUNNEL_ER_NOT_INITIALIZED					-30000

/** The number of P2PTunnel port mapping service has reached maximum.
 * The maximum number of P2PTunnel port mapping service is determined by
 * #TUNNEL_MAX_PORT_MAPPING_SERVICE_NUMBER */
#define		TUNNEL_ER_EXCEED_MAX_SERVICE				-30001

/** Failed to start port mapping when binding because local port had been used by
 * the other service in agent side */
#define		TUNNEL_ER_BIND_LOCAL_SERVICE				-30002

/** Failed to start port mapping when listening because local port has been used
 * by the other service in agent side */
#define		TUNNEL_ER_LISTEN_LOCAL_SERVICE				-30003

/** P2PTunnel module fails to create threads. Please check if OS has ability
 * to create threads for P2PTunnel module. */
#define		TUNNEL_ER_FAIL_CREATE_THREAD				-30004

/** Tunnel agent has already connected to a tunnel server, therefore, it failed
 * connect to another tunnel server */
#define		TUNNEL_ER_ALREADY_CONNECTED					-30005

/** The tunnel between tunnel agent and tunnel server has been disconnected.
 * Used in tunnel status callback function for notifying tunnel connection status */
#define		TUNNEL_ER_DISCONNECTED				  		-30006

/** The P2PTunnel module has been initialized in a tunnel server or a tunnel agent */
#define		TUNNEL_ER_ALREADY_INITIALIZED				-30007

/** Failed to connect to tunnel server because authentication data is wrong. */
#define		TUNNEL_ER_AUTH_FAILED						-30008

/** Authentication data length exceed #MAX_AUTH_DATA_LEN. */
#define		TUNNEL_ER_EXCEED_MAX_LEN					-30009

/** The specified P2PTunnel session ID is not valid */
#define		TUNNEL_ER_INVALID_SID						-30010

/** This UID is illegal. */
#define		TUNNEL_ER_UID_UNLICENSE						-30011

/** The specified device does not support advance function
 *(TCP relay and P2PTunnel module) */
#define		TUNNEL_ER_UID_NO_PERMISSION					-30012

/** This UID can't setup connection through relay. */
#define		TUNNEL_ER_UID_NOT_SUPPORT_RELAY				-30013

/** Tunnel server not login to IOTC server. */
#define		TUNNEL_ER_DEVICE_NOT_ONLINE					-30014

/** Tunner server is not listening for connections. */
#define		TUNNEL_ER_DEVICE_NOT_LISTENING				-30015

/** Internet not available or firewall block. */
#define		TUNNEL_ER_NETWORK_UNREACHABLE				-30016

/** Tunnel agent failed to connect to tunnel server maybe network unstable. */
#define		TUNNEL_ER_FAILED_SETUP_CONNECTION			-30017

/** Tunnel server failed to login to IOTC Server but still can be connected by tunnel agent on LAN. */
#define		TUNNEL_ER_LOGIN_FAILED						-30018

/** Notify tunnel server session connection alreay reached maximum through tunnelStatusCB,
* can't be connected anymore until anyone session release. */
#define		TUNNEL_ER_EXCEED_MAX_SESSION				-30019

/** Tunnel agent can't call P2PTunnelServer_GetSessionInfo() */
#define		TUNNEL_ER_AGENT_NOT_SUPPORT					-30020

/** The arguments passed to a function is invalid. */
#define		TUNNEL_ER_INVALID_ARG                       -30021

/** OS resource not enough to malloc memory or open socket. */
#define		TUNNEL_ER_OS_RESOURCE_LACK                  -30022

/** Tunnel Agent isn't connecting. */
#define		TUNNEL_ER_AGENT_NOT_CONNECTING              -30023

/** Unable to get free session.*/
#define     TUNNEL_ER_NO_FREE_SESSION                   -30024

/** Connection cancelled*/
#define     TUNNEL_ER_CONNECTION_CANCELLED              -30025

/** The API operation is invalid*/
#define     TUNNEL_ER_OPERATION_IS_INVALID              -30026

/** P2PTunnel handshake failed. */
#define     TUNNEL_ER_HANDSHAKE_FAILED              	-30027

/** Remote P2PTunnel not support DTLS*/
#define     TUNNEL_ER_REMOTE_NOT_SUPPORT_DTLS           -30028

/** Remote P2PTunnel need connect with DTLS*/
#define     TUNNEL_ER_LOCAL_NOT_SUPPORT_DTLS            -30029

/** API timeout*/
#define     TUNNEL_ER_TIMEOUT                           -30030

#define     TUNNEL_ER_UNDEFINED              			-31000

/** The remote site already closes the IOTC session.
 * Please call IOTC_Session_Close() to release local IOTC session resource */
#define     TUNNEL_ER_SESSION_CLOSE_BY_REMOTE       -30031

/** This IOTC session is disconnected because remote site has no any response
 * after a specified timeout expires. */
#define     TUNNEL_ER_REMOTE_TIMEOUT_DISCONNECT     -30032


/* ============================================================================
 * Enumeration Declaration
 * ============================================================================
 */

typedef enum {
    TUNNEL_CONNECT_AUTO = 0, //!< Create tunnel connection by SDK inner conenction process
    TUNNEL_CONNECT_MANUAL = 1, //!< Create tunnel connection with user specified IOTC session ID and channel ID
    TUNNEL_CONNECT_COUNT,
} P2PTunnelConnectionType;


/* ============================================================================
 * Type Definition
 * ============================================================================
 */

/**
 * \details The prototype of getting tunnel status function, used by a tunnel server
 *			or tunnel agent to be notified if tunnel status is changed.
 *
 * \param nErrorCode [out]
 *			- #TUNNEL_ER_DISCONNECTED The tunnel between tunnel agent and tunnel server
 *				has been disconnected.
 * \param nSessionID [in] Which session ID of the P2PTunnel session disconnected
 * \param pArg [out] Tunnel server or agent pass user data
 *
 */
typedef void (__stdcall *tunnelStatusCB)(int32_t nErrorCode, int32_t nSessionID, void *pArg);

/* ============================================================================
 * Function Declaration
 * ============================================================================
 */


/**
 * \brief Get the version of P2PTunnel module
 *
 * \details This function returns the version of P2PTunnel module.
 *
 * \return The version of P2PTunnel module from high byte to low byte, for example,
 *			0x01020304 means the version is 1.2.3.4
 */
TUNNEL_API_DEPRECATED int32_t P2PTunnel_Version(void);

/**
 * \brief Get the version of P2PTunnel module
 *
 * \details This function returns the version of P2PTunnel module.
 *
 */
TUNNEL_API const char* P2PTunnel_Version_String(void);

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
TUNNEL_API void P2PTunnelAgent_Set_Log_Path(const char *path, int32_t nMaxSize);

/**
 * \brief Set Attribute of log file
 *
 * \param logAttr [in] See #LogAttr
 *
 * \return #RDT_ER_NoERROR on success.
 * \return The value < 0
 *			- #RDT_ER_INVALID_ARG   Invalid input argument.
 */
TUNNEL_API int32_t P2PTunnel_Set_Log_Attr(LogAttr logAttr);

/**
 * \brief Setup the connection mode of P2PTunnel
 *
 * \details Use TUNNEL_CONNECT_MANUAL mode if you need share IOTC session with other modules,
 *          like AV or RDT. Otherwize there is no need to call this API.
 *
 * \return #TUNNEL_ER_NoERROR if setup successfully
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_INVALID_ARG the connection type is not recognized
 *
 * \see P2PTunnelServer_Listen(), P2PTunnelAgent_Attach_Connect_Ex()
 *
 * \attention Must be called before P2PTunnelServer_Listen and P2PTunnelAgent_Attach_Connect_Ex
 *
 */
TUNNEL_API int32_t P2PTunnelSetConnectionOption(P2PTunnelConnectionType type);

/**
 * \brief Get last IO time of SID
 *
 * \details Get last IO time of SID even if the connection is closed.
 *
 * \param nSessionID [in] Session ID
 *
 * \return POSIX time of last IO if return value > 0
 * \return 0 if no connection ever established on this SID
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_INVALID_SID The session ID already disconnected or not yet established
 *			- #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 *
 */
TUNNEL_API int32_t P2PTunnel_LastIOTime(int32_t nSessionID);

/**
 * \brief Set P2PTunnel buffer size
 *
 * \details Set P2PTunnel buffer size, larger buffer leads more maximum throughput
 *
 * \param nSessionID [in] Session ID
 * \param nSize [in] Buffer size in Bytes
 *
 * \return 0 if success
 * \return Error code if return value < 0
 *			- #TUNNEL_ER_INVALID_SID The session ID already disconnected or not yet established
 *			- #TUNNEL_ER_INVALID_ARG The session ID is not in valid range.
 *
 */
TUNNEL_API int32_t P2PTunnel_SetBufSize(int32_t nSessionID, int32_t nSize);

#ifdef __cplusplus
}
#endif

#endif /* _P2PTUNNELCOMMON_H_ */
