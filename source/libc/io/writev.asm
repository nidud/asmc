; WRITEV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include unistd.inc
ifdef __UNIX__
include sys/uio.inc
include sys/syscall.inc
endif

.code

writev proc fd:int_t, iov:ptr iovec, iovcnt:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_writev(edi, rsi, edx) < 0 )
else
    .ifs ( sys_writev(fd, iov, iovcnt) < 0 )
endif
        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret
writev endp

    end
