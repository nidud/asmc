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

ifndef __windows2Edata2Etext_h__
define __windows2Edata2Etext_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CData__CText__CAlternateWordForm_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CData__CText__CAlternateWordForm_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CData__CText__CAlternateWordForm, "7f463f8a-e08f-516e-b4b8-81b5417bfb58")

.comdef __FIIterator_1_Windows__CData__CText__CAlternateWordForm : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CData__CText__CAlternateWordForm_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CData__CText__CAlternateWordForm_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CData__CText__CAlternateWordForm, "ae838c29-60c1-5093-ae61-0ed22857db05")

.comdef __FIIterable_1_Windows__CData__CText__CAlternateWordForm : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CData__CText__CSelectableWordSegment_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CData__CText__CSelectableWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CData__CText__CSelectableWordSegment, "a5842459-147d-5a88-8f23-a3398afd8a85")

.comdef __FIIterator_1_Windows__CData__CText__CSelectableWordSegment : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CData__CText__CSelectableWordSegment_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CData__CText__CSelectableWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CData__CText__CSelectableWordSegment, "784b0cec-1348-5334-91e5-2e013294e211")

.comdef __FIIterable_1_Windows__CData__CText__CSelectableWordSegment : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CData__CText__CTextSegment, "645a39b4-f001-5272-9015-fb4a327179ae")

.comdef __FIIterator_1_Windows__CData__CText__CTextSegment : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CData__CText__CTextSegment, "5498f4f3-cee4-5b72-9729-815c4ad7b9dc")

.comdef __FIIterable_1_Windows__CData__CText__CTextSegment : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CData__CText__CWordSegment_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CData__CText__CWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CData__CText__CWordSegment, "aeb846b3-664b-545e-ab93-f5fc66d24e32")

.comdef __FIIterator_1_Windows__CData__CText__CWordSegment : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CData__CText__CWordSegment_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CData__CText__CWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CData__CText__CWordSegment, "d14dc94a-a311-5ddc-bf8b-d58795d87d6d")

.comdef __FIIterable_1_Windows__CData__CText__CWordSegment : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CData__CText__CTextSegment, "2f245f9d-eb5f-5641-9dcc-6ab1946cc7e6")

.comdef __FIVectorView_1_Windows__CData__CText__CTextSegment : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment, "77b4daf4-4f4f-5568-90ee-1a32cf0caaea")

.comdef __FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment : public IInspectable

    get_Key		proc :ptr
    get_Value		proc :ptr
   .ends

endif

ifndef ____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIIterator_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment, "00078aa3-8676-5f06-adf5-ffe5d661d670")

.comdef __FIIterator_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIIterable_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment, "f819a276-b3f5-54d4-b8fd-c9adb7f700e3")

.comdef __FIIterable_1___FIKeyValuePair_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIMapView_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIMapView_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMapView_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment, "91d443d6-3777-5102-b0bc-3d4183a26ff9")

.comdef __FIMapView_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    Split		proc :ptr, :ptr
   .ends

endif

ifndef ____FIMap_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__
define ____FIMap_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIMap_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment, "a31b6540-b2b1-536d-818f-8ade7051c3b3")

.comdef __FIMap_2_HSTRING___FIVectorView_1_Windows__CData__CText__CTextSegment : public IInspectable

    Lookup		proc :HSTRING, :ptr
    get_Size		proc :dword
    HasKey		proc :HSTRING, :ptr
    GetView		proc :ptr
    Insert		proc :HSTRING, :ptr, :ptr
    Remove		proc :HSTRING
    Clear		proc
   .ends

endif

ifndef ____FIVectorView_1_Windows__CData__CText__CAlternateWordForm_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CData__CText__CAlternateWordForm_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CData__CText__CAlternateWordForm, "6b742ff2-746a-5545-a6ed-3bba453cf5d9")

.comdef __FIVectorView_1_Windows__CData__CText__CAlternateWordForm : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CData__CText__CSelectableWordSegment_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CData__CText__CSelectableWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CData__CText__CSelectableWordSegment, "33f90a72-86f4-5027-b50a-6939a1f9d560")

