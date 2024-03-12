; _TACCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include tchar.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

_taccess proc uses rbx file:LPTSTR, mode:SINT

    ldr rcx,file
    ldr ebx,mode

ifdef __UNIX__

    .ifsd ( sys_access(rcx, ebx) < 0 )

        neg eax
        _set_errno( eax )
        mov eax,-1
    .endif
else

    .ifd ( _tgetfattr( rcx ) != -1 )

        .if ( ebx == 2 && eax & _A_RDONLY )
            mov eax,-1
        .else
            xor eax,eax
        .endif
    .endif
endif
    ret

_taccess endp

    end