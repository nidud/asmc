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
endif

ifndef __xmllite_h__
__xmllite_h__ equ 1

ifndef __IXmlReader_FWD_DEFINED__
__IXmlReader_FWD_DEFINED__ equ 1
endif
ifndef __IXmlResolver_FWD_DEFINED__
__IXmlResolver_FWD_DEFINED__ equ 1
endif
ifndef __IXmlWriter_FWD_DEFINED__
__IXmlWriter_FWD_DEFINED__ equ 1
endif

include unknwn.inc
include objidl.inc
include oaidl.inc

IXmlReaderInput		typedef IUnknown
IXmlWriterOutput	typedef IUnknown

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
__XmlLite_LIBRARY_DEFINED__ equ <>

XmlNodeType		typedef SDWORD
XmlNodeType_None	equ 0
XmlNodeType_Element	equ 1
XmlNodeType_Attribute	equ 2
XmlNodeType_Text	equ 3
XmlNodeType_CDATA	equ 4
XmlNodeType_ProcessingInstruction equ 7
XmlNodeType_Comment	equ 8
XmlNodeType_DocumentType equ 10
XmlNodeType_Whitespace	equ 13
XmlNodeType_EndElement	equ 15
XmlNodeType_XmlDeclaration equ 17
_XmlNodeType_Last	equ 17

XmlConformanceLevel	typedef SDWORD
XmlConformanceLevel_Auto equ 0
XmlConformanceLevel_Fragment equ 1
XmlConformanceLevel_Document equ 2
_XmlConformanceLevel_Last equ 2

DtdProcessing		typedef SDWORD
DtdProcessing_Prohibit	equ 0
DtdProcessing_Parse	equ ( DtdProcessing_Prohibit + 1 )
_DtdProcessing_Last	equ DtdProcessing_Parse

XmlReadState		typedef SDWORD
XmlReadState_Initial	equ 0
XmlReadState_Interactive equ 1
XmlReadState_Error	equ 2
XmlReadState_EndOfFile	equ 3
XmlReadState_Closed	equ 4

XmlReaderProperty	typedef SDWORD
XmlReaderProperty_MultiLanguage equ 0
XmlReaderProperty_ConformanceLevel equ ( XmlReaderProperty_MultiLanguage + 1 )
XmlReaderProperty_RandomAccess equ ( XmlReaderProperty_ConformanceLevel + 1 )
XmlReaderProperty_XmlResolver equ ( XmlReaderProperty_RandomAccess + 1 )
XmlReaderProperty_DtdProcessing equ ( XmlReaderProperty_XmlResolver + 1 )
XmlReaderProperty_ReadState equ ( XmlReaderProperty_DtdProcessing + 1 )
XmlReaderProperty_MaxElementDepth equ ( XmlReaderProperty_ReadState + 1 )
XmlReaderProperty_MaxEntityExpansion equ ( XmlReaderProperty_MaxElementDepth + 1 )
_XmlReaderProperty_Last equ XmlReaderProperty_MaxEntityExpansion

