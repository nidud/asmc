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

ifndef __windows2Emanagement2Edeployment_h__
define __windows2Emanagement2Edeployment_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.ApplicationModel.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CManagement__CDeployment__CPackageUserInformation_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CManagement__CDeployment__CPackageUserInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterator_1_Windows__CManagement__CDeployment__CPackageUserInformation, "75660566-ae43-5858-ada6-d57ddae90277")

.comdef __FIIterator_1_Windows__CManagement__CDeployment__CPackageUserInformation : public IInspectable

    get_Current		proc :ptr ptr ABI::Windows::Management::Deployment::IPackageUserInformation
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :dword
   .ends

endif

ifndef ____FIIterable_1_Windows__CManagement__CDeployment__CPackageUserInformation_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CManagement__CDeployment__CPackageUserInformation_INTERFACE_DEFINED__

DEFINE_IIDX(__FIIterable_1_Windows__CManagement__CDeployment__CPackageUserInformation, "341348b9-52c8-5b57-9e91-f19f2a05b188")

.comdef __FIIterable_1_Windows__CManagement__CDeployment__CPackageUserInformation : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress, "f1b926d1-1796-597a-9bea-6c6449d03eef")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress, "6e1c7129-61e0-5d88-9fd4-f3ce65a05719")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress_INTERFACE_DEFINED__

DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress, "5a97aab7-b6ea-55ac-a5dc-d5b164d94e94")

.comdef __FIAsyncOperationWithProgress_2_Windows__CManagement__CDeployment__CDeploymentResult_Windows__CManagement__CDeployment__CDeploymentProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace ABI
.namespace Windows
.namespace Management
.namespace Deployment

.enum DeploymentProgressState {
    DeploymentProgressState_Queued	= 0,
    DeploymentProgressState_Processing	= 1
    }

.enum DeploymentOptions {
    DeploymentOptions_None	= 0,
    DeploymentOptions_ForceApplicationShutdown	= 0x1,
    DeploymentOptions_DevelopmentMode	= 0x2,
    DeploymentOptions_InstallAllResources	= 0x20
    }

.enum RemovalOptions {
    RemovalOptions_None = 0,
    RemovalOptions_PreserveApplicationData	= 0x1000
    }

.enum PackageTypes {
    PackageTypes_None	= 0,
    PackageTypes_Main	= 0x1,
    PackageTypes_Framework	= 0x2,
    PackageTypes_Resource	= 0x4,
    PackageTypes_Bundle = 0x8
    }

.enum PackageInstallState {
    PackageInstallState_NotInstalled	= 0,
    PackageInstallState_Staged	= 1,
    PackageInstallState_Installed	= 2
    }

.enum PackageState {
    PackageState_Normal = 0,
    PackageState_LicenseInvalid = 1,
    PackageState_Modified	= 2,
    PackageState_Tampered	= 3
    }

.template DeploymentProgress
    state	LONG ?
    percentage	UINT32 ?
   .ends

ifndef ____x_ABI_CWindows_CManagement_CDeployment_CIDeploymentResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CDeployment_CIDeploymentResult_INTERFACE_DEFINED__

DEFINE_IIDX(IDeploymentResult, "2563B9AE-B77D-4C1F-8A7B-20E6AD515EF3")

.comdef IDeploymentResult : public IInspectable

    get_ErrorText	proc :ptr
    get_ActivityId	proc :ptr
    get_ExtendedErrorCode proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CManagement_CDeployment_CIPackageUserInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CDeployment_CIPackageUserInformation_INTERFACE_DEFINED__

DEFINE_IIDX(IPackageUserInformation, "F6383423-FA09-4CBC-9055-15CA275E2E7E")

.comdef IPackageUserInformation : public IInspectable

    get_UserSecurityId	proc :ptr HSTRING
    get_InstallState	proc :ptr ABI::Windows::Management::Deployment::PackageInstallState
   .ends

endif

