; ATOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .code

atol::

    xor eax,eax
    xor edx,edx

    .repeat

        mov dl,[rcx]
        inc rcx

        .continue(0) .if dl == ' '

        mov r9b,dl

        .if ( dl == '+' || dl == '-' )

            mov dl,[rcx]
            inc rcx

        .endif

        .while 1

            sub dl,'0'
            .break .ifb
            .break .if dl > 9

            lea r8,[rdx+rax*8]
            lea rax,[r8+rax*2]
            mov dl,[rcx]
            inc rcx

        .endw

        .break .if ( r9b != '-' )
        neg rax

    .until 1
    ret

    end
