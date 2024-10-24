; CLOCK_SETTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include time.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

clock_settime proc which_clock:int_t, tp:ptr timespec

ifdef __UNIX__
    .ifsd ( sys_clock_settime( ldr(which_clock), ldr(tp) ) < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

clock_settime endp

    end
