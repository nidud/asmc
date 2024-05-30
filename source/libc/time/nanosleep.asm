; NANOSLEEP.ASM--
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

nanosleep proc req:ptr timespec, rem:ptr timespec
ifdef __UNIX__
ifdef _WIN64
    sys_nanosleep(rdi, rsi)
else
    sys_nanosleep(req, rem)
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

nanosleep endp

    end
