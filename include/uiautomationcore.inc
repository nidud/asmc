ifndef _RPC500_
include rpc500.inc
endif
ifndef __uiautomationcore_h__
define __uiautomationcore_h__

.pragma comment(lib, UIAutomationCore)

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif

.enum NavigateDirection {
    NavigateDirection_Parent,
    NavigateDirection_NextSibling,
    NavigateDirection_PreviousSibling,
    NavigateDirection_FirstChild,
    NavigateDirection_LastChild
    }

.enum ProviderOptions {
    ProviderOptions_ClientSideProvider		= 0x1,
    ProviderOptions_ServerSideProvider		= 0x2,
    ProviderOptions_NonClientAreaProvider	= 0x4,
    ProviderOptions_OverrideProvider		= 0x8,
    ProviderOptions_ProviderOwnsSetFocus	= 0x10,
    ProviderOptions_UseComThreading		= 0x20,
    ProviderOptions_RefuseNonClientSupport	= 0x40,
    ProviderOptions_HasNativeIAccessible	= 0x80,
    ProviderOptions_UseClientCoordinates	= 0x100
    }

.enum StructureChangeType {
    StructureChangeType_ChildAdded,
    StructureChangeType_ChildRemoved,
    StructureChangeType_ChildrenInvalidated,
    StructureChangeType_ChildrenBulkAdded,
    StructureChangeType_ChildrenBulkRemoved,
    StructureChangeType_ChildrenReordered
    }

.enum TextEditChangeType {
    TextEditChangeType_None,
    TextEditChangeType_AutoCorrect,
    TextEditChangeType_Composition,
    TextEditChangeType_CompositionFinalized
    }

.enum OrientationType {
    OrientationType_None,
    OrientationType_Horizontal,
    OrientationType_Vertical
    }

.enum DockPosition {
    DockPosition_Top,
    DockPosition_Left,
    DockPosition_Bottom,
    DockPosition_Right,
    DockPosition_Fill,
    DockPosition_None
    }

.enum ExpandCollapseState {
    ExpandCollapseState_Collapsed,
    ExpandCollapseState_Expanded,
    ExpandCollapseState_PartiallyExpanded,
    ExpandCollapseState_LeafNode
    }

.enum ScrollAmount {
    ScrollAmount_LargeDecrement,
    ScrollAmount_SmallDecrement,
    ScrollAmount_NoAmount,
    ScrollAmount_LargeIncrement,
    ScrollAmount_SmallIncrement
    }

.enum RowOrColumnMajor {
    RowOrColumnMajor_RowMajor,
    RowOrColumnMajor_ColumnMajor,
    RowOrColumnMajor_Indeterminate
    }

.enum ToggleState {
    ToggleState_Off,
    ToggleState_On,
    ToggleState_Indeterminate
    }

.enum WindowVisualState {
    WindowVisualState_Normal,
    WindowVisualState_Maximized,
    WindowVisualState_Minimized
    }

.enum SynchronizedInputType {
    SynchronizedInputType_KeyUp			= 0x1,
    SynchronizedInputType_KeyDown		= 0x2,
    SynchronizedInputType_LeftMouseUp		= 0x4,
    SynchronizedInputType_LeftMouseDown		= 0x8,
    SynchronizedInputType_RightMouseUp		= 0x10,
    SynchronizedInputType_RightMouseDown	= 0x20
    }

.enum WindowInteractionState {
    WindowInteractionState_Running,
    WindowInteractionState_Closing,
    WindowInteractionState_ReadyForUserInteraction,
    WindowInteractionState_BlockedByModalWindow,
    WindowInteractionState_NotResponding
    }

.enum TextUnit {
    TextUnit_Character,
    TextUnit_Format,
    TextUnit_Word,
    TextUnit_Line,
    TextUnit_Paragraph,
    TextUnit_Page,
    TextUnit_Document
    }

.enum TextPatternRangeEndpoint {
    TextPatternRangeEndpoint_Start,
    TextPatternRangeEndpoint_End
    }

.enum SupportedTextSelection {
    SupportedTextSelection_None,
    SupportedTextSelection_Single,
    SupportedTextSelection_Multiple
    }

.enum LiveSetting {
    Off,
    Polite,
    Assertive
    }

.enum ActiveEnd {
    ActiveEnd_None,
    ActiveEnd_Start,
    ActiveEnd_End
    }

.enum CaretPosition {
    CaretPosition_Unknown,
    CaretPosition_EndOfLine,
    CaretPosition_BeginningOfLine
    }

