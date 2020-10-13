include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __urlmon_h__
__urlmon_h__ equ <>

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
ifndef __IUri_FWD_DEFINED__
__IUri_FWD_DEFINED__ equ 1
endif
ifndef __IUriContainer_FWD_DEFINED__
__IUriContainer_FWD_DEFINED__ equ 1
endif
ifndef __IUriBuilder_FWD_DEFINED__
__IUriBuilder_FWD_DEFINED__ equ 1
endif


ifndef __IUriBuilderFactory_FWD_DEFINED__
__IUriBuilderFactory_FWD_DEFINED__ equ 1
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

MIDL_user_allocate	proto WINAPI :size_t
MIDL_user_free		proto WINAPI :PVOID

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

ifndef __IPersistMoniker_INTERFACE_DEFINED__
__IPersistMoniker_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IPersistMoniker, "79eac9c9-baf9-11ce-8c82-00aa004ba90b")

.comdef IPersistMoniker : public IUnknown

    GetClassID		proc :ptr
    IsDirty		proc
    Load		proc :BOOL, :ptr, :LPBC, :DWORD
    Save		proc :ptr, :LPBC, :BOOL
    SaveCompleted	proc :ptr, :LPBC
    GetCurMoniker	proc :ptr

    .ends

LPPERSISTMONIKER	typedef ptr IPersistMoniker

endif

endif
ifndef _LPBINDPROTOCOL_DEFINED
_LPBINDPROTOCOL_DEFINED equ 1

ifndef __IBindProtocol_INTERFACE_DEFINED__
__IBindProtocol_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBindProtocol, "79eac9cd-baf9-11ce-8c82-00aa004ba90b")

.comdef IBindProtocol : public IUnknown

    CreateBinding	proc :LPCWSTR, :ptr, :ptr

    .ends

LPBINDPROTOCOL		typedef ptr IBindProtocol

endif
endif
ifndef _LPBINDING_DEFINED
_LPBINDING_DEFINED equ 1

ifndef __IBinding_INTERFACE_DEFINED__
__IBinding_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBinding, "79eac9c0-baf9-11ce-8c82-00aa004ba90b")

.comdef IBinding : public IUnknown

    Abort		proc
    Suspend		proc
    Resume		proc
    SetPriority		proc :LONG
    GetPriority		proc :ptr
    GetBindResult	proc :ptr, :ptr, :ptr, :DWORD

    .ends

LPBINDING		typedef ptr IBinding

endif
endif
ifndef _LPBINDSTATUSCALLBACK_DEFINED
_LPBINDSTATUSCALLBACK_DEFINED equ 1

ifndef __IBindStatusCallback_INTERFACE_DEFINED__
__IBindStatusCallback_INTERFACE_DEFINED__ equ 1

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

DEFINE_IIDX(IBindStatusCallback, "79eac9c1-baf9-11ce-8c82-00aa004ba90b")

.comdef IBindStatusCallback : public IUnknown

    OnStartBinding	proc :DWORD,:ptr
    GetPriority		proc :ptr
    OnLowResource	proc :DWORD
    OnProgress		proc :DWORD, :DWORD, :DWORD,: LPWSTR
    OnStopBinding	proc :HRESULT, :LPWSTR
    GetBindInfo		proc :ptr, :ptr
    OnDataAvailable	proc :DWORD, :DWORD, :ptr, :ptr
    OnObjectAvailable	proc :REFIID, :ptr

    .ends

LPBINDSTATUSCALLBACK	typedef ptr IBindStatusCallback

endif
endif
ifndef _LPAUTHENTICATION_DEFINED
_LPAUTHENTICATION_DEFINED equ 1

ifndef __IAuthenticate_INTERFACE_DEFINED__
__IAuthenticate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IAuthenticate, "79eac9d0-baf9-11ce-8c82-00aa004ba90b")

.comdef IAuthenticate : public IUnknown

    Authenticate	proc :ptr, :ptr, :ptr

    .ends

LPAUTHENTICATION	typedef ptr IAuthenticate

endif
endif
ifndef _LPHTTPNEGOTIATE_DEFINED
_LPHTTPNEGOTIATE_DEFINED equ 1

