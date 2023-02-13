ifndef __OBJIDL_INC
define __OBJIDL_INC

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif

ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __objidl_h__
define __objidl_h__

include unknwn.inc
include winapifamily.inc

if(NTDDI_VERSION ge NTDDI_VISTA and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0600
endif
if(NTDDI_VERSION ge NTDDI_WS03 and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0502
endif
if(NTDDI_VERSION ge NTDDI_WINXP and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0501
endif
if(NTDDI_VERSION ge NTDDI_WIN2K and not defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0500
endif

include limits.inc

ifndef _OBJIDLBASE_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

_COSERVERINFO		struct
dwReserved1		DWORD ?
pwszName		LPWSTR ?
pAuthInfo		ptr COAUTHINFO ?
dwReserved2		DWORD ?
_COSERVERINFO		ends
COSERVERINFO		typedef _COSERVERINFO

ifndef __IMarshal_INTERFACE_DEFINED__
define __IMarshal_INTERFACE_DEFINED__

LPMARSHAL		typedef ptr IMarshal

DEFINE_IIDX(IMarshal, "00000003-0000-0000-C000-000000000046")

.comdef IMarshal : public IUnknown

    GetUnmarshalClass	proc :REFIID, :ptr, :DWORD, :ptr, :DWORD, :ptr
    GetMarshalSizeMax	proc :REFIID, :ptr, :DWORD, :ptr, :DWORD, :ptr
    MarshalInterface	proc :ptr, :REFIID, :ptr, :DWORD, :ptr, :DWORD
    UnmarshalInterface	proc :ptr, :REFIID, :ptr ptr
    ReleaseMarshalData	proc :ptr
    DisconnectObject	proc :DWORD
   .ends

endif

ifndef __INoMarshal_INTERFACE_DEFINED__
define __INoMarshal_INTERFACE_DEFINED__

DEFINE_IIDX(INoMarshal, "ecc8691b-c1db-4dc0-855e-65f6c551af49")

.comdef INoMarshal : public IUnknown
   .ends

endif

ifndef __IAgileObject_INTERFACE_DEFINED__
define __IAgileObject_INTERFACE_DEFINED__

DEFINE_IIDX(IAgileObject, "94ea2b94-e9cc-49e0-c0ff-ee64ca8f5b90")

.comdef IAgileObject : public IUnknown
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IActivationFilter_INTERFACE_DEFINED__
define __IActivationFilter_INTERFACE_DEFINED__

.enum ACTIVATIONTYPE {
    ACTIVATIONTYPE_UNCATEGORIZED	= 0,
    ACTIVATIONTYPE_FROM_MONIKER		= 0x1,
    ACTIVATIONTYPE_FROM_DATA		= 0x2,
    ACTIVATIONTYPE_FROM_STORAGE		= 0x4,
    ACTIVATIONTYPE_FROM_STREAM		= 0x8,
    ACTIVATIONTYPE_FROM_FILE		= 0x10
    }

DEFINE_IIDX(IActivationFilter, "00000017-0000-0000-C000-000000000046")

.comdef IActivationFilter : public IUnknown
    HandleActivation	proc :DWORD, :REFCLSID, :ptr
   .ends

endif

ifndef __IMarshal2_INTERFACE_DEFINED__
define __IMarshal2_INTERFACE_DEFINED__

LPMARSHAL2		typedef ptr IMarshal2

DEFINE_IIDX(IMarshal2, "000001cf-0000-0000-C000-000000000046")

.comdef IMarshal2 : public IMarshal
   .ends

endif

ifndef __IMalloc_INTERFACE_DEFINED__
define __IMalloc_INTERFACE_DEFINED__

LPMALLOC		typedef ptr IMalloc

DEFINE_IIDX(IMalloc, "00000002-0000-0000-C000-000000000046")

.comdef IMalloc : public IUnknown

    Alloc		proc :SIZE_T
    Realloc		proc :ptr, :SIZE_T
    Free		proc :ptr
    GetSize		proc :ptr
    DidAlloc		proc :ptr
    HeapMinimize	proc
   .ends

endif

ifndef __IStdMarshalInfo_INTERFACE_DEFINED__
define __IStdMarshalInfo_INTERFACE_DEFINED__

LPSTDMARSHALINFO	typedef ptr IStdMarshalInfo

DEFINE_IIDX(IStdMarshalInfo, "00000018-0000-0000-C000-000000000046")

.comdef IStdMarshalInfo : public IUnknown

    GetClassForHandler	proc :DWORD, :ptr, :ptr
   .ends

endif

ifndef __IExternalConnection_INTERFACE_DEFINED__
define __IExternalConnection_INTERFACE_DEFINED__

LPEXTERNALCONNECTION	typedef ptr IExternalConnection

.enum EXTCONN {
    EXTCONN_STRONG	= 0x1,
    EXTCONN_WEAK	= 0x2,
    EXTCONN_CALLABLE	= 0x4
    }

DEFINE_IIDX(IExternalConnection, "00000019-0000-0000-C000-000000000046")

.comdef IExternalConnection : public IUnknown

    AddConnection	proc :DWORD, :DWORD
    ReleaseConnection	proc :DWORD, :DWORD, :BOOL
   .ends

endif

LPMULTIQI		typedef ptr IMultiQI

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

tagMULTI_QI		struct
pIID			ptr IID ?
pItf			ptr IUnknown ?
hr			HRESULT ?
tagMULTI_QI		ends
MULTI_QI		typedef tagMULTI_QI

ifndef __IMultiQI_INTERFACE_DEFINED__
define __IMultiQI_INTERFACE_DEFINED__

DEFINE_IIDX(IMultiQI, "00000020-0000-0000-C000-000000000046")

.comdef IMultiQI : public IUnknown

    QueryMultipleInterfaces proc :ULONG, :ptr
   .ends

endif

ifndef __AsyncIMultiQI_INTERFACE_DEFINED__
define __AsyncIMultiQI_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIMultiQI, "000e0020-0000-0000-C000-000000000046")

.comdef AsyncIMultiQI : public IUnknown

    Begin_QueryMultipleInterfaces proc :ULONG, :ptr
    Finish_QueryMultipleInterfaces proc :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IInternalUnknown_INTERFACE_DEFINED__
define __IInternalUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(IInternalUnknown, "00000021-0000-0000-C000-000000000046")

.comdef IInternalUnknown : public IUnknown
    QueryInternalInterface proc :REFIID, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IEnumUnknown_INTERFACE_DEFINED__
define __IEnumUnknown_INTERFACE_DEFINED__

LPENUMUNKNOWN		typedef ptr IEnumUnknown

DEFINE_IIDX(IEnumUnknown, "00000100-0000-0000-C000-000000000046")

.comdef IEnumUnknown : public IUnknown
    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumUnknown_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumUnknown_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumString_INTERFACE_DEFINED__
define __IEnumString_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumString, "00000101-0000-0000-C000-000000000046")

.comdef IEnumString : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

LPENUMSTRING		typedef ptr IEnumString

IEnumString_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumString_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __ISequentialStream_INTERFACE_DEFINED__
define __ISequentialStream_INTERFACE_DEFINED__

DEFINE_IIDX(ISequentialStream, "0c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ISequentialStream : public IUnknown

    Read		proc :ptr, :ULONG, :ptr
    Write		proc :ptr, :ULONG, :ptr
   .ends

ISequentialStream_RemoteRead_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_RemoteRead_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
ISequentialStream_RemoteWrite_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_RemoteWrite_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IStream_INTERFACE_DEFINED__
define __IStream_INTERFACE_DEFINED__

LPSTREAM		typedef ptr IStream

tagSTATSTG		struct
pwcsName		LPOLESTR ?
type			DWORD ?
cbSize			ULARGE_INTEGER <>
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
grfMode			DWORD ?
grfLocksSupported	DWORD ?
clsid			CLSID <>
grfStateBits		DWORD ?
reserved		DWORD ?
tagSTATSTG		ends
STATSTG			typedef tagSTATSTG

.enum STGTY {
	STGTY_STORAGE	= 1,
	STGTY_STREAM	= 2,
	STGTY_LOCKBYTES = 3,
	STGTY_PROPERTY	= 4
    }

.enum STREAM_SEEK {
	STREAM_SEEK_SET = 0,
	STREAM_SEEK_CUR = 1,
	STREAM_SEEK_END = 2
    }

.enum LOCKTYPE {
	LOCK_WRITE	= 1,
	LOCK_EXCLUSIVE	= 2,
	LOCK_ONLYONCE	= 4
    }

DEFINE_IIDX(IStream, "0000000c-0000-0000-C000-000000000046")

.comdef IStream : public ISequentialStream

    Seek		proc :LARGE_INTEGER, :DWORD, :ptr
    SetSize		proc :ULARGE_INTEGER
    CopyTo		proc :ptr, :ULARGE_INTEGER, :ptr, :ptr
    Commit		proc :DWORD
    Revert		proc
    LockRegion		proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    UnlockRegion	proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    Stat		proc :ptr, :DWORD
    Clone		proc :ptr ptr
   .ends

IStream_RemoteSeek_Proxy proto WINAPI :ptr, :LARGE_INTEGER, :DWORD, :ptr
IStream_RemoteSeek_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IStream_RemoteCopyTo_Proxy proto WINAPI :ptr, :ptr, :ULARGE_INTEGER, :ptr, :ptr
IStream_RemoteCopyTo_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IRpcChannelBuffer_INTERFACE_DEFINED__
define __IRpcChannelBuffer_INTERFACE_DEFINED__

RPCOLEDATAREP		typedef ULONG

tagRPCOLEMESSAGE	struct
reserved1		ptr ?
dataRepresentation	RPCOLEDATAREP ?
Buffer			ptr ?
cbBuffer		ULONG ?
iMethod			ULONG ?
reserved2		ptr 5 dup(?)
rpcFlags		ULONG ?
tagRPCOLEMESSAGE	ends
RPCOLEMESSAGE		typedef tagRPCOLEMESSAGE

PRPCOLEMESSAGE		typedef ptr RPCOLEMESSAGE

DEFINE_IIDX(IRpcChannelBuffer, "D5F56B60-593B-101A-B569-08002B2DBF7A")

.comdef IRpcChannelBuffer : public IUnknown
    GetBuffer		proc :ptr, :REFIID
    SendReceive		proc :ptr, :ptr
    FreeBuffer		proc :ptr
    GetDestCtx		proc :ptr, :ptr ptr
    IsConnected		proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IRpcChannelBuffer2_INTERFACE_DEFINED__
define __IRpcChannelBuffer2_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcChannelBuffer2, "594f31d0-7f19-11d0-b194-00a0c90dc8bf")

.comdef IRpcChannelBuffer2 : public IRpcChannelBuffer

    GetProtocolVersion	proc :ptr
   .ends

endif

ifndef __IAsyncRpcChannelBuffer_INTERFACE_DEFINED__
define __IAsyncRpcChannelBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IAsyncRpcChannelBuffer, "a5029fb6-3c34-11d1-9c99-00c04fb998aa")

.comdef IAsyncRpcChannelBuffer : public IRpcChannelBuffer2

    Send		proc :ptr, :ptr, :ptr
    Receive		proc :ptr, :ptr
    GetDestCtxEx	proc :ptr, :ptr, :ptr ptr
   .ends

endif

ifndef __IRpcChannelBuffer3_INTERFACE_DEFINED__
define __IRpcChannelBuffer3_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcChannelBuffer3, "25B15600-0115-11d0-BF0D-00AA00B8DFD2")

