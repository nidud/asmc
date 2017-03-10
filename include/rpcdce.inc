ifndef __LIBC_INC
 include libc.inc
endif
.xlist
;;
;; This module contains the DCE RPC runtime APIs.
;;
ifndef __RPCDCE_H__
__RPCDCE_H__ equ 1

RPC_BINDING_HANDLE	typedef I_RPC_HANDLE
handle_t		typedef RPC_BINDING_HANDLE
rpc_binding_handle_t	equ <RPC_BINDING_HANDE>

ifndef GUID_DEFINED
GUID_DEFINED		equ 1
GUID			STRUC
Data1			dd ?
Data2			dw ?
Data3			dw ?
Data4			db 8 dup(?)
GUID			ENDS
endif ;; GUID_DEFINED

ifndef UUID_DEFINED
UUID_DEFINED		equ 1
UUID			typedef GUID
ifndef uuid_t
uuid_t			equ UUID
endif
endif

RPC_BINDING_VECTOR	STRUC
Count			dd ?
BindingH		RPC_BINDING_HANDLE ?
RPC_BINDING_VECTOR	ENDS
ifndef rpc_binding_vector_t
rpc_binding_vector_t	equ RPC_BINDING_VECTOR
endif

UUID_VECTOR		STRUC
Count			dd ?
Uuid			PVOID ? ;UUID ?
UUID_VECTOR		ENDS
ifndef uuid_vector_t
uuid_vector_t		equ UUID_VECTOR
endif

RPC_IF_HANDLE		typedef ptr

ifndef IFID_DEFINED
IFID_DEFINED		equ 1
RPC_IF_ID		STRUC
Uuid			UUID <>
VersMajor		dw ?
VersMinor		dw ?
RPC_IF_ID		ENDS
endif

RPC_C_BINDING_INFINITE_TIMEOUT	equ 10
RPC_C_BINDING_MIN_TIMEOUT	equ 0
RPC_C_BINDING_DEFAULT_TIMEOUT	equ 5
RPC_C_BINDING_MAX_TIMEOUT	equ 9

RPC_C_CANCEL_INFINITE_TIMEOUT	equ -1

RPC_C_LISTEN_MAX_CALLS_DEFAULT	equ 1234
RPC_C_PROTSEQ_MAX_REQS_DEFAULT	equ 10

;; RPC_POLICY EndpointFlags.
RPC_C_BIND_TO_ALL_NICS		equ 1
RPC_C_USE_INTERNET_PORT		equ 1
RPC_C_USE_INTRANET_PORT		equ 2

;; RPC_POLICY EndpointFlags specific to the Falcon/RPC transport:
RPC_C_MQ_TEMPORARY		equ 0x0000
RPC_C_MQ_PERMANENT		equ 0x0001
RPC_C_MQ_CLEAR_ON_OPEN		equ 0x0002
RPC_C_MQ_USE_EXISTING_SECURITY	equ 0x0004
RPC_C_MQ_AUTHN_LEVEL_NONE	equ 0x0000
RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY equ 0x0008
RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY equ 0x0010

;; Client: RpcBindingSetOption() values for the Falcon/RPC transport:
RPC_C_OPT_MQ_DELIVERY		equ 1
RPC_C_OPT_MQ_PRIORITY		equ 2
RPC_C_OPT_MQ_JOURNAL		equ 3
RPC_C_OPT_MQ_ACKNOWLEDGE	equ 4
RPC_C_OPT_MQ_AUTHN_SERVICE	equ 5
RPC_C_OPT_MQ_AUTHN_LEVEL	equ 6
RPC_C_OPT_MQ_TIME_TO_REACH_QUEUE equ 7
RPC_C_OPT_MQ_TIME_TO_BE_RECEIVED equ 8
RPC_C_OPT_BINDING_NONCAUSAL	equ 9
RPC_C_OPT_MAX_OPTIONS		equ 10

RPC_C_MQ_EXPRESS		equ 0  ;; Client: RPC_C_MQ_DEIVERY.
RPC_C_MQ_RECOVERABLE		equ 1

RPC_C_MQ_JOURNAL_NONE		equ 0  ;; Client: RPC_C_MQ_JOURNA.
RPC_C_MQ_JOURNAL_DEADLETTER	equ 1
RPC_C_MQ_JOURNAL_ALWAYS		equ 2


ifdef RPC_UNICODE_SUPPORTED
RPC_PROTSEQ_VECTORA	STRUC
Count			UINT ?
Protseq			LPBYTE ?
RPC_PROTSEQ_VECTORA	ENDS

RPC_PROTSEQ_VECTORW	STRUC
Count			UINT ?
Protseq			LPWORD ?
RPC_PROTSEQ_VECTORW	ENDS