ifndef __IHttpNegotiate_INTERFACE_DEFINED__
__IHttpNegotiate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHttpNegotiate, "79eac9d2-baf9-11ce-8c82-00aa004ba90b")

.comdef IHttpNegotiate : public IUnknown

    BeginningTransaction proc :LPCWSTR, :LPCWSTR, :DWORD, :ptr
    OnResponse		proc :DWORD, :LPCWSTR, :LPCWSTR, :ptr

    .ends

LPHTTPNEGOTIATE		typedef ptr IHttpNegotiate

endif
endif
ifndef _LPWINDOWFORBINDINGUI_DEFINED
_LPWINDOWFORBINDINGUI_DEFINED equ 1

ifndef __IWindowForBindingUI_INTERFACE_DEFINED__
__IWindowForBindingUI_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWindowForBindingUI, "79eac9d5-bafa-11ce-8c82-00aa004ba90b")

.comdef IWindowForBindingUI : public IUnknown

    GetWindow		proc :REFGUID, :ptr

    .ends

LPWINDOWFORBINDINGUI	typedef ptr IWindowForBindingUI

endif
endif

ifndef _LPCODEINSTALL_DEFINED
_LPCODEINSTALL_DEFINED equ 1

ifndef __ICodeInstall_INTERFACE_DEFINED__
__ICodeInstall_INTERFACE_DEFINED__ equ 1

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

DEFINE_IIDX(ICodeInstall, "79eac9d1-baf9-11ce-8c82-00aa004ba90b")

.comdef ICodeInstall : public IWindowForBindingUI

    OnCodeInstallProblem proc :ULONG, :LPCWSTR, :LPCWSTR, :DWORD

    .ends

LPCODEINSTALL		typedef ptr ICodeInstall

endif
endif

ifndef __IUri_INTERFACE_DEFINED__
__IUri_INTERFACE_DEFINED__ equ 1

.enum Uri_PROPERTY {
    Uri_PROPERTY_ABSOLUTE_URI	= 0,
    Uri_PROPERTY_STRING_START	= Uri_PROPERTY_ABSOLUTE_URI,
    Uri_PROPERTY_AUTHORITY	= 1,
    Uri_PROPERTY_DISPLAY_URI	= 2,
    Uri_PROPERTY_DOMAIN		= 3,
    Uri_PROPERTY_EXTENSION	= 4,
    Uri_PROPERTY_FRAGMENT	= 5,
    Uri_PROPERTY_HOST		= 6,
    Uri_PROPERTY_PASSWORD	= 7,
    Uri_PROPERTY_PATH		= 8,
    Uri_PROPERTY_PATH_AND_QUERY = 9,
    Uri_PROPERTY_QUERY		= 10,
    Uri_PROPERTY_RAW_URI	= 11,
    Uri_PROPERTY_SCHEME_NAME	= 12,
    Uri_PROPERTY_USER_INFO	= 13,
    Uri_PROPERTY_USER_NAME	= 14,
    Uri_PROPERTY_STRING_LAST	= Uri_PROPERTY_USER_NAME,
    Uri_PROPERTY_HOST_TYPE	= 15,
    Uri_PROPERTY_DWORD_START	= Uri_PROPERTY_HOST_TYPE,
    Uri_PROPERTY_PORT		= 16,
    Uri_PROPERTY_SCHEME		= 17,
    Uri_PROPERTY_ZONE		= 18,
    Uri_PROPERTY_DWORD_LAST	= Uri_PROPERTY_ZONE
    }

.enum Uri_HOST_TYPE {
    Uri_HOST_UNKNOWN	= 0,
    Uri_HOST_DNS	= ( Uri_HOST_UNKNOWN + 1 ),
    Uri_HOST_IPV4	= ( Uri_HOST_DNS + 1 ),
    Uri_HOST_IPV6	= ( Uri_HOST_IPV4 + 1 ),
    Uri_HOST_IDN	= ( Uri_HOST_IPV6 + 1 )
    }


DEFINE_IIDX(IUri, "A39EE748-6A27-4817-A6F2-13914BEF5890")

