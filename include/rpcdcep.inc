ifndef __LIBC_INC
 include libc.inc
endif
ifndef __RPCDCEP_H__
__RPCDCEP_H__ equ <>

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


CALLBACK(RPC_FORWARD_FUNCTION, \
	InterfaceId:ptr UUID, \
	InterfaceVersion:ptr RPC_VERSION, \
	ObjectId:ptr UUID, \
	Rpcpro:LPBYTE, \
	ppDestEndpoint:PVOID)

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
_Length			UINT ?
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
_Length			UINT ?
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

;RPC_STATUS
I_RpcGetBuffer proto WINAPI \
	       Message: ptr RPC_MESSAGE

;RPC_STATUS
I_RpcSendReceive proto WINAPI \
	       Message: ptr RPC_MESSAGE

;RPC_STATUS
I_RpcFreeBuffer proto WINAPI \
	       Message: ptr RPC_MESSAGE

;RPC_STATUS
I_RpcSend proto WINAPI \
	       Message: PRPC_MESSAGE ;

;RPC_STATUS
I_RpcReceive proto WINAPI \
	       Message: PRPC_MESSAGE,
		 _Size: UINT

;RPC_STATUS
I_RpcFreePipeBuffer proto WINAPI \
	       Message: ptr RPC_MESSAGE ;

;RPC_STATUS
I_RpcReallocPipeBuffer proto WINAPI \
	       Message: PRPC_MESSAGE,
	       NewSize: UINT

I_RPC_MUTEX		typedef PVOID

;void
I_RpcRequestMutex proto WINAPI \
		 Mutex: ptr I_RPC_MUTEX

;void
I_RpcClearMutex proto WINAPI \
		 Mutex: I_RPC_MUTEX

;void
I_RpcDeleteMutex proto WINAPI \
		 Mutex: I_RPC_MUTEX

;PVOID
I_RpcAllocate proto WINAPI \
		  _Size: UINT

;void
I_RpcFree proto WINAPI \
		Object: PVOID

;void
I_RpcPauseExecution proto WINAPI \
	  Milliseconds: ULONG

CALLBACK(PRPC_RUNDOWN, AssociationContext:PVOID)

;RPC_STATUS
I_RpcMonitorAssociation proto WINAPI \
		Handle: RPC_BINDING_HANDLE,
	RundownRoutine: PRPC_RUNDOWN,
	       Context: PVOID

;RPC_STATUS
I_RpcStopMonitorAssociation proto WINAPI \
		Handle: RPC_BINDING_HANDLE

;RPC_BINDING_HANDLE
I_RpcGetCurrentCallHandle proto WINAPI

;RPC_STATUS
I_RpcGetAssociationContext proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE,
    AssociationContext: PVOID

;PVOID
I_RpcGetServerContextList proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE

;void
I_RpcSetServerContextList proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE,
     ServerContextList: PVOID

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
I_RpcNsBindingSetEntryNameW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: ULONG,
	     EntryName: LPWORD

;RPC_STATUS
I_RpcNsBindingSetEntryNameA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: ULONG,
	     EntryName: LPBYTE

ifdef _UNICODE
I_RpcNsBindingSetEntryName equ <I_RpcNsBindingSetEntryNameW>
else
I_RpcNsBindingSetEntryName equ <I_RpcNsBindingSetEntryNameA>
endif

else

;RPC_STATUS
I_RpcNsBindingSetEntryName proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: ULONG,
	     EntryName: LPBYTE

endif

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
I_RpcBindingInqDynamicEndpointW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       DynamicEndpoint: LPWORD

;RPC_STATUS
I_RpcBindingInqDynamicEndpointA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       DynamicEndpoint: LPBYTE

ifdef _UNICODE
I_RpcBindingInqDynamicEndpoint equ <I_RpcBindingInqDynamicEndpointW>
else
I_RpcBindingInqDynamicEndpoint equ <I_RpcBindingInqDynamicEndpointA>
endif

else

;RPC_STATUS
I_RpcBindingInqDynamicEndpoint proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       DynamicEndpoint: LPBYTE

endif

TRANSPORT_TYPE_CN	equ 0x01
TRANSPORT_TYPE_DG	equ 0x02
TRANSPORT_TYPE_LPC	equ 0x04
TRANSPORT_TYPE_WMSG	equ 0x08

;RPC_STATUS
I_RpcBindingInqTransportType proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
		 _Type: ptr UINT

