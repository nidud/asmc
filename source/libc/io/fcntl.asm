; FCNTL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include fcntl.inc
include sys/syscall.inc

ifdef _WIN64
option win64:noauto ; skip the vararg stack
endif

.code

fcntl proc fd:int_t, cmd:int_t, argptr:vararg
ifdef __UNIX__
ifdef _WIN64
    .ifs ( sys_fcntl(edi, esi, edx) < 0 )
else
    lea eax,argptr
    mov eax,[eax]
    .ifs ( sys_fcntl(fd, cmd, eax) < 0 )
endif
        neg eax
        _set_errno( eax )
    .endif
endif
    ret

fcntl endp

    end
