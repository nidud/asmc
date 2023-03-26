; _SCPUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputw proc x:BYTE, y:BYTE, l:BYTE, ci:CHAR_INFO

    .if ( ci.Attributes )
        _scputa( x, y, l, ci.Attributes )
    .endif
    _scputc( x, y, l, ci.Char.UnicodeChar )
    ret

_scputw endp

    end