.comdef IUri : public IUnknown
    GetPropertyBSTR	proc :Uri_PROPERTY, :ptr BSTR, :DWORD
    GetPropertyLength	proc :Uri_PROPERTY, :ptr DWORD, :DWORD
    GetPropertyDWORD	proc :Uri_PROPERTY, :ptr DWORD, :DWORD
    HasProperty		proc :Uri_PROPERTY, :ptr BOOL
    GetAbsoluteUri	proc :ptr BSTR
    GetAuthority	proc :ptr BSTR
    GetDisplayUri	proc :ptr BSTR
    GetDomain		proc :ptr BSTR
    GetExtension	proc :ptr BSTR
    GetFragment		proc :ptr BSTR
    GetHost		proc :ptr BSTR
    GetPassword		proc :ptr BSTR
    GetPath		proc :ptr BSTR
    GetPathAndQuery	proc :ptr BSTR
    GetQuery		proc :ptr BSTR
    GetRawUri		proc :ptr BSTR
    GetSchemeName	proc :ptr BSTR
    GetUserInfo		proc :ptr BSTR
    GetUserName		proc :ptr BSTR
    GetHostType		proc :ptr DWORD
    GetPort		proc :ptr DWORD
    GetScheme		proc :ptr DWORD
    GetZone		proc :ptr DWORD
    GetProperties	proc :ptr LPWORD
    IsEqual		proc :ptr IUri, :ptr BOOL
    .ends

endif

CreateUri proto WINAPI \
		pwzURI: LPCWSTR,
	       dwFlags: DWORD,
	    dwReserved: DWORD_PTR,
		 ppURI: ptr ptr IUri

CreateUriWithFragment proto WINAPI \
		pwzURI: LPCWSTR,
	   pwzFragment: LPCWSTR,
	       dwFlags: DWORD,
	    dwReserved: DWORD_PTR,
		 ppURI: ptr ptr IUri

CreateUriFromMultiByteString proto WINAPI \
       pszANSIInputUri: LPCSTR,
       dwEncodingFlags: DWORD,
	    dwCodePage: DWORD,
	 dwCreateFlags: DWORD,
	    dwReserved: DWORD_PTR,
		 ppUri: ptr ptr IUri


Uri_HAS_ABSOLUTE_URI	equ (1 shl Uri_PROPERTY_ABSOLUTE_URI)
Uri_HAS_AUTHORITY	equ (1 shl Uri_PROPERTY_AUTHORITY)
Uri_HAS_DISPLAY_URI	equ (1 shl Uri_PROPERTY_DISPLAY_URI)
Uri_HAS_DOMAIN		equ (1 shl Uri_PROPERTY_DOMAIN)
Uri_HAS_EXTENSION	equ (1 shl Uri_PROPERTY_EXTENSION)
Uri_HAS_FRAGMENT	equ (1 shl Uri_PROPERTY_FRAGMENT)
Uri_HAS_HOST		equ (1 shl Uri_PROPERTY_HOST)
Uri_HAS_PASSWORD	equ (1 shl Uri_PROPERTY_PASSWORD)
Uri_HAS_PATH		equ (1 shl Uri_PROPERTY_PATH)
Uri_HAS_QUERY		equ (1 shl Uri_PROPERTY_QUERY)
Uri_HAS_RAW_URI		equ (1 shl Uri_PROPERTY_RAW_URI)
Uri_HAS_SCHEME_NAME	equ (1 shl Uri_PROPERTY_SCHEME_NAME)
Uri_HAS_USER_NAME	equ (1 shl Uri_PROPERTY_USER_NAME)
Uri_HAS_PATH_AND_QUERY	equ (1 shl Uri_PROPERTY_PATH_AND_QUERY)
Uri_HAS_USER_INFO	equ (1 shl Uri_PROPERTY_USER_INFO)
Uri_HAS_HOST_TYPE	equ (1 shl Uri_PROPERTY_HOST_TYPE)
Uri_HAS_PORT		equ (1 shl Uri_PROPERTY_PORT)
Uri_HAS_SCHEME		equ (1 shl Uri_PROPERTY_SCHEME)
Uri_HAS_ZONE		equ (1 shl Uri_PROPERTY_ZONE)

