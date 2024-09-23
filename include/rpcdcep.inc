ifndef __LIBC_INC
 include libc.inc
endif
ifndef __RPCDCEP_H__
define __RPCDCEP_H__

RPC_VERSION		STRUC
MajorVersion		dw ?
MinorVersion		dw ?
RPC_VERSION		ENDS

RPC_SYNTAX_IDENTIFIER	STRUC
SyntaxGUID		GUID <>
SyntaxVersion		RPC_VERSION <>
RPC_SYNTAX_IDENTIFIER	ENDS
PRPC_SYNTAX_IDENTIFIER	typedef ptr RPC_SYNTAX_IDENTIFIER

RPC_MESSAGE		STRUC
Handle			RPC_BINDING_HANDLE ?
DataRepresentation	ULONG ?
Buffer			PVOID ?
BufferLength		UINT ?
ProcNum			UINT ?
TransferSyntax		PRPC_SYNTAX_IDENTIFIER ?
RpcInterfaceInformation PVOID ?
ReservedForRuntime	PVOID ?
ManagerEpv		PVOID ?;RPC_MGR_EPV ?
ImportContext		PVOID ?
RpcFlags		ULONG ?
RPC_MESSAGE		ENDS
PRPC_MESSAGE		typedef ptr RPC_MESSAGE


CALLBACK(RPC_FORWARD_FUNCTION, :ptr, :ptr, :ptr, :LPBYTE, :ptr)

RPC_NCA_FLAGS_DEFAULT	equ 0x00000000
RPC_NCA_FLAGS_IDEMPOTENT equ 0x00000001
RPC_NCA_FLAGS_BROADCAST equ 0x00000002
RPC_NCA_FLAGS_MAYBE	equ 0x00000004

RPC_BUFFER_COMPLETE	equ 0x00001000
RPC_BUFFER_PARTIAL	equ 0x00002000
RPC_BUFFER_EXTRA	equ 0x00004000
RPC_BUFFER_ASYNC	equ 0x00008000
RPC_BUFFER_NONOTIFY	equ 0x00010000

RPCFLG_MESSAGE		equ 0x01000000
RPCFLG_AUTO_COMPLETE	equ 0x08000000
RPCFLG_LOCAL_CALL	equ 0x10000000
RPCFLG_INPUT_SYNCHRONOUS equ 0x20000000
RPCFLG_ASYNCHRONOUS	equ 0x40000000
RPCFLG_NON_NDR		equ 0x80000000


if defined(__RPC_DOS__) OR defined(__RPC_WIN16__)
RPC_FLAGS_VALID_BIT	equ 0x8000
endif

if defined(__RPC_WIN32__) OR defined(__RPC_MAC__)
RPC_FLAGS_VALID_BIT	equ 0x00008000
endif

CALLBACK(RPC_DISPATCH_FUNCTION, Message:PRPC_MESSAGE)

RPC_DISPATCH_TABLE	STRUC
DispatchTableCount	UINT ?
DispatchTable		PVOID ?;ptr RPC_DISPATCH_FUNCTION ?
Reserved		SINT ?
RPC_DISPATCH_TABLE	ENDS
PRPC_DISPATCH_TABLE	typedef ptr RPC_DISPATCH_TABLE

RPC_PROTSEQ_ENDPOINT	STRUC
RpcProtocolSequence	LPBYTE ?
Endpoint		LPBYTE ?
RPC_PROTSEQ_ENDPOINT	ENDS
PRPC_PROTSEQ_ENDPOINT	typedef ptr RPC_PROTSEQ_ENDPOINT

NT351_INTERFACE_SIZE	equ 0x40
RPC_INTERFACE_HAS_PIPES equ 0x0001

RPC_SERVER_INTERFACE	STRUC
Length			UINT ?
InterfaceId		RPC_SYNTAX_IDENTIFIER <>
TransferSyntax		RPC_SYNTAX_IDENTIFIER <>
DispatchTable		PRPC_DISPATCH_TABLE ?
RpcProtseqEndpointCount UINT ?
RpcProtseqEndpoint	PRPC_PROTSEQ_ENDPOINT ?
DefaultManagerEpv	PVOID ?;RPC_MGR_EPV ?
InterpreterInfo		PVOID ?
Flags			UINT ?
RPC_SERVER_INTERFACE	ENDS
PRPC_SERVER_INTERFACE	typedef ptr RPC_SERVER_INTERFACE

RPC_CLIENT_INTERFACE	STRUC
Length			UINT ?
InterfaceId		RPC_SYNTAX_IDENTIFIER <>
TransferSyntax		RPC_SYNTAX_IDENTIFIER <>
DispatchTable		PRPC_DISPATCH_TABLE ?
RpcProtseqEndpointCount UINT ?
RpcProtseqEndpoint	PRPC_PROTSEQ_ENDPOINT ?
Reserved		ULONG ?
InterpreterInfo		PVOID ?
Flags			UINT ?
RPC_CLIENT_INTERFACE	ENDS
PRPC_CLIENT_INTERFACE	typedef ptr RPC_CLIENT_INTERFACE

I_RpcGetBuffer proto WINAPI :ptr
I_RpcSendReceive proto WINAPI :ptr
I_RpcFreeBuffer proto WINAPI :ptr
I_RpcSend proto WINAPI :ptr
I_RpcReceive proto WINAPI :PRPC_MESSAGE, :UINT
I_RpcFreePipeBuffer proto WINAPI :ptr
I_RpcReallocPipeBuffer proto WINAPI :PRPC_MESSAGE, :UINT

I_RPC_MUTEX typedef ptr

