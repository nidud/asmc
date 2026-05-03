ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Etext_h__
define __windows2Eui2Etext_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc
include Windows.UI.inc

.namespace Windows
.namespace UI
.namespace Text

.enum CaretType {
    CaretType_Normal	= 0,
    CaretType_Null	= 1
    }

.enum FindOptions {
    FindOptions_None	= 0,
    FindOptions_Word	= 0x2,
    FindOptions_Case	= 0x4
    }

.enum FormatEffect {
    FormatEffect_Off	= 0,
    FormatEffect_On	= 1,
    FormatEffect_Toggle = 2,
    FormatEffect_Undefined	= 3
    }

.enum HorizontalCharacterAlignment {
    HorizontalCharacterAlignment_Left	= 0,
    HorizontalCharacterAlignment_Right	= 1,
    HorizontalCharacterAlignment_Center = 2
    }

.enum LetterCase {
    LetterCase_Lower	= 0,
    LetterCase_Upper	= 1
    }

.enum LineSpacingRule {
    LineSpacingRule_Undefined	= 0,
    LineSpacingRule_Single	= 1,
    LineSpacingRule_OneAndHalf	= 2,
    LineSpacingRule_Double	= 3,
    LineSpacingRule_AtLeast	= 4,
    LineSpacingRule_Exactly	= 5,
    LineSpacingRule_Multiple	= 6,
    LineSpacingRule_Percent	= 7
    }

.enum LinkType {
    LinkType_Undefined	= 0,
    LinkType_NotALink	= 1,
    LinkType_ClientLink = 2,
    LinkType_FriendlyLinkName	= 3,
    LinkType_FriendlyLinkAddress	= 4,
    LinkType_AutoLink	= 5,
    LinkType_AutoLinkEmail	= 6,
    LinkType_AutoLinkPhone	= 7,
    LinkType_AutoLinkPath	= 8
    }

.enum MarkerAlignment {
    MarkerAlignment_Undefined	= 0,
    MarkerAlignment_Left	= 1,
    MarkerAlignment_Center	= 2,
    MarkerAlignment_Right	= 3
    }

.enum MarkerStyle {
    MarkerStyle_Undefined	= 0,
    MarkerStyle_Parenthesis	= 1,
    MarkerStyle_Parentheses	= 2,
    MarkerStyle_Period	= 3,
    MarkerStyle_Plain	= 4,
    MarkerStyle_Minus	= 5,
    MarkerStyle_NoNumber	= 6
    }

.enum MarkerType {
    MarkerType_Undefined	= 0,
    MarkerType_None	= 1,
    MarkerType_Bullet	= 2,
    MarkerType_Arabic	= 3,
    MarkerType_LowercaseEnglishLetter	= 4,
    MarkerType_UppercaseEnglishLetter	= 5,
    MarkerType_LowercaseRoman	= 6,
    MarkerType_UppercaseRoman	= 7,
    MarkerType_UnicodeSequence	= 8,
    MarkerType_CircledNumber	= 9,
    MarkerType_BlackCircleWingding	= 10,
    MarkerType_WhiteCircleWingding	= 11,
    MarkerType_ArabicWide	= 12,
    MarkerType_SimplifiedChinese	= 13,
    MarkerType_TraditionalChinese	= 14,
    MarkerType_JapanSimplifiedChinese	= 15,
    MarkerType_JapanKorea	= 16,
    MarkerType_ArabicDictionary = 17,
    MarkerType_ArabicAbjad	= 18,
    MarkerType_Hebrew	= 19,
    MarkerType_ThaiAlphabetic	= 20,
    MarkerType_ThaiNumeric	= 21,
    MarkerType_DevanagariVowel	= 22,
    MarkerType_DevanagariConsonant	= 23,
    MarkerType_DevanagariNumeric	= 24
    }

.enum ParagraphAlignment {
    ParagraphAlignment_Undefined	= 0,
    ParagraphAlignment_Left	= 1,
    ParagraphAlignment_Center	= 2,
    ParagraphAlignment_Right	= 3,
    ParagraphAlignment_Justify	= 4
    }

