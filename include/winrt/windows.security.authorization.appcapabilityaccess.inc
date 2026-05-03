ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Eauthorization2Eappcapabilityaccess_h__
define __windows2Esecurity2Eauthorization2Eappcapabilityaccess_h__
ifndef __windows2Esecurity2Eauthorization2Eappcapabilityaccess_p_h__
define __windows2Esecurity2Eauthorization2Eappcapabilityaccess_p_h__


ifndef SPECIFIC_API_CONTRACT_DEFINITIONS
ifndef WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION
define WINDOWS_FOUNDATION_FOUNDATIONCONTRACT_VERSION 0x40000
endif
ifndef WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION
define WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION 0x130000
endif
ifndef WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION
define WINDOWS_SYSTEM_SYSTEMMANAGEMENTCONTRACT_VERSION 0x70000
endif
endif
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include windowscontracts.inc
include Windows.System.inc

.namespace Windows
.namespace Security
.namespace Authorization
.namespace AppCapabilityAccess


if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
.enum AppCapabilityAccessStatus {
    AppCapabilityAccessStatus_DeniedBySystem = 0,
    AppCapabilityAccessStatus_NotDeclaredByApp = 1,
    AppCapabilityAccessStatus_DeniedByUser = 2,
    AppCapabilityAccessStatus_UserPromptRequired = 3,
    AppCapabilityAccessStatus_Allowed = 4,
    }
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
if not defined(____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapability_INTERFACE_DEFINED__)
define ____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapability_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authorization_AppCapabilityAccess_IAppCapability <"Windows.Security.Authorization.AppCapabilityAccess.IAppCapability">
DEFINE_IIDX(IAppCapability, "4c49d915-8a2a-4295-9437-2df7c396aff4")

.comdef IAppCapability : public IInspectable
    get_CapabilityName  proc :ptr
    get_User            proc :ptr ptr
    RequestAccessAsync  proc :ptr ptr
    CheckAccess         proc :ptr
    add_AccessChanged   proc :ptr, :ptr
    remove_AccessChanged proc :EventRegistrationToken
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0xf0000
if not defined(____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapability2_INTERFACE_DEFINED__)
define ____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapability2_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authorization_AppCapabilityAccess_IAppCapability2 <"Windows.Security.Authorization.AppCapabilityAccess.IAppCapability2">
DEFINE_IIDX(IAppCapability2, "11c7ccb6-c74f-50a3-b960-88008767d939")

.comdef IAppCapability2 : public IInspectable
    get_DisplayMessage  proc :ptr
    put_DisplayMessage  proc :HSTRING
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
if not defined(____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapabilityAccessChangedEventArgs_INTERFACE_DEFINED__)
define ____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapabilityAccessChangedEventArgs_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authorization_AppCapabilityAccess_IAppCapabilityAccessChangedEventArgs <"Windows.Security.Authorization.AppCapabilityAccess.IAppCapabilityAccessChangedEventArgs">
DEFINE_IIDX(IAppCapabilityAccessChangedEventArgs, "0a578d15-bdd7-457e-8cca-6f53bd2e5944")

.comdef IAppCapabilityAccessChangedEventArgs : public IInspectable
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
if not defined(____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapabilityStatics_INTERFACE_DEFINED__)
define ____x_ABI_CWindows_CSecurity_CAuthorization_CAppCapabilityAccess_CIAppCapabilityStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authorization_AppCapabilityAccess_IAppCapabilityStatics <"Windows.Security.Authorization.AppCapabilityAccess.IAppCapabilityStatics">
DEFINE_IIDX(IAppCapabilityStatics, "7c353e2a-46ee-44e5-af3d-6ad3fc49bd22")

.comdef IAppCapabilityStatics : public IInspectable
    RequestAccessForCapabilitiesAsync proc :ptr, :ptr ptr
    RequestAccessForCapabilitiesForUserAsync proc :ptr, :ptr, :ptr ptr
    Create              proc :HSTRING, :ptr ptr
    CreateWithProcessIdForUser proc :ptr, :HSTRING, :UINT32, :ptr ptr
   .ends
endif
endif

.endn
.endn
.endn
.endn

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_Security_Authorization_AppCapabilityAccess_AppCapability_DEFINED
define RUNTIMECLASS_Windows_Security_Authorization_AppCapabilityAccess_AppCapability_DEFINED
define RuntimeClass_Windows_Security_Authorization_AppCapabilityAccess_AppCapability <"Windows.Security.Authorization.AppCapabilityAccess.AppCapability">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_Security_Authorization_AppCapabilityAccess_AppCapabilityAccessChangedEventArgs_DEFINED
define RUNTIMECLASS_Windows_Security_Authorization_AppCapabilityAccess_AppCapabilityAccessChangedEventArgs_DEFINED
define RuntimeClass_Windows_Security_Authorization_AppCapabilityAccess_AppCapabilityAccessChangedEventArgs <"Windows.Security.Authorization.AppCapabilityAccess.AppCapabilityAccessChangedEventArgs">
endif
endif

endif

endif
