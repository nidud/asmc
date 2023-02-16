ifndef __RPCDCE_H__
define __RPCDCE_H__
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

include specstrings.inc

RPC_CSTR                typedef ptr __RPC_FAR

if defined(RPC_USE_NATIVE_WCHAR) and defined(_NATIVE_WCHAR_T_DEFINED)
RPC_WSTR                typedef ptr __RPC_FAR
RPC_CWSTR               typedef ptr wchar_t
else
RPC_WSTR                typedef ptr __RPC_FAR
RPC_CWSTR               typedef ptr word
endif

RPC_BINDING_HANDLE      typedef I_RPC_HANDLE
handle_t                typedef RPC_BINDING_HANDLE
define rpc_binding_handle_t RPC_BINDING_HANDLE

ifndef GUID_DEFINED
include guiddef.inc
endif

ifndef UUID_DEFINED
define UUID_DEFINED
UUID                    typedef GUID
ifndef uuid_t
define uuid_t UUID
endif
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RPC_BINDING_VECTOR      struct
Count                   sdword ?
BindingH                RPC_BINDING_HANDLE 1 dup(?)
RPC_BINDING_VECTOR      ends
ifndef rpc_binding_vector_t
define rpc_binding_vector_t RPC_BINDING_VECTOR
endif

UUID_VECTOR             struct
Count                   sdword ?
Uuid                    ptr UUID 1 dup(?)
UUID_VECTOR             ends
PUUID_VECTOR            typedef ptr UUID_VECTOR
ifndef uuid_vector_t
define uuid_vector_t UUID_VECTOR
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

RPC_IF_HANDLE           typedef ptr __RPC_FAR

ifndef IFID_DEFINED
define IFID_DEFINED
RPC_IF_ID               struct
Uuid                    UUID <>
VersMajor               word ?
VersMinor               word ?
RPC_IF_ID               ends
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

define RPC_C_BINDING_INFINITE_TIMEOUT 10
define RPC_C_BINDING_MIN_TIMEOUT 0
define RPC_C_BINDING_DEFAULT_TIMEOUT 5
define RPC_C_BINDING_MAX_TIMEOUT 9

define RPC_C_CANCEL_INFINITE_TIMEOUT -1

define RPC_C_LISTEN_MAX_CALLS_DEFAULT 1234
define RPC_C_PROTSEQ_MAX_REQS_DEFAULT 10

define RPC_C_BIND_TO_ALL_NICS          1
define RPC_C_USE_INTERNET_PORT         0x1
define RPC_C_USE_INTRANET_PORT         0x2
define RPC_C_DONT_FAIL                 0x4
define RPC_C_RPCHTTP_USE_LOAD_BALANCE  0x8

if (NTDDI_VERSION lt NTDDI_VISTA)
define RPC_C_MQ_TEMPORARY                  0x0000
define RPC_C_MQ_PERMANENT                  0x0001
define RPC_C_MQ_CLEAR_ON_OPEN              0x0002
define RPC_C_MQ_USE_EXISTING_SECURITY      0x0004
define RPC_C_MQ_AUTHN_LEVEL_NONE           0x0000
define RPC_C_MQ_AUTHN_LEVEL_PKT_INTEGRITY  0x0008
define RPC_C_MQ_AUTHN_LEVEL_PKT_PRIVACY    0x0010

define RPC_C_MQ_EXPRESS                0
define RPC_C_MQ_RECOVERABLE            1

define RPC_C_MQ_JOURNAL_NONE           0
define RPC_C_MQ_JOURNAL_DEADLETTER     1
define RPC_C_MQ_JOURNAL_ALWAYS         2

define RPC_C_OPT_MQ_DELIVERY            1
define RPC_C_OPT_MQ_PRIORITY            2
define RPC_C_OPT_MQ_JOURNAL             3
define RPC_C_OPT_MQ_ACKNOWLEDGE         4
define RPC_C_OPT_MQ_AUTHN_SERVICE       5
define RPC_C_OPT_MQ_AUTHN_LEVEL         6
define RPC_C_OPT_MQ_TIME_TO_REACH_QUEUE 7
define RPC_C_OPT_MQ_TIME_TO_BE_RECEIVED 8
endif

define RPC_C_OPT_BINDING_NONCAUSAL      9
define RPC_C_OPT_SECURITY_CALLBACK      10
define RPC_C_OPT_UNIQUE_BINDING         11

if (NTDDI_VERSION le NTDDI_WIN2K)
define RPC_C_OPT_MAX_OPTIONS            12

elseif (NTDDI_VERSION le NTDDI_WS03)
define RPC_C_OPT_CALL_TIMEOUT           12
define RPC_C_OPT_DONT_LINGER            13
define RPC_C_OPT_MAX_OPTIONS            14

else
define RPC_C_OPT_TRANS_SEND_BUFFER_SIZE 5
define RPC_C_OPT_CALL_TIMEOUT           12
define RPC_C_OPT_DONT_LINGER            13
define RPC_C_OPT_TRUST_PEER             14
define RPC_C_OPT_ASYNC_BLOCK            15
define RPC_C_OPT_OPTIMIZE_TIME          16
define RPC_C_OPT_MAX_OPTIONS            17

endif

define RPC_C_FULL_CERT_CHAIN 0x0001

ifdef RPC_UNICODE_SUPPORTED
RPC_PROTSEQ_VECTORA     struct
Count                   dword ?
Protseq                 PVOID 1 dup(?)
RPC_PROTSEQ_VECTORA     ends

RPC_PROTSEQ_VECTORW     struct
Count                   dword ?
Protseq                 PVOID 1 dup(?)
RPC_PROTSEQ_VECTORW     ends

ifdef _UNICODE
define RPC_PROTSEQ_VECTOR <RPC_PROTSEQ_VECTORW>
else
define RPC_PROTSEQ_VECTOR <RPC_PROTSEQ_VECTORA>
endif

else

RPC_PROTSEQ_VECTOR      struct
Count                   dword ?
Protseq                 PVOID 1 dup(?)
RPC_PROTSEQ_VECTOR      ends

endif

RPC_POLICY              struct
Length                  dword ?
EndpointFlags           sdword ?
NICFlags                sdword ?
RPC_POLICY              ends
PRPC_POLICY             typedef ptr RPC_POLICY

CALLBACK(RPC_OBJECT_INQ_FN, :ptr, :ptr, :ptr)
CALLBACK(RPC_IF_CALLBACK_FN, :RPC_IF_HANDLE, :ptr)
CALLBACK(RPC_SECURITY_CALLBACK_FN, :ptr)

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

define RPC_MGR_EPV void

RPC_STATS_VECTOR        struct
Count                   dword ?
Stats                   sdword 1 dup(?)
RPC_STATS_VECTOR        ends

define RPC_C_STATS_CALLS_IN 0
define RPC_C_STATS_CALLS_OUT 1
define RPC_C_STATS_PKTS_IN 2
define RPC_C_STATS_PKTS_OUT 3

RPC_IF_ID_VECTOR        struct
Count                   sdword ?
IfId                    PVOID 1 dup(?)
RPC_IF_ID_VECTOR        ends

RpcBindingCopy proto WINAPI :RPC_BINDING_HANDLE, :ptr
RpcBindingFree proto WINAPI :ptr
RpcBindingSetOption proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ULONG_PTR
RpcBindingInqOption proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr

ifndef _KRPCENV_

ifdef RPC_UNICODE_SUPPORTED

RpcBindingFromStringBindingA proto WINAPI :RPC_CSTR, :ptr
RpcBindingFromStringBindingW proto WINAPI :RPC_WSTR, :ptr
ifdef _UNICODE
define RpcBindingFromStringBinding <RpcBindingFromStringBindingW>
else
define RpcBindingFromStringBinding <RpcBindingFromStringBindingA>
endif

