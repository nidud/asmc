; SCPUTFG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputfg proc frame x:int_t, y:int_t, l:int_t, a:uchar_t

    .for ( : l : l--, x++ )

        _getxya(x, y)
        and al,0xF0
        or  al,a
        _scputa(x, y, 1, al)
    .endf
    ret

_scputfg endp

    end
