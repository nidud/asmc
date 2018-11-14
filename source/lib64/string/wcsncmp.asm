; WCSNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

wcsncmp::

    push rsi
    push rdi
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
    pop rdi
    pop rsi
    ret

    END
