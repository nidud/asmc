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

ifndef __windows2Eweb_h__
define __windows2Eweb_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include Windows.Foundation.inc
include Windows.Storage.Streams.inc
include windows.foundation.collections.inc

.namespace Windows
.namespace Web

.enum WebErrorStatus {
    WebErrorStatus_Unknown  = 0 ,
    WebErrorStatus_CertificateCommonNameIsIncorrect = 1,
    WebErrorStatus_CertificateExpired   = 2,
    WebErrorStatus_CertificateContainsErrors    = 3,
    WebErrorStatus_CertificateRevoked   = 4,
    WebErrorStatus_CertificateIsInvalid = 5,
    WebErrorStatus_ServerUnreachable    = 6,
    WebErrorStatus_Timeout  = 7,
    WebErrorStatus_ErrorHttpInvalidServerResponse   = 8,
    WebErrorStatus_ConnectionAborted    = 9,
    WebErrorStatus_ConnectionReset  = 10,
    WebErrorStatus_Disconnected = 11,
    WebErrorStatus_HttpToHttpsOnRedirection = 12,
    WebErrorStatus_HttpsToHttpOnRedirection = 13,
    WebErrorStatus_CannotConnect    = 14,
    WebErrorStatus_HostNameNotResolved  = 15,
    WebErrorStatus_OperationCanceled    = 16,
    WebErrorStatus_RedirectFailed   = 17,
    WebErrorStatus_UnexpectedStatusCode = 18,
    WebErrorStatus_UnexpectedRedirection    = 19,
    WebErrorStatus_UnexpectedClientError    = 20,
    WebErrorStatus_UnexpectedServerError    = 21,
    WebErrorStatus_MultipleChoices  = 300,
    WebErrorStatus_MovedPermanently = 301,
    WebErrorStatus_Found    = 302,
    WebErrorStatus_SeeOther = 303,
    WebErrorStatus_NotModified  = 304,
    WebErrorStatus_UseProxy = 305,
    WebErrorStatus_TemporaryRedirect    = 307,
    WebErrorStatus_BadRequest   = 400,
    WebErrorStatus_Unauthorized = 401,
    WebErrorStatus_PaymentRequired  = 402,
    WebErrorStatus_Forbidden    = 403,
    WebErrorStatus_NotFound = 404,
    WebErrorStatus_MethodNotAllowed = 405,
    WebErrorStatus_NotAcceptable    = 406,
    WebErrorStatus_ProxyAuthenticationRequired  = 407,
    WebErrorStatus_RequestTimeout   = 408,
    WebErrorStatus_Conflict = 409,
    WebErrorStatus_Gone = 410,
    WebErrorStatus_LengthRequired   = 411,
    WebErrorStatus_PreconditionFailed   = 412,
    WebErrorStatus_RequestEntityTooLarge    = 413,
    WebErrorStatus_RequestUriTooLong    = 414,
    WebErrorStatus_UnsupportedMediaType = 415,
    WebErrorStatus_RequestedRangeNotSatisfiable = 416,
    WebErrorStatus_ExpectationFailed    = 417,
    WebErrorStatus_InternalServerError  = 500,
    WebErrorStatus_NotImplemented   = 501,
    WebErrorStatus_BadGateway   = 502,
    WebErrorStatus_ServiceUnavailable   = 503,
    WebErrorStatus_GatewayTimeout   = 504,
    WebErrorStatus_HttpVersionNotSupported  = 505
    }

ifndef ____x_ABI_CWindows_CWeb_CIUriToStreamResolver_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CIUriToStreamResolver_INTERFACE_DEFINED__
DEFINE_IIDX(IUriToStreamResolver, "B0ABA86A-9AEB-4D3A-9590-003E3CA7E290")

.comdef IUriToStreamResolver : public IInspectable

    UriToStreamAsync    proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CIWebErrorStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CIWebErrorStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_IWebErrorStatics <L"Windows.Web.IWebErrorStatics">
DEFINE_IIDX(IWebErrorStatics, "FE616766-BF27-4064-87B7-6563BB11CE2E")

.comdef IWebErrorStatics : public IInspectable

    GetStatus           proc :INT32, :ptr
   .ends

endif

.endn
.endn

ifndef RUNTIMECLASS_Windows_Web_WebError_DEFINED
define RUNTIMECLASS_Windows_Web_WebError_DEFINED
define RuntimeClass_Windows_Web_WebError <L"Windows.Web.WebError">
endif

endif
