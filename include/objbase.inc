include rpc.inc
include rpcndr.inc
include stdlib.inc
ifndef _OBJBASE_H_
_OBJBASE_H_ equ <>

CLSCTX_INPROC		equ CLSCTX_INPROC_SERVER OR CLSCTX_INPROC_HANDER

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)
CLSCTX_ALL		equ CLSCTX_INPROC_SERVER OR CLSCTX_INPROC_HANDLER OR CLSCTX_LOCAL_SERVER OR CLSCTX_REMOTE_SERVER
CLSCTX_SERVER		equ CLSCTX_INPROC_SERVER OR CLSCTX_LOCAL_SERVER OR CLSCTX_REMOTE_SERVER
else
CLSCTX_ALL		equ CLSCTX_INPROC_SERVER OR CLSCTX_INPROC_HANDLER OR CLSCTX_LOCA_SERVER
CLSCTX_SERVER		equ CLSCTX_INPROC_SERVER OR CLSCTX_LOCA_SERVER
endif

REGCLS_SINGLEUSE	equ 0
REGCLS_MULTIPLEUSE	equ 1
REGCLS_MULTI_SEPARATE	equ 2
REGCLS_SUSPENDED	equ 4
REGCLS_SURROGATE	equ 8

MARSHALINTERFACE_MIN	equ 500

CWCSTORAGENAME		equ 32

STGM_DIRECT		equ 0x00000000
STGM_TRANSACTED		equ 0x00010000
STGM_SIMPLE		equ 0x08000000

STGM_READ		equ 0x00000000
STGM_WRITE		equ 0x00000001
STGM_READWRITE		equ 0x00000002

STGM_SHARE_DENY_NONE	equ 0x00000040
STGM_SHARE_DENY_READ	equ 0x00000030
STGM_SHARE_DENY_WRITE	equ 0x00000020
STGM_SHARE_EXCLUSIVE	equ 0x00000010

STGM_PRIORITY		equ 0x00040000
STGM_DELETEONRELEASE	equ 0x04000000
if (WINVER GE 400)
STGM_NOSCRATCH		equ 0x00100000
endif

STGM_CREATE		equ 0x00001000
STGM_CONVERT		equ 0x00020000
STGM_FAILIFTHERE	equ 0x00000000

STGM_NOSNAPSHOT		equ 0x00200000

ASYNC_MODE_COMPATIBILITY equ 0x00000001
ASYNC_MODE_DEFAULT	equ 0x00000000

STGTY_REPEAT		equ 0x00000100
STG_TOEND		equ 0xFFFFFFFF

STG_LAYOUT_SEQUENTIAL	equ 0x00000000
STG_LAYOUT_INTERLEAVED	equ 0x00000001

STGFMT_STORAGE		equ 0
STGFMT_NATIVE		equ 1
STGFMT_FILE		equ 3
STGFMT_ANY		equ 4
STGFMT_DOCFILE		equ 5

STGFMT_DOCUMENT		equ 0

;IRpcStubBuffer		typedef IRpcStubBuffer
;IRpcChannelBuffer	typedef IRpcChannelBuffer

include wtypes.inc
include unknwn.inc
include objidl.inc

ifndef GUID
GUID	STRUC
Data1	dd ?
Data2	dw ?
Data3	dw ?
Data4	db 8 dup(?)
GUID	ENDS
endif

ifndef DEFINE_GUID
DEFINE_GUID macro id, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8
ifdef __PE__
_&id& equ <{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}>
elseifdef INITGUID
echo id GUID {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}
else
externdef id:GUID
endif
    exitm<>
    endm
endif

ifndef __PE__
includelib uuid.lib
endif

ifndef DEFINE_GUIDS

