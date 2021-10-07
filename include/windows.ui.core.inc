ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __windows2Eui2Ecore_h__
define __windows2Eui2Ecore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.System.inc
include Windows.UI.Input.inc
include windows.foundation.collections.inc

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCharacterReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCharacterReceivedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCharacterReceivedEventArgs, "5aa4a848-86b2-506b-89ab-5eb5786420c6")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCharacterReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCoreWindowEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCoreWindowEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCoreWindowEventArgs, "1a8ac270-a777-50f7-88a1-e34e56c09449")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CCoreWindowEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CInputEnabledEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CInputEnabledEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CInputEnabledEventArgs, "c9965f1c-3641-51b6-b823-048ec3628fb0")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CInputEnabledEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CKeyEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CKeyEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CKeyEventArgs, "eadffdf7-d70e-5688-906c-c2b1229ea16d")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CKeyEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CPointerEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CPointerEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CPointerEventArgs, "26aabf41-a0fd-5e66-b188-6c74182d00cd")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CPointerEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CTouchHitTestingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CTouchHitTestingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CTouchHitTestingEventArgs, "c76e9d25-6a96-58fd-874f-ae52bd603af8")

.comdef __FITypedEventHandler_2_IInspectable_Windows__CUI__CCore__CTouchHitTestingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreDispatcher_Windows__CUI__CCore__CAcceleratorKeyEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreDispatcher_Windows__CUI__CCore__CAcceleratorKeyEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreDispatcher_Windows__CUI__CCore__CAcceleratorKeyEventArgs, "136dff0d-f7e8-5153-b31c-86390c701880")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreDispatcher_Windows__CUI__CCore__CAcceleratorKeyEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CAutomationProviderRequestedEventArgs, "54db5c04-81f7-5f46-9fb8-e49beec70a24")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CAutomationProviderRequestedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCharacterReceivedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCharacterReceivedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCharacterReceivedEventArgs, "73f846a8-0af6-5872-8fb8-ae2f56d8553e")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCharacterReceivedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowEventArgs, "d08e4f66-3457-57f2-ba0c-cb347133bd15")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowPopupShowingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowPopupShowingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowPopupShowingEventArgs, "b32d6422-78b2-5e00-84a8-6e3167aaabde")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CCoreWindowPopupShowingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CInputEnabledEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CInputEnabledEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CInputEnabledEventArgs, "e230a64a-506a-59c3-bb61-5559ff995663")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CInputEnabledEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CKeyEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CKeyEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CKeyEventArgs, "a3ec0774-55ac-5d61-8232-b35c5d35c93c")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CKeyEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CPointerEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CPointerEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CPointerEventArgs, "420e1bb6-e99d-5e64-8e25-07467e3cae9e")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CPointerEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CTouchHitTestingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CTouchHitTestingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CTouchHitTestingEventArgs, "197654c9-0c47-502b-9aa1-0deb03ed9702")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CTouchHitTestingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CVisibilityChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CVisibilityChangedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CVisibilityChangedEventArgs, "14b7f692-5583-52a1-aa42-fc1843c0f748")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CVisibilityChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowActivatedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowActivatedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowActivatedEventArgs, "26a73b35-a7f9-52db-88d6-15726deb2523")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowActivatedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowSizeChangedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowSizeChangedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowSizeChangedEventArgs, "318dbb67-4089-5690-9040-1d454fb2f686")

.comdef __FITypedEventHandler_2_Windows__CUI__CCore__CCoreWindow_Windows__CUI__CCore__CWindowSizeChangedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace ABI
.namespace Windows
.namespace UI
.namespace Core

.enum CoreWindowActivationState {
    CoreWindowActivationState_CodeActivated,
    CoreWindowActivationState_Deactivated,
    CoreWindowActivationState_PointerActivated
    }

.enum CoreCursorType {
    CoreCursorType_Arrow,
    CoreCursorType_Cross,
    CoreCursorType_Custom,
    CoreCursorType_Hand,
    CoreCursorType_Help,
    CoreCursorType_IBeam,
    CoreCursorType_SizeAll,
    CoreCursorType_SizeNortheastSouthwest,
    CoreCursorType_SizeNorthSouth,
    CoreCursorType_SizeNorthwestSoutheast,
    CoreCursorType_SizeWestEast,
    CoreCursorType_UniversalNo,
    CoreCursorType_UpArrow,
    CoreCursorType_Wait
    }

