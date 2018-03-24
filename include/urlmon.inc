include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __urlmon_h__
__urlmon_h__ equ <>
.xlist

ifndef __IPersistMoniker_FWD_DEFINED__
__IPersistMoniker_FWD_DEFINED__ equ 1
endif

ifndef __IBindProtocol_FWD_DEFINED__
__IBindProtocol_FWD_DEFINED__ equ 1
endif

ifndef __IBinding_FWD_DEFINED__
__IBinding_FWD_DEFINED__ equ 1
endif

ifndef __IBindStatusCallback_FWD_DEFINED__
__IBindStatusCallback_FWD_DEFINED__ equ 1
endif

ifndef __IAuthenticate_FWD_DEFINED__
__IAuthenticate_FWD_DEFINED__ equ 1
endif

ifndef __IHttpNegotiate_FWD_DEFINED__
__IHttpNegotiate_FWD_DEFINED__ equ 1
endif

ifndef __IWindowForBindingUI_FWD_DEFINED__
__IWindowForBindingUI_FWD_DEFINED__ equ 1
endif

ifndef __ICodeInstall_FWD_DEFINED__
__ICodeInstall_FWD_DEFINED__ equ 1
endif

ifndef __IWinInetInfo_FWD_DEFINED__
__IWinInetInfo_FWD_DEFINED__ equ 1
endif

ifndef __IHttpSecurity_FWD_DEFINED__
__IHttpSecurity_FWD_DEFINED__ equ 1
endif

ifndef __IWinInetHttpInfo_FWD_DEFINED__
__IWinInetHttpInfo_FWD_DEFINED__ equ 1
endif

ifndef __IBindHost_FWD_DEFINED__
__IBindHost_FWD_DEFINED__ equ 1
endif

ifndef __IInternet_FWD_DEFINED__
__IInternet_FWD_DEFINED__ equ 1
endif

ifndef __IInternetBindInfo_FWD_DEFINED__
__IInternetBindInfo_FWD_DEFINED__ equ 1
endif

ifndef __IInternetProtocolRoot_FWD_DEFINED__
__IInternetProtocolRoot_FWD_DEFINED__ equ 1
endif

ifndef __IInternetProtocol_FWD_DEFINED__
__IInternetProtocol_FWD_DEFINED__ equ 1
endif

ifndef __IInternetProtocolSink_FWD_DEFINED__
__IInternetProtocolSink_FWD_DEFINED__ equ 1
endif

ifndef __IInternetSession_FWD_DEFINED__
__IInternetSession_FWD_DEFINED__ equ 1
endif

ifndef __IInternetThreadSwitch_FWD_DEFINED__
__IInternetThreadSwitch_FWD_DEFINED__ equ 1
endif

ifndef __IInternetPriority_FWD_DEFINED__
__IInternetPriority_FWD_DEFINED__ equ 1
endif

ifndef __IInternetProtocolInfo_FWD_DEFINED__
__IInternetProtocolInfo_FWD_DEFINED__ equ 1
endif

ifndef __IInternetSecurityMgrSite_FWD_DEFINED__
__IInternetSecurityMgrSite_FWD_DEFINED__ equ 1
endif

ifndef __IInternetSecurityManager_FWD_DEFINED__
__IInternetSecurityManager_FWD_DEFINED__ equ 1
endif

ifndef __IInternetHostSecurityManager_FWD_DEFINED__
__IInternetHostSecurityManager_FWD_DEFINED__ equ 1
endif

ifndef __IInternetZoneManager_FWD_DEFINED__
__IInternetZoneManager_FWD_DEFINED__ equ 1
endif

ifndef __ISoftDistExt_FWD_DEFINED__
__ISoftDistExt_FWD_DEFINED__ equ 1
endif

ifndef __IDataFilter_FWD_DEFINED__
__IDataFilter_FWD_DEFINED__ equ 1
endif

ifndef __IEncodingFilterFactory_FWD_DEFINED__
__IEncodingFilterFactory_FWD_DEFINED__ equ 1
endif

include objidl.inc
include oleidl.inc
include servprov.inc
include msxml.inc
.xlist

;void *
MIDL_user_allocate proto WINAPI :size_t
;void
MIDL_user_free proto WINAPI :PVOID



BINDF_DONTUSECACHE	equ <BINDF_GETNEWESTVERSION>
BINDF_DONTPUTINCACHE	equ <BINDF_NOWRITECACHE>
BINDF_NOCOPYDATA	equ <BINDF_PULLDATA>
PI_DOCFILECLSIDLOOKUP	equ <PI_CLSIDOOKUP>
externdef		IID_IAsyncMoniker:IID
externdef		CLSID_StdURLMoniker:IID
externdef		CLSID_HttpProtocol:IID
externdef		CLSID_FtpProtocol:IID
externdef		CLSID_GopherProtocol:IID
externdef		CLSID_HttpSProtocol:IID
externdef		CLSID_FileProtocol:IID
externdef		CLSID_MkProtocol:IID
externdef		CLSID_StdURLProtocol:IID
externdef		CLSID_UrlMkBindCtx:IID
externdef		CLSID_StdEncodingFilterFac:IID
externdef		CLSID_DeCompMimeFilter:IID
externdef		CLSID_CdlProtocol:IID
externdef		CLSID_ClassInstallFilter:IID
externdef		IID_IAsyncBindCtx:IID

SZ_URLCONTEXT		equ <OLESTR("URL Context")>
SZ_ASYNC_CALLEE		equ <OLESTR("AsyncCallee")>
MKSYS_URLMONIKER	equ 6

;STDAPI
CreateURLMoniker proto WINAPI \
		pMkCtx: LPMONIKER,
		 szURL: LPCWSTR,
		  ppmk: ptr LPMONIKER

;STDAPI
GetClassURL proto WINAPI \
		 szURL: LPCWSTR,
		pClsID: ptr CLSID

;STDAPI
CreateAsyncBindCtx proto WINAPI \
	      reserved: DWORD,
		 pBSCb: ptr IBindStatusCallback,
		pEFetc: ptr IEnumFORMATETC,
		  ppBC: ptr IBindCtx

;STDAPI
CreateAsyncBindCtxEx proto WINAPI \
		   pbc: ptr IBindCtx,
	     dwOptions: DWORD,
		 pBSCb: ptr IBindStatusCallback,
		 pEnum: ptr IEnumFORMATETC,
		  ppBC: ptr IBindCtx,
	      reserved: DWORD

;STDAPI
MkParseDisplayNameEx proto WINAPI \
		   pbc: ptr IBindCtx,
	 szDisplayName: LPCWSTR,
	      pchEaten: ptr ULONG,
		  ppmk: ptr LPMONIKER

;STDAPI
RegisterBindStatusCallback proto WINAPI \
		   pBC: LPBC,
		 pBSCb: ptr IBindStatusCallback,
	    ppBSCBPrev: ptr IBindStatusCallback,
	    dwReserved: DWORD

;STDAPI
RevokeBindStatusCallback proto WINAPI \
		   pBC: LPBC,
		 pBSCb: ptr IBindStatusCallback

;STDAPI
GetClassFileOrMime proto WINAPI \
		   pBC: LPBC,
	    szFilename: LPCWSTR,
	       pBuffer: LPVOID,
		cbSize: DWORD,
		szMime: LPCWSTR,
	    dwReserved: DWORD,
		pclsid: ptr CLSID

;STDAPI
IsValidURL proto WINAPI \
		   pBC: LPBC,
		 szURL: LPCWSTR,
	    dwReserved: DWORD

;STDAPI
CoGetClassObjectFromURL proto WINAPI \
	      rCLASSID: REFCLSID,
		szCODE: LPCWSTR,
       dwFileVersionMS: DWORD,
       dwFileVersionLS: DWORD,
		szTYPE: LPCWSTR,
	      pBindCtx: LPBINDCTX,
	  dwClsContext: DWORD,
	    pvReserved: LPVOID,
		  riid: REFIID,
		   ppv: ptr LPVOID


;STDAPI
IsAsyncMoniker proto WINAPI \
		   pmk: ptr IMoniker

;STDAPI
CreateURLBinding proto WINAPI \
	       lpszUrl: LPCWSTR,
		   pbc: ptr IBindCtx,
		 ppBdg: ptr IBinding


;STDAPI
RegisterMediaTypes proto WINAPI \
		ctypes: UINT,
	     rgszTypes: LPCSTR,
	     rgcfTypes: ptr CLIPFORMAT

;STDAPI
FindMediaType proto WINAPI \
	     rgszTypes: LPCSTR,
	     rgcfTypes: ptr CLIPFORMAT

;STDAPI
CreateFormatEnumerator proto WINAPI \
	       cfmtetc: UINT,
	      rgfmtetc: ptr FORMATETC,
	  ppenumfmtetc: ptr IEnumFORMATETC

;STDAPI
RegisterFormatEnumerator proto WINAPI \
		   pBC: LPBC,
		pEFetc: ptr IEnumFORMATETC,
	      reserved: DWORD

;STDAPI
RevokeFormatEnumerator proto WINAPI \
		   pBC: LPBC,
		pEFetc: ptr IEnumFORMATETC

;STDAPI
RegisterMediaTypeClass proto WINAPI \
		   pBC: LPBC,
		ctypes: UINT,
	     rgszTypes: LPCSTR,
	       rgclsID: ptr CLSID,
	      reserved: DWORD

;STDAPI
FindMediaTypeClass proto WINAPI \
		   pBC: LPBC,
		szType: LPCSTR,
		pclsID: ptr CLSID,
	      reserved: DWORD

;STDAPI
UrlMkSetSessionOption proto WINAPI \
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
	    dwReserved: DWORD

;STDAPI
UrlMkGetSessionOption proto WINAPI \
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
       pdwBufferLength: LPDWORD,
	    dwReserved: DWORD

;STDAPI
FindMimeFromData proto WINAPI \
		   pBC: LPBC,
		pwzUrl: LPCWSTR,
	       pBuffer: LPVOID,
		cbSize: DWORD,
       pwzMimeProposed: LPCWSTR,
	   dwMimeFlags: DWORD,
	   ppwzMimeOut: ptr LPWSTR,
	    dwReserved: DWORD

;STDAPI
ObtainUserAgentString proto WINAPI \
	      dwOption: DWORD,
	      pszUAOut: LPSTR,
		cbSize: LPDWORD


URLMON_OPTION_USERAGENT equ 0x10000001
URLMON_OPTION_USERAGENT_REFRESH equ 0x10000002

CF_NULL			equ 0
CFSTR_MIME_NULL		equ NULL
CFSTR_MIME_TEXT		equ <(TEXT("text/plain"))>
CFSTR_MIME_RICHTEXT	equ <(TEXT("text/richtext"))>
CFSTR_MIME_X_BITMAP	equ <(TEXT("image/x-xbitmap"))>
CFSTR_MIME_POSTSCRIPT	equ <(TEXT("application/postscript"))>
CFSTR_MIME_AIFF		equ <(TEXT("audio/aiff"))>
CFSTR_MIME_BASICAUDIO	equ <(TEXT("audio/basic"))>
CFSTR_MIME_WAV		equ <(TEXT("audio/wav"))>
CFSTR_MIME_X_WAV	equ <(TEXT("audio/x-wav"))>
CFSTR_MIME_GIF		equ <(TEXT("image/gif"))>
CFSTR_MIME_PJPEG	equ <(TEXT("image/pjpeg"))>
CFSTR_MIME_JPEG		equ <(TEXT("image/jpeg"))>
CFSTR_MIME_TIFF		equ <(TEXT("image/tiff"))>
CFSTR_MIME_X_PNG	equ <(TEXT("image/x-png"))>
CFSTR_MIME_BMP		equ <(TEXT("image/bmp"))>
CFSTR_MIME_X_ART	equ <(TEXT("image/x-jg"))>
CFSTR_MIME_X_EMF	equ <(TEXT("image/x-emf"))>
CFSTR_MIME_X_WMF	equ <(TEXT("image/x-wmf"))>
CFSTR_MIME_AVI		equ <(TEXT("video/avi"))>
CFSTR_MIME_MPEG		equ <(TEXT("video/mpeg"))>
CFSTR_MIME_FRACTALS	equ <(TEXT("application/fractals"))>
CFSTR_MIME_RAWDATA	equ <(TEXT("application/octet-stream"))>
CFSTR_MIME_RAWDATASTRM	equ <(TEXT("application/octet-stream"))>
CFSTR_MIME_PDF		equ <(TEXT("application/pdf"))>
CFSTR_MIME_X_AIFF	equ <(TEXT("audio/x-aiff"))>
CFSTR_MIME_X_REALAUDIO	equ <(TEXT("audio/x-pn-realaudio"))>
CFSTR_MIME_XBM		equ <(TEXT("image/xbm"))>
CFSTR_MIME_QUICKTIME	equ <(TEXT("video/quicktime"))>
CFSTR_MIME_X_MSVIDEO	equ <(TEXT("video/x-msvideo"))>
CFSTR_MIME_X_SGI_MOVIE	equ <(TEXT("video/x-sgi-movie"))>
CFSTR_MIME_HTML		equ <(TEXT("text/html"))>

