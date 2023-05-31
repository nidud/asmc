; _SCPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_scputw proc uses rdi x:BYTE, y:BYTE, l:BYTE, ci:CHAR_INFO

    _scgetp(x, y, l)
    mov eax,ci
    mov rdi,rcx
    movzx ecx,dl

    .if ( eax & 0xFFFF0000 )
        rep stosd
    .else
        .for ( : ecx : ecx--, rdi+=4 )

            mov [rdi],ax
        .endf
    .endif
    _cendpaint()
    ret

_scputw endp

    end
