; _RCPUTSW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputsW proc uses rsi rdi rc:TRECT, p:PCHAR_INFO, x:BYTE, y:BYTE, attrib:WORD, string:LPWSTR

    .new pos:TRECT = { x, y, 1, 1 }
    .for ( edi = 0, rsi = string : wchar_t ptr [rsi] : rsi += 2, pos.x++, edi++ )

        movzx ecx,wchar_t ptr [rsi]
        _rcputc(rc, pos, p, cx)
        .if ( attrib )
            _rcputa(rc, pos, p, attrib)
        .endif
    .endf
    .return( edi )

_rcputsW endp

    end