ifdef _UNICODE
RPC_PROTSEQ_VECTOR	equ <RPC_PROTSEQ_VECTORW>
else ;; UNICODE
RPC_PROTSEQ_VECTOR	equ <RPC_PROTSEQ_VECTORA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

RPC_PROTSEQ_VECTOR	STRUC
Count			UINT ?
Protseq			LPBYTE ?
RPC_PROTSEQ_VECTOR	ENDS

endif ;; RPC_UNICODE_SUPPORTED
RPC_POLICY		STRUC
_Length			UINT ?
EndpointFlags		dd ?
NICFlags		dd ?
RPC_POLICY		ENDS
PRPC_POLICY		typedef ptr RPC_POLICY

RPC_OBJECT_INQ_FN_T typedef proto _CType \
	     ObjectUuid: ptr UUID,
	       TypeUuid: ptr UUID,
		 Status: ptr RPC_STATUS
RPC_OBJECT_INQ_FN	typedef ptr RPC_OBJECT_INQ_FN_T

RPC_IF_CALLBACK_FN_T typedef proto _CType \
	  InterfaceUuid: RPC_IF_HANDLE,
		Context: PVOID
RPC_IF_CALLBACK_FN	typedef ptr RPC_IF_CALLBACK_FN_T

RPC_MGR_EPV		equ <>

RPC_STATS_VECTOR	STRUC
Count			UINT ?
Stats			dd ?
RPC_STATS_VECTOR	ENDS

RPC_C_STATS_CALLS_IN	equ 0
RPC_C_STATS_CALLS_OUT	equ 1
RPC_C_STATS_PKTS_IN	equ 2
RPC_C_STATS_PKTS_OUT	equ 3

RPC_IF_ID_VECTOR	STRUC
Count			dd ?
IfId			PVOID ?;RPC_IF_ID ?
RPC_IF_ID_VECTOR	ENDS

;; client
;RPC_STATUS
RpcBindingCopy proto _CType \
	 SourceBinding: RPC_BINDING_HANDLE,
    DestinationBinding: ptr RPC_BINDING_HANDLE

;; client
;RPC_STATUS
RpcBindingFree proto _CType \
	       Binding: ptr RPC_BINDING_HANDLE

;; client
;RPC_STATUS
RpcBindingSetOption proto _CType \
	      hBinding: RPC_BINDING_HANDLE,
	       _option: DWORD,
	   optionValue: DWORD

;; client
;RPC_STATUS
RpcBindingInqOption proto _CType \
	      hBinding: RPC_BINDING_HANDLE,
	       _option: DWORD,
	  pOptionValue: LPDWORD

;; client

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingFromStringBindingA proto _CType \
	 StringBinding: PVOID,
	       Binding: ptr RPC_BINDING_HANDLE

;RPC_STATUS
RpcBindingFromStringBindingW proto _CType \
	 StringBinding: PVOID,
	       Binding: ptr RPC_BINDING_HANDLE

ifdef _UNICODE
RpcBindingFromStringBinding equ <RpcBindingFromStringBindingW>
else ;; UNICODE
RpcBindingFromStringBinding equ <RpcBindingFromStringBindingA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingFromStringBinding proto _CType \
	 StringBinding: PVOID,
	       Binding: ptr RPC_BINDING_HANDLE

endif ;; RPC_UNICODE_SUPPORTED

;; client/server
;RPC_STATUS
RpcBindingInqObject proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID

;; client
;RPC_STATUS
RpcBindingReset proto _CType \
	       Binding: RPC_BINDING_HANDLE

;; RpcBindingServerFromClient : UNSUPPORTED
;; RpcBindingSetAuthInfo

;; client
;RPC_STATUS
RpcBindingSetObject proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID

;; client/server
;RPC_STATUS
RpcMgmtInqDefaultProtectLevel proto _CType \
	      AuthnSvc: DWORD,
	    AuthnLevel: LPDWORD

;; client/server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingToStringBindingA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	 StringBinding: PVOID

;RPC_STATUS
RpcBindingToStringBindingW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	 StringBinding: LPWORD

ifdef _UNICODE
RpcBindingToStringBinding equ <RpcBindingToStringBindingW>
else ;; UNICODE
RpcBindingToStringBinding equ <RpcBindingToStringBindingA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingToStringBinding proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	 StringBinding: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;; client/server
;RPC_STATUS
RpcBindingVectorFree proto _CType \
	 BindingVector: ptr RPC_BINDING_VECTOR

;; client/server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringBindingComposeA proto _CType \
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	       Options: PVOID,
	 StringBinding: PVOID

