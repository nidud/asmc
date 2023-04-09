; _CGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_cgets proc uses rbx r12 r13 string:LPSTR

    .if ( rdi == NULL )

        .return
    .endif

    xor   r12,r12               ; len
    movzx ebx,byte ptr [rdi]    ; maxlen
    lea   r13,[rdi+2]
    dec   ebx

    .while ( r12 < rbx )

        _getch()

        .if ( al == 8 ) ; '\b'

            .ifs ( r12 > 0 )

                _cputs( "\b \b" ) ; go back, clear char on screen with space
                dec r12
                mov byte ptr [r13+r12],0
            .endif

        .elseif ( al == 10 ) ; '\n'

            mov byte ptr [r13+r12],0
            .break

        .elseif ( al == 0 )

            mov byte ptr [r13+r12],0
            _ungetch(0)
            .break

        .else

            mov [r13+r12],al
            inc r12
            _putch( eax )
        .endif
    .endw

    mov byte ptr [r13+rbx],0
    mov rax,r13
    mov rcx,r12
    mov [rax-1],cl
    ret

_cgets endp

    end
