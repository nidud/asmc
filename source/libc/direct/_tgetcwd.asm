; _TGETCWD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
ifdef __UNIX__
include errno.inc
include sys/syscall.inc
endif
include tchar.inc

    .code

_tgetcwd proc uses rbx buffer:LPTSTR, maxlen:SINT

    ldr rbx,buffer
    ldr edx,maxlen
ifdef __UNIX__
    .ifsd ( sys_getcwd(rbx, edx) < 0 )

        neg eax
        _set_errno(eax)
        xor ebx,ebx
    .endif
    mov rax,rbx
else
    _tgetdcwd( 0, rbx, edx )
endif
    ret

_tgetcwd endp

    end
