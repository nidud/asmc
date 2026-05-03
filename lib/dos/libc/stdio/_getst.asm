; _GETST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume bx:LPFILE

_getst proc uses bx

    ldr bx,stdin

    .for ( ax = 0, dx = 0 : dx < _nstream : dx++, bx+=FILE )

        .if ( !( esl[bx]._flag & _IOREAD or _IOWRT or _IORW ) )

            mov esl[bx]._cnt,ax
            mov esl[bx]._flag,ax
            mov word ptr esl[bx]._ptr,ax
            mov word ptr esl[bx]._base,ax
            dec ax
            mov esl[bx]._file,ax
            mov ax,bx
            movl dx,es
           .break
        .endif
    .endf
    ret

_getst endp

    end
