; BRK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include errno.inc
include unistd.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

brk proc p:ptr

ifdef __UNIX__
    .ifsd ( sys_brk( ldr(p) ) < 0 )

        neg eax
else
        mov eax,ENOSYS
endif
        _set_errno( eax )
ifdef __UNIX__
    .endif
endif
    ret

brk endp

    end
