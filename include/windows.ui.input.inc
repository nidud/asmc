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

ifndef __windows2Eui2Einput_h__
define __windows2Eui2Einput_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Devices.Input.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CUI__CInput__CPointerPoint, "721fe01c-5ad4-5262-b078-3ab345105db8")

.comdef __FIIterator_1_Windows__CUI__CInput__CPointerPoint : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CUI__CInput__CPointerPoint, "f6f2cba6-7076-5b59-9631-f6ac32b57695")

.comdef __FIIterable_1_Windows__CUI__CInput__CPointerPoint : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CInput__CPointerPoint, "f0f57411-7786-5174-8752-4c5e834b6da2")

.comdef __FIVectorView_1_Windows__CUI__CInput__CPointerPoint : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CInput__CPointerPoint_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVector_1_Windows__CUI__CInput__CPointerPoint, "dfa655cf-fde7-5048-b4bf-c909231b7edb")

.comdef __FIVector_1_Windows__CUI__CInput__CPointerPoint : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    GetView		proc :ptr
    IndexOf		proc :ptr, :UINT, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :UINT
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CEdgeGesture_Windows__CUI__CInput__CEdgeGestureEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CEdgeGesture_Windows__CUI__CInput__CEdgeGestureEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CEdgeGesture_Windows__CUI__CInput__CEdgeGestureEventArgs, "b62d7f11-c7b1-5bf0-a347-3366252db4ce")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CEdgeGesture_Windows__CUI__CInput__CEdgeGestureEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CCrossSlidingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CCrossSlidingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CCrossSlidingEventArgs, "1fc1eb70-0c26-5cf0-9e50-843a34083613")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CCrossSlidingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CDraggingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CDraggingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CDraggingEventArgs, "be7cca42-98dd-5d72-9e91-976113d7985e")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CDraggingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CHoldingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CHoldingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CHoldingEventArgs, "0027bdf5-6948-53f7-afbe-d4d8fe500feb")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CHoldingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationCompletedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationCompletedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationCompletedEventArgs, "c24f5605-3059-52cc-bdf3-7098146d34d7")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationCompletedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationInertiaStartingEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationInertiaStartingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationInertiaStartingEventArgs, "350a72ab-34a5-5193-913d-3d4c5983842c")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationInertiaStartingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationStartedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationStartedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationStartedEventArgs, "110d75c8-ba5e-5462-8b2d-4a1582574b61")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationStartedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationUpdatedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationUpdatedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationUpdatedEventArgs, "eb5216f5-020a-5e40-9c4b-48912c690e2d")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CManipulationUpdatedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CRightTappedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CRightTappedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CRightTappedEventArgs, "8420d242-ba34-5b17-92f3-8f767f1d0de4")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CRightTappedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CTappedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CTappedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CTappedEventArgs, "27f3ad57-8994-5712-8b83-a93ba17c03c2")

.comdef __FITypedEventHandler_2_Windows__CUI__CInput__CGestureRecognizer_Windows__CUI__CInput__CTappedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace ABI
.namespace Windows
.namespace UI
.namespace Input

define InterfaceName_Windows_UI_Input_IEdgeGestureEventArgs <L"Windows.UI.Input.IEdgeGestureEventArgs">

.enum EdgeGestureKind {
    EdgeGestureKind_Touch,
    EdgeGestureKind_Keyboard,
    EdgeGestureKind_Mouse
    }

.enum HoldingState {
    HoldingState_Started,
    HoldingState_Completed,
    HoldingState_Canceled
    }

.enum DraggingState {
    DraggingState_Started,
    DraggingState_Continuing,
    DraggingState_Completed
    }

.enum CrossSlidingState {
    CrossSlidingState_Started,
    CrossSlidingState_Dragging,
    CrossSlidingState_Selecting,
    CrossSlidingState_SelectSpeedBumping,
    CrossSlidingState_SpeedBumping,
    CrossSlidingState_Rearranging,
    CrossSlidingState_Completed
    }

.enum GestureSettings {
    GestureSettings_None	= 0,
    GestureSettings_Tap		= 0x1,
    GestureSettings_DoubleTap	= 0x2,
    GestureSettings_Hold	= 0x4,
    GestureSettings_HoldWithMouse = 0x8,
    GestureSettings_RightTap	= 0x10,
    GestureSettings_Drag	= 0x20,
    GestureSettings_ManipulationTranslateX	= 0x40,
    GestureSettings_ManipulationTranslateY	= 0x80,
    GestureSettings_ManipulationTranslateRailsX = 0x100,
    GestureSettings_ManipulationTranslateRailsY = 0x200,
    GestureSettings_ManipulationRotate	= 0x400,
    GestureSettings_ManipulationScale	= 0x800,
    GestureSettings_ManipulationTranslateInertia	= 0x1000,
    GestureSettings_ManipulationRotateInertia	= 0x2000,
    GestureSettings_ManipulationScaleInertia	= 0x4000,
    GestureSettings_CrossSlide	= 0x8000,
    GestureSettings_ManipulationMultipleFingerPanning	= 0x10000
    }

.enum PointerUpdateKind {
    PointerUpdateKind_Other,
    PointerUpdateKind_LeftButtonPressed,
    PointerUpdateKind_LeftButtonReleased,
    PointerUpdateKind_RightButtonPressed,
    PointerUpdateKind_RightButtonReleased,
    PointerUpdateKind_MiddleButtonPressed,
    PointerUpdateKind_MiddleButtonReleased,
    PointerUpdateKind_XButton1Pressed,
    PointerUpdateKind_XButton1Released,
    PointerUpdateKind_XButton2Pressed,
    PointerUpdateKind_XButton2Released
    }

.template ManipulationDelta
    Translation		real4 2 dup(?);ABI::Windows::Foundation::Point ?
    Scale		real4 ?
    Rotation		real4 ?
    Expansion		real4 ?
   .ends

.template ManipulationVelocities
    Linear		real4 2 dup(?);ABI::Windows::Foundation::Point ?
    Angular		real4 ?
    Expansion		real4 ?
   .ends

.template CrossSlideThresholds
    SelectionStart	real4 ?
    SpeedBumpStart	real4 ?
    SpeedBumpEnd	real4 ?
    RearrangeStart	real4 ?
   .ends


ifndef ____x_ABI_CWindows_CUI_CInput_CIEdgeGestureEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIEdgeGestureEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(IEdgeGestureEventArgs, "44FA4A24-2D09-42E1-8B5E-368208796A4C")

.comdef IEdgeGestureEventArgs : public IInspectable

    get_Kind		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIEdgeGestureStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIEdgeGestureStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IEdgeGestureStatics <L"Windows.UI.Input.IEdgeGestureStatics">

DEFINE_IIDX(IEdgeGestureStatics, "BC6A8519-18EE-4043-9839-4FC584D60A14")

.comdef IEdgeGestureStatics : public IInspectable

    GetForCurrentView	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIEdgeGesture_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIEdgeGesture_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IEdgeGesture <L"Windows.UI.Input.IEdgeGesture">

DEFINE_IIDX(IEdgeGesture, "580D5292-2AB1-49AA-A7F0-33BD3F8DF9F1")

.comdef IEdgeGesture : public IInspectable

    add_Starting	proc :ptr, :ptr
    remove_Starting	proc :EventRegistrationToken
    add_Completed	proc :ptr, :ptr
    remove_Completed	proc :EventRegistrationToken
    add_Canceled	proc :ptr, :ptr
    remove_Canceled	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CITappedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CITappedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_ITappedEventArgs <L"Windows.UI.Input.ITappedEventArgs">

DEFINE_IIDX(ITappedEventArgs, "CFA126E4-253A-4C3C-953B-395C37AED309")

.comdef ITappedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_TapCount	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIRightTappedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIRightTappedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IRightTappedEventArgs <L"Windows.UI.Input.IRightTappedEventArgs">

DEFINE_IIDX(IRightTappedEventArgs, "4CBF40BD-AF7A-4A36-9476-B1DCE141709A")

.comdef IRightTappedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIHoldingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIHoldingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IHoldingEventArgs <L"Windows.UI.Input.IHoldingEventArgs">

DEFINE_IIDX(IHoldingEventArgs, "2BF755C5-E799-41B4-BB40-242F40959B71")

.comdef IHoldingEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_HoldingState	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIDraggingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIDraggingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IDraggingEventArgs <L"Windows.UI.Input.IDraggingEventArgs">

DEFINE_IIDX(IDraggingEventArgs, "1C905384-083C-4BD3-B559-179CDDEB33EC")

