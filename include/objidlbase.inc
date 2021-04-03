ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __objidlbase_h__
__objidlbase_h__ equ <>

ifndef __IMarshal_FWD_DEFINED__
__IMarshal_FWD_DEFINED__ equ 1
endif
ifndef __INoMarshal_FWD_DEFINED__
__INoMarshal_FWD_DEFINED__ equ 1
endif
ifndef __IAgileObject_FWD_DEFINED__
__IAgileObject_FWD_DEFINED__ equ 1
endif
ifndef __IActivationFilter_FWD_DEFINED__
__IActivationFilter_FWD_DEFINED__ equ 1
endif
ifndef __IMarshal2_FWD_DEFINED__
__IMarshal2_FWD_DEFINED__ equ 1
endif
ifndef __IMalloc_FWD_DEFINED__
__IMalloc_FWD_DEFINED__ equ 1
endif
ifndef __IStdMarshalInfo_FWD_DEFINED__
__IStdMarshalInfo_FWD_DEFINED__ equ 1
endif
ifndef __IExternalConnection_FWD_DEFINED__
__IExternalConnection_FWD_DEFINED__ equ 1
endif
ifndef __IMultiQI_FWD_DEFINED__
__IMultiQI_FWD_DEFINED__ equ 1
endif
ifndef __AsyncIMultiQI_FWD_DEFINED__
__AsyncIMultiQI_FWD_DEFINED__ equ 1
endif
ifndef __IInternalUnknown_FWD_DEFINED__
__IInternalUnknown_FWD_DEFINED__ equ 1
endif
ifndef __IEnumUnknown_FWD_DEFINED__
__IEnumUnknown_FWD_DEFINED__ equ 1
endif
ifndef __IEnumString_FWD_DEFINED__
__IEnumString_FWD_DEFINED__ equ 1
endif
ifndef __ISequentialStream_FWD_DEFINED__
__ISequentialStream_FWD_DEFINED__ equ 1
endif
ifndef __IStream_FWD_DEFINED__
__IStream_FWD_DEFINED__ equ 1
endif
ifndef __IRpcChannelBuffer_FWD_DEFINED__
__IRpcChannelBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IRpcChannelBuffer2_FWD_DEFINED__
__IRpcChannelBuffer2_FWD_DEFINED__ equ 1
endif
ifndef __IAsyncRpcChannelBuffer_FWD_DEFINED__
__IAsyncRpcChannelBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IRpcChannelBuffer3_FWD_DEFINED__
__IRpcChannelBuffer3_FWD_DEFINED__ equ 1
endif
ifndef __IRpcSyntaxNegotiate_FWD_DEFINED__
__IRpcSyntaxNegotiate_FWD_DEFINED__ equ 1
endif
ifndef __IRpcProxyBuffer_FWD_DEFINED__
__IRpcProxyBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IRpcStubBuffer_FWD_DEFINED__
__IRpcStubBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IPSFactoryBuffer_FWD_DEFINED__
__IPSFactoryBuffer_FWD_DEFINED__ equ 1
endif
ifndef __IChannelHook_FWD_DEFINED__
__IChannelHook_FWD_DEFINED__ equ 1
endif
ifndef __IClientSecurity_FWD_DEFINED__
__IClientSecurity_FWD_DEFINED__ equ 1
endif
ifndef __IServerSecurity_FWD_DEFINED__
__IServerSecurity_FWD_DEFINED__ equ 1
endif
ifndef __IRpcOptions_FWD_DEFINED__
__IRpcOptions_FWD_DEFINED__ equ 1
endif
ifndef __IGlobalOptions_FWD_DEFINED__
__IGlobalOptions_FWD_DEFINED__ equ 1
endif
ifndef __ISurrogate_FWD_DEFINED__
__ISurrogate_FWD_DEFINED__ equ 1
endif
ifndef __IGlobalInterfaceTable_FWD_DEFINED__
__IGlobalInterfaceTable_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronize_FWD_DEFINED__
__ISynchronize_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronizeHandle_FWD_DEFINED__
__ISynchronizeHandle_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronizeEvent_FWD_DEFINED__
__ISynchronizeEvent_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronizeContainer_FWD_DEFINED__
__ISynchronizeContainer_FWD_DEFINED__ equ 1
endif
ifndef __ISynchronizeMutex_FWD_DEFINED__
__ISynchronizeMutex_FWD_DEFINED__ equ 1
endif
ifndef __ICancelMethodCalls_FWD_DEFINED__
__ICancelMethodCalls_FWD_DEFINED__ equ 1
endif
ifndef __IAsyncManager_FWD_DEFINED__
__IAsyncManager_FWD_DEFINED__ equ 1
endif
ifndef __ICallFactory_FWD_DEFINED__
__ICallFactory_FWD_DEFINED__ equ 1
endif
ifndef __IRpcHelper_FWD_DEFINED__
__IRpcHelper_FWD_DEFINED__ equ 1
endif
ifndef __IReleaseMarshalBuffers_FWD_DEFINED__
__IReleaseMarshalBuffers_FWD_DEFINED__ equ 1
endif
ifndef __IWaitMultiple_FWD_DEFINED__
__IWaitMultiple_FWD_DEFINED__ equ 1
endif
ifndef __IAddrTrackingControl_FWD_DEFINED__
__IAddrTrackingControl_FWD_DEFINED__ equ 1
endif
ifndef __IAddrExclusionControl_FWD_DEFINED__
__IAddrExclusionControl_FWD_DEFINED__ equ 1
endif
ifndef __IPipeByte_FWD_DEFINED__
__IPipeByte_FWD_DEFINED__ equ 1
endif
ifndef __AsyncIPipeByte_FWD_DEFINED__
__AsyncIPipeByte_FWD_DEFINED__ equ 1
endif
ifndef __IPipeLong_FWD_DEFINED__
__IPipeLong_FWD_DEFINED__ equ 1
endif
ifndef __AsyncIPipeLong_FWD_DEFINED__
__AsyncIPipeLong_FWD_DEFINED__ equ 1
endif
ifndef __IPipeDouble_FWD_DEFINED__
__IPipeDouble_FWD_DEFINED__ equ 1
endif
ifndef __AsyncIPipeDouble_FWD_DEFINED__
__AsyncIPipeDouble_FWD_DEFINED__ equ 1
endif
ifndef __IEnumContextProps_FWD_DEFINED__
__IEnumContextProps_FWD_DEFINED__ equ 1
endif
ifndef __IContext_FWD_DEFINED__
__IContext_FWD_DEFINED__ equ 1
endif
ifndef __IObjContext_FWD_DEFINED__
__IObjContext_FWD_DEFINED__ equ 1
endif
ifndef __IComThreadingInfo_FWD_DEFINED__
__IComThreadingInfo_FWD_DEFINED__ equ 1
endif
ifndef __IProcessInitControl_FWD_DEFINED__
__IProcessInitControl_FWD_DEFINED__ equ 1
endif
ifndef __IFastRundown_FWD_DEFINED__
__IFastRundown_FWD_DEFINED__ equ 1
endif
ifndef __IMarshalingStream_FWD_DEFINED__
__IMarshalingStream_FWD_DEFINED__ equ 1
endif
ifndef __IAgileReference_FWD_DEFINED__
__IAgileReference_FWD_DEFINED__ equ 1
endif

