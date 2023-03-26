; _SCPUTBG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputbg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    .for ( a <<= 4 : l : l--, x++ )

        _scgeta(x, y)

        and eax,0x0F
        or  al,a

        _scputa( x, y, 1, ax )
    .endf
    ret

_scputbg endp

    end
