; __ALLOCWPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include direct.inc
include malloc.inc
include errno.inc
include winnls.inc

    .code

__allocwpath PROC USES rsi rdi rbx path:LPSTR

    mov rsi,rcx
    xor rax,rax

    .if MultiByteToWideChar(CP_ACP, eax, rsi, -1, rax, eax)

        mov ebx,eax
        lea ecx,[rax*2+8]
        mov rdi,malloc(ecx)
        add rax,8

        .if MultiByteToWideChar(CP_ACP, 0, rsi, -1, rax, ebx)

            mov rax,0x005C003F005C005C  ; "\\?\"
            mov [rdi],rax
            mov rax,rdi
        .endif
    .endif
    ret

__allocwpath ENDP

    END