MK_S_ASYNCHRONOUS	equ _HRESULT_TYPEDEF_(0x000401E8)
ifndef S_ASYNCHRONOUS
S_ASYNCHRONOUS		equ MK_S_ASYNCHRONOUS
endif

ifndef E_PENDING
E_PENDING		equ _HRESULT_TYPEDEF_(0x8000000A)
endif

INET_E_INVALID_URL	equ _HRESULT_TYPEDEF_(0x800C0002)
INET_E_NO_SESSION	equ _HRESULT_TYPEDEF_(0x800C0003)
INET_E_CANNOT_CONNECT	equ _HRESULT_TYPEDEF_(0x800C0004)
INET_E_RESOURCE_NOT_FOUND equ _HRESULT_TYPEDEF_(0x800C0005)
INET_E_OBJECT_NOT_FOUND equ _HRESULT_TYPEDEF_(0x800C0006)
INET_E_DATA_NOT_AVAILABLE equ _HRESULT_TYPEDEF_(0x800C0007)
INET_E_DOWNLOAD_FAILURE equ _HRESULT_TYPEDEF_(0x800C0008)
INET_E_AUTHENTICATION_REQUIRED equ _HRESULT_TYPEDEF_(0x800C0009)
INET_E_NO_VALID_MEDIA	equ _HRESULT_TYPEDEF_(0x800C000A)
INET_E_CONNECTION_TIMEOUT equ _HRESULT_TYPEDEF_(0x800C000B)
INET_E_INVALID_REQUEST	equ _HRESULT_TYPEDEF_(0x800C000C)
INET_E_UNKNOWN_PROTOCOL equ _HRESULT_TYPEDEF_(0x800C000D)
INET_E_SECURITY_PROBLEM equ _HRESULT_TYPEDEF_(0x800C000E)
INET_E_CANNOT_LOAD_DATA equ _HRESULT_TYPEDEF_(0x800C000F)
INET_E_CANNOT_INSTANTIATE_OBJECT equ _HRESULT_TYPEDEF_(0x800C0010)
INET_E_REDIRECT_FAILED	equ _HRESULT_TYPEDEF_(0x800C0014)
INET_E_REDIRECT_TO_DIR	equ _HRESULT_TYPEDEF_(0x800C0015)
INET_E_CANNOT_LOCK_REQUEST equ _HRESULT_TYPEDEF_(0x800C0016)
INET_E_ERROR_FIRST	equ _HRESULT_TYPEDEF_(0x800C0002)
INET_E_ERROR_LAST	equ INET_E_REDIRECT_TO_DIR
ifndef _LPPERSISTMONIKER_DEFINED
_LPPERSISTMONIKER_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPersistMoniker_INTERFACE_DEFINED__
__IPersistMoniker_INTERFACE_DEFINED__ equ 1

IPersistMonikerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	IsDirty
	STDMETHOD	Load, :BOOL, :ptr, :LPBC, :DWORD
	STDMETHOD	Save, :ptr, :LPBC, :BOOL
	STDMETHOD	SaveCompleted, :ptr, :LPBC
	STDMETHOD	GetCurMoniker, :ptr
IPersistMonikerVtbl ends
IPersistMoniker struct
	lpVtbl		PVOID ?
IPersistMoniker ends
LPPERSISTMONIKER	typedef ptr IPersistMoniker
externdef		IID_IPersistMoniker:IID

;HRESULT
IPersistMoniker_GetClassID_Proxy proto WINAPI \
		 pThis: ptr IPersistMoniker,
	      pClassID: ptr CLSID

;void
IPersistMoniker_GetClassID_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistMoniker_IsDirty_Proxy proto WINAPI \
		 pThis: ptr IPersistMoniker

;void
IPersistMoniker_IsDirty_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistMoniker_Load_Proxy proto WINAPI \
		 pThis: ptr IPersistMoniker,
       fFullyAvailable: BOOL,
	      pimkName: ptr IMoniker,
		  pibc: LPBC,
	       grfMode: DWORD

;void
IPersistMoniker_Load_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistMoniker_Save_Proxy proto WINAPI \
		 pThis: ptr IPersistMoniker,
	      pimkName: ptr IMoniker,
		   pbc: LPBC,
	     fRemember: BOOL

;void
IPersistMoniker_Save_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistMoniker_SaveCompleted_Proxy proto WINAPI \
		 pThis: ptr IPersistMoniker,
	      pimkName: ptr IMoniker,
		  pibc: LPBC

;void
IPersistMoniker_SaveCompleted_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistMoniker_GetCurMoniker_Proxy proto WINAPI \
		 pThis: ptr IPersistMoniker,
	     ppimkName: ptr ptr IMoniker

;void
IPersistMoniker_GetCurMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

endif
ifndef _LPBINDPROTOCOL_DEFINED
_LPBINDPROTOCOL_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0111_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0111_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBindProtocol_INTERFACE_DEFINED__
__IBindProtocol_INTERFACE_DEFINED__ equ 1

IBindProtocolVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateBinding, :LPCWSTR, :ptr, :ptr
IBindProtocolVtbl ends
IBindProtocol struct
	lpVtbl		PVOID ?
IBindProtocol ends
LPBINDPROTOCOL		typedef ptr IBindProtocol
externdef		IID_IBindProtocol:IID

;HRESULT
IBindProtocol_CreateBinding_Proxy proto WINAPI \
		 pThis: ptr IBindProtocol,
		 szUrl: LPCWSTR,
		   pbc: ptr IBindCtx,
		   ppb: ptr IBinding

;void
IBindProtocol_CreateBinding_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPBINDING_DEFINED
_LPBINDING_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0112_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0112_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBinding_INTERFACE_DEFINED__
__IBinding_INTERFACE_DEFINED__ equ 1

IBindingVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Abort
	STDMETHOD	Suspend
	STDMETHOD	Resume
	STDMETHOD	SetPriority, :LONG
	STDMETHOD	GetPriority, :ptr
	STDMETHOD	GetBindResult, :ptr, :ptr, :ptr, :DWORD
IBindingVtbl ends
IBinding struct
	lpVtbl		PVOID ?
IBinding ends
LPBINDING		typedef ptr IBinding
externdef		IID_IBinding:IID

;HRESULT
IBinding_Abort_Proxy proto WINAPI \
		 pThis: ptr IBinding

;void
IBinding_Abort_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBinding_Suspend_Proxy proto WINAPI \
		 pThis: ptr IBinding

;void
IBinding_Suspend_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBinding_Resume_Proxy proto WINAPI \
		 pThis: ptr IBinding

;void
IBinding_Resume_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBinding_SetPriority_Proxy proto WINAPI \
		 pThis: ptr IBinding,
	     nPriority: LONG

;void
IBinding_SetPriority_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBinding_GetPriority_Proxy proto WINAPI \
		 pThis: ptr IBinding,
	    pnPriority: ptr LONG

;void
IBinding_GetPriority_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBinding_RemoteGetBindResult_Proxy proto WINAPI \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	    dwReserved: DWORD

;void
IBinding_RemoteGetBindResult_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPBINDSTATUSCALLBACK_DEFINED
_LPBINDSTATUSCALLBACK_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0113_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0113_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBindStatusCallback_INTERFACE_DEFINED__
__IBindStatusCallback_INTERFACE_DEFINED__ equ 1

LPBINDSTATUSCALLBACK	typedef ptr IBindStatusCallback

;typedef enum __MIDL_IBindStatusCallback_0001

BINDVERB_GET		equ 0
BINDVERB_POST		equ 0x1
BINDVERB_PUT		equ 0x2
BINDVERB_CUSTOM		equ 0x3

;typedef enum __MIDL_IBindStatusCallback_0002

BINDINFOF_URLENCODESTGMEDDATA equ 0x1
BINDINFOF_URLENCODEDEXTRAINFO equ 0x2

;typedef enum __MIDL_IBindStatusCallback_0003

BINDF_ASYNCHRONOUS	equ 0x1
BINDF_ASYNCSTORAGE	equ 0x2
BINDF_NOPROGRESSIVERENDERING equ 0x4
BINDF_OFFLINEOPERATION	equ 0x8
BINDF_GETNEWESTVERSION	equ 0x10
BINDF_NOWRITECACHE	equ 0x20
BINDF_NEEDFILE		equ 0x40
BINDF_PULLDATA		equ 0x80
BINDF_IGNORESECURITYPROBLEM equ 0x100
BINDF_RESYNCHRONIZE	equ 0x200
BINDF_HYPERLINK		equ 0x400
BINDF_NO_UI		equ 0x800
BINDF_SILENTOPERATION	equ 0x1000
BINDF_PRAGMA_NO_CACHE	equ 0x2000
BINDF_FREE_THREADED	equ 0x10000
BINDF_DIRECT_READ	equ 0x20000
BINDF_FORMS_SUBMIT	equ 0x40000
BINDF_GETFROMCACHE_IF_NET_FAIL equ 0x80000

BINDINFO		STRUC
cbSize			ULONG ?
szExtraInfo		LPWSTR ?
stgmedData		STGMEDIUM <>
grfBindInfoF		dd ?
dwBindVerb		dd ?
szCustomVerb		LPWSTR ?
cbstgmedData		dd ?
dwOptions		dd ?
dwOptionsFlags		dd ?
dwCodePage		dd ?
securityAttributes	SECURITY_ATTRIBUTES <>
iid			IID <>
pUnk			LPIUnknown ?
dwReserved		dd ?
BINDINFO		ENDS

REMSECURITY_ATTRIBUTES	STRUC
nLength			dd ?
lpSecurityDescriptor	dd ?
bInheritHandle		BOOL ?
REMSECURITY_ATTRIBUTES	ENDS
PREMSECURITY_ATTRIBUTES typedef ptr REMSECURITY_ATTRIBUTES
LPREMSECURITY_ATTRIBUTES typedef ptr REMSECURITY_ATTRIBUTES

RemBINDINFO		STRUC
cbSize			ULONG ?
szExtraInfo		LPWSTR ?
grfBindInfoF		dd ?
dwBindVerb		dd ?
szCustomVerb		LPWSTR ?
cbstgmedData		dd ?
dwOptions		dd ?
dwOptionsFlags		dd ?
dwCodePage		dd ?
securityAttributes	REMSECURITY_ATTRIBUTES <>
iid			IID <>
pUnk			LPIUnknown ?
dwReserved		dd ?
RemBINDINFO		ENDS

RemFORMATETC		STRUC
cfFormat		dd ?
ptd			dd ?
dwAspect		dd ?
lindex			LONG ?
tymed			dd ?
RemFORMATETC		ENDS
LPREMFORMATETC		typedef ptr RemFORMATETC

;typedef enum __MIDL_IBindStatusCallback_0004

BSCF_FIRSTDATANOTIFICATION equ 0x1
BSCF_INTERMEDIATEDATANOTIFICATION equ 0x2
BSCF_LASTDATANOTIFICATION equ 0x4
BSCF_DATAFULLYAVAILABLE equ 0x8
BSCF_AVAILABLEDATASIZEUNKNOWN equ 0x10

;typedef enum tagBINDSTATUS

BINDSTATUS_FINDINGRESOURCE equ 1
BINDSTATUS_CONNECTING	equ BINDSTATUS_FINDINGRESOURCE + 1
BINDSTATUS_REDIRECTING	equ BINDSTATUS_CONNECTING + 1
BINDSTATUS_BEGINDOWNLOADDATA equ BINDSTATUS_REDIRECTING + 1
BINDSTATUS_DOWNLOADINGDATA equ BINDSTATUS_BEGINDOWNLOADDATA + 1
BINDSTATUS_ENDDOWNLOADDATA equ BINDSTATUS_DOWNLOADINGDATA + 1
BINDSTATUS_BEGINDOWNLOADCOMPONENTS equ BINDSTATUS_ENDDOWNLOADDATA + 1
BINDSTATUS_INSTALLINGCOMPONENTS equ BINDSTATUS_BEGINDOWNLOADCOMPONENTS + 1
BINDSTATUS_ENDDOWNLOADCOMPONENTS equ BINDSTATUS_INSTALLINGCOMPONENTS + 1
BINDSTATUS_USINGCACHEDCOPY equ BINDSTATUS_ENDDOWNLOADCOMPONENTS + 1
BINDSTATUS_SENDINGREQUEST equ BINDSTATUS_USINGCACHEDCOPY + 1
BINDSTATUS_CLASSIDAVAILABLE equ BINDSTATUS_SENDINGREQUEST + 1
BINDSTATUS_MIMETYPEAVAILABLE equ BINDSTATUS_CLASSIDAVAILABLE + 1
BINDSTATUS_CACHEFILENAMEAVAILABLE equ BINDSTATUS_MIMETYPEAVAILABLE + 1
BINDSTATUS_BEGINSYNCOPERATION equ BINDSTATUS_CACHEFILENAMEAVAILABLE + 1
BINDSTATUS_ENDSYNCOPERATION equ BINDSTATUS_BEGINSYNCOPERATION + 1
BINDSTATUS_BEGINUPLOADDATA equ BINDSTATUS_ENDSYNCOPERATION + 1
BINDSTATUS_UPLOADINGDATA equ BINDSTATUS_BEGINUPLOADDATA + 1
BINDSTATUS_ENDUPLOADDATA equ BINDSTATUS_UPLOADINGDATA + 1
BINDSTATUS_PROTOCOLCLASSID equ BINDSTATUS_ENDUPLOADDATA + 1
BINDSTATUS_ENCODING	equ BINDSTATUS_PROTOCOLCLASSID + 1
BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE equ BINDSTATUS_ENCODING + 1
BINDSTATUS_CLASSINSTALLLOCATION equ BINDSTATUS_VERIFIEDMIMETYPEAVAILABLE + 1
BINDSTATUS_DECODING	equ BINDSTATUS_CLASSINSTALLLOCATION + 1
BINDSTATUS_LOADINGMIMEHANDLER equ BINDSTATUS_DECODING + 1

externdef		IID_IBindStatusCallback:IID

IBindStatusCallbackVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnStartBinding,:DWORD,:ptr
	STDMETHOD	GetPriority, :ptr
	STDMETHOD	OnLowResource, :DWORD
	STDMETHOD	OnProgress, :DWORD, :DWORD, :DWORD,: LPWSTR
	STDMETHOD	OnStopBinding, :HRESULT, :LPWSTR
	STDMETHOD	GetBindInfo, :ptr, :ptr
	STDMETHOD	OnDataAvailable, :DWORD, :DWORD, :ptr, :ptr
	STDMETHOD	OnObjectAvailable, :REFIID, :ptr
IBindStatusCallbackVtbl ends
IBindStatusCallback struct
	lpVtbl		PVOID ?
IBindStatusCallback ends

;HRESULT
IBindStatusCallback_OnStartBinding_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	    dwReserved: DWORD,
		   pib: ptr IBinding

;void
IBindStatusCallback_OnStartBinding_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_GetPriority_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	    pnPriority: ptr LONG

;void
IBindStatusCallback_GetPriority_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_OnLowResource_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	      reserved: DWORD

;void
IBindStatusCallback_OnLowResource_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_OnProgress_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	    ulProgress: ULONG,
	 ulProgressMax: ULONG,
	  ulStatusCode: ULONG,
	  szStatusText: LPCWSTR

;void
IBindStatusCallback_OnProgress_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_OnStopBinding_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	       hresult: HRESULT,
	       szError: LPCWSTR

;void
IBindStatusCallback_OnStopBinding_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_RemoteGetBindInfo_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr RemBINDINFO,
	       pstgmed: ptr RemSTGMEDIUM

;void
IBindStatusCallback_RemoteGetBindInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_RemoteOnDataAvailable_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr RemFORMATETC,
	       pstgmed: ptr RemSTGMEDIUM

;void
IBindStatusCallback_RemoteOnDataAvailable_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindStatusCallback_OnObjectAvailable_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
		  riid: REFIID,
		  punk: ptr IUnknown

;void
IBindStatusCallback_OnObjectAvailable_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPAUTHENTICATION_DEFINED
_LPAUTHENTICATION_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0114_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0114_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAuthenticate_INTERFACE_DEFINED__
__IAuthenticate_INTERFACE_DEFINED__ equ 1

IAuthenticateVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Authenticate, :ptr, :ptr, :ptr
IAuthenticateVtbl ends
IAuthenticate struct
	lpVtbl		PVOID ?
IAuthenticate ends
LPAUTHENTICATION	typedef ptr IAuthenticate
externdef		IID_IAuthenticate:IID

;HRESULT
IAuthenticate_Authenticate_Proxy proto WINAPI \
		 pThis: ptr IAuthenticate,
		 phwnd: ptr HWND,
	   pszUsername: ptr LPWSTR,
	   pszPassword: ptr LPWSTR

;void
IAuthenticate_Authenticate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPHTTPNEGOTIATE_DEFINED
_LPHTTPNEGOTIATE_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0115_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0115_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IHttpNegotiate_INTERFACE_DEFINED__
__IHttpNegotiate_INTERFACE_DEFINED__ equ 1

IHttpNegotiateVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	BeginningTransaction, :LPCWSTR, :LPCWSTR, :DWORD, :ptr
	STDMETHOD	OnResponse, :DWORD, :LPCWSTR, :LPCWSTR, :ptr
IHttpNegotiateVtbl ends
IHttpNegotiate struct
	lpVtbl		PVOID ?
IHttpNegotiate ends
LPHTTPNEGOTIATE		typedef ptr IHttpNegotiate
externdef		IID_IHttpNegotiate:IID

;HRESULT
IHttpNegotiate_BeginningTransaction_Proxy proto WINAPI \
		 pThis: ptr IHttpNegotiate,
		 szURL: LPCWSTR,
	     szHeaders: LPCWSTR,
	    dwReserved: DWORD,
  pszAdditionalHeaders: ptr LPWSTR

;void
IHttpNegotiate_BeginningTransaction_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IHttpNegotiate_OnResponse_Proxy proto WINAPI \
		 pThis: ptr IHttpNegotiate,
	dwResponseCode: DWORD,
     szResponseHeaders: LPCWSTR,
      szRequestHeaders: LPCWSTR,
pszAdditionalRequestHeaders: ptr LPWSTR

;void
IHttpNegotiate_OnResponse_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPWINDOWFORBINDINGUI_DEFINED
_LPWINDOWFORBINDINGUI_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0116_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0116_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWindowForBindingUI_INTERFACE_DEFINED__
__IWindowForBindingUI_INTERFACE_DEFINED__ equ 1

IWindowForBindingUIVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :REFGUID, :ptr
IWindowForBindingUIVtbl ends
IWindowForBindingUI struct
	lpVtbl		PVOID ?
IWindowForBindingUI ends
LPWINDOWFORBINDINGUI	typedef ptr IWindowForBindingUI
externdef		IID_IWindowForBindingUI:IID

;HRESULT
IWindowForBindingUI_GetWindow_Proxy proto WINAPI \
		 pThis: ptr IWindowForBindingUI,
	   rguidReason: REFGUID,
		 phwnd: ptr HWND

;void
IWindowForBindingUI_GetWindow_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPCODEINSTALL_DEFINED
_LPCODEINSTALL_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0117_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0117_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ICodeInstall_INTERFACE_DEFINED__
__ICodeInstall_INTERFACE_DEFINED__ equ 1

LPCODEINSTALL		typedef ptr ICodeInstall

;typedef enum __MIDL_ICodeInstall_0001

CIP_DISK_FULL		equ 0
CIP_ACCESS_DENIED	equ CIP_DISK_FULL + 1
CIP_NEWER_VERSION_EXISTS equ CIP_ACCESS_DENIED + 1
CIP_OLDER_VERSION_EXISTS equ CIP_NEWER_VERSION_EXISTS + 1
CIP_NAME_CONFLICT	equ CIP_OLDER_VERSION_EXISTS + 1
CIP_TRUST_VERIFICATION_COMPONENT_MISSING equ CIP_NAME_CONFLICT + 1
CIP_EXE_SELF_REGISTERATION_TIMEOUT equ CIP_TRUST_VERIFICATION_COMPONENT_MISSING + 1
CIP_UNSAFE_TO_ABORT	equ CIP_EXE_SELF_REGISTERATION_TIMEOUT + 1
CIP_NEED_REBOOT		equ CIP_UNSAFE_TO_ABORT + 1

externdef		IID_ICodeInstall:IID

ICodeInstallVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow
	STDMETHOD	OnCodeInstallProblem, :ULONG, :LPCWSTR, :LPCWSTR, :DWORD
ICodeInstallVtbl ends
ICodeInstall struct
	lpVtbl		PVOID ?
ICodeInstall ends

;HRESULT
ICodeInstall_OnCodeInstallProblem_Proxy proto WINAPI \
		 pThis: ptr ICodeInstall,
	  ulStatusCode: ULONG,
	 szDestination: LPCWSTR,
	      szSource: LPCWSTR,
	    dwReserved: DWORD

;void
ICodeInstall_OnCodeInstallProblem_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPWININETINFO_DEFINED
_LPWININETINFO_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0118_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0118_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWinInetInfo_INTERFACE_DEFINED__
__IWinInetInfo_INTERFACE_DEFINED__ equ 1

IWinInetInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryOption, :DWORD, :ptr, :ptr
IWinInetInfoVtbl ends
IWinInetInfo struct
	lpVtbl		PVOID ?
IWinInetInfo ends
LPWININETINFO		typedef ptr IWinInetInfo
externdef		IID_IWinInetInfo:IID

;HRESULT
IWinInetInfo_RemoteQueryOption_Proxy proto WINAPI \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD

;void
IWinInetInfo_RemoteQueryOption_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
WININETINFO_OPTION_LOCK_HANDLE equ 65534
ifndef _LPHTTPSECURITY_DEFINED
_LPHTTPSECURITY_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0119_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0119_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IHttpSecurity_INTERFACE_DEFINED__
__IHttpSecurity_INTERFACE_DEFINED__ equ 1

IHttpSecurityVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :REFGUID, :ptr
	STDMETHOD	OnSecurityProblem, :DWORD
IHttpSecurityVtbl ends
IHttpSecurity struct
	lpVtbl		PVOID ?
IHttpSecurity ends
LPHTTPSECURITY		typedef ptr IHttpSecurity
externdef		IID_IHttpSecurity:IID

;HRESULT
IHttpSecurity_OnSecurityProblem_Proxy proto WINAPI \
		 pThis: ptr IHttpSecurity,
	     dwProblem: DWORD

