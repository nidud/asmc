ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef __peninputpanel_h__
define __peninputpanel_h__

include oaidl.inc
include ocidl.inc
include msinkaut.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __PenInputPanelLib_LIBRARY_DEFINED__
define __PenInputPanelLib_LIBRARY_DEFINED__

define MICROSOFT_PENINPUT_PANEL_PROPERTY_T	<L"Microsoft PenInputPanel 1.5">

.enum DISPID_PenInputPanel {
	DISPID_PIPAttachedEditWindow = DISPID_VALUE,
	DISPID_PIPFactoid,
	DISPID_PIPCurrentPanel,
	DISPID_PIPDefaultPanel,
	DISPID_PIPVisible,
	DISPID_PIPTop,
	DISPID_PIPLeft,
	DISPID_PIPWidth,
	DISPID_PIPHeight,
	DISPID_PIPMoveTo,
	DISPID_PIPCommitPendingInput,
	DISPID_PIPRefresh,
	DISPID_PIPBusy,
	DISPID_PIPVerticalOffset,
	DISPID_PIPHorizontalOffset,
	DISPID_PIPEnableTsf,
	DISPID_PIPAutoShow
	}

.enum DISPID_PenInputPanelEvents {
	DISPID_PIPEVisibleChanged,
	DISPID_PIPEPanelChanged,
	DISPID_PIPEInputFailed,
	DISPID_PIPEPanelMoving
	}

.enum VisualState {
	InPlace,
	Floating,
	DockedTop,
	DockedBottom,
	Closed
	}

.enum InteractionMode {
	InteractionMode_InPlace,
	InteractionMode_Floating,
	InteractionMode_DockedTop,
	InteractionMode_DockedBottom
	}

.enum InPlaceState {
	InPlaceState_Auto,
	InPlaceState_HoverTarget,
	InPlaceState_Expanded
	}

.enum PanelInputArea {
	PanelInputArea_Auto,
	PanelInputArea_Keyboard,
	PanelInputArea_WritingPad,
	PanelInputArea_CharacterPad
	}

.enum CorrectionMode {
	CorrectionMode_NotVisible,
	CorrectionMode_PreInsertion,
	CorrectionMode_PostInsertionCollapsed,
	CorrectionMode_PostInsertionExpanded
	}

.enum CorrectionPosition {
	CorrectionPosition_Auto,
	CorrectionPosition_Bottom,
	CorrectionPosition_Top
	}

.enum InPlaceDirection {
	InPlaceDirection_Auto,
	InPlaceDirection_Bottom,
	InPlaceDirection_Top
	}

.enum EventMask {
	EventMask_InPlaceStateChanging		= 1,
	EventMask_InPlaceStateChanged		= 2,
	EventMask_InPlaceSizeChanging		= 4,
	EventMask_InPlaceSizeChanged		= 8,
	EventMask_InputAreaChanging		= 16,
	EventMask_InputAreaChanged		= 32,
	EventMask_CorrectionModeChanging	= 64,
	EventMask_CorrectionModeChanged		= 128,
	EventMask_InPlaceVisibilityChanging	= 256,
	EventMask_InPlaceVisibilityChanged	= 512,
	EventMask_TextInserting			= 1024,
	EventMask_TextInserted			= 2048,
	EventMask_All				= 0xFFF
	}

define MICROSOFT_URL_EXPERIENCE_PROPERTY <L"Microsoft TIP URL Experience">
define MICROSOFT_TIP_NO_INSERT_BUTTON_PROPERTY <L"Microsoft TIP No Insert Option">
define MICROSOFT_TIP_COMBOBOXLIST_PROPERTY <L"Microsoft TIP ComboBox List Window Identifier">
define MICROSOFT_TIP_OPENING_MSG <L"TabletInputPanelOpening">

externdef LIBID_PenInputPanelLib:IID

ifndef __IPenInputPanel_INTERFACE_DEFINED__
define __IPenInputPanel_INTERFACE_DEFINED__

.enum PanelType {
	PT_Default,
	PT_Inactive,
	PT_Handwriting,
	PT_Keyboard
	}

DEFINE_IIDX(IPenInputPanel, "fa7a4083-5747-4040-a182-0b0e9fd4fac7")

.comdef IPenInputPanel : public IDispatch
    get_Busy		proc :ptr
    get_Factoid		proc :ptr
    put_Factoid		proc :BSTR
    get_AttachedEditWindow proc :ptr
    put_AttachedEditWindow proc :LONG32
    get_CurrentPanel	proc :ptr
    put_CurrentPanel	proc :PanelType
    get_DefaultPanel	proc :ptr
    put_DefaultPanel	proc :PanelType
    get_Visible		proc :ptr
    put_Visible		proc :VARIANT_BOOL
    get_Top		proc :ptr
    get_Left		proc :ptr
    get_Width		proc :ptr
    get_Height		proc :ptr
    get_VerticalOffset	proc :ptr
    put_VerticalOffset	proc :LONG
    get_HorizontalOffset proc :ptr
    put_HorizontalOffset proc :LONG
    get_AutoShow	proc :ptr
    put_AutoShow	proc :VARIANT_BOOL
    MoveTo		proc :LONG, :LONG
    CommitPendingInput	proc
    Refresh		proc
    EnableTsf		proc :VARIANT_BOOL
   .ends

endif