.enum ParagraphStyle {
    ParagraphStyle_Undefined	= 0,
    ParagraphStyle_None = 1,
    ParagraphStyle_Normal	= 2,
    ParagraphStyle_Heading1	= 3,
    ParagraphStyle_Heading2	= 4,
    ParagraphStyle_Heading3	= 5,
    ParagraphStyle_Heading4	= 6,
    ParagraphStyle_Heading5	= 7,
    ParagraphStyle_Heading6	= 8,
    ParagraphStyle_Heading7	= 9,
    ParagraphStyle_Heading8	= 10,
    ParagraphStyle_Heading9	= 11
    }

.enum PointOptions {
    PointOptions_None	= 0,
    PointOptions_IncludeInset	= 0x1,
    PointOptions_Start	= 0x20,
    PointOptions_ClientCoordinates	= 0x100,
    PointOptions_AllowOffClient = 0x200,
    PointOptions_Transform	= 0x400,
    PointOptions_NoHorizontalScroll	= 0x10000,
    PointOptions_NoVerticalScroll	= 0x40000
    }

.enum RangeGravity {
    RangeGravity_UIBehavior	= 0,
    RangeGravity_Backward	= 1,
    RangeGravity_Forward	= 2,
    RangeGravity_Inward = 3,
    RangeGravity_Outward	= 4
    }

.enum SelectionOptions {
    SelectionOptions_StartActive	= 0x1,
    SelectionOptions_AtEndOfLine	= 0x2,
    SelectionOptions_Overtype	= 0x4,
    SelectionOptions_Active	= 0x8,
    SelectionOptions_Replace	= 0x10
    }

.enum SelectionType {
    SelectionType_None	= 0,
    SelectionType_InsertionPoint	= 1,
    SelectionType_Normal	= 2,
    SelectionType_InlineShape	= 7,
    SelectionType_Shape = 8
    }

.enum TabAlignment {
    TabAlignment_Left	= 0,
    TabAlignment_Center = 1,
    TabAlignment_Right	= 2,
    TabAlignment_Decimal	= 3,
    TabAlignment_Bar	= 4
    }

.enum TabLeader {
    TabLeader_Spaces	= 0,
    TabLeader_Dots	= 1,
    TabLeader_Dashes	= 2,
    TabLeader_Lines	= 3,
    TabLeader_ThickLines	= 4,
    TabLeader_Equals	= 5
    }

.enum TextGetOptions {
    TextGetOptions_None = 0,
    TextGetOptions_AdjustCrlf	= 0x1,
    TextGetOptions_UseCrlf	= 0x2,
    TextGetOptions_UseObjectText	= 0x4,
    TextGetOptions_AllowFinalEop	= 0x8,
    TextGetOptions_NoHidden	= 0x20,
    TextGetOptions_IncludeNumbering	= 0x40,
    TextGetOptions_FormatRtf	= 0x2000
    }

.enum TextSetOptions {
    TextSetOptions_None = 0,
    TextSetOptions_UnicodeBidi	= 0x1,
    TextSetOptions_Unlink	= 0x8,
    TextSetOptions_Unhide	= 0x10,
    TextSetOptions_CheckTextLimit	= 0x20,
    TextSetOptions_FormatRtf	= 0x2000,
    TextSetOptions_ApplyRtfDocumentDefaults	= 0x4000
    }

