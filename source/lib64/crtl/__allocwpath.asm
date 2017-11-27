include direct.inc
include malloc.inc
include errno.inc
include winnls.inc

    .code

    option win64:nosave

__allocwpath PROC USES rsi rdi path:LPSTR

    mov rsi,rcx
    xor rax,rax

    .if MultiByteToWideChar(CP_ACP, eax, rsi, -1, rax, eax)

        mov r10,rax
        add eax,4
        shl eax,1
        mov rdi,alloca(eax)
        add rax,8

        .if MultiByteToWideChar(CP_ACP, 0, rsi, -1, rax, r10d)

            mov rax,0x005C003F005C005C  ; "\\?\"
            mov [rdi],rax
            mov rax,rdi
            push [rbp+0x18]
            mov rsi,[rbp+0x10]
            mov rdi,[rbp+0x08]
            mov rbp,[rbp]
            retn
        .endif
    .endif
    mov rax,rsi
    ret

__allocwpath ENDP

    END