;RPC_STATUS
RpcStringBindingComposeW proto _CType \
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	       Options: PVOID,
	 StringBinding: LPWORD

ifdef _UNICODE
RpcStringBindingCompose equ <RpcStringBindingComposeW>
else ;; UNICODE
RpcStringBindingCompose equ <RpcStringBindingComposeA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringBindingCompose proto _CType \
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	       Options: PVOID,
	 StringBinding: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;; client/server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringBindingParseA proto _CType \
	 StringBinding: PVOID,
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	NetworkOptions: PVOID

;RPC_STATUS
RpcStringBindingParseW proto _CType \
	 StringBinding: PVOID,
	       ObjUuid: LPWORD,
	       Protseq: LPWORD,
	   NetworkAddr: LPWORD,
	      Endpoint: LPWORD,
	NetworkOptions: LPWORD

ifdef _UNICODE
RpcStringBindingParse	equ <RpcStringBindingParseW>
else ;; UNICODE
RpcStringBindingParse	equ <RpcStringBindingParseA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringBindingParse proto _CType \
	 StringBinding: PVOID,
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	NetworkOptions: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;; client/server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringFreeA proto _CType \
		String: PVOID

;RPC_STATUS
RpcStringFreeW proto _CType \
		String: LPWORD

ifdef _UNICODE
RpcStringFree		equ <RpcStringFreeW>
else ;; UNICODE
RpcStringFree		equ <RpcStringFreeA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringFree proto _CType \
		String: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;; client/server
;RPC_STATUS
RpcIfInqId proto _CType \
	   RpcIfHandle: RPC_IF_HANDLE,
	       RpcIfId: ptr RPC_IF_ID

;; client/server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNetworkIsProtseqValidA proto _CType \
	       Protseq: PVOID

;RPC_STATUS
RpcNetworkIsProtseqValidW proto _CType \
	       Protseq: PVOID

ifdef _UNICODE
RpcNetworkIsProtseqValid equ <RpcNetworkIsProtseqValidW>
else ;; UNICODE
RpcNetworkIsProtseqValid equ <RpcNetworkIsProtseqValidA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNetworkIsProtseqValid proto _CType \
	       Protseq: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;; client
;RPC_STATUS
RpcMgmtInqComTimeout proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	       Timeout: ptr UINT

;; client
;RPC_STATUS
RpcMgmtSetComTimeout proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	       Timeout: UINT

;; client
;RPC_STATUS
RpcMgmtSetCancelTimeout proto _CType \
	       Timeout: LONG


;; server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNetworkInqProtseqsA proto _CType \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORA

;RPC_STATUS
RpcNetworkInqProtseqsW proto _CType \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORW

ifdef _UNICODE
RpcNetworkInqProtseqs	equ <RpcNetworkInqProtseqsW>
else ;; UNICODE
RpcNetworkInqProtseqs	equ <RpcNetworkInqProtseqsA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNetworkInqProtseqs proto _CType \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTOR

endif ;; RPC_UNICODE_SUPPORTED

;; server
;RPC_STATUS
RpcObjectInqType proto _CType \
	       ObjUuid: ptr UUID,
	      TypeUuid: ptr UUID

;; server
;RPC_STATUS
RpcObjectSetInqFn proto _CType \
	     InquiryFn: ptr RPC_OBJECT_INQ_FN

;; server
;RPC_STATUS
RpcObjectSetType proto _CType \
	       ObjUuid: ptr UUID,
	      TypeUuid: ptr UUID

;; server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcProtseqVectorFreeA proto _CType \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORA

;RPC_STATUS
RpcProtseqVectorFreeW proto _CType \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORW

ifdef _UNICODE
RpcProtseqVectorFree	equ <RpcProtseqVectorFreeW>
else ;; UNICODE
RpcProtseqVectorFree	equ <RpcProtseqVectorFreeA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcProtseqVectorFree proto _CType \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTOR

endif ;; RPC_UNICODE_SUPPORTED

;; server
;RPC_STATUS
RpcServerInqBindings proto _CType \
	 BindingVector: ptr RPC_BINDING_VECTOR

;; server
;RPC_STATUS
RpcServerInqIf proto _CType \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
		MgrEpv: ptr RPC_MGR_EPV

;; server
;RPC_STATUS
RpcServerListen proto _CType \
    MinimumCallThreads: UINT,
	      MaxCalls: UINT,
	      DontWait: UINT

;; server
;RPC_STATUS
RpcServerRegisterIf proto _CType \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
		MgrEpv: ptr RPC_MGR_EPV

