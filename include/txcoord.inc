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

ifndef __txcoord_h__
define __txcoord_h__

include transact.inc
include objidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __ITransactionResourceAsync_INTERFACE_DEFINED__
define __ITransactionResourceAsync_INTERFACE_DEFINED__


DEFINE_IIDX(ITransactionResourceAsync, "69E971F0-23CE-11cf-AD60-00AA00A74CCD")

.comdef ITransactionResourceAsync : public IUnknown

    PrepareRequest	proc :BOOL, :DWORD, :BOOL, :BOOL
    CommitRequest	proc :DWORD, :ptr
    AbortRequest	proc :ptr, :BOOL, :ptr
    TMDown		proc
   .ends

endif

ifndef __ITransactionLastResourceAsync_INTERFACE_DEFINED__
define __ITransactionLastResourceAsync_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionLastResourceAsync, "C82BD532-5B30-11d3-8A91-00C04F79EB6D")

.comdef ITransactionLastResourceAsync : public IUnknown

    DelegateCommit	proc :DWORD
    ForgetRequest	proc :ptr
   .ends

endif

ifndef __ITransactionResource_INTERFACE_DEFINED__
define __ITransactionResource_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionResource, "EE5FF7B3-4572-11d0-9452-00A0C905416E")

.comdef ITransactionResource : public IUnknown

    PrepareRequest	proc :BOOL, :DWORD, :BOOL, :BOOL
    CommitRequest	proc :DWORD, :ptr
    AbortRequest	proc :ptr, :BOOL, :ptr
    TMDown		proc
   .ends

endif

ifndef __ITransactionEnlistmentAsync_INTERFACE_DEFINED__
define __ITransactionEnlistmentAsync_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionEnlistmentAsync, "0fb15081-af41-11ce-bd2b-204c4f4f5020")

.comdef ITransactionEnlistmentAsync : public IUnknown

    PrepareRequestDone	proc :HRESULT, :ptr, :ptr
    CommitRequestDone	proc :HRESULT
    AbortRequestDone	proc :HRESULT
   .ends

endif

ifndef __ITransactionLastEnlistmentAsync_INTERFACE_DEFINED__
define __ITransactionLastEnlistmentAsync_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionLastEnlistmentAsync, "C82BD533-5B30-11d3-8A91-00C04F79EB6D")

.comdef ITransactionLastEnlistmentAsync : public IUnknown

    TransactionOutcome	proc :XACTSTAT, :ptr
   .ends

endif

ifndef __ITransactionExportFactory_INTERFACE_DEFINED__
define __ITransactionExportFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionExportFactory, "E1CF9B53-8745-11ce-A9BA-00AA006C3706")

.comdef ITransactionExportFactory : public IUnknown

    GetRemoteClassId	proc :ptr
    Create		proc :ULONG
   .ends

endif

ifndef __ITransactionImportWhereabouts_INTERFACE_DEFINED__
define __ITransactionImportWhereabouts_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionImportWhereabouts, "0141fda4-8fc0-11ce-bd18-204c4f4f5020")

.comdef ITransactionImportWhereabouts : public IUnknown

    GetWhereaboutsSize	proc :ptr
   .ends

ITransactionImportWhereabouts_RemoteGetWhereabouts_Stub proto __cdecl :ptr, :ptr, :ptr, :ptr

endif

ifndef __ITransactionExport_INTERFACE_DEFINED__
define __ITransactionExport_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionExport, "0141fda5-8fc0-11ce-bd18-204c4f4f5020")

.comdef ITransactionExport : public IUnknown

    Export		proc :ptr, :ptr
   .ends

ITransactionExport_RemoteGetTransactionCookie_Stub proto __cdecl :ptr, :ptr, :ptr, :ptr

endif

ifndef __ITransactionImport_INTERFACE_DEFINED__
define __ITransactionImport_INTERFACE_DEFINED__

DEFINE_IIDX(ITransactionImport, "E1CF9B5A-8745-11ce-A9BA-00AA006C3706")

.comdef ITransactionImport : public IUnknown

    Import		proc :ULONG
   .ends

endif

ifndef __ITipTransaction_INTERFACE_DEFINED__
define __ITipTransaction_INTERFACE_DEFINED__

DEFINE_IIDX(ITipTransaction, "17CF72D0-BAC5-11d1-B1BF-00C04FC2F3EF")

.comdef ITipTransaction : public IUnknown

    _Push		proc :ptr, :ptr
    GetTransactionUrl	proc :ptr
   .ends

endif

ifndef __ITipHelper_INTERFACE_DEFINED__
define __ITipHelper_INTERFACE_DEFINED__

DEFINE_IIDX(ITipHelper, "17CF72D1-BAC5-11d1-B1BF-00C04FC2F3EF")

.comdef ITipHelper : public IUnknown

    Pull		proc :ptr, :ptr
    PullAsync		proc :ptr, :ptr, :ptr
    GetLocalTmUrl	proc :ptr
   .ends

endif

ifndef __ITipPullSink_INTERFACE_DEFINED__
define __ITipPullSink_INTERFACE_DEFINED__

DEFINE_IIDX(ITipPullSink, "17CF72D2-BAC5-11d1-B1BF-00C04FC2F3EF")

.comdef ITipPullSink : public IUnknown

    PullComplete	proc :HRESULT
   .ends

endif

ifndef __IDtcNetworkAccessConfig_INTERFACE_DEFINED__
define __IDtcNetworkAccessConfig_INTERFACE_DEFINED__

DEFINE_IIDX(IDtcNetworkAccessConfig, "9797C15D-A428-4291-87B6-0995031A678D")