.enum CoreDispatcherPriority {
    CoreDispatcherPriority_Idle = -2,
    CoreDispatcherPriority_Low	= -1,
    CoreDispatcherPriority_Normal = 0,
    CoreDispatcherPriority_High = 1
    }

.enum CoreProcessEventsOption {
    CoreProcessEventsOption_ProcessOneAndAllPending,
    CoreProcessEventsOption_ProcessOneIfPresent,
    CoreProcessEventsOption_ProcessUntilQuit,
    CoreProcessEventsOption_ProcessAllIfPresent
    }

.enum CoreWindowFlowDirection {
    CoreWindowFlowDirection_LeftToRight,
    CoreWindowFlowDirection_RightToLeft
    }

.enum CoreVirtualKeyStates {
    CoreVirtualKeyStates_None	= 0,
    CoreVirtualKeyStates_Down	= 0x1,
    CoreVirtualKeyStates_Locked = 0x2
    }

.enum CoreAcceleratorKeyEventType {
    CoreAcceleratorKeyEventType_Character	= 2,
    CoreAcceleratorKeyEventType_DeadCharacter	= 3,
    CoreAcceleratorKeyEventType_KeyDown		= 0,
    CoreAcceleratorKeyEventType_KeyUp		= 1,
    CoreAcceleratorKeyEventType_SystemCharacter = 6,
    CoreAcceleratorKeyEventType_SystemDeadCharacter = 7,
    CoreAcceleratorKeyEventType_SystemKeyDown	= 4,
    CoreAcceleratorKeyEventType_SystemKeyUp	= 5,
    CoreAcceleratorKeyEventType_UnicodeCharacter = 8
    }

.enum CoreProximityEvaluationScore {
    CoreProximityEvaluationScore_Closest	= 0,
    CoreProximityEvaluationScore_Farthest	= 2147483647
    }

.enum CoreInputDeviceTypes {
    CoreInputDeviceTypes_None	= 0,
    CoreInputDeviceTypes_Touch	= 0x1,
    CoreInputDeviceTypes_Pen	= 0x2,
    CoreInputDeviceTypes_Mouse	= 0x4
    }

.template CorePhysicalKeyStatus
    RepeatCount		 UINT32 ?
    ScanCode		 UINT32 ?
    IsExtendedKey	 boolean ?
    IsMenuKeyDown	 boolean ?
    WasKeyDown		 boolean ?
    IsKeyReleased	 boolean ?
   .ends


.template CoreProximityEvaluation
    Score		INT32 ?
    AdjustedPoint	INT32 ?
   .ends


ifndef ____x_ABI_CWindows_CUI_CCore_CIDispatchedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIDispatchedHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IDispatchedHandler, "D1F276C4-98D8-4636-BF49-EB79507548E9")

.comdef IDispatchedHandler : public IUnknown

    _Invoke		proc
    .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIIdleDispatchedHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIIdleDispatchedHandler_INTERFACE_DEFINED__

DEFINE_IIDX(IIdleDispatchedHandler, "A42B0C24-7F21-4ABC-99C1-8F01007F0880")

.comdef IIdleDispatchedHandler : public IUnknown

    _Invoke		proc :ptr
    .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowEventArgs <L"Windows.UI.Core.ICoreWindowEventArgs">

DEFINE_IIDX(ICoreWindowEventArgs, "272B1EF3-C633-4DA5-A26C-C6D0F56B29DA")

.comdef ICoreWindowEventArgs : public IInspectable

    get_Handled		proc :ptr
    put_Handled		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIAutomationProviderRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IAutomationProviderRequestedEventArgs <L"Windows.UI.Core.IAutomationProviderRequestedEventArgs">

DEFINE_IIDX(IAutomationProviderRequestedEventArgs, "961FF258-21BF-4B42-A298-FA479D4C52E2")

.comdef IAutomationProviderRequestedEventArgs : public IInspectable

    get_AutomationProvider proc :ptr
    put_AutomationProvider proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICharacterReceivedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICharacterReceivedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICharacterReceivedEventArgs <L"Windows.UI.Core.ICharacterReceivedEventArgs">

DEFINE_IIDX(ICharacterReceivedEventArgs, "C584659F-99B2-4BCC-BD33-04E63F42902E")