.comdef __FIVectorView_1_Windows__CData__CText__CSelectableWordSegment : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIVectorView_1_Windows__CData__CText__CWordSegment_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CData__CText__CWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CData__CText__CWordSegment, "c706749a-e11d-5e07-8534-2bd23ec210f9")

.comdef __FIVectorView_1_Windows__CData__CText__CWordSegment : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :dword
    IndexOf		proc :ptr, :dword, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :dword
   .ends

endif

.namespace Windows
.namespace Data
.namespace Text

.enum UnicodeGeneralCategory {
    UnicodeGeneralCategory_UppercaseLetter,
    UnicodeGeneralCategory_LowercaseLetter,
    UnicodeGeneralCategory_TitlecaseLetter,
    UnicodeGeneralCategory_ModifierLetter,
    UnicodeGeneralCategory_OtherLetter,
    UnicodeGeneralCategory_NonspacingMark,
    UnicodeGeneralCategory_SpacingCombiningMark,
    UnicodeGeneralCategory_EnclosingMark,
    UnicodeGeneralCategory_DecimalDigitNumber,
    UnicodeGeneralCategory_LetterNumber,
    UnicodeGeneralCategory_OtherNumber,
    UnicodeGeneralCategory_SpaceSeparator,
    UnicodeGeneralCategory_LineSeparator,
    UnicodeGeneralCategory_ParagraphSeparator,
    UnicodeGeneralCategory_Control,
    UnicodeGeneralCategory_Format,
    UnicodeGeneralCategory_Surrogate,
    UnicodeGeneralCategory_PrivateUse,
    UnicodeGeneralCategory_ConnectorPunctuation,
    UnicodeGeneralCategory_DashPunctuation,
    UnicodeGeneralCategory_OpenPunctuation,
    UnicodeGeneralCategory_ClosePunctuation,
    UnicodeGeneralCategory_InitialQuotePunctuation,
    UnicodeGeneralCategory_FinalQuotePunctuation,
    UnicodeGeneralCategory_OtherPunctuation,
    UnicodeGeneralCategory_MathSymbol,
    UnicodeGeneralCategory_CurrencySymbol,
    UnicodeGeneralCategory_ModifierSymbol,
    UnicodeGeneralCategory_OtherSymbol,
    UnicodeGeneralCategory_NotAssigned
    }

.enum UnicodeNumericType {
    UnicodeNumericType_None,
    UnicodeNumericType_Decimal,
    UnicodeNumericType_Digit,
    UnicodeNumericType_Numeric
    }

.enum AlternateNormalizationFormat {
    AlternateNormalizationFormat_NotNormalized,
    AlternateNormalizationFormat_Number,
    AlternateNormalizationFormat_Currency,
    AlternateNormalizationFormat_Date,
    AlternateNormalizationFormat_Time
    }

.template TextSegment
    StartPosition	UINT32 ?
    Length		UINT32 ?
   .ends


ifndef ____x_ABI_CWindows_CData_CText_CIWordSegmentsTokenizingHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CIWordSegmentsTokenizingHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IWordSegmentsTokenizingHandler, "A5DD6357-BF2A-4C4F-A31F-29E71C6F8B35")

.comdef IWordSegmentsTokenizingHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CISelectableWordSegmentsTokenizingHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CISelectableWordSegmentsTokenizingHandler_INTERFACE_DEFINED__

DEFINE_IIDX(ISelectableWordSegmentsTokenizingHandler, "3A3DFC9C-AEDE-4DC7-9E6C-41C044BD3592")

.comdef ISelectableWordSegmentsTokenizingHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CISemanticTextQueryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CISemanticTextQueryFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ISemanticTextQueryFactory, "238C0503-F995-4587-8777-A2B7D80ACFEF")

.comdef ISemanticTextQueryFactory : public IInspectable

    Create		proc :HSTRING, :ptr
    CreateWithLanguage	proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CISemanticTextQuery_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CISemanticTextQuery_INTERFACE_DEFINED__

DEFINE_IIDX(ISemanticTextQuery, "6A1CAB51-1FB2-4909-80B8-35731A2B3E7F")