.enum CaretBidiMode {
    CaretBidiMode_LTR,
    CaretBidiMode_RTL
    }

.enum ZoomUnit {
    ZoomUnit_NoAmount,
    ZoomUnit_LargeDecrement,
    ZoomUnit_SmallDecrement,
    ZoomUnit_LargeIncrement,
    ZoomUnit_SmallIncrement
    }

.enum AnimationStyle {
    AnimationStyle_None,
    AnimationStyle_LasVegasLights,
    AnimationStyle_BlinkingBackground,
    AnimationStyle_SparkleText,
    AnimationStyle_MarchingBlackAnts,
    AnimationStyle_MarchingRedAnts,
    AnimationStyle_Shimmer,
    AnimationStyle_Other = -1
    }

.enum BulletStyle {
    BulletStyle_None,
    BulletStyle_HollowRoundBullet,
    BulletStyle_FilledRoundBullet,
    BulletStyle_HollowSquareBullet,
    BulletStyle_FilledSquareBullet,
    BulletStyle_DashBullet,
    BulletStyle_Other = -1
    }

.enum CapStyle {
    CapStyle_None,
    CapStyle_SmallCap,
    CapStyle_AllCap,
    CapStyle_AllPetiteCaps,
    CapStyle_PetiteCaps,
    CapStyle_Unicase,
    CapStyle_Titling,
    CapStyle_Other = -1
    }

.enum FlowDirections {
    FlowDirections_Default,
    FlowDirections_RightToLeft,
    FlowDirections_BottomToTop,
    FlowDirections_Vertical = 4
    }

.enum HorizontalTextAlignment {
    HorizontalTextAlignment_Left,
    HorizontalTextAlignment_Centered,
    HorizontalTextAlignment_Right,
    HorizontalTextAlignment_Justified
    }

.enum OutlineStyles {
    OutlineStyles_None,
    OutlineStyles_Outline,
    OutlineStyles_Shadow,
    OutlineStyles_Engraved = 4,
    OutlineStyles_Embossed = 8
    }

.enum TextDecorationLineStyle {
    TextDecorationLineStyle_None,
    TextDecorationLineStyle_Single,
    TextDecorationLineStyle_WordsOnly,
    TextDecorationLineStyle_Double,
    TextDecorationLineStyle_Dot,
    TextDecorationLineStyle_Dash,
    TextDecorationLineStyle_DashDot,
    TextDecorationLineStyle_DashDotDot,
    TextDecorationLineStyle_Wavy,
    TextDecorationLineStyle_ThickSingle,
    TextDecorationLineStyle_DoubleWavy	= 11,
    TextDecorationLineStyle_ThickWavy,
    TextDecorationLineStyle_LongDash,
    TextDecorationLineStyle_ThickDash,
    TextDecorationLineStyle_ThickDashDot,
    TextDecorationLineStyle_ThickDashDotDot,
    TextDecorationLineStyle_ThickDot,
    TextDecorationLineStyle_ThickLongDash,
    TextDecorationLineStyle_Other = -1
    }

PROPERTYID		typedef sdword
PATTERNID		typedef sdword
EVENTID			typedef sdword
TEXTATTRIBUTEID		typedef sdword
CONTROLTYPEID		typedef sdword

UiaRect			STRUC
left			real8 ?
top			real8 ?
width			real8 ?
height			real8 ?
UiaRect			ENDS

UiaPoint		STRUC
x			real8 ?
y			real8 ?
UiaPoint		ENDS

ifndef __UIA_LIBRARY_DEFINED__
define __UIA_LIBRARY_DEFINED__

