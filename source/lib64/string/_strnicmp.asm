; _STRNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_strnicmp::

    mov r9,rdx
    mov al,-1
    .repeat

        .break .if !al

        xor eax,eax
        .break .if !r8

        mov al,[r9]
        dec r8
        inc r9
        inc rcx
        .continue(0) .if al == [rcx-1]

        mov ah,[rcx-1]
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

    end
