ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __wbemprov_h__
define __wbemprov_h__

include objidl.inc
include oleidl.inc
ifndef __oaidl_h__
include oaidl.inc
endif
include wbemcli.inc
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

WBEM_VARIANT		typedef VARIANT
WBEM_WSTR		typedef LPWSTR
WBEM_CWSTR		typedef LPCWSTR

.enum WBEM_PROVIDER_REQUIREMENTS_TYPE {
    WBEM_REQUIREMENTS_START_POSTFILTER	= 0,
    WBEM_REQUIREMENTS_STOP_POSTFILTER	= 1,
    WBEM_REQUIREMENTS_RECHECK_SUBSCRIPTIONS	= 2
    }

ifndef __WbemProviders_v1_LIBRARY_DEFINED__
define __WbemProviders_v1_LIBRARY_DEFINED__

externdef LIBID_WbemProviders_v1:IID

ifndef __IWbemPropertyProvider_INTERFACE_DEFINED__
define __IWbemPropertyProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemPropertyProvider, "CE61E841-65BC-11d0-B6BD-00AA003240C7")

.comdef IWbemPropertyProvider : public IUnknown

    GetProperty		proc :LONG, :BSTR, :BSTR, :BSTR, :BSTR, :ptr
    PutProperty		proc :LONG, :BSTR, :BSTR, :BSTR, :BSTR, :ptr
   .ends

endif

ifndef __IWbemUnboundObjectSink_INTERFACE_DEFINED__
define __IWbemUnboundObjectSink_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemUnboundObjectSink, "e246107b-b06e-11d0-ad61-00c04fd8fdff")

.comdef IWbemUnboundObjectSink : public IUnknown

    IndicateToConsumer	proc :ptr, :LONG, :ptr
   .ends

endif

ifndef __IWbemEventProvider_INTERFACE_DEFINED__
define __IWbemEventProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemEventProvider, "e245105b-b06e-11d0-ad61-00c04fd8fdff")

.comdef IWbemEventProvider : public IUnknown

    ProvideEvents	proc :ptr, :LONG
   .ends

endif

ifndef __IWbemEventProviderQuerySink_INTERFACE_DEFINED__
define __IWbemEventProviderQuerySink_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemEventProviderQuerySink, "580acaf8-fa1c-11d0-ad72-00c04fd8fdff")

.comdef IWbemEventProviderQuerySink : public IUnknown

    NewQuery		proc :LONG, :WBEM_WSTR, :WBEM_WSTR
    CancelQuery		proc :LONG
   .ends

endif

ifndef __IWbemEventProviderSecurity_INTERFACE_DEFINED__
define __IWbemEventProviderSecurity_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemEventProviderSecurity, "631f7d96-d993-11d2-b339-00105a1f4aaf")

.comdef IWbemEventProviderSecurity : public IUnknown

    AccessCheck		proc :WBEM_CWSTR, :WBEM_CWSTR, :LONG, :ptr
   .ends

endif

ifndef __IWbemEventConsumerProvider_INTERFACE_DEFINED__
define __IWbemEventConsumerProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemEventConsumerProvider, "e246107a-b06e-11d0-ad61-00c04fd8fdff")

.comdef IWbemEventConsumerProvider : public IUnknown

    FindConsumer	proc :ptr, :ptr
   .ends

endif

ifndef __IWbemProviderInitSink_INTERFACE_DEFINED__
define __IWbemProviderInitSink_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemProviderInitSink, "1be41571-91dd-11d1-aeb2-00c04fb68820")

.comdef IWbemProviderInitSink : public IUnknown

    SetStatus		proc :LONG, :LONG
   .ends

endif

ifndef __IWbemProviderInit_INTERFACE_DEFINED__
define __IWbemProviderInit_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemProviderInit, "1be41572-91dd-11d1-aeb2-00c04fb68820")

.comdef IWbemProviderInit : public IUnknown

    Initialize		proc :LPWSTR, :LONG, :LPWSTR, :LPWSTR, :ptr, :ptr, :ptr
   .ends

endif

ifndef __IWbemHiPerfProvider_INTERFACE_DEFINED__
define __IWbemHiPerfProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemHiPerfProvider, "49353c93-516b-11d1-aea6-00c04fb68820")

