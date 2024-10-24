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
    .ifsd ( sys_gettimeofday( ldr(tv), ldr(tz) ) < 0 )

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
