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

ifndef __windows2Emedia2Eprotection_h__
define __windows2Emedia2Eprotection_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem, "dfb9655c-8b22-511f-8eaf-3aea7521802b")

.comdef __FIIterator_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem, "07015868-578c-556b-8a35-4039a35d1d92")

.comdef __FIIterable_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem, "4a8793e2-33b8-5850-9943-6a94375caa89")

.comdef __FIVectorView_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem, "3623cc0c-c765-57fb-967d-c7cb6097bd78")

.comdef __FIVector_1_Windows__CMedia__CProtection__CRevocationAndRenewalItem : public IInspectable

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

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32, "b9da4aa0-26e0-5d69-a0c8-05716a406235")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32 : public IUnknown

    _Invoke		proc :ptr, :UINT32
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32, "ec067827-67d9-59a6-a57b-3e7ca12b89c1")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32 : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32, "595dcc09-9ad3-5094-800a-0883cce1ef01")

.comdef __FIAsyncOperationWithProgress_2_Windows__CMedia__CProtection__CRenewalStatus_UINT32 : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Media
.namespace Protection

.enum RevocationAndRenewalReasons {
    RevocationAndRenewalReasons_UserModeComponentLoad	= 0x1,
    RevocationAndRenewalReasons_KernelModeComponentLoad = 0x2,
    RevocationAndRenewalReasons_AppComponent	= 0x4,
    RevocationAndRenewalReasons_GlobalRevocationListLoadFailed	= 0x10,
    RevocationAndRenewalReasons_InvalidGlobalRevocationListSignature	= 0x20,
    RevocationAndRenewalReasons_GlobalRevocationListAbsent	= 0x1000,
    RevocationAndRenewalReasons_ComponentRevoked	= 0x2000,
    RevocationAndRenewalReasons_InvalidComponentCertificateExtendedKeyUse	= 0x4000,
    RevocationAndRenewalReasons_ComponentCertificateRevoked	= 0x8000,
    RevocationAndRenewalReasons_InvalidComponentCertificateRoot = 0x10000,
    RevocationAndRenewalReasons_ComponentHighSecurityCertificateRevoked = 0x20000,
    RevocationAndRenewalReasons_ComponentLowSecurityCertificateRevoked	= 0x40000,
    RevocationAndRenewalReasons_BootDriverVerificationFailed	= 0x100000,
    RevocationAndRenewalReasons_ComponentSignedWithTestCertificate	= 0x1000000,
    RevocationAndRenewalReasons_EncryptionFailure	= 0x10000000
    }

.enum RenewalStatus {
    RenewalStatus_NotStarted	= 0,
    RenewalStatus_UpdatesInProgress	= 1,
    RenewalStatus_UserCancelled = 2,
    RenewalStatus_AppComponentsMayNeedUpdating	= 3,
    RenewalStatus_NoComponentsFound	= 4
    }

.enum GraphicsTrustStatus {
    GraphicsTrustStatus_TrustNotRequired	= 0,
    GraphicsTrustStatus_TrustEstablished	= 1,
    GraphicsTrustStatus_EnvironmentNotSupported = 2,
    GraphicsTrustStatus_DriverNotSupported	= 3,
    GraphicsTrustStatus_DriverSigningFailure	= 4,
    GraphicsTrustStatus_UnknownFailure	= 5
    }

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIServiceRequestedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIServiceRequestedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IServiceRequestedEventHandler, "D2D690BA-CAC9-48E1-95C0-D38495A84055")

.comdef IServiceRequestedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIRebootNeededEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIRebootNeededEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IRebootNeededEventHandler, "64E12A45-973B-4A3A-B260-91898A49A82C")

.comdef IRebootNeededEventHandler : public IUnknown

    _Invoke		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIComponentLoadFailedEventHandler_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIComponentLoadFailedEventHandler_INTERFACE_DEFINED__
DEFINE_IIDX(IComponentLoadFailedEventHandler, "95DA643C-6DB9-424B-86CA-091AF432081C")

.comdef IComponentLoadFailedEventHandler : public IUnknown

    _Invoke		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIMediaProtectionManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIMediaProtectionManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IMediaProtectionManager <L"Windows.Media.Protection.IMediaProtectionManager">
DEFINE_IIDX(IMediaProtectionManager, "45694947-C741-434B-A79E-474C12D93D2F")

.comdef IMediaProtectionManager : public IInspectable

    add_ServiceRequested proc :ptr, :ptr
    remove_ServiceRequested proc :EventRegistrationToken
    add_RebootNeeded	proc :ptr, :ptr
    remove_RebootNeeded proc :EventRegistrationToken
    add_ComponentLoadFailed proc :ptr, :ptr
    remove_ComponentLoadFailed proc :EventRegistrationToken
    get_Properties	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIMediaProtectionServiceCompletion_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIMediaProtectionServiceCompletion_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IMediaProtectionServiceCompletion <L"Windows.Media.Protection.IMediaProtectionServiceCompletion">
