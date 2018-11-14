; _FLSWBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include winbase.inc

    .code

    assume rsi:LPFILE

_flswbuf proc uses rsi rdi rbx char:SINT, fp:LPFILE

    mov rsi,rdx
    xor eax,eax

    .repeat

        mov edi,[rsi]._flag
        .if !( edi & _IOREAD or _IOWRT or _IORW ) || edi & _IOSTRG

            or [rsi]._flag,_IOERR
            dec rax
            .break
        .endif


        .if edi & _IOREAD

            mov [rsi]._cnt,eax
            .if !( edi & _IOEOF )

                dec rax
                or [rsi]._flag,_IOERR
                .break
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

        .if !(edi & _IOMYBUF or _IONBF or _IOYOURBUF)

            _isatty(ebx)
            lea r8,stdout
            lea r9,stderr
            .if !((rsi == r8 || rsi == r9) && rax)
                _getbuf(rsi)
            .endif
        .endif

        mov eax,[rsi]._flag
        xor edi,edi
        mov [rsi]._cnt,edi

        .if eax & _IOMYBUF or _IOYOURBUF

            mov rax,[rsi]._base
            mov rdi,[rsi]._ptr
            sub rdi,rax
            add rax,2
            mov [rsi]._ptr,rax
            mov eax,[rsi]._bufsiz
            sub eax,2
            mov [rsi]._cnt,eax
            xor eax,eax

            .ifs edi > eax
                _write(ebx, [rsi]._base, edi)
            .else
                lea r8,_osfile
                mov dl,[r8+rbx]
                .ifs ebx > eax && dl & FH_APPEND

                    lea rcx,_osfhnd
                    mov rcx,[rcx+rbx*8]
                    SetFilePointer(rcx, eax, rax, SEEK_END)
                    xor eax,eax
                .endif
            .endif

            mov edx,char
            mov rbx,[rsi]._base
            mov [rbx],dx
        .else
            add edi,2
            _write(ebx, &char, edi)
        .endif

        .if eax != edi
            or [rsi]._flag,_IOERR
            or eax,-1
        .else
            movzx eax,word ptr char
        .endif
    .until 1
    ret

_flswbuf endp

    END
