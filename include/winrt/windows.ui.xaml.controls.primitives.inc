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

ifndef __windows2Eui2Examl2Econtrols2Eprimitives_h__
define __windows2Eui2Examl2Econtrols2Eprimitives_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Controls
.namespace Primitives

.enum GeneratorDirection {
    GeneratorDirection_Forward	= 0,
    GeneratorDirection_Backward = 1
    }

.enum GroupHeaderPlacement {
    GroupHeaderPlacement_Top	= 0,
    GroupHeaderPlacement_Left	= 1
    }

.enum PlacementMode {
    PlacementMode_Bottom	= 2,
    PlacementMode_Left	= 9,
    PlacementMode_Mouse = 7,
    PlacementMode_Right = 4,
    PlacementMode_Top	= 10
    }

.enum ScrollEventType {
    ScrollEventType_SmallDecrement	= 0,
    ScrollEventType_SmallIncrement	= 1,
    ScrollEventType_LargeDecrement	= 2,
    ScrollEventType_LargeIncrement	= 3,
    ScrollEventType_ThumbPosition	= 4,
    ScrollEventType_ThumbTrack	= 5,
    ScrollEventType_First	= 6,
    ScrollEventType_Last	= 7,
    ScrollEventType_EndScroll	= 8
    }

.enum ScrollingIndicatorMode {
    ScrollingIndicatorMode_None = 0,
    ScrollingIndicatorMode_TouchIndicator	= 1,
    ScrollingIndicatorMode_MouseIndicator	= 2
    }

.enum SliderSnapsTo {
    SliderSnapsTo_StepValues	= 0,
    SliderSnapsTo_Ticks = 1
    }

.enum SnapPointsAlignment {
    SnapPointsAlignment_Near	= 0,
    SnapPointsAlignment_Center	= 1,
    SnapPointsAlignment_Far	= 2
    }

.enum TickPlacement {
    TickPlacement_None	= 0,
    TickPlacement_TopLeft	= 1,
    TickPlacement_BottomRight	= 2,
    TickPlacement_Outside	= 3,
    TickPlacement_Inline	= 4
    }

.enum AnimationDirection {
    AnimationDirection_Left	= 0,
    AnimationDirection_Top	= 1,
    AnimationDirection_Right	= 2,
    AnimationDirection_Bottom	= 3
    }

.enum ComponentResourceLocation {
    ComponentResourceLocation_Application	= 0,
    ComponentResourceLocation_Nested	= 1
    }

.enum EdgeTransitionLocation {
    EdgeTransitionLocation_Left = 0,
    EdgeTransitionLocation_Top	= 1,
    EdgeTransitionLocation_Right	= 2,
    EdgeTransitionLocation_Bottom	= 3
    }

.enum FlyoutPlacementMode {
    FlyoutPlacementMode_Top	= 0,
    FlyoutPlacementMode_Bottom	= 1,
    FlyoutPlacementMode_Left	= 2,
    FlyoutPlacementMode_Right	= 3,
    FlyoutPlacementMode_Full	= 4
    }

.template GeneratorPosition
    Index		INT32 ?
    Offs		INT32 ?
   .ends

.endn
.endn
.endn
.endn
.endn

ifndef __windows2Eui2Examl2Econtrols_h__
 include windows.ui.xaml.controls.inc
endif

include Windows.UI.Xaml.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup, "5bcb0970-5472-56e8-b184-d01fb81e408a")

.comdef __FIIterator_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup, "0af05ce9-3b0f-5a6d-a053-d01a1a554f8c")

.comdef __FIIterable_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup, "7d899fb2-4666-5a3e-b36c-9886bcbc4663")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CControls__CPrimitives__CPopup : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Controls
.namespace Primitives

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragCompletedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragCompletedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDragCompletedEventHandler, "36B28888-19AC-4B4E-9137-A6CF2B023883")

.comdef IDragCompletedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragDeltaEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragDeltaEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDragDeltaEventHandler, "4AC24F9F-AC28-49E9-9189-DCCFFEB66472")

.comdef IDragDeltaEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragStartedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragStartedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDragStartedEventHandler, "D2EEA48A-C65A-495D-A2F1-72C66989142D")

.comdef IDragStartedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIItemsChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIItemsChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IItemsChangedEventHandler, "178257BE-A304-482F-8BF0-B9D2E39612A3")

.comdef IItemsChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseValueChangedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseValueChangedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRangeBaseValueChangedEventHandler, "E3906FD9-4D1B-4AC8-A43C-C3B908742799")

.comdef IRangeBaseValueChangedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IScrollEventHandler, "8860B0A4-A383-4C83-B306-A1C39D7DB87F")

.comdef IScrollEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIButtonBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIButtonBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IButtonBase <L"Windows.UI.Xaml.Controls.Primitives.IButtonBase">
DEFINE_IIDX(IButtonBase, "FA002C1A-494E-46CF-91D4-E14A8D798674")

.comdef IButtonBase : public IInspectable

    get_ClickMode	proc :ptr
    put_ClickMode	proc :Windows::UI::Xaml::Controls::ClickMode
    get_IsPointerOver	proc :ptr
    get_IsPressed	proc :ptr
    get_Command		proc :ptr
    put_Command		proc :ptr
    get_CommandParameter proc :ptr
    put_CommandParameter proc :ptr
    add_Click		proc :ptr, :ptr
    remove_Click	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIButtonBaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIButtonBaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IButtonBaseStatics <L"Windows.UI.Xaml.Controls.Primitives.IButtonBaseStatics">
DEFINE_IIDX(IButtonBaseStatics, "67EF17E1-FE37-474F-9E97-3B5E0B30F2DF")

.comdef IButtonBaseStatics : public IInspectable

    get_ClickModeProperty proc :ptr
    get_IsPointerOverProperty proc :ptr
    get_IsPressedProperty proc :ptr
    get_CommandProperty proc :ptr
    get_CommandParameterProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIButtonBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIButtonBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IButtonBaseFactory <L"Windows.UI.Xaml.Controls.Primitives.IButtonBaseFactory">
