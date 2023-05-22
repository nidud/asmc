; _FILBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume rsi:LPFILE

_filbuf proc uses rsi rdi fp:LPFILE

    ldr rsi,fp

    mov edi,[rsi]._flag
    xor eax,eax
    dec rax

    .if ( !(edi & _IOREAD or _IOWRT or _IORW) || edi & _IOSTRG )
        .return
    .endif
    .if ( edi & _IOWRT )

        or [rsi]._flag,_IOERR
       .return
    .endif

    or  edi,_IOREAD
    mov [rsi]._flag,edi

    .if ( !( edi & _IOMYBUF or _IONBF or _IOYOURBUF ) )

        _getbuf(rsi)
        mov edi,[rsi]._flag
    .else
        mov rax,[rsi]._base
        mov [rsi]._ptr,rax
    .endif

    _read([rsi]._file, [rsi]._base, [rsi]._bufsiz)
    mov [rsi]._cnt,eax

    .ifs ( eax < 1 )
        .if ( eax )
            mov eax,_IOERR
        .else
            mov eax,_IOEOF
        .endif
        or  [rsi]._flag,eax
        xor eax,eax
        mov [rsi]._cnt,eax
        dec rax
       .return
    .endif

    .if ( !( edi & _IOWRT or _IORW ) )

        lea rcx,_osfile
        mov eax,[rsi]._file
        mov al,[rcx+rax]
        and al,FTEXT or FEOFLAG

        .if ( al == FTEXT or FEOFLAG )

            or [rsi]._flag,_IOCTRLZ
        .endif
    .endif

    mov eax,[rsi]._bufsiz
    .if ( eax == _MINIOBUF && edi & _IOMYBUF && !( edi & _IOSETVBUF ) )

        mov [rsi]._bufsiz,_INTIOBUF
    .endif

    dec [rsi]._cnt
    inc [rsi]._ptr
    mov rcx,[rsi]._ptr
    movzx eax,byte ptr [rcx-1]
    ret

_filbuf endp

    end
