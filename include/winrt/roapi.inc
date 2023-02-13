ifndef __ROAPI_H_
define __ROAPI_H_

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif
include apiset.inc
include apisetcconv.inc
include wtypesbase.inc
include inspectable.inc
include combaseapi.inc
include activation.inc
include hstring.inc

.enum RO_INIT_TYPE {
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
    RO_INIT_SINGLETHREADED     = 0,
endif
    RO_INIT_MULTITHREADED      = 1,
    }

RO_REGISTRATION_COOKIE  typedef ptr _RO_REGISTRATION_COOKIE

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

.pragma comment(lib, combase, "api-ms-win-core-winrt-l1-1-0")

RoInitialize proto WINAPI :RO_INIT_TYPE
RoUninitialize proto WINAPI
RoActivateInstance proto WINAPI :HSTRING, :ptr ptr
RoRegisterActivationFactories proto WINAPI :ptr, :ptr, :UINT32, :ptr
RoRevokeActivationFactories proto WINAPI :RO_REGISTRATION_COOKIE
RoGetActivationFactory proto WINAPI :HSTRING, :REFIID, :ptr ptr

DECLARE_HANDLE(APARTMENT_SHUTDOWN_REGISTRATION_COOKIE)

RoRegisterForApartmentShutdown proto WINAPI :ptr, :UINT64, :ptr
RoUnregisterForApartmentShutdown proto WINAPI :APARTMENT_SHUTDOWN_REGISTRATION_COOKIE
RoGetApartmentIdentifier proto WINAPI :ptr

endif

endif