.comdef ICharacterReceivedEventArgs : public IInspectable

    get_KeyCode		proc :ptr
    get_KeyStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIInputEnabledEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIInputEnabledEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IInputEnabledEventArgs <L"Windows.UI.Core.IInputEnabledEventArgs">

DEFINE_IIDX(IInputEnabledEventArgs, "80371D4F-2FD8-4C24-AA86-3163A87B4E5A")

.comdef IInputEnabledEventArgs : public IInspectable

    get_InputEnabled	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIKeyEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIKeyEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IKeyEventArgs <L"Windows.UI.Core.IKeyEventArgs">

DEFINE_IIDX(IKeyEventArgs, "5FF5E930-2544-4A17-BD78-1F2FDEBB106B")

.comdef IKeyEventArgs : public IInspectable

    get_VirtualKey	proc :ptr
    get_KeyStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIPointerEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIPointerEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IPointerEventArgs <L"Windows.UI.Core.IPointerEventArgs">

DEFINE_IIDX(IPointerEventArgs, "920D9CB1-A5FC-4A21-8C09-49DFE6FFE25F")

.comdef IPointerEventArgs : public IInspectable

    get_CurrentPoint	proc :ptr
    get_KeyModifiers	proc :ptr
    GetIntermediatePoints proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CITouchHitTestingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CITouchHitTestingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ITouchHitTestingEventArgs <L"Windows.UI.Core.ITouchHitTestingEventArgs">

DEFINE_IIDX(ITouchHitTestingEventArgs, "22F3B823-0B7C-424E-9DF7-33D4F962931B")

.comdef ITouchHitTestingEventArgs : public IInspectable

    get_ProximityEvaluation proc :ptr
    put_ProximityEvaluation proc :INT32
    get_Point		proc :ptr
    get_BoundingBox	proc :ptr
    EvaluateProximityToRect proc :ptr, :ptr
    EvaluateProximityToPolygon proc :UINT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIWindowActivatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIWindowActivatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IWindowActivatedEventArgs <L"Windows.UI.Core.IWindowActivatedEventArgs">

DEFINE_IIDX(IWindowActivatedEventArgs, "179D65E7-4658-4CB6-AA13-41D094EA255E")

.comdef IWindowActivatedEventArgs : public IInspectable

    get_WindowActivationState proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIWindowSizeChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIWindowSizeChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IWindowSizeChangedEventArgs <L"Windows.UI.Core.IWindowSizeChangedEventArgs">

DEFINE_IIDX(IWindowSizeChangedEventArgs, "5A200EC7-0426-47DC-B86C-6F475915E451")

.comdef IWindowSizeChangedEventArgs : public IInspectable

    get_Size		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIVisibilityChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIVisibilityChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IVisibilityChangedEventArgs <L"Windows.UI.Core.IVisibilityChangedEventArgs">

DEFINE_IIDX(IVisibilityChangedEventArgs, "BF9918EA-D801-4564-A495-B1E84F8AD085")

.comdef IVisibilityChangedEventArgs : public IInspectable

    get_Visible		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindow <L"Windows.UI.Core.ICoreWindow">

DEFINE_IIDX(ICoreWindow, "79B9D5F2-879E-4B89-B798-79E47598030C")

