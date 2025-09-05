ifndef __RPCASYNC_H__
define __RPCASYNC_H__
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif
ifdef __RPC_WIN64__
.pragma pack(push, 8)
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifdef _KRPCENV_
include ntddk.inc
endif

if defined(RPC_NO_WINDOWS_H) or defined(_KRPCENV_)
include windef.inc
endif

define RPC_ASYNC_VERSION_1_0     sizeof(RPC_ASYNC_STATE)

.enum RPC_NOTIFICATION_TYPES {
    RpcNotificationTypeNone,
    RpcNotificationTypeEvent,
if not defined(_KRPCENV_)
    RpcNotificationTypeApc,
    RpcNotificationTypeIoc,
    RpcNotificationTypeHwnd,
endif
    RpcNotificationTypeCallback
    }

if (NTDDI_VERSION ge NTDDI_VISTA)
.enum RPC_ASYNC_EVENT {
    RpcCallComplete,
    RpcSendComplete,
    RpcReceiveComplete,
    RpcClientDisconnect,
    RpcClientCancel
    }
else
.enum RPC_ASYNC_EVENT {
    RpcCallComplete,
    RpcSendComplete,
    RpcReceiveComplete,
    RpcClientDisconnect
    }
endif

CALLBACK(RPCNOTIFICATION_ROUTINE, :ptr, :ptr, :RPC_ASYNC_EVENT)
PFN_RPCNOTIFICATION_ROUTINE typedef ptr RPCNOTIFICATION_ROUTINE

RPC_ASYNC_NOTIFICATION_INFO union
ifndef _KRPCENV_
struct APC
 NotificationRoutine    PFN_RPCNOTIFICATION_ROUTINE ?
 hThread                HANDLE ?
ends
if not defined(RPC_NO_WINDOWS_H) or defined(_WINBASE_)
struct IOC
 hIOPort                HANDLE ?
 dwNumberOfBytesTransferred DWORD ?
 dwCompletionKey        DWORD_PTR ?
 lpOverlapped           LPOVERLAPPED ?
ends
endif
ifndef RPC_NO_WINDOWS_H
struct HWND
 hWnd                   HWND ?
 Msg                    UINT ?
ends
endif
endif
ifndef _KRPCENV_
hEvent                  HANDLE ?
else
Event                   PKEVENT ?
endif
NotificationRoutine     PFN_RPCNOTIFICATION_ROUTINE ?
RPC_ASYNC_NOTIFICATION_INFO ends
PRPC_ASYNC_NOTIFICATION_INFO typedef ptr RPC_ASYNC_NOTIFICATION_INFO

RPC_ASYNC_STATE         struct
Size                    dword ?
Signature               sdword ?
_Lock                   sdword ?
Flags                   sdword ?
StubInfo                PVOID ?
UserInfo                PVOID ?
RuntimeInfo             PVOID ?
Event                   RPC_ASYNC_EVENT ?
NotificationType        RPC_NOTIFICATION_TYPES ?
u                       RPC_ASYNC_NOTIFICATION_INFO <>
Reserved                LONG_PTR 4 dup(?)
RPC_ASYNC_STATE         ends
PRPC_ASYNC_STATE        typedef ptr RPC_ASYNC_STATE

define RPC_C_NOTIFY_ON_SEND_COMPLETE      0x1
define RPC_C_INFINITE_TIMEOUT             INFINITE

RpcAsyncGetCallHandle macro pAsync
  exitm<(((PRPC_ASYNC_STATE) pAsync).RuntimeInfo)>
  endm

ifndef _KRPCENV_
RpcAsyncRegisterInfo proto WINAPI :PRPC_ASYNC_STATE
endif

RpcAsyncInitializeHandle proto WINAPI :PRPC_ASYNC_STATE, :dword
RpcAsyncGetCallStatus proto WINAPI :PRPC_ASYNC_STATE
RpcAsyncCompleteCall proto WINAPI :PRPC_ASYNC_STATE, :ptr
RpcAsyncAbortCall proto WINAPI :PRPC_ASYNC_STATE, :sdword
RpcAsyncCancelCall proto WINAPI :PRPC_ASYNC_STATE, :BOOL

if (NTDDI_VERSION ge NTDDI_WINXP)

if not defined(RPC_NO_WINDOWS_H) or defined(_KRPCENV_) or defined(_WINBASE_)

