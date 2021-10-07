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

ifndef __windows2Eapplicationmodel2Ecore_h__
define __windows2Eapplicationmodel2Ecore_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.inc
include Windows.ApplicationModel.Activation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CApplicationModel__CCore__CCoreApplicationView_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CCore__CCoreApplicationView_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CCore__CCoreApplicationView, "4f5f6944-264b-5868-809e-c7ac1ac5edad")

.comdef __FIIterator_1_Windows__CApplicationModel__CCore__CCoreApplicationView : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CCore__CCoreApplicationView_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CCore__CCoreApplicationView_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CCore__CCoreApplicationView, "32bc12d1-2653-5a41-a55e-88a12af2026a")

.comdef __FIIterable_1_Windows__CApplicationModel__CCore__CCoreApplicationView : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CCore__CCoreApplicationView_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CCore__CCoreApplicationView_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CCore__CCoreApplicationView, "de9e16c4-1b7c-5126-b1d8-7cd04f13bd08")

.comdef __FIVectorView_1_Windows__CApplicationModel__CCore__CCoreApplicationView : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CApplicationModel__CCore__CUnhandledErrorDetectedEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CApplicationModel__CCore__CUnhandledErrorDetectedEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FIEventHandler_1_Windows__CApplicationModel__CCore__CUnhandledErrorDetectedEventArgs, "f68bc421-6b54-559b-9cdd-489aad0bd41d")

.comdef __FIEventHandler_1_Windows__CApplicationModel__CCore__CUnhandledErrorDetectedEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace ABI
.namespace Windows
.namespace ApplicationModel
.namespace Core

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CIFrameworkView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CIFrameworkView_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_IFrameworkView <L"Windows.ApplicationModel.Core.IFrameworkView">

DEFINE_IIDX(IFrameworkView, "FAAB5CD0-8924-45AC-AD0F-A08FAE5D0324")

.comdef IFrameworkView : public IInspectable

    Initialize		proc :ptr
    SetWindow		proc :ptr
    Load		proc :HSTRING
    Run			proc
    Uninitialize	proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CIFrameworkViewSource_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CIFrameworkViewSource_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_IFrameworkViewSource <L"Windows.ApplicationModel.Core.IFrameworkViewSource">

DEFINE_IIDX(IFrameworkViewSource, "CD770614-65C4-426C-9494-34FC43554862")

.comdef IFrameworkViewSource : public IInspectable

    CreateView		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplication_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplication_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreApplication <L"Windows.ApplicationModel.Core.ICoreApplication">

DEFINE_IIDX(ICoreApplication, "0AACF7A4-5E1D-49DF-8034-FB6A68BC5ED1")

.comdef ICoreApplication : public IInspectable

    get_Id		proc :ptr
    add_Suspending	proc :ptr, :ptr
    remove_Suspending	proc :EventRegistrationToken
    add_Resuming	proc :ptr, :ptr
    remove_Resuming	proc :EventRegistrationToken
    get_Properties	proc :ptr
    GetCurrentView	proc :ptr
    Run			proc :ptr
    RunWithActivationFactories proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationUseCount_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationUseCount_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreApplicationUseCount <L"Windows.ApplicationModel.Core.ICoreApplicationUseCount">

DEFINE_IIDX(ICoreApplicationUseCount, "518DC408-C077-475B-809E-0BC0C57E4B74")

.comdef ICoreApplicationUseCount : public IInspectable

    IncrementApplicationUseCount proc
    DecrementApplicationUseCount proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationExit_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationExit_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreApplicationExit <L"Windows.ApplicationModel.Core.ICoreApplicationExit">

DEFINE_IIDX(ICoreApplicationExit, "CF86461D-261E-4B72-9ACD-44ED2ACE6A29")

.comdef ICoreApplicationExit : public IInspectable

    Exit		proc
    add_Exiting		proc :ptr, :ptr
    remove_Exiting	proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreImmersiveApplication_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreImmersiveApplication_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreImmersiveApplication <L"Windows.ApplicationModel.Core.ICoreImmersiveApplication">

