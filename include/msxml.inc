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

.enum DOMNodeType {
    NODE_INVALID	= 0,
    NODE_ELEMENT	= ( NODE_INVALID + 1 ),
    NODE_ATTRIBUTE	= ( NODE_ELEMENT + 1 ),
    NODE_TEXT		= ( NODE_ATTRIBUTE + 1 ),
    NODE_CDATA_SECTION	= ( NODE_TEXT + 1 ),
    NODE_ENTITY_REFERENCE = ( NODE_CDATA_SECTION + 1 ),
    NODE_ENTITY		= ( NODE_ENTITY_REFERENCE + 1 ),
    NODE_PROCESSING_INSTRUCTION = ( NODE_ENTITY + 1 ),
    NODE_COMMENT	= ( NODE_PROCESSING_INSTRUCTION + 1 ),
    NODE_DOCUMENT	= ( NODE_COMMENT + 1 ),
    NODE_DOCUMENT_TYPE	= ( NODE_DOCUMENT + 1 ),
    NODE_DOCUMENT_FRAGMENT = ( NODE_DOCUMENT_TYPE + 1 ),
    NODE_NOTATION	= ( NODE_DOCUMENT_FRAGMENT + 1 )
}

.enum XMLEMEM_TYPE {
    XMLELEMTYPE_ELEMENT = 0,
    XMLELEMTYPE_TEXT	= ( XMLELEMTYPE_ELEMENT + 1 ),
    XMLELEMTYPE_COMMENT = ( XMLELEMTYPE_TEXT + 1 ),
    XMLELEMTYPE_DOCUMENT = ( XMLELEMTYPE_COMMENT + 1 ),
    XMLELEMTYPE_DTD	= ( XMLELEMTYPE_DOCUMENT + 1 ),
    XMLELEMTYPE_PI	= ( XMLELEMTYPE_DTD + 1 ),
    XMLELEMTYPE_OTHER	= ( XMLELEMTYPE_PI + 1 )
}

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

externdef LIBID_MSXML:IID

ifndef __IXMLDOMImplementation_INTERFACE_DEFINED__
__IXMLDOMImplementation_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMImplementation, "2933BF8F-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMImplementation : public IDispatch

    hasFeature		proc :BSTR, :BSTR, :ptr VARIANT_BOOL
    .ends
endif

ifndef __IXMLDOMNode_INTERFACE_DEFINED__
__IXMLDOMNode_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMNode, "2933BF80-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNode : public IDispatch

    get_nodeName	proc :ptr BSTR
    get_nodeValue	proc :ptr VARIANT
    put_nodeValue	proc :VARIANT
    get_nodeType	proc :ptr DOMNodeType
    get_parentNode	proc :ptr ptr
    get_childNodes	proc :ptr ptr IXMLDOMNodeList
    get_firstChild	proc :ptr ptr IXMLDOMNode
    get_lastChild	proc :ptr ptr IXMLDOMNode
    get_previousSibling proc :ptr ptr IXMLDOMNode
    get_nextSibling	proc :ptr ptr IXMLDOMNode
    get_attributes	proc :ptr ptr IXMLDOMNamedNodeMap
    insertBefore	proc :ptr IXMLDOMNode, :VARIANT, :ptr ptr IXMLDOMNode
    replaceChild	proc :ptr IXMLDOMNode, :ptr IXMLDOMNode, :ptr ptr IXMLDOMNode
    removeChild		proc :ptr IXMLDOMNode, :ptr ptr IXMLDOMNode
    appendChild		proc :ptr IXMLDOMNode, :ptr ptr IXMLDOMNode
    hasChildNodes	proc :ptr VARIANT_BOOL
    get_ownerDocument	proc :ptr ptr IXMLDOMDocument
    cloneNode		proc :VARIANT_BOOL, :ptr ptr IXMLDOMNode
    get_nodeTypeString	proc :ptr BSTR
    get_text		proc :ptr BSTR
    put_text		proc :BSTR
    get_specified	proc :ptr VARIANT_BOOL
    get_definition	proc :ptr ptr IXMLDOMNode
    get_nodeTypedValue	proc :ptr VARIANT
    put_nodeTypedValue	proc :VARIANT
    get_dataType	proc :ptr VARIANT
    put_dataType	proc :BSTR
    get_xml		proc :ptr BSTR
    transformNode	proc :ptr IXMLDOMNode, :ptr BSTR
    selectNodes		proc :BSTR, :ptr ptr IXMLDOMNodeList
    selectSingleNode	proc :BSTR, :ptr ptr IXMLDOMNode
    get_parsed		proc :ptr VARIANT_BOOL
    get_namespaceURI	proc :ptr BSTR
    get_prefix		proc :ptr BSTR
    get_baseName	proc :ptr BSTR
    transformNodeToObject proc :ptr IXMLDOMNode, :VARIANT

    .ends
