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

ifndef __windows2Eapplicationmodel_h__
define __windows2Eapplicationmodel_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.inc
include Windows.System.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CApplicationModel__CPackage_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CApplicationModel__CPackage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CApplicationModel__CPackage, "0217f069-025c-5ee6-a87f-e782e3b623ae")

.comdef __FIIterator_1_Windows__CApplicationModel__CPackage : public IInspectable

    get_Current		proc :ptr ptr Windows::ApplicationModel::IPackage
    get_HasCurrent	proc :ptr boolean
    MoveNext		proc :ptr boolean
    GetMany		proc :SINT, :ptr ptr Windows::ApplicationModel::IPackage, :ptr UINT
   .ends

endif

ifndef ____FIIterable_1_Windows__CApplicationModel__CPackage_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CApplicationModel__CPackage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CApplicationModel__CPackage, "69ad6aa7-0c49-5f27-a5eb-ef4d59467b6d")

.comdef __FIIterable_1_Windows__CApplicationModel__CPackage : public IInspectable

    First		proc :ptr ptr __FIIterator_1_Windows__CApplicationModel__CPackage
   .ends

endif

ifndef ____FIVectorView_1_Windows__CApplicationModel__CPackage_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CApplicationModel__CPackage_INTERFACE_DEFINED__

DEFINE_IIDX(__FIVectorView_1_Windows__CApplicationModel__CPackage, "0263c4d4-195c-5dc5-a7ca-6806ceca420b")

.comdef __FIVectorView_1_Windows__CApplicationModel__CPackage : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :UINT
    IndexOf		proc :ptr, :UINT, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :UINT
   .ends

endif

ifndef ____FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs_INTERFACE_DEFINED__
define ____FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs_INTERFACE_DEFINED__

DEFINE_IIDX(__FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs, "338579bf-1a35-5cc4-a622-a6f384fd892c")

.comdef __FIEventHandler_1_Windows__CApplicationModel__CSuspendingEventArgs : public IUnknown

    _Invoke		proc :ptr, :ptr
    .ends

endif

.namespace Windows
.namespace ApplicationModel

.template PackageVersion
    Major	UINT16 ?
    Minor	UINT16 ?
    Build	UINT16 ?
    Revision	UINT16 ?
   .ends


ifndef ____x_ABI_CWindows_CApplicationModel_CISuspendingDeferral_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CISuspendingDeferral_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_ISuspendingDeferral <L"Windows.ApplicationModel.ISuspendingDeferral">

DEFINE_IIDX(ISuspendingDeferral, "59140509-8BC9-4EB4-B636-DABDC4F46F66")

.comdef ISuspendingDeferral : public IInspectable

    Complete		proc
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CISuspendingOperation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CISuspendingOperation_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_ISuspendingOperation <L"Windows.ApplicationModel.ISuspendingOperation">

DEFINE_IIDX(ISuspendingOperation, "9DA4CA41-20E1-4E9B-9F65-A9F435340C3A")

.comdef ISuspendingOperation : public IInspectable

    GetDeferral		proc :ptr
    get_Deadline	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CISuspendingEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CISuspendingEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_ISuspendingEventArgs <L"Windows.ApplicationModel.ISuspendingEventArgs">

DEFINE_IIDX(ISuspendingEventArgs, "96061C05-2DBA-4D08-B0BD-2B30A131C6AA")

.comdef ISuspendingEventArgs : public IInspectable

    get_SuspendingOperation proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CIPackageId_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CIPackageId_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_IPackageId <L"Windows.ApplicationModel.IPackageId">

DEFINE_IIDX(IPackageId, "1ADB665E-37C7-4790-9980-DD7AE74E8BB2")

.comdef IPackageId : public IInspectable

    get_Name		proc :ptr HSTRING
    get_Version		proc :ptr Windows::ApplicationModel::PackageVersion
    get_Architecture	proc :ptr Windows::System::ProcessorArchitecture
    get_ResourceId	proc :ptr HSTRING
    get_Publisher	proc :ptr HSTRING
    get_PublisherId	proc :ptr HSTRING
    get_FullName	proc :ptr HSTRING
    get_FamilyName	proc :ptr HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CIPackage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CIPackage_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_IPackage <L"Windows.ApplicationModel.IPackage">

DEFINE_IIDX(IPackage, "163C792F-BD75-413C-BF23-B1FE7B95D825")

.comdef IPackage : public IInspectable

    get_Id		proc :ptr ptr Windows::ApplicationModel::IPackageId
    get_InstalledLocation proc :ptr ptr Windows::Storage::IStorageFolder
    get_IsFramework	proc :ptr boolean
    get_Dependencies	proc :ptr ptr __FIVectorView_1_Windows__CApplicationModel__CPackage
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CIPackage2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CIPackage2_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_IPackage2 <L"Windows.ApplicationModel.IPackage2">

DEFINE_IIDX(IPackage2, "A6612FB6-7688-4ACE-95FB-359538E7AA01")

.comdef IPackage2 : public IInspectable

    get_DisplayName	proc :ptr
    get_PublisherDisplayName proc :ptr
    get_Description	proc :ptr
    get_Logo		proc :ptr
    get_IsResourcePackage proc :ptr
    get_IsBundle	proc :ptr
    get_IsDevelopmentMode proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CIPackageStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CIPackageStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_IPackageStatics <L"Windows.ApplicationModel.IPackageStatics">

DEFINE_IIDX(IPackageStatics, "4E534BDF-2960-4878-97A4-9624DEB72F2D")

.comdef IPackageStatics : public IInspectable

    get_Current		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CApplicationModel_CIDesignModeStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CApplicationModel_CIDesignModeStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_ApplicationModel_IDesignModeStatics <L"Windows.ApplicationModel.IDesignModeStatics">

DEFINE_IIDX(IDesignModeStatics, "2C3893CC-F81A-4E7A-B857-76A80887E185")

.comdef IDesignModeStatics : public IInspectable

    get_DesignModeEnabled proc :ptr
   .ends

endif

.endn
.endn

define RuntimeClass_Windows_ApplicationModel_SuspendingEventArgs <L"Windows.ApplicationModel.SuspendingEventArgs">
define RuntimeClass_Windows_ApplicationModel_SuspendingDeferral <L"Windows.ApplicationModel.SuspendingDeferral">
define RuntimeClass_Windows_ApplicationModel_SuspendingOperation <L"Windows.ApplicationModel.SuspendingOperation">
define RuntimeClass_Windows_ApplicationModel_PackageId <L"Windows.ApplicationModel.PackageId">
define RuntimeClass_Windows_ApplicationModel_Package <L"Windows.ApplicationModel.Package">
define RuntimeClass_Windows_ApplicationModel_DesignMode <L"Windows.ApplicationModel.DesignMode">

HSTRING_UserSize	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :DWORD, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif
