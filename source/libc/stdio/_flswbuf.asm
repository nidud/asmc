; _FLSWBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include winbase.inc

    .code

    assume rbx:LPFILE

_flswbuf proc uses rbx char:int_t, fp:LPFILE

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
    mov [rbx]._cnt,0

    .if ( eax & _IOMYBUF or _IOYOURBUF )

        mov rax,[rbx]._base
        mov rdx,[rbx]._ptr
        sub rdx,rax
        add rax,2
        mov [rbx]._ptr,rax
        mov eax,[rbx]._bufsiz
        sub eax,2
        mov [rbx]._cnt,eax
        mov charcount,edx

        .ifs ( edx > 0 )
            mov written,_write( [rbx]._file, [rbx]._base, edx )
        .else

            lea rdx,_osfile
            mov ecx,[rbx]._file
            .if ( byte ptr [rcx+rdx] & FAPPEND )

                .if ( _lseeki64( ecx, 0, SEEK_END ) == -1 )

                    or [rbx]._flag,_IOERR
                   .return
                .endif
            .endif
        .endif
        mov edx,char
        mov rcx,[rbx]._base
        mov [rcx],dx
    .else
        mov charcount,2
        mov written,_write( [rbx]._file, &char, 2 )
    .endif
    mov eax,written
    .if ( eax != charcount )
        or [rbx]._flag,_IOERR
        or rax,-1
    .else
        movzx eax,word ptr char
    .endif
    ret

_flswbuf endp

    end
