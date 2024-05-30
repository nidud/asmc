; DUP2.ASM--
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

_dup2 proc oldfd:int_t, newfd:int_t
ifdef __UNIX__
ifdef _WIN64
    .ifsd ( sys_dup2(edi, esi) < 0 )
else
    .ifs ( sys_dup2(oldfd, newfd) < 0 )
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
_dup2 endp

    end