DEFINE_GUIDS macro id, x
    DEFINE_GUID(id, \
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

externdef GUID_NULL:GUID

ifndef _mm_loadreg
_mm_loadreg macro reg, arg
    ifidn @SubStr(arg,1,1),<&>
	lea reg,@SubStr(arg,2)
    elseifdif <arg>,<reg>
	mov reg,arg
    endif
    retm<reg>
    endm
endif

ifdef _OLE32_

ifdef _OLE32PRIV_
;BOOL
wIsEqualGUID proto WINAPI rguid1:REFGUID, rguid2:REFGUID
IsEqualGUID macro rguid1, rguid2
	exitm<wIsEqualGUID(rguid1, rguid2)>
	endm
else
IsEqualGUID macro rguid1, rguid2
ifdef _WIN64
	_mm_loadreg(rcx, rguid1)
	_mm_loadreg(rdx, rguid2)
	mov rax,[rcx]
	sub rax,[rdx]
	.ifz
	    mov rax,[rcx+8]
	    sub rax,[rdx+8]
	.endif
	.if rax
else
	.if memcmp(rguid1, rguid2, GUID)
endif
	    xor eax,eax
	.else
	    inc eax
	.endif
	retm<eax>
	endm
endif
endif

IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
IsEqualCLSID macro rclsid1,rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm

ifndef INITGUID
include cguid.inc
endif

COINIT_APARTMENTTHREADED	equ 0x2
if  (_WIN32_WINNT GE 0x0400) OR defined(_WIN32_DCOM)
COINIT_MULTITHREADED		equ 0x0
COINIT_DISABLE_OLE1DDE		equ 0x4
COINIT_SPEED_OVER_MEMORY	equ 0x8
endif

.pragma comment(lib, ole32)

CoBuildVersion proto WINAPI

CoInitialize proto WINAPI \
	    pvReserved: LPVOID

CoUninitialize proto WINAPI

CoGetMalloc proto WINAPI \
	  dwMemContext: DWORD,
	      ppMalloc: LPMALLOC
;DWORD
CoGetCurrentProcess proto WINAPI

CoRegisterMallocSpy proto WINAPI \
	    pMallocSpy: LPMALLOCSPY

CoRevokeMallocSpy proto WINAPI

CoCreateStandardMalloc proto WINAPI \
		memctx: DWORD,
	      ppMalloc: ptr IMalloc

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)
CoInitializeEx proto WINAPI \
	    pvReserved: LPVOID,
	      dwCoInit: DWORD
endif

;if DBG EQ 1
;ULONG
DebugCoGetRpcFault proto WINAPI
;void
DebugCoSetRpcFault proto WINAPI \
		      : ULONG
;endif

CoGetClassObject proto WINAPI \
		rclsid: REFCLSID,
	  dwClsContext: DWORD,
	    pvReserved: LPVOID,
		  riid: REFIID,
		   ppv: LPVOID

CoRegisterClassObject proto WINAPI \
		rclsid: REFCLSID,
		  pUnk: LPUNKNOWN,
	  dwClsContext: DWORD,
		 flags: DWORD,
	  lpdwRegister: LPDWORD

CoRevokeClassObject proto WINAPI \
	    dwRegister: DWORD

CoResumeClassObjects proto WINAPI

CoSuspendClassObjects proto WINAPI

;ULONG
CoAddRefServerProcess proto WINAPI

;ULONG
CoReleaseServerProcess proto WINAPI

CoGetPSClsid proto WINAPI \
		  riid: REFIID,
		      : ptr CLSID

CoRegisterPSClsid proto WINAPI \
		  riid: REFIID,
		rclsid: REFCLSID

CoRegisterSurrogate proto WINAPI \
	    pSurrogate: LPSURROGATE

CoGetMarshalSizeMax proto WINAPI \
	       pulSize: LPDWORD,
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
	 dwDestContext: DWORD,
	 pvDestContext: LPVOID,
	     mshlflags: DWORD

CoMarshalInterface proto WINAPI \
		  pStm: LPSTREAM,
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
	 dwDestContext: DWORD,
	 pvDestContext: LPVOID,
	     mshlflags: DWORD

CoUnmarshalInterface proto WINAPI \
		  pStm: LPSTREAM,
		  riid: REFIID,
		   ppv: LPVOID

CoMarshalHresult proto WINAPI \
		  pstm: LPSTREAM,
	       hresult: HRESULT

CoUnmarshalHresult proto WINAPI \
		  pstm: LPSTREAM,
	      phresult: ptr HRESULT

CoReleaseMarshalData proto WINAPI \
		  pStm: LPSTREAM

CoDisconnectObject proto WINAPI \
		  pUnk: LPUNKNOWN,
	    dwReserved: DWORD

CoLockObjectExternal proto WINAPI \
		  pUnk: LPUNKNOWN,
		 fLock: BOOL,
   fLastUnlockReleases: BOOL

CoGetStandardMarshal proto WINAPI \
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
	 dwDestContext: DWORD,
	 pvDestContext: LPVOID,
	     mshlflags: DWORD,
	     ppMarshal: LPMARSHAL

CoGetStdMarshalEx proto WINAPI \
	     pUnkOuter: LPUNKNOWN,
	     smexflags: DWORD,
	    ppUnkInner: LPUNKNOWN

