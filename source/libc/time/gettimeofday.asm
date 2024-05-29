; GETTIMEOFDAY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include time.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

gettimeofday proc tv:ptr timeval, tz:ptr timezone
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_gettimeofday(rdi, rsi) < 0 )
else
    .ifs ( sys_gettimeofday(tv, tz) < 0 )
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
gettimeofday endp

    end
