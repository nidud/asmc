; _SCGETW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scgetw proc x:BYTE, y:BYTE

   .new ci:CHAR_INFO

    mov ci.Attributes,       _scgeta( x, y )
    mov ci.Char.UnicodeChar, _scgetc( x, y )

   .return( ci )

_scgetw endp

    end
