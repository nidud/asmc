; WAITPID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/wait.inc
include sys/syscall.inc
include errno.inc

.code

waitpid proc pid:pid_t, wstatus:ptr int_t, options:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_wait4(edi, rsi, edx, NULL) < 0 )
else
    .ifs ( sys_waitpid(pid, wstatus, options) < 0 )
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
waitpid endp

    end
