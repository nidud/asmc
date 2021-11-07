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

ifndef __windows2Eui2Eviewmanagement_h__
define __windows2Eui2Eviewmanagement_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.inc
include Windows.UI.Core.inc
include windows.foundation.collections.inc

ifndef ____FITypedEventHandler_2_Windows__CUI__CViewManagement__CAccessibilitySettings_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CViewManagement__CAccessibilitySettings_IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CViewManagement__CAccessibilitySettings_IInspectable, "f5917e6f-5abf-5e65-b5b4-1b9c8d94e788")

.comdef __FITypedEventHandler_2_Windows__CUI__CViewManagement__CAccessibilitySettings_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CViewManagement__CApplicationView_Windows__CUI__CViewManagement__CApplicationViewConsolidatedEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CViewManagement__CApplicationView_Windows__CUI__CViewManagement__CApplicationViewConsolidatedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CViewManagement__CApplicationView_Windows__CUI__CViewManagement__CApplicationViewConsolidatedEventArgs, "463c606a-8c82-5a29-a2bd-040781f25348")

.comdef __FITypedEventHandler_2_Windows__CUI__CViewManagement__CApplicationView_Windows__CUI__CViewManagement__CApplicationViewConsolidatedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

ifndef ____FITypedEventHandler_2_Windows__CUI__CViewManagement__CInputPane_Windows__CUI__CViewManagement__CInputPaneVisibilityEventArgs_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CUI__CViewManagement__CInputPane_Windows__CUI__CViewManagement__CInputPaneVisibilityEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FITypedEventHandler_2_Windows__CUI__CViewManagement__CInputPane_Windows__CUI__CViewManagement__CInputPaneVisibilityEventArgs, "b813d684-d953-5a8a-9b30-78b79fb9147b")

.comdef __FITypedEventHandler_2_Windows__CUI__CViewManagement__CInputPane_Windows__CUI__CViewManagement__CInputPaneVisibilityEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif


.namespace Windows
.namespace UI
.namespace ViewManagement

.enum ApplicationViewState {
    ApplicationViewState_FullScreenLandscape,
    ApplicationViewState_Filled,
    ApplicationViewState_Snapped,
    ApplicationViewState_FullScreenPortrait
    }

.enum ApplicationViewOrientation {
    ApplicationViewOrientation_Landscape,
    ApplicationViewOrientation_Portrait
    }

.enum ApplicationViewSwitchingOptions {
    ApplicationViewSwitchingOptions_Default,
    ApplicationViewSwitchingOptions_SkipAnimation,
    ApplicationViewSwitchingOptions_ConsolidateViews
    }

.enum ViewSizePreference {
    ViewSizePreference_Default,
    ViewSizePreference_UseLess,
    ViewSizePreference_UseHalf,
    ViewSizePreference_UseMore,
    ViewSizePreference_UseMinimum,
    ViewSizePreference_UseNone
    }

.enum HandPreference {
    HandPreference_LeftHanded,
    HandPreference_RightHanded
    }

.enum UIElementType {
    UIElementType_ActiveCaption,
    UIElementType_Background,
    UIElementType_ButtonFace,
    UIElementType_ButtonText,
    UIElementType_CaptionText,
    UIElementType_GrayText,
    UIElementType_Highlight,
    UIElementType_HighlightText,
    UIElementType_Hotlight,
    UIElementType_InactiveCaption,
    UIElementType_InactiveCaptionText,
    UIElementType_Window,
    UIElementType_WindowText
    }

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewSwitcherStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewSwitcherStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IApplicationViewSwitcherStatics <L"Windows.UI.ViewManagement.IApplicationViewSwitcherStatics">

DEFINE_IIDX(IApplicationViewSwitcherStatics, "975F2F1E-E656-4C5E-A0A1-717C6FFA7D64")

