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
MIDL_user_allocate proto WINAPI \
		      : size_t

;void
MIDL_user_free proto WINAPI \
		      : PVOID


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

    QueryInterface55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface55@MP typedef ptr QueryInterface55@CT
	 QueryInterface QueryInterface55@MP ?

	    AddRef55@CT typedef proto \
		 pThis: ptr IXMLElementCollection

	    AddRef55@MP typedef ptr AddRef55@CT
		 AddRef AddRef55@MP ?

	   Release55@CT typedef proto \
		 pThis: ptr IXMLElementCollection

	   Release55@MP typedef ptr Release55@CT
		Release Release55@MP ?

  GetTypeInfoCount55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
	       pctinfo: ptr UINT

  GetTypeInfoCount55@MP typedef ptr GetTypeInfoCount55@CT
       GetTypeInfoCount GetTypeInfoCount55@MP ?

       GetTypeInfo55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo55@MP typedef ptr GetTypeInfo55@CT
	    GetTypeInfo GetTypeInfo55@MP ?

     GetIDsOfNames55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames55@MP typedef ptr GetIDsOfNames55@CT
	  GetIDsOfNames GetIDsOfNames55@MP ?

	    Invoke55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	    Invoke55@MP typedef ptr Invoke55@CT
		_Invoke Invoke55@MP ?

	put_length55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		     v: LONG

	put_length55@MP typedef ptr put_length55@CT
	     put_length put_length55@MP ?

	get_length55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		     p: ptr LONG

	get_length55@MP typedef ptr get_length55@CT
	     get_length get_length55@MP ?

      get__newEnum55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		 ppUnk: ptr IUnknown

      get__newEnum55@MP typedef ptr get__newEnum55@CT
	   get__newEnum get__newEnum55@MP ?

	      item55@CT typedef proto \
		 pThis: ptr IXMLElementCollection,
		  var1: VARIANT,
		  var2: VARIANT,
		ppDisp: ptr IDispatch

	      item55@MP typedef ptr item55@CT
		   item item55@MP ?

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

    QueryInterface56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface56@MP typedef ptr QueryInterface56@CT
	 QueryInterface QueryInterface56@MP ?

	    AddRef56@CT typedef proto \
		 pThis: ptr IXMLDocument

	    AddRef56@MP typedef ptr AddRef56@CT
		 AddRef AddRef56@MP ?

	   Release56@CT typedef proto \
		 pThis: ptr IXMLDocument

	   Release56@MP typedef ptr Release56@CT
		Release Release56@MP ?

  GetTypeInfoCount56@CT typedef proto \
		 pThis: ptr IXMLDocument,
	       pctinfo: ptr UINT

  GetTypeInfoCount56@MP typedef ptr GetTypeInfoCount56@CT
       GetTypeInfoCount GetTypeInfoCount56@MP ?

       GetTypeInfo56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo56@MP typedef ptr GetTypeInfo56@CT
	    GetTypeInfo GetTypeInfo56@MP ?

     GetIDsOfNames56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames56@MP typedef ptr GetIDsOfNames56@CT
	  GetIDsOfNames GetIDsOfNames56@MP ?

	    Invoke56@CT typedef proto \
		 pThis: ptr IXMLDocument,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	    Invoke56@MP typedef ptr Invoke56@CT
		_Invoke Invoke56@MP ?

	  get_root56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr IXMLElement

	  get_root56@MP typedef ptr get_root56@CT
	       get_root get_root56@MP ?

      get_fileSize56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

      get_fileSize56@MP typedef ptr get_fileSize56@CT
	   get_fileSize get_fileSize56@MP ?

get_fileModifiedDate56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

get_fileModifiedDate56@MP typedef ptr get_fileModifiedDate56@CT
   get_fileModifiedDate get_fileModifiedDate56@MP ?

get_fileUpdatedDate56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