.enum TextRangeUnit {
    TextRangeUnit_Character	= 0,
    TextRangeUnit_Word	= 1,
    TextRangeUnit_Sentence	= 2,
    TextRangeUnit_Paragraph	= 3,
    TextRangeUnit_Line	= 4,
    TextRangeUnit_Story = 5,
    TextRangeUnit_Screen	= 6,
    TextRangeUnit_Section	= 7,
    TextRangeUnit_Window	= 8,
    TextRangeUnit_CharacterFormat	= 9,
    TextRangeUnit_ParagraphFormat	= 10,
    TextRangeUnit_Object	= 11,
    TextRangeUnit_HardParagraph = 12,
    TextRangeUnit_Cluster	= 13,
    TextRangeUnit_Bold	= 14,
    TextRangeUnit_Italic	= 15,
    TextRangeUnit_Underline	= 16,
    TextRangeUnit_Strikethrough = 17,
    TextRangeUnit_ProtectedText = 18,
    TextRangeUnit_Link	= 19,
    TextRangeUnit_SmallCaps	= 20,
    TextRangeUnit_AllCaps	= 21,
    TextRangeUnit_Hidden	= 22,
    TextRangeUnit_Outline	= 23,
    TextRangeUnit_Shadow	= 24,
    TextRangeUnit_Imprint	= 25,
    TextRangeUnit_Disabled	= 26,
    TextRangeUnit_Revised	= 27,
    TextRangeUnit_Subscript	= 28,
    TextRangeUnit_Superscript	= 29,
    TextRangeUnit_FontBound	= 30,
    TextRangeUnit_LinkProtected = 31
    }

.enum TextScript {
    TextScript_Undefined	= 0,
    TextScript_Ansi	= 1,
    TextScript_EastEurope	= 2,
    TextScript_Cyrillic = 3,
    TextScript_Greek	= 4,
    TextScript_Turkish	= 5,
    TextScript_Hebrew	= 6,
    TextScript_Arabic	= 7,
    TextScript_Baltic	= 8,
    TextScript_Vietnamese	= 9,
    TextScript_Default	= 10,
    TextScript_Symbol	= 11,
    TextScript_Thai	= 12,
    TextScript_ShiftJis = 13,
    TextScript_GB2312	= 14,
    TextScript_Hangul	= 15,
    TextScript_Big5	= 16,
    TextScript_PC437	= 17,
    TextScript_Oem	= 18,
    TextScript_Mac	= 19,
    TextScript_Armenian = 20,
    TextScript_Syriac	= 21,
    TextScript_Thaana	= 22,
    TextScript_Devanagari	= 23,
    TextScript_Bengali	= 24,
    TextScript_Gurmukhi = 25,
    TextScript_Gujarati = 26,
    TextScript_Oriya	= 27,
    TextScript_Tamil	= 28,
    TextScript_Telugu	= 29,
    TextScript_Kannada	= 30,
    TextScript_Malayalam	= 31,
    TextScript_Sinhala	= 32,
    TextScript_Lao	= 33,
    TextScript_Tibetan	= 34,
    TextScript_Myanmar	= 35,
    TextScript_Georgian = 36,
    TextScript_Jamo	= 37,
    TextScript_Ethiopic = 38,
    TextScript_Cherokee = 39,
    TextScript_Aboriginal	= 40,
    TextScript_Ogham	= 41,
    TextScript_Runic	= 42,
    TextScript_Khmer	= 43,
    TextScript_Mongolian	= 44,
    TextScript_Braille	= 45,
    TextScript_Yi	= 46,
    TextScript_Limbu	= 47,
    TextScript_TaiLe	= 48,
    TextScript_NewTaiLue	= 49,
    TextScript_SylotiNagri	= 50,
    TextScript_Kharoshthi	= 51,
    TextScript_Kayahli	= 52,
    TextScript_UnicodeSymbol	= 53,
    TextScript_Emoji	= 54,
    TextScript_Glagolitic	= 55,
    TextScript_Lisu	= 56,
    TextScript_Vai	= 57,
    TextScript_NKo	= 58,
    TextScript_Osmanya	= 59,
    TextScript_PhagsPa	= 60,
    TextScript_Gothic	= 61,
    TextScript_Deseret	= 62,
    TextScript_Tifinagh = 63
    }

