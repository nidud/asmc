ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef __xmllite_h__
define __xmllite_h_

include unknwn.inc
include objidl.inc
include oaidl.inc

IXmlReaderInput		typedef IUnknown
IXmlWriterOutput	typedef IUnknown

.pragma comment(lib, xmllite)

CreateXmlReader proto WINAPI \
		  riid: REFIID,
	     ppvObject: ptr,
	       pMalloc: ptr IMalloc

CreateXmlReaderInputWithEncodingCodePage proto WINAPI \
	  pInputStream: ptr IUnknown,
	       pMalloc: ptr IMalloc,
     nEncodingCodePage: UINT,
	 fEncodingHint: BOOL,
	   pwszBaseUri: LPCWSTR,
	       ppInput: ptr IXmlReaderInput

CreateXmlReaderInputWithEncodingName proto WINAPI \
	  pInputStream: ptr IUnknown,
	       pMalloc: ptr IMalloc,
      pwszEncodingName: LPCWSTR,
	 fEncodingHint: BOOL,
	   pwszBaseUri: LPCWSTR,
	       ppInput: ptr IXmlReaderInput

CreateXmlWriter proto WINAPI \
		  riid: REFIID,
	     ppvObject: ptr,
	       pMalloc: ptr IMalloc

CreateXmlWriterOutputWithEncodingCodePage proto WINAPI \
	 pOutputStream: ptr IUnknown,
	       pMalloc: ptr IMalloc,
     nEncodingCodePage: UINT,
	      ppOutput: ptr IXmlWriterOutput

CreateXmlWriterOutputWithEncodingName proto WINAPI \
	 pOutputStream: ptr IUnknown,
	       pMalloc: ptr IMalloc,
      pwszEncodingName: LPCWSTR,
	      ppOutput: ptr IXmlWriterOutput

ifndef __XmlLite_LIBRARY_DEFINED__
define __XmlLite_LIBRARY_DEFINED__

.enum XmlNodeType {
    XmlNodeType_None		= 0,
    XmlNodeType_Element		= 1,
    XmlNodeType_Attribute	= 2,
    XmlNodeType_Text		= 3,
    XmlNodeType_CDATA		= 4,
    XmlNodeType_ProcessingInstruction	= 7,
    XmlNodeType_Comment		= 8,
    XmlNodeType_DocumentType	= 10,
    XmlNodeType_Whitespace	= 13,
    XmlNodeType_EndElement	= 15,
    XmlNodeType_XmlDeclaration	= 17,
    _XmlNodeType_Last		= 17
    }

.enum XmlConformanceLevel {
    XmlConformanceLevel_Auto	= 0,
    XmlConformanceLevel_Fragment = 1,
    XmlConformanceLevel_Document = 2,
    _XmlConformanceLevel_Last	= 2
    }

.enum DtdProcessing {
    DtdProcessing_Prohibit	= 0,
    DtdProcessing_Parse		= ( DtdProcessing_Prohibit + 1 ) ,
    _DtdProcessing_Last		= DtdProcessing_Parse
    }

.enum XmlReadState {
    XmlReadState_Initial	= 0,
    XmlReadState_Interactive	= 1,
    XmlReadState_Error		= 2,
    XmlReadState_EndOfFile	= 3,
    XmlReadState_Closed		= 4
    }

.enum XmlReaderProperty {
    XmlReaderProperty_MultiLanguage	= 0,
    XmlReaderProperty_ConformanceLevel	= ( XmlReaderProperty_MultiLanguage + 1 ) ,
    XmlReaderProperty_RandomAccess	= ( XmlReaderProperty_ConformanceLevel + 1 ) ,
    XmlReaderProperty_XmlResolver	= ( XmlReaderProperty_RandomAccess + 1 ) ,
    XmlReaderProperty_DtdProcessing	= ( XmlReaderProperty_XmlResolver + 1 ) ,
    XmlReaderProperty_ReadState		= ( XmlReaderProperty_DtdProcessing + 1 ) ,
    XmlReaderProperty_MaxElementDepth	= ( XmlReaderProperty_ReadState + 1 ) ,
    XmlReaderProperty_MaxEntityExpansion = ( XmlReaderProperty_MaxElementDepth + 1 ) ,
    _XmlReaderProperty_Last		= XmlReaderProperty_MaxEntityExpansion
    }