;void
IHttpSecurity_OnSecurityProblem_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPWININETHTTPINFO_DEFINED
_LPWININETHTTPINFO_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0120_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0120_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWinInetHttpInfo_INTERFACE_DEFINED__
__IWinInetHttpInfo_INTERFACE_DEFINED__ equ 1

IWinInetHttpInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryOption, :DWORD, :PVOID, :ptr
	STDMETHOD	QueryInfo, :DWORD, :PVOID, :ptr, :ptr, :ptr
IWinInetHttpInfoVtbl ends
IWinInetHttpInfo struct
	lpVtbl		PVOID ?
IWinInetHttpInfo ends
LPWININETHTTPINFO	typedef ptr IWinInetHttpInfo
externdef		IID_IWinInetHttpInfo:IID

;HRESULT
IWinInetHttpInfo_RemoteQueryInfo_Proxy proto WINAPI \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD

;void
IWinInetHttpInfo_RemoteQueryInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
SID_IBindHost		equ IID_IBindHost
SID_SBindHost		equ IID_IBindHost
ifndef _LPBINDHOST_DEFINED
_LPBINDHOST_DEFINED equ 1
externdef		SID_BindHost:GUID

externdef		__MIDL_itf_urlmon_0121_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0121_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBindHost_INTERFACE_DEFINED__
__IBindHost_INTERFACE_DEFINED__ equ 1

IBindHostVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateMoniker, :LPOLESTR,:ptr, :ptr, :DWORD
	STDMETHOD	MonikerBindToStorage, :ptr, :ptr, :ptr, :REFIID, :ptr
	STDMETHOD	MonikerBindToObject, :ptr, :ptr, :ptr, :REFIID, :ptr
IBindHostVtbl ends
IBindHost struct
	lpVtbl		PVOID ?
IBindHost ends
LPBINDHOST		typedef ptr IBindHost
LPIBindHost		typedef ptr IBindHost
externdef		IID_IBindHost:IID

;HRESULT
IBindHost_CreateMoniker_Proxy proto WINAPI \
		 pThis: ptr IBindHost,
		szName: LPOLESTR,
		   pBC: ptr IBindCtx,
		  ppmk: ptr ptr IMoniker,
	    dwReserved: DWORD

;void
IBindHost_CreateMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindHost_RemoteMonikerBindToStorage_Proxy proto WINAPI \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown

;void
IBindHost_RemoteMonikerBindToStorage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindHost_RemoteMonikerBindToObject_Proxy proto WINAPI \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown

;void
IBindHost_RemoteMonikerBindToObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif

URLOSTRM_USECACHEDCOPY_ONLY equ 0x1
URLOSTRM_USECACHEDCOPY	equ 0x2
URLOSTRM_GETNEWESTVERSION equ 0x3

;IBindStatusCallback	typedef STRUC
;STDAPI
HlinkSimpleNavigateToString proto WINAPI \
	      szTarget: LPCWSTR,
	    szLocation: LPCWSTR,
     szTargetFrameName: LPCWSTR,
		  pUnk: ptr IUnknown,
		   pbc: ptr IBindCtx,
		      : ptr IBindStatusCallback,
	       grfHLNF: DWORD,
	    dwReserved: DWORD

;STDAPI
HlinkSimpleNavigateToMoniker proto WINAPI \
	     pmkTarget: ptr IMoniker,
	    szLocation: LPCWSTR,
     szTargetFrameName: LPCWSTR,
		  pUnk: ptr IUnknown,
		   pbc: ptr IBindCtx,
		      : ptr IBindStatusCallback,
	       grfHLNF: DWORD,
	    dwReserved: DWORD

;STDAPI
URLOpenStreamA proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLOpenStreamW proto WINAPI \
		      : LPUNKNOWN,
		      : LPCWSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLOpenPullStreamA proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLOpenPullStreamW proto WINAPI \
		      : LPUNKNOWN,
		      : LPCWSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLDownloadToFileA proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLDownloadToFileW proto WINAPI \
		      : LPUNKNOWN,
		      : LPCWSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLDownloadToCacheFileA proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
       out_cchFileName: LPSTR,
	   cchFileName: DWORD,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLDownloadToCacheFileW proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
       out_cchFileName: LPWSTR,
	   cchFileName: DWORD,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLOpenBlockingStreamA proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
		      : ptr LPSTREAM,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK
;STDAPI
URLOpenBlockingStreamW proto WINAPI \
		      : LPUNKNOWN,
		      : LPCWSTR,
		      : ptr LPSTREAM,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK

ifdef _UNICODE
URLOpenStream		equ <URLOpenStreamW>
URLOpenPullStream	equ <URLOpenPullStreamW>
URLDownloadToFile	equ <URLDownloadToFileW>
URLDownloadToCacheFile	equ <URLDownloadToCacheFileW>
URLOpenBlockingStream	equ <URLOpenBlockingStreamW>
else
URLOpenStream		equ <URLOpenStreamA>
URLOpenPullStream	equ <URLOpenPullStreamA>
URLDownloadToFile	equ <URLDownloadToFileA>
URLDownloadToCacheFile	equ <URLDownloadToCacheFileA>
URLOpenBlockingStream	equ <URLOpenBlockingStreamA>
endif


;STDAPI
HlinkGoBack proto WINAPI \
		  pUnk: ptr IUnknown

;STDAPI
HlinkGoForward proto WINAPI \
		  pUnk: ptr IUnknown

;STDAPI
HlinkNavigateString proto WINAPI \
		  pUnk: ptr IUnknown,
	      szTarget: LPCWSTR

;STDAPI
HlinkNavigateMoniker proto WINAPI \
		  pUnk: ptr IUnknown,
	     pmkTarget: ptr IMoniker


ifndef	 _URLMON_NO_ASYNC_PLUGABLE_PROTOCOLS_

ifndef _LPIINTERNET
_LPIINTERNET equ 1

externdef		__MIDL_itf_urlmon_0122_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0122_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternet_INTERFACE_DEFINED__
__IInternet_INTERFACE_DEFINED__ equ 1

IInternetVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
IInternetVtbl ends
IInternet struct
	lpVtbl		PVOID ?
IInternet ends
LPIINTERNET		typedef ptr IInternet
externdef		IID_IInternet:IID
endif
endif

ifndef _LPIINTERNETBINDINFO
_LPIINTERNETBINDINFO equ 1

externdef		__MIDL_itf_urlmon_0123_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0123_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetBindInfo_INTERFACE_DEFINED__
__IInternetBindInfo_INTERFACE_DEFINED__ equ 1

LPIINTERNETBINDINFO	typedef ptr IInternetBindInfo

;typedef enum tagBINDSTRING

BINDSTRING_HEADERS	equ 1
BINDSTRING_ACCEPT_MIMES equ BINDSTRING_HEADERS + 1
BINDSTRING_EXTRA_URL	equ BINDSTRING_ACCEPT_MIMES + 1
BINDSTRING_LANGUAGE	equ BINDSTRING_EXTRA_URL + 1
BINDSTRING_USERNAME	equ BINDSTRING_LANGUAGE + 1
BINDSTRING_PASSWORD	equ BINDSTRING_USERNAME + 1
BINDSTRING_UA_PIXELS	equ BINDSTRING_PASSWORD + 1
BINDSTRING_UA_COLOR	equ BINDSTRING_UA_PIXELS + 1
BINDSTRING_OS		equ BINDSTRING_UA_COLOR + 1
BINDSTRING_USER_AGENT	equ BINDSTRING_OS + 1
BINDSTRING_ACCEPT_ENCODINGS equ BINDSTRING_USER_AGENT + 1
BINDSTRING_POST_COOKIE	equ BINDSTRING_ACCEPT_ENCODINGS + 1
BINDSTRING_POST_DATA_MIME equ BINDSTRING_POST_COOKIE + 1
BINDSTRING_URL		equ BINDSTRING_POST_DATA_MIME + 1

externdef		IID_IInternetBindInfo:IID

IInternetBindInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetBindInfo, :ptr, :ptr
	STDMETHOD	GetBindString, :DWORD, :ptr, :DWORD, :ptr
IInternetBindInfoVtbl ends
IInternetBindInfo struct
	lpVtbl		PVOID ?
IInternetBindInfo ends

;HRESULT
IInternetBindInfo_GetBindInfo_Proxy proto WINAPI \
		 pThis: ptr IInternetBindInfo,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr BINDINFO

;void
IInternetBindInfo_GetBindInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetBindInfo_GetBindString_Proxy proto WINAPI \
		 pThis: ptr IInternetBindInfo,
	  ulStringType: ULONG,
	       ppwzStr: ptr LPOLESTR,
		   cEl: ULONG,
	   pcElFetched: ptr ULONG

;void
IInternetBindInfo_GetBindString_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETPROTOCOLROOT_DEFINED
_LPIINTERNETPROTOCOLROOT_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0124_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0124_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetProtocolRoot_INTERFACE_DEFINED__
__IInternetProtocolRoot_INTERFACE_DEFINED__ equ 1

LPIINTERNETPROTOCOLROOT typedef ptr IInternetProtocolRoot

;typedef enum _tagPI_FLAGS

PI_PARSE_URL		equ 0x1
PI_FILTER_MODE		equ 0x2
PI_FORCE_ASYNC		equ 0x4
PI_USE_WORKERTHREAD	equ 0x8
PI_MIMEVERIFICATION	equ 0x10
PI_CLSIDLOOKUP		equ 0x20
PI_DATAPROGRESS		equ 0x40
PI_SYNCHRONOUS		equ 0x80
PI_APARTMENTTHREADED	equ 0x100
PI_CLASSINSTALL		equ 0x200
PD_FORCE_SWITCH		equ 0x10000

PROTOCOLDATA		STRUC
grfFlags		dd ?
dwState			dd ?
pData			LPVOID ?
cbData			ULONG ?
PROTOCOLDATA		ENDS

externdef		IID_IInternetProtocolRoot:IID

IInternetProtocolRootVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Start, :LPWSTR, :ptr, :ptr, :DWORD, :DWORD
	STDMETHOD	Continue, :ptr
	STDMETHOD	Abort, :HRESULT, :DWORD
	STDMETHOD	Terminate, :DWORD
	STDMETHOD	Suspend
	STDMETHOD	Resume
IInternetProtocolRootVtbl ends
IInternetProtocolRoot struct
	lpVtbl		PVOID ?
IInternetProtocolRoot ends

;HRESULT
IInternetProtocolRoot_Start_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolRoot,
		 szUrl: LPCWSTR,
	   pOIProtSink: ptr IInternetProtocolSink,
	   pOIBindInfo: ptr IInternetBindInfo,
		 grfPI: DWORD,
	    dwReserved: DWORD

;void
IInternetProtocolRoot_Start_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolRoot_Continue_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolRoot,
	 pProtocolData: ptr PROTOCOLDATA

;void
IInternetProtocolRoot_Continue_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolRoot_Abort_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolRoot,
	      hrReason: HRESULT,
	     dwOptions: DWORD

;void
IInternetProtocolRoot_Abort_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolRoot_Terminate_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolRoot,
	     dwOptions: DWORD

;void
IInternetProtocolRoot_Terminate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolRoot_Suspend_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolRoot

;void
IInternetProtocolRoot_Suspend_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolRoot_Resume_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolRoot

;void
IInternetProtocolRoot_Resume_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETPROTOCOL_DEFINED
_LPIINTERNETPROTOCOL_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0125_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0125_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetProtocol_INTERFACE_DEFINED__
__IInternetProtocol_INTERFACE_DEFINED__ equ 1

IInternetProtocolVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Start, :LPWSTR, :ptr, :ptr, :DWORD, :DWORD
	STDMETHOD	Continue, :ptr
	STDMETHOD	Abort, :HRESULT, :DWORD
	STDMETHOD	Terminate, :DWORD
	STDMETHOD	Suspend
	STDMETHOD	Resume
	STDMETHOD	Read, :ptr, :DWORD, :ptr
	STDMETHOD	Seek, :LARGE_INTEGER, :DWORD, :ptr
	STDMETHOD	LockRequest, :DWORD
	STDMETHOD	UnlockRequest