.enum UnderlineType {
    UnderlineType_Undefined	= 0,
    UnderlineType_None	= 1,
    UnderlineType_Single	= 2,
    UnderlineType_Words = 3,
    UnderlineType_Double	= 4,
    UnderlineType_Dotted	= 5,
    UnderlineType_Dash	= 6,
    UnderlineType_DashDot	= 7,
    UnderlineType_DashDotDot	= 8,
    UnderlineType_Wave	= 9,
    UnderlineType_Thick = 10,
    UnderlineType_Thin	= 11,
    UnderlineType_DoubleWave	= 12,
    UnderlineType_HeavyWave	= 13,
    UnderlineType_LongDash	= 14,
    UnderlineType_ThickDash	= 15,
    UnderlineType_ThickDashDot	= 16,
    UnderlineType_ThickDashDotDot	= 17,
    UnderlineType_ThickDotted	= 18,
    UnderlineType_ThickLongDash = 19
    }

.enum VerticalCharacterAlignment {
    VerticalCharacterAlignment_Top	= 0,
    VerticalCharacterAlignment_Baseline = 1,
    VerticalCharacterAlignment_Bottom	= 2
    }

.enum FontStretch {
    FontStretch_Undefined	= 0,
    FontStretch_UltraCondensed	= 1,
    FontStretch_ExtraCondensed	= 2,
    FontStretch_Condensed	= 3,
    FontStretch_SemiCondensed	= 4,
    FontStretch_Normal	= 5,
    FontStretch_SemiExpanded	= 6,
    FontStretch_Expanded	= 7,
    FontStretch_ExtraExpanded	= 8,
    FontStretch_UltraExpanded	= 9
    }

.enum FontStyle {
    FontStyle_Normal	= 0,
    FontStyle_Oblique	= 1,
    FontStyle_Italic	= 2
    }

.template FontWeight
    Weight		UINT16 ?
   .ends

ifndef ____x_ABI_CWindows_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CITextConstantsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_ITextConstantsStatics <L"Windows.UI.Text.ITextConstantsStatics">
DEFINE_IIDX(ITextConstantsStatics, "779E7C33-189D-4BFA-97C8-10DB135D976E")

.comdef ITextConstantsStatics : public IInspectable

    get_AutoColor	proc :ptr
    get_MinUnitCount	proc :ptr
    get_MaxUnitCount	proc :ptr
    get_UndefinedColor	proc :ptr
    get_UndefinedFloatValue proc :ptr
    get_UndefinedInt32Value proc :ptr
    get_UndefinedFontStretch proc :ptr
    get_UndefinedFontStyle proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CITextDocument_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CITextDocument_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_ITextDocument <L"Windows.UI.Text.ITextDocument">
DEFINE_IIDX(ITextDocument, "BEEE4DDB-90B2-408C-A2F6-0A0AC31E33E4")

.comdef ITextDocument : public IInspectable

    get_CaretType	proc :ptr
    put_CaretType	proc :Windows::UI::Text::CaretType
    get_DefaultTabStop	proc :ptr
    put_DefaultTabStop	proc :FLOAT
    get_Selection	proc :ptr
    get_UndoLimit	proc :ptr
    put_UndoLimit	proc :UINT32
    CanCopy		proc :ptr
    CanPaste		proc :ptr
    CanRedo		proc :ptr
    CanUndo		proc :ptr
    ApplyDisplayUpdates proc :ptr
    BatchDisplayUpdates proc :ptr
    BeginUndoGroup	proc
    EndUndoGroup	proc
    GetDefaultCharacterFormat proc :ptr
    GetDefaultParagraphFormat proc :ptr
    GetRange		proc :INT32, :INT32, :ptr
    GetRangeFromPoint	proc :Windows::Foundation::Point, :Windows::UI::Text::PointOptions, :ptr
    GetText		proc :Windows::UI::Text::TextGetOptions, :ptr
    LoadFromStream	proc :Windows::UI::Text::TextSetOptions, :ptr
    Redo		proc
    SaveToStream	proc :Windows::UI::Text::TextGetOptions, :ptr
    SetDefaultCharacterFormat proc :ptr
    SetDefaultParagraphFormat proc :ptr
    SetText		proc :Windows::UI::Text::TextSetOptions, :HSTRING
    Undo		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CITextRange_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CITextRange_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_ITextRange <L"Windows.UI.Text.ITextRange">
