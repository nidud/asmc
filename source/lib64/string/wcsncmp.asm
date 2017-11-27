include string.inc

    .code

    option win64:rsp nosave noauto

wcsncmp proc uses rsi rdi s1:LPWSTR, s2:LPWSTR, count:SIZE_T

    xchg rcx,r8
    .if rcx
        mov rsi,rcx
        mov rdi,r8
        xor eax,eax
        repnz scasw
        neg rcx
        add rcx,rsi
        mov rdi,r8
        mov rsi,rdx
        repz cmpsw
        mov ax,[rsi-2]
        xor ecx,ecx
        cmp ax,[rdi-2]
        .ifa
            not rcx
        .else
            .ifnz
                sub ecx,2
            .endif
        .endif
    .endif
    mov eax,ecx
    ret

wcsncmp endp

    END