.comdef IApplicationViewSwitcherStatics : public IInspectable

    DisableShowingMainViewOnActivation proc
    TryShowAsStandaloneAsync proc :INT32, :ptr
    TryShowAsStandaloneWithSizePreferenceAsync proc :INT32, :LONG, :ptr
    TryShowAsStandaloneWithAnchorViewAndSizePreferenceAsync proc :INT32, :LONG, :INT32, :LONG, :ptr
    SwitchAsync		proc :INT32, :ptr
    SwitchFromViewAsync proc :INT32, :INT32, :ptr
    SwitchFromViewWithOptionsAsync proc :INT32, :INT32, :LONG, :ptr
    PrepareForCustomAnimatedSwitchAsync proc :INT32, :INT32, :LONG, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewInteropStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewInteropStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IApplicationViewInteropStatics <L"Windows.UI.ViewManagement.IApplicationViewInteropStatics">

DEFINE_IIDX(IApplicationViewInteropStatics, "C446FB5D-4793-4896-A8E2-BE57A8BB0F50")

.comdef IApplicationViewInteropStatics : public IInspectable

    GetApplicationViewIdForWindow proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IApplicationViewStatics <L"Windows.UI.ViewManagement.IApplicationViewStatics">

DEFINE_IIDX(IApplicationViewStatics, "010A6306-C433-44E5-A9F2-BD84D4030A95")

.comdef IApplicationViewStatics : public IInspectable

    get_Value		proc :ptr
    TryUnsnap		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IApplicationViewStatics2 <L"Windows.UI.ViewManagement.IApplicationViewStatics2">

DEFINE_IIDX(IApplicationViewStatics2, "AF338AE5-CF64-423C-85E5-F3E72448FB23")

.comdef IApplicationViewStatics2 : public IInspectable

    GetForCurrentView	proc :ptr
    get_TerminateAppOnFinalViewClose proc :ptr
    put_TerminateAppOnFinalViewClose proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationView_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IApplicationView <L"Windows.UI.ViewManagement.IApplicationView">

DEFINE_IIDX(IApplicationView, "D222D519-4361-451E-96C4-60F4F9742DB0")

.comdef IApplicationView : public IInspectable

    get_Orientation	proc :ptr
    get_AdjacentToLeftDisplayEdge proc :ptr
    get_AdjacentToRightDisplayEdge proc :ptr
    get_IsFullScreen	proc :ptr
    get_IsOnLockScreen	proc :ptr
    get_IsScreenCaptureEnabled proc :ptr
    put_IsScreenCaptureEnabled proc :boolean
    put_Title		proc :HSTRING
    get_Title		proc :ptr
    get_Id		proc :ptr
    add_Consolidated	proc :ptr, :ptr
    remove_Consolidated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewConsolidatedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIApplicationViewConsolidatedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IApplicationViewConsolidatedEventArgs <L"Windows.UI.ViewManagement.IApplicationViewConsolidatedEventArgs">

DEFINE_IIDX(IApplicationViewConsolidatedEventArgs, "514449EC-7EA2-4DE7-A6A6-7DFBAAEBB6FB")

.comdef IApplicationViewConsolidatedEventArgs : public IInspectable

    get_IsUserInitiated proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIProjectionManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIProjectionManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IProjectionManagerStatics <L"Windows.UI.ViewManagement.IProjectionManagerStatics">

DEFINE_IIDX(IProjectionManagerStatics, "B65F913D-E2F0-4FFD-BA95-34241647E45C")

.comdef IProjectionManagerStatics : public IInspectable

    StartProjectingAsync proc :INT32, :INT32, :ptr
    SwapDisplaysForViewsAsync proc :INT32, :INT32, :ptr
    StopProjectingAsync proc :INT32, :INT32, :ptr
    get_ProjectionDisplayAvailable proc :ptr
    add_ProjectionDisplayAvailableChanged proc :ptr, :ptr
    remove_ProjectionDisplayAvailableChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIInputPaneVisibilityEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIInputPaneVisibilityEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IInputPaneVisibilityEventArgs <L"Windows.UI.ViewManagement.IInputPaneVisibilityEventArgs">

DEFINE_IIDX(IInputPaneVisibilityEventArgs, "D243E016-D907-4FCC-BB8D-F77BAA5028F1")

