include rpc.inc
include rpcndr.inc
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif ;;COM_NO_WINDOWS_H

ifndef __urlmon_h__
.xlist
__urlmon_h__ equ 1

;; Forward Declarations

ifndef __IPersistMoniker_FWD_DEFINED__
__IPersistMoniker_FWD_DEFINED__ equ 1
endif	;; __IPersistMoniker_FWD_DEFINED__


ifndef __IBindProtocol_FWD_DEFINED__
__IBindProtocol_FWD_DEFINED__ equ 1
endif	;; __IBindProtocol_FWD_DEFINED__


ifndef __IBinding_FWD_DEFINED__
__IBinding_FWD_DEFINED__ equ 1
endif	;; __IBinding_FWD_DEFINED__


ifndef __IBindStatusCallback_FWD_DEFINED__
__IBindStatusCallback_FWD_DEFINED__ equ 1
endif	;; __IBindStatusCallback_FWD_DEFINED__


ifndef __IAuthenticate_FWD_DEFINED__
__IAuthenticate_FWD_DEFINED__ equ 1
endif	;; __IAuthenticate_FWD_DEFINED__


ifndef __IHttpNegotiate_FWD_DEFINED__
__IHttpNegotiate_FWD_DEFINED__ equ 1
endif	;; __IHttpNegotiate_FWD_DEFINED__


ifndef __IWindowForBindingUI_FWD_DEFINED__
__IWindowForBindingUI_FWD_DEFINED__ equ 1
endif	;; __IWindowForBindingUI_FWD_DEFINED__


ifndef __ICodeInstall_FWD_DEFINED__
__ICodeInstall_FWD_DEFINED__ equ 1
endif	;; __ICodeInstall_FWD_DEFINED__


ifndef __IWinInetInfo_FWD_DEFINED__
__IWinInetInfo_FWD_DEFINED__ equ 1
endif	;; __IWinInetInfo_FWD_DEFINED__


ifndef __IHttpSecurity_FWD_DEFINED__
__IHttpSecurity_FWD_DEFINED__ equ 1
endif	;; __IHttpSecurity_FWD_DEFINED__


ifndef __IWinInetHttpInfo_FWD_DEFINED__
__IWinInetHttpInfo_FWD_DEFINED__ equ 1
endif	;; __IWinInetHttpInfo_FWD_DEFINED__


ifndef __IBindHost_FWD_DEFINED__
__IBindHost_FWD_DEFINED__ equ 1
endif	;; __IBindHost_FWD_DEFINED__


ifndef __IInternet_FWD_DEFINED__
__IInternet_FWD_DEFINED__ equ 1
endif	;; __IInternet_FWD_DEFINED__


ifndef __IInternetBindInfo_FWD_DEFINED__
__IInternetBindInfo_FWD_DEFINED__ equ 1
endif	;; __IInternetBindInfo_FWD_DEFINED__


ifndef __IInternetProtocolRoot_FWD_DEFINED__
__IInternetProtocolRoot_FWD_DEFINED__ equ 1
endif	;; __IInternetProtocolRoot_FWD_DEFINED__


ifndef __IInternetProtocol_FWD_DEFINED__
__IInternetProtocol_FWD_DEFINED__ equ 1
endif	;; __IInternetProtocol_FWD_DEFINED__


ifndef __IInternetProtocolSink_FWD_DEFINED__
__IInternetProtocolSink_FWD_DEFINED__ equ 1
endif	;; __IInternetProtocolSink_FWD_DEFINED__


ifndef __IInternetSession_FWD_DEFINED__
__IInternetSession_FWD_DEFINED__ equ 1
endif	;; __IInternetSession_FWD_DEFINED__


ifndef __IInternetThreadSwitch_FWD_DEFINED__
__IInternetThreadSwitch_FWD_DEFINED__ equ 1
endif	;; __IInternetThreadSwitch_FWD_DEFINED__


ifndef __IInternetPriority_FWD_DEFINED__
__IInternetPriority_FWD_DEFINED__ equ 1
endif	;; __IInternetPriority_FWD_DEFINED__


ifndef __IInternetProtocolInfo_FWD_DEFINED__
__IInternetProtocolInfo_FWD_DEFINED__ equ 1
endif	;; __IInternetProtocolInfo_FWD_DEFINED__


ifndef __IInternetSecurityMgrSite_FWD_DEFINED__
__IInternetSecurityMgrSite_FWD_DEFINED__ equ 1
endif	;; __IInternetSecurityMgrSite_FWD_DEFINED__


ifndef __IInternetSecurityManager_FWD_DEFINED__
__IInternetSecurityManager_FWD_DEFINED__ equ 1
endif	;; __IInternetSecurityManager_FWD_DEFINED__


ifndef __IInternetHostSecurityManager_FWD_DEFINED__
__IInternetHostSecurityManager_FWD_DEFINED__ equ 1
endif	;; __IInternetHostSecurityManager_FWD_DEFINED__


ifndef __IInternetZoneManager_FWD_DEFINED__
__IInternetZoneManager_FWD_DEFINED__ equ 1
endif	;; __IInternetZoneManager_FWD_DEFINED__


ifndef __ISoftDistExt_FWD_DEFINED__
__ISoftDistExt_FWD_DEFINED__ equ 1
endif	;; __ISoftDistExt_FWD_DEFINED__


ifndef __IDataFilter_FWD_DEFINED__
__IDataFilter_FWD_DEFINED__ equ 1
endif	;; __IDataFilter_FWD_DEFINED__


ifndef __IEncodingFilterFactory_FWD_DEFINED__
__IEncodingFilterFactory_FWD_DEFINED__ equ 1
endif	;; __IEncodingFilterFactory_FWD_DEFINED__


;; header files for imported files
include objidl.inc
include oleidl.inc
include servprov.inc
include msxml.inc
.xlist

;void *
MIDL_user_allocate proto _CType :size_t
;void
MIDL_user_free proto _CType :PVOID

;;#pragma comment(lib,"uuid.lib")

;;---------------------------------------------------------------------------=
;; URL Moniker Interfaces.

;; These are for backwards compatibility with previous URLMON versions
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
CreateURLMoniker proto _CType \
		pMkCtx: LPMONIKER,
		 szURL: LPCWSTR,
		  ppmk: ptr LPMONIKER

;STDAPI
GetClassURL proto _CType \
		 szURL: LPCWSTR,
		pClsID: ptr CLSID

;STDAPI
CreateAsyncBindCtx proto _CType \
	      reserved: DWORD,
		 pBSCb: ptr IBindStatusCallback,
		pEFetc: ptr IEnumFORMATETC,
		  ppBC: ptr IBindCtx

;STDAPI
CreateAsyncBindCtxEx proto _CType \
		   pbc: ptr IBindCtx,
	     dwOptions: DWORD,
		 pBSCb: ptr IBindStatusCallback,
		 pEnum: ptr IEnumFORMATETC,
		  ppBC: ptr IBindCtx,
	      reserved: DWORD

;STDAPI
MkParseDisplayNameEx proto _CType \
		   pbc: ptr IBindCtx,
	 szDisplayName: LPCWSTR,
	      pchEaten: ptr ULONG,
		  ppmk: ptr LPMONIKER

;STDAPI
RegisterBindStatusCallback proto _CType \
		   pBC: LPBC,
		 pBSCb: ptr IBindStatusCallback,
	    ppBSCBPrev: ptr IBindStatusCallback,
	    dwReserved: DWORD

;STDAPI
RevokeBindStatusCallback proto _CType \
		   pBC: LPBC,
		 pBSCb: ptr IBindStatusCallback

;STDAPI
GetClassFileOrMime proto _CType \
		   pBC: LPBC,
	    szFilename: LPCWSTR,
	       pBuffer: LPVOID,
		cbSize: DWORD,
		szMime: LPCWSTR,
	    dwReserved: DWORD,
		pclsid: ptr CLSID

;STDAPI
IsValidURL proto _CType \
		   pBC: LPBC,
		 szURL: LPCWSTR,
	    dwReserved: DWORD

;STDAPI
CoGetClassObjectFromURL proto _CType \
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


;;helper apis
;STDAPI
IsAsyncMoniker proto _CType \
		   pmk: ptr IMoniker

;STDAPI
CreateURLBinding proto _CType \
	       lpszUrl: LPCWSTR,
		   pbc: ptr IBindCtx,
		 ppBdg: ptr IBinding


;STDAPI
RegisterMediaTypes proto _CType \
		ctypes: UINT,
	     rgszTypes: LPCSTR,
	     rgcfTypes: ptr CLIPFORMAT

;STDAPI
FindMediaType proto _CType \
	     rgszTypes: LPCSTR,
	     rgcfTypes: ptr CLIPFORMAT

;STDAPI
CreateFormatEnumerator proto _CType \
	       cfmtetc: UINT,
	      rgfmtetc: ptr FORMATETC,
	  ppenumfmtetc: ptr IEnumFORMATETC

;STDAPI
RegisterFormatEnumerator proto _CType \
		   pBC: LPBC,
		pEFetc: ptr IEnumFORMATETC,
	      reserved: DWORD

;STDAPI
RevokeFormatEnumerator proto _CType \
		   pBC: LPBC,
		pEFetc: ptr IEnumFORMATETC

;STDAPI
RegisterMediaTypeClass proto _CType \
		   pBC: LPBC,
		ctypes: UINT,
	     rgszTypes: LPCSTR,
	       rgclsID: ptr CLSID,
	      reserved: DWORD

;STDAPI
FindMediaTypeClass proto _CType \
		   pBC: LPBC,
		szType: LPCSTR,
		pclsID: ptr CLSID,
	      reserved: DWORD

;STDAPI
UrlMkSetSessionOption proto _CType \
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
	    dwReserved: DWORD

;STDAPI
UrlMkGetSessionOption proto _CType \
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
       pdwBufferLength: LPDWORD,
	    dwReserved: DWORD

;STDAPI
FindMimeFromData proto _CType \
		   pBC: LPBC,
		pwzUrl: LPCWSTR,
	       pBuffer: LPVOID,
		cbSize: DWORD,
       pwzMimeProposed: LPCWSTR,
	   dwMimeFlags: DWORD,
	   ppwzMimeOut: ptr LPWSTR,
	    dwReserved: DWORD

;STDAPI
ObtainUserAgentString proto _CType \
	      dwOption: DWORD,
	      pszUAOut: LPSTR,
		cbSize: LPDWORD


;; URLMON-specific defines for UrlMkSetSessionOption() above
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

;; MessageId: MK_S_ASYNCHRONOUS
;; MessageText: Operation is successful, but will complete asynchronously.
;;
MK_S_ASYNCHRONOUS	equ _HRESULT_TYPEDEF_(0x000401E8)
ifndef S_ASYNCHRONOUS
S_ASYNCHRONOUS		equ MK_S_ASYNCHRONOUS
endif

ifndef E_PENDING
E_PENDING		equ _HRESULT_TYPEDEF_(0x8000000A)
endif