.comdef IRpcChannelBuffer3 : public IRpcChannelBuffer2

    Send		proc :ptr, :ptr
    Receive		proc :ptr, :ULONG, :ptr
    Cancel		proc :ptr
    GetCallContext	proc :ptr, :REFIID, :ptr ptr
    GetDestCtxEx	proc :ptr, :ptr, :ptr ptr
    GetState		proc :ptr, :ptr
    RegisterAsync	proc :ptr, :ptr
   .ends

endif

ifndef __IRpcSyntaxNegotiate_INTERFACE_DEFINED__
define __IRpcSyntaxNegotiate_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcSyntaxNegotiate, "58a08519-24c8-4935-b482-3fd823333a4f")

.comdef IRpcSyntaxNegotiate : public IUnknown

    NegotiateSyntax	proc :ptr
   .ends

endif

ifndef __IRpcProxyBuffer_INTERFACE_DEFINED__
define __IRpcProxyBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcProxyBuffer, "D5F56A34-593B-101A-B569-08002B2DBF7A")

.comdef IRpcProxyBuffer : public IUnknown

    Connect		proc :ptr
    Disconnect		proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IRpcStubBuffer_INTERFACE_DEFINED__
define __IRpcStubBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcStubBuffer, "D5F56AFC-593B-101A-B569-08002B2DBF7A")

.comdef IRpcStubBuffer : public IUnknown

    Connect		proc :ptr
    Disconnect		proc
    _Invoke		proc :ptr, :ptr
    IsIIDSupported	proc :REFIID
    CountRefs		proc
    DebugServerQueryInterface proc :ptr ptr
    DebugServerRelease	proc :ptr
   .ends

endif

ifndef __IPSFactoryBuffer_INTERFACE_DEFINED__
define __IPSFactoryBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IPSFactoryBuffer, "D5F569D0-593B-101A-B569-08002B2DBF7A")

.comdef IPSFactoryBuffer : public IUnknown

    CreateProxy		proc :ptr, :REFIID, :ptr ptr, :ptr ptr
    CreateStub		proc :REFIID, :ptr, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
if  (_WIN32_WINNT ge 0x0400 ) or defined(_WIN32_DCOM)
SChannelHookCallInfo	struct
iid			IID <>
cbSize			DWORD ?
uCausality		GUID <>
dwServerPid		DWORD ?
iMethod			DWORD ?
pObject			ptr ?
SChannelHookCallInfo	ends

ifndef __IChannelHook_INTERFACE_DEFINED__
define __IChannelHook_INTERFACE_DEFINED__

DEFINE_IIDX(IChannelHook, "1008c4a0-7613-11cf-9af1-0020af6e72f4")

.comdef IChannelHook : public IUnknown

    ClientGetSize	proc :REFGUID, :REFIID, :ptr
    ClientFillBuffer	proc :REFGUID, :REFIID, :ptr, :ptr
    ClientNotify	proc :REFGUID, :REFIID, :ULONG, :ptr, :DWORD, :HRESULT
    ServerNotify	proc :REFGUID, :REFIID, :ULONG, :ptr, :DWORD
    ServerGetSize	proc :REFGUID, :REFIID, :HRESULT, :ptr
    ServerFillBuffer	proc :REFGUID, :REFIID, :ptr, :ptr, :HRESULT
   .ends

endif

endif
endif

if (_WIN32_WINNT ge 0x0400 ) or defined(_WIN32_DCOM)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IClientSecurity_INTERFACE_DEFINED__
define __IClientSecurity_INTERFACE_DEFINED__

tagSOLE_AUTHENTICATION_SERVICE struct
dwAuthnSvc		DWORD ?
dwAuthzSvc		DWORD ?
pPrincipalName		ptr OLECHAR ?
hr			HRESULT ?
tagSOLE_AUTHENTICATION_SERVICE ends
SOLE_AUTHENTICATION_SERVICE typedef tagSOLE_AUTHENTICATION_SERVICE

PSOLE_AUTHENTICATION_SERVICE typedef ptr SOLE_AUTHENTICATION_SERVICE

.enum EOLE_AUTHENTICATION_CAPABILITIES {
	EOAC_NONE	= 0,
	EOAC_MUTUAL_AUTH	= 0x1,
	EOAC_STATIC_CLOAKING	= 0x20,
	EOAC_DYNAMIC_CLOAKING	= 0x40,
	EOAC_ANY_AUTHORITY	= 0x80,
	EOAC_MAKE_FULLSIC	= 0x100,
	EOAC_DEFAULT	= 0x800,
	EOAC_SECURE_REFS	= 0x2,
	EOAC_ACCESS_CONTROL	= 0x4,
	EOAC_APPID	= 0x8,
	EOAC_DYNAMIC	= 0x10,
	EOAC_REQUIRE_FULLSIC	= 0x200,
	EOAC_AUTO_IMPERSONATE	= 0x400,
	EOAC_DISABLE_AAA	= 0x1000,
	EOAC_NO_CUSTOM_MARSHAL	= 0x2000,
	EOAC_RESERVED1	= 0x4000
    }

define	COLE_DEFAULT_PRINCIPAL	( -1 )
define	COLE_DEFAULT_AUTHINFO	( -1 )

tagSOLE_AUTHENTICATION_INFO struct
dwAuthnSvc		DWORD ?
dwAuthzSvc		DWORD ?
pAuthInfo		ptr ?
tagSOLE_AUTHENTICATION_INFO ends
SOLE_AUTHENTICATION_INFO typedef tagSOLE_AUTHENTICATION_INFO

PSOLE_AUTHENTICATION_INFO typedef ptr tagSOLE_AUTHENTICATION_INFO

tagSOLE_AUTHENTICATION_LIST struct
cAuthInfo		DWORD ?
aAuthInfo		ptr SOLE_AUTHENTICATION_INFO ?
tagSOLE_AUTHENTICATION_LIST ends
SOLE_AUTHENTICATION_LIST typedef tagSOLE_AUTHENTICATION_LIST

PSOLE_AUTHENTICATION_LIST typedef ptr tagSOLE_AUTHENTICATION_LIST

DEFINE_IIDX(IClientSecurity, "0000013D-0000-0000-C000-000000000046")

.comdef IClientSecurity : public IUnknown

    QueryBlanket	proc :ptr, :ptr, :ptr, :ptr ptr, :ptr, :ptr, :ptr ptr, :ptr
    SetBlanket		proc :ptr, :DWORD, :DWORD, :ptr, :DWORD, :DWORD, :ptr, :DWORD
    CopyProxy		proc :ptr, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IServerSecurity_INTERFACE_DEFINED__
define __IServerSecurity_INTERFACE_DEFINED__

DEFINE_IIDX(IServerSecurity, "0000013E-0000-0000-C000-000000000046")

.comdef IServerSecurity : public IUnknown

    QueryBlanket	proc :ptr, :ptr, :ptr ptr, :ptr, :ptr, :ptr ptr, :ptr
    ImpersonateClient	proc
    RevertToSelf	proc
    IsImpersonating	proc
   .ends

endif

.enum RPCOPT_PROPERTIES {
	COMBND_RPCTIMEOUT	= 0x1,
	COMBND_SERVER_LOCALITY	= 0x2,
	COMBND_RESERVED1	= 0x4,
	COMBND_RESERVED2	= 0x5,
	COMBND_RESERVED3	= 0x8,
	COMBND_RESERVED4	= 0x10
    }

.enum RPCOPT_SERVER_LOCALITY_VALUES {
	SERVER_LOCALITY_PROCESS_LOCAL	= 0,
	SERVER_LOCALITY_MACHINE_LOCAL	= 1,
	SERVER_LOCALITY_REMOTE	= 2
    }

