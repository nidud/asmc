include rpc.inc
include rpcndr.inc
ifndef __msxml_h__
define __msxml_h__

include unknwn.inc
include objidl.inc
include oaidl.inc

;void *
MIDL_user_allocate proto WINAPI :size_t
;void
MIDL_user_free proto WINAPI :PVOID

ifndef __MSXML_LIBRARY_DEFINED__
define __MSXML_LIBRARY_DEFINED__

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
define __IXMLDOMImplementation_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMImplementation, "2933BF8F-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMImplementation : public IDispatch

    hasFeature		proc :BSTR, :BSTR, :ptr
   .ends
endif

ifndef __IXMLDOMNode_INTERFACE_DEFINED__
define __IXMLDOMNode_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMNode, "2933BF80-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNode : public IDispatch

    get_nodeName	proc :ptr
    get_nodeValue	proc :ptr
    put_nodeValue	proc :VARIANT
    get_nodeType	proc :ptr
    get_parentNode	proc :ptr
    get_childNodes	proc :ptr
    get_firstChild	proc :ptr
    get_lastChild	proc :ptr
    get_previousSibling proc :ptr
    get_nextSibling	proc :ptr
    get_attributes	proc :ptr
    insertBefore	proc :ptr, :VARIANT, :ptr
    replaceChild	proc :ptr, :ptr, :ptr
    removeChild		proc :ptr, :ptr
    appendChild		proc :ptr, :ptr
    hasChildNodes	proc :ptr
    get_ownerDocument	proc :ptr
    cloneNode		proc :VARIANT_BOOL, :ptr
    get_nodeTypeString	proc :ptr
    get_text		proc :ptr
    put_text		proc :BSTR
    get_specified	proc :ptr
    get_definition	proc :ptr
    get_nodeTypedValue	proc :ptr
    put_nodeTypedValue	proc :VARIANT
    get_dataType	proc :ptr
    put_dataType	proc :BSTR
    get_xml		proc :ptr
    transformNode	proc :ptr, :ptr
    selectNodes		proc :BSTR, :ptr
    selectSingleNode	proc :BSTR, :ptr
    get_parsed		proc :ptr
    get_namespaceURI	proc :ptr
    get_prefix		proc :ptr
    get_baseName	proc :ptr
    transformNodeToObject proc :ptr, :VARIANT
   .ends
endif

ifndef __IXMLDOMDocumentFragment_INTERFACE_DEFINED__
define __IXMLDOMDocumentFragment_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMDocumentFragment, "3efaa413-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMDocumentFragment : public IXMLDOMNode

    .ends
endif

ifndef __IXMLDOMDocument_INTERFACE_DEFINED__
define __IXMLDOMDocument_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMDocument, "2933BF81-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocument : public IXMLDOMNode

    get_doctype			proc :ptr
    get_implementation		proc :ptr
    get_documentElement		proc :ptr
    putref_documentElement	proc :ptr
    createElement		proc :BSTR, :ptr
    createDocumentFragment	proc :ptr
    createTextNode		proc :BSTR, :ptr
    createComment		proc :BSTR, :ptr
    createCDATASection		proc :BSTR, :ptr
    createProcessingInstruction proc :BSTR, :BSTR, :ptr
    createAttribute		proc :BSTR, :ptr
    createEntityReference	proc :BSTR, :ptr
    getElementsByTagName	proc :BSTR, :ptr
    createNode			proc :VARIANT,	:BSTR, :BSTR, :ptr
    nodeFromID			proc :BSTR,  :ptr
    load			proc :VARIANT, :ptr
    get_readyState		proc :ptr
    get_parseError		proc :ptr
    get_url			proc :ptr
    get_async			proc :ptr
    put_async			proc :VARIANT_BOOL
    abort			proc
    loadXML			proc :BSTR, :ptr
    save			proc :VARIANT
    get_validateOnParse		proc :ptr
    put_validateOnParse		proc :VARIANT_BOOL
    get_resolveExternals	proc :ptr
    put_resolveExternals	proc :VARIANT_BOOL
    get_preserveWhiteSpace	proc :ptr
    put_preserveWhiteSpace	proc :VARIANT_BOOL
    put_onreadystatechange	proc :VARIANT
    put_ondataavailable		proc :VARIANT
    put_ontransformnode		proc :VARIANT
   .ends
endif

