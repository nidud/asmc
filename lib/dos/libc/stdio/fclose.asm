; FCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc

    .code

fclose proc uses bx fp:LPFILE

   .new retval:size_t

    ldr bx,fp
    mov ax,esl[bx]._iobuf._flag
    and ax,_IOREAD or _IOWRT or _IORW
    .ifz
        dec ax
       .return
    .endif
    mov retval,fflush( fp )
    _freebuf( fp )

    ldr bx,fp
    xor ax,ax
    mov esl[bx]._iobuf._flag,ax
    mov cx,esl[bx]._iobuf._file
    dec ax
    mov esl[bx]._iobuf._file,ax
    .if ( _close( cx ) == 0 )
        mov ax,retval
    .endif
    ret

fclose endp

    end
