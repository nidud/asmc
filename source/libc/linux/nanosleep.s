; NANOSLEEP.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include sys/syscall.inc

.code

nanosleep proc req:ptr timespec, rem:ptr timespec

    .ifsd ( sys_nanosleep( ldr(req), ldr(rem) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

nanosleep endp

    end