DEFINE_IIDX(IButtonBaseFactory, "389B7C71-5220-42B2-9992-2690C1A6702F")

.comdef IButtonBaseFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CICarouselPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CICarouselPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ICarouselPanel <L"Windows.UI.Xaml.Controls.Primitives.ICarouselPanel">
DEFINE_IIDX(ICarouselPanel, "DEAB78B2-373B-4151-8785-E544D0D9362B")

.comdef ICarouselPanel : public IInspectable

    get_CanVerticallyScroll proc :ptr
    put_CanVerticallyScroll proc :boolean
    get_CanHorizontallyScroll proc :ptr
    put_CanHorizontallyScroll proc :boolean
    get_ExtentWidth	proc :ptr
    get_ExtentHeight	proc :ptr
    get_ViewportWidth	proc :ptr
    get_ViewportHeight	proc :ptr
    get_HorizontalOffset proc :ptr
    get_VerticalOffset	proc :ptr
    get_ScrollOwner	proc :ptr
    put_ScrollOwner	proc :ptr
    LineUp		proc
    LineDown		proc
    LineLeft		proc
    LineRight		proc
    PageUp		proc
    PageDown		proc
    PageLeft		proc
    PageRight		proc
    MouseWheelUp	proc
    MouseWheelDown	proc
    MouseWheelLeft	proc
    MouseWheelRight	proc
    SetHorizontalOffset proc :DOUBLE
    SetVerticalOffset	proc :DOUBLE
    MakeVisible		proc :ptr, :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CICarouselPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CICarouselPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ICarouselPanelFactory <L"Windows.UI.Xaml.Controls.Primitives.ICarouselPanelFactory">
DEFINE_IIDX(ICarouselPanelFactory, "C1109404-9AE1-440E-A0DD-BBB6E2293CBE")

.comdef ICarouselPanelFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIComboBoxTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIComboBoxTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IComboBoxTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IComboBoxTemplateSettings">
DEFINE_IIDX(IComboBoxTemplateSettings, "83285C4E-17F6-4AA3-B61B-E87C718604EA")

.comdef IComboBoxTemplateSettings : public IInspectable

    get_DropDownOpenedHeight proc :ptr
    get_DropDownClosedHeight proc :ptr
    get_DropDownOffset	proc :ptr
    get_SelectedItemDirection proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragCompletedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragCompletedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IDragCompletedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.IDragCompletedEventArgs">
DEFINE_IIDX(IDragCompletedEventArgs, "B04F29A1-BD16-48F6-A511-9C2763641331")

.comdef IDragCompletedEventArgs : public IInspectable

    get_HorizontalChange proc :ptr
    get_VerticalChange	proc :ptr
    get_Canceled	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragCompletedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragCompletedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IDragCompletedEventArgsFactory <L"Windows.UI.Xaml.Controls.Primitives.IDragCompletedEventArgsFactory">
DEFINE_IIDX(IDragCompletedEventArgsFactory, "36A7D99D-148C-495F-A0FC-AFC871D62F33")

.comdef IDragCompletedEventArgsFactory : public IInspectable

    CreateInstanceWithHorizontalChangeVerticalChangeAndCanceled proc :DOUBLE, :DOUBLE, :boolean, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragDeltaEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragDeltaEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IDragDeltaEventArgs <L"Windows.UI.Xaml.Controls.Primitives.IDragDeltaEventArgs">
DEFINE_IIDX(IDragDeltaEventArgs, "2C2DD73C-2806-49FC-AAE9-6D792B572B6A")

.comdef IDragDeltaEventArgs : public IInspectable

    get_HorizontalChange proc :ptr
    get_VerticalChange	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragDeltaEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragDeltaEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IDragDeltaEventArgsFactory <L"Windows.UI.Xaml.Controls.Primitives.IDragDeltaEventArgsFactory">
DEFINE_IIDX(IDragDeltaEventArgsFactory, "46E7A1EF-AE15-44A6-8A04-95B0BF9AB876")

.comdef IDragDeltaEventArgsFactory : public IInspectable

    CreateInstanceWithHorizontalChangeAndVerticalChange proc :DOUBLE, :DOUBLE, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragStartedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragStartedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IDragStartedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.IDragStartedEventArgs">
DEFINE_IIDX(IDragStartedEventArgs, "9F915DD0-A124-4366-BD85-2408214AEED4")

.comdef IDragStartedEventArgs : public IInspectable

    get_HorizontalOffset proc :ptr
    get_VerticalOffset	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragStartedEventArgsFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIDragStartedEventArgsFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IDragStartedEventArgsFactory <L"Windows.UI.Xaml.Controls.Primitives.IDragStartedEventArgsFactory">
DEFINE_IIDX(IDragStartedEventArgsFactory, "5EEFE579-C706-4781-A308-C9E7F4C6A1D7")

.comdef IDragStartedEventArgsFactory : public IInspectable

    CreateInstanceWithHorizontalOffsetAndVerticalOffset proc :DOUBLE, :DOUBLE, :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IFlyoutBase <L"Windows.UI.Xaml.Controls.Primitives.IFlyoutBase">
DEFINE_IIDX(IFlyoutBase, "723EEA0B-D12E-430D-A9F0-9BB32BBF9913")

.comdef IFlyoutBase : public IInspectable

    get_Placement	proc :ptr
    put_Placement	proc :Windows::UI::Xaml::Controls::Primitives::FlyoutPlacementMode
    add_Opened		proc :ptr, :ptr
    remove_Opened	proc :EventRegistrationToken
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
    add_Opening		proc :ptr, :ptr
    remove_Opening	proc :EventRegistrationToken
    ShowAt		proc :ptr
    Hide		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBaseOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBaseOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IFlyoutBaseOverrides <L"Windows.UI.Xaml.Controls.Primitives.IFlyoutBaseOverrides">
