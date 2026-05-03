ifndef _RPC500_
include rpc500.inc
endif
ifndef __msinkaut_h__
define __msinkaut_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include tpcshrd.inc

ifndef _MSINKAUT_IDL_H_
define _MSINKAUT_IDL_H_

ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

include tpcerror.inc

.enum INK_METRIC_FLAGS {
	IMF_FONT_SELECTED_IN_HDC	= 0x1,
	IMF_ITALIC			= 0x2,
	IMF_BOLD			= 0x4
	}

.enum GET_DANDIDATE_FLAGS {
	TCF_ALLOW_RECOGNITION	= 0x1,
	TCF_FORCE_RECOGNITION	= 0x2
	}

INKMETRIC		struct
iHeight			sdword ?
iFontAscent		sdword ?
iFontDescent		sdword ?
dwFlags			DWORD ?
color			COLORREF ?
INKMETRIC		ends
PINKMETRIC		typedef ptr INKMETRIC

ifndef __MSINKAUTLib_LIBRARY_DEFINED__
define __MSINKAUTLib_LIBRARY_DEFINED__

define INK_SERIALIZED_FORMAT	<L"Ink Serialized Format">

.enum InkSelectionConstants {
	ISC_FirstElement,
	ISC_AllElements = -1
	}

define STR_GUID_X				<L"{598A6A8F-52C0-4BA0-93AF-AF357411A561}">
define STR_GUID_Y				<L"{B53F9F75-04E0-4498-A7EE-C30DBB5A9011}">
define STR_GUID_Z				<L"{735ADB30-0EBB-4788-A0E4-0F316490055D}">
define STR_GUID_PAKETSTATUS			<L"{6E0E07BF-AFE7-4CF7-87D1-AF6446208418}">
define STR_GUID_TIMERTICK			<L"{436510C5-FED3-45D1-8B76-71D3EA7A829D}">
define STR_GUID_SERIALNUMBER			<L"{78A81B56-0935-4493-BAAE-00541A8A16C4}">
define STR_GUID_NORMALPRESSURE			<L"{7307502D-F9F4-4E18-B3F2-2CE1B1A3610C}">
define STR_GUID_TANGENTPRESSURE			<L"{6DA4488B-5244-41EC-905B-32D89AB80809}">
define STR_GUID_BUTTONPRESSURE			<L"{8B7FEFC4-96AA-4BFE-AC26-8A5F0BE07BF5}">
define STR_GUID_XTILTORIENTATION		<L"{A8D07B3A-8BF0-40B0-95A9-B80A6BB787BF}">
define STR_GUID_YTILTORIENTATION		<L"{0E932389-1D77-43AF-AC00-5B950D6D4B2D}">
define STR_GUID_AZIMUTHORIENTATION		<L"{029123B4-8828-410B-B250-A0536595E5DC}">
define STR_GUID_ALTITUDEORIENTATION		<L"{82DEC5C7-F6BA-4906-894F-66D68DFC456C}">
define STR_GUID_TWISTORIENTATION		<L"{0D324960-13B2-41E4-ACE6-7AE9D43D2D3B}">
define STR_GUID_PITCHROTATION			<L"{7F7E57B7-BE37-4BE1-A356-7A84160E1893}">
define STR_GUID_ROLLROTATION			<L"{5D5D5E56-6BA9-4C5B-9FB0-851C91714E56}">
define STR_GUID_YAWROTATION			<L"{6A849980-7C3A-45B7-AA82-90A262950E89}">
define STR_GUID_WIDTH				<L"{BAABE94D-2712-48F5-BE9D-8F8B5EA0711A}">
define STR_GUID_HEIGHT				<L"{E61858D2-E447-4218-9D3F-18865C203DF4}">
define STR_GUID_FINGERCONTACTCONFIDENCE		<L"{E706C804-57F0-4F00-8A0C-853D57789BE9}">
define STR_GUID_DEVICE_CONTACT_ID		<L"{02585B91-049B-4750-9615-DF8948AB3C9C}">
define INKRECOGNITIONPROPERTY_LINENUMBER	<L"{DBF29F2C-5289-4BE8-B3D8-6EF63246253E}">
define INKRECOGNITIONPROPERTY_BOXNUMBER		<L"{2C243E3A-F733-4EB6-B1F8-B5DC5C2C4CDA}">
define INKRECOGNITIONPROPERTY_SEGMENTATION	<L"{B3C0FE6C-FB51-4164-BA2F-844AF8F983DA}">
define INKRECOGNITIONPROPERTY_HOTPOINT		<L"{CA6F40DC-5292-452a-91FB-2181C0BEC0DE}">
define INKRECOGNITIONPROPERTY_MAXIMUMSTROKECOUNT <L"{BF0EEC4E-4B7D-47a9-8CFA-234DD24BD22A}">
define INKRECOGNITIONPROPERTY_POINTSPERINCH	<L"{7ED16B76-889C-468e-8276-0021B770187E}">
define INKRECOGNITIONPROPERTY_CONFIDENCELEVEL	<L"{7DFE11A7-FB5D-4958-8765-154ADF0D833F}">
define INKRECOGNITIONPROPERTY_LINEMETRICS	<L"{8CC24B27-30A9-4b96-9056-2D3A90DA0727}">
define FACTOID_NONE				<L"NONE">
define FACTOID_DEFAULT				<L"DEFAULT">
define FACTOID_SYSTEMDICTIONARY			<L"SYSDICT">
define FACTOID_WORDLIST				<L"WORDLIST">
define FACTOID_EMAIL				<L"EMAIL">
define FACTOID_WEB				<L"WEB">
define FACTOID_ONECHAR				<L"ONECHAR">
define FACTOID_NUMBER				<L"NUMBER">
define FACTOID_DIGIT				<L"DIGIT">
define FACTOID_NUMBERSIMPLE			<L"NUMSIMPLE">
define FACTOID_CURRENCY				<L"CURRENCY">
define FACTOID_POSTALCODE			<L"POSTALCODE">
define FACTOID_PERCENT				<L"PERCENT">
define FACTOID_DATE				<L"DATE">
define FACTOID_TIME				<L"TIME">
define FACTOID_TELEPHONE			<L"TELEPHONE">
define FACTOID_FILENAME				<L"FILENAME">
define FACTOID_UPPERCHAR			<L"UPPERCHAR">
define FACTOID_LOWERCHAR			<L"LOWERCHAR">
define FACTOID_PUNCCHAR				<L"PUNCCHAR">
define FACTOID_JAPANESECOMMON			<L"JPN_COMMON">
define FACTOID_CHINESESIMPLECOMMON		<L"CHS_COMMON">
define FACTOID_CHINESETRADITIONALCOMMON		<L"CHT_COMMON">
define FACTOID_KOREANCOMMON			<L"KOR_COMMON">
define FACTOID_HIRAGANA				<L"HIRAGANA">
define FACTOID_KATAKANA				<L"KATAKANA">
define FACTOID_KANJICOMMON			<L"KANJI_COMMON">
define FACTOID_KANJIRARE			<L"KANJI_RARE">
define FACTOID_BOPOMOFO				<L"BOPOMOFO">
define FACTOID_JAMO				<L"JAMO">
define FACTOID_HANGULCOMMON			<L"HANGUL_COMMON">
define FACTOID_HANGULRARE			<L"HANGUL_RARE">

.enum InkBoundingBoxMode {
	IBBM_Default,
	IBBM_NoCurveFit,
	IBBM_CurveFit,
	IBBM_PointsOnly,
	IBBM_Union
	}

define IBBM_Last IBBM_Union + 1

.enum InkExtractFlags {
	IEF_CopyFromOriginal,
	IEF_RemoveFromOriginal,
	IEF_Default
	}

define IEF_All	(IEF_RemoveFromOriginal or IEF_CopyFromOriginal)

.enum InkPersistenceFormat {
	IPF_InkSerializedFormat,
	IPF_Base64InkSerializedFormat,
	IPF_GIF,
	IPF_Base64GIF
	}

define IPF_Last	    IPF_Base64GIF + 1

.enum InkPersistenceCompressionMode {
	IPCM_Default,
	IPCM_MaximumCompression,
	IPCM_NoCompression
	}

.enum InkPenTip {
	IPT_Ball,
	IPT_Rectangle
	}

define IPT_Last	    IPT_Rectangle + 1

.enum InkRasterOperation {
	IRO_Black	= 1,
	IRO_NotMergePen = 2,
	IRO_MaskNotPen	= 3,
	IRO_NotCopyPen	= 4,
	IRO_MaskPenNot	= 5,
	IRO_Not		= 6,
	IRO_XOrPen	= 7,
	IRO_NotMaskPen	= 8,
	IRO_MaskPen	= 9,
	IRO_NotXOrPen	= 10,
	IRO_NoOperation = 11,
	IRO_MergeNotPen = 12,
	IRO_CopyPen	= 13,
	IRO_MergePenNot = 14,
	IRO_MergePen	= 15,
	IRO_White	= 16
	}