endif

ifndef __IXMLDOMDocumentFragment_INTERFACE_DEFINED__
__IXMLDOMDocumentFragment_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMDocumentFragment, "3efaa413-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMDocumentFragment : public IXMLDOMNode

    .ends
endif

ifndef __IXMLDOMDocument_INTERFACE_DEFINED__
__IXMLDOMDocument_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMDocument, "2933BF81-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocument : public IXMLDOMNode

    get_doctype			proc :ptr ptr IXMLDOMDocumentType
    get_implementation		proc :ptr ptr IXMLDOMImplementation
    get_documentElement		proc :ptr ptr IXMLDOMElement
    putref_documentElement	proc :ptr IXMLDOMElement
    createElement		proc :BSTR, :ptr ptr IXMLDOMElement
    createDocumentFragment	proc :ptr ptr IXMLDOMDocumentFragment
    createTextNode		proc :BSTR, :ptr ptr IXMLDOMText
    createComment		proc :BSTR, :ptr ptr IXMLDOMComment
    createCDATASection		proc :BSTR, :ptr ptr IXMLDOMCDATASection
    createProcessingInstruction proc :BSTR, :BSTR, :ptr ptr IXMLDOMProcessingInstruction
    createAttribute		proc :BSTR, :ptr ptr IXMLDOMAttribute
    createEntityReference	proc :BSTR, :ptr ptr IXMLDOMEntityReference
    getElementsByTagName	proc :BSTR, :ptr ptr IXMLDOMNodeList
    createNode			proc :VARIANT,	:BSTR, :BSTR, :ptr ptr IXMLDOMNode
    nodeFromID			proc :BSTR,  :ptr ptr IXMLDOMNode
    load			proc :VARIANT, :ptr VARIANT_BOOL
    get_readyState		proc :ptr
    get_parseError		proc :ptr ptr IXMLDOMParseError
    get_url			proc :ptr BSTR
    get_async			proc :ptr VARIANT_BOOL
    put_async			proc :VARIANT_BOOL
    abort			proc
    loadXML			proc :BSTR, :ptr VARIANT_BOOL
    save			proc :VARIANT
    get_validateOnParse		proc :ptr VARIANT_BOOL
    put_validateOnParse		proc :VARIANT_BOOL
    get_resolveExternals	proc :ptr VARIANT_BOOL
    put_resolveExternals	proc :VARIANT_BOOL
    get_preserveWhiteSpace	proc :ptr VARIANT_BOOL
    put_preserveWhiteSpace	proc :VARIANT_BOOL
    put_onreadystatechange	proc :VARIANT
    put_ondataavailable		proc :VARIANT
    put_ontransformnode		proc :VARIANT

    .ends
endif

ifndef __IXMLDOMNodeList_INTERFACE_DEFINED__
__IXMLDOMNodeList_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMNodeList, "2933BF82-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNodeList : public IDispatch

    get_item		proc :sdword, :ptr ptr IXMLDOMNode
    get_length		proc :ptr
    nextNode		proc :ptr ptr IXMLDOMNode
    reset		proc
    get__newEnum	proc :ptr ptr IUnknown

    .ends
endif

ifndef __IXMLDOMNamedNodeMap_INTERFACE_DEFINED__
__IXMLDOMNamedNodeMap_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMNamedNodeMap, "2933BF83-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNamedNodeMap : public IDispatch

    getNamedItem	proc :BSTR, :ptr ptr IXMLDOMNode
    setNamedItem	proc :ptr IXMLDOMNode, :ptr ptr IXMLDOMNode
    removeNamedItem	proc :BSTR, :ptr ptr IXMLDOMNode
    get_item		proc :sdword, :ptr ptr IXMLDOMNode
    get_length		proc :ptr
    getQualifiedItem	proc :BSTR, :BSTR, :ptr ptr IXMLDOMNode
    removeQualifiedItem proc :BSTR, :BSTR, :ptr ptr IXMLDOMNode
    nextNode		proc :ptr ptr IXMLDOMNode
    reset		proc
    get__newEnum	proc :ptr ptr IUnknown

    .ends