XmlError		typedef SDWORD
MX_E_MX			equ 0xc00cee00
MX_E_INPUTEND		equ ( MX_E_MX + 1 )
MX_E_ENCODING		equ ( MX_E_INPUTEND + 1 )
MX_E_ENCODINGSWITCH	equ ( MX_E_ENCODING + 1 )
MX_E_ENCODINGSIGNATURE	equ ( MX_E_ENCODINGSWITCH + 1 )
WC_E_WC			equ 0xc00cee20
WC_E_WHITESPACE		equ ( WC_E_WC + 1 )
WC_E_SEMICOLON		equ ( WC_E_WHITESPACE + 1 )
WC_E_GREATERTHAN	equ ( WC_E_SEMICOLON + 1 )
WC_E_QUOTE		equ ( WC_E_GREATERTHAN + 1 )
WC_E_EQUAL		equ ( WC_E_QUOTE + 1 )
WC_E_LESSTHAN		equ ( WC_E_EQUAL + 1 )
WC_E_HEXDIGIT		equ ( WC_E_LESSTHAN + 1 )
WC_E_DIGIT		equ ( WC_E_HEXDIGIT + 1 )
WC_E_LEFTBRACKET	equ ( WC_E_DIGIT + 1 )
WC_E_LEFTPAREN		equ ( WC_E_LEFTBRACKET + 1 )
WC_E_XMLCHARACTER	equ ( WC_E_LEFTPAREN + 1 )
WC_E_NAMECHARACTER	equ ( WC_E_XMLCHARACTER + 1 )
WC_E_SYNTAX		equ ( WC_E_NAMECHARACTER + 1 )
WC_E_CDSECT		equ ( WC_E_SYNTAX + 1 )
WC_E_COMMENT		equ ( WC_E_CDSECT + 1 )
WC_E_CONDSECT		equ ( WC_E_COMMENT + 1 )
WC_E_DECLATTLIST	equ ( WC_E_CONDSECT + 1 )
WC_E_DECLDOCTYPE	equ ( WC_E_DECLATTLIST + 1 )
WC_E_DECLELEMENT	equ ( WC_E_DECLDOCTYPE + 1 )
WC_E_DECLENTITY		equ ( WC_E_DECLELEMENT + 1 )
WC_E_DECLNOTATION	equ ( WC_E_DECLENTITY + 1 )
WC_E_NDATA		equ ( WC_E_DECLNOTATION + 1 )
WC_E_PUBLIC		equ ( WC_E_NDATA + 1 )
WC_E_SYSTEM		equ ( WC_E_PUBLIC + 1 )
WC_E_NAME		equ ( WC_E_SYSTEM + 1 )
WC_E_ROOTELEMENT	equ ( WC_E_NAME + 1 )
WC_E_ELEMENTMATCH	equ ( WC_E_ROOTELEMENT + 1 )
WC_E_UNIQUEATTRIBUTE	equ ( WC_E_ELEMENTMATCH + 1 )
WC_E_TEXTXMLDECL	equ ( WC_E_UNIQUEATTRIBUTE + 1 )
WC_E_LEADINGXML		equ ( WC_E_TEXTXMLDECL + 1 )
WC_E_TEXTDECL		equ ( WC_E_LEADINGXML + 1 )
WC_E_XMLDECL		equ ( WC_E_TEXTDECL + 1 )
WC_E_ENCNAME		equ ( WC_E_XMLDECL + 1 )
WC_E_PUBLICID		equ ( WC_E_ENCNAME + 1 )
WC_E_PESINTERNALSUBSET	equ ( WC_E_PUBLICID + 1 )
WC_E_PESBETWEENDECLS	equ ( WC_E_PESINTERNALSUBSET + 1 )
WC_E_NORECURSION	equ ( WC_E_PESBETWEENDECLS + 1 )
WC_E_ENTITYCONTENT	equ ( WC_E_NORECURSION + 1 )
WC_E_UNDECLAREDENTITY	equ ( WC_E_ENTITYCONTENT + 1 )
WC_E_PARSEDENTITY	equ ( WC_E_UNDECLAREDENTITY + 1 )
WC_E_NOEXTERNALENTITYREF equ ( WC_E_PARSEDENTITY + 1 )
WC_E_PI			equ ( WC_E_NOEXTERNALENTITYREF + 1 )
WC_E_SYSTEMID		equ ( WC_E_PI + 1 )
WC_E_QUESTIONMARK	equ ( WC_E_SYSTEMID + 1 )
WC_E_CDSECTEND		equ ( WC_E_QUESTIONMARK + 1 )
WC_E_MOREDATA		equ ( WC_E_CDSECTEND + 1 )
WC_E_DTDPROHIBITED	equ ( WC_E_MOREDATA + 1 )
WC_E_INVALIDXMLSPACE	equ ( WC_E_DTDPROHIBITED + 1 )
NC_E_NC			equ 0xc00cee60
NC_E_QNAMECHARACTER	equ ( NC_E_NC + 1 )
NC_E_QNAMECOLON		equ ( NC_E_QNAMECHARACTER + 1 )
NC_E_NAMECOLON		equ ( NC_E_QNAMECOLON + 1 )
NC_E_DECLAREDPREFIX	equ ( NC_E_NAMECOLON + 1 )
NC_E_UNDECLAREDPREFIX	equ ( NC_E_DECLAREDPREFIX + 1 )
NC_E_EMPTYURI		equ ( NC_E_UNDECLAREDPREFIX + 1 )
NC_E_XMLPREFIXRESERVED	equ ( NC_E_EMPTYURI + 1 )
NC_E_XMLNSPREFIXRESERVED equ ( NC_E_XMLPREFIXRESERVED + 1 )
NC_E_XMLURIRESERVED	equ ( NC_E_XMLNSPREFIXRESERVED + 1 )
NC_E_XMLNSURIRESERVED	equ ( NC_E_XMLURIRESERVED + 1 )
SC_E_SC			equ 0xc00cee80
SC_E_MAXELEMENTDEPTH	equ ( SC_E_SC + 1 )
SC_E_MAXENTITYEXPANSION equ ( SC_E_MAXELEMENTDEPTH + 1 )
WR_E_WR			equ 0xc00cef00
WR_E_NONWHITESPACE	equ ( WR_E_WR + 1 )
WR_E_NSPREFIXDECLARED	equ ( WR_E_NONWHITESPACE + 1 )
WR_E_NSPREFIXWITHEMPTYNSURI equ ( WR_E_NSPREFIXDECLARED + 1 )
WR_E_DUPLICATEATTRIBUTE equ ( WR_E_NSPREFIXWITHEMPTYNSURI + 1 )
WR_E_XMLNSPREFIXDECLARATION equ ( WR_E_DUPLICATEATTRIBUTE + 1 )
WR_E_XMLPREFIXDECLARATION equ ( WR_E_XMLNSPREFIXDECLARATION + 1 )
WR_E_XMLURIDECLARATION	equ ( WR_E_XMLPREFIXDECLARATION + 1 )
WR_E_XMLNSURIDECLARATION equ ( WR_E_XMLURIDECLARATION + 1 )
WR_E_NAMESPACEUNDECLARED equ ( WR_E_XMLNSURIDECLARATION + 1 )
WR_E_INVALIDXMLSPACE	equ ( WR_E_NAMESPACEUNDECLARED + 1 )
WR_E_INVALIDACTION	equ ( WR_E_INVALIDXMLSPACE + 1 )
WR_E_INVALIDSURROGATEPAIR equ ( WR_E_INVALIDACTION + 1 )
XML_E_INVALID_DECIMAL	equ 0xc00ce01d
XML_E_INVALID_HEXIDECIMAL equ 0xc00ce01e
XML_E_INVALID_UNICODE	equ 0xc00ce01f
XML_E_INVALIDENCODING	equ 0xc00ce06e

