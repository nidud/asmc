; _CLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc

    .code

_close proc uses bx handle:int_t

    mov bx,handle
    .if ( bx < 3 || bx >= _nfile )

        mov errno,EBADF
        mov _doserrno,0
       .return( 0 )
    .endif
    mov _osfile[bx],0
    mov ah,0x3E
    int 0x21
    .ifc
        _dosmaperr( ax )
    .else
        xor ax,ax
    .endif
    ret

_close endp

    end
