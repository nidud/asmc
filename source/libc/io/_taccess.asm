; _TACCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include tchar.inc

.code

_taccess proc uses rbx file:LPTSTR, mode:SINT

    ldr rcx,file
    ldr ebx,mode
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov eax,-1
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