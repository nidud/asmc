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

ifndef __windows2Eui2Examl2Enavigation_h__
define __windows2Eui2Examl2Enavigation_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.UI.Xaml.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry, "b89ca96c-ded1-53bd-8744-caa84e87ba87")

.comdef __FIIterator_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry, "dd2278a5-4c14-5967-8a41-9a47c3c5c4a7")

.comdef __FIIterable_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry, "af6d7eac-086f-5c5f-be4b-0858af7506f7")

.comdef __FIVectorView_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry, "e561a13f-89a1-5ef2-a3fe-eba1b4539b46")

.comdef __FIVector_1_Windows__CUI__CXaml__CNavigation__CPageStackEntry : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    GetView		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    SetAt		proc :SINT, :ptr
    InsertAt		proc :SINT, :ptr
    RemoveAt		proc :SINT
    Append		proc :ptr
    RemoveAtEnd		proc
    Clear		proc
    GetMany		proc :SINT, :SINT, :ptr, :ptr
    ReplaceAll		proc :SINT, :ptr
   .ends

endif

.namespace Windows
.namespace UI
.namespace Xaml
.namespace Navigation

.enum NavigationCacheMode {
    NavigationCacheMode_Disabled	= 0,
    NavigationCacheMode_Required	= 1,
    NavigationCacheMode_Enabled = 2
    }

.enum NavigationMode {
    NavigationMode_New	= 0,
    NavigationMode_Back = 1,
    NavigationMode_Forward	= 2,
    NavigationMode_Refresh	= 3
    }

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CILoadCompletedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CILoadCompletedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(ILoadCompletedEventHandler, "AEBAF785-43FC-4E2C-95C3-97AE84EABC8E")

.comdef ILoadCompletedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INavigatedEventHandler, "7BD1CF54-23CF-4CCE-B2F5-4CE78D96896E")

.comdef INavigatedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatingCancelEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INavigatingCancelEventHandler, "75D6A78F-A302-4489-9898-24EA49182910")

.comdef INavigatingCancelEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationFailedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INavigationFailedEventHandler, "4DAB4671-12B2-43C7-B892-9BE2DCD3E88D")

.comdef INavigationFailedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationStoppedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(INavigationStoppedEventHandler, "F0117DDB-12FA-4D8D-8B26-B383D09C2B3C")

.comdef INavigationStoppedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_INavigatingCancelEventArgs <L"Windows.UI.Xaml.Navigation.INavigatingCancelEventArgs">
DEFINE_IIDX(INavigatingCancelEventArgs, "FD1D67AE-EAFB-4079-BE80-6DC92A03AEDF")

.comdef INavigatingCancelEventArgs : public IInspectable

    get_Cancel		proc :ptr
    put_Cancel		proc :boolean
    get_NavigationMode	proc :ptr
    get_SourcePageType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigatingCancelEventArgs2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_INavigatingCancelEventArgs2 <L"Windows.UI.Xaml.Navigation.INavigatingCancelEventArgs2">
DEFINE_IIDX(INavigatingCancelEventArgs2, "5407B704-8147-4343-838F-DD1EE908C137")

.comdef INavigatingCancelEventArgs2 : public IInspectable

    get_Parameter	proc :ptr
    get_NavigationTransitionInfo proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_INavigationEventArgs <L"Windows.UI.Xaml.Navigation.INavigationEventArgs">
DEFINE_IIDX(INavigationEventArgs, "B6AA9834-6691-44D1-BDF7-58820C27B0D0")

.comdef INavigationEventArgs : public IInspectable

    get_Content		proc :ptr
    get_Parameter	proc :ptr
    get_SourcePageType	proc :ptr
    get_NavigationMode	proc :ptr
    get_Uri		proc :ptr
    put_Uri		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationEventArgs2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationEventArgs2_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_INavigationEventArgs2 <L"Windows.UI.Xaml.Navigation.INavigationEventArgs2">
DEFINE_IIDX(INavigationEventArgs2, "DBFF71D9-979A-4B2E-A49B-3BB17FDEF574")

.comdef INavigationEventArgs2 : public IInspectable

    get_NavigationTransitionInfo proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CINavigationFailedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_INavigationFailedEventArgs <L"Windows.UI.Xaml.Navigation.INavigationFailedEventArgs">
DEFINE_IIDX(INavigationFailedEventArgs, "11C1DFF7-36C2-4102-B2EF-0217A97289B3")

.comdef INavigationFailedEventArgs : public IInspectable

    get_Exception	proc :ptr
    get_Handled		proc :ptr
    put_Handled		proc :boolean
    get_SourcePageType	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CIPageStackEntry_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_IPageStackEntry <L"Windows.UI.Xaml.Navigation.IPageStackEntry">
DEFINE_IIDX(IPageStackEntry, "EF8814A6-9388-4ACA-8572-405194069080")

.comdef IPageStackEntry : public IInspectable

    get_SourcePageType	proc :ptr
    get_Parameter	proc :ptr
    get_NavigationTransitionInfo proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CIPageStackEntryStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_IPageStackEntryStatics <L"Windows.UI.Xaml.Navigation.IPageStackEntryStatics">
DEFINE_IIDX(IPageStackEntryStatics, "ACEFF8E3-246C-4033-9F01-01CB0DA5254E")

.comdef IPageStackEntryStatics : public IInspectable

    get_SourcePageTypeProperty proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CUI_CXaml_CNavigation_CIPageStackEntryFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_UI_Xaml_Navigation_IPageStackEntryFactory <L"Windows.UI.Xaml.Navigation.IPageStackEntryFactory">
DEFINE_IIDX(IPageStackEntryFactory, "4454048A-A8B9-4F78-9B84-1F51F58851FF")

.comdef IPageStackEntryFactory : public IInspectable

    CreateInstance	proc :Windows::UI::Xaml::Interop::TypeName, :ptr, :ptr, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_UI_Xaml_Navigation_NavigationEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Navigation_NavigationEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Navigation_NavigationEventArgs <L"Windows.UI.Xaml.Navigation.NavigationEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Navigation_NavigatingCancelEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Navigation_NavigatingCancelEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Navigation_NavigatingCancelEventArgs <L"Windows.UI.Xaml.Navigation.NavigatingCancelEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Navigation_NavigationFailedEventArgs_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Navigation_NavigationFailedEventArgs_DEFINED
define RuntimeClass_Windows_UI_Xaml_Navigation_NavigationFailedEventArgs <L"Windows.UI.Xaml.Navigation.NavigationFailedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_UI_Xaml_Navigation_PageStackEntry_DEFINED
define RUNTIMECLASS_Windows_UI_Xaml_Navigation_PageStackEntry_DEFINED
define RuntimeClass_Windows_UI_Xaml_Navigation_PageStackEntry <L"Windows.UI.Xaml.Navigation.PageStackEntry">
endif

endif
