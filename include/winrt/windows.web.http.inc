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

ifndef __windows2Eweb2Ehttp_h__
define __windows2Eweb2Ehttp_h__

include inspectable.inc
include AsyncInfo.inc
include EventToken.inc
include windowscontracts.inc
include Windows.Foundation.inc
include Windows.Networking.Sockets.inc

.namespace Windows
.namespace Web
.namespace Http

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000

.enum HttpVersion {
    HttpVersion_None = 0,
    HttpVersion_Http10 = 1,
    HttpVersion_Http11 = 2,
    HttpVersion_Http20 = 3,
    }

.enum HttpProgressStage {
    HttpProgressStage_None		= 0,
    HttpProgressStage_DetectingProxy	= 10,
    HttpProgressStage_ResolvingName	= 20,
    HttpProgressStage_ConnectingToServer = 30,
    HttpProgressStage_NegotiatingSsl	= 40,
    HttpProgressStage_SendingHeaders	= 50,
    HttpProgressStage_SendingContent	= 60,
    HttpProgressStage_WaitingForResponse = 70,
    HttpProgressStage_ReceivingHeaders	= 80,
    HttpProgressStage_ReceivingContent	= 90,
    }

.enum HttpResponseMessageSource {
    HttpResponseMessageSource_None = 0,
    HttpResponseMessageSource_Cache = 1,
    HttpResponseMessageSource_Network = 2,
    }

.enum HttpCompletionOption {
    HttpCompletionOption_ResponseContentRead	= 0,
    HttpCompletionOption_ResponseHeadersRead	= 1
    }

.enum HttpStatusCode {
    HttpStatusCode_None = 0,
    HttpStatusCode_Continue	= 100,
    HttpStatusCode_SwitchingProtocols	= 101,
    HttpStatusCode_Processing	= 102,
    HttpStatusCode_Ok	= 200,
    HttpStatusCode_Created	= 201,
    HttpStatusCode_Accepted	= 202,
    HttpStatusCode_NonAuthoritativeInformation	= 203,
    HttpStatusCode_NoContent	= 204,
    HttpStatusCode_ResetContent = 205,
    HttpStatusCode_PartialContent	= 206,
    HttpStatusCode_MultiStatus	= 207,
    HttpStatusCode_AlreadyReported	= 208,
    HttpStatusCode_IMUsed	= 226,
    HttpStatusCode_MultipleChoices	= 300,
    HttpStatusCode_MovedPermanently	= 301,
    HttpStatusCode_Found	= 302,
    HttpStatusCode_SeeOther	= 303,
    HttpStatusCode_NotModified	= 304,
    HttpStatusCode_UseProxy	= 305,
    HttpStatusCode_TemporaryRedirect	= 307,
    HttpStatusCode_PermanentRedirect	= 308,
    HttpStatusCode_BadRequest	= 400,
    HttpStatusCode_Unauthorized = 401,
    HttpStatusCode_PaymentRequired	= 402,
    HttpStatusCode_Forbidden	= 403,
    HttpStatusCode_NotFound	= 404,
    HttpStatusCode_MethodNotAllowed	= 405,
    HttpStatusCode_NotAcceptable	= 406,
    HttpStatusCode_ProxyAuthenticationRequired	= 407,
    HttpStatusCode_RequestTimeout	= 408,
    HttpStatusCode_Conflict	= 409,
    HttpStatusCode_Gone = 410,
    HttpStatusCode_LengthRequired	= 411,
    HttpStatusCode_PreconditionFailed	= 412,
    HttpStatusCode_RequestEntityTooLarge	= 413,
    HttpStatusCode_RequestUriTooLong	= 414,
    HttpStatusCode_UnsupportedMediaType = 415,
    HttpStatusCode_RequestedRangeNotSatisfiable = 416,
    HttpStatusCode_ExpectationFailed	= 417,
    HttpStatusCode_UnprocessableEntity	= 422,
    HttpStatusCode_Locked	= 423,
    HttpStatusCode_FailedDependency	= 424,
    HttpStatusCode_UpgradeRequired	= 426,
    HttpStatusCode_PreconditionRequired = 428,
    HttpStatusCode_TooManyRequests	= 429,
    HttpStatusCode_RequestHeaderFieldsTooLarge	= 431,
    HttpStatusCode_InternalServerError	= 500,
    HttpStatusCode_NotImplemented	= 501,
    HttpStatusCode_BadGateway	= 502,
    HttpStatusCode_ServiceUnavailable	= 503,
    HttpStatusCode_GatewayTimeout	= 504,
    HttpStatusCode_HttpVersionNotSupported	= 505,
    HttpStatusCode_VariantAlsoNegotiates	= 506,
    HttpStatusCode_InsufficientStorage	= 507,
    HttpStatusCode_LoopDetected = 508,
    HttpStatusCode_NotExtended	= 510,
    HttpStatusCode_NetworkAuthenticationRequired	= 511
    }