.comdef ICoreWindow : public IInspectable

    get_AutomationHostProvider proc :ptr
    get_Bounds		proc :ptr
    get_CustomProperties proc :ptr
    get_Dispatcher	proc :ptr
    get_FlowDirection	proc :ptr
    put_FlowDirection	proc :INT32
    get_IsInputEnabled	proc :ptr
    put_IsInputEnabled	proc :boolean
    get_PointerCursor	proc :ptr
    put_PointerCursor	proc :ptr
    get_PointerPosition proc :ptr
    get_Visible		proc :ptr
    Activate		proc
    Close		proc
    GetAsyncKeyState	proc :INT32, :ptr
    GetKeyState		proc :INT32, :ptr
    ReleasePointerCapture proc
    SetPointerCapture	proc
    add_Activated	proc :ptr, :ptr
    remove_Activated	proc :EventRegistrationToken
    add_AutomationProviderRequested proc :ptr, :ptr
    remove_AutomationProviderRequested proc :EventRegistrationToken
    add_CharacterReceived proc :ptr, :ptr
    remove_CharacterReceived proc :EventRegistrationToken
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
    add_InputEnabled	proc :ptr, :ptr
    remove_InputEnabled proc :EventRegistrationToken
    add_KeyDown		proc :ptr, :ptr
    remove_KeyDown	proc :EventRegistrationToken
    add_KeyUp		proc :ptr, :ptr
    remove_KeyUp	proc :EventRegistrationToken
    add_PointerCaptureLost proc :ptr, :ptr
    remove_PointerCaptureLost proc :EventRegistrationToken
    add_PointerEntered	proc :ptr, :ptr
    remove_PointerEntered proc :EventRegistrationToken
    add_PointerExited	proc :ptr, :ptr
    remove_PointerExited proc :EventRegistrationToken
    add_PointerMoved	proc :ptr, :ptr
    remove_PointerMoved proc :EventRegistrationToken
    add_PointerPressed	proc :ptr, :ptr
    remove_PointerPressed proc :EventRegistrationToken
    add_PointerReleased proc :ptr, :ptr
    remove_PointerReleased proc :EventRegistrationToken
    add_TouchHitTesting proc :ptr, :ptr
    remove_TouchHitTesting proc :EventRegistrationToken
    add_PointerWheelChanged proc :ptr, :ptr
    remove_PointerWheelChanged proc :EventRegistrationToken
    add_SizeChanged	proc :ptr, :ptr
    remove_SizeChanged	proc :EventRegistrationToken
    add_VisibilityChanged proc :ptr, :ptr
    remove_VisibilityChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowStatic_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowStatic_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowStatic <L"Windows.UI.Core.ICoreWindowStatic">

DEFINE_IIDX(ICoreWindowStatic, "4D239005-3C2A-41B1-9022-536BB9CF93B1")

.comdef ICoreWindowStatic : public IInspectable

    GetForCurrentThread proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIAcceleratorKeyEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIAcceleratorKeyEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IAcceleratorKeyEventArgs <L"Windows.UI.Core.IAcceleratorKeyEventArgs">

DEFINE_IIDX(IAcceleratorKeyEventArgs, "FF1C4C4A-9287-470B-836E-9086E3126ADE")

.comdef IAcceleratorKeyEventArgs : public IInspectable

    get_EventType	proc :ptr
    get_VirtualKey	proc :ptr
    get_KeyStatus	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreAcceleratorKeys_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreAcceleratorKeys_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreAcceleratorKeys <L"Windows.UI.Core.ICoreAcceleratorKeys">

DEFINE_IIDX(ICoreAcceleratorKeys, "9FFDF7F5-B8C9-4EF0-B7D2-1DE626561FC8")

.comdef ICoreAcceleratorKeys : public IInspectable

    add_AcceleratorKeyActivated proc :ptr, :ptr
    remove_AcceleratorKeyActivated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreDispatcher_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreDispatcher_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreDispatcher <L"Windows.UI.Core.ICoreDispatcher">

DEFINE_IIDX(ICoreDispatcher, "60DB2FA8-B705-4FDE-A7D6-EBBB1891D39E")

.comdef ICoreDispatcher : public IInspectable

    get_HasThreadAccess proc :ptr
    ProcessEvents	proc :INT32
    RunAsync		proc :INT32, :ptr, :ptr
    RunIdleAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreDispatcherWithTaskPriority_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreDispatcherWithTaskPriority_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreDispatcherWithTaskPriority <L"Windows.UI.Core.ICoreDispatcherWithTaskPriority">

DEFINE_IIDX(ICoreDispatcherWithTaskPriority, "BAFAECAD-484D-41BE-BA80-1D58C65263EA")

.comdef ICoreDispatcherWithTaskPriority : public IInspectable

    get_CurrentPriority proc :ptr
    put_CurrentPriority proc :INT32
    ShouldYield		proc :ptr
    ShouldYieldToPriority proc :INT32, :ptr
    StopProcessEvents	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIIdleDispatchedHandlerArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIIdleDispatchedHandlerArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IIdleDispatchedHandlerArgs <L"Windows.UI.Core.IIdleDispatchedHandlerArgs">

DEFINE_IIDX(IIdleDispatchedHandlerArgs, "98BB6A24-DC1C-43CB-B4ED-D1C0EB2391F3")