define IRO_Last IRO_White+1

.enum InkMousePointer {
	IMP_Default	= 0,
	IMP_Arrow	= 1,
	IMP_Crosshair	= 2,
	IMP_Ibeam	= 3,
	IMP_SizeNESW	= 4,
	IMP_SizeNS	= 5,
	IMP_SizeNWSE	= 6,
	IMP_SizeWE	= 7,
	IMP_UpArrow	= 8,
	IMP_Hourglass	= 9,
	IMP_NoDrop	= 10,
	IMP_ArrowHourglass	= 11,
	IMP_ArrowQuestion	= 12,
	IMP_SizeAll	= 13,
	IMP_Hand	= 14,
	IMP_Custom	= 99
	}

.enum InkClipboardModes {
	ICB_Copy	= 0,
	ICB_Cut = 0x1,
	ICB_ExtractOnly = 0x30,
	ICB_DelayedCopy = 0x20,
	ICB_Default	= ICB_Copy
	}

define ICB_Last ICB_DelayedCopy+1

.enum InkClipboardFormats {
	ICF_None	= 0,
	ICF_InkSerializedFormat = 0x1,
	ICF_SketchInk	= 0x2,
	ICF_TextInk	= 0x6,
	ICF_EnhancedMetafile	= 0x8,
	ICF_Metafile	= 0x20,
	ICF_Bitmap	= 0x40,
	ICF_PasteMask	= 0x7,
	ICF_CopyMask	= 0x7f,
	ICF_Default	= ICF_CopyMask
	}

define ICF_Last ICF_CopyMask+1

.enum SelectionHitResult {
	SHR_None,
	SHR_NW,
	SHR_SE,
	SHR_NE,
	SHR_SW,
	SHR_E,
	SHR_W,
	SHR_N,
	SHR_S,
	SHR_Selection
	}

.enum InkRecognitionStatus {
	IRS_NoError		= 0,
	IRS_Interrupted		= 0x1,
	IRS_ProcessFailed	= 0x2,
	IRS_InkAddedFailed	= 0x4,
	IRS_SetAutoCompletionModeFailed = 0x8,
	IRS_SetStrokesFailed	= 0x10,
	IRS_SetGuideFailed	= 0x20,
	IRS_SetFlagsFailed	= 0x40,
	IRS_SetFactoidFailed	= 0x80,
	IRS_SetPrefixSuffixFailed	= 0x100,
	IRS_SetWordListFailed	= 0x200
	}

.enum DISPID_InkRectangle {
	DISPID_IRTop = 1,
	DISPID_IRLeft,
	DISPID_IRBottom,
	DISPID_IRRight,
	DISPID_IRGetRectangle,
	DISPID_IRSetRectangle,
	DISPID_IRData
	}

.enum DISPID_InkExtendedProperty {
	DISPID_IEPGuid	= 1,
	DISPID_IEPData
	}

.enum DISPID_InkExtendedProperties {
	DISPID_IEPs_NewEnum	= DISPID_NEWENUM,
	DISPID_IEPsItem		= DISPID_VALUE,
	DISPID_IEPsCount	= 1,
	DISPID_IEPsAdd,
	DISPID_IEPsRemove,
	DISPID_IEPsClear,
	DISPID_IEPsDoesPropertyExist
	}

.enum DISPID_InkDrawingAttributes {
	DISPID_DAHeight = 1,
	DISPID_DAColor,
	DISPID_DAWidth,
	DISPID_DAFitToCurve,
	DISPID_DAIgnorePressure,
	DISPID_DAAntiAliased,
	DISPID_DATransparency,
	DISPID_DARasterOperation,
	DISPID_DAPenTip,
	DISPID_DAClone,
	DISPID_DAExtendedProperties
	}

.enum DISPID_InkTransform {
	DISPID_ITReset	= 1,
	DISPID_ITTranslate,
	DISPID_ITRotate,
	DISPID_ITReflect,
	DISPID_ITShear,
	DISPID_ITScale,
	DISPID_ITeM11,
	DISPID_ITeM12,
	DISPID_ITeM21,
	DISPID_ITeM22,
	DISPID_ITeDx,
	DISPID_ITeDy,
	DISPID_ITGetTransform,
	DISPID_ITSetTransform,
	DISPID_ITData
	}

.enum InkApplicationGesture {
	IAG_AllGestures = 0,
	IAG_NoGesture	= 0xf000,
	IAG_Scratchout	= 0xf001,
	IAG_Triangle	= 0xf002,
	IAG_Square	= 0xf003,
	IAG_Star	= 0xf004,
	IAG_Check	= 0xf005,
	IAG_Curlicue	= 0xf010,
	IAG_DoubleCurlicue	= 0xf011,
	IAG_Circle	= 0xf020,
	IAG_DoubleCircle	= 0xf021,
	IAG_SemiCircleLeft	= 0xf028,
	IAG_SemiCircleRight	= 0xf029,
	IAG_ChevronUp	= 0xf030,
	IAG_ChevronDown = 0xf031,
	IAG_ChevronLeft = 0xf032,
	IAG_ChevronRight	= 0xf033,
	IAG_ArrowUp	= 0xf038,
	IAG_ArrowDown	= 0xf039,
	IAG_ArrowLeft	= 0xf03a,
	IAG_ArrowRight	= 0xf03b,
	IAG_Up		= 0xf058,
	IAG_Down	= 0xf059,
	IAG_Left	= 0xf05a,
	IAG_Right	= 0xf05b,
	IAG_UpDown	= 0xf060,
	IAG_DownUp	= 0xf061,
	IAG_LeftRight	= 0xf062,
	IAG_RightLeft	= 0xf063,
	IAG_UpLeftLong	= 0xf064,
	IAG_UpRightLong = 0xf065,
	IAG_DownLeftLong	= 0xf066,
	IAG_DownRightLong	= 0xf067,
	IAG_UpLeft	= 0xf068,
	IAG_UpRight	= 0xf069,
	IAG_DownLeft	= 0xf06a,
	IAG_DownRight	= 0xf06b,
	IAG_LeftUp	= 0xf06c,
	IAG_LeftDown	= 0xf06d,
	IAG_RightUp	= 0xf06e,
	IAG_RightDown	= 0xf06f,
	IAG_Exclamation = 0xf0a4,
	IAG_Tap		= 0xf0f0,
	IAG_DoubleTap	= 0xf0f1
	}

.enum InkSystemGesture {
	ISG_Tap = 0x10,
	ISG_DoubleTap	= 0x11,
	ISG_RightTap	= 0x12,
	ISG_Drag	= 0x13,
	ISG_RightDrag	= 0x14,
	ISG_HoldEnter	= 0x15,
	ISG_HoldLeave	= 0x16,
	ISG_HoverEnter	= 0x17,
	ISG_HoverLeave	= 0x18,
	ISG_Flick	= 0x1f
	}

define ISG_First ISG_Tap
define ISG_Last ISG_Flick

.enum InkRecognitionConfidence {
	IRC_Strong,
	IRC_Intermediate,
	IRC_Poor
	}

.enum DISPID_InkGesture {
	DISPID_IGId	= DISPID_VALUE,
	DISPID_IGGetHotPoint,
	DISPID_IGConfidence
	}

.enum DISPID_InkCursor {
	DISPID_ICsrName = DISPID_VALUE,
	DISPID_ICsrId	= 1,
	DISPID_ICsrDrawingAttributes,
	DISPID_ICsrButtons,
	DISPID_ICsrInverted,
	DISPID_ICsrTablet
	}

.enum DISPID_InkCursors {
	DISPID_ICs_NewEnum	= DISPID_NEWENUM,
	DISPID_ICsItem	= DISPID_VALUE,
	DISPID_ICsCount = 1
	}

.enum InkCursorButtonState {
	ICBS_Unavailable,
	ICBS_Up,
	ICBS_Down
	}

define ICBS_Last ICBS_Down
.enum DISPID_InkCursorButton {
	DISPID_ICBName	= DISPID_VALUE,
	DISPID_ICBId	= 1,
	DISPID_ICBState
	}

.enum DISPID_InkCursorButtons {
	DISPID_ICBs_NewEnum	= DISPID_NEWENUM,
	DISPID_ICBsItem		= DISPID_VALUE,
	DISPID_ICBsCount	= 1
	}

.enum TabletHardwareCapabilities {
	THWC_Integrated		= 0x1,
	THWC_CursorMustTouch	= 0x2,
	THWC_HardProximity	= 0x4,
	THWC_CursorsHavePhysicalIds	= 0x8
	}

.enum TabletPropertyMetricUnit {
	TPMU_Default,
	TPMU_Inches,
	TPMU_Centimeters,
	TPMU_Degrees,
	TPMU_Radians,
	TPMU_Seconds,
	TPMU_Pounds,
	TPMU_Grams
	}