.enum XmlError {
    MX_E_MX		= 0xc00cee00,
    MX_E_INPUTEND	= ( MX_E_MX + 1 ) ,
    MX_E_ENCODING	= ( MX_E_INPUTEND + 1 ) ,
    MX_E_ENCODINGSWITCH = ( MX_E_ENCODING + 1 ) ,
    MX_E_ENCODINGSIGNATURE = ( MX_E_ENCODINGSWITCH + 1 ) ,
    WC_E_WC		= 0xc00cee20,
    WC_E_WHITESPACE	= ( WC_E_WC + 1 ) ,
    WC_E_SEMICOLON	= ( WC_E_WHITESPACE + 1 ) ,
    WC_E_GREATERTHAN	= ( WC_E_SEMICOLON + 1 ) ,
    WC_E_QUOTE		= ( WC_E_GREATERTHAN + 1 ) ,
    WC_E_EQUAL		= ( WC_E_QUOTE + 1 ) ,
    WC_E_LESSTHAN	= ( WC_E_EQUAL + 1 ) ,
    WC_E_HEXDIGIT	= ( WC_E_LESSTHAN + 1 ) ,
    WC_E_DIGIT		= ( WC_E_HEXDIGIT + 1 ) ,
    WC_E_LEFTBRACKET	= ( WC_E_DIGIT + 1 ) ,
    WC_E_LEFTPAREN	= ( WC_E_LEFTBRACKET + 1 ) ,
    WC_E_XMLCHARACTER	= ( WC_E_LEFTPAREN + 1 ) ,
    WC_E_NAMECHARACTER	= ( WC_E_XMLCHARACTER + 1 ) ,
    WC_E_SYNTAX		= ( WC_E_NAMECHARACTER + 1 ) ,
    WC_E_CDSECT		= ( WC_E_SYNTAX + 1 ) ,
    WC_E_COMMENT	= ( WC_E_CDSECT + 1 ) ,
    WC_E_CONDSECT	= ( WC_E_COMMENT + 1 ) ,
    WC_E_DECLATTLIST	= ( WC_E_CONDSECT + 1 ) ,
    WC_E_DECLDOCTYPE	= ( WC_E_DECLATTLIST + 1 ) ,
    WC_E_DECLELEMENT	= ( WC_E_DECLDOCTYPE + 1 ) ,
    WC_E_DECLENTITY	= ( WC_E_DECLELEMENT + 1 ) ,
    WC_E_DECLNOTATION	= ( WC_E_DECLENTITY + 1 ) ,
    WC_E_NDATA		= ( WC_E_DECLNOTATION + 1 ) ,
    WC_E_PUBLIC		= ( WC_E_NDATA + 1 ) ,
    WC_E_SYSTEM		= ( WC_E_PUBLIC + 1 ) ,
    WC_E_NAME		= ( WC_E_SYSTEM + 1 ) ,
    WC_E_ROOTELEMENT	= ( WC_E_NAME + 1 ) ,
    WC_E_ELEMENTMATCH	= ( WC_E_ROOTELEMENT + 1 ) ,
    WC_E_UNIQUEATTRIBUTE = ( WC_E_ELEMENTMATCH + 1 ) ,
    WC_E_TEXTXMLDECL	= ( WC_E_UNIQUEATTRIBUTE + 1 ) ,
    WC_E_LEADINGXML	= ( WC_E_TEXTXMLDECL + 1 ) ,
    WC_E_TEXTDECL	= ( WC_E_LEADINGXML + 1 ) ,
    WC_E_XMLDECL	= ( WC_E_TEXTDECL + 1 ) ,
    WC_E_ENCNAME	= ( WC_E_XMLDECL + 1 ) ,
    WC_E_PUBLICID	= ( WC_E_ENCNAME + 1 ) ,
    WC_E_PESINTERNALSUBSET = ( WC_E_PUBLICID + 1 ) ,
    WC_E_PESBETWEENDECLS = ( WC_E_PESINTERNALSUBSET + 1 ) ,
    WC_E_NORECURSION	= ( WC_E_PESBETWEENDECLS + 1 ) ,
    WC_E_ENTITYCONTENT	= ( WC_E_NORECURSION + 1 ) ,
    WC_E_UNDECLAREDENTITY = ( WC_E_ENTITYCONTENT + 1 ) ,
    WC_E_PARSEDENTITY	= ( WC_E_UNDECLAREDENTITY + 1 ) ,
    WC_E_NOEXTERNALENTITYREF = ( WC_E_PARSEDENTITY + 1 ) ,
    WC_E_PI		= ( WC_E_NOEXTERNALENTITYREF + 1 ) ,
    WC_E_SYSTEMID	= ( WC_E_PI + 1 ) ,
    WC_E_QUESTIONMARK	= ( WC_E_SYSTEMID + 1 ) ,
    WC_E_CDSECTEND	= ( WC_E_QUESTIONMARK + 1 ) ,
    WC_E_MOREDATA	= ( WC_E_CDSECTEND + 1 ) ,
    WC_E_DTDPROHIBITED	= ( WC_E_MOREDATA + 1 ) ,
    WC_E_INVALIDXMLSPACE = ( WC_E_DTDPROHIBITED + 1 ) ,
    NC_E_NC		= 0xc00cee60,
    NC_E_QNAMECHARACTER = ( NC_E_NC + 1 ) ,
    NC_E_QNAMECOLON	= ( NC_E_QNAMECHARACTER + 1 ) ,
    NC_E_NAMECOLON	= ( NC_E_QNAMECOLON + 1 ) ,
    NC_E_DECLAREDPREFIX = ( NC_E_NAMECOLON + 1 ) ,
    NC_E_UNDECLAREDPREFIX = ( NC_E_DECLAREDPREFIX + 1 ) ,
    NC_E_EMPTYURI	= ( NC_E_UNDECLAREDPREFIX + 1 ) ,
    NC_E_XMLPREFIXRESERVED = ( NC_E_EMPTYURI + 1 ) ,
    NC_E_XMLNSPREFIXRESERVED = ( NC_E_XMLPREFIXRESERVED + 1 ) ,
    NC_E_XMLURIRESERVED = ( NC_E_XMLNSPREFIXRESERVED + 1 ) ,
    NC_E_XMLNSURIRESERVED = ( NC_E_XMLURIRESERVED + 1 ) ,
    SC_E_SC		= 0xc00cee80,
    SC_E_MAXELEMENTDEPTH = ( SC_E_SC + 1 ) ,
    SC_E_MAXENTITYEXPANSION = ( SC_E_MAXELEMENTDEPTH + 1 ) ,
    WR_E_WR		= 0xc00cef00,
    WR_E_NONWHITESPACE	= ( WR_E_WR + 1 ) ,
    WR_E_NSPREFIXDECLARED = ( WR_E_NONWHITESPACE + 1 ) ,
    WR_E_NSPREFIXWITHEMPTYNSURI = ( WR_E_NSPREFIXDECLARED + 1 ) ,
    WR_E_DUPLICATEATTRIBUTE	= ( WR_E_NSPREFIXWITHEMPTYNSURI + 1 ) ,
    WR_E_XMLNSPREFIXDECLARATION = ( WR_E_DUPLICATEATTRIBUTE + 1 ) ,
    WR_E_XMLPREFIXDECLARATION	= ( WR_E_XMLNSPREFIXDECLARATION + 1 ) ,
    WR_E_XMLURIDECLARATION	= ( WR_E_XMLPREFIXDECLARATION + 1 ) ,
    WR_E_XMLNSURIDECLARATION	= ( WR_E_XMLURIDECLARATION + 1 ) ,
    WR_E_NAMESPACEUNDECLARED	= ( WR_E_XMLNSURIDECLARATION + 1 ) ,
    WR_E_INVALIDXMLSPACE	= ( WR_E_NAMESPACEUNDECLARED + 1 ) ,
    WR_E_INVALIDACTION		= ( WR_E_INVALIDXMLSPACE + 1 ) ,
    WR_E_INVALIDSURROGATEPAIR	= ( WR_E_INVALIDACTION + 1 ) ,
    XML_E_INVALID_DECIMAL	= 0xc00ce01d,
    XML_E_INVALID_HEXIDECIMAL	= 0xc00ce01e,
    XML_E_INVALID_UNICODE	= 0xc00ce01f,
    XML_E_INVALIDENCODING	= 0xc00ce06e
    }

