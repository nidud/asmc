ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esystem2Eprofile_h__
define __windows2Esystem2Eprofile_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Storage.Streams.inc

.namespace Windows
.namespace System
.namespace Profile

ifndef ____x_ABI_CWindows_CSystem_CProfile_CIHardwareToken_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CProfile_CIHardwareToken_INTERFACE_DEFINED__
DEFINE_IIDX(IHardwareToken, "28F6D4C0-FB12-40A4-8167-7F4E03D2724C")

.comdef IHardwareToken : public IInspectable

    get_Id              proc :ptr
    get_Signature       proc :ptr
    get_Certificate     proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSystem_CProfile_CIHardwareIdentificationStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSystem_CProfile_CIHardwareIdentificationStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_System_Profile_IHardwareIdentificationStatics <L"Windows.System.Profile.IHardwareIdentificationStatics">
DEFINE_IIDX(IHardwareIdentificationStatics, "971260E0-F170-4A42-BD55-A900B212DAE2")

.comdef IHardwareIdentificationStatics : public IInspectable

    GetPackageSpecificToken proc :ptr, :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_System_Profile_HardwareToken_DEFINED
define RUNTIMECLASS_Windows_System_Profile_HardwareToken_DEFINED
define RuntimeClass_Windows_System_Profile_HardwareToken <L"Windows.System.Profile.HardwareToken">
endif
ifndef RUNTIMECLASS_Windows_System_Profile_HardwareIdentification_DEFINED
define RUNTIMECLASS_Windows_System_Profile_HardwareIdentification_DEFINED
define RuntimeClass_Windows_System_Profile_HardwareIdentification <L"Windows.System.Profile.HardwareIdentification">
endif

endif
