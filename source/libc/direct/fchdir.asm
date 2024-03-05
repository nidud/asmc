; FCHDIR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif
    .code

fchdir proc fd:int_t
ifdef __UNIX__
    ldr ecx,fd
    .ifsd ( sys_fchdir(ecx) < 0 )

        neg eax
        _set_errno(eax)
        .return(-1)
    .endif
endif
    ret

fchdir endp

    end