.enum DISPID_InkTablet {
	DISPID_ITName			= DISPID_VALUE,
	DISPID_ITPlugAndPlayId		= 1,
	DISPID_ITPropertyMetrics,
	DISPID_ITIsPacketPropertySupported,
	DISPID_ITMaximumInputRectangle,
	DISPID_ITHardwareCapabilities
	}

.enum TabletDeviceKind {
	TDK_Mouse,
	TDK_Pen,
	TDK_Touch
	}

.enum DISPID_InkTablet2 {
	DISPID_IT2DeviceKind	= DISPID_VALUE
	}

.enum DISPID_InkTablet3 {
	DISPID_IT3IsMultiTouch	= DISPID_VALUE,
	DISPID_IT3MaximumCursors
	}

.enum DISPID_InkTablets {
	DISPID_ITs_NewEnum	= DISPID_NEWENUM,
	DISPID_ITsItem		= DISPID_VALUE,
	DISPID_ITsDefaultTablet = 1,
	DISPID_ITsCount,
	DISPID_ITsIsPacketPropertySupported
	}

.enum DISPID_InkStrokeDisp {
	DISPID_ISDInkIndex = 1,
	DISPID_ISDID,
	DISPID_ISDGetBoundingBox,
	DISPID_ISDDrawingAttributes,
	DISPID_ISDFindIntersections,
	DISPID_ISDGetRectangleIntersections,
	DISPID_ISDClip,
	DISPID_ISDHitTestCircle,
	DISPID_ISDNearestPoint,
	DISPID_ISDSplit,
	DISPID_ISDExtendedProperties,
	DISPID_ISDInk,
	DISPID_ISDBezierPoints,
	DISPID_ISDPolylineCusps,
	DISPID_ISDBezierCusps,
	DISPID_ISDSelfIntersections,
	DISPID_ISDPacketCount,
	DISPID_ISDPacketSize,
	DISPID_ISDPacketDescription,
	DISPID_ISDDeleted,
	DISPID_ISDGetPacketDescriptionPropertyMetrics,
	DISPID_ISDGetPoints,
	DISPID_ISDSetPoints,
	DISPID_ISDGetPacketData,
	DISPID_ISDGetPacketValuesByProperty,
	DISPID_ISDSetPacketValuesByProperty,
	DISPID_ISDGetFlattenedBezierPoints,
	DISPID_ISDScaleToRectangle,
	DISPID_ISDTransform,
	DISPID_ISDMove,
	DISPID_ISDRotate,
	DISPID_ISDShear,
	DISPID_ISDScale
	}

.enum DISPID_InkStrokes {
	DISPID_ISs_NewEnum	= DISPID_NEWENUM,
	DISPID_ISsItem		= DISPID_VALUE,
	DISPID_ISsCount		= 1,
	DISPID_ISsValid,
	DISPID_ISsInk,
	DISPID_ISsAdd,
	DISPID_ISsAddStrokes,
	DISPID_ISsRemove,
	DISPID_ISsRemoveStrokes,
	DISPID_ISsToString,
	DISPID_ISsModifyDrawingAttributes,
	DISPID_ISsGetBoundingBox,
	DISPID_ISsScaleToRectangle,
	DISPID_ISsTransform,
	DISPID_ISsMove,
	DISPID_ISsRotate,
	DISPID_ISsShear,
	DISPID_ISsScale,
	DISPID_ISsClip,
	DISPID_ISsRecognitionResult,
	DISPID_ISsRemoveRecognitionResult
	}

.enum DISPID_InkCustomStrokes {
	DISPID_ICSs_NewEnum	= DISPID_NEWENUM,
	DISPID_ICSsItem		= DISPID_VALUE,
	DISPID_ICSsCount	= 1,
	DISPID_ICSsAdd,
	DISPID_ICSsRemove,
	DISPID_ICSsClear
	}

.enum DISPID_StrokeEvent {
	DISPID_SEStrokesAdded = 1,
	DISPID_SEStrokesRemoved
	}

.enum DISPID_Ink {
	DISPID_IStrokes = 1,
	DISPID_IExtendedProperties,
	DISPID_IGetBoundingBox,
	DISPID_IDeleteStrokes,
	DISPID_IDeleteStroke,
	DISPID_IExtractStrokes,
	DISPID_IExtractWithRectangle,
	DISPID_IDirty,
	DISPID_ICustomStrokes,
	DISPID_IClone,
	DISPID_IHitTestCircle,
	DISPID_IHitTestWithRectangle,
	DISPID_IHitTestWithLasso,
	DISPID_INearestPoint,
	DISPID_ICreateStrokes,
	DISPID_ICreateStroke,
	DISPID_IAddStrokesAtRectangle,
	DISPID_IClip,
	DISPID_ISave,
	DISPID_ILoad,
	DISPID_ICreateStrokeFromPoints,
	DISPID_IClipboardCopyWithRectangle,
	DISPID_IClipboardCopy,
	DISPID_ICanPaste,
	DISPID_IClipboardPaste
	}

.enum DISPID_InkEvent {
	DISPID_IEInkAdded = 1,
	DISPID_IEInkDeleted
	}

.enum DISPID_InkRenderer {
	DISPID_IRGetViewTransform = 1,
	DISPID_IRSetViewTransform,
	DISPID_IRGetObjectTransform,
	DISPID_IRSetObjectTransform,
	DISPID_IRDraw,
	DISPID_IRDrawStroke,
	DISPID_IRPixelToInkSpace,
	DISPID_IRInkSpaceToPixel,
	DISPID_IRPixelToInkSpaceFromPoints,
	DISPID_IRInkSpaceToPixelFromPoints,
	DISPID_IRMeasure,
	DISPID_IRMeasureStroke,
	DISPID_IRMove,
	DISPID_IRRotate,
	DISPID_IRScale
	}

.enum InkCollectorEventInterest {
	ICEI_DefaultEvents	= -1,
	ICEI_CursorDown,
	ICEI_Stroke,
	ICEI_NewPackets,
	ICEI_NewInAirPackets,
	ICEI_CursorButtonDown,
	ICEI_CursorButtonUp,
	ICEI_CursorInRange,
	ICEI_CursorOutOfRange,
	ICEI_SystemGesture,
	ICEI_TabletAdded,
	ICEI_TabletRemoved,
	ICEI_MouseDown,
	ICEI_MouseMove,
	ICEI_MouseUp,
	ICEI_MouseWheel,
	ICEI_DblClick,
	ICEI_AllEvents
	}

.enum InkMouseButton {
	IMF_Left	= 1,
	IMF_Right	= 2,
	IMF_Middle	= 4
	}

.enum InkShiftKeyModifierFlags {
	IKM_Shift	= 0x1,
	IKM_Control	= 0x2,
	IKM_Alt		= 0x4
	}

.enum DISPID_InkCollectorEvent {
	DISPID_ICEStroke = 1,
	DISPID_ICECursorDown,
	DISPID_ICENewPackets,
	DISPID_ICENewInAirPackets,
	DISPID_ICECursorButtonDown,
	DISPID_ICECursorButtonUp,
	DISPID_ICECursorInRange,
	DISPID_ICECursorOutOfRange,
	DISPID_ICESystemGesture,
	DISPID_ICEGesture,
	DISPID_ICETabletAdded,
	DISPID_ICETabletRemoved,
	DISPID_IOEPainting,
	DISPID_IOEPainted,
	DISPID_IOESelectionChanging,
	DISPID_IOESelectionChanged,
	DISPID_IOESelectionMoving,
	DISPID_IOESelectionMoved,
	DISPID_IOESelectionResizing,
	DISPID_IOESelectionResized,
	DISPID_IOEStrokesDeleting,
	DISPID_IOEStrokesDeleted,
	DISPID_IPEChangeUICues,
	DISPID_IPEClick,
	DISPID_IPEDblClick,
	DISPID_IPEInvalidated,
	DISPID_IPEMouseDown,
	DISPID_IPEMouseEnter,
	DISPID_IPEMouseHover,
	DISPID_IPEMouseLeave,
	DISPID_IPEMouseMove,
	DISPID_IPEMouseUp,
	DISPID_IPEMouseWheel,
	DISPID_IPESizeModeChanged,
	DISPID_IPEStyleChanged,
	DISPID_IPESystemColorsChanged,
	DISPID_IPEKeyDown,
	DISPID_IPEKeyPress,
	DISPID_IPEKeyUp,
	DISPID_IPEResize,
	DISPID_IPESizeChanged
	}

.enum InkOverlayEditingMode {
	IOEM_Ink,
	IOEM_Delete,
	IOEM_Select
	}

define IOEM_Last IOEM_Select + 1
.enum InkOverlayAttachMode {
	IOAM_Behind,
	IOAM_InFront
	}