include unknwnbase.inc
include winapifamily.inc

if(NTDDI_VERSION GE NTDDI_VISTA AND NOT defined(_WIN32_WINNT))
_WIN32_WINNT equ 0x0600
endif
if(NTDDI_VERSION GE NTDDI_WS03 AND NOT defined(_WIN32_WINNT))
_WIN32_WINNT equ 0x0502
endif
if(NTDDI_VERSION GE NTDDI_WINXP AND NOT defined(_WIN32_WINNT))
_WIN32_WINNT equ 0x0501
endif
if(NTDDI_VERSION GE NTDDI_WIN2K AND NOT defined(_WIN32_WINNT))
_WIN32_WINNT equ 0x0500
endif

ifndef _OBJIDLBASE_

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

COSERVERINFO		STRUC
dwReserved1		dd ?
pwszName		LPWSTR ?
pAuthInfo		LPCOAUTHINFO ?
dwReserved2		dd ?
COSERVERINFO		ENDS

ifndef __IMarshal_INTERFACE_DEFINED__
__IMarshal_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMarshal, "00000003-0000-0000-C000-000000000046")

.comdef IMarshal : public IUnknown

    GetUnmarshalClass	proc :REFIID, :ptr, :DWORD, :ptr, :DWORD, :ptr
    GetMarshalSizeMax	proc :REFIID, :ptr, :DWORD, :ptr, :DWORD, :ptr
    MarshalInterface	proc :ptr, :REFIID, :ptr, :DWORD, :ptr, :DWORD
    UnmarshalInterface	proc :ptr, :REFIID, :ptr
    ReleaseMarshalData	proc :ptr
    DisconnectObject	proc :DWORD
    .ends

    LPMARSHAL typedef ptr IMarshal

