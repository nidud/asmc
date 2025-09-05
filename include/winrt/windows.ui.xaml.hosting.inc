ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eui2Examl2Ehosting_h__
define __windows2Eui2Examl2Ehosting_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.UI.Xaml.inc

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Hosting

ifndef ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterHost_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterHost_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Hosting_IXamlUIPresenterHost <L"Windows.UI.Xaml.Hosting.IXamlUIPresenterHost">
DEFINE_IIDX(IXamlUIPresenterHost, "AAFB84CD-9F6D-4F80-AC2C-0E6CB9F31659")

.comdef IXamlUIPresenterHost : public IInspectable

    ResolveFileResource proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterHost2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterHost2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Hosting_IXamlUIPresenterHost2 <L"Windows.UI.Xaml.Hosting.IXamlUIPresenterHost2">
DEFINE_IIDX(IXamlUIPresenterHost2, "61595672-7CA4-4A21-B56A-88F4812388CA")

.comdef IXamlUIPresenterHost2 : public IInspectable

    GetGenericXamlFilePath proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenter_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Hosting_IXamlUIPresenter <L"Windows.UI.Xaml.Hosting.IXamlUIPresenter">
DEFINE_IIDX(IXamlUIPresenter, "A714944A-1619-4FC6-B31B-89512EF022A2")

.comdef IXamlUIPresenter : public IInspectable

    get_RootElement     proc :ptr
    put_RootElement     proc :ptr
    get_ThemeKey        proc :ptr
    put_ThemeKey        proc :HSTRING
    get_ThemeResourcesXaml proc :ptr
    put_ThemeResourcesXaml proc :HSTRING
    SetSize             proc :INT32, :INT32
    Render              proc
    Present             proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Hosting_IXamlUIPresenterStatics <L"Windows.UI.Xaml.Hosting.IXamlUIPresenterStatics">
DEFINE_IIDX(IXamlUIPresenterStatics, "71EAEAC8-45E1-4192-85AA-3A422EDD23CF")

.comdef IXamlUIPresenterStatics : public IInspectable

    get_CompleteTimelinesAutomatically proc :ptr
    put_CompleteTimelinesAutomatically proc :boolean
    SetHost             proc :ptr
    NotifyWindowSizeChanged proc
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterStatics2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CHosting_CIXamlUIPresenterStatics2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Hosting_IXamlUIPresenterStatics2 <L"Windows.UI.Xaml.Hosting.IXamlUIPresenterStatics2">
DEFINE_IIDX(IXamlUIPresenterStatics2, "5C6B68D2-CF1C-4F53-BF09-6A745F7A9703")

.comdef IXamlUIPresenterStatics2 : public IInspectable

    GetFlyoutPlacementTargetInfo proc :ptr, :Windows::UI::Xaml::Controls::Primitives::FlyoutPlacementMode, :ptr, :ptr, :ptr
    GetFlyoutPlacement  proc :Windows::Foundation::Rect, :Windows::Foundation::Size, :Windows::Foundation::Size, :Windows::Foundation::Rect, :Windows::UI::Xaml::Controls::Primitives::FlyoutPlacementMode, :boolean, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Hosting_XamlUIPresenter_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Hosting_XamlUIPresenter_DEFINED
define RuntimeClass_Windows_UI_Xaml_Hosting_XamlUIPresenter <L"Windows.UI.Xaml.Hosting.XamlUIPresenter">
endif

endif