.comdef IWbemHiPerfProvider : public IUnknown

    QueryInstances	proc :ptr, :ptr, :LONG, :ptr, :ptr
    CreateRefresher	proc :ptr, :LONG, :ptr
    CreateRefreshableObject proc :ptr, :ptr, :ptr, :LONG, :ptr, :ptr, :ptr
    StopRefreshing	proc :ptr, :LONG, :LONG
    CreateRefreshableEnum proc :ptr, :LPCWSTR, :ptr, :LONG, :ptr, :ptr, :ptr
    GetObjects		proc :ptr, :LONG, :ptr, :LONG, :ptr
   .ends

endif

ifndef __IWbemDecoupledRegistrar_INTERFACE_DEFINED__
define __IWbemDecoupledRegistrar_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemDecoupledRegistrar, "1005cbcf-e64f-4646-bcd3-3a089d8a84b4")

.comdef IWbemDecoupledRegistrar : public IUnknown

    Register		proc :LONG, :ptr, :LPCWSTR, :LPCWSTR, :LPCWSTR, :LPCWSTR, :ptr
    UnRegister		proc
   .ends

endif

DEFINE_GUIDS(CLSID_WbemAdministrativeLocator, "cb8555cc-9128-11d1-ad9b-00c04fd8fdff")
DEFINE_GUIDS(CLSID_WbemAuthenticatedLocator, "cd184336-9128-11d1-ad9b-00c04fd8fdff")
DEFINE_GUIDS(CLSID_WbemUnauthenticatedLocator, "443E7B79-DE31-11d2-B340-00104BCC4B4A")
DEFINE_GUIDS(CLSID_WbemDecoupledRegistrar, "4cfc7932-0f9d-4bef-9c32-8ea2a6b56fcb")
DEFINE_GUIDS(CLSID_WbemDecoupledBasicEventProvider, "f5f75737-2843-4f22-933d-c76a97cda62f")

endif

ifndef __IWbemProviderIdentity_INTERFACE_DEFINED__
define __IWbemProviderIdentity_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemProviderIdentity, "631f7d97-d993-11d2-b339-00105a1f4aaf")

.comdef IWbemProviderIdentity : public IUnknown

    SetRegistrationObject proc :LONG, :ptr
   .ends

endif

.enum WBEM_EXTRA_RETURN_CODES {
    WBEM_S_INITIALIZED,
    WBEM_S_LIMITED_SERVICE	= 0x43001,
    WBEM_S_INDIRECTLY_UPDATED,
    WBEM_S_SUBJECT_TO_SDS,
    WBEM_E_RETRY_LATER	= 0x80043001,
    WBEM_E_RESOURCE_CONTENTION
    }

.enum WBEM_PROVIDER_FLAGS {
    WBEM_FLAG_OWNER_UPDATE	= 0x10000
    }


ifndef __IWbemDecoupledBasicEventProvider_INTERFACE_DEFINED__
define __IWbemDecoupledBasicEventProvider_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemDecoupledBasicEventProvider, "86336d20-ca11-4786-9ef1-bc8a946b42fc")

.comdef IWbemDecoupledBasicEventProvider : public IWbemDecoupledRegistrar

    GetSink		proc :LONG, :ptr, :ptr
    GetService		proc :LONG, :ptr, :ptr
   .ends

endif

.enum WBEM_BATCH_TYPE {
    WBEM_FLAG_BATCH_IF_NEEDED	= 0,
    WBEM_FLAG_MUST_BATCH	= 0x1,
    WBEM_FLAG_MUST_NOT_BATCH	= 0x2
    }

ifndef __IWbemEventSink_INTERFACE_DEFINED__
define __IWbemEventSink_INTERFACE_DEFINED__

DEFINE_IIDX(IWbemEventSink, "3ae0080a-7e3a-4366-bf89-0feedc931659")

.comdef IWbemEventSink : public IWbemObjectSink

    SetSinkSecurity	proc :LONG, :ptr
    IsActive		proc
    GetRestrictedSink	proc :LONG
    SetBatchingParameters proc :LONG, :DWORD, :DWORD
   .ends

endif
endif
endif
