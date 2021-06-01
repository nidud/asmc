; FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .data
     table real16 \
        40024000000000000000000000000000r, ; 1.e1
        40059000000000000000000000000000r,
        400C3880000000000000000000000000r,
        40197D78400000000000000000000000r,
        40341C37937E08000000000000000000r,
        40693B8B5B5056E16B3BE04000000000r,
        40D384F03E93FF9F4DAA797ED6E38ED6r,
        41A827748F9301D319BF8CDE66D86D62r,
        435154FDD7F73BF3BD1BBB77203731FDr,
        46A3C633415D4C1D238D98CAB8A978A0r,
        4D4892ECEB0D02EA182ECA1A7A51E316r,
        5A923D1676BB8A7ABBC94E9A519C6535r,
        752588C0A40514412F3592982A7F0094r, ; 5 1.e4096
        7FFF0000000000000000000000000000r  ; INF

    .code

fltscale proc vectorcall uses rsi rdi rbx q:real16, exponent:int_t

    mov edi,edx
    lea rsi,table

    .ifs ( edi > 4096 )

        mulq(xmm0, [rsi+12*16])
        sub edi,4096
    .endif

    .if edi

        xor ebx,ebx
        movaps xmm2,xmm0
        movaps xmm0,{ 1.0 }

        .ifs ( edi < 0 )
            neg edi
            inc ebx
        .endif
        .if ( edi >= 8192 )
            mov edi,8192
        .endif

        .for ( : edi : edi >>= 1, rsi += 16 )
            .if ( edi & 1 )
                mulq(xmm0, [rsi])
            .endif
        .endf

        .if ebx
            divq(xmm2, xmm0)
        .else
            mulq(xmm2, xmm0)
        .endif
    .endif
    ret

fltscale endp

    end