.comdef IIdleDispatchedHandlerArgs : public IInspectable

    get_IsDispatcherIdle proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreCursor_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreCursor_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreCursor <L"Windows.UI.Core.ICoreCursor">

DEFINE_IIDX(ICoreCursor, "96893ACF-111D-442C-8A77-B87992F8E2D6")

.comdef ICoreCursor : public IInspectable

    get_Id		proc :ptr
    get_Type		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreCursorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreCursorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreCursorFactory <L"Windows.UI.Core.ICoreCursorFactory">

DEFINE_IIDX(ICoreCursorFactory, "F6359621-A79D-4ED3-8C32-A9EF9D6B76A4")

.comdef ICoreCursorFactory : public IInspectable

    CreateCursor	proc :INT32, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CIInitializeWithCoreWindow_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CIInitializeWithCoreWindow_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_IInitializeWithCoreWindow <L"Windows.UI.Core.IInitializeWithCoreWindow">

DEFINE_IIDX(IInitializeWithCoreWindow, "188F20D6-9873-464A-ACE5-57E010F465E6")

.comdef IInitializeWithCoreWindow : public IInspectable

    Initialize		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowResizeManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowResizeManager_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowResizeManager <L"Windows.UI.Core.ICoreWindowResizeManager">

DEFINE_IIDX(ICoreWindowResizeManager, "B8F0B925-B350-48B3-A198-5C1A84700243")

.comdef ICoreWindowResizeManager : public IInspectable

    NotifyLayoutCompleted proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowResizeManagerLayoutCapability_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowResizeManagerLayoutCapability_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowResizeManagerLayoutCapability <L"Windows.UI.Core.ICoreWindowResizeManagerLayoutCapability">

DEFINE_IIDX(ICoreWindowResizeManagerLayoutCapability, "BB74F27B-A544-4301-80E6-0AE033EF4536")

.comdef ICoreWindowResizeManagerLayoutCapability : public IInspectable

    put_ShouldWaitForLayoutCompletion proc :boolean
    get_ShouldWaitForLayoutCompletion proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowResizeManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowResizeManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowResizeManagerStatics <L"Windows.UI.Core.ICoreWindowResizeManagerStatics">

DEFINE_IIDX(ICoreWindowResizeManagerStatics, "AE4A9045-6D70-49DB-8E68-46FFBD17D38D")

.comdef ICoreWindowResizeManagerStatics : public IInspectable

    GetForCurrentView	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreInputSourceBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreInputSourceBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreInputSourceBase <L"Windows.UI.Core.ICoreInputSourceBase">

DEFINE_IIDX(ICoreInputSourceBase, "9F488807-4580-4BE8-BE68-92A9311713BB")

.comdef ICoreInputSourceBase : public IInspectable

    get_Dispatcher	proc :ptr
    get_IsInputEnabled	proc :ptr
    put_IsInputEnabled	proc :boolean
    add_InputEnabled	proc :ptr, :ptr
    remove_InputEnabled proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICorePointerInputSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICorePointerInputSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICorePointerInputSource <L"Windows.UI.Core.ICorePointerInputSource">

DEFINE_IIDX(ICorePointerInputSource, "BBF1BB18-E47A-48EB-8807-F8F8D3EA4551")

.comdef ICorePointerInputSource : public IInspectable

    ReleasePointerCapture proc
    SetPointerCapture	proc
    get_HasCapture	proc :ptr
    get_PointerPosition proc :ptr
    get_PointerCursor	proc :ptr
    put_PointerCursor	proc :ptr
    add_PointerCaptureLost proc :ptr, :ptr
    remove_PointerCaptureLost proc :EventRegistrationToken
    add_PointerEntered	proc :ptr, :ptr
    remove_PointerEntered proc :EventRegistrationToken
    add_PointerExited	proc :ptr, :ptr
    remove_PointerExited proc :EventRegistrationToken
    add_PointerMoved	proc :ptr, :ptr
    remove_PointerMoved proc :EventRegistrationToken
    add_PointerPressed	proc :ptr, :ptr
    remove_PointerPressed proc :EventRegistrationToken
    add_PointerReleased proc :ptr, :ptr
    remove_PointerReleased proc :EventRegistrationToken
    add_PointerWheelChanged proc :ptr, :ptr
    remove_PointerWheelChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreKeyboardInputSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreKeyboardInputSource_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreKeyboardInputSource <L"Windows.UI.Core.ICoreKeyboardInputSource">

