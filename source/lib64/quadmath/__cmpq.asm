; __CMPQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cmpq() - Compare Quadruple float
;

include quadmath.inc
include intrin.inc

    .code

    option win64:rsp nosave noauto

__cmpq proc A:ptr, B:ptr

    assume rcx:ptr __m128i
    assume rdx:ptr __m128i

    .repeat

        .if ( [rcx].m128i_u64[0] == [rdx].m128i_u64[0] && \
              [rcx].m128i_u64[8] == [rdx].m128i_u64[8] )

            xor eax,eax
            .break
        .endif

        .if ( [rcx].m128i_i8[15] >= 0 && [rdx].m128i_i8[15] < 0 )

            mov eax,1
            .break
        .endif

        .if ( [rcx].m128i_i8[15] < 0 && [rdx].m128i_i8[15] >= 0 )

            mov eax,-1
            .break
        .endif

        .if ( [rcx].m128i_i8[15] < 0 && [rdx].m128i_i8[15] < 0 )
            .if ( [rdx].m128i_u64[8] == [rcx].m128i_u64[8] )
                mov rax,[rcx].m128i_u64
                cmp [rdx].m128i_u64,rax
            .endif

        .elseif ( [rcx].m128i_u64[8] == [rdx].m128i_u64[8] )
            mov rax,[rdx].m128i_u64
            cmp [rcx].m128i_u64,rax
        .endif
        sbb eax,eax
        sbb eax,-1
    .until 1
    ret

__cmpq endp

    end
