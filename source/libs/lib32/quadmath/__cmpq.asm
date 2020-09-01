; CMPQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cmpq() - Compare Quadruple float
;

include quadmath.inc
include intrin.inc

    .code

__cmpq proc A:ptr, B:ptr

    mov ecx,A
    mov edx,B

    assume ecx:ptr __m128i
    assume edx:ptr __m128i

    .repeat

        .if ( [ecx].m128i_u32[0]  == [edx].m128i_u32[0] && \
              [ecx].m128i_u32[4]  == [edx].m128i_u32[4] && \
              [ecx].m128i_u32[8]  == [edx].m128i_u32[8] && \
              [ecx].m128i_u32[12] == [edx].m128i_u32[12] )

            xor eax,eax
            .break
        .endif

        .if ( [ecx].m128i_i8[15] >= 0 && [edx].m128i_i8[15] < 0 )

            mov eax,1
            .break
        .endif

        .if ( [ecx].m128i_i8[15] < 0 && [edx].m128i_i8[15] >= 0 )

            mov eax,-1
            .break
        .endif

        .if ( [ecx].m128i_i8[15] < 0 && [edx].m128i_i8[15] < 0 )
            .if ( [edx].m128i_u32[12] == [ecx].m128i_u32[12] )
                .if ( [edx].m128i_u32[8] == [ecx].m128i_u32[8] )
                    .if ( [edx].m128i_u32[4] == [ecx].m128i_u32[4] )
                        mov eax,[ecx].m128i_u32
                        cmp [edx].m128i_u32,eax
                    .endif
                .endif
            .endif
        .else
            .if ( [ecx].m128i_u32[12] == [edx].m128i_u32[12] )
                .if ( [ecx].m128i_u32[8] == [edx].m128i_u32[8] )
                    .if ( [ecx].m128i_u32[4] == [edx].m128i_u32[4] )
                        mov eax,[edx].m128i_u32
                        cmp [ecx].m128i_u32,eax
                    .endif
                .endif
            .endif
        .endif
        sbb eax,eax
        sbb eax,-1
    .until 1
    ret
__cmpq endp

    end