get_fileUpdatedDate56@MP typedef ptr get_fileUpdatedDate56@CT
    get_fileUpdatedDate get_fileUpdatedDate56@MP ?

	   get_URL56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

	   get_URL56@MP typedef ptr get_URL56@CT
		get_URL get_URL56@MP ?

	   put_URL56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: BSTR

	   put_URL56@MP typedef ptr put_URL56@CT
		put_URL put_URL56@MP ?

      get_mimeType56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

      get_mimeType56@MP typedef ptr get_mimeType56@CT
	   get_mimeType get_mimeType56@MP ?

    get_readyState56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		    pl: ptr LONG

    get_readyState56@MP typedef ptr get_readyState56@CT
	 get_readyState get_readyState56@MP ?

       get_charset56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

       get_charset56@MP typedef ptr get_charset56@CT
	    get_charset get_charset56@MP ?

       put_charset56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: BSTR

       put_charset56@MP typedef ptr put_charset56@CT
	    put_charset put_charset56@MP ?

       get_version56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

       get_version56@MP typedef ptr get_version56@CT
	    get_version get_version56@MP ?

       get_doctype56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

       get_doctype56@MP typedef ptr get_doctype56@CT
	    get_doctype get_doctype56@MP ?

	get_dtdURL56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		     p: ptr BSTR

	get_dtdURL56@MP typedef ptr get_dtdURL56@CT
	     get_dtdURL get_dtdURL56@MP ?

     createElement56@CT typedef proto \
		 pThis: ptr IXMLDocument,
		 vType: VARIANT,
		  var1: VARIANT,
		ppElem: ptr IXMLElement

     createElement56@MP typedef ptr createElement56@CT
	  createElement createElement56@MP ?

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

    QueryInterface57@CT typedef proto \
		 pThis: ptr IXMLElement,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface57@MP typedef ptr QueryInterface57@CT
	 QueryInterface QueryInterface57@MP ?

	    AddRef57@CT typedef proto \
		 pThis: ptr IXMLElement

	    AddRef57@MP typedef ptr AddRef57@CT
		 AddRef AddRef57@MP ?

	   Release57@CT typedef proto \
		 pThis: ptr IXMLElement

	   Release57@MP typedef ptr Release57@CT
		Release Release57@MP ?

  GetTypeInfoCount57@CT typedef proto \
		 pThis: ptr IXMLElement,
	       pctinfo: ptr UINT

  GetTypeInfoCount57@MP typedef ptr GetTypeInfoCount57@CT
       GetTypeInfoCount GetTypeInfoCount57@MP ?

       GetTypeInfo57@CT typedef proto \
		 pThis: ptr IXMLElement,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo57@MP typedef ptr GetTypeInfo57@CT
	    GetTypeInfo GetTypeInfo57@MP ?

     GetIDsOfNames57@CT typedef proto \
		 pThis: ptr IXMLElement,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames57@MP typedef ptr GetIDsOfNames57@CT
	  GetIDsOfNames GetIDsOfNames57@MP ?

	    Invoke57@CT typedef proto \
		 pThis: ptr IXMLElement,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	    Invoke57@MP typedef ptr Invoke57@CT
		_Invoke Invoke57@MP ?

       get_tagName57@CT typedef proto \
		 pThis: ptr IXMLElement,
		     p: ptr BSTR

       get_tagName57@MP typedef ptr get_tagName57@CT
	    get_tagName get_tagName57@MP ?

       put_tagName57@CT typedef proto \
		 pThis: ptr IXMLElement,
		     p: BSTR

       put_tagName57@MP typedef ptr put_tagName57@CT
	    put_tagName put_tagName57@MP ?

	get_parent57@CT typedef proto \
		 pThis: ptr IXMLElement,
	      ppParent: ptr IXMLElement

	get_parent57@MP typedef ptr get_parent57@CT
	     get_parent get_parent57@MP ?

      setAttribute57@CT typedef proto \
		 pThis: ptr IXMLElement,
       strPropertyName: BSTR,
	 PropertyValue: VARIANT

      setAttribute57@MP typedef ptr setAttribute57@CT
	   setAttribute setAttribute57@MP ?

      getAttribute57@CT typedef proto \
		 pThis: ptr IXMLElement,
       strPropertyName: BSTR,
	 PropertyValue: ptr VARIANT

      getAttribute57@MP typedef ptr getAttribute57@CT
	   getAttribute getAttribute57@MP ?

   removeAttribute57@CT typedef proto \
		 pThis: ptr IXMLElement,
       strPropertyName: BSTR

   removeAttribute57@MP typedef ptr removeAttribute57@CT
	removeAttribute removeAttribute57@MP ?

      get_children57@CT typedef proto \
		 pThis: ptr IXMLElement,
		    pp: ptr IXMLElementCollection

      get_children57@MP typedef ptr get_children57@CT
	   get_children get_children57@MP ?

	  get_type57@CT typedef proto \
		 pThis: ptr IXMLElement,
		plType: ptr LONG

	  get_type57@MP typedef ptr get_type57@CT
	       get_type get_type57@MP ?

	  get_text57@CT typedef proto \
		 pThis: ptr IXMLElement,
		     p: ptr BSTR

	  get_text57@MP typedef ptr get_text57@CT
	       get_text get_text57@MP ?

	  put_text57@CT typedef proto \
		 pThis: ptr IXMLElement,
		     p: BSTR

	  put_text57@MP typedef ptr put_text57@CT
	       put_text put_text57@MP ?

	  addChild57@CT typedef proto \
		 pThis: ptr IXMLElement,
	    pChildElem: ptr IXMLElement,
		lIndex: LONG,
	     lReserved: LONG

	  addChild57@MP typedef ptr addChild57@CT
	       addChild addChild57@MP ?

       removeChild57@CT typedef proto \
		 pThis: ptr IXMLElement,
	    pChildElem: ptr IXMLElement

       removeChild57@MP typedef ptr removeChild57@CT
	    removeChild removeChild57@MP ?

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

    QueryInterface58@CT typedef proto \
		 pThis: ptr IXMLError,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface58@MP typedef ptr QueryInterface58@CT
	 QueryInterface QueryInterface58@MP ?

	    AddRef58@CT typedef proto \
		 pThis: ptr IXMLError

	    AddRef58@MP typedef ptr AddRef58@CT
		 AddRef AddRef58@MP ?

	   Release58@CT typedef proto \
		 pThis: ptr IXMLError

	   Release58@MP typedef ptr Release58@CT
		Release Release58@MP ?

      GetErrorInfo58@CT typedef proto \
		 pThis: ptr IXMLError,
	  pErrorReturn: ptr XML_ERROR

      GetErrorInfo58@MP typedef ptr GetErrorInfo58@CT
	   GetErrorInfo GetErrorInfo58@MP ?

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

    QueryInterface59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface59@MP typedef ptr QueryInterface59@CT
	 QueryInterface QueryInterface59@MP ?

	    AddRef59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink

	    AddRef59@MP typedef ptr AddRef59@CT
		 AddRef AddRef59@MP ?

	   Release59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink

	   Release59@MP typedef ptr Release59@CT
		Release Release59@MP ?

  GetTypeInfoCount59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink,
	       pctinfo: ptr UINT

  GetTypeInfoCount59@MP typedef ptr GetTypeInfoCount59@CT
       GetTypeInfoCount GetTypeInfoCount59@MP ?

       GetTypeInfo59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink,
		iTInfo: UINT,
		  lcid: LCID,
	       ppTInfo: ptr ITypeInfo

       GetTypeInfo59@MP typedef ptr GetTypeInfo59@CT
	    GetTypeInfo GetTypeInfo59@MP ?

     GetIDsOfNames59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink,
		  riid: REFIID,
	     rgszNames: ptr LPOLESTR,
		cNames: UINT,
		  lcid: LCID,
	      rgDispId: ptr DISPID

     GetIDsOfNames59@MP typedef ptr GetIDsOfNames59@CT
	  GetIDsOfNames GetIDsOfNames59@MP ?

	    Invoke59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink,
	  dispIdMember: DISPID,
		  riid: REFIID,
		  lcid: LCID,
		wFlags: WORD,
	   pDispParams: ptr DISPPARAMS,
	    pVarResult: ptr VARIANT,
	    pExcepInfo: ptr EXCEPINFO,
	      puArgErr: ptr UINT

	    Invoke59@MP typedef ptr Invoke59@CT
		_Invoke Invoke59@MP ?

	ChildAdded59@CT typedef proto \
		 pThis: ptr IXMLElementNotificationSink,
	    pChildElem: ptr IDispatch

	ChildAdded59@MP typedef ptr ChildAdded59@CT
	     ChildAdded ChildAdded59@MP ?

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
