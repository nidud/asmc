include rpc.inc
include rpcndr.inc
ifndef __msxml_h__
.xlist
__msxml_h__ equ 1

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

;XMLDocument XMLDocument; STRUC

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


IXMLElementCollectionVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface PVOID ?
		 AddRef PVOID ?
		Release PVOID ?
       GetTypeInfoCount PVOID ?
	    GetTypeInfo PVOID ?
	  GetIDsOfNames PVOID ?
		_Invoke PVOID ?
	     put_length PVOID ?
	     get_length PVOID ?
	   get__newEnum PVOID ?
		   item PVOID ?

	END_INTERFACE

IXMLElementCollectionVtbl ENDS

LPIXMLElementCollectionVtbl typedef ptr IXMLElementCollectionVtbl
IXMLElementCollection	STRUC
lpVtbl			LPIXMLElementCollectionVtbl ?
IXMLElementCollection	ENDS


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


IXMLDocumentVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface PVOID ?
		 AddRef PVOID ?
		Release PVOID ?
       GetTypeInfoCount PVOID ?
	    GetTypeInfo PVOID ?
	  GetIDsOfNames PVOID ?
		_Invoke PVOID ?
	       get_root PVOID ?
	   get_fileSize PVOID ?
   get_fileModifiedDate PVOID ?
    get_fileUpdatedDate PVOID ?
		get_URL PVOID ?
		put_URL PVOID ?
	   get_mimeType PVOID ?
	 get_readyState PVOID ?
	    get_charset PVOID ?
	    put_charset PVOID ?
	    get_version PVOID ?
	    get_doctype PVOID ?
	     get_dtdURL PVOID ?
	  createElement PVOID ?

	END_INTERFACE

IXMLDocumentVtbl	ENDS

LPIXMLDocumentVtbl	typedef ptr IXMLDocumentVtbl
IXMLDocument		STRUC
lpVtbl			LPIXMLDocumentVtbl ?
IXMLDocument		ENDS


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


IXMLElementVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface PVOID ?
		 AddRef PVOID ?
		Release PVOID ?
       GetTypeInfoCount PVOID ?
	    GetTypeInfo PVOID ?
	  GetIDsOfNames PVOID ?
		_Invoke PVOID ?
	    get_tagName PVOID ?
	    put_tagName PVOID ?
	     get_parent PVOID ?
	   setAttribute PVOID ?
	   getAttribute PVOID ?
	removeAttribute PVOID ?
	   get_children PVOID ?
	       get_type PVOID ?
	       get_text PVOID ?
	       put_text PVOID ?
	       addChild PVOID ?
	    removeChild PVOID ?

	END_INTERFACE

IXMLElementVtbl		ENDS

LPIXMLElementVtbl	typedef ptr IXMLElementVtbl
IXMLElement		STRUC
lpVtbl			LPIXMLElementVtbl ?
IXMLElement		ENDS

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


IXMLErrorVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface PVOID ?
		 AddRef PVOID ?
		Release PVOID ?
	   GetErrorInfo PVOID ?

	END_INTERFACE

IXMLErrorVtbl		ENDS

LPIXMLErrorVtbl		typedef ptr IXMLErrorVtbl
IXMLError		STRUC
lpVtbl			LPIXMLErrorVtbl ?
IXMLError		ENDS


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


IXMLElementNotificationSinkVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface PVOID ?
		 AddRef PVOID ?
		Release PVOID ?
       GetTypeInfoCount PVOID ?
	    GetTypeInfo PVOID ?
	  GetIDsOfNames PVOID ?
		_Invoke PVOID ?
	     ChildAdded PVOID ?

	END_INTERFACE

IXMLElementNotificationSinkVtbl ENDS

LPIXMLElementNotificationSinkVtbl typedef ptr IXMLElementNotificationSinkVtbl
IXMLElementNotificationSink STRUC
lpVtbl			LPIXMLElementNotificationSinkVtbl ?
IXMLElementNotificationSink ENDS

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