ifndef __IRpcOptions_INTERFACE_DEFINED__
define __IRpcOptions_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcOptions, "00000144-0000-0000-C000-000000000046")

.comdef IRpcOptions : public IUnknown
    Set			proc :ptr, :RPCOPT_PROPERTIES, :ULONG_PTR
    Query		proc :ptr, :RPCOPT_PROPERTIES, :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

.enum GLOBALOPT_PROPERTIES {
	COMGLB_EXCEPTION_HANDLING	= 1,
	COMGLB_APPID	= 2,
	COMGLB_RPC_THREADPOOL_SETTING	= 3,
	COMGLB_RO_SETTINGS	= 4,
	COMGLB_UNMARSHALING_POLICY	= 5,
	COMGLB_PROPERTIES_RESERVED1	= 6,
	COMGLB_PROPERTIES_RESERVED2	= 7,
	COMGLB_PROPERTIES_RESERVED3	= 8
    }

.enum GLOBALOPT_EH_VALUES {
	COMGLB_EXCEPTION_HANDLE = 0,
	COMGLB_EXCEPTION_DONOT_HANDLE_FATAL	= 1,
	COMGLB_EXCEPTION_DONOT_HANDLE	= COMGLB_EXCEPTION_DONOT_HANDLE_FATAL,
	COMGLB_EXCEPTION_DONOT_HANDLE_ANY	= 2
    }

.enum GLOBALOPT_RPCTP_VALUES {
	COMGLB_RPC_THREADPOOL_SETTING_DEFAULT_POOL	= 0,
	COMGLB_RPC_THREADPOOL_SETTING_PRIVATE_POOL	= 1
    }

.enum GLOBALOPT_RO_FLAGS {
	COMGLB_STA_MODALLOOP_REMOVE_TOUCH_MESSAGES	= 0x1,
	COMGLB_STA_MODALLOOP_SHARED_QUEUE_REMOVE_INPUT_MESSAGES = 0x2,
	COMGLB_STA_MODALLOOP_SHARED_QUEUE_DONOT_REMOVE_INPUT_MESSAGES	= 0x4,
	COMGLB_FAST_RUNDOWN	= 0x8,
	COMGLB_RESERVED1	= 0x10,
	COMGLB_RESERVED2	= 0x20,
	COMGLB_RESERVED3	= 0x40,
	COMGLB_STA_MODALLOOP_SHARED_QUEUE_REORDER_POINTER_MESSAGES	= 0x80,
	COMGLB_RESERVED4	= 0x100,
	COMGLB_RESERVED5	= 0x200,
	COMGLB_RESERVED6	= 0x400
    }

.enum GLOBALOPT_UNMARSHALING_POLICY_VALUES {
	COMGLB_UNMARSHALING_POLICY_NORMAL	= 0,
	COMGLB_UNMARSHALING_POLICY_STRONG	= 1,
	COMGLB_UNMARSHALING_POLICY_HYBRID	= 2
    }

ifndef __IGlobalOptions_INTERFACE_DEFINED__
define __IGlobalOptions_INTERFACE_DEFINED__

DEFINE_IIDX(IGlobalOptions, "0000015B-0000-0000-C000-000000000046")

.comdef IGlobalOptions : public IUnknown

    Set			proc :GLOBALOPT_PROPERTIES, :ULONG_PTR
    Query		proc :GLOBALOPT_PROPERTIES, :ptr
   .ends

endif

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __ISurrogate_INTERFACE_DEFINED__
define __ISurrogate_INTERFACE_DEFINED__

LPSURROGATE		typedef ptr ISurrogate

DEFINE_IIDX(ISurrogate, "00000022-0000-0000-C000-000000000046")

.comdef ISurrogate : public IUnknown
    LoadDllServer	proc :REFCLSID
    FreeSurrogate	proc
   .ends

endif

ifndef __IGlobalInterfaceTable_INTERFACE_DEFINED__
define __IGlobalInterfaceTable_INTERFACE_DEFINED__

LPGLOBALINTERFACETABLE	typedef ptr IGlobalInterfaceTable

DEFINE_IIDX(IGlobalInterfaceTable, "00000146-0000-0000-C000-000000000046")

.comdef IGlobalInterfaceTable : public IUnknown
    RegisterInterfaceInGlobal proc :ptr, :REFIID, :ptr
    RevokeInterfaceFromGlobal proc :DWORD
    GetInterfaceFromGlobal proc :DWORD, :REFIID, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __ISynchronize_INTERFACE_DEFINED__
define __ISynchronize_INTERFACE_DEFINED__

DEFINE_IIDX(ISynchronize, "00000030-0000-0000-C000-000000000046")

.comdef ISynchronize : public IUnknown

    _Wait		proc :DWORD, :DWORD
    Signal		proc
    Reset		proc
   .ends

endif

ifndef __ISynchronizeHandle_INTERFACE_DEFINED__
define __ISynchronizeHandle_INTERFACE_DEFINED__

DEFINE_IIDX(ISynchronizeHandle, "00000031-0000-0000-C000-000000000046")

.comdef ISynchronizeHandle : public IUnknown

    GetHandle		proc :ptr
   .ends

endif

ifndef __ISynchronizeEvent_INTERFACE_DEFINED__
define __ISynchronizeEvent_INTERFACE_DEFINED__

DEFINE_IIDX(ISynchronizeEvent, "00000032-0000-0000-C000-000000000046")

.comdef ISynchronizeEvent : public ISynchronizeHandle

    SetEventHandle	proc :ptr
   .ends

endif

ifndef __ISynchronizeContainer_INTERFACE_DEFINED__
define __ISynchronizeContainer_INTERFACE_DEFINED__

DEFINE_IIDX(ISynchronizeContainer, "00000033-0000-0000-C000-000000000046")

.comdef ISynchronizeContainer : public IUnknown

    AddSynchronize	proc :ptr
    WaitMultiple	proc :DWORD, :DWORD, :ptr ptr
   .ends

endif

ifndef __ISynchronizeMutex_INTERFACE_DEFINED__
define __ISynchronizeMutex_INTERFACE_DEFINED__

DEFINE_IIDX(ISynchronizeMutex, "00000025-0000-0000-C000-000000000046")

.comdef ISynchronizeMutex : public ISynchronize

    ReleaseMutex	proc
   .ends

endif

ifndef __ICancelMethodCalls_INTERFACE_DEFINED__
define __ICancelMethodCalls_INTERFACE_DEFINED__

LPCANCELMETHODCALLS	typedef ptr ICancelMethodCalls

DEFINE_IIDX(ICancelMethodCalls, "00000029-0000-0000-C000-000000000046")

.comdef ICancelMethodCalls : public IUnknown

    Cancel		proc :ULONG
    TestCancel		proc
   .ends

endif

ifndef __IAsyncManager_INTERFACE_DEFINED__
define __IAsyncManager_INTERFACE_DEFINED__

.enum DCOM_CALL_STATE {
	DCOM_NONE	= 0,
	DCOM_CALL_COMPLETE	= 0x1,
	DCOM_CALL_CANCELED	= 0x2
    }

DEFINE_IIDX(IAsyncManager, "0000002A-0000-0000-C000-000000000046")

.comdef IAsyncManager : public IUnknown

    CompleteCall	proc :HRESULT
    GetCallContext	proc :REFIID, :ptr ptr
    GetState		proc :ptr
   .ends

endif

ifndef __ICallFactory_INTERFACE_DEFINED__
define __ICallFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ICallFactory, "1c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ICallFactory : public IUnknown

    CreateCall		proc :REFIID, :ptr, :REFIID, :ptr ptr
   .ends

endif

ifndef __IRpcHelper_INTERFACE_DEFINED__
define __IRpcHelper_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcHelper, "00000149-0000-0000-C000-000000000046")

.comdef IRpcHelper : public IUnknown

    GetDCOMProtocolVersion proc :ptr
    GetIIDFromOBJREF	proc :ptr, :ptr ptr
   .ends

endif

ifndef __IReleaseMarshalBuffers_INTERFACE_DEFINED__
define __IReleaseMarshalBuffers_INTERFACE_DEFINED__

DEFINE_IIDX(IReleaseMarshalBuffers, "eb0cb9e8-7996-11d2-872e-0000f8080859")

.comdef IReleaseMarshalBuffers : public IUnknown

    ReleaseMarshalBuffer proc :ptr, :DWORD, :ptr
   .ends

endif

ifndef __IWaitMultiple_INTERFACE_DEFINED__
define __IWaitMultiple_INTERFACE_DEFINED__

DEFINE_IIDX(IWaitMultiple, "0000002B-0000-0000-C000-000000000046")

.comdef IWaitMultiple : public IUnknown

    WaitMultiple	proc :DWORD, :ptr ptr
    AddSynchronize	proc :ptr
   .ends

endif

ifndef __IAddrTrackingControl_INTERFACE_DEFINED__
define __IAddrTrackingControl_INTERFACE_DEFINED__

LPADDRTRACKINGCONTROL	typedef ptr IAddrTrackingControl

DEFINE_IIDX(IAddrTrackingControl, "00000147-0000-0000-C000-000000000046")

.comdef IAddrTrackingControl : public IUnknown

    EnableCOMDynamicAddrTracking proc
    DisableCOMDynamicAddrTracking proc
   .ends

endif

ifndef __IAddrExclusionControl_INTERFACE_DEFINED__
define __IAddrExclusionControl_INTERFACE_DEFINED__

LPADDREXCLUSIONCONTROL	typedef ptr IAddrExclusionControl

DEFINE_IIDX(IAddrExclusionControl, "00000148-0000-0000-C000-000000000046")

