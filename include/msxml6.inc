ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __msxml6_h__
define __msxml6_h__

include unknwn.inc
include objidl.inc
include oaidl.inc
include winapifamily.inc

ifdef _WIN64
ULONG_PTR typedef qword
PULONG_PTR typedef ptr qword
else
ULONG_PTR typedef dword
PULONG_PTR typedef ptr dword
endif

ifdef __ISAXXMLReader_INTERFACE_DEFINED__
undef __MSXML2_LIBRARY_DEFINED__
endif

ifdef __USE_MSXML6_NAMESPACE__
endif


if NOT defined(__msxml_h__) OR defined(__IXMLElementNotificationSink_INTERFACE_DEFINED__) \
   OR (WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) AND \
   NOT WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP))

.enum DOMNodeType {
    NODE_INVALID	= 0,
    NODE_ELEMENT	= ( NODE_INVALID + 1 ) ,
    NODE_ATTRIBUTE	= ( NODE_ELEMENT + 1 ) ,
    NODE_TEXT		= ( NODE_ATTRIBUTE + 1 ) ,
    NODE_CDATA_SECTION	= ( NODE_TEXT + 1 ) ,
    NODE_ENTITY_REFERENCE = ( NODE_CDATA_SECTION + 1 ) ,
    NODE_ENTITY		= ( NODE_ENTITY_REFERENCE + 1 ) ,
    NODE_PROCESSING_INSTRUCTION = ( NODE_ENTITY + 1 ) ,
    NODE_COMMENT	= ( NODE_PROCESSING_INSTRUCTION + 1 ) ,
    NODE_DOCUMENT	= ( NODE_COMMENT + 1 ) ,
    NODE_DOCUMENT_TYPE	= ( NODE_DOCUMENT + 1 ) ,
    NODE_DOCUMENT_FRAGMENT = ( NODE_DOCUMENT_TYPE + 1 ) ,
    NODE_NOTATION	= ( NODE_DOCUMENT_FRAGMENT + 1 )
    }

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IXMLDOMNode_INTERFACE_DEFINED__
__IXMLDOMNode_INTERFACE_DEFINED__ equ 1

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

ifndef __IXMLDOMDocument_INTERFACE_DEFINED__
__IXMLDOMDocument_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMDocument, "2933BF81-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocument : public IXMLDOMNode

    get_doctype		proc :ptr
    get_implementation	proc :ptr
    get_documentElement proc :ptr
    putref_documentElement proc :ptr
    createElement	proc :BSTR, :ptr
    createDocumentFragment proc :ptr
    createTextNode	proc :BSTR, :ptr
    createComment	proc :BSTR, :ptr
    createCDATASection	proc :BSTR, :ptr
    createProcessingInstruction proc :BSTR, :BSTR, :ptr
    createAttribute	proc :BSTR, :ptr
    createEntityReference proc :BSTR, :ptr
    getElementsByTagName proc :BSTR, :ptr
    createNode		proc :VARIANT, :BSTR, :BSTR, :ptr
    nodeFromID		proc :BSTR, :ptr
    load		proc :VARIANT, :ptr
    get_readyState	proc :ptr
    get_parseError	proc :ptr
    get_url		proc :ptr
    get_async		proc :ptr
    put_async		proc :VARIANT_BOOL
    abort		proc
    loadXML		proc :BSTR, :ptr
    save		proc :VARIANT
    get_validateOnParse proc :ptr
    put_validateOnParse proc :VARIANT_BOOL
    get_resolveExternals proc :ptr
    put_resolveExternals proc :VARIANT_BOOL
    get_preserveWhiteSpace proc :ptr
    put_preserveWhiteSpace proc :VARIANT_BOOL
    put_onreadystatechange proc :VARIANT
    put_ondataavailable proc :VARIANT
    put_ontransformnode proc :VARIANT
    .ends

endif

ifndef __IXMLDOMDocument2_INTERFACE_DEFINED__
__IXMLDOMDocument2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMDocument2, "2933BF95-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocument2 : public IXMLDOMDocument

    get_namespaces	proc :ptr
    get_schemas		proc :ptr
    putref_schemas	proc :VARIANT
    validate		proc :ptr
    setProperty		proc :BSTR, :VARIANT
    getProperty		proc :BSTR, :ptr
    .ends

endif

ifndef __IXMLDOMDocument3_INTERFACE_DEFINED__
__IXMLDOMDocument3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMDocument3, "2933BF96-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocument3 : public IXMLDOMDocument2

    validateNode	proc :ptr, :ptr
    importNode		proc :ptr, :VARIANT_BOOL, :ptr
    .ends

endif

ifndef __IXMLDOMSchemaCollection_INTERFACE_DEFINED__
__IXMLDOMSchemaCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMSchemaCollection, "373984c8-b845-449b-91e7-45ac83036ade")

.comdef IXMLDOMSchemaCollection : public IDispatch

    _add		proc :BSTR, :VARIANT
    get			proc :BSTR, :ptr
    remove		proc :BSTR
    get_length		proc :ptr
    get_namespaceURI	proc :LONG, :ptr
    addCollection	proc :ptr
    get__newEnum	proc :ptr
    .ends

endif

ifndef __IXMLDOMNodeList_INTERFACE_DEFINED__
__IXMLDOMNodeList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMNodeList, "2933BF82-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNodeList : public IDispatch

    get_item		proc :long, :ptr
    get_length		proc :ptr
    nextNode		proc :ptr
    reset		proc
    get__newEnum	proc :ptr
    .ends

endif

ifndef __IXMLDOMSelection_INTERFACE_DEFINED__
__IXMLDOMSelection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMSelection, "AA634FC7-5888-44a7-A257-3A47150D3A0E")

.comdef IXMLDOMSelection : public IXMLDOMNodeList

    get_expr		proc :ptr
    put_expr		proc :BSTR
    get_context		proc :ptr
    putref_context	proc :ptr
    peekNode		proc :ptr
    matches		proc :ptr, :ptr
    removeNext		proc :ptr
    removeAll		proc
    clone		proc :ptr
    getProperty		proc :BSTR, :ptr
    setProperty		proc :BSTR, :VARIANT
    .ends

endif

ifndef __IXMLDOMNamedNodeMap_INTERFACE_DEFINED__
__IXMLDOMNamedNodeMap_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMNamedNodeMap, "2933BF83-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNamedNodeMap : public IDispatch

    getNamedItem	proc :BSTR, :ptr
    setNamedItem	proc :ptr, :ptr
    removeNamedItem	proc :BSTR, :ptr
    get_item		proc :long, :ptr
    get_length		proc :ptr
    getQualifiedItem	proc :BSTR, :BSTR, :ptr
    removeQualifiedItem proc :BSTR, :BSTR, :ptr
    nextNode		proc :ptr
    reset		proc
    get__newEnum	proc :ptr
    .ends

endif

ifndef __IXMLDOMDocumentFragment_INTERFACE_DEFINED__
__IXMLDOMDocumentFragment_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMDocumentFragment, "3efaa413-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMDocumentFragment : public IXMLDOMNode

    .ends

endif

