ifndef __LIBC_INC
 include libc.inc
endif
.xlist
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
endif

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

RPC_C_BIND_TO_ALL_NICS		equ 1
RPC_C_USE_INTERNET_PORT		equ 1
RPC_C_USE_INTRANET_PORT		equ 2

RPC_C_MQ_TEMPORARY		equ 0x0000
RPC_C_MQ_PERMANENT		equ 0x0001
RPC_C_MQ_CLEAR_ON_OPEN		equ 0x0002
RPC_C_MQ_USE_EXISTING_SECURITY	equ 0x0004
RPC_C_MQ_AUTHN_LEVEL_NONE	equ 0x0000
RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY equ 0x0008
RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY equ 0x0010

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

RPC_C_MQ_EXPRESS		equ 0
RPC_C_MQ_RECOVERABLE		equ 1

RPC_C_MQ_JOURNAL_NONE		equ 0
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
else
RPC_PROTSEQ_VECTOR	equ <RPC_PROTSEQ_VECTORA>
endif

else

RPC_PROTSEQ_VECTOR	STRUC
Count			UINT ?
Protseq			LPBYTE ?
RPC_PROTSEQ_VECTOR	ENDS

endif
RPC_POLICY		STRUC
_Length			UINT ?
EndpointFlags		dd ?
NICFlags		dd ?
RPC_POLICY		ENDS
PRPC_POLICY		typedef ptr RPC_POLICY

CALLBACK(RPC_OBJECT_INQ_FN, ObjectUuid:ptr UUID, TypeUuid:ptr UUID, Status: ptr RPC_STATUS)
CALLBACK(RPC_IF_CALLBACK_FN, InterfaceUuid:RPC_IF_HANDLE, Context: PVOID)

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

;RPC_STATUS
RpcBindingCopy proto WINAPI \
	 SourceBinding: RPC_BINDING_HANDLE,
    DestinationBinding: ptr RPC_BINDING_HANDLE

;RPC_STATUS
RpcBindingFree proto WINAPI \
	       Binding: ptr RPC_BINDING_HANDLE

;RPC_STATUS
RpcBindingSetOption proto WINAPI \
	      hBinding: RPC_BINDING_HANDLE,
	       _option: DWORD,
	   optionValue: DWORD

;RPC_STATUS
RpcBindingInqOption proto WINAPI \
	      hBinding: RPC_BINDING_HANDLE,
	       _option: DWORD,
	  pOptionValue: LPDWORD


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingFromStringBindingA proto WINAPI \
	 StringBinding: PVOID,
	       Binding: ptr RPC_BINDING_HANDLE

;RPC_STATUS
RpcBindingFromStringBindingW proto WINAPI \
	 StringBinding: PVOID,
	       Binding: ptr RPC_BINDING_HANDLE

ifdef _UNICODE
RpcBindingFromStringBinding equ <RpcBindingFromStringBindingW>
else
RpcBindingFromStringBinding equ <RpcBindingFromStringBindingA>
endif

else

;RPC_STATUS
RpcBindingFromStringBinding proto WINAPI \
	 StringBinding: PVOID,
	       Binding: ptr RPC_BINDING_HANDLE

endif

;RPC_STATUS
RpcBindingInqObject proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID

;RPC_STATUS
RpcBindingReset proto WINAPI \
	       Binding: RPC_BINDING_HANDLE


;RPC_STATUS
RpcBindingSetObject proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID

;RPC_STATUS
RpcMgmtInqDefaultProtectLevel proto WINAPI \
	      AuthnSvc: DWORD,
	    AuthnLevel: LPDWORD


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingToStringBindingA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	 StringBinding: PVOID

;RPC_STATUS
RpcBindingToStringBindingW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	 StringBinding: LPWORD

ifdef _UNICODE
RpcBindingToStringBinding equ <RpcBindingToStringBindingW>
else
RpcBindingToStringBinding equ <RpcBindingToStringBindingA>
endif

else

;RPC_STATUS
RpcBindingToStringBinding proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	 StringBinding: PVOID

endif

;RPC_STATUS
RpcBindingVectorFree proto WINAPI \
	 BindingVector: ptr RPC_BINDING_VECTOR


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringBindingComposeA proto WINAPI \
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	       Options: PVOID,
	 StringBinding: PVOID

;RPC_STATUS
RpcStringBindingComposeW proto WINAPI \
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	       Options: PVOID,
	 StringBinding: LPWORD