.comdef IInputPaneVisibilityEventArgs : public IInspectable

    get_OccludedRect	proc :ptr
    put_EnsuredFocusedElementInView proc :BOOL
    get_EnsuredFocusedElementInView proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIInputPane_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIInputPane_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IInputPane <L"Windows.UI.ViewManagement.IInputPane">

DEFINE_IIDX(IInputPane, "640ADA70-06F3-4C87-A678-9829C9127C28")

.comdef IInputPane : public IInspectable

    add_Showing		proc :ptr, :ptr
    remove_Showing	proc :EventRegistrationToken
    add_Hiding		proc :ptr, :ptr
    remove_Hiding	proc :EventRegistrationToken
    get_OccludedRect	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIInputPaneStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIInputPaneStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IInputPaneStatics <L"Windows.UI.ViewManagement.IInputPaneStatics">

DEFINE_IIDX(IInputPaneStatics, "95F4AF3A-EF47-424A-9741-FD2815EBA2BD")

.comdef IInputPaneStatics : public IInspectable

    GetForCurrentView	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIAccessibilitySettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIAccessibilitySettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IAccessibilitySettings <L"Windows.UI.ViewManagement.IAccessibilitySettings">

DEFINE_IIDX(IAccessibilitySettings, "FE0E8147-C4C0-4562-B962-1327B52AD5B9")

.comdef IAccessibilitySettings : public IInspectable

    get_HighContrast	proc :ptr
    get_HighContrastScheme proc :ptr
    add_HighContrastChanged proc :ptr, :ptr
    remove_HighContrastChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CViewManagement_CIUISettings_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CViewManagement_CIUISettings_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_ViewManagement_IUISettings <L"Windows.UI.ViewManagement.IUISettings">

DEFINE_IIDX(IUISettings, "85361600-1C63-4627-BCB1-3A89E0BC9C55")

.comdef IUISettings : public IInspectable

    get_HandPreference	proc :ptr
    get_CursorSize	proc :ptr
    get_ScrollBarSize	proc :ptr
    get_ScrollBarArrowSize proc :ptr
    get_ScrollBarThumbBoxSize proc :ptr
    get_MessageDuration proc :ptr
    get_AnimationsEnabled proc :ptr
    get_CaretBrowsingEnabled proc :ptr
    get_CaretBlinkRate	proc :ptr
    get_CaretWidth	proc :ptr
    get_DoubleClickTime proc :ptr
    get_MouseHoverTime	proc :ptr
    UIElementColor	proc :LONG, :ptr
   .ends

endif

.endn
.endn
.endn

define RuntimeClass_Windows_UI_ViewManagement_ApplicationView <L"Windows.UI.ViewManagement.ApplicationView">
define RuntimeClass_Windows_UI_ViewManagement_ApplicationViewConsolidatedEventArgs <L"Windows.UI.ViewManagement.ApplicationViewConsolidatedEventArgs">
define RuntimeClass_Windows_UI_ViewManagement_ApplicationViewSwitcher <L"Windows.UI.ViewManagement.ApplicationViewSwitcher">
define RuntimeClass_Windows_UI_ViewManagement_ProjectionManager <L"Windows.UI.ViewManagement.ProjectionManager">
define RuntimeClass_Windows_UI_ViewManagement_InputPaneVisibilityEventArgs <L"Windows.UI.ViewManagement.InputPaneVisibilityEventArgs">
define RuntimeClass_Windows_UI_ViewManagement_InputPane <L"Windows.UI.ViewManagement.InputPane">
define RuntimeClass_Windows_UI_ViewManagement_AccessibilitySettings <L"Windows.UI.ViewManagement.AccessibilitySettings">
define RuntimeClass_Windows_UI_ViewManagement_UISettings <L"Windows.UI.ViewManagement.UISettings">

HSTRING_UserSize	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr DWORD, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr DWORD, :DWORD, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr DWORD, :LPBYTE, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr DWORD, :ptr HSTRING

endif

