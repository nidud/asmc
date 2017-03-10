include rpc.inc
include rpcndr.inc
include stdlib.inc
.xlist
;;
;; Component object model defintions.
;;
ifndef _OBJBASE_H_
_OBJBASE_H_ equ 1

;;#include <pshpack8.h>

ifdef __PE__
option	dllimport:<ole32>
endif

;;***** Interface Declaration **********************************************

;;
;;	These are macros for declaring interfaces.  They exist so that
;;	a single definition of the interface is simulataneously a proper
;;	declaration of the interface structures (C++ abstract classes)
;;	for both C and C++.
;;
;;	DECLARE_INTERFACE(iface) is used to declare an interface that does
;;	not derive from a base interface.
;;	DECLARE_INTERFACE_(iface, baseiface) is used to declare an interface
;;	that does derive from a base interface.
;;
;;	By default if the source file has a .c extension the C version of
;;	the interface declaratations will be expanded; if it has a .cpp
;;	extension the C++ version will be expanded. if you want to force
;;	the C version expansion even though the source file has a .cpp
;;	extension, then define the macro "CINTERFACE".
;;	eg.	cl -DCINTERFACE file.cpp
;;
;;	Example Interface declaration:
;;
;;	    #undef  INTERFACE
;;	    #define INTERFACE	IClassFactory
;;
;;	    DECLARE_INTERFACE_(IClassFactory, IUnknown)
;;	    {
;;		;; *** IUnknown methods ***
;;		STDMETHOD(QueryInterface) (THIS_
;;					  REFIID riid,
;;					  LPVOID * ppvObj) PURE;
;;		STDMETHOD_(ULONG,AddRef) (THIS) PURE;
;;		STDMETHOD_(ULONG,Release) (THIS) PURE;
;;
;;		;; *** IClassFactory methods ***
;;		STDMETHOD(CreateInstance) (THIS_
;;					  LPUNKNOWN pUnkOuter,
;;					  REFIID riid,
;;					  LPVOID * ppvObject) PURE;
;;	    };
;;
;;	Example C++ expansion:
;;
;;	    struct FAR IClassFactory : public IUnknown
;;	    {
;;		virtual HRESULT STDMETHODCALLTYPE QueryInterface(
;;						    IID FAR& riid,
;;						    LPVOID * ppvObj) = 0;
;;		virtual HRESULT STDMETHODCALLTYPE AddRef(void) = 0;
;;		virtual HRESULT STDMETHODCALLTYPE Release(void) = 0;
;;		virtual HRESULT STDMETHODCALLTYPE CreateInstance(
;;						LPUNKNOWN pUnkOuter,
;;						IID FAR& riid,
;;						LPVOID * ppvObject) = 0;
;;	    };
;;
;;	    NOTE: Our documentation says '#define interface class' but we use
;;	    'struct' instead of 'class' to keep a lot of 'public:' lines
;;	    out of the interfaces.  The 'FAR' forces the 'this' pointers to
;;	    be far, which is what we need.
;;
;;	Example C expansion:
;;
;;	    typedef struct IClassFactory
;;	    {
;;		const struct IClassFactoryVtbl * lpVtbl;
;;	    } IClassFactory;
;;
;;	    typedef struct IClassFactoryVtbl IClassFactoryVtbl;
;;
;;	    struct IClassFactoryVtbl
;;	    {
;;		HRESULT (STDMETHODCALLTYPE * QueryInterface) (
;;						    IClassFactory * This,
;;						    IID * riid,
;;						    LPVOID * ppvObj) ;
;;		HRESULT (STDMETHODCALLTYPE * AddRef) (IClassFactory * This) ;
;;		HRESULT (STDMETHODCALLTYPE * Release) (IClassFactory * This) ;
;;		HRESULT (STDMETHODCALLTYPE * CreateInstance) (
;;						    IClassFactory * This,
;;						    LPUNKNOWN pUnkOuter,
;;						    IID * riid,
;;						    LPVOID * ppvObject);
;;		HRESULT (STDMETHODCALLTYPE * LockServer) (
;;						    IClassFactory * This,
;;						    BOOL fLock);
;;	    };
;;

