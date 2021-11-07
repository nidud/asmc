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

ifndef __windows2Esecurity2Eexchangeactivesyncprovisioning_h__
define __windows2Esecurity2Eexchangeactivesyncprovisioning_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults, "24a4131a-ed31-5eff-972e-750b956404d0")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults, "fc3a733a-7ded-5e92-a569-b43389ee8827")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CExchangeActiveSyncProvisioning__CEasComplianceResults : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace ExchangeActiveSyncProvisioning

.enum EasRequireEncryptionResult {
    EasRequireEncryptionResult_NotEvaluated	= 0,
    EasRequireEncryptionResult_Compliant	= 1,
    EasRequireEncryptionResult_CanBeCompliant	= 2,
    EasRequireEncryptionResult_NotProvisionedOnAllVolumes	= 3,
    EasRequireEncryptionResult_DeFixedDataNotSupported	= 4,
    EasRequireEncryptionResult_FixedDataNotSupported	= 4,
    EasRequireEncryptionResult_DeHardwareNotCompliant	= 5,
    EasRequireEncryptionResult_HardwareNotCompliant	= 5,
    EasRequireEncryptionResult_DeWinReNotConfigured	= 6,
    EasRequireEncryptionResult_LockNotConfigured	= 6,
    EasRequireEncryptionResult_DeProtectionSuspended	= 7,
    EasRequireEncryptionResult_ProtectionSuspended	= 7,
    EasRequireEncryptionResult_DeOsVolumeNotProtected	= 8,
    EasRequireEncryptionResult_OsVolumeNotProtected	= 8,
    EasRequireEncryptionResult_DeProtectionNotYetEnabled	= 9,
    EasRequireEncryptionResult_ProtectionNotYetEnabled	= 9,
    EasRequireEncryptionResult_NoFeatureLicense = 10,
    EasRequireEncryptionResult_OsNotProtected	= 11,
    EasRequireEncryptionResult_UnexpectedFailure	= 12
    }

.enum EasEncryptionProviderType {
    EasEncryptionProviderType_NotEvaluated	= 0,
    EasEncryptionProviderType_WindowsEncryption = 1,
    EasEncryptionProviderType_OtherEncryption	= 2
    }

.enum EasMinPasswordLengthResult {
    EasMinPasswordLengthResult_NotEvaluated	= 0,
    EasMinPasswordLengthResult_Compliant	= 1,
    EasMinPasswordLengthResult_CanBeCompliant	= 2,
    EasMinPasswordLengthResult_RequestedPolicyIsStricter	= 3,
    EasMinPasswordLengthResult_RequestedPolicyNotEnforceable	= 4,
    EasMinPasswordLengthResult_InvalidParameter = 5,
    EasMinPasswordLengthResult_CurrentUserHasBlankPassword	= 6,
    EasMinPasswordLengthResult_AdminsHaveBlankPassword	= 7,
    EasMinPasswordLengthResult_UserCannotChangePassword = 8,
    EasMinPasswordLengthResult_AdminsCannotChangePassword	= 9,
    EasMinPasswordLengthResult_LocalControlledUsersCannotChangePassword = 10,
    EasMinPasswordLengthResult_ConnectedAdminsProviderPolicyIsWeak	= 11,
    EasMinPasswordLengthResult_ConnectedUserProviderPolicyIsWeak	= 12,
    EasMinPasswordLengthResult_ChangeConnectedAdminsPassword	= 13,
    EasMinPasswordLengthResult_ChangeConnectedUserPassword	= 14
    }

.enum EasDisallowConvenienceLogonResult {
    EasDisallowConvenienceLogonResult_NotEvaluated	= 0,
    EasDisallowConvenienceLogonResult_Compliant = 1,
    EasDisallowConvenienceLogonResult_CanBeCompliant	= 2,
    EasDisallowConvenienceLogonResult_RequestedPolicyIsStricter = 3
    }