else

RpcBindingFromStringBinding proto WINAPI :RPC_CSTR, :ptr

endif
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcSsGetContextBinding proto WINAPI :ptr, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)
RpcBindingInqObject proto WINAPI :RPC_BINDING_HANDLE, :ptr
RpcBindingReset proto WINAPI :RPC_BINDING_HANDLE
RpcBindingSetObject proto WINAPI :RPC_BINDING_HANDLE, :ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcMgmtInqDefaultProtectLevel proto WINAPI :sdword, :ptr
endif

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcBindingToStringBindingA proto WINAPI :RPC_BINDING_HANDLE, :ptr
RpcBindingToStringBindingW proto WINAPI :RPC_BINDING_HANDLE, :ptr
ifdef _UNICODE
define RpcBindingToStringBinding <RpcBindingToStringBindingW>
else
define RpcBindingToStringBinding <RpcBindingToStringBindingA>
endif

endif

else
RpcBindingToStringBinding proto WINAPI :RPC_BINDING_HANDLE, :ptr
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcBindingVectorFree proto WINAPI :ptr
endif

ifndef _KRPCENV_

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcStringBindingComposeA proto WINAPI :RPC_CSTR, :RPC_CSTR, :RPC_CSTR, :RPC_CSTR, :RPC_CSTR, :ptr
RpcStringBindingComposeW proto WINAPI :RPC_WSTR, :RPC_WSTR, :RPC_WSTR, :RPC_WSTR, :RPC_WSTR, :ptr

ifdef _UNICODE
define RpcStringBindingCompose <RpcStringBindingComposeW>
else
define RpcStringBindingCompose <RpcStringBindingComposeA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcStringBindingCompose proto WINAPI :RPC_CSTR, :RPC_CSTR, :RPC_CSTR, :RPC_CSTR, :RPC_CSTR, :ptr
endif

endif

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcStringBindingParseA proto WINAPI :RPC_CSTR, :ptr, :ptr, :ptr, :ptr, :ptr
RpcStringBindingParseW proto WINAPI :RPC_WSTR, :ptr, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
define RpcStringBindingParse <RpcStringBindingParseW>
else
define RpcStringBindingParse <RpcStringBindingParseA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcStringBindingParse proto WINAPI :RPC_CSTR, :ptr, :ptr, :ptr, :ptr, :ptr
endif

endif

endif

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcStringFreeA proto WINAPI :ptr
RpcStringFreeW proto WINAPI :ptr
ifdef _UNICODE
define RpcStringFree <RpcStringFreeW>
else
define RpcStringFree <RpcStringFreeA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcStringFree proto WINAPI :ptr
endif

endif

RpcIfInqId proto WINAPI :RPC_IF_HANDLE, :ptr

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcNetworkIsProtseqValidA proto WINAPI :RPC_CSTR
RpcNetworkIsProtseqValidW proto WINAPI :RPC_WSTR
ifdef _UNICODE
define RpcNetworkIsProtseqValid <RpcNetworkIsProtseqValidW>
else
define RpcNetworkIsProtseqValid <RpcNetworkIsProtseqValidA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcNetworkIsProtseqValid proto WINAPI :RPC_CSTR
endif

endif

RpcMgmtInqComTimeout proto WINAPI :RPC_BINDING_HANDLE, :ptr

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcMgmtSetComTimeout proto WINAPI :RPC_BINDING_HANDLE, :dword
RpcMgmtSetCancelTimeout proto WINAPI :sdword

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifdef RPC_UNICODE_SUPPORTED

RpcNetworkInqProtseqsA proto WINAPI :ptr
RpcNetworkInqProtseqsW proto WINAPI :ptr
ifdef _UNICODE
define RpcNetworkInqProtseqs <RpcNetworkInqProtseqsW>
else
define RpcNetworkInqProtseqs <RpcNetworkInqProtseqsA>
endif

else

RpcNetworkInqProtseqs proto WINAPI :ptr

endif

RpcObjectInqType proto WINAPI :ptr, :ptr
RpcObjectSetInqFn proto WINAPI :ptr
RpcObjectSetType proto WINAPI :ptr, :ptr

ifdef RPC_UNICODE_SUPPORTED

RpcProtseqVectorFreeA proto WINAPI :ptr
RpcProtseqVectorFreeW proto WINAPI :ptr
ifdef _UNICODE
define RpcProtseqVectorFree <RpcProtseqVectorFreeW>
else
define RpcProtseqVectorFree <RpcProtseqVectorFreeA>
endif

else

RpcProtseqVectorFree proto WINAPI :ptr

endif

RpcServerInqBindings proto WINAPI :ptr
RpcServerInqBindingsEx proto WINAPI :ptr, :ptr
RpcServerInqIf proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr
RpcServerListen proto WINAPI :dword, :dword, :dword
RpcServerRegisterIf proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr
RpcServerRegisterIfEx proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :dword, :dword, :ptr
RpcServerRegisterIf2 proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :dword, :dword, :dword, :ptr

if (NTDDI_VERSION ge NTDDI_WIN8)
RpcServerRegisterIf3 proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :dword, :dword, :dword, :ptr, :ptr
endif

RpcServerUnregisterIf proto WINAPI :RPC_IF_HANDLE, :ptr, :dword

if (NTDDI_VERSION ge NTDDI_WINXP)
RpcServerUnregisterIfEx proto WINAPI :RPC_IF_HANDLE, :ptr, :sdword
endif

RpcServerUseAllProtseqs proto WINAPI :dword, :ptr
RpcServerUseAllProtseqsEx proto WINAPI :dword, :ptr, :PRPC_POLICY
RpcServerUseAllProtseqsIf proto WINAPI :dword, :RPC_IF_HANDLE, :ptr
RpcServerUseAllProtseqsIfEx proto WINAPI :dword, :RPC_IF_HANDLE, :ptr, :PRPC_POLICY

ifdef RPC_UNICODE_SUPPORTED

RpcServerUseProtseqA proto WINAPI :RPC_CSTR, :dword, :ptr
RpcServerUseProtseqExA proto WINAPI :RPC_CSTR, :dword, :ptr, :PRPC_POLICY
RpcServerUseProtseqW proto WINAPI :RPC_WSTR, :dword, :ptr
RpcServerUseProtseqExW proto WINAPI :RPC_WSTR, :dword, :ptr, :PRPC_POLICY
ifdef _UNICODE
define RpcServerUseProtseq <RpcServerUseProtseqW>
define RpcServerUseProtseqEx <RpcServerUseProtseqExW>
else
define RpcServerUseProtseq <RpcServerUseProtseqA>
define RpcServerUseProtseqEx <RpcServerUseProtseqExA>
endif

else

RpcServerUseProtseq proto WINAPI :RPC_CSTR, :dword, :ptr
RpcServerUseProtseqEx proto WINAPI :RPC_CSTR, :dword, :ptr, :PRPC_POLICY

endif

ifdef RPC_UNICODE_SUPPORTED

RpcServerUseProtseqEpA proto WINAPI :RPC_CSTR, :dword, :RPC_CSTR, :ptr
RpcServerUseProtseqEpExA proto WINAPI :RPC_CSTR, :dword, :RPC_CSTR, :ptr, :PRPC_POLICY
RpcServerUseProtseqEpW proto WINAPI :RPC_WSTR, :dword, :RPC_WSTR, :ptr
RpcServerUseProtseqEpExW proto WINAPI :RPC_WSTR, :dword, :RPC_WSTR, :ptr, :PRPC_POLICY
ifdef _UNICODE
define RpcServerUseProtseqEp <RpcServerUseProtseqEpW>
define RpcServerUseProtseqEpEx <RpcServerUseProtseqEpExW>
else
define RpcServerUseProtseqEp <RpcServerUseProtseqEpA>
define RpcServerUseProtseqEpEx <RpcServerUseProtseqEpExA>
endif