DEFINE_IIDX(IMediaProtectionServiceCompletion, "8B5CCA18-CFD5-44EE-A2ED-DF76010C14B5")

.comdef IMediaProtectionServiceCompletion : public IInspectable

    Complete		proc :boolean
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIServiceRequestedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIServiceRequestedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IServiceRequestedEventArgs <L"Windows.Media.Protection.IServiceRequestedEventArgs">
DEFINE_IIDX(IServiceRequestedEventArgs, "34283BAF-ABB4-4FC1-BD89-93F106573A49")

.comdef IServiceRequestedEventArgs : public IInspectable

    get_Request		proc :ptr
    get_Completion	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIMediaProtectionServiceRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIMediaProtectionServiceRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IMediaProtectionServiceRequest <L"Windows.Media.Protection.IMediaProtectionServiceRequest">
DEFINE_IIDX(IMediaProtectionServiceRequest, "B1DE0EA6-2094-478D-87A4-8B95200F85C6")

.comdef IMediaProtectionServiceRequest : public IInspectable

    get_ProtectionSystem proc :ptr
    get_Type		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIComponentLoadFailedEventArgs_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIComponentLoadFailedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IComponentLoadFailedEventArgs <L"Windows.Media.Protection.IComponentLoadFailedEventArgs">
DEFINE_IIDX(IComponentLoadFailedEventArgs, "95972E93-7746-417E-8495-F031BBC5862C")

.comdef IComponentLoadFailedEventArgs : public IInspectable

    get_Information	proc :ptr
    get_Completion	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIRevocationAndRenewalInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIRevocationAndRenewalInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IRevocationAndRenewalInformation <L"Windows.Media.Protection.IRevocationAndRenewalInformation">
DEFINE_IIDX(IRevocationAndRenewalInformation, "F3A1937B-2501-439E-A6E7-6FC95E175FCF")

.comdef IRevocationAndRenewalInformation : public IInspectable

    get_Items		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIRevocationAndRenewalItem_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIRevocationAndRenewalItem_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IRevocationAndRenewalItem <L"Windows.Media.Protection.IRevocationAndRenewalItem">
DEFINE_IIDX(IRevocationAndRenewalItem, "3099C20C-3CF0-49EA-902D-CAF32D2DDE2C")

.comdef IRevocationAndRenewalItem : public IInspectable

    get_Reasons		proc :ptr
    get_HeaderHash	proc :ptr
    get_PublicKeyHash	proc :ptr
    get_Name		proc :ptr
    get_RenewalId	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CMedia_CProtection_CIComponentRenewalStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CMedia_CProtection_CIComponentRenewalStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Media_Protection_IComponentRenewalStatics <L"Windows.Media.Protection.IComponentRenewalStatics">
DEFINE_IIDX(IComponentRenewalStatics, "6FFBCD67-B795-48C5-8B7B-A7C4EFE202E3")

.comdef IComponentRenewalStatics : public IInspectable

    RenewSystemComponentsAsync proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Media_Protection_MediaProtectionManager_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_MediaProtectionManager_DEFINED
define RuntimeClass_Windows_Media_Protection_MediaProtectionManager <L"Windows.Media.Protection.MediaProtectionManager">
endif
ifndef RUNTIMECLASS_Windows_Media_Protection_ServiceRequestedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_ServiceRequestedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Protection_ServiceRequestedEventArgs <L"Windows.Media.Protection.ServiceRequestedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Protection_ComponentLoadFailedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_ComponentLoadFailedEventArgs_DEFINED
define RuntimeClass_Windows_Media_Protection_ComponentLoadFailedEventArgs <L"Windows.Media.Protection.ComponentLoadFailedEventArgs">
endif
ifndef RUNTIMECLASS_Windows_Media_Protection_MediaProtectionServiceCompletion_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_MediaProtectionServiceCompletion_DEFINED
define RuntimeClass_Windows_Media_Protection_MediaProtectionServiceCompletion <L"Windows.Media.Protection.MediaProtectionServiceCompletion">
endif
ifndef RUNTIMECLASS_Windows_Media_Protection_RevocationAndRenewalInformation_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_RevocationAndRenewalInformation_DEFINED
define RuntimeClass_Windows_Media_Protection_RevocationAndRenewalInformation <L"Windows.Media.Protection.RevocationAndRenewalInformation">
endif
ifndef RUNTIMECLASS_Windows_Media_Protection_RevocationAndRenewalItem_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_RevocationAndRenewalItem_DEFINED
define RuntimeClass_Windows_Media_Protection_RevocationAndRenewalItem <L"Windows.Media.Protection.RevocationAndRenewalItem">
endif
ifndef RUNTIMECLASS_Windows_Media_Protection_ComponentRenewal_DEFINED
define RUNTIMECLASS_Windows_Media_Protection_ComponentRenewal_DEFINED
define RuntimeClass_Windows_Media_Protection_ComponentRenewal <L"Windows.Media.Protection.ComponentRenewal">
endif

endif