DEFINE_IIDX(IFlyoutBaseOverrides, "101DEC86-6F4D-45A4-9D0E-3ECE6F16977E")

.comdef IFlyoutBaseOverrides : public IInspectable

    CreatePresenter	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IFlyoutBaseStatics <L"Windows.UI.Xaml.Controls.Primitives.IFlyoutBaseStatics">
DEFINE_IIDX(IFlyoutBaseStatics, "E2D795E3-85C0-4DE2-BAC1-5294CA011A78")

.comdef IFlyoutBaseStatics : public IInspectable

    get_PlacementProperty proc :ptr
    get_AttachedFlyoutProperty proc :ptr
    GetAttachedFlyout	proc :ptr, :ptr
    SetAttachedFlyout	proc :ptr, :ptr
    ShowAttachedFlyout	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIFlyoutBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IFlyoutBaseFactory <L"Windows.UI.Xaml.Controls.Primitives.IFlyoutBaseFactory">
DEFINE_IIDX(IFlyoutBaseFactory, "1C3363D7-FCA7-407E-920E-70E15E9F0BF1")

.comdef IFlyoutBaseFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IGridViewItemTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IGridViewItemTemplateSettings">
DEFINE_IIDX(IGridViewItemTemplateSettings, "9E30BAAF-165D-4267-A45E-1A43A75706AC")

.comdef IGridViewItemTemplateSettings : public IInspectable

    get_DragItemsCount	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollSnapPointsInfo_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollSnapPointsInfo_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IScrollSnapPointsInfo <L"Windows.UI.Xaml.Controls.Primitives.IScrollSnapPointsInfo">
DEFINE_IIDX(IScrollSnapPointsInfo, "1B5D1336-E61B-4D51-BE41-FD8DDC55C58C")

.comdef IScrollSnapPointsInfo : public IInspectable

    get_AreHorizontalSnapPointsRegular proc :ptr
    get_AreVerticalSnapPointsRegular proc :ptr
    add_HorizontalSnapPointsChanged proc :ptr, :ptr
    remove_HorizontalSnapPointsChanged proc :EventRegistrationToken
    add_VerticalSnapPointsChanged proc :ptr, :ptr
    remove_VerticalSnapPointsChanged proc :EventRegistrationToken
    GetIrregularSnapPoints proc :Windows::UI::Xaml::Controls::Orientation, :Windows::UI::Xaml::Controls::Primitives::SnapPointsAlignment, :ptr
    GetRegularSnapPoints proc :Windows::UI::Xaml::Controls::Orientation, :Windows::UI::Xaml::Controls::Primitives::SnapPointsAlignment, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIItemsChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIItemsChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IItemsChangedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.IItemsChangedEventArgs">
DEFINE_IIDX(IItemsChangedEventArgs, "E8B45568-7D10-421E-BE29-81839A91DE20")

.comdef IItemsChangedEventArgs : public IInspectable

    get_Action		proc :ptr
    get_Position	proc :ptr
    get_OldPosition	proc :ptr
    get_ItemCount	proc :ptr
    get_ItemUICount	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IListViewItemTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IListViewItemTemplateSettings">
DEFINE_IIDX(IListViewItemTemplateSettings, "67AF84BF-8279-4686-9326-CD189F27575D")

.comdef IListViewItemTemplateSettings : public IInspectable

    get_DragItemsCount	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIOrientedVirtualizingPanel_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIOrientedVirtualizingPanel_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IOrientedVirtualizingPanel <L"Windows.UI.Xaml.Controls.Primitives.IOrientedVirtualizingPanel">
DEFINE_IIDX(IOrientedVirtualizingPanel, "F077B577-39BD-46EE-BDD7-0826BEED71B8")

.comdef IOrientedVirtualizingPanel : public IInspectable

    get_CanVerticallyScroll proc :ptr
    put_CanVerticallyScroll proc :boolean
    get_CanHorizontallyScroll proc :ptr
    put_CanHorizontallyScroll proc :boolean
    get_ExtentWidth	proc :ptr
    get_ExtentHeight	proc :ptr
    get_ViewportWidth	proc :ptr
    get_ViewportHeight	proc :ptr
    get_HorizontalOffset proc :ptr
    get_VerticalOffset	proc :ptr
    get_ScrollOwner	proc :ptr
    put_ScrollOwner	proc :ptr
    LineUp		proc
    LineDown		proc
    LineLeft		proc
    LineRight		proc
    PageUp		proc
    PageDown		proc
    PageLeft		proc
    PageRight		proc
    MouseWheelUp	proc
    MouseWheelDown	proc
    MouseWheelLeft	proc
    MouseWheelRight	proc
    SetHorizontalOffset proc :DOUBLE
    SetVerticalOffset	proc :DOUBLE
    MakeVisible		proc :ptr, :Windows::Foundation::Rect, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIOrientedVirtualizingPanelFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIOrientedVirtualizingPanelFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IOrientedVirtualizingPanelFactory <L"Windows.UI.Xaml.Controls.Primitives.IOrientedVirtualizingPanelFactory">
DEFINE_IIDX(IOrientedVirtualizingPanelFactory, "7B8EAEAF-F92F-439D-9EBF-E9919F56C94D")

.comdef IOrientedVirtualizingPanelFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIPopup_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIPopup_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IPopup <L"Windows.UI.Xaml.Controls.Primitives.IPopup">
DEFINE_IIDX(IPopup, "62418240-E6D3-4705-A1DC-39156456EE29")

