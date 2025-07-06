; _ISATTY.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_isatty proc handle:SINT

    mov cx,handle

    .ifs ( cx < 0 || cx >= _nfile )

        mov errno,EINVAL
        .return( 0 )
    .endif

    xchg cx,bx
    mov al,_osfile[bx]
    mov bx,cx
    .if ( al & FDEV )
        mov ax,1
    .else
        xor ax,ax
    .endif
    ret

_isatty endp

    end
