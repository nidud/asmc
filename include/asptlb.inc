ifndef _RPC500_
include rpc500.inc
endif
ifndef __asptlb_h__
define __asptlb_h__

ifndef __ASPTypeLibrary_LIBRARY_DEFINED__
define __ASPTypeLibrary_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_ASPTypeLibrary,0xD97A6DA0,0xA85C,0x11cf,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

ifndef __IStringList_INTERFACE_DEFINED__
define __IStringList_INTERFACE_DEFINED__

DEFINE_GUID(IID_IStringList,0xD97A6DA0,0xA85D,0x11cf,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IStringList : public IDispatch

    get_Item		proc :VARIANT, :ptr
    get_Count		proc :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __IRequestDictionary_INTERFACE_DEFINED__
define __IRequestDictionary_INTERFACE_DEFINED__

DEFINE_GUID(IID_IRequestDictionary,0xD97A6DA0,0xA85F,0x11df,0x83,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IRequestDictionary : public IDispatch

    get_Item		proc :VARIANT, :ptr
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    get_Key		proc :VARIANT, :ptr
   .ends

endif

ifndef __IRequest_INTERFACE_DEFINED__
define __IRequest_INTERFACE_DEFINED__

DEFINE_GUID(IID_IRequest,0xD97A6DA0,0xA861,0x11cf,0x93,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IRequest : public IDispatch

    get_Item		proc :BSTR, :ptr
    get_QueryString	proc :ptr
    get_Form		proc :ptr
    get_Body		proc :ptr
    get_ServerVariables proc :ptr
    get_ClientCertificate proc :ptr
    get_Cookies		proc :ptr
    get_TotalBytes	proc :ptr
    BinaryRead		proc :ptr, :ptr
   .ends

endif

DEFINE_GUID(CLSID_Request,0x920c25d0,0x25d9,0x11d0,0xa5,0x5f,0x00,0xa0,0xc9,0x0c,0x20,0x91)

ifndef __IReadCookie_INTERFACE_DEFINED__
define __IReadCookie_INTERFACE_DEFINED__

DEFINE_GUID(IID_IReadCookie,0x71EAF260,0x0CE0,0x11D0,0xA5,0x3E,0x00,0xA0,0xC9,0x0C,0x20,0x91)

.comdef IReadCookie : public IDispatch

    get_Item		proc :BSTR, :ptr
    get_HasKeys		proc :ptr
    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    get_Key		proc :VARIANT, :ptr
   .ends

endif

ifndef __IWriteCookie_INTERFACE_DEFINED__
define __IWriteCookie_INTERFACE_DEFINED__

DEFINE_GUID(IID_IWriteCookie,0xD97A6DA0,0xA862,0x11cf,0x84,0xAE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IWriteCookie : public IDispatch

    put_Item		proc :VARIANT, :BSTR
    put_Expires		proc :DATE
    put_Domain		proc :BSTR
    put_Path		proc :BSTR
    put_Secure		proc :VARIANT_BOOL
    get_HasKeys		proc :ptr
    get__NewEnum	proc :ptr
   .ends

endif

ifndef __IResponse_INTERFACE_DEFINED__
define __IResponse_INTERFACE_DEFINED__

DEFINE_GUID(IID_IResponse,0xD97A6DA0,0xA864,0x11cf,0x83,0xBE,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IResponse : public IDispatch

    get_Buffer		proc :ptr
    put_Buffer		proc :VARIANT_BOOL
    get_ContentType	proc :ptr
    put_ContentType	proc :BSTR
    get_Expires		proc :ptr
    put_Expires		proc :sdword
    get_ExpiresAbsolute proc :ptr
    put_ExpiresAbsolute proc :DATE
    get_Cookies		proc :ptr
    get_Status		proc :ptr
    put_Status		proc :BSTR
    _Add		proc :BSTR, :BSTR
    AddHeader		proc :BSTR, :BSTR
    AppendToLog		proc :BSTR
    BinaryWrite		proc :VARIANT
    Clear		proc
    _End		proc
    Flush		proc
    Redirect		proc :BSTR
    Write		proc :VARIANT
    WriteBlock		proc :sword
    IsClientConnected	proc :ptr
    get_CharSet		proc :ptr
    put_CharSet		proc :BSTR
    Pics		proc :BSTR
    get_CacheControl	proc :ptr
    put_CacheControl	proc :BSTR
    get_CodePage	proc :ptr
    put_CodePage	proc :sdword
    get_LCID		proc :ptr
    put_LCID		proc :sdword
   .ends

endif

DEFINE_GUID(CLSID_Response,0x46E19BA0,0x25DD,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91)

ifndef __IVariantDictionary_INTERFACE_DEFINED__
define __IVariantDictionary_INTERFACE_DEFINED__

DEFINE_GUID(IID_IVariantDictionary,0x4a7deb90,0xb069,0x11d0,0xb3,0x73,0x00,0xa0,0xc9,0x0c,0x2b,0xd8)

.comdef IVariantDictionary : public IDispatch

    get_Item		proc :VARIANT, :ptr
    put_Item		proc :VARIANT, :VARIANT
    putref_Item		proc :VARIANT, :VARIANT
    get_Key		proc :VARIANT, :ptr
    get_Count		proc :ptr
    get__NewEnum	proc :ptr
    Remove		proc :VARIANT
    RemoveAll		proc
   .ends

endif

ifndef __ISessionObject_INTERFACE_DEFINED__
define __ISessionObject_INTERFACE_DEFINED__

DEFINE_GUID(IID_ISessionObject,0xD97A6DA0,0xA865,0x11cf,0x83,0xAF,0x00,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef ISessionObject : public IDispatch

    get_SessionID	proc :ptr
    get_Value		proc :BSTR, :ptr
    put_Value		proc :BSTR, :VARIANT
    putref_Value	proc :BSTR, :VARIANT
    get_Timeout		proc :ptr
    put_Timeout		proc :sdword
    Abandon		proc
    get_CodePage	proc :ptr
    put_CodePage	proc :sdword
    get_LCID		proc :ptr
    put_LCID		proc :sdword
    get_StaticObjects	proc :ptr
    get_Contents	proc :ptr
   .ends

endif

DEFINE_GUID(CLSID_Session,0x509F8F20,0x25DE,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91)

ifndef __IApplicationObject_INTERFACE_DEFINED__
define __IApplicationObject_INTERFACE_DEFINED__

DEFINE_GUID(IID_IApplicationObject,0xD97A6DA0,0xA866,0x11cf,0x83,0xAE,0x10,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IApplicationObject : public IDispatch

    get_Value		proc :BSTR, :ptr
    put_Value		proc :BSTR, :VARIANT
    putref_Value	proc :BSTR, :VARIANT
    _Lock		proc
    UnLock		proc
    get_StaticObjects	proc :ptr
    get_Contents	proc :ptr
   .ends

endif

DEFINE_GUID(CLSID_Application,0x7C3BAF00,0x25DE,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91)

ifndef __IASPError_INTERFACE_DEFINED__
define __IASPError_INTERFACE_DEFINED__

DEFINE_GUID(IID_IASPError,0xF5A6893E,0xA0F5,0x11d1,0x8C,0x4B,0x00,0xC0,0x4F,0xC3,0x24,0xA4)

.comdef IASPError : public IDispatch

    get_ASPCode		proc :ptr
    get_Number		proc :ptr
    get_Category	proc :ptr
    get_File		proc :ptr
    get_Line		proc :ptr
    get_Description	proc :ptr
    get_ASPDescription	proc :ptr
    get_Column		proc :ptr
    get_Source		proc :ptr
   .ends

endif

ifndef __IServer_INTERFACE_DEFINED__
define __IServer_INTERFACE_DEFINED__

DEFINE_GUID(IID_IServer,0xD97A6DA0,0xA867,0x11cf,0x83,0xAE,0x01,0xA0,0xC9,0x0C,0x2B,0xD8)

.comdef IServer : public IDispatch

    get_ScriptTimeout	proc :ptr
    put_ScriptTimeout	proc :sdword
    CreateObject	proc :BSTR, :ptr
    HTMLEncode		proc :BSTR, :ptr
    MapPath		proc :BSTR, :ptr
    URLEncode		proc :BSTR, :ptr
    URLPathEncode	proc :BSTR, :ptr
    Execute		proc :BSTR
    Transfer		proc :BSTR
    GetLastError	proc :ptr
   .ends

endif

DEFINE_GUID(CLSID_Server,0xA506D160,0x25E0,0x11D0,0xA5,0x5F,0x00,0xA0,0xC9,0x0C,0x20,0x91)

ifndef __IScriptingContext_INTERFACE_DEFINED__
define __IScriptingContext_INTERFACE_DEFINED__

DEFINE_GUID(IID_IScriptingContext,0xD97A6DA0,0xA868,0x11cf,0x83,0xAE,0x00,0xB0,0xC9,0x0C,0x2B,0xD8)

.comdef IScriptingContext : public IDispatch

    get_Request		proc :ptr
    get_Response	proc :ptr
    get_Server		proc :ptr
    get_Session		proc :ptr
    get_Application	proc :ptr
   .ends

endif

DEFINE_GUID(CLSID_ScriptingContext,0xD97A6DA0,0xA868,0x11cf,0x83,0xAE,0x11,0xB0,0xC9,0x0C,0x2B,0xD8)

endif

endif