ifdef _UNICODE
RpcStringBindingCompose equ <RpcStringBindingComposeW>
else
RpcStringBindingCompose equ <RpcStringBindingComposeA>
endif

else

;RPC_STATUS
RpcStringBindingCompose proto WINAPI \
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	       Options: PVOID,
	 StringBinding: PVOID

endif


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringBindingParseA proto WINAPI \
	 StringBinding: PVOID,
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	NetworkOptions: PVOID

;RPC_STATUS
RpcStringBindingParseW proto WINAPI \
	 StringBinding: PVOID,
	       ObjUuid: LPWORD,
	       Protseq: LPWORD,
	   NetworkAddr: LPWORD,
	      Endpoint: LPWORD,
	NetworkOptions: LPWORD

ifdef _UNICODE
RpcStringBindingParse	equ <RpcStringBindingParseW>
else
RpcStringBindingParse	equ <RpcStringBindingParseA>
endif

else

;RPC_STATUS
RpcStringBindingParse proto WINAPI \
	 StringBinding: PVOID,
	       ObjUuid: PVOID,
	       Protseq: PVOID,
	   NetworkAddr: PVOID,
	      Endpoint: PVOID,
	NetworkOptions: PVOID

endif


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcStringFreeA proto WINAPI \
		String: PVOID

;RPC_STATUS
RpcStringFreeW proto WINAPI \
		String: LPWORD

ifdef _UNICODE
RpcStringFree		equ <RpcStringFreeW>
else
RpcStringFree		equ <RpcStringFreeA>
endif

else

;RPC_STATUS
RpcStringFree proto WINAPI \
		String: PVOID

endif

;RPC_STATUS
RpcIfInqId proto WINAPI \
	   RpcIfHandle: RPC_IF_HANDLE,
	       RpcIfId: ptr RPC_IF_ID


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNetworkIsProtseqValidA proto WINAPI \
	       Protseq: PVOID

;RPC_STATUS
RpcNetworkIsProtseqValidW proto WINAPI \
	       Protseq: PVOID

ifdef _UNICODE
RpcNetworkIsProtseqValid equ <RpcNetworkIsProtseqValidW>
else
RpcNetworkIsProtseqValid equ <RpcNetworkIsProtseqValidA>
endif

else

;RPC_STATUS
RpcNetworkIsProtseqValid proto WINAPI \
	       Protseq: PVOID

endif

;RPC_STATUS
RpcMgmtInqComTimeout proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	       Timeout: ptr UINT

;RPC_STATUS
RpcMgmtSetComTimeout proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	       Timeout: UINT

;RPC_STATUS
RpcMgmtSetCancelTimeout proto WINAPI \
	       Timeout: LONG



ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNetworkInqProtseqsA proto WINAPI \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORA

;RPC_STATUS
RpcNetworkInqProtseqsW proto WINAPI \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORW

ifdef _UNICODE
RpcNetworkInqProtseqs	equ <RpcNetworkInqProtseqsW>
else
RpcNetworkInqProtseqs	equ <RpcNetworkInqProtseqsA>
endif

else

;RPC_STATUS
RpcNetworkInqProtseqs proto WINAPI \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTOR

endif

;RPC_STATUS
RpcObjectInqType proto WINAPI \
	       ObjUuid: ptr UUID,
	      TypeUuid: ptr UUID

;RPC_STATUS
RpcObjectSetInqFn proto WINAPI \
	     InquiryFn: ptr RPC_OBJECT_INQ_FN

;RPC_STATUS
RpcObjectSetType proto WINAPI \
	       ObjUuid: ptr UUID,
	      TypeUuid: ptr UUID


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcProtseqVectorFreeA proto WINAPI \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORA

;RPC_STATUS
RpcProtseqVectorFreeW proto WINAPI \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTORW

ifdef _UNICODE
RpcProtseqVectorFree	equ <RpcProtseqVectorFreeW>
else
RpcProtseqVectorFree	equ <RpcProtseqVectorFreeA>
endif

else

;RPC_STATUS
RpcProtseqVectorFree proto WINAPI \
	 ProtseqVector: ptr RPC_PROTSEQ_VECTOR

endif

;RPC_STATUS
RpcServerInqBindings proto WINAPI \
	 BindingVector: ptr RPC_BINDING_VECTOR

;RPC_STATUS
RpcServerInqIf proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
		MgrEpv: ptr RPC_MGR_EPV

;RPC_STATUS
RpcServerListen proto WINAPI \
    MinimumCallThreads: UINT,
	      MaxCalls: UINT,
	      DontWait: UINT