DEFINE_IIDX(ITextRange, "5B9E4E57-C072-42A0-8945-AF503EE54768")

.comdef ITextRange : public IInspectable

    get_Character	proc :ptr
    put_Character	proc :WCHAR
    get_CharacterFormat proc :ptr
    put_CharacterFormat proc :ptr
    get_FormattedText	proc :ptr
    put_FormattedText	proc :ptr
    get_EndPosition	proc :ptr
    put_EndPosition	proc :INT32
    get_Gravity		proc :ptr
    put_Gravity		proc :Windows::UI::Text::RangeGravity
    get_Length		proc :ptr
    get_Link		proc :ptr
    put_Link		proc :HSTRING
    get_ParagraphFormat proc :ptr
    put_ParagraphFormat proc :ptr
    get_StartPosition	proc :ptr
    put_StartPosition	proc :INT32
    get_StoryLength	proc :ptr
    get_Text		proc :ptr
    put_Text		proc :HSTRING
    CanPaste		proc :INT32, :ptr
    ChangeCase		proc :Windows::UI::Text::LetterCase
    Collapse		proc :boolean
    Copy		proc
    Cut			proc
    Delete		proc :Windows::UI::Text::TextRangeUnit, :INT32, :ptr
    EndOf		proc :Windows::UI::Text::TextRangeUnit, :boolean, :ptr
    Expand		proc :Windows::UI::Text::TextRangeUnit, :ptr
    FindText		proc :HSTRING, :INT32, :Windows::UI::Text::FindOptions, :ptr
    GetCharacterUtf32	proc :ptr, :INT32
    GetClone		proc :ptr
    GetIndex		proc :Windows::UI::Text::TextRangeUnit, :ptr
    GetPoint		proc :Windows::UI::Text::HorizontalCharacterAlignment, :Windows::UI::Text::VerticalCharacterAlignment, :Windows::UI::Text::PointOptions, :ptr
    GetRect		proc :Windows::UI::Text::PointOptions, :ptr, :ptr
    GetText		proc :Windows::UI::Text::TextGetOptions, :ptr
    GetTextViaStream	proc :Windows::UI::Text::TextGetOptions, :ptr
    InRange		proc :ptr, :ptr
    InsertImage		proc :INT32, :INT32, :INT32, :Windows::UI::Text::VerticalCharacterAlignment, :HSTRING, :ptr
    InStory		proc :ptr, :ptr
    IsEqual		proc :ptr, :ptr
    Move		proc :Windows::UI::Text::TextRangeUnit, :INT32, :ptr
    MoveEnd		proc :Windows::UI::Text::TextRangeUnit, :INT32, :ptr
    MoveStart		proc :Windows::UI::Text::TextRangeUnit, :INT32, :ptr
    Paste		proc :INT32
    ScrollIntoView	proc :Windows::UI::Text::PointOptions
    MatchSelection	proc
    SetIndex		proc :Windows::UI::Text::TextRangeUnit, :INT32, :boolean
    SetPoint		proc :Windows::Foundation::Point, :Windows::UI::Text::PointOptions, :boolean
    SetRange		proc :INT32, :INT32
    SetText		proc :Windows::UI::Text::TextSetOptions, :HSTRING
    SetTextViaStream	proc :Windows::UI::Text::TextSetOptions, :ptr
    StartOf		proc :Windows::UI::Text::TextRangeUnit, :boolean, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CITextSelection_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CITextSelection_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_ITextSelection <L"Windows.UI.Text.ITextSelection">
DEFINE_IIDX(ITextSelection, "A6D36724-F28F-430A-B2CF-C343671EC0E9")