.enum UIAutomationType {
    UIAutomationType_Int	= 0x1,
    UIAutomationType_Bool	= 0x2,
    UIAutomationType_String	= 0x3,
    UIAutomationType_Double	= 0x4,
    UIAutomationType_Point	= 0x5,
    UIAutomationType_Rect	= 0x6,
    UIAutomationType_Element	= 0x7,
    UIAutomationType_Array	= 0x10000,
    UIAutomationType_Out	= 0x20000,
    UIAutomationType_IntArray		= ( UIAutomationType_Int or UIAutomationType_Array ) ,
    UIAutomationType_BoolArray		= ( UIAutomationType_Bool or UIAutomationType_Array ) ,
    UIAutomationType_StringArray	= ( UIAutomationType_String or UIAutomationType_Array ) ,
    UIAutomationType_DoubleArray	= ( UIAutomationType_Double or UIAutomationType_Array ) ,
    UIAutomationType_PointArray		= ( UIAutomationType_Point  or	UIAutomationType_Array ) ,
    UIAutomationType_RectArray		= ( UIAutomationType_Rect  or  UIAutomationType_Array ) ,
    UIAutomationType_ElementArray	= ( UIAutomationType_Element or UIAutomationType_Array ) ,
    UIAutomationType_OutInt		= ( UIAutomationType_Int or UIAutomationType_Out ) ,
    UIAutomationType_OutBool		= ( UIAutomationType_Bool or UIAutomationType_Out ) ,
    UIAutomationType_OutString		= ( UIAutomationType_String or UIAutomationType_Out ) ,
    UIAutomationType_OutDouble		= ( UIAutomationType_Double or UIAutomationType_Out ) ,
    UIAutomationType_OutPoint		= ( UIAutomationType_Point or UIAutomationType_Out ) ,
    UIAutomationType_OutRect		= ( UIAutomationType_Rect or UIAutomationType_Out ) ,
    UIAutomationType_OutElement		= ( UIAutomationType_Element or UIAutomationType_Out ) ,
    UIAutomationType_OutIntArray	= ( ( UIAutomationType_Int or UIAutomationType_Array ) or UIAutomationType_Out ) ,
    UIAutomationType_OutBoolArray	= ( ( UIAutomationType_Bool or UIAutomationType_Array ) or UIAutomationType_Out ) ,
    UIAutomationType_OutStringArray	= ( ( UIAutomationType_String or UIAutomationType_Array ) or UIAutomationType_Out ) ,
    UIAutomationType_OutDoubleArray	= ( ( UIAutomationType_Double or UIAutomationType_Array ) or UIAutomationType_Out ) ,
    UIAutomationType_OutPointArray	= ( ( UIAutomationType_Point or UIAutomationType_Array ) or UIAutomationType_Out ) ,
    UIAutomationType_OutRectArray	= ( ( UIAutomationType_Rect or UIAutomationType_Array ) or UIAutomationType_Out ) ,
    UIAutomationType_OutElementArray	= ( ( UIAutomationType_Element or UIAutomationType_Array ) or UIAutomationType_Out )
    }

UIAutomationParameter	STRUC
type			UIAutomationType ?
pData			PVOID ?
UIAutomationParameter	ENDS

UIAutomationPropertyInfo STRUC
guid			GUID <>
pProgrammaticName	LPCWSTR ?
type			UIAutomationType ?
UIAutomationPropertyInfo ENDS

UIAutomationEventInfo	STRUC
guid			GUID <>
pProgrammaticName	LPCWSTR ?
UIAutomationEventInfo	ENDS

UIAutomationMethodInfo	STRUC
pProgrammaticName	LPCWSTR ?
doSetFocus		BOOL ?
cInParameters		UINT ?
cOutParameters		UINT ?
pParameterTypes		UIAutomationType ?
pParameterNames		LPCWSTR ?
UIAutomationMethodInfo	ENDS

LPIUIAutomationPatternHandler typedef ptr IUIAutomationPatternHandler
UIAutomationPatternInfo STRUC
guid			GUID <>
pProgrammaticName	LPCWSTR ?
providerInterfaceId	GUID <>
clientInterfaceId	GUID <>
cProperties		UINT ?
pProperties		LPINT ?
cMethods		UINT ?
pMethods		LPINT ?
cEvents			UINT ?
pEvents			LPINT ?
pPatternHandler		LPIUIAutomationPatternHandler ?
UIAutomationPatternInfo ENDS

externdef		LIBID_UIA:IID


ifndef __UIA_OtherConstants_MODULE_DEFINED__
define __UIA_OtherConstants_MODULE_DEFINED__

UIA_ScrollPatternNoScroll equ -1.0

endif

ifndef __IRawElementProviderSimple_INTERFACE_DEFINED__
define __IRawElementProviderSimple_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderSimple, "d6dd68d1-86fd-4332-8666-9abedea2d24c")

.comdef IRawElementProviderSimple : public IUnknown

    get_ProviderOptions proc :ptr
    GetPatternProvider	proc :PATTERNID, :ptr
    GetPropertyValue	proc :PROPERTYID, :ptr
    get_HostRawElementProvider proc :ptr
   .ends

endif

ifndef __IRawElementProviderSimple2_INTERFACE_DEFINED__
define __IRawElementProviderSimple2_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderSimple2, "A0A839A9-8DA1-4A82-806A-8E0D44E79F56")

