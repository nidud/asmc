include stdio.inc
include io.inc
include winbase.inc

    .code

    assume esi:LPFILE

_flsbuf proc uses esi edi ebx char:SIZE_T, fp:LPFILE

    mov esi,fp
    mov edi,[esi]._flag
    test edi,_IOREAD or _IOWRT or _IORW
    jz  error
    test edi,_IOSTRG
    jnz error
    mov ebx,[esi]._file

    .if edi & _IOREAD

        xor eax,eax
        mov [esi]._cnt,eax
        test edi,_IOEOF
        jz  error

        mov eax,[esi]._base
        mov [esi]._ptr,eax
        and edi,not _IOREAD
    .endif

    or  edi,_IOWRT
    and edi,not _IOEOF
    mov [esi]._flag,edi
    xor eax,eax
    mov [esi]._cnt,eax

    .if !( edi & _IOMYBUF or _IONBF or _IOYOURBUF )
        _isatty( ebx )
        .if !( ( esi == offset stdout || esi == offset stderr ) && eax )
            _getbuf( esi )
        .endif
    .endif

    mov eax,[esi]._flag
    xor edi,edi
    mov [esi]._cnt,edi

    .if eax & _IOMYBUF or _IOYOURBUF

        mov eax,[esi]._base
        mov edi,[esi]._ptr
        sub edi,eax
        inc eax
        mov [esi]._ptr,eax
        mov eax,[esi]._bufsiz
        dec eax
        mov [esi]._cnt,eax

        xor eax,eax

        .if sdword ptr edi > eax
            _write( ebx, [esi]._base, edi )
        .elseif sdword ptr ebx > eax && _osfile[ebx] & FH_APPEND
            SetFilePointer( _osfhnd[ebx*4], eax, eax, SEEK_END )
            xor eax,eax
        .endif
        mov edx,char
        mov ebx,[esi]._base
        mov [ebx],dl
    .else
        inc edi
        _write( ebx, addr char, edi )
    .endif
    cmp eax,edi
    jne error
    movzx eax,byte ptr char
toend:
    ret
error:
    or  edi,_IOERR
    mov [esi]._flag,edi
    mov eax,-1
    jmp toend
_flsbuf endp

    END
