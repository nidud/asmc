; FCHDIR.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include sys/syscall.inc

    .code

fchdir proc fd:int_t

    .ifsd ( sys_fchdir( ldr(fd) ) < 0 )

        neg eax
        _set_errno(eax)
    .endif
    ret

fchdir endp

    end