.comdef IRawElementProviderSimple2 : public IRawElementProviderSimple

    ShowContextMenu	proc
   .ends

endif

ifndef __IAccessibleEx_INTERFACE_DEFINED__
define __IAccessibleEx_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibleEx, "f8b80ada-2c44-48d0-89be-5ff23c9cd875")

.comdef IAccessibleEx : public IUnknown

    GetObjectForChild	proc :LONG, :ptr
    GetIAccessiblePair	proc :ptr, :ptr
    GetRuntimeId	proc :ptr
    ConvertReturnedElement proc :ptr, :ptr
   .ends

endif

ifndef __IRawElementProviderFragmentRoot_INTERFACE_DEFINED__
define __IRawElementProviderFragmentRoot_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderFragmentRoot, "620ce2a5-ab8f-40a9-86cb-de3c75599b58")

.comdef IRawElementProviderFragmentRoot : public IUnknown

    ElementProviderFromPoint proc :real8, :real8, :ptr
    GetFocus		proc :ptr
   .ends

endif

ifndef __IRawElementProviderFragment_INTERFACE_DEFINED__
define __IRawElementProviderFragment_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderFragment, "f7063da8-8359-439c-9297-bbc5299a7d87")

.comdef IRawElementProviderFragment : public IUnknown

    Navigate		proc :NavigateDirection, :ptr
    GetRuntimeId	proc :ptr
    get_BoundingRectangle proc :ptr
    GetEmbeddedFragmentRoots proc :ptr
    SetFocus		proc
    get_FragmentRoot	proc :ptr
   .ends

endif

ifndef __IRawElementProviderAdviseEvents_INTERFACE_DEFINED__
define __IRawElementProviderAdviseEvents_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderAdviseEvents, "a407b27b-0f6d-4427-9292-473c7bf93258")

.comdef IRawElementProviderAdviseEvents : public IUnknown

    AdviseEventAdded	proc :EVENTID, :ptr
    AdviseEventRemoved	proc :EVENTID, :ptr
   .ends

endif

ifndef __IRawElementProviderHwndOverride_INTERFACE_DEFINED__
define __IRawElementProviderHwndOverride_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderHwndOverride, "1d5df27c-8947-4425-b8d9-79787bb460b8")

.comdef IRawElementProviderHwndOverride : public IUnknown

    GetOverrideProviderForHwnd proc :HWND, :ptr
   .ends

endif

ifndef __IProxyProviderWinEventSink_INTERFACE_DEFINED__
define __IProxyProviderWinEventSink_INTERFACE_DEFINED__

DEFINE_IIDX(IProxyProviderWinEventSink, "4fd82b78-a43e-46ac-9803-0a6969c7c183")

.comdef IProxyProviderWinEventSink : public IUnknown

    AddAutomationPropertyChangedEvent proc :ptr, :PROPERTYID, :VARIANT
    AddAutomationEvent	proc :ptr, :EVENTID
    AddStructureChangedEvent proc :ptr, :StructureChangeType, :ptr
   .ends

endif

ifndef __IProxyProviderWinEventHandler_INTERFACE_DEFINED__
define __IProxyProviderWinEventHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IProxyProviderWinEventHandler, "89592ad4-f4e0-43d5-a3b6-bad7e111b435")

.comdef IProxyProviderWinEventHandler : public IUnknown

    RespondToWinEvent	proc :DWORD, :HWND, :LONG, :LONG, :ptr
   .ends

endif

ifndef __IRawElementProviderWindowlessSite_INTERFACE_DEFINED__
define __IRawElementProviderWindowlessSite_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderWindowlessSite, "0a2a93cc-bfad-42ac-9b2e-0991fb0d3ea0")

.comdef IRawElementProviderWindowlessSite : public IUnknown

    GetAdjacentFragment proc :NavigateDirection, :ptr
    GetRuntimeIdPrefix	proc :ptr
   .ends

endif

ifndef __IAccessibleHostingElementProviders_INTERFACE_DEFINED__
define __IAccessibleHostingElementProviders_INTERFACE_DEFINED__

DEFINE_IIDX(IAccessibleHostingElementProviders, "33AC331B-943E-4020-B295-DB37784974A3")

.comdef IAccessibleHostingElementProviders : public IUnknown

    GetEmbeddedFragmentRoots proc :ptr
    GetObjectIdForProvider proc :ptr, :ptr
   .ends

endif

