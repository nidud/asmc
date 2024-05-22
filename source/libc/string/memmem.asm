; MEMMEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

.code

memmem proc uses rsi rdi rbx haystack:ptr, hlen:size_t, needle:ptr, nlen:size_t

    ldr rbx,nlen
    ldr rdi,haystack
    ldr rcx,hlen
    ldr rsi,needle

    .if ( rbx == 0 )
        .return( rdi )
    .endif
    dec rbx
    .if ( rcx > rbx )

        .repeat
            mov al,[rsi]
            repnz scasb
            .break .ifnz
            .break .if ( rcx < rbx )
            .for ( rdx = rbx : rdx >= size_t : )

                sub rdx,size_t
                mov rax,[rsi+rdx+1]
               .continue( 01 ) .if ( rax != [rdi+rdx] )
            .endf
            .while ( rdx )

                dec rdx
                mov al,[rsi+rdx+1]
               .continue( 01 ) .if ( al != [rdi+rdx] )
            .endw
            .return( &[rdi-1] )
        .until 1
    .endif
    .return( NULL )

memmem endp

    end
