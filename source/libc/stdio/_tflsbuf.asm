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

    .if ( [rbx]._flag & _IOMYBUF or _IOYOURBUF )

        mov rax,[rbx]._base
        mov rdx,[rbx]._ptr
        sub rdx,rax
        add rax,tchar_t
        mov [rbx]._ptr,rax
        mov eax,[rbx]._bufsiz
        sub eax,tchar_t
        mov [rbx]._cnt,eax
        mov charcount,edx

        .ifs ( edx > 0 )
ifdef STDZIP
            .if ( [rbx]._flag & _IOMEMBUF )

                add eax,tchar_t
                lea ecx,[rax+rax]
                .if ( ecx < _HEAP_GROWSIZE )
                    mov ecx,_HEAP_GROWSIZE
                .elseif ( ecx > _HEAP_MAXREGSIZE_S )
                    lea ecx,[rax+_HEAP_GROWSIZE]
                .endif
                .if ( ecx < eax )
                    _set_errno( ENOMEM )
                    or [rbx]._flag,_IOERR
                   .return
                .endif
                mov [rbx]._bufsiz,ecx
                .if ( realloc([rbx]._base, rcx) == NULL )
                    dec rax
                    or [rbx]._flag,_IOERR
                   .return
                .endif
                mov [rbx]._base,rax
                mov edx,[rbx]._bufsiz
                mov ecx,charcount
                sub edx,ecx
                sub edx,tchar_t
                mov [rbx]._cnt,edx
                lea rcx,[rax+rcx+tchar_t]
                mov [rbx]._ptr,rcx
                movzx eax,tchar_t ptr char
                mov [rcx-tchar_t],_tal
               .return
            .endif

            .if ( [rbx]._flag & _IOCRC32 )

                _crc32( [rbx]._crc32, [rbx]._base, edx )
                mov [rbx]._crc32,eax
                mov edx,charcount
            .endif
endif
            mov written,_write( [rbx]._file, [rbx]._base, edx )

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

        mov charcount,tchar_t
        mov written,_write( [rbx]._file, &char, tchar_t )
    .endif

    movzx eax,tchar_t ptr char
    mov ecx,written
    .if ( ecx != charcount )

        or [rbx]._flag,_IOERR
        or rax,-1
    .endif
    ret

_tflsbuf endp

    end
