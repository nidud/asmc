; GETTIMEOFDAY.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include errno.inc
include sys/syscall.inc

.code

gettimeofday proc tv:ptr timeval, tz:ptr timezone

    .ifsd ( sys_gettimeofday( ldr(tv), ldr(tz) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

gettimeofday endp

    end