ifndef __IXMLDOMNodeList_INTERFACE_DEFINED__
define __IXMLDOMNodeList_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMNodeList, "2933BF82-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNodeList : public IDispatch

    get_item		proc :sdword, :ptr
    get_length		proc :ptr
    nextNode		proc :ptr
    reset		proc
    get__newEnum	proc :ptr
   .ends
endif

ifndef __IXMLDOMNamedNodeMap_INTERFACE_DEFINED__
define __IXMLDOMNamedNodeMap_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMNamedNodeMap, "2933BF83-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNamedNodeMap : public IDispatch

    getNamedItem	proc :BSTR, :ptr
    setNamedItem	proc :ptr, :ptr
    removeNamedItem	proc :BSTR, :ptr
    get_item		proc :sdword, :ptr
    get_length		proc :ptr
    getQualifiedItem	proc :BSTR, :BSTR, :ptr
    removeQualifiedItem proc :BSTR, :BSTR, :ptr
    nextNode		proc :ptr
    reset		proc
    get__newEnum	proc :ptr
   .ends
endif

ifndef __IXMLDOMCharacterData_INTERFACE_DEFINED__
define __IXMLDOMCharacterData_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMCharacterData, "2933BF84-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMCharacterData : public IXMLDOMNode

    get_data		proc :ptr
    put_data		proc :BSTR
    get_length		proc :ptr
    substringData	proc :sdword, :sdword, :ptr
    appendData		proc :BSTR
    insertData		proc :sdword, :BSTR
    deleteData		proc :sdword, :sdword
    replaceData		proc :sdword, :sdword, :BSTR
   .ends
endif

ifndef __IXMLDOMAttribute_INTERFACE_DEFINED__
define __IXMLDOMAttribute_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMAttribute, "2933BF85-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMAttribute : public IXMLDOMNode

    get_name		proc :ptr
    get_value		proc :ptr
    put_value		proc :VARIANT
   .ends
endif

ifndef __IXMLDOMElement_INTERFACE_DEFINED__
define __IXMLDOMElement_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMElement, "2933BF86-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMElement : public IXMLDOMNode

    get_tagName		 proc :ptr
    getAttribute	 proc :BSTR, :ptr
    setAttribute	 proc :BSTR, :VARIANT
    removeAttribute	 proc :BSTR
    getAttributeNode	 proc :BSTR, :ptr
    setAttributeNode	 proc :ptr, :ptr
    removeAttributeNode	 proc :ptr, :ptr
    getElementsByTagName proc :BSTR, :ptr
    normalize		 proc
   .ends
endif

ifndef __IXMLDOMText_INTERFACE_DEFINED__
define __IXMLDOMText_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMText, "2933BF87-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMText : public IXMLDOMCharacterData

    splitText		proc :LONG, :ptr
   .ends
endif

ifndef __IXMLDOMComment_INTERFACE_DEFINED__
define __IXMLDOMComment_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMComment, "2933BF88-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMComment : public IXMLDOMCharacterData

    .ends
endif

ifndef __IXMLDOMProcessingInstruction_INTERFACE_DEFINED__
define __IXMLDOMProcessingInstruction_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMProcessingInstruction, "2933BF89-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMProcessingInstruction : public IXMLDOMNode

    get_target		proc :ptr
    get_data		proc :ptr
    put_data		proc :BSTR
   .ends
endif

ifndef __IXMLDOMCDATASection_INTERFACE_DEFINED__
define __IXMLDOMCDATASection_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMCDATASection, "2933BF8A-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMCDATASection : public IXMLDOMText

    .ends
endif

ifndef __IXMLDOMDocumentType_INTERFACE_DEFINED__
define __IXMLDOMDocumentType_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMDocumentType, "2933BF8B-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocumentType : public IXMLDOMNode

    get_name		proc :ptr
    get_entities	proc :ptr
    get_notations	proc :ptr
   .ends
endif

ifndef __IXMLDOMNotation_INTERFACE_DEFINED__
define __IXMLDOMNotation_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMNotation, "2933BF8C-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNotation : public IXMLDOMNode

    get_publicId	proc :ptr
    get_systemId	proc :ptr
   .ends
endif

ifndef __IXMLDOMEntity_INTERFACE_DEFINED__
define __IXMLDOMEntity_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMEntity, "2933BF8D-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMEntity : public IXMLDOMNode

    get_publicId	proc :ptr
    get_systemId	proc :ptr
    get_notationName	proc :ptr
   .ends
endif

