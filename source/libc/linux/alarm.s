; ALARM.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

alarm proc seconds:uint_t

    .ifsd ( sys_alarm( ldr(seconds) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

alarm endp

    end