CoGetStaticMarshal proto WINAPI \
	   pUnkControl: ptr IUnknown,
		 cItfs: ULONG,
		arIIDs: ptr IID,
	       arIPIDs: ptr UUID,
	dwBindingFlags: DWORD,
	     cBindings: ULONG,
	     pBindings: LPUNKNOWN,
	    ppUnkInner: ptr IUnknown

SMEXF_SERVER		equ 0x01
SMEXF_HANDLER		equ 0x02

;BOOL
CoIsHandlerConnected proto WINAPI \
		  pUnk: LPUNKNOWN
;BOOL
CoHasStrongExternalConnections proto WINAPI \
		  pUnk: LPUNKNOWN


CoMarshalInterThreadInterfaceInStream proto WINAPI \
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
		 ppStm: LPSTREAM

CoGetInterfaceAndReleaseStream proto WINAPI \
		  pStm: LPSTREAM,
		   iid: REFIID,
		   ppv: LPVOID

CoCreateFreeThreadedMarshaler proto WINAPI \
	     punkOuter: LPUNKNOWN,
	  ppunkMarshal: LPUNKNOWN

;HINSTANCE
CoLoadLibrary proto WINAPI \
	   lpszLibName: LPOLESTR,
	     bAutoFree: BOOL
;void
CoFreeLibrary proto WINAPI \
		 hInst: HINSTANCE
;void
CoFreeAllLibraries proto WINAPI
CoFreeUnusedLibraries proto WINAPI

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

CoInitializeSecurity proto WINAPI \
	      pSecDesc: PSECURITY_DESCRIPTOR,
	      cAuthSvc: LONG,
	     asAuthSvc: ptr SOLE_AUTHENTICATION_SERVICE,
	    pReserved1: PVOID,
	  dwAuthnLevel: DWORD,
	    dwImpLevel: DWORD,
	    pReserved2: PVOID,
	dwCapabilities: DWORD,
	    pReserved3: PVOID

CoGetCallContext proto WINAPI \
		  riid: REFIID,
	   ppInterface: PVOID

CoQueryProxyBlanket proto WINAPI \
		pProxy: ptr IUnknown,
	    pwAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
	     pAuthInfo: ptr RPC_AUTH_IDENTITY_HANDLE,
	  pCapabilites: LPDWORD

CoSetProxyBlanket proto WINAPI \
		pProxy: ptr IUnknown,
	    dwAuthnSvc: DWORD,
	    dwAuthzSvc: DWORD,
      pServerPrincName: ptr OLECHAR,
	  dwAuthnLevel: DWORD,
	    dwImpLevel: DWORD,
	     pAuthInfo: RPC_AUTH_IDENTITY_HANDLE,
	dwCapabilities: DWORD

CoCopyProxy proto WINAPI \
		pProxy: ptr IUnknown,
		ppCopy: ptr IUnknown

CoQueryClientBlanket proto WINAPI \
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
		pPrivs: ptr RPC_AUTHZ_HANDLE,
	 pCapabilities: ptr DWORD

CoImpersonateClient proto WINAPI
CoRevertToSelf proto WINAPI

CoQueryAuthenticationServices proto WINAPI \
	     pcAuthSvc: ptr DWORD,
	     asAuthSvc: ptr SOLE_AUTHENTICATION_SERVICE

CoSwitchCallContext proto WINAPI \
	    pNewObject: ptr IUnknown,
	   ppOldObject: ptr IUnknown

COM_RIGHTS_EXECUTE	equ 1

endif

CoCreateInstance proto WINAPI \
		rclsid: REFCLSID,
	     pUnkOuter: LPUNKNOWN,
	  dwClsContext: DWORD,
		  riid: REFIID,
		   ppv: LPVOID

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

CoGetInstanceFromFile proto WINAPI \
	   pServerInfo: ptr COSERVERINFO,
		pClsid: ptr CLSID,
	     punkOuter: ptr IUnknown,
	      dwClsCtx: DWORD,
	       grfMode: DWORD,
	      pwszName: ptr OLECHAR,
	       dwCount: DWORD,
	      pResults: ptr MULTI_QI

CoGetInstanceFromIStorage proto WINAPI \
	   pServerInfo: ptr COSERVERINFO,
		pClsid: ptr CLSID,
	     punkOuter: PVOID,
	      dwClsCtx: DWORD,
		  pstg: PVOID,
	       dwCount: DWORD,
	      pResults: ptr MULTI_QI

CoCreateInstanceEx proto WINAPI \
		 Clsid: REFCLSID,
	     punkOuter: ptr IUnknown,
	      dwClsCtx: DWORD,
	   pServerInfo: ptr COSERVERINFO,
	       dwCount: DWORD,
	      pResults: ptr MULTI_QI

