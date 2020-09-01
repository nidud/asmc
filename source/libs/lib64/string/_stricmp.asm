; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_stricmp::
strcasecmp::

    mov r8,rdx
    mov rax,-1

    .repeat

        .break .if !al

        mov al,[r8]
        cmp al,[rcx]
        lea r8,[r8+1]
        lea rcx,[rcx+1]
        .continue(0) .ifz

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