.comdef ITextSelection : public IInspectable

    get_Options		proc :ptr
    put_Options		proc :Windows::UI::Text::SelectionOptions
    get_Type		proc :ptr
    EndKey		proc :Windows::UI::Text::TextRangeUnit, :boolean, :ptr
    HomeKey		proc :Windows::UI::Text::TextRangeUnit, :boolean, :ptr
    MoveDown		proc :Windows::UI::Text::TextRangeUnit, :INT32, :boolean, :ptr
    MoveLeft		proc :Windows::UI::Text::TextRangeUnit, :INT32, :boolean, :ptr
    MoveRight		proc :Windows::UI::Text::TextRangeUnit, :INT32, :boolean, :ptr
    MoveUp		proc :Windows::UI::Text::TextRangeUnit, :INT32, :boolean, :ptr
    TypeText		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CITextCharacterFormat_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_ITextCharacterFormat <L"Windows.UI.Text.ITextCharacterFormat">
DEFINE_IIDX(ITextCharacterFormat, "5ADEF3DB-05FB-442D-8065-642AFEA02CED")

.comdef ITextCharacterFormat : public IInspectable

    get_AllCaps		proc :ptr
    put_AllCaps		proc :Windows::UI::Text::FormatEffect
    get_BackgroundColor proc :ptr
    put_BackgroundColor proc :Windows::UI::Color
    get_Bold		proc :ptr
    put_Bold		proc :Windows::UI::Text::FormatEffect
    get_FontStretch	proc :ptr
    put_FontStretch	proc :Windows::UI::Text::FontStretch
    get_FontStyle	proc :ptr
    put_FontStyle	proc :Windows::UI::Text::FontStyle
    get_ForegroundColor proc :ptr
    put_ForegroundColor proc :Windows::UI::Color
    get_Hidden		proc :ptr
    put_Hidden		proc :Windows::UI::Text::FormatEffect
    get_Italic		proc :ptr
    put_Italic		proc :Windows::UI::Text::FormatEffect
    get_Kerning		proc :ptr
    put_Kerning		proc :FLOAT
    get_LanguageTag	proc :ptr
    put_LanguageTag	proc :HSTRING
    get_LinkType	proc :ptr
    get_Name		proc :ptr
    put_Name		proc :HSTRING
    get_Outline		proc :ptr
    put_Outline		proc :Windows::UI::Text::FormatEffect
    get_Position	proc :ptr
    put_Position	proc :FLOAT
    get_ProtectedText	proc :ptr
    put_ProtectedText	proc :Windows::UI::Text::FormatEffect
    get_Size		proc :ptr
    put_Size		proc :FLOAT
    get_SmallCaps	proc :ptr
    put_SmallCaps	proc :Windows::UI::Text::FormatEffect
    get_Spacing		proc :ptr
    put_Spacing		proc :FLOAT
    get_Strikethrough	proc :ptr
    put_Strikethrough	proc :Windows::UI::Text::FormatEffect
    get_Subscript	proc :ptr
    put_Subscript	proc :Windows::UI::Text::FormatEffect
    get_Superscript	proc :ptr
    put_Superscript	proc :Windows::UI::Text::FormatEffect
    get_TextScript	proc :ptr
    put_TextScript	proc :Windows::UI::Text::TextScript
    get_Underline	proc :ptr
    put_Underline	proc :Windows::UI::Text::UnderlineType
    get_Weight		proc :ptr
    put_Weight		proc :INT32
    SetClone		proc :ptr
    GetClone		proc :ptr
    IsEqual		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CITextParagraphFormat_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_ITextParagraphFormat <L"Windows.UI.Text.ITextParagraphFormat">
DEFINE_IIDX(ITextParagraphFormat, "2CF8CFA6-4676-498A-93F5-BBDBFC0BD883")