endif


.template HttpProgress
    Stage			Windows::Web::Http::HttpProgressStage ?
    BytesSent			UINT64 ?
    TotalBytesToSend		ptr __FIReference_1_UINT64 ?
    BytesReceived		UINT64 ?
    TotalBytesToReceive		ptr __FIReference_1_UINT64 ?
    Retries			UINT32 ?
   .ends

.endn
.endn
.endn

include Windows.Security.Cryptography.Certificates.inc
include Windows.Storage.Streams.inc

include Windows.Web.Http.Filters.inc
include Windows.Web.Http.Headers.inc
include windows.foundation.collections.inc

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHttpCookie_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHttpCookie_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHttpCookie, "626bc177-8403-5030-a88c-7485cc89d730")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHttpCookie : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHttpCookie_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHttpCookie_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHttpCookie, "0eb9fa36-88de-590d-8ea0-b613d0ab015f")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHttpCookie : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CHttpMethod, "d13a880f-d612-50cf-a6f9-dd96f916f491")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CHttpMethod : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CHttpMethod, "c088bb1a-dc61-57e1-b967-78dab3541da5")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CHttpMethod : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIIterator_1_Windows__CWeb__CHttp__CIHttpContent_INTERFACE_DEFINED__
define ____FIIterator_1_Windows__CWeb__CHttp__CIHttpContent_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterator_1_Windows__CWeb__CHttp__CIHttpContent, "59f44f31-695e-5af7-a3c5-85c01939cec8")

.comdef __FIIterator_1_Windows__CWeb__CHttp__CIHttpContent : public IInspectable

    get_Current		proc :ptr
    get_HasCurrent	proc :ptr
    MoveNext		proc :ptr
    GetMany		proc :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIIterable_1_Windows__CWeb__CHttp__CIHttpContent_INTERFACE_DEFINED__
define ____FIIterable_1_Windows__CWeb__CHttp__CIHttpContent_INTERFACE_DEFINED__
DEFINE_IIDX(__FIIterable_1_Windows__CWeb__CHttp__CIHttpContent, "f102157f-b482-5736-9d12-c683bc494942")

.comdef __FIIterable_1_Windows__CWeb__CHttp__CIHttpContent : public IInspectable

    First		proc :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHttpCookie_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHttpCookie_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHttpCookie, "0064c4f6-3fca-5823-9d92-86c40b28adbc")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHttpCookie : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVectorView_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
define ____FIVectorView_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVectorView_1_Windows__CWeb__CHttp__CHttpMethod, "ef132fb7-d286-5327-b38a-be7d008328fe")

.comdef __FIVectorView_1_Windows__CWeb__CHttp__CHttpMethod : public IInspectable

    GetAt		proc :SINT, :ptr
    get_Size		proc :ptr
    IndexOf		proc :ptr, :ptr, :ptr
    GetMany		proc :SINT, :SINT, :ptr, :ptr
   .ends

endif

ifndef ____FIVector_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
define ____FIVector_1_Windows__CWeb__CHttp__CHttpMethod_INTERFACE_DEFINED__
DEFINE_IIDX(__FIVector_1_Windows__CWeb__CHttp__CHttpMethod, "228a73a2-a509-5a78-bd7f-db94ba0bef21")

.comdef __FIVector_1_Windows__CWeb__CHttp__CHttpMethod : public IInspectable

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

ifndef ____FIAsyncOperationProgressHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress, "cf0a03f6-a80a-5b46-9c80-f4ad9ed6e2d6")

.comdef __FIAsyncOperationProgressHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :Windows::Web::Http::HttpProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress, "98ab9acb-38db-588f-a5f9-9f484b2200cd")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress, "91ecbe45-e889-5518-bd8d-c5bde163109b")

.comdef __FIAsyncOperationWithProgress_2_HSTRING_Windows__CWeb__CHttp__CHttpProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress, "9eb2b852-e019-5440-8f88-0dd7d56fea47")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :Windows::Web::Http::HttpProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress, "b0cf2f85-6992-52be-8f0b-93964b14d963")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress, "88d9bb75-afb4-5f32-9d7e-d3bf3785354c")

.comdef __FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIBuffer_Windows__CWeb__CHttp__CHttpProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress, "04682e89-6e8b-54b1-a466-432e130cf9a6")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :Windows::Web::Http::HttpProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress, "504a34ec-5499-5a16-bffc-3ccb64a3547a")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress, "0b97c784-df17-571f-8337-447dff068a9c")

.comdef __FIAsyncOperationWithProgress_2_Windows__CStorage__CStreams__CIInputStream_Windows__CWeb__CHttp__CHttpProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr
   .ends

endif

ifndef ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationProgressHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationProgressHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress, "68e4606a-76ec-5816-b2fe-a04ecde4126a")

.comdef __FIAsyncOperationProgressHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :ptr Windows::Web::Http::HttpProgress
   .ends

endif

ifndef ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress, "beadb572-f9a3-5e93-b6ca-e311b65933fc")

.comdef __FIAsyncOperationWithProgressCompletedHandler_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress : public IUnknown

    IInvoke		proc :ptr, :AsyncStatus
   .ends

endif

ifndef ____FIAsyncOperationWithProgress_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
define ____FIAsyncOperationWithProgress_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress_INTERFACE_DEFINED__
DEFINE_IIDX(__FIAsyncOperationWithProgress_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress, "5d144364-77d7-5eca-8b09-936a69446652")

.comdef __FIAsyncOperationWithProgress_2_Windows__CWeb__CHttp__CHttpResponseMessage_Windows__CWeb__CHttp__CHttpProgress : public IInspectable

    put_Progress	proc :ptr
    get_Progress	proc :ptr
    put_Completed	proc :ptr
    get_Completed	proc :ptr
    GetResults		proc :ptr ptr Windows::Web::Http::IHttpResponseMessage
   .ends

endif


.namespace Windows
.namespace Web
.namespace Http

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpClientFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpClientFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpClientFactory <L"Windows.Web.Http.IHttpClientFactory">
DEFINE_IIDX(IHttpClientFactory, "C30C4ECA-E3FA-4F99-AFB4-63CC65009462")

.comdef IHttpClientFactory : public IInspectable

    Create		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpClient_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpClient_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpClient <L"Windows.Web.Http.IHttpClient">
DEFINE_IIDX(IHttpClient, "7FDA1151-3574-4880-A8BA-E6B1E0061F3D")

.comdef IHttpClient : public IInspectable

    DeleteAsync		proc :ptr, :ptr
    GetAsync		proc :ptr, :ptr
    GetWithOptionAsync	proc :ptr, :Windows::Web::Http::HttpCompletionOption, :ptr
    GetBufferAsync	proc :ptr, :ptr
    GetInputStreamAsync proc :ptr, :ptr
    GetStringAsync	proc :ptr, :ptr
    PostAsync		proc :ptr, :ptr, :ptr
    PutAsync		proc :ptr, :ptr, :ptr
    SendRequestAsync	proc :ptr, :ptr
    SendRequestWithOptionAsync proc :ptr, :Windows::Web::Http::HttpCompletionOption, :ptr
    get_DefaultRequestHeaders proc :ptr
   .ends

endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpClient2_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpClient2_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpClient2 <"Windows.Web.Http.IHttpClient2">
DEFINE_IIDX(IHttpClient2, "cdd83348-e8b7-4cec-b1b0-dc455fe72c92")

