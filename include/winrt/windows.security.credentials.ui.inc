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

ifndef __windows2Esecurity2Ecredentials2Eui_h__
define __windows2Esecurity2Ecredentials2Eui_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults, "091a96b8-52a6-523a-8c94-7f9c11c6dae5")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults, "83fd09a4-21fd-5c01-9cf6-8293b2929a9f")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CCredentialPickerResults : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult, "0cffc6c9-4c2b-5cd4-b38c-7b8df3ff5afb")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult, "fd596ffd-2318-558f-9dbe-d21df43764a5")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerificationResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability, "28988174-ace2-5c15-a0df-580a26d94294")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability, "ddd384f3-d818-5d83-ab4b-32119c28587c")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CCredentials__CUI__CUserConsentVerifierAvailability : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace Credentials
.namespace UI

.enum UserConsentVerifierAvailability {
    UserConsentVerifierAvailability_Available	= 0,
    UserConsentVerifierAvailability_DeviceNotPresent	= 1,
    UserConsentVerifierAvailability_NotConfiguredForUser	= 2,
    UserConsentVerifierAvailability_DisabledByPolicy	= 3,
    UserConsentVerifierAvailability_DeviceBusy	= 4
    }

.enum UserConsentVerificationResult {
    UserConsentVerificationResult_Verified	= 0,
    UserConsentVerificationResult_DeviceNotPresent	= 1,
    UserConsentVerificationResult_NotConfiguredForUser	= 2,
    UserConsentVerificationResult_DisabledByPolicy	= 3,
    UserConsentVerificationResult_DeviceBusy	= 4,
    UserConsentVerificationResult_RetriesExhausted	= 5,
    UserConsentVerificationResult_Canceled	= 6
    }

.enum AuthenticationProtocol {
    AuthenticationProtocol_Basic	= 0,
    AuthenticationProtocol_Digest	= 1,
    AuthenticationProtocol_Ntlm = 2,
    AuthenticationProtocol_Kerberos	= 3,
    AuthenticationProtocol_Negotiate	= 4,
    AuthenticationProtocol_CredSsp	= 5,
    AuthenticationProtocol_Custom	= 6
    }

.enum CredentialSaveOption {
    CredentialSaveOption_Unselected	= 0,
    CredentialSaveOption_Selected	= 1,
    CredentialSaveOption_Hidden = 2
    }

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CIUserConsentVerifierStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CIUserConsentVerifierStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_UI_IUserConsentVerifierStatics <L"Windows.Security.Credentials.UI.IUserConsentVerifierStatics">
DEFINE_IIDX(IUserConsentVerifierStatics, "AF4F3F91-564C-4DDC-B8B5-973447627C65")

.comdef IUserConsentVerifierStatics : public IInspectable

    CheckAvailabilityAsync proc :ptr
    RequestVerificationAsync proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CICredentialPickerOptions_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CICredentialPickerOptions_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_UI_ICredentialPickerOptions <L"Windows.Security.Credentials.UI.ICredentialPickerOptions">
DEFINE_IIDX(ICredentialPickerOptions, "965A0B4C-95FA-467F-992B-0B22E5859BF6")

.comdef ICredentialPickerOptions : public IInspectable

    put_Caption		proc :HSTRING
    get_Caption		proc :ptr
    put_Message		proc :HSTRING
    get_Message		proc :ptr
    put_ErrorCode	proc :UINT32
    get_ErrorCode	proc :ptr
    put_TargetName	proc :HSTRING
    get_TargetName	proc :ptr
    put_AuthenticationProtocol proc :Windows::Security::Credentials::UI::AuthenticationProtocol
    get_AuthenticationProtocol proc :ptr
    put_CustomAuthenticationProtocol proc :HSTRING
    get_CustomAuthenticationProtocol proc :ptr
    put_PreviousCredential proc :ptr
    get_PreviousCredential proc :ptr
    put_AlwaysDisplayDialog proc :boolean
    get_AlwaysDisplayDialog proc :ptr
    put_CallerSavesCredential proc :boolean
    get_CallerSavesCredential proc :ptr
    put_CredentialSaveOption proc :Windows::Security::Credentials::UI::CredentialSaveOption
    get_CredentialSaveOption proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CICredentialPickerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CICredentialPickerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_UI_ICredentialPickerStatics <L"Windows.Security.Credentials.UI.ICredentialPickerStatics">
DEFINE_IIDX(ICredentialPickerStatics, "AA3A5C73-C9EA-4782-99FB-E6D7E938E12D")

.comdef ICredentialPickerStatics : public IInspectable

    PickWithOptionsAsync proc :ptr, :ptr
    PickWithMessageAsync proc :HSTRING, :HSTRING, :ptr
    PickWithCaptionAsync proc :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CICredentialPickerResults_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CCredentials_CUI_CICredentialPickerResults_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Credentials_UI_ICredentialPickerResults <L"Windows.Security.Credentials.UI.ICredentialPickerResults">
DEFINE_IIDX(ICredentialPickerResults, "1948F99A-CC30-410C-9C38-CC0884C5B3D7")

.comdef ICredentialPickerResults : public IInspectable

    get_ErrorCode	proc :ptr
    get_CredentialSaveOption proc :ptr
    get_CredentialSaved proc :ptr
    get_Credential	proc :ptr
    get_CredentialDomainName proc :ptr
    get_CredentialUserName proc :ptr
    get_CredentialPassword proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Credentials_UI_UserConsentVerifier_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_UI_UserConsentVerifier_DEFINED
define RuntimeClass_Windows_Security_Credentials_UI_UserConsentVerifier <L"Windows.Security.Credentials.UI.UserConsentVerifier">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_UI_CredentialPickerOptions_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_UI_CredentialPickerOptions_DEFINED
define RuntimeClass_Windows_Security_Credentials_UI_CredentialPickerOptions <L"Windows.Security.Credentials.UI.CredentialPickerOptions">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_UI_CredentialPickerResults_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_UI_CredentialPickerResults_DEFINED
define RuntimeClass_Windows_Security_Credentials_UI_CredentialPickerResults <L"Windows.Security.Credentials.UI.CredentialPickerResults">
endif
ifndef RUNTIMECLASS_Windows_Security_Credentials_UI_CredentialPicker_DEFINED
define RUNTIMECLASS_Windows_Security_Credentials_UI_CredentialPicker_DEFINED
define RuntimeClass_Windows_Security_Credentials_UI_CredentialPicker <L"Windows.Security.Credentials.UI.CredentialPicker">
endif

endif