Uri_CREATE_ALLOW_RELATIVE		  equ 0x00000001
Uri_CREATE_ALLOW_IMPLICIT_WILDCARD_SCHEME equ 0x00000002
Uri_CREATE_ALLOW_IMPLICIT_FILE_SCHEME	  equ 0x00000004
Uri_CREATE_NOFRAG			  equ 0x00000008
Uri_CREATE_NO_CANONICALIZE		  equ 0x00000010
Uri_CREATE_CANONICALIZE			  equ 0x00000100
Uri_CREATE_FILE_USE_DOS_PATH		  equ 0x00000020
Uri_CREATE_DECODE_EXTRA_INFO		  equ 0x00000040
Uri_CREATE_NO_DECODE_EXTRA_INFO		  equ 0x00000080
Uri_CREATE_CRACK_UNKNOWN_SCHEMES	  equ 0x00000200
Uri_CREATE_NO_CRACK_UNKNOWN_SCHEMES	  equ 0x00000400
Uri_CREATE_PRE_PROCESS_HTML_URI		  equ 0x00000800
Uri_CREATE_NO_PRE_PROCESS_HTML_URI	  equ 0x00001000
Uri_CREATE_IE_SETTINGS			  equ 0x00002000
Uri_CREATE_NO_IE_SETTINGS		  equ 0x00004000
Uri_CREATE_NO_ENCODE_FORBIDDEN_CHARACTERS equ 0x00008000
Uri_CREATE_NORMALIZE_INTL_CHARACTERS	  equ 0x00010000
Uri_CREATE_CANONICALIZE_ABSOLUTE	  equ 0x00020000

Uri_DISPLAY_NO_FRAGMENT		      equ 0x00000001
Uri_PUNYCODE_IDN_HOST		      equ 0x00000002
Uri_DISPLAY_IDN_HOST		      equ 0x00000004
Uri_DISPLAY_NO_PUNYCODE		      equ 0x00000008

Uri_ENCODING_USER_INFO_AND_PATH_IS_PERCENT_ENCODED_UTF8	 equ 0x00000001
Uri_ENCODING_USER_INFO_AND_PATH_IS_CP			 equ 0x00000002
Uri_ENCODING_HOST_IS_IDN				 equ 0x00000004
Uri_ENCODING_HOST_IS_PERCENT_ENCODED_UTF8		 equ 0x00000008
Uri_ENCODING_HOST_IS_PERCENT_ENCODED_CP			 equ 0x00000010
Uri_ENCODING_QUERY_AND_FRAGMENT_IS_PERCENT_ENCODED_UTF8	 equ 0x00000020
Uri_ENCODING_QUERY_AND_FRAGMENT_IS_CP			 equ 0x00000040
Uri_ENCODING_RFC equ (Uri_ENCODING_USER_INFO_AND_PATH_IS_PERCENT_ENCODED_UTF8 or \
		      Uri_ENCODING_HOST_IS_PERCENT_ENCODED_UTF8 or \
		      Uri_ENCODING_QUERY_AND_FRAGMENT_IS_PERCENT_ENCODED_UTF8)

UriBuilder_USE_ORIGINAL_FLAGS equ 0x00000001

ifndef __IUriContainer_INTERFACE_DEFINED__
__IUriContainer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUriContainer, "a158a630-ed6f-45fb-b987-f68676f57752")

.comdef IUriContainer : public IUnknown

    GetIUri		proc :ptr ptr
    .ends

endif

ifndef __IUriBuilder_INTERFACE_DEFINED__
__IUriBuilder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUriBuilder, "4221B2E1-8955-46c0-BD5B-DE9897565DE7")