endif

if (_WIN32_WINNT GE 0x0500 ) OR defined(_WIN32_DCOM)

CoGetCancelObject proto WINAPI \
	    dwThreadId: DWORD,
		   iid: REFIID,
		 ppUnk: PVOID

CoSetCancelObject proto WINAPI \
		  pUnk: ptr IUnknown

CoCancelCall proto WINAPI \
	    dwThreadId: DWORD,
	     ulTimeout: ULONG

CoTestCancel proto WINAPI
endif

if (_WIN32_WINNT GE 0x0500 ) OR defined(_WIN32_DCOM)

CoGetClassInfo proto WINAPI \
	      pClassSpec: ptr uCLSSPEC,
		pContext: ptr QUERYCONTEXT

CoGetClassAccess proto WINAPI \
	    ppIClassAccess: ptr IClassAccess

CoGetPublishedAppInfo proto WINAPI \
	     QueryType: APPINFOTYPE,
	       lpCount: ptr DWORD,
		ppInfo: ptr PUBLISHEDAPPINFO

endif

StringFromCLSID proto WINAPI \
		rclsid: REFCLSID,
		lplpsz: LPOLESTR

CLSIDFromString proto WINAPI \
		  lpsz: LPOLESTR,
		pclsid: LPCLSID

StringFromIID proto WINAPI \
		rclsid: REFIID,
		lplpsz: LPOLESTR

IIDFromString proto WINAPI \
		  lpsz: LPOLESTR,
		 lpiid: LPIID

CoIsOle1Class proto WINAPI \
		rclsid: REFCLSID

ProgIDFromCLSID proto WINAPI \
		 clsid: REFCLSID,
	  lplpszProgID: LPOLESTR

CLSIDFromProgID proto WINAPI \
	    lpszProgID: LPCOLESTR,
	       lpclsid: LPCLSID
;int
StringFromGUID2 proto WINAPI \
		 rguid: REFGUID,
		  lpsz: LPOLESTR,
		 cbMax: SINT

CoCreateGuid proto WINAPI \
		 pguid: ptr GUID

;BOOL
CoFileTimeToDosDateTime proto WINAPI \
	    lpFileTime: ptr FILETIME,
	     lpDosDate: LPWORD,
	     lpDosTime: LPWORD
;BOOL
CoDosDateTimeToFileTime proto WINAPI \
	      nDosDate: WORD,
	      nDosTime: WORD,
	    lpFileTime: ptr FILETIME

CoFileTimeNow proto WINAPI \
	    lpFileTime: ptr FILETIME

CoRegisterMessageFilter proto WINAPI \
       lpMessageFilter: LPMESSAGEFILTER,
     lplpMessageFilter: LPMESSAGEFILTER

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

CoRegisterChannelHook proto WINAPI \
	 ExtensionUuid: REFGUID,
	  pChannelHook: ptr IChannelHook
endif

CoGetTreatAsClass proto WINAPI \
	      clsidOld: REFCLSID,
	     pClsidNew: LPCLSID

CoTreatAsClass proto WINAPI \
	      clsidOld: REFCLSID,
	      clsidNew: REFCLSID

;HRESULT
CALLBACK(LPFNGETCLASSOBJECT, :REFCLSID, :REFIID, :LPVOID)
CALLBACK(LPFNCANUNLOADNOW)

DllGetClassObject proto WINAPI \
		rclsid: REFCLSID,
		  riid: REFIID,
		   ppv: LPVOID

DllCanUnloadNow proto WINAPI

;LPVOID
CoTaskMemAlloc proto WINAPI \
		    cb: SIZE_T
;LPVOID
CoTaskMemRealloc proto WINAPI \
		    pv: LPVOID,
		    cb: SIZE_T
;void
CoTaskMemFree proto WINAPI \
		    pv: LPVOID

CreateDataAdviseHolder proto WINAPI \
	    ppDAHolder: LPDATAADVISEHOLDER

CreateDataCache proto WINAPI \
	     pUnkOuter: LPUNKNOWN,
		rclsid: REFCLSID,
		   iid: REFIID,
		   ppv: LPVOID

StgCreateDocfile proto WINAPI \
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgCreateDocfileOnILockBytes proto WINAPI \
		plkbyt: ptr ILockBytes,
	       grfMode: DWORD,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgOpenStorage proto WINAPI \
	      pwcsName: ptr OLECHAR,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgOpenStorageOnILockBytes proto WINAPI \
		plkbyt: ptr ILockBytes,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgIsStorageFile proto WINAPI \
	      pwcsName: ptr OLECHAR