.enum ExtendedErrorParamTypes {
    eeptAnsiString = 1,
    eeptUnicodeString,
    eeptLongVal,
    eeptShortVal,
    eeptPointerVal,
    eeptNone,
    eeptBinary
    }

define MaxNumberOfEEInfoParams    4
define RPC_EEINFO_VERSION         1

BinaryParam             struct
Buffer                  PVOID ?
Size                    sword ?
BinaryParam             ends

RPC_EE_INFO_PARAM       struct
ParameterType           ExtendedErrorParamTypes ?
union u
 AnsiString             LPSTR ?
 UnicodeString          LPWSTR ?
 LVal                   sdword ?
 SVal                   sword ?
 PVal                   ULONGLONG ?
 BVal                   BinaryParam <>
ends
RPC_EE_INFO_PARAM       ends

define EEInfoPreviousRecordsMissing     1
define EEInfoNextRecordsMissing         2
define EEInfoUseFileTime                4

define EEInfoGCCOM                     11
if (NTDDI_VERSION ge NTDDI_WS03)
define EEInfoGCFRS                     12
endif

RPC_EXTENDED_ERROR_INFO struct
Version                 ULONG ?
ComputerName            LPWSTR ?
ProcessID               ULONG ?
union u
ifndef _KRPCENV_
 SystemTime             SYSTEMTIME <>
 FileTime               FILETIME <>
else
 KernelTime             LARGE_INTEGER <>
endif
ends
GeneratingComponent     ULONG ?
Status                  ULONG ?
DetectionLocation       USHORT ?
Flags                   USHORT ?
NumberOfParameters      sdword ?
Parameters              RPC_EE_INFO_PARAM MaxNumberOfEEInfoParams dup(<>)
RPC_EXTENDED_ERROR_INFO ends

RPC_ERROR_ENUM_HANDLE   struct
Signature               ULONG ?
CurrentPos              PVOID ?
Head                    PVOID ?
RPC_ERROR_ENUM_HANDLE   ends

RpcErrorStartEnumeration proto WINAPI :ptr
RpcErrorGetNextRecord proto WINAPI :ptr, :BOOL, :ptr
RpcErrorEndEnumeration proto WINAPI :ptr
RpcErrorResetEnumeration proto WINAPI :ptr
RpcErrorGetNumberOfRecords proto WINAPI :ptr, :ptr
RpcErrorSaveErrorInfo proto WINAPI :ptr, :ptr, :ptr
RpcErrorLoadErrorInfo proto WINAPI :PVOID, :size_t, :ptr
RpcErrorAddRecord proto WINAPI :ptr
RpcErrorClearInformation proto WINAPI

endif

ifndef _KRPCENV_

RpcAsyncCleanupThread proto WINAPI :DWORD
RpcGetAuthorizationContextForClient proto WINAPI :RPC_BINDING_HANDLE, :BOOL, :ptr, :PLARGE_INTEGER, :LUID, :DWORD, :PVOID, :ptr
RpcFreeAuthorizationContext proto WINAPI :ptr
RpcSsContextLockExclusive proto WINAPI :RPC_BINDING_HANDLE, :ptr
RpcSsContextLockShared proto WINAPI :RPC_BINDING_HANDLE, :ptr

if (NTDDI_VERSION ge NTDDI_VISTA)
.enum RpcLocalAddressFormat {
    rlafInvalid = 0,
    rlafIPv4,
    rlafIPv6
    }

RPC_CALL_LOCAL_ADDRESS_V1 struct
Version                 dword ?
Buffer                  PVOID ?
BufferSize              sdword ?
AddressFormat           RpcLocalAddressFormat ?
RPC_CALL_LOCAL_ADDRESS_V1 ends
PRPC_CALL_LOCAL_ADDRESS_V1 typedef ptr RPC_CALL_LOCAL_ADDRESS_V1

if ( (NTDDI_VERSION ge NTDDI_VISTA) and (NTDDI_VERSION lt NTDDI_WIN8) )
define RPC_CALL_ATTRIBUTES_VERSION                         (2)
endif

define RPC_QUERY_SERVER_PRINCIPAL_NAME                     (0x02)
define RPC_QUERY_CLIENT_PRINCIPAL_NAME                     (0x04)
define RPC_QUERY_CALL_LOCAL_ADDRESS                        (0x08)
define RPC_QUERY_CLIENT_PID                                (0x10)
define RPC_QUERY_IS_CLIENT_LOCAL                           (0x20)
define RPC_QUERY_NO_AUTH_REQUIRED                          (0x40)
endif

