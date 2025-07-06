; FFLUSH.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc

    .code

    assume bx:LPFILE

fflush proc uses bx fp:LPFILE

   .new size:uint_t
   .new retval:int_t = 0

    lesl bx,fp
    mov ax,esl[bx]._flag

    and ax,_IOREAD or _IOWRT
    .if ( ax == _IOWRT && esl[bx]._flag & _IOMYBUF or _IOYOURBUF )

        mov ax,word ptr esl[bx]._ptr
        sub ax,word ptr esl[bx]._base
        mov size,ax
        .ifg

            _write( esl[bx]._file, esl[bx]._base, ax )
            lesl bx,fp
            .ifd ( ax == size )
                .if ( esl[bx]._flag & _IORW )
                    and esl[bx]._flag,not _IOWRT
                .endif
            .else
                or esl[bx]._flag,_IOERR
                dec retval
            .endif
        .endif
    .endif
    mov esl[bx]._ptr,esl[bx]._base
    mov esl[bx]._cnt,0
   .return( retval )

fflush endp

    end