ifndef __IRawElementProviderHostingAccessibles_INTERFACE_DEFINED__
define __IRawElementProviderHostingAccessibles_INTERFACE_DEFINED__

DEFINE_IIDX(IRawElementProviderHostingAccessibles, "24BE0B07-D37D-487A-98CF-A13ED465E9B3")

.comdef IRawElementProviderHostingAccessibles : public IUnknown

    GetEmbeddedAccessibles proc :ptr
   .ends

endif

ifndef __IDockProvider_INTERFACE_DEFINED__
define __IDockProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IDockProvider, "159bc72c-4ad3-485e-9637-d7052edf0146")

.comdef IDockProvider : public IUnknown

    SetDockPosition	proc :DockPosition
    get_DockPosition	proc :ptr
   .ends

endif

ifndef __IExpandCollapseProvider_INTERFACE_DEFINED__
define __IExpandCollapseProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IExpandCollapseProvider, "d847d3a5-cab0-4a98-8c32-ecb45c59ad24")

.comdef IExpandCollapseProvider : public IUnknown

    Expand		proc
    Collapse		proc
    get_ExpandCollapseState proc :ptr
   .ends

endif

ifndef __IGridProvider_INTERFACE_DEFINED__
define __IGridProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IGridProvider, "b17d6187-0907-464b-a168-0ef17a1572b1")

.comdef IGridProvider : public IUnknown

    GetItem		proc :SINT, :SINT, :ptr
    get_RowCount	proc :ptr
    get_ColumnCount	proc :ptr
   .ends

endif

ifndef __IGridItemProvider_INTERFACE_DEFINED__
define __IGridItemProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IGridItemProvider, "d02541f1-fb81-4d64-ae32-f520f8a6dbd1")

.comdef IGridItemProvider : public IUnknown

    get_Row		proc :ptr
    get_Column		proc :ptr
    get_RowSpan		proc :ptr
    get_ColumnSpan	proc :ptr
    get_ContainingGrid	proc :ptr
   .ends

endif

ifndef __IInvokeProvider_INTERFACE_DEFINED__
define __IInvokeProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IInvokeProvider, "54fcb24b-e18e-47a2-b4d3-eccbe77599a2")

.comdef IInvokeProvider : public IUnknown

    _Invoke		proc
   .ends

endif

ifndef __IMultipleViewProvider_INTERFACE_DEFINED__
define __IMultipleViewProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IMultipleViewProvider, "6278cab1-b556-4a1a-b4e0-418acc523201")

.comdef IMultipleViewProvider : public IUnknown

    GetViewName		proc :SINT, :ptr
    SetCurrentView	proc :SINT
    get_CurrentView	proc :ptr
    GetSupportedViews	proc :ptr
   .ends

endif

ifndef __IRangeValueProvider_INTERFACE_DEFINED__
define __IRangeValueProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IRangeValueProvider, "36dc7aef-33e6-4691-afe1-2be7274b3d33")

.comdef IRangeValueProvider : public IUnknown

    SetValue		proc :real8
    get_Value		proc :ptr
    get_IsReadOnly	proc :ptr
    get_Maximum		proc :ptr
    get_Minimum		proc :ptr
    get_LargeChange	proc :ptr
    get_SmallChange	proc :ptr
   .ends

endif

ifndef __IScrollItemProvider_INTERFACE_DEFINED__
define __IScrollItemProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IScrollItemProvider, "2360c714-4bf1-4b26-ba65-9b21316127eb")

.comdef IScrollItemProvider : public IUnknown

    ScrollIntoView	proc
   .ends

endif

ifndef __ISelectionProvider_INTERFACE_DEFINED__
define __ISelectionProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ISelectionProvider, "fb8b03af-3bdf-48d4-bd36-1a65793be168")

.comdef ISelectionProvider : public IUnknown

    GetSelection	proc :ptr
    get_CanSelectMultiple proc :ptr
    get_IsSelectionRequired proc :ptr
   .ends

endif

ifndef __IScrollProvider_INTERFACE_DEFINED__
define __IScrollProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IScrollProvider, "b38b8077-1fc3-42a5-8cae-d40c2215055a")

.comdef IScrollProvider : public IUnknown

    Scroll		proc :ScrollAmount, :ScrollAmount
    SetScrollPercent	proc :real8, :real8
    get_HorizontalScrollPercent proc :ptr
    get_VerticalScrollPercent proc :ptr
    get_HorizontalViewSize proc :ptr
    get_VerticalViewSize proc :ptr
    get_HorizontallyScrollable proc :ptr
    get_VerticallyScrollable proc :ptr
   .ends