if (NTDDI_VERSION ge NTDDI_WIN8)
define RPC_CALL_ATTRIBUTES_VERSION                         (3)
define RPC_QUERY_CLIENT_ID                                 (0x80)
endif

if ( (NTDDI_VERSION ge NTDDI_WINXP) and (NTDDI_VERSION lt NTDDI_VISTA) )
define RPC_CALL_ATTRIBUTES_VERSION                         (1)
define RPC_QUERY_SERVER_PRINCIPAL_NAME                     (2)
define RPC_QUERY_CLIENT_PRINCIPAL_NAME                     (4)
endif

RPC_CALL_ATTRIBUTES_V1_W struct
Version                 dword ?
Flags                   sdword ?
ServerPrincipalNameBufferLength sdword ?
ServerPrincipalName     LPWSTR ?
ClientPrincipalNameBufferLength sdword ?
ClientPrincipalName     LPWSTR ?
AuthenticationLevel     sdword ?
AuthenticationService   sdword ?
NullSession             BOOL ?
RPC_CALL_ATTRIBUTES_V1_W ends

RPC_CALL_ATTRIBUTES_V1_A struct
Version                 dword ?
Flags                   sdword ?
ServerPrincipalNameBufferLength sdword ?
ServerPrincipalName     LPBYTE ?
ClientPrincipalNameBufferLength sdword ?
ClientPrincipalName     LPBYTE ?
AuthenticationLevel     sdword ?
AuthenticationService   sdword ?
NullSession             BOOL ?
RPC_CALL_ATTRIBUTES_V1_A ends

if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_CALL_STATUS_CANCELLED          0x01
define RPC_CALL_STATUS_DISCONNECTED       0x02

.enum RpcCallType {
    rctInvalid = 0,
    rctNormal,
    rctTraining,
    rctGuaranteed
    }

.enum RpcCallClientLocality {
    rcclInvalid = 0,
    rcclLocal,
    rcclRemote,
    rcclClientUnknownLocality
    }

RPC_CALL_ATTRIBUTES_V2_W struct
Version                 dword ?
Flags                   sdword ?
ServerPrincipalNameBufferLength sdword ?
ServerPrincipalName     LPWSTR ?
ClientPrincipalNameBufferLength sdword ?
ClientPrincipalName     LPWSTR ?
AuthenticationLevel     sdword ?
AuthenticationService   sdword ?
NullSession             BOOL ?
KernelModeCaller        BOOL ?
ProtocolSequence        sdword ?
IsClientLocal           RpcCallClientLocality ?
ClientPID               HANDLE ?
CallStatus              sdword ?
CallType                RpcCallType ?
CallLocalAddress        PRPC_CALL_LOCAL_ADDRESS_V1 ?
OpNum                   word ?
InterfaceUuid           UUID <>
RPC_CALL_ATTRIBUTES_V2_W ends

RPC_CALL_ATTRIBUTES_V2_A struct
Version                 dword ?
Flags                   sdword ?
ServerPrincipalNameBufferLength sdword ?
ServerPrincipalName     LPBYTE ?
ClientPrincipalNameBufferLength sdword ?
ClientPrincipalName     LPBYTE ?
AuthenticationLevel     sdword ?
AuthenticationService   sdword ?
NullSession             BOOL ?
KernelModeCaller        BOOL ?
ProtocolSequence        sdword ?
IsClientLocal           sdword ?
ClientPID               HANDLE ?
CallStatus              sdword ?
CallType                RpcCallType ?
CallLocalAddress        PRPC_CALL_LOCAL_ADDRESS_V1 ?
OpNum                   word ?
InterfaceUuid           UUID <>
RPC_CALL_ATTRIBUTES_V2_A ends

endif

if (NTDDI_VERSION ge NTDDI_WIN8)
RPC_CALL_ATTRIBUTES_V3_W struct
Version                 dword ?
Flags                   sdword ?
ServerPrincipalNameBufferLength sdword ?
ServerPrincipalName     LPWSTR ?
ClientPrincipalNameBufferLength sdword ?
ClientPrincipalName     LPWSTR ?
AuthenticationLevel     sdword ?
AuthenticationService   sdword ?
NullSession             BOOL ?
KernelModeCaller        BOOL ?
ProtocolSequence        sdword ?
IsClientLocal           RpcCallClientLocality ?
ClientPID               HANDLE ?
CallStatus              sdword ?
CallType                RpcCallType ?
CallLocalAddress        PRPC_CALL_LOCAL_ADDRESS_V1 ?
OpNum                   word ?
InterfaceUuid           UUID <>
ClientIdentifierBufferLength sdword ?
ClientIdentifier        LPBYTE ?
RPC_CALL_ATTRIBUTES_V3_W ends