DEFINE_IIDX(ICoreKeyboardInputSource, "231C9088-E469-4DF1-B208-6E490D71CB90")

.comdef ICoreKeyboardInputSource : public IInspectable

    GetCurrentKeyState	proc :INT32, :ptr
    add_CharacterReceived proc :ptr, :ptr
    remove_CharacterReceived proc :EventRegistrationToken
    add_KeyDown		proc :ptr, :ptr
    remove_KeyDown	proc :EventRegistrationToken
    add_KeyUp		proc :ptr, :ptr
    remove_KeyUp	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreComponentFocusable_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreComponentFocusable_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreComponentFocusable <L"Windows.UI.Core.ICoreComponentFocusable">

DEFINE_IIDX(ICoreComponentFocusable, "52F96FA3-8742-4411-AE69-79A85F29AC8B")

.comdef ICoreComponentFocusable : public IInspectable

    get_HasFocus	proc :ptr
    add_GotFocus	proc :ptr, :ptr
    remove_GotFocus	proc :EventRegistrationToken
    add_LostFocus	proc :ptr, :ptr
    remove_LostFocus	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreTouchHitTesting_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreTouchHitTesting_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreTouchHitTesting <L"Windows.UI.Core.ICoreTouchHitTesting">

DEFINE_IIDX(ICoreTouchHitTesting, "B1D8A289-3ACF-4124-9FA3-EA8ABA353C21")

.comdef ICoreTouchHitTesting : public IInspectable

    add_TouchHitTesting proc :ptr, :ptr
    remove_TouchHitTesting proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowPopupShowingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowPopupShowingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowPopupShowingEventArgs <L"Windows.UI.Core.ICoreWindowPopupShowingEventArgs">

DEFINE_IIDX(ICoreWindowPopupShowingEventArgs, "26155FA2-5BA5-4EA4-A3B4-2DC7D63C8E26")

.comdef ICoreWindowPopupShowingEventArgs : public IInspectable

    SetDesiredSize	proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowDialog_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowDialog_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowDialog <L"Windows.UI.Core.ICoreWindowDialog">

DEFINE_IIDX(ICoreWindowDialog, "E7392CE0-C78D-427E-8B2C-01FF420C69D5")

.comdef ICoreWindowDialog : public IInspectable

    add_Showing		proc :ptr, :ptr
    remove_Showing	proc :EventRegistrationToken
    get_MaxSize		proc :ptr
    get_MinSize		proc :ptr
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_IsInteractionDelayed proc :ptr
    put_IsInteractionDelayed proc :INT32
    get_Commands	proc :ptr
    get_DefaultCommandIndex proc :ptr
    put_DefaultCommandIndex proc :UINT32
    get_CancelCommandIndex proc :ptr
    put_CancelCommandIndex proc :UINT32
    get_BackButtonCommand proc :ptr
    put_BackButtonCommand proc :ptr
    ShowAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowDialogFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowDialogFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowDialogFactory <L"Windows.UI.Core.ICoreWindowDialogFactory">

DEFINE_IIDX(ICoreWindowDialogFactory, "CFB2A855-1C59-4B13-B1E5-16E29805F7C4")

.comdef ICoreWindowDialogFactory : public IInspectable

    CreateWithTitle	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowFlyout_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowFlyout_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowFlyout <L"Windows.UI.Core.ICoreWindowFlyout">

DEFINE_IIDX(ICoreWindowFlyout, "E89D854D-2050-40BB-B344-F6F355EEB314")

.comdef ICoreWindowFlyout : public IInspectable

    add_Showing		proc :ptr, :ptr
    remove_Showing	proc :EventRegistrationToken
    get_MaxSize		proc :ptr
    get_MinSize		proc :ptr
    get_Title		proc :ptr
    put_Title		proc :HSTRING
    get_IsInteractionDelayed proc :ptr
    put_IsInteractionDelayed proc :INT32
    get_Commands	proc :ptr
    get_DefaultCommandIndex proc :ptr
    put_DefaultCommandIndex proc :UINT32
    get_BackButtonCommand proc :ptr
    put_BackButtonCommand proc :ptr
    ShowAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CCore_CICoreWindowFlyoutFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CCore_CICoreWindowFlyoutFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Core_ICoreWindowFlyoutFactory <L"Windows.UI.Core.ICoreWindowFlyoutFactory">

