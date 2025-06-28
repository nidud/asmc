; STBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include io.inc
include malloc.inc

    .data
    _stdbuf string_t 2 dup(0) ; buffer for stdout and stderr

    .code

    assume bx:LPFILE

_stbuf proc uses si bx fp:LPFILE

   .new p:string_t

    lesl bx,fp

    .if _isatty( esl[bx]._file )

        xor ax,ax
        mov si,offset _stdbuf
        .if ( bx != word ptr stdout )
            .if ( bx != word ptr stderr )
                .return
            .endif
            add si,string_t
        .endif

        mov cx,esl[bx]._flag
        and cx,_IOMYBUF or _IONBF or _IOYOURBUF
        .ifnz
            .return
        .endif
        or  cx,_IOWRT or _IOYOURBUF or _IOFLRTN
        mov esl[bx]._flag,cx

        mov ax,[si]
        movl dx,ds
        .if ( ax == NULL )

            malloc( _INTIOBUF )
            mov [si],ax
            movl [si+2],dx
            lesl bx,fp
        .endif

        mov cx,_INTIOBUF
        .if ( ax == NULL )

            lea ax,esl[bx]._charbuf
            mov cx,2
        .endif
        movl word ptr esl[bx+2]._ptr,dx
        movl word ptr esl[bx+2]._base,dx
        mov word ptr esl[bx]._ptr,ax
        mov word ptr esl[bx]._base,ax
        mov esl[bx]._bufsiz,cx
        mov ax,1
    .endif
    ret

_stbuf endp

    end