.comdef IDtcNetworkAccessConfig : public IUnknown

    GetAnyNetworkAccess proc :ptr
    SetAnyNetworkAccess proc :BOOL
    GetNetworkAdministrationAccess proc :ptr
    SetNetworkAdministrationAccess proc :BOOL
    GetNetworkTransactionAccess proc :ptr
    SetNetworkTransactionAccess proc :BOOL
    GetNetworkClientAccess proc :ptr
    SetNetworkClientAccess proc :BOOL
    GetNetworkTIPAccess proc :ptr
    SetNetworkTIPAccess proc :BOOL
    GetXAAccess		proc :ptr
    SetXAAccess		proc :BOOL
    RestartDtcService	proc
   .ends

endif

.enum AUTHENTICATION_LEVEL {
    NO_AUTHENTICATION_REQUIRED	= 0,
    INCOMING_AUTHENTICATION_REQUIRED	= 1,
    MUTUAL_AUTHENTICATION_REQUIRED	= 2
    }

ifndef __IDtcNetworkAccessConfig2_INTERFACE_DEFINED__
define __IDtcNetworkAccessConfig2_INTERFACE_DEFINED__

DEFINE_IIDX(IDtcNetworkAccessConfig2, "A7AA013B-EB7D-4f42-B41C-B2DEC09AE034")

.comdef IDtcNetworkAccessConfig2 : public IDtcNetworkAccessConfig

    GetNetworkInboundAccess proc :ptr
    GetNetworkOutboundAccess proc :ptr
    SetNetworkInboundAccess proc :BOOL
    SetNetworkOutboundAccess proc :BOOL
    GetAuthenticationLevel proc :ptr
    SetAuthenticationLevel proc :AUTHENTICATION_LEVEL
   .ends

endif

ifndef __IDtcNetworkAccessConfig3_INTERFACE_DEFINED__
define __IDtcNetworkAccessConfig3_INTERFACE_DEFINED__

DEFINE_IIDX(IDtcNetworkAccessConfig3, "76E4B4F3-2CA5-466b-89D5-FD218EE75B49")

.comdef IDtcNetworkAccessConfig3 : public IDtcNetworkAccessConfig2

    GetLUAccess		proc :ptr
    SetLUAccess		proc :BOOL
   .ends

endif

DEFINE_GUID(IID_ITransactionResourceAsync,	 0x69E971F0, 0x23CE, 0x11cf, 0xAD, 0x60, 0x00, 0xAA, 0x00, 0xA7, 0x4C, 0xCD);
DEFINE_GUID(IID_ITransactionLastResourceAsync,	 0xC82BD532, 0x5B30, 0x11D3, 0x8A, 0x91, 0x00, 0xC0, 0x4F, 0x79, 0xEB, 0x6D);
DEFINE_GUID(IID_ITransactionResource,		 0xEE5FF7B3, 0x4572, 0x11d0, 0x94, 0x52, 0x00, 0xA0, 0xC9, 0x05, 0x41, 0x6E);
DEFINE_GUID(IID_ITransactionEnlistmentAsync,	 0x0fb15081, 0xaf41, 0x11ce, 0xbd, 0x2b, 0x20, 0x4c, 0x4f, 0x4f, 0x50, 0x20);
DEFINE_GUID(IID_ITransactionLastEnlistmentAsync, 0xC82BD533, 0x5B30, 0x11D3, 0x8A, 0x91, 0x00, 0xC0, 0x4F, 0x79, 0xEB, 0x6D);
DEFINE_GUID(IID_ITransactionExportFactory,	 0xE1CF9B53, 0x8745, 0x11ce, 0xA9, 0xBA, 0x00, 0xAA, 0x00, 0x6C, 0x37, 0x06);
DEFINE_GUID(IID_ITransactionImportWhereabouts,	 0x0141fda4, 0x8fc0, 0x11ce, 0xbd, 0x18, 0x20, 0x4c, 0x4f, 0x4f, 0x50, 0x20);
DEFINE_GUID(IID_ITransactionExport,		 0x0141fda5, 0x8fc0, 0x11ce, 0xbd, 0x18, 0x20, 0x4c, 0x4f, 0x4f, 0x50, 0x20);
DEFINE_GUID(IID_ITransactionImport,		 0xE1CF9B5A, 0x8745, 0x11ce, 0xA9, 0xBA, 0x00, 0xAA, 0x00, 0x6C, 0x37, 0x06);
DEFINE_GUID(IID_ITipTransaction,		 0x17cf72d0, 0xbac5, 0x11d1, 0xb1, 0xbf, 0x0, 0xc0, 0x4f, 0xc2, 0xf3, 0xef);
DEFINE_GUID(IID_ITipHelper,			 0x17cf72d1, 0xbac5, 0x11d1, 0xb1, 0xbf, 0x0, 0xc0, 0x4f, 0xc2, 0xf3, 0xef);
DEFINE_GUID(IID_ITipPullSink,			 0x17cf72d2, 0xbac5, 0x11d1, 0xb1, 0xbf, 0x0, 0xc0, 0x4f, 0xc2, 0xf3, 0xef);
DEFINE_GUID(IID_IDtcNetworkAccessConfig,	 0x9797c15d, 0xa428, 0x4291, 0x87, 0xb6, 0x9, 0x95, 0x3, 0x1a, 0x67, 0x8d);
DEFINE_GUID(IID_IDtcNetworkAccessConfig2,	 0xa7aa013b, 0xeb7d, 0x4f42, 0xb4, 0x1c, 0xb2, 0xde, 0xc0, 0x9a, 0xe0, 0x34);

endif
endif
