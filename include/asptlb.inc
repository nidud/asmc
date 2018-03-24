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

IStringListVtbl struct
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Item, :VARIANT, :ptr
STDMETHOD get_Count, :ptr
STDMETHOD get__NewEnum, :ptr
IStringListVtbl ends
IStringList struct
	lpVtbl		PVOID ?
IStringList ends
LPIStringList		typedef ptr IStringList

endif	;; __IStringList_INTERFACE_DEFINED__

ifndef __IRequestDictionary_INTERFACE_DEFINED__
__IRequestDictionary_INTERFACE_DEFINED__ equ 1

;; interface IRequestDictionary

DEFINE_GUID(IID_IRequestDictionary,0xD97A6DA0,0xA85F,0x11df,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

IRequestDictionaryVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Item, :VARIANT, :ptr
STDMETHOD get__NewEnum, :ptr
STDMETHOD get_Count, :ptr
STDMETHOD get_Key, :VARIANT, :ptr
IRequestDictionaryVtbl ends
IRequestDictionary struct
	lpVtbl		PVOID ?
IRequestDictionary ends
LPIRequestDictionary	typedef ptr IRequestDictionary
endif	;; __IRequestDictionary_INTERFACE_DEFINED__

ifndef __IRequest_INTERFACE_DEFINED__
__IRequest_INTERFACE_DEFINED__ equ 1

;; interface IRequest


DEFINE_GUID(IID_IRequest,0xD97A6DA0,0xA861,0x11cf,0x93,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);


IRequestVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Item, :BSTR, :ptr
STDMETHOD get_QueryString, :ptr
STDMETHOD get_Form, :ptr
STDMETHOD get_Body, :ptr
STDMETHOD get_ServerVariables, :ptr
STDMETHOD get_ClientCertificate, :ptr
STDMETHOD get_Cookies, :ptr
STDMETHOD get_TotalBytes, :ptr
STDMETHOD BinaryRead, :ptr, :ptr
IRequestVtbl ends
IRequest struct
	lpVtbl		PVOID ?
IRequest ends
LPIRequest		typedef ptr IRequest

endif	;; __IRequest_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Request,0x920c25d0,0x25d9,0x11d0,0xa5,0x5f,0x00,0xa0,0xc9,0x0c,0x20,0x91);

ifndef __IReadCookie_INTERFACE_DEFINED__
__IReadCookie_INTERFACE_DEFINED__ equ 1

;; interface IReadCookie


DEFINE_GUID(IID_IReadCookie,0x71EAF260,0x0CE0,0x11D0,0xA5,0x3E,0x00,0xA0,0xC9,0x0C,0x20,0x91);


IReadCookieVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Item, :BSTR, :ptr
STDMETHOD get_HasKeys, :ptr
STDMETHOD get__NewEnum, :ptr
STDMETHOD get_Count, :ptr
STDMETHOD get_Key, :VARIANT, :ptr
IReadCookieVtbl ends
IReadCookie struct
	lpVtbl		PVOID ?
IReadCookie ends
LPIReadCookie		typedef ptr IReadCookie

endif	;; __IReadCookie_INTERFACE_DEFINED__

ifndef __IWriteCookie_INTERFACE_DEFINED__
__IWriteCookie_INTERFACE_DEFINED__ equ 1

;; interface IWriteCookie


