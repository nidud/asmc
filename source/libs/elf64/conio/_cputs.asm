; _CPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_cputs proc uses rbx string:string_t

    .for ( rbx = string : byte ptr [rbx] : rbx++ )

        movzx edi,char_t ptr [rbx]
        .if ( _putch( edi ) == WEOF )
            .return
        .endif
    .endf
    .return( 0 )

_cputs endp

    end
