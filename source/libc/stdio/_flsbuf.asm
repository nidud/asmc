; _FLSBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include winbase.inc

    .code

    assume rsi:LPFILE

_flsbuf proc uses rsi rdi rbx char:int_t, fp:LPFILE

ifndef _WIN64
    mov edx,fp
endif
    mov rsi,rdx
    xor eax,eax

    mov edi,[rsi]._flag
    .if ( !( edi & _IOREAD or _IOWRT or _IORW ) || edi & _IOSTRG )

        or  [rsi]._flag,_IOERR
        dec rax
       .return
    .endif

    .if ( edi & _IOREAD )

        mov [rsi]._cnt,eax
        .if !( edi & _IOEOF )

            dec rax
            or  [rsi]._flag,_IOERR
           .return
        .endif

        mov rax,[rsi]._base
        mov [rsi]._ptr,rax
        and edi,not _IOREAD
    .endif

    or  edi,_IOWRT
    and edi,not _IOEOF
    mov [rsi]._flag,edi
    mov [rsi]._cnt,0
    mov ebx,[rsi]._file

    .if ( !( edi & _IOMYBUF or _IONBF or _IOYOURBUF ) )

        _isatty( ebx )

        mov rcx,stdout
        mov rdx,stderr
        .if ( !( ( rsi == rcx || rsi == rdx ) && rax ) )

            _getbuf( rsi )
        .endif
    .endif

    mov eax,[rsi]._flag
    xor edi,edi
    mov [rsi]._cnt,edi

    .if ( eax & _IOMYBUF or _IOYOURBUF )

        mov rax,[rsi]._base
        mov rdi,[rsi]._ptr
        sub rdi,rax
        inc rax
        mov [rsi]._ptr,rax
        mov eax,[rsi]._bufsiz
        dec eax
        mov [rsi]._cnt,eax
        xor eax,eax

        .ifs ( edi > eax )

            _write( ebx, [rsi]._base, edi )

        .else

            lea rcx,_osfile
            mov dl,[rcx+rbx]

            .ifs ( ebx > eax && dl & FH_APPEND )

                lea rcx,_osfhnd
                mov rcx,[rcx+rbx*size_t]
                SetFilePointer( rcx, eax, rax, SEEK_END )
                xor eax,eax
            .endif
        .endif

        mov edx,char
        mov rbx,[rsi]._base
        mov [rbx],dl

    .else

        inc edi
        _write( ebx, addr char, edi )
    .endif

    .if ( eax != edi )
        or [rsi]._flag,_IOERR
        or eax,-1
    .else
        movzx eax,byte ptr char
    .endif
    ret

_flsbuf endp

    end
