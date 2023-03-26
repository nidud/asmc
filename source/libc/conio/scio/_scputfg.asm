; SCPUTFG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputfg proc x:BYTE, y:BYTE, l:BYTE, a:BYTE

    .for ( : l : l--, x++ )

        _scgeta( x, y )

        and eax,0xF0
        or  al,a

        _scputa( x, y, 1, ax )
    .endf
    ret

_scputfg endp

    end
