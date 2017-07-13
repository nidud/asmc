include strlib.inc

    .code

    option win64:rsp nosave noauto

strfcat PROC USES rsi rdi buffer:LPSTR, path:LPSTR, file:LPSTR

    mov rsi,rdx
    mov rdx,rcx
    xor eax,eax
    xor ecx,ecx
    dec rcx

    .if rsi
        mov rdi,rsi     ; overwrite buffer
        repne scasb
        mov rdi,rdx
        not rcx
        rep movsb
    .else
        mov rdi,rdx     ; length of buffer
        repne scasb
    .endif

    dec rdi
    .if rdi != rdx      ; add slash if missing
        mov al,[rdi-1]
        .if !(al == '\' || al == '/')
            mov al,'\'
            stosb
        .endif
    .endif

    mov rsi,r8          ; add file name
    .repeat
        lodsb
        stosb
    .until !eax
    mov rax,rdx
    ret

strfcat ENDP

    END
