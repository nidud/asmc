; KILL.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include signal.inc
include unistd.inc
include errno.inc
include sys/syscall.inc

.code

kill proc pid:pid_t, sig:int_t

    .ifs ( sys_kill( ldr(pid), ldr(sig) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

kill endp

    end
