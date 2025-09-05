ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Edocuments_h__
define __windows2Eui2Examl2Edocuments_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.UI.Text.inc
include Windows.UI.Xaml.inc

ifndef __windows2Eui2Examl2Emedia_h__
 include Windows.UI.Xaml.Media.inc
endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CDocuments__CBlock, "798d518e-a9f8-5fc7-8ccc-2a49069aba05")

.comdef __FIIterator_1_Windows__CUI__CXaml__CDocuments__CBlock : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CDocuments__CBlock, "f7023b9a-e6d1-5e2d-8f41-b28c33323e04")

.comdef __FIIterable_1_Windows__CUI__CXaml__CDocuments__CBlock : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CDocuments__CInline, "f80dc964-2542-5c6a-ba65-b04824b5ed75")

.comdef __FIIterator_1_Windows__CUI__CXaml__CDocuments__CInline : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CDocuments__CInline, "e1d2b910-18c2-5906-8f8a-d62a63f93f18")

.comdef __FIIterable_1_Windows__CUI__CXaml__CDocuments__CInline : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CDocuments__CBlock, "995f73c4-7cf8-5b59-a0fb-7e0c6477172e")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CDocuments__CBlock : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CDocuments__CInline, "c2dd082f-8cb4-51d6-b91b-7e2377780cee")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CDocuments__CInline : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CDocuments__CBlock_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CDocuments__CBlock, "3ee78a34-160e-50ff-b5aa-09f263a669f8")

.comdef __FIVector_1_Windows__CUI__CXaml__CDocuments__CBlock : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CDocuments__CInline_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CDocuments__CInline, "92ec9252-8ee3-55d6-84b4-30b635077778")

.comdef __FIVector_1_Windows__CUI__CXaml__CDocuments__CInline : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CXaml__CDocuments__CHyperlink_Windows__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CXaml__CDocuments__CHyperlink_Windows__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CXaml__CDocuments__CHyperlink_Windows__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs, "5fead0d2-e657-5aef-a91b-7f52ead17fe3")

.comdef __FITypedEventHandler_2_Windows__CUI__CXaml__CDocuments__CHyperlink_Windows__CUI__CXaml__CDocuments__CHyperlinkClickEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Documents

.enum LogicalDirection {
    LogicalDirection_Backward	= 0,
    LogicalDirection_Forward	= 1
    }


ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBlock_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IBlock <L"Windows.UI.Xaml.Documents.IBlock">
DEFINE_IIDX(IBlock, "4BCE0016-DD47-4350-8CB0-E171600AC896")

.comdef IBlock : public IInspectable

    get_TextAlignment	proc :ptr
    put_TextAlignment	proc :Windows::UI::Xaml::TextAlignment
    get_LineHeight	proc :ptr
    put_LineHeight	proc :DOUBLE
    get_LineStackingStrategy proc :ptr
    put_LineStackingStrategy proc :Windows::UI::Xaml::LineStackingStrategy
    get_Margin		proc :ptr
    put_Margin		proc :Windows::UI::Xaml::Thickness
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBlockStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IBlockStatics <L"Windows.UI.Xaml.Documents.IBlockStatics">
DEFINE_IIDX(IBlockStatics, "F86A8C34-8D18-4C53-AEBD-91E610A5E010")

.comdef IBlockStatics : public IInspectable

    get_TextAlignmentProperty proc :ptr
    get_LineHeightProperty proc :ptr
    get_LineStackingStrategyProperty proc :ptr
    get_MarginProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBlockFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IBlockFactory <L"Windows.UI.Xaml.Documents.IBlockFactory">
DEFINE_IIDX(IBlockFactory, "07110532-4F59-4F3B-9CE5-25784C430507")

.comdef IBlockFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIBold_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IBold <L"Windows.UI.Xaml.Documents.IBold">
DEFINE_IIDX(IBold, "ADE73784-1B59-4DA4-BB23-0F20E885B4BF")

.comdef IBold : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIGlyphs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IGlyphs <L"Windows.UI.Xaml.Documents.IGlyphs">
DEFINE_IIDX(IGlyphs, "D079498B-F2B1-4281-99A2-E4D05932B2B5")

.comdef IGlyphs : public IInspectable

    get_UnicodeString	proc :ptr
    put_UnicodeString	proc :HSTRING
    get_Indices		proc :ptr
    put_Indices		proc :HSTRING
    get_FontUri		proc :ptr
    put_FontUri		proc :ptr
    get_StyleSimulations proc :ptr
    put_StyleSimulations proc :Windows::UI::Xaml::Media::StyleSimulations
    get_FontRenderingEmSize proc :ptr
    put_FontRenderingEmSize proc :DOUBLE
    get_OriginX		proc :ptr
    put_OriginX		proc :DOUBLE
    get_OriginY		proc :ptr
    put_OriginY		proc :DOUBLE
    get_Fill		proc :ptr
    put_Fill		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIGlyphsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IGlyphsStatics <L"Windows.UI.Xaml.Documents.IGlyphsStatics">
