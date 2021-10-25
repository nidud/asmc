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

;include unknwn.inc

include winapifamily.inc
if(NTDDI_VERSION GE NTDDI_VISTA AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0600
endif
if(NTDDI_VERSION GE NTDDI_WS03 AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0502
endif
if(NTDDI_VERSION GE NTDDI_WINXP AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0501
endif
if(NTDDI_VERSION GE NTDDI_WIN2K AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0500
endif

include winapifamily.inc
if(NTDDI_VERSION GE NTDDI_VISTA AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0600
endif
if(NTDDI_VERSION GE NTDDI_WS03 AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0502
endif
if(NTDDI_VERSION GE NTDDI_WINXP AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0501
endif
if(NTDDI_VERSION GE NTDDI_WIN2K AND NOT defined(_WIN32_WINNT))
define _WIN32_WINNT 0x0500
endif

ifndef _OBJIDLBASE_

ifndef DEFINE_IIDX
DEFINE_IIDX macro name, x
    DEFINE_GUID(IID_&name&, \
	@CatStr(<0x>, @SubStr(x, 2,8)), \
	@CatStr(<0x>, @SubStr(x,11,4)), \
	@CatStr(<0x>, @SubStr(x,16,4)), \
	@CatStr(<0x>, @SubStr(x,21,2)), \
	@CatStr(<0x>, @SubStr(x,23,2)), \
	@CatStr(<0x>, @SubStr(x,26,2)), \
	@CatStr(<0x>, @SubStr(x,28,2)), \
	@CatStr(<0x>, @SubStr(x,30,2)), \
	@CatStr(<0x>, @SubStr(x,32,2)), \
	@CatStr(<0x>, @SubStr(x,34,2)), \
	@CatStr(<0x>, @SubStr(x,36,2)))
	exitm<>
	endm
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

LPCOAUTHINFO		typedef ptr COAUTHINFO

COSERVERINFO		STRUC
dwReserved1		dd ?
pwszName		LPWSTR ?
pAuthInfo		LPCOAUTHINFO ?
dwReserved2		dd ?
COSERVERINFO		ENDS
LPCOSERVERINFO		typedef ptr COSERVERINFO

ifndef __IMarshal_INTERFACE_DEFINED__
define __IMarshal_INTERFACE_DEFINED__

DEFINE_IIDX(IMarshal, "00000003-0000-0000-C000-000000000046")

.comdef IMarshal : public IUnknown

    GetUnmarshalClass	proc :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
    GetMarshalSizeMax	proc :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
    MarshalInterface	proc :ptr, :REFIID, :ptr, :DWORD, :ptr, :DWORD
    UnmarshalInterface	proc :ptr, :REFIID, :ptr
    ReleaseMarshalData proc :ptr
    DisconnectObject	proc :DWORD
    .ends
    LPMARSHAL		typedef ptr IMarshal

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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IActivationFilter_INTERFACE_DEFINED__
define __IActivationFilter_INTERFACE_DEFINED__

.enum ACTIVATIONTYPE {
    ACTIVATIONTYPE_UNCATEGORIZED = 0,
    ACTIVATIONTYPE_FROM_MONIKER = 0x1,
    ACTIVATIONTYPE_FROM_DATA	= 0x2,
    ACTIVATIONTYPE_FROM_STORAGE = 0x4,
    ACTIVATIONTYPE_FROM_STREAM	= 0x8,
    ACTIVATIONTYPE_FROM_FILE	= 0x10
    }

DEFINE_IIDX(IActivationFilter, "00000017-0000-0000-C000-000000000046")

.comdef IActivationFilter : public IUnknown

    HandleActivation	proc :DWORD, :REFCLSID, :ptr
    .ends

endif

ifndef __IMarshal2_INTERFACE_DEFINED__
define __IMarshal2_INTERFACE_DEFINED__

DEFINE_IIDX(IMarshal2, "000001cf-0000-0000-C000-000000000046")

.comdef IMarshal2 : public IMarshal
    .ends

LPMARSHAL2		typedef ptr IMarshal2

endif

ifndef __IMalloc_INTERFACE_DEFINED__
define __IMalloc_INTERFACE_DEFINED__

DEFINE_IIDX(IMalloc, "00000002-0000-0000-C000-000000000046")

.comdef IMalloc : public IUnknown

    Alloc		proc :DWORD
    Realloc		proc :ptr ,:DWORD
    Free		proc :ptr
    GetSize		proc :ptr
    DidAlloc		proc :ptr
    HeapMinimize	proc
    .ends

LPMALLOC		typedef ptr IMalloc

endif

ifndef __IStdMarshalInfo_INTERFACE_DEFINED__
define __IStdMarshalInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IStdMarshalInfo, "00000018-0000-0000-C000-000000000046")

.comdef IStdMarshalInfo : public IUnknown

    GetClassForHandler	proc :DWORD, :ptr, :ptr
    .ends

LPSTDMARSHALINFO	typedef ptr IStdMarshalInfo

endif

ifndef __IExternalConnection_INTERFACE_DEFINED__
define __IExternalConnection_INTERFACE_DEFINED__

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

LPEXTERNALCONNECTION	typedef ptr IExternalConnection

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MULTI_QI		STRUC
pIID			LPIID ?
pItf			LPUNKNOWN ?
hr			HRESULT ?
MULTI_QI		ENDS

ifndef __IMultiQI_INTERFACE_DEFINED__
define __IMultiQI_INTERFACE_DEFINED__

DEFINE_IIDX(IMultiQI, "00000020-0000-0000-C000-000000000046")

.comdef IMultiQI : public IUnknown

    QueryMultipleInterfaces proc :ULONG, :ptr
    .ends

LPMULTIQI		typedef ptr IMultiQI

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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IInternalUnknown_INTERFACE_DEFINED__
define __IInternalUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(IInternalUnknown, "00000021-0000-0000-C000-000000000046")

.comdef IInternalUnknown : public IUnknown

    QueryInternalInterface proc :REFIID, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IEnumUnknown_INTERFACE_DEFINED__
define __IEnumUnknown_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumUnknown, "00000100-0000-0000-C000-000000000046")

.comdef IEnumUnknown : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

LPENUMUNKNOWN		typedef ptr IEnumUnknown

endif

ifndef __IEnumString_INTERFACE_DEFINED__
define __IEnumString_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumString, "00000101-0000-0000-C000-000000000046")

.comdef IEnumString : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

LPENUMSTRING		typedef ptr IEnumString

endif

ifndef __ISequentialStream_INTERFACE_DEFINED__
define __ISequentialStream_INTERFACE_DEFINED__

DEFINE_IIDX(ISequentialStream, "0c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ISequentialStream : public IUnknown

    Read		proc :ptr, :ULONG, :ptr
    Write		proc :ptr, :ULONG, :ptr
    .ends

endif

ifndef __IStream_INTERFACE_DEFINED__
define __IStream_INTERFACE_DEFINED__

STATSTG			STRUC
pwcsName		LPOLESTR ?
type			dd ?
cbSize			ULARGE_INTEGER <>
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
grfMode			dd ?
grfLocksSupported	dd ?
clsid			CLSID <>
grfStateBits		dd ?
reserved		dd ?
STATSTG			ENDS

.enum STGTY {
    STGTY_STORAGE	= 1,
    STGTY_STREAM	= 2,
    STGTY_LOCKBYTES	= 3,
    STGTY_PROPERTY	= 4
    }

.enum STREAM_SEEK {
    STREAM_SEEK_SET	= 0,
    STREAM_SEEK_CUR	= 1,
    STREAM_SEEK_END	= 2
    }

.enum LOCKTYPE {
    LOCK_WRITE		= 1,
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
    Clone		proc :ptr
    .ends

LPSTREAM		typedef ptr IStream

endif


ifndef __IRpcChannelBuffer_INTERFACE_DEFINED__
define __IRpcChannelBuffer_INTERFACE_DEFINED__

RPCOLEDATAREP		typedef ULONG

RPCOLEMESSAGE		STRUC
reserved1		PVOID ?
dataRepresentation	RPCOLEDATAREP ?
Buffer			PVOID ?
cbBuffer		ULONG ?
iMethod			ULONG ?
reserved2		PVOID 5 dup(?)
rpcFlags		ULONG ?
RPCOLEMESSAGE		ENDS

PRPCOLEMESSAGE		typedef ptr RPCOLEMESSAGE

DEFINE_IIDX(IRpcChannelBuffer, "D5F56B60-593B-101A-B569-08002B2DBF7A")

.comdef IRpcChannelBuffer : public IUnknown

    GetBuffer		proc :ptr, :REFIID
    SendReceive		proc :ptr, :ptr
    FreeBuffer		proc :ptr
    GetDestCtx		proc :ptr, :ptr
    IsConnected		proc
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

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
    GetDestCtxEx	proc :ptr, :ptr, :ptr
    .ends

endif


ifndef __IRpcChannelBuffer3_INTERFACE_DEFINED__
define __IRpcChannelBuffer3_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcChannelBuffer3, "25B15600-0115-11d0-BF0D-00AA00B8DFD2")

.comdef IRpcChannelBuffer3 : public IRpcChannelBuffer2

    Send		proc :ptr, :ptr
    Receive		proc :ptr, :ULONG, :ptr
    Cancel		proc :ptr
    GetCallContext	proc :ptr, :REFIID, :ptr
    GetDestCtxEx	proc :ptr, :ptr, :ptr
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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IRpcStubBuffer_INTERFACE_DEFINED__
define __IRpcStubBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcStubBuffer, "D5F56AFC-593B-101A-B569-08002B2DBF7A")

.comdef IRpcStubBuffer : public IUnknown

    Connect		proc :ptr
    Disconnect		proc
    _Invoke		proc :ptr, :ptr
    IsIIDSupported	proc :REFIID
    CountRefs		proc
    DebugServerQueryInterface proc :ptr
    DebugServerRelease	proc :ptr
    .ends

endif


ifndef __IPSFactoryBuffer_INTERFACE_DEFINED__
define __IPSFactoryBuffer_INTERFACE_DEFINED__

DEFINE_IIDX(IPSFactoryBuffer, "D5F569D0-593B-101A-B569-08002B2DBF7A")

.comdef IPSFactoryBuffer : public IUnknown

    CreateProxy		proc :ptr, :REFIID, :ptr, :ptr
    CreateStub		proc :REFIID, :ptr, :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

SChannelHookCallInfo	STRUC
iid			IID <>
cbSize			dd ?
uCausality		GUID <>
dwServerPid		dd ?
iMethod			dd ?
pObject			PVOID ?
SChannelHookCallInfo	ENDS


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

if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IClientSecurity_INTERFACE_DEFINED__
define __IClientSecurity_INTERFACE_DEFINED__

SOLE_AUTHENTICATION_SERVICE STRUC
dwAuthnSvc		dd ?
dwAuthzSvc		dd ?
pPrincipalName		LPOLESTR ?
hr			HRESULT ?
SOLE_AUTHENTICATION_SERVICE ENDS

PSOLE_AUTHENTICATION_SERVICE typedef ptr SOLE_AUTHENTICATION_SERVICE

.enum EOLE_AUTHENTICATION_CAPABILITIES {
    EOAC_NONE		= 0,
    EOAC_MUTUAL_AUTH	= 0x1,
    EOAC_STATIC_CLOAKING = 0x20,
    EOAC_DYNAMIC_CLOAKING = 0x40,
    EOAC_ANY_AUTHORITY	= 0x80,
    EOAC_MAKE_FULLSIC	= 0x100,
    EOAC_DEFAULT	= 0x800,
    EOAC_SECURE_REFS	= 0x2,
    EOAC_ACCESS_CONTROL = 0x4,
    EOAC_APPID		= 0x8,
    EOAC_DYNAMIC	= 0x10,
    EOAC_REQUIRE_FULLSIC = 0x200,
    EOAC_AUTO_IMPERSONATE = 0x400,
    EOAC_NO_CUSTOM_MARSHAL = 0x2000,
    EOAC_DISABLE_AAA	= 0x1000
    }

COLE_DEFAULT_PRINCIPAL	equ ( -1 )
COLE_DEFAULT_AUTHINFO	equ ( -1 )

SOLE_AUTHENTICATION_INFO STRUC
dwAuthnSvc		dd ?
dwAuthzSvc		dd ?
pAuthInfo		PVOID ?
SOLE_AUTHENTICATION_INFO ENDS

PSOLE_AUTHENTICATION_INFO typedef ptr SOLE_AUTHENTICATION_INFO

SOLE_AUTHENTICATION_LIST STRUC
cAuthInfo		dd ?
aAuthInfo		PSOLE_AUTHENTICATION_INFO ?
SOLE_AUTHENTICATION_LIST ENDS

PSOLE_AUTHENTICATION_LIST typedef ptr SOLE_AUTHENTICATION_LIST

DEFINE_IIDX(IClientSecurity, "0000013D-0000-0000-C000-000000000046")

.comdef IClientSecurity : public IUnknown

    QueryBlanket	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    SetBlanket		proc :ptr, :DWORD, :DWORD, :ptr, :DWORD, :DWORD, :ptr, :DWORD
    CopyProxy		proc :ptr, :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IServerSecurity_INTERFACE_DEFINED__
define __IServerSecurity_INTERFACE_DEFINED__

DEFINE_IIDX(IServerSecurity, "0000013E-0000-0000-C000-000000000046")

.comdef IServerSecurity : public IUnknown

    QueryBlanket	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    ImpersonateClient	proc
    RevertToSelf	proc
    IsImpersonating	proc
    .ends

endif

.enum RPCOPT_PROPERTIES {
    COMBND_RPCTIMEOUT	= 0x1,
    COMBND_SERVER_LOCALITY = 0x2,
    COMBND_RESERVED1	= 0x4,
    COMBND_RESERVED2	= 0x5
    }

.enum RPCOPT_SERVER_LOCALITY_VALUES {
    SERVER_LOCALITY_PROCESS_LOCAL = 0,
    SERVER_LOCALITY_MACHINE_LOCAL = 1,
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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum GLOBALOPT_PROPERTIES {
    COMGLB_EXCEPTION_HANDLING	= 1,
    COMGLB_APPID		= 2,
    COMGLB_RPC_THREADPOOL_SETTING = 3,
    COMGLB_RO_SETTINGS		= 4,
    COMGLB_UNMARSHALING_POLICY	= 5
    }

.enum GLOBALOPT_EH_VALUES {
    COMGLB_EXCEPTION_HANDLE	= 0,
    COMGLB_EXCEPTION_DONOT_HANDLE_FATAL = 1,
    COMGLB_EXCEPTION_DONOT_HANDLE	= COMGLB_EXCEPTION_DONOT_HANDLE_FATAL,
    COMGLB_EXCEPTION_DONOT_HANDLE_ANY	= 2
    }

.enum GLOBALOPT_RPCTP_VALUES {
    COMGLB_RPC_THREADPOOL_SETTING_DEFAULT_POOL	= 0,
    COMGLB_RPC_THREADPOOL_SETTING_PRIVATE_POOL	= 1
    }

.enum GLOBALOPT_RO_FLAGS {
    COMGLB_STA_MODALLOOP_REMOVE_TOUCH_MESSAGES	= 0x1,
    COMGLB_STA_MODALLOOP_SHARED_QUEUE_REMOVE_INPUT_MESSAGES	= 0x2,
    COMGLB_STA_MODALLOOP_SHARED_QUEUE_DONOT_REMOVE_INPUT_MESSAGES = 0x4,
    COMGLB_FAST_RUNDOWN = 0x8,
    COMGLB_RESERVED1	= 0x10,
    COMGLB_RESERVED2	= 0x20,
    COMGLB_RESERVED3	= 0x40,
    COMGLB_STA_MODALLOOP_SHARED_QUEUE_REORDER_POINTER_MESSAGES	= 0x80,
    COMGLB_RESERVED4	= 0x100,
    COMGLB_RESERVED5	= 0x200
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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __ISurrogate_INTERFACE_DEFINED__
define __ISurrogate_INTERFACE_DEFINED__

DEFINE_IIDX(ISurrogate, "00000022-0000-0000-C000-000000000046")

.comdef ISurrogate : public IUnknown

    LoadDllServer	proc :REFCLSID
    FreeSurrogate	proc
    .ends

LPSURROGATE		typedef ptr ISurrogate

endif

ifndef __IGlobalInterfaceTable_INTERFACE_DEFINED__
define __IGlobalInterfaceTable_INTERFACE_DEFINED__

DEFINE_IIDX(IGlobalInterfaceTable, "00000146-0000-0000-C000-000000000046")

.comdef IGlobalInterfaceTable : public IUnknown

    RegisterInterfaceInGlobal proc :ptr, :REFIID, :ptr
    RevokeInterfaceFromGlobal proc :DWORD
    GetInterfaceFromGlobal proc :DWORD, :REFIID, :ptr
    .ends

LPGLOBALINTERFACETABLE	typedef ptr IGlobalInterfaceTable

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

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
    WaitMultiple	proc :DWORD, :DWORD, :ptr
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

DEFINE_IIDX(ICancelMethodCalls, "00000029-0000-0000-C000-000000000046")

.comdef ICancelMethodCalls : public IUnknown

    Cancel		proc :ULONG
    TestCancel		proc
    .ends

LPCANCELMETHODCALLS	typedef ptr ICancelMethodCalls

endif

ifndef __IAsyncManager_INTERFACE_DEFINED__
define __IAsyncManager_INTERFACE_DEFINED__

.enum DCOM_CALL_STATE {
    DCOM_NONE		= 0,
    DCOM_CALL_COMPLETE	= 0x1,
    DCOM_CALL_CANCELED	= 0x2
    }

DEFINE_IIDX(IAsyncManager, "0000002A-0000-0000-C000-000000000046")

.comdef IAsyncManager : public IUnknown

    CompleteCall	proc :HRESULT
    GetCallContext	proc :REFIID, :ptr
    GetState		proc :ptr
    .ends

endif


ifndef __ICallFactory_INTERFACE_DEFINED__
define __ICallFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ICallFactory, "1c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ICallFactory : public IUnknown

    CreateCall		proc :REFIID, :ptr, :REFIID, :ptr
    .ends

endif

ifndef __IRpcHelper_INTERFACE_DEFINED__
define __IRpcHelper_INTERFACE_DEFINED__

DEFINE_IIDX(IRpcHelper, "00000149-0000-0000-C000-000000000046")

.comdef IRpcHelper : public IUnknown

    GetDCOMProtocolVersion proc :ptr
    GetIIDFromOBJREF	proc :ptr, :ptr
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

    WaitMultiple	proc :DWORD, :ptr
    AddSynchronize	proc :ptr
    .ends

endif


ifndef __IAddrTrackingControl_INTERFACE_DEFINED__
define __IAddrTrackingControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAddrTrackingControl, "00000147-0000-0000-C000-000000000046")

.comdef IAddrTrackingControl : public IUnknown

    EnableCOMDynamicAddrTracking proc
    DisableCOMDynamicAddrTracking proc
    .ends

LPADDRTRACKINGCONTROL	typedef ptr IAddrTrackingControl

endif


ifndef __IAddrExclusionControl_INTERFACE_DEFINED__
define __IAddrExclusionControl_INTERFACE_DEFINED__

DEFINE_IIDX(IAddrExclusionControl, "00000148-0000-0000-C000-000000000046")

.comdef IAddrExclusionControl : public IUnknown

    GetCurrentAddrExclusionList proc :REFIID, :ptr
    UpdateAddrExclusionList proc :ptr
    .ends

LPADDREXCLUSIONCONTROL	typedef ptr IAddrExclusionControl

endif


ifndef __IPipeByte_INTERFACE_DEFINED__
define __IPipeByte_INTERFACE_DEFINED__

DEFINE_IIDX(IPipeByte, "DB2F3ACA-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeByte : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc
    .ends

endif


ifndef __AsyncIPipeByte_INTERFACE_DEFINED__
define __AsyncIPipeByte_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIPipeByte, "DB2F3ACB-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeByte : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc
    Finish_Push		proc
    .ends

endif

ifndef __IPipeLong_INTERFACE_DEFINED__
define __IPipeLong_INTERFACE_DEFINED__

DEFINE_IIDX(IPipeLong, "DB2F3ACC-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeLong : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc
    .ends

endif


ifndef __AsyncIPipeLong_INTERFACE_DEFINED__
define __AsyncIPipeLong_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIPipeLong, "DB2F3ACD-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeLong : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc
    Finish_Push		proc
    .ends

endif

ifndef __IPipeDouble_INTERFACE_DEFINED__
define __IPipeDouble_INTERFACE_DEFINED__

DEFINE_IIDX(IPipeDouble, "DB2F3ACE-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeDouble : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc
    .ends

endif

ifndef __AsyncIPipeDouble_INTERFACE_DEFINED__
define __AsyncIPipeDouble_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIPipeDouble, "DB2F3ACF-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeDouble : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc
    Finish_Push		proc
    .ends

endif

if defined(USE_COM_CONTEXT_DEF) OR defined(BUILDTYPE_COMSVCS) OR defined(_COMBASEAPI_) OR defined(_OLE32_)

CPFLAGS			typedef DWORD

ContextProperty		STRUC
policyId		GUID <>
flags			CPFLAGS ?
pUnk			LPUNKNOWN ?
ContextProperty		ENDS


ifndef __IEnumContextProps_INTERFACE_DEFINED__
define __IEnumContextProps_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumContextProps, "000001c1-0000-0000-C000-000000000046")

.comdef IEnumContextProps : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    Count		proc :ptr
    .ends

LPENUMCONTEXTPROPS	typedef ptr IEnumContextProps

endif

ifndef __IContext_INTERFACE_DEFINED__
define __IContext_INTERFACE_DEFINED__

DEFINE_IIDX(IContext, "000001c0-0000-0000-C000-000000000046")

.comdef IContext : public IUnknown

    SetProperty		proc :REFGUID, :CPFLAGS, :ptr
    RemoveProperty	proc :REFGUID
    GetProperty		proc :REFGUID, :ptr, :ptr
    EnumContextProps	proc :ptr
    .ends

endif

if NOT defined(BUILDTYPE_COMSVCS) AND NOT (defined(_COMBASEAPI_) OR defined(_OLE32_))

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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum APTTYPEQUALIFIER {
    APTTYPEQUALIFIER_NONE	= 0,
    APTTYPEQUALIFIER_IMPLICIT_MTA	= 1,
    APTTYPEQUALIFIER_NA_ON_MTA	= 2,
    APTTYPEQUALIFIER_NA_ON_STA	= 3,
    APTTYPEQUALIFIER_NA_ON_IMPLICIT_MTA = 4,
    APTTYPEQUALIFIER_NA_ON_MAINSTA	= 5,
    APTTYPEQUALIFIER_APPLICATION_STA	= 6
    }

.enum APTTYPE {
    APTTYPE_CURRENT = -1,
    APTTYPE_STA = 0,
    APTTYPE_MTA = 1,
    APTTYPE_NA	= 2,
    APTTYPE_MAINSTA = 3
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum THDTYPE {
    THDTYPE_BLOCKMESSAGES	= 0,
    THDTYPE_PROCESSMESSAGES	= 1
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
    CO_MARSHALING_CONTEXT_ATTRIBUTE_RESERVED_2	= 0x80000001
    }


ifndef __IMarshalingStream_INTERFACE_DEFINED__
define __IMarshalingStream_INTERFACE_DEFINED__

DEFINE_IIDX(IMarshalingStream, "D8F2F5E6-6102-4863-9F26-389A4676EFDE")

.comdef IMarshalingStream : public IStream

    GetMarshalingContextAttribute proc :CO_MARSHALING_CONTEXT_ATTRIBUTES, :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IAgileReference_INTERFACE_DEFINED__
define __IAgileReference_INTERFACE_DEFINED__

DEFINE_IIDX(IAgileReference, "C03F6A43-65A4-9818-987E-E0B810D2A6F2")

.comdef IAgileReference : public IUnknown

    Resolve		proc :REFIID, :ptr
    .ends

endif
endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

externdef ICallbackWithNoReentrancyToApplicationSTA:GUID

endif

_OBJIDLBASE_ equ 1
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IMallocSpy_INTERFACE_DEFINED__
define __IMallocSpy_INTERFACE_DEFINED__

DEFINE_IIDX(IMallocSpy, "0000001d-0000-0000-C000-000000000046")

.comdef IMallocSpy : public IUnknown

    PreAlloc		proc :SIZE_T
    PostAlloc		proc :ptr
    PreFree		proc :ptr, :BOOL
    PostFree		proc :BOOL
    PreRealloc		proc :ptr, :SIZE_T, :ptr, :BOOL
    PostRealloc		proc :ptr, :BOOL
    PreGetSize		proc :ptr, :BOOL
    PostGetSize		proc :SIZE_T, :BOOL
    PreDidAlloc		proc :ptr, :BOOL
    PostDidAlloc	proc :ptr, :BOOL, :SINT
    PreHeapMinimize	proc
    PostHeapMinimize	proc
    .ends

LPMALLOCSPY		typedef ptr IMallocSpy

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IBindCtx_INTERFACE_DEFINED__
define __IBindCtx_INTERFACE_DEFINED__

LPBC			typedef ptr IBindCtx
LPBINDCTX		typedef ptr IBindCtx

BIND_OPTS		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
BIND_OPTS		ENDS
LPBIND_OPTS		typedef ptr BIND_OPTS

BIND_OPTS2		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
dwTrackFlags		dd ?
dwClassContext		dd ?
locale			LCID ?
pServerInfo		LPCOSERVERINFO ?
BIND_OPTS2		ENDS
LPBIND_OPTS2		typedef ptr BIND_OPTS2

BIND_OPTS3		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
dwTrackFlags		dd ?
dwClassContext		dd ?
locale			LCID ?
pServerInfo		LPCOSERVERINFO ?
hwnd			HWND ?
BIND_OPTS3		ENDS
LPBIND_OPTS3		typedef ptr BIND_OPTS3

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
    GetRunningObjectTable proc :ptr
    RegisterObjectParam proc :LPOLESTR, :ptr
    GetObjectParam	proc :LPOLESTR, :ptr
    EnumObjectParam	proc :ptr
    RevokeObjectParam	proc :LPOLESTR
    .ends

endif


ifndef __IEnumMoniker_INTERFACE_DEFINED__
define __IEnumMoniker_INTERFACE_DEFINED__

LPENUMMONIKER		typedef ptr IEnumMoniker

DEFINE_IIDX(IEnumMoniker, "00000102-0000-0000-C000-000000000046")

.comdef IEnumMoniker : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IRunnableObject_INTERFACE_DEFINED__
define __IRunnableObject_INTERFACE_DEFINED__

DEFINE_IIDX(IRunnableObject, "00000126-0000-0000-C000-000000000046")

.comdef IRunnableObject : public IUnknown

    GetRunningClass	proc :LPCLSID
    Run			proc :LPBINDCTX
    IsRunning		proc
    LockRunning		proc :BOOL, :BOOL
    SetContainedObject	proc :BOOL
    .ends

LPRUNNABLEOBJECT	typedef ptr IRunnableObject

endif

ifndef __IRunningObjectTable_INTERFACE_DEFINED__
define __IRunningObjectTable_INTERFACE_DEFINED__

DEFINE_IIDX(IRunningObjectTable, "00000010-0000-0000-C000-000000000046")

.comdef IRunningObjectTable : public IUnknown

    Register		proc :DWORD, :ptr, :ptr, :ptr
    Revoke		proc :DWORD
    IsRunning		proc :ptr
    GetObject		proc :ptr, :ptr
    NoteChangeTime	proc :DWORD, :ptr
    GetTimeOfLastChange proc :ptr, :ptr
    EnumRunning		proc :ptr
    .ends

LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IPersist_INTERFACE_DEFINED__
define __IPersist_INTERFACE_DEFINED__

DEFINE_IIDX(IPersist, "0000010c-0000-0000-C000-000000000046")

.comdef IPersist : public IUnknown

    GetClassID		proc :ptr
    .ends

LPPERSIST		typedef ptr IPersist

endif

ifndef __IPersistStream_INTERFACE_DEFINED__
define __IPersistStream_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistStream, "00000109-0000-0000-C000-000000000046")

.comdef IPersistStream : public IPersist

    IsDirty		proc
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    GetSizeMax		proc :ptr
    .ends

LPPERSISTSTREAM		typedef ptr IPersistStream

endif

ifndef __IMoniker_INTERFACE_DEFINED__
define __IMoniker_INTERFACE_DEFINED__

.enum MKSYS {
    MKSYS_NONE		= 0,
    MKSYS_GENERICCOMPOSITE = 1,
    MKSYS_FILEMONIKER	= 2,
    MKSYS_ANTIMONIKER	= 3,
    MKSYS_ITEMMONIKER	= 4,
    MKSYS_POINTERMONIKER = 5,
    MKSYS_CLASSMONIKER	= 7,
    MKSYS_OBJREFMONIKER = 8,
    MKSYS_SESSIONMONIKER = 9,
    MKSYS_LUAMONIKER	= 10
    }

.enum MKREDUCE {
    MKRREDUCE_ONE	= ( 3 shl 16 ),
    MKRREDUCE_TOUSER	= ( 2 shl 16 ),
    MKRREDUCE_THROUGHUSER = ( 1 shl 16 ),
    MKRREDUCE_ALL	= 0
    }

DEFINE_IIDX(IMoniker, "0000000f-0000-0000-C000-000000000046")

.comdef IMoniker : public IPersistStream

    BindToObject	proc :ptr, :ptr, :REFIID, :ptr
    BindToStorage	proc :ptr, :ptr, :REFIID, :ptr
    Reduce		proc :ptr, :DWORD, :ptr, :ptr
    ComposeWith		proc :ptr, :BOOL, :ptr
    Enum		proc :BOOL, :ptr
    IsEqual		proc :ptr
    Hash		proc :ptr
    IsRunning		proc :ptr, :ptr, :ptr
    GetTimeOfLastChange proc :ptr, :ptr, :ptr
    Inverse		proc :ptr
    CommonPrefixWith	proc :ptr, :ptr
    RelativePathTo	proc :ptr, :ptr
    GetDisplayName	proc :ptr, :ptr, :ptr
    ParseDisplayName	proc :ptr, :ptr, :LPOLESTR, :ptr, :ptr
    IsSystemMoniker	proc :ptr
    .ends

LPMONIKER		typedef ptr IMoniker

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IROTData_INTERFACE_DEFINED__
define __IROTData_INTERFACE_DEFINED__

DEFINE_IIDX(IROTData, "f29f6bc0-5021-11ce-aa15-00006901293f")

.comdef IROTData : public IUnknown

    GetComparisonData	proc
    .ends

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IEnumSTATSTG_INTERFACE_DEFINED__
define __IEnumSTATSTG_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumSTATSTG, "0000000d-0000-0000-C000-000000000046")

.comdef IEnumSTATSTG : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

LPENUMSTATSTG		typedef ptr IEnumSTATSTG

endif

ifndef __IStorage_INTERFACE_DEFINED__
define __IStorage_INTERFACE_DEFINED__

RemSNB			STRUC
ulCntStr		ULONG ?
ulCntChar		ULONG ?
rgString		OLECHAR 1 dup(?)
RemSNB			ENDS

wireSNB			typedef ptr RemSNB
SNB			typedef ptr LPOLESTR

DEFINE_IIDX(IStorage, "0000000b-0000-0000-C000-000000000046")

.comdef IStorage : public IUnknown

    CreateStream	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr
    OpenStream		proc :ptr, :ptr, :DWORD, :DWORD, :ptr
    CreateStorage	proc :ptr, :DWORD, :DWORD, :DWORD, :ptr
    OpenStorage		proc :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr
    CopyTo		proc :DWORD
    MoveElementTo	proc :ptr, :ptr, :ptr, :DWORD
    Commit		proc :DWORD
    Revert		proc
    EnumElements	proc :DWORD, :ptr, :DWORD, :ptr
    DestroyElement	proc :ptr
    RenameElement	proc :ptr, :ptr
    SetElementTimes	proc :ptr, :ptr, :ptr, :ptr
    SetClass		proc :REFCLSID
    SetStateBits	proc :DWORD, :DWORD
    Stat		proc :ptr, :DWORD
    .ends

LPSTORAGE		typedef ptr IStorage

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IPersistFile_INTERFACE_DEFINED__
define __IPersistFile_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistFile, "0000010b-0000-0000-C000-000000000046")

.comdef IPersistFile : public IPersist

    IsDirty		proc
    Load		proc :LPCOLESTR, :DWORD
    Save		proc :LPCOLESTR, :BOOL
    SaveCompleted	proc :LPCOLESTR
    GetCurFile		proc :ptr
    .ends

LPPERSISTFILE		typedef ptr IPersistFile

endif

ifndef __IPersistStorage_INTERFACE_DEFINED__
define __IPersistStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistStorage, "0000010a-0000-0000-C000-000000000046")

.comdef IPersistStorage : public IPersist

    IsDirty		proc
    InitNew		proc :ptr
    Load		proc :ptr
    Save		proc :ptr, :BOOL
    SaveCompleted	proc :ptr
    HandsOffStorage	proc
    .ends

LPPERSISTSTORAGE	typedef ptr IPersistStorage

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __ILockBytes_INTERFACE_DEFINED__
define __ILockBytes_INTERFACE_DEFINED__

DEFINE_IIDX(ILockBytes, "0000000a-0000-0000-C000-000000000046")

.comdef ILockBytes : public IUnknown

    ReadAt		proc :ULARGE_INTEGER, :ptr, :ULONG, :ptr
    WriteAt		proc :ULARGE_INTEGER
    Flush		proc
    SetSize		proc :ULARGE_INTEGER
    LockRegion		proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    UnlockRegion	proc :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
    Stat		proc :ptr, :DWORD
    .ends

LPLOCKBYTES		typedef ptr ILockBytes

endif

ifndef __IEnumFORMATETC_INTERFACE_DEFINED__
define __IEnumFORMATETC_INTERFACE_DEFINED__

DVTARGETDEVICE		STRUC
tdSize			dd ?
tdDriverNameOffset	dw ?
tdDeviceNameOffset	dw ?
tdPortNameOffset	dw ?
tdExtDevmodeOffset	dw ?
tdData			db 1 dup(?)
DVTARGETDEVICE		ENDS
LPDVTARGETDEVICE	typedef ptr DVTARGETDEVICE


LPCLIPFORMAT		typedef ptr CLIPFORMAT

FORMATETC		STRUC
cfFormat		CLIPFORMAT ?
ptd			LPDVTARGETDEVICE ?
dwAspect		dd ?
lindex			LONG ?
tymed			dd ?
FORMATETC		ENDS
LPFORMATETC		typedef ptr FORMATETC

DEFINE_IIDX(IEnumFORMATETC, "00000103-0000-0000-C000-000000000046")

.comdef IEnumFORMATETC : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

LPENUMFORMATETC		typedef ptr IEnumFORMATETC

endif

ifndef __IEnumSTATDATA_INTERFACE_DEFINED__
define __IEnumSTATDATA_INTERFACE_DEFINED__

.enum ADVF {
    ADVF_NODATA		= 1,
    ADVF_PRIMEFIRST	= 2,
    ADVF_ONLYONCE	= 4,
    ADVF_DATAONSTOP	= 64,
    ADVFCACHE_NOHANDLER = 8,
    ADVFCACHE_FORCEBUILTIN = 16,
    ADVFCACHE_ONSAVE	= 32
    }

DEFINE_IIDX(IEnumSTATDATA, "00000105-0000-0000-C000-000000000046")

.comdef IEnumSTATDATA : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

LPENUMSTATDATA		typedef ptr IEnumSTATDATA

endif


ifndef __IRootStorage_INTERFACE_DEFINED__
define __IRootStorage_INTERFACE_DEFINED__

DEFINE_IIDX(IRootStorage, "00000012-0000-0000-C000-000000000046")

.comdef IRootStorage : public IUnknown

    SwitchToFile	proc :LPOLESTR
    .ends

LPROOTSTORAGE		typedef ptr IRootStorage

endif

ifndef __IAdviseSink_INTERFACE_DEFINED__
define __IAdviseSink_INTERFACE_DEFINED__

.enum TYMED {
    TYMED_HGLOBAL = 1,
    TYMED_FILE	= 2,
    TYMED_ISTREAM = 4,
    TYMED_ISTORAGE = 8,
    TYMED_GDI	= 16,
    TYMED_MFPICT = 32,
    TYMED_ENHMF = 64,
    TYMED_NULL	= 0
    }

RemSTGMEDIUM		STRUC
tymed			dd ?
dwHandleType		dd ?
pData			ULONG ?
pUnkForRelease		ULONG ?
cbData			ULONG ?
data			db 1 dup(?)
RemSTGMEDIUM		ENDS

uSTGMEDIUM		STRUC
tymed			dd ?
UNION u
hBitmap			HBITMAP ?
hMetaFilePict		HMETAFILEPICT ?
hEnhMetaFile		HENHMETAFILE ?
hGlobal			HGLOBAL ?
lpszFileName		LPOLESTR ?
pstm			LPSTREAM ?
pstg			LPSTORAGE ?
ENDS
pUnkForRelease		LPUNKNOWN ?
uSTGMEDIUM		ENDS

GDI_OBJECT		STRUC
ObjectType		dd ?
UNION u
hBitmap			wireHBITMAP ?
hPalette		wireHPALETTE ?
hGeneric		wireHGLOBAL ?
ENDS
GDI_OBJECT		ENDS
LPGDI_OBJECT		typedef ptr GDI_OBJECT

userSTGMEDIUM		STRUC
STRUC
tymed			dd ?
UNION u
hMetaFilePict		wireHMETAFILEPICT ?
hHEnhMetaFile		wireHENHMETAFILE ?
hGdiHandle		LPGDI_OBJECT ?
hGlobal			wireHGLOBAL ?
lpszFileName		LPOLESTR ?
pstm			UP_BYTE_BLOB ?
pstg			UP_BYTE_BLOB ?
ENDS
ENDS
pUnkForRelease		LPUNKNOWN ?
userSTGMEDIUM		ENDS

wireSTGMEDIUM		typedef ptr userSTGMEDIUM
STGMEDIUM		typedef uSTGMEDIUM
wireASYNC_STGMEDIUM	typedef ptr userSTGMEDIUM
ASYNC_STGMEDIUM		typedef STGMEDIUM
LPSTGMEDIUM		typedef ptr STGMEDIUM

userFLAG_STGMEDIUM	STRUC
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			userSTGMEDIUM <>
userFLAG_STGMEDIUM	ENDS

wireFLAG_STGMEDIUM	typedef ptr userFLAG_STGMEDIUM

FLAG_STGMEDIUM		STRUC
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			STGMEDIUM <>
FLAG_STGMEDIUM		ENDS

DEFINE_IIDX(IAdviseSink, "0000010f-0000-0000-C000-000000000046")

.comdef IAdviseSink : public IUnknown

    OnDataChange	proc :ptr, :ptr
    OnViewChange	proc :DWORD, :LONG
    OnRename		proc :ptr
    OnSave		proc
    OnClose		proc
    .ends

LPADVISESINK		typedef ptr IAdviseSink

STATDATA		STRUC
formatetc		FORMATETC <>
advf			dd ?
pAdvSink		LPADVISESINK ?
dwConnection		dd ?
STATDATA		ENDS
LPSTATDATA		typedef ptr STATDATA

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

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IAdviseSink2_INTERFACE_DEFINED__
define __IAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(IAdviseSink2, "00000125-0000-0000-C000-000000000046")

.comdef IAdviseSink2 : public IAdviseSink

    OnLinkSrcChange	proc :ptr
    .ends

LPADVISESINK2		typedef ptr IAdviseSink2

endif

ifndef __AsyncIAdviseSink2_INTERFACE_DEFINED__
define __AsyncIAdviseSink2_INTERFACE_DEFINED__

DEFINE_IIDX(AsyncIAdviseSink2, "00000151-0000-0000-C000-000000000046")

.comdef AsyncIAdviseSink2 : public AsyncIAdviseSink

    Begin_OnLinkSrcChange proc :ptr
    Finish_OnLinkSrcChange proc
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IDataObject_INTERFACE_DEFINED__
define __IDataObject_INTERFACE_DEFINED__

.enum DATADIR {
    DATADIR_GET = 1,
    DATADIR_SET = 2
    }

DEFINE_IIDX(IDataObject, "0000010e-0000-0000-C000-000000000046")

.comdef IDataObject : public IUnknown

    GetData		proc :ptr, :ptr
    GetDataHere		proc :ptr, :ptr
    QueryGetData	proc :ptr
    GetCanonicalFormatEtc proc :ptr, :ptr
    SetData		proc :ptr, :ptr, :BOOL
    EnumFormatEtc	proc :DWORD, :ptr
    DAdvise		proc :ptr, :DWORD, :ptr, :ptr
    DUnadvise		proc :DWORD
    EnumDAdvise		proc :ptr
    .ends

LPDATAOBJECT		typedef ptr IDataObject

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
define __IDataAdviseHolder_INTERFACE_DEFINED__

DEFINE_IIDX(IDataAdviseHolder, "00000110-0000-0000-C000-000000000046")

.comdef IDataAdviseHolder : public IUnknown

    Advise		proc :ptr, :ptr, :DWORD, :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr
    SendOnDataChange	proc :ptr, :DWORD, :DWORD
    .ends

LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder

endif

ifndef __IMessageFilter_INTERFACE_DEFINED__
define __IMessageFilter_INTERFACE_DEFINED__

.enum CALLTYPE {
    CALLTYPE_TOPLEVEL	= 1,
    CALLTYPE_NESTED	= 2,
    CALLTYPE_ASYNC	= 3,
    CALLTYPE_TOPLEVEL_CALLPENDING = 4,
    CALLTYPE_ASYNC_CALLPENDING	= 5
    }

.enum SERVERCALL {
    SERVERCALL_ISHANDLED = 0,
    SERVERCALL_REJECTED = 1,
    SERVERCALL_RETRYLATER = 2
    }

.enum PENDINGTYPE {
    PENDINGTYPE_TOPLEVEL = 1,
    PENDINGTYPE_NESTED	= 2
    }

.enum PENDINGMSG {
    PENDINGMSG_CANCELCALL	= 0,
    PENDINGMSG_WAITNOPROCESS	= 1,
    PENDINGMSG_WAITDEFPROCESS	= 2
    }

INTERFACEINFO		STRUC
pUnk			LPUNKNOWN ?
iid			IID <>
wMethod			dw ?
INTERFACEINFO		ENDS
LPINTERFACEINFO		typedef ptr INTERFACEINFO

DEFINE_IIDX(IMessageFilter, "00000016-0000-0000-C000-000000000046")

.comdef IMessageFilter : public IUnknown

    HandleInComingCall	proc :DWORD, :HTASK, :DWORD, :LPINTERFACEINFO
    RetryRejectedCall	proc :HTASK, :DWORD, :DWORD
    MessagePending	proc :HTASK, :DWORD, :DWORD
    .ends

LPMESSAGEFILTER		typedef ptr IMessageFilter

endif

externdef		FMTID_SummaryInformation:FMTID
externdef		FMTID_DocSummaryInformation:FMTID
externdef		FMTID_UserDefinedProperties:FMTID
externdef		FMTID_DiscardableInformation:FMTID
externdef		FMTID_ImageSummaryInformation:FMTID
externdef		FMTID_AudioSummaryInformation:FMTID
externdef		FMTID_VideoSummaryInformation:FMTID
externdef		FMTID_MediaFileSummaryInformation:FMTID

ifndef __IClassActivator_INTERFACE_DEFINED__
define __IClassActivator_INTERFACE_DEFINED__

DEFINE_IIDX(IClassActivator, "00000140-0000-0000-C000-000000000046")

.comdef IClassActivator : public IUnknown

    GetClassObject	proc :REFCLSID, :DWORD, :LCID, :REFIID, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IFillLockBytes_INTERFACE_DEFINED__
define __IFillLockBytes_INTERFACE_DEFINED__

DEFINE_IIDX(IFillLockBytes, "99caf010-415e-11cf-8814-00aa00b569f5")

.comdef IFillLockBytes : public IUnknown

    FillAppend		proc
    FillAt		proc :ULARGE_INTEGER
    SetFillSize		proc :ULARGE_INTEGER
    Terminate		proc :BOOL
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IProgressNotify_INTERFACE_DEFINED__
define __IProgressNotify_INTERFACE_DEFINED__

DEFINE_IIDX(IProgressNotify, "a9d758a0-4617-11cf-95fc-00aa00680db4")

.comdef IProgressNotify : public IUnknown

    OnProgress		proc :DWORD, :DWORD, :BOOL, :BOOL
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __ILayoutStorage_INTERFACE_DEFINED__
define __ILayoutStorage_INTERFACE_DEFINED__

StorageLayout		STRUC
LayoutType		dd ?
pwcsElementName		LPOLESTR ?
cOffset			LARGE_INTEGER <>
cBytes			LARGE_INTEGER <>
StorageLayout		ENDS

DEFINE_IIDX(ILayoutStorage, "0e6d4d90-6738-11cf-9608-00aa00680db4")

.comdef ILayoutStorage : public IUnknown

    .ends
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

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

    CreateStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr
    OpenStorageEx	proc :LPCWSTR, :DWORD, :DWORD, :DWORD, :REFIID, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

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

.comdef IDummyHICONIncluder

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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

DEFINE_IIDX(IProcessLock, "947990de-cc28-11d2-a0f7-00805f858fb1")

.comdef IProcessLock : public IUnknown

    AddRefOnProcess	proc
    ReleaseRefOnProcess proc
    .ends

endif


ifndef __ISurrogateService_INTERFACE_DEFINED__
define __ISurrogateService_INTERFACE_DEFINED__

DEFINE_IIDX(ISurrogateService, "000001d5-0000-0000-C000-000000000046")

.comdef ISurrogateService : public IUnknown

    Init		proc :REFGUID, :ptr, :ptr
    ApplicationLaunch	proc :REFGUID, :ApplicationType
    ApplicationFree	proc :REFGUID
    CatalogRefresh	proc :ULONG
    ProcessShutdown	proc :ShutdownType
    .ends

endif

if  (_WIN32_WINNT GE 0x0501 )

ifndef __IInitializeSpy_INTERFACE_DEFINED__
define __IInitializeSpy_INTERFACE_DEFINED__

DEFINE_IIDX(IInitializeSpy, "000001d4-0000-0000-C000-000000000046")

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

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IApartmentShutdown_INTERFACE_DEFINED__
define __IApartmentShutdown_INTERFACE_DEFINED__

DEFINE_IIDX(IApartmentShutdown, "00000034-0000-0000-C000-000000000046")

.comdef IApartmentShutdown : public IUnknown

    OnUninitialize	proc :UINT64
    .ends

endif

endif

endif
