; FCNTL.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include fcntl.inc
include sys/syscall.inc

.code

fcntl proc fd:int_t, cmd:int_t, arg:size_t

    .ifsd ( sys_fcntl( ldr(fd), ldr(cmd), ldr(arg) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

fcntl endp

    end