;; server
;RPC_STATUS
RpcServerRegisterIfEx proto _CType \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
		MgrEpv: ptr RPC_MGR_EPV,
		 Flags: UINT,
	      MaxCalls: UINT,
	    IfCallback: ptr RPC_IF_CALLBACK_FN

;; server
;RPC_STATUS
RpcServerUnregisterIf proto _CType \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
WaitForCallsToComplete: UINT

;; server
;RPC_STATUS
RpcServerUseAllProtseqs proto _CType \
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;; server
;RPC_STATUS
RpcServerUseAllProtseqsEx proto _CType \
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;; server
;RPC_STATUS
RpcServerUseAllProtseqsIf proto _CType \
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;; server
;RPC_STATUS
RpcServerUseAllProtseqsIfEx proto _CType \
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY


;; server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqA proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqExA proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseProtseqW proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqExW proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

ifdef _UNICODE
RpcServerUseProtseq	equ <RpcServerUseProtseqW>
RpcServerUseProtseqEx	equ <RpcServerUseProtseqExW>
else ;; UNICODE
RpcServerUseProtseq	equ <RpcServerUseProtseqA>
RpcServerUseProtseqEx	equ <RpcServerUseProtseqExA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseq proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEx proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

endif ;; RPC_UNICODE_SUPPORTED

;; server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqEpA proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEpExA proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseProtseqEpW proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEpExW proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

ifdef _UNICODE
RpcServerUseProtseqEp	equ <RpcServerUseProtseqEpW>
RpcServerUseProtseqEpEx equ <RpcServerUseProtseqEpExW>
else ;; UNICODE
RpcServerUseProtseqEp	equ <RpcServerUseProtseqEpA>
RpcServerUseProtseqEpEx equ <RpcServerUseProtseqEpExA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqEp proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEpEx proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

endif ;; RPC_UNICODE_SUPPORTED

;; server

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqIfA proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqIfExA proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseProtseqIfW proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqIfExW proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

ifdef _UNICODE
RpcServerUseProtseqIf	equ <RpcServerUseProtseqIfW>
RpcServerUseProtseqIfEx equ <RpcServerUseProtseqIfExW>
else ;; UNICODE
RpcServerUseProtseqIf	equ <RpcServerUseProtseqIfA>
RpcServerUseProtseqIfEx equ <RpcServerUseProtseqIfExA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqIf proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqIfEx proto _CType \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

endif ;; RPC_UNICODE_SUPPORTED

;; server
;RPC_STATUS
RpcMgmtStatsVectorFree proto _CType \
	   StatsVector: ptr RPC_STATS_VECTOR

;; server
;RPC_STATUS
RpcMgmtInqStats proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	    Statistics: ptr RPC_STATS_VECTOR

;; server
;RPC_STATUS
RpcMgmtIsServerListening proto _CType \
	       Binding: RPC_BINDING_HANDLE

;; server
;RPC_STATUS
RpcMgmtStopServerListening proto _CType \
	       Binding: RPC_BINDING_HANDLE

;; server
;RPC_STATUS
RpcMgmtWaitServerListen proto _CType

;; server
;RPC_STATUS
RpcMgmtSetServerStackSize proto _CType \
       ThreadStackSize: DWORD

;; server
;void
RpcSsDontSerializeContext proto _CType

;; client
;RPC_STATUS
RpcMgmtEnableIdleCleanup proto _CType

;RPC_STATUS
RpcMgmtInqIfIds proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	    IfIdVector: ptr RPC_IF_ID_VECTOR

;RPC_STATUS
RpcIfIdVectorFree proto _CType \
	    IfIdVector: ptr RPC_IF_ID_VECTOR

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtInqServerPrincNameA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	      AuthnSvc: DWORD,
       ServerPrincName: PVOID

;RPC_STATUS
RpcMgmtInqServerPrincNameW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	      AuthnSvc: DWORD,
       ServerPrincName: LPWORD

ifdef _UNICODE
RpcMgmtInqServerPrincName equ <RpcMgmtInqServerPrincNameW>
else ;; UNICODE
RpcMgmtInqServerPrincName equ <RpcMgmtInqServerPrincNameA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtInqServerPrincName proto _CType \
	       Binding: RPC_BINDING_HANDLE,
	      AuthnSvc: DWORD,
       ServerPrincName: PVOID

endif ;; RPC_UNICODE_SUPPORTED

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerInqDefaultPrincNameA proto _CType \
	      AuthnSvc: DWORD,
	     PrincName: PVOID

;RPC_STATUS
RpcServerInqDefaultPrincNameW proto _CType \
	      AuthnSvc: DWORD,
	     PrincName: LPWORD

