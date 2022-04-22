; _FLSBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume r12:LPFILE

_flsbuf proc uses rbx r12 r13 c:SINT, fp:LPFILE

   .new char:int_t = c

    mov r12,fp
    xor eax,eax

    mov edi,[r12]._flag
    .if ( !( edi & _IOREAD or _IOWRT or _IORW ) || edi & _IOSTRG )

        or [r12]._flag,_IOERR
        dec rax
       .return
    .endif

    .if ( edi & _IOREAD )

        mov [r12]._cnt,eax
        .if !( edi & _IOEOF )

            dec rax
            or [r12]._flag,_IOERR
           .return
        .endif

        mov rax,[r12]._base
        mov [r12]._ptr,rax
        and edi,not _IOREAD
    .endif

    or  edi,_IOWRT
    and edi,not _IOEOF
    mov [r12]._flag,edi
    mov [r12]._cnt,0
    mov ebx,[r12]._file

    .if ( !( edi & _IOMYBUF or _IONBF or _IOYOURBUF ) )

        _isatty(ebx)

        lea r8,stdout
        lea r9,stderr

        .if ( !( ( r12 == r8 || r12 == r9 ) && rax ) )

            _getbuf(r12)
        .endif
    .endif

    xor r13d,r13d
    mov [r12]._cnt,r13d
    mov eax,[r12]._flag

    .if ( eax & _IOMYBUF or _IOYOURBUF )

        mov rax,[r12]._base
        mov r13,[r12]._ptr
        sub r13,rax
        inc rax
        mov [r12]._ptr,rax
        mov eax,[r12]._bufsiz
        dec eax
        mov [r12]._cnt,eax
        xor eax,eax

        .ifs ( r13 > rax )

            _write(ebx, [r12]._base, r13d)

        .else

            lea r8,_osfile
            mov dl,[r8+rbx]

            .ifs ( ebx > eax && dl & FH_APPEND )

                _lseek(ebx, 0, SEEK_END)
                xor eax,eax
            .endif
        .endif

        mov edx,char
        mov rbx,[r12]._base
        mov [rbx],dl
    .else
        inc r13d
        _write(ebx, addr char, r13d)
    .endif

    .if ( rax != r13 )

        or [r12]._flag,_IOERR
        or rax,-1
    .else
        movzx eax,byte ptr char
    .endif
    ret

_flsbuf endp

    END
