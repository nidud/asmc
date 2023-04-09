; _RCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputsA proc uses rsi rdi rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, string:LPSTR

    .new pos:TRECT = { x, y, 1, 1 }
    .for ( edi = 0, rsi = string : char_t ptr [rsi] : rsi++, pos.x++, edi++ )

        movzx ecx,char_t ptr [rsi]
        _rcputc(rc, pos, p, cx)
        .if ( attrib )
            _rcputa(rc, pos, p, attrib)
        .endif
    .endf
    .return( edi )

_rcputsA endp

    end