endif

ifndef __INoMarshal_INTERFACE_DEFINED__
__INoMarshal_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(INoMarshal, "ecc8691b-c1db-4dc0-855e-65f6c551af49")

.comdef INoMarshal : public IUnknown

    .ends

endif

ifndef __IAgileObject_INTERFACE_DEFINED__
__IAgileObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAgileObject, "94ea2b94-e9cc-49e0-c0ff-ee64ca8f5b90")

.comdef IAgileObject : public IUnknown

    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IActivationFilter_INTERFACE_DEFINED__
__IActivationFilter_INTERFACE_DEFINED__ equ 1

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
__IMarshal2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMarshal2, "000001cf-0000-0000-C000-000000000046")

.comdef IMarshal2 : public IMarshal

    .ends

    LPMARSHAL2 typedef ptr IMarshal2

endif

ifndef __IMalloc_INTERFACE_DEFINED__
__IMalloc_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMalloc, "00000002-0000-0000-C000-000000000046")

.comdef IMalloc : public IUnknown

    Alloc		proc :SIZE_T
    Realloc		proc :ptr, :SIZE_T
    Free		proc :ptr
    GetSize		proc :ptr
    DidAlloc		proc :ptr
    HeapMinimize	proc
    .ends

    LPMALLOC typedef ptr IMalloc

endif

ifndef __IStdMarshalInfo_INTERFACE_DEFINED__
__IStdMarshalInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IStdMarshalInfo, "00000018-0000-0000-C000-000000000046")

.comdef IStdMarshalInfo : public IUnknown

    GetClassForHandler	proc :DWORD, :ptr, :ptr
    .ends

    LPSTDMARSHALINFO typedef ptr IStdMarshalInfo

endif

ifndef __IExternalConnection_INTERFACE_DEFINED__
__IExternalConnection_INTERFACE_DEFINED__ equ 1

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

    LPEXTERNALCONNECTION typedef ptr IExternalConnection

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

MULTI_QI		STRUC
pIID			LPIID ?
pItf			LPIUnknown ?
hr			HRESULT ?
MULTI_QI		ENDS

ifndef __IMultiQI_INTERFACE_DEFINED__
__IMultiQI_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMultiQI, "00000020-0000-0000-C000-000000000046")

.comdef IMultiQI : public IUnknown

    QueryMultipleInterfaces proc :ULONG, :ptr
    .ends

    LPMULTIQI typedef ptr IMultiQI

endif

ifndef __AsyncIMultiQI_INTERFACE_DEFINED__
__AsyncIMultiQI_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(AsyncIMultiQI, "000e0020-0000-0000-C000-000000000046")

.comdef AsyncIMultiQI : public IUnknown

    Begin_QueryMultipleInterfaces proc :ULONG, :ptr
    Finish_QueryMultipleInterfaces proc :ptr
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IInternalUnknown_INTERFACE_DEFINED__
__IInternalUnknown_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternalUnknown, "00000021-0000-0000-C000-000000000046")

.comdef IInternalUnknown : public IUnknown

    QueryInternalInterface proc :REFIID, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IEnumUnknown_INTERFACE_DEFINED__
__IEnumUnknown_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumUnknown, "00000100-0000-0000-C000-000000000046")

.comdef IEnumUnknown : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

    LPENUMUNKNOWN typedef ptr IEnumUnknown

endif

ifndef __IEnumString_INTERFACE_DEFINED__
__IEnumString_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IEnumString, "00000101-0000-0000-C000-000000000046")

.comdef IEnumString : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
    .ends

    LPENUMSTRING typedef ptr IEnumString

endif

ifndef __ISequentialStream_INTERFACE_DEFINED__
__ISequentialStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISequentialStream, "0c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ISequentialStream : public IUnknown

    Read		proc :ptr, :ULONG, :ptr
    Write		proc
    .ends

endif

ifndef __IStream_INTERFACE_DEFINED__
__IStream_INTERFACE_DEFINED__ equ 1