IInternetProtocolVtbl ends
IInternetProtocol struct
	lpVtbl		PVOID ?
IInternetProtocol ends
LPIINTERNETPROTOCOL	typedef ptr IInternetProtocol
externdef		IID_IInternetProtocol:IID

;HRESULT
IInternetProtocol_Read_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocol,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: ptr ULONG

;void
IInternetProtocol_Read_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocol_Seek_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocol,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER

;void
IInternetProtocol_Seek_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocol_LockRequest_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocol,
	     dwOptions: DWORD

;void
IInternetProtocol_LockRequest_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocol_UnlockRequest_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocol

;void
IInternetProtocol_UnlockRequest_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETPROTOCOLSINK_DEFINED
_LPIINTERNETPROTOCOLSINK_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0126_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0126_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetProtocolSink_INTERFACE_DEFINED__
__IInternetProtocolSink_INTERFACE_DEFINED__ equ 1

LPIINTERNETPROTOCOLSINK typedef ptr IInternetProtocolSink
externdef		IID_IInternetProtocolSink:IID

IInternetProtocolSinkVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Switch, :ptr
	STDMETHOD	ReportProgress, :DWORD, :LPWSTR
	STDMETHOD	ReportData, :DWORD, :DWORD, :DWORD
	STDMETHOD	ReportResult, :HRESULT, :DWORD, :LPWSTR
IInternetProtocolSinkVtbl ends
IInternetProtocolSink struct
	lpVtbl		PVOID ?
IInternetProtocolSink ends

;HRESULT
IInternetProtocolSink_Switch_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolSink,
	 pProtocolData: ptr PROTOCOLDATA

;void
IInternetProtocolSink_Switch_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolSink_ReportProgress_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolSink,
	  ulStatusCode: ULONG,
	  szStatusText: LPCWSTR

;void
IInternetProtocolSink_ReportProgress_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolSink_ReportData_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolSink,
	       grfBSCF: DWORD,
	    ulProgress: ULONG,
	 ulProgressMax: ULONG

;void
IInternetProtocolSink_ReportData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolSink_ReportResult_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolSink,
	      hrResult: HRESULT,
	       dwError: DWORD,
	      szResult: LPCWSTR

;void
IInternetProtocolSink_ReportResult_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETSESSION_DEFINED
_LPIINTERNETSESSION_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0127_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0127_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetSession_INTERFACE_DEFINED__
__IInternetSession_INTERFACE_DEFINED__ equ 1

;typedef enum _tagOIBDG_FLAGS

OIBDG_APARTMENTTHREADED equ 0x100

IInternetSessionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RegisterNameSpace, :ptr, :REFCLSID, :LPWSTR, :DWORD, :ptr, :DWORD
	STDMETHOD	UnregisterNameSpace, :LPWSTR
	STDMETHOD	RegisterMimeFilter, :ptr, :REFCLSID, :LPWSTR
	STDMETHOD	UnregisterMimeFilter, :ptr, :LPWSTR
	STDMETHOD	CreateBinding, :LPBC, :LPWSTR, :ptr, :ptr, :ptr, :DWORD
	STDMETHOD	SetSessionOption, :DWORD, :PVOID, :DWORD, :DWORD
	STDMETHOD	GetSessionOption, :DWORD, :PVOID, :ptr, :DWORD
IInternetSessionVtbl ends
IInternetSession struct
	lpVtbl		PVOID ?
IInternetSession ends
LPIINTERNETSESSION	typedef ptr IInternetSession
externdef		IID_IInternetSession:IID

;HRESULT
IInternetSession_RegisterNameSpace_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
		rclsid: REFCLSID,
	   pwzProtocol: LPCWSTR,
	     cPatterns: ULONG,
	  ppwzPatterns: ptr LPCWSTR,
	    dwReserved: DWORD

;void
IInternetSession_RegisterNameSpace_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSession_UnregisterNameSpace_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
	   pszProtocol: LPCWSTR

;void
IInternetSession_UnregisterNameSpace_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSession_RegisterMimeFilter_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
		rclsid: REFCLSID,
	       pwzType: LPCWSTR

;void
IInternetSession_RegisterMimeFilter_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSession_UnregisterMimeFilter_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
	       pwzType: LPCWSTR

;void
IInternetSession_UnregisterMimeFilter_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSession_CreateBinding_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
		   pBC: LPBC,
		 szUrl: LPCWSTR,
	     pUnkOuter: ptr IUnknown,
		 ppUnk: ptr IUnknown,
	   ppOInetProt: ptr IInternetProtocol,
	      dwOption: DWORD

;void
IInternetSession_CreateBinding_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSession_SetSessionOption_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
	    dwReserved: DWORD

;void
IInternetSession_SetSessionOption_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSession_GetSessionOption_Proxy proto WINAPI \
		 pThis: ptr IInternetSession,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
       pdwBufferLength: LPDWORD,
	    dwReserved: DWORD

;void
IInternetSession_GetSessionOption_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETTHREADSWITCH_DEFINED
_LPIINTERNETTHREADSWITCH_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0128_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0128_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetThreadSwitch_INTERFACE_DEFINED__
__IInternetThreadSwitch_INTERFACE_DEFINED__ equ 1

IInternetThreadSwitchVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Prepare
	STDMETHOD	Continue, :ptr, :PRPC_MESSAGE, :ptr
IInternetThreadSwitchVtbl ends
IInternetThreadSwitch struct
	lpVtbl		PVOID ?
IInternetThreadSwitch ends
LPIINTERNETTHREADSWITCH typedef ptr IInternetThreadSwitch
externdef		IID_IInternetThreadSwitch:IID

;HRESULT
IInternetThreadSwitch_Prepare_Proxy proto WINAPI \
		 pThis: ptr IInternetThreadSwitch

;void
IInternetThreadSwitch_Prepare_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetThreadSwitch_Continue_Proxy proto WINAPI \
		 pThis: ptr IInternetThreadSwitch

;void
IInternetThreadSwitch_Continue_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETPRIORITY_DEFINED
_LPIINTERNETPRIORITY_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0129_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0129_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetPriority_INTERFACE_DEFINED__
__IInternetPriority_INTERFACE_DEFINED__ equ 1

IInternetPriorityVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetPriority, :LONG
	STDMETHOD	GetPriority, :ptr
IInternetPriorityVtbl ends
IInternetPriority struct
	lpVtbl		PVOID ?
IInternetPriority ends
LPIINTERNETPRIORITY	typedef ptr IInternetPriority
externdef		IID_IInternetPriority:IID

;HRESULT
IInternetPriority_SetPriority_Proxy proto WINAPI \
		 pThis: ptr IInternetPriority,
	     nPriority: LONG

;void
IInternetPriority_SetPriority_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetPriority_GetPriority_Proxy proto WINAPI \
		 pThis: ptr IInternetPriority,
	    pnPriority: ptr LONG

;void
IInternetPriority_GetPriority_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPIINTERNETPROTOCOLINFO_DEFINED
_LPIINTERNETPROTOCOLINFO_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0130_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0130_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetProtocolInfo_INTERFACE_DEFINED__
__IInternetProtocolInfo_INTERFACE_DEFINED__ equ 1

LPIINTERNETPROTOCOLINFO typedef ptr IInternetProtocolInfo

PARSEACTION		typedef SDWORD
PARSE_CANONICALIZE	equ 1
PARSE_FRIENDLY		equ PARSE_CANONICALIZE + 1
PARSE_SECURITY_URL	equ PARSE_FRIENDLY + 1
PARSE_ROOTDOCUMENT	equ PARSE_SECURITY_URL + 1
PARSE_DOCUMENT		equ PARSE_ROOTDOCUMENT + 1
PARSE_ANCHOR		equ PARSE_DOCUMENT + 1
PARSE_ENCODE		equ PARSE_ANCHOR + 1
PARSE_DECODE		equ PARSE_ENCODE + 1
PARSE_PATH_FROM_URL	equ PARSE_DECODE + 1
PARSE_URL_FROM_PATH	equ PARSE_PATH_FROM_URL + 1
PARSE_MIME		equ PARSE_URL_FROM_PATH + 1
PARSE_SERVER		equ PARSE_MIME + 1
PARSE_SCHEMA		equ PARSE_SERVER + 1
PARSE_SITE		equ PARSE_SCHEMA + 1
PARSE_DOMAIN		equ PARSE_SITE + 1
PARSE_LOCATION		equ PARSE_DOMAIN + 1
PARSE_SECURITY_DOMAIN	equ PARSE_LOCATION + 1

PSUACTION		typedef SDWORD
PSU_DEFAULT		equ 1
PSU_SECURITY_URL_ONLY	equ PSU_DEFAULT + 1

QUERYOPTION		typedef SDWORD
QUERY_EXPIRATION_DATE	equ 1
QUERY_TIME_OF_LAST_CHANGE equ QUERY_EXPIRATION_DATE + 1
QUERY_CONTENT_ENCODING	equ QUERY_TIME_OF_LAST_CHANGE + 1
QUERY_CONTENT_TYPE	equ QUERY_CONTENT_ENCODING + 1
QUERY_REFRESH		equ QUERY_CONTENT_TYPE + 1
QUERY_RECOMBINE		equ QUERY_REFRESH + 1
QUERY_CAN_NAVIGATE	equ QUERY_RECOMBINE + 1
QUERY_USES_NETWORK	equ QUERY_CAN_NAVIGATE + 1
QUERY_IS_CACHED		equ QUERY_USES_NETWORK + 1
QUERY_IS_INSTALLEDENTRY equ QUERY_IS_CACHED + 1
QUERY_IS_CACHED_OR_MAPPED equ QUERY_IS_INSTALLEDENTRY + 1
QUERY_USES_CACHE	equ QUERY_IS_CACHED_OR_MAPPED + 1

externdef		IID_IInternetProtocolInfo:IID

IInternetProtocolInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParseUrl, :LPWSTR, :PARSEACTION, :DWORD, :LPWSTR, :DWORD, :ptr, :DWORD
	STDMETHOD	CombineUrl, :LPWSTR, :LPWSTR, :DWORD, :LPWSTR, :DWORD, :ptr, :DWORD
	STDMETHOD	CompareUrl, :LPWSTR, :LPWSTR, :DWORD
	STDMETHOD	QueryInfo, :LPWSTR, :QUERYOPTION, :DWORD, :PVOID, :DWORD, :ptr, :DWORD
IInternetProtocolInfoVtbl ends
IInternetProtocolInfo struct
	lpVtbl		PVOID ?
IInternetProtocolInfo ends

;HRESULT
IInternetProtocolInfo_ParseUrl_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolInfo,
		pwzUrl: LPCWSTR,
	   ParseAction: PARSEACTION,
	  dwParseFlags: DWORD,
	     pwzResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: LPDWORD,
	    dwReserved: DWORD

;void
IInternetProtocolInfo_ParseUrl_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolInfo_CombineUrl_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolInfo,
	    pwzBaseUrl: LPCWSTR,
	pwzRelativeUrl: LPCWSTR,
	dwCombineFlags: DWORD,
	     pwzResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: LPDWORD,
	    dwReserved: DWORD

;void
IInternetProtocolInfo_CombineUrl_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolInfo_CompareUrl_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolInfo,
	       pwzUrl1: LPCWSTR,
	       pwzUrl2: LPCWSTR,
	dwCompareFlags: DWORD

;void
IInternetProtocolInfo_CompareUrl_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetProtocolInfo_QueryInfo_Proxy proto WINAPI \
		 pThis: ptr IInternetProtocolInfo,
		pwzUrl: LPCWSTR,
	   OueryOption: QUERYOPTION,
	  dwQueryFlags: DWORD,
	       pBuffer: LPVOID,
	      cbBuffer: DWORD,
		pcbBuf: LPDWORD,
	    dwReserved: DWORD