StgIsStorageILockBytes proto WINAPI \
		plkbyt: ptr ILockBytes

StgSetTimes proto WINAPI \
	      lpszName: OLECHAR,
		pctime: ptr FILETIME,
		patime: ptr FILETIME,
		pmtime: ptr FILETIME

StgOpenAsyncDocfileOnIFillLockBytes proto WINAPI \
		  pflb: ptr IFillLockBytes,
	       grfMode: DWORD,
	    asyncFlags: DWORD,
	     ppstgOpen: ptr IStorage

StgGetIFillLockBytesOnILockBytes proto WINAPI \
		  pilb: ptr ILockBytes,
		 ppflb: ptr IFillLockBytes

StgGetIFillLockBytesOnFile proto WINAPI \
	      pwcsName: ptr OLECHAR,
		 ppflb: ptr IFillLockBytes


StgOpenLayoutDocfile proto WINAPI \
	    pwcsDfName: ptr OLECHAR,
	       grfMode: DWORD,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgCreateStorageEx proto WINAPI \
	      pwcsName: ptr WCHAR,
	       grfMode: DWORD,
		stgfmt: DWORD,
	      grfAttrs: DWORD,
	     reserved1: PVOID,
	     reserved2: PVOID,
		  riid: REFIID,
	  ppObjectOpen: PVOID

StgOpenStorageEx proto WINAPI \
	      pwcsName: ptr WCHAR,
	       grfMode: DWORD,
		stgfmt: DWORD,
	      grfAttrs: DWORD,
	     reserved1: PVOID,
	     reserved2: PVOID,
		  riid: REFIID,
	  ppObjectOpen: PVOID



BindMoniker proto WINAPI \
		   pmk: LPMONIKER,
		grfOpt: DWORD,
	     iidResult: REFIID,
	     ppvResult: LPVOID

CoInstall proto WINAPI \
		   pbc: ptr IBindCtx,
	       dwFlags: DWORD,
	    pClassSpec: ptr uCLSSPEC,
		pQuery: ptr QUERYCONTEXT,
	   pszCodeBase: LPWSTR

CoGetObject proto WINAPI \
	       pszName: LPCWSTR,
	  pBindOptions: ptr BIND_OPTS,
		  riid: REFIID,
		   ppv: PVOID

MkParseDisplayName proto WINAPI \
		   pbc: LPBC,
	    szUserName: LPCOLESTR,
	      pchEaten: ptr ULONG,
		  ppmk: LPMONIKER

MonikerRelativePathTo proto WINAPI \
		pmkSrc: LPMONIKER,
	       pmkDest: LPMONIKER,
	   ppmkRelPath: LPMONIKER,
	    dwReserved: BOOL

MonikerCommonPrefixWith proto WINAPI \
	       pmkThis: LPMONIKER,
	      pmkOther: LPMONIKER,
	    ppmkCommon: ptr LPMONIKER

CreateBindCtx proto WINAPI \
	      reserved: DWORD,
		  ppbc: LPBC

CreateGenericComposite proto WINAPI \
	      pmkFirst: LPMONIKER,
	       pmkRest: LPMONIKER,
	 ppmkComposite: ptr LPMONIKER

GetClassFile proto WINAPI \
	    szFilename: LPCOLESTR,
		pclsid: ptr CLSID

CreateClassMoniker proto WINAPI \
		rclsid: REFCLSID,
		  ppmk: ptr LPMONIKER

CreateFileMoniker proto WINAPI \
	  lpszPathName: LPCOLESTR,
		  ppmk: ptr LPMONIKER

CreateItemMoniker proto WINAPI \
	     lpszDelim: LPCOLESTR,
	      lpszItem: LPCOLESTR,
		  ppmk: LPMONIKER

CreateAntiMoniker proto WINAPI \
		  ppmk: ptr LPMONIKER

CreatePointerMoniker proto WINAPI \
		  punk: LPUNKNOWN,
		  ppmk: ptr LPMONIKER

GetRunningObjectTable proto WINAPI \
	      reserved: DWORD,
		 pprot: LPRUNNINGOBJECTTABLE

include urlmon.inc

CreateStdProgressIndicator proto WINAPI \
	    hwndParent: HWND,
	      pszTitle: LPCOLESTR,
	   pIbscCaller: ptr IBindStatusCallback,
		ppIbsc: ptr IBindStatusCallback

endif