.comdef IHttpClient2 : public IInspectable
    TryDeleteAsync	proc :ptr, :ptr ptr
    TryGetAsync		proc :ptr, :ptr ptr
    TryGetAsync2	proc :ptr, :Windows::Web::Http::HttpCompletionOption, :ptr ptr
    TryGetBufferAsync	proc :ptr, :ptr ptr
    TryGetInputStreamAsync proc :ptr, :ptr ptr
    TryGetStringAsync	proc :ptr, :ptr ptr
    TryPostAsync	proc :ptr, :ptr, :ptr ptr
    TryPutAsync		proc :ptr, :ptr, :ptr ptr
    TrySendRequestAsync proc :ptr, :ptr ptr
    TrySendRequestAsync2 proc :ptr, :Windows::Web::Http::HttpCompletionOption, :ptr ptr
   .ends
endif
endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpContent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpContent_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpContent <L"Windows.Web.Http.IHttpContent">
DEFINE_IIDX(IHttpContent, "6B14A441-FBA7-4BD2-AF0A-839DE7C295DA")

.comdef IHttpContent : public IInspectable

    get_Headers		proc :ptr
    BufferAllAsync	proc :ptr
    ReadAsBufferAsync	proc :ptr
    ReadAsInputStreamAsync proc :ptr
    ReadAsStringAsync	proc :ptr
    TryComputeLength	proc :ptr, :ptr
    WriteToStreamAsync	proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpCookieManager_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpCookieManager_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpCookieManager <L"Windows.Web.Http.IHttpCookieManager">
DEFINE_IIDX(IHttpCookieManager, "7A431780-CD4F-4E57-A84A-5B0A53D6BB96")

.comdef IHttpCookieManager : public IInspectable

    SetCookie		proc :ptr, :ptr
    SetCookieWithThirdParty proc :ptr, :boolean, :ptr
    DeleteCookie	proc :ptr
    GetCookies		proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpCookieFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpCookieFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpCookieFactory <L"Windows.Web.Http.IHttpCookieFactory">
DEFINE_IIDX(IHttpCookieFactory, "6A0585A9-931C-4CD1-A96D-C21701785C5F")

.comdef IHttpCookieFactory : public IInspectable

    Create		proc :HSTRING, :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpCookie_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpCookie_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpCookie <L"Windows.Web.Http.IHttpCookie">
DEFINE_IIDX(IHttpCookie, "1F5488E2-CC2D-4779-86A7-88F10687D249")

.comdef IHttpCookie : public IInspectable

    get_Name		proc :ptr
    get_Domain		proc :ptr
    get_Path		proc :ptr
    get_Expires		proc :ptr
    put_Expires		proc :ptr
    get_HttpOnly	proc :ptr
    put_HttpOnly	proc :boolean
    get_Secure		proc :ptr
    put_Secure		proc :boolean
    get_Value		proc :ptr
    put_Value		proc :HSTRING
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMethodStatics_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMethodStatics_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMethodStatics <L"Windows.Web.Http.IHttpMethodStatics">
DEFINE_IIDX(IHttpMethodStatics, "64D171F0-D99A-4153-8DC6-D68CC4CCE317")

.comdef IHttpMethodStatics : public IInspectable

    get_Delete		proc :ptr
    get_Get		proc :ptr
    get_Head		proc :ptr
    get_Options		proc :ptr
    get_Patch		proc :ptr
    get_Post		proc :ptr
    get_Put		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMethodFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMethodFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMethodFactory <L"Windows.Web.Http.IHttpMethodFactory">
DEFINE_IIDX(IHttpMethodFactory, "3C51D10D-36D7-40F8-A86D-E759CAF2F83F")

.comdef IHttpMethodFactory : public IInspectable

    Create		proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMethod_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMethod_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMethod <L"Windows.Web.Http.IHttpMethod">
DEFINE_IIDX(IHttpMethod, "728D4022-700D-4FE0-AFA5-40299C58DBFD")

.comdef IHttpMethod : public IInspectable

    get_Method		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpTransportInformation_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpTransportInformation_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpTransportInformation <L"Windows.Web.Http.IHttpTransportInformation">
DEFINE_IIDX(IHttpTransportInformation, "70127198-C6A7-4ED0-833A-83FD8B8F178D")