ifndef __IXMLDOMEntityReference_INTERFACE_DEFINED__
define __IXMLDOMEntityReference_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMEntityReference, "2933BF8E-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMEntityReference : public IXMLDOMNode

    .ends
endif

ifndef __IXMLDOMParseError_INTERFACE_DEFINED__
define __IXMLDOMParseError_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDOMParseError, "3efaa426-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMParseError : public IDispatch

    get_errorCode	proc :ptr
    get_url		proc :ptr
    get_reason		proc :ptr
    get_srcText		proc :ptr
    get_line		proc :ptr
    get_linepos		proc :ptr
    get_filepos		proc :ptr
   .ends
endif

ifndef __IXTLRuntime_INTERFACE_DEFINED__
define __IXTLRuntime_INTERFACE_DEFINED__

DEFINE_IIDX(IXTLRuntime, "3efaa425-272f-11d2-836f-0000f87a7782")

.comdef IXTLRuntime : public IXMLDOMNode

    uniqueID		proc :ptr, :ptr
    depth		proc :ptr, :ptr
    childNumber		proc :ptr, :ptr
    ancestorChildNumber proc :BSTR, :ptr, :ptr
    absoluteChildNumber proc :ptr, :ptr
    formatIndex		proc :LONG, :BSTR, :ptr
    formatNumber	proc :real8, :BSTR, :ptr
    formatDate		proc :VARIANT, :BSTR, :VARIANT, :ptr
    formatTime		proc :VARIANT, :BSTR, :VARIANT, :ptr
   .ends
endif

ifndef __IXMLElementCollection_INTERFACE_DEFINED__
define __IXMLElementCollection_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLElementCollection, "65725580-9B5D-11d0-9BFE-00C04FC99C8E")

.comdef IXMLElementCollection : public IDispatch

    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr, :ptr
   .ends
endif

ifndef __XMLDOMDocumentEvents_DISPINTERFACE_DEFINED__
define __XMLDOMDocumentEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(XMLDOMDocumentEvents, "3efaa427-272f-11d2-836f-0000f87a7782")

.comdef XMLDOMDocumentEvents : public IDispatch

    .ends
endif

ifndef __IXMLHttpRequest_INTERFACE_DEFINED__
define __IXMLHttpRequest_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLHttpRequest, "ED8C108D-4349-11D2-91A4-00C04F7969E8")

.comdef IXMLHttpRequest : public IDispatch

    open		proc :BSTR, :BSTR, :VARIANT, :VARIANT, :VARIANT
    setRequestHeader	proc :BSTR, :BSTR
    getResponseHeader	proc :BSTR, :ptr
    getAllResponseHeaders proc :ptr
    send		proc :VARIANT
    abort		proc
    get_status		proc :ptr
    get_statusText	proc :ptr
    get_responseXML	proc :ptr
    get_responseText	proc :ptr
    get_responseBody	proc :ptr
    get_responseStream	proc :ptr
    get_readyState	proc :ptr
    put_onreadystatechange proc :ptr
   .ends

endif

ifndef __IXMLDSOControl_INTERFACE_DEFINED__
define __IXMLDSOControl_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLDSOControl, "310afa62-0575-11d2-9ca9-0060b0ec3d39")

.comdef IXMLDSOControl : public IDispatch

    get_XMLDocument	proc :ptr
    put_XMLDocument	proc :ptr
    get_JavaDSOCompatible proc :ptr
    put_JavaDSOCompatible proc :BOOL
    get_readyState	proc :ptr
   .ends
endif

ifndef __IXMLDocument_INTERFACE_DEFINED__
define __IXMLDocument_INTERFACE_DEFINED__

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
define __IXMLElement_INTERFACE_DEFINED__

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
define __IXMLError_INTERFACE_DEFINED__

DEFINE_IIDX(IXMLError, "948C5AD3-C58D-11d0-9C0B-00C04FC99C8E")

.comdef IXMLError : public IUnknown

    GetErrorInfo	proc :ptr
   .ends
endif


ifndef __IXMLElementNotificationSink_INTERFACE_DEFINED__
define __IXMLElementNotificationSink_INTERFACE_DEFINED__

externdef IID_IXMLElementNotificationSink:IID

.comdef IXMLElementNotificationSink : public IDispatch

    ChildAdded		proc :ptr
   .ends

endif
DEFINE_GUIDS(CLSID_XMLDocument, "CFC399AF-D876-11d0-9C10-00C04FC99C8E")
endif

endif
