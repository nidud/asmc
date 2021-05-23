; FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include quadmath.inc
include intrin.inc

    .data

    ; Assembler version independent hard values

    align 16
    table label real16

    Q1e1    real16 40024000000000000000000000000000r
    Q1e2    real16 40059000000000000000000000000000r
    Q1e4    real16 400C3880000000000000000000000000r
    Q1e8    real16 40197D78400000000000000000000000r
    Q1e16   real16 40341C37937E08000000000000000000r
    Q1e32   real16 40693B8B5B5056E16B3BE04000000000r
    Q1e64   real16 40D384F03E93FF9F4DAA797ED6E38ED6r
    Q1e128  real16 41A827748F9301D319BF8CDE66D86D62r
    Q1e256  real16 435154FDD7F73BF3BD1BBB77203731FDr
    Q1e512  real16 46A3C633415D4C1D238D98CAB8A978A0r
    Q1e1024 real16 4D4892ECEB0D02EA182ECA1A7A51E316r
    Q1e2048 real16 5A923D1676BB8A7ABBC94E9A519C6535r
    Q1e4096 real16 752588C0A40514412F3592982A7F0095r
    QINF    real16 7FFF0000000000000000000000000000r

    .code

fltscale proc vectorcall uses rsi rdi rbx q:real16, exponent:int_t

  local signed:int_t

    mov edi,edx
    .ifs ( edi > 4096 )

        mulq(xmm0, Q1e4096)
        sub edi,4096

    .elseif ( sdword ptr edi < -4096 )

        divq(xmm0, Q1e4096)
        add edi,4096
    .endif

    .if edi

        xor ebx,ebx
        movaps xmm3,xmm0
        movaps xmm0,{ 1.0 }

        .ifs ( edi < 0 )
            neg edi
            inc ebx
        .endif
        .if ( edi >= 8192 )
            mov edi,8192
        .endif

        .for ( rsi = &table : edi : edi >>= 1, rsi += 16 )
            .if ( edi & 1 )
                mulq(xmm0, [rsi])
            .endif
        .endf

        .if ebx
            divq(xmm3, xmm0)
        .else
            mulq(xmm3, xmm0)
        .endif
    .endif
    ret

fltscale endp

    end
