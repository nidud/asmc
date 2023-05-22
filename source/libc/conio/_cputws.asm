; _CPUTWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include wchar.inc

    .code

_cputws proc uses rbx string:LPWSTR

    .for ( rbx = string : : rbx+=2 )

        movzx ecx,wchar_t ptr [rbx]
        .break .if ( ecx == 0 )
        .break .if ( _putwch( cx ) == WEOF )
    .endf
    ret

_cputws endp

    end
