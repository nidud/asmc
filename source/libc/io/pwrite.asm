; PWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include unistd.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

pwrite proc fd:int_t, buf:ptr, count:size_t, off:off_t
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_pwrite64(edi, rsi, rdx, rcx) < 0 )
else
    .ifs ( sys_pwrite64(fd, buf, count, dword ptr off, dword ptr off[4]) < 0 )
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
pwrite endp

    end
