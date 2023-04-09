; _FILBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include stdio.inc

    .code

    assume r12:ptr FILE

_filbuf proc uses rbx r12 r13 fp:ptr FILE

    mov r12,rdi
    mov ebx,[r12]._flag
    xor eax,eax
    dec rax

    .return .if ( !( ebx & _IOREAD or _IOWRT or _IORW ) || ebx & _IOSTRG )
    .if ( ebx & _IOWRT )
        or [r12]._flag,_IOERR
        .return
    .endif

    or  ebx,_IOREAD
    mov [r12]._flag,ebx

    .if ( !( ebx & _IOMYBUF or _IONBF or _IOYOURBUF ) )

        _getbuf(r12)
        mov ebx,[r12]._flag
    .else
        mov rax,[r12]._base
        mov [r12]._ptr,rax
    .endif

    _read([r12]._file, [r12]._base, [r12]._bufsiz)
    mov [r12]._cnt,eax

    .ifs ( eax < 1 )
        .if eax
            mov eax,_IOERR
        .else
            mov eax,_IOEOF
        .endif
        or  [r12]._flag,eax
        xor eax,eax
        mov [r12]._cnt,eax
        dec rax
       .return
    .endif

    .if ( !( ebx & _IOWRT or _IORW ) )

        lea rcx,_osfile
        mov eax,[r12]._file
        mov al,[rcx+rax]
        and al,FH_TEXT or FH_EOF
        .if ( al == FH_TEXT or FH_EOF )
            or [r12]._flag,_IOCTRLZ
        .endif
    .endif

    mov eax,[r12]._bufsiz
    .if ( eax == _MINIOBUF && ebx & _IOMYBUF && !( ebx & _IOSETVBUF ) )
        mov [r12]._bufsiz,_INTIOBUF
    .endif

    dec [r12]._cnt
    inc [r12]._ptr
    mov rcx,[r12]._ptr
    movzx eax,byte ptr [rcx-1]
    ret

_filbuf endp

    END