;RPC_STATUS
RpcServerRegisterIf proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
		MgrEpv: ptr RPC_MGR_EPV

;RPC_STATUS
RpcServerRegisterIfEx proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
		MgrEpv: ptr RPC_MGR_EPV,
		 Flags: UINT,
	      MaxCalls: UINT,
	    IfCallback: ptr RPC_IF_CALLBACK_FN

;RPC_STATUS
RpcServerUnregisterIf proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	   MgrTypeUuid: ptr UUID,
WaitForCallsToComplete: UINT

;RPC_STATUS
RpcServerUseAllProtseqs proto WINAPI \
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseAllProtseqsEx proto WINAPI \
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseAllProtseqsIf proto WINAPI \
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseAllProtseqsIfEx proto WINAPI \
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY



ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqA proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqExA proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseProtseqW proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqExW proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

ifdef _UNICODE
RpcServerUseProtseq	equ <RpcServerUseProtseqW>
RpcServerUseProtseqEx	equ <RpcServerUseProtseqExW>
else
RpcServerUseProtseq	equ <RpcServerUseProtseqA>
RpcServerUseProtseqEx	equ <RpcServerUseProtseqExA>
endif

else

;RPC_STATUS
RpcServerUseProtseq proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEx proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

endif


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqEpA proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEpExA proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseProtseqEpW proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEpExW proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

ifdef _UNICODE
RpcServerUseProtseqEp	equ <RpcServerUseProtseqEpW>
RpcServerUseProtseqEpEx equ <RpcServerUseProtseqEpExW>
else
RpcServerUseProtseqEp	equ <RpcServerUseProtseqEpA>
RpcServerUseProtseqEpEx equ <RpcServerUseProtseqEpExA>
endif

else

;RPC_STATUS
RpcServerUseProtseqEp proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqEpEx proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
	      Endpoint: PVOID,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

endif


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerUseProtseqIfA proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqIfExA proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

;RPC_STATUS
RpcServerUseProtseqIfW proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqIfExW proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

ifdef _UNICODE
RpcServerUseProtseqIf	equ <RpcServerUseProtseqIfW>
RpcServerUseProtseqIfEx equ <RpcServerUseProtseqIfExW>
else
RpcServerUseProtseqIf	equ <RpcServerUseProtseqIfA>
RpcServerUseProtseqIfEx equ <RpcServerUseProtseqIfExA>
endif

else

;RPC_STATUS
RpcServerUseProtseqIf proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID

;RPC_STATUS
RpcServerUseProtseqIfEx proto WINAPI \
	       Protseq: PVOID,
	      MaxCalls: UINT,
		IfSpec: RPC_IF_HANDLE,
    SecurityDescriptor: PVOID,
		Policy: PRPC_POLICY

endif

;RPC_STATUS
RpcMgmtStatsVectorFree proto WINAPI \
	   StatsVector: ptr RPC_STATS_VECTOR

;RPC_STATUS
RpcMgmtInqStats proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	    Statistics: ptr RPC_STATS_VECTOR

;RPC_STATUS
RpcMgmtIsServerListening proto WINAPI \
	       Binding: RPC_BINDING_HANDLE

;RPC_STATUS
RpcMgmtStopServerListening proto WINAPI \
	       Binding: RPC_BINDING_HANDLE

;RPC_STATUS
RpcMgmtWaitServerListen proto WINAPI

;RPC_STATUS
RpcMgmtSetServerStackSize proto WINAPI \
       ThreadStackSize: DWORD

;void
RpcSsDontSerializeContext proto WINAPI

;RPC_STATUS
RpcMgmtEnableIdleCleanup proto WINAPI

;RPC_STATUS
RpcMgmtInqIfIds proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	    IfIdVector: ptr RPC_IF_ID_VECTOR

;RPC_STATUS
RpcIfIdVectorFree proto WINAPI \
	    IfIdVector: ptr RPC_IF_ID_VECTOR

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtInqServerPrincNameA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	      AuthnSvc: DWORD,
       ServerPrincName: PVOID

;RPC_STATUS
RpcMgmtInqServerPrincNameW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	      AuthnSvc: DWORD,
       ServerPrincName: LPWORD

ifdef _UNICODE
RpcMgmtInqServerPrincName equ <RpcMgmtInqServerPrincNameW>
else
RpcMgmtInqServerPrincName equ <RpcMgmtInqServerPrincNameA>
endif