else

RpcServerUseProtseqEp proto WINAPI :RPC_CSTR, :dword, :RPC_CSTR, :ptr
RpcServerUseProtseqEpEx proto WINAPI :RPC_WSTR, :dword, :RPC_WSTR, :ptr, :PRPC_POLICY

endif

ifdef RPC_UNICODE_SUPPORTED

RpcServerUseProtseqIfA proto WINAPI :RPC_CSTR, :dword, :RPC_IF_HANDLE, :ptr
RpcServerUseProtseqIfExA proto WINAPI :RPC_CSTR, :dword, :RPC_IF_HANDLE, :ptr, :PRPC_POLICY
RpcServerUseProtseqIfW proto WINAPI :RPC_WSTR, :dword, :RPC_IF_HANDLE, :ptr
RpcServerUseProtseqIfExW proto WINAPI :RPC_WSTR, :dword, :RPC_IF_HANDLE, :ptr, :PRPC_POLICY
ifdef _UNICODE
define RpcServerUseProtseqIf <RpcServerUseProtseqIfW>
define RpcServerUseProtseqIfEx <RpcServerUseProtseqIfExW>
else
define RpcServerUseProtseqIf <RpcServerUseProtseqIfA>
define RpcServerUseProtseqIfEx <RpcServerUseProtseqIfExA>
endif

else

RpcServerUseProtseqIf proto WINAPI :RPC_CSTR, :dword, :RPC_IF_HANDLE, :ptr
RpcServerUseProtseqIfEx proto WINAPI :RPC_CSTR, :dword, :RPC_IF_HANDLE, :ptr, :PRPC_POLICY

endif

RpcServerYield proto WINAPI
RpcMgmtStatsVectorFree proto WINAPI :ptr ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcMgmtInqStats proto WINAPI :RPC_BINDING_HANDLE, :ptr ptr
RpcMgmtIsServerListening proto WINAPI :RPC_BINDING_HANDLE

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcMgmtStopServerListening proto WINAPI :RPC_BINDING_HANDLE
RpcMgmtWaitServerListen proto WINAPI
RpcMgmtSetServerStackSize proto WINAPI :sdword
RpcSsDontSerializeContext proto WINAPI
RpcMgmtEnableIdleCleanup proto WINAPI
RpcMgmtInqIfIds proto WINAPI :RPC_BINDING_HANDLE, :ptr
RpcIfIdVectorFree proto WINAPI :ptr

endif

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcMgmtInqServerPrincNameA proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr
RpcMgmtInqServerPrincNameW proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr
ifdef _UNICODE
define RpcMgmtInqServerPrincName <RpcMgmtInqServerPrincNameW>
else
define RpcMgmtInqServerPrincName <RpcMgmtInqServerPrincNameA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
RpcMgmtInqServerPrincName proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifdef RPC_UNICODE_SUPPORTED

RpcServerInqDefaultPrincNameA proto WINAPI :sdword, :ptr
RpcServerInqDefaultPrincNameW proto WINAPI :sdword, :ptr
ifdef _UNICODE
define RpcServerInqDefaultPrincName <RpcServerInqDefaultPrincNameW>
else
define RpcServerInqDefaultPrincName <RpcServerInqDefaultPrincNameA>
endif

else
RpcServerInqDefaultPrincName proto WINAPI :sdword, :ptr
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)
RpcEpResolveBinding proto WINAPI :RPC_BINDING_HANDLE, :RPC_IF_HANDLE
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifdef RPC_UNICODE_SUPPORTED

RpcNsBindingInqEntryNameA proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr
RpcNsBindingInqEntryNameW proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr
ifdef _UNICODE
define RpcNsBindingInqEntryName <RpcNsBindingInqEntryNameW>
else
define RpcNsBindingInqEntryName <RpcNsBindingInqEntryNameA>
endif

else
RpcNsBindingInqEntryName proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RPC_AUTH_IDENTITY_HANDLE typedef ptr __RPC_FAR
RPC_AUTHZ_HANDLE        typedef ptr __RPC_FAR

define RPC_C_AUTHN_LEVEL_DEFAULT       0
define RPC_C_AUTHN_LEVEL_NONE          1
define RPC_C_AUTHN_LEVEL_CONNECT       2
define RPC_C_AUTHN_LEVEL_CALL          3
define RPC_C_AUTHN_LEVEL_PKT           4
define RPC_C_AUTHN_LEVEL_PKT_INTEGRITY 5
define RPC_C_AUTHN_LEVEL_PKT_PRIVACY   6

define RPC_C_IMP_LEVEL_DEFAULT      0
define RPC_C_IMP_LEVEL_ANONYMOUS    1
define RPC_C_IMP_LEVEL_IDENTIFY     2
define RPC_C_IMP_LEVEL_IMPERSONATE  3
define RPC_C_IMP_LEVEL_DELEGATE     4

define RPC_C_QOS_IDENTITY_STATIC    0
define RPC_C_QOS_IDENTITY_DYNAMIC   1

define RPC_C_QOS_CAPABILITIES_DEFAULT                        0x0
define RPC_C_QOS_CAPABILITIES_MUTUAL_AUTH                    0x1
define RPC_C_QOS_CAPABILITIES_MAKE_FULLSIC                   0x2
define RPC_C_QOS_CAPABILITIES_ANY_AUTHORITY                  0x4

if (NTDDI_VERSION ge NTDDI_WS03)
define RPC_C_QOS_CAPABILITIES_IGNORE_DELEGATE_FAILURE        0x8
define RPC_C_QOS_CAPABILITIES_LOCAL_MA_HINT                 0x10
endif

if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_C_QOS_CAPABILITIES_SCHANNEL_FULL_AUTH_IDENTITY   0x20
endif

define RPC_C_PROTECT_LEVEL_DEFAULT       (RPC_C_AUTHN_LEVEL_DEFAULT)
define RPC_C_PROTECT_LEVEL_NONE          (RPC_C_AUTHN_LEVEL_NONE)
define RPC_C_PROTECT_LEVEL_CONNECT       (RPC_C_AUTHN_LEVEL_CONNECT)
define RPC_C_PROTECT_LEVEL_CALL          (RPC_C_AUTHN_LEVEL_CALL)
define RPC_C_PROTECT_LEVEL_PKT           (RPC_C_AUTHN_LEVEL_PKT)
define RPC_C_PROTECT_LEVEL_PKT_INTEGRITY (RPC_C_AUTHN_LEVEL_PKT_INTEGRITY)
define RPC_C_PROTECT_LEVEL_PKT_PRIVACY   (RPC_C_AUTHN_LEVEL_PKT_PRIVACY)

define RPC_C_AUTHN_NONE          0
define RPC_C_AUTHN_DCE_PRIVATE   1
define RPC_C_AUTHN_DCE_PUBLIC    2
define RPC_C_AUTHN_DEC_PUBLIC    4
define RPC_C_AUTHN_GSS_NEGOTIATE 9
define RPC_C_AUTHN_WINNT        10
define RPC_C_AUTHN_GSS_SCHANNEL 14
define RPC_C_AUTHN_GSS_KERBEROS 16
define RPC_C_AUTHN_DPA          17
define RPC_C_AUTHN_MSN          18
if (NTDDI_VERSION ge NTDDI_WINXP)
define RPC_C_AUTHN_DIGEST       21
endif
if (NTDDI_VERSION ge NTDDI_WIN7)
define RPC_C_AUTHN_KERNEL         20
endif

define RPC_C_AUTHN_NEGO_EXTENDER 30
define RPC_C_AUTHN_PKU2U         31

