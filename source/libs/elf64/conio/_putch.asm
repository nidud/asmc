; _PUTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

    .code

_putch proc c:int_t

   .new cc:int_t = c

    mov eax,_confh
    .if ( eax != -1 )
        ;
        ; write character to console file handle
        ;
        .if write( _confh, &cc, 1 )

            mov eax,cc
        .else
            mov eax,WEOF
        .endif
    .endif
    ret

_putch endp

    end