STATSTG			STRUC
pwcsName		LPOLESTR ?
type			dd ?
cbSize			ULARGE_INTEGER ?
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
grfMode			dd ?
grfLocksSupported	dd ?
clsid			CLSID ?
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
__IRpcChannelBuffer_INTERFACE_DEFINED__ equ 1

RPCOLEDATAREP		typedef ULONG

RPCOLEMESSAGE		STRUC
reserved1		LPvoid ?
dataRepresentation	RPCOLEDATAREP ?
Buffer			LPvoid ?
cbBuffer		ULONG ?
iMethod			ULONG ?
reserved2		LPvoid 5 dup(?)
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

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IRpcChannelBuffer2_INTERFACE_DEFINED__
__IRpcChannelBuffer2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcChannelBuffer2, "594f31d0-7f19-11d0-b194-00a0c90dc8bf")

.comdef IRpcChannelBuffer2 : public IRpcChannelBuffer

    GetProtocolVersion	proc :ptr
    .ends

endif

ifndef __IAsyncRpcChannelBuffer_INTERFACE_DEFINED__
__IAsyncRpcChannelBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAsyncRpcChannelBuffer, "a5029fb6-3c34-11d1-9c99-00c04fb998aa")

.comdef IAsyncRpcChannelBuffer : public IRpcChannelBuffer2

    Send		proc :ptr, :ptr, :ptr
    Receive		proc :ptr, :ptr
    GetDestCtxEx	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __IRpcChannelBuffer3_INTERFACE_DEFINED__
__IRpcChannelBuffer3_INTERFACE_DEFINED__ equ 1

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
__IRpcSyntaxNegotiate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcSyntaxNegotiate, "58a08519-24c8-4935-b482-3fd823333a4f")

.comdef IRpcSyntaxNegotiate : public IUnknown

    NegotiateSyntax	proc :ptr
    .ends

endif

ifndef __IRpcProxyBuffer_INTERFACE_DEFINED__
__IRpcProxyBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcProxyBuffer, "D5F56A34-593B-101A-B569-08002B2DBF7A")

.comdef IRpcProxyBuffer : public IUnknown

    Connect		proc :ptr
    Disconnect		proc
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IRpcStubBuffer_INTERFACE_DEFINED__
__IRpcStubBuffer_INTERFACE_DEFINED__ equ 1

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
__IPSFactoryBuffer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPSFactoryBuffer, "D5F569D0-593B-101A-B569-08002B2DBF7A")

.comdef IPSFactoryBuffer : public IUnknown

    CreateProxy		proc :ptr, :REFIID, :ptr, :ptr
    CreateStub		proc :REFIID, :ptr, :ptr
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

SChannelHookCallInfo	STRUC
iid			IID <>
cbSize			dd ?
uCausality		GUID <>
dwServerPid		dd ?
iMethod			dd ?
pObject			LPVOID ?
SChannelHookCallInfo	ENDS

ifndef __IChannelHook_INTERFACE_DEFINED__
__IChannelHook_INTERFACE_DEFINED__ equ 1

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

endif ;; (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)
endif ;;  WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IClientSecurity_INTERFACE_DEFINED__
__IClientSecurity_INTERFACE_DEFINED__ equ 1

SOLE_AUTHENTICATION_SERVICE STRUC
dwAuthnSvc		dd ?
dwAuthzSvc		dd ?
pPrincipalName		LPOLECHAR ?
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
pAuthInfo		LPVOID ?
SOLE_AUTHENTICATION_INFO ENDS

PSOLE_AUTHENTICATION_INFO typedef ptr SOLE_AUTHENTICATION_INFO

SOLE_AUTHENTICATION_LIST STRUC
cAuthInfo		dd ?
aAuthInfo		LPSOLE_AUTHENTICATION_INFO ?
SOLE_AUTHENTICATION_LIST ENDS

PSOLE_AUTHENTICATION_LIST typedef ptr SOLE_AUTHENTICATION_LIST

DEFINE_IIDX(IClientSecurity, "0000013D-0000-0000-C000-000000000046")

.comdef IClientSecurity : public IUnknown

    QueryBlanket	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    SetBlanket		proc :ptr, :DWORD, :DWORD, :ptr, :DWORD, :DWORD, :ptr, :DWORD
    CopyProxy		proc :ptr, :ptr
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IServerSecurity_INTERFACE_DEFINED__
__IServerSecurity_INTERFACE_DEFINED__ equ 1

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
    SERVER_LOCALITY_REMOTE = 2
    }

