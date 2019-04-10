include rpc.inc
include rpcndr.inc
ifndef __msxml_h__
__msxml_h__ equ <>

ifndef __IXMLElementCollection_FWD_DEFINED__
__IXMLElementCollection_FWD_DEFINED__ equ 1
endif
ifndef __IXMLDocument_FWD_DEFINED__
__IXMLDocument_FWD_DEFINED__ equ 1
endif
ifndef __IXMLElement_FWD_DEFINED__
__IXMLElement_FWD_DEFINED__ equ 1
endif
ifndef __IXMLError_FWD_DEFINED__
__IXMLError_FWD_DEFINED__ equ 1
endif
ifndef __IXMLElementNotificationSink_FWD_DEFINED__
__IXMLElementNotificationSink_FWD_DEFINED__ equ 1
endif
ifndef __XMLDocument_FWD_DEFINED__
__XMLDocument_FWD_DEFINED__ equ 1
endif
include unknwn.inc
include objidl.inc
include oaidl.inc

;void *
MIDL_user_allocate proto WINAPI :size_t
;void
MIDL_user_free proto WINAPI :PVOID

ifndef __MSXML_LIBRARY_DEFINED__
__MSXML_LIBRARY_DEFINED__ equ 1

;typedef enum xmlelemTYPE

XMLELEMTYPE_ELEMENT	equ 0
XMLELEMTYPE_TEXT	equ XMLELEMTYPE_ELEMENT + 1
XMLELEMTYPE_COMMENT	equ XMLELEMTYPE_TEXT + 1
XMLELEMTYPE_DOCUMENT	equ XMLELEMTYPE_COMMENT + 1
XMLELEMTYPE_DTD		equ XMLELEMTYPE_DOCUMENT + 1
XMLELEMTYPE_PI		equ XMLELEMTYPE_DTD + 1
XMLELEMTYPE_OTHER	equ XMLELEMTYPE_PI + 1

XML_ERROR		STRUC
_nLine			dd ?
_pchBuf			BSTR ?
_cchBuf			dd ?
_ich			dd ?
_pszFound		BSTR ?
_pszExpected		BSTR ?
_reserved1		dd ?
_reserved2		dd ?
XML_ERROR		ENDS

externdef		LIBID_MSXML:IID

ifndef __IXMLElementCollection_INTERFACE_DEFINED__
__IXMLElementCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLElementCollection, "65725580-9B5D-11d0-9BFE-00C04FC99C8E")

.comdef IXMLElementCollection
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __IXMLDocument_INTERFACE_DEFINED__
__IXMLDocument_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDocument, "F52E2B61-18A1-11d1-B105-00805F49916B")

.comdef IXMLDocument
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_root		proc :ptr
    get_fileSize	proc :ptr
    get_fileModifiedDate proc :ptr
    get_fileUpdatedDate proc :ptr
    get_URL		proc :ptr
    put_URL		proc :BSTR
    get_mimeType	proc :ptr
    get_readyState	proc :ptr
    get_charset		proc :ptr
    put_charset		proc :BSTR
    get_version		proc :ptr
    get_doctype		proc :ptr
    get_dtdURL		proc :ptr
    createElement	proc :VARIANT, :VARIANT, :ptr
    .ends

endif

ifndef __IXMLElement_INTERFACE_DEFINED__
__IXMLElement_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLElement, "3F7F31AC-E15F-11d0-9C25-00C04FC99C8E")

.comdef IXMLElement
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    get_tagName		proc :ptr
    put_tagName		proc :BSTR
    get_parent		proc :ptr
    setAttribute	proc :BSTR, :VARIANT
    getAttribute	proc :BSTR, :VARIANT
    removeAttribute	proc :BSTR
    get_children	proc :ptr
    get_type		proc :ptr
    get_text		proc :ptr
    put_text		proc :BSTR
    addChild		proc :ptr
    removeChild		proc :ptr, :LONG, :LONG
    .ends

endif

ifndef __IXMLError_INTERFACE_DEFINED__
__IXMLError_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLError, "948C5AD3-C58D-11d0-9C0B-00C04FC99C8E")

.comdef IXMLError
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetErrorInfo	proc :ptr
    .ends

endif


ifndef __IXMLElementNotificationSink_INTERFACE_DEFINED__
__IXMLElementNotificationSink_INTERFACE_DEFINED__ equ 1

externdef IID_IXMLElementNotificationSink:IID

.comdef IXMLElementNotificationSink
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetTypeInfoCount	proc :ptr
    GetTypeInfo		proc :UINT, :LCID, :ptr
    GetIDsOfNames	proc :REFIID, :ptr, :UINT, :LCID, :ptr
    _Invoke		proc :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
    ChildAdded		proc :ptr
    .ends

endif
DEFINE_GUIDS(CLSID_XMLDocument, "CFC399AF-D876-11d0-9C10-00C04FC99C8E")
endif

endif
