; _FTBUF.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume bx:LPFILE

_ftbuf proc uses bx flag:int_t, fp:LPFILE

    mov cx,flag
    lesl bx,fp

    mov dx,esl[bx]._flag
    .if ( cx && dx & _IOFLRTN )

        fflush( ldr(bx) )

        lesl bx,fp
        and esl[bx]._flag,not (_IOYOURBUF or _IOFLRTN)
        xor ax,ax
        mov word ptr esl[bx]._ptr,ax
        mov word ptr esl[bx]._base,ax
        mov esl[bx]._bufsiz,ax
    .endif
    ret

_ftbuf endp

    end