.comdef IHttpTransportInformation : public IInspectable

    get_ServerCertificate proc :ptr
    get_ServerCertificateErrorSeverity proc :ptr
    get_ServerCertificateErrors proc :ptr
    get_ServerIntermediateCertificates proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpRequestMessageFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpRequestMessageFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpRequestMessageFactory <L"Windows.Web.Http.IHttpRequestMessageFactory">
DEFINE_IIDX(IHttpRequestMessageFactory, "5BAC994E-3886-412E-AEC3-52EC7F25616F")

.comdef IHttpRequestMessageFactory : public IInspectable

    Create		proc :ptr, :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpRequestMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpRequestMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpRequestMessage <L"Windows.Web.Http.IHttpRequestMessage">
DEFINE_IIDX(IHttpRequestMessage, "F5762B3C-74D4-4811-B5DC-9F8B4E2F9ABF")

.comdef IHttpRequestMessage : public IInspectable

    get_Content		proc :ptr
    put_Content		proc :ptr
    get_Headers		proc :ptr
    get_Method		proc :ptr
    put_Method		proc :ptr
    get_Properties	proc :ptr
    get_RequestUri	proc :ptr
    put_RequestUri	proc :ptr
    get_TransportInformation proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessageFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessageFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpResponseMessageFactory <L"Windows.Web.Http.IHttpResponseMessageFactory">
DEFINE_IIDX(IHttpResponseMessageFactory, "52A8AF99-F095-43DA-B60F-7CFC2BC7EA2F")

.comdef IHttpResponseMessageFactory : public IInspectable

    Create		proc :Windows::Web::Http::HttpStatusCode, :ptr
   .ends

endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpRequestResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpRequestResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpRequestResult <"Windows.Web.Http.IHttpRequestResult">
DEFINE_IIDX(IHttpRequestResult, "6acf4da8-b5eb-4a35-a902-4217fbe820c5")

.comdef IHttpRequestResult : public IInspectable
    get_ExtendedError	proc :ptr
    get_RequestMessage	proc :ptr ptr
    get_ResponseMessage proc :ptr ptr
    get_Succeeded	proc :ptr
   .ends
endif
endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpResponseMessage_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpResponseMessage <L"Windows.Web.Http.IHttpResponseMessage">
DEFINE_IIDX(IHttpResponseMessage, "FEE200FB-8664-44E0-95D9-42696199BFFC")

.comdef IHttpResponseMessage : public IInspectable

    get_Content		proc :ptr
    put_Content		proc :ptr
    get_Headers		proc :ptr
    get_IsSuccessStatusCode proc :ptr
    get_ReasonPhrase	proc :ptr
    put_ReasonPhrase	proc :HSTRING
    get_RequestMessage	proc :ptr
    put_RequestMessage	proc :ptr
    get_Source		proc :ptr
    put_Source		proc :Windows::Web::Http::HttpResponseMessageSource
    get_StatusCode	proc :ptr
    put_StatusCode	proc :Windows::Web::Http::HttpStatusCode
    get_Version		proc :ptr
    put_Version		proc :Windows::Web::Http::HttpVersion
    EnsureSuccessStatusCode proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpStringContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpStringContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpStringContentFactory <L"Windows.Web.Http.IHttpStringContentFactory">
DEFINE_IIDX(IHttpStringContentFactory, "46649D5B-2E93-48EB-8E61-19677878E57F")

.comdef IHttpStringContentFactory : public IInspectable

    CreateFromString	proc :HSTRING, :ptr
    CreateFromStringWithEncoding proc :HSTRING, :Windows::Storage::Streams::UnicodeEncoding, :ptr
    CreateFromStringWithEncodingAndMediaType proc :HSTRING, :Windows::Storage::Streams::UnicodeEncoding, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpBufferContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpBufferContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpBufferContentFactory <L"Windows.Web.Http.IHttpBufferContentFactory">
DEFINE_IIDX(IHttpBufferContentFactory, "BC20C193-C41F-4FF7-9123-6435736EADC2")