;void
IInternetProtocolInfo_QueryInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif

IOInet			equ <IInternet>
IOInetBindInfo		equ <IInternetBindInfo>
IOInetProtocolRoot	equ <IInternetProtocolRoot>
IOInetProtocol		equ <IInternetProtocol>
IOInetProtocolSink	equ <IInternetProtocolSink>
IOInetProtocolInfo	equ <IInternetProtocolInfo>
IOInetSession		equ <IInternetSession>
IOInetPriority		equ <IInternetPriority>
IOInetThreadSwitch	equ <IInternetThreadSwitch>
LPOINET			equ <LPIINTERNET>
LPOINETPROTOCOLINFO	equ <LPIINTERNETPROTOCOLINFO>
LPOINETBINDINFO		equ <LPIINTERNETBINDINFO>
LPOINETPROTOCOLROOT	equ <LPIINTERNETPROTOCOLROOT>
LPOINETPROTOCOL		equ <LPIINTERNETPROTOCOL>
LPOINETPROTOCOLSINK	equ <LPIINTERNETPROTOCOLSINK>
LPOINETSESSION		equ <LPIINTERNETSESSION>
LPOINETTHREADSWITCH	equ <LPIINTERNETTHREADSWITCH>
LPOINETPRIORITY		equ <LPIINTERNETPRIORITY>
LPOINETPROTOCOLINFO	equ <LPIINTERNETPROTOCOLINFO>
IID_IOInet		equ <IID_IInternet>
IID_IOInetBindInfo	equ <IID_IInternetBindInfo>
IID_IOInetProtocolRoot	equ <IID_IInternetProtocolRoot>
IID_IOInetProtocol	equ <IID_IInternetProtocol>
IID_IOInetProtocolSink	equ <IID_IInternetProtocolSink>
IID_IOInetProtocolInfo	equ <IID_IInternetProtocolInfo>
IID_IOInetSession	equ <IID_IInternetSession>
IID_IOInetPriority	equ <IID_IInternetPriority>
IID_IOInetThreadSwitch	equ <IID_IInternetThreadSwitch>

;STDAPI
CoInternetParseUrl proto WINAPI \
		pwzUrl: LPCWSTR,
	   ParseAction: PARSEACTION,
	       dwFlags: DWORD,
	     pszResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetCombineUrl proto WINAPI \
	    pwzBaseUrl: LPCWSTR,
	pwzRelativeUrl: LPCWSTR,
	dwCombineFlags: DWORD,
	     pszResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetCompareUrl proto WINAPI \
	       pwzUrl1: LPCWSTR,
	       pwzUrl2: LPCWSTR,
	       dwFlags: DWORD

;STDAPI
CoInternetGetProtocolFlags proto WINAPI \
		pwzUrl: LPCWSTR,
	      pdwFlags: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetQueryInfo proto WINAPI \
		pwzUrl: LPCWSTR,
	  QueryOptions: QUERYOPTION,
	  dwQueryFlags: DWORD,
	      pvBuffer: LPVOID,
	      cbBuffer: DWORD,
	     pcbBuffer: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetGetSession proto WINAPI \
	 dwSessionMode: DWORD,
    ppIInternetSession: ptr IInternetSession,
	    dwReserved: DWORD

;STDAPI
CoInternetGetSecurityUrl proto WINAPI \
		pwzUrl: LPCWSTR,
	    ppwzSecUrl: ptr LPWSTR,
	     psuAction: PSUACTION,
	    dwReserved: DWORD


;STDAPI
CopyStgMedium proto WINAPI \
	   pcstgmedSrc: ptr STGMEDIUM,
	   pstgmedDest: ptr STGMEDIUM

;STDAPI
CopyBindInfo proto WINAPI \
	       pcbiSrc: ptr BINDINFO,
	       pbiDest: ptr BINDINFO

;STDAPI_(void)
ReleaseBindInfo proto WINAPI \
	     pbindinfo: ptr BINDINFO


INET_E_USE_DEFAULT_PROTOCOLHANDLER equ _HRESULT_TYPEDEF_(0x800C0011)
INET_E_USE_DEFAULT_SETTING equ _HRESULT_TYPEDEF_(0x800C0012)
INET_E_DEFAULT_ACTION	equ INET_E_USE_DEFAULT_PROTOCOLHANDER
INET_E_QUERYOPTION_UNKNOWN equ _HRESULT_TYPEDEF_(0x800C0013)
INET_E_REDIRECTING	equ _HRESULT_TYPEDEF_(0x800C0014)
OInetParseUrl		equ <CoInternetParseUrl>
OInetCombineUrl		equ <CoInternetCombineUrl>
OInetCompareUrl		equ <CoInternetCompareUrl>
OInetQueryInfo		equ <CoInternetQueryInfo>
OInetGetSession		equ <CoInternetGetSession>
endif
PROTOCOLFLAG_NO_PICS_CHECK equ 0x00000001

;STDAPI
CoInternetCreateSecurityManager proto WINAPI \
		   pSP: ptr IServiceProvider,
		  ppSM: ptr IInternetSecurityManager,
	    dwReserved: DWORD

;STDAPI
CoInternetCreateZoneManager proto WINAPI \
		   pSP: ptr IServiceProvider,
		  ppZM: ptr IInternetZoneManager,
	    dwReserved: DWORD

externdef		CLSID_InternetSecurityManager:IID
externdef		CLSID_InternetZoneManager:IID
SID_SInternetSecurityManager equ IID_IInternetSecurityManager

SID_SInternetHostSecurityManager equ IID_IInternetHostSecurityManager

ifndef _LPINTERNETSECURITYMGRSITE_DEFINED
_LPINTERNETSECURITYMGRSITE_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0131_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0131_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetSecurityMgrSite_INTERFACE_DEFINED__
__IInternetSecurityMgrSite_INTERFACE_DEFINED__ equ 1

externdef		IID_IInternetSecurityMgrSite:IID

IInternetSecurityMgrSiteVtbl	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow, :ptr
	STDMETHOD	EnableModeless, :BOOL
IInternetSecurityMgrSiteVtbl ENDS

;HRESULT
IInternetSecurityMgrSite_GetWindow_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityMgrSite,
		 phwnd: ptr HWND

;void
IInternetSecurityMgrSite_GetWindow_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityMgrSite_EnableModeless_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityMgrSite,
	       fEnable: BOOL

;void
IInternetSecurityMgrSite_EnableModeless_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPINTERNETSECURITYMANANGER_DEFINED
_LPINTERNETSECURITYMANANGER_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0132_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0132_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetSecurityManager_INTERFACE_DEFINED__
__IInternetSecurityManager_INTERFACE_DEFINED__ equ 1

MAX_SIZE_SECURITY_ID	equ 512
;typedef enum __MIDL_IInternetSecurityManager_0001

PUAF_DEFAULT		equ 0
PUAF_NOUI		equ 0x1
PUAF_ISFILE		equ 0x2
PUAF_WARN_IF_DENIED	equ 0x4
PUAF_FORCEUI_FOREGROUND equ 0x8
PUAF_CHECK_TIFS		equ 0x10

;typedef enum __MIDL_IInternetSecurityManager_0002

SZM_CREATE		equ 0
SZM_DELETE		equ 0x1

externdef		IID_IInternetSecurityManager:IID

IInternetSecurityManagerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetSecuritySite, :ptr
	STDMETHOD	GetSecuritySite
	STDMETHOD	MapUrlToZone, :LPWSTR, :ptr, :DWORD
	STDMETHOD	GetSecurityId, :LPWSTR, :ptr, :ptr, :DWORD
	STDMETHOD	ProcessUrlAction, :LPWSTR, :DWORD, :ptr, :DWORD, :ptr, :DWORD, :DWORD, :DWORD
	STDMETHOD	QueryCustomPolicy, :LPWSTR, :REFGUID, :ptr, :ptr, :ptr, :DWORD, :DWORD
	STDMETHOD	SetZoneMapping, :DWORD, :LPWSTR, :DWORD
	STDMETHOD	GetZoneMappings, :DWORD, :ptr, :DWORD
IInternetSecurityManagerVtbl ends
IInternetSecurityManager struct
	lpVtbl		PVOID ?
IInternetSecurityManager ends

;HRESULT
IInternetSecurityManager_SetSecuritySite_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
		 pSite: ptr IInternetSecurityMgrSite

;void
IInternetSecurityManager_SetSecuritySite_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_GetSecuritySite_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
		ppSite: ptr IInternetSecurityMgrSite

;void
IInternetSecurityManager_GetSecuritySite_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_MapUrlToZone_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	       pdwZone: LPDWORD,
	       dwFlags: DWORD

;void
IInternetSecurityManager_MapUrlToZone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_GetSecurityId_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	  pbSecurityId: LPBYTE,
	 pcbSecurityId: LPDWORD,
	    dwReserved: DWORD

;void
IInternetSecurityManager_GetSecurityId_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_ProcessUrlAction_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	       dwFlags: DWORD,
	    dwReserved: DWORD

;void
IInternetSecurityManager_ProcessUrlAction_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_QueryCustomPolicy_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	    dwReserved: DWORD

;void
IInternetSecurityManager_QueryCustomPolicy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_SetZoneMapping_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
		dwZone: DWORD,
	   lpszPattern: LPCWSTR,
	       dwFlags: DWORD

;void
IInternetSecurityManager_SetZoneMapping_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetSecurityManager_GetZoneMappings_Proxy proto WINAPI \
		 pThis: ptr IInternetSecurityManager,
		dwZone: DWORD,
	  ppenumString: ptr IEnumString,
	       dwFlags: DWORD

;void
IInternetSecurityManager_GetZoneMappings_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _LPINTERNETHOSTSECURITYMANANGER_DEFINED
_LPINTERNETHOSTSECURITYMANANGER_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0133_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0133_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetHostSecurityManager_INTERFACE_DEFINED__
__IInternetHostSecurityManager_INTERFACE_DEFINED__ equ 1

externdef		IID_IInternetHostSecurityManager:IID

IInternetHostSecurityManagerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetSecurityId, :ptr, :ptr, :DWORD
	STDMETHOD	ProcessUrlAction, :DWORD, :ptr, :DWORD, :ptr, :DWORD, :DWORD, :DWORD
	STDMETHOD	QueryCustomPolicy, :REFGUID, :ptr, :ptr, :ptr, :DWORD, :DWORD
IInternetHostSecurityManagerVtbl ends
IInternetHostSecurityManager struct
	lpVtbl		PVOID ?
IInternetHostSecurityManager ends

;HRESULT
IInternetHostSecurityManager_GetSecurityId_Proxy proto WINAPI \
		 pThis: ptr IInternetHostSecurityManager,
	  pbSecurityId: LPBYTE,
	 pcbSecurityId: LPDWORD,
	    dwReserved: DWORD

;void
IInternetHostSecurityManager_GetSecurityId_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetHostSecurityManager_ProcessUrlAction_Proxy proto WINAPI \
		 pThis: ptr IInternetHostSecurityManager,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	       dwFlags: DWORD,
	    dwReserved: DWORD

;void
IInternetHostSecurityManager_ProcessUrlAction_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetHostSecurityManager_QueryCustomPolicy_Proxy proto WINAPI \
		 pThis: ptr IInternetHostSecurityManager,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	    dwReserved: DWORD

;void
IInternetHostSecurityManager_QueryCustomPolicy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif

URLACTION_MIN		equ 0x00001000
URLACTION_DOWNLOAD_MIN	equ 0x00001000
URLACTION_DOWNLOAD_SIGNED_ACTIVEX equ 0x00001001
URLACTION_DOWNLOAD_UNSIGNED_ACTIVEX equ 0x00001004
URLACTION_DOWNLOAD_CURR_MAX equ 0x00001004
URLACTION_DOWNLOAD_MAX	equ 0x000011FF

