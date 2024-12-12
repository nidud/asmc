; PIPE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include unistd.inc
include sys/syscall.inc

.code

pipe proc pfd:ptr int_t

    .ifsd ( sys_pipe( ldr(pfd) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

pipe endp

    end
