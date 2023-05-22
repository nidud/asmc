; _CPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_cputs proc uses rbx string:string_t

    .for ( rbx = string : byte ptr [rbx] : rbx++ )

        movzx ecx,char_t ptr [rbx]
        .if ( _putch( ecx ) == WEOF )
            .return
        .endif
    .endf
    .return( 0 )

_cputs endp

    end
