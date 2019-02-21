; STRTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
    s0 dq ?

    .code

strtok proc s1:LPSTR, s2:LPSTR

    .if rcx

        mov s0,rcx
    .else

        mov rcx,s0
    .endif

    .while byte ptr [rcx]

        mov r8,rdx
        mov al,[r8]

        .while al

            .break .if al == [rcx]

            inc r8
            mov al,[r8]

        .endw

        .break .if !al
        inc rcx

    .endw

    .repeat

        xor eax,eax
        .break .if al == [rcx]

        mov r9,rcx

        .while byte ptr [rcx]

            mov r8,rdx
            mov al,[r8]

            .while al

                .if al == [rcx]

                    mov [rcx],ah
                    inc rcx
                    .break(1)

                .endif

                inc r8
                mov al,[r8]

            .endw
            inc rcx

        .endw
        mov rax,r9

    .until 1

    mov s0,rcx
    ret

strtok endp

    END
