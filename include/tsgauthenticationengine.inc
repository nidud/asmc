ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __tsgauthenticationengine_h__
define __tsgauthenticationengine_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

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
