; _GETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    assume bx:LPFILE

_getbuf proc uses bx fp:LPFILE

    malloc( _INTIOBUF )
    ldr bx,fp
    .if ( ax )
        or  esl[bx]._flag,_IOMYBUF
        mov esl[bx]._bufsiz,_INTIOBUF
    .else
        or  esl[bx]._flag,_IONBF
        mov esl[bx]._bufsiz,int_t
        lea ax,esl[bx]._charbuf
    .endif
    mov word ptr esl[bx]._ptr,ax
    mov word ptr esl[bx]._base,ax
    movl word ptr esl[bx]._ptr[2],dx
    movl word ptr esl[bx]._base[2],dx
    mov esl[bx]._cnt,0
    ret

_getbuf endp

    end