.comdef ITextParagraphFormat : public IInspectable

    get_Alignment	proc :ptr
    put_Alignment	proc :Windows::UI::Text::ParagraphAlignment
    get_FirstLineIndent proc :ptr
    get_KeepTogether	proc :ptr
    put_KeepTogether	proc :Windows::UI::Text::FormatEffect
    get_KeepWithNext	proc :ptr
    put_KeepWithNext	proc :Windows::UI::Text::FormatEffect
    get_LeftIndent	proc :ptr
    get_LineSpacing	proc :ptr
    get_LineSpacingRule proc :ptr
    get_ListAlignment	proc :ptr
    put_ListAlignment	proc :Windows::UI::Text::MarkerAlignment
    get_ListLevelIndex	proc :ptr
    put_ListLevelIndex	proc :INT32
    get_ListStart	proc :ptr
    put_ListStart	proc :INT32
    get_ListStyle	proc :ptr
    put_ListStyle	proc :Windows::UI::Text::MarkerStyle
    get_ListTab		proc :ptr
    put_ListTab		proc :FLOAT
    get_ListType	proc :ptr
    put_ListType	proc :Windows::UI::Text::MarkerType
    get_NoLineNumber	proc :ptr
    put_NoLineNumber	proc :Windows::UI::Text::FormatEffect
    get_PageBreakBefore proc :ptr
    put_PageBreakBefore proc :Windows::UI::Text::FormatEffect
    get_RightIndent	proc :ptr
    put_RightIndent	proc :FLOAT
    get_RightToLeft	proc :ptr
    put_RightToLeft	proc :Windows::UI::Text::FormatEffect
    get_Style		proc :ptr
    put_Style		proc :Windows::UI::Text::ParagraphStyle
    get_SpaceAfter	proc :ptr
    put_SpaceAfter	proc :FLOAT
    get_SpaceBefore	proc :ptr
    put_SpaceBefore	proc :FLOAT
    get_WidowControl	proc :ptr
    put_WidowControl	proc :Windows::UI::Text::FormatEffect
    get_TabCount	proc :ptr
    AddTab		proc :FLOAT, :Windows::UI::Text::TabAlignment, :Windows::UI::Text::TabLeader
    ClearAllTabs	proc
    DeleteTab		proc :FLOAT
    GetClone		proc :ptr
    GetTab		proc :INT32, :ptr, :ptr, :ptr
    IsEqual		proc :ptr, :ptr
    SetClone		proc :ptr
    SetIndents		proc :FLOAT, :FLOAT, :FLOAT
    SetLineSpacing	proc :Windows::UI::Text::LineSpacingRule, :FLOAT
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CIFontWeights_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CIFontWeights_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_IFontWeights <L"Windows.UI.Text.IFontWeights">
DEFINE_IIDX(IFontWeights, "7880A444-01AB-4997-8517-DF822A0C45F1")

.comdef IFontWeights : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CText_CIFontWeightsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Text_IFontWeightsStatics <L"Windows.UI.Text.IFontWeightsStatics">
DEFINE_IIDX(IFontWeightsStatics, "B3B579D5-1BA9-48EB-9DAD-C095E8C23BA3")

.comdef IFontWeightsStatics : public IInspectable

    get_Black		proc :ptr
    get_Bold		proc :ptr
    get_ExtraBlack	proc :ptr
    get_ExtraBold	proc :ptr
    get_ExtraLight	proc :ptr
    get_Light		proc :ptr
    get_Medium		proc :ptr
    get_Normal		proc :ptr
    get_SemiBold	proc :ptr
    get_SemiLight	proc :ptr
    get_Thin		proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Text_TextConstants_DEFINED
define RUNTIMECLASS_Windows_UI_Text_TextConstants_DEFINED
define RuntimeClass_Windows_UI_Text_TextConstants <L"Windows.UI.Text.TextConstants">
endif
ifndef RUNTIMECLASS_Windows_UI_Text_FontWeights_DEFINED
define RUNTIMECLASS_Windows_UI_Text_FontWeights_DEFINED
define RuntimeClass_Windows_UI_Text_FontWeights <L"Windows.UI.Text.FontWeights">
endif

endif