define RPC_C_AUTHN_LIVE_SSP      32
define RPC_C_AUTHN_LIVEXP_SSP    35
define RPC_C_AUTHN_CLOUD_AP      36
define RPC_C_AUTHN_MSONLINE      82

define RPC_C_AUTHN_MQ          100
define RPC_C_AUTHN_DEFAULT     0xFFFFFFFF

define RPC_C_NO_CREDENTIALS ((RPC_AUTH_IDENTITY_HANDLE) MAXUINT_PTR)

define RPC_C_SECURITY_QOS_VERSION      1
define RPC_C_SECURITY_QOS_VERSION_1    1

RPC_SECURITY_QOS        struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
RPC_SECURITY_QOS        ends
PRPC_SECURITY_QOS       typedef ptr RPC_SECURITY_QOS

ifndef _AUTH_IDENTITY_DEFINED
define _AUTH_IDENTITY_DEFINED

define SEC_WINNT_AUTH_IDENTITY_ANSI    0x1
define SEC_WINNT_AUTH_IDENTITY_UNICODE 0x2

SEC_WINNT_AUTH_IDENTITY_W struct
User                    PVOID ?
UserLength              sdword ?
Domain                  PVOID ?
DomainLength            sdword ?
Password                PVOID ?
PasswordLength          sdword ?
Flags                   sdword ?
SEC_WINNT_AUTH_IDENTITY_W ends
PSEC_WINNT_AUTH_IDENTITY_W typedef ptr SEC_WINNT_AUTH_IDENTITY_W

if (NTDDI_VERSION ge NTDDI_VISTA)
define _AUTH_IDENTITY_A_DEFINED
endif

SEC_WINNT_AUTH_IDENTITY_A struct
User                    PVOID ?
UserLength              sdword ?
Domain                  PVOID ?
DomainLength            sdword ?
Password                PVOID ?
PasswordLength          sdword ?
Flags                   sdword ?
SEC_WINNT_AUTH_IDENTITY_A ends
PSEC_WINNT_AUTH_IDENTITY_A typedef ptr SEC_WINNT_AUTH_IDENTITY_A

ifdef _UNICODE
define SEC_WINNT_AUTH_IDENTITY <SEC_WINNT_AUTH_IDENTITY_W>
define PSEC_WINNT_AUTH_IDENTITY <PSEC_WINNT_AUTH_IDENTITY_W>
else
define SEC_WINNT_AUTH_IDENTITY <SEC_WINNT_AUTH_IDENTITY_A>
define PSEC_WINNT_AUTH_IDENTITY <PSEC_WINNT_AUTH_IDENTITY_A>
endif

if (NTDDI_VERSION ge NTDDI_WINXP)

define RPC_C_SECURITY_QOS_VERSION_2     2
define RPC_C_AUTHN_INFO_TYPE_HTTP       1
define RPC_C_HTTP_AUTHN_TARGET_SERVER   1
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_C_HTTP_AUTHN_TARGET_PROXY    2
endif

define RPC_C_HTTP_AUTHN_SCHEME_BASIC      0x00000001
define RPC_C_HTTP_AUTHN_SCHEME_NTLM       0x00000002
define RPC_C_HTTP_AUTHN_SCHEME_PASSPORT   0x00000004
define RPC_C_HTTP_AUTHN_SCHEME_DIGEST     0x00000008
define RPC_C_HTTP_AUTHN_SCHEME_NEGOTIATE  0x00000010
if (NTDDI_VERSION ge NTDDI_WS03)
define RPC_C_HTTP_AUTHN_SCHEME_CERT       0x00010000
endif

define RPC_C_HTTP_FLAG_USE_SSL                     1
define RPC_C_HTTP_FLAG_USE_FIRST_AUTH_SCHEME       2
if (NTDDI_VERSION ge NTDDI_WS03)
define RPC_C_HTTP_FLAG_IGNORE_CERT_CN_INVALID      8
endif
if (NTDDI_VERSION ge NTDDI_VISTASP1)
define RPC_C_HTTP_FLAG_ENABLE_CERT_REVOCATION_CHECK 16
endif

RPC_HTTP_TRANSPORT_CREDENTIALS_W struct
TransportCredentials    ptr SEC_WINNT_AUTH_IDENTITY_W ?
Flags                   sdword ?
AuthenticationTarget    sdword ?
NumberOfAuthnSchemes    sdword ?
AuthnSchemes            PVOID ?
ServerCertificateSubject PVOID ?
RPC_HTTP_TRANSPORT_CREDENTIALS_W ends
PRPC_HTTP_TRANSPORT_CREDENTIALS_W typedef ptr RPC_HTTP_TRANSPORT_CREDENTIALS_W

RPC_HTTP_TRANSPORT_CREDENTIALS_A struct
TransportCredentials    ptr SEC_WINNT_AUTH_IDENTITY_A ?
Flags                   sdword ?
AuthenticationTarget    sdword ?
NumberOfAuthnSchemes    sdword ?
AuthnSchemes            PVOID ?
ServerCertificateSubject PVOID ?
RPC_HTTP_TRANSPORT_CREDENTIALS_A ends
PRPC_HTTP_TRANSPORT_CREDENTIALS_A typedef ptr RPC_HTTP_TRANSPORT_CREDENTIALS_A

if (NTDDI_VERSION ge NTDDI_VISTA)

RPC_HTTP_TRANSPORT_CREDENTIALS_V2_W struct
TransportCredentials    PSEC_WINNT_AUTH_IDENTITY_W ?
Flags                   sdword ?
AuthenticationTarget    sdword ?
NumberOfAuthnSchemes    sdword ?
AuthnSchemes            PVOID ?
ServerCertificateSubject PVOID ?
ProxyCredentials        PSEC_WINNT_AUTH_IDENTITY_W ?
NumberOfProxyAuthnSchemes sdword ?
ProxyAuthnSchemes       PVOID ?
RPC_HTTP_TRANSPORT_CREDENTIALS_V2_W ends
PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_W typedef ptr RPC_HTTP_TRANSPORT_CREDENTIALS_V2_W

RPC_HTTP_TRANSPORT_CREDENTIALS_V2_A struct
TransportCredentials    PSEC_WINNT_AUTH_IDENTITY_A ?
Flags                   sdword ?
AuthenticationTarget    sdword ?
NumberOfAuthnSchemes    sdword ?
AuthnSchemes            PVOID ?
ServerCertificateSubject PVOID ?
ProxyCredentials        PSEC_WINNT_AUTH_IDENTITY_A ?
NumberOfProxyAuthnSchemes sdword ?
ProxyAuthnSchemes       PVOID ?
RPC_HTTP_TRANSPORT_CREDENTIALS_V2_A ends
PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_A typedef ptr RPC_HTTP_TRANSPORT_CREDENTIALS_V2_A

endif

if (NTDDI_VERSION ge NTDDI_WIN7)

RPC_HTTP_TRANSPORT_CREDENTIALS_V3_W struct
TransportCredentials    RPC_AUTH_IDENTITY_HANDLE ?
Flags                   sdword ?
AuthenticationTarget    sdword ?
NumberOfAuthnSchemes    sdword ?
AuthnSchemes            PVOID ?
ServerCertificateSubject PVOID ?
ProxyCredentials        RPC_AUTH_IDENTITY_HANDLE ?
NumberOfProxyAuthnSchemes sdword ?
ProxyAuthnSchemes       PVOID ?
RPC_HTTP_TRANSPORT_CREDENTIALS_V3_W ends
PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_W typedef ptr RPC_HTTP_TRANSPORT_CREDENTIALS_V3_W

