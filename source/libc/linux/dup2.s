; DUP2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

_dup2 proc oldfd:int_t, newfd:int_t

    .ifsd ( sys_dup2(ldr(oldfd), ldr(newfd)) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

_dup2 endp

    end
