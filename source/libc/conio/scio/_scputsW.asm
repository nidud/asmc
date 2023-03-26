; _SCPUTSW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputsW proc uses rsi rdi x:BYTE, y:BYTE, string:LPWSTR

    .for ( edi = 0, rsi = string : wchar_t ptr [rsi] : rsi += 2, x++, edi++ )

        movzx ecx,wchar_t ptr [rsi]
        _scputc(x, y, 1, cx)
    .endf
    .return( edi )

_scputsW endp

    end
