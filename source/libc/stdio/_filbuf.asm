; _FILBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume rbx:LPFILE

_filbuf proc uses rbx fp:LPFILE

    ldr rbx,fp
    mov edx,[rbx]._flag
    xor eax,eax
    dec rax

    .if ( !( edx & _IOREAD or _IOWRT or _IORW ) || edx & _IOSTRG )
        .return
    .endif
    .if ( edx & _IOWRT )
        or [rbx]._flag,_IOERR
       .return
    .endif
    or  edx,_IOREAD
    mov [rbx]._flag,edx

    .if ( !( edx & _IOMYBUF or _IONBF or _IOYOURBUF ) )
        _getbuf(rbx)
    .else
        mov [rbx]._ptr,[rbx]._base
    .endif
    _read([rbx]._file, [rbx]._base, [rbx]._bufsiz)
    mov [rbx]._cnt,eax

    .ifs ( eax < 1 )
        .if ( eax )
            mov eax,_IOERR
        .else
            mov eax,_IOEOF
        .endif
        or  [rbx]._flag,eax
        xor eax,eax
        mov [rbx]._cnt,eax
        dec rax
       .return
    .endif

    mov edx,[rbx]._flag
    .if ( !( edx & _IOWRT or _IORW ) )

        mov al,_osfile([rbx]._file)
        and al,FTEXT or FEOFLAG
        .if ( al == FTEXT or FEOFLAG )
            or [rbx]._flag,_IOCTRLZ
        .endif
    .endif

    mov eax,[rbx]._bufsiz
    .if ( eax == _MINIOBUF && edx & _IOMYBUF && !( edx & _IOSETVBUF ) )

        mov [rbx]._bufsiz,_INTIOBUF
    .endif

    dec [rbx]._cnt
    inc [rbx]._ptr
    mov rcx,[rbx]._ptr
    movzx eax,byte ptr [rcx-1]
    ret

_filbuf endp

    end
