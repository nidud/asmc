include stdio.inc
include io.inc

    .code

    assume rsi:LPFILE

_filbuf proc uses rsi rdi fp:LPFILE

    mov rsi,rcx
    mov edi,[rsi]._flag
    mov rax,-1

    .repeat
        .break .if !(edi & _IOREAD or _IOWRT or _IORW) || edi & _IOSTRG
        .if edi & _IOWRT
            or [rsi]._flag,_IOERR
            .break
        .endif

        or  edi,_IOREAD
        mov [rsi]._flag,edi
        .if !(edi & _IOMYBUF or _IONBF or _IOYOURBUF)
            _getbuf(rsi)
            mov edi,[rsi]._flag
        .else
            mov rax,[rsi]._base
            mov [rsi]._ptr,rax
        .endif

        _read([rsi]._file, [rsi]._base, [rsi]._bufsiz)
        mov [rsi]._cnt,eax

        .ifs eax < 2
            .if eax
                mov eax,_IOERR
            .else
                mov eax,_IOEOF
            .endif
            or  [rsi]._flag,eax
            xor eax,eax
            mov [rsi]._cnt,eax
            dec rax
            .break
        .endif

        .if !(edi & _IOWRT or _IORW)
            lea rax,_osfile
            add eax,[rsi]._file
            mov al,[rax]
            and al,FH_TEXT or FH_EOF
            .if al == FH_TEXT or FH_EOF
                or [rsi]._flag,_IOCTRLZ
            .endif
        .endif

        mov eax,[rsi]._bufsiz
        .if eax == _MINIOBUF && edi & _IOMYBUF && !(edi & _IOSETVBUF)
            mov [rsi]._bufsiz,_INTIOBUF
        .endif

        dec [rsi]._cnt
        inc [rsi]._ptr
        mov rsi,[rsi]._ptr
        dec rsi
        movzx rax,byte ptr [rsi]
    .until 1
    ret
_filbuf endp

    END
