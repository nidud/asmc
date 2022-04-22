; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_stricmp proc a:string_t, b:string_t

    mov rax,-1

    .repeat

        .break .if !al

        mov al,[rsi]
        cmp al,[rdi]
        lea rsi,[rsi+1]
        lea rdi,[rdi+1]
        .continue(0) .ifz

        mov ah,[rdi-1]
        sub ax,'AA'
        cmp al,'Z'-'A'+1
        sbb dl,dl
        and dl,'a'-'A'
        cmp ah,'Z'-'A'+1
        sbb dh,dh
        and dh,'a'-'A'
        add ax,dx
        add ax,'AA'
        .continue(0) .if ah == al

        sbb al,al
        sbb al,-1
    .until 1
    movsx rax,al
    ret

_stricmp endp

    end