ifndef __IXMLDOMCharacterData_INTERFACE_DEFINED__
__IXMLDOMCharacterData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMCharacterData, "2933BF84-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMCharacterData : public IXMLDOMNode

    get_data		proc :ptr
    put_data		proc :BSTR
    get_length		proc :ptr
    substringData	proc :long, :long, :ptr
    appendData		proc :BSTR
    insertData		proc :long, :BSTR
    deleteData		proc :long, :long
    replaceData		proc :long, :long, :BSTR
    .ends

endif

ifndef __IXMLDOMAttribute_INTERFACE_DEFINED__
__IXMLDOMAttribute_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMAttribute, "2933BF85-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMAttribute : public IXMLDOMNode

    get_name		proc :ptr
    get_value		proc :ptr
    put_value		proc :VARIANT
    .ends

endif

ifndef __IXMLDOMElement_INTERFACE_DEFINED__
__IXMLDOMElement_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMElement, "2933BF86-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMElement : public IXMLDOMNode

    get_tagName		proc :ptr
    getAttribute	proc :BSTR, :ptr
    setAttribute	proc :BSTR, :VARIANT
    removeAttribute	proc :BSTR
    getAttributeNode	proc :BSTR, :ptr
    setAttributeNode	proc :ptr, :ptr
    removeAttributeNode proc :ptr, :ptr
    getElementsByTagName proc :BSTR, :ptr
    normalize		proc
    .ends

endif

ifndef __IXMLDOMText_INTERFACE_DEFINED__
__IXMLDOMText_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMText, "2933BF87-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMText : public IXMLDOMCharacterData

    splitText		proc :LONG, :ptr
    .ends

endif

ifndef __IXMLDOMComment_INTERFACE_DEFINED__
__IXMLDOMComment_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMComment, "2933BF88-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMComment : public IXMLDOMCharacterData

    .ends

endif

ifndef __IXMLDOMProcessingInstruction_INTERFACE_DEFINED__
__IXMLDOMProcessingInstruction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMProcessingInstruction, "2933BF89-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMProcessingInstruction : public IXMLDOMNode

    get_target		proc :ptr
    get_data		proc :ptr
    put_data		proc :BSTR
    .ends

endif

ifndef __IXMLDOMCDATASection_INTERFACE_DEFINED__
__IXMLDOMCDATASection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMCDATASection, "2933BF8A-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMCDATASection : public IXMLDOMText

    .ends

endif

ifndef __IXMLDOMDocumentType_INTERFACE_DEFINED__
__IXMLDOMDocumentType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMDocumentType, "2933BF8B-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMDocumentType : public IXMLDOMNode

    get_name		proc :ptr
    get_entities	proc :ptr
    get_notations	proc :ptr
    .ends

endif

ifndef __IXMLDOMNotation_INTERFACE_DEFINED__
__IXMLDOMNotation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMNotation, "2933BF8C-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMNotation : public IXMLDOMNode

    get_publicId	proc :ptr
    get_systemId	proc :ptr
    .ends

endif

ifndef __IXMLDOMEntity_INTERFACE_DEFINED__
__IXMLDOMEntity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMEntity, "2933BF8D-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMEntity : public IXMLDOMNode

    get_publicId	proc :ptr
    get_systemId	proc :ptr
    get_notationName	proc :ptr
    .ends

endif

ifndef __IXMLDOMEntityReference_INTERFACE_DEFINED__
__IXMLDOMEntityReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMEntityReference, "2933BF8E-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMEntityReference : public IXMLDOMNode

    .ends

endif

ifndef __IXMLDOMImplementation_INTERFACE_DEFINED__
__IXMLDOMImplementation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMImplementation, "2933BF8F-7B36-11d2-B20E-00C04F983E60")

.comdef IXMLDOMImplementation : public IDispatch

    hasFeature		proc :BSTR, :BSTR, :ptr
    .ends

endif

ifndef __IXTLRuntime_INTERFACE_DEFINED__
__IXTLRuntime_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXTLRuntime, "3efaa425-272f-11d2-836f-0000f87a7782")

.comdef IXTLRuntime : public IXMLDOMNode

    uniqueID		proc :ptr, :ptr
    depth		proc :ptr, :ptr
    childNumber		proc :ptr, :ptr
    ancestorChildNumber proc :BSTR, :ptr, :ptr
    absoluteChildNumber proc :ptr, :ptr
    formatIndex		proc :LONG, :BSTR, :ptr
    formatNumber	proc :double, :BSTR, :ptr
    formatDate		proc :VARIANT, :BSTR, :VARIANT, :ptr
    formatTime		proc :VARIANT, :BSTR, :VARIANT, :ptr
    .ends

endif

ifndef __IXMLDOMParseError_INTERFACE_DEFINED__
__IXMLDOMParseError_INTERFACE_DEFINED__ equ 1

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

ifndef __IXMLDOMParseError2_INTERFACE_DEFINED__
__IXMLDOMParseError2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMParseError2, "3efaa428-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMParseError2 : public IXMLDOMParseError

    get_errorXPath	proc :ptr
    get_allErrors	proc :ptr
    errorParameters	proc :LONG, :ptr
    get_errorParametersCount proc :ptr
    .ends

endif

ifndef __IXMLDOMParseErrorCollection_INTERFACE_DEFINED__
__IXMLDOMParseErrorCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMParseErrorCollection, "3efaa429-272f-11d2-836f-0000f87a7782")

.comdef IXMLDOMParseErrorCollection : public IDispatch

    get_item		proc :LONG, :ptr
    get_length		proc :ptr
    get_next		proc :ptr
    reset		proc
    get__newEnum	proc :ptr
    .ends

endif

ifndef __IXSLProcessor_INTERFACE_DEFINED__
__IXSLProcessor_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXSLProcessor, "2933BF92-7B36-11d2-B20E-00C04F983E60")

.comdef IXSLProcessor : public IDispatch

    put_input		proc :VARIANT
    get_input		proc :ptr
    get_ownerTemplate	proc :ptr
    setStartMode	proc :BSTR, :BSTR
    get_startMode	proc :ptr
    get_startModeURI	proc :ptr
    put_output		proc :VARIANT
    get_output		proc :ptr
    transform		proc :ptr
    reset		proc
    get_readyState	proc :ptr
    addParameter	proc :BSTR, :VARIANT, :BSTR
    addObject		proc :ptr, :BSTR
    get_stylesheet	proc :ptr
    .ends

endif

ifndef __IXSLTemplate_INTERFACE_DEFINED__
__IXSLTemplate_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXSLTemplate, "2933BF93-7B36-11d2-B20E-00C04F983E60")

.comdef IXSLTemplate : public IDispatch

    putref_stylesheet	proc :ptr
    get_stylesheet	proc :ptr
    createProcessor	proc :ptr
    .ends

endif

ifndef __IXMLHttpRequest_INTERFACE_DEFINED__
__IXMLHTTPRequest_INTERFACE_DEFINED__ equ 1

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

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
ifndef __msxml_sxh_enums__
__msxml_sxh_enums__ equ 1