.comdef IDraggingEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_DraggingState	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIManipulationStartedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIManipulationStartedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IManipulationStartedEventArgs <L"Windows.UI.Input.IManipulationStartedEventArgs">

DEFINE_IIDX(IManipulationStartedEventArgs, "DDEC873E-CFCE-4932-8C1D-3C3D011A34C0")

.comdef IManipulationStartedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_Cumulative	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIManipulationUpdatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIManipulationUpdatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IManipulationUpdatedEventArgs <L"Windows.UI.Input.IManipulationUpdatedEventArgs">

DEFINE_IIDX(IManipulationUpdatedEventArgs, "CB354CE5-ABB8-4F9F-B3CE-8181AA61AD82")

.comdef IManipulationUpdatedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_Delta		proc :ptr
    get_Cumulative	proc :ptr
    get_Velocities	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIManipulationInertiaStartingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIManipulationInertiaStartingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IManipulationInertiaStartingEventArgs <L"Windows.UI.Input.IManipulationInertiaStartingEventArgs">

DEFINE_IIDX(IManipulationInertiaStartingEventArgs, "DD37A898-26BF-467A-9CE5-CCF3FB11371E")

.comdef IManipulationInertiaStartingEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_Delta		proc :ptr
    get_Cumulative	proc :ptr
    get_Velocities	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIManipulationCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIManipulationCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IManipulationCompletedEventArgs <L"Windows.UI.Input.IManipulationCompletedEventArgs">

DEFINE_IIDX(IManipulationCompletedEventArgs, "B34AB22B-D19B-46FF-9F38-DEC7754BB9E7")

.comdef IManipulationCompletedEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_Cumulative	proc :ptr
    get_Velocities	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CICrossSlidingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CICrossSlidingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_ICrossSlidingEventArgs <L"Windows.UI.Input.ICrossSlidingEventArgs">

DEFINE_IIDX(ICrossSlidingEventArgs, "E9374738-6F88-41D9-8720-78E08E398349")

.comdef ICrossSlidingEventArgs : public IInspectable

    get_PointerDeviceType proc :ptr
    get_Position	proc :ptr
    get_CrossSlidingState proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIMouseWheelParameters_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIMouseWheelParameters_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IMouseWheelParameters <L"Windows.UI.Input.IMouseWheelParameters">

DEFINE_IIDX(IMouseWheelParameters, "EAD0CA44-9DED-4037-8149-5E4CC2564468")

.comdef IMouseWheelParameters : public IInspectable

    get_CharTranslation proc :ptr
    put_CharTranslation proc :ptr
    get_DeltaScale	proc :ptr
    put_DeltaScale	proc :FLOAT
    get_DeltaRotationAngle proc :ptr
    put_DeltaRotationAngle proc :FLOAT
    get_PageTranslation proc :ptr
    put_PageTranslation proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIGestureRecognizer_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIGestureRecognizer_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IGestureRecognizer <L"Windows.UI.Input.IGestureRecognizer">

DEFINE_IIDX(IGestureRecognizer, "B47A37BF-3D6B-4F88-83E8-6DCB4012FFB0")

