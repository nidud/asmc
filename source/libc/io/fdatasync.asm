; FDATASYNC.ASM--
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

fdatasync proc fd:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_fdatasync(edi) < 0 )
else
    .ifs ( sys_fdatasync(fd) < 0 )
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
fdatasync endp

    end
