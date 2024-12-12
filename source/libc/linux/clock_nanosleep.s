; CLOCK_NANOSLEEP.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include sys/syscall.inc

.code

clock_nanosleep proc which_clock:int_t, flags:int_t, req:ptr timespec, rem:ptr timespec

    .ifsd ( sys_clock_nanosleep( ldr(which_clock), ldr(flags), ldr(req), ldr(rem) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

clock_nanosleep endp

    end
