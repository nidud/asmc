ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Esecurity2Eauthentication2Eweb_h__
define __windows2Esecurity2Eauthentication2Eweb_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif

ifndef ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult_INTERFACE_DEFINED__
define ____FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult, "3c1ec44c-e942-54e5-bcd3-e329c951f595")

.comdef __FIAsyncOperationCompletedHandler_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult : public IUnknown

    _Invoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperation_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult_INTERFACE_DEFINED__
define ____FIAsyncOperation_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperation_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult, "b34952ac-265e-5947-8735-e9318f4301ff")

.comdef __FIAsyncOperation_1_Windows__CSecurity__CAuthentication__CWeb__CWebAuthenticationResult : public IInspectable

    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

.namespace Windows
.namespace Security
.namespace Authentication
.namespace Web

.enum WebAuthenticationStatus {
    WebAuthenticationStatus_Success	= 0,
    WebAuthenticationStatus_UserCancel	= 1,
    WebAuthenticationStatus_ErrorHttp	= 2
    }

.enum WebAuthenticationOptions {
    WebAuthenticationOptions_None	= 0,
    WebAuthenticationOptions_SilentMode = 0x1,
    WebAuthenticationOptions_UseTitle	= 0x2,
    WebAuthenticationOptions_UseHttpPost	= 0x4,
    WebAuthenticationOptions_UseCorporateNetwork	= 0x8
    }

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_CWeb_CIWebAuthenticationResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_CWeb_CIWebAuthenticationResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_Web_IWebAuthenticationResult <L"Windows.Security.Authentication.Web.IWebAuthenticationResult">
DEFINE_IIDX(IWebAuthenticationResult, "64002B4B-EDE9-470A-A5CD-0323FAF6E262")

.comdef IWebAuthenticationResult : public IInspectable

    get_ResponseData	proc :ptr
    get_ResponseStatus	proc :ptr
    get_ResponseErrorDetail proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CSecurity_CAuthentication_CWeb_CIWebAuthenticationBrokerStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CSecurity_CAuthentication_CWeb_CIWebAuthenticationBrokerStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Security_Authentication_Web_IWebAuthenticationBrokerStatics <L"Windows.Security.Authentication.Web.IWebAuthenticationBrokerStatics">
DEFINE_IIDX(IWebAuthenticationBrokerStatics, "2F149F1A-E673-40B5-BC22-201A6864A37B")

.comdef IWebAuthenticationBrokerStatics : public IInspectable

    AuthenticateWithCallbackUriAsync proc :Windows::Security::Authentication::Web::WebAuthenticationOptions, :ptr, :ptr, :ptr
    AuthenticateWithoutCallbackUriAsync proc :Windows::Security::Authentication::Web::WebAuthenticationOptions, :ptr, :ptr
    GetCurrentApplicationCallbackUri proc :ptr
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Security_Authentication_Web_WebAuthenticationResult_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_Web_WebAuthenticationResult_DEFINED
define RuntimeClass_Windows_Security_Authentication_Web_WebAuthenticationResult <L"Windows.Security.Authentication.Web.WebAuthenticationResult">
endif
ifndef RUNTIMECLASS_Windows_Security_Authentication_Web_WebAuthenticationBroker_DEFINED
define RUNTIMECLASS_Windows_Security_Authentication_Web_WebAuthenticationBroker_DEFINED
define RuntimeClass_Windows_Security_Authentication_Web_WebAuthenticationBroker <L"Windows.Security.Authentication.Web.WebAuthenticationBroker">
endif

endif