.enum SERVERXMLHTTP_OPTION {
    SXH_OPTION_URL	= -1,
    SXH_OPTION_URL_CODEPAGE = ( SXH_OPTION_URL + 1 ),
    SXH_OPTION_ESCAPE_PERCENT_IN_URL = ( SXH_OPTION_URL_CODEPAGE + 1 ),
    SXH_OPTION_IGNORE_SERVER_SSL_CERT_ERROR_FLAGS = ( SXH_OPTION_ESCAPE_PERCENT_IN_URL + 1 ),
    SXH_OPTION_SELECT_CLIENT_SSL_CERT = ( SXH_OPTION_IGNORE_SERVER_SSL_CERT_ERROR_FLAGS + 1 )
    }

.enum SXH_SERVER_CERT_OPTION {
    SXH_SERVER_CERT_IGNORE_UNKNOWN_CA = 0x100,
    SXH_SERVER_CERT_IGNORE_WRONG_USAGE = 0x200,
    SXH_SERVER_CERT_IGNORE_CERT_CN_INVALID = 0x1000,
    SXH_SERVER_CERT_IGNORE_CERT_DATE_INVALID = 0x2000,
    SXH_SERVER_CERT_IGNORE_ALL_SERVER_ERRORS = ( ( ( SXH_SERVER_CERT_IGNORE_UNKNOWN_CA or SXH_SERVER_CERT_IGNORE_WRONG_USAGE ) or SXH_SERVER_CERT_IGNORE_CERT_CN_INVALID ) or SXH_SERVER_CERT_IGNORE_CERT_DATE_INVALID )
    }

.enum SXH_PROXY_SETTING {
    SXH_PROXY_SET_DEFAULT	= 0,
    SXH_PROXY_SET_PRECONFIG	= 0,
    SXH_PROXY_SET_DIRECT	= 0x1,
    SXH_PROXY_SET_PROXY		= 0x2
    }

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)


ifndef __IServerXMLHTTPRequest_INTERFACE_DEFINED__
__IServerXMLHTTPRequest_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServerXMLHTTPRequest, "2e9196bf-13ba-4dd4-91ca-6c571f281495")

.comdef IServerXMLHTTPRequest : public IXMLHttpRequest

    setTimeouts		proc :LONG, :LONG, :LONG, :LONG
    waitForResponse	proc :VARIANT, :ptr
    getOption		proc :SERVERXMLHTTP_OPTION, :ptr
    setOption		proc :SERVERXMLHTTP_OPTION, :VARIANT
    .ends

endif

ifndef __IServerXMLHTTPRequest2_INTERFACE_DEFINED__
__IServerXMLHTTPRequest2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IServerXMLHTTPRequest2, "2e01311b-c322-4b0a-bd77-b90cfdc8dce7")

.comdef IServerXMLHTTPRequest2 : public IServerXMLHTTPRequest

    setProxy		proc :SXH_PROXY_SETTING, :VARIANT, :VARIANT
    setProxyCredentials proc :BSTR, :BSTR
    .ends

endif

ifndef __ISAXXMLReader_INTERFACE_DEFINED__
__ISAXXMLReader_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXXMLReader, "a4f96ed0-f829-476e-81c0-cdc7bd2a0802")

.comdef ISAXXMLReader : public IUnknown

    getFeature		proc :ptr, :ptr
    putFeature		proc :ptr, :VARIANT_BOOL
    getProperty		proc :ptr, :ptr
    putProperty		proc :ptr, :VARIANT
    getEntityResolver	proc :ptr
    putEntityResolver	proc :ptr
    getContentHandler	proc :ptr
    putContentHandler	proc :ptr
    getDTDHandler	proc :ptr
    putDTDHandler	proc :ptr
    getErrorHandler	proc :ptr
    putErrorHandler	proc :ptr
    getBaseURL		proc :ptr
    putBaseURL		proc :ptr
    getSecureBaseURL	proc :ptr
    putSecureBaseURL	proc :ptr
    parse		proc :VARIANT
    parseURL		proc :ptr
    .ends

endif

ifndef __ISAXXMLFilter_INTERFACE_DEFINED__
__ISAXXMLFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXXMLFilter, "70409222-ca09-4475-acb8-40312fe8d145")

.comdef ISAXXMLFilter : public ISAXXMLReader

    getParent		proc :ptr
    putParent		proc :ptr
    .ends

endif

ifndef __ISAXLocator_INTERFACE_DEFINED__
__ISAXLocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXLocator, "9b7e472a-0de4-4640-bff3-84d38a051c31")

.comdef ISAXLocator : public IUnknown

    getColumnNumber	proc :ptr
    getLineNumber	proc :ptr
    getPublicId		proc :ptr
    getSystemId		proc :ptr
    .ends

endif

ifndef __ISAXEntityResolver_INTERFACE_DEFINED__
__ISAXEntityResolver_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXEntityResolver, "99bca7bd-e8c4-4d5f-a0cf-6d907901ff07")

.comdef ISAXEntityResolver : public IUnknown

    resolveEntity	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __ISAXContentHandler_INTERFACE_DEFINED__
__ISAXContentHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXContentHandler, "1545cdfa-9e4e-4497-a8a4-2bf7d0112c44")

.comdef ISAXContentHandler : public IUnknown

    putDocumentLocator	proc :ptr
    startDocument	proc
    endDocument		proc
    startPrefixMapping	proc :ptr, :SINT, :ptr, :SINT
    endPrefixMapping	proc :ptr, :SINT
    startElement	proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT, :ptr
    endElement		proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT
    characters		proc :ptr, :SINT
    ignorableWhitespace proc :ptr, :SINT
    processingInstruction proc :ptr, :SINT, :ptr, :SINT
    skippedEntity	proc :ptr, :SINT
    .ends

endif

ifndef __ISAXDTDHandler_INTERFACE_DEFINED__
__ISAXDTDHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXDTDHandler, "e15c1baf-afb3-4d60-8c36-19a8c45defed")

.comdef ISAXDTDHandler : public IUnknown

    notationDecl	proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT
    unparsedEntityDecl	proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT, :ptr, :SINT
    .ends

endif

ifndef __ISAXErrorHandler_INTERFACE_DEFINED__
__ISAXErrorHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXErrorHandler, "a60511c4-ccf5-479e-98a3-dc8dc545b7d0")

.comdef ISAXErrorHandler : public IUnknown

    error		proc :ptr, :ptr, :HRESULT
    fatalError		proc :ptr, :ptr, :HRESULT
    ignorableWarning	proc :ptr, :ptr, :HRESULT
    .ends

endif

ifndef __ISAXLexicalHandler_INTERFACE_DEFINED__
__ISAXLexicalHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXLexicalHandler, "7f85d5f5-47a8-4497-bda5-84ba04819ea6")

.comdef ISAXLexicalHandler : public IUnknown

    startDTD		proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT
    endDTD		proc
    startEntity		proc :ptr, :SINT
    endEntity		proc :ptr, :SINT
    startCDATA		proc
    endCDATA		proc
    comment		proc :ptr, :SINT
    .ends

endif

