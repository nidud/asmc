; STRTOK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .data
     s0 string_t ?

    .code

strtok proc uses rsi rdi s1:string_t, s2:string_t

ifdef _WIN64
    mov rsi,rcx
    mov rdi,rdx
else
    mov rsi,s1
    mov rdi,s2
endif

    .if ( rsi )
        mov s0,rsi
    .else
        mov rsi,s0
    .endif

    .while ( byte ptr [rsi] )

        mov rcx,rdi
        mov al,[rcx]

        .while ( al )

            .break .if ( al == [rsi] )

            inc rcx
            mov al,[rcx]
        .endw
        .break .if ( !al )
        inc rsi
    .endw

    .repeat

        xor eax,eax
        .break .if ( al == [rsi] )

        mov rdx,rsi
        .while ( byte ptr [rsi] )

            mov rcx,rdi
            mov al,[rcx]

            .while ( al )

                .if ( al == [rsi] )

                    mov [rsi],ah
                    inc rsi
                   .break( 1 )
                .endif

                inc rcx
                mov al,[rcx]
            .endw
            inc rsi
        .endw
        mov rax,rdx
    .until 1
    mov s0,rsi
    ret

strtok endp

    end
