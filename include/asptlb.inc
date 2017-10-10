ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
endif
include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif ;; __RPCNDR_H_VERSION__

ifndef __asptlb_h__
__asptlb_h__ equ <>
.xlist

;; Forward Declarations

ifndef __IStringList_FWD_DEFINED__
__IStringList_FWD_DEFINED__ equ 1
endif	;; __IStringList_FWD_DEFINED__


ifndef __IRequestDictionary_FWD_DEFINED__
__IRequestDictionary_FWD_DEFINED__ equ 1
endif	;; __IRequestDictionary_FWD_DEFINED__


ifndef __IRequest_FWD_DEFINED__
__IRequest_FWD_DEFINED__ equ 1
endif	;; __IRequest_FWD_DEFINED__


ifndef __Request_FWD_DEFINED__
__Request_FWD_DEFINED__ equ 1
Request			typedef Request
endif	;; __Request_FWD_DEFINED__


ifndef __IReadCookie_FWD_DEFINED__
__IReadCookie_FWD_DEFINED__ equ 1
endif	;; __IReadCookie_FWD_DEFINED__


ifndef __IWriteCookie_FWD_DEFINED__
__IWriteCookie_FWD_DEFINED__ equ 1
endif	;; __IWriteCookie_FWD_DEFINED__


ifndef __IResponse_FWD_DEFINED__
__IResponse_FWD_DEFINED__ equ 1
endif	;; __IResponse_FWD_DEFINED__


ifndef __Response_FWD_DEFINED__
__Response_FWD_DEFINED__ equ 1
Response		typedef Response
endif	;; __Response_FWD_DEFINED__


ifndef __IVariantDictionary_FWD_DEFINED__
__IVariantDictionary_FWD_DEFINED__ equ 1
endif	;; __IVariantDictionary_FWD_DEFINED__


ifndef __ISessionObject_FWD_DEFINED__
__ISessionObject_FWD_DEFINED__ equ 1
endif	;; __ISessionObject_FWD_DEFINED__


ifndef __Session_FWD_DEFINED__
__Session_FWD_DEFINED__ equ 1
Session			typedef Session
endif	;; __Session_FWD_DEFINED__


ifndef __IApplicationObject_FWD_DEFINED__
__IApplicationObject_FWD_DEFINED__ equ 1
endif	;; __IApplicationObject_FWD_DEFINED__


ifndef __Application_FWD_DEFINED__
__Application_FWD_DEFINED__ equ 1
Application		typedef Application
endif	;; __Application_FWD_DEFINED__


ifndef __IASPError_FWD_DEFINED__
__IASPError_FWD_DEFINED__ equ 1
endif	;; __IASPError_FWD_DEFINED__


ifndef __IServer_FWD_DEFINED__
__IServer_FWD_DEFINED__ equ 1
endif	;; __IServer_FWD_DEFINED__


ifndef __Server_FWD_DEFINED__
__Server_FWD_DEFINED__ equ 1
Server			typedef Server
endif	;; __Server_FWD_DEFINED__


ifndef __IScriptingContext_FWD_DEFINED__
__IScriptingContext_FWD_DEFINED__ equ 1
endif	;; __IScriptingContext_FWD_DEFINED__


ifndef __ScriptingContext_FWD_DEFINED__
__ScriptingContext_FWD_DEFINED__ equ 1
ScriptingContext	typedef ScriptingContext
endif	;; __ScriptingContext_FWD_DEFINED__

ifndef __ASPTypeLibrary_LIBRARY_DEFINED__
__ASPTypeLibrary_LIBRARY_DEFINED__ equ 1

;; library ASPTypeLibrary


