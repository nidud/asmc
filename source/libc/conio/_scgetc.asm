; _SCGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_scgetc proc x:BYTE, y:BYTE

    _scgetw(x, y)
    and eax,0xFFFF
    ret

_scgetc endp

    end
