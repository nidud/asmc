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

ifndef __windows2Esecurity2Eauthentication2Eonlineid_h__
define __windows2Esecurity2Eauthentication2Eonlineid_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket, "039feee7-0882-50e2-bc3f-4fac7e8c2769")

.comdef __FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket, "809d1314-97ab-5544-9891-ddcdfadd1dbb")

.comdef __FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest, "b6a5c8e4-6e3c-5c37-92cf-cf9f1c383335")

.comdef __FIIterator_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest, "cb72d686-9516-520d-a274-fa4cd1762cb2")

.comdef __FIIterable_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicketRequest : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket, "45f03233-e7a8-5ade-9ff3-0b8a1c6ba76b")

.comdef __FIVectorView_1_Windows__CSecurity__CAuthentication__COnlineId__COnlineIdServiceTicket : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity, "cded76fd-7841-52a0-a771-76cd751d13cd")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity, "b8cc25e1-409f-57f4-bbe4-3b95b74b86c8")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CAuthentication__COnlineId__CUserIdentity : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace Authentication
.namespace OnlineId

.enum CredentialPromptType {
    CredentialPromptType_PromptIfNeeded = 0,
    CredentialPromptType_RetypeCredentials	= 1,
    CredentialPromptType_DoNotPrompt	= 2
    }

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdServiceTicketRequest_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdServiceTicketRequest_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_OnlineId_IOnlineIdServiceTicketRequest <L"Windows.Security.Authentication.OnlineId.IOnlineIdServiceTicketRequest">
DEFINE_IIDX(IOnlineIdServiceTicketRequest, "297445D3-FB63-4135-8909-4E354C061466")

.comdef IOnlineIdServiceTicketRequest : public IInspectable

    get_Service		proc :ptr
    get_Policy		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdServiceTicketRequestFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdServiceTicketRequestFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_OnlineId_IOnlineIdServiceTicketRequestFactory <L"Windows.Security.Authentication.OnlineId.IOnlineIdServiceTicketRequestFactory">
DEFINE_IIDX(IOnlineIdServiceTicketRequestFactory, "BEBB0A08-9E73-4077-9614-08614C0BC245")

.comdef IOnlineIdServiceTicketRequestFactory : public IInspectable

    CreateOnlineIdServiceTicketRequest proc :HSTRING, :HSTRING, :ptr
    CreateOnlineIdServiceTicketRequestAdvanced proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdServiceTicket_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdServiceTicket_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_OnlineId_IOnlineIdServiceTicket <L"Windows.Security.Authentication.OnlineId.IOnlineIdServiceTicket">
DEFINE_IIDX(IOnlineIdServiceTicket, "C95C547F-D781-4A94-ACB8-C59874238C26")

.comdef IOnlineIdServiceTicket : public IInspectable

    get_Value		proc :ptr
    get_Request		proc :ptr
    get_ErrorCode	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIUserIdentity_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIUserIdentity_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_OnlineId_IUserIdentity <L"Windows.Security.Authentication.OnlineId.IUserIdentity">
DEFINE_IIDX(IUserIdentity, "2146D9CD-0742-4BE3-8A1C-7C7AE679AA88")

.comdef IUserIdentity : public IInspectable

    get_Tickets		proc :ptr
    get_Id		proc :ptr
    get_SafeCustomerId	proc :ptr
    get_SignInName	proc :ptr
    get_FirstName	proc :ptr
    get_LastName	proc :ptr
    get_IsBetaAccount	proc :ptr
    get_IsConfirmedPC	proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdAuthenticator_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_COnlineId_CIOnlineIdAuthenticator_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_OnlineId_IOnlineIdAuthenticator <L"Windows.Security.Authentication.OnlineId.IOnlineIdAuthenticator">
DEFINE_IIDX(IOnlineIdAuthenticator, "A003F58A-29AB-4817-B884-D7516DAD18B9")

.comdef IOnlineIdAuthenticator : public IInspectable

    AuthenticateUserAsync proc :ptr, :ptr
    AuthenticateUserAsyncAdvanced proc :ptr, :Windows::Security::Authentication::OnlineId::CredentialPromptType, :ptr
    SignOutUserAsync	proc :ptr
    put_ApplicationId	proc :GUID
    get_ApplicationId	proc :ptr
    get_CanSignOut	proc :ptr
    get_AuthenticatedSafeCustomerId proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Authentication_OnlineId_OnlineIdServiceTicketRequest_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_OnlineId_OnlineIdServiceTicketRequest_DEFINED
define RuntimeClass_Windows_Security_Authentication_OnlineId_OnlineIdServiceTicketRequest <L"Windows.Security.Authentication.OnlineId.OnlineIdServiceTicketRequest">
endif
ifndef RUNTIMECLASS_Windows_Security_Authentication_OnlineId_OnlineIdServiceTicket_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_OnlineId_OnlineIdServiceTicket_DEFINED
define RuntimeClass_Windows_Security_Authentication_OnlineId_OnlineIdServiceTicket <L"Windows.Security.Authentication.OnlineId.OnlineIdServiceTicket">
endif
ifndef RUNTIMECLASS_Windows_Security_Authentication_OnlineId_UserAuthenticationOperation_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_OnlineId_UserAuthenticationOperation_DEFINED
define RuntimeClass_Windows_Security_Authentication_OnlineId_UserAuthenticationOperation <L"Windows.Security.Authentication.OnlineId.UserAuthenticationOperation">
endif
ifndef RUNTIMECLASS_Windows_Security_Authentication_OnlineId_SignOutUserOperation_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_OnlineId_SignOutUserOperation_DEFINED
define RuntimeClass_Windows_Security_Authentication_OnlineId_SignOutUserOperation <L"Windows.Security.Authentication.OnlineId.SignOutUserOperation">
endif
ifndef RUNTIMECLASS_Windows_Security_Authentication_OnlineId_UserIdentity_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_OnlineId_UserIdentity_DEFINED
define RuntimeClass_Windows_Security_Authentication_OnlineId_UserIdentity <L"Windows.Security.Authentication.OnlineId.UserIdentity">
endif
ifndef RUNTIMECLASS_Windows_Security_Authentication_OnlineId_OnlineIdAuthenticator_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_OnlineId_OnlineIdAuthenticator_DEFINED
define RuntimeClass_Windows_Security_Authentication_OnlineId_OnlineIdAuthenticator <L"Windows.Security.Authentication.OnlineId.OnlineIdAuthenticator">
endif

endif

