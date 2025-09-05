ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Eenterprisedata_h__
define __windows2Esecurity2Eenterprisedata_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus, "e104f25b-b957-5ed4-b1c5-1993604cfeae")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus, "033efe7c-709e-53a8-8e64-cdab6bd1ed59")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CEnterpriseData__CFileProtectionStatus : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif


.namespace Windows
.namespace Security
.namespace EnterpriseData

.enum FileProtectionStatus {
    FileProtectionStatus_Undetermined	= 0,
    FileProtectionStatus_Unprotected	= 1,
    FileProtectionStatus_Revoked	= 2,
    FileProtectionStatus_Protected	= 3,
    FileProtectionStatus_ProtectedByOtherUser	= 4,
    FileProtectionStatus_ProtectedToOtherEnterprise	= 5,
    FileProtectionStatus_NotProtectable = 6
    }

ifndef ____x_ABI_CWindows_CSecurity_CEnterpriseData_CIFileRevocationManagerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CEnterpriseData_CIFileRevocationManagerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_EnterpriseData_IFileRevocationManagerStatics <L"Windows.Security.EnterpriseData.IFileRevocationManagerStatics">
DEFINE_IIDX(__x_ABI_CWindows_CSecurity_CEnterpriseData_CIFileRevocationManagerStatics, "256BBC3D-1C5D-4260-8C75-9144CFB78BA9")

.comdef __x_ABI_CWindows_CSecurity_CEnterpriseData_CIFileRevocationManagerStatics : public IInspectable

    ProtectAsync	proc :ptr, :HSTRING, :ptr
    CopyProtectionAsync proc :ptr, :ptr, :ptr
    Revoke		proc :HSTRING
    GetStatusAsync	proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_EnterpriseData_FileRevocationManager_DEFINED
define RUNTIMECLASS_Windows_Security_EnterpriseData_FileRevocationManager_DEFINED
define RuntimeClass_Windows_Security_EnterpriseData_FileRevocationManager <L"Windows.Security.EnterpriseData.FileRevocationManager">
endif

endif
