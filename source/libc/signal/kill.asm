; KILL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include signal.inc
include unistd.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

kill proc pid:pid_t, sig:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_kill(edi, esi) < 0 )
else
    .ifs ( sys_kill(pid, sig) < 0 )
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
kill endp

    end
