include rpc.inc
include rpcndr.inc
ifndef __msxml_h__
__msxml_h__ equ 1
.xlist

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
.xlist

;void *
MIDL_user_allocate proto WINAPI :size_t
;void
MIDL_user_free proto WINAPI :PVOID

externdef		__MIDL_itf_msxml_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_msxml_0000_v0_0_s_ifspec:RPC_IF_HANDLE

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

externdef		IID_IXMLElementCollection:IID
IXMLElementCollectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	put_length, :LONG
	STDMETHOD	get_length, :ptr
	STDMETHOD	get__newEnum, :ptr
	STDMETHOD	item, :ptr, :ptr, :ptr
IXMLElementCollectionVtbl ends
IXMLElementCollection struct
	lpVtbl		PVOID ?
IXMLElementCollection ends
LPIXMLElementCollection typedef ptr IXMLElementCollection


;HRESULT
IXMLElementCollection_put_length_Proxy proto WINAPI \
		 pThis: ptr IXMLElementCollection,
		     v: LONG

;void
IXMLElementCollection_put_length_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElementCollection_get_length_Proxy proto WINAPI \
		 pThis: ptr IXMLElementCollection,
		     p: ptr LONG

;void
IXMLElementCollection_get_length_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElementCollection_get__newEnum_Proxy proto WINAPI \
		 pThis: ptr IXMLElementCollection,
		 ppUnk: ptr IUnknown

;void
IXMLElementCollection_get__newEnum_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElementCollection_item_Proxy proto WINAPI \
		 pThis: ptr IXMLElementCollection,
		  var1: VARIANT,
		  var2: VARIANT,
		ppDisp: ptr IDispatch

;void
IXMLElementCollection_item_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IXMLDocument_INTERFACE_DEFINED__
__IXMLDocument_INTERFACE_DEFINED__ equ 1

externdef		IID_IXMLDocument:IID
IXMLDocumentVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_root, :ptr
	STDMETHOD	get_fileSize, :ptr
	STDMETHOD	get_fileModifiedDate, :ptr
	STDMETHOD	get_fileUpdatedDate, :ptr
	STDMETHOD	get_URL, :ptr
	STDMETHOD	put_URL, :BSTR
	STDMETHOD	get_mimeType, :ptr
	STDMETHOD	get_readyState, :ptr
	STDMETHOD	get_charset, :ptr
	STDMETHOD	put_charset, :BSTR
	STDMETHOD	get_version, :ptr
	STDMETHOD	get_doctype, :ptr
	STDMETHOD	get_dtdURL, :ptr
	STDMETHOD	createElement, :VARIANT, :VARIANT, :ptr
IXMLDocumentVtbl ends
IXMLDocument struct
	lpVtbl		PVOID ?
IXMLDocument ends
LPIXMLDocument		typedef ptr IXMLDocument

;HRESULT
IXMLDocument_get_root_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr IXMLElement

;void
IXMLDocument_get_root_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_fileSize_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_fileSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_fileModifiedDate_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_fileModifiedDate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_fileUpdatedDate_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_fileUpdatedDate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_URL_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_URL_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_put_URL_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: BSTR

;void
IXMLDocument_put_URL_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_mimeType_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_mimeType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_readyState_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		    pl: ptr LONG

;void
IXMLDocument_get_readyState_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_charset_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_charset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_put_charset_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: BSTR

;void
IXMLDocument_put_charset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_version_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_version_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_doctype_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_doctype_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_get_dtdURL_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

;void
IXMLDocument_get_dtdURL_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLDocument_createElement_Proxy proto WINAPI \
		 pThis: ptr IXMLDocument,
		 vType: VARIANT,
		  var1: VARIANT,
		ppElem: ptr IXMLElement

;void
IXMLDocument_createElement_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IXMLElement_INTERFACE_DEFINED__
__IXMLElement_INTERFACE_DEFINED__ equ 1