endif

ifndef __IXMLDOMCharacterData_INTERFACE_DEFINED__
__IXMLDOMCharacterData_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMCharacterData, "2933BF84-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMCharacterData : public IXMLDOMNode

    get_data		proc :ptr BSTR
    put_data		proc :BSTR
    get_length		proc :ptr
    substringData	proc :sdword, :sdword, :ptr BSTR
    appendData		proc :BSTR
    insertData		proc :sdword, :BSTR
    deleteData		proc :sdword, :sdword
    replaceData		proc :sdword, :sdword, :BSTR

    .ends
endif

ifndef __IXMLDOMAttribute_INTERFACE_DEFINED__
__IXMLDOMAttribute_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMAttribute, "2933BF85-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMAttribute : public IXMLDOMNode

    get_name		proc :ptr BSTR
    get_value		proc :ptr VARIANT
    put_value		proc :VARIANT

    .ends
endif

ifndef __IXMLDOMElement_INTERFACE_DEFINED__
__IXMLDOMElement_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMElement, "2933BF86-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMElement : public IXMLDOMNode

    get_tagName		 proc :ptr BSTR
    getAttribute	 proc :BSTR, :ptr VARIANT
    setAttribute	 proc :BSTR, :VARIANT
    removeAttribute	 proc :BSTR
    getAttributeNode	 proc :BSTR, :ptr ptr IXMLDOMAttribute
    setAttributeNode	 proc :ptr IXMLDOMAttribute, :ptr ptr IXMLDOMAttribute
    removeAttributeNode	 proc :ptr IXMLDOMAttribute, :ptr ptr IXMLDOMAttribute
    getElementsByTagName proc :BSTR, :ptr ptr IXMLDOMNodeList
    normalize		 proc

    .ends
endif

ifndef __IXMLDOMText_INTERFACE_DEFINED__
__IXMLDOMText_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMText, "2933BF87-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMText : public IXMLDOMCharacterData

    splitText		proc :LONG, :ptr ptr IXMLDOMText

    .ends
endif

ifndef __IXMLDOMComment_INTERFACE_DEFINED__
__IXMLDOMComment_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMComment, "2933BF88-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMComment : public IXMLDOMCharacterData

    .ends
endif

ifndef __IXMLDOMProcessingInstruction_INTERFACE_DEFINED__
__IXMLDOMProcessingInstruction_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMProcessingInstruction, "2933BF89-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMProcessingInstruction : public IXMLDOMNode

    get_target		proc :ptr BSTR
    get_data		proc :ptr BSTR
    put_data		proc :BSTR

    .ends
endif

ifndef __IXMLDOMCDATASection_INTERFACE_DEFINED__
__IXMLDOMCDATASection_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMCDATASection, "2933BF8A-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMCDATASection : public IXMLDOMText

    .ends
endif

ifndef __IXMLDOMDocumentType_INTERFACE_DEFINED__
__IXMLDOMDocumentType_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMDocumentType, "2933BF8B-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocumentType : public IXMLDOMNode

    get_name		proc :ptr BSTR
    get_entities	proc :ptr ptr IXMLDOMNamedNodeMap
    get_notations	proc :ptr ptr IXMLDOMNamedNodeMap

    .ends
endif

ifndef __IXMLDOMNotation_INTERFACE_DEFINED__
__IXMLDOMNotation_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMNotation, "2933BF8C-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNotation : public IXMLDOMNode

    get_publicId	proc :ptr VARIANT
    get_systemId	proc :ptr VARIANT

    .ends
endif

ifndef __IXMLDOMEntity_INTERFACE_DEFINED__
__IXMLDOMEntity_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMEntity, "2933BF8D-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMEntity : public IXMLDOMNode

    get_publicId	proc :ptr VARIANT
    get_systemId	proc :ptr VARIANT
    get_notationName	proc :ptr BSTR

    .ends
endif

ifndef __IXMLDOMEntityReference_INTERFACE_DEFINED__
__IXMLDOMEntityReference_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMEntityReference, "2933BF8E-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMEntityReference : public IXMLDOMNode

    .ends
endif