else

;RPC_STATUS
RpcMgmtInqServerPrincName proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
	      AuthnSvc: DWORD,
       ServerPrincName: PVOID

endif

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcServerInqDefaultPrincNameA proto WINAPI \
	      AuthnSvc: DWORD,
	     PrincName: PVOID

;RPC_STATUS
RpcServerInqDefaultPrincNameW proto WINAPI \
	      AuthnSvc: DWORD,
	     PrincName: LPWORD

ifdef _UNICODE
RpcServerInqDefaultPrincName equ <RpcServerInqDefaultPrincNameW>
else
RpcServerInqDefaultPrincName equ <RpcServerInqDefaultPrincNameA>
endif

else

;RPC_STATUS
RpcServerInqDefaultPrincName proto WINAPI \
	      AuthnSvc: DWORD,
	     PrincName: PVOID

endif

;RPC_STATUS
RpcEpResolveBinding proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
		IfSpec: RPC_IF_HANDLE


ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcNsBindingInqEntryNameA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: DWORD,
	     EntryName: PVOID

;RPC_STATUS
RpcNsBindingInqEntryNameW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: DWORD,
	     EntryName: LPWORD

ifdef _UNICODE
RpcNsBindingInqEntryName equ <RpcNsBindingInqEntryNameW>
else
RpcNsBindingInqEntryName equ <RpcNsBindingInqEntryNameA>
endif

else

;RPC_STATUS
RpcNsBindingInqEntryName proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       EntryNameSyntax: DWORD,
	     EntryName: PVOID

endif

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
else
SEC_WINNT_AUTH_IDENTITY	 equ SEC_WINNT_AUTH_IDENTITY_A
PSEC_WINNT_AUTH_IDENTITY equ PSEC_WINNT_AUTH_IDENTITY_A
_SEC_WINNT_AUTH_IDENTITY equ _SEC_WINNT_AUTH_IDENTITY_A
endif
endif

RPC_C_AUTHZ_NONE	equ 0
RPC_C_AUTHZ_NAME	equ 1
RPC_C_AUTHZ_DCE		equ 2

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcBindingInqAuthClientA proto WINAPI \
	 ClientBinding: RPC_BINDING_HANDLE,
		 Privs: ptr RPC_AUTHZ_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthClientW proto WINAPI \
	 ClientBinding: RPC_BINDING_HANDLE,
		 Privs: ptr RPC_AUTHZ_HANDLE,
       ServerPrincName: LPWORD,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthInfoA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthInfoW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: LPWORD,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingSetAuthInfoA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD

;RPC_STATUS
RpcBindingSetAuthInfoExA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD,
	   SecurityQos: ptr RPC_SECURITY_QOS

;RPC_STATUS
RpcBindingSetAuthInfoW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD

;RPC_STATUS
RpcBindingSetAuthInfoExW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD,
	   SecurityQOS: ptr RPC_SECURITY_QOS

;RPC_STATUS
RpcBindingInqAuthInfoExA proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD,
	 RpcQosVersion: DWORD,
	   SecurityQOS: ptr RPC_SECURITY_QOS

;RPC_STATUS
RpcBindingInqAuthInfoExW proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: LPWORD,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: ptr RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: LPDWORD,
	 RpcQosVersion: DWORD,
	   SecurityQOS: ptr RPC_SECURITY_QOS


CALLBACK(RPC_AUTH_KEY_RETRIEVAL_FN, Arg:PVOID, ServerPrincName:PVOID, KeyVer:DWORD, Key:PVOID, Status: ptr RPC_STATUS)

;RPC_STATUS
RpcServerRegisterAuthInfoA proto WINAPI \
       ServerPrincName: PVOID,
	      AuthnSvc: DWORD,
	      GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN,
		   Arg: PVOID

;RPC_STATUS
RpcServerRegisterAuthInfoW proto WINAPI \
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
else
RpcBindingInqAuthClient equ <RpcBindingInqAuthClientA>
RpcBindingInqAuthInfo	equ <RpcBindingInqAuthInfoA>
RpcBindingSetAuthInfo	equ <RpcBindingSetAuthInfoA>
RpcServerRegisterAuthInfo equ <RpcServerRegisterAuthInfoA>
RpcBindingInqAuthInfoEx equ <RpcBindingInqAuthInfoExA>
RpcBindingSetAuthInfoEx equ <RpcBindingSetAuthInfoExA>
endif

else