URLACTION_ACTIVEX_MIN	equ 0x00001200
URLACTION_ACTIVEX_RUN	equ 0x00001200
URLACTION_ACTIVEX_OVERRIDE_OBJECT_SAFETY equ 0x00001201
URLACTION_ACTIVEX_OVERRIDE_DATA_SAFETY equ 0x00001202
URLACTION_ACTIVEX_OVERRIDE_SCRIPT_SAFETY equ 0x00001203
URLACTION_SCRIPT_OVERRIDE_SAFETY equ 0x00001401
URLACTION_ACTIVEX_CONFIRM_NOOBJECTSAFETY equ 0x00001204
URLACTION_ACTIVEX_TREATASUNTRUSTED equ 0x00001205
URLACTION_ACTIVEX_CURR_MAX equ 0x00001205
URLACTION_ACTIVEX_MAX	equ 0x000013ff

URLACTION_SCRIPT_MIN	equ 0x00001400
URLACTION_SCRIPT_RUN	equ 0x00001400
URLACTION_SCRIPT_JAVA_USE equ 0x00001402
URLACTION_SCRIPT_SAFE_ACTIVEX equ 0x00001405
URLACTION_SCRIPT_CURR_MAX equ 0x00001405
URLACTION_SCRIPT_MAX	equ 0x000015ff

URLACTION_HTML_MIN	equ 0x00001600
URLACTION_HTML_SUBMIT_FORMS equ 0x00001601
URLACTION_HTML_SUBMIT_FORMS_FROM equ 0x00001602
URLACTION_HTML_SUBMIT_FORMS_TO equ 0x00001603
URLACTION_HTML_FONT_DOWNLOAD equ 0x00001604
URLACTION_HTML_JAVA_RUN equ 0x00001605
URLACTION_HTML_CURR_MAX equ 0x00001605
URLACTION_HTML_MAX	equ 0x000017ff

URLACTION_SHELL_MIN	equ 0x00001800
URLACTION_SHELL_INSTALL_DTITEMS equ 0x00001800
URLACTION_SHELL_MOVE_OR_COPY equ 0x00001802
URLACTION_SHELL_FILE_DOWNLOAD equ 0x00001803
URLACTION_SHELL_VERB	equ 0x00001804
URLACTION_SHELL_WEBVIEW_VERB equ 0x00001805
URLACTION_SHELL_CURR_MAX equ 0x00001805
URLACTION_SHELL_MAX	equ 0x000019ff

URLACTION_NETWORK_MIN	equ 0x00001A00

URLACTION_CREDENTIALS_USE equ 0x00001A00
URLPOLICY_CREDENTIALS_SILENT_LOGON_OK equ 0x00000000
URLPOLICY_CREDENTIALS_MUST_PROMPT_USER equ 0x00010000
URLPOLICY_CREDENTIALS_CONDITIONAL_PROMPT equ 0x00020000
URLPOLICY_CREDENTIALS_ANONYMOUS_ONLY equ 0x00030000

URLACTION_AUTHENTICATE_CLIENT equ 0x00001A01
URLPOLICY_AUTHENTICATE_CLEARTEXT_OK equ 0x00000000
URLPOLICY_AUTHENTICATE_CHALLENGE_RESPONSE equ 0x00010000
URLPOLICY_AUTHENTICATE_MUTUAL_ONLY equ 0x00030000


URLACTION_NETWORK_CURR_MAX equ 0x00001A01
URLACTION_NETWORK_MAX	equ 0x00001Bff


URLACTION_JAVA_MIN	equ 0x00001C00
URLACTION_JAVA_PERMISSIONS equ 0x00001C00
URLPOLICY_JAVA_PROHIBIT equ 0x00000000
URLPOLICY_JAVA_HIGH	equ 0x00010000
URLPOLICY_JAVA_MEDIUM	equ 0x00020000
URLPOLICY_JAVA_LOW	equ 0x00030000
URLPOLICY_JAVA_CUSTOM	equ 0x00800000
URLACTION_JAVA_CURR_MAX equ 0x00001C00
URLACTION_JAVA_MAX	equ 0x00001Cff



URLACTION_INFODELIVERY_MIN equ 0x00001D00
URLACTION_INFODELIVERY_NO_ADDING_CHANNELS equ 0x00001D00
URLACTION_INFODELIVERY_NO_EDITING_CHANNELS equ 0x00001D01
URLACTION_INFODELIVERY_NO_REMOVING_CHANNELS equ 0x00001D02
URLACTION_INFODELIVERY_NO_ADDING_SUBSCRIPTIONS equ 0x00001D03
URLACTION_INFODELIVERY_NO_EDITING_SUBSCRIPTIONS equ 0x00001D04
URLACTION_INFODELIVERY_NO_REMOVING_SUBSCRIPTIONS equ 0x00001D05
URLACTION_INFODELIVERY_NO_CHANNEL_LOGGING equ 0x00001D06
URLACTION_INFODELIVERY_CURR_MAX equ 0x00001D06
URLACTION_INFODELIVERY_MAX equ 0x00001Dff
URLACTION_CHANNEL_SOFTDIST_MIN equ 0x00001E00
URLACTION_CHANNEL_SOFTDIST_PERMISSIONS equ 0x00001E05
URLPOLICY_CHANNEL_SOFTDIST_PROHIBIT equ 0x00010000
URLPOLICY_CHANNEL_SOFTDIST_PRECACHE equ 0x00020000
URLPOLICY_CHANNEL_SOFTDIST_AUTOINSTALL equ 0x00030000
URLACTION_CHANNEL_SOFTDIST_MAX equ 0x00001Eff


URLPOLICY_ALLOW		equ 0x00
URLPOLICY_QUERY		equ 0x01
URLPOLICY_DISALLOW	equ 0x03

URLPOLICY_NOTIFY_ON_ALLOW equ 0x10
URLPOLICY_NOTIFY_ON_DISALLOW equ 0x20

URLPOLICY_LOG_ON_ALLOW	equ 0x40
URLPOLICY_LOG_ON_DISALLOW equ 0x80

URLPOLICY_MASK_PERMISSIONS equ 0x0f
GetUrlPolicyPermissions macro dw
	exitm<(dw AND URLPOLICY_MASK_PERMISSIONS)>
	endm
SetUrlPolicyPermissions macro dw,dw2
	exitm<((dw) = ((dw) AND NOT (URLPOLICY_MASK_PERMISSIONS)) OR (dw2))>
	endm


ifndef _LPINTERNETZONEMANAGER_DEFINED
_LPINTERNETZONEMANAGER_DEFINED equ 1

externdef		__MIDL_itf_urlmon_0134_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0134_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetZoneManager_INTERFACE_DEFINED__
__IInternetZoneManager_INTERFACE_DEFINED__ equ 1

;typedef enum tagURLZONE

URLZONE_PREDEFINED_MIN	equ 0
URLZONE_LOCAL_MACHINE	equ 0
URLZONE_INTRANET	equ URLZONE_LOCAL_MACHINE + 1
URLZONE_TRUSTED		equ URLZONE_INTRANET + 1
URLZONE_INTERNET	equ URLZONE_TRUSTED + 1
URLZONE_UNTRUSTED	equ URLZONE_INTERNET + 1
URLZONE_PREDEFINED_MAX	equ 999
URLZONE_USER_MIN	equ 1000
URLZONE_USER_MAX	equ 10000

URLTEMPLATE		typedef SDWORD
URLTEMPLATE_CUSTOM	equ 0
URLTEMPLATE_PREDEFINED_MIN equ 0x10000
URLTEMPLATE_LOW		equ 0x10000
URLTEMPLATE_MEDIUM	equ 0x11000
URLTEMPLATE_HIGH	equ 0x12000
URLTEMPLATE_PREDEFINED_MAX equ 0x20000


;enum __MIDL_IInternetZoneManager_0001
MAX_ZONE_PATH		equ 260
MAX_ZONE_DESCRIPTION	equ 200

;typedef enum __MIDL_IInternetZoneManager_0002

ZAFLAGS_CUSTOM_EDIT	equ 0x1
ZAFLAGS_ADD_SITES	equ 0x2
ZAFLAGS_REQUIRE_VERIFICATION equ 0x4
ZAFLAGS_INCLUDE_PROXY_OVERRIDE equ 0x8
ZAFLAGS_INCLUDE_INTRANET_SITES equ 0x10
ZAFLAGS_NO_UI		equ 0x20
ZAFLAGS_SUPPORTS_VERIFICATION equ 0x40
ZAFLAGS_UNC_AS_INTRANET equ 0x80

ZONEATTRIBUTES		STRUC
cbSize			dd ?
szDisplayName		WCHAR 260 dup(?)
szDescription		WCHAR 200 dup(?)
szIconPath		WCHAR 260 dup(?)
dwTemplateMinLevel	dd ?
dwTemplateRecommended	dd ?
dwTemplateCurrentLevel	dd ?
dwFlags			dd ?
ZONEATTRIBUTES		ENDS
LPZONEATTRIBUTES	typedef ptr ZONEATTRIBUTES

URLZONEREG		typedef SDWORD
URLZONEREG_DEFAULT	equ 0
URLZONEREG_HKLM		equ URLZONEREG_DEFAULT + 1
URLZONEREG_HKCU		equ URLZONEREG_HKLM + 1

IInternetZoneManagerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetZoneAttributes, :DWORD, :ptr
	STDMETHOD	SetZoneAttributes, :DWORD, :ptr
	STDMETHOD	GetZoneCustomPolicy, :DWORD, :REFGUID, :ptr, :ptr, :URLZONEREG
	STDMETHOD	SetZoneCustomPolicy, :DWORD, :REFGUID, :ptr, :DWORD, :URLZONEREG
	STDMETHOD	GetZoneActionPolicy, :DWORD, :DWORD, :ptr, :DWORD, :URLZONEREG
	STDMETHOD	SetZoneActionPolicy, :DWORD, :DWORD, :ptr, :DWORD, :URLZONEREG
	STDMETHOD	PromptAction, :DWORD, :HWND, :LPWSTR, :LPWSTR, :DWORD
	STDMETHOD	LogAction, :DWORD, :LPWSTR, :LPWSTR, :DWORD
	STDMETHOD	CreateZoneEnumerator, :ptr, :ptr, :DWORD
	STDMETHOD	GetZoneAt, :DWORD, :DWORD, :ptr
	STDMETHOD	DestroyZoneEnumerator, :DWORD
	STDMETHOD	CopyTemplatePoliciesToZone, :DWORD, :DWORD, :DWORD
IInternetZoneManagerVtbl ends
IInternetZoneManager struct
	lpVtbl		PVOID ?
IInternetZoneManager ends
LPURLZONEMANAGER	typedef ptr IInternetZoneManager
externdef		IID_IInternetZoneManager:IID

;HRESULT
IInternetZoneManager_GetZoneAttributes_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
       pZoneAttributes: ptr ZONEATTRIBUTES

;void
IInternetZoneManager_GetZoneAttributes_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_SetZoneAttributes_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
       pZoneAttributes: ptr ZONEATTRIBUTES

;void
IInternetZoneManager_SetZoneAttributes_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_GetZoneCustomPolicy_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	    urlZoneReg: URLZONEREG

;void
IInternetZoneManager_GetZoneCustomPolicy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_SetZoneCustomPolicy_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	       guidKey: REFGUID,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG

;void
IInternetZoneManager_SetZoneCustomPolicy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_GetZoneActionPolicy_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG

;void
IInternetZoneManager_GetZoneActionPolicy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_SetZoneActionPolicy_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG

;void
IInternetZoneManager_SetZoneActionPolicy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_PromptAction_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
	      dwAction: DWORD,
	    hwndParent: HWND,
	       pwszUrl: LPCWSTR,
	      pwszText: LPCWSTR,
	 dwPromptFlags: DWORD

;void
IInternetZoneManager_PromptAction_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_LogAction_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
	      dwAction: DWORD,
	       pwszUrl: LPCWSTR,
	      pwszText: LPCWSTR,
	    dwLogFlags: DWORD