DEFINE_IIDX(ICoreImmersiveApplication, "1ADA0E3E-E4A2-4123-B451-DC96BF800419")

.comdef ICoreImmersiveApplication : public IInspectable

    get_Views		proc :ptr
    CreateNewView	proc :HSTRING, :HSTRING, :ptr
    get_MainView	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreImmersiveApplication2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreImmersiveApplication2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreImmersiveApplication2 <L"Windows.ApplicationModel.Core.ICoreImmersiveApplication2">

DEFINE_IIDX(ICoreImmersiveApplication2, "828E1E36-E9E3-4CFC-9B66-48B78EA9BB2C")

.comdef ICoreImmersiveApplication2 : public IInspectable

    CreateNewViewFromMainView proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationUnhandledError_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationUnhandledError_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreApplicationUnhandledError <L"Windows.ApplicationModel.Core.ICoreApplicationUnhandledError">

DEFINE_IIDX(ICoreApplicationUnhandledError, "F0E24AB0-DD09-42E1-B0BC-E0E131F78D7E")

.comdef ICoreApplicationUnhandledError : public IInspectable

    add_UnhandledErrorDetected proc :ptr, :ptr
    remove_UnhandledErrorDetected proc :EventRegistrationToken
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationView_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationView_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreApplicationView <L"Windows.ApplicationModel.Core.ICoreApplicationView">

DEFINE_IIDX(ICoreApplicationView, "638BB2DB-451D-4661-B099-414F34FFB9F1")

.comdef ICoreApplicationView : public IInspectable

    get_CoreWindow	proc :ptr
    add_Activated	proc :ptr, :ptr
    remove_Activated	proc :EventRegistrationToken
    get_IsMain		proc :ptr
    get_IsHosted	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationView2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CICoreApplicationView2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_ICoreApplicationView2 <L"Windows.ApplicationModel.Core.ICoreApplicationView2">

DEFINE_IIDX(ICoreApplicationView2, "68EB7ADF-917F-48EB-9AEB-7DE53E086AB1")

.comdef ICoreApplicationView2 : public IInspectable

    get_Dispatcher	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CIUnhandledErrorDetectedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CIUnhandledErrorDetectedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_IUnhandledErrorDetectedEventArgs <L"Windows.ApplicationModel.Core.IUnhandledErrorDetectedEventArgs">

DEFINE_IIDX(IUnhandledErrorDetectedEventArgs, "679AB78B-B336-4822-AC40-0D750F0B7A2B")

.comdef IUnhandledErrorDetectedEventArgs : public IInspectable

    get_UnhandledError	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CCore_CIUnhandledError_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CCore_CIUnhandledError_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_Core_IUnhandledError <L"Windows.ApplicationModel.Core.IUnhandledError">

DEFINE_IIDX(IUnhandledError, "9459B726-53B5-4686-9EAF-FA8162DC3980")

.comdef IUnhandledError : public IInspectable

    get_Handled		proc :ptr
    Propagate		proc
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_ApplicationModel_Core_CoreApplication_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Core_CoreApplication_DEFINED
define RuntimeClass_Windows_ApplicationModel_Core_CoreApplication <L"Windows.ApplicationModel.Core.CoreApplication">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Core_CoreApplicationView_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Core_CoreApplicationView_DEFINED
define RuntimeClass_Windows_ApplicationModel_Core_CoreApplicationView <L"Windows.ApplicationModel.Core.CoreApplicationView">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Core_UnhandledErrorDetectedEventArgs_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Core_UnhandledErrorDetectedEventArgs_DEFINED
define RuntimeClass_Windows_ApplicationModel_Core_UnhandledErrorDetectedEventArgs <L"Windows.ApplicationModel.Core.UnhandledErrorDetectedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_ApplicationModel_Core_UnhandledError_DEFINED
define RUNTIMECLASS_Windows_ApplicationModel_Core_UnhandledError_DEFINED
define RuntimeClass_Windows_ApplicationModel_Core_UnhandledError <L"Windows.ApplicationModel.Core.UnhandledError">
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