RPC_CALL_ATTRIBUTES_V3_A struct
Version                 dword ?
Flags                   sdword ?
ServerPrincipalNameBufferLength sdword ?
ServerPrincipalName     LPBYTE ?
ClientPrincipalNameBufferLength sdword ?
ClientPrincipalName     LPBYTE ?
AuthenticationLevel     sdword ?
AuthenticationService   sdword ?
NullSession             BOOL ?
KernelModeCaller        BOOL ?
ProtocolSequence        sdword ?
IsClientLocal           sdword ?
ClientPID               HANDLE ?
CallStatus              sdword ?
CallType                RpcCallType ?
CallLocalAddress        PRPC_CALL_LOCAL_ADDRESS_V1 ?
OpNum                   word ?
InterfaceUuid           UUID <>
ClientIdentifierBufferLength sdword ?
ClientIdentifier        LPBYTE ?
RPC_CALL_ATTRIBUTES_V3_A ends

endif

RpcServerInqCallAttributesW proto WINAPI :RPC_BINDING_HANDLE, :ptr
RpcServerInqCallAttributesA proto WINAPI :RPC_BINDING_HANDLE, :ptr

ifdef _UNICODE
define RPC_CALL_ATTRIBUTES_V1 <RPC_CALL_ATTRIBUTES_V1_W>
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_CALL_ATTRIBUTES_V2 <RPC_CALL_ATTRIBUTES_V2_W>
endif
if (NTDDI_VERSION ge NTDDI_WIN8)
define RPC_CALL_ATTRIBUTES_V3 <RPC_CALL_ATTRIBUTES_V3_W>
endif
define RpcServerInqCallAttributes <RpcServerInqCallAttributesW>
else
define RPC_CALL_ATTRIBUTES_V1 <RPC_CALL_ATTRIBUTES_V1_A>
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_CALL_ATTRIBUTES_V2 <RPC_CALL_ATTRIBUTES_V2_A>
endif
if (NTDDI_VERSION ge NTDDI_WIN8)
define RPC_CALL_ATTRIBUTES_V3 <RPC_CALL_ATTRIBUTES_V3_A>
endif
define RpcServerInqCallAttributes <RpcServerInqCallAttributesA>
endif

if (NTDDI_VERSION ge NTDDI_WIN8)
RPC_CALL_ATTRIBUTES     typedef RPC_CALL_ATTRIBUTES_V3
elseif (NTDDI_VERSION ge NTDDI_VISTA)
RPC_CALL_ATTRIBUTES     typedef RPC_CALL_ATTRIBUTES_V2
else
RPC_CALL_ATTRIBUTES     typedef RPC_CALL_ATTRIBUTES_V1
endif

if (NTDDI_VERSION ge NTDDI_VISTA)
.enum RPC_NOTIFICATIONS {
    RpcNotificationCallNone = 0,
    RpcNotificationClientDisconnect = 1,
    RpcNotificationCallCancel = 2
    }

define RpcNotificationCallStatusChange    RpcNotificationClientDisconnect

RpcServerSubscribeForNotification proto WINAPI :RPC_BINDING_HANDLE, :RPC_NOTIFICATIONS, :RPC_NOTIFICATION_TYPES, :ptr
RpcServerUnsubscribeForNotification proto WINAPI :RPC_BINDING_HANDLE, :RPC_NOTIFICATIONS, :ptr

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)
RpcBindingBind proto WINAPI :PRPC_ASYNC_STATE, :RPC_BINDING_HANDLE, :RPC_IF_HANDLE
RpcBindingUnbind proto WINAPI :RPC_BINDING_HANDLE
endif

endif

I_RpcAsyncSetHandle proto WINAPI :PRPC_MESSAGE, :PRPC_ASYNC_STATE
I_RpcAsyncAbortCall proto WINAPI :PRPC_ASYNC_STATE, :sdword

if (NTDDI_VERSION ge NTDDI_WINXP)
I_RpcExceptionFilter proto WINAPI :sdword
endif

if (NTDDI_VERSION ge NTDDI_WIN7)
I_RpcBindingInqClientTokenAttributes proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr
endif

endif

ifdef __RPC_WIN64__
.pragma pack(pop)
endif

endif

