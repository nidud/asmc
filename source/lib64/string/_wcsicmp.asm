; _STRICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

_wcsicmp::

    mov r8,rdx
    mov rax,-1

    .repeat

        .break .if !ax

        mov ax,[r8]
        cmp ax,[rcx]
        lea r8,[r8+2]
        lea rcx,[rcx+2]
        .continue(0) .ifz
        mov dx,[rcx-2]
        .if dx >= 'A' && dx <= 'Z'
            or dl,0x20
        .endif
        .if ax >= 'A' && ax <= 'Z'
            or al,0x20
        .endif
        .continue(0) .if dx == ax

        sbb al,al
        sbb al,-1
    .until 1
    movsx rax,al
    ret

    end
