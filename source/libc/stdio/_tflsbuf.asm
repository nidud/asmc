; _TFLSBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include winbase.inc
include tchar.inc

    .code

    assume rbx:LPFILE

_tflsbuf proc uses rbx char:int_t, fp:LPFILE

   .new charcount:int_t = 0
   .new written:int_t = 0

    ldr rbx,fp
    xor eax,eax
    mov edx,[rbx]._flag
    .if ( !( edx & _IOREAD or _IOWRT or _IORW ) || edx & _IOSTRG )

        or [rbx]._flag,_IOERR
        dec rax
       .return
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
            mov written,_write( [rbx]._file, [rbx]._base, edx )

        .elseif ( _osfile([rbx]._file) & FAPPEND )

            .if ( _lseeki64( ecx, 0, SEEK_END ) == -1 )

                or [rbx]._flag,_IOERR
               .return
            .endif
        .endif
        mov eax,char
        mov rcx,[rbx]._base
ifdef _UNICODE
        mov [rcx],ax
else
        mov [rcx],al
endif
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