ifdef _UNICODE
RpcServerInqDefaultPrincName equ <RpcServerInqDefaultPrincNameW>
else ;; UNICODE
RpcServerInqDefaultPrincName equ <RpcServerInqDefaultPrincNameA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerInqDefaultPrincName proto _CType \
	      AuthnSvc: DWORD,
	     PrincName: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;; client
;RPC_STATUS
RpcEpResolveBinding proto _CType \
	       Binding: RPC_BINDING_HANDLE,
		IfSpec: RPC_IF_HANDLE

;; client

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsBindingInqEntryNameA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: DWORD,
	     EntryName: PVOID

;RPC_STATUS
RpcNsBindingInqEntryNameW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD

ifdef _UNICODE
RpcNsBindingInqEntryName equ <RpcNsBindingInqEntryNameW>
else ;; UNICODE
RpcNsBindingInqEntryName equ <RpcNsBindingInqEntryNameA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsBindingInqEntryName proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: DWORD,
	     EntryName: PVOID

endif ;; RPC_UNICODE_SUPPORTED

RPC_AUTH_IDENTITY_HANDLE typedef PVOID
RPC_AUTHZ_HANDLE	typedef PVOID

RPC_C_AUTHN_LEVEL_DEFAULT equ 0
RPC_C_AUTHN_LEVEL_NONE	equ 1
RPC_C_AUTHN_LEVEL_CONNECT equ 2
RPC_C_AUTHN_LEVEL_CALL	equ 3
RPC_C_AUTHN_LEVEL_PKT	equ 4
RPC_C_AUTHN_LEVEL_PKT_INTEGRITY equ 5
RPC_C_AUTHN_LEVEL_PKT_PRIVACY equ 6

RPC_C_IMP_LEVEL_ANONYMOUS equ 1
RPC_C_IMP_LEVEL_IDENTIFY equ 2
RPC_C_IMP_LEVEL_IMPERSONATE equ 3
RPC_C_IMP_LEVEL_DELEGATE equ 4

RPC_C_QOS_IDENTITY_STATIC equ 0
RPC_C_QOS_IDENTITY_DYNAMIC equ 1

RPC_C_QOS_CAPABILITIES_DEFAULT equ 0
RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH equ 1

RPC_C_PROTECT_LEVEL_DEFAULT	equ (RPC_C_AUTHN_LEVEL_DEFAULT)
RPC_C_PROTECT_LEVEL_NONE	equ (RPC_C_AUTHN_LEVE_NONE)
RPC_C_PROTECT_LEVEL_CONNECT	equ (RPC_C_AUTHN_LEVE_CONNECT)
RPC_C_PROTECT_LEVEL_CALL	equ (RPC_C_AUTHN_LEVEL_CALL)
RPC_C_PROTECT_LEVEL_PKT		equ (RPC_C_AUTHN_LEVE_PKT)
RPC_C_PROTECT_LEVEL_PKT_INTEGRITY equ (RPC_C_AUTHN_LEVEL_PKT_INTEGRITY)
RPC_C_PROTECT_LEVEL_PKT_PRIVACY equ (RPC_C_AUTHN_LEVE_PKT_PRIVACY)

RPC_C_AUTHN_NONE	equ 0
RPC_C_AUTHN_DCE_PRIVATE equ 1
RPC_C_AUTHN_DCE_PUBLIC	equ 2
RPC_C_AUTHN_DEC_PUBLIC	equ 4
RPC_C_AUTHN_WINNT	equ 10
RPC_C_AUTHN_DPA		equ 16
RPC_C_AUTHN_MSN		equ 17
RPC_C_AUTHN_GSS_KERBEROS equ 18
RPC_C_AUTHN_MQ		equ 100
RPC_C_AUTHN_DEFAULT	equ 0xFFFFFFFF

RPC_C_SECURITY_QOS_VERSION equ 1

RPC_SECURITY_QOS	STRUC
Version			dd ?
Capabilities		dd ?
IdentityTracking	dd ?
ImpersonationType	dd ?
RPC_SECURITY_QOS	ENDS
PRPC_SECURITY_QOS	typedef ptr RPC_SECURITY_QOS

if defined(__RPC_DOS__) OR defined(__RPC_WIN16__)
SEC_WINNT_AUTH_IDENTITY STRUC
User			LPSTR ?
Domain			LPSTR ?
Password		LPSTR ?
SEC_WINNT_AUTH_IDENTITY ENDS
else


SEC_WINNT_AUTH_IDENTITY_ANSI equ 0x1
SEC_WINNT_AUTH_IDENTITY_UNICODE equ 0x2