DEFINE_IIDX(IGlyphsStatics, "225CF4C5-FDF1-43ED-958F-414E86F103F2")

.comdef IGlyphsStatics : public IInspectable

    get_UnicodeStringProperty proc :ptr
    get_IndicesProperty proc :ptr
    get_FontUriProperty proc :ptr
    get_StyleSimulationsProperty proc :ptr
    get_FontRenderingEmSizeProperty proc :ptr
    get_OriginXProperty proc :ptr
    get_OriginYProperty proc :ptr
    get_FillProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIInline_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IInline <L"Windows.UI.Xaml.Documents.IInline">
DEFINE_IIDX(IInline, "0C92712D-1BC9-4931-8CB1-1AEADF1CC685")

.comdef IInline : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIInlineFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IInlineFactory <L"Windows.UI.Xaml.Documents.IInlineFactory">
DEFINE_IIDX(IInlineFactory, "4058ACD1-2F90-4B8F-99DD-4218EF5F03DE")

.comdef IInlineFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIInlineUIContainer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IInlineUIContainer <L"Windows.UI.Xaml.Documents.IInlineUIContainer">
DEFINE_IIDX(IInlineUIContainer, "1416CE81-28EE-452E-B121-5FC4F60B86A6")

.comdef IInlineUIContainer : public IInspectable

    get_Child		proc :ptr
    put_Child		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIItalic_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IItalic <L"Windows.UI.Xaml.Documents.IItalic">
DEFINE_IIDX(IItalic, "91F4619C-FCBB-4157-802C-76F63B5FB657")

.comdef IItalic : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CILineBreak_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ILineBreak <L"Windows.UI.Xaml.Documents.ILineBreak">
DEFINE_IIDX(ILineBreak, "645589C4-F769-41ED-895B-8A1B2FB31562")

.comdef ILineBreak : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIParagraph_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IParagraph <L"Windows.UI.Xaml.Documents.IParagraph">
DEFINE_IIDX(IParagraph, "F83EF59A-FA61-4BEF-AE33-0B0AD756A84D")

.comdef IParagraph : public IInspectable

    get_Inlines		proc :ptr
    get_TextIndent	proc :ptr
    put_TextIndent	proc :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIParagraphStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IParagraphStatics <L"Windows.UI.Xaml.Documents.IParagraphStatics">
DEFINE_IIDX(IParagraphStatics, "EF08889A-535B-4E4C-8D84-283B33E98A37")

.comdef IParagraphStatics : public IInspectable

    get_TextIndentProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIRun_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IRun <L"Windows.UI.Xaml.Documents.IRun">
DEFINE_IIDX(IRun, "59553C83-0E14-49BD-B84B-C526F3034349")

.comdef IRun : public IInspectable

    get_Text		proc :ptr
    put_Text		proc :HSTRING
    get_FlowDirection	proc :ptr
    put_FlowDirection	proc :Windows::UI::Xaml::FlowDirection
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIRunStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IRunStatics <L"Windows.UI.Xaml.Documents.IRunStatics">
DEFINE_IIDX(IRunStatics, "E9303CEF-65A0-4B8D-A7F7-8FDB287B46F3")

.comdef IRunStatics : public IInspectable

    get_FlowDirectionProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CISpan_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ISpan <L"Windows.UI.Xaml.Documents.ISpan">
DEFINE_IIDX(ISpan, "9839D4A9-02AF-4811-AA15-6BEF3ACAC97A")

.comdef ISpan : public IInspectable

    get_Inlines		proc :ptr
    put_Inlines		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CISpanFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ISpanFactory <L"Windows.UI.Xaml.Documents.ISpanFactory">
DEFINE_IIDX(ISpanFactory, "5B916F5C-CD2D-40C0-956A-386448322F79")

.comdef ISpanFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElement_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITextElement <L"Windows.UI.Xaml.Documents.ITextElement">
DEFINE_IIDX(ITextElement, "E83B0062-D776-4F92-BAEA-40E77D4791D5")