;;
;;
;; WinINet and protocol specific errors are mapped to one of the following
;; error which are returned in IBSC::OnStopBinding
;;
;;
;; Note: FACILITY C is split into ranges of 1k
;; C0000 - C03FF  INET_E_ (URLMON's original hresult)
;; C0400 - C07FF  INET_E_CLIENT_xxx
;; C0800 - C0BFF  INET_E_SERVER_xxx
;; C0C00 - C0FFF  INET_E_????
;; C1000 - C13FF  INET_E_AGENT_xxx (info delivery agents)
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



LPPERSISTMONIKER	typedef ptr IPersistMoniker


externdef		IID_IPersistMoniker:IID


IPersistMonikerVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface00@CT typedef proto \
		 pThis: ptr IPersistMoniker,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface00@MP typedef ptr QueryInterface00@CT
	 QueryInterface QueryInterface00@MP ?

	    AddRef00@CT typedef proto \
		 pThis: ptr IPersistMoniker

	    AddRef00@MP typedef ptr AddRef00@CT
		 AddRef AddRef00@MP ?

	   Release00@CT typedef proto \
		 pThis: ptr IPersistMoniker

	   Release00@MP typedef ptr Release00@CT
		Release Release00@MP ?

	GetClassID00@CT typedef proto \
		 pThis: ptr IPersistMoniker,
	      pClassID: ptr CLSID

	GetClassID00@MP typedef ptr GetClassID00@CT
	     GetClassID GetClassID00@MP ?

	   IsDirty00@CT typedef proto \
		 pThis: ptr IPersistMoniker

	   IsDirty00@MP typedef ptr IsDirty00@CT
		IsDirty IsDirty00@MP ?

	      Load00@CT typedef proto \
		 pThis: ptr IPersistMoniker,
       fFullyAvailable: BOOL,
	      pimkName: ptr IMoniker,
		  pibc: LPBC,
	       grfMode: DWORD

	      Load00@MP typedef ptr Load00@CT
		   Load Load00@MP ?

	      Save00@CT typedef proto \
		 pThis: ptr IPersistMoniker,
	      pimkName: ptr IMoniker,
		   pbc: LPBC,
	     fRemember: BOOL

	      Save00@MP typedef ptr Save00@CT
		   Save Save00@MP ?

     SaveCompleted00@CT typedef proto \
		 pThis: ptr IPersistMoniker,
	      pimkName: ptr IMoniker,
		  pibc: LPBC

     SaveCompleted00@MP typedef ptr SaveCompleted00@CT
	  SaveCompleted SaveCompleted00@MP ?

     GetCurMoniker00@CT typedef proto \
		 pThis: ptr IPersistMoniker,
	     ppimkName: ptr ptr IMoniker

     GetCurMoniker00@MP typedef ptr GetCurMoniker00@CT
	  GetCurMoniker GetCurMoniker00@MP ?

	END_INTERFACE

IPersistMonikerVtbl	ENDS

LPIPersistMonikerVtbl	typedef ptr IPersistMonikerVtbl
IPersistMoniker		STRUC
lpVtbl			LPIPersistMonikerVtbl ?
IPersistMoniker		ENDS






;HRESULT
IPersistMoniker_GetClassID_Proxy proto _CType \
		 pThis: ptr IPersistMoniker,
	      pClassID: ptr CLSID



;void
IPersistMoniker_GetClassID_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IPersistMoniker_IsDirty_Proxy proto _CType \
		 pThis: ptr IPersistMoniker



;void
IPersistMoniker_IsDirty_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IPersistMoniker_Load_Proxy proto _CType \
		 pThis: ptr IPersistMoniker,
       fFullyAvailable: BOOL,
	      pimkName: ptr IMoniker,
		  pibc: LPBC,
	       grfMode: DWORD



;void
IPersistMoniker_Load_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IPersistMoniker_Save_Proxy proto _CType \
		 pThis: ptr IPersistMoniker,
	      pimkName: ptr IMoniker,
		   pbc: LPBC,
	     fRemember: BOOL



;void
IPersistMoniker_Save_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IPersistMoniker_SaveCompleted_Proxy proto _CType \
		 pThis: ptr IPersistMoniker,
	      pimkName: ptr IMoniker,
		  pibc: LPBC



;void
IPersistMoniker_SaveCompleted_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IPersistMoniker_GetCurMoniker_Proxy proto _CType \
		 pThis: ptr IPersistMoniker,
	     ppimkName: ptr ptr IMoniker



;void
IPersistMoniker_GetCurMoniker_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IPersistMoniker_INTERFACE_DEFINED__





endif
ifndef _LPBINDPROTOCOL_DEFINED
_LPBINDPROTOCOL_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0111_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0111_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBindProtocol_INTERFACE_DEFINED__
__IBindProtocol_INTERFACE_DEFINED__ equ 1



LPBINDPROTOCOL		typedef ptr IBindProtocol


externdef		IID_IBindProtocol:IID


IBindProtocolVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface01@CT typedef proto \
		 pThis: ptr IBindProtocol,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface01@MP typedef ptr QueryInterface01@CT
	 QueryInterface QueryInterface01@MP ?

	    AddRef01@CT typedef proto \
		 pThis: ptr IBindProtocol

	    AddRef01@MP typedef ptr AddRef01@CT
		 AddRef AddRef01@MP ?

	   Release01@CT typedef proto \
		 pThis: ptr IBindProtocol

	   Release01@MP typedef ptr Release01@CT
		Release Release01@MP ?

     CreateBinding01@CT typedef proto \
		 pThis: ptr IBindProtocol,
		 szUrl: LPCWSTR,
		   pbc: ptr IBindCtx,
		   ppb: ptr ptr IBinding

     CreateBinding01@MP typedef ptr CreateBinding01@CT
	  CreateBinding CreateBinding01@MP ?

	END_INTERFACE

IBindProtocolVtbl	ENDS

LPIBindProtocolVtbl	typedef ptr IBindProtocolVtbl
IBindProtocol		STRUC
lpVtbl			LPIBindProtocolVtbl ?
IBindProtocol		ENDS






;HRESULT
IBindProtocol_CreateBinding_Proxy proto _CType \
		 pThis: ptr IBindProtocol,
		 szUrl: LPCWSTR,
		   pbc: ptr IBindCtx,
		   ppb: ptr IBinding



;void
IBindProtocol_CreateBinding_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IBindProtocol_INTERFACE_DEFINED__





endif
ifndef _LPBINDING_DEFINED
_LPBINDING_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0112_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0112_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IBinding_INTERFACE_DEFINED__
__IBinding_INTERFACE_DEFINED__ equ 1



LPBINDING		typedef ptr IBinding


externdef		IID_IBinding:IID


IBindingVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface02@CT typedef proto \
		 pThis: ptr IBinding,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface02@MP typedef ptr QueryInterface02@CT
	 QueryInterface QueryInterface02@MP ?

	    AddRef02@CT typedef proto \
		 pThis: ptr IBinding

	    AddRef02@MP typedef ptr AddRef02@CT
		 AddRef AddRef02@MP ?

	   Release02@CT typedef proto \
		 pThis: ptr IBinding

	   Release02@MP typedef ptr Release02@CT
		Release Release02@MP ?

	     Abort02@CT typedef proto \
		 pThis: ptr IBinding

	     Abort02@MP typedef ptr Abort02@CT
		  Abort Abort02@MP ?

	   Suspend02@CT typedef proto \
		 pThis: ptr IBinding

	   Suspend02@MP typedef ptr Suspend02@CT
		Suspend Suspend02@MP ?

	    Resume02@CT typedef proto \
		 pThis: ptr IBinding

	    Resume02@MP typedef ptr Resume02@CT
		 Resume Resume02@MP ?

       SetPriority02@CT typedef proto \
		 pThis: ptr IBinding,
	     nPriority: LONG

       SetPriority02@MP typedef ptr SetPriority02@CT
	    SetPriority SetPriority02@MP ?

       GetPriority02@CT typedef proto \
		 pThis: ptr IBinding,
	    pnPriority: ptr LONG

       GetPriority02@MP typedef ptr GetPriority02@CT
	    GetPriority GetPriority02@MP ?

     GetBindResult02@CT typedef proto \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	   pdwReserved: LPDWORD

     GetBindResult02@MP typedef ptr GetBindResult02@CT
	  GetBindResult GetBindResult02@MP ?

	END_INTERFACE

IBindingVtbl		ENDS

LPIBindingVtbl		typedef ptr IBindingVtbl
IBinding		STRUC
lpVtbl			LPIBindingVtbl ?
IBinding		ENDS






;HRESULT
IBinding_Abort_Proxy proto _CType \
		 pThis: ptr IBinding



;void
IBinding_Abort_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBinding_Suspend_Proxy proto _CType \
		 pThis: ptr IBinding



;void
IBinding_Suspend_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBinding_Resume_Proxy proto _CType \
		 pThis: ptr IBinding



;void
IBinding_Resume_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBinding_SetPriority_Proxy proto _CType \
		 pThis: ptr IBinding,
	     nPriority: LONG



;void
IBinding_SetPriority_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBinding_GetPriority_Proxy proto _CType \
		 pThis: ptr IBinding,
	    pnPriority: ptr LONG



;void
IBinding_GetPriority_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBinding_RemoteGetBindResult_Proxy proto _CType \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	    dwReserved: DWORD



;void
IBinding_RemoteGetBindResult_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IBinding_INTERFACE_DEFINED__





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


IBindStatusCallbackVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface03@MP typedef ptr QueryInterface03@CT
	 QueryInterface QueryInterface03@MP ?

	    AddRef03@CT typedef proto \
		 pThis: ptr IBindStatusCallback

	    AddRef03@MP typedef ptr AddRef03@CT
		 AddRef AddRef03@MP ?

	   Release03@CT typedef proto \
		 pThis: ptr IBindStatusCallback

	   Release03@MP typedef ptr Release03@CT
		Release Release03@MP ?

    OnStartBinding03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	    dwReserved: DWORD,
		   pib: ptr IBinding

    OnStartBinding03@MP typedef ptr OnStartBinding03@CT
	 OnStartBinding OnStartBinding03@MP ?

       GetPriority03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	    pnPriority: ptr LONG

       GetPriority03@MP typedef ptr GetPriority03@CT
	    GetPriority GetPriority03@MP ?

     OnLowResource03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	      reserved: DWORD

     OnLowResource03@MP typedef ptr OnLowResource03@CT
	  OnLowResource OnLowResource03@MP ?

	OnProgress03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	    ulProgress: ULONG,
	 ulProgressMax: ULONG,
	  ulStatusCode: ULONG,
	  szStatusText: LPCWSTR

	OnProgress03@MP typedef ptr OnProgress03@CT
	     OnProgress OnProgress03@MP ?

     OnStopBinding03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	       hresult: HRESULT,
	       szError: LPCWSTR

     OnStopBinding03@MP typedef ptr OnStopBinding03@CT
	  OnStopBinding OnStopBinding03@MP ?

       GetBindInfo03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr BINDINFO

       GetBindInfo03@MP typedef ptr GetBindInfo03@CT
	    GetBindInfo GetBindInfo03@MP ?

   OnDataAvailable03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr FORMATETC,
	       pstgmed: ptr STGMEDIUM

   OnDataAvailable03@MP typedef ptr OnDataAvailable03@CT
	OnDataAvailable OnDataAvailable03@MP ?

 OnObjectAvailable03@CT typedef proto \
		 pThis: ptr IBindStatusCallback,
		  riid: REFIID,
		  punk: ptr IUnknown

 OnObjectAvailable03@MP typedef ptr OnObjectAvailable03@CT
      OnObjectAvailable OnObjectAvailable03@MP ?

	END_INTERFACE

IBindStatusCallbackVtbl ENDS

LPIBindStatusCallbackVtbl typedef ptr IBindStatusCallbackVtbl
IBindStatusCallback	STRUC
lpVtbl			LPIBindStatusCallbackVtbl ?
IBindStatusCallback	ENDS






;HRESULT
IBindStatusCallback_OnStartBinding_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	    dwReserved: DWORD,
		   pib: ptr IBinding



;void
IBindStatusCallback_OnStartBinding_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_GetPriority_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	    pnPriority: ptr LONG



;void
IBindStatusCallback_GetPriority_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_OnLowResource_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	      reserved: DWORD



;void
IBindStatusCallback_OnLowResource_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_OnProgress_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	    ulProgress: ULONG,
	 ulProgressMax: ULONG,
	  ulStatusCode: ULONG,
	  szStatusText: LPCWSTR



;void
IBindStatusCallback_OnProgress_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_OnStopBinding_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	       hresult: HRESULT,
	       szError: LPCWSTR



;void
IBindStatusCallback_OnStopBinding_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_RemoteGetBindInfo_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr RemBINDINFO,
	       pstgmed: ptr RemSTGMEDIUM



;void
IBindStatusCallback_RemoteGetBindInfo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_RemoteOnDataAvailable_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr RemFORMATETC,
	       pstgmed: ptr RemSTGMEDIUM



;void
IBindStatusCallback_RemoteOnDataAvailable_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindStatusCallback_OnObjectAvailable_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
		  riid: REFIID,
		  punk: ptr IUnknown



;void
IBindStatusCallback_OnObjectAvailable_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IBindStatusCallback_INTERFACE_DEFINED__





endif
ifndef _LPAUTHENTICATION_DEFINED
_LPAUTHENTICATION_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0114_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0114_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IAuthenticate_INTERFACE_DEFINED__
__IAuthenticate_INTERFACE_DEFINED__ equ 1



LPAUTHENTICATION	typedef ptr IAuthenticate


externdef		IID_IAuthenticate:IID


IAuthenticateVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface04@CT typedef proto \
		 pThis: ptr IAuthenticate,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface04@MP typedef ptr QueryInterface04@CT
	 QueryInterface QueryInterface04@MP ?

	    AddRef04@CT typedef proto \
		 pThis: ptr IAuthenticate

	    AddRef04@MP typedef ptr AddRef04@CT
		 AddRef AddRef04@MP ?

	   Release04@CT typedef proto \
		 pThis: ptr IAuthenticate

	   Release04@MP typedef ptr Release04@CT
		Release Release04@MP ?

      Authenticate04@CT typedef proto \
		 pThis: ptr IAuthenticate,
		 phwnd: ptr HWND,
	   pszUsername: ptr LPWSTR,
	   pszPassword: ptr LPWSTR

      Authenticate04@MP typedef ptr Authenticate04@CT
	   Authenticate Authenticate04@MP ?

	END_INTERFACE

IAuthenticateVtbl	ENDS

LPIAuthenticateVtbl	typedef ptr IAuthenticateVtbl
IAuthenticate		STRUC
lpVtbl			LPIAuthenticateVtbl ?
IAuthenticate		ENDS






;HRESULT
IAuthenticate_Authenticate_Proxy proto _CType \
		 pThis: ptr IAuthenticate,
		 phwnd: ptr HWND,
	   pszUsername: ptr LPWSTR,
	   pszPassword: ptr LPWSTR



;void
IAuthenticate_Authenticate_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IAuthenticate_INTERFACE_DEFINED__





endif
ifndef _LPHTTPNEGOTIATE_DEFINED
_LPHTTPNEGOTIATE_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0115_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0115_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IHttpNegotiate_INTERFACE_DEFINED__
__IHttpNegotiate_INTERFACE_DEFINED__ equ 1



LPHTTPNEGOTIATE		typedef ptr IHttpNegotiate


externdef		IID_IHttpNegotiate:IID


IHttpNegotiateVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface05@CT typedef proto \
		 pThis: ptr IHttpNegotiate,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface05@MP typedef ptr QueryInterface05@CT
	 QueryInterface QueryInterface05@MP ?

	    AddRef05@CT typedef proto \
		 pThis: ptr IHttpNegotiate

	    AddRef05@MP typedef ptr AddRef05@CT
		 AddRef AddRef05@MP ?

	   Release05@CT typedef proto \
		 pThis: ptr IHttpNegotiate

	   Release05@MP typedef ptr Release05@CT
		Release Release05@MP ?

BeginningTransaction05@CT typedef proto \
		 pThis: ptr IHttpNegotiate,
		 szURL: LPCWSTR,
	     szHeaders: LPCWSTR,
	    dwReserved: DWORD,
  pszAdditionalHeaders: ptr LPWSTR

BeginningTransaction05@MP typedef ptr BeginningTransaction05@CT
   BeginningTransaction BeginningTransaction05@MP ?

	OnResponse05@CT typedef proto \
		 pThis: ptr IHttpNegotiate,
	dwResponseCode: DWORD,
     szResponseHeaders: LPCWSTR,
      szRequestHeaders: LPCWSTR,
pszAdditionalRequestHeaders: ptr LPWSTR

	OnResponse05@MP typedef ptr OnResponse05@CT
	     OnResponse OnResponse05@MP ?

	END_INTERFACE

IHttpNegotiateVtbl	ENDS

LPIHttpNegotiateVtbl	typedef ptr IHttpNegotiateVtbl
IHttpNegotiate		STRUC
lpVtbl			LPIHttpNegotiateVtbl ?
IHttpNegotiate		ENDS






;HRESULT
IHttpNegotiate_BeginningTransaction_Proxy proto _CType \
		 pThis: ptr IHttpNegotiate,
		 szURL: LPCWSTR,
	     szHeaders: LPCWSTR,
	    dwReserved: DWORD,
  pszAdditionalHeaders: ptr LPWSTR



;void
IHttpNegotiate_BeginningTransaction_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IHttpNegotiate_OnResponse_Proxy proto _CType \
		 pThis: ptr IHttpNegotiate,
	dwResponseCode: DWORD,
     szResponseHeaders: LPCWSTR,
      szRequestHeaders: LPCWSTR,
pszAdditionalRequestHeaders: ptr LPWSTR



;void
IHttpNegotiate_OnResponse_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IHttpNegotiate_INTERFACE_DEFINED__





endif
ifndef _LPWINDOWFORBINDINGUI_DEFINED
_LPWINDOWFORBINDINGUI_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0116_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0116_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWindowForBindingUI_INTERFACE_DEFINED__
__IWindowForBindingUI_INTERFACE_DEFINED__ equ 1



LPWINDOWFORBINDINGUI	typedef ptr IWindowForBindingUI


externdef		IID_IWindowForBindingUI:IID


IWindowForBindingUIVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface06@CT typedef proto \
		 pThis: ptr IWindowForBindingUI,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface06@MP typedef ptr QueryInterface06@CT
	 QueryInterface QueryInterface06@MP ?

	    AddRef06@CT typedef proto \
		 pThis: ptr IWindowForBindingUI

	    AddRef06@MP typedef ptr AddRef06@CT
		 AddRef AddRef06@MP ?

	   Release06@CT typedef proto \
		 pThis: ptr IWindowForBindingUI

	   Release06@MP typedef ptr Release06@CT
		Release Release06@MP ?

	 GetWindow06@CT typedef proto \
		 pThis: ptr IWindowForBindingUI,
	   rguidReason: REFGUID,
		 phwnd: ptr HWND

	 GetWindow06@MP typedef ptr GetWindow06@CT
	      GetWindow GetWindow06@MP ?

	END_INTERFACE

IWindowForBindingUIVtbl ENDS

LPIWindowForBindingUIVtbl typedef ptr IWindowForBindingUIVtbl
IWindowForBindingUI	STRUC
lpVtbl			LPIWindowForBindingUIVtbl ?
IWindowForBindingUI	ENDS






;HRESULT
IWindowForBindingUI_GetWindow_Proxy proto _CType \
		 pThis: ptr IWindowForBindingUI,
	   rguidReason: REFGUID,
		 phwnd: ptr HWND



;void
IWindowForBindingUI_GetWindow_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IWindowForBindingUI_INTERFACE_DEFINED__





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


ICodeInstallVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface07@CT typedef proto \
		 pThis: ptr ICodeInstall,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface07@MP typedef ptr QueryInterface07@CT
	 QueryInterface QueryInterface07@MP ?

	    AddRef07@CT typedef proto \
		 pThis: ptr ICodeInstall

	    AddRef07@MP typedef ptr AddRef07@CT
		 AddRef AddRef07@MP ?

	   Release07@CT typedef proto \
		 pThis: ptr ICodeInstall

	   Release07@MP typedef ptr Release07@CT
		Release Release07@MP ?

	 GetWindow07@CT typedef proto \
		 pThis: ptr ICodeInstall,
	   rguidReason: REFGUID,
		 phwnd: ptr HWND

	 GetWindow07@MP typedef ptr GetWindow07@CT
	      GetWindow GetWindow07@MP ?

OnCodeInstallProblem07@CT typedef proto \
		 pThis: ptr ICodeInstall,
	  ulStatusCode: ULONG,
	 szDestination: LPCWSTR,
	      szSource: LPCWSTR,
	    dwReserved: DWORD

OnCodeInstallProblem07@MP typedef ptr OnCodeInstallProblem07@CT
   OnCodeInstallProblem OnCodeInstallProblem07@MP ?

	END_INTERFACE

ICodeInstallVtbl	ENDS

LPICodeInstallVtbl	typedef ptr ICodeInstallVtbl
ICodeInstall		STRUC
lpVtbl			LPICodeInstallVtbl ?
ICodeInstall		ENDS






;HRESULT
ICodeInstall_OnCodeInstallProblem_Proxy proto _CType \
		 pThis: ptr ICodeInstall,
	  ulStatusCode: ULONG,
	 szDestination: LPCWSTR,
	      szSource: LPCWSTR,
	    dwReserved: DWORD



;void
ICodeInstall_OnCodeInstallProblem_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __ICodeInstall_INTERFACE_DEFINED__





endif
ifndef _LPWININETINFO_DEFINED
_LPWININETINFO_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0118_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0118_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWinInetInfo_INTERFACE_DEFINED__
__IWinInetInfo_INTERFACE_DEFINED__ equ 1



LPWININETINFO		typedef ptr IWinInetInfo


externdef		IID_IWinInetInfo:IID


IWinInetInfoVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface08@CT typedef proto \
		 pThis: ptr IWinInetInfo,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface08@MP typedef ptr QueryInterface08@CT
	 QueryInterface QueryInterface08@MP ?

	    AddRef08@CT typedef proto \
		 pThis: ptr IWinInetInfo

	    AddRef08@MP typedef ptr AddRef08@CT
		 AddRef AddRef08@MP ?

	   Release08@CT typedef proto \
		 pThis: ptr IWinInetInfo

	   Release08@MP typedef ptr Release08@CT
		Release Release08@MP ?

       QueryOption08@CT typedef proto \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD

       QueryOption08@MP typedef ptr QueryOption08@CT
	    QueryOption QueryOption08@MP ?

	END_INTERFACE

IWinInetInfoVtbl	ENDS

LPIWinInetInfoVtbl	typedef ptr IWinInetInfoVtbl
IWinInetInfo		STRUC
lpVtbl			LPIWinInetInfoVtbl ?
IWinInetInfo		ENDS






;HRESULT
IWinInetInfo_RemoteQueryOption_Proxy proto _CType \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD



;void
IWinInetInfo_RemoteQueryOption_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IWinInetInfo_INTERFACE_DEFINED__





endif
WININETINFO_OPTION_LOCK_HANDLE equ 65534
ifndef _LPHTTPSECURITY_DEFINED
_LPHTTPSECURITY_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0119_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0119_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IHttpSecurity_INTERFACE_DEFINED__
__IHttpSecurity_INTERFACE_DEFINED__ equ 1



LPHTTPSECURITY		typedef ptr IHttpSecurity


externdef		IID_IHttpSecurity:IID


IHttpSecurityVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface09@CT typedef proto \
		 pThis: ptr IHttpSecurity,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface09@MP typedef ptr QueryInterface09@CT
	 QueryInterface QueryInterface09@MP ?

	    AddRef09@CT typedef proto \
		 pThis: ptr IHttpSecurity

	    AddRef09@MP typedef ptr AddRef09@CT
		 AddRef AddRef09@MP ?

	   Release09@CT typedef proto \
		 pThis: ptr IHttpSecurity

	   Release09@MP typedef ptr Release09@CT
		Release Release09@MP ?

	 GetWindow09@CT typedef proto \
		 pThis: ptr IHttpSecurity,
	   rguidReason: REFGUID,
		 phwnd: ptr HWND

	 GetWindow09@MP typedef ptr GetWindow09@CT
	      GetWindow GetWindow09@MP ?

 OnSecurityProblem09@CT typedef proto \
		 pThis: ptr IHttpSecurity,
	     dwProblem: DWORD

 OnSecurityProblem09@MP typedef ptr OnSecurityProblem09@CT
      OnSecurityProblem OnSecurityProblem09@MP ?

	END_INTERFACE

IHttpSecurityVtbl	ENDS

LPIHttpSecurityVtbl	typedef ptr IHttpSecurityVtbl
IHttpSecurity		STRUC
lpVtbl			LPIHttpSecurityVtbl ?
IHttpSecurity		ENDS






;HRESULT
IHttpSecurity_OnSecurityProblem_Proxy proto _CType \
		 pThis: ptr IHttpSecurity,
	     dwProblem: DWORD



;void
IHttpSecurity_OnSecurityProblem_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IHttpSecurity_INTERFACE_DEFINED__





endif
ifndef _LPWININETHTTPINFO_DEFINED
_LPWININETHTTPINFO_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0120_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0120_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWinInetHttpInfo_INTERFACE_DEFINED__
__IWinInetHttpInfo_INTERFACE_DEFINED__ equ 1



LPWININETHTTPINFO	typedef ptr IWinInetHttpInfo


externdef		IID_IWinInetHttpInfo:IID


IWinInetHttpInfoVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface10@CT typedef proto \
		 pThis: ptr IWinInetHttpInfo,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface10@MP typedef ptr QueryInterface10@CT
	 QueryInterface QueryInterface10@MP ?

	    AddRef10@CT typedef proto \
		 pThis: ptr IWinInetHttpInfo

	    AddRef10@MP typedef ptr AddRef10@CT
		 AddRef AddRef10@MP ?

	   Release10@CT typedef proto \
		 pThis: ptr IWinInetHttpInfo

	   Release10@MP typedef ptr Release10@CT
		Release Release10@MP ?

       QueryOption10@CT typedef proto \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD

       QueryOption10@MP typedef ptr QueryOption10@CT
	    QueryOption QueryOption10@MP ?

	 QueryInfo10@CT typedef proto \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD

	 QueryInfo10@MP typedef ptr QueryInfo10@CT
	      QueryInfo QueryInfo10@MP ?

	END_INTERFACE

IWinInetHttpInfoVtbl	ENDS

LPIWinInetHttpInfoVtbl	typedef ptr IWinInetHttpInfoVtbl
IWinInetHttpInfo	STRUC
lpVtbl			LPIWinInetHttpInfoVtbl ?
IWinInetHttpInfo	ENDS






;HRESULT
IWinInetHttpInfo_RemoteQueryInfo_Proxy proto _CType \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD



;void
IWinInetHttpInfo_RemoteQueryInfo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IWinInetHttpInfo_INTERFACE_DEFINED__





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



LPBINDHOST		typedef ptr IBindHost


externdef		IID_IBindHost:IID


IBindHostVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface11@CT typedef proto \
		 pThis: ptr IBindHost,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface11@MP typedef ptr QueryInterface11@CT
	 QueryInterface QueryInterface11@MP ?

	    AddRef11@CT typedef proto \
		 pThis: ptr IBindHost

	    AddRef11@MP typedef ptr AddRef11@CT
		 AddRef AddRef11@MP ?

	   Release11@CT typedef proto \
		 pThis: ptr IBindHost

	   Release11@MP typedef ptr Release11@CT
		Release Release11@MP ?

     CreateMoniker11@CT typedef proto \
		 pThis: ptr IBindHost,
		szName: LPOLESTR,
		   pBC: ptr IBindCtx,
		  ppmk: ptr ptr IMoniker,
	    dwReserved: DWORD

     CreateMoniker11@MP typedef ptr CreateMoniker11@CT
	  CreateMoniker CreateMoniker11@MP ?

MonikerBindToStorage11@CT typedef proto \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: PVOID

MonikerBindToStorage11@MP typedef ptr MonikerBindToStorage11@CT
   MonikerBindToStorage MonikerBindToStorage11@MP ?

MonikerBindToObject11@CT typedef proto \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: PVOID

MonikerBindToObject11@MP typedef ptr MonikerBindToObject11@CT
    MonikerBindToObject MonikerBindToObject11@MP ?

	END_INTERFACE

IBindHostVtbl		ENDS

LPIBindHostVtbl		typedef ptr IBindHostVtbl
IBindHost		STRUC
lpVtbl			LPIBindHostVtbl ?
IBindHost		ENDS






;HRESULT
IBindHost_CreateMoniker_Proxy proto _CType \
		 pThis: ptr IBindHost,
		szName: LPOLESTR,
		   pBC: ptr IBindCtx,
		  ppmk: ptr ptr IMoniker,
	    dwReserved: DWORD



;void
IBindHost_CreateMoniker_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindHost_RemoteMonikerBindToStorage_Proxy proto _CType \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown



;void
IBindHost_RemoteMonikerBindToStorage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IBindHost_RemoteMonikerBindToObject_Proxy proto _CType \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown



;void
IBindHost_RemoteMonikerBindToObject_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IBindHost_INTERFACE_DEFINED__





endif

;; These are for backwards compatibility with previous URLMON versions
;; Flags for the UrlDownloadToCacheFile
URLOSTRM_USECACHEDCOPY_ONLY equ 0x1	 ;; Only get from cache
URLOSTRM_USECACHEDCOPY	equ 0x2	 ;; Get from cache if available else download
URLOSTRM_GETNEWESTVERSION equ 0x3	 ;; Get new version only. But put it in cache too


;IBindStatusCallback	typedef STRUC
;STDAPI
HlinkSimpleNavigateToString proto _CType \
	      szTarget: LPCWSTR,
	    szLocation: LPCWSTR,
     szTargetFrameName: LPCWSTR,
		  pUnk: ptr IUnknown,
		   pbc: ptr IBindCtx,
		      : ptr IBindStatusCallback,
	       grfHLNF: DWORD,
	    dwReserved: DWORD


;STDAPI
HlinkSimpleNavigateToMoniker proto _CType \
	     pmkTarget: ptr IMoniker,
	    szLocation: LPCWSTR,
     szTargetFrameName: LPCWSTR,
		  pUnk: ptr IUnknown,
		   pbc: ptr IBindCtx,
		      : ptr IBindStatusCallback,
	       grfHLNF: DWORD,
	    dwReserved: DWORD


;STDAPI
;STDAPI
;STDAPI
;STDAPI
;STDAPI
;STDAPI
;STDAPI
;STDAPI
;STDAPI
;STDAPI

ifdef _UNICODE
URLOpenStream		equ URLOpenStreamW
URLOpenPullStream	equ URLOpenPullStreamW
URLDownloadToFile	equ URLDownloadToFileW
URLDownloadToCacheFile	equ URLDownloadToCacheFileW
URLOpenBlockingStream	equ URLOpenBlockingStreamW
else
URLOpenStream		equ URLOpenStreamA
URLOpenPullStream	equ URLOpenPullStreamA
URLDownloadToFile	equ URLDownloadToFileA
URLDownloadToCacheFile	equ URLDownloadToCacheFileA
URLOpenBlockingStream	equ URLOpenBlockingStreamA
endif ;; NOT UNICODE


;STDAPI
HlinkGoBack proto _CType \
		  pUnk: ptr IUnknown

;STDAPI
HlinkGoForward proto _CType \
		  pUnk: ptr IUnknown

;STDAPI
HlinkNavigateString proto _CType \
		  pUnk: ptr IUnknown,
	      szTarget: LPCWSTR

;STDAPI
HlinkNavigateMoniker proto _CType \
		  pUnk: ptr IUnknown,
	     pmkTarget: ptr IMoniker


ifndef	 _URLMON_NO_ASYNC_PLUGABLE_PROTOCOLS_







ifndef _LPIINTERNET
_LPIINTERNET equ 1


externdef		__MIDL_itf_urlmon_0122_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0122_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternet_INTERFACE_DEFINED__
__IInternet_INTERFACE_DEFINED__ equ 1



LPIINTERNET		typedef ptr IInternet


externdef		IID_IInternet:IID


IInternetVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface12@CT typedef proto \
		 pThis: ptr IInternet,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface12@MP typedef ptr QueryInterface12@CT
	 QueryInterface QueryInterface12@MP ?

	    AddRef12@CT typedef proto \
		 pThis: ptr IInternet

	    AddRef12@MP typedef ptr AddRef12@CT
		 AddRef AddRef12@MP ?

	   Release12@CT typedef proto \
		 pThis: ptr IInternet

	   Release12@MP typedef ptr Release12@CT
		Release Release12@MP ?

	END_INTERFACE

IInternetVtbl		ENDS

LPIInternetVtbl		typedef ptr IInternetVtbl
IInternet		STRUC
lpVtbl			LPIInternetVtbl ?
IInternet		ENDS







endif	;; __IInternet_INTERFACE_DEFINED__





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


IInternetBindInfoVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface13@CT typedef proto \
		 pThis: ptr IInternetBindInfo,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface13@MP typedef ptr QueryInterface13@CT
	 QueryInterface QueryInterface13@MP ?

	    AddRef13@CT typedef proto \
		 pThis: ptr IInternetBindInfo

	    AddRef13@MP typedef ptr AddRef13@CT
		 AddRef AddRef13@MP ?

	   Release13@CT typedef proto \
		 pThis: ptr IInternetBindInfo

	   Release13@MP typedef ptr Release13@CT
		Release Release13@MP ?

       GetBindInfo13@CT typedef proto \
		 pThis: ptr IInternetBindInfo,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr BINDINFO

       GetBindInfo13@MP typedef ptr GetBindInfo13@CT
	    GetBindInfo GetBindInfo13@MP ?

     GetBindString13@CT typedef proto \
		 pThis: ptr IInternetBindInfo,
	  ulStringType: ULONG,
	       ppwzStr: ptr LPOLESTR,
		   cEl: ULONG,
	   pcElFetched: ptr ULONG

     GetBindString13@MP typedef ptr GetBindString13@CT
	  GetBindString GetBindString13@MP ?

	END_INTERFACE

IInternetBindInfoVtbl	ENDS

LPIInternetBindInfoVtbl typedef ptr IInternetBindInfoVtbl
IInternetBindInfo	STRUC
lpVtbl			LPIInternetBindInfoVtbl ?
IInternetBindInfo	ENDS






;HRESULT
IInternetBindInfo_GetBindInfo_Proxy proto _CType \
		 pThis: ptr IInternetBindInfo,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr BINDINFO



;void
IInternetBindInfo_GetBindInfo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetBindInfo_GetBindString_Proxy proto _CType \
		 pThis: ptr IInternetBindInfo,
	  ulStringType: ULONG,
	       ppwzStr: ptr LPOLESTR,
		   cEl: ULONG,
	   pcElFetched: ptr ULONG



;void
IInternetBindInfo_GetBindString_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetBindInfo_INTERFACE_DEFINED__





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


IInternetProtocolRootVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface14@MP typedef ptr QueryInterface14@CT
	 QueryInterface QueryInterface14@MP ?

	    AddRef14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot

	    AddRef14@MP typedef ptr AddRef14@CT
		 AddRef AddRef14@MP ?

	   Release14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot

	   Release14@MP typedef ptr Release14@CT
		Release Release14@MP ?

	     Start14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot,
		 szUrl: LPCWSTR,
	   pOIProtSink: ptr IInternetProtocolSink,
	   pOIBindInfo: ptr IInternetBindInfo,
		 grfPI: DWORD,
	    dwReserved: DWORD

	     Start14@MP typedef ptr Start14@CT
		  Start Start14@MP ?

	  Continue14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot,
	 pProtocolData: ptr PROTOCOLDATA

	  Continue14@MP typedef ptr Continue14@CT
	       Continue Continue14@MP ?

	     Abort14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot,
	      hrReason: HRESULT,
	     dwOptions: DWORD

	     Abort14@MP typedef ptr Abort14@CT
		  Abort Abort14@MP ?

	 Terminate14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot,
	     dwOptions: DWORD

	 Terminate14@MP typedef ptr Terminate14@CT
	      Terminate Terminate14@MP ?

	   Suspend14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot

	   Suspend14@MP typedef ptr Suspend14@CT
		Suspend Suspend14@MP ?

	    Resume14@CT typedef proto \
		 pThis: ptr IInternetProtocolRoot

	    Resume14@MP typedef ptr Resume14@CT
		 Resume Resume14@MP ?

	END_INTERFACE

IInternetProtocolRootVtbl ENDS

LPIInternetProtocolRootVtbl typedef ptr IInternetProtocolRootVtbl
IInternetProtocolRoot	STRUC
lpVtbl			LPIInternetProtocolRootVtbl ?
IInternetProtocolRoot	ENDS






;HRESULT
IInternetProtocolRoot_Start_Proxy proto _CType \
		 pThis: ptr IInternetProtocolRoot,
		 szUrl: LPCWSTR,
	   pOIProtSink: ptr IInternetProtocolSink,
	   pOIBindInfo: ptr IInternetBindInfo,
		 grfPI: DWORD,
	    dwReserved: DWORD



;void
IInternetProtocolRoot_Start_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolRoot_Continue_Proxy proto _CType \
		 pThis: ptr IInternetProtocolRoot,
	 pProtocolData: ptr PROTOCOLDATA



;void
IInternetProtocolRoot_Continue_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolRoot_Abort_Proxy proto _CType \
		 pThis: ptr IInternetProtocolRoot,
	      hrReason: HRESULT,
	     dwOptions: DWORD



;void
IInternetProtocolRoot_Abort_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolRoot_Terminate_Proxy proto _CType \
		 pThis: ptr IInternetProtocolRoot,
	     dwOptions: DWORD



;void
IInternetProtocolRoot_Terminate_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolRoot_Suspend_Proxy proto _CType \
		 pThis: ptr IInternetProtocolRoot



;void
IInternetProtocolRoot_Suspend_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolRoot_Resume_Proxy proto _CType \
		 pThis: ptr IInternetProtocolRoot



;void
IInternetProtocolRoot_Resume_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetProtocolRoot_INTERFACE_DEFINED__





endif
ifndef _LPIINTERNETPROTOCOL_DEFINED
_LPIINTERNETPROTOCOL_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0125_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0125_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetProtocol_INTERFACE_DEFINED__
__IInternetProtocol_INTERFACE_DEFINED__ equ 1



LPIINTERNETPROTOCOL	typedef ptr IInternetProtocol


externdef		IID_IInternetProtocol:IID


IInternetProtocolVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface15@MP typedef ptr QueryInterface15@CT
	 QueryInterface QueryInterface15@MP ?

	    AddRef15@CT typedef proto \
		 pThis: ptr IInternetProtocol

	    AddRef15@MP typedef ptr AddRef15@CT
		 AddRef AddRef15@MP ?

	   Release15@CT typedef proto \
		 pThis: ptr IInternetProtocol

	   Release15@MP typedef ptr Release15@CT
		Release Release15@MP ?

	     Start15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
		 szUrl: LPCWSTR,
	   pOIProtSink: ptr IInternetProtocolSink,
	   pOIBindInfo: ptr IInternetBindInfo,
		 grfPI: DWORD,
	    dwReserved: DWORD

	     Start15@MP typedef ptr Start15@CT
		  Start Start15@MP ?

	  Continue15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
	 pProtocolData: ptr PROTOCOLDATA

	  Continue15@MP typedef ptr Continue15@CT
	       Continue Continue15@MP ?

	     Abort15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
	      hrReason: HRESULT,
	     dwOptions: DWORD

	     Abort15@MP typedef ptr Abort15@CT
		  Abort Abort15@MP ?

	 Terminate15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
	     dwOptions: DWORD

	 Terminate15@MP typedef ptr Terminate15@CT
	      Terminate Terminate15@MP ?

	   Suspend15@CT typedef proto \
		 pThis: ptr IInternetProtocol

	   Suspend15@MP typedef ptr Suspend15@CT
		Suspend Suspend15@MP ?

	    Resume15@CT typedef proto \
		 pThis: ptr IInternetProtocol

	    Resume15@MP typedef ptr Resume15@CT
		 Resume Resume15@MP ?

	      Read15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: ptr ULONG

	      Read15@MP typedef ptr Read15@CT
		   Read Read15@MP ?

	      Seek15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER

	      Seek15@MP typedef ptr Seek15@CT
		   Seek Seek15@MP ?

       LockRequest15@CT typedef proto \
		 pThis: ptr IInternetProtocol,
	     dwOptions: DWORD

       LockRequest15@MP typedef ptr LockRequest15@CT
	    LockRequest LockRequest15@MP ?

     UnlockRequest15@CT typedef proto \
		 pThis: ptr IInternetProtocol

     UnlockRequest15@MP typedef ptr UnlockRequest15@CT
	  UnlockRequest UnlockRequest15@MP ?

	END_INTERFACE

IInternetProtocolVtbl	ENDS

LPIInternetProtocolVtbl typedef ptr IInternetProtocolVtbl
IInternetProtocol	STRUC
lpVtbl			LPIInternetProtocolVtbl ?
IInternetProtocol	ENDS






;HRESULT
IInternetProtocol_Read_Proxy proto _CType \
		 pThis: ptr IInternetProtocol,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: ptr ULONG



;void
IInternetProtocol_Read_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocol_Seek_Proxy proto _CType \
		 pThis: ptr IInternetProtocol,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER



;void
IInternetProtocol_Seek_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocol_LockRequest_Proxy proto _CType \
		 pThis: ptr IInternetProtocol,
	     dwOptions: DWORD



;void
IInternetProtocol_LockRequest_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocol_UnlockRequest_Proxy proto _CType \
		 pThis: ptr IInternetProtocol



;void
IInternetProtocol_UnlockRequest_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetProtocol_INTERFACE_DEFINED__





endif
ifndef _LPIINTERNETPROTOCOLSINK_DEFINED
_LPIINTERNETPROTOCOLSINK_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0126_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0126_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetProtocolSink_INTERFACE_DEFINED__
__IInternetProtocolSink_INTERFACE_DEFINED__ equ 1



LPIINTERNETPROTOCOLSINK typedef ptr IInternetProtocolSink


externdef		IID_IInternetProtocolSink:IID


IInternetProtocolSinkVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface16@MP typedef ptr QueryInterface16@CT
	 QueryInterface QueryInterface16@MP ?

	    AddRef16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink

	    AddRef16@MP typedef ptr AddRef16@CT
		 AddRef AddRef16@MP ?

	   Release16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink

	   Release16@MP typedef ptr Release16@CT
		Release Release16@MP ?

	    Switch16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink,
	 pProtocolData: ptr PROTOCOLDATA

	    Switch16@MP typedef ptr Switch16@CT
		 Switch Switch16@MP ?

    ReportProgress16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink,
	  ulStatusCode: ULONG,
	  szStatusText: LPCWSTR

    ReportProgress16@MP typedef ptr ReportProgress16@CT
	 ReportProgress ReportProgress16@MP ?

	ReportData16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink,
	       grfBSCF: DWORD,
	    ulProgress: ULONG,
	 ulProgressMax: ULONG

	ReportData16@MP typedef ptr ReportData16@CT
	     ReportData ReportData16@MP ?

      ReportResult16@CT typedef proto \
		 pThis: ptr IInternetProtocolSink,
	      hrResult: HRESULT,
	       dwError: DWORD,
	      szResult: LPCWSTR

      ReportResult16@MP typedef ptr ReportResult16@CT
	   ReportResult ReportResult16@MP ?

	END_INTERFACE

IInternetProtocolSinkVtbl ENDS

LPIInternetProtocolSinkVtbl typedef ptr IInternetProtocolSinkVtbl
IInternetProtocolSink	STRUC
lpVtbl			LPIInternetProtocolSinkVtbl ?
IInternetProtocolSink	ENDS






;HRESULT
IInternetProtocolSink_Switch_Proxy proto _CType \
		 pThis: ptr IInternetProtocolSink,
	 pProtocolData: ptr PROTOCOLDATA



;void
IInternetProtocolSink_Switch_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolSink_ReportProgress_Proxy proto _CType \
		 pThis: ptr IInternetProtocolSink,
	  ulStatusCode: ULONG,
	  szStatusText: LPCWSTR



;void
IInternetProtocolSink_ReportProgress_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolSink_ReportData_Proxy proto _CType \
		 pThis: ptr IInternetProtocolSink,
	       grfBSCF: DWORD,
	    ulProgress: ULONG,
	 ulProgressMax: ULONG



;void
IInternetProtocolSink_ReportData_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolSink_ReportResult_Proxy proto _CType \
		 pThis: ptr IInternetProtocolSink,
	      hrResult: HRESULT,
	       dwError: DWORD,
	      szResult: LPCWSTR



;void
IInternetProtocolSink_ReportResult_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetProtocolSink_INTERFACE_DEFINED__





endif
ifndef _LPIINTERNETSESSION_DEFINED
_LPIINTERNETSESSION_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0127_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0127_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetSession_INTERFACE_DEFINED__
__IInternetSession_INTERFACE_DEFINED__ equ 1



LPIINTERNETSESSION	typedef ptr IInternetSession

;typedef enum _tagOIBDG_FLAGS

OIBDG_APARTMENTTHREADED equ 0x100


externdef		IID_IInternetSession:IID


IInternetSessionVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface17@CT typedef proto \
		 pThis: ptr IInternetSession,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface17@MP typedef ptr QueryInterface17@CT
	 QueryInterface QueryInterface17@MP ?

	    AddRef17@CT typedef proto \
		 pThis: ptr IInternetSession

	    AddRef17@MP typedef ptr AddRef17@CT
		 AddRef AddRef17@MP ?

	   Release17@CT typedef proto \
		 pThis: ptr IInternetSession

	   Release17@MP typedef ptr Release17@CT
		Release Release17@MP ?

 RegisterNameSpace17@CT typedef proto \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
		rclsid: REFCLSID,
	   pwzProtocol: LPCWSTR,
	     cPatterns: ULONG,
	  ppwzPatterns: ptr LPCWSTR,
	    dwReserved: DWORD

 RegisterNameSpace17@MP typedef ptr RegisterNameSpace17@CT
      RegisterNameSpace RegisterNameSpace17@MP ?

UnregisterNameSpace17@CT typedef proto \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
	   pszProtocol: LPCWSTR

UnregisterNameSpace17@MP typedef ptr UnregisterNameSpace17@CT
    UnregisterNameSpace UnregisterNameSpace17@MP ?

RegisterMimeFilter17@CT typedef proto \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
		rclsid: REFCLSID,
	       pwzType: LPCWSTR

RegisterMimeFilter17@MP typedef ptr RegisterMimeFilter17@CT
     RegisterMimeFilter RegisterMimeFilter17@MP ?

UnregisterMimeFilter17@CT typedef proto \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
	       pwzType: LPCWSTR

UnregisterMimeFilter17@MP typedef ptr UnregisterMimeFilter17@CT
   UnregisterMimeFilter UnregisterMimeFilter17@MP ?

     CreateBinding17@CT typedef proto \
		 pThis: ptr IInternetSession,
		   pBC: LPBC,
		 szUrl: LPCWSTR,
	     pUnkOuter: ptr IUnknown,
		 ppUnk: ptr IUnknown,
	   ppOInetProt: ptr IInternetProtocol,
	      dwOption: DWORD

     CreateBinding17@MP typedef ptr CreateBinding17@CT
	  CreateBinding CreateBinding17@MP ?

  SetSessionOption17@CT typedef proto \
		 pThis: ptr IInternetSession,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
	    dwReserved: DWORD

  SetSessionOption17@MP typedef ptr SetSessionOption17@CT
       SetSessionOption SetSessionOption17@MP ?

  GetSessionOption17@CT typedef proto \
		 pThis: ptr IInternetSession,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
       pdwBufferLength: LPDWORD,
	    dwReserved: DWORD

  GetSessionOption17@MP typedef ptr GetSessionOption17@CT
       GetSessionOption GetSessionOption17@MP ?

	END_INTERFACE

IInternetSessionVtbl	ENDS

LPIInternetSessionVtbl	typedef ptr IInternetSessionVtbl
IInternetSession	STRUC
lpVtbl			LPIInternetSessionVtbl ?
IInternetSession	ENDS






;HRESULT
IInternetSession_RegisterNameSpace_Proxy proto _CType \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
		rclsid: REFCLSID,
	   pwzProtocol: LPCWSTR,
	     cPatterns: ULONG,
	  ppwzPatterns: ptr LPCWSTR,
	    dwReserved: DWORD



;void
IInternetSession_RegisterNameSpace_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSession_UnregisterNameSpace_Proxy proto _CType \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
	   pszProtocol: LPCWSTR



;void
IInternetSession_UnregisterNameSpace_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSession_RegisterMimeFilter_Proxy proto _CType \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
		rclsid: REFCLSID,
	       pwzType: LPCWSTR



;void
IInternetSession_RegisterMimeFilter_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSession_UnregisterMimeFilter_Proxy proto _CType \
		 pThis: ptr IInternetSession,
		   pCF: ptr IClassFactory,
	       pwzType: LPCWSTR



;void
IInternetSession_UnregisterMimeFilter_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSession_CreateBinding_Proxy proto _CType \
		 pThis: ptr IInternetSession,
		   pBC: LPBC,
		 szUrl: LPCWSTR,
	     pUnkOuter: ptr IUnknown,
		 ppUnk: ptr IUnknown,
	   ppOInetProt: ptr IInternetProtocol,
	      dwOption: DWORD



;void
IInternetSession_CreateBinding_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSession_SetSessionOption_Proxy proto _CType \
		 pThis: ptr IInternetSession,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
	dwBufferLength: DWORD,
	    dwReserved: DWORD



;void
IInternetSession_SetSessionOption_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSession_GetSessionOption_Proxy proto _CType \
		 pThis: ptr IInternetSession,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
       pdwBufferLength: LPDWORD,
	    dwReserved: DWORD



;void
IInternetSession_GetSessionOption_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetSession_INTERFACE_DEFINED__





endif
ifndef _LPIINTERNETTHREADSWITCH_DEFINED
_LPIINTERNETTHREADSWITCH_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0128_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0128_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetThreadSwitch_INTERFACE_DEFINED__
__IInternetThreadSwitch_INTERFACE_DEFINED__ equ 1



LPIINTERNETTHREADSWITCH typedef ptr IInternetThreadSwitch


externdef		IID_IInternetThreadSwitch:IID


IInternetThreadSwitchVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface18@CT typedef proto \
		 pThis: ptr IInternetThreadSwitch,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface18@MP typedef ptr QueryInterface18@CT
	 QueryInterface QueryInterface18@MP ?

	    AddRef18@CT typedef proto \
		 pThis: ptr IInternetThreadSwitch

	    AddRef18@MP typedef ptr AddRef18@CT
		 AddRef AddRef18@MP ?

	   Release18@CT typedef proto \
		 pThis: ptr IInternetThreadSwitch

	   Release18@MP typedef ptr Release18@CT
		Release Release18@MP ?

	   Prepare18@CT typedef proto \
		 pThis: ptr IInternetThreadSwitch

	   Prepare18@MP typedef ptr Prepare18@CT
		Prepare Prepare18@MP ?

	  Continue18@CT typedef proto \
		 pThis: ptr IInternetThreadSwitch

	  Continue18@MP typedef ptr Continue18@CT
	       Continue Continue18@MP ?

	END_INTERFACE

IInternetThreadSwitchVtbl ENDS

LPIInternetThreadSwitchVtbl typedef ptr IInternetThreadSwitchVtbl
IInternetThreadSwitch	STRUC
lpVtbl			LPIInternetThreadSwitchVtbl ?
IInternetThreadSwitch	ENDS






;HRESULT
IInternetThreadSwitch_Prepare_Proxy proto _CType \
		 pThis: ptr IInternetThreadSwitch



;void
IInternetThreadSwitch_Prepare_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetThreadSwitch_Continue_Proxy proto _CType \
		 pThis: ptr IInternetThreadSwitch



;void
IInternetThreadSwitch_Continue_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetThreadSwitch_INTERFACE_DEFINED__





endif
ifndef _LPIINTERNETPRIORITY_DEFINED
_LPIINTERNETPRIORITY_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0129_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0129_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetPriority_INTERFACE_DEFINED__
__IInternetPriority_INTERFACE_DEFINED__ equ 1



LPIINTERNETPRIORITY	typedef ptr IInternetPriority


externdef		IID_IInternetPriority:IID


IInternetPriorityVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface19@CT typedef proto \
		 pThis: ptr IInternetPriority,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface19@MP typedef ptr QueryInterface19@CT
	 QueryInterface QueryInterface19@MP ?

	    AddRef19@CT typedef proto \
		 pThis: ptr IInternetPriority

	    AddRef19@MP typedef ptr AddRef19@CT
		 AddRef AddRef19@MP ?

	   Release19@CT typedef proto \
		 pThis: ptr IInternetPriority

	   Release19@MP typedef ptr Release19@CT
		Release Release19@MP ?

       SetPriority19@CT typedef proto \
		 pThis: ptr IInternetPriority,
	     nPriority: LONG

       SetPriority19@MP typedef ptr SetPriority19@CT
	    SetPriority SetPriority19@MP ?

       GetPriority19@CT typedef proto \
		 pThis: ptr IInternetPriority,
	    pnPriority: ptr LONG

       GetPriority19@MP typedef ptr GetPriority19@CT
	    GetPriority GetPriority19@MP ?

	END_INTERFACE

IInternetPriorityVtbl	ENDS

LPIInternetPriorityVtbl typedef ptr IInternetPriorityVtbl
IInternetPriority	STRUC
lpVtbl			LPIInternetPriorityVtbl ?
IInternetPriority	ENDS






;HRESULT
IInternetPriority_SetPriority_Proxy proto _CType \
		 pThis: ptr IInternetPriority,
	     nPriority: LONG



;void
IInternetPriority_SetPriority_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetPriority_GetPriority_Proxy proto _CType \
		 pThis: ptr IInternetPriority,
	    pnPriority: ptr LONG



;void
IInternetPriority_GetPriority_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetPriority_INTERFACE_DEFINED__





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


IInternetProtocolInfoVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface20@MP typedef ptr QueryInterface20@CT
	 QueryInterface QueryInterface20@MP ?

	    AddRef20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo

	    AddRef20@MP typedef ptr AddRef20@CT
		 AddRef AddRef20@MP ?

	   Release20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo

	   Release20@MP typedef ptr Release20@CT
		Release Release20@MP ?

	  ParseUrl20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo,
		pwzUrl: LPCWSTR,
	   ParseAction: PARSEACTION,
	  dwParseFlags: DWORD,
	     pwzResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: LPDWORD,
	    dwReserved: DWORD

	  ParseUrl20@MP typedef ptr ParseUrl20@CT
	       ParseUrl ParseUrl20@MP ?

	CombineUrl20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo,
	    pwzBaseUrl: LPCWSTR,
	pwzRelativeUrl: LPCWSTR,
	dwCombineFlags: DWORD,
	     pwzResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: LPDWORD,
	    dwReserved: DWORD

	CombineUrl20@MP typedef ptr CombineUrl20@CT
	     CombineUrl CombineUrl20@MP ?

	CompareUrl20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo,
	       pwzUrl1: LPCWSTR,
	       pwzUrl2: LPCWSTR,
	dwCompareFlags: DWORD

	CompareUrl20@MP typedef ptr CompareUrl20@CT
	     CompareUrl CompareUrl20@MP ?

	 QueryInfo20@CT typedef proto \
		 pThis: ptr IInternetProtocolInfo,
		pwzUrl: LPCWSTR,
	   OueryOption: QUERYOPTION,
	  dwQueryFlags: DWORD,
	       pBuffer: LPVOID,
	      cbBuffer: DWORD,
		pcbBuf: LPDWORD,
	    dwReserved: DWORD

	 QueryInfo20@MP typedef ptr QueryInfo20@CT
	      QueryInfo QueryInfo20@MP ?

	END_INTERFACE

IInternetProtocolInfoVtbl ENDS

LPIInternetProtocolInfoVtbl typedef ptr IInternetProtocolInfoVtbl
IInternetProtocolInfo	STRUC
lpVtbl			LPIInternetProtocolInfoVtbl ?
IInternetProtocolInfo	ENDS






;HRESULT
IInternetProtocolInfo_ParseUrl_Proxy proto _CType \
		 pThis: ptr IInternetProtocolInfo,
		pwzUrl: LPCWSTR,
	   ParseAction: PARSEACTION,
	  dwParseFlags: DWORD,
	     pwzResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: LPDWORD,
	    dwReserved: DWORD



;void
IInternetProtocolInfo_ParseUrl_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolInfo_CombineUrl_Proxy proto _CType \
		 pThis: ptr IInternetProtocolInfo,
	    pwzBaseUrl: LPCWSTR,
	pwzRelativeUrl: LPCWSTR,
	dwCombineFlags: DWORD,
	     pwzResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: LPDWORD,
	    dwReserved: DWORD



;void
IInternetProtocolInfo_CombineUrl_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolInfo_CompareUrl_Proxy proto _CType \
		 pThis: ptr IInternetProtocolInfo,
	       pwzUrl1: LPCWSTR,
	       pwzUrl2: LPCWSTR,
	dwCompareFlags: DWORD



;void
IInternetProtocolInfo_CompareUrl_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetProtocolInfo_QueryInfo_Proxy proto _CType \
		 pThis: ptr IInternetProtocolInfo,
		pwzUrl: LPCWSTR,
	   OueryOption: QUERYOPTION,
	  dwQueryFlags: DWORD,
	       pBuffer: LPVOID,
	      cbBuffer: DWORD,
		pcbBuf: LPDWORD,
	    dwReserved: DWORD



;void
IInternetProtocolInfo_QueryInfo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetProtocolInfo_INTERFACE_DEFINED__

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
CoInternetParseUrl proto _CType \
		pwzUrl: LPCWSTR,
	   ParseAction: PARSEACTION,
	       dwFlags: DWORD,
	     pszResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetCombineUrl proto _CType \
	    pwzBaseUrl: LPCWSTR,
	pwzRelativeUrl: LPCWSTR,
	dwCombineFlags: DWORD,
	     pszResult: LPWSTR,
	     cchResult: DWORD,
	    pcchResult: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetCompareUrl proto _CType \
	       pwzUrl1: LPCWSTR,
	       pwzUrl2: LPCWSTR,
	       dwFlags: DWORD

;STDAPI
CoInternetGetProtocolFlags proto _CType \
		pwzUrl: LPCWSTR,
	      pdwFlags: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetQueryInfo proto _CType \
		pwzUrl: LPCWSTR,
	  QueryOptions: QUERYOPTION,
	  dwQueryFlags: DWORD,
	      pvBuffer: LPVOID,
	      cbBuffer: DWORD,
	     pcbBuffer: ptr DWORD,
	    dwReserved: DWORD

;STDAPI
CoInternetGetSession proto _CType \
	 dwSessionMode: DWORD,
    ppIInternetSession: ptr IInternetSession,
	    dwReserved: DWORD

;STDAPI
CoInternetGetSecurityUrl proto _CType \
		pwzUrl: LPCWSTR,
	    ppwzSecUrl: ptr LPWSTR,
	     psuAction: PSUACTION,
	    dwReserved: DWORD


;STDAPI
CopyStgMedium proto _CType \
	   pcstgmedSrc: ptr STGMEDIUM,
	   pstgmedDest: ptr STGMEDIUM

;STDAPI
CopyBindInfo proto _CType \
	       pcbiSrc: ptr BINDINFO,
	       pbiDest: ptr BINDINFO

;STDAPI_(void)
ReleaseBindInfo proto _CType \
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
endif ;; NOT _URLMON_NO_ASYNC_PLUGABLE_PROTOCOLS_
;;
;; Static Protocol flags
;;
PROTOCOLFLAG_NO_PICS_CHECK equ 0x00000001

;; Creates the security manager object. The first argument is the Service provider
;; to allow for delegation
;STDAPI
CoInternetCreateSecurityManager proto _CType \
		   pSP: ptr IServiceProvider,
		  ppSM: ptr IInternetSecurityManager,
	    dwReserved: DWORD


;STDAPI
CoInternetCreateZoneManager proto _CType \
		   pSP: ptr IServiceProvider,
		  ppZM: ptr IInternetZoneManager,
	    dwReserved: DWORD



;; Security manager CLSID's
externdef		CLSID_InternetSecurityManager:IID
externdef		CLSID_InternetZoneManager:IID
;; pThis service is used for delegation support on the Security Manager interface
SID_SInternetSecurityManager equ IID_IInternetSecurityManager

SID_SInternetHostSecurityManager equ IID_IInternetHostSecurityManager

ifndef _LPINTERNETSECURITYMGRSITE_DEFINED
_LPINTERNETSECURITYMGRSITE_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0131_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0131_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetSecurityMgrSite_INTERFACE_DEFINED__
__IInternetSecurityMgrSite_INTERFACE_DEFINED__ equ 1




externdef		IID_IInternetSecurityMgrSite:IID


IInternetSecurityMgrSiteVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface21@CT typedef proto \
		 pThis: ptr IInternetSecurityMgrSite,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface21@MP typedef ptr QueryInterface21@CT
	 QueryInterface QueryInterface21@MP ?

	    AddRef21@CT typedef proto \
		 pThis: ptr IInternetSecurityMgrSite

	    AddRef21@MP typedef ptr AddRef21@CT
		 AddRef AddRef21@MP ?

	   Release21@CT typedef proto \
		 pThis: ptr IInternetSecurityMgrSite

	   Release21@MP typedef ptr Release21@CT
		Release Release21@MP ?

	 GetWindow21@CT typedef proto \
		 pThis: ptr IInternetSecurityMgrSite,
		 phwnd: ptr HWND

	 GetWindow21@MP typedef ptr GetWindow21@CT
	      GetWindow GetWindow21@MP ?

    EnableModeless21@CT typedef proto \
		 pThis: ptr IInternetSecurityMgrSite,
	       fEnable: BOOL

    EnableModeless21@MP typedef ptr EnableModeless21@CT
	 EnableModeless EnableModeless21@MP ?

	END_INTERFACE

IInternetSecurityMgrSiteVtbl ENDS

LPIInternetSecurityMgrSiteVtbl typedef ptr IInternetSecurityMgrSiteVtbl
IInternetSecurityMgrSite STRUC
lpVtbl			LPIInternetSecurityMgrSiteVtbl ?
IInternetSecurityMgrSite ENDS






;HRESULT
IInternetSecurityMgrSite_GetWindow_Proxy proto _CType \
		 pThis: ptr IInternetSecurityMgrSite,
		 phwnd: ptr HWND



;void
IInternetSecurityMgrSite_GetWindow_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityMgrSite_EnableModeless_Proxy proto _CType \
		 pThis: ptr IInternetSecurityMgrSite,
	       fEnable: BOOL



;void
IInternetSecurityMgrSite_EnableModeless_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetSecurityMgrSite_INTERFACE_DEFINED__





endif
ifndef _LPINTERNETSECURITYMANANGER_DEFINED
_LPINTERNETSECURITYMANANGER_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0132_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0132_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetSecurityManager_INTERFACE_DEFINED__
__IInternetSecurityManager_INTERFACE_DEFINED__ equ 1



;; MapUrlToZone returns the zone index given a URL
MAX_SIZE_SECURITY_ID	equ 512 ;; bytes
;typedef enum __MIDL_IInternetSecurityManager_0001

PUAF_DEFAULT		equ 0
PUAF_NOUI		equ 0x1
PUAF_ISFILE		equ 0x2
PUAF_WARN_IF_DENIED	equ 0x4
PUAF_FORCEUI_FOREGROUND equ 0x8
PUAF_CHECK_TIFS		equ 0x10

;; pThis is the wrapper function that most clients will use.
;; It figures out the current Policy for the passed in Action,
;; and puts up UI if the current Policy indicates that the user
;; should be queried. It returns back the Policy which the caller
;; will use to determine if the action should be allowed
;; pThis is the wrapper function to conveniently read a custom policy.
;typedef enum __MIDL_IInternetSecurityManager_0002

SZM_CREATE		equ 0
SZM_DELETE		equ 0x1

;; SetZoneMapping
;;    lpszPattern: string denoting a URL pattern
;;	  Examples of valid patterns:
;;	      *:/;;.msn.com
;;	      http:/;;.sony.co.jp
;;	      *://et.msn.com
;;	      ftp://157.54.23.41/
;;	      https://localsvr
;;	      file:\localsvr\share
;;	      *://157.54.100-200.*
;;	  Examples of invalid patterns:
;;	      http:/;;.lcs.mit.edu
;;	      ftp:/;;
;;    dwFlags: SZM_FLAGS values

externdef		IID_IInternetSecurityManager:IID


IInternetSecurityManagerVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface22@MP typedef ptr QueryInterface22@CT
	 QueryInterface QueryInterface22@MP ?

	    AddRef22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager

	    AddRef22@MP typedef ptr AddRef22@CT
		 AddRef AddRef22@MP ?

	   Release22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager

	   Release22@MP typedef ptr Release22@CT
		Release Release22@MP ?

   SetSecuritySite22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
		 pSite: ptr IInternetSecurityMgrSite

   SetSecuritySite22@MP typedef ptr SetSecuritySite22@CT
	SetSecuritySite SetSecuritySite22@MP ?

   GetSecuritySite22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
		ppSite: ptr IInternetSecurityMgrSite

   GetSecuritySite22@MP typedef ptr GetSecuritySite22@CT
	GetSecuritySite GetSecuritySite22@MP ?

      MapUrlToZone22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	       pdwZone: LPDWORD,
	       dwFlags: DWORD

      MapUrlToZone22@MP typedef ptr MapUrlToZone22@CT
	   MapUrlToZone MapUrlToZone22@MP ?

     GetSecurityId22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	  pbSecurityId: LPBYTE,
	 pcbSecurityId: LPDWORD,
	    dwReserved: DWORD

     GetSecurityId22@MP typedef ptr GetSecurityId22@CT
	  GetSecurityId GetSecurityId22@MP ?

  ProcessUrlAction22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	       dwFlags: DWORD,
	    dwReserved: DWORD

  ProcessUrlAction22@MP typedef ptr ProcessUrlAction22@CT
       ProcessUrlAction ProcessUrlAction22@MP ?

 QueryCustomPolicy22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	    dwReserved: DWORD

 QueryCustomPolicy22@MP typedef ptr QueryCustomPolicy22@CT
      QueryCustomPolicy QueryCustomPolicy22@MP ?

    SetZoneMapping22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
		dwZone: DWORD,
	   lpszPattern: LPCWSTR,
	       dwFlags: DWORD

    SetZoneMapping22@MP typedef ptr SetZoneMapping22@CT
	 SetZoneMapping SetZoneMapping22@MP ?

   GetZoneMappings22@CT typedef proto \
		 pThis: ptr IInternetSecurityManager,
		dwZone: DWORD,
	  ppenumString: ptr IEnumString,
	       dwFlags: DWORD

   GetZoneMappings22@MP typedef ptr GetZoneMappings22@CT
	GetZoneMappings GetZoneMappings22@MP ?

	END_INTERFACE

IInternetSecurityManagerVtbl ENDS

LPIInternetSecurityManagerVtbl typedef ptr IInternetSecurityManagerVtbl
IInternetSecurityManager STRUC
lpVtbl			LPIInternetSecurityManagerVtbl ?
IInternetSecurityManager ENDS






;HRESULT
IInternetSecurityManager_SetSecuritySite_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
		 pSite: ptr IInternetSecurityMgrSite



;void
IInternetSecurityManager_SetSecuritySite_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_GetSecuritySite_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
		ppSite: ptr IInternetSecurityMgrSite



;void
IInternetSecurityManager_GetSecuritySite_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_MapUrlToZone_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	       pdwZone: LPDWORD,
	       dwFlags: DWORD



;void
IInternetSecurityManager_MapUrlToZone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_GetSecurityId_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	  pbSecurityId: LPBYTE,
	 pcbSecurityId: LPDWORD,
	    dwReserved: DWORD



;void
IInternetSecurityManager_GetSecurityId_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_ProcessUrlAction_Proxy proto _CType \
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
IInternetSecurityManager_ProcessUrlAction_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_QueryCustomPolicy_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
	       pwszUrl: LPCWSTR,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	    dwReserved: DWORD



;void
IInternetSecurityManager_QueryCustomPolicy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_SetZoneMapping_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
		dwZone: DWORD,
	   lpszPattern: LPCWSTR,
	       dwFlags: DWORD



;void
IInternetSecurityManager_SetZoneMapping_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetSecurityManager_GetZoneMappings_Proxy proto _CType \
		 pThis: ptr IInternetSecurityManager,
		dwZone: DWORD,
	  ppenumString: ptr IEnumString,
	       dwFlags: DWORD



;void
IInternetSecurityManager_GetZoneMappings_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetSecurityManager_INTERFACE_DEFINED__





endif
ifndef _LPINTERNETHOSTSECURITYMANANGER_DEFINED
_LPINTERNETHOSTSECURITYMANANGER_DEFINED equ 1
;;This is the interface MSHTML exposes to its clients
;;The clients need not pass in a URL to these functions
;;since MSHTML maintains the notion of the current URL


externdef		__MIDL_itf_urlmon_0133_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0133_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetHostSecurityManager_INTERFACE_DEFINED__
__IInternetHostSecurityManager_INTERFACE_DEFINED__ equ 1




externdef		IID_IInternetHostSecurityManager:IID


IInternetHostSecurityManagerVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface23@CT typedef proto \
		 pThis: ptr IInternetHostSecurityManager,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface23@MP typedef ptr QueryInterface23@CT
	 QueryInterface QueryInterface23@MP ?

	    AddRef23@CT typedef proto \
		 pThis: ptr IInternetHostSecurityManager

	    AddRef23@MP typedef ptr AddRef23@CT
		 AddRef AddRef23@MP ?

	   Release23@CT typedef proto \
		 pThis: ptr IInternetHostSecurityManager

	   Release23@MP typedef ptr Release23@CT
		Release Release23@MP ?

     GetSecurityId23@CT typedef proto \
		 pThis: ptr IInternetHostSecurityManager,
	  pbSecurityId: LPBYTE,
	 pcbSecurityId: LPDWORD,
	    dwReserved: DWORD

     GetSecurityId23@MP typedef ptr GetSecurityId23@CT
	  GetSecurityId GetSecurityId23@MP ?

  ProcessUrlAction23@CT typedef proto \
		 pThis: ptr IInternetHostSecurityManager,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	       dwFlags: DWORD,
	    dwReserved: DWORD

  ProcessUrlAction23@MP typedef ptr ProcessUrlAction23@CT
       ProcessUrlAction ProcessUrlAction23@MP ?

 QueryCustomPolicy23@CT typedef proto \
		 pThis: ptr IInternetHostSecurityManager,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	    dwReserved: DWORD

 QueryCustomPolicy23@MP typedef ptr QueryCustomPolicy23@CT
      QueryCustomPolicy QueryCustomPolicy23@MP ?

	END_INTERFACE

IInternetHostSecurityManagerVtbl ENDS

LPIInternetHostSecurityManagerVtbl typedef ptr IInternetHostSecurityManagerVtbl
IInternetHostSecurityManager STRUC
lpVtbl			LPIInternetHostSecurityManagerVtbl ?
IInternetHostSecurityManager ENDS






;HRESULT
IInternetHostSecurityManager_GetSecurityId_Proxy proto _CType \
		 pThis: ptr IInternetHostSecurityManager,
	  pbSecurityId: LPBYTE,
	 pcbSecurityId: LPDWORD,
	    dwReserved: DWORD



;void
IInternetHostSecurityManager_GetSecurityId_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetHostSecurityManager_ProcessUrlAction_Proxy proto _CType \
		 pThis: ptr IInternetHostSecurityManager,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	       dwFlags: DWORD,
	    dwReserved: DWORD



;void
IInternetHostSecurityManager_ProcessUrlAction_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetHostSecurityManager_QueryCustomPolicy_Proxy proto _CType \
		 pThis: ptr IInternetHostSecurityManager,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	      pContext: LPBYTE,
	     cbContext: DWORD,
	    dwReserved: DWORD



;void
IInternetHostSecurityManager_QueryCustomPolicy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetHostSecurityManager_INTERFACE_DEFINED__





endif

;; The zone manager maintains policies for a set of standard actions.
;; These actions are identified by integral values (called action indexes)
;; specified below.

;; Minimum legal value for an action
URLACTION_MIN		equ 0x00001000

URLACTION_DOWNLOAD_MIN	equ 0x00001000
URLACTION_DOWNLOAD_SIGNED_ACTIVEX equ 0x00001001
URLACTION_DOWNLOAD_UNSIGNED_ACTIVEX equ 0x00001004
URLACTION_DOWNLOAD_CURR_MAX equ 0x00001004
URLACTION_DOWNLOAD_MAX	equ 0x000011FF

URLACTION_ACTIVEX_MIN	equ 0x00001200
URLACTION_ACTIVEX_RUN	equ 0x00001200
URLACTION_ACTIVEX_OVERRIDE_OBJECT_SAFETY equ 0x00001201 ;; aggregate next four
URLACTION_ACTIVEX_OVERRIDE_DATA_SAFETY equ 0x00001202 ;;
URLACTION_ACTIVEX_OVERRIDE_SCRIPT_SAFETY equ 0x00001203 ;;
URLACTION_SCRIPT_OVERRIDE_SAFETY equ 0x00001401 ;;
URLACTION_ACTIVEX_CONFIRM_NOOBJECTSAFETY equ 0x00001204 ;;
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
URLACTION_HTML_SUBMIT_FORMS equ 0x00001601 ;; aggregate next two
URLACTION_HTML_SUBMIT_FORMS_FROM equ 0x00001602 ;;
URLACTION_HTML_SUBMIT_FORMS_TO equ 0x00001603 ;;
URLACTION_HTML_FONT_DOWNLOAD equ 0x00001604
URLACTION_HTML_JAVA_RUN equ 0x00001605 ;; derive from Java custom policy
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


;; The following Infodelivery actions should have no default policies
;; in the registry.  They assume that no default policy means fall
;; back to the global restriction.  If an admin sets a policy per
;; zone, then it overrides the global restriction.

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

;; For each action specified above the system maintains
;; a set of policies for the action.
;; The only policies supported currently are permissions (i.e. is something allowed)
;; and logging status.
;; IMPORTANT: If you are defining your own policies don't overload the meaning of the
;; loword of the policy. You can use the hiword to store any policy bits which are only
;; meaningful to your action.
;; For an example of how to do this look at the URLPOLICY_JAVA above

;; Permissions
URLPOLICY_ALLOW		equ 0x00
URLPOLICY_QUERY		equ 0x01
URLPOLICY_DISALLOW	equ 0x03

;; Notifications are not done when user already queried.
URLPOLICY_NOTIFY_ON_ALLOW equ 0x10
URLPOLICY_NOTIFY_ON_DISALLOW equ 0x20

;; Logging is done regardless of whether user was queried.
URLPOLICY_LOG_ON_ALLOW	equ 0x40
URLPOLICY_LOG_ON_DISALLOW equ 0x80

URLPOLICY_MASK_PERMISSIONS equ 0x0f
GetUrlPolicyPermissions macro dw
	exitm<(dw AND URLPOLICY_MASK_PERMISSIONS)>
	endm
SetUrlPolicyPermissions macro dw,dw2
	exitm<((dw) = ((dw) AND NOT (URLPOLICY_MASK_PERMISSIONS)) OR (dw2))>
	endm


;; The ordinal #'s that define the predefined zones internet explorer knows about.
;; When we support user-defined zones their zone numbers should be between
;; URLZONE_USER_MIN and URLZONE_USER_MAX
ifndef _LPINTERNETZONEMANAGER_DEFINED
_LPINTERNETZONEMANAGER_DEFINED equ 1


externdef		__MIDL_itf_urlmon_0134_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0134_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IInternetZoneManager_INTERFACE_DEFINED__
__IInternetZoneManager_INTERFACE_DEFINED__ equ 1



LPURLZONEMANAGER	typedef ptr IInternetZoneManager

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

;; Gets the zone attributes (information in registry other than actual security
;; policies associated with the zone).	Zone attributes are fixed as:
;; Sets the zone attributes (information in registry other than actual security
;; policies associated with the zone).	Zone attributes as above.
;; Returns S_OK or ??? if failed to write the zone attributes.
;; Registry Flags
;;
;; When reading, default behavior is
;; If HKLM allows override and HKCU value exists
;; Then use HKCU value
;; Else use HKLM value
;; When writing, default behavior is same as HKCU
;; If HKLM allows override
;; Then Write to HKCU
;; Else Fail
;;
URLZONEREG		typedef SDWORD
URLZONEREG_DEFAULT	equ 0
URLZONEREG_HKLM		equ URLZONEREG_DEFAULT + 1
URLZONEREG_HKCU		equ URLZONEREG_HKLM + 1

;; Gets a named custom policy associated with a zone;
;; e.g. the Java VM settings can be defined with a unique key such as 'Java'.
;; Custom policy support is intended to allow extensibility from the predefined
;; set of policies that IE4 has built in.
;;
;; pwszKey is the string name designating the custom policy.  Components are
;;   responsible for having unique names.
;; ppPolicy is the callee allocated buffer for the policy byte blob; caller is
;;   responsible for freeing this buffer eventually.
;; pcbPolicy is the size of the byte blob returned.
;; dwRegFlags determines how registry is accessed (see above).
;; Returns S_OK if key is found and buffer allocated; ??? if key is not found (no buffer alloced).
;; Sets a named custom policy associated with a zone;
;; e.g. the Java VM settings can be defined with a unique key such as 'Java'.
;; Custom policy support is intended to allow extensibility from the predefined
;; set of policies that IE4 has built in.
;;
;; pwszKey is the string name designating the custom policy.  Components are
;;   responsible for having unique names.
;; ppPolicy is the caller allocated buffer for the policy byte blob.
;; pcbPolicy is the size of the byte blob to be set.
;; dwRegFlags determines if HTCU or HKLM is set.
;; Returns S_OK or ??? if failed to write the zone custom policy.
;; Gets action policy associated with a zone, the builtin, fixed-length policies info.

;; dwAction is the action code for the action as defined above.
;; pPolicy is the caller allocated buffer for the policy data.
;; cbPolicy is the size of the caller allocated buffer.
;; dwRegFlags determines how registry is accessed (see above).
;; Returns S_OK if action is valid; ??? if action is not valid.

externdef		IID_IInternetZoneManager:IID


IInternetZoneManagerVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface24@MP typedef ptr QueryInterface24@CT
	 QueryInterface QueryInterface24@MP ?

	    AddRef24@CT typedef proto \
		 pThis: ptr IInternetZoneManager

	    AddRef24@MP typedef ptr AddRef24@CT
		 AddRef AddRef24@MP ?

	   Release24@CT typedef proto \
		 pThis: ptr IInternetZoneManager

	   Release24@MP typedef ptr Release24@CT
		Release Release24@MP ?

 GetZoneAttributes24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
       pZoneAttributes: ptr ZONEATTRIBUTES

 GetZoneAttributes24@MP typedef ptr GetZoneAttributes24@CT
      GetZoneAttributes GetZoneAttributes24@MP ?

 SetZoneAttributes24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
       pZoneAttributes: ptr ZONEATTRIBUTES

 SetZoneAttributes24@MP typedef ptr SetZoneAttributes24@CT
      SetZoneAttributes SetZoneAttributes24@MP ?

GetZoneCustomPolicy24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	    urlZoneReg: URLZONEREG

GetZoneCustomPolicy24@MP typedef ptr GetZoneCustomPolicy24@CT
    GetZoneCustomPolicy GetZoneCustomPolicy24@MP ?

SetZoneCustomPolicy24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	       guidKey: REFGUID,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG

SetZoneCustomPolicy24@MP typedef ptr SetZoneCustomPolicy24@CT
    SetZoneCustomPolicy SetZoneCustomPolicy24@MP ?

GetZoneActionPolicy24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG

GetZoneActionPolicy24@MP typedef ptr GetZoneActionPolicy24@CT
    GetZoneActionPolicy GetZoneActionPolicy24@MP ?

SetZoneActionPolicy24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG

SetZoneActionPolicy24@MP typedef ptr SetZoneActionPolicy24@CT
    SetZoneActionPolicy SetZoneActionPolicy24@MP ?

      PromptAction24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
	      dwAction: DWORD,
	    hwndParent: HWND,
	       pwszUrl: LPCWSTR,
	      pwszText: LPCWSTR,
	 dwPromptFlags: DWORD

      PromptAction24@MP typedef ptr PromptAction24@CT
	   PromptAction PromptAction24@MP ?

	 LogAction24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
	      dwAction: DWORD,
	       pwszUrl: LPCWSTR,
	      pwszText: LPCWSTR,
	    dwLogFlags: DWORD

	 LogAction24@MP typedef ptr LogAction24@CT
	      LogAction LogAction24@MP ?

CreateZoneEnumerator24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
	       pdwEnum: LPDWORD,
	      pdwCount: LPDWORD,
	       dwFlags: DWORD

CreateZoneEnumerator24@MP typedef ptr CreateZoneEnumerator24@CT
   CreateZoneEnumerator CreateZoneEnumerator24@MP ?

	 GetZoneAt24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwEnum: DWORD,
	       dwIndex: DWORD,
	       pdwZone: LPDWORD

	 GetZoneAt24@MP typedef ptr GetZoneAt24@CT
	      GetZoneAt GetZoneAt24@MP ?

DestroyZoneEnumerator24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
		dwEnum: DWORD

DestroyZoneEnumerator24@MP typedef ptr DestroyZoneEnumerator24@CT
  DestroyZoneEnumerator DestroyZoneEnumerator24@MP ?

CopyTemplatePoliciesToZone24@CT typedef proto \
		 pThis: ptr IInternetZoneManager,
	    dwTemplate: DWORD,
		dwZone: DWORD,
	    dwReserved: DWORD

CopyTemplatePoliciesToZone24@MP typedef ptr CopyTemplatePoliciesToZone24@CT
CopyTemplatePoliciesToZone CopyTemplatePoliciesToZone24@MP ?

	END_INTERFACE

IInternetZoneManagerVtbl ENDS

LPIInternetZoneManagerVtbl typedef ptr IInternetZoneManagerVtbl
IInternetZoneManager	STRUC
lpVtbl			LPIInternetZoneManagerVtbl ?
IInternetZoneManager	ENDS






;HRESULT
IInternetZoneManager_GetZoneAttributes_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
       pZoneAttributes: ptr ZONEATTRIBUTES



;void
IInternetZoneManager_GetZoneAttributes_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_SetZoneAttributes_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
       pZoneAttributes: ptr ZONEATTRIBUTES



;void
IInternetZoneManager_SetZoneAttributes_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_GetZoneCustomPolicy_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	       guidKey: REFGUID,
	      ppPolicy: LPBYTE,
	     pcbPolicy: LPDWORD,
	    urlZoneReg: URLZONEREG



;void
IInternetZoneManager_GetZoneCustomPolicy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_SetZoneCustomPolicy_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	       guidKey: REFGUID,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG



;void
IInternetZoneManager_SetZoneCustomPolicy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_GetZoneActionPolicy_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG



;void
IInternetZoneManager_GetZoneActionPolicy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_SetZoneActionPolicy_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwZone: DWORD,
	      dwAction: DWORD,
	       pPolicy: LPBYTE,
	      cbPolicy: DWORD,
	    urlZoneReg: URLZONEREG



;void
IInternetZoneManager_SetZoneActionPolicy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_PromptAction_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
	      dwAction: DWORD,
	    hwndParent: HWND,
	       pwszUrl: LPCWSTR,
	      pwszText: LPCWSTR,
	 dwPromptFlags: DWORD



;void
IInternetZoneManager_PromptAction_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_LogAction_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
	      dwAction: DWORD,
	       pwszUrl: LPCWSTR,
	      pwszText: LPCWSTR,
	    dwLogFlags: DWORD



;void
IInternetZoneManager_LogAction_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_CreateZoneEnumerator_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
	       pdwEnum: LPDWORD,
	      pdwCount: LPDWORD,
	       dwFlags: DWORD



;void
IInternetZoneManager_CreateZoneEnumerator_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_GetZoneAt_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwEnum: DWORD,
	       dwIndex: DWORD,
	       pdwZone: LPDWORD



;void
IInternetZoneManager_GetZoneAt_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_DestroyZoneEnumerator_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
		dwEnum: DWORD



;void
IInternetZoneManager_DestroyZoneEnumerator_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IInternetZoneManager_CopyTemplatePoliciesToZone_Proxy proto _CType \
		 pThis: ptr IInternetZoneManager,
	    dwTemplate: DWORD,
		dwZone: DWORD,
	    dwReserved: DWORD



;void
IInternetZoneManager_CopyTemplatePoliciesToZone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IInternetZoneManager_INTERFACE_DEFINED__





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

ISoftDistExtVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface25@CT typedef proto \
		 pThis: ptr ISoftDistExt,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface25@MP typedef ptr QueryInterface25@CT
	 QueryInterface QueryInterface25@MP ?

	    AddRef25@CT typedef proto \
		 pThis: ptr ISoftDistExt

	    AddRef25@MP typedef ptr AddRef25@CT
		 AddRef AddRef25@MP ?

	   Release25@CT typedef proto \
		 pThis: ptr ISoftDistExt

	   Release25@MP typedef ptr Release25@CT
		Release Release25@MP ?

   ProcessSoftDist25@CT typedef proto \
		 pThis: ptr ISoftDistExt,
	      szCDFURL: LPCWSTR,
      pSoftDistElement: ptr IXMLElement,
		 lpsdi: LPSOFTDISTINFO

   ProcessSoftDist25@MP typedef ptr ProcessSoftDist25@CT
	ProcessSoftDist ProcessSoftDist25@MP ?

  GetFirstCodeBase25@CT typedef proto \
		 pThis: ptr ISoftDistExt,
	    szCodeBase: ptr LPWSTR,
	     dwMaxSize: LPDWORD

  GetFirstCodeBase25@MP typedef ptr GetFirstCodeBase25@CT
       GetFirstCodeBase GetFirstCodeBase25@MP ?

   GetNextCodeBase25@CT typedef proto \
		 pThis: ptr ISoftDistExt,
	    szCodeBase: ptr LPWSTR,
	     dwMaxSize: LPDWORD

   GetNextCodeBase25@MP typedef ptr GetNextCodeBase25@CT
	GetNextCodeBase GetNextCodeBase25@MP ?

AsyncInstallDistributionUnit25@CT typedef proto \
		 pThis: ptr ISoftDistExt,
		   pbc: ptr IBindCtx,
	    pvReserved: LPVOID,
		 flags: DWORD,
		 lpcbh: LPCODEBASEHOLD

AsyncInstallDistributionUnit25@MP typedef ptr AsyncInstallDistributionUnit25@CT
AsyncInstallDistributionUnit AsyncInstallDistributionUnit25@MP ?

	END_INTERFACE

ISoftDistExtVtbl	ENDS

LPISoftDistExtVtbl	typedef ptr ISoftDistExtVtbl
ISoftDistExt		STRUC
lpVtbl			LPISoftDistExtVtbl ?
ISoftDistExt		ENDS






;HRESULT
ISoftDistExt_ProcessSoftDist_Proxy proto _CType \
		 pThis: ptr ISoftDistExt,
	      szCDFURL: LPCWSTR,
      pSoftDistElement: ptr IXMLElement,
		 lpsdi: LPSOFTDISTINFO



;void
ISoftDistExt_ProcessSoftDist_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
ISoftDistExt_GetFirstCodeBase_Proxy proto _CType \
		 pThis: ptr ISoftDistExt,
	    szCodeBase: ptr LPWSTR,
	     dwMaxSize: LPDWORD



;void
ISoftDistExt_GetFirstCodeBase_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
ISoftDistExt_GetNextCodeBase_Proxy proto _CType \
		 pThis: ptr ISoftDistExt,
	    szCodeBase: ptr LPWSTR,
	     dwMaxSize: LPDWORD



;void
ISoftDistExt_GetNextCodeBase_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
ISoftDistExt_AsyncInstallDistributionUnit_Proxy proto _CType \
		 pThis: ptr ISoftDistExt,
		   pbc: ptr IBindCtx,
	    pvReserved: LPVOID,
		 flags: DWORD,
		 lpcbh: LPCODEBASEHOLD



;void
ISoftDistExt_AsyncInstallDistributionUnit_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __ISoftDistExt_INTERFACE_DEFINED__





;STDAPI
GetSoftwareUpdateInfo proto _CType \
	    szDistUnit: LPCWSTR,
		  psdi: LPSOFTDISTINFO

;STDAPI
SetSoftwareUpdateAdvertisementState proto _CType \
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



LPDATAFILTER		typedef ptr IDataFilter


externdef		IID_IDataFilter:IID


IDataFilterVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface26@CT typedef proto \
		 pThis: ptr IDataFilter,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface26@MP typedef ptr QueryInterface26@CT
	 QueryInterface QueryInterface26@MP ?

	    AddRef26@CT typedef proto \
		 pThis: ptr IDataFilter

	    AddRef26@MP typedef ptr AddRef26@CT
		 AddRef AddRef26@MP ?

	   Release26@CT typedef proto \
		 pThis: ptr IDataFilter

	   Release26@MP typedef ptr Release26@CT
		Release Release26@MP ?

	  DoEncode26@CT typedef proto \
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

	  DoEncode26@MP typedef ptr DoEncode26@CT
	       DoEncode DoEncode26@MP ?

	  DoDecode26@CT typedef proto \
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

	  DoDecode26@MP typedef ptr DoDecode26@CT
	       DoDecode DoDecode26@MP ?

  SetEncodingLevel26@CT typedef proto \
		 pThis: ptr IDataFilter,
	    dwEncLevel: DWORD

  SetEncodingLevel26@MP typedef ptr SetEncodingLevel26@CT
       SetEncodingLevel SetEncodingLevel26@MP ?

	END_INTERFACE

IDataFilterVtbl		ENDS

LPIDataFilterVtbl	typedef ptr IDataFilterVtbl
IDataFilter		STRUC
lpVtbl			LPIDataFilterVtbl ?
IDataFilter		ENDS






;HRESULT
IDataFilter_DoEncode_Proxy proto _CType \
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
IDataFilter_DoEncode_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IDataFilter_DoDecode_Proxy proto _CType \
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
IDataFilter_DoDecode_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IDataFilter_SetEncodingLevel_Proxy proto _CType \
		 pThis: ptr IDataFilter,
	    dwEncLevel: DWORD



;void
IDataFilter_SetEncodingLevel_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IDataFilter_INTERFACE_DEFINED__

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



LPENCODINGFILTERFACTORY typedef ptr IEncodingFilterFactory

DATAINFO		STRUC
ulTotalSize		dd ?
ulavrPacketSize		dd ?
ulConnectSpeed		dd ?
ulProcessorSpeed	dd ?
DATAINFO		ENDS


externdef		IID_IEncodingFilterFactory:IID


IEncodingFilterFactoryVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface27@CT typedef proto \
		 pThis: ptr IEncodingFilterFactory,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface27@MP typedef ptr QueryInterface27@CT
	 QueryInterface QueryInterface27@MP ?

	    AddRef27@CT typedef proto \
		 pThis: ptr IEncodingFilterFactory

	    AddRef27@MP typedef ptr AddRef27@CT
		 AddRef AddRef27@MP ?

	   Release27@CT typedef proto \
		 pThis: ptr IEncodingFilterFactory

	   Release27@MP typedef ptr Release27@CT
		Release Release27@MP ?

    FindBestFilter27@CT typedef proto \
		 pThis: ptr IEncodingFilterFactory,
	     pwzCodeIn: LPCWSTR,
	    pwzCodeOut: LPCWSTR,
		  info: DATAINFO,
		  ppDF: ptr IDataFilter

    FindBestFilter27@MP typedef ptr FindBestFilter27@CT
	 FindBestFilter FindBestFilter27@MP ?

  GetDefaultFilter27@CT typedef proto \
		 pThis: ptr IEncodingFilterFactory,
	     pwzCodeIn: LPCWSTR,
	    pwzCodeOut: LPCWSTR,
		  ppDF: ptr IDataFilter

  GetDefaultFilter27@MP typedef ptr GetDefaultFilter27@CT
       GetDefaultFilter GetDefaultFilter27@MP ?

	END_INTERFACE

IEncodingFilterFactoryVtbl ENDS

LPIEncodingFilterFactoryVtbl typedef ptr IEncodingFilterFactoryVtbl
IEncodingFilterFactory	STRUC
lpVtbl			LPIEncodingFilterFactoryVtbl ?
IEncodingFilterFactory	ENDS






;HRESULT
IEncodingFilterFactory_FindBestFilter_Proxy proto _CType \
		 pThis: ptr IEncodingFilterFactory,
	     pwzCodeIn: LPCWSTR,
	    pwzCodeOut: LPCWSTR,
		  info: DATAINFO,
		  ppDF: ptr IDataFilter



;void
IEncodingFilterFactory_FindBestFilter_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



;HRESULT
IEncodingFilterFactory_GetDefaultFilter_Proxy proto _CType \
		 pThis: ptr IEncodingFilterFactory,
	     pwzCodeIn: LPCWSTR,
	    pwzCodeOut: LPCWSTR,
		  ppDF: ptr IDataFilter



;void
IEncodingFilterFactory_GetDefaultFilter_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD




endif	;; __IEncodingFilterFactory_INTERFACE_DEFINED__





endif
ifndef _HITLOGGING_DEFINED
_HITLOGGING_DEFINED equ 1
;; Logging-specific apis
;BOOL
IsLoggingEnabledA proto _CType \
		pszUrl: LPCTSTR
IsLoggingEnalbedW proto _CType \
	       pwszUrl: LPCWSTR
ifdef _UNICODE
IsLoggingEnabled	equ <IsLoggingEnabledW>
else
IsLoggingEnabled	equ <IsLoggingEnabledA>
endif ;; NOT UNICODE
HIT_LOGGING_INFO	STRUC
dwStructSize		dd ?
lpszLoggedUrlName	LPSTR ?
StartTime		SYSTEMTIME <>
EndTime			SYSTEMTIME <>
lpszExtendedInfo	LPSTR ?
HIT_LOGGING_INFO	ENDS
LPHIT_LOGGING_INFO	typedef ptr HIT_LOGGING_INFO

;BOOL
WriteHitLogging proto _CType \
	 lpLogginginfo: LPHIT_LOGGING_INFO

endif


externdef		__MIDL_itf_urlmon_0138_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_urlmon_0138_v0_0_s_ifspec:RPC_IF_HANDLE

;; Additional Prototypes for ALL interfaces

;HRESULT
IBinding_GetBindResult_Proxy proto _CType \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	   pdwReserved: LPDWORD



;HRESULT
IBinding_GetBindResult_Stub proto _CType \
		 pThis: ptr IBinding,
	pclsidProtocol: ptr CLSID,
	     pdwResult: LPDWORD,
	     pszResult: ptr LPOLESTR,
	    dwReserved: DWORD


;HRESULT
IBindStatusCallback_GetBindInfo_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr BINDINFO



;HRESULT
IBindStatusCallback_GetBindInfo_Stub proto _CType \
		 pThis: ptr IBindStatusCallback,
	      grfBINDF: LPDWORD,
	     pbindinfo: ptr RemBINDINFO,
	       pstgmed: ptr RemSTGMEDIUM


;HRESULT
IBindStatusCallback_OnDataAvailable_Proxy proto _CType \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr FORMATETC,
	       pstgmed: ptr STGMEDIUM



;HRESULT
IBindStatusCallback_OnDataAvailable_Stub proto _CType \
		 pThis: ptr IBindStatusCallback,
	       grfBSCF: DWORD,
		dwSize: DWORD,
	    pformatetc: ptr RemFORMATETC,
	       pstgmed: ptr RemSTGMEDIUM


;HRESULT
IWinInetInfo_QueryOption_Proxy proto _CType \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD



;HRESULT
IWinInetInfo_QueryOption_Stub proto _CType \
		 pThis: ptr IWinInetInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD


;HRESULT
IWinInetHttpInfo_QueryInfo_Proxy proto _CType \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPVOID,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD



;HRESULT
IWinInetHttpInfo_QueryInfo_Stub proto _CType \
		 pThis: ptr IWinInetHttpInfo,
	      dwOption: DWORD,
	       pBuffer: LPBYTE,
		pcbBuf: LPDWORD,
	      pdwFlags: LPDWORD,
	   pdwReserved: LPDWORD


;HRESULT
IBindHost_MonikerBindToStorage_Proxy proto _CType \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: PVOID



;HRESULT
IBindHost_MonikerBindToStorage_Stub proto _CType \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown


;HRESULT
IBindHost_MonikerBindToObject_Proxy proto _CType \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: PVOID



;HRESULT
IBindHost_MonikerBindToObject_Stub proto _CType \
		 pThis: ptr IBindHost,
		   pMk: ptr IMoniker,
		   pBC: ptr IBindCtx,
		  pBSC: ptr IBindStatusCallback,
		  riid: REFIID,
		ppvObj: ptr IUnknown




;; end of Additional Prototypes
.list
endif