SEC_WINNT_AUTH_IDENTITY_W STRUC
UserLength		dd ?
DomainLength		dd ?
PasswordLength		dd ?
Flags			dd ?
SEC_WINNT_AUTH_IDENTITY_W ENDS
PSEC_WINNT_AUTH_IDENTITY_W typedef ptr SEC_WINNT_AUTH_IDENTITY_W

SEC_WINNT_AUTH_IDENTITY_A STRUC
UserLength		dd ?
DomainLength		dd ?
PasswordLength		dd ?
Flags			dd ?
SEC_WINNT_AUTH_IDENTITY_A ENDS
PSEC_WINNT_AUTH_IDENTITY_A typedef ptr SEC_WINNT_AUTH_IDENTITY_A


ifdef _UNICODE
SEC_WINNT_AUTH_IDENTITY	 equ SEC_WINNT_AUTH_IDENTITY_W
PSEC_WINNT_AUTH_IDENTITY equ PSEC_WINNT_AUTH_IDENTITY_W
_SEC_WINNT_AUTH_IDENTITY equ _SEC_WINNT_AUTH_IDENTITY_W
else ;; UNICODE
SEC_WINNT_AUTH_IDENTITY	 equ SEC_WINNT_AUTH_IDENTITY_A
PSEC_WINNT_AUTH_IDENTITY equ PSEC_WINNT_AUTH_IDENTITY_A
_SEC_WINNT_AUTH_IDENTITY equ _SEC_WINNT_AUTH_IDENTITY_A
endif ;; UNICODE
endif ;; defined(__RPC_DOS__) OR defined(__RPC_WIN16__)

RPC_C_AUTHZ_NONE	equ 0
RPC_C_AUTHZ_NAME	equ 1
RPC_C_AUTHZ_DCE		equ 2

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingInqAuthClientA proto _CType \
	 ClientBinding: RPC_BINDING_HANDLE,
		 Privs: ptr RPC_AUTHZ_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthClientW proto _CType \
	 ClientBinding: RPC_BINDING_HANDLE,
		 Privs: ptr RPC_AUTHZ_HANDLE,
       ServerPrincName: LPWORD,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthInfoA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthInfoW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: LPWORD,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingSetAuthInfoA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD

;RPC_STATUS
RpcBindingSetAuthInfoExA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD,
	   SecurityQos: ptr RPC_SECURITY_QOS

;RPC_STATUS
RpcBindingSetAuthInfoW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD

;RPC_STATUS
RpcBindingSetAuthInfoExW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD,
	   SecurityQOS: ptr RPC_SECURITY_QOS

;RPC_STATUS
RpcBindingInqAuthInfoExA proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD,
	 RpcQosVersion: DWORD,
	   SecurityQOS: ptr RPC_SECURITY_QOS

;RPC_STATUS
RpcBindingInqAuthInfoExW proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: LPWORD,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD,
	 RpcQosVersion: DWORD,
	   SecurityQOS: ptr RPC_SECURITY_QOS


RPC_AUTH_KEY_RETRIEVAL_FN_T typedef proto _CType \
		   Arg: PVOID,
       ServerPrincName: PVOID,
		KeyVer: DWORD,
		   Key: PVOID,
		Status: ptr RPC_STATUS

RPC_AUTH_KEY_RETRIEVAL_FN typedef ptr RPC_AUTH_KEY_RETRIEVAL_FN_T
;RPC_STATUS
RpcServerRegisterAuthInfoA proto _CType \
       ServerPrincName: PVOID,
	      AuthnSvc: DWORD,
	      GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN,
		   Arg: PVOID

;RPC_STATUS
RpcServerRegisterAuthInfoW proto _CType \
       ServerPrincName: PVOID,
	      AuthnSvc: DWORD,
	      GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN,
		   Arg: PVOID

ifdef _UNICODE
RpcBindingInqAuthClient equ <RpcBindingInqAuthClientW>
RpcBindingInqAuthInfo	equ <RpcBindingInqAuthInfoW>
RpcBindingSetAuthInfo	equ <RpcBindingSetAuthInfoW>
RpcServerRegisterAuthInfo equ <RpcServerRegisterAuthInfoW>
RpcBindingInqAuthInfoEx equ <RpcBindingInqAuthInfoExW>
RpcBindingSetAuthInfoEx equ <RpcBindingSetAuthInfoExW>
else ;; UNICODE
RpcBindingInqAuthClient equ <RpcBindingInqAuthClientA>
RpcBindingInqAuthInfo	equ <RpcBindingInqAuthInfoA>
RpcBindingSetAuthInfo	equ <RpcBindingSetAuthInfoA>
RpcServerRegisterAuthInfo equ <RpcServerRegisterAuthInfoA>
RpcBindingInqAuthInfoEx equ <RpcBindingInqAuthInfoExA>
RpcBindingSetAuthInfoEx equ <RpcBindingSetAuthInfoExA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingInqAuthClient proto _CType \
	 ClientBinding: RPC_BINDING_HANDLE,
		 Privs: ptr RPC_AUTHZ_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthInfo proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE*,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingSetAuthInfo proto _CType \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD


