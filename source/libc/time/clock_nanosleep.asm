; CLOCK_NANOSLEEP.ASM--
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

clock_nanosleep proc which_clock:int_t, flags:int_t, req:ptr timespec, rem:ptr timespec
ifdef __UNIX__
ifdef _WIN64
    sys_clock_nanosleep(edi, esi, rdx, rcx)
else
    sys_clock_nanosleep(which_clock, flags, req, rem)
endif
    .ifsd ( eax < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

clock_nanosleep endp

    end