.comdef ITextElement : public IInspectable

    get_Name		proc :ptr
    get_FontSize	proc :ptr
    put_FontSize	proc :DOUBLE
    get_FontFamily	proc :ptr
    put_FontFamily	proc :ptr
    get_FontWeight	proc :ptr
    put_FontWeight	proc :Windows::UI::Text::FontWeight
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
    get_FontStretch	proc :ptr
    put_FontStretch	proc :Windows::UI::Text::FontStretch
    get_CharacterSpacing proc :ptr
    put_CharacterSpacing proc :INT32
    get_Foreground	proc :ptr
    put_Foreground	proc :ptr
    get_Language	proc :ptr
    put_Language	proc :HSTRING
    get_ContentStart	proc :ptr
    get_ContentEnd	proc :ptr
    get_ElementStart	proc :ptr
    get_ElementEnd	proc :ptr
    FindName		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElementOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITextElementOverrides <L"Windows.UI.Xaml.Documents.ITextElementOverrides">
DEFINE_IIDX(ITextElementOverrides, "0CE21EE7-4F76-4DD9-BF91-163BECCF84BC")

.comdef ITextElementOverrides : public IInspectable

    OnDisconnectVisualChildren proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElementStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITextElementStatics <L"Windows.UI.Xaml.Documents.ITextElementStatics">
DEFINE_IIDX(ITextElementStatics, "0A2F9B98-6C03-4470-A79B-3298A10482CE")

.comdef ITextElementStatics : public IInspectable

    get_FontSizeProperty proc :ptr
    get_FontFamilyProperty proc :ptr
    get_FontWeightProperty proc :ptr
    get_FontStyleProperty proc :ptr
    get_FontStretchProperty proc :ptr
    get_CharacterSpacingProperty proc :ptr
    get_ForegroundProperty proc :ptr
    get_LanguageProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextElementFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITextElementFactory <L"Windows.UI.Xaml.Documents.ITextElementFactory">
DEFINE_IIDX(ITextElementFactory, "35007285-CF47-4BFE-B1BC-39C93AF4AE80")

.comdef ITextElementFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITextPointer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITextPointer <L"Windows.UI.Xaml.Documents.ITextPointer">
DEFINE_IIDX(ITextPointer, "AC687AA1-6A41-43FF-851E-45348AA2CF7B")

.comdef ITextPointer : public IInspectable

    get_Parent		proc :ptr
    get_VisualParent	proc :ptr
    get_LogicalDirection proc :ptr
    get_Offset		proc :ptr
    GetCharacterRect	proc :Windows::UI::Xaml::Documents::LogicalDirection, :ptr
    GetPositionAtOffset proc :INT32, :Windows::UI::Xaml::Documents::LogicalDirection, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITypography_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITypography <L"Windows.UI.Xaml.Documents.ITypography">
DEFINE_IIDX(ITypography, "866F65D5-EA97-42AB-9288-9C01AEBC7A97")

.comdef ITypography : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CITypographyStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_ITypographyStatics <L"Windows.UI.Xaml.Documents.ITypographyStatics">
DEFINE_IIDX(ITypographyStatics, "67B9EC88-6C57-4CE0-95F1-D4B9ED632FB4")