.comdef IPopup : public IInspectable

    get_Child		proc :ptr
    put_Child		proc :ptr
    get_IsOpen		proc :ptr
    put_IsOpen		proc :boolean
    get_HorizontalOffset proc :ptr
    put_HorizontalOffset proc :DOUBLE
    get_VerticalOffset	proc :ptr
    put_VerticalOffset	proc :DOUBLE
    get_ChildTransitions proc :ptr
    put_ChildTransitions proc :ptr
    get_IsLightDismissEnabled proc :ptr
    put_IsLightDismissEnabled proc :boolean
    add_Opened		proc :ptr, :ptr
    remove_Opened	proc :EventRegistrationToken
    add_Closed		proc :ptr, :ptr
    remove_Closed	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIPopupStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIPopupStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IPopupStatics <L"Windows.UI.Xaml.Controls.Primitives.IPopupStatics">
DEFINE_IIDX(IPopupStatics, "5AE3BF1A-6E34-40D6-8A7F-CA822AAF59E3")

.comdef IPopupStatics : public IInspectable

    get_ChildProperty	proc :ptr
    get_IsOpenProperty	proc :ptr
    get_HorizontalOffsetProperty proc :ptr
    get_VerticalOffsetProperty proc :ptr
    get_ChildTransitionsProperty proc :ptr
    get_IsLightDismissEnabledProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIProgressBarTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIProgressBarTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IProgressBarTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IProgressBarTemplateSettings">
DEFINE_IIDX(IProgressBarTemplateSettings, "3FE2EA2A-E3F2-4C2B-9488-918D77D2BBE4")

.comdef IProgressBarTemplateSettings : public IInspectable

    get_EllipseDiameter proc :ptr
    get_EllipseOffset	proc :ptr
    get_EllipseAnimationWellPosition proc :ptr
    get_EllipseAnimationEndPosition proc :ptr
    get_ContainerAnimationStartPosition proc :ptr
    get_ContainerAnimationEndPosition proc :ptr
    get_IndicatorLengthDelta proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIProgressRingTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIProgressRingTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IProgressRingTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IProgressRingTemplateSettings">
DEFINE_IIDX(IProgressRingTemplateSettings, "B9B675EC-C723-42E6-83E9-9826272BDC0E")

.comdef IProgressRingTemplateSettings : public IInspectable

    get_EllipseDiameter proc :ptr
    get_EllipseOffset	proc :ptr
    get_MaxSideLength	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBase_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBase_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRangeBase <L"Windows.UI.Xaml.Controls.Primitives.IRangeBase">
DEFINE_IIDX(IRangeBase, "FA002C1A-494E-46CF-91D4-E14A8D798675")

.comdef IRangeBase : public IInspectable

    get_Minimum		proc :ptr
    put_Minimum		proc :DOUBLE
    get_Maximum		proc :ptr
    put_Maximum		proc :DOUBLE
    get_SmallChange	proc :ptr
    put_SmallChange	proc :DOUBLE
    get_LargeChange	proc :ptr
    put_LargeChange	proc :DOUBLE
    get_Value		proc :ptr
    put_Value		proc :DOUBLE
    add_ValueChanged	proc :ptr, :ptr
    remove_ValueChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRangeBaseOverrides <L"Windows.UI.Xaml.Controls.Primitives.IRangeBaseOverrides">
DEFINE_IIDX(IRangeBaseOverrides, "4291AF39-7F0B-4BC2-99C4-06E7062682D8")

.comdef IRangeBaseOverrides : public IInspectable

    OnMinimumChanged	proc :DOUBLE, :DOUBLE
    OnMaximumChanged	proc :DOUBLE, :DOUBLE
    OnValueChanged	proc :DOUBLE, :DOUBLE
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRangeBaseStatics <L"Windows.UI.Xaml.Controls.Primitives.IRangeBaseStatics">
DEFINE_IIDX(IRangeBaseStatics, "67EF17E1-FE37-474F-9E97-3B5E0B30F2E0")

.comdef IRangeBaseStatics : public IInspectable

    get_MinimumProperty proc :ptr
    get_MaximumProperty proc :ptr
    get_SmallChangeProperty proc :ptr
    get_LargeChangeProperty proc :ptr
    get_ValueProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRangeBaseFactory <L"Windows.UI.Xaml.Controls.Primitives.IRangeBaseFactory">
DEFINE_IIDX(IRangeBaseFactory, "389B7C71-5220-42B2-9992-2690C1A67030")

.comdef IRangeBaseFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseValueChangedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRangeBaseValueChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRangeBaseValueChangedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.IRangeBaseValueChangedEventArgs">
DEFINE_IIDX(IRangeBaseValueChangedEventArgs, "A1921777-D5C1-4F9C-A7B0-0401B7E6DC5C")

.comdef IRangeBaseValueChangedEventArgs : public IInspectable

    get_OldValue	proc :ptr
    get_NewValue	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRepeatButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRepeatButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRepeatButton <L"Windows.UI.Xaml.Controls.Primitives.IRepeatButton">
DEFINE_IIDX(IRepeatButton, "02200DF9-021A-484A-A93B-0F31020314E5")

.comdef IRepeatButton : public IInspectable

    get_Delay		proc :ptr
    put_Delay		proc :INT32
    get_Interval	proc :ptr
    put_Interval	proc :INT32
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRepeatButtonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIRepeatButtonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IRepeatButtonStatics <L"Windows.UI.Xaml.Controls.Primitives.IRepeatButtonStatics">
DEFINE_IIDX(IRepeatButtonStatics, "3914AC4E-F462-4F73-8197-E8846639C682")

.comdef IRepeatButtonStatics : public IInspectable

    get_DelayProperty	proc :ptr
    get_IntervalProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollBar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollBar_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IScrollBar <L"Windows.UI.Xaml.Controls.Primitives.IScrollBar">
DEFINE_IIDX(IScrollBar, "F57AE6CA-D1A6-4B90-A4E9-54DF1BA8D2EC")

.comdef IScrollBar : public IInspectable

    get_Orientation	proc :ptr
    put_Orientation	proc :Windows::UI::Xaml::Controls::Orientation
    get_ViewportSize	proc :ptr
    put_ViewportSize	proc :DOUBLE
    get_IndicatorMode	proc :ptr
    put_IndicatorMode	proc :Windows::UI::Xaml::Controls::Primitives::ScrollingIndicatorMode
    add_Scroll		proc :ptr, :ptr
    remove_Scroll	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollBarStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollBarStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IScrollBarStatics <L"Windows.UI.Xaml.Controls.Primitives.IScrollBarStatics">