ifndef __ISAXDeclHandler_INTERFACE_DEFINED__
__ISAXDeclHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXDeclHandler, "862629ac-771a-47b2-8337-4e6843c1be90")

.comdef ISAXDeclHandler : public IUnknown

    elementDecl		proc :ptr, :SINT, :ptr, :SINT
    attributeDecl	proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT, :ptr, :SINT, :ptr, :SINT
    internalEntityDecl	proc :ptr, :SINT, :ptr, :SINT
    externalEntityDecl	proc :ptr, :SINT, :ptr, :SINT, :ptr, :SINT
    .ends

endif

ifndef __ISAXAttributes_INTERFACE_DEFINED__
__ISAXAttributes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISAXAttributes, "f078abe1-45d2-4832-91ea-4466ce2f25c9")

.comdef ISAXAttributes : public IUnknown

    getLength		proc :ptr
    getURI		proc :SINT, :ptr, :ptr
    getLocalName	proc :SINT, :ptr, :ptr
    getQName		proc :SINT, :ptr, :ptr
    getName		proc :SINT, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    getIndexFromName	proc :ptr, :SINT, :ptr, :SINT, :ptr
    getIndexFromQName	proc :ptr, :SINT, :ptr
    getType		proc :SINT, :ptr, :ptr
    getTypeFromName	proc :ptr, :SINT, :ptr, :SINT, :ptr, :ptr
    getTypeFromQName	proc :ptr, :SINT, :ptr, :ptr
    getValue		proc :SINT, :ptr, :ptr
    getValueFromName	proc :ptr, :SINT, :ptr, :SINT, :ptr, :ptr
    getValueFromQName	proc :ptr, :SINT, :ptr, :ptr
    .ends

endif

ifndef __IVBSAXXMLReader_INTERFACE_DEFINED__
__IVBSAXXMLReader_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXXMLReader, "8c033caa-6cd6-4f73-b728-4531af74945f")

.comdef IVBSAXXMLReader : public IDispatch

    getFeature		proc :BSTR, :ptr
    putFeature		proc :BSTR, :VARIANT_BOOL
    getProperty		proc :BSTR, :ptr
    putProperty		proc :BSTR, :VARIANT
    get_entityResolver	proc :ptr
    putref_entityResolver proc :ptr
    get_contentHandler	proc :ptr
    putref_contentHandler proc :ptr
    get_dtdHandler	proc :ptr
    putref_dtdHandler	proc :ptr
    get_errorHandler	proc :ptr
    putref_errorHandler proc :ptr
    get_baseURL		proc :ptr
    put_baseURL		proc :BSTR
    get_secureBaseURL	proc :ptr
    put_secureBaseURL	proc :BSTR
    parse		proc :VARIANT
    parseURL		proc :BSTR
    .ends

endif

ifndef __IVBSAXXMLFilter_INTERFACE_DEFINED__
__IVBSAXXMLFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXXMLFilter, "1299eb1b-5b88-433e-82de-82ca75ad4e04")

.comdef IVBSAXXMLFilter : public IDispatch

    get_parent		proc :ptr
    putref_parent	proc :ptr
    .ends

endif

ifndef __IVBSAXLocator_INTERFACE_DEFINED__
__IVBSAXLocator_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXLocator, "796e7ac5-5aa2-4eff-acad-3faaf01a3288")

.comdef IVBSAXLocator : public IDispatch

    get_columnNumber	proc :ptr
    get_lineNumber	proc :ptr
    get_publicId	proc :ptr
    get_systemId	proc :ptr
    .ends

endif

ifndef __IVBSAXEntityResolver_INTERFACE_DEFINED__
__IVBSAXEntityResolver_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXEntityResolver, "0c05d096-f45b-4aca-ad1a-aa0bc25518dc")

.comdef IVBSAXEntityResolver : public IDispatch

    resolveEntity	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __IVBSAXContentHandler_INTERFACE_DEFINED__
__IVBSAXContentHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXContentHandler, "2ed7290a-4dd5-4b46-bb26-4e4155e77faa")

.comdef IVBSAXContentHandler : public IDispatch

    putref_documentLocator proc :ptr
    startDocument	proc
    endDocument		proc
    startPrefixMapping	proc :ptr, :ptr
    endPrefixMapping	proc :ptr
    startElement	proc :ptr, :ptr, :ptr, :ptr
    endElement		proc :ptr, :ptr, :ptr
    characters		proc :ptr
    ignorableWhitespace proc :ptr
    processingInstruction proc :ptr, :ptr
    skippedEntity	proc :ptr
    .ends

endif

ifndef __IVBSAXDTDHandler_INTERFACE_DEFINED__
__IVBSAXDTDHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXDTDHandler, "24fb3297-302d-4620-ba39-3a732d850558")

.comdef IVBSAXDTDHandler : public IDispatch

    notationDecl	proc :ptr, :ptr, :ptr
    unparsedEntityDecl	proc :ptr, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IVBSAXErrorHandler_INTERFACE_DEFINED__
__IVBSAXErrorHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXErrorHandler, "d963d3fe-173c-4862-9095-b92f66995f52")

.comdef IVBSAXErrorHandler : public IDispatch

    error		proc :ptr, :ptr, :LONG
    fatalError		proc :ptr, :ptr, :LONG
    ignorableWarning	proc :ptr, :ptr, :LONG
    .ends

endif

ifndef __IVBSAXLexicalHandler_INTERFACE_DEFINED__
__IVBSAXLexicalHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXLexicalHandler, "032aac35-8c0e-4d9d-979f-e3b702935576")

.comdef IVBSAXLexicalHandler : public IDispatch

    startDTD		proc :ptr, :ptr, :ptr
    endDTD		proc
    startEntity		proc :ptr
    endEntity		proc :ptr
    startCDATA		proc
    endCDATA		proc
    comment		proc :ptr
    .ends

endif

ifndef __IVBSAXDeclHandler_INTERFACE_DEFINED__
__IVBSAXDeclHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXDeclHandler, "e8917260-7579-4be1-b5dd-7afbfa6f077b")

.comdef IVBSAXDeclHandler : public IDispatch

    elementDecl		proc :ptr, :ptr
    attributeDecl	proc :ptr, :ptr, :ptr, :ptr, :ptr
    internalEntityDecl	proc :ptr, :ptr
    externalEntityDecl	proc :ptr, :ptr, :ptr
    .ends

endif

ifndef __IVBSAXAttributes_INTERFACE_DEFINED__
__IVBSAXAttributes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBSAXAttributes, "10dc0586-132b-4cac-8bb3-db00ac8b7ee0")

.comdef IVBSAXAttributes : public IDispatch

    get_length		proc :ptr
    getURI		proc :SINT, :ptr
    getLocalName	proc :SINT, :ptr
    getQName		proc :SINT, :ptr
    getIndexFromName	proc :BSTR, :BSTR, :ptr
    getIndexFromQName	proc :BSTR, :ptr
    getType		proc :SINT, :ptr
    getTypeFromName	proc :BSTR, :BSTR, :ptr
    getTypeFromQName	proc :BSTR, :ptr
    getValue		proc :SINT, :ptr
    getValueFromName	proc :BSTR, :BSTR, :ptr
    getValueFromQName	proc :BSTR, :ptr
    .ends