ifndef ____x_ABI_CWindows_CManagement_CDeployment_CIPackageManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CDeployment_CIPackageManager_INTERFACE_DEFINED__

DEFINE_IIDX(IPackageManager, "9A7D4B65-5E8F-4FC7-A2E5-7F6925CB8B53")

.comdef IPackageManager : public IInspectable

    AddPackageAsync	proc :ptr, :ptr, :LONG, :ptr
    UpdatePackageAsync	proc :ptr, :ptr, :LONG, :ptr
    RemovePackageAsync	proc :HSTRING, :ptr
    StagePackageAsync	proc :ptr, :ptr, :ptr
    RegisterPackageAsync proc :ptr, :ptr, :LONG, :ptr
    FindPackages	proc :ptr ptr __FIIterable_1_Windows__CApplicationModel__CPackage
    FindPackagesByUserSecurityId proc :HSTRING, :ptr
    FindPackagesByNamePublisher proc :HSTRING, :HSTRING, :ptr
    FindPackagesByUserSecurityIdNamePublisher proc :HSTRING, :HSTRING, :HSTRING, :ptr
    FindUsers		proc :HSTRING, :ptr __FIIterable_1_Windows__CManagement__CDeployment__CPackageUserInformation
    SetPackageState	proc :HSTRING, :LONG
    FindPackageByPackageFullName proc :HSTRING, :ptr
    CleanupPackageForUserAsync proc :HSTRING, :HSTRING, :ptr
    FindPackagesByPackageFamilyName proc :HSTRING, :ptr
    FindPackagesByUserSecurityIdPackageFamilyName proc :HSTRING, :HSTRING, :ptr
    FindPackageByUserSecurityIdPackageFullName proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CManagement_CDeployment_CIPackageManager2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CManagement_CDeployment_CIPackageManager2_INTERFACE_DEFINED__

DEFINE_IIDX(IPackageManager2, "F7AAD08D-0840-46F2-B5D8-CAD47693A095")

.comdef IPackageManager2 : public IInspectable

    RemovePackageWithOptionsAsync proc :HSTRING, :LONG, :ptr
    StagePackageWithOptionsAsync proc :ptr, :ptr, :LONG, :ptr
    RegisterPackageByFullNameAsync proc :HSTRING, :ptr, :LONG, :ptr
    FindPackagesWithPackageTypes proc :LONG, :ptr
    FindPackagesByUserSecurityIdWithPackageTypes proc :HSTRING, :LONG, :ptr
    FindPackagesByNamePublisherWithPackageTypes proc :HSTRING, :HSTRING, :LONG, :ptr
    FindPackagesByUserSecurityIdNamePublisherWithPackageTypes proc :HSTRING, :HSTRING, :HSTRING, :LONG, :ptr
    FindPackagesByPackageFamilyNameWithPackageTypes proc :HSTRING, :LONG, :ptr
    FindPackagesByUserSecurityIdPackageFamilyNameWithPackageTypes proc :HSTRING, :HSTRING, :LONG, :ptr
    StageUserDataAsync	proc :HSTRING, :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Management_Deployment_DeploymentResult_DEFINED
define RUNTIMECLASS_Windows_Management_Deployment_DeploymentResult_DEFINED
define RuntimeClass_Windows_Management_Deployment_DeploymentResult <L"Windows.Management.Deployment.DeploymentResult">
endif
ifndef RUNTIMECLASS_Windows_Management_Deployment_PackageUserInformation_DEFINED
define RUNTIMECLASS_Windows_Management_Deployment_PackageUserInformation_DEFINED
define RuntimeClass_Windows_Management_Deployment_PackageUserInformation <L"Windows.Management.Deployment.PackageUserInformation">
endif
ifndef RUNTIMECLASS_Windows_Management_Deployment_PackageManager_DEFINED
define RUNTIMECLASS_Windows_Management_Deployment_PackageManager_DEFINED
define RuntimeClass_Windows_Management_Deployment_PackageManager <L"Windows.Management.Deployment.PackageManager">
endif

endif