.comdef IAddrExclusionControl : public IUnknown

    GetCurrentAddrExclusionList proc :REFIID, :ptr ptr
    UpdateAddrExclusionList proc :ptr
   .ends

endif

ifndef __IPipeByte_INTERFACE_DEFINED__
define __IPipeByte_INTERFACE_DEFINED__

DEFINE_IIDX(IPipeByte, "DB2F3ACA-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeByte : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc :ptr, :ULONG
   .ends

endif

ifndef __AsyncIPipeByte_INTERFACE_DEFINED__
define __AsyncIPipeByte_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIPipeByte, "DB2F3ACB-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeByte : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc :ptr, :ULONG
    Finish_Push		proc
   .ends

endif

ifndef __IPipeLong_INTERFACE_DEFINED__
define __IPipeLong_INTERFACE_DEFINED__

DEFINE_IIDX(IPipeLong, "DB2F3ACC-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeLong : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc :ptr, :ULONG
   .ends

endif

ifndef __AsyncIPipeLong_INTERFACE_DEFINED__
define __AsyncIPipeLong_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIPipeLong, "DB2F3ACD-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeLong : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc :ptr, :ULONG
    Finish_Push		proc
   .ends

endif

ifndef __IPipeDouble_INTERFACE_DEFINED__
define __IPipeDouble_INTERFACE_DEFINED__

DEFINE_IIDX(IPipeDouble, "DB2F3ACE-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeDouble : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc :ptr, :ULONG
   .ends

endif

ifndef __AsyncIPipeDouble_INTERFACE_DEFINED__
define __AsyncIPipeDouble_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIPipeDouble, "DB2F3ACF-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeDouble : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc :ptr, :ULONG
    Finish_Push		proc
   .ends

endif

if defined(USE_COM_CONTEXT_DEF) or defined(BUILDTYPE_COMSVCS) or defined(_COMBASEAPI_) or defined(_OLE32_)

CPFLAGS			typedef DWORD

tagContextProperty	struct
policyId		GUID <>
flags			CPFLAGS ?
pUnk			LPUNKNOWN ?
tagContextProperty	ends
ContextProperty		typedef tagContextProperty

ifndef __IEnumContextProps_INTERFACE_DEFINED__
define __IEnumContextProps_INTERFACE_DEFINED__

LPENUMCONTEXTPROPS	typedef ptr IEnumContextProps

DEFINE_IIDX(IEnumContextProps, "000001c1-0000-0000-C000-000000000046")

.comdef IEnumContextProps : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
    Count		proc :ptr
   .ends

endif

ifndef __IContext_INTERFACE_DEFINED__
define __IContext_INTERFACE_DEFINED__

DEFINE_IIDX(IContext, "000001c0-0000-0000-C000-000000000046")

.comdef IContext : public IUnknown

    SetProperty		proc :REFGUID, :CPFLAGS, :ptr
    RemoveProperty	proc :REFGUID
    GetProperty		proc :REFGUID, :ptr, :ptr ptr
    EnumContextProps	proc :ptr ptr
   .ends

endif

if not defined BUILDTYPE_COMSVCS and not (defined _COMBASEAPI_ or defined _OLE32_)

ifndef __IObjContext_INTERFACE_DEFINED__
define __IObjContext_INTERFACE_DEFINED__

DEFINE_IIDX(IObjContext, "000001c6-0000-0000-C000-000000000046")

.comdef IObjContext : public IContext

    Reserved1		proc
    Reserved2		proc
    Reserved3		proc
    Reserved4		proc
    Reserved5		proc
    Reserved6		proc
    Reserved7		proc
   .ends

endif

endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

.enum APTTYPEQUALIFIER {
	APTTYPEQUALIFIER_NONE	= 0,
	APTTYPEQUALIFIER_IMPLICIT_MTA	= 1,
	APTTYPEQUALIFIER_NA_ON_MTA	= 2,
	APTTYPEQUALIFIER_NA_ON_STA	= 3,
	APTTYPEQUALIFIER_NA_ON_IMPLICIT_MTA	= 4,
	APTTYPEQUALIFIER_NA_ON_MAINSTA	= 5,
	APTTYPEQUALIFIER_APPLICATION_STA	= 6,
	APTTYPEQUALIFIER_RESERVED_1	= 7
    }

.enum APTTYPE {
	APTTYPE_CURRENT = -1,
	APTTYPE_STA	= 0,
	APTTYPE_MTA	= 1,
	APTTYPE_NA	= 2,
	APTTYPE_MAINSTA = 3
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
.enum THDTYPE {
	THDTYPE_BLOCKMESSAGES	= 0,
	THDTYPE_PROCESSMESSAGES = 1
    }

APARTMENTID		typedef DWORD

ifndef __IComThreadingInfo_INTERFACE_DEFINED__
define __IComThreadingInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IComThreadingInfo, "000001ce-0000-0000-C000-000000000046")

.comdef IComThreadingInfo : public IUnknown

    GetCurrentApartmentType proc :ptr
    GetCurrentThreadType proc :ptr
    GetCurrentLogicalThreadId proc :ptr
    SetCurrentLogicalThreadId proc :REFGUID
   .ends

endif

ifndef __IProcessInitControl_INTERFACE_DEFINED__
define __IProcessInitControl_INTERFACE_DEFINED__

DEFINE_IIDX(IProcessInitControl, "72380d55-8d2b-43a3-8513-2b6ef31434e9")

.comdef IProcessInitControl : public IUnknown

    ResetInitializerTimeout proc :DWORD
   .ends

endif

ifndef __IFastRundown_INTERFACE_DEFINED__
define __IFastRundown_INTERFACE_DEFINED__

DEFINE_IIDX(IFastRundown, "00000040-0000-0000-C000-000000000046")

.comdef IFastRundown : public IUnknown
   .ends

endif

.enum CO_MARSHALING_CONTEXT_ATTRIBUTES {
	CO_MARSHALING_SOURCE_IS_APP_CONTAINER	= 0,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_1	= 0x80000000,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_2	= 0x80000001,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_3	= 0x80000002,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_4	= 0x80000003,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_5	= 0x80000004,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_6	= 0x80000005,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_7	= 0x80000006,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_8	= 0x80000007,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_9	= 0x80000008,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_10	= 0x80000009,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_11	= 0x8000000a,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_12	= 0x8000000b,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_13	= 0x8000000c,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_14	= 0x8000000d,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_15	= 0x8000000e,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_16	= 0x8000000f,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_17	= 0x80000010,
	CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_18	= 0x80000011
    }

ifndef __IMarshalingStream_INTERFACE_DEFINED__
define __IMarshalingStream_INTERFACE_DEFINED__

DEFINE_IIDX(IMarshalingStream, "D8F2F5E6-6102-4863-9F26-389A4676EFDE")

.comdef IMarshalingStream : public IStream

    GetMarshalingContextAttribute proc :CO_MARSHALING_CONTEXT_ATTRIBUTES, :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IAgileReference_INTERFACE_DEFINED__
define __IAgileReference_INTERFACE_DEFINED__

DEFINE_IIDX(IAgileReference, "C03F6A43-65A4-9818-987E-E0B810D2A6F2")

.comdef IAgileReference : public IUnknown

    Resolve		proc :REFIID, :ptr ptr
   .ends


endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)
externdef IID_ICallbackWithNoReentrancyToApplicationSTA:GUID
endif

define _OBJIDLBASE_
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IMallocSpy_INTERFACE_DEFINED__
define __IMallocSpy_INTERFACE_DEFINED__

LPMALLOCSPY		typedef ptr IMallocSpy

DEFINE_IIDX(IMallocSpy, "0000001d-0000-0000-C000-000000000046")

.comdef IMallocSpy : public IUnknown

    PreAlloc		proc :SIZE_T
    PostAlloc		proc :ptr
    PreFree		proc :ptr, :BOOL
    PostFree		proc :BOOL
    PreRealloc		proc :ptr, :SIZE_T, :ptr ptr, :BOOL
    PostRealloc		proc :ptr, :BOOL
    PreGetSize		proc :ptr, :BOOL
    PostGetSize		proc :SIZE_T, :BOOL
    PreDidAlloc		proc :ptr, :BOOL
    PostDidAlloc	proc :ptr, :BOOL, :int_t
    PreHeapMinimize	proc
    PostHeapMinimize	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IBindCtx_INTERFACE_DEFINED__
define __IBindCtx_INTERFACE_DEFINED__

LPBC			typedef ptr IBindCtx
LPBINDCTX		typedef ptr IBindCtx

tagBIND_OPTS		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
tagBIND_OPTS		ends
BIND_OPTS		typedef tagBIND_OPTS
LPBIND_OPTS		typedef ptr tagBIND_OPTS

tagBIND_OPTS2		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
dwTrackFlags		DWORD ?
dwClassContext		DWORD ?
locale			LCID ?
pServerInfo		ptr COSERVERINFO ?
tagBIND_OPTS2		ends
BIND_OPTS2		typedef tagBIND_OPTS2

LPBIND_OPTS2		typedef ptr tagBIND_OPTS2

tagBIND_OPTS3		struct
cbStruct		DWORD ?
grfFlags		DWORD ?
grfMode			DWORD ?
dwTickCountDeadline	DWORD ?
dwTrackFlags		DWORD ?
dwClassContext		DWORD ?
locale			LCID ?
pServerInfo		ptr COSERVERINFO ?
hwnd			HWND ?
tagBIND_OPTS3		ends
BIND_OPTS3		typedef tagBIND_OPTS3
LPBIND_OPTS3		typedef ptr tagBIND_OPTS3

.enum BIND_FLAGS {
	BIND_MAYBOTHERUSER	= 1,
	BIND_JUSTTESTEXISTENCE	= 2
    }

DEFINE_IIDX(IBindCtx, "0000000e-0000-0000-C000-000000000046")

.comdef IBindCtx : public IUnknown
    RegisterObjectBound proc :ptr
    RevokeObjectBound	proc :ptr
    ReleaseBoundObjects proc
    SetBindOptions	proc :ptr
    GetBindOptions	proc :ptr
    GetRunningObjectTable proc :ptr ptr
    RegisterObjectParam proc :LPOLESTR, :ptr
    GetObjectParam	proc :LPOLESTR, :ptr ptr
    EnumObjectParam	proc :ptr ptr
    RevokeObjectParam	proc :LPOLESTR
   .ends

IBindCtx_RemoteSetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_RemoteSetBindOptions_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IBindCtx_RemoteGetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_RemoteGetBindOptions_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumMoniker_INTERFACE_DEFINED__
define __IEnumMoniker_INTERFACE_DEFINED__

LPENUMMONIKER		typedef ptr IEnumMoniker

DEFINE_IIDX(IEnumMoniker, "00000102-0000-0000-C000-000000000046")

.comdef IEnumMoniker : public IUnknown

    Next		proc :ULONG, :ptr ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumMoniker_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumMoniker_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IRunnableObject_INTERFACE_DEFINED__
define __IRunnableObject_INTERFACE_DEFINED__

LPRUNNABLEOBJECT	typedef ptr IRunnableObject

DEFINE_IIDX(IRunnableObject, "00000126-0000-0000-C000-000000000046")

.comdef IRunnableObject : public IUnknown

    GetRunningClass	proc :LPCLSID
    Run			proc :LPBINDCTX
    IsRunning		proc
    LockRunning		proc :BOOL, :BOOL
    SetContainedObject	proc :BOOL
   .ends

IRunnableObject_RemoteIsRunning_Proxy proto WINAPI :ptr
IRunnableObject_RemoteIsRunning_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IRunningObjectTable_INTERFACE_DEFINED__
define __IRunningObjectTable_INTERFACE_DEFINED__

LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable

DEFINE_IIDX(IRunningObjectTable, "00000010-0000-0000-C000-000000000046")

.comdef IRunningObjectTable : public IUnknown

    Register		proc :DWORD, :ptr, :ptr, :ptr
    Revoke		proc :DWORD
    IsRunning		proc :ptr
    GetObject		proc :ptr, :ptr ptr
    NoteChangeTime	proc :DWORD, :ptr
    GetTimeOfLastChange proc :ptr, :ptr
    EnumRunning		proc :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IPersist_INTERFACE_DEFINED__
define __IPersist_INTERFACE_DEFINED__

LPPERSIST		typedef ptr IPersist

DEFINE_IIDX(IPersist, "0000010c-0000-0000-C000-000000000046")

.comdef IPersist : public IUnknown

    GetClassID		proc :ptr
   .ends

endif

ifndef __IPersistStream_INTERFACE_DEFINED__
define __IPersistStream_INTERFACE_DEFINED__

LPPERSISTSTREAM		typedef ptr IPersistStream

DEFINE_IIDX(IPersistStream, "00000109-0000-0000-C000-000000000046")

.comdef IPersistStream : public IPersist

    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr
   .ends

endif

ifndef __IMoniker_INTERFACE_DEFINED__
define __IMoniker_INTERFACE_DEFINED__

LPMONIKER		typedef ptr IMoniker

.enum MKSYS {
	MKSYS_NONE	= 0,
	MKSYS_GENERICCOMPOSITE	= 1,
	MKSYS_FILEMONIKER	= 2,
	MKSYS_ANTIMONIKER	= 3,
	MKSYS_ITEMMONIKER	= 4,
	MKSYS_POINTERMONIKER	= 5,
	MKSYS_CLASSMONIKER	= 7,
	MKSYS_OBJREFMONIKER	= 8,
	MKSYS_SESSIONMONIKER	= 9,
	MKSYS_LUAMONIKER	= 10
    }

.enum MKRREDUCE {
	MKRREDUCE_ONE	= ( 3 shl 16 ) ,
	MKRREDUCE_TOUSER	= ( 2 shl 16 ) ,
	MKRREDUCE_THROUGHUSER	= ( 1 shl 16 ) ,
	MKRREDUCE_ALL	= 0
    }

DEFINE_IIDX(IMoniker, "0000000f-0000-0000-C000-000000000046")

.comdef IMoniker : public IPersistStream

    BindToObject	proc :ptr, :ptr, :REFIID, :ptr ptr
    BindToStorage	proc :ptr, :ptr, :REFIID, :ptr ptr
    Reduce		proc :ptr, :DWORD, :ptr ptr, :ptr ptr
    ComposeWith		proc :ptr, :BOOL, :ptr ptr
    Enum		proc :BOOL, :ptr ptr
    IsEqual		proc :ptr
    Hash		proc :ptr
    IsRunning		proc :ptr, :ptr, :ptr
    GetTimeOfLastChange proc :ptr, :ptr, :ptr
    Inverse		proc :ptr ptr
    CommonPrefixWith	proc :ptr, :ptr ptr
    RelativePathTo	proc :ptr, :ptr ptr
    GetDisplayName	proc :ptr, :ptr, :ptr
    ParseDisplayName	proc :ptr, :ptr, :LPOLESTR, :ptr, :ptr ptr
    IsSystemMoniker	proc :ptr
   .ends

IMoniker_RemoteBindToObject_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_RemoteBindToObject_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IMoniker_RemoteBindToStorage_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_RemoteBindToStorage_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IROTData_INTERFACE_DEFINED__
define __IROTData_INTERFACE_DEFINED__

DEFINE_IIDX(IROTData, "f29f6bc0-5021-11ce-aa15-00006901293f")

.comdef IROTData : public IUnknown

    GetComparisonData	proc :ptr, :ULONG, :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IEnumSTATSTG_INTERFACE_DEFINED__
define __IEnumSTATSTG_INTERFACE_DEFINED__

LPENUMSTATSTG		typedef ptr IEnumSTATSTG

DEFINE_IIDX(IEnumSTATSTG, "0000000d-0000-0000-C000-000000000046")

.comdef IEnumSTATSTG : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumSTATSTG_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATSTG_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IStorage_INTERFACE_DEFINED__
define __IStorage_INTERFACE_DEFINED__

LPSTORAGE		typedef ptr IStorage

tagRemSNB		struct
ulCntStr		ULONG ?
ulCntChar		ULONG ?
rgString		OLECHAR 1 dup(?)
tagRemSNB		ends
RemSNB			typedef tagRemSNB

wireSNB			typedef ptr RemSNB

SNB			typedef ptr LPOLESTR

DEFINE_IIDX(IStorage, "0000000b-0000-0000-C000-000000000046")

.comdef IStorage : public IUnknown

    CreateStream	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr ptr
    OpenStream		proc :ptr, :ptr, :DWORD, :DWORD, :ptr ptr
    CreateStorage	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr ptr
    OpenStorage		proc :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr ptr
    CopyTo		proc :DWORD, :ptr, :SNB, :ptr
    MoveElementTo	proc :ptr, :ptr, :ptr, :DWORD
    Commit		proc :DWORD
    Revert		proc
    EnumElements	proc :DWORD, :ptr, :DWORD, :ptr ptr
    DestroyElement	proc :ptr
    RenameElement	proc :ptr, :ptr
    SetElementTimes	proc :ptr, :ptr, :ptr, :ptr
    SetClass		proc :REFCLSID
    SetStateBits	proc :DWORD, :DWORD
    Stat		proc :ptr, :DWORD
   .ends

IStorage_RemoteOpenStream_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr, :DWORD, :DWORD, :ptr ptr
IStorage_RemoteOpenStream_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IStorage_RemoteCopyTo_Proxy proto WINAPI :ptr, :DWORD, :ptr, :SNB, :ptr
IStorage_RemoteCopyTo_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IStorage_RemoteEnumElements_Proxy proto WINAPI :ptr, :DWORD, :ULONG, :ptr, :DWORD, :ptr ptr
IStorage_RemoteEnumElements_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IPersistFile_INTERFACE_DEFINED__
define __IPersistFile_INTERFACE_DEFINED__

LPPERSISTFILE		typedef ptr IPersistFile

DEFINE_IIDX(IPersistFile, "0000010b-0000-0000-C000-000000000046")

.comdef IPersistFile : public IPersist

    IsDirty		proc
    Load		proc :LPCOLESTR, :DWORD
    Save		proc :LPCOLESTR, :BOOL
    SaveCompleted	proc :LPCOLESTR
    GetCurFile		proc :ptr
   .ends

endif

ifndef __IPersistStorage_INTERFACE_DEFINED__
define __IPersistStorage_INTERFACE_DEFINED__

LPPERSISTSTORAGE	typedef ptr IPersistStorage

DEFINE_IIDX(IPersistStorage, "0000010a-0000-0000-C000-000000000046")

.comdef IPersistStorage : public IPersist

    IsDirty		proc
    InitNew		proc :ptr
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    SaveCompleted	proc :ptr
    HandsOffStorage	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __ILockBytes_INTERFACE_DEFINED__
define __ILockBytes_INTERFACE_DEFINED__

LPLOCKBYTES		typedef ptr ILockBytes

DEFINE_IIDX(ILockBytes, "0000000a-0000-0000-C000-000000000046")

.comdef ILockBytes : public IUnknown

    ReadAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    WriteAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    Flush		proc
    SetSize		proc :ULARGE_INTEGER
    LockRegion		proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    UnlockRegion	proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    Stat		proc :ptr, :DWORD
   .ends

ILockBytes_RemoteReadAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_RemoteReadAt_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
ILockBytes_RemoteWriteAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_RemoteWriteAt_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumFORMATETC_INTERFACE_DEFINED__
define __IEnumFORMATETC_INTERFACE_DEFINED__

LPENUMFORMATETC		typedef ptr IEnumFORMATETC

tagDVTARGETDEVICE	struct
tdSize			DWORD ?
tdDriverNameOffset	WORD ?
tdDeviceNameOffset	WORD ?
tdPortNameOffset	WORD ?
tdExtDevmodeOffset	WORD ?
tdData			BYTE 1 dup(?)
tagDVTARGETDEVICE	ends
DVTARGETDEVICE		typedef tagDVTARGETDEVICE

LPCLIPFORMAT		typedef ptr CLIPFORMAT

tagFORMATETC		struct
cfFormat		CLIPFORMAT ?
ptd			ptr DVTARGETDEVICE ?
dwAspect		DWORD ?
lindex			LONG ?
tymed			DWORD ?
tagFORMATETC		ends
FORMATETC		typedef tagFORMATETC

LPFORMATETC		typedef ptr tagFORMATETC

DEFINE_IIDX(IEnumFORMATETC, "00000103-0000-0000-C000-000000000046")

.comdef IEnumFORMATETC : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumFORMATETC_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumFORMATETC_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IEnumSTATDATA_INTERFACE_DEFINED__
define __IEnumSTATDATA_INTERFACE_DEFINED__

LPENUMSTATDATA		typedef ptr IEnumSTATDATA

.enum ADVF {
	ADVF_NODATA	= 1,
	ADVF_PRIMEFIRST = 2,
	ADVF_ONLYONCE	= 4,
	ADVF_DATAONSTOP = 64,
	ADVFCACHE_NOHANDLER	= 8,
	ADVFCACHE_FORCEBUILTIN	= 16,
	ADVFCACHE_ONSAVE	= 32
    }

tagSTATDATA		struct
formatetc		FORMATETC <>
advf			DWORD ?
pAdvSink		ptr IAdviseSink ?
dwConnection		DWORD ?
tagSTATDATA		ends
STATDATA		typedef tagSTATDATA
LPSTATDATA		typedef ptr STATDATA

DEFINE_IIDX(IEnumSTATDATA, "00000105-0000-0000-C000-000000000046")

.comdef IEnumSTATDATA : public IUnknown
    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr ptr
   .ends

IEnumSTATDATA_RemoteNext_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATDATA_RemoteNext_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __IRootStorage_INTERFACE_DEFINED__
define __IRootStorage_INTERFACE_DEFINED__

LPROOTSTORAGE		typedef ptr IRootStorage

DEFINE_IIDX(IRootStorage, "00000012-0000-0000-C000-000000000046")

.comdef IRootStorage : public IUnknown

    SwitchToFile	proc :LPOLESTR
   .ends

endif

ifndef __IAdviseSink_INTERFACE_DEFINED__
define __IAdviseSink_INTERFACE_DEFINED__

LPADVISESINK		typedef ptr IAdviseSink

.enum TYMED {
	TYMED_HGLOBAL	= 1,
	TYMED_FILE	= 2,
	TYMED_ISTREAM	= 4,
	TYMED_ISTORAGE	= 8,
	TYMED_GDI	= 16,
	TYMED_MFPICT	= 32,
	TYMED_ENHMF	= 64,
	TYMED_NULL	= 0
    }

tagRemSTGMEDIUM		struct
tymed			DWORD ?
dwHandleType		DWORD ?
pData			ULONG ?
pUnkForRelease		ULONG ?
cbData			ULONG ?
data			byte 1 dup(?)
tagRemSTGMEDIUM		ends
RemSTGMEDIUM		typedef tagRemSTGMEDIUM


tagSTGMEDIUM		struct
tymed			DWORD ?
union u
 hBitmap		HBITMAP ?
 hMetaFilePict		HMETAFILEPICT ?
 hEnhMetaFile		HENHMETAFILE ?
 hGlobal		HGLOBAL ?
 lpszFileName		LPOLESTR ?
 pstm			LPSTREAM ?
 pstg			LPSTORAGE ?
ends
pUnkForRelease		LPUNKNOWN ?
tagSTGMEDIUM		ends
uSTGMEDIUM		typedef tagSTGMEDIUM

GDI_OBJECT		struct
ObjectType		DWORD ?
union u
 hBitmap		wireHBITMAP ?
 hPalette		wireHPALETTE ?
 hGeneric		wireHGLOBAL ?
ends
GDI_OBJECT		ends
LPGDI_OBJECT		typedef ptr GDI_OBJECT

userSTGMEDIUM		struct
struct
 tymed			DWORD ?
 union u
  hHEnhMetaFile		wireHENHMETAFILE ?
  hGdiHandle		ptr GDI_OBJECT ?
  hGlobal		wireHGLOBAL ?
  lpszFileName		LPOLESTR ?
  pstm			UP_BYTE_BLOB ?
  pstg			UP_BYTE_BLOB ?
 ends
ends
pUnkForRelease		LPUNKNOWN ?
userSTGMEDIUM		ends
wireSTGMEDIUM		typedef ptr userSTGMEDIUM
STGMEDIUM		typedef uSTGMEDIUM
wireASYNC_STGMEDIUM	typedef ptr userSTGMEDIUM
ASYNC_STGMEDIUM		typedef STGMEDIUM
LPSTGMEDIUM		typedef ptr STGMEDIUM

userFLAG_STGMEDIUM	struct
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			userSTGMEDIUM <>
userFLAG_STGMEDIUM	ends
wireFLAG_STGMEDIUM	typedef ptr userFLAG_STGMEDIUM

FLAG_STGMEDIUM		struct
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			STGMEDIUM <>
FLAG_STGMEDIUM		ends


DEFINE_IIDX(IAdviseSink, "0000010f-0000-0000-C000-000000000046")

.comdef IAdviseSink : public IUnknown

    OnDataChange	proc :ptr, :ptr
    OnViewChange	proc :DWORD, :LONG
    OnRename		proc :ptr
    OnSave		proc
    OnClose		proc
   .ends

IAdviseSink_RemoteOnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
IAdviseSink_RemoteOnDataChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
IAdviseSink_RemoteOnViewChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnRename_Proxy proto WINAPI :ptr, :ptr
IAdviseSink_RemoteOnRename_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnSave_Proxy proto WINAPI :ptr
IAdviseSink_RemoteOnSave_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IAdviseSink_RemoteOnClose_Proxy proto WINAPI :ptr
IAdviseSink_RemoteOnClose_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __AsyncIAdviseSink_INTERFACE_DEFINED__
define __AsyncIAdviseSink_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIAdviseSink, "00000150-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink : public IUnknown

    Begin_OnDataChange	proc :ptr, :ptr
    Finish_OnDataChange proc
    Begin_OnViewChange	proc :DWORD, :LONG
    Finish_OnViewChange proc
    Begin_OnRename	proc :ptr
    Finish_OnRename	proc
    Begin_OnSave	proc
    Finish_OnSave	proc
    Begin_OnClose	proc
    Finish_OnClose	proc
   .ends

AsyncIAdviseSink_Begin_RemoteOnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
AsyncIAdviseSink_Begin_RemoteOnDataChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnDataChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnDataChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
AsyncIAdviseSink_Begin_RemoteOnViewChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnViewChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnViewChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnRename_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink_Begin_RemoteOnRename_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnRename_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnRename_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_RemoteOnSave_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnSave_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Begin_RemoteOnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_RemoteOnClose_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink_Finish_RemoteOnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_RemoteOnClose_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IAdviseSink2_INTERFACE_DEFINED__
define __IAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(IAdviseSink2, "00000125-0000-0000-C000-000000000046")

.comdef IAdviseSink2 : public IAdviseSink

    OnLinkSrcChange	proc :ptr
   .ends

LPADVISESINK2		typedef ptr IAdviseSink2

IAdviseSink2_RemoteOnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
IAdviseSink2_RemoteOnLinkSrcChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

ifndef __AsyncIAdviseSink2_INTERFACE_DEFINED__
define __AsyncIAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIAdviseSink2, "00000151-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink2 : public AsyncIAdviseSink

    Begin_OnLinkSrcChange proc :ptr
    Finish_OnLinkSrcChange proc
   .ends

AsyncIAdviseSink2_Begin_RemoteOnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink2_Begin_RemoteOnLinkSrcChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
AsyncIAdviseSink2_Finish_RemoteOnLinkSrcChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink2_Finish_RemoteOnLinkSrcChange_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IDataObject_INTERFACE_DEFINED__
define __IDataObject_INTERFACE_DEFINED__

.enum DATADIR {
	DATADIR_GET	= 1,
	DATADIR_SET	= 2
    }

DEFINE_IIDX(IDataObject, "0000010e-0000-0000-C000-000000000046")

.comdef IDataObject : public IUnknown

    GetData		proc :ptr, :ptr
    GetDataHere		proc :ptr, :ptr
    QueryGetData	proc :ptr
    GetCanonicalFormatEtc proc :ptr, :ptr
    SetData		proc :ptr, :ptr, :BOOL
    EnumFormatEtc	proc :DWORD, :ptr ptr
    DAdvise		proc :ptr, :DWORD, :ptr, :ptr
    DUnadvise		proc :DWORD
    EnumDAdvise		proc :ptr ptr
   .ends

LPDATAOBJECT		typedef ptr IDataObject

IDataObject_RemoteGetData_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_RemoteGetData_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IDataObject_RemoteGetDataHere_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_RemoteGetDataHere_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IDataObject_RemoteSetData_Proxy proto WINAPI :ptr, :ptr, :ptr, :BOOL
IDataObject_RemoteSetData_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
define __IDataAdviseHolder_INTERFACE_DEFINED__

DEFINE_IIDX(IDataAdviseHolder, "00000110-0000-0000-C000-000000000046")

.comdef IDataAdviseHolder : public IUnknown

    Advise		proc :ptr, :ptr, :DWORD, :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr ptr
    SendOnDataChange	proc :ptr, :DWORD, :DWORD
   .ends

LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder

endif

ifndef __IMessageFilter_INTERFACE_DEFINED__
define __IMessageFilter_INTERFACE_DEFINED__

.enum CALLTYPE {
	CALLTYPE_TOPLEVEL	= 1,
	CALLTYPE_NESTED = 2,
	CALLTYPE_ASYNC	= 3,
	CALLTYPE_TOPLEVEL_CALLPENDING	= 4,
	CALLTYPE_ASYNC_CALLPENDING	= 5
    }

.enum SERVERCALL {
	SERVERCALL_ISHANDLED	= 0,
	SERVERCALL_REJECTED	= 1,
	SERVERCALL_RETRYLATER	= 2
    }

.enum PENDINGTYPE {
	PENDINGTYPE_TOPLEVEL	= 1,
	PENDINGTYPE_NESTED	= 2
    }

.enum PENDINGMSG {
	PENDINGMSG_CANCELCALL	= 0,
	PENDINGMSG_WAITNOPROCESS	= 1,
	PENDINGMSG_WAITDEFPROCESS	= 2
    }

tagINTERFACEINFO	struct
pUnk			LPUNKNOWN ?
iid			IID <>
wMethod			WORD ?
tagINTERFACEINFO	ends
INTERFACEINFO		typedef tagINTERFACEINFO
LPINTERFACEINFO		typedef ptr tagINTERFACEINFO

DEFINE_IIDX(IMessageFilter, "00000016-0000-0000-C000-000000000046")

.comdef IMessageFilter : public IUnknown

    HandleInComingCall	proc :DWORD, :HTASK, :DWORD, :LPINTERFACEINFO
    RetryRejectedCall	proc :HTASK, :DWORD, :DWORD
    MessagePending	proc :HTASK, :DWORD, :DWORD
   .ends

LPMESSAGEFILTER		typedef ptr IMessageFilter

endif

externdef FMTID_SummaryInformation:FMTID
externdef FMTID_DocSummaryInformation:FMTID
externdef FMTID_UserDefinedProperties:FMTID
externdef FMTID_DiscardableInformation:FMTID
externdef FMTID_ImageSummaryInformation:FMTID
externdef FMTID_AudioSummaryInformation:FMTID
externdef FMTID_VideoSummaryInformation:FMTID
externdef FMTID_MediaFileSummaryInformation:FMTID

ifndef __IClassActivator_INTERFACE_DEFINED__
define __IClassActivator_INTERFACE_DEFINED__

DEFINE_IIDX(IClassActivator, "00000140-0000-0000-C000-000000000046")

.comdef IClassActivator : public IUnknown

    GetClassObject	proc :REFCLSID, :DWORD, :LCID, :REFIID, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __IFillLockBytes_INTERFACE_DEFINED__
define __IFillLockBytes_INTERFACE_DEFINED__

DEFINE_IIDX(IFillLockBytes, "99caf010-415e-11cf-8814-00aa00b569f5")

.comdef IFillLockBytes : public IUnknown

    FillAppend		proc :ptr, :ULONG, :ptr
    FillAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    SetFillSize		proc :ULARGE_INTEGER
    Terminate		proc :BOOL
   .ends

IFillLockBytes_RemoteFillAppend_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
IFillLockBytes_RemoteFillAppend_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr
IFillLockBytes_RemoteFillAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
IFillLockBytes_RemoteFillAt_Stub proto WINAPI :ptr, :ptr, :PRPC_MESSAGE, :ptr

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IProgressNotify_INTERFACE_DEFINED__
define __IProgressNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IProgressNotify, "a9d758a0-4617-11cf-95fc-00aa00680db4")

.comdef IProgressNotify : public IUnknown

    OnProgress		proc :DWORD, :DWORD, :BOOL, :BOOL
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __ILayoutStorage_INTERFACE_DEFINED__
define __ILayoutStorage_INTERFACE_DEFINED__

tagStorageLayout	struct
LayoutType		DWORD ?
pwcsElementName		ptr OLECHAR ?
cOffset			LARGE_INTEGER <>
cBytes			LARGE_INTEGER <>
tagStorageLayout	ends
StorageLayout		typedef tagStorageLayout

DEFINE_IIDX(ILayoutStorage, "0e6d4d90-6738-11cf-9608-00aa00680db4")

.comdef ILayoutStorage : public IUnknown

    LayoutScript	proc :ptr, :DWORD, :DWORD
    BeginMonitor	proc
    EndMonitor		proc
    ReLayoutDocfile	proc :ptr
    ReLayoutDocfileOnILockBytes proc :ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IBlockingLock_INTERFACE_DEFINED__
define __IBlockingLock_INTERFACE_DEFINED__

DEFINE_IIDX(IBlockingLock, "30f3d47a-6447-11d1-8e3c-00c04fb9386d")

.comdef IBlockingLock : public IUnknown

    _Lock		proc :DWORD
    Unlock		proc
   .ends

endif

ifndef __ITimeAndNoticeControl_INTERFACE_DEFINED__
define __ITimeAndNoticeControl_INTERFACE_DEFINED__

DEFINE_IIDX(ITimeAndNoticeControl, "bc0bf6ae-8878-11d1-83e9-00c04fc2c6d4")

.comdef ITimeAndNoticeControl : public IUnknown

    SuppressChanges	proc :DWORD, :DWORD
   .ends

endif

ifndef __IOplockStorage_INTERFACE_DEFINED__
define __IOplockStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IOplockStorage, "8d19c834-8879-11d1-83e9-00c04fc2c6d4")

.comdef IOplockStorage : public IUnknown

    CreateStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr ptr
    OpenStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr ptr
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __IDirectWriterLock_INTERFACE_DEFINED__
define __IDirectWriterLock_INTERFACE_DEFINED__

DEFINE_IIDX(IDirectWriterLock, "0e6d4d92-6738-11cf-9608-00aa00680db4")

.comdef IDirectWriterLock : public IUnknown

    WaitForWriteAccess	proc :DWORD
    ReleaseWriteAccess	proc
    HaveWriteAccess	proc
   .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)

ifndef __IUrlMon_INTERFACE_DEFINED__
define __IUrlMon_INTERFACE_DEFINED__

DEFINE_IIDX(IUrlMon, "00000026-0000-0000-C000-000000000046")

.comdef IUrlMon : public IUnknown

    AsyncGetClassBits	proc :REFCLSID, :LPCWSTR, :LPCWSTR, :DWORD, :DWORD, :LPCWSTR, :ptr, :DWORD, :REFIID, :DWORD
   .ends

endif

ifndef __IForegroundTransfer_INTERFACE_DEFINED__
define __IForegroundTransfer_INTERFACE_DEFINED__

DEFINE_IIDX(IForegroundTransfer, "00000145-0000-0000-C000-000000000046")

