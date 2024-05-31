; FSYNC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include unistd.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

fsync proc fd:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_fsync(edi) < 0 )
else
    .ifs ( sys_fsync(fd) < 0 )
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
fsync endp

    end
