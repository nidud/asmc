; FORK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifdef __UNIX__
include unistd.inc
include sys/syscall.inc
endif
include errno.inc

.code

fork proc
ifdef __UNIX__
    .ifs ( sys_fork() < 0 )
        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

fork endp

    end
