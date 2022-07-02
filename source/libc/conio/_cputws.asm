; _CPUTWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include wchar.inc

    .code

_cputws proc uses rsi string:LPWSTR

ifndef _WIN64
    mov rcx,string
endif

    .for ( rsi = rcx : : rsi += 2 )

        movzx eax,WORD PTR [rsi]

        .break .if ( eax == 0 )
        .break .if ( _putwch_nolock( eax ) == WEOF )
    .endf
    ret

_cputws endp

    end