externdef		IID_IXMLElement:IID
IXMLElementVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	get_tagName, :ptr
	STDMETHOD	put_tagName, :BSTR
	STDMETHOD	get_parent, :ptr
	STDMETHOD	setAttribute, :BSTR, :VARIANT
	STDMETHOD	getAttribute, :BSTR, :VARIANT
	STDMETHOD	removeAttribute, :BSTR
	STDMETHOD	get_children, :ptr
	STDMETHOD	get_type, :ptr
	STDMETHOD	get_text, :ptr
	STDMETHOD	put_text, :BSTR
	STDMETHOD	addChild, :ptr
	STDMETHOD	removeChild, :ptr, :LONG, :LONG
IXMLElementVtbl ends
IXMLElement struct
	lpVtbl		PVOID ?
IXMLElement ends
LPIXMLElement		typedef ptr IXMLElement

;HRESULT
IXMLElement_get_tagName_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
		     p: ptr BSTR

;void
IXMLElement_get_tagName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_put_tagName_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
		     p: BSTR

;void
IXMLElement_put_tagName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_get_parent_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
	      ppParent: ptr IXMLElement

;void
IXMLElement_get_parent_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_setAttribute_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
       strPropertyName: BSTR,
	 PropertyValue: VARIANT

;void
IXMLElement_setAttribute_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_getAttribute_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
       strPropertyName: BSTR,
	 PropertyValue: ptr VARIANT

;void
IXMLElement_getAttribute_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_removeAttribute_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
       strPropertyName: BSTR

;void
IXMLElement_removeAttribute_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_get_children_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
		    pp: ptr IXMLElementCollection
;void
IXMLElement_get_children_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_get_type_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
		plType: ptr LONG

;void
IXMLElement_get_type_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_get_text_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
		     p: ptr BSTR

;void
IXMLElement_get_text_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_put_text_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
		     p: BSTR
;void
IXMLElement_put_text_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_addChild_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
	    pChildElem: ptr IXMLElement,
		lIndex: LONG,
	     lReserved: LONG

;void
IXMLElement_addChild_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IXMLElement_removeChild_Proxy proto WINAPI \
		 pThis: ptr IXMLElement,
	    pChildElem: ptr IXMLElement

;void
IXMLElement_removeChild_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IXMLError_INTERFACE_DEFINED__
__IXMLError_INTERFACE_DEFINED__ equ 1

externdef		IID_IXMLError:IID
IXMLErrorVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetErrorInfo, :ptr
IXMLErrorVtbl ends
IXMLError struct
	lpVtbl		PVOID ?
IXMLError ends
LPIXMLError		typedef ptr IXMLError

;HRESULT
IXMLError_GetErrorInfo_Proxy proto WINAPI \
		 pThis: ptr IXMLError,
	  pErrorReturn: ptr XML_ERROR

;void
IXMLError_GetErrorInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif


ifndef __IXMLElementNotificationSink_INTERFACE_DEFINED__
__IXMLElementNotificationSink_INTERFACE_DEFINED__ equ 1

externdef		IID_IXMLElementNotificationSink:IID
IXMLElementNotificationSinkVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetTypeInfoCount, :ptr
	STDMETHOD	GetTypeInfo, :UINT, :LCID, :ptr
	STDMETHOD	GetIDsOfNames, :REFIID, :ptr, :UINT, :LCID, :ptr
	STDMETHOD	_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ChildAdded, :ptr
IXMLElementNotificationSinkVtbl ends
IXMLElementNotificationSink struct
	lpVtbl		PVOID ?
IXMLElementNotificationSink ends
LPIXMLElementNotificationSink typedef ptr IXMLElementNotificationSink

;HRESULT
IXMLElementNotificationSink_ChildAdded_Proxy proto WINAPI \
		 pThis: ptr IXMLElementNotificationSink,
	    pChildElem: ptr IDispatch

;void
IXMLElementNotificationSink_ChildAdded_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif
externdef		CLSID_XMLDocument:CLSID
endif

.list
endif