.comdef IForegroundTransfer : public IUnknown

    AllowForegroundTransfer proc :ptr
   .ends

endif

ifndef __IThumbnailExtractor_INTERFACE_DEFINED__
define __IThumbnailExtractor_INTERFACE_DEFINED__

DEFINE_IIDX(IThumbnailExtractor, "969dc708-5c76-11d1-8d86-0000f804b057")

.comdef IThumbnailExtractor : public IUnknown

    ExtractThumbnail	proc :ptr, :ULONG, :ULONG, :ptr, :ptr, :ptr
    OnFileUpdated	proc :ptr
   .ends

endif

ifndef __IDummyHICONIncluder_INTERFACE_DEFINED__
define __IDummyHICONIncluder_INTERFACE_DEFINED__

DEFINE_IIDX(IDummyHICONIncluder, "947990de-cc28-11d2-a0f7-00805f858fb1")

.comdef IDummyHICONIncluder : public IUnknown

    Dummy		proc :HICON, :HDC
   .ends

endif

.enum ApplicationType {
	ServerApplication	= 0,
	LibraryApplication	= ( ServerApplication + 1 )
    }

.enum ShutdownType {
	IdleShutdown	= 0,
	ForcedShutdown	= ( IdleShutdown + 1 )
    }

ifndef __IProcessLock_INTERFACE_DEFINED__
define __IProcessLock_INTERFACE_DEFINED__

