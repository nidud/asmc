; _ACCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

.code

_access proc uses rbx file:LPSTR, mode:UINT

    ldr rcx,file
    ldr ebx,mode
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov eax,-1
else

    .ifd ( getfattr( rcx ) != -1 )

        .if ( ebx == 2 && eax & _A_RDONLY )
            mov eax,-1
        .else
            xor eax,eax
        .endif
    .endif
endif
    ret

_access endp

    end