RPC_HTTP_TRANSPORT_CREDENTIALS_V3_A struct
TransportCredentials    RPC_AUTH_IDENTITY_HANDLE ?
Flags                   sdword ?
AuthenticationTarget    sdword ?
NumberOfAuthnSchemes    sdword ?
AuthnSchemes            PVOID ?
ServerCertificateSubject PVOID ?
ProxyCredentials        RPC_AUTH_IDENTITY_HANDLE ?
NumberOfProxyAuthnSchemes sdword ?
ProxyAuthnSchemes       PVOID ?
RPC_HTTP_TRANSPORT_CREDENTIALS_V3_A ends
PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_A typedef ptr RPC_HTTP_TRANSPORT_CREDENTIALS_V3_A

endif

RPC_SECURITY_QOS_V2_W   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_W ?
ends
RPC_SECURITY_QOS_V2_W   ends
PRPC_SECURITY_QOS_V2_W  typedef ptr RPC_SECURITY_QOS_V2_W

RPC_SECURITY_QOS_V2_A   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_A ?
ends
RPC_SECURITY_QOS_V2_A   ends
PRPC_SECURITY_QOS_V2_A  typedef ptr RPC_SECURITY_QOS_V2_A

if (NTDDI_VERSION ge NTDDI_WS03)
define RPC_C_SECURITY_QOS_VERSION_3 3

RPC_SECURITY_QOS_V3_W   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_W ?
ends
Sid                     ptr ?
RPC_SECURITY_QOS_V3_W   ends
PRPC_SECURITY_QOS_V3_W  typedef ptr RPC_SECURITY_QOS_V3_W

RPC_SECURITY_QOS_V3_A   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_A ?
ends
Sid                     ptr ?
RPC_SECURITY_QOS_V3_A   ends
PRPC_SECURITY_QOS_V3_A  typedef ptr RPC_SECURITY_QOS_V3_A
endif

if (NTDDI_VERSION ge NTDDI_VISTA)

define RPC_C_SECURITY_QOS_VERSION_4 4

RPC_SECURITY_QOS_V4_W   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_W ?
ends
Sid                     ptr ?
EffectiveOnly           dword ?
RPC_SECURITY_QOS_V4_W   ends
PRPC_SECURITY_QOS_V4_W  typedef ptr _RPC_SECURITY_QOS_V4_W

RPC_SECURITY_QOS_V4_A   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_A ?
ends
Sid                     ptr ?
EffectiveOnly           dword ?
RPC_SECURITY_QOS_V4_A   ends
PRPC_SECURITY_QOS_V4_A  typedef ptr RPC_SECURITY_QOS_V4_A

endif

if (NTDDI_VERSION ge NTDDI_WIN8)
define RPC_C_SECURITY_QOS_VERSION_5 5

RPC_SECURITY_QOS_V5_W   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_W ?
ends
Sid                     ptr ?
EffectiveOnly           dword ?
ServerSecurityDescriptor ptr ?
RPC_SECURITY_QOS_V5_W   ends
PRPC_SECURITY_QOS_V5_W  typedef ptr RPC_SECURITY_QOS_V5_W

RPC_SECURITY_QOS_V5_A   struct
Version                 sdword ?
Capabilities            sdword ?
IdentityTracking        sdword ?
ImpersonationType       sdword ?
AdditionalSecurityInfoType sdword ?
union u
 HttpCredentials        PRPC_HTTP_TRANSPORT_CREDENTIALS_A ?
ends
Sid                     ptr ?
EffectiveOnly           dword ?
ServerSecurityDescriptor ptr ?
RPC_SECURITY_QOS_V5_A   ends
PRPC_SECURITY_QOS_V5_A  typedef ptr RPC_SECURITY_QOS_V5_A

endif

endif
endif

endif

