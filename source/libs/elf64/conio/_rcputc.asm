; _RCPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_rcputc proc w:TRECT, _rc:TRECT, p:PCHAR_INFO, c:wchar_t

    .new rc:TRECT = _rc
     shr edi,24

    .for ( : rc.row : rc.row--, rc.y++ )

        mov     eax,edi
        mul     rc.y
        movzx   esi,rc.x
        add     esi,eax
        shl     esi,2
        add     rsi,p

        .for ( r8b = 0 : r8b < rc.col : r8b++, rsi += 4 )

            mov [rsi],c
        .endf
    .endf
    ret

_rcputc endp

    end