endif

ifndef __ISelectionItemProvider_INTERFACE_DEFINED__
define __ISelectionItemProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ISelectionItemProvider, "2acad808-b2d4-452d-a407-91ff1ad167b2")

.comdef ISelectionItemProvider : public IUnknown

    Select		proc
    AddToSelection	proc
    RemoveFromSelection proc
    get_IsSelected	proc :ptr
    get_SelectionContainer proc :ptr
   .ends

endif

ifndef __ISynchronizedInputProvider_INTERFACE_DEFINED__
define __ISynchronizedInputProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ISynchronizedInputProvider, "29db1a06-02ce-4cf7-9b42-565d4fab20ee")

.comdef ISynchronizedInputProvider : public IUnknown

    StartListening	proc :SynchronizedInputType
    Cancel		proc
   .ends

endif

ifndef __ITableProvider_INTERFACE_DEFINED__
define __ITableProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITableProvider, "9c860395-97b3-490a-b52a-858cc22af166")

.comdef ITableProvider : public IUnknown

    GetRowHeaders	proc :ptr
    GetColumnHeaders	proc :ptr
    get_RowOrColumnMajor proc :ptr
   .ends

endif

ifndef __ITableItemProvider_INTERFACE_DEFINED__
define __ITableItemProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITableItemProvider, "b9734fa6-771f-4d78-9c90-2517999349cd")

.comdef ITableItemProvider : public IUnknown

    GetRowHeaderItems	proc :ptr
    GetColumnHeaderItems proc :ptr
   .ends

endif

ifndef __IToggleProvider_INTERFACE_DEFINED__
define __IToggleProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IToggleProvider, "56d00bd0-c4f4-433c-a836-1a52a57e0892")

.comdef IToggleProvider : public IUnknown

    Toggle		proc
    get_ToggleState	proc :ptr
   .ends

endif

ifndef __ITransformProvider_INTERFACE_DEFINED__
define __ITransformProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITransformProvider, "6829ddc4-4f91-4ffa-b86f-bd3e2987cb4c")

.comdef ITransformProvider : public IUnknown

    Move		proc :real8, :real8
    Resize		proc :real8, :real8
    Rotate		proc :real8
    get_CanMove		proc :ptr
    get_CanResize	proc :ptr
    get_CanRotate	proc :ptr
   .ends

endif

ifndef __IValueProvider_INTERFACE_DEFINED__
define __IValueProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IValueProvider, "c7935180-6fb3-4201-b174-7df73adbf64a")

.comdef IValueProvider : public IUnknown

    SetValue		proc :LPCWSTR
    get_Value		proc :ptr
    get_IsReadOnly	proc :ptr
   .ends

endif

ifndef __IWindowProvider_INTERFACE_DEFINED__
define __IWindowProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWindowProvider, "987df77b-db06-4d77-8f8a-86a9c3bb90b9")

.comdef IWindowProvider : public IUnknown

    SetVisualState	proc :WindowVisualState
    Close		proc
    WaitForInputIdle	proc :SINT, :ptr
    get_CanMaximize	proc :ptr
    get_CanMinimize	proc :ptr
    get_IsModal		proc :ptr
    get_WindowVisualState proc :ptr
    get_WindowInteractionState proc :ptr
    get_IsTopmost	proc :ptr
   .ends

endif

ifndef __ILegacyIAccessibleProvider_INTERFACE_DEFINED__
define __ILegacyIAccessibleProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ILegacyIAccessibleProvider, "e44c3566-915d-4070-99c6-047bff5a08f5")

.comdef ILegacyIAccessibleProvider : public IUnknown

    Select		proc :LONG
    DoDefaultAction	proc
    SetValue		proc :LPCWSTR
    GetIAccessible	proc :ptr
    get_ChildId		proc :ptr
    get_Name		proc :ptr
    get_Value		proc :ptr
    get_Description	proc :ptr
    get_Role		proc :ptr
    get_State		proc :ptr
    get_Help		proc :ptr
    get_KeyboardShortcut proc :ptr
    GetSelection	proc :ptr
    get_DefaultAction	proc :ptr
   .ends

endif

ifndef __IItemContainerProvider_INTERFACE_DEFINED__
define __IItemContainerProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IItemContainerProvider, "e747770b-39ce-4382-ab30-d8fb3f336f24")