DEFINE_IIDX(IScrollBarStatics, "45EAF38D-B814-48CF-97F2-539EB16DFD4D")

.comdef IScrollBarStatics : public IInspectable

    get_OrientationProperty proc :ptr
    get_ViewportSizeProperty proc :ptr
    get_IndicatorModeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIScrollEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IScrollEventArgs <L"Windows.UI.Xaml.Controls.Primitives.IScrollEventArgs">
DEFINE_IIDX(IScrollEventArgs, "C57E5168-3AFE-448D-B752-2F364C75D743")

.comdef IScrollEventArgs : public IInspectable

    get_NewValue	proc :ptr
    get_ScrollEventType proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelector_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelector_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISelector <L"Windows.UI.Xaml.Controls.Primitives.ISelector">
DEFINE_IIDX(ISelector, "E30EB3A5-B36B-42DC-8527-CD25136C083C")

.comdef ISelector : public IInspectable

    get_SelectedIndex	proc :ptr
    put_SelectedIndex	proc :INT32
    get_SelectedItem	proc :ptr
    put_SelectedItem	proc :ptr
    get_SelectedValue	proc :ptr
    put_SelectedValue	proc :ptr
    get_SelectedValuePath proc :ptr
    put_SelectedValuePath proc :HSTRING
    get_IsSynchronizedWithCurrentItem proc :ptr
    put_IsSynchronizedWithCurrentItem proc :ptr
    add_SelectionChanged proc :ptr, :ptr
    remove_SelectionChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISelectorStatics <L"Windows.UI.Xaml.Controls.Primitives.ISelectorStatics">
DEFINE_IIDX(ISelectorStatics, "13300B06-BD10-4E09-BFF7-71EFB8BBB42B")

.comdef ISelectorStatics : public IInspectable

    get_SelectedIndexProperty proc :ptr
    get_SelectedItemProperty proc :ptr
    get_SelectedValueProperty proc :ptr
    get_SelectedValuePathProperty proc :ptr
    get_IsSynchronizedWithCurrentItemProperty proc :ptr
    GetIsSelectionActive proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISelectorFactory <L"Windows.UI.Xaml.Controls.Primitives.ISelectorFactory">
DEFINE_IIDX(ISelectorFactory, "C9BE2995-D136-4600-B187-8AD56079B48A")

.comdef ISelectorFactory : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorItem_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISelectorItem <L"Windows.UI.Xaml.Controls.Primitives.ISelectorItem">
DEFINE_IIDX(ISelectorItem, "541C8D6C-0283-4581-B945-2A64C28A0646")

.comdef ISelectorItem : public IInspectable

    get_IsSelected	proc :ptr
    put_IsSelected	proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorItemStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorItemStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISelectorItemStatics <L"Windows.UI.Xaml.Controls.Primitives.ISelectorItemStatics">
DEFINE_IIDX(ISelectorItemStatics, "2A353AB8-CBE9-4303-92E7-C8906E218392")

.comdef ISelectorItemStatics : public IInspectable

    get_IsSelectedProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorItemFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISelectorItemFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISelectorItemFactory <L"Windows.UI.Xaml.Controls.Primitives.ISelectorItemFactory">
DEFINE_IIDX(ISelectorItemFactory, "B9363945-C86A-4B1E-9440-1879378D5313")

.comdef ISelectorItemFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISettingsFlyoutTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CISettingsFlyoutTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ISettingsFlyoutTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ISettingsFlyoutTemplateSettings">
DEFINE_IIDX(ISettingsFlyoutTemplateSettings, "BCF14C10-CEA7-43F1-9D68-57605DED69D4")

.comdef ISettingsFlyoutTemplateSettings : public IInspectable

    get_HeaderBackground proc :ptr
    get_HeaderForeground proc :ptr
    get_BorderBrush	proc :ptr
    get_BorderThickness proc :ptr
    get_IconSource	proc :ptr
    get_ContentTransitions proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIThumb_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIThumb_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IThumb <L"Windows.UI.Xaml.Controls.Primitives.IThumb">
DEFINE_IIDX(IThumb, "E8B2B281-0D6A-45CF-B333-2402B037F099")

.comdef IThumb : public IInspectable

    get_IsDragging	proc :ptr
    add_DragStarted	proc :ptr, :ptr
    remove_DragStarted	proc :EventRegistrationToken
    add_DragDelta	proc :ptr, :ptr
    remove_DragDelta	proc :EventRegistrationToken
    add_DragCompleted	proc :ptr, :ptr
    remove_DragCompleted proc :EventRegistrationToken
    CancelDrag		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIThumbStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIThumbStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IThumbStatics <L"Windows.UI.Xaml.Controls.Primitives.IThumbStatics">
DEFINE_IIDX(IThumbStatics, "955024EB-36F3-4672-A186-BAAF626AC4AD")

.comdef IThumbStatics : public IInspectable

    get_IsDraggingProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CITickBar_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CITickBar_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ITickBar <L"Windows.UI.Xaml.Controls.Primitives.ITickBar">
DEFINE_IIDX(ITickBar, "994683FA-F1F6-487D-A5AC-C15921BFA995")

.comdef ITickBar : public IInspectable

    get_Fill		proc :ptr
    put_Fill		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CITickBarStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CITickBarStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ITickBarStatics <L"Windows.UI.Xaml.Controls.Primitives.ITickBarStatics">
DEFINE_IIDX(ITickBarStatics, "2C6D7E40-799D-4A54-BE09-1FEFC61D018E")

.comdef ITickBarStatics : public IInspectable

    get_FillProperty	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButton_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButton_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IToggleButton <L"Windows.UI.Xaml.Controls.Primitives.IToggleButton">
