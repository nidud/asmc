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

RoGetBufferMarshaler proto WINAPI :ptr ptr

endif

