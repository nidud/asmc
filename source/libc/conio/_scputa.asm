; _SCPUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputa proc x:BYTE, y:BYTE, l:BYTE, a:WORD

    _scgetp(x, y, l)
    mov ax,a
    .for ( : dl : dl--, rcx+=4 )

        mov [rcx+2],ax
    .endf
    _cendpaint()
    ret

_scputa endp

    end