.enum EasMinPasswordComplexCharactersResult {
    EasMinPasswordComplexCharactersResult_NotEvaluated	= 0,
    EasMinPasswordComplexCharactersResult_Compliant	= 1,
    EasMinPasswordComplexCharactersResult_CanBeCompliant	= 2,
    EasMinPasswordComplexCharactersResult_RequestedPolicyIsStricter	= 3,
    EasMinPasswordComplexCharactersResult_RequestedPolicyNotEnforceable = 4,
    EasMinPasswordComplexCharactersResult_InvalidParameter	= 5,
    EasMinPasswordComplexCharactersResult_CurrentUserHasBlankPassword	= 6,
    EasMinPasswordComplexCharactersResult_AdminsHaveBlankPassword	= 7,
    EasMinPasswordComplexCharactersResult_UserCannotChangePassword	= 8,
    EasMinPasswordComplexCharactersResult_AdminsCannotChangePassword	= 9,
    EasMinPasswordComplexCharactersResult_LocalControlledUsersCannotChangePassword	= 10,
    EasMinPasswordComplexCharactersResult_ConnectedAdminsProviderPolicyIsWeak	= 11,
    EasMinPasswordComplexCharactersResult_ConnectedUserProviderPolicyIsWeak	= 12,
    EasMinPasswordComplexCharactersResult_ChangeConnectedAdminsPassword = 13,
    EasMinPasswordComplexCharactersResult_ChangeConnectedUserPassword	= 14
    }

.enum EasPasswordExpirationResult {
    EasPasswordExpirationResult_NotEvaluated	= 0,
    EasPasswordExpirationResult_Compliant	= 1,
    EasPasswordExpirationResult_CanBeCompliant	= 2,
    EasPasswordExpirationResult_RequestedPolicyIsStricter	= 3,
    EasPasswordExpirationResult_RequestedExpirationIncompatible = 4,
    EasPasswordExpirationResult_InvalidParameter	= 5,
    EasPasswordExpirationResult_UserCannotChangePassword	= 6,
    EasPasswordExpirationResult_AdminsCannotChangePassword	= 7,
    EasPasswordExpirationResult_LocalControlledUsersCannotChangePassword	= 8
    }

.enum EasPasswordHistoryResult {
    EasPasswordHistoryResult_NotEvaluated	= 0,
    EasPasswordHistoryResult_Compliant	= 1,
    EasPasswordHistoryResult_CanBeCompliant	= 2,
    EasPasswordHistoryResult_RequestedPolicyIsStricter	= 3,
    EasPasswordHistoryResult_InvalidParameter	= 4
    }

.enum EasMaxPasswordFailedAttemptsResult {
    EasMaxPasswordFailedAttemptsResult_NotEvaluated	= 0,
    EasMaxPasswordFailedAttemptsResult_Compliant	= 1,
    EasMaxPasswordFailedAttemptsResult_CanBeCompliant	= 2,
    EasMaxPasswordFailedAttemptsResult_RequestedPolicyIsStricter	= 3,
    EasMaxPasswordFailedAttemptsResult_InvalidParameter = 4
    }

.enum EasMaxInactivityTimeLockResult {
    EasMaxInactivityTimeLockResult_NotEvaluated = 0,
    EasMaxInactivityTimeLockResult_Compliant	= 1,
    EasMaxInactivityTimeLockResult_CanBeCompliant	= 2,
    EasMaxInactivityTimeLockResult_RequestedPolicyIsStricter	= 3,
    EasMaxInactivityTimeLockResult_InvalidParameter	= 4
    }

ifndef ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasClientDeviceInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasClientDeviceInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_ExchangeActiveSyncProvisioning_IEasClientDeviceInformation <L"Windows.Security.ExchangeActiveSyncProvisioning.IEasClientDeviceInformation">
DEFINE_IIDX(IEasClientDeviceInformation, "54DFD981-1968-4CA3-B958-E595D16505EB")

.comdef IEasClientDeviceInformation : public IInspectable

    get_Id		proc :ptr
    get_OperatingSystem proc :ptr
    get_FriendlyName	proc :ptr
    get_SystemManufacturer proc :ptr
    get_SystemProductName proc :ptr
    get_SystemSku	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasClientSecurityPolicy_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasClientSecurityPolicy_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_ExchangeActiveSyncProvisioning_IEasClientSecurityPolicy <L"Windows.Security.ExchangeActiveSyncProvisioning.IEasClientSecurityPolicy">
