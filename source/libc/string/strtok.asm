; STRTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
     s0 string_t ?

    .code

strtok proc uses rbx s1:string_t, s2:string_t

    ldr rbx,s1
    ldr rdx,s2

    .if ( rbx )
        mov s0,rbx
    .else
        mov rbx,s0
    .endif

    .while ( byte ptr [rbx] )

        mov rcx,rdx
        mov al,[rcx]

        .while ( al )

            .break .if ( al == [rbx] )

            inc rcx
            mov al,[rcx]
        .endw
        .break .if ( !al )
        inc rbx
    .endw

    .repeat

        xor eax,eax
        .break .if ( al == [rbx] )

        push rbx
        .while ( byte ptr [rbx] )

            mov rcx,rdx
            mov al,[rcx]

            .while ( al )

                .if ( al == [rbx] )

                    mov [rbx],ah
                    inc rbx
                   .break( 1 )
                .endif

                inc rcx
                mov al,[rcx]
            .endw
            inc rbx
        .endw
        pop rax
    .until 1
    mov s0,rbx
    ret

strtok endp

    end