.comdef IUriBuilder : public IUnknown

    CreateUriSimple	proc :DWORD, :DWORD_PTR, :ptr ptr IUri
    CreateUri		proc :DWORD, :DWORD, :DWORD_PTR, :ptr ptr IUri
    CreateUriWithFlags	proc :DWORD, :DWORD, :DWORD, :DWORD_PTR, :ptr ptr IUri
    GetIUri		proc :ptr ptr IUri
    SetIUri		proc :ptr IUri
    GetFragment		proc :ptr DWORD, :ptr LPCWSTR
    GetHost		proc :ptr DWORD, :ptr LPCWSTR
    GetPassword		proc :ptr DWORD, :ptr LPCWSTR
    GetPath		proc :ptr DWORD, :ptr LPCWSTR
    GetPort		proc :ptr BOOL, :ptr DWORD
    GetQuery		proc :ptr DWORD, :ptr LPCWSTR
    GetSchemeName	proc :ptr DWORD, :ptr LPCWSTR
    GetUserName		proc :ptr DWORD, :ptr LPCWSTR
    SetFragment		proc :LPCWSTR
    SetHost		proc :LPCWSTR
    SetPassword		proc :LPCWSTR
    SetPath		proc :LPCWSTR
    SetPort		proc :BOOL, :DWORD
    SetQuery		proc :LPCWSTR
    SetSchemeName	proc :LPCWSTR
    SetUserName		proc :LPCWSTR
    RemoveProperties	proc :DWORD
    HasBeenModified	proc :ptr BOOL
    .ends

endif

ifndef __IUriBuilderFactory_INTERFACE_DEFINED__
__IUriBuilderFactory_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IUriBuilderFactory, "E982CE48-0B96-440c-BC37-0C869B27A29E")

.comdef IUriBuilderFactory : public IUnknown

    CreateIUriBuilder	proc :DWORD, :DWORD_PTR, :ptr ptr IUriBuilder
    CreateInitializedIUriBuilder proc :DWORD, :DWORD_PTR, :ptr ptr IUriBuilder

    .ends

endif

CreateIUriBuilder proto WINAPI \
		 pIUri: ptr IUri,
	       dwFlags: DWORD,
	    dwReserved: DWORD_PTR,
	 ppIUriBuilder: ptr ptr IUriBuilder


ifndef _LPWININETINFO_DEFINED
_LPWININETINFO_DEFINED equ 1

ifndef __IWinInetInfo_INTERFACE_DEFINED__
__IWinInetInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWinInetInfo, "79eac9d6-bafa-11ce-8c82-00aa004ba90b")

.comdef IWinInetInfo : public IUnknown

    QueryOption		proc :DWORD, :ptr, :ptr

    .ends

LPWININETINFO		typedef ptr IWinInetInfo

endif
endif
WININETINFO_OPTION_LOCK_HANDLE equ 65534
ifndef _LPHTTPSECURITY_DEFINED
_LPHTTPSECURITY_DEFINED equ 1

ifndef __IHttpSecurity_INTERFACE_DEFINED__
__IHttpSecurity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IHttpSecurity, "79eac9d7-bafa-11ce-8c82-00aa004ba90b")

.comdef IHttpSecurity : public IWindowForBindingUI

    OnSecurityProblem	proc :DWORD

    .ends

LPHTTPSECURITY		typedef ptr IHttpSecurity

endif
endif
ifndef _LPWININETHTTPINFO_DEFINED
_LPWININETHTTPINFO_DEFINED equ 1

ifndef __IWinInetHttpInfo_INTERFACE_DEFINED__
__IWinInetHttpInfo_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IWinInetHttpInfo, "79eac9d8-bafa-11ce-8c82-00aa004ba90b")

.comdef IWinInetHttpInfo : public IWinInetInfo

    QueryInfo		proc :DWORD, :PVOID, :ptr, :ptr, :ptr

    .ends

LPWININETHTTPINFO	typedef ptr IWinInetHttpInfo

endif
endif
SID_IBindHost		equ <IID_IBindHost>
SID_SBindHost		equ <IID_IBindHost>
ifndef _LPBINDHOST_DEFINED
_LPBINDHOST_DEFINED equ 1
externdef		SID_BindHost:GUID

ifndef __IBindHost_INTERFACE_DEFINED__
__IBindHost_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IBindHost, "fc4801a1-2ba9-11cf-a229-00aa003d7352")

.comdef IBindHost : public IUnknown

    CreateMoniker	proc :LPOLESTR,:ptr, :ptr, :DWORD
    MonikerBindToStorage proc :ptr, :ptr, :ptr, :REFIID, :ptr
    MonikerBindToObject proc :ptr, :ptr, :ptr, :REFIID, :ptr

    .ends