.comdef ISemanticTextQuery : public IInspectable

    Find		proc :HSTRING, :ptr
    FindInProperty	proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CIUnicodeCharactersStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CIUnicodeCharactersStatics_INTERFACE_DEFINED__

DEFINE_IIDX(IUnicodeCharactersStatics, "97909E87-9291-4F91-B6C8-B6E359D7A7FB")

.comdef IUnicodeCharactersStatics : public IInspectable

    GetCodepointFromSurrogatePair proc :UINT32, :UINT32, :ptr
    GetSurrogatePairFromCodepoint proc :UINT32, :ptr, :ptr
    IsHighSurrogate	proc :UINT32, :ptr
    IsLowSurrogate	proc :UINT32, :ptr
    IsSupplementary	proc :UINT32, :ptr
    IsNoncharacter	proc :UINT32, :ptr
    IsWhitespace	proc :UINT32, :ptr
    IsAlphabetic	proc :UINT32, :ptr
    IsCased		proc :UINT32, :ptr
    IsUppercase		proc :UINT32, :ptr
    IsLowercase		proc :UINT32, :ptr
    IsIdStart		proc :UINT32, :ptr
    IsIdContinue	proc :UINT32, :ptr
    IsGraphemeBase	proc :UINT32, :ptr
    IsGraphemeExtend	proc :UINT32, :ptr
    GetNumericType	proc :UINT32, :ptr
    GetGeneralCategory	proc :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CIAlternateWordForm_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CIAlternateWordForm_INTERFACE_DEFINED__

DEFINE_IIDX(IAlternateWordForm, "47396C1E-51B9-4207-9146-248E636A1D1D")

.comdef IAlternateWordForm : public IInspectable

    get_SourceTextSegment proc :ptr
    get_AlternateText	proc :ptr
    get_NormalizationFormat proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CISelectableWordSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CISelectableWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(ISelectableWordSegment, "916A4CB7-8AA7-4C78-B374-5DEDB752E60B")

.comdef ISelectableWordSegment : public IInspectable

    get_Text		proc :ptr
    get_SourceTextSegment proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CIWordSegment_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CIWordSegment_INTERFACE_DEFINED__

DEFINE_IIDX(IWordSegment, "D2D4BA6D-987C-4CC0-B6BD-D49A11B38F9A")

.comdef IWordSegment : public IInspectable

    get_Text		proc :ptr
    get_SourceTextSegment proc :ptr
    get_AlternateForms	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CIWordsSegmenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CIWordsSegmenter_INTERFACE_DEFINED__

DEFINE_IIDX(IWordsSegmenter, "86B4D4D1-B2FE-4E34-A81D-66640300454F")

.comdef IWordsSegmenter : public IInspectable

    get_ResolvedLanguage proc :ptr
    GetTokenAt		proc :HSTRING, :UINT32, :ptr
    GetTokens		proc :HSTRING, :ptr
    Tokenize		proc :HSTRING, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CIWordsSegmenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CIWordsSegmenterFactory_INTERFACE_DEFINED__

DEFINE_IIDX(IWordsSegmenterFactory, "E6977274-FC35-455C-8BFB-6D7F4653CA97")

.comdef IWordsSegmenterFactory : public IInspectable

    CreateWithLanguage	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CISelectableWordsSegmenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CISelectableWordsSegmenter_INTERFACE_DEFINED__

DEFINE_IIDX(ISelectableWordsSegmenter, "F6DC31E7-4B13-45C5-8897-7D71269E085D")

.comdef ISelectableWordsSegmenter : public IInspectable

    get_ResolvedLanguage proc :ptr
    GetTokenAt		proc :HSTRING, :UINT32, :ptr
    GetTokens		proc :HSTRING, :ptr
    Tokenize		proc :HSTRING, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CData_CText_CISelectableWordsSegmenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CData_CText_CISelectableWordsSegmenterFactory_INTERFACE_DEFINED__

DEFINE_IIDX(ISelectableWordsSegmenterFactory, "8C7A7648-6057-4339-BC70-F210010A4150")

.comdef ISelectableWordsSegmenterFactory : public IInspectable

    CreateWithLanguage	proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn

HSTRING_UserSize	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