define IOAM_Last IOAM_InFront+1
.enum InkPictureSizeMode {
	IPSM_AutoSize,
	IPSM_CenterImage,
	IPSM_Normal,
	IPSM_StretchImage
	}

define IPSM_Last IPSM_StretchImage + 1
.enum InkOverlayEraserMode {
	IOERM_StrokeErase,
	IOERM_PointErase
	}

define IOERM_Last IOERM_PointErase + 1
.enum InkCollectionMode {
	ICM_InkOnly,
	ICM_GestureOnly,
	ICM_InkAndGesture
	}

define ICM_Last ICM_InkAndGesture
.enum DISPID_InkCollector {
	DISPID_ICEnabled = 1,
	DISPID_ICHwnd,
	DISPID_ICPaint,
	DISPID_ICText,
	DISPID_ICDefaultDrawingAttributes,
	DISPID_ICRenderer,
	DISPID_ICInk,
	DISPID_ICAutoRedraw,
	DISPID_ICCollectingInk,
	DISPID_ICSetEventInterest,
	DISPID_ICGetEventInterest,
	DISPID_IOEditingMode,
	DISPID_IOSelection,
	DISPID_IOAttachMode,
	DISPID_IOHitTestSelection,
	DISPID_IODraw,
	DISPID_IPPicture,
	DISPID_IPSizeMode,
	DISPID_IPBackColor,
	DISPID_ICCursors,
	DISPID_ICMarginX,
	DISPID_ICMarginY,
	DISPID_ICSetWindowInputRectangle,
	DISPID_ICGetWindowInputRectangle,
	DISPID_ICTablet,
	DISPID_ICSetAllTabletsMode,
	DISPID_ICSetSingleTabletIntegratedMode,
	DISPID_ICCollectionMode,
	DISPID_ICSetGestureStatus,
	DISPID_ICGetGestureStatus,
	DISPID_ICDynamicRendering,
	DISPID_ICDesiredPacketDescription,
	DISPID_IOEraserMode,
	DISPID_IOEraserWidth,
	DISPID_ICMouseIcon,
	DISPID_ICMousePointer,
	DISPID_IPInkEnabled,
	DISPID_ICSupportHighContrastInk,
	DISPID_IOSupportHighContrastSelectionUI
	}

.enum DISPID_InkRecognizer {
	DISPID_RecoClsid = 1,
	DISPID_RecoName,
	DISPID_RecoVendor,
	DISPID_RecoCapabilities,
	DISPID_RecoLanguageID,
	DISPID_RecoPreferredPacketDescription,
	DISPID_RecoCreateRecognizerContext,
	DISPID_RecoSupportedProperties
	}

.enum InkRecognizerCapabilities {
	IRC_DontCare		= 1,
	IRC_Object		= 2,
	IRC_FreeInput		= 4,
	IRC_LinedInput		= 8,
	IRC_BoxedInput		= 16,
	IRC_CharacterAutoCompletionInput	= 32,
	IRC_RightAndDown	= 64,
	IRC_LeftAndDown		= 128,
	IRC_DownAndLeft		= 256,
	IRC_DownAndRight	= 512,
	IRC_ArbitraryAngle	= 1024,
	IRC_Lattice		= 2048,
	IRC_AdviseInkChange	= 4096,
	IRC_StrokeReorder	= 8192,
	IRC_Personalizable	= 16384,
	IRC_PrefersArbitraryAngle	= 32768,
	IRC_PrefersParagraphBreaking	= 65536,
	IRC_PrefersSegmentation = 131072,
	IRC_Cursive		= 262144,
	IRC_TextPrediction	= 524288,
	IRC_Alpha		= 1048576,
	IRC_Beta		= 2097152
	}

.enum DISPID_InkRecognizer2 {
	DISPID_RecoId	= DISPID_VALUE,
	DISPID_RecoUnicodeRanges	= 1
	}

.enum DISPID_InkRecognizers {
	DISPID_IRecos_NewEnum	= DISPID_NEWENUM,
	DISPID_IRecosItem	= DISPID_VALUE,
	DISPID_IRecosCount	= 1,
	DISPID_IRecosGetDefaultRecognizer
	}

.enum InkRecognizerCharacterAutoCompletionMode {
	IRCACM_Full,
	IRCACM_Prefix,
	IRCACM_Random
	}

.enum InkRecognitionModes {
	IRM_None			= 0,
	IRM_WordModeOnly		= 0x1,
	IRM_Coerce			= 0x2,
	IRM_TopInkBreaksOnly		= 0x4,
	IRM_PrefixOk			= 0x8,
	IRM_LineMode			= 0x10,
	IRM_DisablePersonalization	= 0x20,
	IRM_AutoSpace			= 0x40,
	IRM_Max				= 0x80
	}

.enum DISPID_InkRecognitionEvent {
	DISPID_IRERecognitionWithAlternates	= 1,
	DISPID_IRERecognition
	}

.enum DISPID_InkRecoContext {
	DISPID_IRecoCtx_Strokes = 1,
	DISPID_IRecoCtx_CharacterAutoCompletionMode,
	DISPID_IRecoCtx_Factoid,
	DISPID_IRecoCtx_WordList,
	DISPID_IRecoCtx_Recognizer,
	DISPID_IRecoCtx_Guide,
	DISPID_IRecoCtx_Flags,
	DISPID_IRecoCtx_PrefixText,
	DISPID_IRecoCtx_SuffixText,
	DISPID_IRecoCtx_StopRecognition,
	DISPID_IRecoCtx_Clone,
	DISPID_IRecoCtx_Recognize,
	DISPID_IRecoCtx_StopBackgroundRecognition,
	DISPID_IRecoCtx_EndInkInput,
	DISPID_IRecoCtx_BackgroundRecognize,
	DISPID_IRecoCtx_BackgroundRecognizeWithAlternates,
	DISPID_IRecoCtx_IsStringSupported
	}

.enum DISPID_InkRecoContext2 {
	DISPID_IRecoCtx2_EnabledUnicodeRanges	= DISPID_VALUE
	}

.enum InkRecognitionAlternatesSelection {
	IRAS_Start	= 0,
	IRAS_DefaultCount	= 10,
	IRAS_All	= -1
	}

.enum DISPID_InkRecognitionResult {
	DISPID_InkRecognitionResult_TopString	= 1,
	DISPID_InkRecognitionResult_TopAlternate,
	DISPID_InkRecognitionResult_Strokes,
	DISPID_InkRecognitionResult_TopConfidence,
	DISPID_InkRecognitionResult_AlternatesFromSelection,
	DISPID_InkRecognitionResult_ModifyTopAlternate,
	DISPID_InkRecognitionResult_SetResultOnStrokes
	}

.enum DISPID_InkRecoAlternate {
	DISPID_InkRecoAlternate_String	= 1,
	DISPID_InkRecoAlternate_LineNumber,
	DISPID_InkRecoAlternate_Baseline,
	DISPID_InkRecoAlternate_Midline,
	DISPID_InkRecoAlternate_Ascender,
	DISPID_InkRecoAlternate_Descender,
	DISPID_InkRecoAlternate_Confidence,
	DISPID_InkRecoAlternate_Strokes,
	DISPID_InkRecoAlternate_GetStrokesFromStrokeRanges,
	DISPID_InkRecoAlternate_GetStrokesFromTextRange,
	DISPID_InkRecoAlternate_GetTextRangeFromStrokes,
	DISPID_InkRecoAlternate_GetPropertyValue,
	DISPID_InkRecoAlternate_LineAlternates,
	DISPID_InkRecoAlternate_ConfidenceAlternates,
	DISPID_InkRecoAlternate_AlternatesWithConstantPropertyValues
	}

.enum DISPID_InkRecognitionAlternates {
	DISPID_InkRecognitionAlternates_NewEnum = DISPID_NEWENUM,
	DISPID_InkRecognitionAlternates_Item	= DISPID_VALUE,
	DISPID_InkRecognitionAlternates_Count	= 1,
	DISPID_InkRecognitionAlternates_Strokes
	}

InkRecoGuide		struct
rectWritingBox		RECT <>
rectDrawnBox		RECT <>
cRows			sdword ?
cColumns		sdword ?
midline			sdword ?
InkRecoGuide		ends

.enum DISPID_InkRecognizerGuide {
	DISPID_IRGWritingBox = 1,
	DISPID_IRGDrawnBox,
	DISPID_IRGRows,
	DISPID_IRGColumns,
	DISPID_IRGMidline,
	DISPID_IRGGuideData
	}

.enum DISPID_InkWordList {
	DISPID_InkWordList_AddWord,
	DISPID_InkWordList_RemoveWord,
	DISPID_InkWordList_Merge
	}

.enum DISPID_InkWordList2 {
	DISPID_InkWordList2_AddWords	= ( DISPID_InkWordList_Merge + 1 )
	}

externdef LIBID_MSINKAUTLib:IID