ifndef __IRpcOptions_INTERFACE_DEFINED__
__IRpcOptions_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcOptions, "00000144-0000-0000-C000-000000000046")

.comdef IRpcOptions : public IUnknown

    Set			proc :ptr, :RPCOPT_PROPERTIES, :ULONG_PTR
    Query		proc :ptr, :RPCOPT_PROPERTIES, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

.enum GLOBALOPT_PROPERTIES {
    COMGLB_EXCEPTION_HANDLING = 1,
    COMGLB_APPID	= 2,
    COMGLB_RPC_THREADPOOL_SETTING = 3,
    COMGLB_RO_SETTINGS	= 4,
    COMGLB_UNMARSHALING_POLICY = 5
    }

.enum GLOBALOPT_EH_VALUES {
    COMGLB_EXCEPTION_HANDLE = 0,
    COMGLB_EXCEPTION_DONOT_HANDLE_FATAL = 1,
    COMGLB_EXCEPTION_DONOT_HANDLE = COMGLB_EXCEPTION_DONOT_HANDLE_FATAL,
    COMGLB_EXCEPTION_DONOT_HANDLE_ANY = 2
    }

.enum GLOBALOPT_RPCTP_VALUES {
    COMGLB_RPC_THREADPOOL_SETTING_DEFAULT_POOL = 0,
    COMGLB_RPC_THREADPOOL_SETTING_PRIVATE_POOL = 1
    }

.enum GLOBALOPT_RO_FLAGS {
    COMGLB_STA_MODALLOOP_REMOVE_TOUCH_MESSAGES = 0x1,
    COMGLB_STA_MODALLOOP_SHARED_QUEUE_REMOVE_INPUT_MESSAGES = 0x2,
    COMGLB_STA_MODALLOOP_SHARED_QUEUE_DONOT_REMOVE_INPUT_MESSAGES = 0x4,
    COMGLB_FAST_RUNDOWN = 0x8,
    COMGLB_RESERVED1	= 0x10,
    COMGLB_RESERVED2	= 0x20,
    COMGLB_RESERVED3	= 0x40,
    COMGLB_STA_MODALLOOP_SHARED_QUEUE_REORDER_POINTER_MESSAGES = 0x80,
    COMGLB_RESERVED4	= 0x100,
    COMGLB_RESERVED5	= 0x200
    }

.enum GLOBALOPT_UNMARSHALING_POLICY_VALUES {
    COMGLB_UNMARSHALING_POLICY_NORMAL = 0,
    COMGLB_UNMARSHALING_POLICY_STRONG = 1,
    COMGLB_UNMARSHALING_POLICY_HYBRID = 2
    }

ifndef __IGlobalOptions_INTERFACE_DEFINED__
__IGlobalOptions_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IGlobalOptions, "0000015B-0000-0000-C000-000000000046")

.comdef IGlobalOptions : public IUnknown

    Set			proc :GLOBALOPT_PROPERTIES, :ULONG_PTR
    Query		proc :GLOBALOPT_PROPERTIES, :ptr
    .ends

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

endif ;; (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __ISurrogate_INTERFACE_DEFINED__
__ISurrogate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISurrogate, "00000022-0000-0000-C000-000000000046")

.comdef ISurrogate : public IUnknown

    LoadDllServer	proc :REFCLSID
    FreeSurrogate	proc
    .ends

    LPSURROGATE typedef ptr ISurrogate

endif

ifndef __IGlobalInterfaceTable_INTERFACE_DEFINED__
__IGlobalInterfaceTable_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IGlobalInterfaceTable, "00000146-0000-0000-C000-000000000046")

.comdef IGlobalInterfaceTable : public IUnknown

    RegisterInterfaceInGlobal proc :ptr, :REFIID, :ptr
    RevokeInterfaceFromGlobal proc :DWORD
    GetInterfaceFromGlobal proc :DWORD, :REFIID, :ptr
    .ends

    LPGLOBALINTERFACETABLE typedef ptr IGlobalInterfaceTable

endif

endif ;; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __ISynchronize_INTERFACE_DEFINED__
__ISynchronize_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronize, "00000030-0000-0000-C000-000000000046")

