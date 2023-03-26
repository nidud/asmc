; _PUTWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include wchar.inc

    .code

_putws proc uses rsi rdi string:LPWSTR

ifndef _WIN64
    mov ecx,string
endif
    .for ( rsi = rcx, edi = 0 : word ptr [rsi] : rsi += 2, edi++ )

        movzx ecx,word ptr [rsi]
        .if ( _putwch( cx ) == WEOF )

            movsx edi,ax
           .break
        .endif
    .endf
    .return( edi )

_putws endp

    end