DEFINE_GUID(LIBID_ASPTypeLibrary,0xD97A6DA0,0xA85C,0x11cf,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

ifndef __IStringList_INTERFACE_DEFINED__
__IStringList_INTERFACE_DEFINED__ equ 1

;; interface IStringList


DEFINE_GUID(IID_IStringList,0xD97A6DA0,0xA85D,0x11cf,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);


IStringListVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface60@CT typedef proto \
		 _This: ptr IStringList,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface60@MP typedef ptr QueryInterface60@CT
	 QueryInterface QueryInterface60@MP ?

	    AddRef60@CT typedef proto \
		 _This: ptr IStringList

	    AddRef60@MP typedef ptr AddRef60@CT
		 AddRef AddRef60@MP ?

	   Release60@CT typedef proto \
		 _This: ptr IStringList

	   Release60@MP typedef ptr Release60@CT
		Release Release60@MP ?

  GetTypeInfoCount60@CT typedef proto \
		 _This: ptr IStringList,
	       pctinfo: ptr UINT

  GetTypeInfoCount60@MP typedef ptr GetTypeInfoCount60@CT
       GetTypeInfoCount GetTypeInfoCount60@MP ?

       GetTypeInfo60@CT typedef proto \
		 _This: ptr IStringList,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo60@MP typedef ptr GetTypeInfo60@CT
	    GetTypeInfo GetTypeInfo60@MP ?

     GetIDsOfNames60@CT typedef proto \
		 _This: ptr IStringList,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames60@MP typedef ptr GetIDsOfNames60@CT
	  GetIDsOfNames GetIDsOfNames60@MP ?

	   _Invoke60@CT typedef proto \
		 _This: ptr IStringList,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke60@MP typedef ptr _Invoke60@CT
		_Invoke _Invoke60@MP ?

	  get_Item60@CT typedef proto \
		 _This: ptr IStringList,
		     i: VARIANT,
	pVariantReturn: ptr VARIANT

	  get_Item60@MP typedef ptr get_Item60@CT
	       get_Item get_Item60@MP ?

	 get_Count60@CT typedef proto \
		 _This: ptr IStringList,
	       cStrRet: ptr SINT

	 get_Count60@MP typedef ptr get_Count60@CT
	      get_Count get_Count60@MP ?

      get__NewEnum60@CT typedef proto \
		 _This: ptr IStringList,
	  ppEnumReturn: ptr IUnknown

      get__NewEnum60@MP typedef ptr get__NewEnum60@CT
	   get__NewEnum get__NewEnum60@MP ?

	END_INTERFACE

IStringListVtbl		ENDS

LPIStringListVtbl	typedef ptr IStringListVtbl
IStringList		STRUC
lpVtbl			LPIStringListVtbl ?
IStringList		ENDS

endif	;; __IStringList_INTERFACE_DEFINED__

ifndef __IRequestDictionary_INTERFACE_DEFINED__
__IRequestDictionary_INTERFACE_DEFINED__ equ 1

;; interface IRequestDictionary

DEFINE_GUID(IID_IRequestDictionary,0xD97A6DA0,0xA85F,0x11df,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

IRequestDictionaryVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface61@CT typedef proto \
		 _This: ptr IRequestDictionary,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface61@MP typedef ptr QueryInterface61@CT
	 QueryInterface QueryInterface61@MP ?

	    AddRef61@CT typedef proto \
		 _This: ptr IRequestDictionary

	    AddRef61@MP typedef ptr AddRef61@CT
		 AddRef AddRef61@MP ?

	   Release61@CT typedef proto \
		 _This: ptr IRequestDictionary

	   Release61@MP typedef ptr Release61@CT
		Release Release61@MP ?

  GetTypeInfoCount61@CT typedef proto \
		 _This: ptr IRequestDictionary,
	       pctinfo: ptr UINT

  GetTypeInfoCount61@MP typedef ptr GetTypeInfoCount61@CT
       GetTypeInfoCount GetTypeInfoCount61@MP ?

       GetTypeInfo61@CT typedef proto \
		 _This: ptr IRequestDictionary,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo61@MP typedef ptr GetTypeInfo61@CT
	    GetTypeInfo GetTypeInfo61@MP ?

     GetIDsOfNames61@CT typedef proto \
		 _This: ptr IRequestDictionary,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames61@MP typedef ptr GetIDsOfNames61@CT
	  GetIDsOfNames GetIDsOfNames61@MP ?

	   _Invoke61@CT typedef proto \
		 _This: ptr IRequestDictionary,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke61@MP typedef ptr _Invoke61@CT
		_Invoke _Invoke61@MP ?

	  get_Item61@CT typedef proto \
		 _This: ptr IRequestDictionary,
		   Var: VARIANT,
	pVariantReturn: ptr VARIANT

	  get_Item61@MP typedef ptr get_Item61@CT
	       get_Item get_Item61@MP ?

      get__NewEnum61@CT typedef proto \
		 _This: ptr IRequestDictionary,
	  ppEnumReturn: ptr IUnknown

      get__NewEnum61@MP typedef ptr get__NewEnum61@CT
	   get__NewEnum get__NewEnum61@MP ?

	 get_Count61@CT typedef proto \
		 _This: ptr IRequestDictionary,
	       cStrRet: ptr SINT

	 get_Count61@MP typedef ptr get_Count61@CT
	      get_Count get_Count61@MP ?

	   get_Key61@CT typedef proto \
		 _This: ptr IRequestDictionary,
		VarKey: VARIANT,
		  pvar: ptr VARIANT

	   get_Key61@MP typedef ptr get_Key61@CT
		get_Key get_Key61@MP ?

	END_INTERFACE

IRequestDictionaryVtbl	ENDS

LPIRequestDictionaryVtbl typedef ptr IRequestDictionaryVtbl
IRequestDictionary	STRUC
lpVtbl			LPIRequestDictionaryVtbl ?
IRequestDictionary	ENDS

endif	;; __IRequestDictionary_INTERFACE_DEFINED__

ifndef __IRequest_INTERFACE_DEFINED__
__IRequest_INTERFACE_DEFINED__ equ 1

;; interface IRequest


DEFINE_GUID(IID_IRequest,0xD97A6DA0,0xA861,0x11cf,0x93,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);


IRequestVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface62@CT typedef proto \
		 _This: ptr IRequest,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface62@MP typedef ptr QueryInterface62@CT
	 QueryInterface QueryInterface62@MP ?

	    AddRef62@CT typedef proto \
		 _This: ptr IRequest

	    AddRef62@MP typedef ptr AddRef62@CT
		 AddRef AddRef62@MP ?

	   Release62@CT typedef proto \
		 _This: ptr IRequest

	   Release62@MP typedef ptr Release62@CT
		Release Release62@MP ?

  GetTypeInfoCount62@CT typedef proto \
		 _This: ptr IRequest,
	       pctinfo: ptr UINT

  GetTypeInfoCount62@MP typedef ptr GetTypeInfoCount62@CT
       GetTypeInfoCount GetTypeInfoCount62@MP ?

       GetTypeInfo62@CT typedef proto \
		 _This: ptr IRequest,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo62@MP typedef ptr GetTypeInfo62@CT
	    GetTypeInfo GetTypeInfo62@MP ?

     GetIDsOfNames62@CT typedef proto \
		 _This: ptr IRequest,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames62@MP typedef ptr GetIDsOfNames62@CT
	  GetIDsOfNames GetIDsOfNames62@MP ?

	   _Invoke62@CT typedef proto \
		 _This: ptr IRequest,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke62@MP typedef ptr _Invoke62@CT
		_Invoke _Invoke62@MP ?

	  get_Item62@CT typedef proto \
		 _This: ptr IRequest,
	       bstrVar: BSTR,
	   ppObjReturn: ptr IDispatch

	  get_Item62@MP typedef ptr get_Item62@CT
	       get_Item get_Item62@MP ?

   get_QueryString62@CT typedef proto \
		 _This: ptr IRequest,
	  ppDictReturn: ptr IRequestDictionary

   get_QueryString62@MP typedef ptr get_QueryString62@CT
	get_QueryString get_QueryString62@MP ?

	  get_Form62@CT typedef proto \
		 _This: ptr IRequest,
	  ppDictReturn: ptr IRequestDictionary

	  get_Form62@MP typedef ptr get_Form62@CT
	       get_Form get_Form62@MP ?

	  get_Body62@CT typedef proto \
		 _This: ptr IRequest,
	  ppDictReturn: ptr IRequestDictionary

	  get_Body62@MP typedef ptr get_Body62@CT
	       get_Body get_Body62@MP ?

get_ServerVariables62@CT typedef proto \
		 _This: ptr IRequest,
	  ppDictReturn: ptr IRequestDictionary

get_ServerVariables62@MP typedef ptr get_ServerVariables62@CT
    get_ServerVariables get_ServerVariables62@MP ?

get_ClientCertificate62@CT typedef proto \
		 _This: ptr IRequest,
	  ppDictReturn: ptr IRequestDictionary

get_ClientCertificate62@MP typedef ptr get_ClientCertificate62@CT
  get_ClientCertificate get_ClientCertificate62@MP ?

       get_Cookies62@CT typedef proto \
		 _This: ptr IRequest,
	  ppDictReturn: ptr IRequestDictionary

       get_Cookies62@MP typedef ptr get_Cookies62@CT
	    get_Cookies get_Cookies62@MP ?

    get_TotalBytes62@CT typedef proto \
		 _This: ptr IRequest,
	      pcbTotal: ptr long

    get_TotalBytes62@MP typedef ptr get_TotalBytes62@CT
	 get_TotalBytes get_TotalBytes62@MP ?

	BinaryRead62@CT typedef proto \
		 _This: ptr IRequest,
       pvarCountToRead: ptr VARIANT,
	    pvarReturn: ptr VARIANT

	BinaryRead62@MP typedef ptr BinaryRead62@CT
	     BinaryRead BinaryRead62@MP ?

	END_INTERFACE

IRequestVtbl		ENDS

LPIRequestVtbl		typedef ptr IRequestVtbl
IRequest		STRUC
lpVtbl			LPIRequestVtbl ?
IRequest		ENDS

endif	;; __IRequest_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Request,0x920c25d0,0x25d9,0x11d0,0xa5,0x5f,0x00,0xa0,0xc9,0x0c,0x20,0x91);

ifndef __IReadCookie_INTERFACE_DEFINED__
__IReadCookie_INTERFACE_DEFINED__ equ 1

;; interface IReadCookie


DEFINE_GUID(IID_IReadCookie,0x71EAF260,0x0CE0,0x11D0,0xA5,0x3E,0x00,0xA0,0xC9,0x0C,0x20,0x91);


IReadCookieVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface63@CT typedef proto \
		 _This: ptr IReadCookie,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface63@MP typedef ptr QueryInterface63@CT
	 QueryInterface QueryInterface63@MP ?

	    AddRef63@CT typedef proto \
		 _This: ptr IReadCookie

	    AddRef63@MP typedef ptr AddRef63@CT
		 AddRef AddRef63@MP ?

	   Release63@CT typedef proto \
		 _This: ptr IReadCookie

	   Release63@MP typedef ptr Release63@CT
		Release Release63@MP ?

  GetTypeInfoCount63@CT typedef proto \
		 _This: ptr IReadCookie,
	       pctinfo: ptr UINT

  GetTypeInfoCount63@MP typedef ptr GetTypeInfoCount63@CT
       GetTypeInfoCount GetTypeInfoCount63@MP ?

       GetTypeInfo63@CT typedef proto \
		 _This: ptr IReadCookie,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo63@MP typedef ptr GetTypeInfo63@CT
	    GetTypeInfo GetTypeInfo63@MP ?

     GetIDsOfNames63@CT typedef proto \
		 _This: ptr IReadCookie,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames63@MP typedef ptr GetIDsOfNames63@CT
	  GetIDsOfNames GetIDsOfNames63@MP ?

	   _Invoke63@CT typedef proto \
		 _This: ptr IReadCookie,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke63@MP typedef ptr _Invoke63@CT
		_Invoke _Invoke63@MP ?

	  get_Item63@CT typedef proto \
		 _This: ptr IReadCookie,
		   Var: VARIANT,
	pVariantReturn: ptr VARIANT

	  get_Item63@MP typedef ptr get_Item63@CT
	       get_Item get_Item63@MP ?

       get_HasKeys63@CT typedef proto \
		 _This: ptr IReadCookie,
	     pfHasKeys: ptr VARIANT_BOOL

       get_HasKeys63@MP typedef ptr get_HasKeys63@CT
	    get_HasKeys get_HasKeys63@MP ?

      get__NewEnum63@CT typedef proto \
		 _This: ptr IReadCookie,
	  ppEnumReturn: ptr IUnknown

      get__NewEnum63@MP typedef ptr get__NewEnum63@CT
	   get__NewEnum get__NewEnum63@MP ?

	 get_Count63@CT typedef proto \
		 _This: ptr IReadCookie,
	       cStrRet: ptr SINT

	 get_Count63@MP typedef ptr get_Count63@CT
	      get_Count get_Count63@MP ?

	   get_Key63@CT typedef proto \
		 _This: ptr IReadCookie,
		VarKey: VARIANT,
		  pvar: ptr VARIANT

	   get_Key63@MP typedef ptr get_Key63@CT
		get_Key get_Key63@MP ?

	END_INTERFACE

IReadCookieVtbl		ENDS

LPIReadCookieVtbl	typedef ptr IReadCookieVtbl
IReadCookie		STRUC
lpVtbl			LPIReadCookieVtbl ?
IReadCookie		ENDS

endif	;; __IReadCookie_INTERFACE_DEFINED__

ifndef __IWriteCookie_INTERFACE_DEFINED__
__IWriteCookie_INTERFACE_DEFINED__ equ 1

;; interface IWriteCookie


DEFINE_GUID(IID_IWriteCookie,0xD97A6DA0,0xA862,0x11cf,0x84,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);


IWriteCookieVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface64@CT typedef proto \
		 _This: ptr IWriteCookie,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface64@MP typedef ptr QueryInterface64@CT
	 QueryInterface QueryInterface64@MP ?

	    AddRef64@CT typedef proto \
		 _This: ptr IWriteCookie

	    AddRef64@MP typedef ptr AddRef64@CT
		 AddRef AddRef64@MP ?

	   Release64@CT typedef proto \
		 _This: ptr IWriteCookie

	   Release64@MP typedef ptr Release64@CT
		Release Release64@MP ?

  GetTypeInfoCount64@CT typedef proto \
		 _This: ptr IWriteCookie,
	       pctinfo: ptr UINT

  GetTypeInfoCount64@MP typedef ptr GetTypeInfoCount64@CT
       GetTypeInfoCount GetTypeInfoCount64@MP ?

       GetTypeInfo64@CT typedef proto \
		 _This: ptr IWriteCookie,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo64@MP typedef ptr GetTypeInfo64@CT
	    GetTypeInfo GetTypeInfo64@MP ?

     GetIDsOfNames64@CT typedef proto \
		 _This: ptr IWriteCookie,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames64@MP typedef ptr GetIDsOfNames64@CT
	  GetIDsOfNames GetIDsOfNames64@MP ?

	   _Invoke64@CT typedef proto \
		 _This: ptr IWriteCookie,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke64@MP typedef ptr _Invoke64@CT
		_Invoke _Invoke64@MP ?

	  put_Item64@CT typedef proto \
		 _This: ptr IWriteCookie,
		   key: VARIANT,
	     bstrValue: BSTR

	  put_Item64@MP typedef ptr put_Item64@CT
	       put_Item put_Item64@MP ?

       put_Expires64@CT typedef proto \
		 _This: ptr IWriteCookie,
	     dtExpires: DATE

       put_Expires64@MP typedef ptr put_Expires64@CT
	    put_Expires put_Expires64@MP ?

	put_Domain64@CT typedef proto \
		 _This: ptr IWriteCookie,
	    bstrDomain: BSTR

	put_Domain64@MP typedef ptr put_Domain64@CT
	     put_Domain put_Domain64@MP ?

	  put_Path64@CT typedef proto \
		 _This: ptr IWriteCookie,
	      bstrPath: BSTR

	  put_Path64@MP typedef ptr put_Path64@CT
	       put_Path put_Path64@MP ?

	put_Secure64@CT typedef proto \
		 _This: ptr IWriteCookie,
	       fSecure: VARIANT_BOOL

	put_Secure64@MP typedef ptr put_Secure64@CT
	     put_Secure put_Secure64@MP ?

       get_HasKeys64@CT typedef proto \
		 _This: ptr IWriteCookie,
	     pfHasKeys: ptr VARIANT_BOOL

       get_HasKeys64@MP typedef ptr get_HasKeys64@CT
	    get_HasKeys get_HasKeys64@MP ?

      get__NewEnum64@CT typedef proto \
		 _This: ptr IWriteCookie,
	  ppEnumReturn: ptr IUnknown

      get__NewEnum64@MP typedef ptr get__NewEnum64@CT
	   get__NewEnum get__NewEnum64@MP ?

	END_INTERFACE

IWriteCookieVtbl	ENDS

LPIWriteCookieVtbl	typedef ptr IWriteCookieVtbl
IWriteCookie		STRUC
lpVtbl			LPIWriteCookieVtbl ?
IWriteCookie		ENDS

endif	;; __IWriteCookie_INTERFACE_DEFINED__

ifndef __IResponse_INTERFACE_DEFINED__
__IResponse_INTERFACE_DEFINED__ equ 1

;; interface IResponse

DEFINE_GUID(IID_IResponse,0xD97A6DA0,0xA864,0x11cf,0x83,0xBE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

IResponseVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface65@CT typedef proto \
		 _This: ptr IResponse,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface65@MP typedef ptr QueryInterface65@CT
	 QueryInterface QueryInterface65@MP ?

	    AddRef65@CT typedef proto \
		 _This: ptr IResponse

	    AddRef65@MP typedef ptr AddRef65@CT
		 AddRef AddRef65@MP ?

	   Release65@CT typedef proto \
		 _This: ptr IResponse

	   Release65@MP typedef ptr Release65@CT
		Release Release65@MP ?

  GetTypeInfoCount65@CT typedef proto \
		 _This: ptr IResponse,
	       pctinfo: ptr UINT

  GetTypeInfoCount65@MP typedef ptr GetTypeInfoCount65@CT
       GetTypeInfoCount GetTypeInfoCount65@MP ?

       GetTypeInfo65@CT typedef proto \
		 _This: ptr IResponse,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo65@MP typedef ptr GetTypeInfo65@CT
	    GetTypeInfo GetTypeInfo65@MP ?

     GetIDsOfNames65@CT typedef proto \
		 _This: ptr IResponse,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames65@MP typedef ptr GetIDsOfNames65@CT
	  GetIDsOfNames GetIDsOfNames65@MP ?

	   _Invoke65@CT typedef proto \
		 _This: ptr IResponse,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke65@MP typedef ptr _Invoke65@CT
		_Invoke _Invoke65@MP ?

	get_Buffer65@CT typedef proto \
		 _This: ptr IResponse,
	  fIsBuffering: ptr VARIANT_BOOL

	get_Buffer65@MP typedef ptr get_Buffer65@CT
	     get_Buffer get_Buffer65@MP ?

	put_Buffer65@CT typedef proto \
		 _This: ptr IResponse,
	  fIsBuffering: VARIANT_BOOL

	put_Buffer65@MP typedef ptr put_Buffer65@CT
	     put_Buffer put_Buffer65@MP ?

   get_ContentType65@CT typedef proto \
		 _This: ptr IResponse,
   pbstrContentTypeRet: ptr BSTR

   get_ContentType65@MP typedef ptr get_ContentType65@CT
	get_ContentType get_ContentType65@MP ?

   put_ContentType65@CT typedef proto \
		 _This: ptr IResponse,
       bstrContentType: BSTR

   put_ContentType65@MP typedef ptr put_ContentType65@CT
	put_ContentType put_ContentType65@MP ?

       get_Expires65@CT typedef proto \
		 _This: ptr IResponse,
 pvarExpiresMinutesRet: ptr VARIANT

       get_Expires65@MP typedef ptr get_Expires65@CT
	    get_Expires get_Expires65@MP ?

       put_Expires65@CT typedef proto \
		 _This: ptr IResponse,
       lExpiresMinutes: long

       put_Expires65@MP typedef ptr put_Expires65@CT
	    put_Expires put_Expires65@MP ?

get_ExpiresAbsolute65@CT typedef proto \
		 _This: ptr IResponse,
	pvarExpiresRet: ptr VARIANT

get_ExpiresAbsolute65@MP typedef ptr get_ExpiresAbsolute65@CT
    get_ExpiresAbsolute get_ExpiresAbsolute65@MP ?

put_ExpiresAbsolute65@CT typedef proto \
		 _This: ptr IResponse,
	     dtExpires: DATE

put_ExpiresAbsolute65@MP typedef ptr put_ExpiresAbsolute65@CT
    put_ExpiresAbsolute put_ExpiresAbsolute65@MP ?

       get_Cookies65@CT typedef proto \
		 _This: ptr IResponse,
	     ppCookies: ptr IRequestDictionary

       get_Cookies65@MP typedef ptr get_Cookies65@CT
	    get_Cookies get_Cookies65@MP ?

	get_Status65@CT typedef proto \
		 _This: ptr IResponse,
	pbstrStatusRet: ptr BSTR

	get_Status65@MP typedef ptr get_Status65@CT
	     get_Status get_Status65@MP ?

	put_Status65@CT typedef proto \
		 _This: ptr IResponse,
	    bstrStatus: BSTR

	put_Status65@MP typedef ptr put_Status65@CT
	     put_Status put_Status65@MP ?

	       Add65@CT typedef proto \
		 _This: ptr IResponse,
       bstrHeaderValue: BSTR,
	bstrHeaderName: BSTR

	       Add65@MP typedef ptr Add65@CT
		   _Add Add65@MP ?

	 AddHeader65@CT typedef proto \
		 _This: ptr IResponse,
	bstrHeaderName: BSTR,
       bstrHeaderValue: BSTR

	 AddHeader65@MP typedef ptr AddHeader65@CT
	      AddHeader AddHeader65@MP ?

       AppendToLog65@CT typedef proto \
		 _This: ptr IResponse,
	  bstrLogEntry: BSTR

       AppendToLog65@MP typedef ptr AppendToLog65@CT
	    AppendToLog AppendToLog65@MP ?

       BinaryWrite65@CT typedef proto \
		 _This: ptr IResponse,
	      varInput: VARIANT

       BinaryWrite65@MP typedef ptr BinaryWrite65@CT
	    BinaryWrite BinaryWrite65@MP ?

	     Clear65@CT typedef proto \
		 _This: ptr IResponse

	     Clear65@MP typedef ptr Clear65@CT
		  Clear Clear65@MP ?

	       End65@CT typedef proto \
		 _This: ptr IResponse

	       End65@MP typedef ptr End65@CT
		   _End End65@MP ?

	     Flush65@CT typedef proto \
		 _This: ptr IResponse

	     Flush65@MP typedef ptr Flush65@CT
		  Flush Flush65@MP ?

	  Redirect65@CT typedef proto \
		 _This: ptr IResponse,
	       bstrURL: BSTR

	  Redirect65@MP typedef ptr Redirect65@CT
	       Redirect Redirect65@MP ?

	     Write65@CT typedef proto \
		 _This: ptr IResponse,
	       varText: VARIANT

	     Write65@MP typedef ptr Write65@CT
		  Write Write65@MP ?

	WriteBlock65@CT typedef proto \
		 _This: ptr IResponse,
	  iBlockNumber: sword

	WriteBlock65@MP typedef ptr WriteBlock65@CT
	     WriteBlock WriteBlock65@MP ?

 IsClientConnected65@CT typedef proto \
		 _This: ptr IResponse,
   pfIsClientConnected: ptr VARIANT_BOOL

 IsClientConnected65@MP typedef ptr IsClientConnected65@CT
      IsClientConnected IsClientConnected65@MP ?

       get_CharSet65@CT typedef proto \
		 _This: ptr IResponse,
       pbstrCharSetRet: ptr BSTR

       get_CharSet65@MP typedef ptr get_CharSet65@CT
	    get_CharSet get_CharSet65@MP ?

       put_CharSet65@CT typedef proto \
		 _This: ptr IResponse,
	   bstrCharSet: BSTR

       put_CharSet65@MP typedef ptr put_CharSet65@CT
	    put_CharSet put_CharSet65@MP ?

	      Pics65@CT typedef proto \
		 _This: ptr IResponse,
       bstrHeaderValue: BSTR

	      Pics65@MP typedef ptr Pics65@CT
		   Pics Pics65@MP ?

  get_CacheControl65@CT typedef proto \
		 _This: ptr IResponse,
     pbstrCacheControl: ptr BSTR

  get_CacheControl65@MP typedef ptr get_CacheControl65@CT
       get_CacheControl get_CacheControl65@MP ?

  put_CacheControl65@CT typedef proto \
		 _This: ptr IResponse,
      bstrCacheControl: BSTR

  put_CacheControl65@MP typedef ptr put_CacheControl65@CT
       put_CacheControl put_CacheControl65@MP ?

      get_CodePage65@CT typedef proto \
		 _This: ptr IResponse,
		 plvar: ptr long

      get_CodePage65@MP typedef ptr get_CodePage65@CT
	   get_CodePage get_CodePage65@MP ?

      put_CodePage65@CT typedef proto \
		 _This: ptr IResponse,
		  lvar: long

      put_CodePage65@MP typedef ptr put_CodePage65@CT
	   put_CodePage put_CodePage65@MP ?

	  get_LCID65@CT typedef proto \
		 _This: ptr IResponse,
		 plvar: ptr long

	  get_LCID65@MP typedef ptr get_LCID65@CT
	       get_LCID get_LCID65@MP ?

	  put_LCID65@CT typedef proto \
		 _This: ptr IResponse,
		  lvar: long

	  put_LCID65@MP typedef ptr put_LCID65@CT
	       put_LCID put_LCID65@MP ?

	END_INTERFACE

IResponseVtbl		ENDS

LPIResponseVtbl		typedef ptr IResponseVtbl
IResponse		STRUC
lpVtbl			LPIResponseVtbl ?
IResponse		ENDS

endif	;; __IResponse_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Response,0x46E19BA0,0x25DD,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IVariantDictionary_INTERFACE_DEFINED__
__IVariantDictionary_INTERFACE_DEFINED__ equ 1

;; interface IVariantDictionary


DEFINE_GUID(IID_IVariantDictionary,0x4a7deb90,0xb069,0x11d0,0xb3,0x73,0x00,0xa0,0xc9,0x0c,0x2b,0xd8);


IVariantDictionaryVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface66@MP typedef ptr QueryInterface66@CT
	 QueryInterface QueryInterface66@MP ?

	    AddRef66@CT typedef proto \
		 _This: ptr IVariantDictionary

	    AddRef66@MP typedef ptr AddRef66@CT
		 AddRef AddRef66@MP ?

	   Release66@CT typedef proto \
		 _This: ptr IVariantDictionary

	   Release66@MP typedef ptr Release66@CT
		Release Release66@MP ?

  GetTypeInfoCount66@CT typedef proto \
		 _This: ptr IVariantDictionary,
	       pctinfo: ptr UINT

  GetTypeInfoCount66@MP typedef ptr GetTypeInfoCount66@CT
       GetTypeInfoCount GetTypeInfoCount66@MP ?

       GetTypeInfo66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo66@MP typedef ptr GetTypeInfo66@CT
	    GetTypeInfo GetTypeInfo66@MP ?

     GetIDsOfNames66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames66@MP typedef ptr GetIDsOfNames66@CT
	  GetIDsOfNames GetIDsOfNames66@MP ?

	   _Invoke66@CT typedef proto \
		 _This: ptr IVariantDictionary,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke66@MP typedef ptr _Invoke66@CT
		_Invoke _Invoke66@MP ?

	  get_Item66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		VarKey: VARIANT,
		  pvar: ptr VARIANT

	  get_Item66@MP typedef ptr get_Item66@CT
	       get_Item get_Item66@MP ?

	  put_Item66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		VarKey: VARIANT,
		   var: VARIANT

	  put_Item66@MP typedef ptr put_Item66@CT
	       put_Item put_Item66@MP ?

       putref_Item66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		VarKey: VARIANT,
		   var: VARIANT

       putref_Item66@MP typedef ptr putref_Item66@CT
	    putref_Item putref_Item66@MP ?

	   get_Key66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		VarKey: VARIANT,
		  pvar: ptr VARIANT

	   get_Key66@MP typedef ptr get_Key66@CT
		get_Key get_Key66@MP ?

	 get_Count66@CT typedef proto \
		 _This: ptr IVariantDictionary,
	       cStrRet: ptr SINT

	 get_Count66@MP typedef ptr get_Count66@CT
	      get_Count get_Count66@MP ?

      get__NewEnum66@CT typedef proto \
		 _This: ptr IVariantDictionary,
	  ppEnumReturn: ptr IUnknown

      get__NewEnum66@MP typedef ptr get__NewEnum66@CT
	   get__NewEnum get__NewEnum66@MP ?

	    Remove66@CT typedef proto \
		 _This: ptr IVariantDictionary,
		VarKey: VARIANT

	    Remove66@MP typedef ptr Remove66@CT
		 Remove Remove66@MP ?

	 RemoveAll66@CT typedef proto \
		 _This: ptr IVariantDictionary

	 RemoveAll66@MP typedef ptr RemoveAll66@CT
	      RemoveAll RemoveAll66@MP ?

	END_INTERFACE

IVariantDictionaryVtbl	ENDS

LPIVariantDictionaryVtbl typedef ptr IVariantDictionaryVtbl
IVariantDictionary	STRUC
lpVtbl			LPIVariantDictionaryVtbl ?
IVariantDictionary	ENDS

endif	;; __IVariantDictionary_INTERFACE_DEFINED__

ifndef __ISessionObject_INTERFACE_DEFINED__
__ISessionObject_INTERFACE_DEFINED__ equ 1

;; interface ISessionObject


DEFINE_GUID(IID_ISessionObject,0xD97A6DA0,0xA865,0x11cf,0x83,0xAF,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);


ISessionObjectVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface67@CT typedef proto \
		 _This: ptr ISessionObject,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface67@MP typedef ptr QueryInterface67@CT
	 QueryInterface QueryInterface67@MP ?

	    AddRef67@CT typedef proto \
		 _This: ptr ISessionObject

	    AddRef67@MP typedef ptr AddRef67@CT
		 AddRef AddRef67@MP ?

	   Release67@CT typedef proto \
		 _This: ptr ISessionObject

	   Release67@MP typedef ptr Release67@CT
		Release Release67@MP ?

  GetTypeInfoCount67@CT typedef proto \
		 _This: ptr ISessionObject,
	       pctinfo: ptr UINT

  GetTypeInfoCount67@MP typedef ptr GetTypeInfoCount67@CT
       GetTypeInfoCount GetTypeInfoCount67@MP ?

       GetTypeInfo67@CT typedef proto \
		 _This: ptr ISessionObject,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo67@MP typedef ptr GetTypeInfo67@CT
	    GetTypeInfo GetTypeInfo67@MP ?

     GetIDsOfNames67@CT typedef proto \
		 _This: ptr ISessionObject,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames67@MP typedef ptr GetIDsOfNames67@CT
	  GetIDsOfNames GetIDsOfNames67@MP ?

	   _Invoke67@CT typedef proto \
		 _This: ptr ISessionObject,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke67@MP typedef ptr _Invoke67@CT
		_Invoke _Invoke67@MP ?

     get_SessionID67@CT typedef proto \
		 _This: ptr ISessionObject,
	      pbstrRet: ptr BSTR

     get_SessionID67@MP typedef ptr get_SessionID67@CT
	  get_SessionID get_SessionID67@MP ?

	 get_Value67@CT typedef proto \
		 _This: ptr ISessionObject,
	     bstrValue: BSTR,
		  pvar: ptr VARIANT

	 get_Value67@MP typedef ptr get_Value67@CT
	      get_Value get_Value67@MP ?

	 put_Value67@CT typedef proto \
		 _This: ptr ISessionObject,
	     bstrValue: BSTR,
		   var: VARIANT

	 put_Value67@MP typedef ptr put_Value67@CT
	      put_Value put_Value67@MP ?

      putref_Value67@CT typedef proto \
		 _This: ptr ISessionObject,
	     bstrValue: BSTR,
		   var: VARIANT

      putref_Value67@MP typedef ptr putref_Value67@CT
	   putref_Value putref_Value67@MP ?

       get_Timeout67@CT typedef proto \
		 _This: ptr ISessionObject,
		 plvar: ptr long

       get_Timeout67@MP typedef ptr get_Timeout67@CT
	    get_Timeout get_Timeout67@MP ?

       put_Timeout67@CT typedef proto \
		 _This: ptr ISessionObject,
		  lvar: long

       put_Timeout67@MP typedef ptr put_Timeout67@CT
	    put_Timeout put_Timeout67@MP ?

	   Abandon67@CT typedef proto \
		 _This: ptr ISessionObject

	   Abandon67@MP typedef ptr Abandon67@CT
		Abandon Abandon67@MP ?

      get_CodePage67@CT typedef proto \
		 _This: ptr ISessionObject,
		 plvar: ptr long

      get_CodePage67@MP typedef ptr get_CodePage67@CT
	   get_CodePage get_CodePage67@MP ?

      put_CodePage67@CT typedef proto \
		 _This: ptr ISessionObject,
		  lvar: long

      put_CodePage67@MP typedef ptr put_CodePage67@CT
	   put_CodePage put_CodePage67@MP ?

	  get_LCID67@CT typedef proto \
		 _This: ptr ISessionObject,
		 plvar: ptr long

	  get_LCID67@MP typedef ptr get_LCID67@CT
	       get_LCID get_LCID67@MP ?

	  put_LCID67@CT typedef proto \
		 _This: ptr ISessionObject,
		  lvar: long

	  put_LCID67@MP typedef ptr put_LCID67@CT
	       put_LCID put_LCID67@MP ?

 get_StaticObjects67@CT typedef proto \
		 _This: ptr ISessionObject,
       ppTaggedObjects: ptr IVariantDictionary

 get_StaticObjects67@MP typedef ptr get_StaticObjects67@CT
      get_StaticObjects get_StaticObjects67@MP ?

      get_Contents67@CT typedef proto \
		 _This: ptr ISessionObject,
	  ppProperties: ptr IVariantDictionary

      get_Contents67@MP typedef ptr get_Contents67@CT
	   get_Contents get_Contents67@MP ?

	END_INTERFACE

ISessionObjectVtbl	ENDS

LPISessionObjectVtbl	typedef ptr ISessionObjectVtbl
ISessionObject		STRUC
lpVtbl			LPISessionObjectVtbl ?
ISessionObject		ENDS

endif	;; __ISessionObject_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Session,0x509F8F20,0x25DE,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IApplicationObject_INTERFACE_DEFINED__
__IApplicationObject_INTERFACE_DEFINED__ equ 1

;; interface IApplicationObject


DEFINE_GUID(IID_IApplicationObject,0xD97A6DA0,0xA866,0x11cf,0x83,0xAE,0x10,0xA0,0xC9,0x0C,0x2B,0xD8);


IApplicationObjectVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface68@CT typedef proto \
		 _This: ptr IApplicationObject,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface68@MP typedef ptr QueryInterface68@CT
	 QueryInterface QueryInterface68@MP ?

	    AddRef68@CT typedef proto \
		 _This: ptr IApplicationObject

	    AddRef68@MP typedef ptr AddRef68@CT
		 AddRef AddRef68@MP ?

	   Release68@CT typedef proto \
		 _This: ptr IApplicationObject

	   Release68@MP typedef ptr Release68@CT
		Release Release68@MP ?

  GetTypeInfoCount68@CT typedef proto \
		 _This: ptr IApplicationObject,
	       pctinfo: ptr UINT

  GetTypeInfoCount68@MP typedef ptr GetTypeInfoCount68@CT
       GetTypeInfoCount GetTypeInfoCount68@MP ?

       GetTypeInfo68@CT typedef proto \
		 _This: ptr IApplicationObject,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo68@MP typedef ptr GetTypeInfo68@CT
	    GetTypeInfo GetTypeInfo68@MP ?

     GetIDsOfNames68@CT typedef proto \
		 _This: ptr IApplicationObject,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames68@MP typedef ptr GetIDsOfNames68@CT
	  GetIDsOfNames GetIDsOfNames68@MP ?

	   _Invoke68@CT typedef proto \
		 _This: ptr IApplicationObject,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke68@MP typedef ptr _Invoke68@CT
		_Invoke _Invoke68@MP ?

	 get_Value68@CT typedef proto \
		 _This: ptr IApplicationObject,
	     bstrValue: BSTR,
		  pvar: ptr VARIANT

	 get_Value68@MP typedef ptr get_Value68@CT
	      get_Value get_Value68@MP ?

	 put_Value68@CT typedef proto \
		 _This: ptr IApplicationObject,
	     bstrValue: BSTR,
		   var: VARIANT

	 put_Value68@MP typedef ptr put_Value68@CT
	      put_Value put_Value68@MP ?

      putref_Value68@CT typedef proto \
		 _This: ptr IApplicationObject,
	     bstrValue: BSTR,
		   var: VARIANT

      putref_Value68@MP typedef ptr putref_Value68@CT
	   putref_Value putref_Value68@MP ?

	      Lock68@CT typedef proto \
		 _This: ptr IApplicationObject

	      Lock68@MP typedef ptr Lock68@CT
		  _Lock Lock68@MP ?

	    UnLock68@CT typedef proto \
		 _This: ptr IApplicationObject

	    UnLock68@MP typedef ptr UnLock68@CT
		 UnLock UnLock68@MP ?

 get_StaticObjects68@CT typedef proto \
		 _This: ptr IApplicationObject,
	  ppProperties: ptr IVariantDictionary

 get_StaticObjects68@MP typedef ptr get_StaticObjects68@CT
      get_StaticObjects get_StaticObjects68@MP ?

      get_Contents68@CT typedef proto \
		 _This: ptr IApplicationObject,
	  ppProperties: ptr IVariantDictionary

      get_Contents68@MP typedef ptr get_Contents68@CT
	   get_Contents get_Contents68@MP ?

	END_INTERFACE

IApplicationObjectVtbl	ENDS

LPIApplicationObjectVtbl typedef ptr IApplicationObjectVtbl
IApplicationObject	STRUC
lpVtbl			LPIApplicationObjectVtbl ?
IApplicationObject	ENDS

endif	;; __IApplicationObject_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Application,0x7C3BAF00,0x25DE,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IASPError_INTERFACE_DEFINED__
__IASPError_INTERFACE_DEFINED__ equ 1

;; interface IASPError


DEFINE_GUID(IID_IASPError,0xF5A6893E,0xA0F5,0x11d1,0x8C,0x4B,0x00,0xC0,0x4F,0xC3,0x24,0xA4);


IASPErrorVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface69@CT typedef proto \
		 _This: ptr IASPError,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface69@MP typedef ptr QueryInterface69@CT
	 QueryInterface QueryInterface69@MP ?

	    AddRef69@CT typedef proto \
		 _This: ptr IASPError

	    AddRef69@MP typedef ptr AddRef69@CT
		 AddRef AddRef69@MP ?

	   Release69@CT typedef proto \
		 _This: ptr IASPError

	   Release69@MP typedef ptr Release69@CT
		Release Release69@MP ?

  GetTypeInfoCount69@CT typedef proto \
		 _This: ptr IASPError,
	       pctinfo: ptr UINT

  GetTypeInfoCount69@MP typedef ptr GetTypeInfoCount69@CT
       GetTypeInfoCount GetTypeInfoCount69@MP ?

       GetTypeInfo69@CT typedef proto \
		 _This: ptr IASPError,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo69@MP typedef ptr GetTypeInfo69@CT
	    GetTypeInfo GetTypeInfo69@MP ?

     GetIDsOfNames69@CT typedef proto \
		 _This: ptr IASPError,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames69@MP typedef ptr GetIDsOfNames69@CT
	  GetIDsOfNames GetIDsOfNames69@MP ?

	   _Invoke69@CT typedef proto \
		 _This: ptr IASPError,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke69@MP typedef ptr _Invoke69@CT
		_Invoke _Invoke69@MP ?

       get_ASPCode69@CT typedef proto \
		 _This: ptr IASPError,
	  pbstrASPCode: ptr BSTR

       get_ASPCode69@MP typedef ptr get_ASPCode69@CT
	    get_ASPCode get_ASPCode69@MP ?

	get_Number69@CT typedef proto \
		 _This: ptr IASPError,
	      plNumber: ptr long

	get_Number69@MP typedef ptr get_Number69@CT
	     get_Number get_Number69@MP ?

      get_Category69@CT typedef proto \
		 _This: ptr IASPError,
	   pbstrSource: ptr BSTR

      get_Category69@MP typedef ptr get_Category69@CT
	   get_Category get_Category69@MP ?

	  get_File69@CT typedef proto \
		 _This: ptr IASPError,
	 pbstrFileName: ptr BSTR

	  get_File69@MP typedef ptr get_File69@CT
	       get_File get_File69@MP ?

	  get_Line69@CT typedef proto \
		 _This: ptr IASPError,
	  plLineNumber: ptr long

	  get_Line69@MP typedef ptr get_Line69@CT
	       get_Line get_Line69@MP ?

   get_Description69@CT typedef proto \
		 _This: ptr IASPError,
      pbstrDescription: ptr BSTR

   get_Description69@MP typedef ptr get_Description69@CT
	get_Description get_Description69@MP ?

get_ASPDescription69@CT typedef proto \
		 _This: ptr IASPError,
      pbstrDescription: ptr BSTR

get_ASPDescription69@MP typedef ptr get_ASPDescription69@CT
     get_ASPDescription get_ASPDescription69@MP ?

	get_Column69@CT typedef proto \
		 _This: ptr IASPError,
	      plColumn: ptr long

	get_Column69@MP typedef ptr get_Column69@CT
	     get_Column get_Column69@MP ?

	get_Source69@CT typedef proto \
		 _This: ptr IASPError,
	 pbstrLineText: ptr BSTR

	get_Source69@MP typedef ptr get_Source69@CT
	     get_Source get_Source69@MP ?

	END_INTERFACE

IASPErrorVtbl		ENDS

LPIASPErrorVtbl		typedef ptr IASPErrorVtbl
IASPError		STRUC
lpVtbl			LPIASPErrorVtbl ?
IASPError		ENDS

endif	;; __IASPError_INTERFACE_DEFINED__

ifndef __IServer_INTERFACE_DEFINED__
__IServer_INTERFACE_DEFINED__ equ 1

;; interface IServer


DEFINE_GUID(IID_IServer,0xD97A6DA0,0xA867,0x11cf,0x83,0xAE,0x01,0xA0,0xC9,0x0C,0x2B,0xD8);


IServerVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface70@CT typedef proto \
		 _This: ptr IServer,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface70@MP typedef ptr QueryInterface70@CT
	 QueryInterface QueryInterface70@MP ?

	    AddRef70@CT typedef proto \
		 _This: ptr IServer

	    AddRef70@MP typedef ptr AddRef70@CT
		 AddRef AddRef70@MP ?

	   Release70@CT typedef proto \
		 _This: ptr IServer

	   Release70@MP typedef ptr Release70@CT
		Release Release70@MP ?

  GetTypeInfoCount70@CT typedef proto \
		 _This: ptr IServer,
	       pctinfo: ptr UINT

  GetTypeInfoCount70@MP typedef ptr GetTypeInfoCount70@CT
       GetTypeInfoCount GetTypeInfoCount70@MP ?

       GetTypeInfo70@CT typedef proto \
		 _This: ptr IServer,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo70@MP typedef ptr GetTypeInfo70@CT
	    GetTypeInfo GetTypeInfo70@MP ?

     GetIDsOfNames70@CT typedef proto \
		 _This: ptr IServer,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames70@MP typedef ptr GetIDsOfNames70@CT
	  GetIDsOfNames GetIDsOfNames70@MP ?

	   _Invoke70@CT typedef proto \
		 _This: ptr IServer,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke70@MP typedef ptr _Invoke70@CT
		_Invoke _Invoke70@MP ?

 get_ScriptTimeout70@CT typedef proto \
		 _This: ptr IServer,
      plTimeoutSeconds: ptr long

 get_ScriptTimeout70@MP typedef ptr get_ScriptTimeout70@CT
      get_ScriptTimeout get_ScriptTimeout70@MP ?

 put_ScriptTimeout70@CT typedef proto \
		 _This: ptr IServer,
       lTimeoutSeconds: long

 put_ScriptTimeout70@MP typedef ptr put_ScriptTimeout70@CT
      put_ScriptTimeout put_ScriptTimeout70@MP ?

      CreateObject70@CT typedef proto \
		 _This: ptr IServer,
	    bstrProgID: BSTR,
	  ppDispObject: ptr IDispatch

      CreateObject70@MP typedef ptr CreateObject70@CT
	   CreateObject CreateObject70@MP ?

	HTMLEncode70@CT typedef proto \
		 _This: ptr IServer,
		bstrIn: BSTR,
	  pbstrEncoded: ptr BSTR

	HTMLEncode70@MP typedef ptr HTMLEncode70@CT
	     HTMLEncode HTMLEncode70@MP ?

	   MapPath70@CT typedef proto \
		 _This: ptr IServer,
       bstrLogicalPath: BSTR,
     pbstrPhysicalPath: ptr BSTR

	   MapPath70@MP typedef ptr MapPath70@CT
		MapPath MapPath70@MP ?

	 URLEncode70@CT typedef proto \
		 _This: ptr IServer,
		bstrIn: BSTR,
	  pbstrEncoded: ptr BSTR

	 URLEncode70@MP typedef ptr URLEncode70@CT
	      URLEncode URLEncode70@MP ?

     URLPathEncode70@CT typedef proto \
		 _This: ptr IServer,
		bstrIn: BSTR,
	  pbstrEncoded: ptr BSTR

     URLPathEncode70@MP typedef ptr URLPathEncode70@CT
	  URLPathEncode URLPathEncode70@MP ?

	   Execute70@CT typedef proto \
		 _This: ptr IServer,
       bstrLogicalPath: BSTR

	   Execute70@MP typedef ptr Execute70@CT
		Execute Execute70@MP ?

	  Transfer70@CT typedef proto \
		 _This: ptr IServer,
       bstrLogicalPath: BSTR

	  Transfer70@MP typedef ptr Transfer70@CT
	       Transfer Transfer70@MP ?

      GetLastError70@CT typedef proto \
		 _This: ptr IServer,
      ppASPErrorObject: ptr IASPError

      GetLastError70@MP typedef ptr GetLastError70@CT
	   GetLastError GetLastError70@MP ?

	END_INTERFACE

IServerVtbl		ENDS

LPIServerVtbl		typedef ptr IServerVtbl
IServer			STRUC
lpVtbl			LPIServerVtbl ?
IServer			ENDS

endif	;; __IServer_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Server,0xA506D160,0x25E0,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IScriptingContext_INTERFACE_DEFINED__
__IScriptingContext_INTERFACE_DEFINED__ equ 1

;; interface IScriptingContext


DEFINE_GUID(IID_IScriptingContext,0xD97A6DA0,0xA868,0x11cf,0x83,0xAE,0x00,0xB0,0xC9,0x0C,0x2B,0xD8);


IScriptingContextVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface71@CT typedef proto \
		 _This: ptr IScriptingContext,
		  riid: REFIID,
	     ppvObject: ptr PVOID

    QueryInterface71@MP typedef ptr QueryInterface71@CT
	 QueryInterface QueryInterface71@MP ?

	    AddRef71@CT typedef proto \
		 _This: ptr IScriptingContext

	    AddRef71@MP typedef ptr AddRef71@CT
		 AddRef AddRef71@MP ?

	   Release71@CT typedef proto \
		 _This: ptr IScriptingContext

	   Release71@MP typedef ptr Release71@CT
		Release Release71@MP ?

  GetTypeInfoCount71@CT typedef proto \
		 _This: ptr IScriptingContext,
	       pctinfo: ptr UINT

  GetTypeInfoCount71@MP typedef ptr GetTypeInfoCount71@CT
       GetTypeInfoCount GetTypeInfoCount71@MP ?

       GetTypeInfo71@CT typedef proto \
		 _This: ptr IScriptingContext,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo71@MP typedef ptr GetTypeInfo71@CT
	    GetTypeInfo GetTypeInfo71@MP ?

     GetIDsOfNames71@CT typedef proto \
		 _This: ptr IScriptingContext,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames71@MP typedef ptr GetIDsOfNames71@CT
	  GetIDsOfNames GetIDsOfNames71@MP ?

	   _Invoke71@CT typedef proto \
		 _This: ptr IScriptingContext,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	   _Invoke71@MP typedef ptr _Invoke71@CT
		_Invoke _Invoke71@MP ?

       get_Request71@CT typedef proto \
		 _This: ptr IScriptingContext,
	     ppRequest: ptr IRequest

       get_Request71@MP typedef ptr get_Request71@CT
	    get_Request get_Request71@MP ?

      get_Response71@CT typedef proto \
		 _This: ptr IScriptingContext,
	    ppResponse: ptr IResponse

      get_Response71@MP typedef ptr get_Response71@CT
	   get_Response get_Response71@MP ?

	get_Server71@CT typedef proto \
		 _This: ptr IScriptingContext,
	      ppServer: ptr IServer

	get_Server71@MP typedef ptr get_Server71@CT
	     get_Server get_Server71@MP ?

       get_Session71@CT typedef proto \
		 _This: ptr IScriptingContext,
	     ppSession: ptr ISessionObject

       get_Session71@MP typedef ptr get_Session71@CT
	    get_Session get_Session71@MP ?

   get_Application71@CT typedef proto \
		 _This: ptr IScriptingContext,
	 ppApplication: ptr IApplicationObject

   get_Application71@MP typedef ptr get_Application71@CT
	get_Application get_Application71@MP ?

	END_INTERFACE

IScriptingContextVtbl	ENDS

LPIScriptingContextVtbl typedef ptr IScriptingContextVtbl
IScriptingContext	STRUC
lpVtbl			LPIScriptingContextVtbl ?
IScriptingContext	ENDS

endif	;; __IScriptingContext_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_ScriptingContext,0xD97A6DA0,0xA868,0x11cf,0x83,0xAE,0x11,0xB0,0xC9,0x0C,0x2B,0xD8);

endif ;; __ASPTypeLibrary_LIBRARY_DEFINED__

;; Additional Prototypes for ALL interfaces

;; end of Additional Prototypes
.list
endif
