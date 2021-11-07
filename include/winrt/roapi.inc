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

ifndef _APISET_ROAPI_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION ge 0x0100
define _APISET_ROAPI_VER 0x0100
endif
endif
endif

.enum RO_INIT_TYPE {
    RO_INIT_SINGLETHREADED = 0,
    RO_INIT_MULTITHREADED  = 1,
    }

RO_REGISTRATION_COOKIE typedef ptr

CALLBACK(PFNGETACTIVATIONFACTORY, :HSTRING, :ptr ptr IActivationFactory)

.pragma comment(lib, combase, "api-ms-win-core-winrt-l1-1-0")

RoInitialize proto WINAPI \
                  : RO_INIT_TYPE

RoUninitialize proto WINAPI

RoActivateInstance proto WINAPI \
                  : HSTRING,
                  : ptr ptr IInspectable

RoRegisterActivationFactories proto WINAPI \
                  : ptr HSTRING,
                  : ptr PFNGETACTIVATIONFACTORY,
                  : UINT32,
                  : ptr RO_REGISTRATION_COOKIE

RoRevokeActivationFactories proto WINAPI \
                  : RO_REGISTRATION_COOKIE

RoGetActivationFactory proto WINAPI \
                  : HSTRING,
                  : REFIID,
                  : ptr ptr

RoRegisterForApartmentShutdown proto WINAPI \
    callbackObject: ptr IApartmentShutdown,
apartmentIdentifier: UINT64,
         regCookie: ptr APARTMENT_SHUTDOWN_REGISTRATION_COOKIE

RoUnregisterForApartmentShutdown proto WINAPI \
         regCookie: APARTMENT_SHUTDOWN_REGISTRATION_COOKIE


RoGetApartmentIdentifier proto WINAPI \
apartmentIdentifier: ptr UINT64

endif