endif

ifndef __IMXWriter_INTERFACE_DEFINED__
__IMXWriter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXWriter, "4d7ff4ba-1565-4ea8-94e1-6e724a46f98d")

.comdef IMXWriter : public IDispatch

    put_output		proc :VARIANT
    get_output		proc :ptr
    put_encoding	proc :BSTR
    get_encoding	proc :ptr
    put_byteOrderMark	proc :VARIANT_BOOL
    get_byteOrderMark	proc :ptr
    put_indent		proc :VARIANT_BOOL
    get_indent		proc :ptr
    put_standalone	proc :VARIANT_BOOL
    get_standalone	proc :ptr
    put_omitXMLDeclaration proc :VARIANT_BOOL
    get_omitXMLDeclaration proc :ptr
    put_version		proc :BSTR
    get_version		proc :ptr
    put_disableOutputEscaping proc :VARIANT_BOOL
    get_disableOutputEscaping proc :ptr
    flush		proc
    .ends

endif

ifndef __IMXAttributes_INTERFACE_DEFINED__
__IMXAttributes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXAttributes, "f10d27cc-3ec0-415c-8ed8-77ab1c5e7262")

.comdef IMXAttributes : public IDispatch

    addAttribute	proc :BSTR, :BSTR, :BSTR, :BSTR, :BSTR
    addAttributeFromIndex proc :VARIANT, :SINT
    clear		proc
    removeAttribute	proc :SINT
    setAttribute	proc :SINT, :BSTR, :BSTR, :BSTR, :BSTR, :BSTR
    setAttributes	proc :VARIANT
    setLocalName	proc :SINT, :BSTR
    setQName		proc :SINT, :BSTR
    setType		proc :SINT, :BSTR
    setURI		proc :SINT, :BSTR
    setValue		proc :SINT, :BSTR
    .ends

endif

ifndef __IMXReaderControl_INTERFACE_DEFINED__
__IMXReaderControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXReaderControl, "808f4e35-8d5a-4fbe-8466-33a41279ed30")

.comdef IMXReaderControl : public IDispatch

    abort		proc
    resume		proc
    suspend		proc
    .ends

endif

ifndef __IMXSchemaDeclHandler_INTERFACE_DEFINED__
__IMXSchemaDeclHandler_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXSchemaDeclHandler, "fa4bb38c-faf9-4cca-9302-d1dd0fe520db")

.comdef IMXSchemaDeclHandler : public IDispatch

    schemaElementDecl	proc :ptr
    .ends

endif

ifndef __IMXNamespacePrefixes_INTERFACE_DEFINED__
__IMXNamespacePrefixes_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXNamespacePrefixes, "c90352f4-643c-4fbc-bb23-e996eb2d51fd")

.comdef IMXNamespacePrefixes : public IDispatch

    get_item		proc :LONG, :ptr
    get_length		proc :ptr
    get__newEnum	proc :ptr
    .ends

endif

ifndef __IVBMXNamespaceManager_INTERFACE_DEFINED__
__IVBMXNamespaceManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IVBMXNamespaceManager, "c90352f5-643c-4fbc-bb23-e996eb2d51fd")

.comdef IVBMXNamespaceManager : public IDispatch

    put_allowOverride	proc :VARIANT_BOOL
    get_allowOverride	proc :ptr
    reset		proc
    _pushContext	proc
    pushNodeContext	proc :ptr, :VARIANT_BOOL
    _popContext		proc
    declarePrefix	proc :BSTR, :BSTR
    getDeclaredPrefixes proc :ptr
    getPrefixes		proc :BSTR, :ptr
    getURI		proc :BSTR, :ptr
    getURIFromNode	proc :BSTR, :ptr, :ptr
    .ends

endif

ifndef __IMXNamespaceManager_INTERFACE_DEFINED__
__IMXNamespaceManager_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXNamespaceManager, "c90352f6-643c-4fbc-bb23-e996eb2d51fd")

.comdef IMXNamespaceManager : public IUnknown

    putAllowOverride	proc :VARIANT_BOOL
    getAllowOverride	proc :ptr
    reset		proc
    _pushContext	proc
    pushNodeContext	proc :ptr, :VARIANT_BOOL
    _popContext		proc
    declarePrefix	proc :LPCWSTR, :LPCWSTR
    getDeclaredPrefix	proc :LONG, :ptr, :ptr
    getPrefix		proc :LPCWSTR, :LONG, :ptr, :ptr
    getURI		proc :LPCWSTR, :ptr, :ptr, :ptr
    .ends

endif

ifndef __IMXXMLFilter_INTERFACE_DEFINED__
__IMXXMLFilter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IMXXMLFilter, "c90352f7-643c-4fbc-bb23-e996eb2d51fd")

.comdef IMXXMLFilter : public IDispatch

    getFeature		proc :BSTR, :ptr
    putFeature		proc :BSTR, :VARIANT_BOOL
    getProperty		proc :BSTR, :ptr
    putProperty		proc :BSTR, :VARIANT
    get_entityResolver	proc :ptr
    putref_entityResolver proc :ptr
    get_contentHandler	proc :ptr
    putref_contentHandler proc :ptr
    get_dtdHandler	proc :ptr
    putref_dtdHandler	proc :ptr
    get_errorHandler	proc :ptr
    putref_errorHandler proc :ptr
    .ends

endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
if NOT defined(__msxml_som_enums__)
__msxml_som_enums__ equ 1
.enum SOMITEMTYPE {
    SOMITEM_SCHEMA		= 0x1000,
    SOMITEM_ATTRIBUTE		= 0x1001,
    SOMITEM_ATTRIBUTEGROUP	= 0x1002,
    SOMITEM_NOTATION		= 0x1003,
    SOMITEM_ANNOTATION		= 0x1004,
    SOMITEM_IDENTITYCONSTRAINT	= 0x1100,
    SOMITEM_KEY			= 0x1101,
    SOMITEM_KEYREF		= 0x1102,
    SOMITEM_UNIQUE		= 0x1103,
    SOMITEM_ANYTYPE		= 0x2000,
    SOMITEM_DATATYPE		= 0x2100,
    SOMITEM_DATATYPE_ANYTYPE	= 0x2101,
    SOMITEM_DATATYPE_ANYURI	= 0x2102,
    SOMITEM_DATATYPE_BASE64BINARY = 0x2103,
    SOMITEM_DATATYPE_BOOLEAN	= 0x2104,
    SOMITEM_DATATYPE_BYTE	= 0x2105,
    SOMITEM_DATATYPE_DATE	= 0x2106,
    SOMITEM_DATATYPE_DATETIME	= 0x2107,
    SOMITEM_DATATYPE_DAY	= 0x2108,
    SOMITEM_DATATYPE_DECIMAL	= 0x2109,
    SOMITEM_DATATYPE_DOUBLE	= 0x210a,
    SOMITEM_DATATYPE_DURATION	= 0x210b,
    SOMITEM_DATATYPE_ENTITIES	= 0x210c,
    SOMITEM_DATATYPE_ENTITY	= 0x210d,
    SOMITEM_DATATYPE_FLOAT	= 0x210e,
    SOMITEM_DATATYPE_HEXBINARY	= 0x210f,
    SOMITEM_DATATYPE_ID		= 0x2110,
    SOMITEM_DATATYPE_IDREF	= 0x2111,
    SOMITEM_DATATYPE_IDREFS	= 0x2112,
    SOMITEM_DATATYPE_INT	= 0x2113,
    SOMITEM_DATATYPE_INTEGER	= 0x2114,
    SOMITEM_DATATYPE_LANGUAGE	= 0x2115,
    SOMITEM_DATATYPE_LONG	= 0x2116,
    SOMITEM_DATATYPE_MONTH	= 0x2117,
    SOMITEM_DATATYPE_MONTHDAY	= 0x2118,
    SOMITEM_DATATYPE_NAME	= 0x2119,
    SOMITEM_DATATYPE_NCNAME	= 0x211a,
    SOMITEM_DATATYPE_NEGATIVEINTEGER = 0x211b,
    SOMITEM_DATATYPE_NMTOKEN	= 0x211c,
    SOMITEM_DATATYPE_NMTOKENS	= 0x211d,
    SOMITEM_DATATYPE_NONNEGATIVEINTEGER = 0x211e,
    SOMITEM_DATATYPE_NONPOSITIVEINTEGER = 0x211f,
    SOMITEM_DATATYPE_NORMALIZEDSTRING	= 0x2120,
    SOMITEM_DATATYPE_NOTATION	= 0x2121,
    SOMITEM_DATATYPE_POSITIVEINTEGER	= 0x2122,
    SOMITEM_DATATYPE_QNAME	= 0x2123,
    SOMITEM_DATATYPE_SHORT	= 0x2124,
    SOMITEM_DATATYPE_STRING	= 0x2125,
    SOMITEM_DATATYPE_TIME	= 0x2126,
    SOMITEM_DATATYPE_TOKEN	= 0x2127,
    SOMITEM_DATATYPE_UNSIGNEDBYTE = 0x2128,
    SOMITEM_DATATYPE_UNSIGNEDINT = 0x2129,
    SOMITEM_DATATYPE_UNSIGNEDLONG = 0x212a,
    SOMITEM_DATATYPE_UNSIGNEDSHORT = 0x212b,
    SOMITEM_DATATYPE_YEAR	= 0x212c,
    SOMITEM_DATATYPE_YEARMONTH	= 0x212d,
    SOMITEM_DATATYPE_ANYSIMPLETYPE = 0x21ff,
    SOMITEM_SIMPLETYPE		= 0x2200,
    SOMITEM_COMPLEXTYPE		= 0x2400,
    SOMITEM_PARTICLE		= 0x4000,
    SOMITEM_ANY			= 0x4001,
    SOMITEM_ANYATTRIBUTE	= 0x4002,
    SOMITEM_ELEMENT		= 0x4003,
    SOMITEM_GROUP		= 0x4100,
    SOMITEM_ALL			= 0x4101,
    SOMITEM_CHOICE		= 0x4102,
    SOMITEM_SEQUENCE		= 0x4103,
    SOMITEM_EMPTYPARTICLE	= 0x4104,
    SOMITEM_NULL		= 0x800,
    SOMITEM_NULL_TYPE		= 0x2800,
    SOMITEM_NULL_ANY		= 0x4801,
    SOMITEM_NULL_ANYATTRIBUTE	= 0x4802,
    SOMITEM_NULL_ELEMENT	= 0x4803
    }

.enum SCHEMAUSE {
    SCHEMAUSE_OPTIONAL		= 0,
    SCHEMAUSE_PROHIBITED	= ( SCHEMAUSE_OPTIONAL + 1 ),
    SCHEMAUSE_REQUIRED		= ( SCHEMAUSE_PROHIBITED + 1 )
    }

.enum SCHEMADERIVATIONMETHOD {
    SCHEMADERIVATIONMETHOD_EMPTY	= 0,
    SCHEMADERIVATIONMETHOD_SUBSTITUTION = 0x1,
    SCHEMADERIVATIONMETHOD_EXTENSION	= 0x2,
    SCHEMADERIVATIONMETHOD_RESTRICTION	= 0x4,
    SCHEMADERIVATIONMETHOD_LIST		= 0x8,
    SCHEMADERIVATIONMETHOD_UNION	= 0x10,
    SCHEMADERIVATIONMETHOD_ALL		= 0xff,
    SCHEMADERIVATIONMETHOD_NONE		= 0x100
    }

.enum SCHEMACONTENTTYPE {
    SCHEMACONTENTTYPE_EMPTY		= 0,
    SCHEMACONTENTTYPE_TEXTONLY		= ( SCHEMACONTENTTYPE_EMPTY + 1 ),
    SCHEMACONTENTTYPE_ELEMENTONLY	= ( SCHEMACONTENTTYPE_TEXTONLY + 1 ),
    SCHEMACONTENTTYPE_MIXED		= ( SCHEMACONTENTTYPE_ELEMENTONLY + 1 )
    }

.enum SCHEMAPROCESSCONTENTS {
    SCHEMAPROCESSCONTENTS_NONE	= 0,
    SCHEMAPROCESSCONTENTS_SKIP	= ( SCHEMAPROCESSCONTENTS_NONE + 1 ),
    SCHEMAPROCESSCONTENTS_LAX	= ( SCHEMAPROCESSCONTENTS_SKIP + 1 ),
    SCHEMAPROCESSCONTENTS_STRICT = ( SCHEMAPROCESSCONTENTS_LAX + 1 )
    }

.enum SCHEMAWHITESPACE {
    SCHEMAWHITESPACE_NONE	= -1,
    SCHEMAWHITESPACE_PRESERVE	= 0,
    SCHEMAWHITESPACE_REPLACE	= 1,
    SCHEMAWHITESPACE_COLLAPSE	= 2
    }

.enum SCHEMATYPEVARIETY {
    SCHEMATYPEVARIETY_NONE	= -1,
    SCHEMATYPEVARIETY_ATOMIC	= 0,
    SCHEMATYPEVARIETY_LIST	= 1,
    SCHEMATYPEVARIETY_UNION	= 2
    }

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __IXMLDOMSchemaCollection2_INTERFACE_DEFINED__
__IXMLDOMSchemaCollection2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLDOMSchemaCollection2, "50ea08b0-dd1b-4664-9a50-c2f40f4bd79a")

.comdef IXMLDOMSchemaCollection2 : public IXMLDOMSchemaCollection

    validate		proc
    put_validateOnLoad	proc :VARIANT_BOOL
    get_validateOnLoad	proc :ptr
    getSchema		proc :BSTR, :ptr
    getDeclaration	proc :ptr, :ptr
    .ends

endif

ifndef __ISchemaStringCollection_INTERFACE_DEFINED__
__ISchemaStringCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaStringCollection, "50ea08b1-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaStringCollection : public IDispatch

    get_item		proc :LONG, :ptr
    get_length		proc :ptr
    get__newEnum	proc :ptr
    .ends

