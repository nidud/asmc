include stdio.inc
include io.inc
include malloc.inc
include crtl.inc

externdef _stdbuf:qword

    .code

    option win64:rsp nosave
    assume rbx:ptr _iobuf

_stbuf proc uses rsi rbx fp:LPFILE

    mov rbx,rcx
    .if _isatty([rbx]._file)

        xor rax,rax
        xor rsi,rsi
        lea r10,stdout
        lea r11,stderr
        .repeat
            .if rbx != r10
                .break .if rbx != r11
                inc rsi
            .endif
            mov ecx,[rbx]._flag
            and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
            .break .ifnz
            or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
            mov [rbx]._flag,ecx
            shl rsi,3
            lea r10,_stdbuf
            add rsi,r10
            mov rax,[rsi]
            mov ecx,_INTIOBUF
            .if !eax
                mov [rsi],malloc(rcx)
                mov ecx,_INTIOBUF
                .if !rax
                    lea rax,[rbx]._charbuf
                    mov ecx,4
                .endif
            .endif
            mov [rbx]._ptr,rax
            mov [rbx]._base,rax
            mov [rbx]._bufsiz,ecx
            mov rax,1
        .until 1
    .endif
    ret
_stbuf endp

    END