.comdef IHttpBufferContentFactory : public IInspectable

    CreateFromBuffer	proc :ptr, :ptr
    CreateFromBufferWithOffset proc :ptr, :UINT32, :UINT32, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpStreamContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpStreamContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpStreamContentFactory <L"Windows.Web.Http.IHttpStreamContentFactory">
DEFINE_IIDX(IHttpStreamContentFactory, "F3E64D9D-F725-407E-942F-0EDA189809F4")

.comdef IHttpStreamContentFactory : public IInspectable

    CreateFromInputStream proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpFormUrlEncodedContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpFormUrlEncodedContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpFormUrlEncodedContentFactory <L"Windows.Web.Http.IHttpFormUrlEncodedContentFactory">
DEFINE_IIDX(IHttpFormUrlEncodedContentFactory, "43F0138C-2F73-4302-B5F3-EAE9238A5E01")

.comdef IHttpFormUrlEncodedContentFactory : public IInspectable

    Create		proc :ptr, :ptr
   .ends

endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpGetBufferResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpGetBufferResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpGetBufferResult <"Windows.Web.Http.IHttpGetBufferResult">
DEFINE_IIDX(IHttpGetBufferResult, "53d08e7c-e209-404e-9a49-742d8236fd3a")

.comdef IHttpGetBufferResult : public IInspectable
    get_ExtendedError	proc :ptr
    get_RequestMessage	proc :ptr ptr
    get_ResponseMessage proc :ptr ptr
    get_Succeeded	proc :ptr
    get_Value		proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpGetInputStreamResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpGetInputStreamResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpGetInputStreamResult <"Windows.Web.Http.IHttpGetInputStreamResult">
DEFINE_IIDX(IHttpGetInputStreamResult, "d5d63463-13aa-4ee0-be95-a0c39fe91203")

.comdef IHttpGetInputStreamResult : public IInspectable
    get_ExtendedError	proc :ptr
    get_RequestMessage	proc :ptr ptr
    get_ResponseMessage proc :ptr ptr
    get_Succeeded	proc :ptr
    get_Value		proc :ptr ptr
   .ends
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpGetStringResult_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpGetStringResult_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpGetStringResult <"Windows.Web.Http.IHttpGetStringResult">
DEFINE_IIDX(IHttpGetStringResult, "9bac466d-8509-4775-b16d-8953f47a7f5f")

.comdef IHttpGetStringResult : public IInspectable
    get_ExtendedError	proc :ptr
    get_RequestMessage	proc :ptr ptr
    get_ResponseMessage proc :ptr ptr
    get_Succeeded	proc :ptr
    get_Value		proc :ptr
   .ends
endif
endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMultipartContentFactory <L"Windows.Web.Http.IHttpMultipartContentFactory">
DEFINE_IIDX(IHttpMultipartContentFactory, "7EB42E62-0222-4F20-B372-47D5DB5D33B4")

.comdef IHttpMultipartContentFactory : public IInspectable

    CreateWithSubtype	proc :HSTRING, :ptr
    CreateWithSubtypeAndBoundary proc :HSTRING, :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartContent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartContent_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMultipartContent <L"Windows.Web.Http.IHttpMultipartContent">
DEFINE_IIDX(IHttpMultipartContent, "DF916AFF-9926-4AC9-AAF1-E0D04EF09BB9")

.comdef IHttpMultipartContent : public IInspectable

    _Add		proc :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartFormDataContentFactory_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartFormDataContentFactory_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMultipartFormDataContentFactory <L"Windows.Web.Http.IHttpMultipartFormDataContentFactory">
DEFINE_IIDX(IHttpMultipartFormDataContentFactory, "A04D7311-5017-4622-93A8-49B24A4FCBFC")

.comdef IHttpMultipartFormDataContentFactory : public IInspectable

    CreateWithBoundary	proc :HSTRING, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartFormDataContent_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CIHttpMultipartFormDataContent_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_IHttpMultipartFormDataContent <L"Windows.Web.Http.IHttpMultipartFormDataContent">
DEFINE_IIDX(IHttpMultipartFormDataContent, "64D337E2-E967-4624-B6D1-CF74604A4A42")