DEFINE_IIDX(IProcessLock, "000001d5-0000-0000-C000-000000000046")

.comdef IProcessLock : public IUnknown

    AddRefOnProcess	proc
    ReleaseRefOnProcess proc
   .ends

endif

ifndef __ISurrogateService_INTERFACE_DEFINED__
define __ISurrogateService_INTERFACE_DEFINED__

DEFINE_IIDX(ISurrogateService, "000001d4-0000-0000-C000-000000000046")

.comdef ISurrogateService : public IUnknown

    Init		proc :REFGUID, :ptr, :ptr
    ApplicationLaunch	proc :REFGUID, :ApplicationType
    ApplicationFree	proc :REFGUID
    CatalogRefresh	proc :ULONG
    ProcessShutdown	proc :ShutdownType
   .ends

endif

if  (_WIN32_WINNT ge 0x0501 )

ifndef __IInitializeSpy_INTERFACE_DEFINED__
define __IInitializeSpy_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeSpy, "00000034-0000-0000-C000-000000000046")

.comdef IInitializeSpy : public IUnknown

    PreInitialize	proc :DWORD, :DWORD
    PostInitialize	proc :HRESULT, :DWORD, :DWORD
    PreUninitialize	proc :DWORD
    PostUninitialize	proc :DWORD
   .ends

