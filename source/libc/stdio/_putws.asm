; _PUTWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include wchar.inc

    .code

_putws proc uses rbx string:LPWSTR

   .new retval:int_t = 0

    ldr rbx,string
    .for ( : word ptr [rbx] : rbx += 2, retval++ )

        movzx ecx,word ptr [rbx]
        .if ( _putwch( cx ) == WEOF )

           .return
        .endif
    .endf
    .return( retval )

_putws endp

    end
