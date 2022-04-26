; FCHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
include linux/kernel.inc

    .code

fchdir proc fd:int_t

    .ifsd ( sys_fchdir(fd) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
    ret

fchdir endp

    end