ifndef __InkConstants_MODULE_DEFINED__
define __InkConstants_MODULE_DEFINED__
define InkMinTransparencyValue 0
define InkMaxTransparencyValue 255
endif

ifndef __InkCollectorConstants_MODULE_DEFINED__
define __InkCollectorConstants_MODULE_DEFINED__
define InkCollectorClipInkToMargin 0
define InkCollectorDefaultMargin ( -2147483647 - 1 )
endif

ifndef __IInkRectangle_INTERFACE_DEFINED__
define __IInkRectangle_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRectangle, "9794FF82-6071-4717-8A8B-6AC7C64A686E")

.comdef IInkRectangle : public IDispatch
    get_Top		proc :ptr
    put_Top		proc :LONG
    get_Left		proc :ptr
    put_Left		proc :LONG
    get_Bottom		proc :ptr
    put_Bottom		proc :LONG
    get_Right		proc :ptr
    put_Right		proc :LONG
    get_Data		proc :ptr
    put_Data		proc :RECT
    GetRectangle	proc :ptr, :ptr, :ptr, :ptr
    SetRectangle	proc :LONG, :LONG, :LONG, :LONG
   .ends

endif

ifndef __IInkExtendedProperty_INTERFACE_DEFINED__
define __IInkExtendedProperty_INTERFACE_DEFINED__

DEFINE_IIDX(IInkExtendedProperty, "DB489209-B7C3-411D-90F6-1548CFFF271E")

.comdef IInkExtendedProperty : public IDispatch
    get_Guid		proc :ptr
    get_Data		proc :ptr
    put_Data		proc :VARIANT
   .ends

endif

ifndef __IInkExtendedProperties_INTERFACE_DEFINED__
define __IInkExtendedProperties_INTERFACE_DEFINED__

DEFINE_IIDX(IInkExtendedProperties, "89F2A8BE-95A9-4530-8B8F-88E971E3E25F")

.comdef IInkExtendedProperties : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    Item		proc :VARIANT, :ptr ptr
    _Add		proc :BSTR, :VARIANT, :ptr ptr
    Remove		proc :VARIANT
    Clear		proc
    DoesPropertyExist	proc :BSTR, :ptr
   .ends

endif

ifndef __IInkDrawingAttributes_INTERFACE_DEFINED__
define __IInkDrawingAttributes_INTERFACE_DEFINED__

DEFINE_IIDX(IInkDrawingAttributes, "BF519B75-0A15-4623-ADC9-C00D436A8092")

.comdef IInkDrawingAttributes : public IDispatch
    get_Color		proc :ptr
    put_Color		proc :LONG
    get_Width		proc :ptr
    put_Width		proc :real4
    get_Height		proc :ptr
    put_Height		proc :real4
    get_FitToCurve	proc :ptr
    put_FitToCurve	proc :VARIANT_BOOL
    get_IgnorePressure	proc :ptr
    put_IgnorePressure	proc :VARIANT_BOOL
    get_AntiAliased	proc :ptr
    put_AntiAliased	proc :VARIANT_BOOL
    get_Transparency	proc :ptr
    put_Transparency	proc :LONG
    get_RasterOperation proc :ptr
    put_RasterOperation proc :InkRasterOperation
    get_PenTip		proc :ptr
    put_PenTip		proc :InkPenTip
    get_ExtendedProperties proc :ptr ptr
    Clone		proc :ptr ptr
   .ends

endif

ifndef __IInkTransform_INTERFACE_DEFINED__
define __IInkTransform_INTERFACE_DEFINED__

DEFINE_IIDX(IInkTransform, "615F1D43-8703-4565-88E2-8201D2ECD7B7")

.comdef IInkTransform : public IDispatch
    Reset		proc
    Translate		proc :real4, :real4
    Rotate		proc :real4, :real4, :real4
    Reflect		proc :VARIANT_BOOL, :VARIANT_BOOL
    Shear		proc :real4, :real4
    ScaleTransform	proc :real4, :real4
    GetTransform	proc :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
    SetTransform	proc :real4, :real4, :real4, :real4, :real4, :real4
    get_eM11		proc :ptr
    put_eM11		proc :real4
    get_eM12		proc :ptr
    put_eM12		proc :real4
    get_eM21		proc :ptr
    put_eM21		proc :real4
    get_eM22		proc :ptr
    put_eM22		proc :real4
    get_eDx		proc :ptr
    put_eDx		proc :real4
    get_eDy		proc :ptr
    put_eDy		proc :real4
    get_Data		proc :ptr
    put_Data		proc :XFORM
   .ends

endif

ifndef __IInkGesture_INTERFACE_DEFINED__
define __IInkGesture_INTERFACE_DEFINED__

DEFINE_IIDX(IInkGesture, "3BDC0A97-04E5-4e26-B813-18F052D41DEF")

.comdef IInkGesture : public IDispatch
    get_Confidence	proc :ptr
    get_Id		proc :ptr
    GetHotPoint		proc :ptr, :ptr
   .ends

endif

ifndef __IInkCursor_INTERFACE_DEFINED__
define __IInkCursor_INTERFACE_DEFINED__

DEFINE_IIDX(IInkCursor, "AD30C630-40C5-4350-8405-9C71012FC558")

.comdef IInkCursor : public IDispatch
    get_Name		proc :ptr
    get_Id		proc :ptr
    get_Inverted	proc :ptr
    get_DrawingAttributes proc :ptr ptr
    putref_DrawingAttributes proc :ptr
    get_Tablet		proc :ptr ptr
    get_Buttons		proc :ptr ptr
   .ends

endif

ifndef __IInkCursors_INTERFACE_DEFINED__
define __IInkCursors_INTERFACE_DEFINED__

DEFINE_IIDX(IInkCursors, "A248C1AC-C698-4e06-9E5C-D57F77C7E647")

.comdef IInkCursors : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    Item		proc :LONG, :ptr ptr
   .ends

endif

ifndef __IInkCursorButton_INTERFACE_DEFINED__
define __IInkCursorButton_INTERFACE_DEFINED__

DEFINE_IIDX(IInkCursorButton, "85EF9417-1D59-49b2-A13C-702C85430894")

.comdef IInkCursorButton : public IDispatch
    get_Name		proc :ptr
    get_Id		proc :ptr
    get_State		proc :ptr
   .ends

endif

ifndef __IInkCursorButtons_INTERFACE_DEFINED__
define __IInkCursorButtons_INTERFACE_DEFINED__

DEFINE_IIDX(IInkCursorButtons, "3671CC40-B624-4671-9FA0-DB119D952D54")

.comdef IInkCursorButtons : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    Item		proc :VARIANT, :ptr ptr
   .ends

endif

ifndef __IInkTablet_INTERFACE_DEFINED__
define __IInkTablet_INTERFACE_DEFINED__

DEFINE_IIDX(IInkTablet, "2DE25EAA-6EF8-42d5-AEE9-185BC81B912D")

.comdef IInkTablet : public IDispatch
    get_Name		proc :ptr
    get_PlugAndPlayId	proc :ptr
    get_MaximumInputRectangle proc :ptr ptr
    get_HardwareCapabilities proc :ptr
    IsPacketPropertySupported proc :BSTR, :ptr
    GetPropertyMetrics	proc :BSTR, :ptr, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IInkTablet2_INTERFACE_DEFINED__
define __IInkTablet2_INTERFACE_DEFINED__

DEFINE_IIDX(IInkTablet2, "90c91ad2-fa36-49d6-9516-ce8d570f6f85")

.comdef IInkTablet2 : public IDispatch
    get_DeviceKind	proc :ptr
   .ends

endif

ifndef __IInkTablet3_INTERFACE_DEFINED__
define __IInkTablet3_INTERFACE_DEFINED__

DEFINE_IIDX(IInkTablet3, "7e313997-1327-41dd-8ca9-79f24be17250")

.comdef IInkTablet3 : public IDispatch
    get_IsMultiTouch	proc :ptr
    get_MaximumCursors	proc :ptr
   .ends

endif

ifndef __IInkTablets_INTERFACE_DEFINED__
define __IInkTablets_INTERFACE_DEFINED__

DEFINE_IIDX(IInkTablets, "112086D9-7779-4535-A699-862B43AC1863")

.comdef IInkTablets : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    get_DefaultTablet	proc :ptr ptr
    Item		proc :LONG, :ptr ptr
    IsPacketPropertySupported proc :BSTR, :ptr
   .ends

endif

ifndef __IInkStrokeDisp_INTERFACE_DEFINED__
define __IInkStrokeDisp_INTERFACE_DEFINED__

DEFINE_IIDX(IInkStrokeDisp, "43242FEA-91D1-4a72-963E-FBB91829CFA2")