.comdef IItemContainerProvider : public IUnknown

    FindItemByProperty	proc :ptr, :PROPERTYID, :VARIANT, :ptr
   .ends

endif

ifndef __IVirtualizedItemProvider_INTERFACE_DEFINED__
define __IVirtualizedItemProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IVirtualizedItemProvider, "cb98b665-2d35-4fac-ad35-f3c60d0c0b8b")

.comdef IVirtualizedItemProvider : public IUnknown

    Realize		proc
   .ends

endif

ifndef __IObjectModelProvider_INTERFACE_DEFINED__
define __IObjectModelProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IObjectModelProvider, "3ad86ebd-f5ef-483d-bb18-b1042a475d64")

.comdef IObjectModelProvider : public IUnknown

    GetUnderlyingObjectModel proc :ptr
   .ends

endif

ifndef __IAnnotationProvider_INTERFACE_DEFINED__
define __IAnnotationProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IAnnotationProvider, "f95c7e80-bd63-4601-9782-445ebff011fc")

.comdef IAnnotationProvider : public IUnknown

    get_AnnotationTypeId proc :ptr
    get_AnnotationTypeName proc :ptr
    get_Author		proc :ptr
    get_DateTime	proc :ptr
    get_Target		proc :ptr
   .ends

endif

ifndef __IStylesProvider_INTERFACE_DEFINED__
define __IStylesProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IStylesProvider, "19b6b649-f5d7-4a6d-bdcb-129252be588a")

.comdef IStylesProvider : public IUnknown

    get_StyleId		proc :ptr
    get_StyleName	proc :ptr
    get_FillColor	proc :ptr
    get_FillPatternStyle proc :ptr
    get_Shape		proc :ptr
    get_FillPatternColor proc :ptr
    get_ExtendedProperties proc :ptr
   .ends

endif

ifndef __ISpreadsheetProvider_INTERFACE_DEFINED__
define __ISpreadsheetProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ISpreadsheetProvider, "6f6b5d35-5525-4f80-b758-85473832ffc7")

.comdef ISpreadsheetProvider : public IUnknown

    GetItemByName	proc :LPCWSTR, :ptr
   .ends

endif

ifndef __ISpreadsheetItemProvider_INTERFACE_DEFINED__
define __ISpreadsheetItemProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ISpreadsheetItemProvider, "eaed4660-7b3d-4879-a2e6-365ce603f3d0")

.comdef ISpreadsheetItemProvider : public IUnknown

    get_Formula		proc :ptr
    GetAnnotationObjects proc :ptr
    GetAnnotationTypes	proc :ptr
   .ends

endif

ifndef __ITransformProvider2_INTERFACE_DEFINED__
define __ITransformProvider2_INTERFACE_DEFINED__

DEFINE_IIDX(ITransformProvider2, "4758742f-7ac2-460c-bc48-09fc09308a93")

.comdef ITransformProvider2 : public ITransformProvider

    Zoom		proc :real8
    get_CanZoom		proc :ptr
    get_ZoomLevel	proc :ptr
    get_ZoomMinimum	proc :ptr
    get_ZoomMaximum	proc :ptr
    ZoomByUnit		proc :ZoomUnit
   .ends

endif

ifndef __IDragProvider_INTERFACE_DEFINED__
define __IDragProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IDragProvider, "6aa7bbbb-7ff9-497d-904f-d20b897929d8")

.comdef IDragProvider : public IUnknown

    get_IsGrabbed	proc :ptr
    get_DropEffect	proc :ptr
    get_DropEffects	proc :ptr
    GetGrabbedItems	proc :ptr
   .ends

endif

ifndef __IDropTargetProvider_INTERFACE_DEFINED__
define __IDropTargetProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IDropTargetProvider, "bae82bfd-358a-481c-85a0-d8b4d90a5d61")

.comdef IDropTargetProvider : public IUnknown

    get_DropTargetEffect proc :ptr
    get_DropTargetEffects proc :ptr
   .ends

endif

ifndef __ITextRangeProvider_INTERFACE_DEFINED__
define __ITextRangeProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITextRangeProvider, "5347ad7b-c355-46f8-aff5-909033582f63")

