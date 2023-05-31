; _SCPUTFG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_scputfg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    _scgetp(x, y, l)
    mov dh,a
    .for ( : dl : dl--, rcx+=4 )

        mov al,[rcx+2]
        and eax,0xF0
        or  al,dh
        mov [rcx+2],ax
    .endf
    _cendpaint()
    ret

_scputfg endp

    end