.comdef IInkStrokeDisp : public IDispatch
    get_ID		proc :ptr
    get_BezierPoints	proc :ptr
    get_DrawingAttributes proc :ptr ptr
    putref_DrawingAttributes proc :ptr
    get_Ink		proc :ptr ptr
    get_ExtendedProperties proc :ptr ptr
    get_PolylineCusps	proc :ptr
    get_BezierCusps	proc :ptr
    get_SelfIntersections proc :ptr
    get_PacketCount	proc :ptr
    get_PacketSize	proc :ptr
    get_PacketDescription proc :ptr
    get_Deleted		proc :ptr
    GetBoundingBox	proc :InkBoundingBoxMode, :ptr ptr
    FindIntersections	proc :ptr, :ptr
    GetRectangleIntersections proc :ptr, :ptr
    Clip		proc :ptr
    HitTestCircle	proc :LONG, :LONG, :real4, :ptr
    NearestPoint	proc :LONG, :LONG, :ptr, :ptr
    Split		proc :real4, :ptr ptr
    GetPacketDescriptionPropertyMetrics proc :BSTR, :ptr, :ptr, :ptr, :ptr
    GetPoints		proc :LONG, :LONG, :ptr
    SetPoints		proc :VARIANT, :LONG, :LONG, :ptr
    GetPacketData	proc :LONG, :LONG, :ptr
    GetPacketValuesByProperty proc :BSTR, :LONG, :LONG, :ptr
    SetPacketValuesByProperty proc :BSTR, :VARIANT, :LONG, :LONG, :ptr
    GetFlattenedBezierPoints proc :LONG, :ptr
    Transform		proc :ptr, :VARIANT_BOOL
    ScaleToRectangle	proc :ptr
    Move		proc :real4, :real4
    Rotate		proc :real4, :real4, :real4
    Shear		proc :real4, :real4
    ScaleTransform	proc :real4, :real4
   .ends

endif

ifndef __IInkStrokes_INTERFACE_DEFINED__
define __IInkStrokes_INTERFACE_DEFINED__

DEFINE_IIDX(IInkStrokes, "F1F4C9D8-590A-4963-B3AE-1935671BB6F3")

.comdef IInkStrokes : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    get_Ink		proc :ptr ptr
    get_RecognitionResult proc :ptr ptr
    ToString		proc :ptr
    Item		proc :LONG, :ptr ptr
    _Add		proc :ptr
    AddStrokes		proc :ptr
    Remove		proc :ptr
    RemoveStrokes	proc :ptr
    ModifyDrawingAttributes proc :ptr
    GetBoundingBox	proc :InkBoundingBoxMode, :ptr ptr
    Transform		proc :ptr, :VARIANT_BOOL
    ScaleToRectangle	proc :ptr
    Move		proc :real4, :real4
    Rotate		proc :real4, :real4, :real4
    Shear		proc :real4, :real4
    ScaleTransform	proc :real4, :real4
    Clip		proc :ptr
    RemoveRecognitionResult proc
   .ends

endif

ifndef __IInkCustomStrokes_INTERFACE_DEFINED__
define __IInkCustomStrokes_INTERFACE_DEFINED__

DEFINE_IIDX(IInkCustomStrokes, "7E23A88F-C30E-420f-9BDB-28902543F0C1")

.comdef IInkCustomStrokes : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    Item		proc :VARIANT, :ptr ptr
    _Add		proc :BSTR, :ptr
    Remove		proc :VARIANT
    Clear		proc
   .ends

endif

ifndef ___IInkStrokesEvents_DISPINTERFACE_DEFINED__
define ___IInkStrokesEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkStrokesEvents, "F33053EC-5D25-430a-928F-76A6491DDE15")

.comdef _IInkStrokesEvents : public IDispatch
   .ends

endif

ifndef __IInkDisp_INTERFACE_DEFINED__
define __IInkDisp_INTERFACE_DEFINED__

DEFINE_IIDX(IInkDisp, "9D398FA0-C4E2-4fcd-9973-975CAAF47EA6")

.comdef IInkDisp : public IDispatch
    get_Strokes		proc :ptr ptr
    get_ExtendedProperties proc :ptr ptr
    get_Dirty		proc :ptr
    put_Dirty		proc :VARIANT_BOOL
    get_CustomStrokes	proc :ptr ptr
    GetBoundingBox	proc :InkBoundingBoxMode, :ptr ptr
    DeleteStrokes	proc :ptr
    DeleteStroke	proc :ptr
    ExtractStrokes	proc :ptr, :InkExtractFlags, :ptr ptr
    ExtractWithRectangle proc :ptr, :InkExtractFlags, :ptr ptr
    Clip		proc :ptr
    Clone		proc :ptr ptr
    HitTestCircle	proc :LONG, :LONG, :real4, :ptr ptr
    HitTestWithRectangle proc :ptr, :real4, :ptr ptr
    HitTestWithLasso	proc :VARIANT, :real4, :ptr, :ptr ptr
    NearestPoint	proc :LONG, :LONG, :ptr, :ptr, :ptr ptr
    CreateStrokes	proc :VARIANT, :ptr ptr
    AddStrokesAtRectangle proc :ptr, :ptr
    Save		proc :InkPersistenceFormat, :InkPersistenceCompressionMode, :ptr
    Load		proc :VARIANT
    CreateStroke	proc :VARIANT, :VARIANT, :ptr ptr
    ClipboardCopyWithRectangle proc :ptr, :InkClipboardFormats, :InkClipboardModes, :ptr ptr
    ClipboardCopy	proc :ptr, :InkClipboardFormats, :InkClipboardModes, :ptr ptr
    CanPaste		proc :ptr, :ptr
    ClipboardPaste	proc :LONG, :LONG, :ptr, :ptr ptr
   .ends

endif

ifndef ___IInkEvents_DISPINTERFACE_DEFINED__
define ___IInkEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkEvents, "427B1865-CA3F-479a-83A9-0F420F2A0073")

.comdef _IInkEvents : public IDispatch
   .ends

endif

ifndef __IInkRenderer_INTERFACE_DEFINED__
define __IInkRenderer_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRenderer, "E6257A9C-B511-4f4c-A8B0-A7DBC9506B83")

.comdef IInkRenderer : public IDispatch
    GetViewTransform	proc :ptr
    SetViewTransform	proc :ptr
    GetObjectTransform	proc :ptr
    SetObjectTransform	proc :ptr
    Draw		proc :LONG_PTR, :ptr
    DrawStroke		proc :LONG_PTR, :ptr, :ptr
    PixelToInkSpace	proc :LONG_PTR, :ptr, :ptr
    InkSpaceToPixel	proc :LONG_PTR, :ptr, :ptr
    PixelToInkSpaceFromPoints proc :LONG_PTR, :ptr
    InkSpaceToPixelFromPoints proc :LONG_PTR, :ptr
    Measure		proc :ptr, :ptr ptr
    MeasureStroke	proc :ptr, :ptr, :ptr ptr
    Move		proc :real4, :real4
    Rotate		proc :real4, :real4, :real4
    ScaleTransform	proc :real4, :real4, :VARIANT_BOOL
   .ends

endif

ifndef __IInkCollector_INTERFACE_DEFINED__
define __IInkCollector_INTERFACE_DEFINED__

DEFINE_IIDX(IInkCollector, "F0F060B5-8B1F-4a7c-89EC-880692588A4F")

.comdef IInkCollector : public IDispatch
    get_hWnd		proc :ptr
    put_hWnd		proc :LONG_PTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_DefaultDrawingAttributes proc :ptr ptr
    putref_DefaultDrawingAttributes proc :ptr
    get_Renderer	proc :ptr ptr
    putref_Renderer	proc :ptr
    get_Ink		proc :ptr ptr
    putref_Ink		proc :ptr
    get_AutoRedraw	proc :ptr
    put_AutoRedraw	proc :VARIANT_BOOL
    get_CollectingInk	proc :ptr
    get_CollectionMode	proc :ptr
    put_CollectionMode	proc :InkCollectionMode
    get_DynamicRendering proc :ptr
    put_DynamicRendering proc :VARIANT_BOOL
    get_DesiredPacketDescription proc :ptr
    put_DesiredPacketDescription proc :VARIANT
    get_MouseIcon	proc :ptr ptr
    put_MouseIcon	proc :ptr
    putref_MouseIcon	proc :ptr
    get_MousePointer	proc :ptr
    put_MousePointer	proc :InkMousePointer
    get_Cursors		proc :ptr ptr
    get_MarginX		proc :ptr
    put_MarginX		proc :LONG
    get_MarginY		proc :ptr
    put_MarginY		proc :LONG
    get_Tablet		proc :ptr ptr
    get_SupportHighContrastInk proc :ptr
    put_SupportHighContrastInk proc :VARIANT_BOOL
    SetGestureStatus	proc :InkApplicationGesture, :VARIANT_BOOL
    GetGestureStatus	proc :InkApplicationGesture, :ptr
    GetWindowInputRectangle proc :ptr ptr
    SetWindowInputRectangle proc :ptr
    SetAllTabletsMode	proc :VARIANT_BOOL
    SetSingleTabletIntegratedMode proc :ptr
    GetEventInterest	proc :InkCollectorEventInterest, :ptr
    SetEventInterest	proc :InkCollectorEventInterest, :VARIANT_BOOL
   .ends

