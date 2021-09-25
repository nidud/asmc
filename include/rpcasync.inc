ifndef __LIBC_INC
 include libc.inc
endif
ifndef __RPCASYNC_H__
define __RPCASYNC_H__

RPC_ASYNC_VERSION_1_0	equ RPC_ASYNC_STATE

RpcNotificationTypeNone		equ 0
RpcNotificationTypeEvent	equ 1
RpcNotificationTypeApc		equ 2
RpcNotificationTypeIoc		equ 3
RpcNotificationTypeHwnd		equ 4
RpcNotificationTypeCallback	equ 5
RPC_NOTIFICATION_TYPES	typedef sdword

RpcCallComplete		equ 0
RpcSendComplete		equ 1
RpcReceiveComplete	equ 2
RPC_ASYNC_EVENT		typedef sdword

CALLBACK(RPCNOTIFICATION_ROUTINE, pAsync:PVOID, Context:PVOID, Event:RPC_ASYNC_EVENT)
PFN_RPCNOTIFICATION_ROUTINE typedef ptr RPCNOTIFICATION_ROUTINE

RPC_ASYNC_STATE		STRUC
Size			UINT ?
Signature		ULONG ?
_Lock			LONG ?
Flags			ULONG ?
StubInfo		PVOID ?
UserInfo		PVOID ?
RuntimeInfo		PVOID ?
Event			RPC_ASYNC_EVENT ?
NotificationType	RPC_NOTIFICATION_TYPES ?
UNION u
    STRUC APC
	NotificationRoutine PFN_RPCNOTIFICATION_ROUTINE ?
	hThread		HANDLE ?
    ENDS
    STRUC IOC
	hIOPort		HANDLE ?
	dwNumberOfBytesTransferred dd ?
	dwCompletionKey dd ?
	lpOverlapped	LPOVERLAPPED ?
    ENDS
    STRUC HWND
	hWnd		HWND ?
	Msg		UINT ?
    ENDS
    hEvent		HANDLE ?
    NotificationRoutine PFN_RPCNOTIFICATION_ROUTINE ?
ENDS
Reserved		LONG 4 dup(?)
RPC_ASYNC_STATE		ENDS
PRPC_ASYNC_STATE	typedef ptr RPC_ASYNC_STATE

RPC_C_NOTIFY_ON_SEND_COMPLETE equ 0x1
RPC_C_INFINITE_TIMEOUT	equ INFINITE

RpcAsyncGetCallHandle macro pAsync
	exitm<pAsync.RuntimeInfo>
	endm

;RPC_STATUS
RpcAsyncInitializeHandle proto WINAPI \
		pAsync: PRPC_ASYNC_STATE,
		  Size: UINT

;RPC_STATUS
RpcAsyncRegisterInfo proto WINAPI \
		pAsync: PRPC_ASYNC_STATE ;

;RPC_STATUS
RpcAsyncGetCallStatus proto WINAPI \
		pAsync: PRPC_ASYNC_STATE ;

;RPC_STATUS
RpcAsyncCompleteCall proto WINAPI \
		pAsync: PRPC_ASYNC_STATE,
		 Reply: PVOID ;

;RPC_STATUS
RpcAsyncAbortCall proto WINAPI \
		pAsync: PRPC_ASYNC_STATE,
	 ExceptionCode: DWORD ;

;RPC_STATUS
RpcAsyncCancelCall proto WINAPI \
		pAsync: PRPC_ASYNC_STATE,
		fAbort: BOOL ;

;RPC_STATUS RPC_ENTRY
I_RpcAsyncSetHandle proto WINAPI \
		Message: PRPC_MESSAGE,
		pAsync: PRPC_ASYNC_STATE

;RPC_STATUS RPC_ENTRY
I_RpcAsyncAbortCall proto WINAPI \
		pAsync: PRPC_ASYNC_STATE,
		ExceptionCode: DWORD

endif