LPBINDHOST		typedef ptr IBindHost

endif
endif

URLOSTRM_USECACHEDCOPY_ONLY equ 0x1
URLOSTRM_USECACHEDCOPY	equ 0x2
URLOSTRM_GETNEWESTVERSION equ 0x3

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

HlinkSimpleNavigateToMoniker proto WINAPI \
	     pmkTarget: ptr IMoniker,
	    szLocation: LPCWSTR,
     szTargetFrameName: LPCWSTR,
		  pUnk: ptr IUnknown,
		   pbc: ptr IBindCtx,
		      : ptr IBindStatusCallback,
	       grfHLNF: DWORD,
	    dwReserved: DWORD

URLOpenStreamA proto WINAPI \
		      : LPUNKNOWN,
		      : LPCSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK

URLOpenStreamW proto WINAPI \
		      : LPUNKNOWN,
		      : LPCWSTR,
		      : DWORD,
		      : LPBINDSTATUSCALLBACK

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

ifndef __IInternet_INTERFACE_DEFINED__
__IInternet_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternet, "79eac9e0-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternet : public IUnknown

    .ends

LPIINTERNET		typedef ptr IInternet
endif
endif

ifndef _LPIINTERNETBINDINFO
_LPIINTERNETBINDINFO equ 1

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