.comdef ITextRangeProvider : public IUnknown

    Clone		proc :ptr
    Compare		proc :ptr, :ptr
    CompareEndpoints	proc :TextPatternRangeEndpoint, :ptr, :TextPatternRangeEndpoint, :ptr
    ExpandToEnclosingUnit proc :TextUnit
    FindAttribute	proc :TEXTATTRIBUTEID, :VARIANT, :BOOL, :ptr
    FindText		proc :BSTR, :BOOL, :BOOL, :ptr
    GetAttributeValue	proc :TEXTATTRIBUTEID, :ptr
    GetBoundingRectangles proc :ptr
    GetEnclosingElement proc :ptr
    GetText		proc :SINT, :ptr
    Move		proc :TextUnit, :SINT, :ptr
    MoveEndpointByUnit	proc :TextPatternRangeEndpoint, :TextUnit, :SINT, :ptr
    MoveEndpointByRange proc :TextPatternRangeEndpoint, :ptr, :TextPatternRangeEndpoint
    Select		proc
    AddToSelection	proc
    RemoveFromSelection proc
    ScrollIntoView	proc :BOOL
    GetChildren		proc :ptr
   .ends

endif

ifndef __ITextProvider_INTERFACE_DEFINED__
define __ITextProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITextProvider, "3589c92c-63f3-4367-99bb-ada653b77cf2")

.comdef ITextProvider : public IUnknown

    GetSelection	proc :ptr
    GetVisibleRanges	proc :ptr
    RangeFromChild	proc :ptr, :ptr
    RangeFromPoint	proc :UiaPoint, :ptr
    get_DocumentRange	proc :ptr
    get_SupportedTextSelection proc :ptr
   .ends

endif

ifndef __ITextProvider2_INTERFACE_DEFINED__
define __ITextProvider2_INTERFACE_DEFINED__

DEFINE_IIDX(ITextProvider2, "0dc5e6ed-3e16-4bf1-8f9a-a979878bc195")

.comdef ITextProvider2 : public ITextProvider

    RangeFromAnnotation proc :ptr, :ptr
    GetCaretRange	proc :ptr, :ptr
   .ends

endif

ifndef __ITextEditProvider_INTERFACE_DEFINED__
define __ITextEditProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITextEditProvider, "EA3605B4-3A05-400E-B5F9-4E91B40F6176")

.comdef ITextEditProvider : public ITextProvider

    GetActiveComposition proc :ptr
    GetConversionTarget proc :ptr
   .ends

endif

ifndef __ITextRangeProvider2_INTERFACE_DEFINED__
define __ITextRangeProvider2_INTERFACE_DEFINED__

DEFINE_IIDX(ITextRangeProvider2, "9BBCE42C-1921-4F18-89CA-DBA1910A0386")

.comdef ITextRangeProvider2 : public ITextRangeProvider

    ShowContextMenu	proc
   .ends

endif

ifndef __ITextChildProvider_INTERFACE_DEFINED__
define __ITextChildProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITextChildProvider, "4c2de2b9-c88f-4f88-a111-f1d336b7d1a9")

.comdef ITextChildProvider : public IUnknown

    get_TextContainer	proc :ptr
    get_TextRange	proc :ptr
   .ends

endif

ifndef __IUIAutomationPatternInstance_INTERFACE_DEFINED__
define __IUIAutomationPatternInstance_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationPatternInstance, "c03a7fe4-9431-409f-bed8-ae7c2299bc8d")

.comdef IUIAutomationPatternInstance : public IUnknown

    GetProperty		proc :UINT, :BOOL, :UIAutomationType, :ptr
    CallMethod		proc :UINT, :ptr, :UINT
   .ends

endif

ifndef __IUIAutomationPatternHandler_INTERFACE_DEFINED__
define __IUIAutomationPatternHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationPatternHandler, "d97022f3-a947-465e-8b2a-ac4315fa54e8")

.comdef IUIAutomationPatternHandler : public IUnknown

    CreateClientWrapper proc :ptr, :ptr
    Dispatch		proc :ptr, :UINT, :ptr, :UINT
   .ends

endif

ifndef __IUIAutomationRegistrar_INTERFACE_DEFINED__
define __IUIAutomationRegistrar_INTERFACE_DEFINED__

DEFINE_IIDX(IUIAutomationRegistrar, "8609c4ec-4a1a-4d88-a357-5a66e060e1cf")

.comdef IUIAutomationRegistrar : public IUnknown

    RegisterProperty	proc :ptr, :ptr
    RegisterEvent	proc :ptr, :ptr
    RegisterPattern	proc :ptr, :ptr, :ptr, :UINT, :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_CUIAutomationRegistrar, "6e29fabf-9977-42d1-8d0e-ca7e61ad87e6")

endif
endif
