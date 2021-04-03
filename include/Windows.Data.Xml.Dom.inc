ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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

ifndef __windows2Edata2Exml2Edom_h__
__windows2Edata2Exml2Edom_h__ equ 1

ifndef ____FIIterator_1_Windows__CData__CXml__CDom__CIXmlNode_FWD_DEFINED__
____FIIterator_1_Windows__CData__CXml__CDom__CIXmlNode_FWD_DEFINED__ equ 1
endif
ifndef ____FIIterable_1_Windows__CData__CXml__CDom__CIXmlNode_FWD_DEFINED__
____FIIterable_1_Windows__CData__CXml__CDom__CIXmlNode_FWD_DEFINED__ equ 1
endif
ifndef ____FIVectorView_1_Windows__CData__CXml__CDom__CIXmlNode_FWD_DEFINED__
____FIVectorView_1_Windows__CData__CXml__CDom__CIXmlNode_FWD_DEFINED__ equ 1
endif
ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CData__CXml__CDom__CXmlDocument_FWD_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CData__CXml__CDom__CXmlDocument_FWD_DEFINED__ equ 1
endif
ifndef ____FIAsyncOperation_1_Windows__CData__CXml__CDom__CXmlDocument_FWD_DEFINED__
____FIAsyncOperation_1_Windows__CData__CXml__CDom__CXmlDocument_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSelector_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSelector_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSerializer_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSerializer_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNode_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNode_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDomImplementation_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDomImplementation_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentType_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentType_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlAttribute_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlAttribute_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentFragment_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentFragment_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlElement_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlElement_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIDtdNotation_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIDtdNotation_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIDtdEntity_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIDtdEntity_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlEntityReference_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlEntityReference_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlProcessingInstruction_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlProcessingInstruction_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlCharacterData_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlCharacterData_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlComment_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlComment_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlText_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlText_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlCDataSection_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlCDataSection_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNamedNodeMap_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNamedNodeMap_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeList_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeList_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlLoadSettings_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlLoadSettings_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO_FWD_DEFINED__ equ 1
endif
ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentStatics_FWD_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentStatics_FWD_DEFINED__ equ 1
endif

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc

include windows.foundation.collections.inc

ifndef DEF___FIIterator_1_Windows__CData__CXml__CDom__CIXmlNode_USE
DEF___FIIterator_1_Windows__CData__CXml__CDom__CIXmlNode_USE equ 1

DEFINE_IIDX(__FIIterator_1_Windows__CData__CXml__CDom__CIXmlNode, "3833a35e-2c61-56bd-b093-3694165f8898")

.comdef __FIIterator_1_Windows__CData__CXml__CDom__CIXmlNode : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
    .ends

endif

ifndef ____FIIterable_1_Windows__CData__CXml__CDom__CIXmlNode_INTERFACE_DEFINED__
____FIIterable_1_Windows__CData__CXml__CDom__CIXmlNode_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIIterable_1_Windows__CData__CXml__CDom__CIXmlNode, "f1146ffc-8c92-56e8-93f1-711f86722633")

.comdef __FIIterable_1_Windows__CData__CXml__CDom__CIXmlNode : public IInspectable

    First		proc :ptr
    .ends

endif

ifndef ____FIVectorView_1_Windows__CData__CXml__CDom__CIXmlNode_INTERFACE_DEFINED__
____FIVectorView_1_Windows__CData__CXml__CDom__CIXmlNode_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIVectorView_1_Windows__CData__CXml__CDom__CIXmlNode, "139d959e-e7b5-5cb6-a596-4b544478da9b")

.comdef __FIVectorView_1_Windows__CData__CXml__CDom__CIXmlNode : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
    .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CData__CXml__CDom__CXmlDocument_INTERFACE_DEFINED__
____FIAsyncOperationCompletedHandler_1_Windows__CData__CXml__CDom__CXmlDocument_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CData__CXml__CDom__CXmlDocument, "5eef7817-93dd-5c0b-9e5a-eb490408f3a9")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CData__CXml__CDom__CXmlDocument : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
    .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CData__CXml__CDom__CXmlDocument_INTERFACE_DEFINED__
____FIAsyncOperation_1_Windows__CData__CXml__CDom__CXmlDocument_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__FIAsyncOperation_1_Windows__CData__CXml__CDom__CXmlDocument, "f858e239-1896-5982-8495-143168478eb8")

.comdef __FIAsyncOperation_1_Windows__CData__CXml__CDom__CXmlDocument : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
    .ends

endif

