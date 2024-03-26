; TIMES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
ifdef __UNIX__
include errno.inc
include sys/syscall.inc
else
include winbase.inc
endif

.code

times proc pt:ptr tms

ifdef __UNIX__

    ldr rcx,pt

    .ifsd ( sys_times(rcx) < 0 )

        neg eax
        _set_errno( eax )
    .endif
else
    GetTickCount()
endif
    ret

times endp

    end
