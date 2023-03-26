; _SCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputsA proc uses rsi rdi x:BYTE, y:BYTE, string:LPSTR

    .for ( edi = 0, rsi = string : byte ptr [rsi] : rsi++, x++, edi++ )

        movzx ecx,byte ptr [rsi]
        _scputc(x, y, 1, cx)
    .endf
    .return( edi )

_scputsA endp

    end
