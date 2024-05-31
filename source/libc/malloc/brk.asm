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
ifdef _WIN64
    .ifsd ( sys_brk(rdi) < 0 )
else
    .ifs ( sys_brk(p) < 0 )
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
brk endp

    end
