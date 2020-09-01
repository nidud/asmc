; _SCPUTBG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputbg proc frame x:int_t, y:int_t, l:int_t, a:uchar_t

    .for ( a <<= 4 : l : l--, x++ )

        _getxya(x, y)
        and al,0x0F
        or  al,a
        _scputa(x, y, 1, al)
    .endf
    ret

_scputbg endp

    end