.comdef ISynchronize : public IUnknown

    _Wait		proc :DWORD, :DWORD
    Signal		proc
    Reset		proc
    .ends

endif

ifndef __ISynchronizeHandle_INTERFACE_DEFINED__
__ISynchronizeHandle_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeHandle, "00000031-0000-0000-C000-000000000046")

.comdef ISynchronizeHandle : public IUnknown

    GetHandle		proc :ptr
    .ends

endif

ifndef __ISynchronizeEvent_INTERFACE_DEFINED__
__ISynchronizeEvent_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeEvent, "00000032-0000-0000-C000-000000000046")

.comdef ISynchronizeEvent : public ISynchronizeHandle

    SetEventHandle	proc :ptr
    .ends

endif

ifndef __ISynchronizeContainer_INTERFACE_DEFINED__
__ISynchronizeContainer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeContainer, "00000033-0000-0000-C000-000000000046")

.comdef ISynchronizeContainer : public IUnknown

    AddSynchronize	proc :ptr
    WaitMultiple	proc :DWORD, :DWORD, :ptr
    .ends

endif

ifndef __ISynchronizeMutex_INTERFACE_DEFINED__
__ISynchronizeMutex_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISynchronizeMutex, "00000025-0000-0000-C000-000000000046")

.comdef ISynchronizeMutex : public ISynchronize

    ReleaseMutex	proc
    .ends

endif

ifndef __ICancelMethodCalls_INTERFACE_DEFINED__
__ICancelMethodCalls_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICancelMethodCalls, "00000029-0000-0000-C000-000000000046")

.comdef ICancelMethodCalls : public IUnknown

    Cancel		proc :ULONG
    TestCancel		proc
    .ends

    LPCANCELMETHODCALLS typedef ptr ICancelMethodCalls

endif

ifndef __IAsyncManager_INTERFACE_DEFINED__
__IAsyncManager_INTERFACE_DEFINED__ equ 1

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
__ICallFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ICallFactory, "1c733a30-2a1c-11ce-ade5-00aa0044773d")

.comdef ICallFactory : public IUnknown

    CreateCall		proc :REFIID, :ptr, :REFIID, :ptr
    .ends

endif

ifndef __IRpcHelper_INTERFACE_DEFINED__
__IRpcHelper_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IRpcHelper, "00000149-0000-0000-C000-000000000046")

.comdef IRpcHelper : public IUnknown

    GetDCOMProtocolVersion proc :ptr
    GetIIDFromOBJREF	proc :ptr, :ptr
    .ends

endif

ifndef __IReleaseMarshalBuffers_INTERFACE_DEFINED__
__IReleaseMarshalBuffers_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IReleaseMarshalBuffers, "eb0cb9e8-7996-11d2-872e-0000f8080859")

.comdef IReleaseMarshalBuffers : public IUnknown

    ReleaseMarshalBuffer proc :ptr, :DWORD, :ptr
    .ends

endif

ifndef __IWaitMultiple_INTERFACE_DEFINED__
__IWaitMultiple_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWaitMultiple, "0000002B-0000-0000-C000-000000000046")

.comdef IWaitMultiple : public IUnknown

    WaitMultiple	proc :DWORD, :ptr
    AddSynchronize	proc :ptr
    .ends

endif

ifndef __IAddrTrackingControl_INTERFACE_DEFINED__
__IAddrTrackingControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAddrTrackingControl, "00000147-0000-0000-C000-000000000046")

.comdef IAddrTrackingControl : public IUnknown

    EnableCOMDynamicAddrTracking proc
    DisableCOMDynamicAddrTracking proc
    .ends

    LPADDRTRACKINGCONTROL typedef ptr IAddrTrackingControl

endif

ifndef __IAddrExclusionControl_INTERFACE_DEFINED__
__IAddrExclusionControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAddrExclusionControl, "00000148-0000-0000-C000-000000000046")

.comdef IAddrExclusionControl : public IUnknown

    GetCurrentAddrExclusionList proc :REFIID, :ptr
    UpdateAddrExclusionList proc :ptr
    .ends

    LPADDREXCLUSIONCONTROL typedef ptr IAddrExclusionControl

endif

ifndef __IPipeByte_INTERFACE_DEFINED__
__IPipeByte_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPipeByte, "DB2F3ACA-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeByte : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc
    .ends