;void
IInternetZoneManager_LogAction_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_CreateZoneEnumerator_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
	       pdwEnum: LPDWORD,
	      pdwCount: LPDWORD,
	       dwFlags: DWORD

;void
IInternetZoneManager_CreateZoneEnumerator_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_GetZoneAt_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwEnum: DWORD,
	       dwIndex: DWORD,
	       pdwZone: LPDWORD

;void
IInternetZoneManager_GetZoneAt_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_DestroyZoneEnumerator_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
		dwEnum: DWORD

;void
IInternetZoneManager_DestroyZoneEnumerator_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IInternetZoneManager_CopyTemplatePoliciesToZone_Proxy proto WINAPI \
		 pThis: ptr IInternetZoneManager,
	    dwTemplate: DWORD,
		dwZone: DWORD,
	    dwReserved: DWORD

;void
IInternetZoneManager_CopyTemplatePoliciesToZone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
externdef		CLSID_SoftDistExt:IID
ifndef _LPSOFTDISTEXT_DEFINED
_LPSOFTDISTEXT_DEFINED equ 1

SOFTDIST_FLAG_USAGE_EMAIL equ 0x00000001
SOFTDIST_FLAG_USAGE_PRECACHE equ 0x00000002
SOFTDIST_FLAG_USAGE_AUTOINSTALL equ 0x00000004
SOFTDIST_FLAG_DELETE_SUBSCRIPTION equ 0x00000008


SOFTDIST_ADSTATE_NONE	equ 0x00000000
SOFTDIST_ADSTATE_AVAILABLE equ 0x00000001
SOFTDIST_ADSTATE_DOWNLOADED equ 0x00000002
SOFTDIST_ADSTATE_INSTALLED equ 0x00000003

CODEBASEHOLD		STRUC
cbSize			ULONG ?
szDistUnit		LPWSTR ?
szCodeBase		LPWSTR ?
dwVersionMS		dd ?
dwVersionLS		dd ?
dwStyle			dd ?
CODEBASEHOLD		ENDS
LPCODEBASEHOLD		typedef ptr CODEBASEHOLD

SOFTDISTINFO		STRUC
cbSize			ULONG ?
dwFlags			dd ?
dwAdState		dd ?
szTitle			LPWSTR ?
szAbstract		LPWSTR ?
szHREF			LPWSTR ?
dwInstalledVersionMS	dd ?
dwInstalledVersionLS	dd ?
dwUpdateVersionMS	dd ?
dwUpdateVersionLS	dd ?
dwAdvertisedVersionMS	dd ?
dwAdvertisedVersionLS	dd ?
dwReserved		dd ?
SOFTDISTINFO		ENDS
LPSOFTDISTINFO		typedef ptr SOFTDISTINFO

externdef		__MIDL_itf_urlmon_0135_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0135_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __ISoftDistExt_INTERFACE_DEFINED__
__ISoftDistExt_INTERFACE_DEFINED__ equ 1

externdef		IID_ISoftDistExt:IID

ISoftDistExtVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ProcessSoftDist, :LPWSTR, :ptr, :LPSOFTDISTINFO
	STDMETHOD	GetFirstCodeBase, :ptr, :ptr
	STDMETHOD	GetNextCodeBase, :ptr, :ptr
	STDMETHOD	AsyncInstallDistributionUnit, :ptr, :LPVOID, :DWORD, :LPCODEBASEHOLD
ISoftDistExtVtbl ends
ISoftDistExt struct
	lpVtbl		PVOID ?
ISoftDistExt ends

;HRESULT
ISoftDistExt_ProcessSoftDist_Proxy proto WINAPI \
		 pThis: ptr ISoftDistExt,
	      szCDFURL: LPCWSTR,
      pSoftDistElement: ptr IXMLElement,
		 lpsdi: LPSOFTDISTINFO

;void
ISoftDistExt_ProcessSoftDist_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISoftDistExt_GetFirstCodeBase_Proxy proto WINAPI \
		 pThis: ptr ISoftDistExt,
	    szCodeBase: ptr LPWSTR,
	     dwMaxSize: LPDWORD

;void
ISoftDistExt_GetFirstCodeBase_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISoftDistExt_GetNextCodeBase_Proxy proto WINAPI \
		 pThis: ptr ISoftDistExt,
	    szCodeBase: ptr LPWSTR,
	     dwMaxSize: LPDWORD

;void
ISoftDistExt_GetNextCodeBase_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISoftDistExt_AsyncInstallDistributionUnit_Proxy proto WINAPI \
		 pThis: ptr ISoftDistExt,
		   pbc: ptr IBindCtx,
	    pvReserved: LPVOID,
		 flags: DWORD,
		 lpcbh: LPCODEBASEHOLD

;void
ISoftDistExt_AsyncInstallDistributionUnit_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

;STDAPI
GetSoftwareUpdateInfo proto WINAPI \
	    szDistUnit: LPCWSTR,
		  psdi: LPSOFTDISTINFO

;STDAPI
SetSoftwareUpdateAdvertisementState proto WINAPI \
	    szDistUnit: LPCWSTR,
	     dwAdState: DWORD,
 dwAdvertisedVersionMS: DWORD,
 dwAdvertisedVersionLS: DWORD

endif
ifndef _LPDATAFILTER_DEFINED
_LPDATAFILTER_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0136_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0136_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IDataFilter_INTERFACE_DEFINED__
__IDataFilter_INTERFACE_DEFINED__ equ 1

IDataFilterVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	DoEncode, :DWORD, :SDWORD, :ptr, :SDWORD, :ptr, :SDWORD, :ptr, :ptr, :DWORD
	STDMETHOD	DoDecode, :DWORD, :SDWORD, :ptr, :SDWORD, :ptr, :SDWORD, :ptr, :ptr, :DWORD
	STDMETHOD	SetEncodingLevel, :DWORD
IDataFilterVtbl ends
IDataFilter struct
	lpVtbl		PVOID ?
IDataFilter ends
LPDATAFILTER		typedef ptr IDataFilter
externdef		IID_IDataFilter:IID

;HRESULT
IDataFilter_DoEncode_Proxy proto WINAPI \
		 pThis: ptr IDataFilter,
	       dwFlags: DWORD,
	 lInBufferSize: LONG,
	    pbInBuffer: LPBYTE,
	lOutBufferSize: LONG,
	   pbOutBuffer: LPBYTE,
     lInBytesAvailable: LONG,
	 plInBytesRead: ptr LONG,
     plOutBytesWritten: ptr LONG,
	    dwReserved: DWORD

;void
IDataFilter_DoEncode_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataFilter_DoDecode_Proxy proto WINAPI \
		 pThis: ptr IDataFilter,
	       dwFlags: DWORD,
	 lInBufferSize: LONG,
	    pbInBuffer: LPBYTE,
	lOutBufferSize: LONG,
	   pbOutBuffer: LPBYTE,
     lInBytesAvailable: LONG,
	 plInBytesRead: LPLONG,
     plOutBytesWritten: LPLONG,
	    dwReserved: DWORD

;void
IDataFilter_DoDecode_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataFilter_SetEncodingLevel_Proxy proto WINAPI \
		 pThis: ptr IDataFilter,
	    dwEncLevel: DWORD

;void
IDataFilter_SetEncodingLevel_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif

ifndef _LPENCODINGFILTERFACTORY_DEFINED
_LPENCODINGFILTERFACTORY_DEFINED equ 1
PROTOCOLFILTERDATA	STRUC
cbSize			dd ?
pProtocolSink		PVOID ?;LPIInternetProtocolSink ?
pProtocol		PVOID ?;LPIInternetProtocol ?
pUnk			LPIUnknown ?
dwFilterFlags		dd ?
PROTOCOLFILTERDATA	ENDS

externdef		__MIDL_itf_urlmon_0137_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0137_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEncodingFilterFactory_INTERFACE_DEFINED__
__IEncodingFilterFactory_INTERFACE_DEFINED__ equ 1

DATAINFO		STRUC
ulTotalSize		dd ?
ulavrPacketSize		dd ?
ulConnectSpeed		dd ?
ulProcessorSpeed	dd ?
DATAINFO		ENDS

IEncodingFilterFactoryVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	FindBestFilter, :LPWSTR, :LPWSTR, :DATAINFO, :ptr
	STDMETHOD	GetDefaultFilter, :LPWSTR, :LPWSTR, :ptr
IEncodingFilterFactoryVtbl ends
IEncodingFilterFactory struct
	lpVtbl		PVOID ?
IEncodingFilterFactory ends
LPENCODINGFILTERFACTORY typedef ptr IEncodingFilterFactory
externdef		IID_IEncodingFilterFactory:IID

;HRESULT
IEncodingFilterFactory_FindBestFilter_Proxy proto WINAPI \
		 pThis: ptr IEncodingFilterFactory,
	     pwzCodeIn: LPCWSTR,
	    pwzCodeOut: LPCWSTR,
		  info: DATAINFO,
		  ppDF: ptr IDataFilter

;void
IEncodingFilterFactory_FindBestFilter_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEncodingFilterFactory_GetDefaultFilter_Proxy proto WINAPI \
		 pThis: ptr IEncodingFilterFactory,
	     pwzCodeIn: LPCWSTR,
	    pwzCodeOut: LPCWSTR,
		  ppDF: ptr IDataFilter

;void
IEncodingFilterFactory_GetDefaultFilter_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif
endif
ifndef _HITLOGGING_DEFINED
_HITLOGGING_DEFINED equ 1
;BOOL
IsLoggingEnabledA proto WINAPI \
		pszUrl: LPCTSTR
IsLoggingEnalbedW proto WINAPI \
	       pwszUrl: LPCWSTR
ifdef _UNICODE
IsLoggingEnabled	equ <IsLoggingEnabledW>
else
IsLoggingEnabled	equ <IsLoggingEnabledA>
endif
HIT_LOGGING_INFO	STRUC
dwStructSize		dd ?
lpszLoggedUrlName	LPSTR ?
StartTime		SYSTEMTIME <>
EndTime			SYSTEMTIME <>
lpszExtendedInfo	LPSTR ?
HIT_LOGGING_INFO	ENDS
LPHIT_LOGGING_INFO	typedef ptr HIT_LOGGING_INFO

;BOOL
WriteHitLogging proto WINAPI \
	 lpLogginginfo: LPHIT_LOGGING_INFO

endif


externdef		__MIDL_itf_urlmon_0138_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0138_v0_0_s_ifspec:RPC_IF_HANDLE

;HRESULT
IBinding_GetBindResult_Proxy proto WINAPI \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	   pdwReserved: LPDWORD

;HRESULT
IBinding_GetBindResult_Stub proto WINAPI \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	    dwReserved: DWORD

;HRESULT
IBindStatusCallback_GetBindInfo_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr BINDINFO

;HRESULT
IBindStatusCallback_GetBindInfo_Stub proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr RemBINDINFO,
	       pstgmed: ptr RemSTGMEDIUM

;HRESULT
IBindStatusCallback_OnDataAvailable_Proxy proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr FORMATETC,
	       pstgmed: ptr STGMEDIUM

;HRESULT
IBindStatusCallback_OnDataAvailable_Stub proto WINAPI \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr RemFORMATETC,
	       pstgmed: ptr RemSTGMEDIUM

;HRESULT
IWinInetInfo_QueryOption_Proxy proto WINAPI \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD

;HRESULT
IWinInetInfo_QueryOption_Stub proto WINAPI \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD

;HRESULT
IWinInetHttpInfo_QueryInfo_Proxy proto WINAPI \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD

;HRESULT
IWinInetHttpInfo_QueryInfo_Stub proto WINAPI \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD

;HRESULT
IBindHost_MonikerBindToStorage_Proxy proto WINAPI \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: PVOID

;HRESULT
IBindHost_MonikerBindToStorage_Stub proto WINAPI \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown

;HRESULT
IBindHost_MonikerBindToObject_Proxy proto WINAPI \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: PVOID

;HRESULT
IBindHost_MonikerBindToObject_Stub proto WINAPI \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown

.list
endif
