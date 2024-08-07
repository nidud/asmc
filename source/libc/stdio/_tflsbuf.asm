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

    assume rbx:LPFILE

_tflsbuf proc uses rbx char:int_t, fp:LPFILE

   .new charcount:int_t = 0
   .new written:int_t = 0

    ldr rbx,fp

    xor eax,eax
    mov edx,[rbx]._flag

    .if !( edx & _IOWRT or _IORW )

        or [rbx]._flag,_IOERR
       .return _set_errno(EBADF)

    .elseif ( edx & _IOSTRG )

        or [rbx]._flag,_IOERR
       .return _set_errno(ERANGE)
    .endif

    .if ( edx & _IOREAD )

        mov [rbx]._cnt,eax
        .if ( !( edx & _IOEOF ) )

            dec rax
            or [rbx]._flag,_IOERR
           .return
        .endif

        mov [rbx]._ptr,[rbx]._base
        and edx,not _IOREAD
    .endif

    or  edx,_IOWRT
    and edx,not _IOEOF
    mov [rbx]._flag,edx
    mov [rbx]._cnt,0

    .if ( !( edx & _IOMYBUF or _IONBF or _IOYOURBUF ) )

        _isatty( [rbx]._file )
        .if ( !( ( rbx == stdout || rbx == stderr ) && eax ) )
            _getbuf( rbx )
        .endif
    .endif

    mov eax,[rbx]._flag
    .if ( eax & _IOMYBUF or _IOYOURBUF )

        mov rax,[rbx]._base
        mov rdx,[rbx]._ptr
        sub rdx,rax
        add rax,TCHAR
        mov [rbx]._ptr,rax
        mov eax,[rbx]._bufsiz
        sub eax,TCHAR
        mov [rbx]._cnt,eax
        mov charcount,edx

        .ifs ( edx > 0 )

            .if ( [rbx]._flag & _IOMEMBUF )

                mov [rbx]._ptr,rdx
                .if ( realloc([rbx]._base, &[rax+TCHAR+_INTIOBUF]) == NULL )

                    dec rax
                    or [rbx]._flag,_IOERR
                   .return
                .endif
                mov [rbx]._base,rax
                add [rbx]._bufsiz,_INTIOBUF
                mov edx,[rbx]._bufsiz
                mov rcx,[rbx]._ptr
                sub edx,ecx
                sub edx,TCHAR
                mov [rbx]._cnt,edx
                lea rcx,[rax+rcx+TCHAR]
                mov [rbx]._ptr,rcx
                movzx eax,TCHAR ptr char
                mov [rcx-TCHAR],_tal
               .return

            .else

                mov written,_write( [rbx]._file, [rbx]._base, edx )
            .endif

        .elseif ( _osfile([rbx]._file) & FAPPEND )

            .if ( _lseeki64( [rbx]._file, 0, SEEK_END ) == -1 )

                or [rbx]._flag,_IOERR
               .return
            .endif
        .endif
        mov eax,char
        mov rcx,[rbx]._base
        mov [rcx],_tal
    .else
        mov charcount,TCHAR
        mov written,_write( [rbx]._file, &char, TCHAR )
    .endif
    mov eax,written
    .if ( eax != charcount )
        or [rbx]._flag,_IOERR
        or rax,-1
    .else
        movzx eax,TCHAR ptr char
    .endif
    ret

_tflsbuf endp

    end
