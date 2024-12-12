; FSYNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include unistd.inc
include errno.inc
include sys/syscall.inc

.code

fsync proc fd:int_t

    .ifsd ( sys_fsync( ldr(fd) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

fsync endp

    end