DEFINE_IIDX(IToggleButton, "589877FB-0FC7-4036-9D8B-127DFA75C16D")

.comdef IToggleButton : public IInspectable

    get_IsChecked	proc :ptr
    put_IsChecked	proc :ptr
    get_IsThreeState	proc :ptr
    put_IsThreeState	proc :boolean
    add_Checked		proc :ptr, :ptr
    remove_Checked	proc :EventRegistrationToken
    add_Unchecked	proc :ptr, :ptr
    remove_Unchecked	proc :EventRegistrationToken
    add_Indeterminate	proc :ptr, :ptr
    remove_Indeterminate proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButtonOverrides_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButtonOverrides_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IToggleButtonOverrides <L"Windows.UI.Xaml.Controls.Primitives.IToggleButtonOverrides">
DEFINE_IIDX(IToggleButtonOverrides, "D20E4C28-F18B-491A-9A45-F1A04A9369A4")

.comdef IToggleButtonOverrides : public IInspectable

    OnToggle		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButtonStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButtonStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IToggleButtonStatics <L"Windows.UI.Xaml.Controls.Primitives.IToggleButtonStatics">
DEFINE_IIDX(IToggleButtonStatics, "AF1EAB12-0128-4F67-9C5A-82320C445D19")

.comdef IToggleButtonStatics : public IInspectable

    get_IsCheckedProperty proc :ptr
    get_IsThreeStateProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButtonFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleButtonFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IToggleButtonFactory <L"Windows.UI.Xaml.Controls.Primitives.IToggleButtonFactory">
DEFINE_IIDX(IToggleButtonFactory, "D56AA2FC-FC7F-449C-9855-7A1055D668A8")

.comdef IToggleButtonFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleSwitchTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToggleSwitchTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IToggleSwitchTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IToggleSwitchTemplateSettings">
DEFINE_IIDX(IToggleSwitchTemplateSettings, "02B7BDCD-628A-4363-86E0-51D6E2E89E58")

.comdef IToggleSwitchTemplateSettings : public IInspectable

    get_KnobCurrentToOnOffset proc :ptr
    get_KnobCurrentToOffOffset proc :ptr
    get_KnobOnToOffOffset proc :ptr
    get_KnobOffToOnOffset proc :ptr
    get_CurtainCurrentToOnOffset proc :ptr
    get_CurtainCurrentToOffOffset proc :ptr
    get_CurtainOnToOffOffset proc :ptr
    get_CurtainOffToOnOffset proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToolTipTemplateSettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIToolTipTemplateSettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IToolTipTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.IToolTipTemplateSettings">
DEFINE_IIDX(IToolTipTemplateSettings, "D4388247-0EC4-4506-AFFD-AFAC2225B48C")

.comdef IToolTipTemplateSettings : public IInspectable

    get_FromHorizontalOffset proc :ptr
    get_FromVerticalOffset proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IGridViewItemPresenter <L"Windows.UI.Xaml.Controls.Primitives.IGridViewItemPresenter">
DEFINE_IIDX(IGridViewItemPresenter, "214F9010-56E2-4821-8A1C-2305709AF94B")

.comdef IGridViewItemPresenter : public IInspectable

    get_SelectionCheckMarkVisualEnabled proc :ptr
    put_SelectionCheckMarkVisualEnabled proc :boolean
    get_CheckHintBrush	proc :ptr
    put_CheckHintBrush	proc :ptr
    get_CheckSelectingBrush proc :ptr
    put_CheckSelectingBrush proc :ptr
    get_CheckBrush	proc :ptr
    put_CheckBrush	proc :ptr
    get_DragBackground	proc :ptr
    put_DragBackground	proc :ptr
    get_DragForeground	proc :ptr
    put_DragForeground	proc :ptr
    get_FocusBorderBrush proc :ptr
    put_FocusBorderBrush proc :ptr
    get_PlaceholderBackground proc :ptr
    put_PlaceholderBackground proc :ptr
    get_PointerOverBackground proc :ptr
    put_PointerOverBackground proc :ptr
    get_SelectedBackground proc :ptr
    put_SelectedBackground proc :ptr
    get_SelectedForeground proc :ptr
    put_SelectedForeground proc :ptr
    get_SelectedPointerOverBackground proc :ptr
    put_SelectedPointerOverBackground proc :ptr
    get_SelectedPointerOverBorderBrush proc :ptr
    put_SelectedPointerOverBorderBrush proc :ptr
    get_SelectedBorderThickness proc :ptr
    put_SelectedBorderThickness proc :Windows::UI::Xaml::Thickness
    get_DisabledOpacity proc :ptr
    put_DisabledOpacity proc :DOUBLE
    get_DragOpacity	proc :ptr
    put_DragOpacity	proc :DOUBLE
    get_ReorderHintOffset proc :ptr
    put_ReorderHintOffset proc :DOUBLE
    get_HorizontalContentAlignment proc :ptr
    put_HorizontalContentAlignment proc :Windows::UI::Xaml::HorizontalAlignment
    get_VerticalContentAlignment proc :ptr
    put_VerticalContentAlignment proc :Windows::UI::Xaml::VerticalAlignment
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_PointerOverBackgroundMargin proc :ptr
    put_PointerOverBackgroundMargin proc :Windows::UI::Xaml::Thickness
    get_ContentMargin	proc :ptr
    put_ContentMargin	proc :Windows::UI::Xaml::Thickness
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemPresenterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemPresenterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IGridViewItemPresenterStatics <L"Windows.UI.Xaml.Controls.Primitives.IGridViewItemPresenterStatics">
DEFINE_IIDX(IGridViewItemPresenterStatics, "E958F8C4-277E-4A72-A01E-9E1688980178")