;RPC_STATUS
RpcBindingInqAuthClient proto WINAPI \
	 ClientBinding: RPC_BINDING_HANDLE,
		 Privs: ptr RPC_AUTHZ_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingInqAuthInfo proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: LPDWORD,
	      AuthnSvc: LPDWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE*,
	      AuthzSvc: LPDWORD

;RPC_STATUS
RpcBindingSetAuthInfo proto WINAPI \
	       Binding: RPC_BINDING_HANDLE,
       ServerPrincName: PVOID,
	    AuthnLevel: DWORD,
	      AuthnSvc: DWORD,
	  AuthIdentity: RPC_AUTH_IDENTITY_HANDLE,
	      AuthzSvc: DWORD


CALLBACK(RPC_AUTH_KEY_RETRIEVAL_FN, Arg:PVOID, ServerPrincName:PVOID, KeyVer:DWORD, Key:PVOID, Status:ptr RPC_STATUS)

;RPC_STATUS
RpcServerRegisterAuthInfo proto WINAPI \
       ServerPrincName: PVOID,
	      AuthnSvc: DWORD,
	      GetKeyFn: RPC_AUTH_KEY_RETRIEVAL_FN,
		   Arg: PVOID

endif

RPC_CLIENT_INFORMATION1 STRUC
UserName		LPBYTE ?
ComputerName		LPBYTE ?
Privilege		dw ?
AuthFlags		dd ?
RPC_CLIENT_INFORMATION1 ENDS
PRPC_CLIENT_INFORMATION1 typedef ptr RPC_CLIENT_INFORMATION1

;RPC_STATUS
RpcBindingServerFromClient proto WINAPI \
	 ClientBinding: RPC_BINDING_HANDLE,
	 ServerBinding: ptr RPC_BINDING_HANDLE

;void
RpcRaiseException proto WINAPI \
	     exception: RPC_STATUS

;RPC_STATUS
RpcTestCancel proto WINAPI

;RPC_STATUS
RpcServerTestCancel proto WINAPI \
	 BindingHandle: RPC_BINDING_HANDLE

;RPC_STATUS
RpcCancelThread proto WINAPI \
		Thread: PVOID

;RPC_STATUS
UuidCreate proto WINAPI \
		  Uuid: ptr UUID

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
UuidToStringA proto WINAPI \
		  Uuid: ptr UUID,
	    StringUuid: PVOID

;RPC_STATUS
UuidFromStringA proto WINAPI \
	    StringUuid: PVOID,
		  Uuid: ptr UUID

;RPC_STATUS
UuidToStringW proto WINAPI \
		  Uuid: ptr UUID,
	    StringUuid: LPWORD

;RPC_STATUS
UuidFromStringW proto WINAPI \
	    StringUuid: PVOID,
		  Uuid: ptr UUID

ifdef _UNICODE
UuidFromString		equ <UuidFromStringW>
UuidToString		equ <UuidToStringW>
else
UuidFromString		equ <UuidFromStringA>
UuidToString		equ <UuidToStringA>
endif

else

;RPC_STATUS
UuidToString proto WINAPI \
		  Uuid: ptr UUID,
	    StringUuid: PVOID

;RPC_STATUS
UuidFromString proto WINAPI \
	    StringUuid: PVOID,
		  Uuid: ptr UUID

endif

;signed
UuidCompare proto WINAPI \
		 Uuid1: ptr UUID,
		 Uuid2: ptr UUID,
		Status: ptr RPC_STATUS

;RPC_STATUS
UuidCreateNil proto WINAPI \
	       NilUuid: ptr UUID

;int
UuidEqual proto WINAPI \
		 Uuid1: ptr UUID,
		 Uuid2: ptr UUID,
		Status: ptr RPC_STATUS

;WORD
UuidHash proto WINAPI \
		  Uuid: ptr UUID,
		Status: ptr RPC_STATUS

;int
UuidIsNil proto WINAPI \
		  Uuid: ptr UUID,
		Status: ptr RPC_STATUS

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcEpRegisterNoReplaceA proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

;RPC_STATUS
RpcEpRegisterNoReplaceW proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPWORD

;RPC_STATUS
RpcEpRegisterA proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

;RPC_STATUS
RpcEpRegisterW proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPWORD

ifdef _UNICODE
RpcEpRegisterNoReplace	equ <RpcEpRegisterNoReplaceW>
RpcEpRegister		equ <RpcEpRegisterW>
else
RpcEpRegisterNoReplace	equ <RpcEpRegisterNoReplaceA>
RpcEpRegister		equ <RpcEpRegisterA>
endif