endif

ifndef __AsyncIPipeByte_INTERFACE_DEFINED__
__AsyncIPipeByte_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(AsyncIPipeByte, "DB2F3ACB-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeByte : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc
    Finish_Push		proc
    .ends

endif

ifndef __IPipeLong_INTERFACE_DEFINED__
__IPipeLong_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPipeLong, "DB2F3ACC-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeLong : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc
    .ends

endif

ifndef __AsyncIPipeLong_INTERFACE_DEFINED__
__AsyncIPipeLong_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(AsyncIPipeLong, "DB2F3ACD-2F86-11d1-8E04-00C04FB9989A")

.comdef AsyncIPipeLong : public IUnknown

    Begin_Pull		proc :ULONG
    Finish_Pull		proc :ptr, :ptr
    Begin_Push		proc
    Finish_Push		proc
    .ends

endif

ifndef __IPipeDouble_INTERFACE_DEFINED__
__IPipeDouble_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPipeDouble, "DB2F3ACE-2F86-11d1-8E04-00C04FB9989A")

.comdef IPipeDouble : public IUnknown

    Pull		proc :ptr, :ULONG, :ptr
    _Push		proc
    .ends

endif

ifndef __AsyncIPipeDouble_INTERFACE_DEFINED__
__AsyncIPipeDouble_INTERFACE_DEFINED__ equ 1

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
__IEnumContextProps_INTERFACE_DEFINED__ equ 1

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
__IContext_INTERFACE_DEFINED__ equ 1

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
__IObjContext_INTERFACE_DEFINED__ equ 1

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
    APTTYPEQUALIFIER_NONE		= 0,
    APTTYPEQUALIFIER_IMPLICIT_MTA	= 1,
    APTTYPEQUALIFIER_NA_ON_MTA		= 2,
    APTTYPEQUALIFIER_NA_ON_STA		= 3,
    APTTYPEQUALIFIER_NA_ON_IMPLICIT_MTA = 4,
    APTTYPEQUALIFIER_NA_ON_MAINSTA	= 5,
    APTTYPEQUALIFIER_APPLICATION_STA	= 6
    }

.enum APTTYPE {
    APTTYPE_CURRENT	= -1,
    APTTYPE_STA		= 0,
    APTTYPE_MTA		= 1,
    APTTYPE_NA		= 2,
    APTTYPE_MAINSTA	= 3
    }

endif


if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum THDTYPE {
    THDTYPE_BLOCKMESSAGES	= 0,
    THDTYPE_PROCESSMESSAGES	= 1
    }

APARTMENTID		typedef DWORD

ifndef __IComThreadingInfo_INTERFACE_DEFINED__
__IComThreadingInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IComThreadingInfo, "000001ce-0000-0000-C000-000000000046")

.comdef IComThreadingInfo : public IUnknown

    GetCurrentApartmentType proc :ptr
    GetCurrentThreadType proc :ptr
    GetCurrentLogicalThreadId proc :ptr
    SetCurrentLogicalThreadId proc :REFGUID
    .ends

endif

ifndef __IProcessInitControl_INTERFACE_DEFINED__
__IProcessInitControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IProcessInitControl, "72380d55-8d2b-43a3-8513-2b6ef31434e9")

.comdef IProcessInitControl : public IUnknown

    ResetInitializerTimeout proc :DWORD
    .ends

endif

ifndef __IFastRundown_INTERFACE_DEFINED__
__IFastRundown_INTERFACE_DEFINED__ equ 1

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
__IMarshalingStream_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMarshalingStream, "D8F2F5E6-6102-4863-9F26-389A4676EFDE")

.comdef IMarshalingStream : public IStream

    GetMarshalingContextAttribute proc :CO_MARSHALING_CONTEXT_ATTRIBUTES, :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __IAgileReference_INTERFACE_DEFINED__
__IAgileReference_INTERFACE_DEFINED__ equ 1
endif

else

DEFINE_IIDX(IAgileReference, "C03F6A43-65A4-9818-987E-E0B810D2A6F2")

.comdef IAgileReference : public IUnknown

    Resolve		proc :REFIID, :ptr
    .ends

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
externdef IID_ICallbackWithNoReentrancyToApplicationSTA:GUID
endif

_OBJIDLBASE_ equ 1
endif ;; _OBJIDLBASE_

endif ;; __objidlbase_h__