;;***** Additional basic types *********************************************

CLSCTX_INPROC		equ CLSCTX_INPROC_SERVER OR CLSCTX_INPROC_HANDER

;; With DCOM, CLSCTX_REMOTE_SERVER should be included
if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM) ;; DCOM
CLSCTX_ALL		equ CLSCTX_INPROC_SERVER OR CLSCTX_INPROC_HANDLER OR CLSCTX_LOCAL_SERVER OR CSCTX_REMOTE_SERVER
CLSCTX_SERVER		equ CLSCTX_INPROC_SERVER OR CLSCTX_LOCAL_SERVER OR CSCTX_REMOTE_SERVER
else
CLSCTX_ALL		equ CLSCTX_INPROC_SERVER OR CLSCTX_INPROC_HANDLER OR CLSCTX_LOCA_SERVER
CLSCTX_SERVER		equ CLSCTX_INPROC_SERVER OR CLSCTX_LOCA_SERVER
endif

;;
;; class registration flags; passed to CoRegisterClassObject
;;
REGCLS_SINGLEUSE	equ 0	;; class object only generates one instance
REGCLS_MULTIPLEUSE	equ 1	;; same class object genereates multiple inst.
				;; and local automatically goes into inproc tbl.
REGCLS_MULTI_SEPARATE	equ 2	;; multiple use, but separate control over each
				;; context.
REGCLS_SUSPENDED	equ 4	;; register is as suspended, will be activated
				;; when app calls CoResumeClassObjects
REGCLS_SURROGATE	equ 8	;; must be used when a surrogate process
				;; is registering a class object that will be
				;; loaded in the surrogate
				;; interface marshaling definitions

MARSHALINTERFACE_MIN	equ 500 ;; minimum number of bytes for interface marshl


;;
;; Common typedefs for paramaters used in Storage API's, gleamed from storage.h
;; Also contains Storage error codes, which should be moved into the storage
;; idl files.
;;


CWCSTORAGENAME		equ 32

;; Storage instantiation modes
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
endif ;; WINVER

STGM_CREATE		equ 0x00001000
STGM_CONVERT		equ 0x00020000
STGM_FAILIFTHERE	equ 0x00000000

STGM_NOSNAPSHOT		equ 0x00200000

;;  flags for internet asyncronous and layout docfile
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

;; This is a legacy define to allow old component to builds
STGFMT_DOCUMENT		equ 0

;; here is where we pull in the MIDL generated headers for the interfaces
;IRpcStubBuffer		typedef IRpcStubBuffer
;IRpcChannelBuffer	typedef IRpcChannelBuffer

include wtypes.inc
include unknwn.inc
include objidl.inc
.xlist

;; macros to define byte pattern for a GUID.
;;	Example: DEFINE_GUID(GUID_XXX, a, b, c, ...);
;;
;; Each dll/exe must initialize the GUIDs once.	 This is done in one of
;; two ways.  If you are not using precompiled headers for the file(s) which
;; initializes the GUIDs, define INITGUID before including objbase.h.  This
;; is how OLE builds the initialized versions of the GUIDs which are included
;; in ole2.lib.	 The GUIDs in ole2.lib are all defined in the same text
;; segment GUID_TEXT.
;;
;; The alternative (which some versions of the compiler don't handle properly;
;; they wind up with the initialized GUIDs in a data, not a text segment),
;; is to use a precompiled version of objbase.h and then include initguid.h
;; after objbase.h followed by one or more of the guid defintion files.

ifndef GUID
GUID		STRUC
Data1		dd ?
Data2		dw ?
Data3		dw ?
Data4		db 8 dup(?)
GUID		ENDS
endif

DEFINE_GUID macro name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8
	exitm <externdef name:GUID>
	endm

