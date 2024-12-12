; WRITEV.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include unistd.inc
include sys/uio.inc
include sys/syscall.inc

.code

writev proc fd:int_t, iov:ptr iovec, iovcnt:int_t

    .ifsd ( sys_writev(ldr(fd), ldr(iov), ldr(iovcnt)) < 0 )

        neg eax
        _set_errno( eax )
    .endif
    ret

writev endp

    end
