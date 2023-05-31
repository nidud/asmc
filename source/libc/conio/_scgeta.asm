; _SCGETA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_scgeta proc x:BYTE, y:BYTE

    _scgetw(x, y)
    shr eax,16
    ret

_scgeta endp

    end