ifndef __IXMLDOMParseError_INTERFACE_DEFINED__
__IXMLDOMParseError_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDOMParseError, "3efaa426-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMParseError : public IDispatch

    get_errorCode	proc :ptr LONG
    get_url		proc :ptr BSTR
    get_reason		proc :ptr BSTR
    get_srcText		proc :ptr BSTR
    get_line		proc :ptr LONG
    get_linepos		proc :ptr LONG
    get_filepos		proc :ptr LONG

    .ends
endif

ifndef __IXTLRuntime_INTERFACE_DEFINED__
__IXTLRuntime_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXTLRuntime, "3efaa425-272f-11d2-836f-0000f87a7782")

.comdef IXTLRuntime : public IXMLDOMNode

    uniqueID		proc :ptr IXMLDOMNode, :ptr LONG
    depth		proc :ptr IXMLDOMNode, :ptr LONG
    childNumber		proc :ptr IXMLDOMNode, :ptr LONG
    ancestorChildNumber proc :BSTR, :ptr IXMLDOMNode, :ptr LONG
    absoluteChildNumber proc :ptr IXMLDOMNode, :ptr LONG
    formatIndex		proc :LONG, :BSTR, :ptr BSTR
    formatNumber	proc :real8, :BSTR, :ptr BSTR
    formatDate		proc :VARIANT, :BSTR, :VARIANT, :ptr BSTR
    formatTime		proc :VARIANT, :BSTR, :VARIANT, :ptr BSTR

    .ends
endif

ifndef __IXMLElementCollection_INTERFACE_DEFINED__
__IXMLElementCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLElementCollection, "65725580-9B5D-11d0-9BFE-00C04FC99C8E")

.comdef IXMLElementCollection : public IDispatch

    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr, :ptr

    .ends
endif

ifndef __XMLDOMDocumentEvents_DISPINTERFACE_DEFINED__
__XMLDOMDocumentEvents_DISPINTERFACE_DEFINED__ equ <>

DEFINE_IIDX(XMLDOMDocumentEvents, "3efaa427-272f-11d2-836f-0000f87a7782")

.comdef XMLDOMDocumentEvents : public IDispatch

    .ends
endif

ifndef __IXMLHttpRequest_INTERFACE_DEFINED__
__IXMLHttpRequest_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLHttpRequest, "ED8C108D-4349-11D2-91A4-00C04F7969E8")

.comdef IXMLHttpRequest : public IDispatch

    open		proc :BSTR, :BSTR, :VARIANT, :VARIANT, :VARIANT
    setRequestHeader	proc :BSTR, :BSTR
    getResponseHeader	proc :BSTR, :ptr BSTR
    getAllResponseHeaders proc :ptr BSTR
    send		proc :VARIANT
    abort		proc
    get_status		proc :ptr LONG
    get_statusText	proc :ptr BSTR
    get_responseXML	proc :ptr ptr IDispatch
    get_responseText	proc :ptr BSTR
    get_responseBody	proc :ptr VARIANT
    get_responseStream	proc :ptr VARIANT
    get_readyState	proc :ptr
    put_onreadystatechange proc :ptr IDispatch

    .ends
endif

ifndef __IXMLDSOControl_INTERFACE_DEFINED__
__IXMLDSOControl_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXMLDSOControl, "310afa62-0575-11d2-9ca9-0060b0ec3d39")

.comdef IXMLDSOControl : public IDispatch

    get_XMLDocument	proc :ptr ptr IXMLDOMDocument
    put_XMLDocument	proc :ptr MLDOMDocument
    get_JavaDSOCompatible proc :ptr BOOL
    put_JavaDSOCompatible proc :BOOL
    get_readyState	proc :ptr LONG

    .ends
endif

ifndef __IXMLDocument_INTERFACE_DEFINED__
__IXMLDocument_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDocument, "F52E2B61-18A1-11d1-B105-00805F49916B")

.comdef IXMLDocument : public IDispatch

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

.comdef IXMLElement : public IDispatch

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

.comdef IXMLError : public IUnknown

    GetErrorInfo	proc :ptr

    .ends
endif


ifndef __IXMLElementNotificationSink_INTERFACE_DEFINED__
__IXMLElementNotificationSink_INTERFACE_DEFINED__ equ 1

externdef IID_IXMLElementNotificationSink:IID

.comdef IXMLElementNotificationSink : public IUnknown

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