.comdef IGestureRecognizer : public IInspectable

    get_GestureSettings proc :ptr
    put_GestureSettings proc :ptr
    get_IsInertial	proc :ptr
    get_IsActive	proc :ptr
    get_ShowGestureFeedback proc :ptr
    put_ShowGestureFeedback proc :boolean
    get_PivotCenter	proc :ptr
    put_PivotCenter	proc :ptr
    get_PivotRadius	proc :ptr
    put_PivotRadius	proc :FLOAT
    get_InertiaTranslationDeceleration proc :ptr
    put_InertiaTranslationDeceleration proc :FLOAT
    get_InertiaRotationDeceleration proc :ptr
    put_InertiaRotationDeceleration proc :FLOAT
    get_InertiaExpansionDeceleration proc :ptr
    put_InertiaExpansionDeceleration proc :FLOAT
    get_InertiaTranslationDisplacement proc :ptr
    put_InertiaTranslationDisplacement proc :FLOAT
    get_InertiaRotationAngle proc :ptr
    put_InertiaRotationAngle proc :FLOAT
    get_InertiaExpansion proc :ptr
    put_InertiaExpansion proc :FLOAT
    get_ManipulationExact proc :ptr
    put_ManipulationExact proc :boolean
    get_CrossSlideThresholds proc :ptr
    put_CrossSlideThresholds proc :ptr
    get_CrossSlideHorizontally proc :ptr
    put_CrossSlideHorizontally proc :boolean
    get_CrossSlideExact proc :ptr
    put_CrossSlideExact proc :boolean
    get_AutoProcessInertia proc :ptr
    put_AutoProcessInertia proc :boolean
    get_MouseWheelParameters proc :ptr
    CanBeDoubleTap	proc :ptr, :ptr
    ProcessDownEvent	proc :ptr
    ProcessMoveEvents	proc :ptr
    ProcessUpEvent	proc :ptr
    ProcessMouseWheelEvent proc :ptr, :boolean, :boolean
    ProcessInertia	proc
    CompleteGesture	proc
    add_Tapped		proc :ptr, :ptr
    remove_Tapped	proc :EventRegistrationToken
    add_RightTapped	proc :ptr, :ptr
    remove_RightTapped	proc :EventRegistrationToken
    add_Holding		proc :ptr, :ptr
    remove_Holding	proc :EventRegistrationToken
    add_Dragging	proc :ptr, :ptr
    remove_Dragging	proc :EventRegistrationToken
    add_ManipulationStarted proc :ptr, :ptr
    remove_ManipulationStarted proc :EventRegistrationToken
    add_ManipulationUpdated proc :ptr, :ptr
    remove_ManipulationUpdated proc :EventRegistrationToken
    add_ManipulationInertiaStarting proc :ptr, :ptr
    remove_ManipulationInertiaStarting proc :EventRegistrationToken
    add_ManipulationCompleted proc :ptr, :ptr
    remove_ManipulationCompleted proc :EventRegistrationToken
    add_CrossSliding	proc :ptr, :ptr
    remove_CrossSliding proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIPointerPointStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIPointerPointStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IPointerPointStatics <L"Windows.UI.Input.IPointerPointStatics">

DEFINE_IIDX(IPointerPointStatics, "A506638D-2A1A-413E-BC75-9F38381CC069")

.comdef IPointerPointStatics : public IInspectable

    GetCurrentPoint	proc :UINT32, :ptr
    GetIntermediatePoints proc :UINT32, :ptr
    GetCurrentPointTransformed proc :UINT32, :ptr, :ptr
    GetIntermediatePointsTransformed proc :UINT32, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIPointerPointTransform_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIPointerPointTransform_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IPointerPointTransform <L"Windows.UI.Input.IPointerPointTransform">

DEFINE_IIDX(IPointerPointTransform, "4D5FE14F-B87C-4028-BC9C-59E9947FB056")

.comdef IPointerPointTransform : public IInspectable

    get_Inverse		proc :ptr
    TryTransform	proc :ptr, :ptr, :ptr
    TransformBounds	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIPointerPoint_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIPointerPoint_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IPointerPoint <L"Windows.UI.Input.IPointerPoint">

DEFINE_IIDX(IPointerPoint, "E995317D-7296-42D9-8233-C5BE73B74A4A")

.comdef IPointerPoint : public IInspectable

    get_PointerDevice	proc :ptr
    get_Position	proc :ptr
    get_RawPosition	proc :ptr
    get_PointerId	proc :ptr
    get_FrameId		proc :ptr
    get_Timestamp	proc :ptr
    get_IsInContact	proc :ptr
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIPointerPointProperties_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIPointerPointProperties_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IPointerPointProperties <L"Windows.UI.Input.IPointerPointProperties">

DEFINE_IIDX(IPointerPointProperties, "C79D8A4B-C163-4EE7-803F-67CE79F9972D")

.comdef IPointerPointProperties : public IInspectable

    get_Pressure	proc :ptr
    get_IsInverted	proc :ptr
    get_IsEraser	proc :ptr
    get_Orientation	proc :ptr
    get_XTilt		proc :ptr
    get_YTilt		proc :ptr
    get_Twist		proc :ptr
    get_ContactRect	proc :ptr
    get_ContactRectRaw	proc :ptr
    get_TouchConfidence proc :ptr
    get_IsLeftButtonPressed proc :ptr
    get_IsRightButtonPressed proc :ptr
    get_IsMiddleButtonPressed proc :ptr
    get_MouseWheelDelta proc :ptr
    get_IsHorizontalMouseWheel proc :ptr
    get_IsPrimary	proc :ptr
    get_IsInRange	proc :ptr
    get_IsCanceled	proc :ptr
    get_IsBarrelButtonPressed proc :ptr
    get_IsXButton1Pressed proc :ptr
    get_IsXButton2Pressed proc :ptr
    get_PointerUpdateKind proc :ptr
    HasUsage		proc :UINT32, :UINT32, :ptr
    GetUsageValue	proc :UINT32, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIPointerVisualizationSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIPointerVisualizationSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IPointerVisualizationSettings <L"Windows.UI.Input.IPointerVisualizationSettings">

