ifndef __ROREGISTRATIONAPI_H_
define __ROREGISTRATIONAPI_H_

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif
include apiset.inc
include apisetcconv.inc
include wtypesbase.inc
include hstring.inc
include activationregistration.inc
include sdkddkver.inc

if (NTDDI_VERSION GE NTDDI_WIN8)

ifndef _APISET_RO_REGISTRATION_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0100
define _APISET_RO_REGISTRATION_VER 0x0100l
endif
endif
endif

PActivatableClassRegistration typedef ptr ABI::Windows::Foundation::IActivatableClassRegistration

RoGetActivatableClassRegistration proto WINAPI \
    activatableClassId: HSTRING,
 activatableClassRegistration: ptr PActivatableClassRegistration

RoGetServerActivatableClasses proto WINAPI \
            serverName: HSTRING,
   activatableClassIds: ptr HSTRING,
                 count: ptr DWORD

Windows::Foundation::GetActivatableClassRegistration proto activatableClassId:HSTRING,
        activatableClassRegistration: ptr PActivatableClassRegistration {
    RoGetActivatableClassRegistration(activatableClassId, activatableClassRegistration)
    }

Windows::Foundation::GetServerActivatableClasses proto serverName:HSTRING,
        activatableClassIds:ptr HSTRING, count:ptr DWORD {
    RoGetServerActivatableClasses(serverName, activatableClassIds, count)
    }

endif
endif
