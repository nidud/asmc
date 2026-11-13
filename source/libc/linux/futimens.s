; FUTIMENS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include time.inc
include errno.inc
include fcntl.inc
include sys/stat.inc
include sys/syscall.inc

.code
 futimens proc fd:int_t, ts:ptr timespec
    .ifsd ( sys_utimensat( ldr(fd), NULL, ldr(ts), 0 ) < 0 )
        neg eax
        _set_errno( eax )
    .endif
    ret
    endp

    end
