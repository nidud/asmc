; WAIT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/wait.inc
include sys/syscall.inc
include errno.inc

.code

wait4 proc pid:pid_t, stat_addr:ptr int_t, options:int_t, ru:ptr rusage
ifdef __UNIX__
    .ifsd ( sys_wait4(ldr(pid), ldr(stat_addr), ldr(options), ldr(ru)) < 0 )
        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

wait4 endp

    end