endif

ifndef __ISchemaItemCollection_INTERFACE_DEFINED__
__ISchemaItemCollection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaItemCollection, "50ea08b2-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaItemCollection : public IDispatch

    get_item		proc :LONG, :ptr
    itemByName		proc :BSTR, :ptr
    itemByQName		proc :BSTR, :BSTR, :ptr
    get_length		proc :ptr
    get__newEnum	proc :ptr
    .ends

endif

ifndef __ISchemaItem_INTERFACE_DEFINED__
__ISchemaItem_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaItem, "50ea08b3-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaItem : public IDispatch

    get_name		proc :ptr
    get_namespaceURI	proc :ptr
    get_schema		proc :ptr
    get_id		proc :ptr
    get_itemType	proc :ptr
    get_unhandledAttributes proc :ptr
    writeAnnotation	proc :ptr, :ptr
    .ends

endif

ifndef __ISchema_INTERFACE_DEFINED__
__ISchema_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchema, "50ea08b4-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchema : public ISchemaItem

    get_targetNamespace proc :ptr
    get_version		proc :ptr
    get_types		proc :ptr
    get_elements	proc :ptr
    get_attributes	proc :ptr
    get_attributeGroups proc :ptr
    get_modelGroups	proc :ptr
    get_notations	proc :ptr
    get_schemaLocations proc :ptr
    .ends

endif

ifndef __ISchemaParticle_INTERFACE_DEFINED__
__ISchemaParticle_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaParticle, "50ea08b5-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaParticle : public ISchemaItem

    get_minOccurs	proc :ptr
    get_maxOccurs	proc :ptr
    .ends

endif

ifndef __ISchemaAttribute_INTERFACE_DEFINED__
__ISchemaAttribute_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaAttribute, "50ea08b6-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaAttribute : public ISchemaItem

    get_type		proc :ptr
    get_scope		proc :ptr
    get_defaultValue	proc :ptr
    get_fixedValue	proc :ptr
    get_use		proc :ptr
    get_isReference	proc :ptr
    .ends

endif

ifndef __ISchemaElement_INTERFACE_DEFINED__
__ISchemaElement_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaElement, "50ea08b7-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaElement : public ISchemaParticle

    get_type		proc :ptr
    get_scope		proc :ptr
    get_defaultValue	proc :ptr
    get_fixedValue	proc :ptr
    get_isNillable	proc :ptr
    get_identityConstraints proc :ptr
    get_substitutionGroup proc :ptr
    get_substitutionGroupExclusions proc :ptr
    get_disallowedSubstitutions proc :ptr
    get_isAbstract	proc :ptr
    get_isReference	proc :ptr
    .ends

endif

ifndef __ISchemaType_INTERFACE_DEFINED__
__ISchemaType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaType, "50ea08b8-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaType : public ISchemaItem

    get_baseTypes	proc :ptr
    get_final		proc :ptr
    get_variety		proc :ptr
    get_derivedBy	proc :ptr
    isValid		proc :BSTR, :ptr
    get_minExclusive	proc :ptr
    get_minInclusive	proc :ptr
    get_maxExclusive	proc :ptr
    get_maxInclusive	proc :ptr
    get_totalDigits	proc :ptr
    get_fractionDigits	proc :ptr
    get_length		proc :ptr
    get_minLength	proc :ptr
    get_maxLength	proc :ptr
    get_enumeration	proc :ptr
    get_whitespace	proc :ptr
    get_patterns	proc :ptr
    .ends

endif

ifndef __ISchemaComplexType_INTERFACE_DEFINED__
__ISchemaComplexType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaComplexType, "50ea08b9-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaComplexType : public ISchemaType

    get_isAbstract	proc :ptr
    get_anyAttribute	proc :ptr
    get_attributes	proc :ptr
    get_contentType	proc :ptr
    get_contentModel	proc :ptr
    get_prohibitedSubstitutions proc :ptr
    .ends

endif

ifndef __ISchemaAttributeGroup_INTERFACE_DEFINED__
__ISchemaAttributeGroup_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaAttributeGroup, "50ea08ba-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaAttributeGroup : public ISchemaItem

    get_anyAttribute	proc :ptr
    get_attributes	proc :ptr
    .ends

endif

ifndef __ISchemaModelGroup_INTERFACE_DEFINED__
__ISchemaModelGroup_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaModelGroup, "50ea08bb-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaModelGroup : public ISchemaParticle

    get_particles	proc :ptr
    .ends

endif

ifndef __ISchemaAny_INTERFACE_DEFINED__
__ISchemaAny_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaAny, "50ea08bc-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaAny : public ISchemaParticle

    get_namespaces	proc :ptr
    get_processContents proc :ptr
    .ends

endif


ifndef __ISchemaIdentityConstraint_INTERFACE_DEFINED__
__ISchemaIdentityConstraint_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaIdentityConstraint, "50ea08bd-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaIdentityConstraint : public ISchemaItem

    get_selector	proc :ptr
    get_fields		proc :ptr
    get_referencedKey	proc :ptr
    .ends

endif

ifndef __ISchemaNotation_INTERFACE_DEFINED__
__ISchemaNotation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(ISchemaNotation, "50ea08be-dd1b-4664-9a50-c2f40f4bd79a")

.comdef ISchemaNotation : public ISchemaItem

    get_systemIdentifier proc :ptr
    get_publicIdentifier proc :ptr
    .ends

endif

endif

ifndef __MSXML2_LIBRARY_DEFINED__
define __MSXML2_LIBRARY_DEFINED__

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
define CLSID_XmlHttpRequest <CLSID_FreeThreadedXMLHTTP60>
endif

externdef LIBID_MSXML2:IID

ifndef __XMLDOMDocumentEvents_DISPINTERFACE_DEFINED__
define __XMLDOMDocumentEvents_DISPINTERFACE_DEFINED__

externdef DIID_XMLDOMDocumentEvents:IID

DEFINE_IIDX(XMLDOMDocumentEvents, "3efaa427-272f-11d2-836f-0000f87a7782")

.comdef XMLDOMDocumentEvents : public IDispatch

    .ends

endif

DEFINE_GUIDS(CLSID_DOMDocument60, "88d96a05-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_FreeThreadedDOMDocument60, "88d96a06-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_XMLSchemaCache60, "88d96a07-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_XSLTemplate60, "88d96a08-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_XMLHTTP60, "88d96a0a-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_FreeThreadedXMLHTTP60, "88d96a09-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_ServerXMLHTTP60, "88d96a0b-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_SAXXMLReader60, "88d96a0c-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_MXXMLWriter60, "88d96a0f-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_MXHTMLWriter60, "88d96a10-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_SAXAttributes60, "88d96a0e-f192-11d4-a65f-0040963251e5")
DEFINE_GUIDS(CLSID_MXNamespaceManager60, "88d96a11-f192-11d4-a65f-0040963251e5")

endif ; __MSXML2_LIBRARY_DEFINED__

