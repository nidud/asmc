; CLOCK_SETTIME.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include time.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

clock_settime proc which_clock:int_t, tp:ptr timespec
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_clock_settime(edi, rsi) < 0 )
else
    .ifs ( sys_clock_settime(which_clock, tp) < 0 )
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
clock_settime endp

    end
