; GETPID.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include unistd.inc
include sys/syscall.inc
include errno.inc

.code

getpid proc

    .ifsd ( sys_getpid() < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

getpid endp

    end
