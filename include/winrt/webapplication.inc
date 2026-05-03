ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __webapplication_h__
define __webapplication_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
include Mshtml.inc
include activscp.inc
include urlmon.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
ifndef __IWebApplicationScriptEvents_INTERFACE_DEFINED__
define __IWebApplicationScriptEvents_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationScriptEvents, "7C3F6998-1567-4BBA-B52B-48D32141D613")

.comdef IWebApplicationScriptEvents : public IUnknown

    BeforeScriptExecute proc :ptr
    ScriptError         proc :ptr, :ptr, :LPCWSTR, :BOOL
   .ends

endif

ifndef __IWebApplicationNavigationEvents_INTERFACE_DEFINED__
define __IWebApplicationNavigationEvents_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationNavigationEvents, "C22615D2-D318-4DA2-8422-1FCAF77B10E4")

.comdef IWebApplicationNavigationEvents : public IUnknown

    BeforeNavigate      proc :ptr, :LPCWSTR, :DWORD, :LPCWSTR
    NavigateComplete    proc :ptr, :LPCWSTR
    NavigateError       proc :ptr, :LPCWSTR, :LPCWSTR, :DWORD
    DocumentComplete    proc :ptr, :LPCWSTR
    DownloadBegin       proc
    DownloadComplete    proc
   .ends

endif

ifndef __IWebApplicationUIEvents_INTERFACE_DEFINED__
define __IWebApplicationUIEvents_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationUIEvents, "5B2B3F99-328C-41D5-A6f7-7483ED8E71DD")

.comdef IWebApplicationUIEvents : public IUnknown

    SecurityProblem     proc :DWORD, :ptr
   .ends

endif

ifndef __IWebApplicationUpdateEvents_INTERFACE_DEFINED__
define __IWebApplicationUpdateEvents_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationUpdateEvents, "3E59E6B7-C652-4DAF-AD5E-16FEB350CDE3")

.comdef IWebApplicationUpdateEvents : public IUnknown

    OnPaint             proc
    OnCssChanged        proc
   .ends

endif

ifndef __IWebApplicationHost_INTERFACE_DEFINED__
define __IWebApplicationHost_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationHost, "CECBD2C3-A3A5-4749-9681-20E9161C6794")

.comdef IWebApplicationHost : public IUnknown

    get_HWND            proc :ptr
    get_Document        proc :ptr
    Refresh             proc
    Advise              proc :REFIID, :ptr, :ptr
    Unadvise            proc :DWORD
   .ends

endif

ifndef __IWebApplicationActivation_INTERFACE_DEFINED__
define __IWebApplicationActivation_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationActivation, "BCDCD0DE-330E-481B-B843-4898A6A8EBAC")

.comdef IWebApplicationActivation : public IUnknown

    CancelPendingActivation proc
   .ends

endif

ifndef __IWebApplicationAuthoringMode_INTERFACE_DEFINED__
define __IWebApplicationAuthoringMode_INTERFACE_DEFINED__
DEFINE_IIDX(IWebApplicationAuthoringMode, "720AEA93-1964-4DB0-B005-29EB9E2B18A9")

.comdef IWebApplicationAuthoringMode : public IServiceProvider

    get_AuthoringClientBinary proc :ptr
   .ends

endif
define SID_SWebApplicationAuthor <IID_IWebApplicationAuthoringMode>

CALLBACK(RegisterAuthoringClientFunctionType, :ptr, :ptr)
CALLBACK(UnregisterAuthoringClientFunctionType, :ptr)

endif

endif