.comdef ITypographyStatics : public IInspectable

    get_AnnotationAlternatesProperty proc :ptr
    GetAnnotationAlternates proc :ptr, :ptr
    SetAnnotationAlternates proc :ptr, :INT32
    get_EastAsianExpertFormsProperty proc :ptr
    GetEastAsianExpertForms proc :ptr, :ptr
    SetEastAsianExpertForms proc :ptr, :boolean
    get_EastAsianLanguageProperty proc :ptr
    GetEastAsianLanguage proc :ptr, :ptr
    SetEastAsianLanguage proc :ptr, :Windows::UI::Xaml::FontEastAsianLanguage
    get_EastAsianWidthsProperty proc :ptr
    GetEastAsianWidths	proc :ptr, :ptr
    SetEastAsianWidths	proc :ptr, :Windows::UI::Xaml::FontEastAsianWidths
    get_StandardLigaturesProperty proc :ptr
    GetStandardLigatures proc :ptr, :ptr
    SetStandardLigatures proc :ptr, :boolean
    get_ContextualLigaturesProperty proc :ptr
    GetContextualLigatures proc :ptr, :ptr
    SetContextualLigatures proc :ptr, :boolean
    get_DiscretionaryLigaturesProperty proc :ptr
    GetDiscretionaryLigatures proc :ptr, :ptr
    SetDiscretionaryLigatures proc :ptr, :boolean
    get_HistoricalLigaturesProperty proc :ptr
    GetHistoricalLigatures proc :ptr, :ptr
    SetHistoricalLigatures proc :ptr, :boolean
    get_StandardSwashesProperty proc :ptr
    GetStandardSwashes	proc :ptr, :ptr
    SetStandardSwashes	proc :ptr, :INT32
    get_ContextualSwashesProperty proc :ptr
    GetContextualSwashes proc :ptr, :ptr
    SetContextualSwashes proc :ptr, :INT32
    get_ContextualAlternatesProperty proc :ptr
    GetContextualAlternates proc :ptr, :ptr
    SetContextualAlternates proc :ptr, :boolean
    get_StylisticAlternatesProperty proc :ptr
    GetStylisticAlternates proc :ptr, :ptr
    SetStylisticAlternates proc :ptr, :INT32
    get_StylisticSet1Property proc :ptr
    GetStylisticSet1	proc :ptr, :ptr
    SetStylisticSet1	proc :ptr, :boolean
    get_StylisticSet2Property proc :ptr
    GetStylisticSet2	proc :ptr, :ptr
    SetStylisticSet2	proc :ptr, :boolean
    get_StylisticSet3Property proc :ptr
    GetStylisticSet3	proc :ptr, :ptr
    SetStylisticSet3	proc :ptr, :boolean
    get_StylisticSet4Property proc :ptr
    GetStylisticSet4	proc :ptr, :ptr
    SetStylisticSet4	proc :ptr, :boolean
    get_StylisticSet5Property proc :ptr
    GetStylisticSet5	proc :ptr, :ptr
    SetStylisticSet5	proc :ptr, :boolean
    get_StylisticSet6Property proc :ptr
    GetStylisticSet6	proc :ptr, :ptr
    SetStylisticSet6	proc :ptr, :boolean
    get_StylisticSet7Property proc :ptr
    GetStylisticSet7	proc :ptr, :ptr
    SetStylisticSet7	proc :ptr, :boolean
    get_StylisticSet8Property proc :ptr
    GetStylisticSet8	proc :ptr, :ptr
    SetStylisticSet8	proc :ptr, :boolean
    get_StylisticSet9Property proc :ptr
    GetStylisticSet9	proc :ptr, :ptr
    SetStylisticSet9	proc :ptr, :boolean
    get_StylisticSet10Property proc :ptr
    GetStylisticSet10	proc :ptr, :ptr
    SetStylisticSet10	proc :ptr, :boolean
    get_StylisticSet11Property proc :ptr
    GetStylisticSet11	proc :ptr, :ptr
    SetStylisticSet11	proc :ptr, :boolean
    get_StylisticSet12Property proc :ptr
    GetStylisticSet12	proc :ptr, :ptr
    SetStylisticSet12	proc :ptr, :boolean
    get_StylisticSet13Property proc :ptr
    GetStylisticSet13	proc :ptr, :ptr
    SetStylisticSet13	proc :ptr, :boolean
    get_StylisticSet14Property proc :ptr
    GetStylisticSet14	proc :ptr, :ptr
    SetStylisticSet14	proc :ptr, :boolean
    get_StylisticSet15Property proc :ptr
    GetStylisticSet15	proc :ptr, :ptr
    SetStylisticSet15	proc :ptr, :boolean
    get_StylisticSet16Property proc :ptr
    GetStylisticSet16	proc :ptr, :ptr
    SetStylisticSet16	proc :ptr, :boolean
    get_StylisticSet17Property proc :ptr
    GetStylisticSet17	proc :ptr, :ptr
    SetStylisticSet17	proc :ptr, :boolean
    get_StylisticSet18Property proc :ptr
    GetStylisticSet18	proc :ptr, :ptr
    SetStylisticSet18	proc :ptr, :boolean
    get_StylisticSet19Property proc :ptr
    GetStylisticSet19	proc :ptr, :ptr
    SetStylisticSet19	proc :ptr, :boolean
    get_StylisticSet20Property proc :ptr
    GetStylisticSet20	proc :ptr, :ptr
    SetStylisticSet20	proc :ptr, :boolean
    get_CapitalsProperty proc :ptr
    GetCapitals		proc :ptr, :ptr
    SetCapitals		proc :ptr, :Windows::UI::Xaml::FontCapitals
    get_CapitalSpacingProperty proc :ptr
    GetCapitalSpacing	proc :ptr, :ptr
    SetCapitalSpacing	proc :ptr, :boolean
    get_KerningProperty proc :ptr
    GetKerning		proc :ptr, :ptr
    SetKerning		proc :ptr, :boolean
    get_CaseSensitiveFormsProperty proc :ptr
    GetCaseSensitiveForms proc :ptr, :ptr
    SetCaseSensitiveForms proc :ptr, :boolean
    get_HistoricalFormsProperty proc :ptr
    GetHistoricalForms	proc :ptr, :ptr
    SetHistoricalForms	proc :ptr, :boolean
    get_FractionProperty proc :ptr
    GetFraction		proc :ptr, :ptr
    SetFraction		proc :ptr, :Windows::UI::Xaml::FontFraction
    get_NumeralStyleProperty proc :ptr
    GetNumeralStyle	proc :ptr, :ptr
    SetNumeralStyle	proc :ptr, :Windows::UI::Xaml::FontNumeralStyle
    get_NumeralAlignmentProperty proc :ptr
    GetNumeralAlignment proc :ptr, :ptr
    SetNumeralAlignment proc :ptr, :Windows::UI::Xaml::FontNumeralAlignment
    get_SlashedZeroProperty proc :ptr
    GetSlashedZero	proc :ptr, :ptr
    SetSlashedZero	proc :ptr, :boolean
    get_MathematicalGreekProperty proc :ptr
    GetMathematicalGreek proc :ptr, :ptr
    SetMathematicalGreek proc :ptr, :boolean
    get_VariantsProperty proc :ptr
    GetVariants		proc :ptr, :ptr
    SetVariants		proc :ptr, :Windows::UI::Xaml::FontVariants
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIUnderline_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IUnderline <L"Windows.UI.Xaml.Documents.IUnderline">
DEFINE_IIDX(IUnderline, "A5FA8202-61C0-47D7-93EF-BC0B577C5F26")