RPC_TRANSFER_SYNTAX	STRUC
Uuid			UUID <>
VersMajor		dw ?
VersMinor		dw ?
RPC_TRANSFER_SYNTAX	ENDS

;RPC_STATUS
I_RpcIfInqTransferSyntaxes proto WINAPI \
	   RpcIfHandle: RPC_IF_HANDLE,
      TransferSyntaxes: ptr RPC_TRANSFER_SYNTAX,
    TransferSyntaxSize: UINT,
   TransferSyntaxCount: ptr UINT

;RPC_STATUS
I_UuidCreate proto WINAPI \
		  Uuid: ptr UUID

;RPC_STATUS
I_RpcBindingCopy proto WINAPI \
	 SourceBinding: RPC_BINDING_HANDLE,
    DestinationBinding: ptr RPC_BINDING_HANDLE

;RPC_STATUS
I_RpcBindingIsClientLocal proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE,
       ClientLocalFlag: ptr UINT

;void
I_RpcSsDontSerializeContext proto WINAPI

;RPC_STATUS
I_RpcLaunchDatagramReceiveThread proto WINAPI \
	      pAddress: PVOID

;RPC_STATUS
I_RpcServerRegisterForwardFunction proto WINAPI \
      pForwardFunction: ptr RPC_FORWARD_FUNCTION


;RPC_STATUS
I_RpcConnectionInqSockBuffSize proto WINAPI \
	  RecvBuffSize: ptr ULONG,
	  SendBuffSize: ptr ULONG

;RPC_STATUS
I_RpcConnectionSetSockBuffSize proto WINAPI \
	  RecvBuffSize: ULONG,
	  SendBuffSize: ULONG

ifdef WINNT
ifdef MSWMSG
;RPC_STATUS
I_RpcServerStartListening proto WINAPI \
		  hWnd: HWND

;RPC_STATUS
I_RpcServerStopListening proto WINAPI


;RPC_STATUS
I_RpcGetThreadWindowHandle proto WINAPI \
	  WindowHandle: ptr HWND

;RPC_STATUS
I_RpcAsyncSendReceive proto WINAPI \
	   pRpcMessage: PRPC_MESSAGE,
	       Context: PVOID,
		  hWnd: HWND

CALLBACK(RPC_BLOCKING_FN, wnd:PVOID, Context:PVOID, hSyncEvent:HANDLE)

;RPC_STATUS
I_RpcBindingSetAsync proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	    BlockingFn: RPC_BLOCKING_FN

;LONG
I_RpcWindowProc proto WINAPI \
		  hWnd: HWND,
	       Message: UINT,
		wParam: WPARAM,
		lParam: LPARAM ;

;RPC_STATUS
I_RpcSetWMsgEndpoint proto WINAPI \
	      Endpoint: ptr WCHAR ;
endif

else

;RPC_STATUS
I_RpcServerStartListening proto WINAPI \
		  hWnd: PVOID ;

;RPC_STATUS
I_RpcServerStopListening proto WINAPI

CALLBACK(RPC_BLOCKING_FN, hWnd:PVOID, Context:PVOID, hSyncEvent:PVOID)

;RPC_STATUS
I_RpcBindingSetAsync proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	    BlockingFn: RPC_BLOCKING_FN,
	     ServerTid: ULONG

;RPC_STATUS
I_RpcSetThreadParams proto WINAPI \
	   fClientFree: SINT,
	       Context: PVOID,
	    hWndClient: PVOID

;UINT
I_RpcWindowProc proto WINAPI \
		  hWnd: PVOID,
	       Message: UINT,
		wParam: UINT,
		lParam: ULONG
endif

ifndef WINNT
;RPC_STATUS
I_RpcServerUnregisterEndpointA proto WINAPI \
	       Protseq: LPBYTE,
	      Endpoint: LPBYTE

;RPC_STATUS
I_RpcServerUnregisterEndpointW proto WINAPI \
	       Protseq: LPWORD,
	      Endpoint: LPWORD

ifdef _UNICODE
I_RpcServerUnregisterEndpoint equ <I_RpcServerUnregisterEndpointW>
else
I_RpcServerUnregisterEndpoint equ <I_RpcServerUnregisterEndpointA>
endif
endif

;RPC_STATUS
I_RpcServerInqTransportType proto WINAPI \
		  _Type: LPDWORD

endif