.enum _x_ABI_CWindows_CData_CXml_CDom_CNodeType {
    NodeType_Invalid		= 0,
    NodeType_ElementNode	= 1,
    NodeType_AttributeNode	= 2,
    NodeType_TextNode		= 3,
    NodeType_DataSectionNode	= 4,
    NodeType_EntityReferenceNode = 5,
    NodeType_EntityNode		= 6,
    NodeType_ProcessingInstructionNode = 7,
    NodeType_CommentNode	= 8,
    NodeType_DocumentNode	= 9,
    NodeType_DocumentTypeNode	= 10,
    NodeType_DocumentFragmentNode = 11,
    NodeType_NotationNode	= 12
    }

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSelector_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSelector_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSelector, "63DBBA8B-D0DB-4FE1-B745-F9433AFDC25B")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSelector : public IInspectable

    SelectSingleNode	proc :HSTRING, :ptr
    SelectNodes		proc :HSTRING, :ptr
    SelectSingleNodeNS	proc :HSTRING, :ptr, :ptr
    SelectNodesNS	proc :HSTRING, :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSerializer_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSerializer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSerializer, "5CC5B382-E6DD-4991-ABEF-06D8D2E7BD0C")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeSerializer : public IInspectable

    GetXml		proc :ptr
    get_InnerText	proc :ptr
    put_InnerText	proc :HSTRING
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNode_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNode_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlNode, "1C741D59-2122-47D5-A856-83F3D4214875")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlNode : public IInspectable

    get_NodeValue	proc :ptr
    put_NodeValue	proc :ptr
    get_NodeType	proc :ptr
    get_NodeName	proc :ptr
    get_ParentNode	proc :ptr
    get_ChildNodes	proc :ptr
    get_FirstChild	proc :ptr
    get_LastChild	proc :ptr
    get_PreviousSibling proc :ptr
    get_NextSibling	proc :ptr
    get_Attributes	proc :ptr
    HasChildNodes	proc :ptr
    get_OwnerDocument	proc :ptr
    InsertBefore	proc :ptr, :ptr, :ptr
    ReplaceChild	proc :ptr, :ptr, :ptr
    RemoveChild		proc :ptr, :ptr
    AppendChild		proc :ptr, :ptr
    CloneNode		proc :boolean, :ptr
    get_NamespaceUri	proc :ptr
    get_LocalName	proc :ptr
    get_Prefix		proc :ptr
    Normalize		proc
    put_Prefix		proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDomImplementation_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDomImplementation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlDomImplementation, "6DE58132-F11D-4FBB-8CC6-583CBA93112F")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlDomImplementation : public IInspectable

    HasFeature		proc :HSTRING, :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentType_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentType_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentType, "F7342425-9781-4964-8E94-9B1C6DFC9BC7")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentType : public IInspectable

    get_Name		proc :ptr
    get_Entities	proc :ptr
    get_Notations	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlAttribute_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlAttribute_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlAttribute, "AC144AA4-B4F1-4DB6-B206-8A22C308DB0A")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlAttribute : public IInspectable

    get_Name		proc :ptr
    get_Specified	proc :ptr
    get_Value		proc :ptr
    put_Value		proc :HSTRING
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentFragment_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentFragment_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentFragment, "E2EA6A96-0C21-44A5-8BC9-9E4A262708EC")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentFragment : public IInspectable

    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlElement_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlElement_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlElement, "2DFB8A1F-6B10-4EF8-9F83-EFCCE8FAEC37")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlElement : public IInspectable

    get_TagName		proc :ptr
    GetAttribute	proc :HSTRING, :ptr
    SetAttribute	proc :HSTRING, :HSTRING
    RemoveAttribute	proc :HSTRING
    GetAttributeNode	proc :HSTRING, :ptr
    SetAttributeNode	proc :ptr, :ptr
    RemoveAttributeNode proc :ptr, :ptr
    GetElementsByTagName proc :HSTRING, :ptr
    SetAttributeNS	proc :ptr, :HSTRING, :HSTRING
    GetAttributeNS	proc :ptr, :HSTRING, :ptr
    RemoveAttributeNS	proc :ptr, :HSTRING
    SetAttributeNodeNS	proc :ptr, :ptr
    GetAttributeNodeNS	proc :ptr, :HSTRING, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIDtdNotation_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIDtdNotation_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIDtdNotation, "8CB4E04D-6D46-4EDB-AB73-DF83C51AD397")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIDtdNotation : public IInspectable

    get_PublicId	proc :ptr
    get_SystemId	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIDtdEntity_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIDtdEntity_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIDtdEntity, "6A0B5FFC-63B4-480F-9E6A-8A92816AADE4")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIDtdEntity : public IInspectable

    get_PublicId	proc :ptr
    get_SystemId	proc :ptr
    get_NotationName	proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlEntityReference_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlEntityReference_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlEntityReference, "2E2F47BC-C3D0-4CCF-BB86-0AB8C36A61CF")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlEntityReference : public IInspectable

    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlProcessingInstruction_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlProcessingInstruction_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlProcessingInstruction, "2707FD1E-1E92-4ECE-B6F4-26F069078DDC")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlProcessingInstruction : public IInspectable

    get_Target		proc :ptr
    get_Data		proc :ptr
    put_Data		proc :HSTRING
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlCharacterData_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlCharacterData_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlCharacterData, "132E42AB-4E36-4DF6-B1C8-0CE62FD88B26")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlCharacterData : public IInspectable

    get_Data		proc :ptr
    put_Data		proc :HSTRING
    get_Length		proc :ptr
    SubstringData	proc :UINT32, :UINT32, :ptr
    AppendData		proc :HSTRING
    InsertData		proc :UINT32, :HSTRING
    DeleteData		proc :UINT32, :UINT32
    ReplaceData		proc :UINT32, :UINT32, :HSTRING
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlComment_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlComment_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlComment, "BCA474D5-B61F-4611-9CAC-2E92E3476D47")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlComment : public IInspectable

    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlText_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlText_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlText, "F931A4CB-308D-4760-A1D5-43B67450AC7E")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlText : public IInspectable

    SplitText		proc :UINT32, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlCDataSection_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlCDataSection_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlCDataSection, "4D04B46F-C8BD-45B4-8899-0400D7C2C60F")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlCDataSection : public IInspectable

    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument, "F7F3A506-1E87-42D6-BCFB-B8C809FA5494")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocument : public IInspectable

    get_Doctype		proc :ptr
    get_Implementation	proc :ptr
    get_DocumentElement proc :ptr
    CreateElement	proc :HSTRING, :ptr
    CreateDocumentFragment proc :ptr
    CreateTextNode	proc :HSTRING, :ptr
    CreateComment	proc :HSTRING, :ptr
    CreateProcessingInstruction proc :HSTRING, :HSTRING, :ptr
    CreateAttribute	proc :HSTRING, :ptr
    CreateEntityReference proc :HSTRING, :ptr
    GetElementsByTagName proc :HSTRING, :ptr
    CreateCDataSection	proc :HSTRING, :ptr
    get_DocumentUri	proc :ptr
    CreateAttributeNS	proc :ptr, :HSTRING, :ptr
    CreateElementNS	proc :ptr, :HSTRING, :ptr
    GetElementById	proc :HSTRING, :ptr
    ImportNode		proc :ptr, :boolean, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNamedNodeMap_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNamedNodeMap_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlNamedNodeMap, "B3A69EB0-AAB0-4B82-A6FA-B1453F7C021B")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlNamedNodeMap : public IInspectable

    get_Length		proc :ptr
    Item		proc :UINT32, :ptr
    GetNamedItem	proc :HSTRING, :ptr
    SetNamedItem	proc :ptr, :ptr
    RemoveNamedItem	proc :HSTRING, :ptr
    GetNamedItemNS	proc :ptr, :HSTRING, :ptr
    RemoveNamedItemNS	proc :ptr, :HSTRING, :ptr
    SetNamedItemNS	proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeList_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeList_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeList, "8C60AD77-83A4-4EC1-9C54-7BA429E13DA6")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlNodeList : public IInspectable

    get_Length		proc :ptr
    Item		proc :UINT32, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlLoadSettings_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlLoadSettings_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlLoadSettings, "58AA07A8-FED6-46F7-B4C5-FB1BA72108D6")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlLoadSettings : public IInspectable

    get_MaxElementDepth proc :ptr
    put_MaxElementDepth proc :UINT32
    get_ProhibitDtd	proc :ptr
    put_ProhibitDtd	proc :boolean
    get_ResolveExternals proc :ptr
    put_ResolveExternals proc :boolean
    get_ValidateOnParse proc :ptr
    put_ValidateOnParse proc :boolean
    get_ElementContentWhiteSpace proc :ptr
    put_ElementContentWhiteSpace proc :boolean
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO, "6CD0E74E-EE65-4489-9EBF-CA43E87BA637")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentIO : public IInspectable

    LoadXml		proc :HSTRING
    LoadXmlWithSettings proc :HSTRING, :ptr
    SaveToFileAsync	proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentStatics_INTERFACE_DEFINED__
____x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentStatics_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(__x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentStatics, "5543D254-D757-4B79-9539-232B18F50BF1")

.comdef __x_ABI_CWindows_CData_CXml_CDom_CIXmlDocumentStatics : public IInspectable

    LoadFromUriAsync	proc :ptr, :ptr
    LoadFromUriWithSettingsAsync proc :ptr, :ptr, :ptr
    LoadFromFileAsync	proc :ptr, :ptr
    LoadFromFileWithSettingsAsync proc :ptr, :ptr, :ptr
    .ends

endif

HSTRING_UserSize proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HSTRING

HSTRING_UserMarshal proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserUnmarshal proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserFree proto WINAPI \
		      : ptr DWORD,
		      : ptr HSTRING


HSTRING_UserSize64 proto WINAPI \
		      : ptr DWORD,
		      : DWORD,
		      : ptr HSTRING

HSTRING_UserMarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserUnmarshal64 proto WINAPI \
		      : ptr DWORD,
		      : LPBYTE,
		      : ptr HSTRING

HSTRING_UserFree64 proto WINAPI \
		      : ptr DWORD,
		      : ptr HSTRING

endif