DEFINE_IIDX(IEasClientSecurityPolicy, "45B72362-DFBA-4A9B-ACED-6FE2ADCB6420")

.comdef IEasClientSecurityPolicy : public IInspectable

    get_RequireEncryption proc :ptr
    put_RequireEncryption proc :boolean
    get_MinPasswordLength proc :ptr
    put_MinPasswordLength proc :BYTE
    get_DisallowConvenienceLogon proc :ptr
    put_DisallowConvenienceLogon proc :boolean
    get_MinPasswordComplexCharacters proc :ptr
    put_MinPasswordComplexCharacters proc :BYTE
    get_PasswordExpiration proc :ptr
    put_PasswordExpiration proc :Windows::Foundation::TimeSpan
    get_PasswordHistory proc :ptr
    put_PasswordHistory proc :UINT32
    get_MaxPasswordFailedAttempts proc :ptr
    put_MaxPasswordFailedAttempts proc :BYTE
    get_MaxInactivityTimeLock proc :ptr
    put_MaxInactivityTimeLock proc :Windows::Foundation::TimeSpan
    CheckCompliance	proc :ptr
    ApplyAsync		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasComplianceResults_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasComplianceResults_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_ExchangeActiveSyncProvisioning_IEasComplianceResults <L"Windows.Security.ExchangeActiveSyncProvisioning.IEasComplianceResults">
DEFINE_IIDX(IEasComplianceResults, "463C299C-7F19-4C66-B403-CB45DD57A2B3")

.comdef IEasComplianceResults : public IInspectable

    get_Compliant	proc :ptr
    get_RequireEncryptionResult proc :ptr
    get_MinPasswordLengthResult proc :ptr
    get_DisallowConvenienceLogonResult proc :ptr
    get_MinPasswordComplexCharactersResult proc :ptr
    get_PasswordExpirationResult proc :ptr
    get_PasswordHistoryResult proc :ptr
    get_MaxPasswordFailedAttemptsResult proc :ptr
    get_MaxInactivityTimeLockResult proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasComplianceResults2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CExchangeActiveSyncProvisioning_CIEasComplianceResults2_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_ExchangeActiveSyncProvisioning_IEasComplianceResults2 <L"Windows.Security.ExchangeActiveSyncProvisioning.IEasComplianceResults2">
DEFINE_IIDX(IEasComplianceResults2, "2FBE60C9-1AA8-47F5-88BB-CB3EF0BFFB15")

.comdef IEasComplianceResults2 : public IInspectable

    get_EncryptionProviderType proc :ptr
   .ends

endif

.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_ExchangeActiveSyncProvisioning_EasComplianceResults_DEFINED
define RUNTIMECLASS_Windows_Security_ExchangeActiveSyncProvisioning_EasComplianceResults_DEFINED
define RuntimeClass_Windows_Security_ExchangeActiveSyncProvisioning_EasComplianceResults <L"Windows.Security.ExchangeActiveSyncProvisioning.EasComplianceResults">
endif
ifndef RUNTIMECLASS_Windows_Security_ExchangeActiveSyncProvisioning_EasClientSecurityPolicy_DEFINED
define RUNTIMECLASS_Windows_Security_ExchangeActiveSyncProvisioning_EasClientSecurityPolicy_DEFINED
define RuntimeClass_Windows_Security_ExchangeActiveSyncProvisioning_EasClientSecurityPolicy <L"Windows.Security.ExchangeActiveSyncProvisioning.EasClientSecurityPolicy">
endif
ifndef RUNTIMECLASS_Windows_Security_ExchangeActiveSyncProvisioning_EasClientDeviceInformation_DEFINED
define RUNTIMECLASS_Windows_Security_ExchangeActiveSyncProvisioning_EasClientDeviceInformation_DEFINED
define RuntimeClass_Windows_Security_ExchangeActiveSyncProvisioning_EasClientDeviceInformation <L"Windows.Security.ExchangeActiveSyncProvisioning.EasClientDeviceInformation">
endif

endif