RPC_AUTH_KEY_RETRIEVAL_FN_T typedef proto _CType \
		   Arg: PVOID,
       ServerPrincName: PVOID,
		KeyVer: DWORD,
		   Key: PVOID,
		Status: ptr RPC_STATUS

RPC_AUTH_KEY_RETRIEVAL_FN typedef ptr RPC_AUTH_KEY_RETRIEVAL_FN_T

;RPC_STATUS
RpcServerRegisterAuthInfo proto _CType \
       ServerPrincName: PVOID,
	      AuthnSvc: DWORD,
	      GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN,
		   Arg: PVOID

endif ;; RPC_UNICODE_SUPPORTED

RPC_CLIENT_INFORMATION1 STRUC
UserName		LPBYTE ?
ComputerName		LPBYTE ?
Privilege		dw ?
AuthFlags		dd ?
RPC_CLIENT_INFORMATION1 ENDS
PRPC_CLIENT_INFORMATION1 typedef ptr RPC_CLIENT_INFORMATION1

;RPC_STATUS
RpcBindingServerFromClient proto _CType \
	 ClientBinding: RPC_BINDING_HANDLE,
	 ServerBinding: ptr RPC_BINDING_HANDLE

;void
RpcRaiseException proto _CType \
	     exception: RPC_STATUS

;RPC_STATUS
RpcTestCancel proto _CType

;RPC_STATUS
RpcServerTestCancel proto _CType \
	 BindingHandle: RPC_BINDING_HANDLE

;RPC_STATUS
RpcCancelThread proto _CType \
		Thread: PVOID

;; client/server
;RPC_STATUS
UuidCreate proto _CType \
		  Uuid: ptr UUID

ifdef RPC_UNICODE_SUPPORTED

;; client/server
;RPC_STATUS
UuidToStringA proto _CType \
		  Uuid: ptr UUID,
	    StringUuid: PVOID

;; client/server
;RPC_STATUS
UuidFromStringA proto _CType \
	    StringUuid: PVOID,
		  Uuid: ptr UUID

;; client/server
;RPC_STATUS
UuidToStringW proto _CType \
		  Uuid: ptr UUID,
	    StringUuid: LPWORD

;; client/server
;RPC_STATUS
UuidFromStringW proto _CType \
	    StringUuid: PVOID,
		  Uuid: ptr UUID

ifdef _UNICODE
UuidFromString		equ <UuidFromStringW>
UuidToString		equ <UuidToStringW>
else ;; UNICODE
UuidFromString		equ <UuidFromStringA>
UuidToString		equ <UuidToStringA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;; client/server
;RPC_STATUS
UuidToString proto _CType \
		  Uuid: ptr UUID,
	    StringUuid: PVOID

;; client/server
;RPC_STATUS
UuidFromString proto _CType \
	    StringUuid: PVOID,
		  Uuid: ptr UUID

endif ;; RPC_UNICODE_SUPPORTED

;signed
UuidCompare proto _CType \
		 Uuid1: ptr UUID,
		 Uuid2: ptr UUID,
		Status: ptr RPC_STATUS

;RPC_STATUS
UuidCreateNil proto _CType \
	       NilUuid: ptr UUID

;int
UuidEqual proto _CType \
		 Uuid1: ptr UUID,
		 Uuid2: ptr UUID,
		Status: ptr RPC_STATUS

;WORD
UuidHash proto _CType \
		  Uuid: ptr UUID,
		Status: ptr RPC_STATUS

;int
UuidIsNil proto _CType \
		  Uuid: ptr UUID,
		Status: ptr RPC_STATUS

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcEpRegisterNoReplaceA proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

;RPC_STATUS
RpcEpRegisterNoReplaceW proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPWORD

;RPC_STATUS
RpcEpRegisterA proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

;RPC_STATUS
RpcEpRegisterW proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPWORD

ifdef _UNICODE
RpcEpRegisterNoReplace	equ <RpcEpRegisterNoReplaceW>
RpcEpRegister		equ <RpcEpRegisterW>
else ;; UNICODE
RpcEpRegisterNoReplace	equ <RpcEpRegisterNoReplaceA>
RpcEpRegister		equ <RpcEpRegisterA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcEpRegisterNoReplace proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

;RPC_STATUS
RpcEpRegister proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

endif ;; RPC_UNICODE_SUPPORTED


