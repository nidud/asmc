; _TFLSBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include malloc.inc
include errno.inc
include tchar.inc

    .code

    assume bx:LPFILE

_tflsbuf proc uses bx char:int_t, fp:LPFILE

   .new charcount:int_t = 0
   .new written:int_t = 0

    lesl bx,fp

    xor ax,ax
    mov dx,esl[bx]._flag

    .if !( dx & _IOWRT or _IORW )

        or esl[bx]._flag,_IOERR
       .return _set_errno(EBADF)

    .elseif ( dx & _IOSTRG )

        or esl[bx]._flag,_IOERR
       .return _set_errno(ERANGE)
    .endif

    .if ( dx & _IOREAD )

        mov esl[bx]._cnt,ax
        .if ( !( dx & _IOEOF ) )

            dec ax
            or esl[bx]._flag,_IOERR
           .return
        .endif

        mov esl[bx]._ptr,esl[bx]._base
        and dx,not _IOREAD
    .endif

    or  dx,_IOWRT
    and dx,not _IOEOF
    mov esl[bx]._flag,dx
    mov esl[bx]._cnt,0

    .if ( !( dx & _IOMYBUF or _IONBF or _IOYOURBUF ) )

        _isatty( esl[bx]._file )
        .if ( !( ( bx == word ptr stdout || bx == word ptr stderr ) && ax ) )
            _getbuf( rbx )
        .endif
    .endif

    .if ( esl[bx]._flag & _IOMYBUF or _IOYOURBUF )

        mov ax,word ptr esl[bx]._base
        mov dx,word ptr esl[bx]._ptr
        sub dx,ax
        add ax,TCHAR
        mov word ptr esl[bx]._ptr,ax
        mov ax,esl[bx]._bufsiz
        sub ax,TCHAR
        mov esl[bx]._cnt,ax
        mov charcount,dx
        mov cx,bx
        mov bx,esl[bx]._file
        mov al,_osfile[bx]
        mov bx,cx

        .ifs ( dx > 0 )

            mov written,_write( esl[bx]._file, esl[bx]._base, dx )

        .elseif ( al & FAPPEND )

            .if ( _lseek( esl[bx]._file, 0, SEEK_END ) == -1 )

                or esl[bx]._flag,_IOERR
               .return
            .endif
        .endif

        mov ax,char
        lesl bx,esl[bx]._base
        mov esl[bx],al

    .else

        mov charcount,TCHAR
        mov written,_write( esl[bx]._file, &char, TCHAR )
    .endif

    xor ax,ax
    mov al,char_t ptr char
    mov cx,written
    .if ( cx != charcount )

        lesl bx,fp
        or esl[bx]._flag,_IOERR
        or ax,-1
    .endif
    ret

_tflsbuf endp

    end