.comdef IGridViewItemPresenterStatics : public IInspectable

    get_SelectionCheckMarkVisualEnabledProperty proc :ptr
    get_CheckHintBrushProperty proc :ptr
    get_CheckSelectingBrushProperty proc :ptr
    get_CheckBrushProperty proc :ptr
    get_DragBackgroundProperty proc :ptr
    get_DragForegroundProperty proc :ptr
    get_FocusBorderBrushProperty proc :ptr
    get_PlaceholderBackgroundProperty proc :ptr
    get_PointerOverBackgroundProperty proc :ptr
    get_SelectedBackgroundProperty proc :ptr
    get_SelectedForegroundProperty proc :ptr
    get_SelectedPointerOverBackgroundProperty proc :ptr
    get_SelectedPointerOverBorderBrushProperty proc :ptr
    get_SelectedBorderThicknessProperty proc :ptr
    get_DisabledOpacityProperty proc :ptr
    get_DragOpacityProperty proc :ptr
    get_ReorderHintOffsetProperty proc :ptr
    get_HorizontalContentAlignmentProperty proc :ptr
    get_VerticalContentAlignmentProperty proc :ptr
    get_PaddingProperty proc :ptr
    get_PointerOverBackgroundMarginProperty proc :ptr
    get_ContentMarginProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemPresenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGridViewItemPresenterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IGridViewItemPresenterFactory <L"Windows.UI.Xaml.Controls.Primitives.IGridViewItemPresenterFactory">
DEFINE_IIDX(IGridViewItemPresenterFactory, "53C12178-63BB-4A65-A3F1-AB114CFC6FFE")

.comdef IGridViewItemPresenterFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IListViewItemPresenter <L"Windows.UI.Xaml.Controls.Primitives.IListViewItemPresenter">
DEFINE_IIDX(IListViewItemPresenter, "FC8946BD-A3A2-4969-8174-25B5D3C28033")

.comdef IListViewItemPresenter : public IInspectable

    get_SelectionCheckMarkVisualEnabled proc :ptr
    put_SelectionCheckMarkVisualEnabled proc :boolean
    get_CheckHintBrush	proc :ptr
    put_CheckHintBrush	proc :ptr
    get_CheckSelectingBrush proc :ptr
    put_CheckSelectingBrush proc :ptr
    get_CheckBrush	proc :ptr
    put_CheckBrush	proc :ptr
    get_DragBackground	proc :ptr
    put_DragBackground	proc :ptr
    get_DragForeground	proc :ptr
    put_DragForeground	proc :ptr
    get_FocusBorderBrush proc :ptr
    put_FocusBorderBrush proc :ptr
    get_PlaceholderBackground proc :ptr
    put_PlaceholderBackground proc :ptr
    get_PointerOverBackground proc :ptr
    put_PointerOverBackground proc :ptr
    get_SelectedBackground proc :ptr
    put_SelectedBackground proc :ptr
    get_SelectedForeground proc :ptr
    put_SelectedForeground proc :ptr
    get_SelectedPointerOverBackground proc :ptr
    put_SelectedPointerOverBackground proc :ptr
    get_SelectedPointerOverBorderBrush proc :ptr
    put_SelectedPointerOverBorderBrush proc :ptr
    get_SelectedBorderThickness proc :ptr
    put_SelectedBorderThickness proc :Windows::UI::Xaml::Thickness
    get_DisabledOpacity proc :ptr
    put_DisabledOpacity proc :DOUBLE
    get_DragOpacity	proc :ptr
    put_DragOpacity	proc :DOUBLE
    get_ReorderHintOffset proc :ptr
    put_ReorderHintOffset proc :DOUBLE
    get_HorizontalContentAlignment proc :ptr
    put_HorizontalContentAlignment proc :Windows::UI::Xaml::HorizontalAlignment
    get_VerticalContentAlignment proc :ptr
    put_VerticalContentAlignment proc :Windows::UI::Xaml::VerticalAlignment
    get_Padding		proc :ptr
    put_Padding		proc :Windows::UI::Xaml::Thickness
    get_PointerOverBackgroundMargin proc :ptr
    put_PointerOverBackgroundMargin proc :Windows::UI::Xaml::Thickness
    get_ContentMargin	proc :ptr
    put_ContentMargin	proc :Windows::UI::Xaml::Thickness
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemPresenterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemPresenterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IListViewItemPresenterStatics <L"Windows.UI.Xaml.Controls.Primitives.IListViewItemPresenterStatics">
DEFINE_IIDX(IListViewItemPresenterStatics, "6504A55A-15DD-42FB-AA5D-2D8CE2E9C294")

.comdef IListViewItemPresenterStatics : public IInspectable

    get_SelectionCheckMarkVisualEnabledProperty proc :ptr
    get_CheckHintBrushProperty proc :ptr
    get_CheckSelectingBrushProperty proc :ptr
    get_CheckBrushProperty proc :ptr
    get_DragBackgroundProperty proc :ptr
    get_DragForegroundProperty proc :ptr
    get_FocusBorderBrushProperty proc :ptr
    get_PlaceholderBackgroundProperty proc :ptr
    get_PointerOverBackgroundProperty proc :ptr
    get_SelectedBackgroundProperty proc :ptr
    get_SelectedForegroundProperty proc :ptr
    get_SelectedPointerOverBackgroundProperty proc :ptr
    get_SelectedPointerOverBorderBrushProperty proc :ptr
    get_SelectedBorderThicknessProperty proc :ptr
    get_DisabledOpacityProperty proc :ptr
    get_DragOpacityProperty proc :ptr
    get_ReorderHintOffsetProperty proc :ptr
    get_HorizontalContentAlignmentProperty proc :ptr
    get_VerticalContentAlignmentProperty proc :ptr
    get_PaddingProperty proc :ptr
    get_PointerOverBackgroundMarginProperty proc :ptr
    get_ContentMarginProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemPresenterFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIListViewItemPresenterFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IListViewItemPresenterFactory <L"Windows.UI.Xaml.Controls.Primitives.IListViewItemPresenterFactory">
