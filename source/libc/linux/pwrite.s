; PWRITE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include unistd.inc
include sys/syscall.inc

.code

pwrite proc fd:int_t, buf:ptr, count:size_t, off:off_t

ifdef _WIN64
    .ifs ( sys_pwrite64(edi, rsi, rdx, rcx) < 0 )
else
    .ifs ( sys_pwrite64(fd, buf, count, dword ptr off, dword ptr off[4]) < 0 )
endif
        neg eax
        _set_errno( eax )
    .endif
    ret

pwrite endp

    end