else

;RPC_STATUS
RpcEpRegisterNoReplace proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

;RPC_STATUS
RpcEpRegister proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR,
	    Annotation: LPBYTE

endif


;RPC_STATUS
RpcEpUnregister proto WINAPI \
		IfSpec: RPC_IF_HANDLE,
	 BindingVector: ptr RPC_BINDING_VECTOR,
	    UuidVector: ptr UUID_VECTOR

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
DceErrorInqTextA proto WINAPI \
	     RpcStatus: RPC_STATUS,
	     ErrorText: LPBYTE

;RPC_STATUS
DceErrorInqTextW proto WINAPI \
	     RpcStatus: RPC_STATUS,
	     ErrorText: LPWORD

ifdef _UNICODE
DceErrorInqText		equ <DceErrorInqTextW>
else
DceErrorInqText		equ <DceErrorInqTextA>
endif

else

;RPC_STATUS
DceErrorInqText proto WINAPI \
	     RpcStatus: RPC_STATUS,
	     ErrorText: LPBYTE

endif

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
RpcMgmtEpEltInqBegin proto WINAPI \
	     EpBinding: RPC_BINDING_HANDLE,
	   InquiryType: DWORD,
		  IfId: ptr RPC_IF_ID,
	    VersOption: DWORD,
	    ObjectUuid: ptr UUID,
	InquiryContext: ptr RPC_EP_INQ_HANDLE

;RPC_STATUS
RpcMgmtEpEltInqDone proto WINAPI \
	InquiryContext: ptr RPC_EP_INQ_HANDLE

ifdef RPC_UNICODE_SUPPORTED

;RPC_STATUS
RpcMgmtEpEltInqNextA proto WINAPI \
	InquiryContext: RPC_EP_INQ_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: ptr RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID,
	    Annotation: PVOID

;RPC_STATUS
RpcMgmtEpEltInqNextW proto WINAPI \
	InquiryContext: RPC_EP_INQ_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: ptr RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID,
	    Annotation: LPWORD

ifdef _UNICODE
RpcMgmtEpEltInqNext	equ <RpcMgmtEpEltInqNextW>
else
RpcMgmtEpEltInqNext	equ <RpcMgmtEpEltInqNextA>
endif

else

;RPC_STATUS
RpcMgmtEpEltInqNext proto WINAPI \
	InquiryContext: RPC_EP_INQ_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: ptr RPC_BINDING_HANDLE,
	    Annotation: PVOID

endif

;RPC_STATUS
RpcMgmtEpUnregister proto WINAPI \
	     EpBinding: RPC_BINDING_HANDLE,
		  IfId: ptr RPC_IF_ID,
	       Binding: RPC_BINDING_HANDLE,
	    ObjectUuid: ptr UUID

CALLBACK(RPC_MGMT_AUTHORIZATION_FN, ClientBinding:RPC_BINDING_HANDLE, RequestedMgmtOperation:DWORD, Status:ptr RPC_STATUS)

RPC_C_MGMT_INQ_IF_IDS		equ 0
RPC_C_MGMT_INQ_PRINC_NAME	equ 1
RPC_C_MGMT_INQ_STATS		equ 2
RPC_C_MGMT_IS_SERVER_LISTEN	equ 3
RPC_C_MGMT_STOP_SERVER_LISTEN	equ 4

;RPC_STATUS
RpcMgmtSetAuthorizationFn proto WINAPI \
       AuthorizationFn: RPC_MGMT_AUTHORIZATION_FN


RPC_C_PARM_MAX_PACKET_LENGTH equ 1
RPC_C_PARM_BUFFER_LENGTH equ 2

;RPC_STATUS
RpcMgmtInqParameter proto WINAPI \
	     Parameter: UINT,
		 Value: LPDWORD

;RPC_STATUS
RpcMgmtSetParameter proto WINAPI \
	     Parameter: UINT,
		 Value: DWORD

;RPC_STATUS
RpcMgmtBindingInqParameter proto WINAPI \
		Handle: RPC_BINDING_HANDLE,
	     Parameter: UINT,
		 Value: LPDWORD

;RPC_STATUS
RpcMgmtBindingSetParameter proto WINAPI \
		Handle: RPC_BINDING_HANDLE,
	     Parameter: UINT,
		 Value: DWORD

RPC_IF_AUTOLISTEN	equ 0x0001
RPC_IF_OLE		equ 0x0002

include rpcdcep.inc

endif

.list