.enum XmlStandalone {
    XmlStandalone_Omit	= 0,
    XmlStandalone_Yes	= 1,
    XmlStandalone_No	= 2,
    _XmlStandalone_Last = 2
    }

.enum XmlWriterProperty {
    XmlWriterProperty_MultiLanguage	= 0,
    XmlWriterProperty_Indent		= ( XmlWriterProperty_MultiLanguage + 1 ) ,
    XmlWriterProperty_ByteOrderMark	= ( XmlWriterProperty_Indent + 1 ) ,
    XmlWriterProperty_OmitXmlDeclaration = ( XmlWriterProperty_ByteOrderMark + 1 ) ,
    XmlWriterProperty_ConformanceLevel	= ( XmlWriterProperty_OmitXmlDeclaration + 1 ) ,
    _XmlWriterProperty_Last		= XmlWriterProperty_OmitXmlDeclaration
    }


externdef LIBID_XmlLite:IID

ifndef __IXmlReader_INTERFACE_DEFINED__
define __IXmlReader_INTERFACE_DEFINED__

DEFINE_IIDX(IXmlReader, "7279FC81-709D-4095-B63D-69FE4B0D9030")

.comdef IXmlReader : public IUnknown

    SetInput		proc :ptr
    GetProperty		proc :UINT, :ptr
    SetProperty		proc :UINT, :LONG_PTR
    Read		proc :ptr
    GetNodeType		proc :ptr
    MoveToFirstAttribute proc
    MoveToNextAttribute proc
    MoveToAttributeByName proc :LPCWSTR, :LPCWSTR
    MoveToElement	proc
    GetQualifiedName	proc :LPCWSTR, :ptr UINT
    GetNamespaceUri	proc :LPCWSTR, :ptr UINT
    GetLocalName	proc :LPCWSTR, :ptr UINT
    GetPrefix		proc :LPCWSTR, :ptr UINT
    GetValue		proc :LPCWSTR, :ptr UINT
    ReadValueChunk	proc :ptr, :UINT, :ptr
    GetBaseUri		proc :LPCWSTR, :ptr UINT
    IsDefault		proc
    IsEmptyElement	proc
    GetLineNumber	proc :ptr
    GetLinePosition	proc :ptr
    GetAttributeCount	proc :ptr
    GetDepth		proc :ptr
    IsEOF		proc
   .ends