externdef GUID_NULL:GUID

ifdef _OLE32_

ifdef _OLE32PRIV_
;BOOL
wIsEqualGUID proto _CType rguid1:REFGUID, rguid2:REFGUID
IsEqualGUID macro rguid1, rguid2
	exitm<wIsEqualGUID(rguid1, rguid2)>
	endm
else
IsEqualGUID macro rguid1, rguid2
	.if memcmp(rguid1, rguid2, sizeof(GUID))
	    xor eax,eax
	.else
	    inc eax
	.endif
	exitm<eax>
	endm
endif	;;  _OLE32PRIV_
endif	;;  _OLE32_

IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
IsEqualCLSID macro rclsid1,rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm

ifndef INITGUID
include cguid.inc
.xlist
endif

;; COM initialization flags; passed to CoInitialize.

COINIT_APARTMENTTHREADED	equ 0x2 ;; Apartment model
if  (_WIN32_WINNT GE 0x0400) OR defined(_WIN32_DCOM)
;; These constants are only valid on Windows NT 4.0
COINIT_MULTITHREADED		equ 0x0 ;; OLE calls objects on any thread.
COINIT_DISABLE_OLE1DDE		equ 0x4 ;; Don't use DDE for Ole1 support.
COINIT_SPEED_OVER_MEMORY	equ 0x8 ;; Trade memory for speed.
endif

;;***** STD Object API Prototypes ****************************************

CoBuildVersion proto _CType

;; init/uninit

CoInitialize proto _CType \
	    pvReserved: LPVOID

CoUninitialize proto _CType

CoGetMalloc proto _CType \
	  dwMemContext: DWORD,
	      ppMalloc: LPMALLOC
;DWORD
CoGetCurrentProcess proto _CType

CoRegisterMallocSpy proto _CType \
	    pMallocSpy: LPMALLOCSPY

CoRevokeMallocSpy proto _CType

CoCreateStandardMalloc proto _CType \
		memctx: DWORD,
	      ppMalloc: ptr IMalloc

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM) ;; DCOM
CoInitializeEx proto _CType \
	    pvReserved: LPVOID,
	      dwCoInit: DWORD
endif ;; DCOM

;if DBG EQ 1
;ULONG
DebugCoGetRpcFault proto _CType
;void
DebugCoSetRpcFault proto _CType \
		      : ULONG
;endif

;; register/revoke/get class objects

CoGetClassObject proto _CType \
		rclsid: REFCLSID,
	  dwClsContext: DWORD,
	    pvReserved: LPVOID,
		  riid: REFIID,
		   ppv: LPVOID

CoRegisterClassObject proto _CType \
		rclsid: REFCLSID,
		  pUnk: LPUNKNOWN,
	  dwClsContext: DWORD,
		 flags: DWORD,
	  lpdwRegister: LPDWORD

CoRevokeClassObject proto _CType \
	    dwRegister: DWORD

CoResumeClassObjects proto _CType

CoSuspendClassObjects proto _CType

;ULONG
CoAddRefServerProcess proto _CType

;ULONG
CoReleaseServerProcess proto _CType

CoGetPSClsid proto _CType \
		  riid: REFIID,
		      : ptr CLSIDpClsid

CoRegisterPSClsid proto _CType \
		  riid: REFIID,
		rclsid: REFCLSID

;; Registering surrogate processes

CoRegisterSurrogate proto _CType \
	    pSurrogate: LPSURROGATE

;; marshaling interface pointers

CoGetMarshalSizeMax proto _CType \
	       pulSize: LPDWORD,
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
	 dwDestContext: DWORD,
	 pvDestContext: LPVOID,
	     mshlflags: DWORD

CoMarshalInterface proto _CType \
		  pStm: LPSTREAM,
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
	 dwDestContext: DWORD,
	 pvDestContext: LPVOID,
	     mshlflags: DWORD