;RPC_STATUS
RpcEpUnregister proto _CType \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
DceErrorInqTextA proto _CType \
	     RpcStatus: RPC_STATUS,
	     ErrorText: LPBYTE

;RPC_STATUS
DceErrorInqTextW proto _CType \
	     RpcStatus: RPC_STATUS,
	     ErrorText: LPWORD

ifdef _UNICODE
DceErrorInqText		equ <DceErrorInqTextW>
else ;; UNICODE
DceErrorInqText		equ <DceErrorInqTextA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
DceErrorInqText proto _CType \
	     RpcStatus: RPC_STATUS,
	     ErrorText: LPBYTE

endif ;; RPC_UNICODE_SUPPORTED

DCE_C_ERROR_STRING_LEN	equ 256

RPC_EP_INQ_HANDLE	typedef ptr I_RPC_HANDLE

RPC_C_EP_ALL_ELTS	equ 0
RPC_C_EP_MATCH_BY_IF	equ 1
RPC_C_EP_MATCH_BY_OBJ	equ 2
RPC_C_EP_MATCH_BY_BOTH	equ 3

RPC_C_VERS_ALL		equ 1
RPC_C_VERS_COMPATIBLE	equ 2
RPC_C_VERS_EXACT	equ 3
RPC_C_VERS_MAJOR_ONLY	equ 4
RPC_C_VERS_UPTO		equ 5

;RPC_STATUS
RpcMgmtEpEltInqBegin proto _CType \
	     EpBinding: RPC_BINDING_HANDLE,
	   InquiryType: DWORD,
		  IfId: ptr RPC_IF_ID,
	    VersOption: DWORD,
	    ObjectUuid: ptr UUID,
	InquiryContext: ptr RPC_EP_INQ_HANDLE

;RPC_STATUS
RpcMgmtEpEltInqDone proto _CType \
	InquiryContext: ptr RPC_EP_INQ_HANDLE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtEpEltInqNextA proto _CType \
	InquiryContext: RPC_EP_INQ_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: ptr RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID,
	    Annotation: PVOID

;RPC_STATUS
RpcMgmtEpEltInqNextW proto _CType \
	InquiryContext: RPC_EP_INQ_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: ptr RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID,
	    Annotation: LPWORD

ifdef _UNICODE
RpcMgmtEpEltInqNext	equ <RpcMgmtEpEltInqNextW>
else ;; UNICODE
RpcMgmtEpEltInqNext	equ <RpcMgmtEpEltInqNextA>
endif ;; UNICODE

else ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtEpEltInqNext proto _CType \
	InquiryContext: RPC_EP_INQ_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: ptr RPC_BINDING_HANDLE,
	    Annotation: PVOID

endif ;; RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtEpUnregister proto _CType \
	     EpBinding: RPC_BINDING_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID

RPC_MGMT_AUTHORIZATION_FN_T typedef proto _CType \
	 ClientBinding: RPC_BINDING_HANDLE,
RequestedMgmtOperation: DWORD,
		Status: ptr RPC_STATUS

RPC_MGMT_AUTHORIZATION_FN typedef ptr RPC_MGMT_AUTHORIZATION_FN_T

RPC_C_MGMT_INQ_IF_IDS		equ 0
RPC_C_MGMT_INQ_PRINC_NAME	equ 1
RPC_C_MGMT_INQ_STATS		equ 2
RPC_C_MGMT_IS_SERVER_LISTEN	equ 3
RPC_C_MGMT_STOP_SERVER_LISTEN	equ 4

;RPC_STATUS
RpcMgmtSetAuthorizationFn proto _CType \
       AuthorizationFn: RPC_MGMT_AUTHORIZATION_FN


RPC_C_PARM_MAX_PACKET_LENGTH equ 1
RPC_C_PARM_BUFFER_LENGTH equ 2

;RPC_STATUS
RpcMgmtInqParameter proto _CType \
	     Parameter: UINT,
		 Value: LPDWORD

;RPC_STATUS
RpcMgmtSetParameter proto _CType \
	     Parameter: UINT,
		 Value: DWORD

;RPC_STATUS
RpcMgmtBindingInqParameter proto _CType \
		Handle: RPC_BINDING_HANDLE,
	     Parameter: UINT,
		 Value: LPDWORD

;RPC_STATUS
RpcMgmtBindingSetParameter proto _CType \
		Handle: RPC_BINDING_HANDLE,
	     Parameter: UINT,
		 Value: DWORD

RPC_IF_AUTOLISTEN	equ 0x0001
RPC_IF_OLE		equ 0x0002

include rpcdcep.inc

endif ;; __RPCDCE_H__

.list
