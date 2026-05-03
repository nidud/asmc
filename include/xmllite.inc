ifndef _RPC500_
include rpc500.inc
endif
ifndef __xmllite_h__
define __xmllite_h_
ifndef __unknwn_h__
include unknwn.inc
endif
ifndef __objidl_h__
include objidl.inc
endif
ifndef __oaidl_h__
include oaidl.inc
endif

IXmlReaderInput		typedef IUnknown
IXmlWriterOutput	typedef IUnknown

.pragma comment(lib, xmllite)

CreateXmlReader proto WINAPI :REFIID, :ptr, :ptr
CreateXmlReaderInputWithEncodingCodePage proto WINAPI :ptr, :ptr, :UINT, :BOOL, :LPCWSTR, :ptr
CreateXmlReaderInputWithEncodingName proto WINAPI :ptr, :ptr, :LPCWSTR, :BOOL, :LPCWSTR, :ptr
CreateXmlWriter proto WINAPI :REFIID, :ptr, :ptr
CreateXmlWriterOutputWithEncodingCodePage proto WINAPI :ptr, :ptr, :UINT, :ptr
CreateXmlWriterOutputWithEncodingName proto WINAPI :ptr, :ptr, :LPCWSTR, :ptr

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
    XmlConformanceLevel_Auto,
    XmlConformanceLevel_Fragment,
    XmlConformanceLevel_Document,
    _XmlConformanceLevel_Last = 2
    }

.enum DtdProcessing {
    DtdProcessing_Prohibit,
    DtdProcessing_Parse,
    _DtdProcessing_Last = DtdProcessing_Parse
    }

.enum XmlReadState {
    XmlReadState_Initial,
    XmlReadState_Interactive,
    XmlReadState_Error,
    XmlReadState_EndOfFile,
    XmlReadState_Closed
    }

.enum XmlReaderProperty {
    XmlReaderProperty_MultiLanguage,
    XmlReaderProperty_ConformanceLevel,
    XmlReaderProperty_RandomAccess,
    XmlReaderProperty_XmlResolver,
    XmlReaderProperty_DtdProcessing,
    XmlReaderProperty_ReadState,
    XmlReaderProperty_MaxElementDepth,
    XmlReaderProperty_MaxEntityExpansion,
    _XmlReaderProperty_Last
    }

.enum XmlError {
    MX_E_MX		= 0xc00cee00,
    MX_E_INPUTEND,
    MX_E_ENCODING,
    MX_E_ENCODINGSWITCH,
    MX_E_ENCODINGSIGNATURE,
    WC_E_WC		= 0xc00cee20,
    WC_E_WHITESPACE,
    WC_E_SEMICOLON,
    WC_E_GREATERTHAN,
    WC_E_QUOTE,
    WC_E_EQUAL,
    WC_E_LESSTHAN,
    WC_E_HEXDIGIT,
    WC_E_DIGIT,
    WC_E_LEFTBRACKET,
    WC_E_LEFTPAREN,
    WC_E_XMLCHARACTER,
    WC_E_NAMECHARACTER,
    WC_E_SYNTAX,
    WC_E_CDSECT,
    WC_E_COMMENT,
    WC_E_CONDSECT,
    WC_E_DECLATTLIST,
    WC_E_DECLDOCTYPE,
    WC_E_DECLELEMENT,
    WC_E_DECLENTITY,
    WC_E_DECLNOTATION,
    WC_E_NDATA,
    WC_E_PUBLIC,
    WC_E_SYSTEM,
    WC_E_NAME,
    WC_E_ROOTELEMENT,
    WC_E_ELEMENTMATCH,
    WC_E_UNIQUEATTRIBUTE,
    WC_E_TEXTXMLDECL,
    WC_E_LEADINGXML,
    WC_E_TEXTDECL,
    WC_E_XMLDECL,
    WC_E_ENCNAME,
    WC_E_PUBLICID,
    WC_E_PESINTERNALSUBSET,
    WC_E_PESBETWEENDECLS,
    WC_E_NORECURSION,
    WC_E_ENTITYCONTENT,
    WC_E_UNDECLAREDENTITY,
    WC_E_PARSEDENTITY,
    WC_E_NOEXTERNALENTITYREF,
    WC_E_PI,
    WC_E_SYSTEMID,
    WC_E_QUESTIONMARK,
    WC_E_CDSECTEND,
    WC_E_MOREDATA,
    WC_E_DTDPROHIBITED,
    WC_E_INVALIDXMLSPACE,
    NC_E_NC		= 0xc00cee60,
    NC_E_QNAMECHARACTER,
    NC_E_QNAMECOLON,
    NC_E_NAMECOLON,
    NC_E_DECLAREDPREFIX,
    NC_E_UNDECLAREDPREFIX,
    NC_E_EMPTYURI,
    NC_E_XMLPREFIXRESERVED,
    NC_E_XMLNSPREFIXRESERVED,
    NC_E_XMLURIRESERVED,
    NC_E_XMLNSURIRESERVED,
    SC_E_SC		= 0xc00cee80,
    SC_E_MAXELEMENTDEPTH,
    SC_E_MAXENTITYEXPANSION,
    WR_E_WR		= 0xc00cef00,
    WR_E_NONWHITESPACE,
    WR_E_NSPREFIXDECLARED,
    WR_E_NSPREFIXWITHEMPTYNSURI,
    WR_E_DUPLICATEATTRIBUTE,
    WR_E_XMLNSPREFIXDECLARATION,
    WR_E_XMLPREFIXDECLARATION,
    WR_E_XMLURIDECLARATION,
    WR_E_XMLNSURIDECLARATION,
    WR_E_NAMESPACEUNDECLARED,
    WR_E_INVALIDXMLSPACE,
    WR_E_INVALIDACTION,
    WR_E_INVALIDSURROGATEPAIR,
    XML_E_INVALID_DECIMAL	= 0xc00ce01d,
    XML_E_INVALID_HEXIDECIMAL	= 0xc00ce01e,
    XML_E_INVALID_UNICODE	= 0xc00ce01f,
    XML_E_INVALIDENCODING	= 0xc00ce06e
    }

.enum XmlStandalone {
    XmlStandalone_Omit,
    XmlStandalone_Yes,
    XmlStandalone_No,
    _XmlStandalone_Last
    }

.enum XmlWriterProperty {
    XmlWriterProperty_MultiLanguage,
    XmlWriterProperty_Indent,
    XmlWriterProperty_ByteOrderMark,
    XmlWriterProperty_OmitXmlDeclaration,
    XmlWriterProperty_ConformanceLevel,
    _XmlWriterProperty_Last
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
    GetQualifiedName	proc :LPCWSTR, :ptr
    GetNamespaceUri	proc :LPCWSTR, :ptr
    GetLocalName	proc :LPCWSTR, :ptr
    GetPrefix		proc :LPCWSTR, :ptr
    GetValue		proc :LPCWSTR, :ptr
    ReadValueChunk	proc :ptr, :UINT, :ptr
    GetBaseUri		proc :LPCWSTR, :ptr
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
    WriteChars		proc :ptr, :UINT
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
    WriteRawChars	proc :ptr, :UINT
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