endif

ifndef __IXmlResolver_INTERFACE_DEFINED__
define __IXmlResolver_INTERFACE_DEFINED__

DEFINE_IIDX(IXmlResolver, "7279FC82-709D-4095-B63D-69FE4B0D9030")

.comdef IXmlResolver : public IUnknown

    ResolveUri		proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr
   .ends

endif

ifndef __IXmlWriter_INTERFACE_DEFINED__
define __IXmlWriter_INTERFACE_DEFINED__

DEFINE_IIDX(IXmlWriter, "7279FC88-709D-4095-B63D-69FE4B0D9030")

.comdef IXmlWriter : public IUnknown

    SetOutput		proc :ptr
    GetProperty		proc :UINT, :ptr
    SetProperty		proc :UINT, :LONG_PTR
    WriteAttributes	proc :ptr, :BOOL
    WriteAttributeString proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR
    WriteCData		proc :LPCWSTR
    WriteCharEntity	proc :WCHAR
    WriteChars		proc :ptr WCHAR, :UINT
    WriteComment	proc :LPCWSTR
    WriteDocType	proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR
    WriteElementString	proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR
    WriteEndDocument	proc
    WriteEndElement	proc
    WriteEntityRef	proc :LPCWSTR
    WriteFullEndElement proc
    WriteName		proc :LPCWSTR
    WriteNmToken	proc :LPCWSTR
    WriteNode		proc :ptr, :BOOL
    WriteNodeShallow	proc :ptr, :BOOL
    WriteProcessingInstruction proc :LPCWSTR, :LPCWSTR
    WriteQualifiedName	proc :LPCWSTR, :LPCWSTR
    WriteRaw		proc :LPCWSTR
    WriteRawChars	proc :ptr WCHAR, :UINT
    WriteStartDocument	proc :XmlStandalone
    WriteStartElement	proc :LPCWSTR, :LPCWSTR, :LPCWSTR
    WriteString		proc :LPCWSTR
    WriteSurrogateCharEntity proc :WCHAR, :WCHAR
    WriteWhitespace	proc :LPCWSTR
    Flush		proc
   .ends

endif
endif

ifndef __PE__
_IID_IXmlReader	  equ <{ 0x7279FC81, 0x709D, 0x4095, { 0xB6, 0x3D, 0x69, 0xFE, 0x4B, 0x0D, 0x90, 0x30 } }>
_IID_IXmlWriter	  equ <{ 0x7279FC88, 0x709D, 0x4095, { 0xB6, 0x3D, 0x69, 0xFE, 0x4B, 0x0D, 0x90, 0x30 } }>
_IID_IXmlResolver equ <{ 0x7279FC82, 0x709D, 0x4095, { 0xB6, 0x3D, 0x69, 0xFE, 0x4B, 0x0D, 0x90, 0x30 } }>
endif

endif
