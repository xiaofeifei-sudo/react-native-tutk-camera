#ifndef _Nebula_Error_H_
#define _Nebula_Error_H_


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */



/** The function is performed successfully. */
#define     NEBULA_ER_NoERROR                            0

/** Nebula module has not been initialized */
#define     NEBULA_ER_NOT_INITIALIZE                    -40000

/** The specified timeout has expired during some operation */
#define     NEBULA_ER_TIMEOUT                           -40001

/** The passed-in arguments for the function are incorrect */
#define     NEBULA_ER_INVALID_ARG                       -40002

/** The passed-in UDID for the function is incorrect */
#define     NEBULA_ER_INVALID_UDID                      -40003

/** An error occurred during the http connection */
#define     NEBULA_ER_HTTP_ERROR                        -40004

/** Failed to create threads. Please check if OS has ability to create threads */
#define     NEBULA_ER_FAIL_CREATE_THREAD                -40005

/** Insufficient memory for allocation */
#define     NEBULA_ER_MEM_INSUFFICIENT                  -40006

/** Failed to login to bridge server */
#define     NEBULA_ER_BRIDGE_SERVER_LOGIN_FAIL          -40007

/** Nebula module has some resource allocating problem.*/
#define     NEBULA_ER_RESOURCE_ERROR                    -40008

/** Failed to login to binding server */
#define     NEBULA_ER_BIND_SERVER_LOGIN_FAIL            -40009

/** The passed-in buffer size is insufficient for the device token */
#define     NEBULA_ER_TOKEN_BUF_SIZE_INSUFFICIENT       -40010

/** Device can not get rental UID */
#define     NEBULA_ER_RENT_UID_FAILED                   -40011

/** The token for device to rent UID is invalid */
#define     NEBULA_ER_INVALID_TOKEN                     -40012

/** The validity period of token for device to rent UID is expired */
#define     NEBULA_ER_TOKEN_EXPIRED                     -40013

/** The passed-in command is not defined */
#define     NEBULA_ER_UNKNOWN_COMMAND                   -40014

/** The http connection timeout */
#define     NEBULA_ER_HTTP_TIMEOUT                      -40015

/** Device not login to bridge server */
#define     NEBULA_ER_BRIDGE_SERVER_NOT_LOGIN           -40016

/** Client not bind to device */
#define     NEBULA_ER_CLIENT_NOT_BIND_TO_DEVICE         -40017

/** Unknow status */
#define     NEBULA_ER_UNKNOW_STATUS                     -40018

/** Device is online */
#define     NEBULA_ER_DEVICE_ONLINE                     -40019

/** Device is offline */
#define     NEBULA_ER_DEVICE_OFFLINE                    -40020

/** Device is in sleep mode */
#define     NEBULA_ER_DEVICE_SLEEPING                   -40021

/** Try to awake the device */
#define     NEBULA_ER_DEVICE_AWAKENING                  -40022

/** Client send command function already in progress */
//#define     NEBULA_ER_CLIENT_COMMAND_IN_PROGRESS        -40023

/** The passed-in pin code is invalid */
#define     NEBULA_ER_INVALID_PIN_CODE                  -40024

/** The passed-in realm is invalid */
#define     NEBULA_ER_INVALID_REALM                     -40025

/** No notification settings */
#define     NEBULA_ER_NO_NOTIFICATION_LIST              -40026

/** Device login already in progress */
#define     NEBULA_ER_LOGIN_ALREADY_CALLED              -40027

/** Connection refused because of the device is not login to server */
#define     NEBULA_ER_CONNECT_REFUSED                   -40028

/** The device blocking API is terminated by the given abort flag */
#define     NEBULA_ER_DEVICE_FORCE_STOP                 -40029

/** The client blocking API is terminated by the given abort flag */
#define     NEBULA_ER_CLIENT_FORCE_STOP                 -40030

/** The passed-in psk is invalid */
#define     NEBULA_ER_INVALID_PSK                       -40031

/** Nebula module is already initialized. It is not necessary to re-initialize */
#define     NEBULA_ER_ALREADY_INITIALIZED               -40032

/** The passed-in SECRETID is invalid */
#define     NEBULA_ER_INVALID_SECRETID                  -40033

/** Duplicate value */
#define     NEBULA_ER_DUPLICATE                         -40034

/** No such entry */
#define     NEBULA_ER_NO_SUCH_ENTRY                     -40035

/** The blocking API is terminated by the given abort flag */
#define     NEBULA_ER_FORCE_STOP                        -40036

/** UDID of the node is invalid */
#define     NEBULA_ER_INVALID_NODE                      -40037

/** Syntax error */
#define     NEBULA_ER_SYNTAX_ERROR                      -40038

/** Device failed to IOTC login */
#define     NEBULA_ER_IOTC_LOGIN_ERROR                  -40039

/** Try again */
#define     NEBULA_ER_RETRY                             -40040

/** Not support */
#define     NEBULA_ER_NOT_SUPPORT                       -40041

/** An error occurred during the curl connection */
#define     NEBULA_ER_CURL_ERROR                        -40042

/** Nebula Server not in service */
#define     NEBULA_ER_SERVICE_UNAVAILABLE               -40043

/** Buffer size too small */
#define     NEBULA_ER_EXCEED_BUFFER_SIZE                -41001

/** Unknow message */
#define     NEBULA_ER_UNKNOW_MESSAGE                    -41002

/** Message type and length not match */
#define     NEBULA_ER_MESSAGE_CHECK_FAIL                -41003

/** Nebula Deivce not start */
#define     NEBULA_ER_BLE_DEVICE_NOT_READY              -41007

/** Nebula Deivce callback function is NULL */
#define     NEBULA_ER_BLE_CALLBACK_IS_NULL              -41008

/** Unknow UUID */
#define     NEBULA_ER_BLE_UNKNOW_UUID                   -41009

/** BLE service is still woring */
#define     NEBULA_ER_BLE_SERVICE_NOT_STOP              -41010

/** Unknow status */
#define     NEBULA_ER_BLE_UNKNOW_STATUS                 -41011


/** An error occurred while creating socket*/
#define    NEBULA_ER_SOCKET_CREATE_FAIL                 -42001

/** An error occurred while creating socket*/
#define    NEBULA_ER_SOCKET_ERROR                       -42002

/** TCP connection not created yet*/
#define    NEBULA_ER_TCP_CONNECTION_NOT_CREATE          -42003

/** There already a TCP connection created*/
#define    NEBULA_ER_TCP_ALREADY_CONNECTED              -42004

/** JSON object is not this type*/
#define    NEBULA_ER_JSON_OBJ_TYPE_ERROR                -43001

/** JSON object add data error*/
#define    NEBULA_ER_JSON_OBJ_ADD_ERROR                 -43002

/** object is not exist in JSON*/
#define    NEBULA_ER_JSON_OBJ_NOT_EXIST                 -43003

/** JSON array operate error*/
#define    NEBULA_ER_JSON_OBJ_ARRAY_ERROR               -43004


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _Nebula_Error_H_ */
