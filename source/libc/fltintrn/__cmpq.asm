; __CMPQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cmpq() - Compare Quadruple float
;

include fltintrn.inc
include intrin.inc

    .code

__cmpq proc __ccall A:ptr qfloat_t, B:ptr qfloat_t

ifndef _WIN64
    mov ecx,A
    mov edx,B
endif
    assume rcx:ptr __m128i
    assume rdx:ptr __m128i

    .if ( [rcx].m128i_u64[0] == [rdx].m128i_u64[0] &&
          [rcx].m128i_u64[8] == [rdx].m128i_u64[8] )
        .return( 0 )
    .endif
    .if ( [rcx].m128i_i8[15] >= 0 && [rdx].m128i_i8[15] < 0 )
        .return( 1 )
    .endif
    .if ( [rcx].m128i_i8[15] < 0 && [rdx].m128i_i8[15] >= 0 )
        .return( -1 )
    .endif
    .if ( [rcx].m128i_i8[15] < 0 && [rdx].m128i_i8[15] < 0 )
        .if ( [rdx].m128i_u64[8] == [rcx].m128i_u64[8] )
            cmp [rdx].m128i_u64,[rcx].m128i_u64
        .endif
    .elseif ( [rcx].m128i_u64[8] == [rdx].m128i_u64[8] )
        cmp [rcx].m128i_u64,[rdx].m128i_u64
    .endif
    sbb eax,eax
    sbb eax,-1
    ret

__cmpq endp

    end