CoUnmarshalInterface proto _CType \
		  pStm: LPSTREAM,
		  riid: REFIID,
		   ppv: LPVOID

CoMarshalHresult proto _CType \
		  pstm: LPSTREAM,
	       hresult: HRESULT

CoUnmarshalHresult proto _CType \
		  pstm: LPSTREAM,
	      phresult: ptr HRESULT

CoReleaseMarshalData proto _CType \
		  pStm: LPSTREAM

CoDisconnectObject proto _CType \
		  pUnk: LPUNKNOWN,
	    dwReserved: DWORD

CoLockObjectExternal proto _CType \
		  pUnk: LPUNKNOWN,
		 fLock: BOOL,
   fLastUnlockReleases: BOOL

CoGetStandardMarshal proto _CType \
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
	 dwDestContext: DWORD,
	 pvDestContext: LPVOID,
	     mshlflags: DWORD,
	     ppMarshal: LPMARSHAL


CoGetStdMarshalEx proto _CType \
	     pUnkOuter: LPUNKNOWN,
	     smexflags: DWORD,
	    ppUnkInner: LPUNKNOWN

CoGetStaticMarshal proto _CType \
	   pUnkControl: ptr IUnknown,
		 cItfs: ULONG,
		arIIDs: ptr IID,
	       arIPIDs: ptr UUID,
	dwBindingFlags: DWORD,
	     cBindings: ULONG,
	     pBindings: LPUNKNOWN,
	    ppUnkInner: ptr IUnknown

;; flags for CoGetStdMarshalEx
SMEXF_SERVER		equ 0x01
SMEXF_HANDLER		equ 0x02


;BOOL
CoIsHandlerConnected proto _CType \
		  pUnk: LPUNKNOWN
;BOOL
CoHasStrongExternalConnections proto _CType \
		  pUnk: LPUNKNOWN

;; Apartment model inter-thread interface passing helpers

CoMarshalInterThreadInterfaceInStream proto _CType \
		  riid: REFIID,
		  pUnk: LPUNKNOWN,
		 ppStm: LPSTREAM

CoGetInterfaceAndReleaseStream proto _CType \
		  pStm: LPSTREAM,
		   iid: REFIID,
		   ppv: LPVOID

CoCreateFreeThreadedMarshaler proto _CType \
	     punkOuter: LPUNKNOWN,
	  ppunkMarshal: LPUNKNOWN

;; dll loading helpers; keeps track of ref counts and unloads all on exit

;HINSTANCE
CoLoadLibrary proto _CType \
	   lpszLibName: LPOLESTR,
	     bAutoFree: BOOL
;void
CoFreeLibrary proto _CType \
		 hInst: HINSTANCE
;void
CoFreeAllLibraries proto _CType
CoFreeUnusedLibraries proto _CType


if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM) ;; DCOM

;; Call Security.

CoInitializeSecurity proto _CType \
	      pSecDesc: PSECURITY_DESCRIPTOR,
	      cAuthSvc: LONG,
	     asAuthSvc: ptr SOLE_AUTHENTICATION_SERVICE,
	    pReserved1: PVOID,
	  dwAuthnLevel: DWORD,
	    dwImpLevel: DWORD,
	    pReserved2: PVOID,
	dwCapabilities: DWORD,
	    pReserved3: PVOID

CoGetCallContext proto _CType \
		  riid: REFIID,
	   ppInterface: PVOID

CoQueryProxyBlanket proto _CType \
		pProxy: ptr IUnknown,
	    pwAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
	     pAuthInfo: ptr RPC_AUTH_IDENTITY_HANDLE,
	  pCapabilites: LPDWORD

CoSetProxyBlanket proto _CType \
		pProxy: ptr IUnknown,
	    dwAuthnSvc: DWORD,
	    dwAuthzSvc: DWORD,
      pServerPrincName: ptr OLECHAR,
	  dwAuthnLevel: DWORD,
	    dwImpLevel: DWORD,
	     pAuthInfo: RPC_AUTH_IDENTITY_HANDLE,
	dwCapabilities: DWORD

