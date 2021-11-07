ifndef _ROBUFFER_H
define _ROBUFFER_H

ifdef _CONTRACT_GEN
include nt.inc
include ntrtl.inc
include nturtl.inc
endif

include apiset.inc
include apisetcconv.inc
include objidl.inc

ifndef _APISET_ROBUFFER_VER
ifdef _APISET_MINCORE_VERSION
if _APISET_MINCORE_VERSION GE 0x0100
define _APISET_ROBUFFER_VER 0x0100
endif
endif
endif

RoGetBufferMarshaler proto WINAPI \
       bufferMarshaler: ptr IMarshal

endif
