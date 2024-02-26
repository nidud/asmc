; _TCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include wchar.inc
include tchar.inc

    .code

_cputts proc uses rbx string:LPTSTR

    .for ( rbx = string : : rbx+=TCHAR )

        movzx ecx,TCHAR ptr [rbx]
        .break .if ( ecx == 0 )
        .break .ifd ( _puttch( ecx ) == WEOF )
    .endf
    .return( 0 )

_cputts endp

    end
