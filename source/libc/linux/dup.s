; DUP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

_dup proc fd:int_t

    .ifsd ( sys_dup(ldr(fd)) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

_dup endp

    end