DEFINE_IIDX(IPointerVisualizationSettings, "4D1E6461-84F7-499D-BD91-2A36E2B7AAA2")

.comdef IPointerVisualizationSettings : public IInspectable

    put_IsContactFeedbackEnabled proc :boolean
    get_IsContactFeedbackEnabled proc :ptr
    put_IsBarrelButtonFeedbackEnabled proc :boolean
    get_IsBarrelButtonFeedbackEnabled proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CInput_CIPointerVisualizationSettingsStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CInput_CIPointerVisualizationSettingsStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Input_IPointerVisualizationSettingsStatics <L"Windows.UI.Input.IPointerVisualizationSettingsStatics">

DEFINE_IIDX(IPointerVisualizationSettingsStatics, "68870EDB-165B-4214-B4F3-584ECA8C8A69")

.comdef IPointerVisualizationSettingsStatics : public IInspectable

    GetForCurrentView	proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Input_EdgeGestureEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_EdgeGestureEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_EdgeGestureEventArgs <L"Windows.UI.Input.EdgeGestureEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_EdgeGesture_DEFINED
define RUNTIMECLASS_Windows_UI_Input_EdgeGesture_DEFINED
define RuntimeClass_Windows_UI_Input_EdgeGesture <L"Windows.UI.Input.EdgeGesture">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_MouseWheelParameters_DEFINED
define RUNTIMECLASS_Windows_UI_Input_MouseWheelParameters_DEFINED
define RuntimeClass_Windows_UI_Input_MouseWheelParameters <L"Windows.UI.Input.MouseWheelParameters">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_GestureRecognizer_DEFINED
define RUNTIMECLASS_Windows_UI_Input_GestureRecognizer_DEFINED
define RuntimeClass_Windows_UI_Input_GestureRecognizer <L"Windows.UI.Input.GestureRecognizer">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_TappedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_TappedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_TappedEventArgs <L"Windows.UI.Input.TappedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_RightTappedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_RightTappedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_RightTappedEventArgs <L"Windows.UI.Input.RightTappedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_HoldingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_HoldingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_HoldingEventArgs <L"Windows.UI.Input.HoldingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_DraggingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_DraggingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_DraggingEventArgs <L"Windows.UI.Input.DraggingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_ManipulationStartedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_ManipulationStartedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_ManipulationStartedEventArgs <L"Windows.UI.Input.ManipulationStartedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_ManipulationUpdatedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_ManipulationUpdatedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_ManipulationUpdatedEventArgs <L"Windows.UI.Input.ManipulationUpdatedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_ManipulationInertiaStartingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_ManipulationInertiaStartingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_ManipulationInertiaStartingEventArgs <L"Windows.UI.Input.ManipulationInertiaStartingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_ManipulationCompletedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_ManipulationCompletedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_ManipulationCompletedEventArgs <L"Windows.UI.Input.ManipulationCompletedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_CrossSlidingEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Input_CrossSlidingEventArgs_DEFINED
define RuntimeClass_Windows_UI_Input_CrossSlidingEventArgs <L"Windows.UI.Input.CrossSlidingEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_PointerPoint_DEFINED
define RUNTIMECLASS_Windows_UI_Input_PointerPoint_DEFINED
define RuntimeClass_Windows_UI_Input_PointerPoint <L"Windows.UI.Input.PointerPoint">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_PointerPointProperties_DEFINED
define RUNTIMECLASS_Windows_UI_Input_PointerPointProperties_DEFINED
define RuntimeClass_Windows_UI_Input_PointerPointProperties <L"Windows.UI.Input.PointerPointProperties">
endif
ifndef RUNTIMECLASS_Windows_UI_Input_PointerVisualizationSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Input_PointerVisualizationSettings_DEFINED
define RuntimeClass_Windows_UI_Input_PointerVisualizationSettings <L"Windows.UI.Input.PointerVisualizationSettings">
endif

endif

