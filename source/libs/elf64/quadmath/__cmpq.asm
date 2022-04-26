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

    option win64:noauto

__cmpq proc A:ptr, B:ptr

    assume rdi:ptr __m128i
    assume rsi:ptr __m128i

    .return 0 .if ( [rdi].m128i_u64[0] == [rsi].m128i_u64[0] &&
                    [rdi].m128i_u64[8] == [rsi].m128i_u64[8] )
    .return 1 .if ( [rdi].m128i_i8[15] >= 0 && [rsi].m128i_i8[15] < 0 )
    .return -1 .if ( [rdi].m128i_i8[15] < 0 && [rsi].m128i_i8[15] >= 0 )
    .if ( [rsi].m128i_i8[15] < 0 && [rsi].m128i_i8[15] < 0 )
        .if ( [rsi].m128i_u64[8] == [rdi].m128i_u64[8] )
            mov rax,[rdi].m128i_u64
            cmp [rsi].m128i_u64,rax
        .endif
    .elseif ( [rdi].m128i_u64[8] == [rsi].m128i_u64[8] )
        mov rax,[rsi].m128i_u64
        cmp [rdi].m128i_u64,rax
    .endif
    sbb eax,eax
    sbb eax,-1
    ret

__cmpq endp

    end
