; _WCSNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
    .code

_wcsnicmp::

    mov r9,rdx
    mov al,-1

    .repeat

        .break .if !ax

        xor eax,eax
        .break .if !r8d

        mov ax,[r9]
        dec r8d
        add r9,2
        add rcx,2
        .continue(0) .if ax == [rcx-2]

        mov dx,[rcx-2]
        and eax,0xFFDF
        and edx,0xFFDF
        .continue(0) .if edx == eax

        sbb ax,ax
        sbb ax,-1
    .until 1
    movsx rax,ax
    ret

    end
