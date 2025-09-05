ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Egraphics2Edisplay_h__
define __windows2Egraphics2Edisplay_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

ifndef ____FITypedEventHandler_2_Windows__CGraphics__CDisplay__CDisplayInformation_IInspectable_INTERFACE_DEFINED__
define ____FITypedEventHandler_2_Windows__CGraphics__CDisplay__CDisplayInformation_IInspectable_INTERFACE_DEFINED__
DEFINE_IIDX(__FITypedEventHandler_2_Windows__CGraphics__CDisplay__CDisplayInformation_IInspectable, "86c4f619-67b6-51c7-b30d-d8cf13625327")

.comdef __FITypedEventHandler_2_Windows__CGraphics__CDisplay__CDisplayInformation_IInspectable : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

.namespace Windows
.namespace Graphics
.namespace Display

.enum DisplayOrientations {
    DisplayOrientations_None	= 0,
    DisplayOrientations_Landscape	= 0x1,
    DisplayOrientations_Portrait	= 0x2,
    DisplayOrientations_LandscapeFlipped	= 0x4,
    DisplayOrientations_PortraitFlipped = 0x8
    }

.enum ResolutionScale {
    ResolutionScale_Invalid	= 0,
    ResolutionScale_Scale100Percent	= 100,
    ResolutionScale_Scale120Percent	= 120,
    ResolutionScale_Scale140Percent	= 140,
    ResolutionScale_Scale150Percent	= 150,
    ResolutionScale_Scale160Percent	= 160,
    ResolutionScale_Scale180Percent	= 180,
    ResolutionScale_Scale225Percent	= 225
    }

ifndef ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayPropertiesEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayPropertiesEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IDisplayPropertiesEventHandler, "DBDD8B01-F1A1-46D1-9EE3-543BCC995980")

.comdef IDisplayPropertiesEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayInformationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Display_IDisplayInformationStatics <L"Windows.Graphics.Display.IDisplayInformationStatics">
DEFINE_IIDX(IDisplayInformationStatics, "C6A02A6C-D452-44DC-BA07-96F3C6ADF9D1")

.comdef IDisplayInformationStatics : public IInspectable

    GetForCurrentView	proc :ptr
    get_AutoRotationPreferences proc :ptr
    put_AutoRotationPreferences proc :Windows::Graphics::Display::DisplayOrientations
    add_DisplayContentsInvalidated proc :ptr, :ptr
    remove_DisplayContentsInvalidated proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Display_IDisplayInformation <L"Windows.Graphics.Display.IDisplayInformation">
DEFINE_IIDX(IDisplayInformation, "BED112AE-ADC3-4DC9-AE65-851F4D7D4799")

.comdef IDisplayInformation : public IInspectable

    get_CurrentOrientation proc :ptr
    get_NativeOrientation proc :ptr
    add_OrientationChanged proc :ptr, :ptr
    remove_OrientationChanged proc :EventRegistrationToken
    get_ResolutionScale proc :ptr
    get_LogicalDpi	proc :ptr
    get_RawDpiX		proc :ptr
    get_RawDpiY		proc :ptr
    add_DpiChanged	proc :ptr, :ptr
    remove_DpiChanged	proc :EventRegistrationToken
    get_StereoEnabled	proc :ptr
    add_StereoEnabledChanged proc :ptr, :ptr
    remove_StereoEnabledChanged proc :EventRegistrationToken
    GetColorProfileAsync proc :ptr
    add_ColorProfileChanged proc :ptr, :ptr
    remove_ColorProfileChanged proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayPropertiesStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CGraphics_CDisplay_CIDisplayPropertiesStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Graphics_Display_IDisplayPropertiesStatics <L"Windows.Graphics.Display.IDisplayPropertiesStatics">
DEFINE_IIDX(IDisplayPropertiesStatics, "6937ED8D-30EA-4DED-8271-4553FF02F68A")

.comdef IDisplayPropertiesStatics : public IInspectable

    get_CurrentOrientation proc :ptr
    get_NativeOrientation proc :ptr
    get_AutoRotationPreferences proc :ptr
    put_AutoRotationPreferences proc :Windows::Graphics::Display::DisplayOrientations
    add_OrientationChanged proc :ptr, :ptr
    remove_OrientationChanged proc :EventRegistrationToken
    get_ResolutionScale proc :ptr
    get_LogicalDpi	proc :ptr
    add_LogicalDpiChanged proc :ptr, :ptr
    remove_LogicalDpiChanged proc :EventRegistrationToken
    get_StereoEnabled	proc :ptr
    add_StereoEnabledChanged proc :ptr, :ptr
    remove_StereoEnabledChanged proc :EventRegistrationToken
    GetColorProfileAsync proc :ptr
    add_ColorProfileChanged proc :ptr, :ptr
    remove_ColorProfileChanged proc :EventRegistrationToken
    add_DisplayContentsInvalidated proc :ptr, :ptr
    remove_DisplayContentsInvalidated proc :EventRegistrationToken
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Graphics_Display_DisplayInformation_DEFINED
define RUNTIMECLASS_Windows_Graphics_Display_DisplayInformation_DEFINED
define RuntimeClass_Windows_Graphics_Display_DisplayInformation <L"Windows.Graphics.Display.DisplayInformation">
endif
ifndef RUNTIMECLASS_Windows_Graphics_Display_DisplayProperties_DEFINED
define RUNTIMECLASS_Windows_Graphics_Display_DisplayProperties_DEFINED
define RuntimeClass_Windows_Graphics_Display_DisplayProperties <L"Windows.Graphics.Display.DisplayProperties">
endif

endif