LPINITIALIZESPY		typedef ptr IInitializeSpy

endif

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

ifndef __IApartmentShutdown_INTERFACE_DEFINED__
define __IApartmentShutdown_INTERFACE_DEFINED__

DEFINE_IIDX(IApartmentShutdown, "A2F05A09-27A2-42B5-BC0E-AC163EF49D9B")

.comdef IApartmentShutdown : public IUnknown

    OnUninitialize	proc :UINT64
   .ends

endif

endif

ASYNC_STGMEDIUM_UserSize proto WINAPI :ptr, :dword, :ptr
ASYNC_STGMEDIUM_UserMarshal proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserFree proto WINAPI :ptr, :ptr

CLIPFORMAT_UserSize proto WINAPI :ptr, :dword, :ptr
CLIPFORMAT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserFree proto WINAPI :ptr, :ptr

FLAG_STGMEDIUM_UserSize proto WINAPI :ptr, :dword, :ptr
FLAG_STGMEDIUM_UserMarshal proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserFree proto WINAPI :ptr, :ptr

HBITMAP_UserSize proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree proto WINAPI :ptr, :ptr

HDC_UserSize proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree proto WINAPI :ptr, :ptr

HICON_UserSize proto WINAPI :ptr, :dword, :ptr
HICON_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HICON_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HICON_UserFree proto WINAPI :ptr, :ptr

SNB_UserSize proto WINAPI :ptr, :dword, :ptr
SNB_UserMarshal proto WINAPI :ptr, :ptr, :ptr
SNB_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
SNB_UserFree proto WINAPI :ptr, :ptr

STGMEDIUM_UserSize proto WINAPI :ptr, :dword, :ptr
STGMEDIUM_UserMarshal proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserFree proto WINAPI :ptr, :ptr

ASYNC_STGMEDIUM_UserSize64 proto WINAPI :ptr, :dword, :ptr
ASYNC_STGMEDIUM_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
ASYNC_STGMEDIUM_UserFree64 proto WINAPI :ptr, :ptr

CLIPFORMAT_UserSize64 proto WINAPI :ptr, :dword, :ptr
CLIPFORMAT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserFree64 proto WINAPI :ptr, :ptr

FLAG_STGMEDIUM_UserSize64 proto WINAPI :ptr, :dword, :ptr
FLAG_STGMEDIUM_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
FLAG_STGMEDIUM_UserFree64 proto WINAPI :ptr, :ptr

HBITMAP_UserSize64 proto WINAPI :ptr, :dword, :ptr
HBITMAP_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HBITMAP_UserFree64 proto WINAPI :ptr, :ptr

HDC_UserSize64 proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree64 proto WINAPI :ptr, :ptr

HICON_UserSize64 proto WINAPI :ptr, :dword, :ptr
HICON_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HICON_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HICON_UserFree64 proto WINAPI :ptr, :ptr

SNB_UserSize64 proto WINAPI :ptr, :dword, :ptr
SNB_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
SNB_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
SNB_UserFree64 proto WINAPI :ptr, :ptr

STGMEDIUM_UserSize64 proto WINAPI :ptr, :dword, :ptr
STGMEDIUM_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
STGMEDIUM_UserFree64 proto WINAPI :ptr, :ptr

IEnumUnknown_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumUnknown_Next_Stub proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumString_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumString_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr
ISequentialStream_Read_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_Read_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_Write_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
ISequentialStream_Write_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr
IStream_Seek_Proxy proto WINAPI :ptr, :LARGE_INTEGER, :DWORD, :ptr
IStream_Seek_Stub proto WINAPI :ptr, :LARGE_INTEGER, :DWORD, :ptr
IStream_CopyTo_Proxy proto WINAPI :ptr, :ptr, :ULARGE_INTEGER, :ptr, :ptr
IStream_CopyTo_Stub proto WINAPI :ptr, :ptr, :ULARGE_INTEGER, :ptr, :ptr

IBindCtx_SetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_SetBindOptions_Stub proto WINAPI :ptr, :ptr
IBindCtx_GetBindOptions_Proxy proto WINAPI :ptr, :ptr
IBindCtx_GetBindOptions_Stub proto WINAPI :ptr, :ptr

IEnumMoniker_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr
IEnumMoniker_Next_Stub proto WINAPI :ptr, :ULONG, :ptr ptr, :ptr

IRunnableObject_IsRunning_Proxy proto WINAPI :ptr
IRunnableObject_IsRunning_Stub proto WINAPI :ptr

IMoniker_BindToObject_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_BindToObject_Stub proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_BindToStorage_Proxy proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr
IMoniker_BindToStorage_Stub proto WINAPI :ptr, :ptr, :ptr, :REFIID, :ptr ptr

IEnumSTATSTG_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATSTG_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr

IStorage_OpenStream_Proxy proto WINAPI :ptr, :ptr, :ptr, :DWORD, :DWORD, :ptr ptr
IStorage_OpenStream_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr, :DWORD, :DWORD, :ptr ptr
IStorage_CopyTo_Proxy proto WINAPI :ptr, :DWORD, :ptr, :SNB, :ptr
IStorage_CopyTo_Stub proto WINAPI :ptr, :DWORD, :ptr, :SNB, :ptr
IStorage_EnumElements_Proxy proto WINAPI :ptr, :DWORD, :ptr, :DWORD, :ptr ptr
IStorage_EnumElements_Stub proto WINAPI :ptr, :DWORD, :ULONG, :ptr, :DWORD, :ptr ptr

ILockBytes_ReadAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_ReadAt_Stub proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_WriteAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
ILockBytes_WriteAt_Stub proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr

IEnumFORMATETC_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumFORMATETC_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATDATA_Next_Proxy proto WINAPI :ptr, :ULONG, :ptr, :ptr
IEnumSTATDATA_Next_Stub proto WINAPI :ptr, :ULONG, :ptr, :ptr

IAdviseSink_OnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
IAdviseSink_OnDataChange_Stub proto WINAPI :ptr, :ptr, :ptr
IAdviseSink_OnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
IAdviseSink_OnViewChange_Stub proto WINAPI :ptr, :DWORD, :LONG
IAdviseSink_OnRename_Proxy proto WINAPI :ptr, :ptr
IAdviseSink_OnRename_Stub proto WINAPI :ptr, :ptr
IAdviseSink_OnSave_Proxy proto WINAPI :ptr
IAdviseSink_OnSave_Stub proto WINAPI :ptr
IAdviseSink_OnClose_Proxy proto WINAPI :ptr
IAdviseSink_OnClose_Stub proto WINAPI :ptr

AsyncIAdviseSink_Begin_OnDataChange_Proxy proto WINAPI :ptr, :ptr, :ptr
AsyncIAdviseSink_Begin_OnDataChange_Stub proto WINAPI :ptr, :ptr, :ptr
AsyncIAdviseSink_Finish_OnDataChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnDataChange_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnViewChange_Proxy proto WINAPI :ptr, :DWORD, :LONG
AsyncIAdviseSink_Begin_OnViewChange_Stub proto WINAPI :ptr, :DWORD, :LONG
AsyncIAdviseSink_Finish_OnViewChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnViewChange_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnRename_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink_Begin_OnRename_Stub proto WINAPI :ptr, :ptr
AsyncIAdviseSink_Finish_OnRename_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnRename_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnSave_Stub proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnSave_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnSave_Stub proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Begin_OnClose_Stub proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnClose_Proxy proto WINAPI :ptr
AsyncIAdviseSink_Finish_OnClose_Stub proto WINAPI :ptr

IAdviseSink2_OnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
IAdviseSink2_OnLinkSrcChange_Stub proto WINAPI :ptr, :ptr

AsyncIAdviseSink2_Begin_OnLinkSrcChange_Proxy proto WINAPI :ptr, :ptr
AsyncIAdviseSink2_Begin_OnLinkSrcChange_Stub proto WINAPI :ptr, :ptr
AsyncIAdviseSink2_Finish_OnLinkSrcChange_Proxy proto WINAPI :ptr
AsyncIAdviseSink2_Finish_OnLinkSrcChange_Stub proto WINAPI :ptr

IDataObject_GetData_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_GetData_Stub proto WINAPI :ptr, :ptr, :ptr
IDataObject_GetDataHere_Proxy proto WINAPI :ptr, :ptr, :ptr
IDataObject_GetDataHere_Stub proto WINAPI :ptr, :ptr, :ptr
IDataObject_SetData_Proxy proto WINAPI :ptr, :ptr, :ptr, :BOOL
IDataObject_SetData_Stub proto WINAPI :ptr, :ptr, :ptr, :BOOL

IFillLockBytes_FillAppend_Proxy proto WINAPI :ptr, :ptr, :ULONG, :ptr
IFillLockBytes_FillAppend_Stub proto WINAPI :ptr, :ptr, :ULONG, :ptr
IFillLockBytes_FillAt_Proxy proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr
IFillLockBytes_FillAt_Stub proto WINAPI :ptr, :ULARGE_INTEGER, :ptr, :ULONG, :ptr

endif

endif