.comdef IUnderline : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIHyperlink_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IHyperlink <L"Windows.UI.Xaml.Documents.IHyperlink">
DEFINE_IIDX(IHyperlink, "0FE2363B-14E9-4152-9E58-5AEA5B21F08D")

.comdef IHyperlink : public IInspectable

    get_NavigateUri	proc :ptr
    put_NavigateUri	proc :ptr
    add_Click		proc :ptr, :ptr
    remove_Click	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIHyperlinkStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IHyperlinkStatics <L"Windows.UI.Xaml.Documents.IHyperlinkStatics">
DEFINE_IIDX(IHyperlinkStatics, "3A44D3D4-FD41-41DB-8C72-3B790ACD9FD3")

.comdef IHyperlinkStatics : public IInspectable

    get_NavigateUriProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CDocuments_CIHyperlinkClickEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Documents_IHyperlinkClickEventArgs <L"Windows.UI.Xaml.Documents.IHyperlinkClickEventArgs">
DEFINE_IIDX(IHyperlinkClickEventArgs, "C755916B-7BDC-4BE7-B373-9240A503D870")

.comdef IHyperlinkClickEventArgs : public IInspectable

   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_BlockCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_BlockCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_BlockCollection <L"Windows.UI.Xaml.Documents.BlockCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_InlineCollection_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_InlineCollection_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_InlineCollection <L"Windows.UI.Xaml.Documents.InlineCollection">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_TextPointer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_TextPointer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_TextPointer <L"Windows.UI.Xaml.Documents.TextPointer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Typography_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Typography_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Typography <L"Windows.UI.Xaml.Documents.Typography">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_TextElement_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_TextElement_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_TextElement <L"Windows.UI.Xaml.Documents.TextElement">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Block_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Block_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Block <L"Windows.UI.Xaml.Documents.Block">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Inline_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Inline_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Inline <L"Windows.UI.Xaml.Documents.Inline">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_InlineUIContainer_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_InlineUIContainer_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_InlineUIContainer <L"Windows.UI.Xaml.Documents.InlineUIContainer">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_LineBreak_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_LineBreak_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_LineBreak <L"Windows.UI.Xaml.Documents.LineBreak">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Paragraph_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Paragraph_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Paragraph <L"Windows.UI.Xaml.Documents.Paragraph">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Run_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Run_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Run <L"Windows.UI.Xaml.Documents.Run">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Span_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Span_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Span <L"Windows.UI.Xaml.Documents.Span">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Bold_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Bold_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Bold <L"Windows.UI.Xaml.Documents.Bold">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Italic_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Italic_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Italic <L"Windows.UI.Xaml.Documents.Italic">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Underline_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Underline_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Underline <L"Windows.UI.Xaml.Documents.Underline">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Hyperlink_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Hyperlink_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Hyperlink <L"Windows.UI.Xaml.Documents.Hyperlink">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_HyperlinkClickEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_HyperlinkClickEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_HyperlinkClickEventArgs <L"Windows.UI.Xaml.Documents.HyperlinkClickEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Documents_Glyphs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Documents_Glyphs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Documents_Glyphs <L"Windows.UI.Xaml.Documents.Glyphs">
endif

endif
