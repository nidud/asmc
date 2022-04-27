; ATAN2Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

atan2q proc Y:real16, X:real16

  local x:__m128i, y:__m128i, m:uint_t

    movaps x,xmm1
    movaps y,xmm0

    mov rax,x.m128i_u64[8]
    mov rdx,y.m128i_u64[8]
    mov rcx,0x7fffffffffffffff
    and rax,rcx
    and rdx,rcx

    mov r10,x.m128i_u64[0]
    mov r11,y.m128i_u64[0]
    mov r8,r10
    mov r9,r11
    neg r8
    neg r9
    or  r8,r10
    or  r9,r11
    shr r8,63
    shr r9,63
    or  r8,rax
    or  r9,rdx
    mov rcx,0x7fff000000000000

    .if r8 > rcx || r9 > rcx ; x or y is NaN

        .return addq(xmm0, xmm1)
    .endif

    mov r8,x.m128i_u64[8]
    mov rcx,0x3fff000000000000
    sub r8,rcx
    or  r8,r10
    .ifz
        .return atanq(xmm0) ; x = 1.0
    .endif

    mov r8,x.m128i_u64[8]
    mov r9,y.m128i_u64[8]
    shr r8,62
    shr r9,63
    and r8d,2
    and r9d,1
    or  r8d,r9d ; 2 * sign(x) + sign(y)
    mov m,r8d

    ; when y = 0

    or r11,rdx
    .ifz
        .switch r8
        .case 0
        .case 1: .return
        .case 2: .return 3.14159265358979323846264338327950280 + 1.0e-4900
        .case 3: .return -3.14159265358979323846264338327950280 - 1.0e-4900
        .endsw
    .endif

    ; when x = 0

    or r10,rax
    .ifz
        mov rax,y.m128i_u64[8]
        test rax,rax
        .return real16( -1.57079632679489661923132169163975140 - 1.0e-4900 ) .ifs
        .return 1.57079632679489661923132169163975140 + 1.0e-4900
    .endif

    ; when x is INF

    mov rcx,0x7fff000000000000
    .if rax == rcx
        .if rdx == rcx
            .switch r8
            .case 0: .return 7.85398163397448309615660845819875699e-1 + 1.0e-4900
            .case 1: .return -7.85398163397448309615660845819875699e-1 - 1.0e-4900
            .case 2: .return 3.0 * 7.85398163397448309615660845819875699e-1 + 1.0e-4900
            .case 3: .return -3.0 * 7.85398163397448309615660845819875699e-1 - 1.0e-4900
            .endsw
        .else
            .switch r8
            .case 0: .return 0.0
            .case 1: .return -0.0
            .case 2: .return 3.14159265358979323846264338327950280 + 1.0e-4900
            .case 3: .return -3.14159265358979323846264338327950280 - 1.0e-4900
            .endsw
        .endif
    .endif

    ; when y is INF

    .if rdx == rcx
        mov rax,y.m128i_u64[8]
        test rax,rax
        .ifs
            .return -1.57079632679489661923132169163975140 - 1.0e-4900
        .endif
        .return 1.57079632679489661923132169163975140 + 1.0e-4900
    .endif

    ; compute y/x

    mov rcx,rdx
    sub rcx,rax
    sar rcx,48
    .ifs rcx > 120

        movaps xmm0,{ 0.58800260354756755124561108062508520 }
    .else
        mov rax,x.m128i_u64[8]
        .ifs rax < 0 && rdx < -120

            xorps xmm0,xmm0
        .else

            atanq(fabsq(divq(xmm0, xmm1)))
        .endif
    .endif

    mov eax,m
    .if eax
        .if eax == 1
            pxor xmm0,{ -0.0 }
        .elseif eax == 2
            movaps xmm1,subq( xmm0, 8.67181013012378102479704402604335225e-35 )
            subq( M_PI, xmm1 )
        .else
            subq(subq( xmm0, 8.67181013012378102479704402604335225e-35 ), M_PI )
        .endif
    .endif
    ret

atan2q endp

    end
