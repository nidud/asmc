; _PUTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

    .code

_putch proc c:int_t

    mov eax,_confh
    .if ( eax != -1 )
        ;
        ; write character to console file handle
        ;
        .if write( _confh, &c, 1 )

            mov eax,c
        .else
            mov eax,WEOF
        .endif
    .endif
    ret

_putch endp

    end