.comdef IHttpMultipartFormDataContent : public IInspectable

    _Add		proc :ptr
    AddWithName		proc :ptr, :HSTRING
    AddWithNameAndFileName proc :ptr, :HSTRING, :HSTRING
   .ends

endif

.endn
.endn
.endn

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000

ifndef RUNTIMECLASS_Windows_Web_Http_HttpBufferContent_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpBufferContent_DEFINED
define RuntimeClass_Windows_Web_Http_HttpBufferContent <"Windows.Web.Http.HttpBufferContent">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpClient_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpClient_DEFINED
define RuntimeClass_Windows_Web_Http_HttpClient <"Windows.Web.Http.HttpClient">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpCookie_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpCookie_DEFINED
define RuntimeClass_Windows_Web_Http_HttpCookie <"Windows.Web.Http.HttpCookie">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpCookieCollection_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpCookieCollection_DEFINED
define RuntimeClass_Windows_Web_Http_HttpCookieCollection <"Windows.Web.Http.HttpCookieCollection">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpCookieManager_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpCookieManager_DEFINED
define RuntimeClass_Windows_Web_Http_HttpCookieManager <"Windows.Web.Http.HttpCookieManager">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpFormUrlEncodedContent_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpFormUrlEncodedContent_DEFINED
define RuntimeClass_Windows_Web_Http_HttpFormUrlEncodedContent <"Windows.Web.Http.HttpFormUrlEncodedContent">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_Web_Http_HttpGetBufferResult_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpGetBufferResult_DEFINED
define RuntimeClass_Windows_Web_Http_HttpGetBufferResult <"Windows.Web.Http.HttpGetBufferResult">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpGetInputStreamResult_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpGetInputStreamResult_DEFINED
define RuntimeClass_Windows_Web_Http_HttpGetInputStreamResult <"Windows.Web.Http.HttpGetInputStreamResult">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpGetStringResult_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpGetStringResult_DEFINED
define RuntimeClass_Windows_Web_Http_HttpGetStringResult <"Windows.Web.Http.HttpGetStringResult">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000

ifndef RUNTIMECLASS_Windows_Web_Http_HttpMethod_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpMethod_DEFINED
define RuntimeClass_Windows_Web_Http_HttpMethod <"Windows.Web.Http.HttpMethod">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpMultipartContent_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpMultipartContent_DEFINED
define RuntimeClass_Windows_Web_Http_HttpMultipartContent <"Windows.Web.Http.HttpMultipartContent">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpMultipartFormDataContent_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpMultipartFormDataContent_DEFINED
define RuntimeClass_Windows_Web_Http_HttpMultipartFormDataContent <"Windows.Web.Http.HttpMultipartFormDataContent">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpRequestMessage_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpRequestMessage_DEFINED
define RuntimeClass_Windows_Web_Http_HttpRequestMessage <"Windows.Web.Http.HttpRequestMessage">
endif
endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x80000
ifndef RUNTIMECLASS_Windows_Web_Http_HttpRequestResult_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpRequestResult_DEFINED
define RuntimeClass_Windows_Web_Http_HttpRequestResult <"Windows.Web.Http.HttpRequestResult">
endif

endif

if WINDOWS_FOUNDATION_UNIVERSALAPICONTRACT_VERSION ge 0x10000

ifndef RUNTIMECLASS_Windows_Web_Http_HttpResponseMessage_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpResponseMessage_DEFINED
define RuntimeClass_Windows_Web_Http_HttpResponseMessage <"Windows.Web.Http.HttpResponseMessage">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpStreamContent_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpStreamContent_DEFINED
define RuntimeClass_Windows_Web_Http_HttpStreamContent <"Windows.Web.Http.HttpStreamContent">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpStringContent_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpStringContent_DEFINED
define RuntimeClass_Windows_Web_Http_HttpStringContent <"Windows.Web.Http.HttpStringContent">
endif

ifndef RUNTIMECLASS_Windows_Web_Http_HttpTransportInformation_DEFINED
define RUNTIMECLASS_Windows_Web_Http_HttpTransportInformation_DEFINED
define RuntimeClass_Windows_Web_Http_HttpTransportInformation <"Windows.Web.Http.HttpTransportInformation">
endif

endif

endif
