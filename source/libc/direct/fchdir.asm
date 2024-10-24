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

    .ifsd ( sys_fchdir(ldr(fd)) < 0 )

        neg eax
        _set_errno(eax)
    .endif
endif
    ret

fchdir endp

    end