XmlStandalone		typedef SDWORD
XmlStandalone_Omit	equ 0
XmlStandalone_Yes	equ 1
XmlStandalone_No	equ 2
_XmlStandalone_Last	equ 2

XmlWriterProperty	typedef SDWORD
XmlWriterProperty_MultiLanguage equ 0
XmlWriterProperty_Indent equ ( XmlWriterProperty_MultiLanguage + 1 )
XmlWriterProperty_ByteOrderMark equ ( XmlWriterProperty_Indent + 1 )
XmlWriterProperty_OmitXmlDeclaration equ ( XmlWriterProperty_ByteOrderMark + 1 )
XmlWriterProperty_ConformanceLevel equ ( XmlWriterProperty_OmitXmlDeclaration + 1 )
_XmlWriterProperty_Last equ XmlWriterProperty_OmitXmlDeclaration


externdef		LIBID_XmlLite:IID

ifndef __IXmlReader_INTERFACE_DEFINED__
__IXmlReader_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXmlReader, "7279FC81-709D-4095-B63D-69FE4B0D9030")

.comdef IXmlReader

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetInput		proc :ptr
    GetProperty		proc :UINT, :ptr
    SetProperty		proc :UINT, :LONG_PTR
    Read		proc :ptr
    GetNodeType		proc :ptr
    MoveToFirstAttribute proc
    MoveToNextAttribute proc
    MoveToAttributeByName proc :LPCWSTR, :LPCWSTR
    MoveToElement	proc
    GetQualifiedName	proc
    GetNamespaceUri	proc
    GetLocalName	proc
    GetPrefix		proc
    GetValue		proc
    ReadValueChunk	proc :ptr, :UINT, :ptr
    GetBaseUri		proc
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
__IXmlResolver_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IXmlResolver, "7279FC82-709D-4095-B63D-69FE4B0D9030")

.comdef IXmlResolver

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ResolveUri		proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr
    .ends

endif

ifndef __IXmlWriter_INTERFACE_DEFINED__
__IXmlWriter_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IXmlWriter, "7279FC88-709D-4095-B63D-69FE4B0D9030")

.comdef IXmlWriter

    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetOutput		proc :ptr
    GetProperty		proc :UINT, :ptr
    SetProperty		proc :UINT, :LONG_PTR
    WriteAttributes	proc :ptr, :BOOL
    WriteAttributeString proc :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR
    WriteCData		proc :LPCWSTR
    WriteCharEntity	proc :WCHAR
    WriteChars		proc
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
    WriteRawChars	proc
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
_IID_IXmlReader		equ <{ 0x7279FC81, 0x709D, 0x4095, { 0xB6, 0x3D, 0x69, 0xFE, 0x4B, 0x0D, 0x90, 0x30 } }>
_IID_IXmlWriter		equ <{ 0x7279FC88, 0x709D, 0x4095, { 0xB6, 0x3D, 0x69, 0xFE, 0x4B, 0x0D, 0x90, 0x30 } }>
_IID_IXmlResolver	equ <{ 0x7279FC82, 0x709D, 0x4095, { 0xB6, 0x3D, 0x69, 0xFE, 0x4B, 0x0D, 0x90, 0x30 } }>
endif

endif
