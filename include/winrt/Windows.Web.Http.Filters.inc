ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __windows2Eweb2Ehttp2Efilters_h__
define __windows2Eweb2Ehttp2Efilters_h__
ifndef __windows2Efoundation_h__
include Windows.Foundation.inc
endif
include Windows.Security.Credentials.inc
include Windows.Security.Cryptography.Certificates.inc
include Windows.Web.Http.inc

.namespace Windows
.namespace Web
.namespace Http
.namespace Filters

.enum HttpCacheReadBehavior {
    HttpCacheReadBehavior_Default   = 0,
    HttpCacheReadBehavior_MostRecent    = 1,
    HttpCacheReadBehavior_OnlyFromCache = 2
    }

.enum HttpCacheWriteBehavior {
    HttpCacheWriteBehavior_Default  = 0,
    HttpCacheWriteBehavior_NoCache  = 1
    }

ifndef ____x_ABI_CWindows_CWeb_CHttp_CFilters_CIHttpFilter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CFilters_CIHttpFilter_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Filters_IHttpFilter <L"Windows.Web.Http.Filters.IHttpFilter">
DEFINE_IIDX(IHttpFilter, "A4CB6DD5-0902-439E-BFD7-E12552B165CE")

.comdef IHttpFilter : public IInspectable

    SendRequestAsync    proc :ptr, :ptr
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CFilters_CIHttpCacheControl_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CFilters_CIHttpCacheControl_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Filters_IHttpCacheControl <L"Windows.Web.Http.Filters.IHttpCacheControl">
DEFINE_IIDX(IHttpCacheControl, "C77E1CB4-3CEA-4EB5-AC85-04E186E63AB7")

.comdef IHttpCacheControl : public IInspectable

    get_ReadBehavior    proc :ptr
    put_ReadBehavior    proc :Windows::Web::Http::Filters::HttpCacheReadBehavior
    get_WriteBehavior   proc :ptr
    put_WriteBehavior   proc :Windows::Web::Http::Filters::HttpCacheWriteBehavior
   .ends

endif

ifndef ____x_ABI_CWindows_CWeb_CHttp_CFilters_CIHttpBaseProtocolFilter_INTERFACE_DEFINED__
define ____x_ABI_CWindows_CWeb_CHttp_CFilters_CIHttpBaseProtocolFilter_INTERFACE_DEFINED__
define InterfaceName_Windows_Web_Http_Filters_IHttpBaseProtocolFilter <L"Windows.Web.Http.Filters.IHttpBaseProtocolFilter">
DEFINE_IIDX(IHttpBaseProtocolFilter, "71C89B09-E131-4B54-A53C-EB43FF37E9BB")

.comdef IHttpBaseProtocolFilter : public IInspectable

    get_AllowAutoRedirect proc :ptr
    put_AllowAutoRedirect proc :boolean
    get_AllowUI         proc :ptr
    put_AllowUI         proc :boolean
    get_AutomaticDecompression proc :ptr
    put_AutomaticDecompression proc :boolean
    get_CacheControl    proc :ptr
    get_CookieManager   proc :ptr
    get_ClientCertificate proc :ptr
    put_ClientCertificate proc :ptr
    get_IgnorableServerCertificateErrors proc :ptr
    get_MaxConnectionsPerServer proc :ptr
    put_MaxConnectionsPerServer proc :UINT32
    get_ProxyCredential proc :ptr
    put_ProxyCredential proc :ptr
    get_ServerCredential proc :ptr
    put_ServerCredential proc :ptr
    get_UseProxy        proc :ptr
    put_UseProxy        proc :boolean
   .ends

endif

.endn
.endn
.endn
.endn

ifndef RUNTIMECLASS_Windows_Web_Http_Filters_HttpCacheControl_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Filters_HttpCacheControl_DEFINED
define RuntimeClass_Windows_Web_Http_Filters_HttpCacheControl <L"Windows.Web.Http.Filters.HttpCacheControl">
endif
ifndef RUNTIMECLASS_Windows_Web_Http_Filters_HttpBaseProtocolFilter_DEFINED
define RUNTIMECLASS_Windows_Web_Http_Filters_HttpBaseProtocolFilter_DEFINED
define RuntimeClass_Windows_Web_Http_Filters_HttpBaseProtocolFilter <L"Windows.Web.Http.Filters.HttpBaseProtocolFilter">
endif

endif
