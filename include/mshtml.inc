ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __mshtml_h__
define __mshtml_h__
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef __dimm_h__
include dimm.inc
endif
ifndef __shtypes_h__
include shtypes.inc
endif
ifndef __dispex_h__
include dispex.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include dxgitype.inc
ifndef _OLECTL_H_
include olectl.inc
endif

externdef CMDSETID_Forms3:GUID
externdef CLSID_MHTMLDocument:GUID
externdef CLSID_IEXMLDocument:GUID
externdef CLSID_SVGDocument:GUID
externdef CLSID_XHTMLDocument:GUID
externdef CLSID_HTADocument:GUID
externdef CLSID_HTMLApplication:GUID
externdef CLSID_HTMLPluginDocument:GUID

DEFINE_GUID(SID_SEditCommandTarget,0x3050f4b5,0x98b5,0x11cf,0xbb,0x82,0x00,0xaa,0x00,0xbd,0xce,0x0b)
DEFINE_GUID(CGID_EditStateCommands,0x3050f4b6,0x98b5,0x11cf,0xbb,0x82,0x00,0xaa,0x00,0xbd,0xce,0x0b)
DEFINE_GUID(SID_SHTMLEditHost,0x3050f6a0,0x98b5,0x11cf,0xbb,0x82,0x00,0xaa,0x00,0xbd,0xce,0x0b)
DEFINE_GUID(SID_SHTMLEditServices,0x3050f7f9,0x98b5,0x11cf,0xbb,0x82,0x00,0xaa,0x00,0xbd,0xce,0x0b)

define SID_SHTMLWindow <IID_IHTMLWindow2>
define SID_SElementBehaviorFactory <IID_IElementBehaviorFactory>
define SID_STrackingProtection <IID_ITrackingProtection>

define COOKIEACTION_NONE	   0x00000000
define COOKIEACTION_ACCEPT	   0x00000001
define COOKIEACTION_REJECT	   0x00000002
define COOKIEACTION_DOWNGRADE	   0x00000004
define COOKIEACTION_LEASH	   0x00000008
define COOKIEACTION_SUPPRESS	   0x00000010
define COOKIEACTION_READ	   0x00000020

define PRIVACY_URLISTOPLEVEL	      0x00010000
define PRIVACY_URLHASCOMPACTPOLICY    0x00020000
define PRIVACY_URLHASPOSTDATA	      0x00080000
define PRIVACY_URLHASPOLICYREFLINK    0x00100000
define PRIVACY_URLHASPOLICYREFHEADER  0x00200000
define PRIVACY_URLHASP3PHEADER	      0x00400000

define DEBUGCALLBACKNOTIFICATION_TIMEOUT				0x00000001
define DEBUGCALLBACKNOTIFICATION_INTERVAL				0x00000002
define DEBUGCALLBACKNOTIFICATION_IMMEDIATE				0x00000004
define DEBUGCALLBACKNOTIFICATION_ANIMATIONFRAME				0x00000008
define DEBUGCALLBACKNOTIFICATION_DOMEVENT				0x00000010
define DEBUGDOMEVENTPROPAGATIONSTATUS_DEFAULTCANCELED			0x00000001
define DEBUGDOMEVENTPROPAGATIONSTATUS_STOPIMMEDIATEPROPAGATION		0x00000002
define DEBUGDOMEVENTPROPAGATIONSTATUS_STOPPROPAGATION			0x00000004

ifndef __IHTMLFiltersCollection_INTERFACE_DEFINED__
define __IHTMLFiltersCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFiltersCollection, "3050f3ee-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFiltersCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr
   .ends

endif
ifndef __IIE70DispatchEx_INTERFACE_DEFINED__
define __IIE70DispatchEx_INTERFACE_DEFINED__
DEFINE_IIDX(IIE70DispatchEx, "3051046b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IIE70DispatchEx : public IDispatchEx

   .ends

endif
ifndef __IIE80DispatchEx_INTERFACE_DEFINED__
define __IIE80DispatchEx_INTERFACE_DEFINED__
DEFINE_IIDX(IIE80DispatchEx, "3051046c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IIE80DispatchEx : public IDispatchEx

   .ends

endif
ifndef __MSHTML_LIBRARY_DEFINED__
define __MSHTML_LIBRARY_DEFINED__
.enum htmlDesignMode {
    htmlDesignModeInherit	= -2,
    htmlDesignModeOn	= -1,
    htmlDesignModeOff	= 0,
    htmlDesignMode_Max	= 2147483647
    }
.enum htmlZOrder {
    htmlZOrderFront	= 0,
    htmlZOrderBack	= 1,
    htmlZOrder_Max	= 2147483647
    }
.enum htmlClear {
    htmlClearNotSet	= 0,
    htmlClearAll	= 1,
    htmlClearLeft	= 2,
    htmlClearRight	= 3,
    htmlClearBoth	= 4,
    htmlClearNone	= 5,
    htmlClear_Max	= 2147483647
    }
.enum htmlControlAlign {
    htmlControlAlignNotSet	= 0,
    htmlControlAlignLeft	= 1,
    htmlControlAlignCenter	= 2,
    htmlControlAlignRight	= 3,
    htmlControlAlignTextTop	= 4,
    htmlControlAlignAbsMiddle	= 5,
    htmlControlAlignBaseline	= 6,
    htmlControlAlignAbsBottom	= 7,
    htmlControlAlignBottom	= 8,
    htmlControlAlignMiddle	= 9,
    htmlControlAlignTop = 10,
    htmlControlAlign_Max	= 2147483647
    }
.enum htmlBlockAlign {
    htmlBlockAlignNotSet	= 0,
    htmlBlockAlignLeft	= 1,
    htmlBlockAlignCenter	= 2,
    htmlBlockAlignRight = 3,
    htmlBlockAlignJustify	= 4,
    htmlBlockAlign_Max	= 2147483647
    }
.enum htmlReadyState {
    htmlReadyStateuninitialized = 0,
    htmlReadyStateloading	= 1,
    htmlReadyStateloaded	= 2,
    htmlReadyStateinteractive	= 3,
    htmlReadyStatecomplete	= 4,
    htmlReadyState_Max	= 2147483647
    }
.enum htmlLoop {
    htmlLoopLoopInfinite	= -1,
    htmlLoop_Max	= 2147483647
    }
.enum mediaType {
    mediaTypeNotSet	= 0,
    mediaTypeAll	= 511,
    mediaTypeAural	= 1,
    mediaTypeBraille	= 2,
    mediaTypeEmbossed	= 4,
    mediaTypeHandheld	= 8,
    mediaTypePrint	= 16,
    mediaTypeProjection = 32,
    mediaTypeScreen	= 64,
    mediaTypeTty	= 128,
    mediaTypeTv = 256,
    mediaType_Max	= 2147483647
    }
.enum DomConstructor {
    DomConstructorObject	= 0,
    DomConstructorAttr	= 1,
    DomConstructorBehaviorUrnsCollection	= 2,
    DomConstructorBookmarkCollection	= 3,
    DomConstructorCompatibleInfo	= 4,
    DomConstructorCompatibleInfoCollection	= 5,
    DomConstructorControlRangeCollection	= 6,
    DomConstructorCSSCurrentStyleDeclaration	= 7,
    DomConstructorCSSRuleList	= 8,
    DomConstructorCSSRuleStyleDeclaration	= 9,
    DomConstructorCSSStyleDeclaration	= 10,
    DomConstructorCSSStyleRule	= 11,
    DomConstructorCSSStyleSheet = 12,
    DomConstructorDataTransfer	= 13,
    DomConstructorDOMImplementation	= 14,
    DomConstructorElement	= 15,
    DomConstructorEvent = 16,
    DomConstructorHistory	= 17,
    DomConstructorHTCElementBehaviorDefaults	= 18,
    DomConstructorHTMLAnchorElement	= 19,
    DomConstructorHTMLAreaElement	= 20,
    DomConstructorHTMLAreasCollection	= 21,
    DomConstructorHTMLBaseElement	= 22,
    DomConstructorHTMLBaseFontElement	= 23,
    DomConstructorHTMLBGSoundElement	= 24,
    DomConstructorHTMLBlockElement	= 25,
    DomConstructorHTMLBodyElement	= 26,
    DomConstructorHTMLBRElement = 27,
    DomConstructorHTMLButtonElement	= 28,
    DomConstructorHTMLCollection	= 29,
    DomConstructorHTMLCommentElement	= 30,
    DomConstructorHTMLDDElement = 31,
    DomConstructorHTMLDivElement	= 32,
    DomConstructorHTMLDocument	= 33,
    DomConstructorHTMLDListElement	= 34,
    DomConstructorHTMLDTElement = 35,
    DomConstructorHTMLEmbedElement	= 36,
    DomConstructorHTMLFieldSetElement	= 37,
    DomConstructorHTMLFontElement	= 38,
    DomConstructorHTMLFormElement	= 39,
    DomConstructorHTMLFrameElement	= 40,
    DomConstructorHTMLFrameSetElement	= 41,
    DomConstructorHTMLGenericElement	= 42,
    DomConstructorHTMLHeadElement	= 43,
    DomConstructorHTMLHeadingElement	= 44,
    DomConstructorHTMLHRElement = 45,
    DomConstructorHTMLHtmlElement	= 46,
    DomConstructorHTMLIFrameElement	= 47,
    DomConstructorHTMLImageElement	= 48,
    DomConstructorHTMLInputElement	= 49,
    DomConstructorHTMLIsIndexElement	= 50,
    DomConstructorHTMLLabelElement	= 51,
    DomConstructorHTMLLegendElement	= 52,
    DomConstructorHTMLLIElement = 53,
    DomConstructorHTMLLinkElement	= 54,
    DomConstructorHTMLMapElement	= 55,
    DomConstructorHTMLMarqueeElement	= 56,
    DomConstructorHTMLMetaElement	= 57,
    DomConstructorHTMLModelessDialog	= 58,
    DomConstructorHTMLNamespaceInfo	= 59,
    DomConstructorHTMLNamespaceInfoCollection	= 60,
    DomConstructorHTMLNextIdElement	= 61,
    DomConstructorHTMLNoShowElement	= 62,
    DomConstructorHTMLObjectElement	= 63,
    DomConstructorHTMLOListElement	= 64,
    DomConstructorHTMLOptionElement	= 65,
    DomConstructorHTMLParagraphElement	= 66,
    DomConstructorHTMLParamElement	= 67,
    DomConstructorHTMLPhraseElement	= 68,
    DomConstructorHTMLPluginsCollection = 69,
    DomConstructorHTMLPopup	= 70,
    DomConstructorHTMLScriptElement	= 71,
    DomConstructorHTMLSelectElement	= 72,
    DomConstructorHTMLSpanElement	= 73,
    DomConstructorHTMLStyleElement	= 74,
    DomConstructorHTMLTableCaptionElement	= 75,
    DomConstructorHTMLTableCellElement	= 76,
    DomConstructorHTMLTableColElement	= 77,
    DomConstructorHTMLTableElement	= 78,
    DomConstructorHTMLTableRowElement	= 79,
    DomConstructorHTMLTableSectionElement	= 80,
    DomConstructorHTMLTextAreaElement	= 81,
    DomConstructorHTMLTextElement	= 82,
    DomConstructorHTMLTitleElement	= 83,
    DomConstructorHTMLUListElement	= 84,
    DomConstructorHTMLUnknownElement	= 85,
    DomConstructorImage = 86,
    DomConstructorLocation	= 87,
    DomConstructorNamedNodeMap	= 88,
    DomConstructorNavigator	= 89,
    DomConstructorNodeList	= 90,
    DomConstructorOption	= 91,
    DomConstructorScreen	= 92,
    DomConstructorSelection	= 93,
    DomConstructorStaticNodeList	= 94,
    DomConstructorStorage	= 95,
    DomConstructorStyleSheetList	= 96,
    DomConstructorStyleSheetPage	= 97,
    DomConstructorStyleSheetPageList	= 98,
    DomConstructorText	= 99,
    DomConstructorTextRange	= 100,
    DomConstructorTextRangeCollection	= 101,
    DomConstructorTextRectangle = 102,
    DomConstructorTextRectangleList	= 103,
    DomConstructorWindow	= 104,
    DomConstructorXDomainRequest	= 105,
    DomConstructorXMLHttpRequest	= 106,
    DomConstructorMax	= 107,
    DomConstructor_Max	= 2147483647
    }
.enum styleTextTransform {
    styleTextTransformNotSet	= 0,
    styleTextTransformCapitalize	= 1,
    styleTextTransformLowercase = 2,
    styleTextTransformUppercase = 3,
    styleTextTransformNone	= 4,
    styleTextTransform_Max	= 2147483647
    }
.enum styleDataRepeat {
    styleDataRepeatNone = 0,
    styleDataRepeatInner	= 1,
    styleDataRepeat_Max = 2147483647
    }
.enum styleOverflow {
    styleOverflowNotSet = 0,
    styleOverflowAuto	= 1,
    styleOverflowHidden = 2,
    styleOverflowVisible	= 3,
    styleOverflowScroll = 4,
    styleOverflow_Max	= 2147483647
    }
.enum styleMsOverflowStyle {
    styleMsOverflowStyleNotSet	= 0,
    styleMsOverflowStyleAuto	= 1,
    styleMsOverflowStyleNone	= 2,
    styleMsOverflowStyleScrollbar	= 3,
    styleMsOverflowStyleMsAutoHidingScrollbar	= 4,
    styleMsOverflowStyle_Max	= 2147483647
    }
.enum styleTableLayout {
    styleTableLayoutNotSet	= 0,
    styleTableLayoutAuto	= 1,
    styleTableLayoutFixed	= 2,
    styleTableLayout_Max	= 2147483647
    }
.enum styleBorderCollapse {
    styleBorderCollapseNotSet	= 0,
    styleBorderCollapseSeparate = 1,
    styleBorderCollapseCollapse = 2,
    styleBorderCollapse_Max	= 2147483647
    }
.enum styleCaptionSide {
    styleCaptionSideNotSet	= 0,
    styleCaptionSideTop = 1,
    styleCaptionSideBottom	= 2,
    styleCaptionSideLeft	= 3,
    styleCaptionSideRight	= 4,
    styleCaptionSide_Max	= 2147483647
    }
.enum styleEmptyCells {
    styleEmptyCellsNotSet	= 0,
    styleEmptyCellsShow = 1,
    styleEmptyCellsHide = 2,
    styleEmptyCells_Max = 2147483647
    }
.enum styleFontStyle {
    styleFontStyleNotSet	= 0,
    styleFontStyleItalic	= 1,
    styleFontStyleOblique	= 2,
    styleFontStyleNormal	= 3,
    styleFontStyle_Max	= 2147483647
    }
.enum styleFontVariant {
    styleFontVariantNotSet	= 0,
    styleFontVariantSmallCaps	= 1,
    styleFontVariantNormal	= 2,
    styleFontVariant_Max	= 2147483647
    }
.enum styleBackgroundRepeat {
    styleBackgroundRepeatRepeat = 0,
    styleBackgroundRepeatRepeatX	= 1,
    styleBackgroundRepeatRepeatY	= 2,
    styleBackgroundRepeatNoRepeat	= 3,
    styleBackgroundRepeatNotSet = 4,
    styleBackgroundRepeat_Max	= 2147483647
    }
.enum styleBackgroundAttachment {
    styleBackgroundAttachmentFixed	= 0,
    styleBackgroundAttachmentScroll	= 1,
    styleBackgroundAttachmentNotSet	= 2,
    styleBackgroundAttachment_Max	= 2147483647
    }
.enum styleBackgroundAttachment3 {
    styleBackgroundAttachment3Fixed	= 0,
    styleBackgroundAttachment3Scroll	= 1,
    styleBackgroundAttachment3Local	= 2,
    styleBackgroundAttachment3NotSet	= 3,
    styleBackgroundAttachment3_Max	= 2147483647
    }
.enum styleBackgroundClip {
    styleBackgroundClipBorderBox	= 0,
    styleBackgroundClipPaddingBox	= 1,
    styleBackgroundClipContentBox	= 2,
    styleBackgroundClipNotSet	= 3,
    styleBackgroundClip_Max	= 2147483647
    }
.enum styleBackgroundOrigin {
    styleBackgroundOriginBorderBox	= 0,
    styleBackgroundOriginPaddingBox	= 1,
    styleBackgroundOriginContentBox	= 2,
    styleBackgroundOriginNotSet = 3,
    styleBackgroundOrigin_Max	= 2147483647
    }
.enum styleVerticalAlign {
    styleVerticalAlignAuto	= 0,
    styleVerticalAlignBaseline	= 1,
    styleVerticalAlignSub	= 2,
    styleVerticalAlignSuper	= 3,
    styleVerticalAlignTop	= 4,
    styleVerticalAlignTextTop	= 5,
    styleVerticalAlignMiddle	= 6,
    styleVerticalAlignBottom	= 7,
    styleVerticalAlignTextBottom	= 8,
    styleVerticalAlignInherit	= 9,
    styleVerticalAlignNotSet	= 10,
    styleVerticalAlign_Max	= 2147483647
    }
.enum styleFontWeight {
    styleFontWeightNotSet	= 0,
    styleFontWeight100	= 1,
    styleFontWeight200	= 2,
    styleFontWeight300	= 3,
    styleFontWeight400	= 4,
    styleFontWeight500	= 5,
    styleFontWeight600	= 6,
    styleFontWeight700	= 7,
    styleFontWeight800	= 8,
    styleFontWeight900	= 9,
    styleFontWeightNormal	= 10,
    styleFontWeightBold = 11,
    styleFontWeightBolder	= 12,
    styleFontWeightLighter	= 13,
    styleFontWeight_Max = 2147483647
    }
.enum styleFontSize {
    styleFontSizeXXSmall	= 0,
    styleFontSizeXSmall = 1,
    styleFontSizeSmall	= 2,
    styleFontSizeMedium = 3,
    styleFontSizeLarge	= 4,
    styleFontSizeXLarge = 5,
    styleFontSizeXXLarge	= 6,
    styleFontSizeSmaller	= 7,
    styleFontSizeLarger = 8,
    styleFontSize_Max	= 2147483647
    }
.enum styleZIndex {
    styleZIndexAuto	= -2147483647,
    styleZIndex_Max	= 2147483647
    }
.enum styleWidowsOrphans {
    styleWidowsOrphansNotSet	= -2147483647,
    styleWidowsOrphans_Max	= 2147483647
    }
.enum styleAuto {
    styleAutoAuto	= 0,
    styleAuto_Max	= 2147483647
    }
.enum styleNone {
    styleNoneNone	= 0,
    styleNone_Max	= 2147483647
    }
.enum styleNormal {
    styleNormalNormal	= 0,
    styleNormal_Max	= 2147483647
    }
.enum styleBorderWidth {
    styleBorderWidthThin	= 0,
    styleBorderWidthMedium	= 1,
    styleBorderWidthThick	= 2,
    styleBorderWidth_Max	= 2147483647
    }
.enum stylePosition {
    stylePositionNotSet = 0,
    stylePositionstatic = 1,
    stylePositionrelative	= 2,
    stylePositionabsolute	= 3,
    stylePositionfixed	= 4,
    stylePositionMsPage = 5,
    stylePositionMsDeviceFixed	= 6,
    stylePosition_Max	= 2147483647
    }
.enum styleBorderStyle {
    styleBorderStyleNotSet	= 0,
    styleBorderStyleDotted	= 1,
    styleBorderStyleDashed	= 2,
    styleBorderStyleSolid	= 3,
    styleBorderStyleDouble	= 4,
    styleBorderStyleGroove	= 5,
    styleBorderStyleRidge	= 6,
    styleBorderStyleInset	= 7,
    styleBorderStyleOutset	= 8,
    styleBorderStyleWindowInset = 9,
    styleBorderStyleNone	= 10,
    styleBorderStyleHidden	= 11,
    styleBorderStyle_Max	= 2147483647
    }
.enum styleOutlineStyle {
    styleOutlineStyleNotSet	= 0,
    styleOutlineStyleDotted	= 1,
    styleOutlineStyleDashed	= 2,
    styleOutlineStyleSolid	= 3,
    styleOutlineStyleDouble	= 4,
    styleOutlineStyleGroove	= 5,
    styleOutlineStyleRidge	= 6,
    styleOutlineStyleInset	= 7,
    styleOutlineStyleOutset	= 8,
    styleOutlineStyleWindowInset	= 9,
    styleOutlineStyleNone	= 10,
    styleOutlineStyle_Max	= 2147483647
    }
.enum styleStyleFloat {
    styleStyleFloatNotSet	= 0,
    styleStyleFloatLeft = 1,
    styleStyleFloatRight	= 2,
    styleStyleFloatNone = 3,
    styleStyleFloat_Max = 2147483647
    }
.enum styleDisplay {
    styleDisplayNotSet	= 0,
    styleDisplayBlock	= 1,
    styleDisplayInline	= 2,
    styleDisplayListItem	= 3,
    styleDisplayNone	= 4,
    styleDisplayTableHeaderGroup	= 5,
    styleDisplayTableFooterGroup	= 6,
    styleDisplayInlineBlock	= 7,
    styleDisplayTable	= 8,
    styleDisplayInlineTable	= 9,
    styleDisplayTableRow	= 10,
    styleDisplayTableRowGroup	= 11,
    styleDisplayTableColumn	= 12,
    styleDisplayTableColumnGroup	= 13,
    styleDisplayTableCell	= 14,
    styleDisplayTableCaption	= 15,
    styleDisplayRunIn	= 16,
    styleDisplayRuby	= 17,
    styleDisplayRubyBase	= 18,
    styleDisplayRubyText	= 19,
    styleDisplayRubyBaseContainer	= 20,
    styleDisplayRubyTextContainer	= 21,
    styleDisplayMsFlexbox	= 22,
    styleDisplayMsInlineFlexbox = 23,
    styleDisplayMsGrid	= 24,
    styleDisplayMsInlineGrid	= 25,
    styleDisplayFlex	= 26,
    styleDisplayInlineFlex	= 27,
    styleDisplay_Max	= 2147483647
    }
.enum styleVisibility {
    styleVisibilityNotSet	= 0,
    styleVisibilityInherit	= 1,
    styleVisibilityVisible	= 2,
    styleVisibilityHidden	= 3,
    styleVisibilityCollapse	= 4,
    styleVisibility_Max = 2147483647
    }
.enum styleListStyleType {
    styleListStyleTypeNotSet	= 0,
    styleListStyleTypeDisc	= 1,
    styleListStyleTypeCircle	= 2,
    styleListStyleTypeSquare	= 3,
    styleListStyleTypeDecimal	= 4,
    styleListStyleTypeLowerRoman	= 5,
    styleListStyleTypeUpperRoman	= 6,
    styleListStyleTypeLowerAlpha	= 7,
    styleListStyleTypeUpperAlpha	= 8,
    styleListStyleTypeNone	= 9,
    styleListStyleTypeDecimalLeadingZero	= 10,
    styleListStyleTypeGeorgian	= 11,
    styleListStyleTypeArmenian	= 12,
    styleListStyleTypeUpperLatin	= 13,
    styleListStyleTypeLowerLatin	= 14,
    styleListStyleTypeUpperGreek	= 15,
    styleListStyleTypeLowerGreek	= 16,
    styleListStyleType_Max	= 2147483647
    }
.enum styleListStylePosition {
    styleListStylePositionNotSet	= 0,
    styleListStylePositionInside	= 1,
    styleListStylePositionOutSide	= 2,
    styleListStylePosition_Max	= 2147483647
    }
.enum styleWhiteSpace {
    styleWhiteSpaceNotSet	= 0,
    styleWhiteSpaceNormal	= 1,
    styleWhiteSpacePre	= 2,
    styleWhiteSpaceNowrap	= 3,
    styleWhiteSpacePreline	= 4,
    styleWhiteSpacePrewrap	= 5,
    styleWhiteSpace_Max = 2147483647
    }
.enum stylePageBreak {
    stylePageBreakNotSet	= 0,
    stylePageBreakAuto	= 1,
    stylePageBreakAlways	= 2,
    stylePageBreakLeft	= 3,
    stylePageBreakRight = 4,
    stylePageBreakAvoid = 5,
    stylePageBreak_Max	= 2147483647
    }
.enum stylePageBreakInside {
    stylePageBreakInsideNotSet	= 0,
    stylePageBreakInsideAuto	= 1,
    stylePageBreakInsideAvoid	= 2,
    stylePageBreakInside_Max	= 2147483647
    }
.enum styleCursor {
    styleCursorAuto	= 0,
    styleCursorCrosshair	= 1,
    styleCursorDefault	= 2,
    styleCursorHand	= 3,
    styleCursorMove	= 4,
    styleCursorE_resize = 5,
    styleCursorNe_resize	= 6,
    styleCursorNw_resize	= 7,
    styleCursorN_resize = 8,
    styleCursorSe_resize	= 9,
    styleCursorSw_resize	= 10,
    styleCursorS_resize = 11,
    styleCursorW_resize = 12,
    styleCursorText	= 13,
    styleCursorWait	= 14,
    styleCursorHelp	= 15,
    styleCursorPointer	= 16,
    styleCursorProgress = 17,
    styleCursorNot_allowed	= 18,
    styleCursorNo_drop	= 19,
    styleCursorVertical_text	= 20,
    styleCursorall_scroll	= 21,
    styleCursorcol_resize	= 22,
    styleCursorrow_resize	= 23,
    styleCursorNone	= 24,
    styleCursorContext_menu	= 25,
    styleCursorEw_resize	= 26,
    styleCursorNs_resize	= 27,
    styleCursorNesw_resize	= 28,
    styleCursorNwse_resize	= 29,
    styleCursorCell	= 30,
    styleCursorCopy	= 31,
    styleCursorAlias	= 32,
    styleCursorcustom	= 33,
    styleCursorNotSet	= 34,
    styleCursor_Max	= 2147483647
    }
.enum styleDir {
    styleDirNotSet	= 0,
    styleDirLeftToRight = 1,
    styleDirRightToLeft = 2,
    styleDirInherit	= 3,
    styleDir_Max	= 2147483647
    }
.enum styleBidi {
    styleBidiNotSet	= 0,
    styleBidiNormal	= 1,
    styleBidiEmbed	= 2,
    styleBidiOverride	= 3,
    styleBidiInherit	= 4,
    styleBidi_Max	= 2147483647
    }
.enum styleImeMode {
    styleImeModeAuto	= 0,
    styleImeModeActive	= 1,
    styleImeModeInactive	= 2,
    styleImeModeDisabled	= 3,
    styleImeModeNotSet	= 4,
    styleImeMode_Max	= 2147483647
    }
.enum styleRubyAlign {
    styleRubyAlignNotSet	= 0,
    styleRubyAlignAuto	= 1,
    styleRubyAlignLeft	= 2,
    styleRubyAlignCenter	= 3,
    styleRubyAlignRight = 4,
    styleRubyAlignDistributeLetter	= 5,
    styleRubyAlignDistributeSpace	= 6,
    styleRubyAlignLineEdge	= 7,
    styleRubyAlign_Max	= 2147483647
    }
.enum styleRubyPosition {
    styleRubyPositionNotSet	= 0,
    styleRubyPositionAbove	= 1,
    styleRubyPositionInline	= 2,
    styleRubyPosition_Max	= 2147483647
    }
.enum styleRubyOverhang {
    styleRubyOverhangNotSet	= 0,
    styleRubyOverhangAuto	= 1,
    styleRubyOverhangWhitespace = 2,
    styleRubyOverhangNone	= 3,
    styleRubyOverhang_Max	= 2147483647
    }
.enum styleLayoutGridChar {
    styleLayoutGridCharNotSet	= 0,
    styleLayoutGridCharAuto	= 1,
    styleLayoutGridCharNone	= 2,
    styleLayoutGridChar_Max	= 2147483647
    }
.enum styleLayoutGridLine {
    styleLayoutGridLineNotSet	= 0,
    styleLayoutGridLineAuto	= 1,
    styleLayoutGridLineNone	= 2,
    styleLayoutGridLine_Max	= 2147483647
    }
.enum styleLayoutGridMode {
    styleLayoutGridModeNotSet	= 0,
    styleLayoutGridModeChar	= 1,
    styleLayoutGridModeLine	= 2,
    styleLayoutGridModeBoth	= 3,
    styleLayoutGridModeNone	= 4,
    styleLayoutGridMode_Max	= 2147483647
    }
.enum styleLayoutGridType {
    styleLayoutGridTypeNotSet	= 0,
    styleLayoutGridTypeLoose	= 1,
    styleLayoutGridTypeStrict	= 2,
    styleLayoutGridTypeFixed	= 3,
    styleLayoutGridType_Max	= 2147483647
    }
.enum styleLineBreak {
    styleLineBreakNotSet	= 0,
    styleLineBreakNormal	= 1,
    styleLineBreakStrict	= 2,
    styleLineBreak_Max	= 2147483647
    }
.enum styleWordBreak {
    styleWordBreakNotSet	= 0,
    styleWordBreakNormal	= 1,
    styleWordBreakBreakAll	= 2,
    styleWordBreakKeepAll	= 3,
    styleWordBreak_Max	= 2147483647
    }
.enum styleWordWrap {
    styleWordWrapNotSet = 0,
    styleWordWrapOff	= 1,
    styleWordWrapOn	= 2,
    styleWordWrap_Max	= 2147483647
    }
.enum styleTextJustify {
    styleTextJustifyNotSet	= 0,
    styleTextJustifyInterWord	= 1,
    styleTextJustifyNewspaper	= 2,
    styleTextJustifyDistribute	= 3,
    styleTextJustifyDistributeAllLines	= 4,
    styleTextJustifyInterIdeograph	= 5,
    styleTextJustifyInterCluster	= 6,
    styleTextJustifyKashida	= 7,
    styleTextJustifyAuto	= 8,
    styleTextJustify_Max	= 2147483647
    }
.enum styleTextAlignLast {
    styleTextAlignLastNotSet	= 0,
    styleTextAlignLastLeft	= 1,
    styleTextAlignLastCenter	= 2,
    styleTextAlignLastRight	= 3,
    styleTextAlignLastJustify	= 4,
    styleTextAlignLastAuto	= 5,
    styleTextAlignLast_Max	= 2147483647
    }
.enum styleTextJustifyTrim {
    styleTextJustifyTrimNotSet	= 0,
    styleTextJustifyTrimNone	= 1,
    styleTextJustifyTrimPunctuation	= 2,
    styleTextJustifyTrimPunctAndKana	= 3,
    styleTextJustifyTrim_Max	= 2147483647
    }
.enum styleAccelerator {
    styleAcceleratorFalse	= 0,
    styleAcceleratorTrue	= 1,
    styleAccelerator_Max	= 2147483647
    }
.enum styleLayoutFlow {
    styleLayoutFlowHorizontal	= 0,
    styleLayoutFlowVerticalIdeographic	= 1,
    styleLayoutFlowNotSet	= 2,
    styleLayoutFlow_Max = 2147483647
    }
.enum styleBlockProgression {
    styleBlockProgressionTb	= 0,
    styleBlockProgressionRl	= 1,
    styleBlockProgressionBt	= 2,
    styleBlockProgressionLr	= 3,
    styleBlockProgressionNotSet = 4,
    styleBlockProgression_Max	= 2147483647
    }
.enum styleWritingMode {
    styleWritingModeLrtb	= 0,
    styleWritingModeTbrl	= 1,
    styleWritingModeRltb	= 2,
    styleWritingModeBtrl	= 3,
    styleWritingModeNotSet	= 4,
    styleWritingModeTblr	= 5,
    styleWritingModeBtlr	= 6,
    styleWritingModeLrbt	= 7,
    styleWritingModeRlbt	= 8,
    styleWritingModeLr	= 9,
    styleWritingModeRl	= 10,
    styleWritingModeTb	= 11,
    styleWritingMode_Max	= 2147483647
    }
.enum styleBool {
    styleBoolFalse	= 0,
    styleBoolTrue	= 1,
    styleBool_Max	= 2147483647
    }
.enum styleTextUnderlinePosition {
    styleTextUnderlinePositionBelow	= 0,
    styleTextUnderlinePositionAbove	= 1,
    styleTextUnderlinePositionAuto	= 2,
    styleTextUnderlinePositionNotSet	= 3,
    styleTextUnderlinePosition_Max	= 2147483647
    }
.enum styleTextOverflow {
    styleTextOverflowClip	= 0,
    styleTextOverflowEllipsis	= 1,
    styleTextOverflowNotSet	= 2,
    styleTextOverflow_Max	= 2147483647
    }
.enum styleInterpolation {
    styleInterpolationNotSet	= 0,
    styleInterpolationNN	= 1,
    styleInterpolationBCH	= 2,
    styleInterpolation_Max	= 2147483647
    }
.enum styleBoxSizing {
    styleBoxSizingNotSet	= 0,
    styleBoxSizingContentBox	= 1,
    styleBoxSizingBorderBox	= 2,
    styleBoxSizing_Max	= 2147483647
    }
.enum styleFlex {
    styleFlexNone	= 0,
    styleFlexNotSet	= 1,
    styleFlex_Max	= 2147483647
    }
.enum styleFlexBasis {
    styleFlexBasisAuto	= 0,
    styleFlexBasisNotSet	= 1,
    styleFlexBasis_Max	= 2147483647
    }
.enum styleFlexDirection {
    styleFlexDirectionRow	= 0,
    styleFlexDirectionRowReverse	= 1,
    styleFlexDirectionColumn	= 2,
    styleFlexDirectionColumnReverse	= 3,
    styleFlexDirectionNotSet	= 4,
    styleFlexDirection_Max	= 2147483647
    }
.enum styleFlexWrap {
    styleFlexWrapNowrap = 0,
    styleFlexWrapWrap	= 1,
    styleFlexWrapWrapReverse	= 2,
    styleFlexWrapNotSet = 3,
    styleFlexWrap_Max	= 2147483647
    }
.enum styleMsFlexAlign {
    styleMsFlexAlignStart	= 0,
    styleMsFlexAlignEnd = 1,
    styleMsFlexAlignCenter	= 2,
    styleMsFlexAlignBaseline	= 3,
    styleMsFlexAlignStretch	= 4,
    styleMsFlexAlignNotSet	= 5,
    styleMsFlexAlign_Max	= 2147483647
    }
.enum styleAlignItems {
    styleAlignItemsFlexStart	= 0,
    styleAlignItemsFlexEnd	= 1,
    styleAlignItemsCenter	= 2,
    styleAlignItemsBaseline	= 3,
    styleAlignItemsStretch	= 4,
    styleAlignItemsNotSet	= 5,
    styleAlignItems_Max = 2147483647
    }
.enum styleMsFlexItemAlign {
    styleMsFlexItemAlignStart	= 0,
    styleMsFlexItemAlignEnd	= 1,
    styleMsFlexItemAlignCenter	= 2,
    styleMsFlexItemAlignBaseline	= 3,
    styleMsFlexItemAlignStretch = 4,
    styleMsFlexItemAlignAuto	= 5,
    styleMsFlexItemAlignNotSet	= 6,
    styleMsFlexItemAlign_Max	= 2147483647
    }
.enum styleAlignSelf {
    styleAlignSelfFlexStart	= 0,
    styleAlignSelfFlexEnd	= 1,
    styleAlignSelfCenter	= 2,
    styleAlignSelfBaseline	= 3,
    styleAlignSelfStretch	= 4,
    styleAlignSelfAuto	= 5,
    styleAlignSelfNotSet	= 6,
    styleAlignSelf_Max	= 2147483647
    }
.enum styleMsFlexPack {
    styleMsFlexPackStart	= 0,
    styleMsFlexPackEnd	= 1,
    styleMsFlexPackCenter	= 2,
    styleMsFlexPackJustify	= 3,
    styleMsFlexPackDistribute	= 4,
    styleMsFlexPackNotSet	= 5,
    styleMsFlexPack_Max = 2147483647
    }
.enum styleJustifyContent {
    styleJustifyContentFlexStart	= 0,
    styleJustifyContentFlexEnd	= 1,
    styleJustifyContentCenter	= 2,
    styleJustifyContentSpaceBetween	= 3,
    styleJustifyContentSpaceAround	= 4,
    styleJustifyContentNotSet	= 5,
    styleJustifyContent_Max	= 2147483647
    }
.enum styleMsFlexLinePack {
    styleMsFlexLinePackStart	= 0,
    styleMsFlexLinePackEnd	= 1,
    styleMsFlexLinePackCenter	= 2,
    styleMsFlexLinePackJustify	= 3,
    styleMsFlexLinePackDistribute	= 4,
    styleMsFlexLinePackStretch	= 5,
    styleMsFlexLinePackNotSet	= 6,
    styleMsFlexLinePack_Max	= 2147483647
    }
.enum styleAlignContent {
    styleAlignContentFlexStart	= 0,
    styleAlignContentFlexEnd	= 1,
    styleAlignContentCenter	= 2,
    styleAlignContentSpaceBetween	= 3,
    styleAlignContentSpaceAround	= 4,
    styleAlignContentStretch	= 5,
    styleAlignContentNotSet	= 6,
    styleAlignContent_Max	= 2147483647
    }
.enum styleColumnFill {
    styleColumnFillAuto = 0,
    styleColumnFillBalance	= 1,
    styleColumnFillNotSet	= 2,
    styleColumnFill_Max = 2147483647
    }
.enum styleColumnSpan {
    styleColumnSpanOne	= 0,
    styleColumnSpanAll	= 1,
    styleColumnSpanNotSet	= 2,
    styleColumnSpan_Max = 2147483647
    }
.enum styleBreak {
    styleBreakNotSet	= 0,
    styleBreakAuto	= 1,
    styleBreakAlways	= 2,
    styleBreakAvoid	= 3,
    styleBreakLeft	= 4,
    styleBreakRight	= 5,
    styleBreakPage	= 6,
    styleBreakColumn	= 7,
    styleBreakAvoidPage = 8,
    styleBreakAvoidColumn	= 9,
    styleBreak_Max	= 2147483647
    }
.enum styleBreakInside {
    styleBreakInsideNotSet	= 0,
    styleBreakInsideAuto	= 1,
    styleBreakInsideAvoid	= 2,
    styleBreakInsideAvoidPage	= 3,
    styleBreakInsideAvoidColumn = 4,
    styleBreakInside_Max	= 2147483647
    }
.enum styleMsScrollChaining {
    styleMsScrollChainingNotSet = 0,
    styleMsScrollChainingNone	= 1,
    styleMsScrollChainingChained	= 2,
    styleMsScrollChaining_Max	= 2147483647
    }
.enum styleMsContentZooming {
    styleMsContentZoomingNotSet = 0,
    styleMsContentZoomingNone	= 1,
    styleMsContentZoomingZoom	= 2,
    styleMsContentZooming_Max	= 2147483647
    }
.enum styleMsContentZoomSnapType {
    styleMsContentZoomSnapTypeNotSet	= 0,
    styleMsContentZoomSnapTypeNone	= 1,
    styleMsContentZoomSnapTypeMandatory = 2,
    styleMsContentZoomSnapTypeProximity = 3,
    styleMsContentZoomSnapType_Max	= 2147483647
    }
.enum styleMsScrollRails {
    styleMsScrollRailsNotSet	= 0,
    styleMsScrollRailsNone	= 1,
    styleMsScrollRailsRailed	= 2,
    styleMsScrollRails_Max	= 2147483647
    }
.enum styleMsContentZoomChaining {
    styleMsContentZoomChainingNotSet	= 0,
    styleMsContentZoomChainingNone	= 1,
    styleMsContentZoomChainingChained	= 2,
    styleMsContentZoomChaining_Max	= 2147483647
    }
.enum styleMsScrollSnapType {
    styleMsScrollSnapTypeNotSet = 0,
    styleMsScrollSnapTypeNone	= 1,
    styleMsScrollSnapTypeMandatory	= 2,
    styleMsScrollSnapTypeProximity	= 3,
    styleMsScrollSnapType_Max	= 2147483647
    }
.enum styleGridColumn {
    styleGridColumnNotSet	= 0,
    styleGridColumn_Max = 2147483647
    }
.enum styleGridColumnAlign {
    styleGridColumnAlignCenter	= 0,
    styleGridColumnAlignEnd	= 1,
    styleGridColumnAlignStart	= 2,
    styleGridColumnAlignStretch = 3,
    styleGridColumnAlignNotSet	= 4,
    styleGridColumnAlign_Max	= 2147483647
    }
.enum styleGridColumnSpan {
    styleGridColumnSpanNotSet	= 0,
    styleGridColumnSpan_Max	= 2147483647
    }
.enum styleGridRow {
    styleGridRowNotSet	= 0,
    styleGridRow_Max	= 2147483647
    }
.enum styleGridRowAlign {
    styleGridRowAlignCenter	= 0,
    styleGridRowAlignEnd	= 1,
    styleGridRowAlignStart	= 2,
    styleGridRowAlignStretch	= 3,
    styleGridRowAlignNotSet	= 4,
    styleGridRowAlign_Max	= 2147483647
    }
.enum styleGridRowSpan {
    styleGridRowSpanNotSet	= 0,
    styleGridRowSpan_Max	= 2147483647
    }
.enum styleWrapThrough {
    styleWrapThroughNotSet	= 0,
    styleWrapThroughWrap	= 1,
    styleWrapThroughNone	= 2,
    styleWrapThrough_Max	= 2147483647
    }
.enum styleWrapFlow {
    styleWrapFlowNotSet = 0,
    styleWrapFlowAuto	= 1,
    styleWrapFlowBoth	= 2,
    styleWrapFlowStart	= 3,
    styleWrapFlowEnd	= 4,
    styleWrapFlowClear	= 5,
    styleWrapFlowMinimum	= 6,
    styleWrapFlowMaximum	= 7,
    styleWrapFlow_Max	= 2147483647
    }
.enum styleAlignmentBaseline {
    styleAlignmentBaselineNotSet	= 0,
    styleAlignmentBaselineAfterEdge	= 1,
    styleAlignmentBaselineAlphabetic	= 2,
    styleAlignmentBaselineAuto	= 3,
    styleAlignmentBaselineBaseline	= 4,
    styleAlignmentBaselineBeforeEdge	= 5,
    styleAlignmentBaselineCentral	= 6,
    styleAlignmentBaselineHanging	= 7,
    styleAlignmentBaselineMathematical	= 8,
    styleAlignmentBaselineMiddle	= 9,
    styleAlignmentBaselineTextAfterEdge = 10,
    styleAlignmentBaselineTextBeforeEdge	= 11,
    styleAlignmentBaselineIdeographic	= 12,
    styleAlignmentBaseline_Max	= 2147483647
    }
.enum styleBaselineShift {
    styleBaselineShiftBaseline	= 0,
    styleBaselineShiftSub	= 1,
    styleBaselineShiftSuper	= 2,
    styleBaselineShift_Max	= 2147483647
    }
.enum styleClipRule {
    styleClipRuleNotSet = 0,
    styleClipRuleNonZero	= 1,
    styleClipRuleEvenOdd	= 2,
    styleClipRule_Max	= 2147483647
    }
.enum styleDominantBaseline {
    styleDominantBaselineNotSet = 0,
    styleDominantBaselineAlphabetic	= 1,
    styleDominantBaselineAuto	= 2,
    styleDominantBaselineCentral	= 3,
    styleDominantBaselineHanging	= 4,
    styleDominantBaselineIdeographic	= 5,
    styleDominantBaselineMathematical	= 6,
    styleDominantBaselineMiddle = 7,
    styleDominantBaselineNoChange	= 8,
    styleDominantBaselineResetSize	= 9,
    styleDominantBaselineTextAfterEdge	= 10,
    styleDominantBaselineTextBeforeEdge = 11,
    styleDominantBaselineUseScript	= 12,
    styleDominantBaseline_Max	= 2147483647
    }
.enum styleFillRule {
    styleFillRuleNotSet = 0,
    styleFillRuleNonZero	= 1,
    styleFillRuleEvenOdd	= 2,
    styleFillRule_Max	= 2147483647
    }
.enum styleFontStretch {
    styleFontStretchNotSet	= 0,
    styleFontStretchWider	= 1,
    styleFontStretchNarrower	= 2,
    styleFontStretchUltraCondensed	= 3,
    styleFontStretchExtraCondensed	= 4,
    styleFontStretchCondensed	= 5,
    styleFontStretchSemiCondensed	= 6,
    styleFontStretchNormal	= 7,
    styleFontStretchSemiExpanded	= 8,
    styleFontStretchExpanded	= 9,
    styleFontStretchExtraExpanded	= 10,
    styleFontStretchUltraExpanded	= 11,
    styleFontStretch_Max	= 2147483647
    }
.enum stylePointerEvents {
    stylePointerEventsNotSet	= 0,
    stylePointerEventsVisiblePainted	= 1,
    stylePointerEventsVisibleFill	= 2,
    stylePointerEventsVisibleStroke	= 3,
    stylePointerEventsVisible	= 4,
    stylePointerEventsPainted	= 5,
    stylePointerEventsFill	= 6,
    stylePointerEventsStroke	= 7,
    stylePointerEventsAll	= 8,
    stylePointerEventsNone	= 9,
    stylePointerEventsAuto	= 10,
    stylePointerEvents_Max	= 2147483647
    }
.enum styleEnableBackground {
    styleEnableBackgroundNotSet = 0,
    styleEnableBackgroundAccumulate	= 1,
    styleEnableBackgroundNew	= 2,
    styleEnableBackgroundInherit	= 3,
    styleEnableBackground_Max	= 2147483647
    }
.enum styleStrokeLinecap {
    styleStrokeLinecapNotSet	= 0,
    styleStrokeLinecapButt	= 1,
    styleStrokeLinecapRound	= 2,
    styleStrokeLinecapSquare	= 3,
    styleStrokeLinecap_Max	= 2147483647
    }
.enum styleStrokeLinejoin {
    styleStrokeLinejoinNotSet	= 0,
    styleStrokeLinejoinMiter	= 1,
    styleStrokeLinejoinRound	= 2,
    styleStrokeLinejoinBevel	= 3,
    styleStrokeLinejoin_Max	= 2147483647
    }
.enum styleTextAnchor {
    styleTextAnchorNotSet	= 0,
    styleTextAnchorStart	= 1,
    styleTextAnchorMiddle	= 2,
    styleTextAnchorEnd	= 3,
    styleTextAnchor_Max = 2147483647
    }
.enum styleAttrType {
    styleAttrTypeString = 0,
    styleAttrTypeColor	= 1,
    styleAttrTypeUrl	= 2,
    styleAttrTypeInteger	= 3,
    styleAttrTypeNumber = 4,
    styleAttrTypeLength = 5,
    styleAttrTypePx	= 6,
    styleAttrTypeEm	= 7,
    styleAttrTypeEx	= 8,
    styleAttrTypeIn	= 9,
    styleAttrTypeCm	= 10,
    styleAttrTypeMm	= 11,
    styleAttrTypePt	= 12,
    styleAttrTypePc	= 13,
    styleAttrTypeRem	= 14,
    styleAttrTypeCh	= 15,
    styleAttrTypeVh	= 16,
    styleAttrTypeVw	= 17,
    styleAttrTypeVmin	= 18,
    styleAttrTypePercentage	= 19,
    styleAttrTypeAngle	= 20,
    styleAttrTypeDeg	= 21,
    styleAttrTypeRad	= 22,
    styleAttrTypeGrad	= 23,
    styleAttrTypeTime	= 24,
    styleAttrTypeS	= 25,
    styleAttrTypeMs	= 26,
    styleAttrType_Max	= 2147483647
    }
.enum styleInitialColor {
    styleInitialColorNoInitial	= 0,
    styleInitialColorColorProperty	= 1,
    styleInitialColorTransparent	= 2,
    styleInitialColorInvert	= 3,
    styleInitialColor_Max	= 2147483647
    }
.enum styleInitialString {
    styleInitialStringNoInitial = 0,
    styleInitialStringNone	= 1,
    styleInitialStringAuto	= 2,
    styleInitialStringNormal	= 3,
    styleInitialString_Max	= 2147483647
    }
.enum styleTransformOriginX {
    styleTransformOriginXNotSet = 0,
    styleTransformOriginXLeft	= 1,
    styleTransformOriginXCenter = 2,
    styleTransformOriginXRight	= 3,
    styleTransformOriginX_Max	= 2147483647
    }
.enum styleTransformOriginY {
    styleTransformOriginYNotSet = 0,
    styleTransformOriginYTop	= 1,
    styleTransformOriginYCenter = 2,
    styleTransformOriginYBottom = 3,
    styleTransformOriginY_Max	= 2147483647
    }
.enum stylePerspectiveOriginX {
    stylePerspectiveOriginXNotSet	= 0,
    stylePerspectiveOriginXLeft = 1,
    stylePerspectiveOriginXCenter	= 2,
    stylePerspectiveOriginXRight	= 3,
    stylePerspectiveOriginX_Max = 2147483647
    }
.enum stylePerspectiveOriginY {
    stylePerspectiveOriginYNotSet	= 0,
    stylePerspectiveOriginYTop	= 1,
    stylePerspectiveOriginYCenter	= 2,
    stylePerspectiveOriginYBottom	= 3,
    stylePerspectiveOriginY_Max = 2147483647
    }
.enum styleTransformStyle {
    styleTransformStyleFlat	= 0,
    styleTransformStyleNotSet	= 1,
    styleTransformStyle_Max	= 2147483647
    }
.enum styleBackfaceVisibility {
    styleBackfaceVisibilityVisible	= 0,
    styleBackfaceVisibilityHidden	= 1,
    styleBackfaceVisibilityNotSet	= 2,
    styleBackfaceVisibility_Max = 2147483647
    }
.enum styleTextSizeAdjust {
    styleTextSizeAdjustNone	= 0,
    styleTextSizeAdjustAuto	= 1,
    styleTextSizeAdjust_Max	= 2147483647
    }
.enum styleColorInterpolationFilters {
    styleColorInterpolationFiltersAuto	= 0,
    styleColorInterpolationFiltersSRgb	= 1,
    styleColorInterpolationFiltersLinearRgb	= 2,
    styleColorInterpolationFiltersNotSet	= 3,
    styleColorInterpolationFilters_Max	= 2147483647
    }
.enum styleHyphens {
    styleHyphensNone	= 0,
    styleHyphensManual	= 1,
    styleHyphensAuto	= 2,
    styleHyphensNotSet	= 3,
    styleHyphens_Max	= 2147483647
    }
.enum styleHyphenateLimitLines {
    styleHyphenateLimitLinesNoLimit	= 0,
    styleHyphenateLimitLines_Max	= 2147483647
    }
.enum styleMsAnimationPlayState {
    styleMsAnimationPlayStateRunning	= 0,
    styleMsAnimationPlayStatePaused	= 1,
    styleMsAnimationPlayStateNotSet	= 2,
    styleMsAnimationPlayState_Max	= 2147483647
    }
.enum styleMsAnimationDirection {
    styleMsAnimationDirectionNormal	= 0,
    styleMsAnimationDirectionAlternate	= 1,
    styleMsAnimationDirectionReverse	= 2,
    styleMsAnimationDirectionAlternateReverse	= 3,
    styleMsAnimationDirectionNotSet	= 4,
    styleMsAnimationDirection_Max	= 2147483647
    }
.enum styleMsAnimationFillMode {
    styleMsAnimationFillModeNone	= 0,
    styleMsAnimationFillModeForwards	= 1,
    styleMsAnimationFillModeBackwards	= 2,
    styleMsAnimationFillModeBoth	= 3,
    styleMsAnimationFillModeNotSet	= 4,
    styleMsAnimationFillMode_Max	= 2147483647
    }
.enum styleMsHighContrastAdjust {
    styleMsHighContrastAdjustNotSet	= 0,
    styleMsHighContrastAdjustAuto	= 1,
    styleMsHighContrastAdjustNone	= 2,
    styleMsHighContrastAdjust_Max	= 2147483647
    }
.enum styleMsUserSelect {
    styleMsUserSelectAuto	= 0,
    styleMsUserSelectText	= 1,
    styleMsUserSelectElement	= 2,
    styleMsUserSelectNone	= 3,
    styleMsUserSelectNotSet	= 4,
    styleMsUserSelect_Max	= 2147483647
    }
.enum styleMsTouchAction {
    styleMsTouchActionNotSet	= -1,
    styleMsTouchActionNone	= 0,
    styleMsTouchActionAuto	= 1,
    styleMsTouchActionManipulation	= 2,
    styleMsTouchActionDoubleTapZoom	= 4,
    styleMsTouchActionPanX	= 8,
    styleMsTouchActionPanY	= 16,
    styleMsTouchActionPinchZoom = 32,
    styleMsTouchActionCrossSlideX	= 64,
    styleMsTouchActionCrossSlideY	= 128,
    styleMsTouchAction_Max	= 2147483647
    }
.enum styleMsTouchSelect {
    styleMsTouchSelectGrippers	= 0,
    styleMsTouchSelectNone	= 1,
    styleMsTouchSelectNotSet	= 2,
    styleMsTouchSelect_Max	= 2147483647
    }
.enum styleMsScrollTranslation {
    styleMsScrollTranslationNotSet	= 0,
    styleMsScrollTranslationNone	= 1,
    styleMsScrollTranslationVtoH	= 2,
    styleMsScrollTranslation_Max	= 2147483647
    }
.enum styleBorderImageRepeat {
    styleBorderImageRepeatStretch	= 0,
    styleBorderImageRepeatRepeat	= 1,
    styleBorderImageRepeatRound = 2,
    styleBorderImageRepeatSpace = 3,
    styleBorderImageRepeatNotSet	= 4,
    styleBorderImageRepeat_Max	= 2147483647
    }
.enum styleBorderImageSliceFill {
    styleBorderImageSliceFillNotSet	= 0,
    styleBorderImageSliceFillFill	= 1,
    styleBorderImageSliceFill_Max	= 2147483647
    }
.enum styleMsImeAlign {
    styleMsImeAlignAuto = 0,
    styleMsImeAlignAfter	= 1,
    styleMsImeAlignNotSet	= 2,
    styleMsImeAlign_Max = 2147483647
    }
.enum styleMsTextCombineHorizontal {
    styleMsTextCombineHorizontalNone	= 0,
    styleMsTextCombineHorizontalAll	= 1,
    styleMsTextCombineHorizontalDigits	= 2,
    styleMsTextCombineHorizontalNotSet	= 3,
    styleMsTextCombineHorizontal_Max	= 2147483647
    }
.enum styleViewportSize {
    styleViewportSizeAuto	= 0,
    styleViewportSizeDeviceWidth	= 1,
    styleViewportSizeDeviceHeight	= 2,
    styleViewportSize_Max	= 2147483647
    }
.enum styleUserZoom {
    styleUserZoomNotSet = 0,
    styleUserZoomZoom	= 1,
    styleUserZoomFixed	= 2,
    styleUserZoom_Max	= 2147483647
    }
.enum styleTextLineThroughStyle {
    styleTextLineThroughStyleUndefined	= 0,
    styleTextLineThroughStyleSingle	= 1,
    styleTextLineThroughStyleDouble	= 2,
    styleTextLineThroughStyle_Max	= 2147483647
    }
.enum styleTextUnderlineStyle {
    styleTextUnderlineStyleUndefined	= 0,
    styleTextUnderlineStyleSingle	= 1,
    styleTextUnderlineStyleDouble	= 2,
    styleTextUnderlineStyleWords	= 3,
    styleTextUnderlineStyleDotted	= 4,
    styleTextUnderlineStyleThick	= 5,
    styleTextUnderlineStyleDash = 6,
    styleTextUnderlineStyleDotDash	= 7,
    styleTextUnderlineStyleDotDotDash	= 8,
    styleTextUnderlineStyleWave = 9,
    styleTextUnderlineStyleSingleAccounting	= 10,
    styleTextUnderlineStyleDoubleAccounting	= 11,
    styleTextUnderlineStyleThickDash	= 12,
    styleTextUnderlineStyle_Max = 2147483647
    }
.enum styleTextEffect {
    styleTextEffectNone = 0,
    styleTextEffectEmboss	= 1,
    styleTextEffectEngrave	= 2,
    styleTextEffectOutline	= 3,
    styleTextEffect_Max = 2147483647
    }
.enum styleDefaultTextSelection {
    styleDefaultTextSelectionFalse	= 0,
    styleDefaultTextSelectionTrue	= 1,
    styleDefaultTextSelection_Max	= 2147483647
    }
.enum styleTextDecoration {
    styleTextDecorationNone	= 0,
    styleTextDecorationUnderline	= 1,
    styleTextDecorationOverline = 2,
    styleTextDecorationLineThrough	= 3,
    styleTextDecorationBlink	= 4,
    styleTextDecoration_Max	= 2147483647
    }
.enum textDecoration {
    textDecorationNone	= 0,
    textDecorationUnderline	= 1,
    textDecorationOverline	= 2,
    textDecorationLineThrough	= 3,
    textDecorationBlink = 4,
    textDecoration_Max	= 2147483647
    }
.enum htmlListType {
    htmlListTypeNotSet	= 0,
    htmlListTypeLargeAlpha	= 1,
    htmlListTypeSmallAlpha	= 2,
    htmlListTypeLargeRoman	= 3,
    htmlListTypeSmallRoman	= 4,
    htmlListTypeNumbers = 5,
    htmlListTypeDisc	= 6,
    htmlListTypeCircle	= 7,
    htmlListTypeSquare	= 8,
    htmlListType_Max	= 2147483647
    }
.enum htmlMethod {
    htmlMethodNotSet	= 0,
    htmlMethodGet	= 1,
    htmlMethodPost	= 2,
    htmlMethod_Max	= 2147483647
    }
.enum htmlWrap {
    htmlWrapOff = 1,
    htmlWrapSoft	= 2,
    htmlWrapHard	= 3,
    htmlWrap_Max	= 2147483647
    }
.enum htmlDir {
    htmlDirNotSet	= 0,
    htmlDirLeftToRight	= 1,
    htmlDirRightToLeft	= 2,
    htmlDir_Max = 2147483647
    }
.enum htmlEditable {
    htmlEditableInherit = 0,
    htmlEditableTrue	= 1,
    htmlEditableFalse	= 2,
    htmlEditable_Max	= 2147483647
    }
.enum htmlInput {
    htmlInputNotSet	= 0,
    htmlInputButton	= 1,
    htmlInputCheckbox	= 2,
    htmlInputFile	= 3,
    htmlInputHidden	= 4,
    htmlInputImage	= 5,
    htmlInputPassword	= 6,
    htmlInputRadio	= 7,
    htmlInputReset	= 8,
    htmlInputSelectOne	= 9,
    htmlInputSelectMultiple	= 10,
    htmlInputSubmit	= 11,
    htmlInputText	= 12,
    htmlInputTextarea	= 13,
    htmlInputRichtext	= 14,
    htmlInputRange	= 15,
    htmlInputUrl	= 16,
    htmlInputEmail	= 17,
    htmlInputNumber	= 18,
    htmlInputTel	= 19,
    htmlInputSearch	= 20,
    htmlInput_Max	= 2147483647
    }
.enum htmlSpellCheck {
    htmlSpellCheckNotSet	= 0,
    htmlSpellCheckTrue	= 1,
    htmlSpellCheckFalse = 2,
    htmlSpellCheckDefault	= 3,
    htmlSpellCheck_Max	= 2147483647
    }
.enum htmlEncoding {
    htmlEncodingURL	= 0,
    htmlEncodingMultipart	= 1,
    htmlEncodingText	= 2,
    htmlEncoding_Max	= 2147483647
    }
.enum htmlAdjacency {
    htmlAdjacencyBeforeBegin	= 1,
    htmlAdjacencyAfterBegin	= 2,
    htmlAdjacencyBeforeEnd	= 3,
    htmlAdjacencyAfterEnd	= 4,
    htmlAdjacency_Max	= 2147483647
    }
.enum htmlTabIndex {
    htmlTabIndexNotSet	= -32768,
    htmlTabIndex_Max	= 2147483647
    }
.enum htmlComponent {
    htmlComponentClient = 0,
    htmlComponentSbLeft = 1,
    htmlComponentSbPageLeft	= 2,
    htmlComponentSbHThumb	= 3,
    htmlComponentSbPageRight	= 4,
    htmlComponentSbRight	= 5,
    htmlComponentSbUp	= 6,
    htmlComponentSbPageUp	= 7,
    htmlComponentSbVThumb	= 8,
    htmlComponentSbPageDown	= 9,
    htmlComponentSbDown = 10,
    htmlComponentSbLeft2	= 11,
    htmlComponentSbPageLeft2	= 12,
    htmlComponentSbRight2	= 13,
    htmlComponentSbPageRight2	= 14,
    htmlComponentSbUp2	= 15,
    htmlComponentSbPageUp2	= 16,
    htmlComponentSbDown2	= 17,
    htmlComponentSbPageDown2	= 18,
    htmlComponentSbTop	= 19,
    htmlComponentSbBottom	= 20,
    htmlComponentOutside	= 21,
    htmlComponentGHTopLeft	= 22,
    htmlComponentGHLeft = 23,
    htmlComponentGHTop	= 24,
    htmlComponentGHBottomLeft	= 25,
    htmlComponentGHTopRight	= 26,
    htmlComponentGHBottom	= 27,
    htmlComponentGHRight	= 28,
    htmlComponentGHBottomRight	= 29,
    htmlComponent_Max	= 2147483647
    }
.enum htmlApplyLocation {
    htmlApplyLocationInside	= 0,
    htmlApplyLocationOutside	= 1,
    htmlApplyLocation_Max	= 2147483647
    }
.enum htmlGlyphMode {
    htmlGlyphModeNone	= 0,
    htmlGlyphModeBegin	= 1,
    htmlGlyphModeEnd	= 2,
    htmlGlyphModeBoth	= 3,
    htmlGlyphMode_Max	= 2147483647
    }
.enum htmlDraggable {
    htmlDraggableAuto	= 0,
    htmlDraggableTrue	= 1,
    htmlDraggableFalse	= 2,
    htmlDraggable_Max	= 2147483647
    }
.enum htmlUnit {
    htmlUnitCharacter	= 1,
    htmlUnitWord	= 2,
    htmlUnitSentence	= 3,
    htmlUnitTextEdit	= 6,
    htmlUnit_Max	= 2147483647
    }
.enum htmlEndPoints {
    htmlEndPointsStartToStart	= 1,
    htmlEndPointsStartToEnd	= 2,
    htmlEndPointsEndToStart	= 3,
    htmlEndPointsEndToEnd	= 4,
    htmlEndPoints_Max	= 2147483647
    }
.enum htmlDirection {
    htmlDirectionForward	= 99999,
    htmlDirectionBackward	= -99999,
    htmlDirection_Max	= 2147483647
    }
.enum htmlStart {
    htmlStartfileopen	= 0,
    htmlStartmouseover	= 1,
    htmlStart_Max	= 2147483647
    }
.enum bodyScroll {
    bodyScrollyes	= 1,
    bodyScrollno	= 2,
    bodyScrollauto	= 4,
    bodyScrolldefault	= 3,
    bodyScroll_Max	= 2147483647
    }
.enum htmlSelectType {
    htmlSelectTypeSelectOne	= 1,
    htmlSelectTypeSelectMultiple	= 2,
    htmlSelectType_Max	= 2147483647
    }
.enum htmlSelectExFlag {
    htmlSelectExFlagNone	= 0,
    htmlSelectExFlagHideSelectionInDesign	= 0x1,
    htmlSelectExFlag_Max	= 2147483647
    }
.enum htmlSelection {
    htmlSelectionNone	= 0,
    htmlSelectionText	= 1,
    htmlSelectionControl	= 2,
    htmlSelectionTable	= 3,
    htmlSelection_Max	= 2147483647
    }
.enum htmlMarqueeBehavior {
    htmlMarqueeBehaviorscroll	= 1,
    htmlMarqueeBehaviorslide	= 2,
    htmlMarqueeBehavioralternate	= 3,
    htmlMarqueeBehavior_Max	= 2147483647
    }
.enum htmlMarqueeDirection {
    htmlMarqueeDirectionleft	= 1,
    htmlMarqueeDirectionright	= 3,
    htmlMarqueeDirectionup	= 5,
    htmlMarqueeDirectiondown	= 7,
    htmlMarqueeDirection_Max	= 2147483647
    }
.enum htmlPersistState {
    htmlPersistStateNormal	= 0,
    htmlPersistStateFavorite	= 1,
    htmlPersistStateHistory	= 2,
    htmlPersistStateSnapshot	= 3,
    htmlPersistStateUserData	= 4,
    htmlPersistState_Max	= 2147483647
    }
.enum htmlDropEffect {
    htmlDropEffectCopy	= 0,
    htmlDropEffectLink	= 1,
    htmlDropEffectMove	= 2,
    htmlDropEffectNone	= 3,
    htmlDropEffect_Max	= 2147483647
    }
.enum htmlEffectAllowed {
    htmlEffectAllowedCopy	= 0,
    htmlEffectAllowedLink	= 1,
    htmlEffectAllowedMove	= 2,
    htmlEffectAllowedCopyLink	= 3,
    htmlEffectAllowedCopyMove	= 4,
    htmlEffectAllowedLinkMove	= 5,
    htmlEffectAllowedAll	= 6,
    htmlEffectAllowedNone	= 7,
    htmlEffectAllowedUninitialized	= 8,
    htmlEffectAllowed_Max	= 2147483647
    }
.enum htmlCompatMode {
    htmlCompatModeBackCompat	= 0,
    htmlCompatModeCSS1Compat	= 1,
    htmlCompatMode_Max	= 2147483647
    }
.enum BoolValue {
    True	= 1,
    False	= 0,
    BoolValue_Max	= 2147483647
    }
.enum htmlCaptionAlign {
    htmlCaptionAlignNotSet	= 0,
    htmlCaptionAlignLeft	= 1,
    htmlCaptionAlignCenter	= 2,
    htmlCaptionAlignRight	= 3,
    htmlCaptionAlignJustify	= 4,
    htmlCaptionAlignTop = 5,
    htmlCaptionAlignBottom	= 6,
    htmlCaptionAlign_Max	= 2147483647
    }
.enum htmlCaptionVAlign {
    htmlCaptionVAlignNotSet	= 0,
    htmlCaptionVAlignTop	= 1,
    htmlCaptionVAlignBottom	= 2,
    htmlCaptionVAlign_Max	= 2147483647
    }
.enum htmlFrame {
    htmlFrameNotSet	= 0,
    htmlFramevoid	= 1,
    htmlFrameabove	= 2,
    htmlFramebelow	= 3,
    htmlFramehsides	= 4,
    htmlFramelhs	= 5,
    htmlFramerhs	= 6,
    htmlFramevsides	= 7,
    htmlFramebox	= 8,
    htmlFrameborder	= 9,
    htmlFrame_Max	= 2147483647
    }
.enum htmlRules {
    htmlRulesNotSet	= 0,
    htmlRulesnone	= 1,
    htmlRulesgroups	= 2,
    htmlRulesrows	= 3,
    htmlRulescols	= 4,
    htmlRulesall	= 5,
    htmlRules_Max	= 2147483647
    }
.enum htmlCellAlign {
    htmlCellAlignNotSet = 0,
    htmlCellAlignLeft	= 1,
    htmlCellAlignCenter = 2,
    htmlCellAlignRight	= 3,
    htmlCellAlignMiddle = htmlCellAlignCenter,
    htmlCellAlign_Max	= 2147483647
    }
.enum htmlCellVAlign {
    htmlCellVAlignNotSet	= 0,
    htmlCellVAlignTop	= 1,
    htmlCellVAlignMiddle	= 2,
    htmlCellVAlignBottom	= 3,
    htmlCellVAlignBaseline	= 4,
    htmlCellVAlignCenter	= htmlCellVAlignMiddle,
    htmlCellVAlign_Max	= 2147483647
    }
.enum frameScrolling {
    frameScrollingyes	= 1,
    frameScrollingno	= 2,
    frameScrollingauto	= 4,
    frameScrolling_Max	= 2147483647
    }
.enum sandboxAllow {
    sandboxAllowScripts = 0,
    sandboxAllowSameOrigin	= 1,
    sandboxAllowTopNavigation	= 2,
    sandboxAllowForms	= 3,
    sandboxAllowPopups	= 4,
    sandboxAllow_Max	= 2147483647
    }
.enum svgAngleType {
    SVG_ANGLETYPE_UNKNOWN	= 0,
    SVG_ANGLETYPE_UNSPECIFIED	= 1,
    SVG_ANGLETYPE_DEG	= 2,
    SVG_ANGLETYPE_RAD	= 3,
    SVG_ANGLETYPE_GRAD	= 4,
    svgAngleType_Max	= 2147483647
    }
.enum svgExternalResourcesRequired {
    svgExternalResourcesRequiredFalse	= 0,
    svgExternalResourcesRequiredTrue	= 1,
    svgExternalResourcesRequired_Max	= 2147483647
    }
.enum svgFocusable {
    svgFocusableNotSet	= 0,
    svgFocusableAuto	= 1,
    svgFocusableTrue	= 2,
    svgFocusableFalse	= 3,
    svgFocusable_Max	= 2147483647
    }
.enum svgLengthType {
    SVG_LENGTHTYPE_UNKNOWN	= 0,
    SVG_LENGTHTYPE_NUMBER	= 1,
    SVG_LENGTHTYPE_PERCENTAGE	= 2,
    SVG_LENGTHTYPE_EMS	= 3,
    SVG_LENGTHTYPE_EXS	= 4,
    SVG_LENGTHTYPE_PX	= 5,
    SVG_LENGTHTYPE_CM	= 6,
    SVG_LENGTHTYPE_MM	= 7,
    SVG_LENGTHTYPE_IN	= 8,
    SVG_LENGTHTYPE_PT	= 9,
    SVG_LENGTHTYPE_PC	= 10,
    svgLengthType_Max	= 2147483647
    }
.enum svgPathSegType {
    PATHSEG_UNKNOWN	= 0,
    PATHSEG_CLOSEPATH	= 1,
    PATHSEG_MOVETO_ABS	= 2,
    PATHSEG_MOVETO_REL	= 3,
    PATHSEG_LINETO_ABS	= 4,
    PATHSEG_LINETO_REL	= 5,
    PATHSEG_CURVETO_CUBIC_ABS	= 6,
    PATHSEG_CURVETO_CUBIC_REL	= 7,
    PATHSEG_CURVETO_QUADRATIC_ABS	= 8,
    PATHSEG_CURVETO_QUADRATIC_REL	= 9,
    PATHSEG_ARC_ABS	= 10,
    PATHSEG_ARC_REL	= 11,
    PATHSEG_LINETO_HORIZONTAL_ABS	= 12,
    PATHSEG_LINETO_HORIZONTAL_REL	= 13,
    PATHSEG_LINETO_VERTICAL_ABS = 14,
    PATHSEG_LINETO_VERTICAL_REL = 15,
    PATHSEG_CURVETO_CUBIC_SMOOTH_ABS	= 16,
    PATHSEG_CURVETO_CUBIC_SMOOTH_REL	= 17,
    PATHSEG_CURVETO_QUADRATIC_SMOOTH_ABS	= 18,
    PATHSEG_CURVETO_QUADRATIC_SMOOTH_REL	= 19,
    svgPathSegType_Max	= 2147483647
    }
.enum svgTransformType {
    SVG_TRANSFORM_UNKNOWN	= 0,
    SVG_TRANSFORM_MATRIX	= 1,
    SVG_TRANSFORM_TRANSLATE	= 2,
    SVG_TRANSFORM_SCALE = 3,
    SVG_TRANSFORM_ROTATE	= 4,
    SVG_TRANSFORM_SKEWX = 5,
    SVG_TRANSFORM_SKEWY = 6,
    svgTransformType_Max	= 2147483647
    }
.enum svgPreserveAspectRatioAlignType {
    SVG_PRESERVEASPECTRATIO_UNKNOWN	= 0,
    SVG_PRESERVEASPECTRATIO_NONE	= 1,
    SVG_PRESERVEASPECTRATIO_XMINYMIN	= 2,
    SVG_PRESERVEASPECTRATIO_XMIDYMIN	= 3,
    SVG_PRESERVEASPECTRATIO_XMAXYMIN	= 4,
    SVG_PRESERVEASPECTRATIO_XMINYMID	= 5,
    SVG_PRESERVEASPECTRATIO_XMIDYMID	= 6,
    SVG_PRESERVEASPECTRATIO_XMAXYMID	= 7,
    SVG_PRESERVEASPECTRATIO_XMINYMAX	= 8,
    SVG_PRESERVEASPECTRATIO_XMIDYMAX	= 9,
    SVG_PRESERVEASPECTRATIO_XMAXYMAX	= 10,
    svgPreserveAspectRatioAlignType_Max = 2147483647
    }
.enum svgPreserveAspectMeetOrSliceType {
    SVG_MEETORSLICE_UNKNOWN	= 0,
    SVG_MEETORSLICE_MEET	= 1,
    SVG_MEETORSLICE_SLICE	= 2,
    svgPreserveAspectMeetOrSliceType_Max	= 2147483647
    }
.enum svgUnitTypes {
    SVG_UNITTYPE_UNKNOWN	= 0,
    SVG_UNITTYPE_USERSPACEONUSE = 1,
    SVG_UNITTYPE_OBJECTBOUNDINGBOX	= 2,
    svgUnitTypes_Max	= 2147483647
    }
.enum svgSpreadMethod {
    SVG_SPREADMETHOD_UNKNOWN	= 0,
    SVG_SPREADMETHOD_PAD	= 1,
    SVG_SPREADMETHOD_REFLECT	= 2,
    SVG_SPREADMETHOD_REPEAT	= 3,
    svgSpreadMethod_Max = 2147483647
    }
.enum svgFeblendMode {
    SVG_FEBLEND_MODE_UNKNOWN	= 0,
    SVG_FEBLEND_MODE_NORMAL	= 1,
    SVG_FEBLEND_MODE_MULTIPLY	= 2,
    SVG_FEBLEND_MODE_SCREEN	= 3,
    SVG_FEBLEND_MODE_DARKEN	= 4,
    SVG_FEBLEND_MODE_LIGHTEN	= 5,
    svgFeblendMode_Max	= 2147483647
    }
.enum svgFecolormatrixType {
    SVG_FECOLORMATRIX_TYPE_UNKNOWN	= 0,
    SVG_FECOLORMATRIX_TYPE_MATRIX	= 1,
    SVG_FECOLORMATRIX_TYPE_SATURATE	= 2,
    SVG_FECOLORMATRIX_TYPE_HUEROTATE	= 3,
    SVG_FECOLORMATRIX_TYPE_LUMINANCETOALPHA	= 4,
    svgFecolormatrixType_Max	= 2147483647
    }
.enum svgFecomponenttransferType {
    SVG_FECOMPONENTTRANSFER_TYPE_UNKNOWN	= 0,
    SVG_FECOMPONENTTRANSFER_TYPE_IDENTITY	= 1,
    SVG_FECOMPONENTTRANSFER_TYPE_TABLE	= 2,
    SVG_FECOMPONENTTRANSFER_TYPE_DISCRETE	= 3,
    SVG_FECOMPONENTTRANSFER_TYPE_LINEAR = 4,
    SVG_FECOMPONENTTRANSFER_TYPE_GAMMA	= 5,
    svgFecomponenttransferType_Max	= 2147483647
    }
.enum svgFecompositeOperator {
    SVG_FECOMPOSITE_OPERATOR_UNKNOWN	= 0,
    SVG_FECOMPOSITE_OPERATOR_OVER	= 1,
    SVG_FECOMPOSITE_OPERATOR_IN = 2,
    SVG_FECOMPOSITE_OPERATOR_OUT	= 3,
    SVG_FECOMPOSITE_OPERATOR_ATOP	= 4,
    SVG_FECOMPOSITE_OPERATOR_XOR	= 5,
    SVG_FECOMPOSITE_OPERATOR_ARITHMETIC = 6,
    svgFecompositeOperator_Max	= 2147483647
    }
.enum svgEdgemode {
    SVG_EDGEMODE_UNKNOWN	= 0,
    SVG_EDGEMODE_DUPLICATE	= 1,
    SVG_EDGEMODE_WRAP	= 2,
    SVG_EDGEMODE_NONE	= 3,
    svgEdgemode_Max	= 2147483647
    }
.enum svgPreserveAlpha {
    SVG_PRESERVEALPHA_FALSE	= 0,
    SVG_PRESERVEALPHA_TRUE	= 1,
    svgPreserveAlpha_Max	= 2147483647
    }
.enum svgChannel {
    SVG_CHANNEL_UNKNOWN = 0,
    SVG_CHANNEL_R	= 1,
    SVG_CHANNEL_G	= 2,
    SVG_CHANNEL_B	= 3,
    SVG_CHANNEL_A	= 4,
    svgChannel_Max	= 2147483647
    }
.enum svgMorphologyOperator {
    SVG_MORPHOLOGY_OPERATOR_UNKNOWN	= 0,
    SVG_MORPHOLOGY_OPERATOR_ERODE	= 1,
    SVG_MORPHOLOGY_OPERATOR_DILATE	= 2,
    svgMorphologyOperator_Max	= 2147483647
    }
.enum svgTurbulenceType {
    SVG_TURBULENCE_TYPE_UNKNOWN = 0,
    SVG_TURBULENCE_TYPE_FACTALNOISE	= 1,
    SVG_TURBULENCE_TYPE_TURBULENCE	= 2,
    svgTurbulenceType_Max	= 2147483647
    }
.enum svgStitchtype {
    SVG_STITCHTYPE_UNKNOWN	= 0,
    SVG_STITCHTYPE_STITCH	= 1,
    SVG_STITCHTYPE_NOSTITCH	= 2,
    svgStitchtype_Max	= 2147483647
    }
.enum svgMarkerUnits {
    SVG_MARKERUNITS_UNKNOWN	= 0,
    SVG_MARKERUNITS_USERSPACEONUSE	= 1,
    SVG_MARKERUNITS_STROKEWIDTH = 2,
    svgMarkerUnits_Max	= 2147483647
    }
.enum svgMarkerOrient {
    SVG_MARKER_ORIENT_UNKNOWN	= 0,
    SVG_MARKER_ORIENT_AUTO	= 1,
    SVG_MARKER_ORIENT_ANGLE	= 2,
    svgMarkerOrient_Max = 2147483647
    }
.enum svgMarkerOrientAttribute {
    svgMarkerOrientAttributeAuto	= 0,
    svgMarkerOrientAttribute_Max	= 2147483647
    }
.enum htmlMediaNetworkState {
    htmlMediaNetworkStateEmpty	= 0,
    htmlMediaNetworkStateIdle	= 1,
    htmlMediaNetworkStateLoading	= 2,
    htmlMediaNetworkStateNoSource	= 3,
    htmlMediaNetworkState_Max	= 2147483647
    }
.enum htmlMediaReadyState {
    htmlMediaReadyStateHaveNothing	= 0,
    htmlMediaReadyStateHaveMetadata	= 1,
    htmlMediaReadyStateHaveCurrentData	= 2,
    htmlMediaReadyStateHaveFutureData	= 3,
    htmlMediaReadyStateHaveEnoughData	= 4,
    htmlMediaReadyState_Max	= 2147483647
    }
.enum htmlMediaErr {
    htmlMediaErrAborted = 0,
    htmlMediaErrNetwork = 1,
    htmlMediaErrDecode	= 2,
    htmlMediaErrSrcNotSupported = 3,
    htmlMediaErr_Max	= 2147483647
    }
.enum lengthAdjust {
    LENGTHADJUST_UNKNOWN	= 0,
    LENGTHADJUST_SPACING	= 1,
    LENGTHADJUST_SPACINGANDGLYPHS	= 2,
    lengthAdjust_Max	= 2147483647
    }
.enum textpathMethodtype {
    TEXTPATH_METHODTYPE_UNKNOWN = 0,
    TEXTPATH_METHODTYPE_ALIGN	= 1,
    TEXTPATH_METHODTYPE_STRETCH = 2,
    textpathMethodtype_Max	= 2147483647
    }
.enum textpathSpacingtype {
    TEXTPATH_SPACINGTYPE_UNKNOWN	= 0,
    TEXTPATH_SPACINGTYPE_AUTO	= 1,
    TEXTPATH_SPACINGTYPE_EXACT	= 2,
    textpathSpacingtype_Max	= 2147483647
    }
.enum ELEMENT_CORNER {
    ELEMENT_CORNER_NONE = 0,
    ELEMENT_CORNER_TOP	= 1,
    ELEMENT_CORNER_LEFT = 2,
    ELEMENT_CORNER_BOTTOM	= 3,
    ELEMENT_CORNER_RIGHT	= 4,
    ELEMENT_CORNER_TOPLEFT	= 5,
    ELEMENT_CORNER_TOPRIGHT	= 6,
    ELEMENT_CORNER_BOTTOMLEFT	= 7,
    ELEMENT_CORNER_BOTTOMRIGHT	= 8,
    ELEMENT_CORNER_Max	= 2147483647
    }
.enum SECUREURLHOSTVALIDATE_FLAGS {
    SUHV_PROMPTBEFORENO = 0x1,
    SUHV_SILENTYES	= 0x2,
    SUHV_UNSECURESOURCE = 0x4,
    SECUREURLHOSTVALIDATE_FLAGS_Max	= 2147483647
    }
.enum POINTER_GRAVITY {
    POINTER_GRAVITY_Left	= 0,
    POINTER_GRAVITY_Right	= 1,
    POINTER_GRAVITY_Max = 2147483647
    }
.enum ELEMENT_ADJACENCY {
    ELEM_ADJ_BeforeBegin	= 0,
    ELEM_ADJ_AfterBegin = 1,
    ELEM_ADJ_BeforeEnd	= 2,
    ELEM_ADJ_AfterEnd	= 3,
    ELEMENT_ADJACENCY_Max	= 2147483647
    }
.enum MARKUP_CONTEXT_TYPE {
    CONTEXT_TYPE_None	= 0,
    CONTEXT_TYPE_Text	= 1,
    CONTEXT_TYPE_EnterScope	= 2,
    CONTEXT_TYPE_ExitScope	= 3,
    CONTEXT_TYPE_NoScope	= 4,
    MARKUP_CONTEXT_TYPE_Max	= 2147483647
    }
.enum FINDTEXT_FLAGS {
    FINDTEXT_BACKWARDS	= 0x1,
    FINDTEXT_WHOLEWORD	= 0x2,
    FINDTEXT_MATCHCASE	= 0x4,
    FINDTEXT_RAW	= 0x20000,
    FINDTEXT_MATCHREPEATEDWHITESPACE	= 0x40000,
    FINDTEXT_MATCHDIAC	= 0x20000000,
    FINDTEXT_MATCHKASHIDA	= 0x40000000,
    FINDTEXT_MATCHALEFHAMZA	= 0x80000000,
    FINDTEXT_FLAGS_Max	= 2147483647
    }
.enum MOVEUNIT_ACTION {
    MOVEUNIT_PREVCHAR	= 0,
    MOVEUNIT_NEXTCHAR	= 1,
    MOVEUNIT_PREVCLUSTERBEGIN	= 2,
    MOVEUNIT_NEXTCLUSTERBEGIN	= 3,
    MOVEUNIT_PREVCLUSTEREND	= 4,
    MOVEUNIT_NEXTCLUSTEREND	= 5,
    MOVEUNIT_PREVWORDBEGIN	= 6,
    MOVEUNIT_NEXTWORDBEGIN	= 7,
    MOVEUNIT_PREVWORDEND	= 8,
    MOVEUNIT_NEXTWORDEND	= 9,
    MOVEUNIT_PREVPROOFWORD	= 10,
    MOVEUNIT_NEXTPROOFWORD	= 11,
    MOVEUNIT_NEXTURLBEGIN	= 12,
    MOVEUNIT_PREVURLBEGIN	= 13,
    MOVEUNIT_NEXTURLEND = 14,
    MOVEUNIT_PREVURLEND = 15,
    MOVEUNIT_PREVSENTENCE	= 16,
    MOVEUNIT_NEXTSENTENCE	= 17,
    MOVEUNIT_PREVBLOCK	= 18,
    MOVEUNIT_NEXTBLOCK	= 19,
    MOVEUNIT_ACTION_Max = 2147483647
    }
.enum PARSE_FLAGS {
    PARSE_ABSOLUTIFYIE40URLS	= 0x1,
    PARSE_DISABLEVML	= 0x2,
    PARSE_FLAGS_Max	= 2147483647
    }
.enum ELEMENT_TAG_ID {
    TAGID_NULL	= 0,
    TAGID_UNKNOWN	= 1,
    TAGID_A	= 2,
    TAGID_ACRONYM	= 3,
    TAGID_ADDRESS	= 4,
    TAGID_APPLET	= 5,
    TAGID_AREA	= 6,
    TAGID_B	= 7,
    TAGID_BASE	= 8,
    TAGID_BASEFONT	= 9,
    TAGID_BDO	= 10,
    TAGID_BGSOUND	= 11,
    TAGID_BIG	= 12,
    TAGID_BLINK = 13,
    TAGID_BLOCKQUOTE	= 14,
    TAGID_BODY	= 15,
    TAGID_BR	= 16,
    TAGID_BUTTON	= 17,
    TAGID_CAPTION	= 18,
    TAGID_CENTER	= 19,
    TAGID_CITE	= 20,
    TAGID_CODE	= 21,
    TAGID_COL	= 22,
    TAGID_COLGROUP	= 23,
    TAGID_COMMENT	= 24,
    TAGID_COMMENT_RAW	= 25,
    TAGID_DD	= 26,
    TAGID_DEL	= 27,
    TAGID_DFN	= 28,
    TAGID_DIR	= 29,
    TAGID_DIV	= 30,
    TAGID_DL	= 31,
    TAGID_DT	= 32,
    TAGID_EM	= 33,
    TAGID_EMBED = 34,
    TAGID_FIELDSET	= 35,
    TAGID_FONT	= 36,
    TAGID_FORM	= 37,
    TAGID_FRAME = 38,
    TAGID_FRAMESET	= 39,
    TAGID_GENERIC	= 40,
    TAGID_H1	= 41,
    TAGID_H2	= 42,
    TAGID_H3	= 43,
    TAGID_H4	= 44,
    TAGID_H5	= 45,
    TAGID_H6	= 46,
    TAGID_HEAD	= 47,
    TAGID_HR	= 48,
    TAGID_HTML	= 49,
    TAGID_I	= 50,
    TAGID_IFRAME	= 51,
    TAGID_IMG	= 52,
    TAGID_INPUT = 53,
    TAGID_INS	= 54,
    TAGID_KBD	= 55,
    TAGID_LABEL = 56,
    TAGID_LEGEND	= 57,
    TAGID_LI	= 58,
    TAGID_LINK	= 59,
    TAGID_LISTING	= 60,
    TAGID_MAP	= 61,
    TAGID_MARQUEE	= 62,
    TAGID_MENU	= 63,
    TAGID_META	= 64,
    TAGID_NEXTID	= 65,
    TAGID_NOBR	= 66,
    TAGID_NOEMBED	= 67,
    TAGID_NOFRAMES	= 68,
    TAGID_NOSCRIPT	= 69,
    TAGID_OBJECT	= 70,
    TAGID_OL	= 71,
    TAGID_OPTION	= 72,
    TAGID_P	= 73,
    TAGID_PARAM = 74,
    TAGID_PLAINTEXT	= 75,
    TAGID_PRE	= 76,
    TAGID_Q	= 77,
    TAGID_RP	= 78,
    TAGID_RT	= 79,
    TAGID_RUBY	= 80,
    TAGID_S	= 81,
    TAGID_SAMP	= 82,
    TAGID_SCRIPT	= 83,
    TAGID_SELECT	= 84,
    TAGID_SMALL = 85,
    TAGID_SPAN	= 86,
    TAGID_STRIKE	= 87,
    TAGID_STRONG	= 88,
    TAGID_STYLE = 89,
    TAGID_SUB	= 90,
    TAGID_SUP	= 91,
    TAGID_TABLE = 92,
    TAGID_TBODY = 93,
    TAGID_TC	= 94,
    TAGID_TD	= 95,
    TAGID_TEXTAREA	= 96,
    TAGID_TFOOT = 97,
    TAGID_TH	= 98,
    TAGID_THEAD = 99,
    TAGID_TITLE = 100,
    TAGID_TR	= 101,
    TAGID_TT	= 102,
    TAGID_U	= 103,
    TAGID_UL	= 104,
    TAGID_VAR	= 105,
    TAGID_WBR	= 106,
    TAGID_XMP	= 107,
    TAGID_ROOT	= 108,
    TAGID_OPTGROUP	= 109,
    TAGID_ABBR	= 110,
    TAGID_SVG_A = 111,
    TAGID_SVG_ALTGLYPH	= 112,
    TAGID_SVG_ALTGLYPHDEF	= 113,
    TAGID_SVG_ALTGLYPHITEM	= 114,
    TAGID_SVG_ANIMATE	= 115,
    TAGID_SVG_ANIMATECOLOR	= 116,
    TAGID_SVG_ANIMATEMOTION	= 117,
    TAGID_SVG_ANIMATETRANSFORM	= 118,
    TAGID_SVG_CIRCLE	= 119,
    TAGID_SVG_CLIPPATH	= 120,
    TAGID_SVG_COLOR_PROFILE	= 121,
    TAGID_SVG_CURSOR	= 122,
    TAGID_SVG_DEFINITION_SRC	= 123,
    TAGID_SVG_DEFS	= 124,
    TAGID_SVG_DESC	= 125,
    TAGID_SVG_ELLIPSE	= 126,
    TAGID_SVG_FEBLEND	= 127,
    TAGID_SVG_FECOLORMATRIX	= 128,
    TAGID_SVG_FECOMPONENTTRANSFER	= 129,
    TAGID_SVG_FECOMPOSITE	= 130,
    TAGID_SVG_FECONVOLVEMATRIX	= 131,
    TAGID_SVG_FEDIFFUSELIGHTING = 132,
    TAGID_SVG_FEDISPLACEMENTMAP = 133,
    TAGID_SVG_FEDISTANTLIGHT	= 134,
    TAGID_SVG_FEFLOOD	= 135,
    TAGID_SVG_FEFUNCA	= 136,
    TAGID_SVG_FEFUNCB	= 137,
    TAGID_SVG_FEFUNCG	= 138,
    TAGID_SVG_FEFUNCR	= 139,
    TAGID_SVG_FEGAUSSIANBLUR	= 140,
    TAGID_SVG_FEIMAGE	= 141,
    TAGID_SVG_FEMERGE	= 142,
    TAGID_SVG_FEMERGENODE	= 143,
    TAGID_SVG_FEMORPHOLOGY	= 144,
    TAGID_SVG_FEOFFSET	= 145,
    TAGID_SVG_FEPOINTLIGHT	= 146,
    TAGID_SVG_FESPECULARLIGHTING	= 147,
    TAGID_SVG_FESPOTLIGHT	= 148,
    TAGID_SVG_FETILE	= 149,
    TAGID_SVG_FETURBULENCE	= 150,
    TAGID_SVG_FILTER	= 151,
    TAGID_SVG_FONT	= 152,
    TAGID_SVG_FONT_FACE = 153,
    TAGID_SVG_FONT_FACE_FORMAT	= 154,
    TAGID_SVG_FONT_FACE_NAME	= 155,
    TAGID_SVG_FONT_FACE_SRC	= 156,
    TAGID_SVG_FONT_FACE_URI	= 157,
    TAGID_SVG_FOREIGNOBJECT	= 158,
    TAGID_SVG_G = 159,
    TAGID_SVG_GLYPH	= 160,
    TAGID_SVG_GLYPHREF	= 161,
    TAGID_SVG_HKERN	= 162,
    TAGID_SVG_IMAGE	= 163,
    TAGID_SVG_LINE	= 164,
    TAGID_SVG_LINEARGRADIENT	= 165,
    TAGID_SVG_MARKER	= 166,
    TAGID_SVG_MASK	= 167,
    TAGID_SVG_METADATA	= 168,
    TAGID_SVG_MISSING_GLYPH	= 169,
    TAGID_SVG_MPATH	= 170,
    TAGID_SVG_PATH	= 171,
    TAGID_SVG_PATTERN	= 172,
    TAGID_SVG_POLYGON	= 173,
    TAGID_SVG_POLYLINE	= 174,
    TAGID_SVG_RADIALGRADIENT	= 175,
    TAGID_SVG_RECT	= 176,
    TAGID_SVG_SCRIPT	= 177,
    TAGID_SVG_SET	= 178,
    TAGID_SVG_STOP	= 179,
    TAGID_SVG_STYLE	= 180,
    TAGID_SVG_SVG	= 181,
    TAGID_SVG_SWITCH	= 182,
    TAGID_SVG_SYMBOL	= 183,
    TAGID_SVG_TEXT	= 184,
    TAGID_SVG_TEXTPATH	= 185,
    TAGID_SVG_TITLE	= 186,
    TAGID_SVG_TREF	= 187,
    TAGID_SVG_TSPAN	= 188,
    TAGID_SVG_USE	= 189,
    TAGID_SVG_VIEW	= 190,
    TAGID_SVG_VKERN	= 191,
    TAGID_AUDIO = 192,
    TAGID_SOURCE	= 193,
    TAGID_VIDEO = 194,
    TAGID_CANVAS	= 195,
    TAGID_DOCTYPE	= 196,
    TAGID_KEYGEN	= 197,
    TAGID_PROCESSINGINSTRUCTION = 198,
    TAGID_ARTICLE	= 199,
    TAGID_ASIDE = 200,
    TAGID_FIGCAPTION	= 201,
    TAGID_FIGURE	= 202,
    TAGID_FOOTER	= 203,
    TAGID_HEADER	= 204,
    TAGID_HGROUP	= 205,
    TAGID_MARK	= 206,
    TAGID_NAV	= 207,
    TAGID_SECTION	= 208,
    TAGID_PROGRESS	= 209,
    TAGID_MATHML_ANNOTATION_XML = 210,
    TAGID_MATHML_MATH	= 211,
    TAGID_MATHML_MI	= 212,
    TAGID_MATHML_MN	= 213,
    TAGID_MATHML_MO	= 214,
    TAGID_MATHML_MS	= 215,
    TAGID_MATHML_MTEXT	= 216,
    TAGID_DATALIST	= 217,
    TAGID_TRACK = 218,
    TAGID_ISINDEX	= 219,
    TAGID_COMMAND	= 220,
    TAGID_DETAILS	= 221,
    TAGID_SUMMARY	= 222,
    TAGID_X_MS_WEBVIEW	= 223,
    TAGID_COUNT = 224,
    TAGID_LAST_PREDEFINED	= 10000,
    ELEMENT_TAG_ID_Max	= 2147483647
    }
.enum SELECTION_TYPE {
    SELECTION_TYPE_None = 0,
    SELECTION_TYPE_Caret	= 1,
    SELECTION_TYPE_Text = 2,
    SELECTION_TYPE_Control	= 3,
    SELECTION_TYPE_Max	= 2147483647
    }
.enum SAVE_SEGMENTS_FLAGS {
    SAVE_SEGMENTS_NoIE4SelectionCompat	= 0x1,
    SAVE_SEGMENTS_FLAGS_Max	= 2147483647
    }
.enum CARET_DIRECTION {
    CARET_DIRECTION_INDETERMINATE	= 0,
    CARET_DIRECTION_SAME	= 1,
    CARET_DIRECTION_BACKWARD	= 2,
    CARET_DIRECTION_FORWARD	= 3,
    CARET_DIRECTION_Max = 2147483647
    }
.enum LINE_DIRECTION {
    LINE_DIRECTION_RightToLeft	= 1,
    LINE_DIRECTION_LeftToRight	= 2,
    LINE_DIRECTION_Max	= 2147483647
    }
.enum HT_OPTIONS {
    HT_OPT_AllowAfterEOL	= 0x1,
    HT_OPTIONS_Max	= 2147483647
    }
.enum HT_RESULTS {
    HT_RESULTS_Glyph	= 0x1,
    HT_RESULTS_Max	= 2147483647
    }
.enum DISPLAY_MOVEUNIT {
    DISPLAY_MOVEUNIT_PreviousLine	= 1,
    DISPLAY_MOVEUNIT_NextLine	= 2,
    DISPLAY_MOVEUNIT_CurrentLineStart	= 3,
    DISPLAY_MOVEUNIT_CurrentLineEnd	= 4,
    DISPLAY_MOVEUNIT_TopOfWindow	= 5,
    DISPLAY_MOVEUNIT_BottomOfWindow	= 6,
    DISPLAY_MOVEUNIT_Max	= 2147483647
    }
.enum DISPLAY_GRAVITY {
    DISPLAY_GRAVITY_PreviousLine	= 1,
    DISPLAY_GRAVITY_NextLine	= 2,
    DISPLAY_GRAVITY_Max = 2147483647
    }
.enum DISPLAY_BREAK {
    DISPLAY_BREAK_None	= 0,
    DISPLAY_BREAK_Block = 0x1,
    DISPLAY_BREAK_Break = 0x2,
    DISPLAY_BREAK_Max	= 2147483647
    }
.enum COORD_SYSTEM {
    COORD_SYSTEM_GLOBAL = 0,
    COORD_SYSTEM_PARENT = 1,
    COORD_SYSTEM_CONTAINER	= 2,
    COORD_SYSTEM_CONTENT	= 3,
    COORD_SYSTEM_FRAME	= 4,
    COORD_SYSTEM_CLIENT = 5,
    COORD_SYSTEM_Max	= 2147483647
    }
.enum DEV_CONSOLE_MESSAGE_LEVEL {
    DCML_INFORMATIONAL	= 0,
    DCML_WARNING	= 0x1,
    DCML_ERROR	= 0x2,
    DEV_CONSOLE_MESSAGE_LEVEL_Max	= 2147483647
    }
.enum DOM_EVENT_PHASE {
    DEP_CAPTURING_PHASE = 0x1,
    DEP_AT_TARGET	= 0x2,
    DEP_BUBBLING_PHASE	= 0x3,
    DOM_EVENT_PHASE_Max = 2147483647
    }
.enum SCRIPT_TIMER_TYPE {
    STT_TIMEOUT = 0,
    STT_INTERVAL	= 0x1,
    STT_IMMEDIATE	= 0x2,
    STT_ANIMATION_FRAME = 0x3,
    SCRIPT_TIMER_TYPE_Max	= 2147483647
    }
.enum HTML_PAINTER {
    HTMLPAINTER_OPAQUE	= 0x1,
    HTMLPAINTER_TRANSPARENT	= 0x2,
    HTMLPAINTER_ALPHA	= 0x4,
    HTMLPAINTER_COMPLEX = 0x8,
    HTMLPAINTER_OVERLAY = 0x10,
    HTMLPAINTER_HITTEST = 0x20,
    HTMLPAINTER_SURFACE = 0x100,
    HTMLPAINTER_3DSURFACE	= 0x200,
    HTMLPAINTER_NOBAND	= 0x400,
    HTMLPAINTER_NODC	= 0x1000,
    HTMLPAINTER_NOPHYSICALCLIP	= 0x2000,
    HTMLPAINTER_NOSAVEDC	= 0x4000,
    HTMLPAINTER_SUPPORTS_XFORM	= 0x8000,
    HTMLPAINTER_EXPAND	= 0x10000,
    HTMLPAINTER_NOSCROLLBITS	= 0x20000,
    HTML_PAINTER_Max	= 2147483647
    }
.enum HTML_PAINT_ZORDER {
    HTMLPAINT_ZORDER_NONE	= 0,
    HTMLPAINT_ZORDER_REPLACE_ALL	= 1,
    HTMLPAINT_ZORDER_REPLACE_CONTENT	= 2,
    HTMLPAINT_ZORDER_REPLACE_BACKGROUND = 3,
    HTMLPAINT_ZORDER_BELOW_CONTENT	= 4,
    HTMLPAINT_ZORDER_BELOW_FLOW = 5,
    HTMLPAINT_ZORDER_ABOVE_FLOW = 6,
    HTMLPAINT_ZORDER_ABOVE_CONTENT	= 7,
    HTMLPAINT_ZORDER_WINDOW_TOP = 8,
    HTML_PAINT_ZORDER_Max	= 2147483647
    }
.enum HTML_PAINT_DRAW_FLAGS {
    HTMLPAINT_DRAW_UPDATEREGION = 0x1,
    HTMLPAINT_DRAW_USE_XFORM	= 0x2,
    HTML_PAINT_DRAW_FLAGS_Max	= 2147483647
    }
.enum HTML_PAINT_EVENT_FLAGS {
    HTMLPAINT_EVENT_TARGET	= 0x1,
    HTMLPAINT_EVENT_SETCURSOR	= 0x2,
    HTML_PAINT_EVENT_FLAGS_Max	= 2147483647
    }
.enum HTML_PAINT_DRAW_INFO_FLAGS {
    HTMLPAINT_DRAWINFO_VIEWPORT = 0x1,
    HTMLPAINT_DRAWINFO_UPDATEREGION	= 0x2,
    HTMLPAINT_DRAWINFO_XFORM	= 0x4,
    HTML_PAINT_DRAW_INFO_FLAGS_Max	= 2147483647
    }
HTML_PAINTER_INFO	STRUC
lFlags			LONG ?
lZOrder			LONG ?
iidDrawObject		IID <>
rcExpand		RECT <>
HTML_PAINTER_INFO	ENDS
HTML_PAINT_XFORM	STRUC
eM11			FLOAT ?
eM12			FLOAT ?
eM21			FLOAT ?
eM22			FLOAT ?
_eDx			FLOAT ?
eDy			FLOAT ?
HTML_PAINT_XFORM	ENDS
HTML_PAINT_DRAW_INFO	STRUC
rcViewport		RECT <>
hrgnUpdate		HRGN ?
xform			HTML_PAINT_XFORM <>
HTML_PAINT_DRAW_INFO	ENDS
.enum HTMLDlgFlag {
    HTMLDlgFlagNo	= 0,
    HTMLDlgFlagOff	= 0,
    HTMLDlgFlag0	= 0,
    HTMLDlgFlagYes	= 1,
    HTMLDlgFlagOn	= 1,
    HTMLDlgFlag1	= 1,
    HTMLDlgFlagNotSet	= -1,
    HTMLDlgFlag_Max	= 2147483647
    }
.enum HTMLDlgBorder {
    HTMLDlgBorderThin	= 0,
    HTMLDlgBorderThick	= 0x40000,
    HTMLDlgBorder_Max	= 2147483647
    }
.enum HTMLDlgEdge {
    HTMLDlgEdgeSunken	= 0,
    HTMLDlgEdgeRaised	= 16,
    HTMLDlgEdge_Max	= 2147483647
    }
.enum HTMLDlgCenter {
    HTMLDlgCenterNo	= 0,
    HTMLDlgCenterOff	= 0,
    HTMLDlgCenter0	= 0,
    HTMLDlgCenterYes	= 1,
    HTMLDlgCenterOn	= 1,
    HTMLDlgCenter1	= 1,
    HTMLDlgCenterParent = 1,
    HTMLDlgCenterDesktop	= 2,
    HTMLDlgCenter_Max	= 2147483647
    }
.enum HTMLAppFlag {
    HTMLAppFlagNo	= 0,
    HTMLAppFlagOff	= 0,
    HTMLAppFlag0	= 0,
    HTMLAppFlagYes	= 1,
    HTMLAppFlagOn	= 1,
    HTMLAppFlag1	= 1,
    HTMLAppFlag_Max	= 2147483647
    }
.enum HTMLMinimizeFlag {
    HTMLMinimizeFlagNo	= 0,
    HTMLMinimizeFlagYes = 0x20000,
    HTMLMinimizeFlag_Max	= 2147483647
    }
.enum HTMLMaximizeFlag {
    HTMLMaximizeFlagNo	= 0,
    HTMLMaximizeFlagYes = 0x10000,
    HTMLMaximizeFlag_Max	= 2147483647
    }
.enum HTMLCaptionFlag {
    HTMLCaptionFlagNo	= 0,
    HTMLCaptionFlagYes	= 0xc00000,
    HTMLCaptionFlag_Max = 2147483647
    }
.enum HTMLSysMenuFlag {
    HTMLSysMenuFlagNo	= 0,
    HTMLSysMenuFlagYes	= 0x80000,
    HTMLSysMenuFlag_Max = 2147483647
    }
.enum HTMLBorder {
    HTMLBorderNone	= 0,
    HTMLBorderThick	= 0x40000,
    HTMLBorderDialog	= 0x400000,
    HTMLBorderThin	= 0x800000,
    HTMLBorder_Max	= 2147483647
    }
.enum HTMLBorderStyle {
    HTMLBorderStyleNormal	= 0,
    HTMLBorderStyleRaised	= 0x100,
    HTMLBorderStyleSunken	= 0x200,
    HTMLBorderStylecombined	= 0x300,
    HTMLBorderStyleStatic	= 0x20000,
    HTMLBorderStyle_Max = 2147483647
    }
.enum HTMLWindowState {
    HTMLWindowStateNormal	= 1,
    HTMLWindowStateMaximize	= 3,
    HTMLWindowStateMinimize	= 6,
    HTMLWindowState_Max = 2147483647
    }
.enum BEHAVIOR_EVENT {
    BEHAVIOREVENT_FIRST = 0,
    BEHAVIOREVENT_CONTENTREADY	= 0,
    BEHAVIOREVENT_DOCUMENTREADY = 1,
    BEHAVIOREVENT_APPLYSTYLE	= 2,
    BEHAVIOREVENT_DOCUMENTCONTEXTCHANGE = 3,
    BEHAVIOREVENT_CONTENTSAVE	= 4,
    BEHAVIOREVENT_LAST	= 4,
    BEHAVIOR_EVENT_Max	= 2147483647
    }
.enum BEHAVIOR_EVENT_FLAGS {
    BEHAVIOREVENTFLAGS_BUBBLE	= 1,
    BEHAVIOREVENTFLAGS_STANDARDADDITIVE = 2,
    BEHAVIOR_EVENT_FLAGS_Max	= 2147483647
    }
.enum BEHAVIOR_RENDER_INFO {
    BEHAVIORRENDERINFO_BEFOREBACKGROUND = 0x1,
    BEHAVIORRENDERINFO_AFTERBACKGROUND	= 0x2,
    BEHAVIORRENDERINFO_BEFORECONTENT	= 0x4,
    BEHAVIORRENDERINFO_AFTERCONTENT	= 0x8,
    BEHAVIORRENDERINFO_AFTERFOREGROUND	= 0x20,
    BEHAVIORRENDERINFO_ABOVECONTENT	= 0x28,
    BEHAVIORRENDERINFO_ALLLAYERS	= 0xff,
    BEHAVIORRENDERINFO_DISABLEBACKGROUND	= 0x100,
    BEHAVIORRENDERINFO_DISABLENEGATIVEZ = 0x200,
    BEHAVIORRENDERINFO_DISABLECONTENT	= 0x400,
    BEHAVIORRENDERINFO_DISABLEPOSITIVEZ = 0x800,
    BEHAVIORRENDERINFO_DISABLEALLLAYERS = 0xf00,
    BEHAVIORRENDERINFO_HITTESTING	= 0x1000,
    BEHAVIORRENDERINFO_SURFACE	= 0x100000,
    BEHAVIORRENDERINFO_3DSURFACE	= 0x200000,
    BEHAVIOR_RENDER_INFO_Max	= 2147483647
    }
.enum BEHAVIOR_RELATION {
    BEHAVIOR_FIRSTRELATION	= 0,
    BEHAVIOR_SAMEELEMENT	= 0,
    BEHAVIOR_PARENT	= 1,
    BEHAVIOR_CHILD	= 2,
    BEHAVIOR_SIBLING	= 3,
    BEHAVIOR_LASTRELATION	= 3,
    BEHAVIOR_RELATION_Max	= 2147483647
    }
.enum BEHAVIOR_LAYOUT_INFO {
    BEHAVIORLAYOUTINFO_FULLDELEGATION	= 0x1,
    BEHAVIORLAYOUTINFO_MODIFYNATURAL	= 0x2,
    BEHAVIORLAYOUTINFO_MAPSIZE	= 0x4,
    BEHAVIOR_LAYOUT_INFO_Max	= 2147483647
    }
.enum BEHAVIOR_LAYOUT_MODE {
    BEHAVIORLAYOUTMODE_NATURAL	= 0x1,
    BEHAVIORLAYOUTMODE_MINWIDTH = 0x2,
    BEHAVIORLAYOUTMODE_MAXWIDTH = 0x4,
    BEHAVIORLAYOUTMODE_MEDIA_RESOLUTION = 0x4000,
    BEHAVIORLAYOUTMODE_FINAL_PERCENT	= 0x8000,
    BEHAVIOR_LAYOUT_MODE_Max	= 2147483647
    }
.enum ELEMENTDESCRIPTOR_FLAGS {
    ELEMENTDESCRIPTORFLAGS_LITERAL	= 1,
    ELEMENTDESCRIPTORFLAGS_NESTED_LITERAL	= 2,
    ELEMENTDESCRIPTOR_FLAGS_Max = 2147483647
    }
.enum ELEMENTNAMESPACE_FLAGS {
    ELEMENTNAMESPACEFLAGS_ALLOWANYTAG	= 0x1,
    ELEMENTNAMESPACEFLAGS_QUERYFORUNKNOWNTAGS	= 0x2,
    ELEMENTNAMESPACE_FLAGS_Max	= 2147483647
    }
.enum VIEW_OBJECT_ALPHA_MODE {
    VIEW_OBJECT_ALPHA_MODE_IGNORE	= 0,
    VIEW_OBJECT_ALPHA_MODE_PREMULTIPLIED	= 1,
    VIEW_OBJECT_ALPHA_MODE_Max	= 2147483647
    }
.enum VIEW_OBJECT_COMPOSITION_MODE {
    VIEW_OBJECT_COMPOSITION_MODE_LEGACY = 0,
    VIEW_OBJECT_COMPOSITION_MODE_SURFACEPRESENTER	= 1,
    VIEW_OBJECT_COMPOSITION_MODE_Max	= 2147483647
    }

ifndef __IHTMLEventObj_INTERFACE_DEFINED__
define __IHTMLEventObj_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEventObj, "3050f32d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEventObj : public IDispatch

    get_srcElement	proc :ptr
    get_altKey		proc :ptr
    get_ctrlKey		proc :ptr
    get_shiftKey	proc :ptr
    put_returnValue	proc :VARIANT
    get_returnValue	proc :ptr
    put_cancelBubble	proc :VARIANT_BOOL
    get_cancelBubble	proc :ptr
    get_fromElement	proc :ptr
    get_toElement	proc :ptr
    put_keyCode		proc :LONG
    get_keyCode		proc :ptr
    get_button		proc :ptr
    get_type		proc :ptr
    get_qualifier	proc :ptr
    get_reason		proc :ptr
    get_x		proc :ptr
    get_y		proc :ptr
    get_clientX		proc :ptr
    get_clientY		proc :ptr
    get_offsetX		proc :ptr
    get_offsetY		proc :ptr
    get_screenX		proc :ptr
    get_screenY		proc :ptr
    get_srcFilter	proc :ptr
   .ends

endif

ifndef __IElementBehaviorSite_INTERFACE_DEFINED__
define __IElementBehaviorSite_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSite, "3050f427-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSite : public IUnknown

    GetElement		proc :ptr
    RegisterNotification proc :LONG
   .ends

endif

ifndef __IElementBehavior_INTERFACE_DEFINED__
define __IElementBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehavior, "3050f425-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehavior : public IUnknown

    Init		proc :ptr
    Notify		proc :LONG, :ptr
    Detach		proc
   .ends

endif

ifndef __IElementBehaviorFactory_INTERFACE_DEFINED__
define __IElementBehaviorFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorFactory, "3050f429-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorFactory : public IUnknown

    FindBehavior	proc :BSTR, :BSTR, :ptr, :ptr
   .ends

endif

ifndef __IElementBehaviorSiteOM_INTERFACE_DEFINED__
define __IElementBehaviorSiteOM_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSiteOM, "3050f489-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSiteOM : public IUnknown

    RegisterEvent	proc :LPOLESTR, :LONG, :ptr
    GetEventCookie	proc :LPOLESTR, :ptr
    FireEvent		proc :LONG, :ptr
    CreateEventObject	proc :ptr
    RegisterName	proc :LPOLESTR
    RegisterUrn		proc :LPOLESTR
   .ends

endif

ifndef __IElementBehaviorRender_INTERFACE_DEFINED__
define __IElementBehaviorRender_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorRender, "3050f4aa-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorRender : public IUnknown

    Draw		proc :HDC, :LONG, :ptr, :ptr
    GetRenderInfo	proc :ptr
    HitTestPoint	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __IElementBehaviorSiteRender_INTERFACE_DEFINED__
define __IElementBehaviorSiteRender_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSiteRender, "3050f4a7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSiteRender : public IUnknown

    Invalidate		proc :ptr
    InvalidateRenderInfo proc
    InvalidateStyle	proc
   .ends

endif

ifndef __IDOMEvent_INTERFACE_DEFINED__
define __IDOMEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMEvent, "305104ba-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMEvent : public IDispatch

    get_bubbles		proc :ptr
    get_cancelable	proc :ptr
    get_currentTarget	proc :ptr
    get_defaultPrevented proc :ptr
    get_eventPhase	proc :ptr
    get_target		proc :ptr
    get_timeStamp	proc :ptr
    get_type		proc :ptr
    initEvent		proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL
    preventDefault	proc
    stopPropagation	proc
    stopImmediatePropagation proc
    get_isTrusted	proc :ptr
    put_cancelBubble	proc :VARIANT_BOOL
    get_cancelBubble	proc :ptr
    get_srcElement	proc :ptr
   .ends

endif

ifndef __IHTMLDOMConstructor_INTERFACE_DEFINED__
define __IHTMLDOMConstructor_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMConstructor, "3051049b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMConstructor : public IDispatch

    get_constructor	proc :ptr
    LookupGetter	proc :BSTR, :ptr
    LookupSetter	proc :BSTR, :ptr
    DefineGetter	proc :BSTR, :ptr
    DefineSetter	proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLStyleSheetRule_INTERFACE_DEFINED__
define __IHTMLStyleSheetRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetRule, "3050f357-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetRule : public IDispatch

    put_selectorText	proc :BSTR
    get_selectorText	proc :ptr
    get_style		proc :ptr
    get_readOnly	proc :ptr
   .ends

endif

ifndef __IHTMLCSSStyleDeclaration_INTERFACE_DEFINED__
define __IHTMLCSSStyleDeclaration_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSStyleDeclaration, "30510740-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSStyleDeclaration : public IDispatch

    get_length		proc :ptr
    get_parentRule	proc :ptr
    getPropertyValue	proc :BSTR, :ptr
    getPropertyPriority proc :BSTR, :ptr
    removeProperty	proc :BSTR, :ptr
    setProperty		proc :BSTR, :ptr, :ptr
    item		proc :LONG, :ptr
    put_fontFamily	proc :BSTR
    get_fontFamily	proc :ptr
    put_fontStyle	proc :BSTR
    get_fontStyle	proc :ptr
    put_fontVariant	proc :BSTR
    get_fontVariant	proc :ptr
    put_fontWeight	proc :BSTR
    get_fontWeight	proc :ptr
    put_fontSize	proc :VARIANT
    get_fontSize	proc :ptr
    put_font		proc :BSTR
    get_font		proc :ptr
    put_color		proc :VARIANT
    get_color		proc :ptr
    put_background	proc :BSTR
    get_background	proc :ptr
    put_backgroundColor proc :VARIANT
    get_backgroundColor proc :ptr
    put_backgroundImage proc :BSTR
    get_backgroundImage proc :ptr
    put_backgroundRepeat proc :BSTR
    get_backgroundRepeat proc :ptr
    put_backgroundAttachment proc :BSTR
    get_backgroundAttachment proc :ptr
    put_backgroundPosition proc :BSTR
    get_backgroundPosition proc :ptr
    put_backgroundPositionX proc :VARIANT
    get_backgroundPositionX proc :ptr
    put_backgroundPositionY proc :VARIANT
    get_backgroundPositionY proc :ptr
    put_wordSpacing	proc :VARIANT
    get_wordSpacing	proc :ptr
    put_letterSpacing	proc :VARIANT
    get_letterSpacing	proc :ptr
    put_textDecoration	proc :BSTR
    get_textDecoration	proc :ptr
    put_verticalAlign	proc :VARIANT
    get_verticalAlign	proc :ptr
    put_textTransform	proc :BSTR
    get_textTransform	proc :ptr
    put_textAlign	proc :BSTR
    get_textAlign	proc :ptr
    put_textIndent	proc :VARIANT
    get_textIndent	proc :ptr
    put_lineHeight	proc :VARIANT
    get_lineHeight	proc :ptr
    put_marginTop	proc :VARIANT
    get_marginTop	proc :ptr
    put_marginRight	proc :VARIANT
    get_marginRight	proc :ptr
    put_marginBottom	proc :VARIANT
    get_marginBottom	proc :ptr
    put_marginLeft	proc :VARIANT
    get_marginLeft	proc :ptr
    put_margin		proc :BSTR
    get_margin		proc :ptr
    put_paddingTop	proc :VARIANT
    get_paddingTop	proc :ptr
    put_paddingRight	proc :VARIANT
    get_paddingRight	proc :ptr
    put_paddingBottom	proc :VARIANT
    get_paddingBottom	proc :ptr
    put_paddingLeft	proc :VARIANT
    get_paddingLeft	proc :ptr
    put_padding		proc :BSTR
    get_padding		proc :ptr
    put_border		proc :BSTR
    get_border		proc :ptr
    put_borderTop	proc :BSTR
    get_borderTop	proc :ptr
    put_borderRight	proc :BSTR
    get_borderRight	proc :ptr
    put_borderBottom	proc :BSTR
    get_borderBottom	proc :ptr
    put_borderLeft	proc :BSTR
    get_borderLeft	proc :ptr
    put_borderColor	proc :BSTR
    get_borderColor	proc :ptr
    put_borderTopColor	proc :VARIANT
    get_borderTopColor	proc :ptr
    put_borderRightColor proc :VARIANT
    get_borderRightColor proc :ptr
    put_borderBottomColor proc :VARIANT
    get_borderBottomColor proc :ptr
    put_borderLeftColor proc :VARIANT
    get_borderLeftColor proc :ptr
    put_borderWidth	proc :BSTR
    get_borderWidth	proc :ptr
    put_borderTopWidth	proc :VARIANT
    get_borderTopWidth	proc :ptr
    put_borderRightWidth proc :VARIANT
    get_borderRightWidth proc :ptr
    put_borderBottomWidth proc :VARIANT
    get_borderBottomWidth proc :ptr
    put_borderLeftWidth proc :VARIANT
    get_borderLeftWidth proc :ptr
    put_borderStyle	proc :BSTR
    get_borderStyle	proc :ptr
    put_borderTopStyle	proc :BSTR
    get_borderTopStyle	proc :ptr
    put_borderRightStyle proc :BSTR
    get_borderRightStyle proc :ptr
    put_borderBottomStyle proc :BSTR
    get_borderBottomStyle proc :ptr
    put_borderLeftStyle proc :BSTR
    get_borderLeftStyle proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    put_styleFloat	proc :BSTR
    get_styleFloat	proc :ptr
    put_clear		proc :BSTR
    get_clear		proc :ptr
    put_display		proc :BSTR
    get_display		proc :ptr
    put_visibility	proc :BSTR
    get_visibility	proc :ptr
    put_listStyleType	proc :BSTR
    get_listStyleType	proc :ptr
    put_listStylePosition proc :BSTR
    get_listStylePosition proc :ptr
    put_listStyleImage	proc :BSTR
    get_listStyleImage	proc :ptr
    put_listStyle	proc :BSTR
    get_listStyle	proc :ptr
    put_whiteSpace	proc :BSTR
    get_whiteSpace	proc :ptr
    put_top		proc :VARIANT
    get_top		proc :ptr
    put_left		proc :VARIANT
    get_left		proc :ptr
    put_zIndex		proc :VARIANT
    get_zIndex		proc :ptr
    put_overflow	proc :BSTR
    get_overflow	proc :ptr
    put_pageBreakBefore proc :BSTR
    get_pageBreakBefore proc :ptr
    put_pageBreakAfter	proc :BSTR
    get_pageBreakAfter	proc :ptr
    put_cssText		proc :BSTR
    get_cssText		proc :ptr
    put_cursor		proc :BSTR
    get_cursor		proc :ptr
    put_clip		proc :BSTR
    get_clip		proc :ptr
    put_filter		proc :BSTR
    get_filter		proc :ptr
    put_tableLayout	proc :BSTR
    get_tableLayout	proc :ptr
    put_borderCollapse	proc :BSTR
    get_borderCollapse	proc :ptr
    put_direction	proc :BSTR
    get_direction	proc :ptr
    put_behavior	proc :BSTR
    get_behavior	proc :ptr
    put_position	proc :BSTR
    get_position	proc :ptr
    put_unicodeBidi	proc :BSTR
    get_unicodeBidi	proc :ptr
    put_bottom		proc :VARIANT
    get_bottom		proc :ptr
    put_right		proc :VARIANT
    get_right		proc :ptr
    put_imeMode		proc :BSTR
    get_imeMode		proc :ptr
    put_rubyAlign	proc :BSTR
    get_rubyAlign	proc :ptr
    put_rubyPosition	proc :BSTR
    get_rubyPosition	proc :ptr
    put_rubyOverhang	proc :BSTR
    get_rubyOverhang	proc :ptr
    put_layoutGridChar	proc :VARIANT
    get_layoutGridChar	proc :ptr
    put_layoutGridLine	proc :VARIANT
    get_layoutGridLine	proc :ptr
    put_layoutGridMode	proc :BSTR
    get_layoutGridMode	proc :ptr
    put_layoutGridType	proc :BSTR
    get_layoutGridType	proc :ptr
    put_layoutGrid	proc :BSTR
    get_layoutGrid	proc :ptr
    put_textAutospace	proc :BSTR
    get_textAutospace	proc :ptr
    put_wordBreak	proc :BSTR
    get_wordBreak	proc :ptr
    put_lineBreak	proc :BSTR
    get_lineBreak	proc :ptr
    put_textJustify	proc :BSTR
    get_textJustify	proc :ptr
    put_textJustifyTrim proc :BSTR
    get_textJustifyTrim proc :ptr
    put_textKashida	proc :VARIANT
    get_textKashida	proc :ptr
    put_overflowX	proc :BSTR
    get_overflowX	proc :ptr
    put_overflowY	proc :BSTR
    get_overflowY	proc :ptr
    put_accelerator	proc :BSTR
    get_accelerator	proc :ptr
    put_layoutFlow	proc :BSTR
    get_layoutFlow	proc :ptr
    put_zoom		proc :VARIANT
    get_zoom		proc :ptr
    put_wordWrap	proc :BSTR
    get_wordWrap	proc :ptr
    put_textUnderlinePosition proc :BSTR
    get_textUnderlinePosition proc :ptr
    put_scrollbarBaseColor proc :VARIANT
    get_scrollbarBaseColor proc :ptr
    put_scrollbarFaceColor proc :VARIANT
    get_scrollbarFaceColor proc :ptr
    put_scrollbar3dLightColor proc :VARIANT
    get_scrollbar3dLightColor proc :ptr
    put_scrollbarShadowColor proc :VARIANT
    get_scrollbarShadowColor proc :ptr
    put_scrollbarHighlightColor proc :VARIANT
    get_scrollbarHighlightColor proc :ptr
    put_scrollbarDarkShadowColor proc :VARIANT
    get_scrollbarDarkShadowColor proc :ptr
    put_scrollbarArrowColor proc :VARIANT
    get_scrollbarArrowColor proc :ptr
    put_scrollbarTrackColor proc :VARIANT
    get_scrollbarTrackColor proc :ptr
    put_writingMode	proc :BSTR
    get_writingMode	proc :ptr
    put_textAlignLast	proc :BSTR
    get_textAlignLast	proc :ptr
    put_textKashidaSpace proc :VARIANT
    get_textKashidaSpace proc :ptr
    put_textOverflow	proc :BSTR
    get_textOverflow	proc :ptr
    put_minHeight	proc :VARIANT
    get_minHeight	proc :ptr
    put_msInterpolationMode proc :BSTR
    get_msInterpolationMode proc :ptr
    put_maxHeight	proc :VARIANT
    get_maxHeight	proc :ptr
    put_minWidth	proc :VARIANT
    get_minWidth	proc :ptr
    put_maxWidth	proc :VARIANT
    get_maxWidth	proc :ptr
    put_content		proc :BSTR
    get_content		proc :ptr
    put_captionSide	proc :BSTR
    get_captionSide	proc :ptr
    put_counterIncrement proc :BSTR
    get_counterIncrement proc :ptr
    put_counterReset	proc :BSTR
    get_counterReset	proc :ptr
    put_outline		proc :BSTR
    get_outline		proc :ptr
    put_outlineWidth	proc :VARIANT
    get_outlineWidth	proc :ptr
    put_outlineStyle	proc :BSTR
    get_outlineStyle	proc :ptr
    put_outlineColor	proc :VARIANT
    get_outlineColor	proc :ptr
    put_boxSizing	proc :BSTR
    get_boxSizing	proc :ptr
    put_borderSpacing	proc :BSTR
    get_borderSpacing	proc :ptr
    put_orphans		proc :VARIANT
    get_orphans		proc :ptr
    put_widows		proc :VARIANT
    get_widows		proc :ptr
    put_pageBreakInside proc :BSTR
    get_pageBreakInside proc :ptr
    put_emptyCells	proc :BSTR
    get_emptyCells	proc :ptr
    put_msBlockProgression proc :BSTR
    get_msBlockProgression proc :ptr
    put_quotes		proc :BSTR
    get_quotes		proc :ptr
    put_alignmentBaseline proc :BSTR
    get_alignmentBaseline proc :ptr
    put_baselineShift	proc :VARIANT
    get_baselineShift	proc :ptr
    put_dominantBaseline proc :BSTR
    get_dominantBaseline proc :ptr
    put_fontSizeAdjust	proc :VARIANT
    get_fontSizeAdjust	proc :ptr
    put_fontStretch	proc :BSTR
    get_fontStretch	proc :ptr
    put_opacity		proc :VARIANT
    get_opacity		proc :ptr
    put_clipPath	proc :BSTR
    get_clipPath	proc :ptr
    put_clipRule	proc :BSTR
    get_clipRule	proc :ptr
    put_fill		proc :BSTR
    get_fill		proc :ptr
    put_fillOpacity	proc :VARIANT
    get_fillOpacity	proc :ptr
    put_fillRule	proc :BSTR
    get_fillRule	proc :ptr
    put_kerning		proc :VARIANT
    get_kerning		proc :ptr
    put_marker		proc :BSTR
    get_marker		proc :ptr
    put_markerEnd	proc :BSTR
    get_markerEnd	proc :ptr
    put_markerMid	proc :BSTR
    get_markerMid	proc :ptr
    put_markerStart	proc :BSTR
    get_markerStart	proc :ptr
    put_mask		proc :BSTR
    get_mask		proc :ptr
    put_pointerEvents	proc :BSTR
    get_pointerEvents	proc :ptr
    put_stopColor	proc :VARIANT
    get_stopColor	proc :ptr
    put_stopOpacity	proc :VARIANT
    get_stopOpacity	proc :ptr
    put_stroke		proc :BSTR
    get_stroke		proc :ptr
    put_strokeDasharray proc :BSTR
    get_strokeDasharray proc :ptr
    put_strokeDashoffset proc :VARIANT
    get_strokeDashoffset proc :ptr
    put_strokeLinecap	proc :BSTR
    get_strokeLinecap	proc :ptr
    put_strokeLinejoin	proc :BSTR
    get_strokeLinejoin	proc :ptr
    put_strokeMiterlimit proc :VARIANT
    get_strokeMiterlimit proc :ptr
    put_strokeOpacity	proc :VARIANT
    get_strokeOpacity	proc :ptr
    put_strokeWidth	proc :VARIANT
    get_strokeWidth	proc :ptr
    put_textAnchor	proc :BSTR
    get_textAnchor	proc :ptr
    put_glyphOrientationHorizontal proc :VARIANT
    get_glyphOrientationHorizontal proc :ptr
    put_glyphOrientationVertical proc :VARIANT
    get_glyphOrientationVertical proc :ptr
    put_borderRadius	proc :BSTR
    get_borderRadius	proc :ptr
    put_borderTopLeftRadius proc :BSTR
    get_borderTopLeftRadius proc :ptr
    put_borderTopRightRadius proc :BSTR
    get_borderTopRightRadius proc :ptr
    put_borderBottomRightRadius proc :BSTR
    get_borderBottomRightRadius proc :ptr
    put_borderBottomLeftRadius proc :BSTR
    get_borderBottomLeftRadius proc :ptr
    put_clipTop		proc :VARIANT
    get_clipTop		proc :ptr
    put_clipRight	proc :VARIANT
    get_clipRight	proc :ptr
    get_clipBottom	proc :ptr
    put_clipLeft	proc :VARIANT
    get_clipLeft	proc :ptr
    put_cssFloat	proc :BSTR
    get_cssFloat	proc :ptr
    put_backgroundClip	proc :BSTR
    get_backgroundClip	proc :ptr
    put_backgroundOrigin proc :BSTR
    get_backgroundOrigin proc :ptr
    put_backgroundSize	proc :BSTR
    get_backgroundSize	proc :ptr
    put_boxShadow	proc :BSTR
    get_boxShadow	proc :ptr
    put_msTransform	proc :BSTR
    get_msTransform	proc :ptr
    put_msTransformOrigin proc :BSTR
    get_msTransformOrigin proc :ptr
   .ends

endif

ifndef __IHTMLCSSStyleDeclaration2_INTERFACE_DEFINED__
define __IHTMLCSSStyleDeclaration2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSStyleDeclaration2, "305107d1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSStyleDeclaration2 : public IDispatch

    put_msScrollChaining proc :BSTR
    get_msScrollChaining proc :ptr
    put_msContentZooming proc :BSTR
    get_msContentZooming proc :ptr
    put_msContentZoomSnapType proc :BSTR
    get_msContentZoomSnapType proc :ptr
    put_msScrollRails	proc :BSTR
    get_msScrollRails	proc :ptr
    put_msContentZoomChaining proc :BSTR
    get_msContentZoomChaining proc :ptr
    put_msScrollSnapType proc :BSTR
    get_msScrollSnapType proc :ptr
    put_msContentZoomLimit proc :BSTR
    get_msContentZoomLimit proc :ptr
    put_msContentZoomSnap proc :BSTR
    get_msContentZoomSnap proc :ptr
    put_msContentZoomSnapPoints proc :BSTR
    get_msContentZoomSnapPoints proc :ptr
    put_msContentZoomLimitMin proc :VARIANT
    get_msContentZoomLimitMin proc :ptr
    put_msContentZoomLimitMax proc :VARIANT
    get_msContentZoomLimitMax proc :ptr
    put_msScrollSnapX	proc :BSTR
    get_msScrollSnapX	proc :ptr
    put_msScrollSnapY	proc :BSTR
    get_msScrollSnapY	proc :ptr
    put_msScrollSnapPointsX proc :BSTR
    get_msScrollSnapPointsX proc :ptr
    put_msScrollSnapPointsY proc :BSTR
    get_msScrollSnapPointsY proc :ptr
    put_msGridColumn	proc :VARIANT
    get_msGridColumn	proc :ptr
    put_msGridColumnAlign proc :BSTR
    get_msGridColumnAlign proc :ptr
    put_msGridColumns	proc :BSTR
    get_msGridColumns	proc :ptr
    put_msGridColumnSpan proc :VARIANT
    get_msGridColumnSpan proc :ptr
    put_msGridRow	proc :VARIANT
    get_msGridRow	proc :ptr
    put_msGridRowAlign	proc :BSTR
    get_msGridRowAlign	proc :ptr
    put_msGridRows	proc :BSTR
    get_msGridRows	proc :ptr
    put_msGridRowSpan	proc :VARIANT
    get_msGridRowSpan	proc :ptr
    put_msWrapThrough	proc :BSTR
    get_msWrapThrough	proc :ptr
    put_msWrapMargin	proc :VARIANT
    get_msWrapMargin	proc :ptr
    put_msWrapFlow	proc :BSTR
    get_msWrapFlow	proc :ptr
    put_msAnimationName proc :BSTR
    get_msAnimationName proc :ptr
    put_msAnimationDuration proc :BSTR
    get_msAnimationDuration proc :ptr
    put_msAnimationTimingFunction proc :BSTR
    get_msAnimationTimingFunction proc :ptr
    put_msAnimationDelay proc :BSTR
    get_msAnimationDelay proc :ptr
    put_msAnimationDirection proc :BSTR
    get_msAnimationDirection proc :ptr
    put_msAnimationPlayState proc :BSTR
    get_msAnimationPlayState proc :ptr
    put_msAnimationIterationCount proc :BSTR
    get_msAnimationIterationCount proc :ptr
    put_msAnimation	proc :BSTR
    get_msAnimation	proc :ptr
    put_msAnimationFillMode proc :BSTR
    get_msAnimationFillMode proc :ptr
    put_colorInterpolationFilters proc :BSTR
    get_colorInterpolationFilters proc :ptr
    put_columnCount	proc :VARIANT
    get_columnCount	proc :ptr
    put_columnWidth	proc :VARIANT
    get_columnWidth	proc :ptr
    put_columnGap	proc :VARIANT
    get_columnGap	proc :ptr
    put_columnFill	proc :BSTR
    get_columnFill	proc :ptr
    put_columnSpan	proc :BSTR
    get_columnSpan	proc :ptr
    put_columns		proc :BSTR
    get_columns		proc :ptr
    put_columnRule	proc :BSTR
    get_columnRule	proc :ptr
    put_columnRuleColor proc :VARIANT
    get_columnRuleColor proc :ptr
    put_columnRuleStyle proc :BSTR
    get_columnRuleStyle proc :ptr
    put_columnRuleWidth proc :VARIANT
    get_columnRuleWidth proc :ptr
    put_breakBefore	proc :BSTR
    get_breakBefore	proc :ptr
    put_breakAfter	proc :BSTR
    get_breakAfter	proc :ptr
    put_breakInside	proc :BSTR
    get_breakInside	proc :ptr
    put_floodColor	proc :VARIANT
    get_floodColor	proc :ptr
    put_floodOpacity	proc :VARIANT
    get_floodOpacity	proc :ptr
    put_lightingColor	proc :VARIANT
    get_lightingColor	proc :ptr
    put_msScrollLimitXMin proc :VARIANT
    get_msScrollLimitXMin proc :ptr
    put_msScrollLimitYMin proc :VARIANT
    get_msScrollLimitYMin proc :ptr
    put_msScrollLimitXMax proc :VARIANT
    get_msScrollLimitXMax proc :ptr
    put_msScrollLimitYMax proc :VARIANT
    get_msScrollLimitYMax proc :ptr
    put_msScrollLimit	proc :BSTR
    get_msScrollLimit	proc :ptr
    put_textShadow	proc :BSTR
    get_textShadow	proc :ptr
    put_msFlowFrom	proc :BSTR
    get_msFlowFrom	proc :ptr
    put_msFlowInto	proc :BSTR
    get_msFlowInto	proc :ptr
    put_msHyphens	proc :BSTR
    get_msHyphens	proc :ptr
    put_msHyphenateLimitZone proc :VARIANT
    get_msHyphenateLimitZone proc :ptr
    put_msHyphenateLimitChars proc :BSTR
    get_msHyphenateLimitChars proc :ptr
    put_msHyphenateLimitLines proc :VARIANT
    get_msHyphenateLimitLines proc :ptr
    put_msHighContrastAdjust proc :BSTR
    get_msHighContrastAdjust proc :ptr
    put_enableBackground proc :BSTR
    get_enableBackground proc :ptr
    put_msFontFeatureSettings proc :BSTR
    get_msFontFeatureSettings proc :ptr
    put_msUserSelect	proc :BSTR
    get_msUserSelect	proc :ptr
    put_msOverflowStyle proc :BSTR
    get_msOverflowStyle proc :ptr
    put_msTransformStyle proc :BSTR
    get_msTransformStyle proc :ptr
    put_msBackfaceVisibility proc :BSTR
    get_msBackfaceVisibility proc :ptr
    put_msPerspective	proc :VARIANT
    get_msPerspective	proc :ptr
    put_msPerspectiveOrigin proc :BSTR
    get_msPerspectiveOrigin proc :ptr
    put_msTransitionProperty proc :BSTR
    get_msTransitionProperty proc :ptr
    put_msTransitionDuration proc :BSTR
    get_msTransitionDuration proc :ptr
    put_msTransitionTimingFunction proc :BSTR
    get_msTransitionTimingFunction proc :ptr
    put_msTransitionDelay proc :BSTR
    get_msTransitionDelay proc :ptr
    put_msTransition	proc :BSTR
    get_msTransition	proc :ptr
    put_msTouchAction	proc :BSTR
    get_msTouchAction	proc :ptr
    put_msScrollTranslation proc :BSTR
    get_msScrollTranslation proc :ptr
    put_msFlex		proc :BSTR
    get_msFlex		proc :ptr
    put_msFlexPositive	proc :VARIANT
    get_msFlexPositive	proc :ptr
    put_msFlexNegative	proc :VARIANT
    get_msFlexNegative	proc :ptr
    put_msFlexPreferredSize proc :VARIANT
    get_msFlexPreferredSize proc :ptr
    put_msFlexFlow	proc :BSTR
    get_msFlexFlow	proc :ptr
    put_msFlexDirection proc :BSTR
    get_msFlexDirection proc :ptr
    put_msFlexWrap	proc :BSTR
    get_msFlexWrap	proc :ptr
    put_msFlexAlign	proc :BSTR
    get_msFlexAlign	proc :ptr
    put_msFlexItemAlign proc :BSTR
    get_msFlexItemAlign proc :ptr
    put_msFlexPack	proc :BSTR
    get_msFlexPack	proc :ptr
    put_msFlexLinePack	proc :BSTR
    get_msFlexLinePack	proc :ptr
    put_msFlexOrder	proc :VARIANT
    get_msFlexOrder	proc :ptr
    put_msTouchSelect	proc :BSTR
    get_msTouchSelect	proc :ptr
    put_transform	proc :BSTR
    get_transform	proc :ptr
    put_transformOrigin proc :BSTR
    get_transformOrigin proc :ptr
    put_transformStyle	proc :BSTR
    get_transformStyle	proc :ptr
    put_backfaceVisibility proc :BSTR
    get_backfaceVisibility proc :ptr
    put_perspective	proc :VARIANT
    get_perspective	proc :ptr
    put_perspectiveOrigin proc :BSTR
    get_perspectiveOrigin proc :ptr
    put_transitionProperty proc :BSTR
    get_transitionProperty proc :ptr
    put_transitionDuration proc :BSTR
    get_transitionDuration proc :ptr
    put_transitionTimingFunction proc :BSTR
    get_transitionTimingFunction proc :ptr
    put_transitionDelay proc :BSTR
    get_transitionDelay proc :ptr
    put_transition	proc :BSTR
    get_transition	proc :ptr
    put_fontFeatureSettings proc :BSTR
    get_fontFeatureSettings proc :ptr
    put_animationName	proc :BSTR
    get_animationName	proc :ptr
    put_animationDuration proc :BSTR
    get_animationDuration proc :ptr
    put_animationTimingFunction proc :BSTR
    get_animationTimingFunction proc :ptr
    put_animationDelay	proc :BSTR
    get_animationDelay	proc :ptr
    put_animationDirection proc :BSTR
    get_animationDirection proc :ptr
    put_animationPlayState proc :BSTR
    get_animationPlayState proc :ptr
    put_animationIterationCount proc :BSTR
    get_animationIterationCount proc :ptr
    put_animation	proc :BSTR
    get_animation	proc :ptr
    put_animationFillMode proc :BSTR
    get_animationFillMode proc :ptr
   .ends

endif

ifndef __IHTMLCSSStyleDeclaration3_INTERFACE_DEFINED__
define __IHTMLCSSStyleDeclaration3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSStyleDeclaration3, "3051085C-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSStyleDeclaration3 : public IDispatch

    put_flex		proc :BSTR
    get_flex		proc :ptr
    put_flexDirection	proc :BSTR
    get_flexDirection	proc :ptr
    put_flexWrap	proc :BSTR
    get_flexWrap	proc :ptr
    put_flexFlow	proc :BSTR
    get_flexFlow	proc :ptr
    put_flexGrow	proc :VARIANT
    get_flexGrow	proc :ptr
    put_flexShrink	proc :VARIANT
    get_flexShrink	proc :ptr
    put_flexBasis	proc :VARIANT
    get_flexBasis	proc :ptr
    put_justifyContent	proc :BSTR
    get_justifyContent	proc :ptr
    put_alignItems	proc :BSTR
    get_alignItems	proc :ptr
    put_alignSelf	proc :BSTR
    get_alignSelf	proc :ptr
    put_alignContent	proc :BSTR
    get_alignContent	proc :ptr
    put_borderImage	proc :BSTR
    get_borderImage	proc :ptr
    put_borderImageSource proc :BSTR
    get_borderImageSource proc :ptr
    put_borderImageSlice proc :BSTR
    get_borderImageSlice proc :ptr
    put_borderImageWidth proc :BSTR
    get_borderImageWidth proc :ptr
    put_borderImageOutset proc :BSTR
    get_borderImageOutset proc :ptr
    put_borderImageRepeat proc :BSTR
    get_borderImageRepeat proc :ptr
    put_msImeAlign	proc :BSTR
    get_msImeAlign	proc :ptr
    put_msTextCombineHorizontal proc :BSTR
    get_msTextCombineHorizontal proc :ptr
    put_touchAction	proc :BSTR
    get_touchAction	proc :ptr
   .ends

endif

ifndef __IHTMLStyleEnabled_INTERFACE_DEFINED__
define __IHTMLStyleEnabled_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleEnabled, "305104c2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleEnabled : public IDispatch

    msGetPropertyEnabled proc :BSTR, :ptr
    msPutPropertyEnabled proc :BSTR, :VARIANT_BOOL
   .ends

endif

ifndef __DispHTMLCSSStyleDeclaration_DISPINTERFACE_DEFINED__
define __DispHTMLCSSStyleDeclaration_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCSSStyleDeclaration, "3059009a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCSSStyleDeclaration : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCSSStyleDeclaration, "30510741-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyle_INTERFACE_DEFINED__
define __IHTMLStyle_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyle, "3059009a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyle : public IDispatch

    put_fontFamily	proc :BSTR
    get_fontFamily	proc :ptr
    put_fontStyle	proc :BSTR
    get_fontStyle	proc :ptr
    put_fontVariant	proc :BSTR
    get_fontVariant	proc :ptr
    put_fontWeight	proc :BSTR
    get_fontWeight	proc :ptr
    put_fontSize	proc :VARIANT
    get_fontSize	proc :ptr
    put_font		proc :BSTR
    get_font		proc :ptr
    put_color		proc :VARIANT
    get_color		proc :ptr
    put_background	proc :BSTR
    get_background	proc :ptr
    put_backgroundColor proc :VARIANT
    get_backgroundColor proc :ptr
    put_backgroundImage proc :BSTR
    get_backgroundImage proc :ptr
    put_backgroundRepeat proc :BSTR
    get_backgroundRepeat proc :ptr
    put_backgroundAttachment proc :BSTR
    get_backgroundAttachment proc :ptr
    put_backgroundPosition proc :BSTR
    get_backgroundPosition proc :ptr
    put_backgroundPositionX proc :VARIANT
    get_backgroundPositionX proc :ptr
    put_backgroundPositionY proc :VARIANT
    get_backgroundPositionY proc :ptr
    put_wordSpacing	proc :VARIANT
    get_wordSpacing	proc :ptr
    put_letterSpacing	proc :VARIANT
    get_letterSpacing	proc :ptr
    put_textDecoration	proc :BSTR
    get_textDecoration	proc :ptr
    put_textDecorationNone proc :VARIANT_BOOL
    get_textDecorationNone proc :ptr
    put_textDecorationUnderline proc :VARIANT_BOOL
    get_textDecorationUnderline proc :ptr
    put_textDecorationOverline proc :VARIANT_BOOL
    get_textDecorationOverline proc :ptr
    put_textDecorationLineThrough proc :VARIANT_BOOL
    get_textDecorationLineThrough proc :ptr
    put_textDecorationBlink proc :VARIANT_BOOL
    get_textDecorationBlink proc :ptr
    put_verticalAlign	proc :VARIANT
    get_verticalAlign	proc :ptr
    put_textTransform	proc :BSTR
    get_textTransform	proc :ptr
    put_textAlign	proc :BSTR
    get_textAlign	proc :ptr
    put_textIndent	proc :VARIANT
    get_textIndent	proc :ptr
    put_lineHeight	proc :VARIANT
    get_lineHeight	proc :ptr
    put_marginTop	proc :VARIANT
    get_marginTop	proc :ptr
    put_marginRight	proc :VARIANT
    get_marginRight	proc :ptr
    put_marginBottom	proc :VARIANT
    get_marginBottom	proc :ptr
    put_marginLeft	proc :VARIANT
    get_marginLeft	proc :ptr
    put_margin		proc :BSTR
    get_margin		proc :ptr
    put_paddingTop	proc :VARIANT
    get_paddingTop	proc :ptr
    put_paddingRight	proc :VARIANT
    get_paddingRight	proc :ptr
    put_paddingBottom	proc :VARIANT
    get_paddingBottom	proc :ptr
    put_paddingLeft	proc :VARIANT
    get_paddingLeft	proc :ptr
    put_padding		proc :BSTR
    get_padding		proc :ptr
    put_border		proc :BSTR
    get_border		proc :ptr
    put_borderTop	proc :BSTR
    get_borderTop	proc :ptr
    put_borderRight	proc :BSTR
    get_borderRight	proc :ptr
    put_borderBottom	proc :BSTR
    get_borderBottom	proc :ptr
    put_borderLeft	proc :BSTR
    get_borderLeft	proc :ptr
    put_borderColor	proc :BSTR
    get_borderColor	proc :ptr
    put_borderTopColor	proc :VARIANT
    get_borderTopColor	proc :ptr
    put_borderRightColor proc :VARIANT
    get_borderRightColor proc :ptr
    put_borderBottomColor proc :VARIANT
    get_borderBottomColor proc :ptr
    put_borderLeftColor proc :VARIANT
    get_borderLeftColor proc :ptr
    put_borderWidth	proc :BSTR
    get_borderWidth	proc :ptr
    put_borderTopWidth	proc :VARIANT
    get_borderTopWidth	proc :ptr
    put_borderRightWidth proc :VARIANT
    get_borderRightWidth proc :ptr
    put_borderBottomWidth proc :VARIANT
    get_borderBottomWidth proc :ptr
    put_borderLeftWidth proc :VARIANT
    get_borderLeftWidth proc :ptr
    put_borderStyle	proc :BSTR
    get_borderStyle	proc :ptr
    put_borderTopStyle	proc :BSTR
    get_borderTopStyle	proc :ptr
    put_borderRightStyle proc :BSTR
    get_borderRightStyle proc :ptr
    put_borderBottomStyle proc :BSTR
    get_borderBottomStyle proc :ptr
    put_borderLeftStyle proc :BSTR
    get_borderLeftStyle proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    put_styleFloat	proc :BSTR
    get_styleFloat	proc :ptr
    put_clear		proc :BSTR
    get_clear		proc :ptr
    put_display		proc :BSTR
    get_display		proc :ptr
    put_visibility	proc :BSTR
    get_visibility	proc :ptr
    put_listStyleType	proc :BSTR
    get_listStyleType	proc :ptr
    put_listStylePosition proc :BSTR
    get_listStylePosition proc :ptr
    put_listStyleImage	proc :BSTR
    get_listStyleImage	proc :ptr
    put_listStyle	proc :BSTR
    get_listStyle	proc :ptr
    put_whiteSpace	proc :BSTR
    get_whiteSpace	proc :ptr
    put_top		proc :VARIANT
    get_top		proc :ptr
    put_left		proc :VARIANT
    get_left		proc :ptr
    get_position	proc :ptr
    put_zIndex		proc :VARIANT
    get_zIndex		proc :ptr
    put_overflow	proc :BSTR
    get_overflow	proc :ptr
    put_pageBreakBefore proc :BSTR
    get_pageBreakBefore proc :ptr
    put_pageBreakAfter	proc :BSTR
    get_pageBreakAfter	proc :ptr
    put_cssText		proc :BSTR
    get_cssText		proc :ptr
    put_pixelTop	proc :LONG
    get_pixelTop	proc :ptr
    put_pixelLeft	proc :LONG
    get_pixelLeft	proc :ptr
    put_pixelWidth	proc :LONG
    get_pixelWidth	proc :ptr
    put_pixelHeight	proc :LONG
    get_pixelHeight	proc :ptr
    put_posTop		proc :FLOAT
    get_posTop		proc :ptr
    put_posLeft		proc :FLOAT
    get_posLeft		proc :ptr
    put_posWidth	proc :FLOAT
    get_posWidth	proc :ptr
    put_posHeight	proc :FLOAT
    get_posHeight	proc :ptr
    put_cursor		proc :BSTR
    get_cursor		proc :ptr
    put_clip		proc :BSTR
    get_clip		proc :ptr
    put_filter		proc :BSTR
    get_filter		proc :ptr
    setAttribute	proc :BSTR, :VARIANT, :LONG
    getAttribute	proc :BSTR, :LONG, :ptr
    removeAttribute	proc :BSTR, :LONG, :ptr
    toString		proc :ptr
   .ends

endif

ifndef __IHTMLStyle2_INTERFACE_DEFINED__
define __IHTMLStyle2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyle2, "3050f25e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyle2 : public IDispatch

    put_tableLayout	proc :BSTR
    get_tableLayout	proc :ptr
    put_borderCollapse	proc :BSTR
    get_borderCollapse	proc :ptr
    put_direction	proc :BSTR
    get_direction	proc :ptr
    put_behavior	proc :BSTR
    get_behavior	proc :ptr
    setExpression	proc :BSTR, :BSTR, :BSTR
    getExpression	proc :BSTR, :ptr
    removeExpression	proc :BSTR, :ptr
    put_position	proc :BSTR
    get_position	proc :ptr
    put_unicodeBidi	proc :BSTR
    get_unicodeBidi	proc :ptr
    put_bottom		proc :VARIANT
    get_bottom		proc :ptr
    put_right		proc :VARIANT
    get_right		proc :ptr
    put_pixelBottom	proc :LONG
    get_pixelBottom	proc :ptr
    put_pixelRight	proc :LONG
    get_pixelRight	proc :ptr
    put_posBottom	proc :FLOAT
    get_posBottom	proc :ptr
    put_posRight	proc :FLOAT
    get_posRight	proc :ptr
    put_imeMode		proc :BSTR
    get_imeMode		proc :ptr
    put_rubyAlign	proc :BSTR
    get_rubyAlign	proc :ptr
    put_rubyPosition	proc :BSTR
    get_rubyPosition	proc :ptr
    put_rubyOverhang	proc :BSTR
    get_rubyOverhang	proc :ptr
    put_layoutGridChar	proc :VARIANT
    get_layoutGridChar	proc :ptr
    put_layoutGridLine	proc :VARIANT
    get_layoutGridLine	proc :ptr
    put_layoutGridMode	proc :BSTR
    get_layoutGridMode	proc :ptr
    put_layoutGridType	proc :BSTR
    get_layoutGridType	proc :ptr
    put_layoutGrid	proc :BSTR
    get_layoutGrid	proc :ptr
    put_wordBreak	proc :BSTR
    get_wordBreak	proc :ptr
    put_lineBreak	proc :BSTR
    get_lineBreak	proc :ptr
    put_textJustify	proc :BSTR
    get_textJustify	proc :ptr
    put_textJustifyTrim proc :BSTR
    get_textJustifyTrim proc :ptr
    put_textKashida	proc :VARIANT
    get_textKashida	proc :ptr
    put_textAutospace	proc :BSTR
    get_textAutospace	proc :ptr
    put_overflowX	proc :BSTR
    get_overflowX	proc :ptr
    put_overflowY	proc :BSTR
    get_overflowY	proc :ptr
    put_accelerator	proc :BSTR
    get_accelerator	proc :ptr
   .ends

endif

ifndef __IHTMLStyle3_INTERFACE_DEFINED__
define __IHTMLStyle3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyle3, "3050f4a2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyle3 : public IDispatch

    put_layoutFlow	proc :BSTR
    get_layoutFlow	proc :ptr
    put_zoom		proc :VARIANT
    get_zoom		proc :ptr
    put_wordWrap	proc :BSTR
    get_wordWrap	proc :ptr
    put_textUnderlinePosition proc :BSTR
    get_textUnderlinePosition proc :ptr
    put_scrollbarBaseColor proc :VARIANT
    get_scrollbarBaseColor proc :ptr
    put_scrollbarFaceColor proc :VARIANT
    get_scrollbarFaceColor proc :ptr
    put_scrollbar3dLightColor proc :VARIANT
    get_scrollbar3dLightColor proc :ptr
    put_scrollbarShadowColor proc :VARIANT
    get_scrollbarShadowColor proc :ptr
    put_scrollbarHighlightColor proc :VARIANT
    get_scrollbarHighlightColor proc :ptr
    put_scrollbarDarkShadowColor proc :VARIANT
    get_scrollbarDarkShadowColor proc :ptr
    put_scrollbarArrowColor proc :VARIANT
    get_scrollbarArrowColor proc :ptr
    put_scrollbarTrackColor proc :VARIANT
    get_scrollbarTrackColor proc :ptr
    put_writingMode	proc :BSTR
    get_writingMode	proc :ptr
    put_textAlignLast	proc :BSTR
    get_textAlignLast	proc :ptr
    put_textKashidaSpace proc :VARIANT
    get_textKashidaSpace proc :ptr
   .ends

endif

ifndef __IHTMLStyle4_INTERFACE_DEFINED__
define __IHTMLStyle4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyle4, "3050f656-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyle4 : public IDispatch

    put_textOverflow	proc :BSTR
    get_textOverflow	proc :ptr
    put_minHeight	proc :VARIANT
    get_minHeight	proc :ptr
   .ends

endif

ifndef __IHTMLStyle5_INTERFACE_DEFINED__
define __IHTMLStyle5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyle5, "3050f816-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyle5 : public IDispatch

    put_msInterpolationMode proc :BSTR
    get_msInterpolationMode proc :ptr
    put_maxHeight	proc :VARIANT
    get_maxHeight	proc :ptr
    put_minWidth	proc :VARIANT
    get_minWidth	proc :ptr
    put_maxWidth	proc :VARIANT
    get_maxWidth	proc :ptr
   .ends

endif

ifndef __IHTMLStyle6_INTERFACE_DEFINED__
define __IHTMLStyle6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyle6, "3050f33a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyle6 : public IDispatch

    put_content		proc :BSTR
    get_content		proc :ptr
    put_captionSide	proc :BSTR
    get_captionSide	proc :ptr
    put_counterIncrement proc :BSTR
    get_counterIncrement proc :ptr
    put_counterReset	proc :BSTR
    get_counterReset	proc :ptr
    put_outline		proc :BSTR
    get_outline		proc :ptr
    put_outlineWidth	proc :VARIANT
    get_outlineWidth	proc :ptr
    put_outlineStyle	proc :BSTR
    get_outlineStyle	proc :ptr
    put_outlineColor	proc :VARIANT
    get_outlineColor	proc :ptr
    put_boxSizing	proc :BSTR
    get_boxSizing	proc :ptr
    put_borderSpacing	proc :BSTR
    get_borderSpacing	proc :ptr
    put_orphans		proc :VARIANT
    get_orphans		proc :ptr
    put_widows		proc :VARIANT
    get_widows		proc :ptr
    put_pageBreakInside proc :BSTR
    get_pageBreakInside proc :ptr
    put_emptyCells	proc :BSTR
    get_emptyCells	proc :ptr
    put_msBlockProgression proc :BSTR
    get_msBlockProgression proc :ptr
    put_quotes		proc :BSTR
    get_quotes		proc :ptr
   .ends

endif

ifndef __IHTMLRuleStyle_INTERFACE_DEFINED__
define __IHTMLRuleStyle_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRuleStyle, "30510480-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRuleStyle : public IDispatch

    put_fontFamily	proc :BSTR
    get_fontFamily	proc :ptr
    put_fontStyle	proc :BSTR
    get_fontStyle	proc :ptr
    put_fontVariant	proc :BSTR
    get_fontVariant	proc :ptr
    put_fontWeight	proc :BSTR
    get_fontWeight	proc :ptr
    put_fontSize	proc :VARIANT
    get_fontSize	proc :ptr
    put_font		proc :BSTR
    get_font		proc :ptr
    put_color		proc :VARIANT
    get_color		proc :ptr
    put_background	proc :BSTR
    get_background	proc :ptr
    put_backgroundColor proc :VARIANT
    get_backgroundColor proc :ptr
    put_backgroundImage proc :BSTR
    get_backgroundImage proc :ptr
    put_backgroundRepeat proc :BSTR
    get_backgroundRepeat proc :ptr
    put_backgroundAttachment proc :BSTR
    get_backgroundAttachment proc :ptr
    put_backgroundPosition proc :BSTR
    get_backgroundPosition proc :ptr
    put_backgroundPositionX proc :VARIANT
    get_backgroundPositionX proc :ptr
    put_backgroundPositionY proc :VARIANT
    get_backgroundPositionY proc :ptr
    put_wordSpacing	proc :VARIANT
    get_wordSpacing	proc :ptr
    put_letterSpacing	proc :VARIANT
    get_letterSpacing	proc :ptr
    put_textDecoration	proc :BSTR
    get_textDecoration	proc :ptr
    put_textDecorationNone proc :VARIANT_BOOL
    get_textDecorationNone proc :ptr
    put_textDecorationUnderline proc :VARIANT_BOOL
    get_textDecorationUnderline proc :ptr
    put_textDecorationOverline proc :VARIANT_BOOL
    get_textDecorationOverline proc :ptr
    put_textDecorationLineThrough proc :VARIANT_BOOL
    get_textDecorationLineThrough proc :ptr
    put_textDecorationBlink proc :VARIANT_BOOL
    get_textDecorationBlink proc :ptr
    put_verticalAlign	proc :VARIANT
    get_verticalAlign	proc :ptr
    put_textTransform	proc :BSTR
    get_textTransform	proc :ptr
    put_textAlign	proc :BSTR
    get_textAlign	proc :ptr
    put_textIndent	proc :VARIANT
    get_textIndent	proc :ptr
    put_lineHeight	proc :VARIANT
    get_lineHeight	proc :ptr
    put_marginTop	proc :VARIANT
    get_marginTop	proc :ptr
    put_marginRight	proc :VARIANT
    get_marginRight	proc :ptr
    put_marginBottom	proc :VARIANT
    get_marginBottom	proc :ptr
    put_marginLeft	proc :VARIANT
    get_marginLeft	proc :ptr
    put_margin		proc :BSTR
    get_margin		proc :ptr
    put_paddingTop	proc :VARIANT
    get_paddingTop	proc :ptr
    put_paddingRight	proc :VARIANT
    get_paddingRight	proc :ptr
    put_paddingBottom	proc :VARIANT
    get_paddingBottom	proc :ptr
    put_paddingLeft	proc :VARIANT
    get_paddingLeft	proc :ptr
    put_padding		proc :BSTR
    get_padding		proc :ptr
    put_border		proc :BSTR
    get_border		proc :ptr
    put_borderTop	proc :BSTR
    get_borderTop	proc :ptr
    put_borderRight	proc :BSTR
    get_borderRight	proc :ptr
    put_borderBottom	proc :BSTR
    get_borderBottom	proc :ptr
    put_borderLeft	proc :BSTR
    get_borderLeft	proc :ptr
    put_borderColor	proc :BSTR
    get_borderColor	proc :ptr
    put_borderTopColor	proc :VARIANT
    get_borderTopColor	proc :ptr
    put_borderRightColor proc :VARIANT
    get_borderRightColor proc :ptr
    put_borderBottomColor proc :VARIANT
    get_borderBottomColor proc :ptr
    put_borderLeftColor proc :VARIANT
    get_borderLeftColor proc :ptr
    put_borderWidth	proc :BSTR
    get_borderWidth	proc :ptr
    put_borderTopWidth	proc :VARIANT
    get_borderTopWidth	proc :ptr
    put_borderRightWidth proc :VARIANT
    get_borderRightWidth proc :ptr
    put_borderBottomWidth proc :VARIANT
    get_borderBottomWidth proc :ptr
    put_borderLeftWidth proc :VARIANT
    get_borderLeftWidth proc :ptr
    put_borderStyle	proc :BSTR
    get_borderStyle	proc :ptr
    put_borderTopStyle	proc :BSTR
    get_borderTopStyle	proc :ptr
    put_borderRightStyle proc :BSTR
    get_borderRightStyle proc :ptr
    put_borderBottomStyle proc :BSTR
    get_borderBottomStyle proc :ptr
    put_borderLeftStyle proc :BSTR
    get_borderLeftStyle proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    put_styleFloat	proc :BSTR
    get_styleFloat	proc :ptr
    put_clear		proc :BSTR
    get_clear		proc :ptr
    put_display		proc :BSTR
    get_display		proc :ptr
    put_visibility	proc :BSTR
    get_visibility	proc :ptr
    put_listStyleType	proc :BSTR
    get_listStyleType	proc :ptr
    put_listStylePosition proc :BSTR
    get_listStylePosition proc :ptr
    put_listStyleImage	proc :BSTR
    get_listStyleImage	proc :ptr
    put_listStyle	proc :BSTR
    get_listStyle	proc :ptr
    put_whiteSpace	proc :BSTR
    get_whiteSpace	proc :ptr
    put_top		proc :VARIANT
    get_top		proc :ptr
    put_left		proc :VARIANT
    get_left		proc :ptr
    get_position	proc :ptr
    put_zIndex		proc :VARIANT
    get_zIndex		proc :ptr
    put_overflow	proc :BSTR
    get_overflow	proc :ptr
    put_pageBreakBefore proc :BSTR
    get_pageBreakBefore proc :ptr
    put_pageBreakAfter	proc :BSTR
    get_pageBreakAfter	proc :ptr
    put_cssText		proc :BSTR
    get_cssText		proc :ptr
    put_cursor		proc :BSTR
    get_cursor		proc :ptr
    put_clip		proc :BSTR
    get_clip		proc :ptr
    put_filter		proc :BSTR
    get_filter		proc :ptr
    setAttribute	proc :BSTR, :VARIANT, :LONG
    getAttribute	proc :BSTR, :LONG, :ptr
    removeAttribute	proc :BSTR, :LONG, :ptr
   .ends

endif

ifndef __IHTMLRuleStyle2_INTERFACE_DEFINED__
define __IHTMLRuleStyle2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRuleStyle2, "3050f3cf-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRuleStyle2 : public IDispatch

    put_tableLayout	proc :BSTR
    get_tableLayout	proc :ptr
    put_borderCollapse	proc :BSTR
    get_borderCollapse	proc :ptr
    put_direction	proc :BSTR
    get_direction	proc :ptr
    put_behavior	proc :BSTR
    get_behavior	proc :ptr
    put_position	proc :BSTR
    get_position	proc :ptr
    put_unicodeBidi	proc :BSTR
    get_unicodeBidi	proc :ptr
    put_bottom		proc :VARIANT
    get_bottom		proc :ptr
    put_right		proc :VARIANT
    get_right		proc :ptr
    put_pixelBottom	proc :LONG
    get_pixelBottom	proc :ptr
    put_pixelRight	proc :LONG
    get_pixelRight	proc :ptr
    put_posBottom	proc :FLOAT
    get_posBottom	proc :ptr
    put_posRight	proc :FLOAT
    get_posRight	proc :ptr
    put_imeMode		proc :BSTR
    get_imeMode		proc :ptr
    put_rubyAlign	proc :BSTR
    get_rubyAlign	proc :ptr
    put_rubyPosition	proc :BSTR
    get_rubyPosition	proc :ptr
    put_rubyOverhang	proc :BSTR
    get_rubyOverhang	proc :ptr
    put_layoutGridChar	proc :VARIANT
    get_layoutGridChar	proc :ptr
    put_layoutGridLine	proc :VARIANT
    get_layoutGridLine	proc :ptr
    put_layoutGridMode	proc :BSTR
    get_layoutGridMode	proc :ptr
    put_layoutGridType	proc :BSTR
    get_layoutGridType	proc :ptr
    put_layoutGrid	proc :BSTR
    get_layoutGrid	proc :ptr
    put_textAutospace	proc :BSTR
    get_textAutospace	proc :ptr
    put_wordBreak	proc :BSTR
    get_wordBreak	proc :ptr
    put_lineBreak	proc :BSTR
    get_lineBreak	proc :ptr
    put_textJustify	proc :BSTR
    get_textJustify	proc :ptr
    put_textJustifyTrim proc :BSTR
    get_textJustifyTrim proc :ptr
    put_textKashida	proc :VARIANT
    get_textKashida	proc :ptr
    put_overflowX	proc :BSTR
    get_overflowX	proc :ptr
    put_overflowY	proc :BSTR
    get_overflowY	proc :ptr
    put_accelerator	proc :BSTR
    get_accelerator	proc :ptr
   .ends

endif

ifndef __IHTMLRuleStyle3_INTERFACE_DEFINED__
define __IHTMLRuleStyle3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRuleStyle3, "3050f4ac-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRuleStyle3 : public IDispatch

    put_layoutFlow	proc :BSTR
    get_layoutFlow	proc :ptr
    put_zoom		proc :VARIANT
    get_zoom		proc :ptr
    put_wordWrap	proc :BSTR
    get_wordWrap	proc :ptr
    put_textUnderlinePosition proc :BSTR
    get_textUnderlinePosition proc :ptr
    put_scrollbarBaseColor proc :VARIANT
    get_scrollbarBaseColor proc :ptr
    put_scrollbarFaceColor proc :VARIANT
    get_scrollbarFaceColor proc :ptr
    put_scrollbar3dLightColor proc :VARIANT
    get_scrollbar3dLightColor proc :ptr
    put_scrollbarShadowColor proc :VARIANT
    get_scrollbarShadowColor proc :ptr
    put_scrollbarHighlightColor proc :VARIANT
    get_scrollbarHighlightColor proc :ptr
    put_scrollbarDarkShadowColor proc :VARIANT
    get_scrollbarDarkShadowColor proc :ptr
    put_scrollbarArrowColor proc :VARIANT
    get_scrollbarArrowColor proc :ptr
    put_scrollbarTrackColor proc :VARIANT
    get_scrollbarTrackColor proc :ptr
    put_writingMode	proc :BSTR
    get_writingMode	proc :ptr
    put_textAlignLast	proc :BSTR
    get_textAlignLast	proc :ptr
    put_textKashidaSpace proc :VARIANT
    get_textKashidaSpace proc :ptr
   .ends

endif

ifndef __IHTMLRuleStyle4_INTERFACE_DEFINED__
define __IHTMLRuleStyle4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRuleStyle4, "3050f657-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRuleStyle4 : public IDispatch

    put_textOverflow	proc :BSTR
    get_textOverflow	proc :ptr
    put_minHeight	proc :VARIANT
    get_minHeight	proc :ptr
   .ends

endif

ifndef __IHTMLRuleStyle5_INTERFACE_DEFINED__
define __IHTMLRuleStyle5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRuleStyle5, "3050f817-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRuleStyle5 : public IDispatch

    put_msInterpolationMode proc :BSTR
    get_msInterpolationMode proc :ptr
    put_maxHeight	proc :VARIANT
    get_maxHeight	proc :ptr
    put_minWidth	proc :VARIANT
    get_minWidth	proc :ptr
    put_maxWidth	proc :VARIANT
    get_maxWidth	proc :ptr
   .ends

endif

ifndef __IHTMLRuleStyle6_INTERFACE_DEFINED__
define __IHTMLRuleStyle6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRuleStyle6, "3050f335-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRuleStyle6 : public IDispatch

    put_content		proc :BSTR
    get_content		proc :ptr
    put_captionSide	proc :BSTR
    get_captionSide	proc :ptr
    put_counterIncrement proc :BSTR
    get_counterIncrement proc :ptr
    put_counterReset	proc :BSTR
    get_counterReset	proc :ptr
    put_outline		proc :BSTR
    get_outline		proc :ptr
    put_outlineWidth	proc :VARIANT
    get_outlineWidth	proc :ptr
    put_outlineStyle	proc :BSTR
    get_outlineStyle	proc :ptr
    put_outlineColor	proc :VARIANT
    get_outlineColor	proc :ptr
    put_boxSizing	proc :BSTR
    get_boxSizing	proc :ptr
    put_borderSpacing	proc :BSTR
    get_borderSpacing	proc :ptr
    put_orphans		proc :VARIANT
    get_orphans		proc :ptr
    put_widows		proc :VARIANT
    get_widows		proc :ptr
    put_pageBreakInside proc :BSTR
    get_pageBreakInside proc :ptr
    put_emptyCells	proc :BSTR
    get_emptyCells	proc :ptr
    put_msBlockProgression proc :BSTR
    get_msBlockProgression proc :ptr
    put_quotes		proc :BSTR
    get_quotes		proc :ptr
   .ends

endif

ifndef __DispHTMLStyle_DISPINTERFACE_DEFINED__
define __DispHTMLStyle_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyle, "3050f55a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyle : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyle, "3050f285-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLRuleStyle_DISPINTERFACE_DEFINED__
define __DispHTMLRuleStyle_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLRuleStyle, "3050f55c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLRuleStyle : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLRuleStyle, "3050f3d0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleSheetRulesCollection_INTERFACE_DEFINED__
define __IHTMLStyleSheetRulesCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetRulesCollection, "30510471-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetRulesCollection : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLStyleSheet_INTERFACE_DEFINED__
define __IHTMLStyleSheet_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheet, "3050f55a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheet : public IDispatch

    put_title		proc :BSTR
    get_title		proc :ptr
    get_parentStyleSheet proc :ptr
    get_owningElement	proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_readOnly	proc :ptr
    get_imports		proc :ptr
    put_href		proc :BSTR
    get_href		proc :ptr
    get_type		proc :ptr
    get_id		proc :ptr
    addImport		proc :BSTR, :LONG, :ptr
    addRule		proc :BSTR, :BSTR, :LONG, :ptr
    removeImport	proc :LONG
    removeRule		proc :LONG
    put_media		proc :BSTR
    get_media		proc :ptr
    put_cssText		proc :BSTR
    get_cssText		proc :ptr
    get_rules		proc :ptr
   .ends

endif

ifndef __IHTMLCSSRule_INTERFACE_DEFINED__
define __IHTMLCSSRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSRule, "3050f55c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSRule : public IDispatch

    get_type		proc :ptr
    put_cssText		proc :BSTR
    get_cssText		proc :ptr
    get_parentRule	proc :ptr
    get_parentStyleSheet proc :ptr
   .ends

endif

ifndef __IHTMLCSSImportRule_INTERFACE_DEFINED__
define __IHTMLCSSImportRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSImportRule, "3050f2e5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSImportRule : public IDispatch

    get_href		proc :ptr
    put_media		proc :VARIANT
    get_media		proc :ptr
    get_styleSheet	proc :ptr
   .ends

endif

ifndef __IHTMLCSSMediaRule_INTERFACE_DEFINED__
define __IHTMLCSSMediaRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSMediaRule, "3050f2e3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSMediaRule : public IDispatch

    put_media		proc :VARIANT
    get_media		proc :ptr
    get_cssRules	proc :ptr
    insertRule		proc :BSTR, :LONG, :ptr
    deleteRule		proc :LONG
   .ends

endif

ifndef __IHTMLCSSMediaList_INTERFACE_DEFINED__
define __IHTMLCSSMediaList_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSMediaList, "305106e9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSMediaList : public IDispatch

    put_mediaText	proc :BSTR
    get_mediaText	proc :ptr
    get_length		proc :ptr
    item		proc :LONG, :ptr
    appendMedium	proc :BSTR
    deleteMedium	proc :BSTR
   .ends

endif

ifndef __IHTMLCSSNamespaceRule_INTERFACE_DEFINED__
define __IHTMLCSSNamespaceRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCSSNamespaceRule, "305106ea-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCSSNamespaceRule : public IDispatch

    get_namespaceURI	proc :ptr
    get_prefix		proc :ptr
   .ends

endif

ifndef __IHTMLMSCSSKeyframeRule_INTERFACE_DEFINED__
define __IHTMLMSCSSKeyframeRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMSCSSKeyframeRule, "305106eb-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMSCSSKeyframeRule : public IDispatch

    put_keyText		proc :BSTR
    get_keyText		proc :ptr
    get_style		proc :ptr
   .ends

endif

ifndef __IHTMLMSCSSKeyframesRule_INTERFACE_DEFINED__
define __IHTMLMSCSSKeyframesRule_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMSCSSKeyframesRule, "30510731-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMSCSSKeyframesRule : public IDispatch

    put_name		proc :BSTR
    get_name		proc :ptr
    get_cssRules	proc :ptr
    appendRule		proc :BSTR
    deleteRule		proc :BSTR
    findRule		proc :BSTR, :ptr
   .ends

endif

ifndef __DispHTMLCSSRule_DISPINTERFACE_DEFINED__
define __DispHTMLCSSRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCSSRule, "3059007d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCSSRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCSSRule, "305106ef-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLCSSImportRule_DISPINTERFACE_DEFINED__
define __DispHTMLCSSImportRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCSSImportRule, "3059007e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCSSImportRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCSSImportRule, "305106f0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLCSSMediaRule_DISPINTERFACE_DEFINED__
define __DispHTMLCSSMediaRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCSSMediaRule, "3059007f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCSSMediaRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCSSMediaRule, "305106f1-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLCSSMediaList_DISPINTERFACE_DEFINED__
define __DispHTMLCSSMediaList_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCSSMediaList, "30590097-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCSSMediaList : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCSSMediaList, "30510732-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLCSSNamespaceRule_DISPINTERFACE_DEFINED__
define __DispHTMLCSSNamespaceRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCSSNamespaceRule, "30590080-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCSSNamespaceRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCSSNamespaceRule, "305106f2-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLMSCSSKeyframeRule_DISPINTERFACE_DEFINED__
define __DispHTMLMSCSSKeyframeRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMSCSSKeyframeRule, "305900de-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMSCSSKeyframeRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMSCSSKeyframeRule, "3051080E-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLMSCSSKeyframesRule_DISPINTERFACE_DEFINED__
define __DispHTMLMSCSSKeyframesRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMSCSSKeyframesRule, "305900df-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMSCSSKeyframesRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMSCSSKeyframesRule, "3051080F-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLRenderStyle_INTERFACE_DEFINED__
define __IHTMLRenderStyle_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRenderStyle, "305106ee-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRenderStyle : public IDispatch

    put_textLineThroughStyle proc :BSTR
    get_textLineThroughStyle proc :ptr
    put_textUnderlineStyle proc :BSTR
    get_textUnderlineStyle proc :ptr
    put_textEffect	proc :BSTR
    get_textEffect	proc :ptr
    put_textColor	proc :VARIANT
    get_textColor	proc :ptr
    put_textBackgroundColor proc :VARIANT
    get_textBackgroundColor proc :ptr
    put_textDecorationColor proc :VARIANT
    get_textDecorationColor proc :ptr
    put_renderingPriority proc :LONG
    get_renderingPriority proc :ptr
    put_defaultTextSelection proc :BSTR
    get_defaultTextSelection proc :ptr
    put_textDecoration	proc :BSTR
    get_textDecoration	proc :ptr
   .ends

endif

ifndef __DispHTMLRenderStyle_DISPINTERFACE_DEFINED__
define __DispHTMLRenderStyle_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLRenderStyle, "3050f58b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLRenderStyle : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLRenderStyle, "3050f6aa-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLCurrentStyle_INTERFACE_DEFINED__
define __IHTMLCurrentStyle_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCurrentStyle, "3051080C-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCurrentStyle : public IDispatch

    get_position	proc :ptr
    get_styleFloat	proc :ptr
    get_color		proc :ptr
    get_backgroundColor proc :ptr
    get_fontFamily	proc :ptr
    get_fontStyle	proc :ptr
    get_fontVariant	proc :ptr
    get_fontWeight	proc :ptr
    get_fontSize	proc :ptr
    get_backgroundImage proc :ptr
    get_backgroundPositionX proc :ptr
    get_backgroundPositionY proc :ptr
    get_backgroundRepeat proc :ptr
    get_borderLeftColor proc :ptr
    get_borderTopColor	proc :ptr
    get_borderRightColor proc :ptr
    get_borderBottomColor proc :ptr
    get_borderTopStyle	proc :ptr
    get_borderRightStyle proc :ptr
    get_borderBottomStyle proc :ptr
    get_borderLeftStyle proc :ptr
    get_borderTopWidth	proc :ptr
    get_borderRightWidth proc :ptr
    get_borderBottomWidth proc :ptr
    get_borderLeftWidth proc :ptr
    get_left		proc :ptr
    get_top		proc :ptr
    get_width		proc :ptr
    get_height		proc :ptr
    get_paddingLeft	proc :ptr
    get_paddingTop	proc :ptr
    get_paddingRight	proc :ptr
    get_paddingBottom	proc :ptr
    get_textAlign	proc :ptr
    get_textDecoration	proc :ptr
    get_display		proc :ptr
    get_visibility	proc :ptr
    get_zIndex		proc :ptr
    get_letterSpacing	proc :ptr
    get_lineHeight	proc :ptr
    get_textIndent	proc :ptr
    get_verticalAlign	proc :ptr
    get_backgroundAttachment proc :ptr
    get_marginTop	proc :ptr
    get_marginRight	proc :ptr
    get_marginBottom	proc :ptr
    get_marginLeft	proc :ptr
    get_clear		proc :ptr
    get_listStyleType	proc :ptr
    get_listStylePosition proc :ptr
    get_listStyleImage	proc :ptr
    get_clipTop		proc :ptr
    get_clipRight	proc :ptr
    get_clipBottom	proc :ptr
    get_clipLeft	proc :ptr
    get_overflow	proc :ptr
    get_pageBreakBefore proc :ptr
    get_pageBreakAfter	proc :ptr
    get_cursor		proc :ptr
    get_tableLayout	proc :ptr
    get_borderCollapse	proc :ptr
    get_direction	proc :ptr
    get_behavior	proc :ptr
    getAttribute	proc :BSTR, :LONG, :ptr
    get_unicodeBidi	proc :ptr
    get_right		proc :ptr
    get_bottom		proc :ptr
    get_imeMode		proc :ptr
    get_rubyAlign	proc :ptr
    get_rubyPosition	proc :ptr
    get_rubyOverhang	proc :ptr
    get_textAutospace	proc :ptr
    get_lineBreak	proc :ptr
    get_wordBreak	proc :ptr
    get_textJustify	proc :ptr
    get_textJustifyTrim proc :ptr
    get_textKashida	proc :ptr
    get_blockDirection	proc :ptr
    get_layoutGridChar	proc :ptr
    get_layoutGridLine	proc :ptr
    get_layoutGridMode	proc :ptr
    get_layoutGridType	proc :ptr
    get_borderStyle	proc :ptr
    get_borderColor	proc :ptr
    get_borderWidth	proc :ptr
    get_padding		proc :ptr
    get_margin		proc :ptr
    get_accelerator	proc :ptr
    get_overflowX	proc :ptr
    get_overflowY	proc :ptr
    get_textTransform	proc :ptr
   .ends

endif

ifndef __IHTMLCurrentStyle2_INTERFACE_DEFINED__
define __IHTMLCurrentStyle2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCurrentStyle2, "3051080D-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCurrentStyle2 : public IDispatch

    get_layoutFlow	proc :ptr
    get_wordWrap	proc :ptr
    get_textUnderlinePosition proc :ptr
    get_hasLayout	proc :ptr
    get_scrollbarBaseColor proc :ptr
    get_scrollbarFaceColor proc :ptr
    get_scrollbar3dLightColor proc :ptr
    get_scrollbarShadowColor proc :ptr
    get_scrollbarHighlightColor proc :ptr
    get_scrollbarDarkShadowColor proc :ptr
    get_scrollbarArrowColor proc :ptr
    get_scrollbarTrackColor proc :ptr
    get_writingMode	proc :ptr
    get_zoom		proc :ptr
    get_filter		proc :ptr
    get_textAlignLast	proc :ptr
    get_textKashidaSpace proc :ptr
    get_isBlock		proc :ptr
   .ends

endif

ifndef __IHTMLCurrentStyle3_INTERFACE_DEFINED__
define __IHTMLCurrentStyle3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCurrentStyle3, "3059007d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCurrentStyle3 : public IDispatch

    get_textOverflow	proc :ptr
    get_minHeight	proc :ptr
    get_wordSpacing	proc :ptr
    get_whiteSpace	proc :ptr
   .ends

endif

ifndef __IHTMLCurrentStyle4_INTERFACE_DEFINED__
define __IHTMLCurrentStyle4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCurrentStyle4, "3059007e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCurrentStyle4 : public IDispatch

    get_msInterpolationMode proc :ptr
    get_maxHeight	proc :ptr
    get_minWidth	proc :ptr
    get_maxWidth	proc :ptr
   .ends

endif

ifndef __IHTMLCurrentStyle5_INTERFACE_DEFINED__
define __IHTMLCurrentStyle5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCurrentStyle5, "3059007f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCurrentStyle5 : public IDispatch

    get_captionSide	proc :ptr
    get_outline		proc :ptr
    get_outlineWidth	proc :ptr
    get_outlineStyle	proc :ptr
    get_outlineColor	proc :ptr
    get_boxSizing	proc :ptr
    get_borderSpacing	proc :ptr
    get_orphans		proc :ptr
    get_widows		proc :ptr
    get_pageBreakInside proc :ptr
    get_emptyCells	proc :ptr
    get_msBlockProgression proc :ptr
    get_quotes		proc :ptr
   .ends

endif

ifndef __DispHTMLCurrentStyle_DISPINTERFACE_DEFINED__
define __DispHTMLCurrentStyle_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCurrentStyle, "3050f557-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCurrentStyle : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCurrentStyle, "3050f3dc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLElement_INTERFACE_DEFINED__
define __IHTMLElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement, "30590097-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement : public IDispatch

    setAttribute	proc :BSTR, :VARIANT, :LONG
    getAttribute	proc :BSTR, :LONG, :ptr
    removeAttribute	proc :BSTR, :LONG, :ptr
    put_className	proc :BSTR
    get_className	proc :ptr
    put_id		proc :BSTR
    get_id		proc :ptr
    get_tagName		proc :ptr
    get_parentElement	proc :ptr
    get_style		proc :ptr
    put_onhelp		proc :VARIANT
    get_onhelp		proc :ptr
    put_onclick		proc :VARIANT
    get_onclick		proc :ptr
    put_ondblclick	proc :VARIANT
    get_ondblclick	proc :ptr
    put_onkeydown	proc :VARIANT
    get_onkeydown	proc :ptr
    put_onkeyup		proc :VARIANT
    get_onkeyup		proc :ptr
    put_onkeypress	proc :VARIANT
    get_onkeypress	proc :ptr
    put_onmouseout	proc :VARIANT
    get_onmouseout	proc :ptr
    put_onmouseover	proc :VARIANT
    get_onmouseover	proc :ptr
    put_onmousemove	proc :VARIANT
    get_onmousemove	proc :ptr
    put_onmousedown	proc :VARIANT
    get_onmousedown	proc :ptr
    put_onmouseup	proc :VARIANT
    get_onmouseup	proc :ptr
    get_document	proc :ptr
    put_title		proc :BSTR
    get_title		proc :ptr
    put_language	proc :BSTR
    get_language	proc :ptr
    put_onselectstart	proc :VARIANT
    get_onselectstart	proc :ptr
    scrollIntoView	proc :VARIANT
    contains		proc :ptr, :ptr
    get_sourceIndex	proc :ptr
    get_recordNumber	proc :ptr
    put_lang		proc :BSTR
    get_lang		proc :ptr
    get_offsetLeft	proc :ptr
    get_offsetTop	proc :ptr
    get_offsetWidth	proc :ptr
    get_offsetHeight	proc :ptr
    get_offsetParent	proc :ptr
    put_innerHTML	proc :BSTR
    get_innerHTML	proc :ptr
    put_innerText	proc :BSTR
    get_innerText	proc :ptr
    put_outerHTML	proc :BSTR
    get_outerHTML	proc :ptr
    put_outerText	proc :BSTR
    get_outerText	proc :ptr
    insertAdjacentHTML	proc :BSTR, :BSTR
    insertAdjacentText	proc :BSTR, :BSTR
    get_parentTextEdit	proc :ptr
    get_isTextEdit	proc :ptr
    click		proc
    get_filters		proc :ptr
    put_ondragstart	proc :VARIANT
    get_ondragstart	proc :ptr
    toString		proc :ptr
    put_onbeforeupdate	proc :VARIANT
    get_onbeforeupdate	proc :ptr
    put_onafterupdate	proc :VARIANT
    get_onafterupdate	proc :ptr
    put_onerrorupdate	proc :VARIANT
    get_onerrorupdate	proc :ptr
    put_onrowexit	proc :VARIANT
    get_onrowexit	proc :ptr
    put_onrowenter	proc :VARIANT
    get_onrowenter	proc :ptr
    put_ondatasetchanged proc :VARIANT
    get_ondatasetchanged proc :ptr
    put_ondataavailable proc :VARIANT
    get_ondataavailable proc :ptr
    put_ondatasetcomplete proc :VARIANT
    get_ondatasetcomplete proc :ptr
    put_onfilterchange	proc :VARIANT
    get_onfilterchange	proc :ptr
    get_children	proc :ptr
    get_all		proc :ptr
   .ends

endif

ifndef __IHTMLRect_INTERFACE_DEFINED__
define __IHTMLRect_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRect, "30590080-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRect : public IDispatch

    put_left		proc :LONG
    get_left		proc :ptr
    put_top		proc :LONG
    get_top		proc :ptr
    put_right		proc :LONG
    get_right		proc :ptr
    put_bottom		proc :LONG
    get_bottom		proc :ptr
   .ends

endif

ifndef __IHTMLRect2_INTERFACE_DEFINED__
define __IHTMLRect2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRect2, "305900de-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRect2 : public IDispatch

    get_width		proc :ptr
    get_height		proc :ptr
   .ends

endif

ifndef __IHTMLRectCollection_INTERFACE_DEFINED__
define __IHTMLRectCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLRectCollection, "305900df-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLRectCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr
   .ends

endif

ifndef __IHTMLElementCollection_INTERFACE_DEFINED__
define __IHTMLElementCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementCollection, "3050f6ae-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementCollection : public IDispatch

    toString		proc :ptr
    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :VARIANT, :VARIANT, :ptr
    tags		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLElement2_INTERFACE_DEFINED__
define __IHTMLElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement2, "3050f58b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement2 : public IDispatch

    get_scopeName	proc :ptr
    setCapture		proc :VARIANT_BOOL
    releaseCapture	proc
    put_onlosecapture	proc :VARIANT
    get_onlosecapture	proc :ptr
    componentFromPoint	proc :LONG, :LONG, :ptr
    doScroll		proc :VARIANT
    put_onscroll	proc :VARIANT
    get_onscroll	proc :ptr
    put_ondrag		proc :VARIANT
    get_ondrag		proc :ptr
    put_ondragend	proc :VARIANT
    get_ondragend	proc :ptr
    put_ondragenter	proc :VARIANT
    get_ondragenter	proc :ptr
    put_ondragover	proc :VARIANT
    get_ondragover	proc :ptr
    put_ondragleave	proc :VARIANT
    get_ondragleave	proc :ptr
    put_ondrop		proc :VARIANT
    get_ondrop		proc :ptr
    put_onbeforecut	proc :VARIANT
    get_onbeforecut	proc :ptr
    put_oncut		proc :VARIANT
    get_oncut		proc :ptr
    put_onbeforecopy	proc :VARIANT
    get_onbeforecopy	proc :ptr
    put_oncopy		proc :VARIANT
    get_oncopy		proc :ptr
    put_onbeforepaste	proc :VARIANT
    get_onbeforepaste	proc :ptr
    put_onpaste		proc :VARIANT
    get_onpaste		proc :ptr
    get_currentStyle	proc :ptr
    put_onpropertychange proc :VARIANT
    get_onpropertychange proc :ptr
    getClientRects	proc :ptr
    getBoundingClientRect proc :ptr
    setExpression	proc :BSTR, :BSTR, :BSTR
    getExpression	proc :BSTR, :ptr
    removeExpression	proc :BSTR, :ptr
    put_tabIndex	proc :sword
    get_tabIndex	proc :ptr
    focus		proc
    put_accessKey	proc :BSTR
    get_accessKey	proc :ptr
    put_onblur		proc :VARIANT
    get_onblur		proc :ptr
    put_onfocus		proc :VARIANT
    get_onfocus		proc :ptr
    put_onresize	proc :VARIANT
    get_onresize	proc :ptr
    blur		proc
    addFilter		proc :ptr
    removeFilter	proc :ptr
    get_clientHeight	proc :ptr
    get_clientWidth	proc :ptr
    get_clientTop	proc :ptr
    get_clientLeft	proc :ptr
    attachEvent		proc :BSTR, :ptr, :ptr
    detachEvent		proc :BSTR, :ptr
    get_readyState	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    put_onrowsdelete	proc :VARIANT
    get_onrowsdelete	proc :ptr
    put_onrowsinserted	proc :VARIANT
    get_onrowsinserted	proc :ptr
    put_oncellchange	proc :VARIANT
    get_oncellchange	proc :ptr
    put_dir		proc :BSTR
    get_dir		proc :ptr
    createControlRange	proc :ptr
    get_scrollHeight	proc :ptr
    get_scrollWidth	proc :ptr
    put_scrollTop	proc :LONG
    get_scrollTop	proc :ptr
    put_scrollLeft	proc :LONG
    get_scrollLeft	proc :ptr
    clearAttributes	proc
    mergeAttributes	proc
    put_oncontextmenu	proc :VARIANT
    get_oncontextmenu	proc :ptr
    insertAdjacentElement proc :BSTR, :ptr, :ptr
    applyElement	proc :ptr, :BSTR, :ptr
    getAdjacentText	proc :BSTR, :ptr
    replaceAdjacentText proc :BSTR, :BSTR, :ptr
    get_canHaveChildren proc :ptr
    addBehavior		proc :BSTR, :ptr, :ptr
    removeBehavior	proc :LONG, :ptr
    get_runtimeStyle	proc :ptr
    get_behaviorUrns	proc :ptr
    put_tagUrn		proc :BSTR
    get_tagUrn		proc :ptr
    put_onbeforeeditfocus proc :VARIANT
    get_onbeforeeditfocus proc :ptr
    get_readyStateValue proc :ptr
    getElementsByTagName proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLAttributeCollection3_INTERFACE_DEFINED__
define __IHTMLAttributeCollection3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAttributeCollection3, "3050f3db-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAttributeCollection3 : public IDispatch

    getNamedItem	proc :BSTR, :ptr
    setNamedItem	proc :ptr, :ptr
    removeNamedItem	proc :BSTR, :ptr
    item		proc :LONG, :ptr
    get_length		proc :ptr
   .ends

endif

ifndef __IDOMDocumentType_INTERFACE_DEFINED__
define __IDOMDocumentType_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMDocumentType, "3050f658-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMDocumentType : public IDispatch

    get_name		proc :ptr
    get_entities	proc :ptr
    get_notations	proc :ptr
    get_publicId	proc :ptr
    get_systemId	proc :ptr
    get_internalSubset	proc :ptr
   .ends

endif

ifndef __IHTMLDocument7_INTERFACE_DEFINED__
define __IHTMLDocument7_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument7, "3050f818-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument7 : public IDispatch

    get_defaultView	proc :ptr
    createCDATASection	proc :BSTR, :ptr
    getSelection	proc :ptr
    getElementsByTagNameNS proc :ptr, :BSTR, :ptr
    createElementNS	proc :ptr, :BSTR, :ptr
    createAttributeNS	proc :ptr, :BSTR, :ptr
    put_onmsthumbnailclick proc :VARIANT
    get_onmsthumbnailclick proc :ptr
    get_characterSet	proc :ptr
    createElement	proc :BSTR, :ptr
    createAttribute	proc :BSTR, :ptr
    getElementsByClassName proc :BSTR, :ptr
    createProcessingInstruction proc :BSTR, :BSTR, :ptr
    adoptNode		proc :ptr, :ptr
    put_onmssitemodejumplistitemremoved proc :VARIANT
    get_onmssitemodejumplistitemremoved proc :ptr
    get_all		proc :ptr
    get_inputEncoding	proc :ptr
    get_xmlEncoding	proc :ptr
    put_xmlStandalone	proc :VARIANT_BOOL
    get_xmlStandalone	proc :ptr
    put_xmlVersion	proc :BSTR
    get_xmlVersion	proc :ptr
    hasAttributes	proc :ptr
    put_onabort		proc :VARIANT
    get_onabort		proc :ptr
    put_onblur		proc :VARIANT
    get_onblur		proc :ptr
    put_oncanplay	proc :VARIANT
    get_oncanplay	proc :ptr
    put_oncanplaythrough proc :VARIANT
    get_oncanplaythrough proc :ptr
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_ondrag		proc :VARIANT
    get_ondrag		proc :ptr
    put_ondragend	proc :VARIANT
    get_ondragend	proc :ptr
    put_ondragenter	proc :VARIANT
    get_ondragenter	proc :ptr
    put_ondragleave	proc :VARIANT
    get_ondragleave	proc :ptr
    put_ondragover	proc :VARIANT
    get_ondragover	proc :ptr
    put_ondrop		proc :VARIANT
    get_ondrop		proc :ptr
    put_ondurationchange proc :VARIANT
    get_ondurationchange proc :ptr
    put_onemptied	proc :VARIANT
    get_onemptied	proc :ptr
    put_onended		proc :VARIANT
    get_onended		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_onfocus		proc :VARIANT
    get_onfocus		proc :ptr
    put_oninput		proc :VARIANT
    get_oninput		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onloadeddata	proc :VARIANT
    get_onloadeddata	proc :ptr
    put_onloadedmetadata proc :VARIANT
    get_onloadedmetadata proc :ptr
    put_onloadstart	proc :VARIANT
    get_onloadstart	proc :ptr
    put_onpause		proc :VARIANT
    get_onpause		proc :ptr
    put_onplay		proc :VARIANT
    get_onplay		proc :ptr
    put_onplaying	proc :VARIANT
    get_onplaying	proc :ptr
    put_onprogress	proc :VARIANT
    get_onprogress	proc :ptr
    put_onratechange	proc :VARIANT
    get_onratechange	proc :ptr
    put_onreset		proc :VARIANT
    get_onreset		proc :ptr
    put_onscroll	proc :VARIANT
    get_onscroll	proc :ptr
    put_onseeked	proc :VARIANT
    get_onseeked	proc :ptr
    put_onseeking	proc :VARIANT
    get_onseeking	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_onstalled	proc :VARIANT
    get_onstalled	proc :ptr
    put_onsubmit	proc :VARIANT
    get_onsubmit	proc :ptr
    put_onsuspend	proc :VARIANT
    get_onsuspend	proc :ptr
    put_ontimeupdate	proc :VARIANT
    get_ontimeupdate	proc :ptr
    put_onvolumechange	proc :VARIANT
    get_onvolumechange	proc :ptr
    put_onwaiting	proc :VARIANT
    get_onwaiting	proc :ptr
    normalize		proc
    importNode		proc :ptr, :VARIANT_BOOL, :ptr
    get_parentWindow	proc :ptr
    putref_body		proc :ptr
    get_body		proc :ptr
    get_head		proc :ptr
   .ends

endif

ifndef __IHTMLDOMNode_INTERFACE_DEFINED__
define __IHTMLDOMNode_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMNode, "3050f33b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMNode : public IDispatch

    get_nodeType	proc :ptr
    get_parentNode	proc :ptr
    hasChildNodes	proc :ptr
    get_childNodes	proc :ptr
    get_attributes	proc :ptr
    insertBefore	proc :ptr, :VARIANT, :ptr
    removeChild		proc :ptr, :ptr
    replaceChild	proc :ptr, :ptr, :ptr
    cloneNode		proc :VARIANT_BOOL, :ptr
    removeNode		proc :VARIANT_BOOL, :ptr
    swapNode		proc :ptr, :ptr
    replaceNode		proc :ptr, :ptr
    appendChild		proc :ptr, :ptr
    get_nodeName	proc :ptr
    put_nodeValue	proc :VARIANT
    get_nodeValue	proc :ptr
    get_firstChild	proc :ptr
    get_lastChild	proc :ptr
    get_previousSibling proc :ptr
    get_nextSibling	proc :ptr
   .ends

endif

ifndef __IHTMLDOMNode2_INTERFACE_DEFINED__
define __IHTMLDOMNode2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMNode2, "30510481-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMNode2 : public IDispatch

    get_ownerDocument	proc :ptr
   .ends

endif

ifndef __IHTMLDOMNode3_INTERFACE_DEFINED__
define __IHTMLDOMNode3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMNode3, "3050f557-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMNode3 : public IDispatch

    put_prefix		proc :VARIANT
    get_prefix		proc :ptr
    get_localName	proc :ptr
    get_namespaceURI	proc :ptr
    put_textContent	proc :VARIANT
    get_textContent	proc :ptr
    isEqualNode		proc :ptr, :ptr
    lookupNamespaceURI	proc :ptr, :ptr
    lookupPrefix	proc :ptr, :ptr
    isDefaultNamespace	proc :ptr, :ptr
    appendChild		proc :ptr, :ptr
    insertBefore	proc :ptr, :VARIANT, :ptr
    removeChild		proc :ptr, :ptr
    replaceChild	proc :ptr, :ptr, :ptr
    isSameNode		proc :ptr, :ptr
    compareDocumentPosition proc :ptr, :ptr
    isSupported		proc :BSTR, :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLDOMAttribute_INTERFACE_DEFINED__
define __IHTMLDOMAttribute_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMAttribute, "3050f1ff-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMAttribute : public IDispatch

    get_nodeName	proc :ptr
    put_nodeValue	proc :VARIANT
    get_nodeValue	proc :ptr
    get_specified	proc :ptr
   .ends

endif

ifndef __IHTMLDOMAttribute2_INTERFACE_DEFINED__
define __IHTMLDOMAttribute2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMAttribute2, "3050f4a3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMAttribute2 : public IDispatch

    get_name		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    get_expando		proc :ptr
    get_nodeType	proc :ptr
    get_parentNode	proc :ptr
    get_childNodes	proc :ptr
    get_firstChild	proc :ptr
    get_lastChild	proc :ptr
    get_previousSibling proc :ptr
    get_nextSibling	proc :ptr
    get_attributes	proc :ptr
    get_ownerDocument	proc :ptr
    insertBefore	proc :ptr, :VARIANT, :ptr
    replaceChild	proc :ptr, :ptr, :ptr
    removeChild		proc :ptr, :ptr
    appendChild		proc :ptr, :ptr
    hasChildNodes	proc :ptr
    cloneNode		proc :VARIANT_BOOL, :ptr
   .ends

endif

ifndef __IHTMLDOMAttribute3_INTERFACE_DEFINED__
define __IHTMLDOMAttribute3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMAttribute3, "3051076c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMAttribute3 : public IDispatch

    put_nodeValue	proc :VARIANT
    get_nodeValue	proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    get_specified	proc :ptr
    get_ownerElement	proc :ptr
   .ends

endif

ifndef __IHTMLDOMAttribute4_INTERFACE_DEFINED__
define __IHTMLDOMAttribute4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMAttribute4, "3050f4a4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMAttribute4 : public IDispatch

    put_nodeValue	proc :VARIANT
    get_nodeValue	proc :ptr
    get_nodeName	proc :ptr
    get_name		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    get_firstChild	proc :ptr
    get_lastChild	proc :ptr
    get_childNodes	proc :ptr
    hasAttributes	proc :ptr
    hasChildNodes	proc :ptr
    normalize		proc
    get_specified	proc :ptr
   .ends

endif

ifndef __IHTMLDOMTextNode_INTERFACE_DEFINED__
define __IHTMLDOMTextNode_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMTextNode, "3050f21f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMTextNode : public IDispatch

    put_data		proc :BSTR
    get_data		proc :ptr
    toString		proc :ptr
    get_length		proc :ptr
    splitText		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLDOMTextNode2_INTERFACE_DEFINED__
define __IHTMLDOMTextNode2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMTextNode2, "3050f434-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMTextNode2 : public IDispatch

    substringData	proc :LONG, :LONG, :ptr
    appendData		proc :BSTR
    insertData		proc :LONG, :BSTR
    deleteData		proc :LONG, :LONG
    replaceData		proc :LONG, :LONG, :BSTR
   .ends

endif

ifndef __IHTMLDOMTextNode3_INTERFACE_DEFINED__
define __IHTMLDOMTextNode3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMTextNode3, "30510469-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMTextNode3 : public IDispatch

    substringData	proc :LONG, :LONG, :ptr
    insertData		proc :LONG, :BSTR
    deleteData		proc :LONG, :LONG
    replaceData		proc :LONG, :LONG, :BSTR
    splitText		proc :LONG, :ptr
    get_wholeText	proc :ptr
    replaceWholeText	proc :BSTR, :ptr
    hasAttributes	proc :ptr
    normalize		proc
   .ends

endif

ifndef __IHTMLDOMImplementation_INTERFACE_DEFINED__
define __IHTMLDOMImplementation_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMImplementation, "30510738-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMImplementation : public IDispatch

    hasFeature		proc :BSTR, :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLDOMImplementation2_INTERFACE_DEFINED__
define __IHTMLDOMImplementation2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMImplementation2, "305104b8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMImplementation2 : public IDispatch

    createDocumentType	proc :BSTR, :ptr, :ptr, :ptr
    createDocument	proc :ptr, :ptr, :ptr, :ptr
    createHTMLDocument	proc :BSTR, :ptr
    hasFeature		proc :BSTR, :VARIANT, :ptr
   .ends

endif

ifndef __DispHTMLDOMAttribute_DISPINTERFACE_DEFINED__
define __DispHTMLDOMAttribute_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDOMAttribute, "3050f564-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDOMAttribute : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDOMAttribute, "3050f4b2-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLDOMTextNode_DISPINTERFACE_DEFINED__
define __DispHTMLDOMTextNode_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDOMTextNode, "3050f565-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDOMTextNode : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDOMTextNode, "3050f4ba-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLDOMImplementation_DISPINTERFACE_DEFINED__
define __DispHTMLDOMImplementation_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDOMImplementation, "3050f58f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDOMImplementation : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDOMImplementation, "3050f80e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLAttributeCollection_INTERFACE_DEFINED__
define __IHTMLAttributeCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAttributeCollection, "3050f5da-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAttributeCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr
   .ends

endif

ifndef __IHTMLAttributeCollection2_INTERFACE_DEFINED__
define __IHTMLAttributeCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAttributeCollection2, "3050f80b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAttributeCollection2 : public IDispatch

    getNamedItem	proc :BSTR, :ptr
    setNamedItem	proc :ptr, :ptr
    removeNamedItem	proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLAttributeCollection4_INTERFACE_DEFINED__
define __IHTMLAttributeCollection4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAttributeCollection4, "305106e0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAttributeCollection4 : public IDispatch

    getNamedItemNS	proc :ptr, :BSTR, :ptr
    setNamedItemNS	proc :ptr, :ptr
    removeNamedItemNS	proc :ptr, :BSTR, :ptr
    getNamedItem	proc :BSTR, :ptr
    setNamedItem	proc :ptr, :ptr
    removeNamedItem	proc :BSTR, :ptr
    item		proc :LONG, :ptr
    get_length		proc :ptr
   .ends

endif

ifndef __IHTMLDOMChildrenCollection_INTERFACE_DEFINED__
define __IHTMLDOMChildrenCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMChildrenCollection, "3050f4b0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMChildrenCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLDOMChildrenCollection2_INTERFACE_DEFINED__
define __IHTMLDOMChildrenCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMChildrenCollection2, "3050f810-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMChildrenCollection2 : public IDispatch

    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispHTMLAttributeCollection_DISPINTERFACE_DEFINED__
define __DispHTMLAttributeCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLAttributeCollection, "3050f56c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLAttributeCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLAttributeCollection, "3050f4cc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispStaticNodeList_DISPINTERFACE_DEFINED__
define __DispStaticNodeList_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispStaticNodeList, "3050f59b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispStaticNodeList : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_StaticNodeList, "30510467-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispDOMChildrenCollection_DISPINTERFACE_DEFINED__
define __DispDOMChildrenCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMChildrenCollection, "3050f577-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMChildrenCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMChildrenCollection, "3050f5aa-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLElementEvents4_DISPINTERFACE_DEFINED__
define __HTMLElementEvents4_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLElementEvents4, "3051075e-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLElementEvents4 : public IDispatch

   .ends

endif

ifndef __HTMLElementEvents3_DISPINTERFACE_DEFINED__
define __HTMLElementEvents3_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLElementEvents3, "3050f59f-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLElementEvents3 : public IDispatch

   .ends

endif

ifndef __HTMLElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLElementEvents2, "3050f60f-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLElementEvents_DISPINTERFACE_DEFINED__
define __HTMLElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLElementEvents, "3050f33c-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLElementEvents : public IDispatch

   .ends

endif

ifndef __IRulesAppliedCollection_INTERFACE_DEFINED__
define __IRulesAppliedCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IRulesAppliedCollection, "30510468-98b5-11cf-bb82-00aa00bdce0b")

.comdef IRulesAppliedCollection : public IDispatch

    item		proc :LONG, :ptr
    get_length		proc :ptr
    get_element		proc :ptr
    propertyInheritedFrom proc :BSTR, :ptr
    get_propertyCount	proc :ptr
    property		proc :LONG, :ptr
    propertyInheritedTrace proc :BSTR, :LONG, :ptr
    propertyInheritedTraceLength proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLElement3_INTERFACE_DEFINED__
define __IHTMLElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement3, "305106f9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement3 : public IDispatch

    mergeAttributes	proc :ptr
    get_isMultiLine	proc :ptr
    get_canHaveHTML	proc :ptr
    put_onlayoutcomplete proc :VARIANT
    get_onlayoutcomplete proc :ptr
    put_onpage		proc :VARIANT
    get_onpage		proc :ptr
    put_inflateBlock	proc :VARIANT_BOOL
    get_inflateBlock	proc :ptr
    put_onbeforedeactivate proc :VARIANT
    get_onbeforedeactivate proc :ptr
    setActive		proc
    put_contentEditable proc :BSTR
    get_contentEditable proc :ptr
    get_isContentEditable proc :ptr
    put_hideFocus	proc :VARIANT_BOOL
    get_hideFocus	proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_isDisabled	proc :ptr
    put_onmove		proc :VARIANT
    get_onmove		proc :ptr
    put_oncontrolselect proc :VARIANT
    get_oncontrolselect proc :ptr
    fireEvent		proc :BSTR, :ptr, :ptr
    put_onresizestart	proc :VARIANT
    get_onresizestart	proc :ptr
    put_onresizeend	proc :VARIANT
    get_onresizeend	proc :ptr
    put_onmovestart	proc :VARIANT
    get_onmovestart	proc :ptr
    put_onmoveend	proc :VARIANT
    get_onmoveend	proc :ptr
    put_onmouseenter	proc :VARIANT
    get_onmouseenter	proc :ptr
    put_onmouseleave	proc :VARIANT
    get_onmouseleave	proc :ptr
    put_onactivate	proc :VARIANT
    get_onactivate	proc :ptr
    put_ondeactivate	proc :VARIANT
    get_ondeactivate	proc :ptr
    dragDrop		proc :ptr
    get_glyphMode	proc :ptr
   .ends

endif

ifndef __IHTMLElement4_INTERFACE_DEFINED__
define __IHTMLElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement4, "3050f4b1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement4 : public IDispatch

    put_onmousewheel	proc :VARIANT
    get_onmousewheel	proc :ptr
    normalize		proc
    getAttributeNode	proc :BSTR, :ptr
    setAttributeNode	proc :ptr, :ptr
    removeAttributeNode proc :ptr, :ptr
    put_onbeforeactivate proc :VARIANT
    get_onbeforeactivate proc :ptr
    put_onfocusin	proc :VARIANT
    get_onfocusin	proc :ptr
    put_onfocusout	proc :VARIANT
    get_onfocusout	proc :ptr
   .ends

endif

ifndef __IElementSelector_INTERFACE_DEFINED__
define __IElementSelector_INTERFACE_DEFINED__
DEFINE_IIDX(IElementSelector, "3050f809-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementSelector : public IDispatch

    querySelector	proc :BSTR, :ptr
    querySelectorAll	proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLElementRender_INTERFACE_DEFINED__
define __IHTMLElementRender_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementRender, "3051073e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementRender : public IUnknown

    DrawToDC		proc :HDC
    SetDocumentPrinter	proc :BSTR, :HDC
   .ends

endif

ifndef __IHTMLUniqueName_INTERFACE_DEFINED__
define __IHTMLUniqueName_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLUniqueName, "3050f80d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLUniqueName : public IDispatch

    get_uniqueNumber	proc :ptr
    get_uniqueID	proc :ptr
   .ends

endif

ifndef __IHTMLElement5_INTERFACE_DEFINED__
define __IHTMLElement5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement5, "3051073c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement5 : public IDispatch

    getAttributeNode	proc :BSTR, :ptr
    setAttributeNode	proc :ptr, :ptr
    removeAttributeNode proc :ptr, :ptr
    hasAttribute	proc :BSTR, :ptr
    put_role		proc :BSTR
    get_role		proc :ptr
    put_ariaBusy	proc :BSTR
    get_ariaBusy	proc :ptr
    put_ariaChecked	proc :BSTR
    get_ariaChecked	proc :ptr
    put_ariaDisabled	proc :BSTR
    get_ariaDisabled	proc :ptr
    put_ariaExpanded	proc :BSTR
    get_ariaExpanded	proc :ptr
    put_ariaHaspopup	proc :BSTR
    get_ariaHaspopup	proc :ptr
    put_ariaHidden	proc :BSTR
    get_ariaHidden	proc :ptr
    put_ariaInvalid	proc :BSTR
    get_ariaInvalid	proc :ptr
    put_ariaMultiselectable proc :BSTR
    get_ariaMultiselectable proc :ptr
    put_ariaPressed	proc :BSTR
    get_ariaPressed	proc :ptr
    put_ariaReadonly	proc :BSTR
    get_ariaReadonly	proc :ptr
    put_ariaRequired	proc :BSTR
    get_ariaRequired	proc :ptr
    put_ariaSecret	proc :BSTR
    get_ariaSecret	proc :ptr
    put_ariaSelected	proc :BSTR
    get_ariaSelected	proc :ptr
    getAttribute	proc :BSTR, :ptr
    setAttribute	proc :BSTR, :VARIANT
    removeAttribute	proc :BSTR, :ptr
    get_attributes	proc :ptr
    put_ariaValuenow	proc :BSTR
    get_ariaValuenow	proc :ptr
    put_ariaPosinset	proc :sword
    get_ariaPosinset	proc :ptr
    put_ariaSetsize	proc :sword
    get_ariaSetsize	proc :ptr
    put_ariaLevel	proc :sword
    get_ariaLevel	proc :ptr
    put_ariaValuemin	proc :BSTR
    get_ariaValuemin	proc :ptr
    put_ariaValuemax	proc :BSTR
    get_ariaValuemax	proc :ptr
    put_ariaControls	proc :BSTR
    get_ariaControls	proc :ptr
    put_ariaDescribedby proc :BSTR
    get_ariaDescribedby proc :ptr
    put_ariaFlowto	proc :BSTR
    get_ariaFlowto	proc :ptr
    put_ariaLabelledby	proc :BSTR
    get_ariaLabelledby	proc :ptr
    put_ariaActivedescendant proc :BSTR
    get_ariaActivedescendant proc :ptr
    put_ariaOwns	proc :BSTR
    get_ariaOwns	proc :ptr
    hasAttributes	proc :ptr
    put_ariaLive	proc :BSTR
    get_ariaLive	proc :ptr
    put_ariaRelevant	proc :BSTR
    get_ariaRelevant	proc :ptr
   .ends

endif

ifndef __IHTMLElement6_INTERFACE_DEFINED__
define __IHTMLElement6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement6, "3050f564-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement6 : public IDispatch

    getAttributeNS	proc :ptr, :BSTR, :ptr
    setAttributeNS	proc :ptr, :BSTR, :ptr
    removeAttributeNS	proc :ptr, :BSTR
    getAttributeNodeNS	proc :ptr, :BSTR, :ptr
    setAttributeNodeNS	proc :ptr, :ptr
    hasAttributeNS	proc :ptr, :BSTR, :ptr
    getAttribute	proc :BSTR, :ptr
    setAttribute	proc :BSTR, :ptr
    removeAttribute	proc :BSTR
    getAttributeNode	proc :BSTR, :ptr
    setAttributeNode	proc :ptr, :ptr
    removeAttributeNode proc :ptr, :ptr
    hasAttribute	proc :BSTR, :ptr
    getElementsByTagNameNS proc :ptr, :BSTR, :ptr
    get_tagName		proc :ptr
    get_nodeName	proc :ptr
    getElementsByClassName proc :BSTR, :ptr
    msMatchesSelector	proc :BSTR, :ptr
    put_onabort		proc :VARIANT
    get_onabort		proc :ptr
    put_oncanplay	proc :VARIANT
    get_oncanplay	proc :ptr
    put_oncanplaythrough proc :VARIANT
    get_oncanplaythrough proc :ptr
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_ondurationchange proc :VARIANT
    get_ondurationchange proc :ptr
    put_onemptied	proc :VARIANT
    get_onemptied	proc :ptr
    put_onended		proc :VARIANT
    get_onended		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_oninput		proc :VARIANT
    get_oninput		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onloadeddata	proc :VARIANT
    get_onloadeddata	proc :ptr
    put_onloadedmetadata proc :VARIANT
    get_onloadedmetadata proc :ptr
    put_onloadstart	proc :VARIANT
    get_onloadstart	proc :ptr
    put_onpause		proc :VARIANT
    get_onpause		proc :ptr
    put_onplay		proc :VARIANT
    get_onplay		proc :ptr
    put_onplaying	proc :VARIANT
    get_onplaying	proc :ptr
    put_onprogress	proc :VARIANT
    get_onprogress	proc :ptr
    put_onratechange	proc :VARIANT
    get_onratechange	proc :ptr
    put_onreset		proc :VARIANT
    get_onreset		proc :ptr
    put_onseeked	proc :VARIANT
    get_onseeked	proc :ptr
    put_onseeking	proc :VARIANT
    get_onseeking	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_onstalled	proc :VARIANT
    get_onstalled	proc :ptr
    put_onsubmit	proc :VARIANT
    get_onsubmit	proc :ptr
    put_onsuspend	proc :VARIANT
    get_onsuspend	proc :ptr
    put_ontimeupdate	proc :VARIANT
    get_ontimeupdate	proc :ptr
    put_onvolumechange	proc :VARIANT
    get_onvolumechange	proc :ptr
    put_onwaiting	proc :VARIANT
    get_onwaiting	proc :ptr
    hasAttributes	proc :ptr
   .ends

endif

ifndef __IHTMLElement7_INTERFACE_DEFINED__
define __IHTMLElement7_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElement7, "3050f565-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElement7 : public IDispatch

    put_onmspointerdown proc :VARIANT
    get_onmspointerdown proc :ptr
    put_onmspointermove proc :VARIANT
    get_onmspointermove proc :ptr
    put_onmspointerup	proc :VARIANT
    get_onmspointerup	proc :ptr
    put_onmspointerover proc :VARIANT
    get_onmspointerover proc :ptr
    put_onmspointerout	proc :VARIANT
    get_onmspointerout	proc :ptr
    put_onmspointercancel proc :VARIANT
    get_onmspointercancel proc :ptr
    put_onmspointerhover proc :VARIANT
    get_onmspointerhover proc :ptr
    put_onmslostpointercapture proc :VARIANT
    get_onmslostpointercapture proc :ptr
    put_onmsgotpointercapture proc :VARIANT
    get_onmsgotpointercapture proc :ptr
    put_onmsgesturestart proc :VARIANT
    get_onmsgesturestart proc :ptr
    put_onmsgesturechange proc :VARIANT
    get_onmsgesturechange proc :ptr
    put_onmsgestureend	proc :VARIANT
    get_onmsgestureend	proc :ptr
    put_onmsgesturehold proc :VARIANT
    get_onmsgesturehold proc :ptr
    put_onmsgesturetap	proc :VARIANT
    get_onmsgesturetap	proc :ptr
    put_onmsgesturedoubletap proc :VARIANT
    get_onmsgesturedoubletap proc :ptr
    put_onmsinertiastart proc :VARIANT
    get_onmsinertiastart proc :ptr
    msSetPointerCapture proc :LONG
    msReleasePointerCapture proc :LONG
    put_onmstransitionstart proc :VARIANT
    get_onmstransitionstart proc :ptr
    put_onmstransitionend proc :VARIANT
    get_onmstransitionend proc :ptr
    put_onmsanimationstart proc :VARIANT
    get_onmsanimationstart proc :ptr
    put_onmsanimationend proc :VARIANT
    get_onmsanimationend proc :ptr
    put_onmsanimationiteration proc :VARIANT
    get_onmsanimationiteration proc :ptr
    put_oninvalid	proc :VARIANT
    get_oninvalid	proc :ptr
    put_xmsAcceleratorKey proc :BSTR
    get_xmsAcceleratorKey proc :ptr
    put_spellcheck	proc :VARIANT
    get_spellcheck	proc :ptr
    put_onmsmanipulationstatechanged proc :VARIANT
    get_onmsmanipulationstatechanged proc :ptr
    put_oncuechange	proc :VARIANT
    get_oncuechange	proc :ptr
   .ends

endif

ifndef __IHTMLElementAppliedStyles_INTERFACE_DEFINED__
define __IHTMLElementAppliedStyles_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementAppliedStyles, "3050f58f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementAppliedStyles : public IDispatch

    msGetRulesApplied	proc :ptr
    msGetRulesAppliedWithAncestor proc :VARIANT, :ptr
   .ends

endif

ifndef __IElementTraversal_INTERFACE_DEFINED__
define __IElementTraversal_INTERFACE_DEFINED__
DEFINE_IIDX(IElementTraversal, "3050f4c3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementTraversal : public IDispatch

    get_firstElementChild proc :ptr
    get_lastElementChild proc :ptr
    get_previousElementSibling proc :ptr
    get_nextElementSibling proc :ptr
    get_childElementCount proc :ptr
   .ends

endif

ifndef __IHTMLDatabinding_INTERFACE_DEFINED__
define __IHTMLDatabinding_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDatabinding, "3050f80a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDatabinding : public IDispatch

    put_dataFld		proc :BSTR
    get_dataFld		proc :ptr
    put_dataSrc		proc :BSTR
    get_dataSrc		proc :ptr
    put_dataFormatAs	proc :BSTR
    get_dataFormatAs	proc :ptr
   .ends

endif

ifndef __IHTMLDocument_INTERFACE_DEFINED__
define __IHTMLDocument_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument, "305106fa-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument : public IDispatch

    get_Script		proc :ptr
   .ends

endif

ifndef __IHTMLElementDefaults_INTERFACE_DEFINED__
define __IHTMLElementDefaults_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementDefaults, "3050f5ab-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementDefaults : public IDispatch

    get_style		proc :ptr
    put_tabStop		proc :VARIANT_BOOL
    get_tabStop		proc :ptr
    put_viewInheritStyle proc :VARIANT_BOOL
    get_viewInheritStyle proc :ptr
    put_viewMasterTab	proc :VARIANT_BOOL
    get_viewMasterTab	proc :ptr
    put_scrollSegmentX	proc :LONG
    get_scrollSegmentX	proc :ptr
    put_scrollSegmentY	proc :LONG
    get_scrollSegmentY	proc :ptr
    put_isMultiLine	proc :VARIANT_BOOL
    get_isMultiLine	proc :ptr
    put_contentEditable proc :BSTR
    get_contentEditable proc :ptr
    put_canHaveHTML	proc :VARIANT_BOOL
    get_canHaveHTML	proc :ptr
    putref_viewLink	proc :ptr
    get_viewLink	proc :ptr
    put_frozen		proc :VARIANT_BOOL
    get_frozen		proc :ptr
   .ends

endif

ifndef __DispHTMLDefaults_DISPINTERFACE_DEFINED__
define __DispHTMLDefaults_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDefaults, "3050f58c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDefaults : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDefaults, "3050f6c8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTCDefaultDispatch_INTERFACE_DEFINED__
define __IHTCDefaultDispatch_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCDefaultDispatch, "30510791-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCDefaultDispatch : public IDispatch

    get_element		proc :ptr
    createEventObject	proc :ptr
    get_defaults	proc :ptr
    get_document	proc :ptr
   .ends

endif

ifndef __IHTCPropertyBehavior_INTERFACE_DEFINED__
define __IHTCPropertyBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCPropertyBehavior, "3050f56c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCPropertyBehavior : public IDispatch

    fireChange		proc
    put_value		proc :VARIANT
    get_value		proc :ptr
   .ends

endif

ifndef __IHTCMethodBehavior_INTERFACE_DEFINED__
define __IHTCMethodBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCMethodBehavior, "3050f59b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCMethodBehavior : public IDispatch

   .ends

endif

ifndef __IHTCEventBehavior_INTERFACE_DEFINED__
define __IHTCEventBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCEventBehavior, "3050f577-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCEventBehavior : public IDispatch

    fire		proc :ptr
   .ends

endif

ifndef __IHTCAttachBehavior_INTERFACE_DEFINED__
define __IHTCAttachBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCAttachBehavior, "3051075e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCAttachBehavior : public IDispatch

    fireEvent		proc :ptr
    detachEvent		proc
   .ends

endif

ifndef __IHTCAttachBehavior2_INTERFACE_DEFINED__
define __IHTCAttachBehavior2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCAttachBehavior2, "3050f59f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCAttachBehavior2 : public IDispatch

    fireEvent		proc :VARIANT
   .ends

endif

ifndef __IHTCDescBehavior_INTERFACE_DEFINED__
define __IHTCDescBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IHTCDescBehavior, "3050f60f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTCDescBehavior : public IDispatch

    get_urn		proc :ptr
    get_name		proc :ptr
   .ends

endif

ifndef __DispHTCDefaultDispatch_DISPINTERFACE_DEFINED__
define __DispHTCDefaultDispatch_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTCDefaultDispatch, "3050f573-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTCDefaultDispatch : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTCDefaultDispatch, "3050f4fc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTCPropertyBehavior_DISPINTERFACE_DEFINED__
define __DispHTCPropertyBehavior_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTCPropertyBehavior, "3050f57f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTCPropertyBehavior : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTCPropertyBehavior, "3050f5de-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTCMethodBehavior_DISPINTERFACE_DEFINED__
define __DispHTCMethodBehavior_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTCMethodBehavior, "3050f587-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTCMethodBehavior : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTCMethodBehavior, "3050f630-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTCEventBehavior_DISPINTERFACE_DEFINED__
define __DispHTCEventBehavior_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTCEventBehavior, "3050f574-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTCEventBehavior : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTCEventBehavior, "3050f4fe-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTCAttachBehavior_DISPINTERFACE_DEFINED__
define __DispHTCAttachBehavior_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTCAttachBehavior, "3050f583-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTCAttachBehavior : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTCAttachBehavior, "3050f5f5-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTCDescBehavior_DISPINTERFACE_DEFINED__
define __DispHTCDescBehavior_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTCDescBehavior, "3050f57e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTCDescBehavior : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTCDescBehavior, "3050f5dd-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLUrnCollection_INTERFACE_DEFINED__
define __IHTMLUrnCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLUrnCollection, "3050f33c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLUrnCollection : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispHTMLUrnCollection_DISPINTERFACE_DEFINED__
define __DispHTMLUrnCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLUrnCollection, "3050f551-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLUrnCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLUrnCollection, "3050f580-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLGenericElement_INTERFACE_DEFINED__
define __IHTMLGenericElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLGenericElement, "305104be-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLGenericElement : public IDispatch

    get_recordset	proc :ptr
    namedRecordset	proc :BSTR, :ptr, :ptr
   .ends

endif

ifndef __DispHTMLGenericElement_DISPINTERFACE_DEFINED__
define __DispHTMLGenericElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLGenericElement, "3050f563-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLGenericElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLGenericElement, "3050f4b8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleSheetRuleApplied_INTERFACE_DEFINED__
define __IHTMLStyleSheetRuleApplied_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetRuleApplied, "3050f673-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetRuleApplied : public IDispatch

    get_msSpecificity	proc :ptr
    msGetSpecificity	proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLStyleSheetRule2_INTERFACE_DEFINED__
define __IHTMLStyleSheetRule2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetRule2, "3050f80f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetRule2 : public IDispatch

    put_selectorText	proc :BSTR
    get_selectorText	proc :ptr
   .ends

endif

ifndef __IHTMLStyleSheetRulesCollection2_INTERFACE_DEFINED__
define __IHTMLStyleSheetRulesCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetRulesCollection2, "30510463-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetRulesCollection2 : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispHTMLStyleSheetRule_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheetRule_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheetRule, "3050f50e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheetRule : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheetRule, "3050f3ce-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLStyleSheetRulesCollection_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheetRulesCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheetRulesCollection, "3050f52f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheetRulesCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheetRulesCollection, "3050f3cd-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleSheetPage_INTERFACE_DEFINED__
define __IHTMLStyleSheetPage_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetPage, "3050f669-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetPage : public IDispatch

    get_selector	proc :ptr
    get_pseudoClass	proc :ptr
   .ends

endif

ifndef __IHTMLStyleSheetPage2_INTERFACE_DEFINED__
define __IHTMLStyleSheetPage2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetPage2, "3050f4d0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetPage2 : public IDispatch

    put_selectorText	proc :BSTR
    get_selectorText	proc :ptr
    get_style		proc :ptr
   .ends

endif

ifndef __IHTMLStyleSheetPagesCollection_INTERFACE_DEFINED__
define __IHTMLStyleSheetPagesCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetPagesCollection, "3051045d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetPagesCollection : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispHTMLStyleSheetPage_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheetPage_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheetPage, "3050f540-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheetPage : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheetPage, "3050f7ef-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLStyleSheetPagesCollection_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheetPagesCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheetPagesCollection, "3050f543-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheetPagesCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheetPagesCollection, "3050f7f1-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleSheetsCollection_INTERFACE_DEFINED__
define __IHTMLStyleSheetsCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetsCollection, "305106f8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetsCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr
   .ends

endif

ifndef __IHTMLStyleSheet2_INTERFACE_DEFINED__
define __IHTMLStyleSheet2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheet2, "305107aa-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheet2 : public IDispatch

    get_pages		proc :ptr
    addPageRule		proc :BSTR, :BSTR, :LONG, :ptr
   .ends

endif

ifndef __IHTMLStyleSheet3_INTERFACE_DEFINED__
define __IHTMLStyleSheet3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheet3, "305104bd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheet3 : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
    get_isAlternate	proc :ptr
    get_isPrefAlternate proc :ptr
   .ends

endif

ifndef __IHTMLStyleSheet4_INTERFACE_DEFINED__
define __IHTMLStyleSheet4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheet4, "30510736-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheet4 : public IDispatch

    get_type		proc :ptr
    get_href		proc :ptr
    get_title		proc :ptr
    get_ownerNode	proc :ptr
    get_ownerRule	proc :ptr
    get_cssRules	proc :ptr
    get_media		proc :ptr
    insertRule		proc :BSTR, :LONG, :ptr
    deleteRule		proc :LONG
   .ends

endif

ifndef __DispHTMLStyleSheet_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheet_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheet, "3050f58d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheet : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheet, "3050f2e4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleSheetsCollection2_INTERFACE_DEFINED__
define __IHTMLStyleSheetsCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetsCollection2, "3050f3f2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetsCollection2 : public IDispatch

    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispHTMLStyleSheetsCollection_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheetsCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheetsCollection, "3050f547-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheetsCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheetsCollection, "3050f37f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLLinkElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLLinkElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLLinkElementEvents2, "3050f61d-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLLinkElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLLinkElementEvents_DISPINTERFACE_DEFINED__
define __HTMLLinkElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLLinkElementEvents, "3050f3cc-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLLinkElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLLinkElement_INTERFACE_DEFINED__
define __IHTMLLinkElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLinkElement, "626FC520-A41E-11cf-A731-00A0C9082637")

.comdef IHTMLLinkElement : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
    put_rel		proc :BSTR
    get_rel		proc :ptr
    put_rev		proc :BSTR
    get_rev		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
    get_readyState	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    get_styleSheet	proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    put_media		proc :BSTR
    get_media		proc :ptr
   .ends

endif

ifndef __IHTMLLinkElement2_INTERFACE_DEFINED__
define __IHTMLLinkElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLinkElement2, "3050f6c9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLinkElement2 : public IDispatch

    put_target		proc :BSTR
    get_target		proc :ptr
   .ends

endif

ifndef __IHTMLLinkElement3_INTERFACE_DEFINED__
define __IHTMLLinkElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLinkElement3, "3050f58c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLinkElement3 : public IDispatch

    put_charset		proc :BSTR
    get_charset		proc :ptr
    put_hreflang	proc :BSTR
    get_hreflang	proc :ptr
   .ends

endif

ifndef __IHTMLLinkElement4_INTERFACE_DEFINED__
define __IHTMLLinkElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLinkElement4, "3050f4fd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLinkElement4 : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
   .ends

endif

ifndef __IHTMLLinkElement5_INTERFACE_DEFINED__
define __IHTMLLinkElement5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLinkElement5, "3050f5df-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLinkElement5 : public IDispatch

    get_sheet		proc :ptr
   .ends

endif

ifndef __DispHTMLLinkElement_DISPINTERFACE_DEFINED__
define __DispHTMLLinkElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLLinkElement, "3050f524-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLLinkElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLLinkElement, "3050f277-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLTxtRange_INTERFACE_DEFINED__
define __IHTMLTxtRange_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTxtRange, "3050f631-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTxtRange : public IDispatch

    get_htmlText	proc :ptr
    put_text		proc :BSTR
    get_text		proc :ptr
    parentElement	proc :ptr
    duplicate		proc :ptr
    inRange		proc :ptr, :ptr
    isEqual		proc :ptr, :ptr
    scrollIntoView	proc :VARIANT_BOOL
    collapse		proc :VARIANT_BOOL
    expand		proc :BSTR, :ptr
    move		proc :BSTR, :LONG, :ptr
    moveStart		proc :BSTR, :LONG, :ptr
    moveEnd		proc :BSTR, :LONG, :ptr
    select		proc
    pasteHTML		proc :BSTR
    moveToElementText	proc :ptr
    setEndPoint		proc :BSTR, :ptr
    compareEndPoints	proc :BSTR, :ptr, :ptr
    findText		proc :BSTR, :LONG, :LONG, :ptr
    moveToPoint		proc :LONG, :LONG
    getBookmark		proc :ptr
    moveToBookmark	proc :BSTR, :ptr
    queryCommandSupported proc :BSTR, :ptr
    queryCommandEnabled proc :BSTR, :ptr
    queryCommandState	proc :BSTR, :ptr
    queryCommandIndeterm proc :BSTR, :ptr
    queryCommandText	proc :BSTR, :ptr
    queryCommandValue	proc :BSTR, :ptr
    execCommand		proc :BSTR, :VARIANT_BOOL, :VARIANT, :ptr
    execCommandShowHelp proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLTextRangeMetrics_INTERFACE_DEFINED__
define __IHTMLTextRangeMetrics_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTextRangeMetrics, "3050f4ff-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTextRangeMetrics : public IDispatch

    get_offsetTop	proc :ptr
    get_offsetLeft	proc :ptr
    get_boundingTop	proc :ptr
    get_boundingLeft	proc :ptr
    get_boundingWidth	proc :ptr
    get_boundingHeight	proc :ptr
   .ends

endif

ifndef __IHTMLTextRangeMetrics2_INTERFACE_DEFINED__
define __IHTMLTextRangeMetrics2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTextRangeMetrics2, "3050f5f4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTextRangeMetrics2 : public IDispatch

    getClientRects	proc :ptr
    getBoundingClientRect proc :ptr
   .ends

endif

ifndef __IHTMLTxtRangeCollection_INTERFACE_DEFINED__
define __IHTMLTxtRangeCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTxtRangeCollection, "3050f7eb-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTxtRangeCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :ptr, :ptr
   .ends

endif

ifndef __IHTMLDOMRange_INTERFACE_DEFINED__
define __IHTMLDOMRange_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMRange, "3050f5dc-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMRange : public IDispatch

    get_startContainer	proc :ptr
    get_startOffset	proc :ptr
    get_endContainer	proc :ptr
    get_endOffset	proc :ptr
    get_collapsed	proc :ptr
    get_commonAncestorContainer proc :ptr
    setStart		proc :ptr, :LONG
    setEnd		proc :ptr, :LONG
    setStartBefore	proc :ptr
    setStartAfter	proc :ptr
    setEndBefore	proc :ptr
    setEndAfter		proc :ptr
    collapse		proc :VARIANT_BOOL
    selectNode		proc :ptr
    selectNodeContents	proc :ptr
    compareBoundaryPoints proc :sword, :ptr, :ptr
    deleteContents	proc
    extractContents	proc :ptr
    cloneContents	proc :ptr
    insertNode		proc :ptr
    surroundContents	proc :ptr
    cloneRange		proc :ptr
    toString		proc :ptr
    detach		proc
    getClientRects	proc :ptr
    getBoundingClientRect proc :ptr
   .ends

endif

ifndef __DispHTMLDOMRange_DISPINTERFACE_DEFINED__
define __DispHTMLDOMRange_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDOMRange, "3050f5a3-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDOMRange : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDOMRange, "305106C3-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLFormElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLFormElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLFormElementEvents2, "3050f614-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLFormElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLFormElementEvents_DISPINTERFACE_DEFINED__
define __HTMLFormElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLFormElementEvents, "3050f364-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLFormElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLFormElement_INTERFACE_DEFINED__
define __IHTMLFormElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFormElement, "3050f573-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFormElement : public IDispatch

    put_action		proc :BSTR
    get_action		proc :ptr
    put_dir		proc :BSTR
    get_dir		proc :ptr
    put_encoding	proc :BSTR
    get_encoding	proc :ptr
    put_method		proc :BSTR
    get_method		proc :ptr
    get_elements	proc :ptr
    put_target		proc :BSTR
    get_target		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_onsubmit	proc :VARIANT
    get_onsubmit	proc :ptr
    put_onreset		proc :VARIANT
    get_onreset		proc :ptr
    submit		proc
    reset		proc
    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :VARIANT, :VARIANT, :ptr
    tags		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLFormElement2_INTERFACE_DEFINED__
define __IHTMLFormElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFormElement2, "3050f57f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFormElement2 : public IDispatch

    put_acceptCharset	proc :BSTR
    get_acceptCharset	proc :ptr
    urns		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLFormElement3_INTERFACE_DEFINED__
define __IHTMLFormElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFormElement3, "3050f587-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFormElement3 : public IDispatch

    namedItem		proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLSubmitData_INTERFACE_DEFINED__
define __IHTMLSubmitData_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSubmitData, "3050f574-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSubmitData : public IDispatch

    appendNameValuePair proc :BSTR, :BSTR
    appendNameFilePair	proc :BSTR, :BSTR
    appendItemSeparator proc
   .ends

endif

ifndef __IHTMLFormElement4_INTERFACE_DEFINED__
define __IHTMLFormElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFormElement4, "3050f583-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFormElement4 : public IDispatch

    put_action		proc :BSTR
    get_action		proc :ptr
   .ends

endif

ifndef __DispHTMLFormElement_DISPINTERFACE_DEFINED__
define __DispHTMLFormElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLFormElement, "3050f510-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLFormElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLFormElement, "3050f251-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLControlElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLControlElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLControlElementEvents2, "3050f612-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLControlElementEvents2 : public IDispatch

   .ends

endif
ifndef __HTMLControlElementEvents_DISPINTERFACE_DEFINED__
define __HTMLControlElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLControlElementEvents, "3050f4ea-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLControlElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLControlElement_INTERFACE_DEFINED__
define __IHTMLControlElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLControlElement, "3050f57e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLControlElement : public IDispatch

    put_tabIndex	proc :sword
    get_tabIndex	proc :ptr
    focus		proc
    put_accessKey	proc :BSTR
    get_accessKey	proc :ptr
    put_onblur		proc :VARIANT
    get_onblur		proc :ptr
    put_onfocus		proc :VARIANT
    get_onfocus		proc :ptr
    put_onresize	proc :VARIANT
    get_onresize	proc :ptr
    blur		proc
    addFilter		proc :ptr
    removeFilter	proc :ptr
    get_clientHeight	proc :ptr
    get_clientWidth	proc :ptr
    get_clientTop	proc :ptr
    get_clientLeft	proc :ptr
   .ends

endif

ifndef __IHTMLTextElement_INTERFACE_DEFINED__
define __IHTMLTextElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTextElement, "3050f5e2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTextElement : public IDispatch

   .ends

endif
ifndef __DispHTMLTextElement_DISPINTERFACE_DEFINED__
define __DispHTMLTextElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTextElement, "3050f537-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTextElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTextElement, "3050f26a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLTextContainerEvents2_DISPINTERFACE_DEFINED__
define __HTMLTextContainerEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLTextContainerEvents2, "3050f624-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLTextContainerEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLTextContainerEvents_DISPINTERFACE_DEFINED__
define __HTMLTextContainerEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLTextContainerEvents, "1FF6AA72-5842-11cf-A707-00AA00C0098D")

.comdef HTMLTextContainerEvents : public IDispatch

   .ends

endif

ifndef __IHTMLTextContainer_INTERFACE_DEFINED__
define __IHTMLTextContainer_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTextContainer, "3050f551-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTextContainer : public IDispatch

    createControlRange	proc :ptr
    get_scrollHeight	proc :ptr
    get_scrollWidth	proc :ptr
    put_scrollTop	proc :LONG
    get_scrollTop	proc :ptr
    put_scrollLeft	proc :LONG
    get_scrollLeft	proc :ptr
    put_onscroll	proc :VARIANT
    get_onscroll	proc :ptr
   .ends

endif

ifndef __IHTMLControlRange_INTERFACE_DEFINED__
define __IHTMLControlRange_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLControlRange, "3050f4b7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLControlRange : public IDispatch

    select		proc
    _add		proc :ptr
    remove		proc :LONG
    item		proc :LONG, :ptr
    scrollIntoView	proc :VARIANT
    queryCommandSupported proc :BSTR, :ptr
    queryCommandEnabled proc :BSTR, :ptr
    queryCommandState	proc :BSTR, :ptr
    queryCommandIndeterm proc :BSTR, :ptr
    queryCommandText	proc :BSTR, :ptr
    queryCommandValue	proc :BSTR, :ptr
    execCommand		proc :BSTR, :VARIANT_BOOL, :VARIANT, :ptr
    execCommandShowHelp proc :BSTR, :ptr
    commonParentElement proc :ptr
    get_length		proc :ptr
   .ends

endif

ifndef __IHTMLControlRange2_INTERFACE_DEFINED__
define __IHTMLControlRange2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLControlRange2, "3050f563-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLControlRange2 : public IDispatch

    addElement		proc :ptr
   .ends

endif

ifndef __HTMLImgEvents2_DISPINTERFACE_DEFINED__
define __HTMLImgEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLImgEvents2, "3050f616-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLImgEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLImgEvents_DISPINTERFACE_DEFINED__
define __HTMLImgEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLImgEvents, "3050f25b-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLImgEvents : public IDispatch

   .ends

endif

ifndef __IHTMLImgElement_INTERFACE_DEFINED__
define __IHTMLImgElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLImgElement, "305104c1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLImgElement : public IDispatch

    put_isMap		proc :VARIANT_BOOL
    get_isMap		proc :ptr
    put_useMap		proc :BSTR
    get_useMap		proc :ptr
    get_mimeType	proc :ptr
    get_fileSize	proc :ptr
    get_fileCreatedDate proc :ptr
    get_fileModifiedDate proc :ptr
    get_fileUpdatedDate proc :ptr
    get_protocol	proc :ptr
    get_href		proc :ptr
    get_nameProp	proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_vspace		proc :LONG
    get_vspace		proc :ptr
    put_hspace		proc :LONG
    get_hspace		proc :ptr
    put_alt		proc :BSTR
    get_alt		proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    put_lowsrc		proc :BSTR
    get_lowsrc		proc :ptr
    put_vrml		proc :BSTR
    get_vrml		proc :ptr
    put_dynsrc		proc :BSTR
    get_dynsrc		proc :ptr
    get_readyState	proc :ptr
    get_complete	proc :ptr
    put_loop		proc :VARIANT
    get_loop		proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_onabort		proc :VARIANT
    get_onabort		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_width		proc :LONG
    get_width		proc :ptr
    put_height		proc :LONG
    get_height		proc :ptr
    put_start		proc :BSTR
    get_start		proc :ptr
   .ends

endif

ifndef __IHTMLImgElement2_INTERFACE_DEFINED__
define __IHTMLImgElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLImgElement2, "305106fd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLImgElement2 : public IDispatch

    put_longDesc	proc :BSTR
    get_longDesc	proc :ptr
   .ends

endif

ifndef __IHTMLImgElement3_INTERFACE_DEFINED__
define __IHTMLImgElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLImgElement3, "305106e8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLImgElement3 : public IDispatch

    put_longDesc	proc :BSTR
    get_longDesc	proc :ptr
    put_vrml		proc :BSTR
    get_vrml		proc :ptr
    put_lowsrc		proc :BSTR
    get_lowsrc		proc :ptr
    put_dynsrc		proc :BSTR
    get_dynsrc		proc :ptr
   .ends

endif

ifndef __IHTMLImgElement4_INTERFACE_DEFINED__
define __IHTMLImgElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLImgElement4, "3050f50e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLImgElement4 : public IDispatch

    get_naturalWidth	proc :ptr
    get_naturalHeight	proc :ptr
   .ends

endif

ifndef __IHTMLMSImgElement_INTERFACE_DEFINED__
define __IHTMLMSImgElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMSImgElement, "3050f52f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMSImgElement : public IDispatch

    put_msPlayToDisabled proc :VARIANT_BOOL
    get_msPlayToDisabled proc :ptr
    put_msPlayToPrimary proc :VARIANT_BOOL
    get_msPlayToPrimary proc :ptr
   .ends

endif

ifndef __IHTMLImageElementFactory_INTERFACE_DEFINED__
define __IHTMLImageElementFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLImageElementFactory, "3050f7ee-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLImageElementFactory : public IDispatch

    create		proc :VARIANT, :VARIANT, :ptr
   .ends

endif

ifndef __DispHTMLImg_DISPINTERFACE_DEFINED__
define __DispHTMLImg_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLImg, "3050f51c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLImg : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLImg, "3050f241-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_HTMLImageElementFactory, "3050f38f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLBodyElement_INTERFACE_DEFINED__
define __IHTMLBodyElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBodyElement, "305106ed-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBodyElement : public IDispatch

    put_background	proc :BSTR
    get_background	proc :ptr
    put_bgProperties	proc :BSTR
    get_bgProperties	proc :ptr
    put_leftMargin	proc :VARIANT
    get_leftMargin	proc :ptr
    put_topMargin	proc :VARIANT
    get_topMargin	proc :ptr
    put_rightMargin	proc :VARIANT
    get_rightMargin	proc :ptr
    put_bottomMargin	proc :VARIANT
    get_bottomMargin	proc :ptr
    put_noWrap		proc :VARIANT_BOOL
    get_noWrap		proc :ptr
    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    put_text		proc :VARIANT
    get_text		proc :ptr
    put_link		proc :VARIANT
    get_link		proc :ptr
    put_vLink		proc :VARIANT
    get_vLink		proc :ptr
    put_aLink		proc :VARIANT
    get_aLink		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onunload	proc :VARIANT
    get_onunload	proc :ptr
    put_scroll		proc :BSTR
    get_scroll		proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_onbeforeunload	proc :VARIANT
    get_onbeforeunload	proc :ptr
    createTextRange	proc :ptr
   .ends

endif

ifndef __IHTMLBodyElement2_INTERFACE_DEFINED__
define __IHTMLBodyElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBodyElement2, "3050f7f0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBodyElement2 : public IDispatch

    put_onbeforeprint	proc :VARIANT
    get_onbeforeprint	proc :ptr
    put_onafterprint	proc :VARIANT
    get_onafterprint	proc :ptr
   .ends

endif

ifndef __IHTMLBodyElement3_INTERFACE_DEFINED__
define __IHTMLBodyElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBodyElement3, "3050f540-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBodyElement3 : public IDispatch

    put_background	proc :BSTR
    get_background	proc :ptr
    put_ononline	proc :VARIANT
    get_ononline	proc :ptr
    put_onoffline	proc :VARIANT
    get_onoffline	proc :ptr
    put_onhashchange	proc :VARIANT
    get_onhashchange	proc :ptr
   .ends

endif

ifndef __IHTMLBodyElement4_INTERFACE_DEFINED__
define __IHTMLBodyElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBodyElement4, "3050f543-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBodyElement4 : public IDispatch

    put_onmessage	proc :VARIANT
    get_onmessage	proc :ptr
    put_onstorage	proc :VARIANT
    get_onstorage	proc :ptr
   .ends

endif

ifndef __IHTMLBodyElement5_INTERFACE_DEFINED__
define __IHTMLBodyElement5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBodyElement5, "3050f37e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBodyElement5 : public IDispatch

    put_onpopstate	proc :VARIANT
    get_onpopstate	proc :ptr
   .ends

endif

ifndef __DispHTMLBody_DISPINTERFACE_DEFINED__
define __DispHTMLBody_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLBody, "3050f507-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLBody : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLBody, "3050f24a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLFontElement_INTERFACE_DEFINED__
define __IHTMLFontElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFontElement, "3050f3d1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFontElement : public IDispatch

    put_color		proc :VARIANT
    get_color		proc :ptr
    put_face		proc :BSTR
    get_face		proc :ptr
    put_size		proc :VARIANT
    get_size		proc :ptr
   .ends

endif

ifndef __DispHTMLFontElement_DISPINTERFACE_DEFINED__
define __DispHTMLFontElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLFontElement, "3050f512-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLFontElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLFontElement, "3050f27b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLAnchorEvents2_DISPINTERFACE_DEFINED__
define __HTMLAnchorEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLAnchorEvents2, "3050f610-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLAnchorEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLAnchorEvents_DISPINTERFACE_DEFINED__
define __HTMLAnchorEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLAnchorEvents, "3050f29d-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLAnchorEvents : public IDispatch

   .ends

endif

ifndef __IHTMLAnchorElement_INTERFACE_DEFINED__
define __IHTMLAnchorElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAnchorElement, "30510496-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAnchorElement : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
    put_target		proc :BSTR
    get_target		proc :ptr
    put_rel		proc :BSTR
    get_rel		proc :ptr
    put_rev		proc :BSTR
    get_rev		proc :ptr
    put_urn		proc :BSTR
    get_urn		proc :ptr
    put_Methods		proc :BSTR
    get_Methods		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_host		proc :BSTR
    get_host		proc :ptr
    put_hostname	proc :BSTR
    get_hostname	proc :ptr
    put_pathname	proc :BSTR
    get_pathname	proc :ptr
    put_port		proc :BSTR
    get_port		proc :ptr
    put_protocol	proc :BSTR
    get_protocol	proc :ptr
    put_search		proc :BSTR
    get_search		proc :ptr
    put_hash		proc :BSTR
    get_hash		proc :ptr
    put_onblur		proc :VARIANT
    get_onblur		proc :ptr
    put_onfocus		proc :VARIANT
    get_onfocus		proc :ptr
    put_accessKey	proc :BSTR
    get_accessKey	proc :ptr
    get_protocolLong	proc :ptr
    get_mimeType	proc :ptr
    get_nameProp	proc :ptr
    put_tabIndex	proc :sword
    get_tabIndex	proc :ptr
    focus		proc
    blur		proc
   .ends

endif

ifndef __IHTMLAnchorElement2_INTERFACE_DEFINED__
define __IHTMLAnchorElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAnchorElement2, "305106f4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAnchorElement2 : public IDispatch

    put_charset		proc :BSTR
    get_charset		proc :ptr
    put_coords		proc :BSTR
    get_coords		proc :ptr
    put_hreflang	proc :BSTR
    get_hreflang	proc :ptr
    put_shape		proc :BSTR
    get_shape		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
   .ends

endif

ifndef __IHTMLAnchorElement3_INTERFACE_DEFINED__
define __IHTMLAnchorElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAnchorElement3, "3050f58d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAnchorElement3 : public IDispatch

    put_shape		proc :BSTR
    get_shape		proc :ptr
    put_coords		proc :BSTR
    get_coords		proc :ptr
    put_href		proc :BSTR
    get_href		proc :ptr
   .ends

endif

ifndef __DispHTMLAnchorElement_DISPINTERFACE_DEFINED__
define __DispHTMLAnchorElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLAnchorElement, "3050f502-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLAnchorElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLAnchorElement, "3050f248-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLLabelEvents2_DISPINTERFACE_DEFINED__
define __HTMLLabelEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLLabelEvents2, "3050f61c-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLLabelEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLLabelEvents_DISPINTERFACE_DEFINED__
define __HTMLLabelEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLLabelEvents, "3050f329-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLLabelEvents : public IDispatch

   .ends

endif

ifndef __IHTMLLabelElement_INTERFACE_DEFINED__
define __IHTMLLabelElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLabelElement, "305106e7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLabelElement : public IDispatch

    put_htmlFor		proc :BSTR
    get_htmlFor		proc :ptr
    put_accessKey	proc :BSTR
    get_accessKey	proc :ptr
   .ends

endif

ifndef __IHTMLLabelElement2_INTERFACE_DEFINED__
define __IHTMLLabelElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLabelElement2, "3050f547-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLabelElement2 : public IDispatch

    get_form		proc :ptr
   .ends

endif

ifndef __DispHTMLLabelElement_DISPINTERFACE_DEFINED__
define __DispHTMLLabelElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLLabelElement, "3050f522-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLLabelElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLLabelElement, "3050f32b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLListElement_INTERFACE_DEFINED__
define __IHTMLListElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLListElement, "3050f61d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLListElement : public IDispatch

   .ends

endif

ifndef __IHTMLListElement2_INTERFACE_DEFINED__
define __IHTMLListElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLListElement2, "3050f3cc-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLListElement2 : public IDispatch

    put_compact		proc :VARIANT_BOOL
    get_compact		proc :ptr
   .ends

endif

ifndef __DispHTMLListElement_DISPINTERFACE_DEFINED__
define __DispHTMLListElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLListElement, "3050f525-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLListElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLListElement, "3050f272-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLUListElement_INTERFACE_DEFINED__
define __IHTMLUListElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLUListElement, "3050f205-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLUListElement : public IDispatch

    put_compact		proc :VARIANT_BOOL
    get_compact		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
   .ends

endif

ifndef __DispHTMLUListElement_DISPINTERFACE_DEFINED__
define __DispHTMLUListElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLUListElement, "3050f538-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLUListElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLUListElement, "3050f269-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLOListElement_INTERFACE_DEFINED__
define __IHTMLOListElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOListElement, "3050f4e5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOListElement : public IDispatch

    put_compact		proc :VARIANT_BOOL
    get_compact		proc :ptr
    put_start		proc :LONG
    get_start		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
   .ends

endif

ifndef __DispHTMLOListElement_DISPINTERFACE_DEFINED__
define __DispHTMLOListElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLOListElement, "3050f52a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLOListElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLOListElement, "3050f270-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLLIElement_INTERFACE_DEFINED__
define __IHTMLLIElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLIElement, "3050f81e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLIElement : public IDispatch

    put_type		proc :BSTR
    get_type		proc :ptr
    put_value		proc :LONG
    get_value		proc :ptr
   .ends

endif

ifndef __DispHTMLLIElement_DISPINTERFACE_DEFINED__
define __DispHTMLLIElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLLIElement, "3050f523-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLLIElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLLIElement, "3050f273-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLBlockElement_INTERFACE_DEFINED__
define __IHTMLBlockElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBlockElement, "3051043a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBlockElement : public IDispatch

    put_clear		proc :BSTR
    get_clear		proc :ptr
   .ends

endif

ifndef __IHTMLBlockElement2_INTERFACE_DEFINED__
define __IHTMLBlockElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBlockElement2, "30510726-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBlockElement2 : public IDispatch

    put_cite		proc :BSTR
    get_cite		proc :ptr
    put_width		proc :BSTR
    get_width		proc :ptr
   .ends

endif

ifndef __IHTMLBlockElement3_INTERFACE_DEFINED__
define __IHTMLBlockElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBlockElement3, "3050f524-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBlockElement3 : public IDispatch

    put_cite		proc :BSTR
    get_cite		proc :ptr
   .ends

endif

ifndef __DispHTMLBlockElement_DISPINTERFACE_DEFINED__
define __DispHTMLBlockElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLBlockElement, "3050f273-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLBlockElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLBlockElement, "3050f281-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLDivElement_INTERFACE_DEFINED__
define __IHTMLDivElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDivElement, "3050f220-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDivElement : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
    put_noWrap		proc :VARIANT_BOOL
    get_noWrap		proc :ptr
   .ends

endif

ifndef __DispHTMLDivElement_DISPINTERFACE_DEFINED__
define __DispHTMLDivElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDivElement, "3050f50c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDivElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDivElement, "3050f27e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLDDElement_INTERFACE_DEFINED__
define __IHTMLDDElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDDElement, "3050f40b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDDElement : public IDispatch

    put_noWrap		proc :VARIANT_BOOL
    get_noWrap		proc :ptr
   .ends

endif

ifndef __DispHTMLDDElement_DISPINTERFACE_DEFINED__
define __DispHTMLDDElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDDElement, "3050f50b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDDElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDDElement, "3050f27f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLDTElement_INTERFACE_DEFINED__
define __IHTMLDTElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDTElement, "3050f4a6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDTElement : public IDispatch

    put_noWrap		proc :VARIANT_BOOL
    get_noWrap		proc :ptr
   .ends

endif

ifndef __DispHTMLDTElement_DISPINTERFACE_DEFINED__
define __DispHTMLDTElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDTElement, "3050f50d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDTElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDTElement, "3050f27c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLBRElement_INTERFACE_DEFINED__
define __IHTMLBRElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBRElement, "3050f7ed-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBRElement : public IDispatch

    put_clear		proc :BSTR
    get_clear		proc :ptr
   .ends

endif

ifndef __DispHTMLBRElement_DISPINTERFACE_DEFINED__
define __DispHTMLBRElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLBRElement, "3050f53a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLBRElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLBRElement, "3050f280-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLDListElement_INTERFACE_DEFINED__
define __IHTMLDListElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDListElement, "305104ae-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDListElement : public IDispatch

    put_compact		proc :VARIANT_BOOL
    get_compact		proc :ptr
   .ends

endif

ifndef __DispHTMLDListElement_DISPINTERFACE_DEFINED__
define __DispHTMLDListElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDListElement, "3050f53b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDListElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDListElement, "3050f27d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLHRElement_INTERFACE_DEFINED__
define __IHTMLHRElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLHRElement, "3050f5a3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLHRElement : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
    put_color		proc :VARIANT
    get_color		proc :ptr
    put_noShade		proc :VARIANT_BOOL
    get_noShade		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_size		proc :VARIANT
    get_size		proc :ptr
   .ends

endif

ifndef __DispHTMLHRElement_DISPINTERFACE_DEFINED__
define __DispHTMLHRElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLHRElement, "3050f53d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLHRElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLHRElement, "3050f252-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLParaElement_INTERFACE_DEFINED__
define __IHTMLParaElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLParaElement, "3050f614-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLParaElement : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __DispHTMLParaElement_DISPINTERFACE_DEFINED__
define __DispHTMLParaElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLParaElement, "3050f52c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLParaElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLParaElement, "3050f26f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLElementCollection2_INTERFACE_DEFINED__
define __IHTMLElementCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementCollection2, "3050f364-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementCollection2 : public IDispatch

    urns		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLElementCollection3_INTERFACE_DEFINED__
define __IHTMLElementCollection3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementCollection3, "3050f1f7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementCollection3 : public IDispatch

    namedItem		proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLElementCollection4_INTERFACE_DEFINED__
define __IHTMLElementCollection4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLElementCollection4, "3050f4f6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLElementCollection4 : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
    namedItem		proc :BSTR, :ptr
   .ends

endif

ifndef __DispHTMLElementCollection_DISPINTERFACE_DEFINED__
define __DispHTMLElementCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLElementCollection, "3050f56b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLElementCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLElementCollection, "3050f4cb-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLHeaderElement_INTERFACE_DEFINED__
define __IHTMLHeaderElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLHeaderElement, "3050f836-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLHeaderElement : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __DispHTMLHeaderElement_DISPINTERFACE_DEFINED__
define __DispHTMLHeaderElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLHeaderElement, "3050f515-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLHeaderElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLHeaderElement, "3050f27a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLSelectElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLSelectElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLSelectElementEvents2, "3050f622-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLSelectElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLSelectElementEvents_DISPINTERFACE_DEFINED__
define __HTMLSelectElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLSelectElementEvents, "3050f302-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLSelectElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLOptionElement_INTERFACE_DEFINED__
define __IHTMLOptionElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOptionElement, "3050f645-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOptionElement : public IDispatch

    put_selected	proc :VARIANT_BOOL
    get_selected	proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_defaultSelected proc :VARIANT_BOOL
    get_defaultSelected proc :ptr
    put_index		proc :LONG
    get_index		proc :ptr
    put_text		proc :BSTR
    get_text		proc :ptr
    get_form		proc :ptr
   .ends

endif

ifndef __IHTMLSelectElementEx_INTERFACE_DEFINED__
define __IHTMLSelectElementEx_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectElementEx, "3051042c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectElementEx : public IUnknown

    ShowDropdown	proc :BOOL
    SetSelectExFlags	proc :DWORD
    GetSelectExFlags	proc :ptr
    GetDropdownOpen	proc :ptr
   .ends

endif

ifndef __IHTMLSelectElement_INTERFACE_DEFINED__
define __IHTMLSelectElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectElement, "3050f510-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectElement : public IDispatch

    put_size		proc :LONG
    get_size		proc :ptr
    put_multiple	proc :VARIANT_BOOL
    get_multiple	proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    get_options		proc :ptr
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_selectedIndex	proc :LONG
    get_selectedIndex	proc :ptr
    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    _add		proc :ptr, :VARIANT
    remove		proc :LONG
    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :VARIANT, :VARIANT, :ptr
    tags		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLSelectElement2_INTERFACE_DEFINED__
define __IHTMLSelectElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectElement2, "3050f612-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectElement2 : public IDispatch

    urns		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLSelectElement4_INTERFACE_DEFINED__
define __IHTMLSelectElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectElement4, "3050f4ea-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectElement4 : public IDispatch

    namedItem		proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLSelectElement5_INTERFACE_DEFINED__
define __IHTMLSelectElement5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectElement5, "3050f4e9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectElement5 : public IDispatch

    _add		proc :ptr, :ptr
   .ends

endif

ifndef __IHTMLSelectElement6_INTERFACE_DEFINED__
define __IHTMLSelectElement6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectElement6, "3050f218-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectElement6 : public IDispatch

    _add		proc :ptr, :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
   .ends

endif

ifndef __DispHTMLSelectElement_DISPINTERFACE_DEFINED__
define __DispHTMLSelectElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLSelectElement, "3050f531-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLSelectElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLSelectElement, "3050f245-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLWndSelectElement_DISPINTERFACE_DEFINED__
define __DispHTMLWndSelectElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLWndSelectElement, "3050f597-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLWndSelectElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLWndSelectElement, "3050f2cf-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLSelectionObject_INTERFACE_DEFINED__
define __IHTMLSelectionObject_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectionObject, "3050f537-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectionObject : public IDispatch

    createRange		proc :ptr
    empty		proc
    clear		proc
    get_type		proc :ptr
   .ends

endif

ifndef __IHTMLSelectionObject2_INTERFACE_DEFINED__
define __IHTMLSelectionObject2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelectionObject2, "3050f624-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSelectionObject2 : public IDispatch

    createRangeCollection proc :ptr
    get_typeDetail	proc :ptr
   .ends

endif

ifndef __IHTMLSelection_INTERFACE_DEFINED__
define __IHTMLSelection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSelection, "1FF6AA72-5842-11cf-A707-00AA00C0098D")

.comdef IHTMLSelection : public IDispatch

    get_anchorNode	proc :ptr
    get_anchorOffset	proc :ptr
    get_focusNode	proc :ptr
    get_focusOffset	proc :ptr
    get_isCollapsed	proc :ptr
    collapse		proc :ptr, :LONG
    collapseToStart	proc
    collapseToEnd	proc
    selectAllChildren	proc :ptr
    deleteFromDocument	proc
    get_rangeCount	proc :ptr
    getRangeAt		proc :LONG, :ptr
    addRange		proc :ptr
    removeRange		proc :ptr
    removeAllRanges	proc
    toString		proc :ptr
   .ends

endif

ifndef __IHTMLOptionElement3_INTERFACE_DEFINED__
define __IHTMLOptionElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOptionElement3, "3050f230-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOptionElement3 : public IDispatch

    put_label		proc :BSTR
    get_label		proc :ptr
   .ends

endif

ifndef __IHTMLOptionElement4_INTERFACE_DEFINED__
define __IHTMLOptionElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOptionElement4, "3050f29c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOptionElement4 : public IDispatch

    put_value		proc :BSTR
    get_value		proc :ptr
   .ends

endif

ifndef __IHTMLOptionElementFactory_INTERFACE_DEFINED__
define __IHTMLOptionElementFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOptionElementFactory, "3050f65e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOptionElementFactory : public IDispatch

    create		proc :VARIANT, :VARIANT, :VARIANT, :VARIANT, :ptr
   .ends

endif

ifndef __DispHTMLOptionElement_DISPINTERFACE_DEFINED__
define __DispHTMLOptionElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLOptionElement, "3050f52b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLOptionElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLOptionElement, "3050f24d-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_HTMLOptionElementFactory, "3050f38d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLWndOptionElement_DISPINTERFACE_DEFINED__
define __DispHTMLWndOptionElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLWndOptionElement, "3050f598-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLWndOptionElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLWndOptionElement, "3050f2d0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLButtonElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLButtonElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLButtonElementEvents2, "3050f617-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLButtonElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLButtonElementEvents_DISPINTERFACE_DEFINED__
define __HTMLButtonElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLButtonElementEvents, "3050f2b3-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLButtonElementEvents : public IDispatch

   .ends

endif

ifndef __HTMLInputTextElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLInputTextElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLInputTextElementEvents2, "3050f618-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLInputTextElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLOptionButtonElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLOptionButtonElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLOptionButtonElementEvents2, "3050f619-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLOptionButtonElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLInputFileElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLInputFileElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLInputFileElementEvents2, "3050f61a-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLInputFileElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLInputImageEvents2_DISPINTERFACE_DEFINED__
define __HTMLInputImageEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLInputImageEvents2, "3050f61b-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLInputImageEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLInputTextElementEvents_DISPINTERFACE_DEFINED__
define __HTMLInputTextElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLInputTextElementEvents, "3050f2a7-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLInputTextElementEvents : public IDispatch

   .ends

endif

ifndef __HTMLOptionButtonElementEvents_DISPINTERFACE_DEFINED__
define __HTMLOptionButtonElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLOptionButtonElementEvents, "3050f2bd-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLOptionButtonElementEvents : public IDispatch

   .ends

endif

ifndef __HTMLInputFileElementEvents_DISPINTERFACE_DEFINED__
define __HTMLInputFileElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLInputFileElementEvents, "3050f2af-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLInputFileElementEvents : public IDispatch

   .ends

endif

ifndef __HTMLInputImageEvents_DISPINTERFACE_DEFINED__
define __HTMLInputImageEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLInputImageEvents, "3050f2c3-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLInputImageEvents : public IDispatch

   .ends

endif

ifndef __IHTMLInputElement_INTERFACE_DEFINED__
define __IHTMLInputElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputElement, "3050f616-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputElement : public IDispatch

    put_type		proc :BSTR
    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT_BOOL
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    put_size		proc :LONG
    get_size		proc :ptr
    put_maxLength	proc :LONG
    get_maxLength	proc :ptr
    select		proc
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_defaultValue	proc :BSTR
    get_defaultValue	proc :ptr
    put_readOnly	proc :VARIANT_BOOL
    get_readOnly	proc :ptr
    createTextRange	proc :ptr
    put_indeterminate	proc :VARIANT_BOOL
    get_indeterminate	proc :ptr
    put_defaultChecked	proc :VARIANT_BOOL
    get_defaultChecked	proc :ptr
    put_checked		proc :VARIANT_BOOL
    get_checked		proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_vspace		proc :LONG
    get_vspace		proc :ptr
    put_hspace		proc :LONG
    get_hspace		proc :ptr
    put_alt		proc :BSTR
    get_alt		proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    put_lowsrc		proc :BSTR
    get_lowsrc		proc :ptr
    put_vrml		proc :BSTR
    get_vrml		proc :ptr
    put_dynsrc		proc :BSTR
    get_dynsrc		proc :ptr
    get_readyState	proc :ptr
    get_complete	proc :ptr
    put_loop		proc :VARIANT
    get_loop		proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_onabort		proc :VARIANT
    get_onabort		proc :ptr
    put_width		proc :LONG
    get_width		proc :ptr
    put_height		proc :LONG
    get_height		proc :ptr
    put_start		proc :BSTR
    get_start		proc :ptr
   .ends

endif

ifndef __IHTMLInputElement2_INTERFACE_DEFINED__
define __IHTMLInputElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputElement2, "3050f25b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputElement2 : public IDispatch

    put_accept		proc :BSTR
    get_accept		proc :ptr
    put_useMap		proc :BSTR
    get_useMap		proc :ptr
   .ends

endif

ifndef __IHTMLInputElement3_INTERFACE_DEFINED__
define __IHTMLInputElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputElement3, "3050f240-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputElement3 : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
    put_lowsrc		proc :BSTR
    get_lowsrc		proc :ptr
    put_vrml		proc :BSTR
    get_vrml		proc :ptr
    put_dynsrc		proc :BSTR
    get_dynsrc		proc :ptr
   .ends

endif

ifndef __IHTMLInputButtonElement_INTERFACE_DEFINED__
define __IHTMLInputButtonElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputButtonElement, "3050f826-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputButtonElement : public IDispatch

    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    createTextRange	proc :ptr
   .ends

endif

ifndef __IHTMLInputHiddenElement_INTERFACE_DEFINED__
define __IHTMLInputHiddenElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputHiddenElement, "30510434-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputHiddenElement : public IDispatch

    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    createTextRange	proc :ptr
   .ends

endif

ifndef __IHTMLInputTextElement_INTERFACE_DEFINED__
define __IHTMLInputTextElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputTextElement, "305107f6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputTextElement : public IDispatch

    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    put_defaultValue	proc :BSTR
    get_defaultValue	proc :ptr
    put_size		proc :LONG
    get_size		proc :ptr
    put_maxLength	proc :LONG
    get_maxLength	proc :ptr
    select		proc
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_readOnly	proc :VARIANT_BOOL
    get_readOnly	proc :ptr
    createTextRange	proc :ptr
   .ends

endif

ifndef __IHTMLInputTextElement2_INTERFACE_DEFINED__
define __IHTMLInputTextElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputTextElement2, "30510793-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputTextElement2 : public IDispatch

    put_selectionStart	proc :LONG
    get_selectionStart	proc :ptr
    put_selectionEnd	proc :LONG
    get_selectionEnd	proc :ptr
    setSelectionRange	proc :LONG, :LONG
   .ends

endif

ifndef __IHTMLInputFileElement_INTERFACE_DEFINED__
define __IHTMLInputFileElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputFileElement, "3050f38e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputFileElement : public IDispatch

    get_type		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    put_size		proc :LONG
    get_size		proc :ptr
    put_maxLength	proc :LONG
    get_maxLength	proc :ptr
    select		proc
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
   .ends

endif

ifndef __IHTMLOptionButtonElement_INTERFACE_DEFINED__
define __IHTMLOptionButtonElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOptionButtonElement, "3050f51c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOptionButtonElement : public IDispatch

    put_value		proc :BSTR
    get_value		proc :ptr
    get_type		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_checked		proc :VARIANT_BOOL
    get_checked		proc :ptr
    put_defaultChecked	proc :VARIANT_BOOL
    get_defaultChecked	proc :ptr
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    put_status		proc :VARIANT_BOOL
    get_status		proc :ptr
    put_indeterminate	proc :VARIANT_BOOL
    get_indeterminate	proc :ptr
    get_form		proc :ptr
   .ends

endif

ifndef __IHTMLInputImage_INTERFACE_DEFINED__
define __IHTMLInputImage_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputImage, "3050f1d8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputImage : public IDispatch

    get_type		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_vspace		proc :LONG
    get_vspace		proc :ptr
    put_hspace		proc :LONG
    get_hspace		proc :ptr
    put_alt		proc :BSTR
    get_alt		proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    put_lowsrc		proc :BSTR
    get_lowsrc		proc :ptr
    put_vrml		proc :BSTR
    get_vrml		proc :ptr
    put_dynsrc		proc :BSTR
    get_dynsrc		proc :ptr
    get_readyState	proc :ptr
    get_complete	proc :ptr
    put_loop		proc :VARIANT
    get_loop		proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_onabort		proc :VARIANT
    get_onabort		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_width		proc :LONG
    get_width		proc :ptr
    put_height		proc :LONG
    get_height		proc :ptr
    put_start		proc :BSTR
    get_start		proc :ptr
   .ends

endif

ifndef __IHTMLInputRangeElement_INTERFACE_DEFINED__
define __IHTMLInputRangeElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLInputRangeElement, "3050f5c5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLInputRangeElement : public IDispatch

    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_type		proc :ptr
    put_alt		proc :BSTR
    get_alt		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_min		proc :BSTR
    get_min		proc :ptr
    put_max		proc :BSTR
    get_max		proc :ptr
    put_step		proc :BSTR
    get_step		proc :ptr
    put_valueAsNumber	proc :DOUBLE
    get_valueAsNumber	proc :ptr
    stepUp		proc :LONG
    stepDown		proc :LONG
   .ends

endif

ifndef __DispHTMLInputElement_DISPINTERFACE_DEFINED__
define __DispHTMLInputElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLInputElement, "3050f57d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLInputElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLInputElement, "3050f5d8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLTextAreaElement_INTERFACE_DEFINED__
define __IHTMLTextAreaElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTextAreaElement, "30510422-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTextAreaElement : public IDispatch

    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    put_defaultValue	proc :BSTR
    get_defaultValue	proc :ptr
    select		proc
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_readOnly	proc :VARIANT_BOOL
    get_readOnly	proc :ptr
    put_rows		proc :LONG
    get_rows		proc :ptr
    put_cols		proc :LONG
    get_cols		proc :ptr
    put_wrap		proc :BSTR
    get_wrap		proc :ptr
    createTextRange	proc :ptr
   .ends

endif

ifndef __IHTMLTextAreaElement2_INTERFACE_DEFINED__
define __IHTMLTextAreaElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTextAreaElement2, "30510795-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTextAreaElement2 : public IDispatch

    put_selectionStart	proc :LONG
    get_selectionStart	proc :ptr
    put_selectionEnd	proc :LONG
    get_selectionEnd	proc :ptr
    setSelectionRange	proc :LONG, :LONG
   .ends

endif

ifndef __DispHTMLTextAreaElement_DISPINTERFACE_DEFINED__
define __DispHTMLTextAreaElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTextAreaElement, "3050f521-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTextAreaElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTextAreaElement, "3050f2ac-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLRichtextElement_DISPINTERFACE_DEFINED__
define __DispHTMLRichtextElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLRichtextElement, "3050f54d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLRichtextElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLRichtextElement, "3050f2df-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLButtonElement_INTERFACE_DEFINED__
define __IHTMLButtonElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLButtonElement, "30510822-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLButtonElement : public IDispatch

    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_status		proc :VARIANT
    get_status		proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    get_form		proc :ptr
    createTextRange	proc :ptr
   .ends

endif

ifndef __IHTMLButtonElement2_INTERFACE_DEFINED__
define __IHTMLButtonElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLButtonElement2, "3050f507-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLButtonElement2 : public IDispatch

    put_type		proc :BSTR
    get_type		proc :ptr
   .ends

endif

ifndef __DispHTMLButtonElement_DISPINTERFACE_DEFINED__
define __DispHTMLButtonElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLButtonElement, "3050f51f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLButtonElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLButtonElement, "3050f2c6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLMarqueeElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLMarqueeElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLMarqueeElementEvents2, "3050f61f-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLMarqueeElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLMarqueeElementEvents_DISPINTERFACE_DEFINED__
define __HTMLMarqueeElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLMarqueeElementEvents, "3050f2b8-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLMarqueeElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLMarqueeElement_INTERFACE_DEFINED__
define __IHTMLMarqueeElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMarqueeElement, "3050f1d9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMarqueeElement : public IDispatch

    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    put_scrollDelay	proc :LONG
    get_scrollDelay	proc :ptr
    put_direction	proc :BSTR
    get_direction	proc :ptr
    put_behavior	proc :BSTR
    get_behavior	proc :ptr
    put_scrollAmount	proc :LONG
    get_scrollAmount	proc :ptr
    put_loop		proc :LONG
    get_loop		proc :ptr
    put_vspace		proc :LONG
    get_vspace		proc :ptr
    put_hspace		proc :LONG
    get_hspace		proc :ptr
    put_onfinish	proc :VARIANT
    get_onfinish	proc :ptr
    put_onstart		proc :VARIANT
    get_onstart		proc :ptr
    put_onbounce	proc :VARIANT
    get_onbounce	proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    put_trueSpeed	proc :VARIANT_BOOL
    get_trueSpeed	proc :ptr
    start		proc
    stop		proc
   .ends

endif

ifndef __DispHTMLMarqueeElement_DISPINTERFACE_DEFINED__
define __DispHTMLMarqueeElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMarqueeElement, "3050f527-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMarqueeElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMarqueeElement, "3050f2b9-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLHtmlElement_INTERFACE_DEFINED__
define __IHTMLHtmlElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLHtmlElement, "3050f512-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLHtmlElement : public IDispatch

    put_version		proc :BSTR
    get_version		proc :ptr
   .ends

endif

ifndef __IHTMLHeadElement_INTERFACE_DEFINED__
define __IHTMLHeadElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLHeadElement, "3050f610-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLHeadElement : public IDispatch

    put_profile		proc :BSTR
    get_profile		proc :ptr
   .ends

endif

ifndef __IHTMLHeadElement2_INTERFACE_DEFINED__
define __IHTMLHeadElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLHeadElement2, "3050f29d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLHeadElement2 : public IDispatch

    put_profile		proc :BSTR
    get_profile		proc :ptr
   .ends

endif

ifndef __IHTMLTitleElement_INTERFACE_DEFINED__
define __IHTMLTitleElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTitleElement, "3050f1da-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTitleElement : public IDispatch

    put_text		proc :BSTR
    get_text		proc :ptr
   .ends

endif

ifndef __IHTMLMetaElement_INTERFACE_DEFINED__
define __IHTMLMetaElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMetaElement, "3050f825-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMetaElement : public IDispatch

    put_httpEquiv	proc :BSTR
    get_httpEquiv	proc :ptr
    put_content		proc :BSTR
    get_content		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_url		proc :BSTR
    get_url		proc :ptr
    put_charset		proc :BSTR
    get_charset		proc :ptr
   .ends

endif

ifndef __IHTMLMetaElement2_INTERFACE_DEFINED__
define __IHTMLMetaElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMetaElement2, "3051041d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMetaElement2 : public IDispatch

    put_scheme		proc :BSTR
    get_scheme		proc :ptr
   .ends

endif

ifndef __IHTMLMetaElement3_INTERFACE_DEFINED__
define __IHTMLMetaElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMetaElement3, "3050f502-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMetaElement3 : public IDispatch

    put_url		proc :BSTR
    get_url		proc :ptr
   .ends

endif

ifndef __IHTMLBaseElement_INTERFACE_DEFINED__
define __IHTMLBaseElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBaseElement, "3050f61c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBaseElement : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
    put_target		proc :BSTR
    get_target		proc :ptr
   .ends

endif

ifndef __IHTMLBaseElement2_INTERFACE_DEFINED__
define __IHTMLBaseElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBaseElement2, "3050f329-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBaseElement2 : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
   .ends

endif

ifndef __IHTMLIsIndexElement_INTERFACE_DEFINED__
define __IHTMLIsIndexElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLIsIndexElement, "3050f32a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLIsIndexElement : public IDispatch

    put_prompt		proc :BSTR
    get_prompt		proc :ptr
    put_action		proc :BSTR
    get_action		proc :ptr
   .ends

endif

ifndef __IHTMLIsIndexElement2_INTERFACE_DEFINED__
define __IHTMLIsIndexElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLIsIndexElement2, "3050f832-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLIsIndexElement2 : public IDispatch

    get_form		proc :ptr
   .ends

endif

ifndef __IHTMLNextIdElement_INTERFACE_DEFINED__
define __IHTMLNextIdElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLNextIdElement, "3050f522-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLNextIdElement : public IDispatch

    put_n		proc :BSTR
    get_n		proc :ptr
   .ends

endif

ifndef __DispHTMLHtmlElement_DISPINTERFACE_DEFINED__
define __DispHTMLHtmlElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLHtmlElement, "3050f560-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLHtmlElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLHtmlElement, "3050f491-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLHeadElement_DISPINTERFACE_DEFINED__
define __DispHTMLHeadElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLHeadElement, "3050f561-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLHeadElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLHeadElement, "3050f493-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLTitleElement_DISPINTERFACE_DEFINED__
define __DispHTMLTitleElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTitleElement, "3050f516-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTitleElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTitleElement, "3050f284-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLMetaElement_DISPINTERFACE_DEFINED__
define __DispHTMLMetaElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMetaElement, "3050f517-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMetaElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMetaElement, "3050f275-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLBaseElement_DISPINTERFACE_DEFINED__
define __DispHTMLBaseElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLBaseElement, "3050f518-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLBaseElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLBaseElement, "3050f276-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLIsIndexElement_DISPINTERFACE_DEFINED__
define __DispHTMLIsIndexElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLIsIndexElement, "3050f519-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLIsIndexElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLIsIndexElement, "3050f278-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLNextIdElement_DISPINTERFACE_DEFINED__
define __DispHTMLNextIdElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLNextIdElement, "3050f51a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLNextIdElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLNextIdElement, "3050f279-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLBaseFontElement_INTERFACE_DEFINED__
define __IHTMLBaseFontElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBaseFontElement, "3050f20e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBaseFontElement : public IDispatch

    put_color		proc :VARIANT
    get_color		proc :ptr
    put_face		proc :BSTR
    get_face		proc :ptr
    put_size		proc :LONG
    get_size		proc :ptr
   .ends

endif

ifndef __DispHTMLBaseFontElement_DISPINTERFACE_DEFINED__
define __DispHTMLBaseFontElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLBaseFontElement, "3050f504-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLBaseFontElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLBaseFontElement, "3050f282-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLUnknownElement_INTERFACE_DEFINED__
define __IHTMLUnknownElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLUnknownElement, "3050f822-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLUnknownElement : public IDispatch

   .ends

endif
ifndef __DispHTMLUnknownElement_DISPINTERFACE_DEFINED__
define __DispHTMLUnknownElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLUnknownElement, "3050f539-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLUnknownElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLUnknownElement, "3050f268-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IWebGeolocation_INTERFACE_DEFINED__
define __IWebGeolocation_INTERFACE_DEFINED__
DEFINE_IIDX(IWebGeolocation, "3050f525-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWebGeolocation : public IDispatch

    getCurrentPosition	proc :ptr, :ptr, :ptr
    watchPosition	proc :ptr, :ptr, :ptr, :ptr
    clearWatch		proc :LONG
   .ends

endif

ifndef __IOmHistory_INTERFACE_DEFINED__
define __IOmHistory_INTERFACE_DEFINED__
DEFINE_IIDX(IOmHistory, "3050f1dd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IOmHistory : public IDispatch

    get_length		proc :ptr
    back		proc :ptr
    forward		proc :ptr
    go			proc :ptr
   .ends

endif

ifndef __IHTMLMimeTypesCollection_INTERFACE_DEFINED__
define __IHTMLMimeTypesCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMimeTypesCollection, "3050f538-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMimeTypesCollection : public IDispatch

    get_length		proc :ptr
   .ends

endif

ifndef __IHTMLPluginsCollection_INTERFACE_DEFINED__
define __IHTMLPluginsCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPluginsCollection, "3050f1de-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPluginsCollection : public IDispatch

    get_length		proc :ptr
    refresh		proc :VARIANT_BOOL
   .ends

endif

ifndef __IHTMLOpsProfile_INTERFACE_DEFINED__
define __IHTMLOpsProfile_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOpsProfile, "3050f52a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOpsProfile : public IDispatch

    addRequest		proc :BSTR, :VARIANT, :ptr
    clearRequest	proc
    doRequest		proc :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    getAttribute	proc :BSTR, :ptr
    setAttribute	proc :BSTR, :BSTR, :VARIANT, :ptr
    commitChanges	proc :ptr
    addReadRequest	proc :BSTR, :VARIANT, :ptr
    doReadRequest	proc :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    doWriteRequest	proc :ptr
   .ends

endif

ifndef __IOmNavigator_INTERFACE_DEFINED__
define __IOmNavigator_INTERFACE_DEFINED__
DEFINE_IIDX(IOmNavigator, "3050f1e0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IOmNavigator : public IDispatch

    get_appCodeName	proc :ptr
    get_appName		proc :ptr
    get_appVersion	proc :ptr
    get_userAgent	proc :ptr
    javaEnabled		proc :ptr
    taintEnabled	proc :ptr
    get_mimeTypes	proc :ptr
    get_plugins		proc :ptr
    get_cookieEnabled	proc :ptr
    get_opsProfile	proc :ptr
    toString		proc :ptr
    get_cpuClass	proc :ptr
    get_systemLanguage	proc :ptr
    get_browserLanguage proc :ptr
    get_userLanguage	proc :ptr
    get_platform	proc :ptr
    get_appMinorVersion proc :ptr
    get_connectionSpeed proc :ptr
    get_onLine		proc :ptr
    get_userProfile	proc :ptr
   .ends

endif

ifndef __INavigatorGeolocation_INTERFACE_DEFINED__
define __INavigatorGeolocation_INTERFACE_DEFINED__
DEFINE_IIDX(INavigatorGeolocation, "3050f523-98b5-11cf-bb82-00aa00bdce0b")

.comdef INavigatorGeolocation : public IDispatch

    get_geolocation	proc :ptr
   .ends

endif

ifndef __INavigatorDoNotTrack_INTERFACE_DEFINED__
define __INavigatorDoNotTrack_INTERFACE_DEFINED__
DEFINE_IIDX(INavigatorDoNotTrack, "3050f208-98b5-11cf-bb82-00aa00bdce0b")

.comdef INavigatorDoNotTrack : public IDispatch

    get_msDoNotTrack	proc :ptr
   .ends

endif

ifndef __IHTMLLocation_INTERFACE_DEFINED__
define __IHTMLLocation_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLocation, "3050f823-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLocation : public IDispatch

    put_href		proc :BSTR
    get_href		proc :ptr
    put_protocol	proc :BSTR
    get_protocol	proc :ptr
    put_host		proc :BSTR
    get_host		proc :ptr
    put_hostname	proc :BSTR
    get_hostname	proc :ptr
    put_port		proc :BSTR
    get_port		proc :ptr
    put_pathname	proc :BSTR
    get_pathname	proc :ptr
    put_search		proc :BSTR
    get_search		proc :ptr
    put_hash		proc :BSTR
    get_hash		proc :ptr
    reload		proc :VARIANT_BOOL
    replace		proc :BSTR
    assign		proc :BSTR
    toString		proc :ptr
   .ends

endif

ifndef __DispHTMLHistory_DISPINTERFACE_DEFINED__
define __DispHTMLHistory_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLHistory, "3050f549-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLHistory : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLHistory, "FECEAAA3-8405-11cf-8BA1-00AA00476DA6")
DEFINE_GUIDS(CLSID_CMimeTypes, "3050f3fe-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispCPlugins_DISPINTERFACE_DEFINED__
define __DispCPlugins_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCPlugins, "3050f54a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCPlugins : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CPlugins, "3050f3ff-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_COpsProfile, "3050f402-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLNavigator_DISPINTERFACE_DEFINED__
define __DispHTMLNavigator_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLNavigator, "3050f54c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLNavigator : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLNavigator, "FECEAAA6-8405-11cf-8BA1-00AA00476DA6")

ifndef __DispHTMLLocation_DISPINTERFACE_DEFINED__
define __DispHTMLLocation_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLLocation, "3050f54e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLLocation : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLLocation, "163BB1E1-6E00-11cf-837A-48DC04C10000")

ifndef __IHTMLBookmarkCollection_INTERFACE_DEFINED__
define __IHTMLBookmarkCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBookmarkCollection, "30510494-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBookmarkCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLDataTransfer_INTERFACE_DEFINED__
define __IHTMLDataTransfer_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDataTransfer, "3050f506-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDataTransfer : public IDispatch

    setData		proc :BSTR, :ptr, :ptr
    getData		proc :BSTR, :ptr
    clearData		proc :BSTR, :ptr
    put_dropEffect	proc :BSTR
    get_dropEffect	proc :ptr
    put_effectAllowed	proc :BSTR
    get_effectAllowed	proc :ptr
   .ends

endif

ifndef __IHTMLEventObj2_INTERFACE_DEFINED__
define __IHTMLEventObj2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEventObj2, "3050f200-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEventObj2 : public IDispatch

    setAttribute	proc :BSTR, :VARIANT, :LONG
    getAttribute	proc :BSTR, :LONG, :ptr
    removeAttribute	proc :BSTR, :LONG, :ptr
    put_propertyName	proc :BSTR
    get_propertyName	proc :ptr
    putref_bookmarks	proc :ptr
    get_bookmarks	proc :ptr
    putref_recordset	proc :ptr
    get_recordset	proc :ptr
    put_dataFld		proc :BSTR
    get_dataFld		proc :ptr
    putref_boundElements proc :ptr
    get_boundElements	proc :ptr
    put_repeat		proc :VARIANT_BOOL
    get_repeat		proc :ptr
    put_srcUrn		proc :BSTR
    get_srcUrn		proc :ptr
    putref_srcElement	proc :ptr
    get_srcElement	proc :ptr
    put_altKey		proc :VARIANT_BOOL
    get_altKey		proc :ptr
    put_ctrlKey		proc :VARIANT_BOOL
    get_ctrlKey		proc :ptr
    put_shiftKey	proc :VARIANT_BOOL
    get_shiftKey	proc :ptr
    putref_fromElement	proc :ptr
    get_fromElement	proc :ptr
    putref_toElement	proc :ptr
    get_toElement	proc :ptr
    put_button		proc :LONG
    get_button		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
    put_qualifier	proc :BSTR
    get_qualifier	proc :ptr
    put_reason		proc :LONG
    get_reason		proc :ptr
    put_x		proc :LONG
    get_x		proc :ptr
    put_y		proc :LONG
    get_y		proc :ptr
    put_clientX		proc :LONG
    get_clientX		proc :ptr
    put_clientY		proc :LONG
    get_clientY		proc :ptr
    put_offsetX		proc :LONG
    get_offsetX		proc :ptr
    put_offsetY		proc :LONG
    get_offsetY		proc :ptr
    put_screenX		proc :LONG
    get_screenX		proc :ptr
    put_screenY		proc :LONG
    get_screenY		proc :ptr
    putref_srcFilter	proc :ptr
    get_srcFilter	proc :ptr
    get_dataTransfer	proc :ptr
   .ends

endif

ifndef __IHTMLEventObj3_INTERFACE_DEFINED__
define __IHTMLEventObj3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEventObj3, "3050f50c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEventObj3 : public IDispatch

    get_contentOverflow proc :ptr
    put_shiftLeft	proc :VARIANT_BOOL
    get_shiftLeft	proc :ptr
    put_altLeft		proc :VARIANT_BOOL
    get_altLeft		proc :ptr
    put_ctrlLeft	proc :VARIANT_BOOL
    get_ctrlLeft	proc :ptr
    get_imeCompositionChange proc :ptr
    get_imeNotifyCommand proc :ptr
    get_imeNotifyData	proc :ptr
    get_imeRequest	proc :ptr
    get_imeRequestData	proc :ptr
    get_keyboardLayout	proc :ptr
    get_behaviorCookie	proc :ptr
    get_behaviorPart	proc :ptr
    get_nextPage	proc :ptr
   .ends

endif

ifndef __IHTMLEventObj4_INTERFACE_DEFINED__
define __IHTMLEventObj4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEventObj4, "3050f1f2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEventObj4 : public IDispatch

    get_wheelDelta	proc :ptr
   .ends

endif

ifndef __IHTMLEventObj5_INTERFACE_DEFINED__
define __IHTMLEventObj5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEventObj5, "3050f50b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEventObj5 : public IDispatch

    put_url		proc :BSTR
    get_url		proc :ptr
    put_data		proc :BSTR
    get_data		proc :ptr
    get_source		proc :ptr
    put_origin		proc :BSTR
    get_origin		proc :ptr
    put_issession	proc :VARIANT_BOOL
    get_issession	proc :ptr
   .ends

endif

ifndef __IHTMLEventObj6_INTERFACE_DEFINED__
define __IHTMLEventObj6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEventObj6, "3050f1f3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEventObj6 : public IDispatch

    get_actionURL	proc :ptr
    get_buttonID	proc :ptr
   .ends

endif

ifndef __DispCEventObj_DISPINTERFACE_DEFINED__
define __DispCEventObj_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCEventObj, "3050f558-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCEventObj : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CEventObj, "3050f48A-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleMedia_INTERFACE_DEFINED__
define __IHTMLStyleMedia_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleMedia, "3050f50d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleMedia : public IDispatch

    get_type		proc :ptr
    matchMedium		proc :BSTR, :ptr
   .ends

endif

ifndef __DispHTMLStyleMedia_DISPINTERFACE_DEFINED__
define __DispHTMLStyleMedia_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleMedia, "3059009e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleMedia : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleMedia, "3051074c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLWindowEvents3_DISPINTERFACE_DEFINED__
define __HTMLWindowEvents3_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLWindowEvents3, "3050f5a1-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLWindowEvents3 : public IDispatch

   .ends

endif
ifndef __HTMLWindowEvents2_DISPINTERFACE_DEFINED__
define __HTMLWindowEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLWindowEvents2, "3050f625-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLWindowEvents2 : public IDispatch

   .ends

endif
ifndef __HTMLWindowEvents_DISPINTERFACE_DEFINED__
define __HTMLWindowEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLWindowEvents, "96A0A4E0-D062-11cf-94B6-00AA0060275C")

.comdef HTMLWindowEvents : public IDispatch

   .ends

endif

ifndef __IHTMLDocument2_INTERFACE_DEFINED__
define __IHTMLDocument2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument2, "3050f1f0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument2 : public IHTMLDocument

    get_all		proc :ptr
    get_body		proc :ptr
    get_activeElement	proc :ptr
    get_images		proc :ptr
    get_applets		proc :ptr
    get_links		proc :ptr
    get_forms		proc :ptr
    get_anchors		proc :ptr
    put_title		proc :BSTR
    get_title		proc :ptr
    get_scripts		proc :ptr
    put_designMode	proc :BSTR
    get_designMode	proc :ptr
    get_selection	proc :ptr
    get_readyState	proc :ptr
    get_frames		proc :ptr
    get_embeds		proc :ptr
    get_plugins		proc :ptr
    put_alinkColor	proc :VARIANT
    get_alinkColor	proc :ptr
    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    put_fgColor		proc :VARIANT
    get_fgColor		proc :ptr
    put_linkColor	proc :VARIANT
    get_linkColor	proc :ptr
    put_vlinkColor	proc :VARIANT
    get_vlinkColor	proc :ptr
    get_referrer	proc :ptr
    get_location	proc :ptr
    get_lastModified	proc :ptr
    put_URL		proc :BSTR
    get_URL		proc :ptr
    put_domain		proc :BSTR
    get_domain		proc :ptr
    put_cookie		proc :BSTR
    get_cookie		proc :ptr
    put_expando		proc :VARIANT_BOOL
    get_expando		proc :ptr
    put_charset		proc :BSTR
    get_charset		proc :ptr
    put_defaultCharset	proc :BSTR
    get_defaultCharset	proc :ptr
    get_mimeType	proc :ptr
    get_fileSize	proc :ptr
    get_fileCreatedDate proc :ptr
    get_fileModifiedDate proc :ptr
    get_fileUpdatedDate proc :ptr
    get_security	proc :ptr
    get_protocol	proc :ptr
    get_nameProp	proc :ptr
    write		proc :ptr
    writeln		proc :ptr
    open		proc :BSTR, :VARIANT, :VARIANT, :VARIANT, :ptr
    close		proc
    clear		proc
    queryCommandSupported proc :BSTR, :ptr
    queryCommandEnabled proc :BSTR, :ptr
    queryCommandState	proc :BSTR, :ptr
    queryCommandIndeterm proc :BSTR, :ptr
    queryCommandText	proc :BSTR, :ptr
    queryCommandValue	proc :BSTR, :ptr
    execCommand		proc :BSTR, :VARIANT_BOOL, :VARIANT, :ptr
    execCommandShowHelp proc :BSTR, :ptr
    createElement	proc :BSTR, :ptr
    put_onhelp		proc :VARIANT
    get_onhelp		proc :ptr
    put_onclick		proc :VARIANT
    get_onclick		proc :ptr
    put_ondblclick	proc :VARIANT
    get_ondblclick	proc :ptr
    put_onkeyup		proc :VARIANT
    get_onkeyup		proc :ptr
    put_onkeydown	proc :VARIANT
    get_onkeydown	proc :ptr
    put_onkeypress	proc :VARIANT
    get_onkeypress	proc :ptr
    put_onmouseup	proc :VARIANT
    get_onmouseup	proc :ptr
    put_onmousedown	proc :VARIANT
    get_onmousedown	proc :ptr
    put_onmousemove	proc :VARIANT
    get_onmousemove	proc :ptr
    put_onmouseout	proc :VARIANT
    get_onmouseout	proc :ptr
    put_onmouseover	proc :VARIANT
    get_onmouseover	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    put_onafterupdate	proc :VARIANT
    get_onafterupdate	proc :ptr
    put_onrowexit	proc :VARIANT
    get_onrowexit	proc :ptr
    put_onrowenter	proc :VARIANT
    get_onrowenter	proc :ptr
    put_ondragstart	proc :VARIANT
    get_ondragstart	proc :ptr
    put_onselectstart	proc :VARIANT
    get_onselectstart	proc :ptr
    elementFromPoint	proc :LONG, :LONG, :ptr
    get_parentWindow	proc :ptr
    get_styleSheets	proc :ptr
    put_onbeforeupdate	proc :VARIANT
    get_onbeforeupdate	proc :ptr
    put_onerrorupdate	proc :VARIANT
    get_onerrorupdate	proc :ptr
    toString		proc :ptr
    createStyleSheet	proc :BSTR, :LONG, :ptr
   .ends

endif

ifndef __IHTMLFramesCollection2_INTERFACE_DEFINED__
define __IHTMLFramesCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFramesCollection2, "3050f53a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFramesCollection2 : public IDispatch

    item		proc :ptr, :ptr
    get_length		proc :ptr
   .ends

endif

ifndef __IHTMLWindow2_INTERFACE_DEFINED__
define __IHTMLWindow2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow2, "3050f1f1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow2 : public IHTMLFramesCollection2

    get_frames		proc :ptr
    put_defaultStatus	proc :BSTR
    get_defaultStatus	proc :ptr
    put_status		proc :BSTR
    get_status		proc :ptr
    setTimeout		proc :BSTR, :LONG, :ptr, :ptr
    clearTimeout	proc :LONG
    alert		proc :BSTR
    confirm		proc :BSTR, :ptr
    prompt		proc :BSTR, :BSTR, :ptr
    get_Image		proc :ptr
    get_location	proc :ptr
    get_history		proc :ptr
    close		proc
    put_opener		proc :VARIANT
    get_opener		proc :ptr
    get_navigator	proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    get_parent		proc :ptr
    open		proc :BSTR, :BSTR, :BSTR, :VARIANT_BOOL, :ptr
    get_self		proc :ptr
    get_top		proc :ptr
    get_window		proc :ptr
    navigate		proc :BSTR
    put_onfocus		proc :VARIANT
    get_onfocus		proc :ptr
    put_onblur		proc :VARIANT
    get_onblur		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onbeforeunload	proc :VARIANT
    get_onbeforeunload	proc :ptr
    put_onunload	proc :VARIANT
    get_onunload	proc :ptr
    put_onhelp		proc :VARIANT
    get_onhelp		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_onresize	proc :VARIANT
    get_onresize	proc :ptr
    put_onscroll	proc :VARIANT
    get_onscroll	proc :ptr
    get_document	proc :ptr
    get_event		proc :ptr
    get__newEnum	proc :ptr
    showModalDialog	proc :BSTR, :ptr, :ptr, :ptr
    showHelp		proc :BSTR, :VARIANT, :BSTR
    get_screen		proc :ptr
    get_Option		proc :ptr
    focus		proc
    get_closed		proc :ptr
    blur		proc
    scroll		proc :LONG, :LONG
    get_clientInformation proc :ptr
    setInterval		proc :BSTR, :LONG, :ptr, :ptr
    clearInterval	proc :LONG
    put_offscreenBuffering proc :VARIANT
    get_offscreenBuffering proc :ptr
    execScript		proc :BSTR, :BSTR, :ptr
    toString		proc :ptr
    scrollBy		proc :LONG, :LONG
    scrollTo		proc :LONG, :LONG
    moveTo		proc :LONG, :LONG
    moveBy		proc :LONG, :LONG
    resizeTo		proc :LONG, :LONG
    resizeBy		proc :LONG, :LONG
    get_external	proc :ptr
   .ends

endif

ifndef __IHTMLWindow3_INTERFACE_DEFINED__
define __IHTMLWindow3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow3, "3050f53b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow3 : public IDispatch

    get_screenLeft	proc :ptr
    get_screenTop	proc :ptr
    attachEvent		proc :BSTR, :ptr, :ptr
    detachEvent		proc :BSTR, :ptr
    setTimeout		proc :ptr, :LONG, :ptr, :ptr
    setInterval		proc :ptr, :LONG, :ptr, :ptr
    print		proc
    put_onbeforeprint	proc :VARIANT
    get_onbeforeprint	proc :ptr
    put_onafterprint	proc :VARIANT
    get_onafterprint	proc :ptr
    get_clipboardData	proc :ptr
    showModelessDialog	proc :BSTR, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IHTMLFrameBase_INTERFACE_DEFINED__
define __IHTMLFrameBase_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameBase, "3050f1f4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameBase : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_frameBorder	proc :BSTR
    get_frameBorder	proc :ptr
    put_frameSpacing	proc :VARIANT
    get_frameSpacing	proc :ptr
    put_marginWidth	proc :VARIANT
    get_marginWidth	proc :ptr
    put_marginHeight	proc :VARIANT
    get_marginHeight	proc :ptr
    put_noResize	proc :VARIANT_BOOL
    get_noResize	proc :ptr
    put_scrolling	proc :BSTR
    get_scrolling	proc :ptr
   .ends

endif

ifndef __IHTMLStorage_INTERFACE_DEFINED__
define __IHTMLStorage_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStorage, "3050f53d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStorage : public IDispatch

    get_length		proc :ptr
    get_remainingSpace	proc :ptr
    key			proc :LONG, :ptr
    getItem		proc :BSTR, :ptr
    setItem		proc :BSTR, :BSTR
    removeItem		proc :BSTR
    clear		proc
   .ends

endif

ifndef __IHTMLPerformance_INTERFACE_DEFINED__
define __IHTMLPerformance_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPerformance, "3050f1f5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPerformance : public IDispatch

    get_navigation	proc :ptr
    get_timing		proc :ptr
    toString		proc :ptr
    toJSON		proc :ptr
   .ends

endif

ifndef __IHTMLApplicationCache_INTERFACE_DEFINED__
define __IHTMLApplicationCache_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLApplicationCache, "3050f52c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLApplicationCache : public IDispatch

    get_status		proc :ptr
    put_onchecking	proc :VARIANT
    get_onchecking	proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_onnoupdate	proc :VARIANT
    get_onnoupdate	proc :ptr
    put_ondownloading	proc :VARIANT
    get_ondownloading	proc :ptr
    put_onprogress	proc :VARIANT
    get_onprogress	proc :ptr
    put_onupdateready	proc :VARIANT
    get_onupdateready	proc :ptr
    put_oncached	proc :VARIANT
    get_oncached	proc :ptr
    put_onobsolete	proc :VARIANT
    get_onobsolete	proc :ptr
    update		proc
    swapCache		proc
    abort		proc
   .ends

endif

ifndef __IHTMLScreen_INTERFACE_DEFINED__
define __IHTMLScreen_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScreen, "3050f5ee-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScreen : public IDispatch

    get_colorDepth	proc :ptr
    put_bufferDepth	proc :LONG
    get_bufferDepth	proc :ptr
    get_width		proc :ptr
    get_height		proc :ptr
    put_updateInterval	proc :LONG
    get_updateInterval	proc :ptr
    get_availHeight	proc :ptr
    get_availWidth	proc :ptr
    get_fontSmoothingEnabled proc :ptr
   .ends

endif

ifndef __IHTMLScreen2_INTERFACE_DEFINED__
define __IHTMLScreen2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScreen2, "3050f835-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScreen2 : public IDispatch

    get_logicalXDPI	proc :ptr
    get_logicalYDPI	proc :ptr
    get_deviceXDPI	proc :ptr
    get_deviceYDPI	proc :ptr
   .ends

endif

ifndef __IHTMLScreen3_INTERFACE_DEFINED__
define __IHTMLScreen3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScreen3, "30510425-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScreen3 : public IDispatch

    get_systemXDPI	proc :ptr
    get_systemYDPI	proc :ptr
   .ends

endif

ifndef __IHTMLScreen4_INTERFACE_DEFINED__
define __IHTMLScreen4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScreen4, "3050f56b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScreen4 : public IDispatch

    get_pixelDepth	proc :ptr
   .ends

endif

ifndef __IHTMLWindow4_INTERFACE_DEFINED__
define __IHTMLWindow4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow4, "3050f1f6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow4 : public IDispatch

    createPopup		proc :ptr, :ptr
    get_frameElement	proc :ptr
   .ends

endif

ifndef __IHTMLWindow5_INTERFACE_DEFINED__
define __IHTMLWindow5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow5, "3050f515-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow5 : public IDispatch

    put_XMLHttpRequest	proc :VARIANT
    get_XMLHttpRequest	proc :ptr
   .ends

endif

ifndef __IHTMLWindow6_INTERFACE_DEFINED__
define __IHTMLWindow6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow6, "3050f622-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow6 : public IDispatch

    put_XDomainRequest	proc :VARIANT
    get_XDomainRequest	proc :ptr
    get_sessionStorage	proc :ptr
    get_localStorage	proc :ptr
    put_onhashchange	proc :VARIANT
    get_onhashchange	proc :ptr
    get_maxConnectionsPerServer proc :ptr
    postMessage		proc :BSTR, :VARIANT
    toStaticHTML	proc :BSTR, :ptr
    put_onmessage	proc :VARIANT
    get_onmessage	proc :ptr
    msWriteProfilerMark proc :BSTR
   .ends

endif

ifndef __IHTMLWindow7_INTERFACE_DEFINED__
define __IHTMLWindow7_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow7, "3050f302-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow7 : public IDispatch

    getSelection	proc :ptr
    getComputedStyle	proc :ptr, :BSTR, :ptr
    get_styleMedia	proc :ptr
    put_performance	proc :VARIANT
    get_performance	proc :ptr
    get_innerWidth	proc :ptr
    get_innerHeight	proc :ptr
    get_pageXOffset	proc :ptr
    get_pageYOffset	proc :ptr
    get_screenX		proc :ptr
    get_screenY		proc :ptr
    get_outerWidth	proc :ptr
    get_outerHeight	proc :ptr
    put_onabort		proc :VARIANT
    get_onabort		proc :ptr
    put_oncanplay	proc :VARIANT
    get_oncanplay	proc :ptr
    put_oncanplaythrough proc :VARIANT
    get_oncanplaythrough proc :ptr
    put_onchange	proc :VARIANT
    get_onchange	proc :ptr
    put_onclick		proc :VARIANT
    get_onclick		proc :ptr
    put_oncontextmenu	proc :VARIANT
    get_oncontextmenu	proc :ptr
    put_ondblclick	proc :VARIANT
    get_ondblclick	proc :ptr
    put_ondrag		proc :VARIANT
    get_ondrag		proc :ptr
    put_ondragend	proc :VARIANT
    get_ondragend	proc :ptr
    put_ondragenter	proc :VARIANT
    get_ondragenter	proc :ptr
    put_ondragleave	proc :VARIANT
    get_ondragleave	proc :ptr
    put_ondragover	proc :VARIANT
    get_ondragover	proc :ptr
    put_ondragstart	proc :VARIANT
    get_ondragstart	proc :ptr
    put_ondrop		proc :VARIANT
    get_ondrop		proc :ptr
    put_ondurationchange proc :VARIANT
    get_ondurationchange proc :ptr
    put_onfocusin	proc :VARIANT
    get_onfocusin	proc :ptr
    put_onfocusout	proc :VARIANT
    get_onfocusout	proc :ptr
    put_oninput		proc :VARIANT
    get_oninput		proc :ptr
    put_onemptied	proc :VARIANT
    get_onemptied	proc :ptr
    put_onended		proc :VARIANT
    get_onended		proc :ptr
    put_onkeydown	proc :VARIANT
    get_onkeydown	proc :ptr
    put_onkeypress	proc :VARIANT
    get_onkeypress	proc :ptr
    put_onkeyup		proc :VARIANT
    get_onkeyup		proc :ptr
    put_onloadeddata	proc :VARIANT
    get_onloadeddata	proc :ptr
    put_onloadedmetadata proc :VARIANT
    get_onloadedmetadata proc :ptr
    put_onloadstart	proc :VARIANT
    get_onloadstart	proc :ptr
    put_onmousedown	proc :VARIANT
    get_onmousedown	proc :ptr
    put_onmouseenter	proc :VARIANT
    get_onmouseenter	proc :ptr
    put_onmouseleave	proc :VARIANT
    get_onmouseleave	proc :ptr
    put_onmousemove	proc :VARIANT
    get_onmousemove	proc :ptr
    put_onmouseout	proc :VARIANT
    get_onmouseout	proc :ptr
    put_onmouseover	proc :VARIANT
    get_onmouseover	proc :ptr
    put_onmouseup	proc :VARIANT
    get_onmouseup	proc :ptr
    put_onmousewheel	proc :VARIANT
    get_onmousewheel	proc :ptr
    put_onoffline	proc :VARIANT
    get_onoffline	proc :ptr
    put_ononline	proc :VARIANT
    get_ononline	proc :ptr
    put_onprogress	proc :VARIANT
    get_onprogress	proc :ptr
    put_onratechange	proc :VARIANT
    get_onratechange	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    put_onreset		proc :VARIANT
    get_onreset		proc :ptr
    put_onseeked	proc :VARIANT
    get_onseeked	proc :ptr
    put_onseeking	proc :VARIANT
    get_onseeking	proc :ptr
    put_onselect	proc :VARIANT
    get_onselect	proc :ptr
    put_onstalled	proc :VARIANT
    get_onstalled	proc :ptr
    put_onstorage	proc :VARIANT
    get_onstorage	proc :ptr
    put_onsubmit	proc :VARIANT
    get_onsubmit	proc :ptr
    put_onsuspend	proc :VARIANT
    get_onsuspend	proc :ptr
    put_ontimeupdate	proc :VARIANT
    get_ontimeupdate	proc :ptr
    put_onpause		proc :VARIANT
    get_onpause		proc :ptr
    put_onplay		proc :VARIANT
    get_onplay		proc :ptr
    put_onplaying	proc :VARIANT
    get_onplaying	proc :ptr
    put_onvolumechange	proc :VARIANT
    get_onvolumechange	proc :ptr
    put_onwaiting	proc :VARIANT
    get_onwaiting	proc :ptr
   .ends

endif

ifndef __IHTMLWindow8_INTERFACE_DEFINED__
define __IHTMLWindow8_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLWindow8, "3050f211-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLWindow8 : public IDispatch

    put_onmspointerdown proc :VARIANT
    get_onmspointerdown proc :ptr
    put_onmspointermove proc :VARIANT
    get_onmspointermove proc :ptr
    put_onmspointerup	proc :VARIANT
    get_onmspointerup	proc :ptr
    put_onmspointerover proc :VARIANT
    get_onmspointerover proc :ptr
    put_onmspointerout	proc :VARIANT
    get_onmspointerout	proc :ptr
    put_onmspointercancel proc :VARIANT
    get_onmspointercancel proc :ptr
    put_onmspointerhover proc :VARIANT
    get_onmspointerhover proc :ptr
    put_onmsgesturestart proc :VARIANT
    get_onmsgesturestart proc :ptr
    put_onmsgesturechange proc :VARIANT
    get_onmsgesturechange proc :ptr
    put_onmsgestureend	proc :VARIANT
    get_onmsgestureend	proc :ptr
    put_onmsgesturehold proc :VARIANT
    get_onmsgesturehold proc :ptr
    put_onmsgesturetap	proc :VARIANT
    get_onmsgesturetap	proc :ptr
    put_onmsgesturedoubletap proc :VARIANT
    get_onmsgesturedoubletap proc :ptr
    put_onmsinertiastart proc :VARIANT
    get_onmsinertiastart proc :ptr
    get_applicationCache proc :ptr
    put_onpopstate	proc :VARIANT
    get_onpopstate	proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_FramesCollection, "3050f7f6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLScreen_DISPINTERFACE_DEFINED__
define __DispHTMLScreen_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLScreen, "3050f591-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLScreen : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLScreen, "3050f35d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLWindow2_DISPINTERFACE_DEFINED__
define __DispHTMLWindow2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLWindow2, "3050f55d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLWindow2 : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLWindow2, "D48A6EC6-6A4A-11cf-94A7-444553540000")

ifndef __DispHTMLWindowProxy_DISPINTERFACE_DEFINED__
define __DispHTMLWindowProxy_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLWindowProxy, "3050f55e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLWindowProxy : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLWindowProxy, "3050f391-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLDocumentCompatibleInfo_INTERFACE_DEFINED__
define __IHTMLDocumentCompatibleInfo_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocumentCompatibleInfo, "3050f2d1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocumentCompatibleInfo : public IDispatch

    get_userAgent	proc :ptr
    get_version		proc :ptr
   .ends

endif

ifndef __IHTMLDocumentCompatibleInfoCollection_INTERFACE_DEFINED__
define __IHTMLDocumentCompatibleInfoCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocumentCompatibleInfoCollection, "3050f244-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocumentCompatibleInfoCollection : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispHTMLDocumentCompatibleInfo_DISPINTERFACE_DEFINED__
define __DispHTMLDocumentCompatibleInfo_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDocumentCompatibleInfo, "3050f53e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDocumentCompatibleInfo : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDocumentCompatibleInfo, "3051041b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLDocumentCompatibleInfoCollection_DISPINTERFACE_DEFINED__
define __DispHTMLDocumentCompatibleInfoCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDocumentCompatibleInfoCollection, "3050f53f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDocumentCompatibleInfoCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDocumentCompatibleInfoCollection, "30510419-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLDocumentEvents4_DISPINTERFACE_DEFINED__
define __HTMLDocumentEvents4_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLDocumentEvents4, "30510737-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLDocumentEvents4 : public IDispatch

   .ends

endif

ifndef __HTMLDocumentEvents3_DISPINTERFACE_DEFINED__
define __HTMLDocumentEvents3_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLDocumentEvents3, "3050f5a0-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLDocumentEvents3 : public IDispatch

   .ends

endif

ifndef __HTMLDocumentEvents2_DISPINTERFACE_DEFINED__
define __HTMLDocumentEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLDocumentEvents2, "3050f613-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLDocumentEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLDocumentEvents_DISPINTERFACE_DEFINED__
define __HTMLDocumentEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLDocumentEvents, "3050f260-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLDocumentEvents : public IDispatch

   .ends

endif

ifndef __ISVGSVGElement_INTERFACE_DEFINED__
define __ISVGSVGElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGSVGElement, "3050f5ed-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGSVGElement : public IDispatch

    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_width	proc :ptr
    get_width		proc :ptr
    putref_height	proc :ptr
    get_height		proc :ptr
    put_contentScriptType proc :BSTR
    get_contentScriptType proc :ptr
    put_contentStyleType proc :BSTR
    get_contentStyleType proc :ptr
    putref_viewport	proc :ptr
    get_viewport	proc :ptr
    put_pixelUnitToMillimeterX proc :FLOAT
    get_pixelUnitToMillimeterX proc :ptr
    put_pixelUnitToMillimeterY proc :FLOAT
    get_pixelUnitToMillimeterY proc :ptr
    put_screenPixelToMillimeterX proc :FLOAT
    get_screenPixelToMillimeterX proc :ptr
    put_screenPixelToMillimeterY proc :FLOAT
    get_screenPixelToMillimeterY proc :ptr
    put_useCurrentView	proc :VARIANT_BOOL
    get_useCurrentView	proc :ptr
    putref_currentView	proc :ptr
    get_currentView	proc :ptr
    put_currentScale	proc :FLOAT
    get_currentScale	proc :ptr
    putref_currentTranslate proc :ptr
    get_currentTranslate proc :ptr
    suspendRedraw	proc :ULONG, :ptr
    unsuspendRedraw	proc :ULONG
    unsuspendRedrawAll	proc
    forceRedraw		proc
    pauseAnimations	proc
    unpauseAnimations	proc
    animationsPaused	proc :ptr
    getCurrentTime	proc :ptr
    setCurrentTime	proc :FLOAT
    getIntersectionList proc :ptr, :ptr, :ptr
    getEnclosureList	proc :ptr, :ptr, :ptr
    checkIntersection	proc :ptr, :ptr, :ptr
    checkEnclosure	proc :ptr, :ptr, :ptr
    deselectAll		proc
    createSVGNumber	proc :ptr
    createSVGLength	proc :ptr
    createSVGAngle	proc :ptr
    createSVGPoint	proc :ptr
    createSVGMatrix	proc :ptr
    createSVGRect	proc :ptr
    createSVGTransform	proc :ptr
    createSVGTransformFromMatrix proc :ptr, :ptr
    getElementById	proc :BSTR, :ptr
   .ends

endif

ifndef __IDOMNodeIterator_INTERFACE_DEFINED__
define __IDOMNodeIterator_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMNodeIterator, "3050f838-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMNodeIterator : public IDispatch

    get_root		proc :ptr
    get_whatToShow	proc :ptr
    get_filter		proc :ptr
    get_expandEntityReferences proc :ptr
    nextNode		proc :ptr
    previousNode	proc :ptr
    detach		proc
   .ends

endif

ifndef __IDOMTreeWalker_INTERFACE_DEFINED__
define __IDOMTreeWalker_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMTreeWalker, "3051049d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMTreeWalker : public IDispatch

    get_root		proc :ptr
    get_whatToShow	proc :ptr
    get_filter		proc :ptr
    get_expandEntityReferences proc :ptr
    putref_currentNode	proc :ptr
    get_currentNode	proc :ptr
    parentNode		proc :ptr
    firstChild		proc :ptr
    lastChild		proc :ptr
    previousSibling	proc :ptr
    nextSibling		proc :ptr
    previousNode	proc :ptr
    nextNode		proc :ptr
   .ends

endif

ifndef __IDOMProcessingInstruction_INTERFACE_DEFINED__
define __IDOMProcessingInstruction_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMProcessingInstruction, "30510760-98b6-11cf-bb82-00aa00bdce0b")

.comdef IDOMProcessingInstruction : public IDispatch

    get_target		proc :ptr
    put_data		proc :BSTR
    get_data		proc :ptr
   .ends

endif

ifndef __IHTMLDocument3_INTERFACE_DEFINED__
define __IHTMLDocument3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument3, "3050f531-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument3 : public IDispatch

    releaseCapture	proc
    recalc		proc :VARIANT_BOOL
    createTextNode	proc :BSTR, :ptr
    get_documentElement proc :ptr
    get_uniqueID	proc :ptr
    attachEvent		proc :BSTR, :ptr, :ptr
    detachEvent		proc :BSTR, :ptr
    put_onrowsdelete	proc :VARIANT
    get_onrowsdelete	proc :ptr
    put_onrowsinserted	proc :VARIANT
    get_onrowsinserted	proc :ptr
    put_oncellchange	proc :VARIANT
    get_oncellchange	proc :ptr
    put_ondatasetchanged proc :VARIANT
    get_ondatasetchanged proc :ptr
    put_ondataavailable proc :VARIANT
    get_ondataavailable proc :ptr
    put_ondatasetcomplete proc :VARIANT
    get_ondatasetcomplete proc :ptr
    put_onpropertychange proc :VARIANT
    get_onpropertychange proc :ptr
    put_dir		proc :BSTR
    get_dir		proc :ptr
    put_oncontextmenu	proc :VARIANT
    get_oncontextmenu	proc :ptr
    put_onstop		proc :VARIANT
    get_onstop		proc :ptr
    createDocumentFragment proc :ptr
    get_parentDocument	proc :ptr
    put_enableDownload	proc :VARIANT_BOOL
    get_enableDownload	proc :ptr
    put_baseUrl		proc :BSTR
    get_baseUrl		proc :ptr
    get_childNodes	proc :ptr
    put_inheritStyleSheets proc :VARIANT_BOOL
    get_inheritStyleSheets proc :ptr
    put_onbeforeeditfocus proc :VARIANT
    get_onbeforeeditfocus proc :ptr
    getElementsByName	proc :BSTR, :ptr
    getElementById	proc :BSTR, :ptr
    getElementsByTagName proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLDocument4_INTERFACE_DEFINED__
define __IHTMLDocument4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument4, "3050f597-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument4 : public IDispatch

    focus		proc
    hasFocus		proc :ptr
    put_onselectionchange proc :VARIANT
    get_onselectionchange proc :ptr
    get_namespaces	proc :ptr
    createDocumentFromUrl proc :BSTR, :BSTR, :ptr
    put_media		proc :BSTR
    get_media		proc :ptr
    createEventObject	proc :ptr, :ptr
    fireEvent		proc :BSTR, :ptr, :ptr
    createRenderStyle	proc :BSTR, :ptr
    put_oncontrolselect proc :VARIANT
    get_oncontrolselect proc :ptr
    get_URLUnencoded	proc :ptr
   .ends

endif

ifndef __IHTMLDocument5_INTERFACE_DEFINED__
define __IHTMLDocument5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument5, "3050f25A-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument5 : public IDispatch

    put_onmousewheel	proc :VARIANT
    get_onmousewheel	proc :ptr
    get_doctype		proc :ptr
    get_implementation	proc :ptr
    createAttribute	proc :BSTR, :ptr
    createComment	proc :BSTR, :ptr
    put_onfocusin	proc :VARIANT
    get_onfocusin	proc :ptr
    put_onfocusout	proc :VARIANT
    get_onfocusout	proc :ptr
    put_onactivate	proc :VARIANT
    get_onactivate	proc :ptr
    put_ondeactivate	proc :VARIANT
    get_ondeactivate	proc :ptr
    put_onbeforeactivate proc :VARIANT
    get_onbeforeactivate proc :ptr
    put_onbeforedeactivate proc :VARIANT
    get_onbeforedeactivate proc :ptr
    get_compatMode	proc :ptr
   .ends

endif

ifndef __IHTMLDocument6_INTERFACE_DEFINED__
define __IHTMLDocument6_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument6, "3050f7ec-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument6 : public IDispatch

    get_compatible	proc :ptr
    get_documentMode	proc :ptr
    put_onstorage	proc :VARIANT
    get_onstorage	proc :ptr
    put_onstoragecommit proc :VARIANT
    get_onstoragecommit proc :ptr
    getElementById	proc :BSTR, :ptr
    updateSettings	proc
   .ends

endif

ifndef __IHTMLDocument8_INTERFACE_DEFINED__
define __IHTMLDocument8_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDocument8, "305104b6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDocument8 : public IDispatch

    put_onmscontentzoom proc :VARIANT
    get_onmscontentzoom proc :ptr
    put_onmspointerdown proc :VARIANT
    get_onmspointerdown proc :ptr
    put_onmspointermove proc :VARIANT
    get_onmspointermove proc :ptr
    put_onmspointerup	proc :VARIANT
    get_onmspointerup	proc :ptr
    put_onmspointerover proc :VARIANT
    get_onmspointerover proc :ptr
    put_onmspointerout	proc :VARIANT
    get_onmspointerout	proc :ptr
    put_onmspointercancel proc :VARIANT
    get_onmspointercancel proc :ptr
    put_onmspointerhover proc :VARIANT
    get_onmspointerhover proc :ptr
    put_onmsgesturestart proc :VARIANT
    get_onmsgesturestart proc :ptr
    put_onmsgesturechange proc :VARIANT
    get_onmsgesturechange proc :ptr
    put_onmsgestureend	proc :VARIANT
    get_onmsgestureend	proc :ptr
    put_onmsgesturehold proc :VARIANT
    get_onmsgesturehold proc :ptr
    put_onmsgesturetap	proc :VARIANT
    get_onmsgesturetap	proc :ptr
    put_onmsgesturedoubletap proc :VARIANT
    get_onmsgesturedoubletap proc :ptr
    put_onmsinertiastart proc :VARIANT
    get_onmsinertiastart proc :ptr
    elementsFromPoint	proc :FLOAT, :FLOAT, :ptr
    elementsFromRect	proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    put_onmsmanipulationstatechanged proc :VARIANT
    get_onmsmanipulationstatechanged proc :ptr
    put_msCapsLockWarningOff proc :VARIANT_BOOL
    get_msCapsLockWarningOff proc :ptr
   .ends

endif

ifndef __IDocumentEvent_INTERFACE_DEFINED__
define __IDocumentEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDocumentEvent, "3050f820-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDocumentEvent : public IDispatch

    createEvent		proc :BSTR, :ptr
   .ends

endif

ifndef __IDocumentRange_INTERFACE_DEFINED__
define __IDocumentRange_INTERFACE_DEFINED__
DEFINE_IIDX(IDocumentRange, "305107b4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDocumentRange : public IDispatch

    createRange		proc :ptr
   .ends

endif

ifndef __IDocumentSelector_INTERFACE_DEFINED__
define __IDocumentSelector_INTERFACE_DEFINED__
DEFINE_IIDX(IDocumentSelector, "3050f38c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDocumentSelector : public IDispatch

    querySelector	proc :BSTR, :ptr
    querySelectorAll	proc :BSTR, :ptr
   .ends

endif

ifndef __IDocumentTraversal_INTERFACE_DEFINED__
define __IDocumentTraversal_INTERFACE_DEFINED__
DEFINE_IIDX(IDocumentTraversal, "3050f52b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDocumentTraversal : public IDispatch

    createNodeIterator	proc :ptr, :LONG, :ptr, :VARIANT_BOOL, :ptr
    createTreeWalker	proc :ptr, :LONG, :ptr, :VARIANT_BOOL, :ptr
   .ends

endif

ifndef __DispHTMLDocument_DISPINTERFACE_DEFINED__
define __DispHTMLDocument_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDocument, "3050f55f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDocument : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDocument, "25336920-03F9-11cf-8FD0-00AA00686F13")

ifndef __DWebBridgeEvents_DISPINTERFACE_DEFINED__
define __DWebBridgeEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DWebBridgeEvents, "A6D897FF-0A95-11d1-B0BA-006008166E11")

.comdef DWebBridgeEvents : public IDispatch

   .ends

endif

ifndef __IWebBridge_INTERFACE_DEFINED__
define __IWebBridge_INTERFACE_DEFINED__
DEFINE_IIDX(IWebBridge, "3050f598-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWebBridge : public IDispatch

    put_URL		proc :BSTR
    get_URL		proc :ptr
    put_Scrollbar	proc :VARIANT_BOOL
    get_Scrollbar	proc :ptr
    put_embed		proc :VARIANT_BOOL
    get_embed		proc :ptr
    get_event		proc :ptr
    get_readyState	proc :ptr
    AboutBox		proc
   .ends

endif

ifndef __IWBScriptControl_INTERFACE_DEFINED__
define __IWBScriptControl_INTERFACE_DEFINED__
DEFINE_IIDX(IWBScriptControl, "3050f617-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWBScriptControl : public IDispatch

    raiseEvent		proc :BSTR, :VARIANT
    bubbleEvent		proc
    setContextMenu	proc :VARIANT
    put_selectableContent proc :VARIANT_BOOL
    get_selectableContent proc :ptr
    get_frozen		proc :ptr
    put_scrollbar	proc :VARIANT_BOOL
    get_scrollbar	proc :ptr
    get_version		proc :ptr
    get_visibility	proc :ptr
    put_onvisibilitychange proc :VARIANT
    get_onvisibilitychange proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_Scriptlet, "AE24FDAE-03C6-11D1-8B76-0080C744F389")

ifndef __IHTMLEmbedElement_INTERFACE_DEFINED__
define __IHTMLEmbedElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEmbedElement, "3050f2b3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEmbedElement : public IDispatch

    put_hidden		proc :BSTR
    get_hidden		proc :ptr
    get_palette		proc :ptr
    get_pluginspage	proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    put_units		proc :BSTR
    get_units		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
   .ends

endif

ifndef __IHTMLEmbedElement2_INTERFACE_DEFINED__
define __IHTMLEmbedElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEmbedElement2, "3050f618-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEmbedElement2 : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
    get_pluginspage	proc :ptr
   .ends

endif

ifndef __DispHTMLEmbed_DISPINTERFACE_DEFINED__
define __DispHTMLEmbed_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLEmbed, "3050f52e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLEmbed : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLEmbed, "3050f25d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLMapEvents2_DISPINTERFACE_DEFINED__
define __HTMLMapEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLMapEvents2, "3050f61e-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLMapEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLMapEvents_DISPINTERFACE_DEFINED__
define __HTMLMapEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLMapEvents, "3050f3ba-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLMapEvents : public IDispatch

   .ends

endif

ifndef __IHTMLAreasCollection_INTERFACE_DEFINED__
define __IHTMLAreasCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAreasCollection, "3050f619-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAreasCollection : public IDispatch

    put_length		proc :LONG
    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :VARIANT, :VARIANT, :ptr
    tags		proc :VARIANT, :ptr
    _add		proc :ptr, :VARIANT
    remove		proc :LONG
   .ends

endif

ifndef __IHTMLAreasCollection2_INTERFACE_DEFINED__
define __IHTMLAreasCollection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAreasCollection2, "3050f61a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAreasCollection2 : public IDispatch

    urns		proc :VARIANT, :ptr
   .ends

endif

ifndef __IHTMLAreasCollection3_INTERFACE_DEFINED__
define __IHTMLAreasCollection3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAreasCollection3, "3050f61b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAreasCollection3 : public IDispatch

    namedItem		proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLAreasCollection4_INTERFACE_DEFINED__
define __IHTMLAreasCollection4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAreasCollection4, "3050f2a7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAreasCollection4 : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
    namedItem		proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLMapElement_INTERFACE_DEFINED__
define __IHTMLMapElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMapElement, "3050f2bd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMapElement : public IDispatch

    get_areas		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
   .ends

endif

ifndef __DispHTMLAreasCollection_DISPINTERFACE_DEFINED__
define __DispHTMLAreasCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLAreasCollection, "3050f56a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLAreasCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLAreasCollection, "3050f4ca-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLMapElement_DISPINTERFACE_DEFINED__
define __DispHTMLMapElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMapElement, "3050f526-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMapElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMapElement, "3050f271-98b5-11cf-bb82-00aa00bdce0b")
ifndef __HTMLAreaEvents2_DISPINTERFACE_DEFINED__
define __HTMLAreaEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLAreaEvents2, "3050f611-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLAreaEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLAreaEvents_DISPINTERFACE_DEFINED__
define __HTMLAreaEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLAreaEvents, "3050f366-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLAreaEvents : public IDispatch

   .ends

endif

ifndef __IHTMLAreaElement_INTERFACE_DEFINED__
define __IHTMLAreaElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAreaElement, "3050f2af-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAreaElement : public IDispatch

    put_shape		proc :BSTR
    get_shape		proc :ptr
    put_coords		proc :BSTR
    get_coords		proc :ptr
    put_href		proc :BSTR
    get_href		proc :ptr
    put_target		proc :BSTR
    get_target		proc :ptr
    put_alt		proc :BSTR
    get_alt		proc :ptr
    put_noHref		proc :VARIANT_BOOL
    get_noHref		proc :ptr
    put_host		proc :BSTR
    get_host		proc :ptr
    put_hostname	proc :BSTR
    get_hostname	proc :ptr
    put_pathname	proc :BSTR
    get_pathname	proc :ptr
    put_port		proc :BSTR
    get_port		proc :ptr
    put_protocol	proc :BSTR
    get_protocol	proc :ptr
    put_search		proc :BSTR
    get_search		proc :ptr
    put_hash		proc :BSTR
    get_hash		proc :ptr
    put_onblur		proc :VARIANT
    get_onblur		proc :ptr
    put_onfocus		proc :VARIANT
    get_onfocus		proc :ptr
    put_tabIndex	proc :sword
    get_tabIndex	proc :ptr
    focus		proc
    blur		proc
   .ends

endif

ifndef __IHTMLAreaElement2_INTERFACE_DEFINED__
define __IHTMLAreaElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAreaElement2, "3050f2c3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAreaElement2 : public IDispatch

    put_shape		proc :BSTR
    get_shape		proc :ptr
    put_coords		proc :BSTR
    get_coords		proc :ptr
    put_href		proc :BSTR
    get_href		proc :ptr
   .ends

endif

ifndef __DispHTMLAreaElement_DISPINTERFACE_DEFINED__
define __DispHTMLAreaElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLAreaElement, "3050f503-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLAreaElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLAreaElement, "3050f283-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLTableCaption_INTERFACE_DEFINED__
define __IHTMLTableCaption_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCaption, "3050f5d2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCaption : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
    put_vAlign		proc :BSTR
    get_vAlign		proc :ptr
   .ends

endif

ifndef __DispHTMLTableCaption_DISPINTERFACE_DEFINED__
define __DispHTMLTableCaption_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTableCaption, "3050f508-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTableCaption : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTableCaption, "3050f2ec-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLCommentElement_INTERFACE_DEFINED__
define __IHTMLCommentElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCommentElement, "3050f821-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCommentElement : public IDispatch

    put_text		proc :BSTR
    get_text		proc :ptr
    put_atomic		proc :LONG
    get_atomic		proc :ptr
   .ends

endif

ifndef __IHTMLCommentElement2_INTERFACE_DEFINED__
define __IHTMLCommentElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCommentElement2, "30510435-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCommentElement2 : public IDispatch

    put_data		proc :BSTR
    get_data		proc :ptr
    get_length		proc :ptr
    substringData	proc :LONG, :LONG, :ptr
    appendData		proc :BSTR
    insertData		proc :LONG, :BSTR
    deleteData		proc :LONG, :LONG
    replaceData		proc :LONG, :LONG, :BSTR
   .ends

endif

ifndef __IHTMLCommentElement3_INTERFACE_DEFINED__
define __IHTMLCommentElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCommentElement3, "3050f2b2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCommentElement3 : public IDispatch

    substringData	proc :LONG, :LONG, :ptr
    insertData		proc :LONG, :BSTR
    deleteData		proc :LONG, :LONG
    replaceData		proc :LONG, :LONG, :BSTR
   .ends

endif

ifndef __DispHTMLCommentElement_DISPINTERFACE_DEFINED__
define __DispHTMLCommentElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCommentElement, "3050f50a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCommentElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCommentElement, "3050f317-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLPhraseElement_INTERFACE_DEFINED__
define __IHTMLPhraseElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPhraseElement, "3050f2a4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPhraseElement : public IDispatch

   .ends

endif

ifndef __IHTMLPhraseElement2_INTERFACE_DEFINED__
define __IHTMLPhraseElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPhraseElement2, "3050f2a6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPhraseElement2 : public IDispatch

    put_cite		proc :BSTR
    get_cite		proc :ptr
    put_dateTime	proc :BSTR
    get_dateTime	proc :ptr
   .ends

endif

ifndef __IHTMLPhraseElement3_INTERFACE_DEFINED__
define __IHTMLPhraseElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPhraseElement3, "3050f2d2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPhraseElement3 : public IDispatch

    put_cite		proc :BSTR
    get_cite		proc :ptr
   .ends

endif

ifndef __IHTMLSpanElement_INTERFACE_DEFINED__
define __IHTMLSpanElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSpanElement, "3050f2ad-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSpanElement : public IDispatch

   .ends

endif

ifndef __DispHTMLPhraseElement_DISPINTERFACE_DEFINED__
define __DispHTMLPhraseElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLPhraseElement, "3050f52d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLPhraseElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLPhraseElement, "3050f26e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLSpanElement_DISPINTERFACE_DEFINED__
define __DispHTMLSpanElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLSpanElement, "3050f548-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLSpanElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLSpanElement, "3050f3f5-98b4-11cf-bb82-00aa00bdce0b")

ifndef __HTMLTableEvents2_DISPINTERFACE_DEFINED__
define __HTMLTableEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLTableEvents2, "3050f623-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLTableEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLTableEvents_DISPINTERFACE_DEFINED__
define __HTMLTableEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLTableEvents, "3050f407-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLTableEvents : public IDispatch

   .ends

endif

ifndef __IHTMLTableSection_INTERFACE_DEFINED__
define __IHTMLTableSection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableSection, "3050f2bc-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableSection : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
    put_vAlign		proc :BSTR
    get_vAlign		proc :ptr
    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    get_rows		proc :ptr
    insertRow		proc :LONG, :ptr
    deleteRow		proc :LONG
   .ends

endif

ifndef __IHTMLTable_INTERFACE_DEFINED__
define __IHTMLTable_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTable, "3050f2c2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTable : public IDispatch

    put_cols		proc :LONG
    get_cols		proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_frame		proc :BSTR
    get_frame		proc :ptr
    put_rules		proc :BSTR
    get_rules		proc :ptr
    put_cellSpacing	proc :VARIANT
    get_cellSpacing	proc :ptr
    put_cellPadding	proc :VARIANT
    get_cellPadding	proc :ptr
    put_background	proc :BSTR
    get_background	proc :ptr
    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    put_borderColor	proc :VARIANT
    get_borderColor	proc :ptr
    put_borderColorLight proc :VARIANT
    get_borderColorLight proc :ptr
    put_borderColorDark proc :VARIANT
    get_borderColorDark proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    refresh		proc
    get_rows		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    put_dataPageSize	proc :LONG
    get_dataPageSize	proc :ptr
    nextPage		proc
    previousPage	proc
    get_tHead		proc :ptr
    get_tFoot		proc :ptr
    get_tBodies		proc :ptr
    get_caption		proc :ptr
    createTHead		proc :ptr
    deleteTHead		proc
    createTFoot		proc :ptr
    deleteTFoot		proc
    createCaption	proc :ptr
    deleteCaption	proc
    insertRow		proc :LONG, :ptr
    deleteRow		proc :LONG
    get_readyState	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
   .ends

endif

ifndef __IHTMLTable2_INTERFACE_DEFINED__
define __IHTMLTable2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTable2, "3050f2d4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTable2 : public IDispatch

    firstPage		proc
    lastPage		proc
    get_cells		proc :ptr
    moveRow		proc :LONG, :LONG, :ptr
   .ends

endif

ifndef __IHTMLTable3_INTERFACE_DEFINED__
define __IHTMLTable3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTable3, "3050f57d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTable3 : public IDispatch

    put_summary		proc :BSTR
    get_summary		proc :ptr
   .ends

endif

ifndef __IHTMLTable4_INTERFACE_DEFINED__
define __IHTMLTable4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTable4, "3050f2aa-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTable4 : public IDispatch

    putref_tHead	proc :ptr
    get_tHead		proc :ptr
    putref_tFoot	proc :ptr
    get_tFoot		proc :ptr
    putref_caption	proc :ptr
    get_caption		proc :ptr
    insertRow		proc :LONG, :ptr
    deleteRow		proc :LONG
    createTBody		proc :ptr
   .ends

endif

ifndef __IHTMLTableCol_INTERFACE_DEFINED__
define __IHTMLTableCol_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCol, "3050f2d3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCol : public IDispatch

    put_span		proc :LONG
    get_span		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    put_vAlign		proc :BSTR
    get_vAlign		proc :ptr
   .ends

endif

ifndef __IHTMLTableCol2_INTERFACE_DEFINED__
define __IHTMLTableCol2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCol2, "3050f521-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCol2 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
   .ends

endif

ifndef __IHTMLTableCol3_INTERFACE_DEFINED__
define __IHTMLTableCol3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCol3, "3050f54d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCol3 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
   .ends

endif

ifndef __IHTMLTableSection2_INTERFACE_DEFINED__
define __IHTMLTableSection2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableSection2, "3050f2bb-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableSection2 : public IDispatch

    moveRow		proc :LONG, :LONG, :ptr
   .ends

endif

ifndef __IHTMLTableSection3_INTERFACE_DEFINED__
define __IHTMLTableSection3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableSection3, "305106f3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableSection3 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
   .ends

endif

ifndef __IHTMLTableSection4_INTERFACE_DEFINED__
define __IHTMLTableSection4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableSection4, "3050f51f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableSection4 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
    insertRow		proc :LONG, :ptr
    deleteRow		proc :LONG
   .ends

endif

ifndef __IHTMLTableRow_INTERFACE_DEFINED__
define __IHTMLTableRow_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableRow, "3050f61f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableRow : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
    put_vAlign		proc :BSTR
    get_vAlign		proc :ptr
    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    put_borderColor	proc :VARIANT
    get_borderColor	proc :ptr
    put_borderColorLight proc :VARIANT
    get_borderColorLight proc :ptr
    put_borderColorDark proc :VARIANT
    get_borderColorDark proc :ptr
    get_rowIndex	proc :ptr
    get_sectionRowIndex proc :ptr
    get_cells		proc :ptr
    insertCell		proc :LONG, :ptr
    deleteCell		proc :LONG
   .ends

endif

ifndef __IHTMLTableRow2_INTERFACE_DEFINED__
define __IHTMLTableRow2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableRow2, "3050f2b8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableRow2 : public IDispatch

    put_height		proc :VARIANT
    get_height		proc :ptr
   .ends

endif

ifndef __IHTMLTableRow3_INTERFACE_DEFINED__
define __IHTMLTableRow3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableRow3, "3050f2b5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableRow3 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
   .ends

endif

ifndef __IHTMLTableRow4_INTERFACE_DEFINED__
define __IHTMLTableRow4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableRow4, "3050f527-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableRow4 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
    insertCell		proc :LONG, :ptr
    deleteCell		proc :LONG
   .ends

endif

ifndef __IHTMLTableRowMetrics_INTERFACE_DEFINED__
define __IHTMLTableRowMetrics_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableRowMetrics, "3050f81c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableRowMetrics : public IDispatch

    get_clientHeight	proc :ptr
    get_clientWidth	proc :ptr
    get_clientTop	proc :ptr
    get_clientLeft	proc :ptr
   .ends

endif

ifndef __IHTMLTableCell_INTERFACE_DEFINED__
define __IHTMLTableCell_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCell, "3050f81d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCell : public IDispatch

    put_rowSpan		proc :LONG
    get_rowSpan		proc :ptr
    put_colSpan		proc :LONG
    get_colSpan		proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    put_vAlign		proc :BSTR
    get_vAlign		proc :ptr
    put_bgColor		proc :VARIANT
    get_bgColor		proc :ptr
    put_noWrap		proc :VARIANT_BOOL
    get_noWrap		proc :ptr
    put_background	proc :BSTR
    get_background	proc :ptr
    put_borderColor	proc :VARIANT
    get_borderColor	proc :ptr
    put_borderColorLight proc :VARIANT
    get_borderColorLight proc :ptr
    put_borderColorDark proc :VARIANT
    get_borderColorDark proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    get_cellIndex	proc :ptr
   .ends

endif

ifndef __IHTMLTableCell2_INTERFACE_DEFINED__
define __IHTMLTableCell2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCell2, "3051042f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCell2 : public IDispatch

    put_abbr		proc :BSTR
    get_abbr		proc :ptr
    put_axis		proc :BSTR
    get_axis		proc :ptr
    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
    put_headers		proc :BSTR
    get_headers		proc :ptr
    put_scope		proc :BSTR
    get_scope		proc :ptr
   .ends

endif

ifndef __IHTMLTableCell3_INTERFACE_DEFINED__
define __IHTMLTableCell3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTableCell3, "3050f322-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTableCell3 : public IDispatch

    put_ch		proc :BSTR
    get_ch		proc :ptr
    put_chOff		proc :BSTR
    get_chOff		proc :ptr
   .ends

endif

ifndef __DispHTMLTable_DISPINTERFACE_DEFINED__
define __DispHTMLTable_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTable, "3050f532-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTable : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTable, "3050f26b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLTableCol_DISPINTERFACE_DEFINED__
define __DispHTMLTableCol_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTableCol, "3050f533-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTableCol : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTableCol, "3050f26c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLTableSection_DISPINTERFACE_DEFINED__
define __DispHTMLTableSection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTableSection, "3050f534-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTableSection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTableSection, "3050f2e9-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLTableRow_DISPINTERFACE_DEFINED__
define __DispHTMLTableRow_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTableRow, "3050f535-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTableRow : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTableRow, "3050f26d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLTableCell_DISPINTERFACE_DEFINED__
define __DispHTMLTableCell_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTableCell, "3050f536-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTableCell : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLTableCell, "3050f246-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLScriptEvents2_DISPINTERFACE_DEFINED__
define __HTMLScriptEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLScriptEvents2, "3050f621-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLScriptEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLScriptEvents_DISPINTERFACE_DEFINED__
define __HTMLScriptEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLScriptEvents, "3050f3e2-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLScriptEvents : public IDispatch

   .ends

endif

ifndef __IHTMLScriptElement_INTERFACE_DEFINED__
define __IHTMLScriptElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScriptElement, "3050f203-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScriptElement : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
    put_htmlFor		proc :BSTR
    get_htmlFor		proc :ptr
    put_event		proc :BSTR
    get_event		proc :ptr
    put_text		proc :BSTR
    get_text		proc :ptr
    put_defer		proc :VARIANT_BOOL
    get_defer		proc :ptr
    get_readyState	proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
   .ends

endif

ifndef __IHTMLScriptElement2_INTERFACE_DEFINED__
define __IHTMLScriptElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScriptElement2, "3050f81f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScriptElement2 : public IDispatch

    put_charset		proc :BSTR
    get_charset		proc :ptr
   .ends

endif

ifndef __IHTMLScriptElement3_INTERFACE_DEFINED__
define __IHTMLScriptElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScriptElement3, "30510495-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScriptElement3 : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
   .ends

endif

ifndef __IHTMLScriptElement4_INTERFACE_DEFINED__
define __IHTMLScriptElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLScriptElement4, "3050f204-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLScriptElement4 : public IDispatch

    get_usedCharset	proc :ptr
   .ends

endif

ifndef __DispHTMLScriptElement_DISPINTERFACE_DEFINED__
define __DispHTMLScriptElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLScriptElement, "3050f530-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLScriptElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLScriptElement, "3050f28c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLNoShowElement_INTERFACE_DEFINED__
define __IHTMLNoShowElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLNoShowElement, "30510420-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLNoShowElement : public IDispatch

   .ends

endif
ifndef __DispHTMLNoShowElement_DISPINTERFACE_DEFINED__
define __DispHTMLNoShowElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLNoShowElement, "3050f528-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLNoShowElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLNoShowElement, "3050f38b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLObjectElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLObjectElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLObjectElementEvents2, "3050f620-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLObjectElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLObjectElementEvents_DISPINTERFACE_DEFINED__
define __HTMLObjectElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLObjectElementEvents, "3050f3c4-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLObjectElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLObjectElement_INTERFACE_DEFINED__
define __IHTMLObjectElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLObjectElement, "3050f206-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLObjectElement : public IDispatch

    get_object		proc :ptr
    get_classid		proc :ptr
    get_data		proc :ptr
    putref_recordset	proc :ptr
    get_recordset	proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_codeBase	proc :BSTR
    get_codeBase	proc :ptr
    put_codeType	proc :BSTR
    get_codeType	proc :ptr
    put_code		proc :BSTR
    get_code		proc :ptr
    get_BaseHref	proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
    get_form		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
    put_height		proc :VARIANT
    get_height		proc :ptr
    get_readyState	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_altHtml		proc :BSTR
    get_altHtml		proc :ptr
    put_vspace		proc :LONG
    get_vspace		proc :ptr
    put_hspace		proc :LONG
    get_hspace		proc :ptr
   .ends

endif

ifndef __IHTMLObjectElement2_INTERFACE_DEFINED__
define __IHTMLObjectElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLObjectElement2, "3050f82f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLObjectElement2 : public IDispatch

    namedRecordset	proc :BSTR, :ptr, :ptr
    put_classid		proc :BSTR
    get_classid		proc :ptr
    put_data		proc :BSTR
    get_data		proc :ptr
   .ends

endif

ifndef __IHTMLObjectElement3_INTERFACE_DEFINED__
define __IHTMLObjectElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLObjectElement3, "3050f207-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLObjectElement3 : public IDispatch

    put_archive		proc :BSTR
    get_archive		proc :ptr
    put_alt		proc :BSTR
    get_alt		proc :ptr
    put_declare		proc :VARIANT_BOOL
    get_declare		proc :ptr
    put_standby		proc :BSTR
    get_standby		proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_useMap		proc :BSTR
    get_useMap		proc :ptr
   .ends

endif

ifndef __IHTMLObjectElement4_INTERFACE_DEFINED__
define __IHTMLObjectElement4_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLObjectElement4, "3050f560-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLObjectElement4 : public IDispatch

    get_contentDocument proc :ptr
    put_codeBase	proc :BSTR
    get_codeBase	proc :ptr
    put_data		proc :BSTR
    get_data		proc :ptr
   .ends

endif

ifndef __IHTMLObjectElement5_INTERFACE_DEFINED__
define __IHTMLObjectElement5_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLObjectElement5, "3050f561-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLObjectElement5 : public IDispatch

    put_object		proc :BSTR
    get_object		proc :ptr
   .ends

endif

ifndef __IHTMLParamElement_INTERFACE_DEFINED__
define __IHTMLParamElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLParamElement, "3050f516-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLParamElement : public IDispatch

    put_name		proc :BSTR
    get_name		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
    put_valueType	proc :BSTR
    get_valueType	proc :ptr
   .ends

endif

ifndef __IHTMLParamElement2_INTERFACE_DEFINED__
define __IHTMLParamElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLParamElement2, "3050f517-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLParamElement2 : public IDispatch

    put_name		proc :BSTR
    get_name		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
    put_value		proc :BSTR
    get_value		proc :ptr
    put_valueType	proc :BSTR
    get_valueType	proc :ptr
   .ends

endif

ifndef __DispHTMLObjectElement_DISPINTERFACE_DEFINED__
define __DispHTMLObjectElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLObjectElement, "3050f529-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLObjectElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLObjectElement, "3050f24e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLParamElement_DISPINTERFACE_DEFINED__
define __DispHTMLParamElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLParamElement, "3050f590-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLParamElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLParamElement, "3050f83e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLFrameSiteEvents2_DISPINTERFACE_DEFINED__
define __HTMLFrameSiteEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLFrameSiteEvents2, "3050f7ff-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLFrameSiteEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLFrameSiteEvents_DISPINTERFACE_DEFINED__
define __HTMLFrameSiteEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLFrameSiteEvents, "3050f800-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLFrameSiteEvents : public IDispatch

   .ends

endif

ifndef __IHTMLFrameBase2_INTERFACE_DEFINED__
define __IHTMLFrameBase2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameBase2, "3050f518-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameBase2 : public IDispatch

    get_contentWindow	proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    get_readyState	proc :ptr
    put_allowTransparency proc :VARIANT_BOOL
    get_allowTransparency proc :ptr
   .ends

endif

ifndef __IHTMLFrameBase3_INTERFACE_DEFINED__
define __IHTMLFrameBase3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameBase3, "3050f519-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameBase3 : public IDispatch

    put_longDesc	proc :BSTR
    get_longDesc	proc :ptr
   .ends

endif

ifndef __DispHTMLFrameBase_DISPINTERFACE_DEFINED__
define __DispHTMLFrameBase_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLFrameBase, "3050f541-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLFrameBase : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLFrameBase, "3050f312-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLFrameElement_INTERFACE_DEFINED__
define __IHTMLFrameElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameElement, "3050f51a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameElement : public IDispatch

    put_borderColor	proc :VARIANT
    get_borderColor	proc :ptr
   .ends

endif

ifndef __IHTMLFrameElement2_INTERFACE_DEFINED__
define __IHTMLFrameElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameElement2, "3050f202-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameElement2 : public IDispatch

    put_height		proc :VARIANT
    get_height		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
   .ends

endif

ifndef __IHTMLFrameElement3_INTERFACE_DEFINED__
define __IHTMLFrameElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameElement3, "3050f504-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameElement3 : public IDispatch

    get_contentDocument proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    put_longDesc	proc :BSTR
    get_longDesc	proc :ptr
    put_frameBorder	proc :BSTR
    get_frameBorder	proc :ptr
   .ends

endif

ifndef __DispHTMLFrameElement_DISPINTERFACE_DEFINED__
define __DispHTMLFrameElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLFrameElement, "3050f513-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLFrameElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLFrameElement, "3050f314-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLIFrameElement_INTERFACE_DEFINED__
define __IHTMLIFrameElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLIFrameElement, "3050f209-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLIFrameElement : public IDispatch

    put_vspace		proc :LONG
    get_vspace		proc :ptr
    put_hspace		proc :LONG
    get_hspace		proc :ptr
    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __IHTMLIFrameElement2_INTERFACE_DEFINED__
define __IHTMLIFrameElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLIFrameElement2, "3050f539-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLIFrameElement2 : public IDispatch

    put_height		proc :VARIANT
    get_height		proc :ptr
    put_width		proc :VARIANT
    get_width		proc :ptr
   .ends

endif

ifndef __IHTMLIFrameElement3_INTERFACE_DEFINED__
define __IHTMLIFrameElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLIFrameElement3, "305107c5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLIFrameElement3 : public IDispatch

    get_contentDocument proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    put_longDesc	proc :BSTR
    get_longDesc	proc :ptr
    put_frameBorder	proc :BSTR
    get_frameBorder	proc :ptr
   .ends

endif

ifndef __DispHTMLIFrame_DISPINTERFACE_DEFINED__
define __DispHTMLIFrame_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLIFrame, "3050f51b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLIFrame : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLIFrame, "3050f316-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLDivPosition_INTERFACE_DEFINED__
define __IHTMLDivPosition_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDivPosition, "FECEAAA2-8405-11cf-8BA1-00AA00476DA6")

.comdef IHTMLDivPosition : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __IHTMLFieldSetElement_INTERFACE_DEFINED__
define __IHTMLFieldSetElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFieldSetElement, "3050f3fc-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFieldSetElement : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __IHTMLFieldSetElement2_INTERFACE_DEFINED__
define __IHTMLFieldSetElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFieldSetElement2, "3050f3fd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFieldSetElement2 : public IDispatch

    get_form		proc :ptr
   .ends

endif

ifndef __IHTMLLegendElement_INTERFACE_DEFINED__
define __IHTMLLegendElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLegendElement, "3050f401-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLLegendElement : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __IHTMLLegendElement2_INTERFACE_DEFINED__
define __IHTMLLegendElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLLegendElement2, "FECEAAA5-8405-11cf-8BA1-00AA00476DA6")

.comdef IHTMLLegendElement2 : public IDispatch

    get_form		proc :ptr
   .ends

endif

ifndef __DispHTMLDivPosition_DISPINTERFACE_DEFINED__
define __DispHTMLDivPosition_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLDivPosition, "3050f50f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLDivPosition : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLDivPosition, "3050f249-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLFieldSetElement_DISPINTERFACE_DEFINED__
define __DispHTMLFieldSetElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLFieldSetElement, "3050f545-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLFieldSetElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLFieldSetElement, "3050f3e8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLLegendElement_DISPINTERFACE_DEFINED__
define __DispHTMLLegendElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLLegendElement, "3050f546-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLLegendElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLLegendElement, "3050f3e9-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLSpanFlow_INTERFACE_DEFINED__
define __IHTMLSpanFlow_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSpanFlow, "305107cf-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSpanFlow : public IDispatch

    put_align		proc :BSTR
    get_align		proc :ptr
   .ends

endif

ifndef __DispHTMLSpanFlow_DISPINTERFACE_DEFINED__
define __DispHTMLSpanFlow_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLSpanFlow, "3050f544-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLSpanFlow : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLSpanFlow, "3050f3e6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLFrameSetElement_INTERFACE_DEFINED__
define __IHTMLFrameSetElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameSetElement, "30510804-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameSetElement : public IDispatch

    put_rows		proc :BSTR
    get_rows		proc :ptr
    put_cols		proc :BSTR
    get_cols		proc :ptr
    put_border		proc :VARIANT
    get_border		proc :ptr
    put_borderColor	proc :VARIANT
    get_borderColor	proc :ptr
    put_frameBorder	proc :BSTR
    get_frameBorder	proc :ptr
    put_frameSpacing	proc :VARIANT
    get_frameSpacing	proc :ptr
    put_name		proc :BSTR
    get_name		proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onunload	proc :VARIANT
    get_onunload	proc :ptr
    put_onbeforeunload	proc :VARIANT
    get_onbeforeunload	proc :ptr
   .ends

endif

ifndef __IHTMLFrameSetElement2_INTERFACE_DEFINED__
define __IHTMLFrameSetElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameSetElement2, "163BB1E0-6E00-11cf-837A-48DC04C10000")

.comdef IHTMLFrameSetElement2 : public IDispatch

    put_onbeforeprint	proc :VARIANT
    get_onbeforeprint	proc :ptr
    put_onafterprint	proc :VARIANT
    get_onafterprint	proc :ptr
   .ends

endif

ifndef __IHTMLFrameSetElement3_INTERFACE_DEFINED__
define __IHTMLFrameSetElement3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFrameSetElement3, "3050f549-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFrameSetElement3 : public IDispatch

    put_onhashchange	proc :VARIANT
    get_onhashchange	proc :ptr
    put_onmessage	proc :VARIANT
    get_onmessage	proc :ptr
    put_onoffline	proc :VARIANT
    get_onoffline	proc :ptr
    put_ononline	proc :VARIANT
    get_ononline	proc :ptr
    put_onstorage	proc :VARIANT
    get_onstorage	proc :ptr
   .ends

endif

ifndef __DispHTMLFrameSetSite_DISPINTERFACE_DEFINED__
define __DispHTMLFrameSetSite_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLFrameSetSite, "3050f514-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLFrameSetSite : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLFrameSetSite, "3050f31A-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLBGsound_INTERFACE_DEFINED__
define __IHTMLBGsound_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLBGsound, "3050f54a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLBGsound : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
    put_loop		proc :VARIANT
    get_loop		proc :ptr
    put_volume		proc :VARIANT
    get_volume		proc :ptr
    put_balance		proc :VARIANT
    get_balance		proc :ptr
   .ends

endif

ifndef __DispHTMLBGsound_DISPINTERFACE_DEFINED__
define __DispHTMLBGsound_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLBGsound, "3050f53c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLBGsound : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLBGsound, "3050f370-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLFontNamesCollection_INTERFACE_DEFINED__
define __IHTMLFontNamesCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFontNamesCollection, "3050f54c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFontNamesCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLFontSizesCollection_INTERFACE_DEFINED__
define __IHTMLFontSizesCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLFontSizesCollection, "3050f54e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLFontSizesCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    get_forFont		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLOptionsHolder_INTERFACE_DEFINED__
define __IHTMLOptionsHolder_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLOptionsHolder, "3050f4ce-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLOptionsHolder : public IDispatch

    get_document	proc :ptr
    get_fonts		proc :ptr
    put_execArg		proc :VARIANT
    get_execArg		proc :ptr
    put_errorLine	proc :LONG
    get_errorLine	proc :ptr
    put_errorCharacter	proc :LONG
    get_errorCharacter	proc :ptr
    put_errorCode	proc :LONG
    get_errorCode	proc :ptr
    put_errorMessage	proc :BSTR
    get_errorMessage	proc :ptr
    put_errorDebug	proc :VARIANT_BOOL
    get_errorDebug	proc :ptr
    get_unsecuredWindowOfDocument proc :ptr
    put_findText	proc :BSTR
    get_findText	proc :ptr
    put_anythingAfterFrameset proc :VARIANT_BOOL
    get_anythingAfterFrameset proc :ptr
    sizes		proc :BSTR, :ptr
    openfiledlg		proc :VARIANT, :VARIANT, :VARIANT, :VARIANT, :ptr
    savefiledlg		proc :VARIANT, :VARIANT, :VARIANT, :VARIANT, :ptr
    choosecolordlg	proc :VARIANT, :ptr
    showSecurityInfo	proc
    isApartmentModel	proc :ptr, :ptr
    getCharset		proc :BSTR, :ptr
    get_secureConnectionInfo proc :ptr
   .ends

endif

ifndef __HTMLStyleElementEvents2_DISPINTERFACE_DEFINED__
define __HTMLStyleElementEvents2_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLStyleElementEvents2, "3050f615-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLStyleElementEvents2 : public IDispatch

   .ends

endif

ifndef __HTMLStyleElementEvents_DISPINTERFACE_DEFINED__
define __HTMLStyleElementEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLStyleElementEvents, "3050f3cb-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLStyleElementEvents : public IDispatch

   .ends

endif

ifndef __IHTMLStyleElement_INTERFACE_DEFINED__
define __IHTMLStyleElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleElement, "3050f4b3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleElement : public IDispatch

    put_type		proc :BSTR
    get_type		proc :ptr
    get_readyState	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    get_styleSheet	proc :ptr
    put_disabled	proc :VARIANT_BOOL
    get_disabled	proc :ptr
    put_media		proc :BSTR
    get_media		proc :ptr
   .ends

endif

ifndef __IHTMLStyleElement2_INTERFACE_DEFINED__
define __IHTMLStyleElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleElement2, "3050f48B-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleElement2 : public IDispatch

    get_sheet		proc :ptr
   .ends

endif

ifndef __DispHTMLStyleElement_DISPINTERFACE_DEFINED__
define __DispHTMLStyleElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleElement, "3050f511-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleElement, "3050f37d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleFontFace_INTERFACE_DEFINED__
define __IHTMLStyleFontFace_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleFontFace, "3050f680-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleFontFace : public IDispatch

    put_fontsrc		proc :BSTR
    get_fontsrc		proc :ptr
   .ends

endif

ifndef __IHTMLStyleFontFace2_INTERFACE_DEFINED__
define __IHTMLStyleFontFace2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleFontFace2, "3050f814-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleFontFace2 : public IDispatch

    get_style		proc :ptr
   .ends

endif

ifndef __DispHTMLStyleFontFace_DISPINTERFACE_DEFINED__
define __DispHTMLStyleFontFace_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleFontFace, "30590081-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleFontFace : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleFontFace, "3050f3d4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLXDomainRequest_INTERFACE_DEFINED__
define __IHTMLXDomainRequest_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLXDomainRequest, "30510478-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLXDomainRequest : public IDispatch

    get_responseText	proc :ptr
    put_timeout		proc :LONG
    get_timeout		proc :ptr
    get_contentType	proc :ptr
    put_onprogress	proc :VARIANT
    get_onprogress	proc :ptr
    put_onerror		proc :VARIANT
    get_onerror		proc :ptr
    put_ontimeout	proc :VARIANT
    get_ontimeout	proc :ptr
    put_onload		proc :VARIANT
    get_onload		proc :ptr
    abort		proc
    open		proc :BSTR, :BSTR
    send		proc :VARIANT
   .ends

endif

ifndef __IHTMLXDomainRequestFactory_INTERFACE_DEFINED__
define __IHTMLXDomainRequestFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLXDomainRequestFactory, "30510734-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLXDomainRequestFactory : public IDispatch

    create		proc :ptr
   .ends

endif

ifndef __DispXDomainRequest_DISPINTERFACE_DEFINED__
define __DispXDomainRequest_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispXDomainRequest, "3050f599-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispXDomainRequest : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_XDomainRequest, "30510455-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_XDomainRequestFactory, "30510457-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStorage2_INTERFACE_DEFINED__
define __IHTMLStorage2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStorage2, "3050f558-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStorage2 : public IDispatch

    setItem		proc :BSTR, :BSTR
   .ends

endif

ifndef __DispHTMLStorage_DISPINTERFACE_DEFINED__
define __DispHTMLStorage_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStorage, "3050f59d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStorage : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStorage, "30510475-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IEventTarget_INTERFACE_DEFINED__
define __IEventTarget_INTERFACE_DEFINED__
DEFINE_IIDX(IEventTarget, "3051074b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IEventTarget : public IDispatch

    addEventListener	proc :BSTR, :ptr, :VARIANT_BOOL
    removeEventListener proc :BSTR, :ptr, :VARIANT_BOOL
    dispatchEvent	proc :ptr, :ptr
   .ends

endif

ifndef __DispDOMEvent_DISPINTERFACE_DEFINED__
define __DispDOMEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMEvent, "3050f5a2-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMEvent, "305104bb-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMUIEvent_INTERFACE_DEFINED__
define __IDOMUIEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMUIEvent, "3059009e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMUIEvent : public IDispatch

    get_view		proc :ptr
    get_detail		proc :ptr
    initUIEvent		proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG
   .ends

endif

ifndef __DispDOMUIEvent_DISPINTERFACE_DEFINED__
define __DispDOMUIEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMUIEvent, "30590072-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMUIEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMUIEvent, "305106cb-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMMouseEvent_INTERFACE_DEFINED__
define __IDOMMouseEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMouseEvent, "3050f5a1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMMouseEvent : public IDispatch

    get_screenX		proc :ptr
    get_screenY		proc :ptr
    get_clientX		proc :ptr
    get_clientY		proc :ptr
    get_ctrlKey		proc :ptr
    get_shiftKey	proc :ptr
    get_altKey		proc :ptr
    get_metaKey		proc :ptr
    get_button		proc :ptr
    get_relatedTarget	proc :ptr
    initMouseEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG, :LONG, :LONG, :LONG, :LONG, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :USHORT, :ptr
    getModifierState	proc :BSTR, :ptr
    get_buttons		proc :ptr
    get_fromElement	proc :ptr
    get_toElement	proc :ptr
    get_x		proc :ptr
    get_y		proc :ptr
    get_offsetX		proc :ptr
    get_offsetY		proc :ptr
    get_pageX		proc :ptr
    get_pageY		proc :ptr
    get_layerX		proc :ptr
    get_layerY		proc :ptr
    get_which		proc :ptr
   .ends

endif

ifndef __DispDOMMouseEvent_DISPINTERFACE_DEFINED__
define __DispDOMMouseEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMouseEvent, "30590073-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMouseEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMouseEvent, "305106cf-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMDragEvent_INTERFACE_DEFINED__
define __IDOMDragEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMDragEvent, "3050f625-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMDragEvent : public IDispatch

    get_dataTransfer	proc :ptr
    initDragEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG, :LONG, :LONG, :LONG, :LONG, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :USHORT, :ptr, :ptr
   .ends

endif

ifndef __DispDOMDragEvent_DISPINTERFACE_DEFINED__
define __DispDOMDragEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMDragEvent, "305900a7-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMDragEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMDragEvent, "30510762-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMMouseWheelEvent_INTERFACE_DEFINED__
define __IDOMMouseWheelEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMouseWheelEvent, "96A0A4E0-D062-11cf-94B6-00AA0060275C")

.comdef IDOMMouseWheelEvent : public IDispatch

    get_wheelDelta	proc :ptr
    initMouseWheelEvent proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG, :LONG, :LONG, :LONG, :LONG, :USHORT, :ptr, :BSTR, :LONG
   .ends

endif

ifndef __DispDOMMouseWheelEvent_DISPINTERFACE_DEFINED__
define __DispDOMMouseWheelEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMouseWheelEvent, "30590074-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMouseWheelEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMouseWheelEvent, "305106d1-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMWheelEvent_INTERFACE_DEFINED__
define __IDOMWheelEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMWheelEvent, "332c4425-26cb-11d0-b483-00c04fd90119")

.comdef IDOMWheelEvent : public IDispatch

    get_deltaX		proc :ptr
    get_deltaY		proc :ptr
    get_deltaZ		proc :ptr
    get_deltaMode	proc :ptr
    initWheelEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG, :LONG, :LONG, :LONG, :LONG, :USHORT, :ptr, :BSTR, :LONG, :LONG, :LONG, :ULONG
   .ends

endif

ifndef __DispDOMWheelEvent_DISPINTERFACE_DEFINED__
define __DispDOMWheelEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMWheelEvent, "30590075-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMWheelEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMWheelEvent, "305106d3-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMTextEvent_INTERFACE_DEFINED__
define __IDOMTextEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMTextEvent, "332c4426-26cb-11d0-b483-00c04fd90119")

.comdef IDOMTextEvent : public IDispatch

    get_data		proc :ptr
    get_inputMethod	proc :ptr
    initTextEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :BSTR, :ULONG, :BSTR
    get_locale		proc :ptr
   .ends

endif

ifndef __DispDOMTextEvent_DISPINTERFACE_DEFINED__
define __DispDOMTextEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMTextEvent, "30590076-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMTextEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMTextEvent, "305106d5-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMKeyboardEvent_INTERFACE_DEFINED__
define __IDOMKeyboardEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMKeyboardEvent, "332c4427-26cb-11d0-b483-00c04fd90119")

.comdef IDOMKeyboardEvent : public IDispatch

    get_key		proc :ptr
    get_location	proc :ptr
    get_ctrlKey		proc :ptr
    get_shiftKey	proc :ptr
    get_altKey		proc :ptr
    get_metaKey		proc :ptr
    get_repeat		proc :ptr
    getModifierState	proc :BSTR, :ptr
    initKeyboardEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :BSTR, :ULONG, :BSTR, :VARIANT_BOOL, :BSTR
    get_keyCode		proc :ptr
    get_charCode	proc :ptr
    get_which		proc :ptr
    get_ie9_char	proc :ptr
    get_locale		proc :ptr
   .ends

endif

ifndef __DispDOMKeyboardEvent_DISPINTERFACE_DEFINED__
define __DispDOMKeyboardEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMKeyboardEvent, "30590077-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMKeyboardEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMKeyboardEvent, "305106d7-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMCompositionEvent_INTERFACE_DEFINED__
define __IDOMCompositionEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMCompositionEvent, "3050f4ae-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMCompositionEvent : public IDispatch

    get_data		proc :ptr
    initCompositionEvent proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :BSTR, :BSTR
    get_locale		proc :ptr
   .ends

endif

ifndef __DispDOMCompositionEvent_DISPINTERFACE_DEFINED__
define __DispDOMCompositionEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMCompositionEvent, "30590078-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMCompositionEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMCompositionEvent, "305106d9-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMMutationEvent_INTERFACE_DEFINED__
define __IDOMMutationEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMutationEvent, "3050f311-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMMutationEvent : public IDispatch

    get_relatedNode	proc :ptr
    get_prevValue	proc :ptr
    get_newValue	proc :ptr
    get_attrName	proc :ptr
    get_attrChange	proc :ptr
    initMutationEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :BSTR, :BSTR, :BSTR, :USHORT
   .ends

endif

ifndef __DispDOMMutationEvent_DISPINTERFACE_DEFINED__
define __DispDOMMutationEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMutationEvent, "30590079-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMutationEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMutationEvent, "305106db-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMBeforeUnloadEvent_INTERFACE_DEFINED__
define __IDOMBeforeUnloadEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMBeforeUnloadEvent, "30510474-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMBeforeUnloadEvent : public IDispatch

    put_returnValue	proc :VARIANT
    get_returnValue	proc :ptr
   .ends

endif

ifndef __DispDOMBeforeUnloadEvent_DISPINTERFACE_DEFINED__
define __DispDOMBeforeUnloadEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMBeforeUnloadEvent, "305900a8-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMBeforeUnloadEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMBeforeUnloadEvent, "30510764-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMFocusEvent_INTERFACE_DEFINED__
define __IDOMFocusEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMFocusEvent, "3051074e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMFocusEvent : public IDispatch

    get_relatedTarget	proc :ptr
    initFocusEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG, :ptr
   .ends

endif

ifndef __DispDOMFocusEvent_DISPINTERFACE_DEFINED__
define __DispDOMFocusEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMFocusEvent, "30590071-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMFocusEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMFocusEvent, "305106cd-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMCustomEvent_INTERFACE_DEFINED__
define __IDOMCustomEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMCustomEvent, "30510828-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMCustomEvent : public IDispatch

    get_detail		proc :ptr
    initCustomEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr
   .ends

endif

ifndef __DispDOMCustomEvent_DISPINTERFACE_DEFINED__
define __DispDOMCustomEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMCustomEvent, "3059007c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMCustomEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMCustomEvent, "305106df-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ICanvasGradient_INTERFACE_DEFINED__
define __ICanvasGradient_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasGradient, "3050f35c-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasGradient : public IDispatch

    addColorStop	proc :FLOAT, :BSTR
   .ends

endif

ifndef __ICanvasPattern_INTERFACE_DEFINED__
define __ICanvasPattern_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasPattern, "3050f84a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasPattern : public IDispatch

   .ends

endif

ifndef __ICanvasTextMetrics_INTERFACE_DEFINED__
define __ICanvasTextMetrics_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasTextMetrics, "305104a1-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasTextMetrics : public IDispatch

    get_width		proc :ptr
   .ends

endif

ifndef __ICanvasImageData_INTERFACE_DEFINED__
define __ICanvasImageData_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasImageData, "3051076b-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasImageData : public IDispatch

    get_width		proc :ptr
    get_height		proc :ptr
    get_data		proc :ptr
   .ends

endif

ifndef __ICanvasPixelArray_INTERFACE_DEFINED__
define __ICanvasPixelArray_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasPixelArray, "3050f6cf-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasPixelArray : public IDispatch

    get_length		proc :ptr
   .ends

endif

ifndef __IHTMLCanvasElement_INTERFACE_DEFINED__
define __IHTMLCanvasElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCanvasElement, "3051040e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCanvasElement : public IDispatch

    put_width		proc :LONG
    get_width		proc :ptr
    put_height		proc :LONG
    get_height		proc :ptr
    getContext		proc :BSTR, :ptr
    toDataURL		proc :BSTR, :VARIANT, :ptr
   .ends

endif

ifndef __ICanvasRenderingContext2D_INTERFACE_DEFINED__
define __ICanvasRenderingContext2D_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasRenderingContext2D, "30510453-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasRenderingContext2D : public IDispatch

    get_canvas		proc :ptr
    restore		proc
    save		proc
    rotate		proc :FLOAT
    scale		proc :FLOAT, :FLOAT
    setTransform	proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
    transform		proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
    translate		proc :FLOAT, :FLOAT
    put_globalAlpha	proc :FLOAT
    get_globalAlpha	proc :ptr
    put_globalCompositeOperation proc :BSTR
    get_globalCompositeOperation proc :ptr
    put_fillStyle	proc :VARIANT
    get_fillStyle	proc :ptr
    put_strokeStyle	proc :VARIANT
    get_strokeStyle	proc :ptr
    createLinearGradient proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createRadialGradient proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createPattern	proc :ptr, :VARIANT, :ptr
    put_lineCap		proc :BSTR
    get_lineCap		proc :ptr
    put_lineJoin	proc :BSTR
    get_lineJoin	proc :ptr
    put_lineWidth	proc :FLOAT
    get_lineWidth	proc :ptr
    put_miterLimit	proc :FLOAT
    get_miterLimit	proc :ptr
    put_shadowBlur	proc :FLOAT
    get_shadowBlur	proc :ptr
    put_shadowColor	proc :BSTR
    get_shadowColor	proc :ptr
    put_shadowOffsetX	proc :FLOAT
    get_shadowOffsetX	proc :ptr
    put_shadowOffsetY	proc :FLOAT
    get_shadowOffsetY	proc :ptr
    clearRect		proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
    fillRect		proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
    strokeRect		proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
    arc			proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :BOOL
    arcTo		proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
    beginPath		proc
    bezierCurveTo	proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT
    clip		proc
    closePath		proc
    fill		proc
    lineTo		proc :FLOAT, :FLOAT
    moveTo		proc :FLOAT, :FLOAT
    quadraticCurveTo	proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
    rect		proc :FLOAT, :FLOAT, :FLOAT, :FLOAT
    stroke		proc
    isPointInPath	proc :FLOAT, :FLOAT, :ptr
    put_font		proc :BSTR
    get_font		proc :ptr
    put_textAlign	proc :BSTR
    get_textAlign	proc :ptr
    put_textBaseline	proc :BSTR
    get_textBaseline	proc :ptr
    fillText		proc :BSTR, :FLOAT, :FLOAT, :VARIANT
    measureText		proc :BSTR, :ptr
    strokeText		proc :BSTR, :FLOAT, :FLOAT, :VARIANT
    drawImage		proc :ptr, :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT, :VARIANT
    createImageData	proc :VARIANT, :VARIANT, :ptr
    getImageData	proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    putImageData	proc :ptr, :FLOAT, :FLOAT, :VARIANT, :VARIANT, :VARIANT, :VARIANT
   .ends

endif

ifndef __DispCanvasGradient_DISPINTERFACE_DEFINED__
define __DispCanvasGradient_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCanvasGradient, "3059008c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCanvasGradient : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CanvasGradient, "30510715-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispCanvasPattern_DISPINTERFACE_DEFINED__
define __DispCanvasPattern_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCanvasPattern, "3059008d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCanvasPattern : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CanvasPattern, "30510717-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispCanvasTextMetrics_DISPINTERFACE_DEFINED__
define __DispCanvasTextMetrics_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCanvasTextMetrics, "3059008e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCanvasTextMetrics : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CanvasTextMetrics, "30510719-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispCanvasImageData_DISPINTERFACE_DEFINED__
define __DispCanvasImageData_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCanvasImageData, "3059008f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCanvasImageData : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CanvasImageData, "3051071b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispCanvasRenderingContext2D_DISPINTERFACE_DEFINED__
define __DispCanvasRenderingContext2D_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCanvasRenderingContext2D, "30590082-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCanvasRenderingContext2D : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CanvasRenderingContext2D, "30510700-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLCanvasElement_DISPINTERFACE_DEFINED__
define __DispHTMLCanvasElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLCanvasElement, "3059007b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLCanvasElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLCanvasElement, "305106e5-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMProgressEvent_INTERFACE_DEFINED__
define __IDOMProgressEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMProgressEvent, "305104b7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMProgressEvent : public IDispatch

    get_lengthComputable proc :ptr
    get_loaded		proc :ptr
    get_total		proc :ptr
    initProgressEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :ULONGLONG, :ULONGLONG
   .ends

endif

ifndef __DispDOMProgressEvent_DISPINTERFACE_DEFINED__
define __DispDOMProgressEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMProgressEvent, "30590091-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMProgressEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMProgressEvent, "3051071f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMMessageEvent_INTERFACE_DEFINED__
define __IDOMMessageEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMessageEvent, "305107AB-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMMessageEvent : public IDispatch

    get_data		proc :ptr
    get_origin		proc :ptr
    get_source		proc :ptr
    initMessageEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __DispDOMMessageEvent_DISPINTERFACE_DEFINED__
define __DispDOMMessageEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMessageEvent, "30590092-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMessageEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMessageEvent, "30510721-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMSiteModeEvent_INTERFACE_DEFINED__
define __IDOMSiteModeEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMSiteModeEvent, "3050f591-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMSiteModeEvent : public IDispatch

    get_buttonID	proc :ptr
    get_actionURL	proc :ptr
   .ends

endif

ifndef __DispDOMSiteModeEvent_DISPINTERFACE_DEFINED__
define __DispDOMSiteModeEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMSiteModeEvent, "305900a9-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMSiteModeEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMSiteModeEvent, "30510766-98b6-11cf-bb82-00aa00bdce0b")

ifndef __IDOMStorageEvent_INTERFACE_DEFINED__
define __IDOMStorageEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMStorageEvent, "3050f55d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMStorageEvent : public IDispatch

    get_key		proc :ptr
    get_oldValue	proc :ptr
    get_newValue	proc :ptr
    get_url		proc :ptr
    get_storageArea	proc :ptr
    initStorageEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :BSTR, :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __DispDOMStorageEvent_DISPINTERFACE_DEFINED__
define __DispDOMStorageEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMStorageEvent, "30590093-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMStorageEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMStorageEvent, "30510723-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IXMLHttpRequestEventTarget_INTERFACE_DEFINED__
define __IXMLHttpRequestEventTarget_INTERFACE_DEFINED__
DEFINE_IIDX(IXMLHttpRequestEventTarget, "3050f55e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IXMLHttpRequestEventTarget : public IDispatch

   .ends

endif

ifndef __DispXMLHttpRequestEventTarget_DISPINTERFACE_DEFINED__
define __DispXMLHttpRequestEventTarget_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispXMLHttpRequestEventTarget, "305900e7-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispXMLHttpRequestEventTarget : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_XMLHttpRequestEventTarget, "30510831-98b5-11cf-bb82-00aa00bdce0b")

ifndef __HTMLXMLHttpRequestEvents_DISPINTERFACE_DEFINED__
define __HTMLXMLHttpRequestEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLXMLHttpRequestEvents, "30510498-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLXMLHttpRequestEvents : public IDispatch

   .ends

endif

ifndef __IHTMLXMLHttpRequest_INTERFACE_DEFINED__
define __IHTMLXMLHttpRequest_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLXMLHttpRequest, "3051041a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLXMLHttpRequest : public IDispatch

    get_readyState	proc :ptr
    get_responseBody	proc :ptr
    get_responseText	proc :ptr
    get_responseXML	proc :ptr
    get_status		proc :ptr
    get_statusText	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    abort		proc
    open		proc :BSTR, :BSTR, :VARIANT, :VARIANT, :VARIANT
    send		proc :VARIANT
    getAllResponseHeaders proc :ptr
    getResponseHeader	proc :BSTR, :ptr
    setRequestHeader	proc :BSTR, :BSTR
   .ends

endif

ifndef __IHTMLXMLHttpRequest2_INTERFACE_DEFINED__
define __IHTMLXMLHttpRequest2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLXMLHttpRequest2, "30510418-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLXMLHttpRequest2 : public IDispatch

    put_timeout		proc :LONG
    get_timeout		proc :ptr
    put_ontimeout	proc :VARIANT
    get_ontimeout	proc :ptr
   .ends

endif

ifndef __IHTMLXMLHttpRequestFactory_INTERFACE_DEFINED__
define __IHTMLXMLHttpRequestFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLXMLHttpRequestFactory, "3050f53e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLXMLHttpRequestFactory : public IDispatch

    create		proc :ptr
   .ends

endif

ifndef __DispHTMLXMLHttpRequest_DISPINTERFACE_DEFINED__
define __DispHTMLXMLHttpRequest_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLXMLHttpRequest, "3050f596-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLXMLHttpRequest : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLXMLHttpRequest, "3051040b-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_HTMLXMLHttpRequestFactory, "3051040d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGAngle_INTERFACE_DEFINED__
define __ISVGAngle_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAngle, "3050f53f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAngle : public IDispatch

    put_unitType	proc :sword
    get_unitType	proc :ptr
    put_value		proc :FLOAT
    get_value		proc :ptr
    put_valueInSpecifiedUnits proc :FLOAT
    get_valueInSpecifiedUnits proc :ptr
    put_valueAsString	proc :BSTR
    get_valueAsString	proc :ptr
    newValueSpecifiedUnits proc :sword, :FLOAT
    convertToSpecifiedUnits proc :sword
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAngle, "30510584-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGElement_INTERFACE_DEFINED__
define __ISVGElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGElement, "30510737-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGElement : public IDispatch

    put_xmlbase		proc :BSTR
    get_xmlbase		proc :ptr
    putref_ownerSVGElement proc :ptr
    get_ownerSVGElement proc :ptr
    putref_viewportElement proc :ptr
    get_viewportElement proc :ptr
    putref_focusable	proc :ptr
    get_focusable	proc :ptr
   .ends

endif

ifndef __ISVGRect_INTERFACE_DEFINED__
define __ISVGRect_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGRect, "3050f5a0-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGRect : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_width		proc :FLOAT
    get_width		proc :ptr
    put_height		proc :FLOAT
    get_height		proc :ptr
   .ends

endif

ifndef __ISVGMatrix_INTERFACE_DEFINED__
define __ISVGMatrix_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGMatrix, "3050f613-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGMatrix : public IDispatch

    put_a		proc :FLOAT
    get_a		proc :ptr
    put_b		proc :FLOAT
    get_b		proc :ptr
    put_c		proc :FLOAT
    get_c		proc :ptr
    put_d		proc :FLOAT
    get_d		proc :ptr
    put_e		proc :FLOAT
    get_e		proc :ptr
    put_f		proc :FLOAT
    get_f		proc :ptr
    multiply		proc :ptr, :ptr
    inverse		proc :ptr
    translate		proc :FLOAT, :FLOAT, :ptr
    scale		proc :FLOAT, :ptr
    scaleNonUniform	proc :FLOAT, :FLOAT, :ptr
    rotate		proc :FLOAT, :ptr
    rotateFromVector	proc :FLOAT, :FLOAT, :ptr
    flipX		proc :ptr
    flipY		proc :ptr
    skewX		proc :FLOAT, :ptr
    skewY		proc :FLOAT, :ptr
   .ends

endif

ifndef __ISVGStringList_INTERFACE_DEFINED__
define __ISVGStringList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGStringList, "3050f260-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGStringList : public IDispatch

    put_numberOfItems	proc :LONG
    get_numberOfItems	proc :ptr
    clear		proc
    initialize		proc :BSTR, :ptr
    getItem		proc :LONG, :ptr
    insertItemBefore	proc :BSTR, :LONG, :ptr
    replaceItem		proc :BSTR, :LONG, :ptr
    removeItem		proc :LONG, :ptr
    appendItem		proc :BSTR, :ptr
   .ends

endif

ifndef __ISVGAnimatedRect_INTERFACE_DEFINED__
define __ISVGAnimatedRect_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedRect, "305104e7-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedRect : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

ifndef __ISVGAnimatedString_INTERFACE_DEFINED__
define __ISVGAnimatedString_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedString, "30510746-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedString : public IDispatch

    put_baseVal		proc :BSTR
    get_baseVal		proc :ptr
    get_animVal		proc :ptr
   .ends

endif

ifndef __ISVGAnimatedBoolean_INTERFACE_DEFINED__
define __ISVGAnimatedBoolean_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedBoolean, "30510748-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedBoolean : public IDispatch

    put_baseVal		proc :VARIANT_BOOL
    get_baseVal		proc :ptr
    put_animVal		proc :VARIANT_BOOL
    get_animVal		proc :ptr
   .ends

endif

ifndef __ISVGAnimatedTransformList_INTERFACE_DEFINED__
define __ISVGAnimatedTransformList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedTransformList, "30510742-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedTransformList : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

ifndef __ISVGAnimatedPreserveAspectRatio_INTERFACE_DEFINED__
define __ISVGAnimatedPreserveAspectRatio_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedPreserveAspectRatio, "3050f485-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedPreserveAspectRatio : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

ifndef __ISVGStylable_INTERFACE_DEFINED__
define __ISVGStylable_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGStylable, "3050f69a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGStylable : public IDispatch

    get_className	proc :ptr
   .ends

endif

ifndef __ISVGLocatable_INTERFACE_DEFINED__
define __ISVGLocatable_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGLocatable, "3050f80c-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGLocatable : public IDispatch

    get_nearestViewportElement proc :ptr
    get_farthestViewportElement proc :ptr
    getBBox		proc :ptr
    getCTM		proc :ptr
    getScreenCTM	proc :ptr
    getTransformToElement proc :ptr, :ptr
   .ends

endif

ifndef __ISVGTransformable_INTERFACE_DEFINED__
define __ISVGTransformable_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTransformable, "30510417-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTransformable : public IDispatch

    get_transform	proc :ptr
   .ends

endif

ifndef __ISVGTests_INTERFACE_DEFINED__
define __ISVGTests_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTests, "305107d0-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTests : public IDispatch

    get_requiredFeatures proc :ptr
    get_requiredExtensions proc :ptr
    get_systemLanguage	proc :ptr
    hasExtension	proc :BSTR, :ptr
   .ends

endif

ifndef __ISVGLangSpace_INTERFACE_DEFINED__
define __ISVGLangSpace_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGLangSpace, "305104bc-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGLangSpace : public IDispatch

    put_xmllang		proc :BSTR
    get_xmllang		proc :ptr
    put_xmlspace	proc :BSTR
    get_xmlspace	proc :ptr
   .ends

endif

ifndef __ISVGExternalResourcesRequired_INTERFACE_DEFINED__
define __ISVGExternalResourcesRequired_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGExternalResourcesRequired, "305104af-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGExternalResourcesRequired : public IDispatch

    get_externalResourcesRequired proc :ptr
   .ends

endif

ifndef __ISVGFitToViewBox_INTERFACE_DEFINED__
define __ISVGFitToViewBox_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGFitToViewBox, "30510462-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGFitToViewBox : public IDispatch

    get_viewBox		proc :ptr
    putref_preserveAspectRatio proc :ptr
    get_preserveAspectRatio proc :ptr
   .ends

endif

ifndef __ISVGZoomAndPan_INTERFACE_DEFINED__
define __ISVGZoomAndPan_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGZoomAndPan, "30510744-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGZoomAndPan : public IDispatch

    get_zoomAndPan	proc :ptr
   .ends

endif

ifndef __ISVGURIReference_INTERFACE_DEFINED__
define __ISVGURIReference_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGURIReference, "3050f55f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGURIReference : public IDispatch

    get_href		proc :ptr
   .ends

endif

ifndef __ISVGAnimatedAngle_INTERFACE_DEFINED__
define __ISVGAnimatedAngle_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedAngle, "A6D897FF-0A95-11d1-B0BA-006008166E11")

.comdef ISVGAnimatedAngle : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedAngle, "305105e4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGTransformList_INTERFACE_DEFINED__
define __ISVGTransformList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTransformList, "AE24FDAD-03C6-11D1-8B76-0080C744F389")

.comdef ISVGTransformList : public IDispatch

    put_numberOfItems	proc :LONG
    get_numberOfItems	proc :ptr
    clear		proc
    initialize		proc :ptr, :ptr
    getItem		proc :LONG, :ptr
    insertItemBefore	proc :ptr, :LONG, :ptr
    replaceItem		proc :ptr, :LONG, :ptr
    removeItem		proc :LONG, :ptr
    appendItem		proc :ptr, :ptr
    createSVGTransformFromMatrix proc :ptr, :ptr
    consolidate		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedTransformList, "305105b1-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGAnimatedBoolean, "3051058b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGAnimatedEnumeration_INTERFACE_DEFINED__
define __ISVGAnimatedEnumeration_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedEnumeration, "A5170870-0CF8-11D1-8B91-0080C744F389")

.comdef ISVGAnimatedEnumeration : public IDispatch

    put_baseVal		proc :USHORT
    get_baseVal		proc :ptr
    put_animVal		proc :USHORT
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedEnumeration, "3051058e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGAnimatedInteger_INTERFACE_DEFINED__
define __ISVGAnimatedInteger_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedInteger, "3050f25f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedInteger : public IDispatch

    put_baseVal		proc :LONG
    get_baseVal		proc :ptr
    put_animVal		proc :LONG
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedInteger, "3051058f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGLength_INTERFACE_DEFINED__
define __ISVGLength_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGLength, "30510493-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGLength : public IDispatch

    put_unitType	proc :sword
    get_unitType	proc :ptr
    put_value		proc :FLOAT
    get_value		proc :ptr
    put_valueInSpecifiedUnits proc :FLOAT
    get_valueInSpecifiedUnits proc :ptr
    put_valueAsString	proc :BSTR
    get_valueAsString	proc :ptr
    newValueSpecifiedUnits proc :sword, :FLOAT
    convertToSpecifiedUnits proc :sword
   .ends

endif

ifndef __ISVGAnimatedLength_INTERFACE_DEFINED__
define __ISVGAnimatedLength_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedLength, "3050f52e-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedLength : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedLength, "30510581-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGLengthList_INTERFACE_DEFINED__
define __ISVGLengthList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGLengthList, "3050f61e-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGLengthList : public IDispatch

    put_numberOfItems	proc :LONG
    get_numberOfItems	proc :ptr
    clear		proc
    initialize		proc :ptr, :ptr
    getItem		proc :LONG, :ptr
    insertItemBefore	proc :ptr, :LONG, :ptr
    replaceItem		proc :ptr, :LONG, :ptr
    removeItem		proc :LONG, :ptr
    appendItem		proc :ptr, :ptr
   .ends

endif

ifndef __ISVGAnimatedLengthList_INTERFACE_DEFINED__
define __ISVGAnimatedLengthList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedLengthList, "3050f3ba-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedLengthList : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedLengthList, "30510582-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGNumber_INTERFACE_DEFINED__
define __ISVGNumber_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGNumber, "3050f383-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGNumber : public IDispatch

    put_value		proc :FLOAT
    get_value		proc :ptr
   .ends

endif

ifndef __ISVGAnimatedNumber_INTERFACE_DEFINED__
define __ISVGAnimatedNumber_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedNumber, "3050f5ec-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedNumber : public IDispatch

    put_baseVal		proc :FLOAT
    get_baseVal		proc :ptr
    put_animVal		proc :FLOAT
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedNumber, "30510588-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGNumberList_INTERFACE_DEFINED__
define __ISVGNumberList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGNumberList, "3050f837-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGNumberList : public IDispatch

    put_numberOfItems	proc :LONG
    get_numberOfItems	proc :ptr
    clear		proc
    initialize		proc :ptr, :ptr
    getItem		proc :LONG, :ptr
    insertItemBefore	proc :ptr, :LONG, :ptr
    replaceItem		proc :ptr, :LONG, :ptr
    removeItem		proc :LONG, :ptr
    appendItem		proc :ptr, :ptr
   .ends

endif

ifndef __ISVGAnimatedNumberList_INTERFACE_DEFINED__
define __ISVGAnimatedNumberList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedNumberList, "30510492-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedNumberList : public IDispatch

    putref_baseVal	proc :ptr
    get_baseVal		proc :ptr
    putref_animVal	proc :ptr
    get_animVal		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGAnimatedNumberList, "3051058a-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGAnimatedRect, "30510586-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGAnimatedString, "3051058c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGClipPathElement_INTERFACE_DEFINED__
define __ISVGClipPathElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGClipPathElement, "3050f266-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGClipPathElement : public IDispatch

    putref_clipPathUnits proc :ptr
    get_clipPathUnits	proc :ptr
   .ends

endif

ifndef __DispSVGClipPathElement_DISPINTERFACE_DEFINED__
define __DispSVGClipPathElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGClipPathElement, "3059003B-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGClipPathElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGClipPathElement, "305105e6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGDocument_INTERFACE_DEFINED__
define __ISVGDocument_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGDocument, "3050f56a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGDocument : public IDispatch

    get_rootElement	proc :ptr
   .ends

endif

ifndef __IGetSVGDocument_INTERFACE_DEFINED__
define __IGetSVGDocument_INTERFACE_DEFINED__
DEFINE_IIDX(IGetSVGDocument, "3050f526-98b5-11cf-bb82-00aa00bdce0b")

.comdef IGetSVGDocument : public IDispatch

    getSVGDocument	proc :ptr
   .ends

endif

ifndef __DispSVGElement_DISPINTERFACE_DEFINED__
define __DispSVGElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGElement, "30590000-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGElement, "30510564-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IICCSVGColor_INTERFACE_DEFINED__
define __IICCSVGColor_INTERFACE_DEFINED__
DEFINE_IIDX(IICCSVGColor, "3050f611-98b5-11cf-bb82-00aa00bdce0b")

.comdef IICCSVGColor : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGLength, "3051057e-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGLengthList, "30510580-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGMatrix, "305105ae-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGNumber, "30510587-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGNumberList, "30510589-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGPaint_INTERFACE_DEFINED__
define __ISVGPaint_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPaint, "3050f366-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPaint : public IDispatch

   .ends

endif

ifndef __ISVGPatternElement_INTERFACE_DEFINED__
define __ISVGPatternElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPatternElement, "3050f265-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPatternElement : public IDispatch

    putref_patternUnits proc :ptr
    get_patternUnits	proc :ptr
    putref_patternContentUnits proc :ptr
    get_patternContentUnits proc :ptr
    putref_patternTransform proc :ptr
    get_patternTransform proc :ptr
    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_width	proc :ptr
    get_width		proc :ptr
    putref_height	proc :ptr
    get_height		proc :ptr
   .ends

endif

ifndef __DispSVGPatternElement_DISPINTERFACE_DEFINED__
define __DispSVGPatternElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPatternElement, "3059002c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPatternElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPatternElement, "305105d4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGPathSeg_INTERFACE_DEFINED__
define __ISVGPathSeg_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSeg, "3051041f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSeg : public IDispatch

    put_pathSegType	proc :sword
    get_pathSegType	proc :ptr
    get_pathSegTypeAsLetter proc :ptr
   .ends

endif

ifndef __ISVGPathSegArcAbs_INTERFACE_DEFINED__
define __ISVGPathSegArcAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegArcAbs, "3050f503-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegArcAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_r1		proc :FLOAT
    get_r1		proc :ptr
    put_r2		proc :FLOAT
    get_r2		proc :ptr
    put_angle		proc :FLOAT
    get_angle		proc :ptr
    put_largeArcFlag	proc :VARIANT_BOOL
    get_largeArcFlag	proc :ptr
    put_sweepFlag	proc :VARIANT_BOOL
    get_sweepFlag	proc :ptr
   .ends

endif

ifndef __ISVGPathSegArcRel_INTERFACE_DEFINED__
define __ISVGPathSegArcRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegArcRel, "3050f2eb-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegArcRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_r1		proc :FLOAT
    get_r1		proc :ptr
    put_r2		proc :FLOAT
    get_r2		proc :ptr
    put_angle		proc :FLOAT
    get_angle		proc :ptr
    put_largeArcFlag	proc :VARIANT_BOOL
    get_largeArcFlag	proc :ptr
    put_sweepFlag	proc :VARIANT_BOOL
    get_sweepFlag	proc :ptr
   .ends

endif

ifndef __ISVGPathSegClosePath_INTERFACE_DEFINED__
define __ISVGPathSegClosePath_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegClosePath, "3050f508-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegClosePath : public IDispatch

   .ends

endif

ifndef __ISVGPathSegMovetoAbs_INTERFACE_DEFINED__
define __ISVGPathSegMovetoAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegMovetoAbs, "3050f20c-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegMovetoAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegMovetoRel_INTERFACE_DEFINED__
define __ISVGPathSegMovetoRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegMovetoRel, "3050f813-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegMovetoRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegLinetoAbs_INTERFACE_DEFINED__
define __ISVGPathSegLinetoAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegLinetoAbs, "3051073f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegLinetoAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegLinetoRel_INTERFACE_DEFINED__
define __ISVGPathSegLinetoRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegLinetoRel, "3050f50a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegLinetoRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoCubicAbs_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoCubicAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoCubicAbs, "3050f20a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoCubicAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_x1		proc :FLOAT
    get_x1		proc :ptr
    put_y1		proc :FLOAT
    get_y1		proc :ptr
    put_x2		proc :FLOAT
    get_x2		proc :ptr
    put_y2		proc :FLOAT
    get_y2		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoCubicRel_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoCubicRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoCubicRel, "3050f824-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoCubicRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_x1		proc :FLOAT
    get_x1		proc :ptr
    put_y1		proc :FLOAT
    get_y1		proc :ptr
    put_x2		proc :FLOAT
    get_x2		proc :ptr
    put_y2		proc :FLOAT
    get_y2		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoCubicSmoothAbs_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoCubicSmoothAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoCubicSmoothAbs, "3051043d-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoCubicSmoothAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_x2		proc :FLOAT
    get_x2		proc :ptr
    put_y2		proc :FLOAT
    get_y2		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoCubicSmoothRel_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoCubicSmoothRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoCubicSmoothRel, "3050f3f3-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoCubicSmoothRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_x2		proc :FLOAT
    get_x2		proc :ptr
    put_y2		proc :FLOAT
    get_y2		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoQuadraticAbs_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoQuadraticAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoQuadraticAbs, "3050f52d-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoQuadraticAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_x1		proc :FLOAT
    get_x1		proc :ptr
    put_y1		proc :FLOAT
    get_y1		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoQuadraticRel_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoQuadraticRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoQuadraticRel, "3050f548-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoQuadraticRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    put_x1		proc :FLOAT
    get_x1		proc :ptr
    put_y1		proc :FLOAT
    get_y1		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoQuadraticSmoothAbs_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoQuadraticSmoothAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoQuadraticSmoothAbs, "3050f623-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoQuadraticSmoothAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegCurvetoQuadraticSmoothRel_INTERFACE_DEFINED__
define __ISVGPathSegCurvetoQuadraticSmoothRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegCurvetoQuadraticSmoothRel, "3050f407-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegCurvetoQuadraticSmoothRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegLinetoHorizontalAbs_INTERFACE_DEFINED__
define __ISVGPathSegLinetoHorizontalAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegLinetoHorizontalAbs, "3050f23b-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegLinetoHorizontalAbs : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
   .ends

endif

ifndef __ISVGPathSegLinetoHorizontalRel_INTERFACE_DEFINED__
define __ISVGPathSegLinetoHorizontalRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegLinetoHorizontalRel, "3050f21e-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegLinetoHorizontalRel : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
   .ends

endif

ifndef __ISVGPathSegLinetoVerticalAbs_INTERFACE_DEFINED__
define __ISVGPathSegLinetoVerticalAbs_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegLinetoVerticalAbs, "3050f4ad-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegLinetoVerticalAbs : public IDispatch

    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

ifndef __ISVGPathSegLinetoVerticalRel_INTERFACE_DEFINED__
define __ISVGPathSegLinetoVerticalRel_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegLinetoVerticalRel, "3050f829-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegLinetoVerticalRel : public IDispatch

    put_y		proc :FLOAT
    get_y		proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSeg, "305105b3-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegArcAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegArcAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegArcAbs, "30590013-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegArcAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegArcAbs, "305105bb-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegArcRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegArcRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegArcRel, "30590014-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegArcRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegArcRel, "305105bc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegClosePath_DISPINTERFACE_DEFINED__
define __DispSVGPathSegClosePath_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegClosePath, "30590015-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegClosePath : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegClosePath, "305105bd-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegMovetoAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegMovetoAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegMovetoAbs, "30590024-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegMovetoAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegMovetoAbs, "305105cc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegMovetoRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegMovetoRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegMovetoRel, "30590025-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegMovetoRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegMovetoRel, "305105cd-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegLinetoAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegLinetoAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegLinetoAbs, "3059001e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegLinetoAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegLinetoAbs, "305105c6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegLinetoRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegLinetoRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegLinetoRel, "30590021-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegLinetoRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegLinetoRel, "305105c9-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoCubicAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoCubicAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoCubicAbs, "30590016-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoCubicAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoCubicAbs, "305105be-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoCubicRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoCubicRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoCubicRel, "30590017-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoCubicRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoCubicRel, "305105bf-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoCubicSmoothAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoCubicSmoothAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoCubicSmoothAbs, "30590018-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoCubicSmoothAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoCubicSmoothAbs, "305105c0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoCubicSmoothRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoCubicSmoothRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoCubicSmoothRel, "30590019-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoCubicSmoothRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoCubicSmoothRel, "305105c1-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoQuadraticAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoQuadraticAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoQuadraticAbs, "3059001a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoQuadraticAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoQuadraticAbs, "305105c2-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoQuadraticRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoQuadraticRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoQuadraticRel, "3059001b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoQuadraticRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoQuadraticRel, "305105c3-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoQuadraticSmoothAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoQuadraticSmoothAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoQuadraticSmoothAbs, "3059001c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoQuadraticSmoothAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoQuadraticSmoothAbs, "305105c4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegCurvetoQuadraticSmoothRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegCurvetoQuadraticSmoothRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegCurvetoQuadraticSmoothRel, "3059001d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegCurvetoQuadraticSmoothRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegCurvetoQuadraticSmoothRel, "305105c5-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegLinetoHorizontalAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegLinetoHorizontalAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegLinetoHorizontalAbs, "3059001f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegLinetoHorizontalAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegLinetoHorizontalAbs, "305105c7-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegLinetoHorizontalRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegLinetoHorizontalRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegLinetoHorizontalRel, "30590020-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegLinetoHorizontalRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegLinetoHorizontalRel, "305105c8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegLinetoVerticalAbs_DISPINTERFACE_DEFINED__
define __DispSVGPathSegLinetoVerticalAbs_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegLinetoVerticalAbs, "30590022-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegLinetoVerticalAbs : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegLinetoVerticalAbs, "305105ca-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPathSegLinetoVerticalRel_DISPINTERFACE_DEFINED__
define __DispSVGPathSegLinetoVerticalRel_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathSegLinetoVerticalRel, "30590023-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathSegLinetoVerticalRel : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegLinetoVerticalRel, "305105cb-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGPathSegList_INTERFACE_DEFINED__
define __ISVGPathSegList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathSegList, "305106C2-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathSegList : public IDispatch

    put_numberOfItems	proc :LONG
    get_numberOfItems	proc :ptr
    clear		proc
    initialize		proc :ptr, :ptr
    getItem		proc :LONG, :ptr
    insertItemBefore	proc :ptr, :LONG, :ptr
    replaceItem		proc :ptr, :LONG, :ptr
    removeItem		proc :LONG, :ptr
    appendItem		proc :ptr, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathSegList, "305105b4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGPoint_INTERFACE_DEFINED__
define __ISVGPoint_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPoint, "3050f23a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPoint : public IDispatch

    put_x		proc :FLOAT
    get_x		proc :ptr
    put_y		proc :FLOAT
    get_y		proc :ptr
    matrixTransform	proc :ptr, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGPoint, "305105ba-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGPointList_INTERFACE_DEFINED__
define __ISVGPointList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPointList, "3050f82a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPointList : public IDispatch

    put_numberOfItems	proc :LONG
    get_numberOfItems	proc :ptr
    clear		proc
    initialize		proc :ptr, :ptr
    getItem		proc :LONG, :ptr
    insertItemBefore	proc :ptr, :LONG, :ptr
    replaceItem		proc :ptr, :LONG, :ptr
    removeItem		proc :LONG, :ptr
    appendItem		proc :ptr, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGPointList, "305105b9-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGRect, "30510583-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGStringList, "3051058d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGViewSpec_INTERFACE_DEFINED__
define __ISVGViewSpec_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGViewSpec, "305106c4-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGViewSpec : public IDispatch

   .ends

endif

ifndef __ISVGTransform_INTERFACE_DEFINED__
define __ISVGTransform_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTransform, "3050f5c7-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTransform : public IDispatch

    put_type		proc :sword
    get_type		proc :ptr
    putref_matrix	proc :ptr
    get_matrix		proc :ptr
    put_angle		proc :FLOAT
    get_angle		proc :ptr
    setMatrix		proc :ptr
    setTranslate	proc :FLOAT, :FLOAT
    setScale		proc :FLOAT, :FLOAT
    setRotate		proc :FLOAT, :FLOAT, :FLOAT
    setSkewX		proc :FLOAT
    setSkewY		proc :FLOAT
   .ends

endif

DEFINE_GUIDS(CLSID_SVGTransform, "305105af-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGSVGElement_DISPINTERFACE_DEFINED__
define __DispSVGSVGElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGSVGElement, "30590001-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGSVGElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGSVGElement, "30510574-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGElementInstance_INTERFACE_DEFINED__
define __ISVGElementInstance_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGElementInstance, "3050f82b-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGElementInstance : public IDispatch

    get_correspondingElement proc :ptr
    get_correspondingUseElement proc :ptr
    get_parentNode	proc :ptr
    get_childNodes	proc :ptr
    get_firstChild	proc :ptr
    get_lastChild	proc :ptr
    get_previousSibling proc :ptr
    get_nextSibling	proc :ptr
   .ends

endif

ifndef __ISVGUseElement_INTERFACE_DEFINED__
define __ISVGUseElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGUseElement, "305106c5-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGUseElement : public IDispatch

    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_width	proc :ptr
    get_width		proc :ptr
    putref_height	proc :ptr
    get_height		proc :ptr
    putref_instanceRoot proc :ptr
    get_instanceRoot	proc :ptr
    putref_animatedInstanceRoot proc :ptr
    get_animatedInstanceRoot proc :ptr
   .ends

endif

ifndef __DispSVGUseElement_DISPINTERFACE_DEFINED__
define __DispSVGUseElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGUseElement, "30590010-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGUseElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGUseElement, "30510590-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLStyleSheetRulesAppliedCollection_INTERFACE_DEFINED__
define __IHTMLStyleSheetRulesAppliedCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLStyleSheetRulesAppliedCollection, "3050f23c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLStyleSheetRulesAppliedCollection : public IDispatch

    item		proc :LONG, :ptr
    get_length		proc :ptr
    propertyAppliedBy	proc :BSTR, :ptr
    propertyAppliedTrace proc :BSTR, :LONG, :ptr
    propertyAppliedTraceLength proc :BSTR, :ptr
   .ends

endif

ifndef __IRulesApplied_INTERFACE_DEFINED__
define __IRulesApplied_INTERFACE_DEFINED__
DEFINE_IIDX(IRulesApplied, "3050f4a1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IRulesApplied : public IDispatch

    get_element		proc :ptr
    get_inlineStyles	proc :ptr
    get_appliedRules	proc :ptr
    propertyIsInline	proc :BSTR, :ptr
    propertyIsInheritable proc :BSTR, :ptr
    hasInheritableProperty proc :ptr
   .ends

endif

ifndef __DispHTMLStyleSheetRulesAppliedCollection_DISPINTERFACE_DEFINED__
define __DispHTMLStyleSheetRulesAppliedCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLStyleSheetRulesAppliedCollection, "3050f5a6-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLStyleSheetRulesAppliedCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLStyleSheetRulesAppliedCollection, "eb36f845-2395-4719-b85c-d0d80e184bd9")

ifndef __DispRulesApplied_DISPINTERFACE_DEFINED__
define __DispRulesApplied_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispRulesApplied, "3050f5a5-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispRulesApplied : public IDispatch

   .ends

endif
DEFINE_GUIDS(CLSID_RulesApplied, "7c803920-7a53-4d26-98ac-fdd23e6b9e01")

ifndef __DispRulesAppliedCollection_DISPINTERFACE_DEFINED__
define __DispRulesAppliedCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispRulesAppliedCollection, "3050f5a4-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispRulesAppliedCollection : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_RulesAppliedCollection, "671926ee-c3cf-40af-be8f-1cbaee6486e8")

ifndef __DispHTMLW3CComputedStyle_DISPINTERFACE_DEFINED__
define __DispHTMLW3CComputedStyle_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLW3CComputedStyle, "30590070-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLW3CComputedStyle : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLW3CComputedStyle, "305106c8-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGTransformList, "305105b0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGAnimatedPoints_INTERFACE_DEFINED__
define __ISVGAnimatedPoints_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedPoints, "3050f82c-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedPoints : public IDispatch

    putref_points	proc :ptr
    get_points		proc :ptr
    putref_animatedPoints proc :ptr
    get_animatedPoints	proc :ptr
   .ends

endif

ifndef __ISVGCircleElement_INTERFACE_DEFINED__
define __ISVGCircleElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGCircleElement, "305106c6-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGCircleElement : public IDispatch

    putref_cx		proc :ptr
    get_cx		proc :ptr
    putref_cy		proc :ptr
    get_cy		proc :ptr
    putref_r		proc :ptr
    get_r		proc :ptr
   .ends

endif

ifndef __ISVGEllipseElement_INTERFACE_DEFINED__
define __ISVGEllipseElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGEllipseElement, "3050f413-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGEllipseElement : public IDispatch

    putref_cx		proc :ptr
    get_cx		proc :ptr
    putref_cy		proc :ptr
    get_cy		proc :ptr
    putref_rx		proc :ptr
    get_rx		proc :ptr
    putref_ry		proc :ptr
    get_ry		proc :ptr
   .ends

endif

ifndef __ISVGLineElement_INTERFACE_DEFINED__
define __ISVGLineElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGLineElement, "3050f23d-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGLineElement : public IDispatch

    putref_x1		proc :ptr
    get_x1		proc :ptr
    putref_y1		proc :ptr
    get_y1		proc :ptr
    putref_x2		proc :ptr
    get_x2		proc :ptr
    putref_y2		proc :ptr
    get_y2		proc :ptr
   .ends

endif

ifndef __ISVGRectElement_INTERFACE_DEFINED__
define __ISVGRectElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGRectElement, "3050f82d-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGRectElement : public IDispatch

    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_width	proc :ptr
    get_width		proc :ptr
    putref_height	proc :ptr
    get_height		proc :ptr
    putref_rx		proc :ptr
    get_rx		proc :ptr
    putref_ry		proc :ptr
    get_ry		proc :ptr
   .ends

endif

ifndef __ISVGPolygonElement_INTERFACE_DEFINED__
define __ISVGPolygonElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPolygonElement, "305106c7-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPolygonElement : public IDispatch

   .ends

endif

ifndef __ISVGPolylineElement_INTERFACE_DEFINED__
define __ISVGPolylineElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPolylineElement, "3050f532-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPolylineElement : public IDispatch

   .ends

endif

ifndef __DispSVGCircleElement_DISPINTERFACE_DEFINED__
define __DispSVGCircleElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGCircleElement, "3059000a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGCircleElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGCircleElement, "30510578-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGEllipseElement_DISPINTERFACE_DEFINED__
define __DispSVGEllipseElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGEllipseElement, "3059000b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGEllipseElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGEllipseElement, "30510579-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGLineElement_DISPINTERFACE_DEFINED__
define __DispSVGLineElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGLineElement, "3059000c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGLineElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGLineElement, "3051057a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGRectElement_DISPINTERFACE_DEFINED__
define __DispSVGRectElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGRectElement, "30590009-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGRectElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGRectElement, "30510577-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPolygonElement_DISPINTERFACE_DEFINED__
define __DispSVGPolygonElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPolygonElement, "3059000d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPolygonElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPolygonElement, "3051057b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGPolylineElement_DISPINTERFACE_DEFINED__
define __DispSVGPolylineElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPolylineElement, "3059000e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPolylineElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPolylineElement, "3051057c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGGElement_INTERFACE_DEFINED__
define __ISVGGElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGGElement, "3050f533-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGGElement : public IDispatch

   .ends

endif

ifndef __DispSVGGElement_DISPINTERFACE_DEFINED__
define __DispSVGGElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGGElement, "30590002-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGGElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGGElement, "3051056f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGSymbolElement_INTERFACE_DEFINED__
define __ISVGSymbolElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGSymbolElement, "3050f534-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGSymbolElement : public IDispatch

   .ends

endif
ifndef __DispSVGSymbolElement_DISPINTERFACE_DEFINED__
define __DispSVGSymbolElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGSymbolElement, "30590004-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGSymbolElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGSymbolElement, "30510571-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGDefsElement_INTERFACE_DEFINED__
define __ISVGDefsElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGDefsElement, "3050f535-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGDefsElement : public IDispatch

   .ends

endif

ifndef __DispSVGDefsElement_DISPINTERFACE_DEFINED__
define __DispSVGDefsElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGDefsElement, "30590003-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGDefsElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGDefsElement, "30510570-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGAnimatedPathData_INTERFACE_DEFINED__
define __ISVGAnimatedPathData_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAnimatedPathData, "3050f536-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAnimatedPathData : public IDispatch

    putref_pathSegList	proc :ptr
    get_pathSegList	proc :ptr
    putref_normalizedPathSegList proc :ptr
    get_normalizedPathSegList proc :ptr
    putref_animatedPathSegList proc :ptr
    get_animatedPathSegList proc :ptr
    putref_animatedNormalizedPathSegList proc :ptr
    get_animatedNormalizedPathSegList proc :ptr
   .ends

endif

ifndef __ISVGPathElement_INTERFACE_DEFINED__
define __ISVGPathElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPathElement, "3050f621-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPathElement : public IDispatch

    putref_pathLength	proc :ptr
    get_pathLength	proc :ptr
    getTotalLength	proc :ptr
    getPointAtLength	proc :FLOAT, :ptr
    getPathSegAtLength	proc :FLOAT, :ptr
    createSVGPathSegClosePath proc :ptr
    createSVGPathSegMovetoAbs proc :FLOAT, :FLOAT, :ptr
    createSVGPathSegMovetoRel proc :FLOAT, :FLOAT, :ptr
    createSVGPathSegLinetoAbs proc :FLOAT, :FLOAT, :ptr
    createSVGPathSegLinetoRel proc :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoCubicAbs proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoCubicRel proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoQuadraticAbs proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoQuadraticRel proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createSVGPathSegArcAbs proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :VARIANT_BOOL, :VARIANT_BOOL, :ptr
    createSVGPathSegArcRel proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :FLOAT, :VARIANT_BOOL, :VARIANT_BOOL, :ptr
    createSVGPathSegLinetoHorizontalAbs proc :FLOAT, :ptr
    createSVGPathSegLinetoHorizontalRel proc :FLOAT, :ptr
    createSVGPathSegLinetoVerticalAbs proc :FLOAT, :ptr
    createSVGPathSegLinetoVerticalRel proc :FLOAT, :ptr
    createSVGPathSegCurvetoCubicSmoothAbs proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoCubicSmoothRel proc :FLOAT, :FLOAT, :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoQuadraticSmoothAbs proc :FLOAT, :FLOAT, :ptr
    createSVGPathSegCurvetoQuadraticSmoothRel proc :FLOAT, :FLOAT, :ptr
   .ends

endif

ifndef __DispSVGPathElement_DISPINTERFACE_DEFINED__
define __DispSVGPathElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGPathElement, "30590011-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGPathElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGPathElement, "305105b2-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGPreserveAspectRatio_INTERFACE_DEFINED__
define __ISVGPreserveAspectRatio_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGPreserveAspectRatio, "3050f3e2-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGPreserveAspectRatio : public IDispatch

    put_align		proc :sword
    get_align		proc :ptr
    put_meetOrSlice	proc :sword
    get_meetOrSlice	proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_SVGPreserveAspectRatio, "305105d0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGTextElement_INTERFACE_DEFINED__
define __ISVGTextElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTextElement, "3050f28b-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTextElement : public IDispatch

   .ends

endif

ifndef __DispSVGTextElement_DISPINTERFACE_DEFINED__
define __DispSVGTextElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGTextElement, "30590037-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGTextElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGTextElement, "305105df-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_SVGAnimatedPreserveAspectRatio, "305105ce-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGImageElement_INTERFACE_DEFINED__
define __ISVGImageElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGImageElement, "3050f828-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGImageElement : public IDispatch

    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_width	proc :ptr
    get_width		proc :ptr
    putref_height	proc :ptr
    get_height		proc :ptr
   .ends

endif

ifndef __DispSVGImageElement_DISPINTERFACE_DEFINED__
define __DispSVGImageElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGImageElement, "30590027-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGImageElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGImageElement, "305105cf-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGStopElement_INTERFACE_DEFINED__
define __ISVGStopElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGStopElement, "30510447-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGStopElement : public IDispatch

    putref_offset	proc :ptr
    get_offset		proc :ptr
   .ends

endif

ifndef __DispSVGStopElement_DISPINTERFACE_DEFINED__
define __DispSVGStopElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGStopElement, "3059002d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGStopElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGStopElement, "305105d5-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGGradientElement_INTERFACE_DEFINED__
define __ISVGGradientElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGGradientElement, "30510801-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGGradientElement : public IDispatch

    putref_gradientUnits proc :ptr
    get_gradientUnits	proc :ptr
    putref_gradientTransform proc :ptr
    get_gradientTransform proc :ptr
    putref_spreadMethod proc :ptr
    get_spreadMethod	proc :ptr
   .ends

endif

ifndef __DispSVGGradientElement_DISPINTERFACE_DEFINED__
define __DispSVGGradientElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGGradientElement, "3059002e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGGradientElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGGradientElement, "305105d6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGLinearGradientElement_INTERFACE_DEFINED__
define __ISVGLinearGradientElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGLinearGradientElement, "3050f530-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGLinearGradientElement : public IDispatch

    putref_x1		proc :ptr
    get_x1		proc :ptr
    putref_y1		proc :ptr
    get_y1		proc :ptr
    putref_x2		proc :ptr
    get_x2		proc :ptr
    putref_y2		proc :ptr
    get_y2		proc :ptr
   .ends

endif

ifndef __DispSVGLinearGradientElement_DISPINTERFACE_DEFINED__
define __DispSVGLinearGradientElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGLinearGradientElement, "3059002a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGLinearGradientElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGLinearGradientElement, "305105d2-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGRadialGradientElement_INTERFACE_DEFINED__
define __ISVGRadialGradientElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGRadialGradientElement, "3050f38a-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGRadialGradientElement : public IDispatch

    putref_cx		proc :ptr
    get_cx		proc :ptr
    putref_cy		proc :ptr
    get_cy		proc :ptr
    putref_r		proc :ptr
    get_r		proc :ptr
    putref_fx		proc :ptr
    get_fx		proc :ptr
    putref_fy		proc :ptr
    get_fy		proc :ptr
   .ends

endif

ifndef __DispSVGRadialGradientElement_DISPINTERFACE_DEFINED__
define __DispSVGRadialGradientElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGRadialGradientElement, "3059002b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGRadialGradientElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGRadialGradientElement, "305105d3-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGMaskElement_INTERFACE_DEFINED__
define __ISVGMaskElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGMaskElement, "3050f528-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGMaskElement : public IDispatch

    putref_maskUnits	proc :ptr
    get_maskUnits	proc :ptr
    putref_maskContentUnits proc :ptr
    get_maskContentUnits proc :ptr
    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_width	proc :ptr
    get_width		proc :ptr
    putref_height	proc :ptr
    get_height		proc :ptr
   .ends

endif

ifndef __DispSVGMaskElement_DISPINTERFACE_DEFINED__
define __DispSVGMaskElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGMaskElement, "3059003C-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGMaskElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGMaskElement, "305105e7-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGMarkerElement_INTERFACE_DEFINED__
define __ISVGMarkerElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGMarkerElement, "3050f620-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGMarkerElement : public IDispatch

    putref_refX		proc :ptr
    get_refX		proc :ptr
    putref_refY		proc :ptr
    get_refY		proc :ptr
    putref_markerUnits	proc :ptr
    get_markerUnits	proc :ptr
    putref_markerWidth	proc :ptr
    get_markerWidth	proc :ptr
    putref_markerHeight proc :ptr
    get_markerHeight	proc :ptr
    putref_orientType	proc :ptr
    get_orientType	proc :ptr
    putref_orientAngle	proc :ptr
    get_orientAngle	proc :ptr
    setOrientToAuto	proc
    setOrientToAngle	proc :ptr
   .ends

endif

ifndef __DispSVGMarkerElement_DISPINTERFACE_DEFINED__
define __DispSVGMarkerElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGMarkerElement, "30590036-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGMarkerElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGMarkerElement, "305105de-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGZoomEvent_INTERFACE_DEFINED__
define __ISVGZoomEvent_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGZoomEvent, "3050f3c4-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGZoomEvent : public IDispatch

    get_zoomRectScreen	proc :ptr
    get_previousScale	proc :ptr
    get_previousTranslate proc :ptr
    get_newScale	proc :ptr
    get_newTranslate	proc :ptr
   .ends

endif

ifndef __DispSVGZoomEvent_DISPINTERFACE_DEFINED__
define __DispSVGZoomEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGZoomEvent, "30590031-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGZoomEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGZoomEvent, "305105d9-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGAElement_INTERFACE_DEFINED__
define __ISVGAElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGAElement, "3050f24f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGAElement : public IDispatch

    putref_target	proc :ptr
    get_target		proc :ptr
   .ends

endif

ifndef __DispSVGAElement_DISPINTERFACE_DEFINED__
define __DispSVGAElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGAElement, "30590033-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGAElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGAElement, "305105db-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGViewElement_INTERFACE_DEFINED__
define __ISVGViewElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGViewElement, "3050f4cd-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGViewElement : public IDispatch

    putref_viewTarget	proc :ptr
    get_viewTarget	proc :ptr
   .ends

endif

ifndef __DispSVGViewElement_DISPINTERFACE_DEFINED__
define __DispSVGViewElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGViewElement, "30590034-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGViewElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGViewElement, "305105dc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLMediaError_INTERFACE_DEFINED__
define __IHTMLMediaError_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMediaError, "3050f827-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMediaError : public IDispatch

    get_code		proc :ptr
   .ends

endif

ifndef __IHTMLTimeRanges_INTERFACE_DEFINED__
define __IHTMLTimeRanges_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTimeRanges, "3051043e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTimeRanges : public IDispatch

    get_length		proc :ptr
    start		proc :LONG, :ptr
    _end		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLTimeRanges2_INTERFACE_DEFINED__
define __IHTMLTimeRanges2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLTimeRanges2, "305104b5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLTimeRanges2 : public IDispatch

    startDouble		proc :LONG, :ptr
    endDouble		proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLMediaElement_INTERFACE_DEFINED__
define __IHTMLMediaElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMediaElement, "3050f83d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMediaElement : public IDispatch

    get_error		proc :ptr
    put_src		proc :BSTR
    get_src		proc :ptr
    get_currentSrc	proc :ptr
    get_networkState	proc :ptr
    put_preload		proc :BSTR
    get_preload		proc :ptr
    get_buffered	proc :ptr
    load		proc
    canPlayType		proc :BSTR, :ptr
    get_seeking		proc :ptr
    put_currentTime	proc :FLOAT
    get_currentTime	proc :ptr
    get_initialTime	proc :ptr
    get_duration	proc :ptr
    get_paused		proc :ptr
    put_defaultPlaybackRate proc :FLOAT
    get_defaultPlaybackRate proc :ptr
    put_playbackRate	proc :FLOAT
    get_playbackRate	proc :ptr
    get_played		proc :ptr
    get_seekable	proc :ptr
    get_ended		proc :ptr
    put_autoplay	proc :VARIANT_BOOL
    get_autoplay	proc :ptr
    put_loop		proc :VARIANT_BOOL
    get_loop		proc :ptr
    play		proc
    _pause		proc
    put_controls	proc :VARIANT_BOOL
    get_controls	proc :ptr
    put_volume		proc :FLOAT
    get_volume		proc :ptr
    put_muted		proc :VARIANT_BOOL
    get_muted		proc :ptr
    put_autobuffer	proc :VARIANT_BOOL
    get_autobuffer	proc :ptr
   .ends

endif

ifndef __IHTMLMediaElement2_INTERFACE_DEFINED__
define __IHTMLMediaElement2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMediaElement2, "30510444-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMediaElement2 : public IDispatch

    put_currentTimeDouble proc :DOUBLE
    get_currentTimeDouble proc :ptr
    get_initialTimeDouble proc :ptr
    get_durationDouble	proc :ptr
    put_defaultPlaybackRateDouble proc :DOUBLE
    get_defaultPlaybackRateDouble proc :ptr
    put_playbackRateDouble proc :DOUBLE
    get_playbackRateDouble proc :ptr
    put_volumeDouble	proc :DOUBLE
    get_volumeDouble	proc :ptr
   .ends

endif

ifndef __IHTMLMSMediaElement_INTERFACE_DEFINED__
define __IHTMLMSMediaElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLMSMediaElement, "3050f529-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLMSMediaElement : public IDispatch

    put_msPlayToDisabled proc :VARIANT_BOOL
    get_msPlayToDisabled proc :ptr
    put_msPlayToPrimary proc :VARIANT_BOOL
    get_msPlayToPrimary proc :ptr
   .ends

endif

ifndef __IHTMLSourceElement_INTERFACE_DEFINED__
define __IHTMLSourceElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLSourceElement, "3050f590-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLSourceElement : public IDispatch

    put_src		proc :BSTR
    get_src		proc :ptr
    put_type		proc :BSTR
    get_type		proc :ptr
    put_media		proc :BSTR
    get_media		proc :ptr
   .ends

endif

ifndef __IHTMLAudioElement_INTERFACE_DEFINED__
define __IHTMLAudioElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAudioElement, "3050f7ff-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAudioElement : public IDispatch

   .ends

endif

ifndef __IHTMLVideoElement_INTERFACE_DEFINED__
define __IHTMLVideoElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLVideoElement, "3050f800-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLVideoElement : public IDispatch

    put_width		proc :LONG
    get_width		proc :ptr
    put_height		proc :LONG
    get_height		proc :ptr
    get_videoWidth	proc :ptr
    get_videoHeight	proc :ptr
    put_poster		proc :BSTR
    get_poster		proc :ptr
   .ends

endif

ifndef __IHTMLAudioElementFactory_INTERFACE_DEFINED__
define __IHTMLAudioElementFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAudioElementFactory, "3050f6db-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAudioElementFactory : public IDispatch

    create		proc :VARIANT, :ptr
   .ends

endif

ifndef __DispHTMLMediaError_DISPINTERFACE_DEFINED__
define __DispHTMLMediaError_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMediaError, "30590086-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMediaError : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMediaError, "3051070a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLTimeRanges_DISPINTERFACE_DEFINED__
define __DispHTMLTimeRanges_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLTimeRanges, "30590087-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLTimeRanges : public IDispatch

   .ends

endif
DEFINE_GUIDS(CLSID_HTMLTimeRanges, "3051070b-98b5-11cf-bb82-00aa00bdce0b")
ifndef __DispHTMLMediaElement_DISPINTERFACE_DEFINED__
define __DispHTMLMediaElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLMediaElement, "30590088-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLMediaElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLMediaElement, "3051070c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLSourceElement_DISPINTERFACE_DEFINED__
define __DispHTMLSourceElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLSourceElement, "30590089-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLSourceElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLSourceElement, "3051070d-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLAudioElement_DISPINTERFACE_DEFINED__
define __DispHTMLAudioElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLAudioElement, "3059008a-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLAudioElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLAudioElement, "3051070e-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_HTMLAudioElementFactory, "305107ec-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLVideoElement_DISPINTERFACE_DEFINED__
define __DispHTMLVideoElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLVideoElement, "3059008b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLVideoElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLVideoElement, "3051070f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGSwitchElement_INTERFACE_DEFINED__
define __ISVGSwitchElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGSwitchElement, "3050f82e-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGSwitchElement : public IDispatch

   .ends

endif

ifndef __DispSVGSwitchElement_DISPINTERFACE_DEFINED__
define __DispSVGSwitchElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGSwitchElement, "30590030-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGSwitchElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGSwitchElement, "305105d8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGDescElement_INTERFACE_DEFINED__
define __ISVGDescElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGDescElement, "3050f541-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGDescElement : public IDispatch

   .ends

endif

ifndef __DispSVGDescElement_DISPINTERFACE_DEFINED__
define __DispSVGDescElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGDescElement, "30590005-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGDescElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGDescElement, "30510572-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGTitleElement_INTERFACE_DEFINED__
define __ISVGTitleElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTitleElement, "3050f313-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTitleElement : public IDispatch

   .ends

endif

ifndef __DispSVGTitleElement_DISPINTERFACE_DEFINED__
define __DispSVGTitleElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGTitleElement, "30590006-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGTitleElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGTitleElement, "30510573-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGMetadataElement_INTERFACE_DEFINED__
define __ISVGMetadataElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGMetadataElement, "3050f7f5-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGMetadataElement : public IDispatch

   .ends

endif

ifndef __DispSVGMetadataElement_DISPINTERFACE_DEFINED__
define __DispSVGMetadataElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGMetadataElement, "3059002f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGMetadataElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGMetadataElement, "305105d7-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGElementInstanceList_INTERFACE_DEFINED__
define __ISVGElementInstanceList_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGElementInstanceList, "3051042d-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGElementInstanceList : public IDispatch

    get_length		proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __DispSVGElementInstance_DISPINTERFACE_DEFINED__
define __DispSVGElementInstance_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGElementInstance, "30590007-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGElementInstance : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGElementInstance, "30510575-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGElementInstanceList_DISPINTERFACE_DEFINED__
define __DispSVGElementInstanceList_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGElementInstanceList, "30590008-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGElementInstanceList : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGElementInstanceList, "30510576-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMException_INTERFACE_DEFINED__
define __IDOMException_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMException, "3050f513-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMException : public IDispatch

    put_code		proc :LONG
    get_code		proc :ptr
    get_message		proc :ptr
   .ends

endif

ifndef __IRangeException_INTERFACE_DEFINED__
define __IRangeException_INTERFACE_DEFINED__
DEFINE_IIDX(IRangeException, "3050f315-98b5-11cf-bb82-00aa00bdce0b")

.comdef IRangeException : public IDispatch

    put_code		proc :LONG
    get_code		proc :ptr
    get_message		proc :ptr
   .ends

endif

ifndef __ISVGException_INTERFACE_DEFINED__
define __ISVGException_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGException, "3050f4e6-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGException : public IDispatch

    put_code		proc :LONG
    get_code		proc :ptr
    get_message		proc :ptr
   .ends

endif

ifndef __IEventException_INTERFACE_DEFINED__
define __IEventException_INTERFACE_DEFINED__
DEFINE_IIDX(IEventException, "30510433-98b5-11cf-bb82-00aa00bdce0b")

.comdef IEventException : public IDispatch

    put_code		proc :LONG
    get_code		proc :ptr
    get_message		proc :ptr
   .ends

endif

ifndef __DispDOMException_DISPINTERFACE_DEFINED__
define __DispDOMException_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMException, "30590094-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMException : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMException, "3051072c-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispRangeException_DISPINTERFACE_DEFINED__
define __DispRangeException_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispRangeException, "30590095-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispRangeException : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_RangeException, "3051072e-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispSVGException_DISPINTERFACE_DEFINED__
define __DispSVGException_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGException, "30590096-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGException : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGException, "30510730-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispEventException_DISPINTERFACE_DEFINED__
define __DispEventException_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispEventException, "30590099-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispEventException : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_EventException, "3051073b-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGScriptElement_INTERFACE_DEFINED__
define __ISVGScriptElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGScriptElement, "3050f51b-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGScriptElement : public IDispatch

    put_type		proc :BSTR
    get_type		proc :ptr
   .ends

endif

ifndef __DispSVGScriptElement_DISPINTERFACE_DEFINED__
define __DispSVGScriptElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGScriptElement, "30590039-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGScriptElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGScriptElement, "305105e1-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGStyleElement_INTERFACE_DEFINED__
define __ISVGStyleElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGStyleElement, "3050f212-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGStyleElement : public IDispatch

    put_type		proc :BSTR
    get_type		proc :ptr
    put_media		proc :BSTR
    get_media		proc :ptr
   .ends

endif

ifndef __DispSVGStyleElement_DISPINTERFACE_DEFINED__
define __DispSVGStyleElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGStyleElement, "30590029-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGStyleElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGStyleElement, "305105d1-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGTextContentElement_INTERFACE_DEFINED__
define __ISVGTextContentElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTextContentElement, "3050f3e7-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTextContentElement : public IDispatch

    putref_textLength	proc :ptr
    get_textLength	proc :ptr
    putref_lengthAdjust proc :ptr
    get_lengthAdjust	proc :ptr
    getNumberOfChars	proc :ptr
    getComputedTextLength proc :ptr
    getSubStringLength	proc :LONG, :LONG, :ptr
    getStartPositionOfChar proc :LONG, :ptr
    getEndPositionOfChar proc :LONG, :ptr
    getExtentOfChar	proc :LONG, :ptr
    getRotationOfChar	proc :LONG, :ptr
    getCharNumAtPosition proc :ptr, :ptr
    selectSubString	proc :LONG, :LONG
   .ends

endif

ifndef __DispSVGTextContentElement_DISPINTERFACE_DEFINED__
define __DispSVGTextContentElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGTextContentElement, "30590035-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGTextContentElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGTextContentElement, "305105dd-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGTextPositioningElement_INTERFACE_DEFINED__
define __ISVGTextPositioningElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTextPositioningElement, "3050f833-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTextPositioningElement : public IDispatch

    putref_x		proc :ptr
    get_x		proc :ptr
    putref_y		proc :ptr
    get_y		proc :ptr
    putref_dx		proc :ptr
    get_dx		proc :ptr
    putref_dy		proc :ptr
    get_dy		proc :ptr
    putref_rotate	proc :ptr
    get_rotate		proc :ptr
   .ends

endif

ifndef __DispSVGTextPositioningElement_DISPINTERFACE_DEFINED__
define __DispSVGTextPositioningElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGTextPositioningElement, "30590038-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGTextPositioningElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGTextPositioningElement, "305105e0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispDOMDocumentType_DISPINTERFACE_DEFINED__
define __DispDOMDocumentType_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMDocumentType, "30590098-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMDocumentType : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMDocumentType, "30510739-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispNodeIterator_DISPINTERFACE_DEFINED__
define __DispNodeIterator_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispNodeIterator, "3059009c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispNodeIterator : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_NodeIterator, "30510745-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispTreeWalker_DISPINTERFACE_DEFINED__
define __DispTreeWalker_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispTreeWalker, "3059009d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispTreeWalker : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_TreeWalker, "30510747-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispDOMProcessingInstruction_DISPINTERFACE_DEFINED__
define __DispDOMProcessingInstruction_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMProcessingInstruction, "3059009b-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMProcessingInstruction : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMProcessingInstruction, "30510743-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLPerformanceNavigation_INTERFACE_DEFINED__
define __IHTMLPerformanceNavigation_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPerformanceNavigation, "3050f3ea-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPerformanceNavigation : public IDispatch

    get_type		proc :ptr
    get_redirectCount	proc :ptr
    toString		proc :ptr
    toJSON		proc :ptr
   .ends

endif

ifndef __IHTMLPerformanceTiming_INTERFACE_DEFINED__
define __IHTMLPerformanceTiming_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPerformanceTiming, "3050f834-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPerformanceTiming : public IDispatch

    get_navigationStart proc :ptr
    get_unloadEventStart proc :ptr
    get_unloadEventEnd	proc :ptr
    get_redirectStart	proc :ptr
    get_redirectEnd	proc :ptr
    get_fetchStart	proc :ptr
    get_domainLookupStart proc :ptr
    get_domainLookupEnd proc :ptr
    get_connectStart	proc :ptr
    get_connectEnd	proc :ptr
    get_requestStart	proc :ptr
    get_responseStart	proc :ptr
    get_responseEnd	proc :ptr
    get_domLoading	proc :ptr
    get_domInteractive	proc :ptr
    get_domContentLoadedEventStart proc :ptr
    get_domContentLoadedEventEnd proc :ptr
    get_domComplete	proc :ptr
    get_loadEventStart	proc :ptr
    get_loadEventEnd	proc :ptr
    get_msFirstPaint	proc :ptr
    toString		proc :ptr
    toJSON		proc :ptr
   .ends

endif

ifndef __DispHTMLPerformance_DISPINTERFACE_DEFINED__
define __DispHTMLPerformance_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLPerformance, "3059009f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLPerformance : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLPerformance, "3051074f-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLPerformanceNavigation_DISPINTERFACE_DEFINED__
define __DispHTMLPerformanceNavigation_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLPerformanceNavigation, "305900a0-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLPerformanceNavigation : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLPerformanceNavigation, "30510751-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLPerformanceTiming_DISPINTERFACE_DEFINED__
define __DispHTMLPerformanceTiming_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLPerformanceTiming, "305900a1-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLPerformanceTiming : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLPerformanceTiming, "30510753-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ISVGTSpanElement_INTERFACE_DEFINED__
define __ISVGTSpanElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTSpanElement, "3050f50f-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTSpanElement : public IDispatch

   .ends

endif

ifndef __DispSVGTSpanElement_DISPINTERFACE_DEFINED__
define __DispSVGTSpanElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGTSpanElement, "3059003A-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGTSpanElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGTSpanElement, "305105e2-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ITemplatePrinter_INTERFACE_DEFINED__
define __ITemplatePrinter_INTERFACE_DEFINED__
DEFINE_IIDX(ITemplatePrinter, "3050f545-98b5-11cf-bb82-00aa00bdce0b")

.comdef ITemplatePrinter : public IDispatch

    startDoc		proc :BSTR, :ptr
    stopDoc		proc
    printBlankPage	proc
    printPage		proc :ptr
    ensurePrintDialogDefaults proc :ptr
    showPrintDialog	proc :ptr
    showPageSetupDialog proc :ptr
    printNonNative	proc :ptr, :ptr
    printNonNativeFrames proc :ptr, :VARIANT_BOOL
    put_framesetDocument proc :VARIANT_BOOL
    get_framesetDocument proc :ptr
    put_frameActive	proc :VARIANT_BOOL
    get_frameActive	proc :ptr
    put_frameAsShown	proc :VARIANT_BOOL
    get_frameAsShown	proc :ptr
    put_selection	proc :VARIANT_BOOL
    get_selection	proc :ptr
    put_selectedPages	proc :VARIANT_BOOL
    get_selectedPages	proc :ptr
    put_currentPage	proc :VARIANT_BOOL
    get_currentPage	proc :ptr
    put_currentPageAvail proc :VARIANT_BOOL
    get_currentPageAvail proc :ptr
    put_collate		proc :VARIANT_BOOL
    get_collate		proc :ptr
    get_duplex		proc :ptr
    put_copies		proc :USHORT
    get_copies		proc :ptr
    put_pageFrom	proc :USHORT
    get_pageFrom	proc :ptr
    put_pageTo		proc :USHORT
    get_pageTo		proc :ptr
    put_tableOfLinks	proc :VARIANT_BOOL
    get_tableOfLinks	proc :ptr
    put_allLinkedDocuments proc :VARIANT_BOOL
    get_allLinkedDocuments proc :ptr
    put_header		proc :BSTR
    get_header		proc :ptr
    put_footer		proc :BSTR
    get_footer		proc :ptr
    put_marginLeft	proc :LONG
    get_marginLeft	proc :ptr
    put_marginRight	proc :LONG
    get_marginRight	proc :ptr
    put_marginTop	proc :LONG
    get_marginTop	proc :ptr
    put_marginBottom	proc :LONG
    get_marginBottom	proc :ptr
    get_pageWidth	proc :ptr
    get_pageHeight	proc :ptr
    get_unprintableLeft proc :ptr
    get_unprintableTop	proc :ptr
    get_unprintableRight proc :ptr
    get_unprintableBottom proc :ptr
    updatePageStatus	proc :ptr
   .ends

endif

ifndef __ITemplatePrinter2_INTERFACE_DEFINED__
define __ITemplatePrinter2_INTERFACE_DEFINED__
DEFINE_IIDX(ITemplatePrinter2, "3050f546-98b5-11cf-bb82-00aa00bdce0b")

.comdef ITemplatePrinter2 : public ITemplatePrinter

    put_selectionEnabled proc :VARIANT_BOOL
    get_selectionEnabled proc :ptr
    put_frameActiveEnabled proc :VARIANT_BOOL
    get_frameActiveEnabled proc :ptr
    put_orientation	proc :BSTR
    get_orientation	proc :ptr
    put_usePrinterCopyCollate proc :VARIANT_BOOL
    get_usePrinterCopyCollate proc :ptr
    deviceSupports	proc :BSTR, :ptr
   .ends

endif

ifndef __ITemplatePrinter3_INTERFACE_DEFINED__
define __ITemplatePrinter3_INTERFACE_DEFINED__
DEFINE_IIDX(ITemplatePrinter3, "3050f3e5-98b5-11cf-bb82-00aa00bdce0b")

.comdef ITemplatePrinter3 : public ITemplatePrinter2

    put_headerFooterFont proc :BSTR
    get_headerFooterFont proc :ptr
    getPageMarginTop	proc :ptr, :LONG, :LONG, :ptr
    getPageMarginRight	proc :ptr, :LONG, :LONG, :ptr
    getPageMarginBottom proc :ptr, :LONG, :LONG, :ptr
    getPageMarginLeft	proc :ptr, :LONG, :LONG, :ptr
    getPageMarginTopImportant proc :ptr, :ptr
    getPageMarginRightImportant proc :ptr, :ptr
    getPageMarginBottomImportant proc :ptr, :ptr
    getPageMarginLeftImportant proc :ptr, :ptr
   .ends

endif

ifndef __IPrintManagerTemplatePrinter_INTERFACE_DEFINED__
define __IPrintManagerTemplatePrinter_INTERFACE_DEFINED__
DEFINE_IIDX(IPrintManagerTemplatePrinter, "3050f544-98b5-11cf-bb82-00aa00bdce0b")

.comdef IPrintManagerTemplatePrinter : public IDispatch

    startPrint		proc
    drawPreviewPage	proc :ptr, :LONG
    setPageCount	proc :LONG
    invalidatePreview	proc
    getPrintTaskOptionValue proc :BSTR, :ptr
    endPrint		proc
   .ends

endif

ifndef __IPrintManagerTemplatePrinter2_INTERFACE_DEFINED__
define __IPrintManagerTemplatePrinter2_INTERFACE_DEFINED__
DEFINE_IIDX(IPrintManagerTemplatePrinter2, "3050f319-98b5-11cf-bb82-00aa00bdce0b")

.comdef IPrintManagerTemplatePrinter2 : public IPrintManagerTemplatePrinter

    get_showHeaderFooter proc :ptr
    get_shrinkToFit	proc :ptr
    get_percentScale	proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_CTemplatePrinter, "3050f6b3-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispCPrintManagerTemplatePrinter_DISPINTERFACE_DEFINED__
define __DispCPrintManagerTemplatePrinter_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispCPrintManagerTemplatePrinter, "305900e9-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispCPrintManagerTemplatePrinter : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_CPrintManagerTemplatePrinter, "63619f54-9d71-4c23-a08d-50d7f18db2e9")

ifndef __ISVGTextPathElement_INTERFACE_DEFINED__
define __ISVGTextPathElement_INTERFACE_DEFINED__
DEFINE_IIDX(ISVGTextPathElement, "3050f5c6-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISVGTextPathElement : public IDispatch

    putref_startOffset	proc :ptr
    get_startOffset	proc :ptr
    putref_method	proc :ptr
    get_method		proc :ptr
    putref_spacing	proc :ptr
    get_spacing		proc :ptr
   .ends

endif

ifndef __DispSVGTextPathElement_DISPINTERFACE_DEFINED__
define __DispSVGTextPathElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispSVGTextPathElement, "3059003D-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispSVGTextPathElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_SVGTextPathElement, "305105eb-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMXmlSerializer_INTERFACE_DEFINED__
define __IDOMXmlSerializer_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMXmlSerializer, "30510796-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMXmlSerializer : public IDispatch

    serializeToString	proc :ptr, :ptr
   .ends

endif

ifndef __IDOMXmlSerializerFactory_INTERFACE_DEFINED__
define __IDOMXmlSerializerFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMXmlSerializerFactory, "3050f514-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMXmlSerializerFactory : public IDispatch

    create		proc :ptr
   .ends

endif

ifndef __IDOMParser_INTERFACE_DEFINED__
define __IDOMParser_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMParser, "3050f369-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMParser : public IDispatch

    parseFromString	proc :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IDOMParserFactory_INTERFACE_DEFINED__
define __IDOMParserFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMParserFactory, "3050f53c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMParserFactory : public IDispatch

    create		proc :ptr
   .ends

endif

ifndef __DispXMLSerializer_DISPINTERFACE_DEFINED__
define __DispXMLSerializer_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispXMLSerializer, "305900ad-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispXMLSerializer : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_XMLSerializer, "3051077e-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_HTMLDOMXmlSerializerFactory, "30510780-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispDOMParser_DISPINTERFACE_DEFINED__
define __DispDOMParser_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMParser, "305900ae-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMParser : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMParser, "30510782-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_DOMParserFactory, "30510784-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLSemanticElement_DISPINTERFACE_DEFINED__
define __DispHTMLSemanticElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLSemanticElement, "305900ba-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLSemanticElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLSemanticElement, "305107b0-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLProgressElement_INTERFACE_DEFINED__
define __IHTMLProgressElement_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLProgressElement, "3050f376-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLProgressElement : public IDispatch

    put_value		proc :FLOAT
    get_value		proc :ptr
    put_max		proc :FLOAT
    get_max		proc :ptr
    get_position	proc :ptr
    get_form		proc :ptr
   .ends

endif

ifndef __DispHTMLProgressElement_DISPINTERFACE_DEFINED__
define __DispHTMLProgressElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLProgressElement, "305900af-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLProgressElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLProgressElement, "3050f2d5-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMMSTransitionEvent_INTERFACE_DEFINED__
define __IDOMMSTransitionEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMSTransitionEvent, "3050f377-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMMSTransitionEvent : public IDispatch

    get_propertyName	proc :ptr
    get_elapsedTime	proc :ptr
    initMSTransitionEvent proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :FLOAT
   .ends

endif

ifndef __DispDOMMSTransitionEvent_DISPINTERFACE_DEFINED__
define __DispDOMMSTransitionEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMSTransitionEvent, "305900bb-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMSTransitionEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMSTransitionEvent, "305107b6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMMSAnimationEvent_INTERFACE_DEFINED__
define __IDOMMSAnimationEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMSAnimationEvent, "3050f378-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMMSAnimationEvent : public IDispatch

    get_animationName	proc :ptr
    get_elapsedTime	proc :ptr
    initMSAnimationEvent proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :BSTR, :FLOAT
   .ends

endif

ifndef __DispDOMMSAnimationEvent_DISPINTERFACE_DEFINED__
define __DispDOMMSAnimationEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMSAnimationEvent, "305900bc-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMSAnimationEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMSAnimationEvent, "305107b8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IWebGeocoordinates_INTERFACE_DEFINED__
define __IWebGeocoordinates_INTERFACE_DEFINED__
DEFINE_IIDX(IWebGeocoordinates, "3050f615-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWebGeocoordinates : public IDispatch

    get_latitude	proc :ptr
    get_longitude	proc :ptr
    get_altitude	proc :ptr
    get_accuracy	proc :ptr
    get_altitudeAccuracy proc :ptr
    get_heading		proc :ptr
    get_speed		proc :ptr
   .ends

endif

ifndef __IWebGeopositionError_INTERFACE_DEFINED__
define __IWebGeopositionError_INTERFACE_DEFINED__
DEFINE_IIDX(IWebGeopositionError, "3050f3cb-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWebGeopositionError : public IDispatch

    get_code		proc :ptr
    get_message		proc :ptr
   .ends

endif

ifndef __IWebGeoposition_INTERFACE_DEFINED__
define __IWebGeoposition_INTERFACE_DEFINED__
DEFINE_IIDX(IWebGeoposition, "3050f375-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWebGeoposition : public IDispatch

    get_coords		proc :ptr
    get_timestamp	proc :ptr
   .ends

endif

ifndef __DispWebGeolocation_DISPINTERFACE_DEFINED__
define __DispWebGeolocation_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispWebGeolocation, "305900bd-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispWebGeolocation : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_WebGeolocation, "305107c6-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispWebGeocoordinates_DISPINTERFACE_DEFINED__
define __DispWebGeocoordinates_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispWebGeocoordinates, "305900be-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispWebGeocoordinates : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_WebGeocoordinates, "305107c8-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispWebGeopositionError_DISPINTERFACE_DEFINED__
define __DispWebGeopositionError_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispWebGeopositionError, "305900bf-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispWebGeopositionError : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_WebGeopositionError, "305107ca-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispWebGeoposition_DISPINTERFACE_DEFINED__
define __DispWebGeoposition_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispWebGeoposition, "305900c1-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispWebGeoposition : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_WebGeoposition, "305107ce-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IClientCaps_INTERFACE_DEFINED__
define __IClientCaps_INTERFACE_DEFINED__
DEFINE_IIDX(IClientCaps, "3051072a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IClientCaps : public IDispatch

    get_javaEnabled	proc :ptr
    get_cookieEnabled	proc :ptr
    get_cpuClass	proc :ptr
    get_systemLanguage	proc :ptr
    get_userLanguage	proc :ptr
    get_platform	proc :ptr
    get_connectionSpeed proc :ptr
    get_onLine		proc :ptr
    get_colorDepth	proc :ptr
    get_bufferDepth	proc :ptr
    get_width		proc :ptr
    get_height		proc :ptr
    get_availHeight	proc :ptr
    get_availWidth	proc :ptr
    get_connectionType	proc :ptr
    isComponentInstalled proc :BSTR, :BSTR, :BSTR, :ptr
    getComponentVersion proc :BSTR, :BSTR, :ptr
    compareVersions	proc :BSTR, :BSTR, :ptr
    addComponentRequest proc :BSTR, :BSTR, :BSTR
    doComponentRequest	proc :ptr
    clearComponentRequest proc
   .ends

endif

DEFINE_GUIDS(CLSID_CClientCaps, "7E8BC44E-AEFF-11D1-89C2-00C04FB6BFC4")

ifndef __IDOMMSManipulationEvent_INTERFACE_DEFINED__
define __IDOMMSManipulationEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMMSManipulationEvent, "3050f511-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMMSManipulationEvent : public IDispatch

    get_lastState	proc :ptr
    get_currentState	proc :ptr
    initMSManipulationEvent proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :ptr, :LONG, :LONG, :LONG
   .ends

endif

ifndef __DispDOMMSManipulationEvent_DISPINTERFACE_DEFINED__
define __DispDOMMSManipulationEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMMSManipulationEvent, "305900e1-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMMSManipulationEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMMSManipulationEvent, "30510817-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDOMCloseEvent_INTERFACE_DEFINED__
define __IDOMCloseEvent_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMCloseEvent, "3050f3d5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMCloseEvent : public IDispatch

    get_wasClean	proc :ptr
    initCloseEvent	proc :BSTR, :VARIANT_BOOL, :VARIANT_BOOL, :VARIANT_BOOL, :LONG, :BSTR
   .ends

endif

ifndef __DispDOMCloseEvent_DISPINTERFACE_DEFINED__
define __DispDOMCloseEvent_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispDOMCloseEvent, "305900dc-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispDOMCloseEvent : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_DOMCloseEvent, "30510800-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispApplicationCache_DISPINTERFACE_DEFINED__
define __DispApplicationCache_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispApplicationCache, "305900e4-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispApplicationCache : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_ApplicationCache, "30510829-98b5-11cf-bb82-00aa00bdce0b")

ifndef __ICSSFilterSite_INTERFACE_DEFINED__
define __ICSSFilterSite_INTERFACE_DEFINED__
DEFINE_IIDX(ICSSFilterSite, "305106ec-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICSSFilterSite : public IUnknown

    GetElement		proc :ptr
    FireOnFilterChangeEvent proc
   .ends

endif

ifndef __IMarkupPointer_INTERFACE_DEFINED__
define __IMarkupPointer_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupPointer, "30590081-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupPointer : public IUnknown

    OwningDoc		proc :ptr
    Gravity		proc :ptr
    SetGravity		proc :POINTER_GRAVITY
    Cling		proc :ptr
    SetCling		proc :BOOL
    Unposition		proc
    IsPositioned	proc :ptr
    GetContainer	proc :ptr
    MoveAdjacentToElement proc :ptr, :ELEMENT_ADJACENCY
    MoveToPointer	proc :ptr
    MoveToContainer	proc :ptr, :BOOL
    Left		proc :BOOL, :ptr, :ptr, :ptr, :ptr
    Right		proc :BOOL, :ptr, :ptr, :ptr, :ptr
    CurrentScope	proc :ptr
    IsLeftOf		proc :ptr, :ptr
    IsLeftOfOrEqualTo	proc :ptr, :ptr
    IsRightOf		proc :ptr, :ptr
    IsRightOfOrEqualTo	proc :ptr, :ptr
    IsEqualTo		proc :ptr, :ptr
    MoveUnit		proc :MOVEUNIT_ACTION
    FindText		proc :ptr, :DWORD, :ptr, :ptr
   .ends

endif

ifndef __IMarkupContainer_INTERFACE_DEFINED__
define __IMarkupContainer_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupContainer, "30510454-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupContainer : public IUnknown

    OwningDoc		proc :ptr
   .ends

endif

ifndef __IMarkupContainer2_INTERFACE_DEFINED__
define __IMarkupContainer2_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupContainer2, "30510456-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupContainer2 : public IMarkupContainer

    CreateChangeLog	proc :ptr, :ptr, :BOOL, :BOOL
    RegisterForDirtyRange proc :ptr, :ptr
    UnRegisterForDirtyRange proc :DWORD
    GetAndClearDirtyRange proc :DWORD, :ptr, :ptr
    GetVersionNumber	proc
    GetMasterElement	proc :ptr
   .ends

endif

ifndef __IHTMLChangeLog_INTERFACE_DEFINED__
define __IHTMLChangeLog_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLChangeLog, "3050f599-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLChangeLog : public IUnknown

    GetNextChange	proc :ptr, :LONG, :ptr
   .ends

endif

ifndef __IHTMLChangeSink_INTERFACE_DEFINED__
define __IHTMLChangeSink_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLChangeSink, "30510799-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLChangeSink : public IUnknown

    Notify		proc
   .ends

endif

ifndef __IActiveIMMApp_INTERFACE_DEFINED__
define __IActiveIMMApp_INTERFACE_DEFINED__
DEFINE_IIDX(IActiveIMMApp, "3050f59d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IActiveIMMApp : public IUnknown

    AssociateContext	proc :HWND, :HIMC, :ptr
    ConfigureIMEA	proc :HKL, :HWND, :DWORD, :ptr
    ConfigureIMEW	proc :HKL, :HWND, :DWORD, :ptr
    CreateContext	proc :ptr
    DestroyContext	proc :HIMC
    EnumRegisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR, :LPVOID, :ptr
    EnumRegisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR, :LPVOID, :ptr
    EscapeA		proc :HKL, :HIMC, :UINT, :LPVOID, :ptr
    EscapeW		proc :HKL, :HIMC, :UINT, :LPVOID, :ptr
    GetCandidateListA	proc :HIMC, :DWORD, :UINT, :ptr, :ptr
    GetCandidateListW	proc :HIMC, :DWORD, :UINT, :ptr, :ptr
    GetCandidateListCountA proc :HIMC, :ptr, :ptr
    GetCandidateListCountW proc :HIMC, :ptr, :ptr
    GetCandidateWindow	proc :HIMC, :DWORD, :ptr
    GetCompositionFontA proc :HIMC, :ptr
    GetCompositionFontW proc :HIMC, :ptr
    GetCompositionStringA proc :HIMC, :DWORD, :DWORD, :ptr, :LPVOID
    GetCompositionStringW proc :HIMC, :DWORD, :DWORD, :ptr, :LPVOID
    GetCompositionWindow proc :HIMC, :ptr
    GetContext		proc :HWND, :ptr
    GetConversionListA	proc :HKL, :HIMC, :LPSTR, :UINT, :UINT, :ptr, :ptr
    GetConversionListW	proc :HKL, :HIMC, :LPWSTR, :UINT, :UINT, :ptr, :ptr
    GetConversionStatus proc :HIMC, :ptr, :ptr
    GetDefaultIMEWnd	proc :HWND, :ptr
    GetDescriptionA	proc :HKL, :UINT, :LPSTR, :ptr
    GetDescriptionW	proc :HKL, :UINT, :LPWSTR, :ptr
    GetGuideLineA	proc :HIMC, :DWORD, :DWORD, :LPSTR, :ptr
    GetGuideLineW	proc :HIMC, :DWORD, :DWORD, :LPWSTR, :ptr
    GetIMEFileNameA	proc :HKL, :UINT, :LPSTR, :ptr
    GetIMEFileNameW	proc :HKL, :UINT, :LPWSTR, :ptr
    GetOpenStatus	proc :HIMC
    GetProperty		proc :HKL, :DWORD, :ptr
    GetRegisterWordStyleA proc :HKL, :UINT, :ptr, :ptr
    GetRegisterWordStyleW proc :HKL, :UINT, :ptr, :ptr
    GetStatusWindowPos	proc :HIMC, :ptr
    GetVirtualKey	proc :HWND, :ptr
    InstallIMEA		proc :LPSTR, :LPSTR, :ptr
    InstallIMEW		proc :LPWSTR, :LPWSTR, :ptr
    IsIME		proc :HKL
    IsUIMessageA	proc :HWND, :UINT, :WPARAM, :LPARAM
    IsUIMessageW	proc :HWND, :UINT, :WPARAM, :LPARAM
    NotifyIME		proc :HIMC, :DWORD, :DWORD, :DWORD
    RegisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR
    RegisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR
    ReleaseContext	proc :HWND, :HIMC
    SetCandidateWindow	proc :HIMC, :ptr
    SetCompositionFontA proc :HIMC, :ptr
    SetCompositionFontW proc :HIMC, :ptr
    SetCompositionStringA proc :HIMC, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD
    SetCompositionStringW proc :HIMC, :DWORD, :LPVOID, :DWORD, :LPVOID, :DWORD
    SetCompositionWindow proc :HIMC, :ptr
    SetConversionStatus proc :HIMC, :DWORD, :DWORD
    SetOpenStatus	proc :HIMC, :BOOL
    SetStatusWindowPos	proc :HIMC, :ptr
    SimulateHotKey	proc :HWND, :DWORD
    UnregisterWordA	proc :HKL, :LPSTR, :DWORD, :LPSTR
    UnregisterWordW	proc :HKL, :LPWSTR, :DWORD, :LPWSTR
    Activate		proc :BOOL
    Deactivate		proc
    OnDefWindowProc	proc :HWND, :UINT, :WPARAM, :LPARAM, :ptr
    FilterClientWindows proc :ptr, :UINT
    GetCodePageA	proc :HKL, :ptr
    GetLangId		proc :HKL, :ptr
    AssociateContextEx	proc :HWND, :HIMC, :DWORD
    DisableIME		proc :DWORD
    GetImeMenuItemsA	proc :HIMC, :DWORD, :DWORD, :ptr, :ptr, :DWORD, :ptr
    GetImeMenuItemsW	proc :HIMC, :DWORD, :DWORD, :ptr, :ptr, :DWORD, :ptr
    EnumInputContext	proc :DWORD, :ptr
   .ends

endif

ifndef __ISegmentList_INTERFACE_DEFINED__
define __ISegmentList_INTERFACE_DEFINED__
DEFINE_IIDX(ISegmentList, "305104b9-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISegmentList : public IUnknown

    CreateIterator	proc :ptr
    GetType		proc :ptr
    IsEmpty		proc :ptr
   .ends

endif

ifndef __ISegmentListIterator_INTERFACE_DEFINED__
define __ISegmentListIterator_INTERFACE_DEFINED__
DEFINE_IIDX(ISegmentListIterator, "3050f5a2-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISegmentListIterator : public IUnknown

    Current		proc :ptr
    First		proc
    IsDone		proc
    Advance		proc
   .ends

endif

ifndef __IHTMLCaret_INTERFACE_DEFINED__
define __IHTMLCaret_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLCaret, "305106ca-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLCaret : public IUnknown

    MoveCaretToPointer	proc :ptr, :BOOL, :CARET_DIRECTION
    MoveCaretToPointerEx proc :ptr, :BOOL, :BOOL, :CARET_DIRECTION
    MoveMarkupPointerToCaret proc :ptr
    MoveDisplayPointerToCaret proc :ptr
    IsVisible		proc :ptr
    Show		proc :BOOL
    Hide		proc
    InsertText		proc :ptr, :LONG
    ScrollIntoView	proc
    GetLocation		proc :ptr, :BOOL
    GetCaretDirection	proc :ptr
    SetCaretDirection	proc :CARET_DIRECTION
   .ends

endif

ifndef __ISegment_INTERFACE_DEFINED__
define __ISegment_INTERFACE_DEFINED__
DEFINE_IIDX(ISegment, "30590072-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISegment : public IUnknown

    GetPointers		proc :ptr, :ptr
   .ends

endif

ifndef __IElementSegment_INTERFACE_DEFINED__
define __IElementSegment_INTERFACE_DEFINED__
DEFINE_IIDX(IElementSegment, "305106ce-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementSegment : public ISegment

    GetElement		proc :ptr
    SetPrimary		proc :BOOL
    IsPrimary		proc :ptr
   .ends

endif

ifndef __IHighlightSegment_INTERFACE_DEFINED__
define __IHighlightSegment_INTERFACE_DEFINED__
DEFINE_IIDX(IHighlightSegment, "30590073-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHighlightSegment : public ISegment

   .ends

endif

ifndef __IHighlightRenderingServices_INTERFACE_DEFINED__
define __IHighlightRenderingServices_INTERFACE_DEFINED__
DEFINE_IIDX(IHighlightRenderingServices, "30510761-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHighlightRenderingServices : public IUnknown

    AddSegment		proc :ptr, :ptr, :ptr, :ptr
    MoveSegmentToPointers proc :ptr, :ptr, :ptr
    RemoveSegment	proc :ptr
   .ends

endif

ifndef __ILineInfo_INTERFACE_DEFINED__
define __ILineInfo_INTERFACE_DEFINED__
DEFINE_IIDX(ILineInfo, "305900a7-98b5-11cf-bb82-00aa00bdce0b")

.comdef ILineInfo : public IUnknown

    get_x		proc :ptr
    get_baseLine	proc :ptr
    get_textDescent	proc :ptr
    get_textHeight	proc :ptr
    get_lineDirection	proc :ptr
   .ends

endif

ifndef __IDisplayPointer_INTERFACE_DEFINED__
define __IDisplayPointer_INTERFACE_DEFINED__
DEFINE_IIDX(IDisplayPointer, "305106d0-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDisplayPointer : public IUnknown

    MoveToPoint		proc :POINT, :COORD_SYSTEM, :ptr, :DWORD, :ptr
    MoveUnit		proc :DISPLAY_MOVEUNIT, :LONG
    PositionMarkupPointer proc :ptr
    MoveToPointer	proc :ptr
    SetPointerGravity	proc :POINTER_GRAVITY
    GetPointerGravity	proc :ptr
    SetDisplayGravity	proc :DISPLAY_GRAVITY
    GetDisplayGravity	proc :ptr
    IsPositioned	proc :ptr
    Unposition		proc
    IsEqualTo		proc :ptr, :ptr
    IsLeftOf		proc :ptr, :ptr
    IsRightOf		proc :ptr, :ptr
    IsAtBOL		proc :ptr
    MoveToMarkupPointer proc :ptr, :ptr
    ScrollIntoView	proc
    GetLineInfo		proc :ptr
    GetFlowElement	proc :ptr
    QueryBreaks		proc :ptr
   .ends

endif

ifndef __IDisplayServices_INTERFACE_DEFINED__
define __IDisplayServices_INTERFACE_DEFINED__
DEFINE_IIDX(IDisplayServices, "30590074-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDisplayServices : public IUnknown

    CreateDisplayPointer proc :ptr
    TransformRect	proc :ptr, :COORD_SYSTEM, :COORD_SYSTEM, :ptr
    TransformPoint	proc :ptr, :COORD_SYSTEM, :COORD_SYSTEM, :ptr
    GetCaret		proc :ptr
    GetComputedStyle	proc :ptr, :ptr
    ScrollRectIntoView	proc :ptr, :RECT
    HasFlowLayout	proc :ptr, :ptr
   .ends

endif

ifndef __IHtmlDlgSafeHelper_INTERFACE_DEFINED__
define __IHtmlDlgSafeHelper_INTERFACE_DEFINED__
DEFINE_IIDX(IHtmlDlgSafeHelper, "305106d2-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHtmlDlgSafeHelper : public IDispatch

    choosecolordlg	proc :VARIANT, :ptr
    getCharset		proc :BSTR, :ptr
    get_Fonts		proc :ptr
    get_BlockFormats	proc :ptr
   .ends

endif

ifndef __IBlockFormats_INTERFACE_DEFINED__
define __IBlockFormats_INTERFACE_DEFINED__
DEFINE_IIDX(IBlockFormats, "30590075-98b5-11cf-bb82-00aa00bdce0b")

.comdef IBlockFormats : public IDispatch

    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :ptr, :ptr
   .ends

endif

ifndef __IFontNames_INTERFACE_DEFINED__
define __IFontNames_INTERFACE_DEFINED__
DEFINE_IIDX(IFontNames, "305106d4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IFontNames : public IDispatch

    get__NewEnum	proc :ptr
    get_Count		proc :ptr
    Item		proc :ptr, :ptr
   .ends

endif

ifndef __ICSSFilter_INTERFACE_DEFINED__
define __ICSSFilter_INTERFACE_DEFINED__
DEFINE_IIDX(ICSSFilter, "30590076-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICSSFilter : public IUnknown

    SetSite		proc :ptr
    OnAmbientPropertyChange proc :LONG
   .ends

endif

ifndef __ISecureUrlHost_INTERFACE_DEFINED__
define __ISecureUrlHost_INTERFACE_DEFINED__
DEFINE_IIDX(ISecureUrlHost, "305106d6-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISecureUrlHost : public IUnknown

    ValidateSecureUrl	proc :ptr, :ptr, :DWORD
   .ends

endif

ifndef __IMarkupServices_INTERFACE_DEFINED__
define __IMarkupServices_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupServices, "30590077-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupServices : public IUnknown

    CreateMarkupPointer proc :ptr
    CreateMarkupContainer proc :ptr
    CreateElement	proc :ELEMENT_TAG_ID, :ptr, :ptr
    CloneElement	proc :ptr
    InsertElement	proc :ptr, :ptr, :ptr
    RemoveElement	proc :ptr
    Remove		proc :ptr, :ptr
    Copy		proc :ptr, :ptr, :ptr
    Move		proc :ptr, :ptr, :ptr
    InsertText		proc :ptr, :LONG, :ptr
    ParseString		proc :ptr, :DWORD, :ptr, :ptr, :ptr
    ParseGlobal		proc :HGLOBAL, :DWORD, :ptr, :ptr, :ptr
    IsScopedElement	proc :ptr, :ptr
    GetElementTagId	proc :ptr, :ptr
    GetTagIDForName	proc :BSTR, :ptr
    GetNameForTagID	proc :ELEMENT_TAG_ID, :ptr
    MovePointersToRange proc :ptr, :ptr, :ptr
    MoveRangeToPointers proc :ptr, :ptr, :ptr
    BeginUndoUnit	proc :ptr
    EndUndoUnit		proc
   .ends

endif

ifndef __IMarkupServices2_INTERFACE_DEFINED__
define __IMarkupServices2_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupServices2, "305106d8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupServices2 : public IMarkupServices

    ParseGlobalEx	proc :HGLOBAL, :DWORD, :ptr, :ptr, :ptr, :ptr
    ValidateElements	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    SaveSegmentsToClipboard proc :ptr, :DWORD
   .ends

endif

ifndef __IHTMLChangePlayback_INTERFACE_DEFINED__
define __IHTMLChangePlayback_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLChangePlayback, "30590078-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLChangePlayback : public IUnknown

    ExecChange		proc :ptr, :BOOL
   .ends

endif

ifndef __IMarkupPointer2_INTERFACE_DEFINED__
define __IMarkupPointer2_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupPointer2, "305106da-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupPointer2 : public IMarkupPointer

    IsAtWordBreak	proc :ptr
    GetMarkupPosition	proc :ptr
    MoveToMarkupPosition proc :ptr, :LONG
    MoveUnitBounded	proc :MOVEUNIT_ACTION, :ptr
    IsInsideURL		proc :ptr, :ptr
    MoveToContent	proc :ptr, :BOOL
   .ends

endif

ifndef __IMarkupTextFrags_INTERFACE_DEFINED__
define __IMarkupTextFrags_INTERFACE_DEFINED__
DEFINE_IIDX(IMarkupTextFrags, "30590079-98b5-11cf-bb82-00aa00bdce0b")

.comdef IMarkupTextFrags : public IUnknown

    GetTextFragCount	proc :ptr
    GetTextFrag		proc :LONG, :ptr, :ptr
    RemoveTextFrag	proc :LONG
    InsertTextFrag	proc :LONG, :BSTR, :ptr
    FindTextFragFromMarkupPointer proc :ptr, :ptr, :ptr
   .ends

endif

ifndef __IXMLGenericParse_INTERFACE_DEFINED__
define __IXMLGenericParse_INTERFACE_DEFINED__
DEFINE_IIDX(IXMLGenericParse, "30510763-98b5-11cf-bb82-00aa00bdce0b")

.comdef IXMLGenericParse : public IUnknown

    SetGenericParse	proc :VARIANT_BOOL
   .ends

endif

ifndef __IHTMLEditHost_INTERFACE_DEFINED__
define __IHTMLEditHost_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEditHost, "305900a8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEditHost : public IUnknown

    SnapRect		proc :ptr, :ptr, :ELEMENT_CORNER
   .ends

endif

ifndef __IHTMLEditHost2_INTERFACE_DEFINED__
define __IHTMLEditHost2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEditHost2, "305106cc-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEditHost2 : public IHTMLEditHost

    PreDrag		proc
   .ends

endif

ifndef __ISequenceNumber_INTERFACE_DEFINED__
define __ISequenceNumber_INTERFACE_DEFINED__
DEFINE_IIDX(ISequenceNumber, "30590071-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISequenceNumber : public IUnknown

    GetSequenceNumber	proc :LONG, :ptr
   .ends

endif

ifndef __IIMEServices_INTERFACE_DEFINED__
define __IIMEServices_INTERFACE_DEFINED__
DEFINE_IIDX(IIMEServices, "305106de-98b5-11cf-bb82-00aa00bdce0b")

.comdef IIMEServices : public IUnknown

    GetActiveIMM	proc :ptr
   .ends

endif

ifndef __ISelectionServicesListener_INTERFACE_DEFINED__
define __ISelectionServicesListener_INTERFACE_DEFINED__
DEFINE_IIDX(ISelectionServicesListener, "3059007c-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISelectionServicesListener : public IUnknown

    BeginSelectionUndo	proc
    EndSelectionUndo	proc
    OnSelectedElementExit proc :ptr, :ptr, :ptr, :ptr
    OnChangeType	proc :SELECTION_TYPE, :ptr
    GetTypeDetail	proc :ptr
   .ends

endif

ifndef __ISelectionServices_INTERFACE_DEFINED__
define __ISelectionServices_INTERFACE_DEFINED__
DEFINE_IIDX(ISelectionServices, "30510714-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISelectionServices : public IUnknown

    SetSelectionType	proc :SELECTION_TYPE, :ptr
    GetMarkupContainer	proc :ptr
    AddSegment		proc :ptr, :ptr, :ptr
    AddElementSegment	proc :ptr, :ptr
    RemoveSegment	proc :ptr
    GetSelectionServicesListener proc :ptr
   .ends

endif

ifndef __IHTMLEditDesigner_INTERFACE_DEFINED__
define __IHTMLEditDesigner_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEditDesigner, "30510716-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEditDesigner : public IUnknown

    PreHandleEvent	proc :DISPID, :ptr
    PostHandleEvent	proc :DISPID, :ptr
    TranslateAccelerator proc :DISPID, :ptr
    PostEditorEventNotify proc :DISPID, :ptr
   .ends

endif

ifndef __IHTMLEditServices_INTERFACE_DEFINED__
define __IHTMLEditServices_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEditServices, "30510718-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEditServices : public IUnknown

    AddDesigner		proc :ptr
    RemoveDesigner	proc :ptr
    GetSelectionServices proc :ptr, :ptr
    MoveToSelectionAnchor proc :ptr
    MoveToSelectionEnd	proc :ptr
    SelectRange		proc :ptr, :ptr, :SELECTION_TYPE
   .ends

endif

ifndef __IHTMLEditServices2_INTERFACE_DEFINED__
define __IHTMLEditServices2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLEditServices2, "3051071a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLEditServices2 : public IHTMLEditServices

    MoveToSelectionAnchorEx proc :ptr
    MoveToSelectionEndEx proc :ptr
    FreezeVirtualCaretPos proc :BOOL
    UnFreezeVirtualCaretPos proc :BOOL
   .ends

endif

ifndef __IHTMLComputedStyle_INTERFACE_DEFINED__
define __IHTMLComputedStyle_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLComputedStyle, "3051071c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLComputedStyle : public IUnknown

    get_bold		proc :ptr
    get_italic		proc :ptr
    get_underline	proc :ptr
    get_overline	proc :ptr
    get_strikeOut	proc :ptr
    get_subScript	proc :ptr
    get_superScript	proc :ptr
    get_explicitFace	proc :ptr
    get_fontWeight	proc :ptr
    get_fontSize	proc :ptr
    get_fontName	proc :ptr
    get_hasBgColor	proc :ptr
    get_textColor	proc :ptr
    get_backgroundColor proc :ptr
    get_preFormatted	proc :ptr
    get_direction	proc :ptr
    get_blockDirection	proc :ptr
    get_OL		proc :ptr
    IsEqual		proc :ptr, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_HtmlDlgSafeHelper, "3050f819-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_BlockFormats, "3050f831-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_FontNames, "3050f83a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IDeveloperConsoleMessageReceiver_INTERFACE_DEFINED__
define __IDeveloperConsoleMessageReceiver_INTERFACE_DEFINED__
DEFINE_IIDX(IDeveloperConsoleMessageReceiver, "305106e4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDeveloperConsoleMessageReceiver : public IUnknown

    Write		proc :LPCWSTR, :DEV_CONSOLE_MESSAGE_LEVEL, :SINT, :LPCWSTR
    WriteWithUrl	proc :LPCWSTR, :DEV_CONSOLE_MESSAGE_LEVEL, :SINT, :LPCWSTR, :LPCWSTR
    WriteWithUrlAndLine proc :LPCWSTR, :DEV_CONSOLE_MESSAGE_LEVEL, :SINT, :LPCWSTR, :LPCWSTR, :ULONG
    WriteWithUrlLineAndColumn proc :LPCWSTR, :DEV_CONSOLE_MESSAGE_LEVEL, :SINT, :LPCWSTR, :LPCWSTR, :ULONG, :ULONG
   .ends

endif

ifndef __IScriptEventHandler_INTERFACE_DEFINED__
define __IScriptEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IScriptEventHandler, "305106ff-98b5-11cf-bb82-00aa00bdce0b")

.comdef IScriptEventHandler : public IUnknown

    FunctionName	proc :ptr
    DebugDocumentContext proc :ptr
    EventHandlerDispatch proc :ptr
    UsesCapture		proc :ptr
    Cookie		proc :ptr
   .ends

endif

ifndef __IDebugCallbackNotificationHandler_INTERFACE_DEFINED__
define __IDebugCallbackNotificationHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDebugCallbackNotificationHandler, "3059008c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDebugCallbackNotificationHandler : public IUnknown

    RequestedCallbackTypes proc :ptr
    BeforeDispatchEvent proc :ptr
    DispatchEventComplete proc :ptr, :DWORD
    BeforeInvokeDomCallback proc :ptr, :ptr, :DOM_EVENT_PHASE, :DWORD
    InvokeDomCallbackComplete proc :ptr, :ptr, :DOM_EVENT_PHASE, :DWORD
    BeforeInvokeCallback proc :SCRIPT_TIMER_TYPE, :DWORD, :ptr, :ULONGLONG, :BSTR, :UINT32, :UINT32, :UINT32, :ptr
    InvokeCallbackComplete proc :SCRIPT_TIMER_TYPE, :DWORD, :ptr, :ULONGLONG, :BSTR, :UINT32, :UINT32, :UINT32, :ptr
   .ends

endif

ifndef __IScriptEventHandlerSourceInfo_INTERFACE_DEFINED__
define __IScriptEventHandlerSourceInfo_INTERFACE_DEFINED__
DEFINE_IIDX(IScriptEventHandlerSourceInfo, "3059008d-98b5-11cf-bb82-00aa00bdce0b")

.comdef IScriptEventHandlerSourceInfo : public IUnknown

    GetSourceInfo	proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IDOMEventRegistrationCallback_INTERFACE_DEFINED__
define __IDOMEventRegistrationCallback_INTERFACE_DEFINED__
DEFINE_IIDX(IDOMEventRegistrationCallback, "3059008e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IDOMEventRegistrationCallback : public IUnknown

    OnDOMEventListenerAdded proc :LPCWSTR, :ptr
    OnDOMEventListenerRemoved proc :ULONGLONG
   .ends

endif

ifndef __IEventTarget2_INTERFACE_DEFINED__
define __IEventTarget2_INTERFACE_DEFINED__
DEFINE_IIDX(IEventTarget2, "3059008f-98b5-11cf-bb82-00aa00bdce0b")

.comdef IEventTarget2 : public IUnknown

    GetRegisteredEventTypes proc :ptr
    GetListenersForType proc :LPCWSTR, :ptr
    RegisterForDOMEventListeners proc :ptr
    UnregisterForDOMEventListeners proc :ptr
   .ends

endif

ifndef __HTMLNamespaceEvents_DISPINTERFACE_DEFINED__
define __HTMLNamespaceEvents_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLNamespaceEvents, "3050f6bd-98b5-11cf-bb82-00aa00bdce0b")

.comdef HTMLNamespaceEvents : public IDispatch

   .ends

endif

ifndef __IHTMLNamespace_INTERFACE_DEFINED__
define __IHTMLNamespace_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLNamespace, "30590082-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLNamespace : public IDispatch

    get_name		proc :ptr
    get_urn		proc :ptr
    get_tagNames	proc :ptr
    get_readyState	proc :ptr
    put_onreadystatechange proc :VARIANT
    get_onreadystatechange proc :ptr
    doImport		proc :BSTR
    attachEvent		proc :BSTR, :ptr, :ptr
    detachEvent		proc :BSTR, :ptr
   .ends

endif

ifndef __IHTMLNamespaceCollection_INTERFACE_DEFINED__
define __IHTMLNamespaceCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLNamespaceCollection, "3059007b-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLNamespaceCollection : public IDispatch

    get_length		proc :ptr
    item		proc :VARIANT, :ptr
    _add		proc :BSTR, :BSTR, :VARIANT, :ptr
   .ends

endif

ifndef __DispHTMLNamespace_DISPINTERFACE_DEFINED__
define __DispHTMLNamespace_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLNamespace, "3050f54f-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLNamespace : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLNamespace, "3050f6bc-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispHTMLNamespaceCollection_DISPINTERFACE_DEFINED__
define __DispHTMLNamespaceCollection_DISPINTERFACE_DEFINED__
DEFINE_IIDX(HTMLNamespaceCollection, "3050f6b9-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLNamespaceCollection : public IDispatch

   .ends

endif

ifndef __IHTMLPainter_INTERFACE_DEFINED__
define __IHTMLPainter_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPainter, "3051071e-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPainter : public IUnknown

    Draw		proc :RECT, :RECT, :LONG, :HDC, :LPVOID
    OnResize		proc :tagSIZE
    GetPainterInfo	proc :ptr
    HitTestPoint	proc :POINT, :ptr, :ptr
   .ends

endif

ifndef __IHTMLPaintSite_INTERFACE_DEFINED__
define __IHTMLPaintSite_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPaintSite, "30590091-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPaintSite : public IUnknown

    InvalidatePainterInfo proc
    InvalidateRect	proc :ptr
    InvalidateRegion	proc :HRGN
    GetDrawInfo		proc :LONG, :ptr
    TransformGlobalToLocal proc :POINT, :ptr
    TransformLocalToGlobal proc :POINT, :ptr
    GetHitTestCookie	proc :ptr
   .ends

endif

ifndef __IHTMLPainterEventInfo_INTERFACE_DEFINED__
define __IHTMLPainterEventInfo_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPainterEventInfo, "30510720-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPainterEventInfo : public IUnknown

    GetEventInfoFlags	proc :ptr
    GetEventTarget	proc :ptr
    SetCursor		proc :LONG
    StringFromPartID	proc :LONG, :ptr
   .ends

endif

ifndef __IHTMLPainterOverlay_INTERFACE_DEFINED__
define __IHTMLPainterOverlay_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPainterOverlay, "30590092-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPainterOverlay : public IUnknown

    OnMove		proc :RECT
   .ends

endif

ifndef __IHTMLIPrintCollection_INTERFACE_DEFINED__
define __IHTMLIPrintCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLIPrintCollection, "30510765-98b6-11cf-bb82-00aa00bdce0b")

.comdef IHTMLIPrintCollection : public IDispatch

    get_length		proc :ptr
    get__newEnum	proc :ptr
    item		proc :LONG, :ptr
   .ends

endif

ifndef __IEnumPrivacyRecords_INTERFACE_DEFINED__
define __IEnumPrivacyRecords_INTERFACE_DEFINED__
DEFINE_IIDX(IEnumPrivacyRecords, "305900a9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IEnumPrivacyRecords : public IUnknown

    Reset		proc
    GetSize		proc :ptr
    GetPrivacyImpacted	proc :ptr
    Next		proc :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IWPCBlockedUrls_INTERFACE_DEFINED__
define __IWPCBlockedUrls_INTERFACE_DEFINED__
DEFINE_IIDX(IWPCBlockedUrls, "30510722-98b5-11cf-bb82-00aa00bdce0b")

.comdef IWPCBlockedUrls : public IUnknown

    GetCount		proc :ptr
    GetUrl		proc :DWORD, :ptr
   .ends

endif

ifndef __IHTMLDOMConstructorCollection_INTERFACE_DEFINED__
define __IHTMLDOMConstructorCollection_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDOMConstructorCollection, "30590093-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDOMConstructorCollection : public IDispatch

    get_Attr		proc :ptr
    get_BehaviorUrnsCollection proc :ptr
    get_BookmarkCollection proc :ptr
    get_CompatibleInfo	proc :ptr
    get_CompatibleInfoCollection proc :ptr
    get_ControlRangeCollection proc :ptr
    get_CSSCurrentStyleDeclaration proc :ptr
    get_CSSRuleList	proc :ptr
    get_CSSRuleStyleDeclaration proc :ptr
    get_CSSStyleDeclaration proc :ptr
    get_CSSStyleRule	proc :ptr
    get_CSSStyleSheet	proc :ptr
    get_DataTransfer	proc :ptr
    get_DOMImplementation proc :ptr
    get_Element		proc :ptr
    get_Event		proc :ptr
    get_History		proc :ptr
    get_HTCElementBehaviorDefaults proc :ptr
    get_HTMLAnchorElement proc :ptr
    get_HTMLAreaElement proc :ptr
    get_HTMLAreasCollection proc :ptr
    get_HTMLBaseElement proc :ptr
    get_HTMLBaseFontElement proc :ptr
    get_HTMLBGSoundElement proc :ptr
    get_HTMLBlockElement proc :ptr
    get_HTMLBodyElement proc :ptr
    get_HTMLBRElement	proc :ptr
    get_HTMLButtonElement proc :ptr
    get_HTMLCollection	proc :ptr
    get_HTMLCommentElement proc :ptr
    get_HTMLDDElement	proc :ptr
    get_HTMLDivElement	proc :ptr
    get_HTMLDocument	proc :ptr
    get_HTMLDListElement proc :ptr
    get_HTMLDTElement	proc :ptr
    get_HTMLEmbedElement proc :ptr
    get_HTMLFieldSetElement proc :ptr
    get_HTMLFontElement proc :ptr
    get_HTMLFormElement proc :ptr
    get_HTMLFrameElement proc :ptr
    get_HTMLFrameSetElement proc :ptr
    get_HTMLGenericElement proc :ptr
    get_HTMLHeadElement proc :ptr
    get_HTMLHeadingElement proc :ptr
    get_HTMLHRElement	proc :ptr
    get_HTMLHtmlElement proc :ptr
    get_HTMLIFrameElement proc :ptr
    get_HTMLImageElement proc :ptr
    get_HTMLInputElement proc :ptr
    get_HTMLIsIndexElement proc :ptr
    get_HTMLLabelElement proc :ptr
    get_HTMLLegendElement proc :ptr
    get_HTMLLIElement	proc :ptr
    get_HTMLLinkElement proc :ptr
    get_HTMLMapElement	proc :ptr
    get_HTMLMarqueeElement proc :ptr
    get_HTMLMetaElement proc :ptr
    get_HTMLModelessDialog proc :ptr
    get_HTMLNamespaceInfo proc :ptr
    get_HTMLNamespaceInfoCollection proc :ptr
    get_HTMLNextIdElement proc :ptr
    get_HTMLNoShowElement proc :ptr
    get_HTMLObjectElement proc :ptr
    get_HTMLOListElement proc :ptr
    get_HTMLOptionElement proc :ptr
    get_HTMLParagraphElement proc :ptr
    get_HTMLParamElement proc :ptr
    get_HTMLPhraseElement proc :ptr
    get_HTMLPluginsCollection proc :ptr
    get_HTMLPopup	proc :ptr
    get_HTMLScriptElement proc :ptr
    get_HTMLSelectElement proc :ptr
    get_HTMLSpanElement proc :ptr
    get_HTMLStyleElement proc :ptr
    get_HTMLTableCaptionElement proc :ptr
    get_HTMLTableCellElement proc :ptr
    get_HTMLTableColElement proc :ptr
    get_HTMLTableElement proc :ptr
    get_HTMLTableRowElement proc :ptr
    get_HTMLTableSectionElement proc :ptr
    get_HTMLTextAreaElement proc :ptr
    get_HTMLTextElement proc :ptr
    get_HTMLTitleElement proc :ptr
    get_HTMLUListElement proc :ptr
    get_HTMLUnknownElement proc :ptr
    get_Image		proc :ptr
    get_Location	proc :ptr
    get_NamedNodeMap	proc :ptr
    get_Navigator	proc :ptr
    get_NodeList	proc :ptr
    get_Option		proc :ptr
    get_Screen		proc :ptr
    get_Selection	proc :ptr
    get_StaticNodeList	proc :ptr
    get_Storage		proc :ptr
    get_StyleSheetList	proc :ptr
    get_StyleSheetPage	proc :ptr
    get_StyleSheetPageList proc :ptr
    get_Text		proc :ptr
    get_TextRange	proc :ptr
    get_TextRangeCollection proc :ptr
    get_TextRectangle	proc :ptr
    get_TextRectangleList proc :ptr
    get_Window		proc :ptr
    get_XDomainRequest	proc :ptr
    get_XMLHttpRequest	proc :ptr
   .ends

endif

ifndef __IHTMLDialog_INTERFACE_DEFINED__
define __IHTMLDialog_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDialog, "30510830-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDialog : public IDispatch

    put_dialogTop	proc :VARIANT
    get_dialogTop	proc :ptr
    put_dialogLeft	proc :VARIANT
    get_dialogLeft	proc :ptr
    put_dialogWidth	proc :VARIANT
    get_dialogWidth	proc :ptr
    put_dialogHeight	proc :VARIANT
    get_dialogHeight	proc :ptr
    get_dialogArguments proc :ptr
    get_menuArguments	proc :ptr
    put_returnValue	proc :VARIANT
    get_returnValue	proc :ptr
    close		proc
    toString		proc :ptr
   .ends

endif

ifndef __IHTMLDialog2_INTERFACE_DEFINED__
define __IHTMLDialog2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDialog2, "305900e7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDialog2 : public IDispatch

    put_status		proc :BSTR
    get_status		proc :ptr
    put_resizable	proc :BSTR
    get_resizable	proc :ptr
   .ends

endif

ifndef __IHTMLDialog3_INTERFACE_DEFINED__
define __IHTMLDialog3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLDialog3, "30510498-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLDialog3 : public IDispatch

    put_unadorned	proc :BSTR
    get_unadorned	proc :ptr
    put_dialogHide	proc :BSTR
    get_dialogHide	proc :ptr
   .ends

endif

ifndef __IHTMLModelessInit_INTERFACE_DEFINED__
define __IHTMLModelessInit_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLModelessInit, "3051040a-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLModelessInit : public IDispatch

    get_parameters	proc :ptr
    get_optionString	proc :ptr
    get_moniker		proc :ptr
    get_document	proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID__ThreadDialogProcParam, "3050f5eb-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID__HTMLDialog, "3050f28a-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLPopup_INTERFACE_DEFINED__
define __IHTMLPopup_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLPopup, "30510482-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLPopup : public IDispatch

    show		proc :LONG, :LONG, :LONG, :LONG, :ptr
    hide		proc
    get_document	proc :ptr
    get_isOpen		proc :ptr
   .ends

endif

ifndef __DispHTMLPopup_DISPINTERFACE_DEFINED__
define __DispHTMLPopup_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLPopup, "3050f589-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLPopup : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLPopup, "3050f667-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IHTMLAppBehavior_INTERFACE_DEFINED__
define __IHTMLAppBehavior_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAppBehavior, "3051040c-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAppBehavior : public IDispatch

    put_applicationName proc :BSTR
    get_applicationName proc :ptr
    put_version		proc :BSTR
    get_version		proc :ptr
    put_icon		proc :BSTR
    get_icon		proc :ptr
    put_singleInstance	proc :BSTR
    get_singleInstance	proc :ptr
    put_minimizeButton	proc :BSTR
    get_minimizeButton	proc :ptr
    put_maximizeButton	proc :BSTR
    get_maximizeButton	proc :ptr
    put_border		proc :BSTR
    get_border		proc :ptr
    put_borderStyle	proc :BSTR
    get_borderStyle	proc :ptr
    put_sysMenu		proc :BSTR
    get_sysMenu		proc :ptr
    put_caption		proc :BSTR
    get_caption		proc :ptr
    put_windowState	proc :BSTR
    get_windowState	proc :ptr
    put_showInTaskBar	proc :BSTR
    get_showInTaskBar	proc :ptr
    get_commandLine	proc :ptr
   .ends

endif

ifndef __IHTMLAppBehavior2_INTERFACE_DEFINED__
define __IHTMLAppBehavior2_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAppBehavior2, "3050f596-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAppBehavior2 : public IDispatch

    put_contextMenu	proc :BSTR
    get_contextMenu	proc :ptr
    put_innerBorder	proc :BSTR
    get_innerBorder	proc :ptr
    put_scroll		proc :BSTR
    get_scroll		proc :ptr
    put_scrollFlat	proc :BSTR
    get_scrollFlat	proc :ptr
    put_selection	proc :BSTR
    get_selection	proc :ptr
   .ends

endif

ifndef __IHTMLAppBehavior3_INTERFACE_DEFINED__
define __IHTMLAppBehavior3_INTERFACE_DEFINED__
DEFINE_IIDX(IHTMLAppBehavior3, "305104d3-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHTMLAppBehavior3 : public IDispatch

    put_navigable	proc :BSTR
    get_navigable	proc :ptr
   .ends

endif

ifndef __DispHTMLAppBehavior_DISPINTERFACE_DEFINED__
define __DispHTMLAppBehavior_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispHTMLAppBehavior, "3050f57c-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispHTMLAppBehavior : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLAppBehavior, "3050f5cb-98b5-11cf-bb82-00aa00bdce0b")
DEFINE_GUIDS(CLSID_OldHTMLDocument, "D48A6EC9-6A4A-11CF-94A7-444553540000")
DEFINE_GUIDS(CLSID_OldHTMLFormElement, "0D04D285-6BEC-11CF-8B97-00AA00476DA6")

ifndef __DispIHTMLInputButtonElement_DISPINTERFACE_DEFINED__
define __DispIHTMLInputButtonElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispIHTMLInputButtonElement, "3050f51e-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispIHTMLInputButtonElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLInputButtonElement, "3050f2b4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispIHTMLInputTextElement_DISPINTERFACE_DEFINED__
define __DispIHTMLInputTextElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispIHTMLInputTextElement, "3050f520-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispIHTMLInputTextElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLInputTextElement, "3050f2ab-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispIHTMLInputFileElement_DISPINTERFACE_DEFINED__
define __DispIHTMLInputFileElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispIHTMLInputFileElement, "3050f542-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispIHTMLInputFileElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLInputFileElement, "3050f2ae-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispIHTMLOptionButtonElement_DISPINTERFACE_DEFINED__
define __DispIHTMLOptionButtonElement_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispIHTMLOptionButtonElement, "3050f509-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispIHTMLOptionButtonElement : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLOptionButtonElement, "3050f2be-98b5-11cf-bb82-00aa00bdce0b")

ifndef __DispIHTMLInputImage_DISPINTERFACE_DEFINED__
define __DispIHTMLInputImage_DISPINTERFACE_DEFINED__
DEFINE_IIDX(DispIHTMLInputImage, "3050f51d-98b5-11cf-bb82-00aa00bdce0b")

.comdef DispIHTMLInputImage : public IDispatch

   .ends

endif

DEFINE_GUIDS(CLSID_HTMLInputImage, "3050f2c4-98b5-11cf-bb82-00aa00bdce0b")

ifndef __IElementNamespace_INTERFACE_DEFINED__
define __IElementNamespace_INTERFACE_DEFINED__
DEFINE_IIDX(IElementNamespace, "305104c5-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementNamespace : public IUnknown

    AddTag		proc :BSTR, :LONG
   .ends

endif

ifndef __IElementNamespaceTable_INTERFACE_DEFINED__
define __IElementNamespaceTable_INTERFACE_DEFINED__
DEFINE_IIDX(IElementNamespaceTable, "305104d7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementNamespaceTable : public IUnknown

    AddNamespace	proc :BSTR, :BSTR, :LONG, :ptr
   .ends

endif

ifndef __IElementNamespaceFactory_INTERFACE_DEFINED__
define __IElementNamespaceFactory_INTERFACE_DEFINED__
DEFINE_IIDX(IElementNamespaceFactory, "305104f6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementNamespaceFactory : public IUnknown

    Create		proc :ptr
   .ends

endif

ifndef __IElementNamespaceFactory2_INTERFACE_DEFINED__
define __IElementNamespaceFactory2_INTERFACE_DEFINED__
DEFINE_IIDX(IElementNamespaceFactory2, "305104c8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementNamespaceFactory2 : public IElementNamespaceFactory

    CreateWithImplementation proc :ptr, :BSTR
   .ends

endif

ifndef __IElementNamespaceFactoryCallback_INTERFACE_DEFINED__
define __IElementNamespaceFactoryCallback_INTERFACE_DEFINED__
DEFINE_IIDX(IElementNamespaceFactoryCallback, "305104d8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementNamespaceFactoryCallback : public IUnknown

    Resolve		proc :BSTR, :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IElementBehaviorSiteOM2_INTERFACE_DEFINED__
define __IElementBehaviorSiteOM2_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSiteOM2, "305104c7-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSiteOM2 : public IElementBehaviorSiteOM

    GetDefaults		proc :ptr
   .ends

endif

ifndef __IElementBehaviorCategory_INTERFACE_DEFINED__
define __IElementBehaviorCategory_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorCategory, "305104c6-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorCategory : public IUnknown

    GetCategory		proc :ptr
   .ends

endif

ifndef __IElementBehaviorSiteCategory_INTERFACE_DEFINED__
define __IElementBehaviorSiteCategory_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSiteCategory, "305104f9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSiteCategory : public IUnknown

    GetRelatedBehaviors proc :LONG, :LPOLESTR, :ptr
   .ends

endif

ifndef __IElementBehaviorSubmit_INTERFACE_DEFINED__
define __IElementBehaviorSubmit_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSubmit, "305104fb-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSubmit : public IUnknown

    GetSubmitInfo	proc :ptr
    Reset		proc
   .ends

endif

ifndef __IElementBehaviorFocus_INTERFACE_DEFINED__
define __IElementBehaviorFocus_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorFocus, "305104da-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorFocus : public IUnknown

    GetFocusRect	proc :ptr
   .ends

endif

ifndef __IElementBehaviorLayout_INTERFACE_DEFINED__
define __IElementBehaviorLayout_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorLayout, "305104db-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorLayout : public IUnknown

    GetSize		proc :LONG, :tagSIZE, :ptr, :ptr, :ptr
    GetLayoutInfo	proc :ptr
    GetPosition		proc :LONG, :ptr
    MapSize		proc :ptr, :ptr
   .ends

endif

ifndef __IElementBehaviorLayout2_INTERFACE_DEFINED__
define __IElementBehaviorLayout2_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorLayout2, "305104dc-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorLayout2 : public IUnknown

    GetTextDescent	proc :ptr
   .ends

endif

ifndef __IElementBehaviorSiteLayout_INTERFACE_DEFINED__
define __IElementBehaviorSiteLayout_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSiteLayout, "305104dd-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSiteLayout : public IUnknown

    InvalidateLayoutInfo proc
    InvalidateSize	proc
    GetMediaResolution	proc :ptr
   .ends

endif

ifndef __IElementBehaviorSiteLayout2_INTERFACE_DEFINED__
define __IElementBehaviorSiteLayout2_INTERFACE_DEFINED__
DEFINE_IIDX(IElementBehaviorSiteLayout2, "305104de-98b5-11cf-bb82-00aa00bdce0b")

.comdef IElementBehaviorSiteLayout2 : public IUnknown

    GetFontInfo		proc :ptr
   .ends

endif

ifndef __IHostBehaviorInit_INTERFACE_DEFINED__
define __IHostBehaviorInit_INTERFACE_DEFINED__
DEFINE_IIDX(IHostBehaviorInit, "305104df-98b5-11cf-bb82-00aa00bdce0b")

.comdef IHostBehaviorInit : public IUnknown

    PopulateNamespaceTable proc
   .ends

endif

ifndef __ISurfacePresenter_INTERFACE_DEFINED__
define __ISurfacePresenter_INTERFACE_DEFINED__
DEFINE_IIDX(ISurfacePresenter, "305104e0-98b5-11cf-bb82-00aa00bdce0b")

.comdef ISurfacePresenter : public IUnknown

    Present		proc :UINT, :ptr
    GetBuffer		proc :UINT, :REFIID, :ptr
    IsCurrent		proc :ptr
   .ends

endif

ifndef __IViewObjectPresentSite_INTERFACE_DEFINED__
define __IViewObjectPresentSite_INTERFACE_DEFINED__
DEFINE_IIDX(IViewObjectPresentSite, "305104e1-98b5-11cf-bb82-00aa00bdce0b")

.comdef IViewObjectPresentSite : public IUnknown

    CreateSurfacePresenter proc :ptr, :UINT, :UINT, :UINT, :DXGI_FORMAT, :VIEW_OBJECT_ALPHA_MODE, :ptr
    IsHardwareComposition proc :ptr
    SetCompositionMode	proc :VIEW_OBJECT_COMPOSITION_MODE
   .ends

endif

ifndef __ICanvasPixelArrayData_INTERFACE_DEFINED__
define __ICanvasPixelArrayData_INTERFACE_DEFINED__
DEFINE_IIDX(ICanvasPixelArrayData, "305104e3-98b5-11cf-bb82-00aa00bdce0b")

.comdef ICanvasPixelArrayData : public IUnknown

    GetBufferPointer	proc :ptr, :ptr
   .ends

endif

ifndef __IViewObjectPrint_INTERFACE_DEFINED__
define __IViewObjectPrint_INTERFACE_DEFINED__
DEFINE_IIDX(IViewObjectPrint, "305104d4-98b5-11cf-bb82-00aa00bdce0b")

.comdef IViewObjectPrint : public IUnknown

    GetPrintBitmap	proc :ptr
   .ends

endif

ifndef __IViewObjectPresentNotifySite_INTERFACE_DEFINED__
define __IViewObjectPresentNotifySite_INTERFACE_DEFINED__
DEFINE_IIDX(IViewObjectPresentNotifySite, "305104f8-98b5-11cf-bb82-00aa00bdce0b")

.comdef IViewObjectPresentNotifySite : public IViewObjectPresentSite

    RequestFrame	proc
   .ends

endif

ifndef __IViewObjectPresentNotify_INTERFACE_DEFINED__
define __IViewObjectPresentNotify_INTERFACE_DEFINED__
DEFINE_IIDX(IViewObjectPresentNotify, "305104c9-98b5-11cf-bb82-00aa00bdce0b")

.comdef IViewObjectPresentNotify : public IUnknown

    OnPreRender		proc
   .ends

endif

ifndef __ITrackingProtection_INTERFACE_DEFINED__
define __ITrackingProtection_INTERFACE_DEFINED__
DEFINE_IIDX(ITrackingProtection, "305104ca-98b5-11cf-bb82-00aa00bdce0b")

.comdef ITrackingProtection : public IUnknown

    EvaluateUrl		proc :BSTR, :ptr
    GetEnabled		proc :ptr
   .ends

endif

ifndef __IBFCacheable_INTERFACE_DEFINED__
define __IBFCacheable_INTERFACE_DEFINED__
DEFINE_IIDX(IBFCacheable, "305104cf-98b5-11cf-bb82-00aa00bdce0b")

.comdef IBFCacheable : public IUnknown

    EnterBFCache	proc
    ExitBFCache		proc
   .ends

endif

endif
endif
endif