CoCopyProxy proto _CType \
		pProxy: ptr IUnknown,
		ppCopy: ptr IUnknown

CoQueryClientBlanket proto _CType \
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
		pPrivs: ptr RPC_AUTHZ_HANDLE,
	 pCapabilities: ptr DWORD

CoImpersonateClient proto _CType
CoRevertToSelf proto _CType

CoQueryAuthenticationServices proto _CType \
	     pcAuthSvc: ptr DWORD,
	     asAuthSvc: ptr SOLE_AUTHENTICATION_SERVICE

CoSwitchCallContext proto _CType \
	    pNewObject: ptr IUnknown,
	   ppOldObject: ptr IUnknown

COM_RIGHTS_EXECUTE	equ 1

endif ;; DCOM

;; helper for creating instances

CoCreateInstance proto _CType \
		rclsid: REFCLSID,
	     pUnkOuter: LPUNKNOWN,
	  dwClsContext: DWORD,
		  riid: REFIID,
		   ppv: LPVOID


if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)

CoGetInstanceFromFile proto _CType \
	   pServerInfo: ptr COSERVERINFO,
		pClsid: ptr CLSID,
	     punkOuter: ptr IUnknown,
	      dwClsCtx: DWORD,
	       grfMode: DWORD,
	      pwszName: ptr OLECHAR,
	       dwCount: DWORD,
	      pResults: ptr MULTI_QI

CoGetInstanceFromIStorage proto _CType \
	   pServerInfo: ptr COSERVERINFO,
		pClsid: ptr CLSID,
	     punkOuter: PVOID,
	      dwClsCtx: DWORD,
		  pstg: PVOID,
	       dwCount: DWORD,
	      pResults: ptr MULTI_QI

CoCreateInstanceEx proto _CType \
		 Clsid: REFCLSID,
	     punkOuter: PVOID,
	      dwClsCtx: DWORD,
	   pServerInfo: ptr COSERVERINFO,
	       dwCount: DWORD,
	      pResults: ptr MULTI_QI

endif ;; DCOM

;; Call related APIs
if (_WIN32_WINNT GE 0x0500 ) OR defined(_WIN32_DCOM) ;; DCOM


CoGetCancelObject proto _CType \
	    dwThreadId: DWORD,
		   iid: REFIID,
		 ppUnk: PVOID

CoSetCancelObject proto _CType \
		  pUnk: ptr IUnknown

CoCancelCall proto _CType \
	    dwThreadId: DWORD

CoTestCancel proto _CType
endif

;; DS related APIs

;; Type definitions for these APIs can be found in wtypes.{idl,h}.

if (_WIN32_WINNT GE 0x0500 ) OR defined(_WIN32_DCOM) ;; DCOM

CoGetClassInfo proto _CType \
	      pClassSpec: ptr uCLSSPEC,
		pContext: ptr QUERYCONTEXT

;; the following api returns a class access interface pointer

CoGetClassAccess proto _CType \
	    ppIClassAccess: ptr IClassAccess

;; The following API is for shell32's use only

CoGetPublishedAppInfo proto _CType \
	     QueryType: APPINFOTYPE,
	       lpCount: ptr DWORD,
		ppInfo: ptr PUBLISHEDAPPINFO

endif

;; other helpers

StringFromCLSID proto _CType \
		rclsid: REFCLSID,
		lplpsz: LPOLESTR

CLSIDFromString proto _CType \
		  lpsz: LPOLESTR,
		pclsid: LPCLSID

StringFromIID proto _CType \
		rclsid: REFIID,
		lplpsz: LPOLESTR

IIDFromString proto _CType \
		  lpsz: LPOLESTR,
		 lpiid: LPIID

CoIsOle1Class proto _CType \
		rclsid: REFCLSID

ProgIDFromCLSID proto _CType \
		 clsid: REFCLSID,
	  lplpszProgID: LPOLESTR