I_RpcRequestMutex proto WINAPI :ptr
I_RpcClearMutex proto WINAPI :I_RPC_MUTEX
I_RpcDeleteMutex proto WINAPI :I_RPC_MUTEX
I_RpcAllocate proto WINAPI :UINT
I_RpcFree proto WINAPI :ptr
I_RpcPauseExecution proto WINAPI :ULONG

CALLBACK(PRPC_RUNDOWN, AssociationContext:PVOID)

I_RpcMonitorAssociation proto WINAPI :RPC_BINDING_HANDLE, :PRPC_RUNDOWN, :ptr
I_RpcStopMonitorAssociation proto WINAPI :RPC_BINDING_HANDLE
I_RpcGetCurrentCallHandle proto WINAPI
I_RpcGetAssociationContext proto WINAPI :RPC_BINDING_HANDLE, :ptr
I_RpcGetServerContextList proto WINAPI :RPC_BINDING_HANDLE
I_RpcSetServerContextList proto WINAPI :RPC_BINDING_HANDLE, :ptr

ifdef RPC_UNICODE_SUPPORTED
I_RpcNsBindingSetEntryNameW proto WINAPI :RPC_BINDING_HANDLE, :ULONG, :LPWORD
I_RpcNsBindingSetEntryNameA proto WINAPI :RPC_BINDING_HANDLE, :ULONG, :LPBYTE
ifdef _UNICODE
I_RpcNsBindingSetEntryName equ <I_RpcNsBindingSetEntryNameW>
else
I_RpcNsBindingSetEntryName equ <I_RpcNsBindingSetEntryNameA>
endif
else
I_RpcNsBindingSetEntryName proto WINAPI :RPC_BINDING_HANDLE, :ULONG, :LPBYTE
endif

ifdef RPC_UNICODE_SUPPORTED
I_RpcBindingInqDynamicEndpointW proto WINAPI :RPC_BINDING_HANDLE, :LPWORD
I_RpcBindingInqDynamicEndpointA proto WINAPI :RPC_BINDING_HANDLE, :LPBYTE
ifdef _UNICODE
I_RpcBindingInqDynamicEndpoint equ <I_RpcBindingInqDynamicEndpointW>
else
I_RpcBindingInqDynamicEndpoint equ <I_RpcBindingInqDynamicEndpointA>
endif
else
I_RpcBindingInqDynamicEndpoint proto WINAPI :RPC_BINDING_HANDLE, :LPBYTE
endif

TRANSPORT_TYPE_CN	equ 0x01
TRANSPORT_TYPE_DG	equ 0x02
TRANSPORT_TYPE_LPC	equ 0x04
TRANSPORT_TYPE_WMSG	equ 0x08

I_RpcBindingInqTransportType proto WINAPI :RPC_BINDING_HANDLE, :ptr

RPC_TRANSFER_SYNTAX	STRUC
Uuid			UUID <>
VersMajor		dw ?
VersMinor		dw ?
RPC_TRANSFER_SYNTAX	ENDS

I_RpcIfInqTransferSyntaxes proto WINAPI :RPC_IF_HANDLE, :ptr, :UINT, :ptr
I_UuidCreate proto WINAPI :ptr
I_RpcBindingCopy proto WINAPI :RPC_BINDING_HANDLE, :ptr
I_RpcBindingIsClientLocal proto WINAPI :RPC_BINDING_HANDLE, :ptr
I_RpcSsDontSerializeContext proto WINAPI
I_RpcLaunchDatagramReceiveThread proto WINAPI :ptr
I_RpcServerRegisterForwardFunction proto WINAPI :ptr
I_RpcConnectionInqSockBuffSize proto WINAPI :ptr, :ptr
I_RpcConnectionSetSockBuffSize proto WINAPI :ULONG, :ULONG

ifdef WINNT
ifdef MSWMSG
I_RpcServerStartListening proto WINAPI :HWND
I_RpcServerStopListening proto WINAPI
I_RpcGetThreadWindowHandle proto WINAPI :ptr
I_RpcAsyncSendReceive proto WINAPI :PRPC_MESSAGE, :ptr, :HWND

CALLBACK(RPC_BLOCKING_FN, :ptr, :ptr, :HANDLE)

I_RpcBindingSetAsync proto WINAPI :RPC_BINDING_HANDLE, :RPC_BLOCKING_FN
I_RpcWindowProc proto WINAPI :HWND, :UINT, :WPARAM, :LPARAM
I_RpcSetWMsgEndpoint proto WINAPI :ptr
endif

else
I_RpcServerStartListening proto WINAPI :ptr
I_RpcServerStopListening proto WINAPI

CALLBACK(RPC_BLOCKING_FN, :ptr, :ptr, :ptr)

I_RpcBindingSetAsync proto WINAPI :RPC_BINDING_HANDLE, :RPC_BLOCKING_FN, :ULONG
I_RpcSetThreadParams proto WINAPI :SINT, :ptr, :ptr
I_RpcWindowProc proto WINAPI :ptr, :UINT, :UINT, :ULONG
endif

ifndef WINNT
I_RpcServerUnregisterEndpointA proto WINAPI :LPBYTE, :LPBYTE
I_RpcServerUnregisterEndpointW proto WINAPI :LPWORD, :LPWORD
ifdef _UNICODE
I_RpcServerUnregisterEndpoint equ <I_RpcServerUnregisterEndpointW>
else
I_RpcServerUnregisterEndpoint equ <I_RpcServerUnregisterEndpointA>
endif
endif

I_RpcServerInqTransportType proto WINAPI :LPDWORD

endif