endif

ifndef ___IInkCollectorEvents_DISPINTERFACE_DEFINED__
define ___IInkCollectorEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkCollectorEvents, "11A583F2-712D-4fea-ABCF-AB4AF38EA06B")

.comdef _IInkCollectorEvents : public IDispatch
   .ends
endif

ifndef __IInkOverlay_INTERFACE_DEFINED__
define __IInkOverlay_INTERFACE_DEFINED__

DEFINE_IIDX(IInkOverlay, "b82a463b-c1c5-45a3-997c-deab5651b67a")

.comdef IInkOverlay : public IDispatch
    get_hWnd		proc :ptr
    put_hWnd		proc :LONG_PTR
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
    get_DefaultDrawingAttributes proc :ptr ptr
    putref_DefaultDrawingAttributes proc :ptr
    get_Renderer	proc :ptr ptr
    putref_Renderer	proc :ptr
    get_Ink		proc :ptr ptr
    putref_Ink		proc :ptr
    get_AutoRedraw	proc :ptr
    put_AutoRedraw	proc :VARIANT_BOOL
    get_CollectingInk	proc :ptr
    get_CollectionMode	proc :ptr
    put_CollectionMode	proc :InkCollectionMode
    get_DynamicRendering proc :ptr
    put_DynamicRendering proc :VARIANT_BOOL
    get_DesiredPacketDescription proc :ptr
    put_DesiredPacketDescription proc :VARIANT
    get_MouseIcon	proc :ptr ptr
    put_MouseIcon	proc :ptr
    putref_MouseIcon	proc :ptr
    get_MousePointer	proc :ptr
    put_MousePointer	proc :InkMousePointer
    get_EditingMode	proc :ptr
    put_EditingMode	proc :InkOverlayEditingMode
    get_Selection	proc :ptr ptr
    put_Selection	proc :ptr
    get_EraserMode	proc :ptr
    put_EraserMode	proc :InkOverlayEraserMode
    get_EraserWidth	proc :ptr
    put_EraserWidth	proc :LONG
    get_AttachMode	proc :ptr
    put_AttachMode	proc :InkOverlayAttachMode
    get_Cursors		proc :ptr ptr
    get_MarginX		proc :ptr
    put_MarginX		proc :LONG
    get_MarginY		proc :ptr
    put_MarginY		proc :LONG
    get_Tablet		proc :ptr ptr
    get_SupportHighContrastInk proc :ptr
    put_SupportHighContrastInk proc :VARIANT_BOOL
    get_SupportHighContrastSelectionUI proc :ptr
    put_SupportHighContrastSelectionUI proc :VARIANT_BOOL
    HitTestSelection	proc :LONG, :LONG, :ptr
    Draw		proc :ptr
    SetGestureStatus	proc :InkApplicationGesture, :VARIANT_BOOL
    GetGestureStatus	proc :InkApplicationGesture, :ptr
    GetWindowInputRectangle proc :ptr ptr
    SetWindowInputRectangle proc :ptr
    SetAllTabletsMode	proc :VARIANT_BOOL
    SetSingleTabletIntegratedMode proc :ptr
    GetEventInterest	proc :InkCollectorEventInterest, :ptr
    SetEventInterest	proc :InkCollectorEventInterest, :VARIANT_BOOL
   .ends

endif

ifndef ___IInkOverlayEvents_DISPINTERFACE_DEFINED__
define ___IInkOverlayEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkOverlayEvents, "31179b69-e563-489e-b16f-712f1e8a0651")

.comdef _IInkOverlayEvents : public IDispatch
   .ends

endif

ifndef __IInkPicture_INTERFACE_DEFINED__
define __IInkPicture_INTERFACE_DEFINED__

DEFINE_IIDX(IInkPicture, "e85662e0-379a-40d7-9b5c-757d233f9923")

.comdef IInkPicture : public IDispatch
    get_hWnd		proc :ptr
    get_DefaultDrawingAttributes proc :ptr ptr
    putref_DefaultDrawingAttributes proc :ptr
    get_Renderer	proc :ptr ptr
    putref_Renderer	proc :ptr
    get_Ink		proc :ptr ptr
    putref_Ink		proc :ptr
    get_AutoRedraw	proc :ptr
    put_AutoRedraw	proc :VARIANT_BOOL
    get_CollectingInk	proc :ptr
    get_CollectionMode	proc :ptr
    put_CollectionMode	proc :InkCollectionMode
    get_DynamicRendering proc :ptr
    put_DynamicRendering proc :VARIANT_BOOL
    get_DesiredPacketDescription proc :ptr
    put_DesiredPacketDescription proc :VARIANT
    get_MouseIcon	proc :ptr ptr
    put_MouseIcon	proc :ptr
    putref_MouseIcon	proc :ptr
    get_MousePointer	proc :ptr
    put_MousePointer	proc :InkMousePointer
    get_EditingMode	proc :ptr
    put_EditingMode	proc :InkOverlayEditingMode
    get_Selection	proc :ptr ptr
    put_Selection	proc :ptr
    get_EraserMode	proc :ptr
    put_EraserMode	proc :InkOverlayEraserMode
    get_EraserWidth	proc :ptr
    put_EraserWidth	proc :LONG
    putref_Picture	proc :ptr
    put_Picture		proc :ptr
    get_Picture		proc :ptr ptr
    put_SizeMode	proc :InkPictureSizeMode
    get_SizeMode	proc :ptr
    put_BackColor	proc :OLE_COLOR
    get_BackColor	proc :ptr
    get_Cursors		proc :ptr ptr
    get_MarginX		proc :ptr
    put_MarginX		proc :LONG
    get_MarginY		proc :ptr
    put_MarginY		proc :LONG
    get_Tablet		proc :ptr ptr
    get_SupportHighContrastInk proc :ptr
    put_SupportHighContrastInk proc :VARIANT_BOOL
    get_SupportHighContrastSelectionUI proc :ptr
    put_SupportHighContrastSelectionUI proc :VARIANT_BOOL
    HitTestSelection	proc :LONG, :LONG, :ptr
    SetGestureStatus	proc :InkApplicationGesture, :VARIANT_BOOL
    GetGestureStatus	proc :InkApplicationGesture, :ptr
    GetWindowInputRectangle proc :ptr ptr
    SetWindowInputRectangle proc :ptr
    SetAllTabletsMode	proc :VARIANT_BOOL
    SetSingleTabletIntegratedMode proc :ptr
    GetEventInterest	proc :InkCollectorEventInterest, :ptr
    SetEventInterest	proc :InkCollectorEventInterest, :VARIANT_BOOL
    get_InkEnabled	proc :ptr
    put_InkEnabled	proc :VARIANT_BOOL
    get_Enabled		proc :ptr
    put_Enabled		proc :VARIANT_BOOL
   .ends

endif

ifndef ___IInkPictureEvents_DISPINTERFACE_DEFINED__
define ___IInkPictureEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkPictureEvents, "60ff4fee-22ff-4484-acc1-d308d9cd7ea3")

.comdef _IInkPictureEvents : public IDispatch
   .ends

endif

ifndef __IInkRecognizer_INTERFACE_DEFINED__
define __IInkRecognizer_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognizer, "782BF7CF-034B-4396-8A32-3A1833CF6B56")

.comdef IInkRecognizer : public IDispatch
    get_Name		proc :ptr
    get_Vendor		proc :ptr
    get_Capabilities	proc :ptr
    get_Languages	proc :ptr
    get_SupportedProperties proc :ptr
    get_PreferredPacketDescription proc :ptr
    CreateRecognizerContext proc :ptr ptr
   .ends

endif

ifndef __IInkRecognizer2_INTERFACE_DEFINED__
define __IInkRecognizer2_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognizer2, "6110118A-3A75-4ad6-B2AA-04B2B72BBE65")

.comdef IInkRecognizer2 : public IDispatch
    get_Id		proc :ptr
    get_UnicodeRanges	proc :ptr
   .ends

endif

ifndef __IInkRecognizers_INTERFACE_DEFINED__
define __IInkRecognizers_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognizers, "9CCC4F12-B0B7-4a8b-BF58-4AECA4E8CEFD")

.comdef IInkRecognizers : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    GetDefaultRecognizer proc :LONG, :ptr ptr
    Item		proc :LONG, :ptr ptr
   .ends

endif

ifndef ___IInkRecognitionEvents_DISPINTERFACE_DEFINED__
define ___IInkRecognitionEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IInkRecognitionEvents, "17BCE92F-2E21-47FD-9D33-3C6AFBFD8C59")

.comdef _IInkRecognitionEvents : public IDispatch
   .ends
