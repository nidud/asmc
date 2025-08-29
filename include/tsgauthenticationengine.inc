ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __tsgauthenticationengine_h__
define __tsgauthenticationengine_h__

include oaidl.inc
include ocidl.inc
include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __ITSGAuthenticateUserSink_INTERFACE_DEFINED__
define __ITSGAuthenticateUserSink_INTERFACE_DEFINED__

DEFINE_IIDX(ITSGAuthenticateUserSink, "2c3e2e73-a782-47f9-8dfb-77ee1ed27a03")

.comdef ITSGAuthenticateUserSink : public IUnknown
    OnUserAuthenticated proc :BSTR, :BSTR, :ULONG_PTR, :HANDLE_PTR
    OnUserAuthenticationFailed proc :ULONG_PTR, :HRESULT, :HRESULT
    ReauthenticateUser  proc :ULONG_PTR
    DisconnectUser      proc :ULONG_PTR
   .ends

endif

ifndef __ITSGAuthenticationEngine_INTERFACE_DEFINED__
define __ITSGAuthenticationEngine_INTERFACE_DEFINED__

DEFINE_IIDX(ITSGAuthenticationEngine, "9ee3e5bf-04ab-4691-998c-d7f622321a56")

.comdef ITSGAuthenticationEngine : public IUnknown
    AuthenticateUser    proc :GUID, :ptr, :ULONG, :ULONG_PTR, :ptr
    CancelAuthentication proc :GUID, :ULONG_PTR
   .ends

endif

endif

endif