DEFINE_GUID(IID_IWriteCookie,0xD97A6DA0,0xA862,0x11cf,0x84,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

IWriteCookieVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD put_Item, :VARIANT, :BSTR
STDMETHOD put_Expires, :DATE
STDMETHOD put_Domain, :BSTR
STDMETHOD put_Path, :BSTR
STDMETHOD put_Secure, :VARIANT_BOOL
STDMETHOD get_HasKeys, :ptr
STDMETHOD get__NewEnum, :ptr
IWriteCookieVtbl ends
IWriteCookie struct
	lpVtbl		PVOID ?
IWriteCookie ends
LPIWriteCookie	typedef ptr IWriteCookie

endif	;; __IWriteCookie_INTERFACE_DEFINED__

ifndef __IResponse_INTERFACE_DEFINED__
__IResponse_INTERFACE_DEFINED__ equ 1

;; interface IResponse

DEFINE_GUID(IID_IResponse,0xD97A6DA0,0xA864,0x11cf,0x83,0xBE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

IResponseVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Buffer, :ptr
STDMETHOD put_Buffer, :VARIANT_BOOL
STDMETHOD get_ContentType, :ptr
STDMETHOD put_ContentType, :BSTR
STDMETHOD get_Expires, :ptr
STDMETHOD put_Expires, :long
STDMETHOD get_ExpiresAbsolute, :ptr
STDMETHOD put_ExpiresAbsolute, :DATE
STDMETHOD get_Cookies, :ptr
STDMETHOD get_Status, :ptr
STDMETHOD put_Status, :BSTR
STDMETHOD _Add, :BSTR, :BSTR
STDMETHOD AddHeader, :BSTR, :BSTR
STDMETHOD AppendToLog, :BSTR
STDMETHOD BinaryWrite, :VARIANT
STDMETHOD Clear
STDMETHOD _End
STDMETHOD Flush
STDMETHOD Redirect, :BSTR
STDMETHOD Write, :VARIANT
STDMETHOD WriteBlock, :sword
STDMETHOD IsClientConnected, :ptr
STDMETHOD get_CharSet, :ptr
STDMETHOD put_CharSet, :BSTR
STDMETHOD Pics, :BSTR
STDMETHOD get_CacheControl, :ptr
STDMETHOD put_CacheControl, :BSTR
STDMETHOD get_CodePage, :ptr
STDMETHOD put_CodePage, :long
STDMETHOD get_LCID, :ptr
STDMETHOD put_LCID, :long
IResponseVtbl ends
IResponse struct
	lpVtbl		PVOID ?
IResponse ends
LPIResponse		typedef ptr IResponse

endif	;; __IResponse_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Response,0x46E19BA0,0x25DD,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IVariantDictionary_INTERFACE_DEFINED__
__IVariantDictionary_INTERFACE_DEFINED__ equ 1

;; interface IVariantDictionary


DEFINE_GUID(IID_IVariantDictionary,0x4a7deb90,0xb069,0x11d0,0xb3,0x73,0x00,0xa0,0xc9,0x0c,0x2b,0xd8);

IVariantDictionaryVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Item, :VARIANT, :ptr
STDMETHOD put_Item, :VARIANT, :VARIANT
STDMETHOD putref_Item, :VARIANT, :VARIANT
STDMETHOD get_Key, :VARIANT, :ptr
STDMETHOD get_Count, :ptr
STDMETHOD get__NewEnum, :ptr
STDMETHOD Remove, :VARIANT
STDMETHOD RemoveAll
IVariantDictionaryVtbl ends
IVariantDictionary struct
	lpVtbl		PVOID ?
IVariantDictionary ends
LPIVariantDictionary	typedef ptr IVariantDictionary

endif	;; __IVariantDictionary_INTERFACE_DEFINED__

ifndef __ISessionObject_INTERFACE_DEFINED__
__ISessionObject_INTERFACE_DEFINED__ equ 1

;; interface ISessionObject


DEFINE_GUID(IID_ISessionObject,0xD97A6DA0,0xA865,0x11cf,0x83,0xAF,0x00,0xA0,0xC9,0x0C,0x2B,0xD8);

ISessionObjectVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_SessionID, :ptr
STDMETHOD get_Value, :BSTR, :ptr
STDMETHOD put_Value, :BSTR, :VARIANT
STDMETHOD putref_Value, :BSTR, :VARIANT
STDMETHOD get_Timeout, :ptr
STDMETHOD put_Timeout, :long
STDMETHOD Abandon
STDMETHOD get_CodePage, :ptr
STDMETHOD put_CodePage, :long
STDMETHOD get_LCID, :ptr
STDMETHOD put_LCID, :long
STDMETHOD get_StaticObjects, :ptr
STDMETHOD get_Contents, :ptr
ISessionObjectVtbl ends
ISessionObject struct
	lpVtbl		PVOID ?
ISessionObject ends
LPISessionObject	typedef ptr ISessionObject

endif	;; __ISessionObject_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Session,0x509F8F20,0x25DE,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IApplicationObject_INTERFACE_DEFINED__
__IApplicationObject_INTERFACE_DEFINED__ equ 1

;; interface IApplicationObject


DEFINE_GUID(IID_IApplicationObject,0xD97A6DA0,0xA866,0x11cf,0x83,0xAE,0x10,0xA0,0xC9,0x0C,0x2B,0xD8);

IApplicationObjectVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Value, :BSTR, :ptr
STDMETHOD put_Value, :BSTR, :VARIANT
STDMETHOD putref_Value, :BSTR, :VARIANT
STDMETHOD _Lock
STDMETHOD UnLock
STDMETHOD get_StaticObjects, :ptr
STDMETHOD get_Contents, :ptr
IApplicationObjectVtbl ends
IApplicationObject struct
	lpVtbl		PVOID ?
IApplicationObject ends
LPIApplicationObject	typedef ptr IApplicationObject

endif	;; __IApplicationObject_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Application,0x7C3BAF00,0x25DE,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IASPError_INTERFACE_DEFINED__
__IASPError_INTERFACE_DEFINED__ equ 1

;; interface IASPError


DEFINE_GUID(IID_IASPError,0xF5A6893E,0xA0F5,0x11d1,0x8C,0x4B,0x00,0xC0,0x4F,0xC3,0x24,0xA4);


IASPErrorVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_ASPCode, :ptr
STDMETHOD get_Number, :ptr
STDMETHOD get_Category, :ptr
STDMETHOD get_File, :ptr
STDMETHOD get_Line, :ptr
STDMETHOD get_Description, :ptr
STDMETHOD get_ASPDescription, :ptr
STDMETHOD get_Column, :ptr
STDMETHOD get_Source, :ptr
IASPErrorVtbl ends
IASPError struct
	lpVtbl		PVOID ?
IASPError ends
LPIASPError		typedef ptr IASPError

endif	;; __IASPError_INTERFACE_DEFINED__

ifndef __IServer_INTERFACE_DEFINED__
__IServer_INTERFACE_DEFINED__ equ 1

;; interface IServer


DEFINE_GUID(IID_IServer,0xD97A6DA0,0xA867,0x11cf,0x83,0xAE,0x01,0xA0,0xC9,0x0C,0x2B,0xD8);


IServerVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_ScriptTimeout, :ptr
STDMETHOD put_ScriptTimeout, :long
STDMETHOD CreateObject, :BSTR, :ptr
STDMETHOD HTMLEncode, :BSTR, :ptr
STDMETHOD MapPath, :BSTR, :ptr
STDMETHOD URLEncode, :BSTR, :ptr
STDMETHOD URLPathEncode, :BSTR, :ptr
STDMETHOD Execute, :BSTR
STDMETHOD Transfer, :BSTR
STDMETHOD GetLastError, :ptr
IServerVtbl ends
IServer struct
	lpVtbl		PVOID ?
IServer ends
LPIServer		typedef ptr IServer

endif	;; __IServer_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_Server,0xA506D160,0x25E0,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91);

ifndef __IScriptingContext_INTERFACE_DEFINED__
__IScriptingContext_INTERFACE_DEFINED__ equ 1

;; interface IScriptingContext


DEFINE_GUID(IID_IScriptingContext,0xD97A6DA0,0xA868,0x11cf,0x83,0xAE,0x00,0xB0,0xC9,0x0C,0x2B,0xD8);


IScriptingContextVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetTypeInfoCount, :ptr
STDMETHOD GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
STDMETHOD _Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
STDMETHOD get_Request, :ptr
STDMETHOD get_Response, :ptr
STDMETHOD get_Server, :ptr
STDMETHOD get_Session, :ptr
STDMETHOD get_Application, :ptr
IScriptingContextVtbl ends
IScriptingContext struct
	lpVtbl		PVOID ?
IScriptingContext ends
LPIScriptingContext	typedef ptr IScriptingContext

endif	;; __IScriptingContext_INTERFACE_DEFINED__

DEFINE_GUID(CLSID_ScriptingContext,0xD97A6DA0,0xA868,0x11cf,0x83,0xAE,0x11,0xB0,0xC9,0x0C,0x2B,0xD8);

endif ;; __ASPTypeLibrary_LIBRARY_DEFINED__

;; Additional Prototypes for ALL interfaces

;; end of Additional Prototypes
.list
endif
