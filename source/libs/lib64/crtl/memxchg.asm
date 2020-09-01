; MEMXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

memxchg::

    option loopalign:4

    .while( r8 >= 8 )

        sub r8,8
        mov rax,[rcx+r8]
        mov r10,[rdx+r8]
        mov [rcx+r8],r10
        mov [rdx+r8],rax

    .endw

    .while( r8 )

        dec r8
        mov al,[rcx+r8]
        mov r10b,[rdx+r8]
        mov [rcx+r8],r10b
        mov [rdx+r8],al

    .endw

    mov rax,rcx
    ret

    end
