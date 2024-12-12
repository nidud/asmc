; CLOCK_GETTIME.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include time.inc
include sys/syscall.inc

.code

clock_gettime proc which_clock:int_t, tp:ptr timespec

    .ifsd ( sys_clock_gettime( ldr(which_clock), ldr(tp) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

clock_gettime endp

    end