DEFINE_IIDX(ICoreWindowFlyoutFactory, "DEC4C6C4-93E8-4F7C-BE27-CEFAA1AF68A7")

.comdef ICoreWindowFlyoutFactory : public IInspectable

    Create		proc :ptr, :ptr
    CreateWithTitle	proc :ptr, :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Core_CoreDispatcher_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreDispatcher_DEFINED
define RuntimeClass_Windows_UI_Core_CoreDispatcher <L"Windows.UI.Core.CoreDispatcher">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreCursor_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreCursor_DEFINED
define RuntimeClass_Windows_UI_Core_CoreCursor <L"Windows.UI.Core.CoreCursor">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreWindow_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreWindow_DEFINED
define RuntimeClass_Windows_UI_Core_CoreWindow <L"Windows.UI.Core.CoreWindow">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_WindowActivatedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_WindowActivatedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_WindowActivatedEventArgs <L"Windows.UI.Core.WindowActivatedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_AutomationProviderRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AutomationProviderRequestedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_AutomationProviderRequestedEventArgs <L"Windows.UI.Core.AutomationProviderRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CharacterReceivedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CharacterReceivedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_CharacterReceivedEventArgs <L"Windows.UI.Core.CharacterReceivedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreWindowEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreWindowEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_CoreWindowEventArgs <L"Windows.UI.Core.CoreWindowEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_InputEnabledEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_InputEnabledEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_InputEnabledEventArgs <L"Windows.UI.Core.InputEnabledEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_KeyEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_KeyEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_KeyEventArgs <L"Windows.UI.Core.KeyEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_PointerEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_PointerEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_PointerEventArgs <L"Windows.UI.Core.PointerEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_TouchHitTestingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_TouchHitTestingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_TouchHitTestingEventArgs <L"Windows.UI.Core.TouchHitTestingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_WindowSizeChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_WindowSizeChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_WindowSizeChangedEventArgs <L"Windows.UI.Core.WindowSizeChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_VisibilityChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_VisibilityChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_VisibilityChangedEventArgs <L"Windows.UI.Core.VisibilityChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_IdleDispatchedHandlerArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_IdleDispatchedHandlerArgs_DEFINED
define RuntimeClass_Windows_UI_Core_IdleDispatchedHandlerArgs <L"Windows.UI.Core.IdleDispatchedHandlerArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_AcceleratorKeyEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_AcceleratorKeyEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_AcceleratorKeyEventArgs <L"Windows.UI.Core.AcceleratorKeyEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreAcceleratorKeys_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreAcceleratorKeys_DEFINED
define RuntimeClass_Windows_UI_Core_CoreAcceleratorKeys <L"Windows.UI.Core.CoreAcceleratorKeys">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreWindowResizeManager_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreWindowResizeManager_DEFINED
define RuntimeClass_Windows_UI_Core_CoreWindowResizeManager <L"Windows.UI.Core.CoreWindowResizeManager">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreIndependentInputSource_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreIndependentInputSource_DEFINED
define RuntimeClass_Windows_UI_Core_CoreIndependentInputSource <L"Windows.UI.Core.CoreIndependentInputSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreComponentInputSource_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreComponentInputSource_DEFINED
define RuntimeClass_Windows_UI_Core_CoreComponentInputSource <L"Windows.UI.Core.CoreComponentInputSource">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreWindowPopupShowingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreWindowPopupShowingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Core_CoreWindowPopupShowingEventArgs <L"Windows.UI.Core.CoreWindowPopupShowingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreWindowDialog_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreWindowDialog_DEFINED
define RuntimeClass_Windows_UI_Core_CoreWindowDialog <L"Windows.UI.Core.CoreWindowDialog">
endif
ifndef RUNTIMECLASS_Windows_UI_Core_CoreWindowFlyout_DEFINED
define RUNTIMECLASS_Windows_UI_Core_CoreWindowFlyout_DEFINED
define RuntimeClass_Windows_UI_Core_CoreWindowFlyout <L"Windows.UI.Core.CoreWindowFlyout">
endif

HSTRING_UserSize	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr ULONG, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr ULONG, :ptr HSTRING

endif
