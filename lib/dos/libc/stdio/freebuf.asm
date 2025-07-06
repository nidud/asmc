; _FREEBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc

    .code

    assume bx:LPFILE

_freebuf proc uses bx fp:LPFILE

    lesl bx,fp

    mov ax,esl[bx]._flag
    .if ( ax & _IOREAD or _IOWRT or _IORW )

	.if ( ax & _IOMYBUF )

	    xor cx,cx
	    mov ax,word ptr esl[bx]._base
	    movl dx,word ptr esl[bx]._base[2]
	    mov word ptr esl[bx]._ptr,cx
	    mov word ptr esl[bx]._base,cx
	    mov esl[bx]._flag,cx
	    mov esl[bx]._bufsiz,cx
	    mov esl[bx]._cnt,cx
	    free( ldr(ax) )
	.endif
    .endif
    ret

_freebuf endp

    end