DEFINE_IIDX(IInternetBindInfo, "79eac9e1-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetBindInfo : public IUnknown

    GetBindInfo		proc :ptr, :ptr
    GetBindString	proc :DWORD, :ptr, :DWORD, :ptr

    .ends

endif
endif
ifndef _LPIINTERNETPROTOCOLROOT_DEFINED
_LPIINTERNETPROTOCOLROOT_DEFINED equ 1

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

DEFINE_IIDX(IInternetProtocolRoot, "79eac9e3-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetProtocolRoot : public IUnknown

    Start		proc :LPWSTR, :ptr, :ptr, :DWORD, :DWORD
    Continue		proc :ptr
    Abort		proc :HRESULT, :DWORD
    Terminate		proc :DWORD
    Suspend		proc
    Resume		proc

    .ends

endif
endif
ifndef _LPIINTERNETPROTOCOL_DEFINED
_LPIINTERNETPROTOCOL_DEFINED equ 1

ifndef __IInternetProtocol_INTERFACE_DEFINED__
__IInternetProtocol_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternetProtocol, "79eac9e4-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetProtocol : public IInternetProtocolRoot

    Read		proc :ptr, :DWORD, :ptr
    Seek		proc :LARGE_INTEGER, :DWORD, :ptr
    LockRequest		proc :DWORD
    UnlockRequest	proc

    .ends

LPIINTERNETPROTOCOL	typedef ptr IInternetProtocol

endif
endif
ifndef _LPIINTERNETPROTOCOLSINK_DEFINED
_LPIINTERNETPROTOCOLSINK_DEFINED equ 1

ifndef __IInternetProtocolSink_INTERFACE_DEFINED__
__IInternetProtocolSink_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternetProtocolSink, "79eac9e5-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetProtocolSink : public IUnknown

    Switch		proc :ptr
    ReportProgress	proc :DWORD, :LPWSTR
    ReportData		proc :DWORD, :DWORD, :DWORD
    ReportResult	proc :HRESULT, :DWORD, :LPWSTR

    .ends

LPIINTERNETPROTOCOLSINK typedef ptr IInternetProtocolSink

endif
endif
ifndef _LPIINTERNETSESSION_DEFINED
_LPIINTERNETSESSION_DEFINED equ 1

ifndef __IInternetSession_INTERFACE_DEFINED__
__IInternetSession_INTERFACE_DEFINED__ equ 1

;typedef enum _tagOIBDG_FLAGS

OIBDG_APARTMENTTHREADED equ 0x100

DEFINE_IIDX(IInternetSession, "79eac9e7-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetSession : public IUnknown

    RegisterNameSpace	proc :ptr, :REFCLSID, :LPWSTR, :DWORD, :ptr, :DWORD
    UnregisterNameSpace proc :LPWSTR
    RegisterMimeFilter	proc :ptr, :REFCLSID, :LPWSTR
    UnregisterMimeFilter proc :ptr, :LPWSTR
    CreateBinding	proc :LPBC, :LPWSTR, :ptr, :ptr, :ptr, :DWORD
    SetSessionOption	proc :DWORD, :PVOID, :DWORD, :DWORD
    GetSessionOption	proc :DWORD, :PVOID, :ptr, :DWORD

    .ends

LPIINTERNETSESSION	typedef ptr IInternetSession

endif
endif
ifndef _LPIINTERNETTHREADSWITCH_DEFINED
_LPIINTERNETTHREADSWITCH_DEFINED equ 1

ifndef __IInternetThreadSwitch_INTERFACE_DEFINED__
__IInternetThreadSwitch_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternetThreadSwitch, "79eac9e8-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetThreadSwitch : public IUnknown

    Prepare		proc
    Continue		proc :ptr, :PRPC_MESSAGE, :ptr

    .ends

LPIINTERNETTHREADSWITCH typedef ptr IInternetThreadSwitch

endif
endif
ifndef _LPIINTERNETPRIORITY_DEFINED
_LPIINTERNETPRIORITY_DEFINED equ 1

ifndef __IInternetPriority_INTERFACE_DEFINED__
__IInternetPriority_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternetPriority, "79eac9eb-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetPriority : public IUnknown

    SetPriority		proc :LONG
    GetPriority		proc :ptr

    .ends

LPIINTERNETPRIORITY	typedef ptr IInternetPriority

endif
endif
ifndef _LPIINTERNETPROTOCOLINFO_DEFINED
_LPIINTERNETPROTOCOLINFO_DEFINED equ 1

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

DEFINE_IIDX(IInternetProtocolInfo, "79eac9ec-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetProtocolInfo : public IUnknown

    ParseUrl		proc :LPWSTR, :PARSEACTION, :DWORD, :LPWSTR, :DWORD, :ptr, :DWORD
    CombineUrl		proc :LPWSTR, :LPWSTR, :DWORD, :LPWSTR, :DWORD, :ptr, :DWORD
    CompareUrl		proc :LPWSTR, :LPWSTR, :DWORD
    QueryInfo		proc :LPWSTR, :QUERYOPTION, :DWORD, :PVOID, :DWORD, :ptr, :DWORD

    .ends

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

ifndef __IInternetSecurityMgrSite_INTERFACE_DEFINED__
__IInternetSecurityMgrSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternetSecurityMgrSite, "79eac9ed-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetSecurityMgrSite : public IUnknown

    GetWindow		proc :ptr
    EnableModeless	proc :BOOL

    .ends

endif
endif
ifndef _LPINTERNETSECURITYMANANGER_DEFINED
_LPINTERNETSECURITYMANANGER_DEFINED equ 1

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

DEFINE_IIDX(IInternetSecurityManager, "79eac9ee-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetSecurityManager : public IUnknown

    SetSecuritySite	proc :ptr
    GetSecuritySite	proc
    MapUrlToZone	proc :LPWSTR, :ptr, :DWORD
    GetSecurityId	proc :LPWSTR, :ptr, :ptr, :DWORD
    ProcessUrlAction	proc :LPWSTR, :DWORD, :ptr, :DWORD, :ptr, :DWORD, :DWORD, :DWORD
    QueryCustomPolicy	proc :LPWSTR, :REFGUID, :ptr, :ptr, :ptr, :DWORD, :DWORD
    SetZoneMapping	proc :DWORD, :LPWSTR, :DWORD
    GetZoneMappings	proc :DWORD, :ptr, :DWORD

    .ends

endif
endif
ifndef _LPINTERNETHOSTSECURITYMANANGER_DEFINED
_LPINTERNETHOSTSECURITYMANANGER_DEFINED equ 1

ifndef __IInternetHostSecurityManager_INTERFACE_DEFINED__
__IInternetHostSecurityManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IInternetHostSecurityManager, "3af280b6-cb3f-11d0-891e-00c04fb6bfc4")

.comdef IInternetHostSecurityManager : public IUnknown

    GetSecurityId	proc :ptr, :ptr, :DWORD
    ProcessUrlAction	proc :DWORD, :ptr, :DWORD, :ptr, :DWORD, :DWORD, :DWORD
    QueryCustomPolicy	proc :REFGUID, :ptr, :ptr, :ptr, :DWORD, :DWORD

    .ends

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
GetUrlPolicyPermissions macro d
	exitm<(d AND URLPOLICY_MASK_PERMISSIONS)>
	endm
SetUrlPolicyPermissions macro d,d2
	exitm<((d) = ((d) AND NOT (URLPOLICY_MASK_PERMISSIONS)) OR (d2))>
	endm


ifndef _LPINTERNETZONEMANAGER_DEFINED
_LPINTERNETZONEMANAGER_DEFINED equ 1

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

DEFINE_IIDX(IInternetZoneManager, "79eac9ef-baf9-11ce-8c82-00aa004ba90b")

.comdef IInternetZoneManager : public IUnknown

    GetZoneAttributes	proc :DWORD, :ptr
    SetZoneAttributes	proc :DWORD, :ptr
    GetZoneCustomPolicy proc :DWORD, :REFGUID, :ptr, :ptr, :URLZONEREG
    SetZoneCustomPolicy proc :DWORD, :REFGUID, :ptr, :DWORD, :URLZONEREG
    GetZoneActionPolicy proc :DWORD, :DWORD, :ptr, :DWORD, :URLZONEREG
    SetZoneActionPolicy proc :DWORD, :DWORD, :ptr, :DWORD, :URLZONEREG
    PromptAction	proc :DWORD, :HWND, :LPWSTR, :LPWSTR, :DWORD
    LogAction		proc :DWORD, :LPWSTR, :LPWSTR, :DWORD
    CreateZoneEnumerator proc :ptr, :ptr, :DWORD
    GetZoneAt		proc :DWORD, :DWORD, :ptr
    DestroyZoneEnumerator proc :DWORD
    CopyTemplatePoliciesToZone proc :DWORD, :DWORD, :DWORD

    .ends

LPURLZONEMANAGER	typedef ptr IInternetZoneManager

endif
endif
externdef CLSID_SoftDistExt:IID
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

ifndef __ISoftDistExt_INTERFACE_DEFINED__
__ISoftDistExt_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISoftDistExt, "B15B8DC1-C7E1-11d0-8680-00AA00BDCB71")

.comdef ISoftDistExt : public IUnknown

    ProcessSoftDist	proc :LPWSTR, :ptr, :LPSOFTDISTINFO
    GetFirstCodeBase	proc :ptr, :ptr
    GetNextCodeBase	proc :ptr, :ptr
    AsyncInstallDistributionUnit proc :ptr, :LPVOID, :DWORD, :LPCODEBASEHOLD

    .ends

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

ifndef __IDataFilter_INTERFACE_DEFINED__
__IDataFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDataFilter, "69d14c80-c18e-11d0-a9ce-006097942311")

.comdef IDataFilter : public IUnknown

    DoEncode		proc :DWORD, :SDWORD, :ptr, :SDWORD, :ptr, :SDWORD, :ptr, :ptr, :DWORD
    DoDecode		proc :DWORD, :SDWORD, :ptr, :SDWORD, :ptr, :SDWORD, :ptr, :ptr, :DWORD
    SetEncodingLevel	proc :DWORD

    .ends

LPDATAFILTER		typedef ptr IDataFilter

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

ifndef __IEncodingFilterFactory_INTERFACE_DEFINED__
__IEncodingFilterFactory_INTERFACE_DEFINED__ equ 1

DATAINFO		STRUC
ulTotalSize		dd ?
ulavrPacketSize		dd ?
ulConnectSpeed		dd ?
ulProcessorSpeed	dd ?
DATAINFO		ENDS

DEFINE_IIDX(IEncodingFilterFactory, "70bdde00-c18e-11d0-a9ce-006097942311")

.comdef IEncodingFilterFactory : public IUnknown

    FindBestFilter	proc :LPWSTR, :LPWSTR, :DATAINFO, :ptr
    GetDefaultFilter	proc :LPWSTR, :LPWSTR, :ptr

    .ends

LPENCODINGFILTERFACTORY typedef ptr IEncodingFilterFactory

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

endif