CLSIDFromProgID proto _CType \
	    lpszProgID: LPCOLESTR,
	       lpclsid: LPCLSID
;int
StringFromGUID2 proto _CType \
		 rguid: REFGUID,
		  lpsz: LPOLESTR,
		 cbMax: SINT

CoCreateGuid proto _CType \
		 pguid: ptr GUID

;BOOL
CoFileTimeToDosDateTime proto _CType \
	    lpFileTime: ptr FILETIME,
	     lpDosDate: LPWORD,
	     lpDosTime: LPWORD
;BOOL
CoDosDateTimeToFileTime proto _CType \
	      nDosDate: WORD,
	      nDosTime: WORD,
	    lpFileTime: ptr FILETIME

CoFileTimeNow proto _CType \
	    lpFileTime: ptr FILETIME

CoRegisterMessageFilter proto _CType \
       lpMessageFilter: LPMESSAGEFILTER,
     lplpMessageFilter: LPMESSAGEFILTER

if (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM) ;; DCOM

CoRegisterChannelHook proto _CType \
	 ExtensionUuid: REFGUID,
	  pChannelHook: ptr IChannelHook
endif ;; DCOM


;; TreatAs APIS

CoGetTreatAsClass proto _CType \
	      clsidOld: REFCLSID,
	     pClsidNew: LPCLSID

CoTreatAsClass proto _CType \
	      clsidOld: REFCLSID,
	      clsidNew: REFCLSID


;; the server dlls must define their DllGetClassObject and DllCanUnloadNow
;; to match these; the typedefs are located here to ensure all are changed at
;; the same time.
;;

;HRESULT
LPFNGETCLASSOBJECT_T typedef proto _CType \
		      : REFCLSID,
		      : REFIID,
		      : LPVOID
LPFNGETCLASSOBJECT typedef ptr LPFNGETCLASSOBJECT_T


LPFNCANUNLOADNOW_T typedef proto _CType
LPFNCANUNLOADNOW typedef ptr LPFNCANUNLOADNOW_T

DllGetClassObject proto _CType \
		rclsid: REFCLSID,
		  riid: REFIID,
		   ppv: LPVOID

DllCanUnloadNow proto _CType


;;***** Default Memory Allocation *****************************************
;LPVOID
CoTaskMemAlloc proto _CType \
		    cb: ULONG
;LPVOID
CoTaskMemRealloc proto _CType \
		    pv: LPVOID,
		    cb: ULONG
;void
CoTaskMemFree proto _CType \
		    pv: LPVOID

;;***** DV APIs **********************************************************


CreateDataAdviseHolder proto _CType \
	    ppDAHolder: LPDATAADVISEHOLDER

CreateDataCache proto _CType \
	     pUnkOuter: LPUNKNOWN,
		rclsid: REFCLSID,
		   iid: REFIID,
		   ppv: LPVOID




;;***** Storage API Prototypes *******************************************

StgCreateDocfile proto _CType \
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgCreateDocfileOnILockBytes proto _CType \
		plkbyt: ptr ILockBytes,
	       grfMode: DWORD,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgOpenStorage proto _CType \
	      pwcsName: ptr OLECHAR,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgOpenStorageOnILockBytes proto _CType \
		plkbyt: ptr ILockBytes,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgIsStorageFile proto _CType \
	      pwcsName: ptr OLECHAR

StgIsStorageILockBytes proto _CType \
		plkbyt: ptr ILockBytes

StgSetTimes proto _CType \
	      lpszName: OLECHAR,
		pctime: ptr FILETIME,
		patime: ptr FILETIME,
		pmtime: ptr FILETIME

StgOpenAsyncDocfileOnIFillLockBytes proto _CType \
		  pflb: ptr IFillLockBytes,
	       grfMode: DWORD,
	    asyncFlags: DWORD,
	     ppstgOpen: ptr IStorage