ifndef ___IPenInputPanelEvents_DISPINTERFACE_DEFINED__
define ___IPenInputPanelEvents_DISPINTERFACE_DEFINED__

DEFINE_IIDX(_IPenInputPanelEvents, "b7e489da-3719-439f-848f-e7acbd820f17")

.comdef _IPenInputPanelEvents : public IDispatch
   .ends

endif

ifndef __IHandwrittenTextInsertion_INTERFACE_DEFINED__
define __IHandwrittenTextInsertion_INTERFACE_DEFINED__

DEFINE_IIDX(IHandwrittenTextInsertion, "56FDEA97-ECD6-43e7-AA3A-816BE7785860")

.comdef IHandwrittenTextInsertion : public IUnknown
    InsertRecognitionResultsArray proc :ptr, :LCID, :BOOL
    InsertInkRecognitionResult proc :ptr, :LCID, :BOOL
   .ends

endif

DEFINE_GUIDS(CLSID_HandwrittenTextInsertion, "9F074EE2-E6E9-4d8a-A047-EB5B5C3C55DA")
DEFINE_GUIDS(CLSID_PenInputPanel, "f744e496-1b5a-489e-81dc-fbd7ac6298a8")

ifndef __ITextInputPanelEventSink_INTERFACE_DEFINED__
define __ITextInputPanelEventSink_INTERFACE_DEFINED__

DEFINE_IIDX(ITextInputPanelEventSink, "27560408-8e64-4fe1-804e-421201584b31")

.comdef ITextInputPanelEventSink : public IUnknown
    InPlaceStateChanging proc :InPlaceState, :InPlaceState
    InPlaceStateChanged proc :InPlaceState, :InPlaceState
    InPlaceSizeChanging proc :RECT, :RECT
    InPlaceSizeChanged	proc :RECT, :RECT
    InputAreaChanging	proc :PanelInputArea, :PanelInputArea
    InputAreaChanged	proc :PanelInputArea, :PanelInputArea
    CorrectionModeChanging proc :CorrectionMode, :CorrectionMode
    CorrectionModeChanged proc :CorrectionMode, :CorrectionMode
    InPlaceVisibilityChanging proc :BOOL, :BOOL
    InPlaceVisibilityChanged proc :BOOL, :BOOL
    TextInserting	proc :ptr
    TextInserted	proc :ptr
   .ends

endif

ifndef __ITextInputPanel_INTERFACE_DEFINED__
define __ITextInputPanel_INTERFACE_DEFINED__

DEFINE_IIDX(ITextInputPanel, "6b6a65a5-6af3-46c2-b6ea-56cd1f80df71")

.comdef ITextInputPanel : public IUnknown
    get_AttachedEditWindow proc :ptr
    put_AttachedEditWindow proc :HWND
    get_CurrentInteractionMode proc :ptr
    get_DefaultInPlaceState proc :ptr
    put_DefaultInPlaceState proc :InPlaceState
    get_CurrentInPlaceState proc :ptr
    get_DefaultInputArea proc :ptr
    put_DefaultInputArea proc :PanelInputArea
    get_CurrentInputArea proc :ptr
    get_CurrentCorrectionMode proc :ptr
    get_PreferredInPlaceDirection proc :ptr
    put_PreferredInPlaceDirection proc :InPlaceDirection
    get_ExpandPostInsertionCorrection proc :ptr
    put_ExpandPostInsertionCorrection proc :BOOL
    get_InPlaceVisibleOnFocus proc :ptr
    put_InPlaceVisibleOnFocus proc :BOOL
    get_InPlaceBoundingRectangle proc :ptr
    get_PopUpCorrectionHeight proc :ptr
    get_PopDownCorrectionHeight proc :ptr
    CommitPendingInput	proc
    SetInPlaceVisibility proc :BOOL
    SetInPlacePosition	proc :int_t, :int_t, :CorrectionPosition
    SetInPlaceHoverTargetPosition proc :int_t, :int_t
    Advise		proc :ptr, :DWORD
    Unadvise		proc :ptr
   .ends

endif

ifndef __IInputPanelWindowHandle_INTERFACE_DEFINED__
define __IInputPanelWindowHandle_INTERFACE_DEFINED__

DEFINE_IIDX(IInputPanelWindowHandle, "4AF81847-FDC4-4fc3-AD0B-422479C1B935")

.comdef IInputPanelWindowHandle : public IUnknown
    get_AttachedEditWindow32 proc :ptr
    put_AttachedEditWindow32 proc :LONG32
    get_AttachedEditWindow64 proc :ptr
    put_AttachedEditWindow64 proc :LONG64
   .ends

endif

ifndef __ITextInputPanelRunInfo_INTERFACE_DEFINED__
define __ITextInputPanelRunInfo_INTERFACE_DEFINED__

DEFINE_IIDX(ITextInputPanelRunInfo, "9F424568-1920-48cc-9811-A993CBF5ADBA")

.comdef ITextInputPanelRunInfo : public IUnknown
    IsTipRunning	proc :ptr
   .ends

endif

DEFINE_GUIDS(CLSID_TextInputPanel, "f9b189d7-228b-4f2b-8650-b97f59e02c8c")
DEFINE_GUIDS(CLSID_PenInputPanel_Internal, "802B1FB9-056B-4720-B0CC-80D23B71171E")

endif

endif

endif