endif

ifndef __IInkRecognizerContext_INTERFACE_DEFINED__
define __IInkRecognizerContext_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognizerContext, "C68F52F9-32A3-4625-906C-44FC23B40958")

.comdef IInkRecognizerContext : public IDispatch
    get_Strokes		proc :ptr ptr
    putref_Strokes	proc :ptr
    get_CharacterAutoCompletionMode proc :ptr
    put_CharacterAutoCompletionMode proc :InkRecognizerCharacterAutoCompletionMode
    get_Factoid		proc :ptr
    put_Factoid		proc :BSTR
    get_Guide		proc :ptr ptr
    putref_Guide	proc :ptr
    get_PrefixText	proc :ptr
    put_PrefixText	proc :BSTR
    get_SuffixText	proc :ptr
    put_SuffixText	proc :BSTR
    get_RecognitionFlags proc :ptr
    put_RecognitionFlags proc :InkRecognitionModes
    get_WordList	proc :ptr ptr
    putref_WordList	proc :ptr
    get_Recognizer	proc :ptr ptr
    Recognize		proc :ptr, :ptr ptr
    StopBackgroundRecognition proc
    EndInkInput		proc
    BackgroundRecognize proc :VARIANT
    BackgroundRecognizeWithAlternates proc :VARIANT
    Clone		proc :ptr ptr
    IsStringSupported	proc :BSTR, :ptr
   .ends

endif

ifndef __IInkRecognizerContext2_INTERFACE_DEFINED__
define __IInkRecognizerContext2_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognizerContext2, "D6F0E32F-73D8-408e-8E9F-5FEA592C363F")

.comdef IInkRecognizerContext2 : public IDispatch
    get_EnabledUnicodeRanges proc :ptr
    put_EnabledUnicodeRanges proc :VARIANT
   .ends

endif

ifndef __IInkRecognitionResult_INTERFACE_DEFINED__
define __IInkRecognitionResult_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognitionResult, "3BC129A8-86CD-45ad-BDE8-E0D32D61C16D")

.comdef IInkRecognitionResult : public IDispatch
    get_TopString	proc :ptr
    get_TopAlternate	proc :ptr ptr
    get_TopConfidence	proc :ptr
    get_Strokes		proc :ptr ptr
    AlternatesFromSelection proc :LONG, :LONG, :LONG, :ptr ptr
    ModifyTopAlternate	proc :ptr
    SetResultOnStrokes	proc
   .ends

endif

ifndef __IInkRecognitionAlternate_INTERFACE_DEFINED__
define __IInkRecognitionAlternate_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognitionAlternate, "B7E660AD-77E4-429b-ADDA-873780D1FC4A")

.comdef IInkRecognitionAlternate : public IDispatch
    get_String		proc :ptr
    get_Confidence	proc :ptr
    get_Baseline	proc :ptr
    get_Midline		proc :ptr
    get_Ascender	proc :ptr
    get_Descender	proc :ptr
    get_LineNumber	proc :ptr
    get_Strokes		proc :ptr ptr
    get_LineAlternates	proc :ptr ptr
    get_ConfidenceAlternates proc :ptr ptr
    GetStrokesFromStrokeRanges proc :ptr, :ptr ptr
    GetStrokesFromTextRange proc :ptr, :ptr, :ptr ptr
    GetTextRangeFromStrokes proc :ptr, :ptr, :ptr
    AlternatesWithConstantPropertyValues proc :BSTR, :ptr ptr
    GetPropertyValue	proc :BSTR, :ptr
   .ends

endif

ifndef __IInkRecognitionAlternates_INTERFACE_DEFINED__
define __IInkRecognitionAlternates_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognitionAlternates, "286A167F-9F19-4c61-9D53-4F07BE622B84")

.comdef IInkRecognitionAlternates : public IDispatch
    get_Count		proc :ptr
    get__NewEnum	proc :ptr ptr
    get_Strokes		proc :ptr ptr
    Item		proc :LONG, :ptr ptr
   .ends

endif

ifndef __IInkRecognizerGuide_INTERFACE_DEFINED__
define __IInkRecognizerGuide_INTERFACE_DEFINED__

DEFINE_IIDX(IInkRecognizerGuide, "D934BE07-7B84-4208-9136-83C20994E905")

.comdef IInkRecognizerGuide : public IDispatch
    get_WritingBox	proc :ptr ptr
    put_WritingBox	proc :ptr
    get_DrawnBox	proc :ptr ptr
    put_DrawnBox	proc :ptr
    get_Rows		proc :ptr
    put_Rows		proc :LONG
    get_Columns		proc :ptr
    put_Columns		proc :LONG
    get_Midline		proc :ptr
    put_Midline		proc :LONG
    get_GuideData	proc :ptr
    put_GuideData	proc :InkRecoGuide
   .ends

endif

ifndef __IInkWordList_INTERFACE_DEFINED__
define __IInkWordList_INTERFACE_DEFINED__

DEFINE_IIDX(IInkWordList, "76BA3491-CB2F-406b-9961-0E0C4CDAAEF2")

.comdef IInkWordList : public IDispatch
    AddWord		proc :BSTR
    RemoveWord		proc :BSTR
    Merge		proc :ptr
   .ends

endif

ifndef __IInkWordList2_INTERFACE_DEFINED__
define __IInkWordList2_INTERFACE_DEFINED__

DEFINE_IIDX(IInkWordList2, "14542586-11BF-4f5f-B6E7-49D0744AAB6E")

.comdef IInkWordList2 : public IDispatch
    AddWords		proc :BSTR
   .ends

endif

DEFINE_GUIDS(CLSID_InkDisp, "937C1A34-151D-4610-9CA6-A8CC9BDB5D83")
DEFINE_GUIDS(CLSID_InkOverlay, "65d00646-cde3-4a88-9163-6769f0f1a97d")
DEFINE_GUIDS(CLSID_InkPicture, "04a1e553-fe36-4fde-865e-344194e69424")
DEFINE_GUIDS(CLSID_InkCollector, "43FB1553-AD74-4ee8-88E4-3E6DAAC915DB")
DEFINE_GUIDS(CLSID_InkDrawingAttributes, "D8BF32A2-05A5-44c3-B3AA-5E80AC7D2576")
DEFINE_GUIDS(CLSID_InkRectangle, "43B07326-AAE0-4B62-A83D-5FD768B7353C")
DEFINE_GUIDS(CLSID_InkRenderer, "9C1CC6E4-D7EB-4eeb-9091-15A7C8791ED9")
DEFINE_GUIDS(CLSID_InkTransform, "E3D5D93C-1663-4A78-A1A7-22375DFEBAEE")
DEFINE_GUIDS(CLSID_InkRecognizers, "9FD4E808-F6E6-4e65-98D3-AA39054C1255")
DEFINE_GUIDS(CLSID_InkRecognizerContext, "AAC46A37-9229-4fc0-8CCE-4497569BF4D1")
DEFINE_GUIDS(CLSID_InkRecognizerGuide, "8770D941-A63A-4671-A375-2855A18EBA73")
DEFINE_GUIDS(CLSID_InkTablets, "6E4FCB12-510A-4d40-9304-1DA10AE9147C")
DEFINE_GUIDS(CLSID_InkWordList, "9DE85094-F71F-44f1-8471-15A2FA76FCF3")
DEFINE_GUIDS(CLSID_InkStrokes, "48F491BC-240E-4860-B079-A1E94D3D2C86")

ifndef __IInk_INTERFACE_DEFINED__
define __IInk_INTERFACE_DEFINED__

DEFINE_IIDX(IInk, "03F8E511-43A1-11D3-8BB6-0080C7D6BAD5")

.comdef IInk : public IDispatch
   .ends

endif

ifndef __IInkLineInfo_INTERFACE_DEFINED__
define __IInkLineInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IInkLineInfo, "9C1C5AD6-F22F-4DE4-B453-A2CC482E7C33")

.comdef IInkLineInfo : public IUnknown
    SetFormat		proc :ptr
    GetFormat		proc :ptr
    GetInkExtent	proc :ptr, :ptr
    GetCandidate	proc :UINT, :LPWSTR, :ptr, :DWORD
    SetCandidate	proc :UINT, :LPWSTR
    Recognize		proc
   .ends

endif

ifndef __ISketchInk_INTERFACE_DEFINED__
define __ISketchInk_INTERFACE_DEFINED__

DEFINE_IIDX(ISketchInk, "B4563688-98EB-4646-B279-44DA14D45748")

.comdef ISketchInk : public IDispatch
   .ends

endif

DEFINE_GUIDS(CLSID_Ink, "13DE4A42-8D21-4C8E-BF9C-8F69CB068FCA")
DEFINE_GUIDS(CLSID_SketchInk, "F0291081-E87C-4E07-97DA-A0A03761E586")

endif

endif

endif

endif