StgGetIFillLockBytesOnILockBytes proto _CType \
		  pilb: ptr ILockBytes,
		 ppflb: ptr IFillLockBytes

StgGetIFillLockBytesOnFile proto _CType \
	      pwcsName: ptr OLECHAR,
		 ppflb: ptr IFillLockBytes


StgOpenLayoutDocfile proto _CType \
	    pwcsDfName: ptr OLECHAR,
	       grfMode: DWORD,
	      reserved: DWORD,
	     ppstgOpen: ptr IStorage

StgCreateStorageEx proto _CType \
	      pwcsName: ptr WCHAR,
	       grfMode: DWORD,
		stgfmt: DWORD,
	      grfAttrs: DWORD,
	     reserved1: PVOID,
	     reserved2: PVOID,
		  riid: REFIID,
	  ppObjectOpen: PVOID

StgOpenStorageEx proto _CType \
	      pwcsName: ptr WCHAR,
	       grfMode: DWORD,
		stgfmt: DWORD,
	      grfAttrs: DWORD,
	     reserved1: PVOID,
	     reserved2: PVOID,
		  riid: REFIID,
	  ppObjectOpen: PVOID


;;
;;  Moniker APIs
;;

BindMoniker proto _CType \
		   pmk: LPMONIKER,
		grfOpt: DWORD,
	     iidResult: REFIID,
	     ppvResult: LPVOID

CoInstall proto _CType \
		   pbc: ptr IBindCtx,
	       dwFlags: DWORD,
	    pClassSpec: ptr uCLSSPEC,
		pQuery: ptr QUERYCONTEXT,
	   pszCodeBase: LPWSTR

CoGetObject proto _CType \
	       pszName: LPCWSTR,
	  pBindOptions: ptr BIND_OPTS,
		  riid: REFIID,
		   ppv: PVOID

MkParseDisplayName proto _CType \
		   pbc: LPBC,
	    szUserName: LPCOLESTR,
	      pchEaten: ptr ULONG,
		  ppmk: LPMONIKER

MonikerRelativePathTo proto _CType \
		pmkSrc: LPMONIKER,
	       pmkDest: LPMONIKER,
	   ppmkRelPath: LPMONIKER,
	    dwReserved: BOOL

MonikerCommonPrefixWith proto _CType \
	       pmkThis: LPMONIKER,
	      pmkOther: LPMONIKER,
	    ppmkCommon: ptr LPMONIKER

CreateBindCtx proto _CType \
	      reserved: DWORD,
		  ppbc: LPBC

CreateGenericComposite proto _CType \
	      pmkFirst: LPMONIKER,
	       pmkRest: LPMONIKER,
	 ppmkComposite: ptr LPMONIKER

GetClassFile proto _CType \
	    szFilename: LPCOLESTR,
		pclsid: ptr CLSID

CreateClassMoniker proto _CType \
		rclsid: REFCLSID,
		  ppmk: ptr LPMONIKER

CreateFileMoniker proto _CType \
	  lpszPathName: LPCOLESTR,
		  ppmk: ptr LPMONIKER

CreateItemMoniker proto _CType \
	     lpszDelim: LPCOLESTR,
	      lpszItem: LPCOLESTR,
		  ppmk: LPMONIKER

CreateAntiMoniker proto _CType \
		  ppmk: ptr LPMONIKER

CreatePointerMoniker proto _CType \
		  punk: LPUNKNOWN,
		  ppmk: ptr LPMONIKER

GetRunningObjectTable proto _CType \
	      reserved: DWORD,
		 pprot: LPRUNNINGOBJECTTABLE

include urlmon.inc
.xlist
;;
;; Standard Progress Indicator impolementation
;;
;?
CreateStdProgressIndicator proto _CType \
	    hwndParent: HWND,
	      pszTitle: LPCOLESTR,
	   pIbscCaller: ptr IBindStatusCallback,
		ppIbsc: ptr IBindStatusCallback

endif	   ;; __OBJBASE_H__

.list