if (NTDDI_VERSION ge NTDDI_WINXP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifdef _UNICODE
define RPC_SECURITY_QOS_V2 <RPC_SECURITY_QOS_V2_W>
define PRPC_SECURITY_QOS_V2 <PRPC_SECURITY_QOS_V2_W>
define RPC_HTTP_TRANSPORT_CREDENTIALS <RPC_HTTP_TRANSPORT_CREDENTIALS_W>
define PRPC_HTTP_TRANSPORT_CREDENTIALS <PRPC_HTTP_TRANSPORT_CREDENTIALS_W>
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_HTTP_TRANSPORT_CREDENTIALS_V2 <RPC_HTTP_TRANSPORT_CREDENTIALS_V2_W>
define PRPC_HTTP_TRANSPORT_CREDENTIALS_V2 <PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_W>
endif
if (NTDDI_VERSION ge NTDDI_WIN7)
define RPC_HTTP_TRANSPORT_CREDENTIALS_V3 RPC_HTTP_TRANSPORT_CREDENTIALS_V3_W
define PRPC_HTTP_TRANSPORT_CREDENTIALS_V3 PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_W
endif
if (NTDDI_VERSION ge NTDDI_WS03)
define RPC_SECURITY_QOS_V3 RPC_SECURITY_QOS_V3_W
define PRPC_SECURITY_QOS_V3 PRPC_SECURITY_QOS_V3_W
endif
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_SECURITY_QOS_V4 RPC_SECURITY_QOS_V4_W
define PRPC_SECURITY_QOS_V4 PRPC_SECURITY_QOS_V4_W
endif
if (NTDDI_VERSION ge NTDDI_WIN8)
define RPC_SECURITY_QOS_V5 RPC_SECURITY_QOS_V5_W
define PRPC_SECURITY_QOS_V5 PRPC_SECURITY_QOS_V5_W
endif

else

define RPC_SECURITY_QOS_V2 RPC_SECURITY_QOS_V2_A
define PRPC_SECURITY_QOS_V2 PRPC_SECURITY_QOS_V2_A
define RPC_HTTP_TRANSPORT_CREDENTIALS RPC_HTTP_TRANSPORT_CREDENTIALS_A
define PRPC_HTTP_TRANSPORT_CREDENTIALS PRPC_HTTP_TRANSPORT_CREDENTIALS_A
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_HTTP_TRANSPORT_CREDENTIALS_V2 RPC_HTTP_TRANSPORT_CREDENTIALS_V2_A
define PRPC_HTTP_TRANSPORT_CREDENTIALS_V2 PRPC_HTTP_TRANSPORT_CREDENTIALS_V2_A
endif
if (NTDDI_VERSION ge NTDDI_WIN7)
define RPC_HTTP_TRANSPORT_CREDENTIALS_V3 RPC_HTTP_TRANSPORT_CREDENTIALS_V3_A
define PRPC_HTTP_TRANSPORT_CREDENTIALS_V3 PRPC_HTTP_TRANSPORT_CREDENTIALS_V3_A
endif
if (NTDDI_VERSION ge NTDDI_WS03)
define RPC_SECURITY_QOS_V3 RPC_SECURITY_QOS_V3_A
define PRPC_SECURITY_QOS_V3 PRPC_SECURITY_QOS_V3_A
endif
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_SECURITY_QOS_V4 RPC_SECURITY_QOS_V4_A
define PRPC_SECURITY_QOS_V4 PRPC_SECURITY_QOS_V4_A
endif
if (NTDDI_VERSION ge NTDDI_WIN8)
define RPC_SECURITY_QOS_V5 RPC_SECURITY_QOS_V5_A
define PRPC_SECURITY_QOS_V5 PRPC_SECURITY_QOS_V5_A
endif

endif

endif

if (NTDDI_VERSION ge NTDDI_VISTA)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

define RPC_PROTSEQ_TCP                             (0x1)
define RPC_PROTSEQ_NMP                             (0x2)
define RPC_PROTSEQ_LRPC                            (0x3)
define RPC_PROTSEQ_HTTP                            (0x4)
define RPC_BHT_OBJECT_UUID_VALID                   (0x1)
define RPC_BHO_NONCAUSAL                           (0x1)
define RPC_BHO_DONTLINGER                          (0x2)
define RPC_BHO_EXCLUSIVE_AND_GUARANTEED            (0x4)

RPC_BINDING_HANDLE_TEMPLATE_V1_W struct
Version                 sdword ?
Flags                   sdword ?
ProtocolSequence        sdword ?
NetworkAddress          LPWSTR ?
StringEndpoint          LPWSTR ?
union u1
 Reserved               LPWSTR ?
ends
ObjectUuid              UUID <>
RPC_BINDING_HANDLE_TEMPLATE_V1_W ends
PRPC_BINDING_HANDLE_TEMPLATE_V1_W typedef ptr RPC_BINDING_HANDLE_TEMPLATE_V1_W

RPC_BINDING_HANDLE_TEMPLATE_V1_A struct
Version                 sdword ?
Flags                   sdword ?
ProtocolSequence        sdword ?
NetworkAddress          LPBYTE ?
StringEndpoint          LPBYTE ?
union u1
 Reserved               LPBYTE ?
ends
ObjectUuid              UUID <>
RPC_BINDING_HANDLE_TEMPLATE_V1_A ends
PRPC_BINDING_HANDLE_TEMPLATE_V1_A typedef ptr RPC_BINDING_HANDLE_TEMPLATE_V1_A

RPC_BINDING_HANDLE_SECURITY_V1_W struct
Version                 sdword ?
ServerPrincName         LPWSTR ?
AuthnLevel              sdword ?
AuthnSvc                sdword ?
AuthIdentity            PSEC_WINNT_AUTH_IDENTITY_W ?
SecurityQos             PRPC_SECURITY_QOS ?
RPC_BINDING_HANDLE_SECURITY_V1_W ends
PRPC_BINDING_HANDLE_SECURITY_V1_W typedef ptr RPC_BINDING_HANDLE_SECURITY_V1_W

ifdef _AUTH_IDENTITY_A_DEFINED

RPC_BINDING_HANDLE_SECURITY_V1_A struct
Version                 sdword ?
ServerPrincName         LPBYTE ?
AuthnLevel              sdword ?
AuthnSvc                sdword ?
AuthIdentity            PSEC_WINNT_AUTH_IDENTITY_A ?
SecurityQos             PRPC_SECURITY_QOS ?
RPC_BINDING_HANDLE_SECURITY_V1_A ends
PRPC_BINDING_HANDLE_SECURITY_V1_A typedef ptr RPC_BINDING_HANDLE_SECURITY_V1_A

endif

RPC_BINDING_HANDLE_OPTIONS_V1 struct
Version                 sdword ?
Flags                   sdword ?
ComTimeout              sdword ?
CallTimeout             sdword ?
RPC_BINDING_HANDLE_OPTIONS_V1 ends
PRPC_BINDING_HANDLE_OPTIONS_V1 typedef ptr RPC_BINDING_HANDLE_OPTIONS_V1

ifdef _UNICODE
define RPC_BINDING_HANDLE_TEMPLATE_V1 <RPC_BINDING_HANDLE_TEMPLATE_V1_W>
define PRPC_BINDING_HANDLE_TEMPLATE_V1 <PRPC_BINDING_HANDLE_TEMPLATE_V1_W>
define RPC_BINDING_HANDLE_SECURITY_V1 <RPC_BINDING_HANDLE_SECURITY_V1_W>
define PRPC_BINDING_HANDLE_SECURITY_V1 <PRPC_BINDING_HANDLE_SECURITY_V1_W>
else
define RPC_BINDING_HANDLE_TEMPLATE_V1 <RPC_BINDING_HANDLE_TEMPLATE_V1_A>
define PRPC_BINDING_HANDLE_TEMPLATE_V1 <PRPC_BINDING_HANDLE_TEMPLATE_V1_A>
define RPC_BINDING_HANDLE_SECURITY_V1 <RPC_BINDING_HANDLE_SECURITY_V1_A>
define PRPC_BINDING_HANDLE_SECURITY_V1 <PRPC_BINDING_HANDLE_SECURITY_V1_A>
endif

ifdef _AUTH_IDENTITY_A_DEFINED

RpcBindingCreateA proto WINAPI :ptr, :ptr, :ptr, :ptr

endif

RpcBindingCreateW proto WINAPI :ptr, :ptr, :ptr, :ptr

ifdef _UNICODE
define RpcBindingCreate <RpcBindingCreateW>
else
define RpcBindingCreate <RpcBindingCreateA>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcBindingGetTrainingContextHandle proto WINAPI :RPC_BINDING_HANDLE, :ptr ptr
RpcServerInqBindingHandle proto WINAPI :ptr

endif

endif

if (NTDDI_VERSION ge NTDDI_WS03)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

.enum RPC_HTTP_REDIRECTOR_STAGE {
    RPCHTTP_RS_REDIRECT = 1,
    RPCHTTP_RS_ACCESS_1,
    RPCHTTP_RS_SESSION,
    RPCHTTP_RS_ACCESS_2,
    RPCHTTP_RS_INTERFACE
    }

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

if (NTDDI_VERSION ge NTDDI_WS03)
CALLBACK(RPC_NEW_HTTP_PROXY_CHANNEL, :RPC_HTTP_REDIRECTOR_STAGE, :RPC_WSTR, :RPC_WSTR, :RPC_WSTR, :RPC_WSTR, :ptr, :ptr, :ptr, :ptr, :sdword, :ptr, :ptr)

else

CALLBACK(RPC_NEW_HTTP_PROXY_CHANNEL, :ptr, :ptr, :ptr, :ptr ptr)
endif

CALLBACK(RPC_HTTP_PROXY_FREE_STRING, :RPC_WSTR)

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

define RPC_C_AUTHZ_NONE    0
define RPC_C_AUTHZ_NAME    1
define RPC_C_AUTHZ_DCE     2
define RPC_C_AUTHZ_DEFAULT 0xffffffff

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcImpersonateClient proto WINAPI :RPC_BINDING_HANDLE
RpcImpersonateClient2 proto WINAPI :RPC_BINDING_HANDLE
RpcRevertToSelfEx proto WINAPI :RPC_BINDING_HANDLE
RpcRevertToSelf proto WINAPI
RpcImpersonateClientContainer proto WINAPI :RPC_BINDING_HANDLE
RpcRevertContainerImpersonation proto WINAPI

endif

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcBindingInqAuthClientA proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr
RpcBindingInqAuthClientW proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr
RpcBindingInqAuthClientExA proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr, :sdword
RpcBindingInqAuthClientExW proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr, :sdword

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcBindingInqAuthInfoA proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr
RpcBindingInqAuthInfoW proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr
RpcBindingSetAuthInfoA proto WINAPI :RPC_BINDING_HANDLE, :RPC_CSTR, :sdword, :sdword, :RPC_AUTH_IDENTITY_HANDLE, :sdword
RpcBindingSetAuthInfoExA proto WINAPI :RPC_BINDING_HANDLE, :RPC_CSTR, :sdword, :sdword, :RPC_AUTH_IDENTITY_HANDLE, :sdword, :ptr
RpcBindingSetAuthInfoW proto WINAPI :RPC_BINDING_HANDLE, :RPC_WSTR, :sdword, :sdword, :RPC_AUTH_IDENTITY_HANDLE, :sdword
RpcBindingSetAuthInfoExW proto WINAPI :RPC_BINDING_HANDLE, :RPC_WSTR, :sdword, :sdword, :RPC_AUTH_IDENTITY_HANDLE, :sdword, :ptr
RpcBindingInqAuthInfoExA proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr, :sdword, :ptr
RpcBindingInqAuthInfoExW proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr, :sdword, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

CALLBACK(RPC_AUTH_KEY_RETRIEVAL_FN, :ptr, :RPC_WSTR, :sdword, :ptr, :ptr)

RpcServerCompleteSecurityCallback proto WINAPI :RPC_BINDING_HANDLE, :RPC_STATUS
RpcServerRegisterAuthInfoA proto WINAPI :RPC_CSTR, :sdword, :RPC_AUTH_KEY_RETRIEVAL_FN, :ptr
RpcServerRegisterAuthInfoW proto WINAPI :RPC_WSTR, :sdword, :RPC_AUTH_KEY_RETRIEVAL_FN, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifdef _UNICODE
define RpcBindingInqAuthClient <RpcBindingInqAuthClientW>
define RpcBindingInqAuthClientEx <RpcBindingInqAuthClientExW>
define RpcBindingInqAuthInfo <RpcBindingInqAuthInfoW>
define RpcBindingSetAuthInfo <RpcBindingSetAuthInfoW>
define RpcServerRegisterAuthInfo <RpcServerRegisterAuthInfoW>
define RpcBindingInqAuthInfoEx <RpcBindingInqAuthInfoExW>
define RpcBindingSetAuthInfoEx <RpcBindingSetAuthInfoExW>
else
define RpcBindingInqAuthClient <RpcBindingInqAuthClientA>
define RpcBindingInqAuthClientEx <RpcBindingInqAuthClientExA>
define RpcBindingInqAuthInfo <RpcBindingInqAuthInfoA>
define RpcBindingSetAuthInfo <RpcBindingSetAuthInfoA>
define RpcServerRegisterAuthInfo <RpcServerRegisterAuthInfoA>
define RpcBindingInqAuthInfoEx <RpcBindingInqAuthInfoExA>
define RpcBindingSetAuthInfoEx <RpcBindingSetAuthInfoExA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcBindingInqAuthClient proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr
RpcBindingInqAuthClientEx proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr, :sdword
RpcBindingInqAuthInfo proto WINAPI :RPC_BINDING_HANDLE, :ptr, :ptr, :ptr, :ptr, :ptr
RpcBindingSetAuthInfo proto WINAPI :RPC_BINDING_HANDLE, :RPC_CSTR, :sdword, :sdword, :RPC_AUTH_IDENTITY_HANDLE, :sdword

CALLBACK(RPC_AUTH_KEY_RETRIEVAL_FN, :ptr, :ptr, :sdword, :ptr, :ptr)

RpcServerRegisterAuthInfo proto WINAPI :RPC_CSTR, :sdword, :RPC_AUTH_KEY_RETRIEVAL_FN, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

if (NTDDI_VERSION ge NTDDI_WINXP)
if not defined(_M_IA64)
RPC_CLIENT_INFORMATION1 struct
UserName                PVOID ?
ComputerName            PVOID ?
Privilege               word ?
AuthFlags               sdword ?
RPC_CLIENT_INFORMATION1 ends
PRPC_CLIENT_INFORMATION1 typedef ptr RPC_CLIENT_INFORMATION1
endif
endif

RpcBindingServerFromClient proto WINAPI :RPC_BINDING_HANDLE, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

RpcRaiseException proto WINAPI :RPC_STATUS
RpcTestCancel proto WINAPI

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RpcServerTestCancel proto WINAPI :RPC_BINDING_HANDLE
RpcCancelThread proto WINAPI :ptr
RpcCancelThreadEx proto WINAPI :ptr, :sdword

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

UuidCreate proto WINAPI :ptr
UuidCreateSequential proto WINAPI :ptr

ifdef RPC_UNICODE_SUPPORTED

UuidToStringA proto WINAPI :ptr, :ptr
UuidFromStringA proto WINAPI :RPC_CSTR, :ptr
UuidToStringW proto WINAPI :ptr, :ptr
UuidFromStringW proto WINAPI :RPC_WSTR, :ptr

ifdef _UNICODE
define UuidFromString <UuidFromStringW>
define UuidToString <UuidToStringW>
else
define UuidFromString <UuidFromStringA>
define UuidToString <UuidToStringA>
endif

else

UuidToString proto WINAPI :ptr, :ptr
UuidFromString proto WINAPI :RPC_CSTR, :ptr

endif

UuidCompare proto WINAPI :ptr, :ptr, :ptr
UuidCreateNil proto WINAPI :ptr
UuidEqual proto WINAPI :ptr, :ptr, :ptr
UuidHash proto WINAPI :ptr, :ptr
UuidIsNil proto WINAPI :ptr, :ptr

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifdef RPC_UNICODE_SUPPORTED

RpcEpRegisterNoReplaceA proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :RPC_CSTR
RpcEpRegisterNoReplaceW proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :RPC_WSTR
RpcEpRegisterA proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :RPC_CSTR
RpcEpRegisterW proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :RPC_WSTR
ifdef _UNICODE
define RpcEpRegisterNoReplace <RpcEpRegisterNoReplaceW>
define RpcEpRegister <RpcEpRegisterW>
else
define RpcEpRegisterNoReplace <RpcEpRegisterNoReplaceA>
define RpcEpRegister <RpcEpRegisterA>
endif

else

RpcEpRegisterNoReplace proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :RPC_CSTR
RpcEpRegister proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr, :RPC_CSTR

endif

RpcEpUnregister proto WINAPI :RPC_IF_HANDLE, :ptr, :ptr

endif

define DCE_C_ERROR_STRING_LEN 256

ifdef RPC_UNICODE_SUPPORTED

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

DceErrorInqTextA proto WINAPI :RPC_STATUS, :RPC_CSTR
DceErrorInqTextW proto WINAPI :RPC_STATUS, :RPC_WSTR

ifdef _UNICODE
define DceErrorInqText <DceErrorInqTextW>
else
define DceErrorInqText <DceErrorInqTextA>
endif

endif

else

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
DceErrorInqText proto WINAPI :RPC_STATUS, :RPC_CSTR
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

RPC_EP_INQ_HANDLE       typedef ptr I_RPC_HANDLE

define  RPC_C_EP_ALL_ELTS        0
define  RPC_C_EP_MATCH_BY_IF     1
define  RPC_C_EP_MATCH_BY_OBJ    2
define  RPC_C_EP_MATCH_BY_BOTH   3

define  RPC_C_VERS_ALL           1
define  RPC_C_VERS_COMPATIBLE    2
define  RPC_C_VERS_EXACT         3
define  RPC_C_VERS_MAJOR_ONLY    4
define  RPC_C_VERS_UPTO          5

RpcMgmtEpEltInqBegin proto WINAPI :RPC_BINDING_HANDLE, :sdword, :ptr, :sdword, :ptr, :ptr
RpcMgmtEpEltInqDone proto WINAPI :ptr

ifdef RPC_UNICODE_SUPPORTED

RpcMgmtEpEltInqNextA proto WINAPI :RPC_EP_INQ_HANDLE, :ptr, :ptr, :ptr, :ptr
RpcMgmtEpEltInqNextW proto WINAPI :RPC_EP_INQ_HANDLE, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
define RpcMgmtEpEltInqNext <RpcMgmtEpEltInqNextW>
else
define RpcMgmtEpEltInqNext <RpcMgmtEpEltInqNextA>
endif

else

RpcMgmtEpEltInqNext proto WINAPI :RPC_EP_INQ_HANDLE, :ptr, :ptr, :ptr

endif

RpcMgmtEpUnregister proto WINAPI :RPC_BINDING_HANDLE, :ptr, :RPC_BINDING_HANDLE, :ptr

CALLBACK(RPC_MGMT_AUTHORIZATION_FN, :RPC_BINDING_HANDLE, :sdword, :ptr)

define RPC_C_MGMT_INQ_IF_IDS         0
define RPC_C_MGMT_INQ_PRINC_NAME     1
define RPC_C_MGMT_INQ_STATS          2
define RPC_C_MGMT_IS_SERVER_LISTEN   3
define RPC_C_MGMT_STOP_SERVER_LISTEN 4

RpcMgmtSetAuthorizationFn proto WINAPI :RPC_MGMT_AUTHORIZATION_FN

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

if (NTDDI_VERSION ge NTDDI_VISTA)
RpcExceptionFilter proto WINAPI :sdword
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

define RPC_C_PARM_MAX_PACKET_LENGTH    1
define RPC_C_PARM_BUFFER_LENGTH        2

define RPC_IF_AUTOLISTEN                   0x0001
define RPC_IF_OLE                          0x0002
define RPC_IF_ALLOW_UNKNOWN_AUTHORITY      0x0004
define RPC_IF_ALLOW_SECURE_ONLY            0x0008
define RPC_IF_ALLOW_CALLBACKS_WITH_NO_AUTH 0x0010
define RPC_IF_ALLOW_LOCAL_ONLY             0x0020
define RPC_IF_SEC_NO_CACHE                 0x0040
if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_IF_SEC_CACHE_PER_PROC           0x0080
define RPC_IF_ASYNC_CALLBACK               0x0100
endif

if (NTDDI_VERSION ge NTDDI_VISTA)
define RPC_FW_IF_FLAG_DCOM                 0x0001
endif

if (NTDDI_VERSION ge NTDDI_WIN8)
RPC_INTERFACE_GROUP    typedef ptr
PRPC_INTERFACE_GROUP    typedef ptr

ifdef RPC_UNICODE_SUPPORTED
RPC_ENDPOINT_TEMPLATEW  struct
Version                 sdword ?
ProtSeq                 RPC_WSTR ?
Endpoint                RPC_WSTR ?
SecurityDescriptor      PVOID ?
Backlog                 sdword ?
RPC_ENDPOINT_TEMPLATEW  ends
PRPC_ENDPOINT_TEMPLATEW typedef ptr RPC_ENDPOINT_TEMPLATEW

RPC_ENDPOINT_TEMPLATEA  struct
Version                 sdword ?
ProtSeq                 RPC_CSTR ?
Endpoint                RPC_CSTR ?
SecurityDescriptor      PVOID ?
Backlog                 sdword ?
RPC_ENDPOINT_TEMPLATEA  ends
PRPC_ENDPOINT_TEMPLATEA typedef ptr RPC_ENDPOINT_TEMPLATEA

ifdef _UNICODE
define RPC_ENDPOINT_TEMPLATE <RPC_ENDPOINT_TEMPLATEW>
define PRPC_ENDPOINT_TEMPLATE <PRPC_ENDPOINT_TEMPLATEW>
else
define RPC_ENDPOINT_TEMPLATE <RPC_ENDPOINT_TEMPLATEA>
define PRPC_ENDPOINT_TEMPLATE <PRPC_ENDPOINT_TEMPLATEA>
endif

else
RPC_ENDPOINT_TEMPLATE   struct
Version                 sdword ?
ProtSeq                 RPC_CSTR ?
Endpoint                RPC_CSTR ?
SecurityDescriptor      PVOID ?
Backlog                 sdword ?
RPC_ENDPOINT_TEMPLATE   ends
PRPC_ENDPOINT_TEMPLATE  typedef ptr RPC_ENDPOINT_TEMPLATE
endif

ifdef RPC_UNICODE_SUPPORTED
RPC_INTERFACE_TEMPLATEA struct
Version                 sdword ?
IfSpec                  RPC_IF_HANDLE ?
MgrTypeUuid             ptr UUID ?
MgrEpv                  ptr RPC_MGR_EPV ?
Flags                   dword ?
MaxCalls                dword ?
MaxRpcSize              dword ?
IfCallback              RPC_IF_CALLBACK_FN ?
UuidVector              PUUID_VECTOR ?
Annotation              RPC_CSTR ?
SecurityDescriptor      PVOID ?
RPC_INTERFACE_TEMPLATEA ends
PRPC_INTERFACE_TEMPLATEA typedef ptr RPC_INTERFACE_TEMPLATEA

RPC_INTERFACE_TEMPLATEW struct
Version                 sdword ?
IfSpec                  RPC_IF_HANDLE ?
MgrTypeUuid             ptr UUID ?
MgrEpv                  ptr RPC_MGR_EPV ?
Flags                   dword ?
MaxCalls                dword ?
MaxRpcSize              dword ?
IfCallback              RPC_IF_CALLBACK_FN ?
UuidVector              PUUID_VECTOR ?
Annotation              RPC_WSTR ?
SecurityDescriptor      PVOID ?
RPC_INTERFACE_TEMPLATEW ends
PRPC_INTERFACE_TEMPLATEW typedef ptr RPC_INTERFACE_TEMPLATEW

ifdef _UNICODE
define RPC_INTERFACE_TEMPLATE <RPC_INTERFACE_TEMPLATEW>
define PRPC_INTERFACE_TEMPLATE <PRPC_INTERFACE_TEMPLATEW>
else
define RPC_INTERFACE_TEMPLATE <RPC_INTERFACE_TEMPLATEA>
define PRPC_INTERFACE_TEMPLATE <PRPC_INTERFACE_TEMPLATEA>
endif

else

RPC_INTERFACE_TEMPLATE  struct
Version                 sdword ?
IfSpec                  RPC_IF_HANDLE ?
MgrTypeUuid             ptr UUID ?
MgrEpv                  ptr RPC_MGR_EPV ?
Flags                   dword ?
MaxCalls                dword ?
MaxRpcSize              dword ?
IfCallback              RPC_IF_CALLBACK_FN ?
UuidVector              PUUID_VECTOR ?
Annotation              RPC_CSTR ?
SecurityDescriptor      PVOID ?
RPC_INTERFACE_TEMPLATE  ends
PRPC_INTERFACE_TEMPLATE typedef ptr RPC_INTERFACE_TEMPLATE

endif

CALLBACK(RPC_INTERFACE_GROUP_IDLE_CALLBACK_FN, :RPC_INTERFACE_GROUP, :ptr, :dword)

ifdef RPC_UNICODE_SUPPORTED

RpcServerInterfaceGroupCreateW proto WINAPI :ptr, :sdword, :ptr, :sdword, :sdword, :RPC_INTERFACE_GROUP_IDLE_CALLBACK_FN, :ptr, :PRPC_INTERFACE_GROUP
RpcServerInterfaceGroupCreateA proto WINAPI :ptr, :sdword, :ptr, :sdword, :sdword, :RPC_INTERFACE_GROUP_IDLE_CALLBACK_FN, :ptr, :PRPC_INTERFACE_GROUP
ifdef _UNICODE
define RpcServerInterfaceGroupCreate <RpcServerInterfaceGroupCreateW>
else
define RpcServerInterfaceGroupCreate <RpcServerInterfaceGroupCreateA>
endif

else

RpcServerInterfaceGroupCreate proto WINAPI :ptr, :sdword, :ptr, :sdword, :sdword, :RPC_INTERFACE_GROUP_IDLE_CALLBACK_FN, :ptr, :PRPC_INTERFACE_GROUP

endif

RpcServerInterfaceGroupClose proto WINAPI :RPC_INTERFACE_GROUP
RpcServerInterfaceGroupActivate proto WINAPI :RPC_INTERFACE_GROUP
RpcServerInterfaceGroupDeactivate proto WINAPI :RPC_INTERFACE_GROUP, :sdword
RpcServerInterfaceGroupInqBindings proto WINAPI :RPC_INTERFACE_GROUP, :ptr

endif

endif

include rpcdcep.inc

endif