DEFINE_IIDX(IListViewItemPresenterFactory, "E0777CFD-F7E4-4A67-9AC0-A994FCACD020")

.comdef IListViewItemPresenterFactory : public IInspectable

    CreateInstance	proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGeneratorPositionHelper_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGeneratorPositionHelper_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IGeneratorPositionHelper <L"Windows.UI.Xaml.Controls.Primitives.IGeneratorPositionHelper">
DEFINE_IIDX(IGeneratorPositionHelper, "CD40318D-7745-40D9-AB9D-ABBDA4A7FFEA")

.comdef IGeneratorPositionHelper : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGeneratorPositionHelperStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CIGeneratorPositionHelperStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_IGeneratorPositionHelperStatics <L"Windows.UI.Xaml.Controls.Primitives.IGeneratorPositionHelperStatics">
DEFINE_IIDX(IGeneratorPositionHelperStatics, "AD4095CD-60EC-4588-8D60-39D29097A4DF")

.comdef IGeneratorPositionHelperStatics : public IInspectable

    FromIndexAndOffset	proc :INT32, :INT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CILayoutInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CILayoutInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ILayoutInformation <L"Windows.UI.Xaml.Controls.Primitives.ILayoutInformation">
DEFINE_IIDX(ILayoutInformation, "B5384C9B-C8CF-41B3-BF16-18C8420E72C9")

.comdef ILayoutInformation : public IInspectable

   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CILayoutInformationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CControls_CPrimitives_CILayoutInformationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Controls_Primitives_ILayoutInformationStatics <L"Windows.UI.Xaml.Controls.Primitives.ILayoutInformationStatics">
DEFINE_IIDX(ILayoutInformationStatics, "CF06CF99-58E9-4682-8326-50CAAB65ED7C")

.comdef ILayoutInformationStatics : public IInspectable

    GetLayoutExceptionElement proc :ptr, :ptr
    GetLayoutSlot	proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ItemsChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ItemsChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ItemsChangedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.ItemsChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_FlyoutBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_FlyoutBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_FlyoutBase <L"Windows.UI.Xaml.Controls.Primitives.FlyoutBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ComboBoxTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ComboBoxTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ComboBoxTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ComboBoxTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_GridViewItemTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_GridViewItemTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_GridViewItemTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.GridViewItemTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ListViewItemTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ListViewItemTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ListViewItemTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ListViewItemTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ProgressBarTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ProgressBarTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ProgressBarTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ProgressBarTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ProgressRingTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ProgressRingTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ProgressRingTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ProgressRingTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_SettingsFlyoutTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_SettingsFlyoutTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_SettingsFlyoutTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.SettingsFlyoutTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ToggleSwitchTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ToggleSwitchTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ToggleSwitchTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ToggleSwitchTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ToolTipTemplateSettings_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ToolTipTemplateSettings_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ToolTipTemplateSettings <L"Windows.UI.Xaml.Controls.Primitives.ToolTipTemplateSettings">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_GeneratorPositionHelper_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_GeneratorPositionHelper_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_GeneratorPositionHelper <L"Windows.UI.Xaml.Controls.Primitives.GeneratorPositionHelper">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_DragCompletedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_DragCompletedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_DragCompletedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.DragCompletedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_DragDeltaEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_DragDeltaEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_DragDeltaEventArgs <L"Windows.UI.Xaml.Controls.Primitives.DragDeltaEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_DragStartedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_DragStartedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_DragStartedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.DragStartedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_RangeBaseValueChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_RangeBaseValueChangedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_RangeBaseValueChangedEventArgs <L"Windows.UI.Xaml.Controls.Primitives.RangeBaseValueChangedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ScrollEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ScrollEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ScrollEventArgs <L"Windows.UI.Xaml.Controls.Primitives.ScrollEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_CarouselPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_CarouselPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_CarouselPanel <L"Windows.UI.Xaml.Controls.Primitives.CarouselPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_OrientedVirtualizingPanel_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_OrientedVirtualizingPanel_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_OrientedVirtualizingPanel <L"Windows.UI.Xaml.Controls.Primitives.OrientedVirtualizingPanel">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_Popup_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_Popup_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_Popup <L"Windows.UI.Xaml.Controls.Primitives.Popup">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_TickBar_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_TickBar_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_TickBar <L"Windows.UI.Xaml.Controls.Primitives.TickBar">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_GridViewItemPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_GridViewItemPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_GridViewItemPresenter <L"Windows.UI.Xaml.Controls.Primitives.GridViewItemPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ListViewItemPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ListViewItemPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ListViewItemPresenter <L"Windows.UI.Xaml.Controls.Primitives.ListViewItemPresenter">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_SelectorItem_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_SelectorItem_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_SelectorItem <L"Windows.UI.Xaml.Controls.Primitives.SelectorItem">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ButtonBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ButtonBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ButtonBase <L"Windows.UI.Xaml.Controls.Primitives.ButtonBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_RangeBase_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_RangeBase_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_RangeBase <L"Windows.UI.Xaml.Controls.Primitives.RangeBase">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_RepeatButton_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_RepeatButton_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_RepeatButton <L"Windows.UI.Xaml.Controls.Primitives.RepeatButton">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ScrollBar_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ScrollBar_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ScrollBar <L"Windows.UI.Xaml.Controls.Primitives.ScrollBar">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_Selector_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_Selector_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_Selector <L"Windows.UI.Xaml.Controls.Primitives.Selector">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_Thumb_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_Thumb_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_Thumb <L"Windows.UI.Xaml.Controls.Primitives.Thumb">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ToggleButton_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_ToggleButton_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_ToggleButton <L"Windows.UI.Xaml.Controls.Primitives.ToggleButton">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_LayoutInformation_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Controls_Primitives_LayoutInformation_DEFINED
define RuntimeClass_Windows_UI_Xaml_Controls_Primitives_LayoutInformation <L"Windows.UI.Xaml.Controls.Primitives.LayoutInformation">
endif

endif