E_XML_NOTWF		equ 0xC00CE223
E_XML_NODTD		equ 0xC00CE224
E_XML_INVALID		equ 0xC00CE225
E_XML_BUFFERTOOSMALL	equ 0xC00CE226

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

ifndef __msxml_xhr_enums
define __msxml_xhr_enums

.enum XHR_COOKIE_STATE {
    XHR_COOKIE_STATE_UNKNOWN	= 0,
    XHR_COOKIE_STATE_ACCEPT	= 0x1,
    XHR_COOKIE_STATE_PROMPT	= 0x2,
    XHR_COOKIE_STATE_LEASH	= 0x3,
    XHR_COOKIE_STATE_DOWNGRADE	= 0x4,
    XHR_COOKIE_STATE_REJECT	= 0x5
    }

.enum XHR_COOKIE_FLAG {
    XHR_COOKIE_IS_SECURE	= 0x1,
    XHR_COOKIE_IS_SESSION	= 0x2,
    XHR_COOKIE_THIRD_PARTY	= 0x10,
    XHR_COOKIE_PROMPT_REQUIRED	= 0x20,
    XHR_COOKIE_EVALUATE_P3P	= 0x40,
    XHR_COOKIE_APPLY_P3P	= 0x80,
    XHR_COOKIE_P3P_ENABLED	= 0x100,
    XHR_COOKIE_IS_RESTRICTED	= 0x200,
    XHR_COOKIE_IE6	= 0x400,
    XHR_COOKIE_IS_LEGACY	= 0x800,
    XHR_COOKIE_NON_SCRIPT	= 0x1000,
    XHR_COOKIE_HTTPONLY = 0x2000
    }

.enum XHR_CRED_PROMPT {
    XHR_CRED_PROMPT_ALL = 0,
    XHR_CRED_PROMPT_NONE	= 0x1,
    XHR_CRED_PROMPT_PROXY	= 0x2
    }

.enum XHR_AUTH {
    XHR_AUTH_ALL	= 0,
    XHR_AUTH_NONE	= 0x1,
    XHR_AUTH_PROXY	= 0x2
    }

.enum XHR_PROPERTY {
    XHR_PROP_NO_CRED_PROMPT	= 0,
    XHR_PROP_NO_AUTH	= 0x1,
    XHR_PROP_TIMEOUT	= 0x2,
    XHR_PROP_NO_DEFAULT_HEADERS = 0x3,
    XHR_PROP_REPORT_REDIRECT_STATUS	= 0x4,
    XHR_PROP_NO_CACHE	= 0x5,
    XHR_PROP_EXTENDED_ERROR	= 0x6,
    XHR_PROP_QUERY_STRING_UTF8	= 0x7,
    XHR_PROP_IGNORE_CERT_ERRORS = 0x8
    }

.enum XHR_CERT_IGNORE_FLAG {
    XHR_CERT_IGNORE_REVOCATION_FAILED	= 0x80,
    XHR_CERT_IGNORE_UNKNOWN_CA		= 0x100,
    XHR_CERT_IGNORE_CERT_CN_INVALID	= 0x1000,
    XHR_CERT_IGNORE_CERT_DATE_INVALID	= 0x2000,
    XHR_CERT_IGNORE_ALL_SERVER_ERRORS	= ( ( ( XHR_CERT_IGNORE_REVOCATION_FAILED or XHR_CERT_IGNORE_UNKNOWN_CA ) or XHR_CERT_IGNORE_CERT_CN_INVALID ) or XHR_CERT_IGNORE_CERT_DATE_INVALID )
    }

.enum XHR_CERT_ERROR_FLAG {
    XHR_CERT_ERROR_REVOCATION_FAILED	= 0x800000,
    XHR_CERT_ERROR_UNKNOWN_CA		= 0x1000000,
    XHR_CERT_ERROR_CERT_CN_INVALID	= 0x2000000,
    XHR_CERT_ERROR_CERT_DATE_INVALID	= 0x4000000,
    XHR_CERT_ERROR_ALL_SERVER_ERRORS	= ( ( ( XHR_CERT_ERROR_REVOCATION_FAILED or XHR_CERT_ERROR_UNKNOWN_CA ) or XHR_CERT_ERROR_CERT_CN_INVALID ) or XHR_CERT_ERROR_CERT_DATE_INVALID )
    }

endif

XHR_COOKIE		STRUC
pwszUrl			LPWSTR ?
pwszName		LPWSTR ?
pwszValue		LPWSTR ?
pwszP3PPolicy		LPWSTR ?
ftExpires		FILETIME <>
dwFlags			dd ?
XHR_COOKIE		ENDS

ifndef __IXMLHTTPRequest2Callback_INTERFACE_DEFINED__
__IXMLHTTPRequest2Callback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLHTTPRequest2Callback, "A44A9299-E321-40DE-8866-341B41669162")

.comdef IXMLHTTPRequest2Callback : public IUnknown

    OnRedirect		proc :ptr, :ptr
    OnHeadersAvailable	proc :ptr, :DWORD, :ptr
    OnDataAvailable	proc :ptr, :ptr
    OnResponseReceived	proc :ptr, :ptr
    OnError		proc :ptr, :HRESULT
    .ends

endif

ifndef __IXMLHTTPRequest2_INTERFACE_DEFINED__
__IXMLHTTPRequest2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLHTTPRequest2, "E5D37DC0-552A-4D52-9CC0-A14D546FBD04")

.comdef IXMLHTTPRequest2 : public IUnknown

    Open		proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    Send		proc :ptr, :ULONGLONG
    Abort		proc
    SetCookie		proc :ptr, :ptr
    SetCustomResponseStream proc :ptr
    SetProperty		proc :XHR_PROPERTY, :ULONGLONG
    SetRequestHeader	proc :ptr, :ptr
    GetAllResponseHeaders proc :ptr
    GetCookie		proc :ptr, :ptr, :DWORD, :ptr, :ptr
    GetResponseHeader	proc :ptr, :ptr
    .ends

endif

XHR_CERT		STRUC
cbCert			dd ?
pbCert			LPBYTE ?
XHR_CERT		ENDS

ifndef __IXMLHTTPRequest3Callback_INTERFACE_DEFINED__
__IXMLHTTPRequest3Callback_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLHTTPRequest3Callback, "b9e57830-8c6c-4a6f-9c13-47772bb047bb")

.comdef IXMLHTTPRequest3Callback : public IXMLHTTPRequest2Callback

    OnServerCertificateReceived proc :ptr, :DWORD, :DWORD, :ptr
    OnClientCertificateRequested proc :ptr, :DWORD, :ptr
    .ends

endif

ifndef __IXMLHTTPRequest3_INTERFACE_DEFINED__
__IXMLHTTPRequest3_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXMLHTTPRequest3, "a1c9feee-0617-4f23-9d58-8961ea43567c")

.comdef IXMLHTTPRequest3 : public IXMLHTTPRequest2

    SetClientCertificate proc :DWORD
    .ends

endif

endif ; WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

VARIANT_UserSize proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

VARIANT_UserSize64 proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree64 proto WINAPI :ptr, :ptr

endif
