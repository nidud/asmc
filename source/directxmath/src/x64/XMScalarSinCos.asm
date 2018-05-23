include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMScalarSinCos proc pSin:ptr float, pCos:ptr float, Value:float
    ;
    ; Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
    ;
    _mm_store_ps(xmm0, xmm2)
    _mm_setzero_ps(xmm1)
    _mm_cvtsi64_si128(xmm2, XM_1DIV2PI)
    _mm_cvtsi32_si128(xmm3, 0.5)

    ucomiss xmm0,xmm1
    _mm_cvtss_sd(xmm1, xmm0)
    _mm_mul_sd(xmm2, xmm1)
    _mm_cvtsd_ss(xmm2, xmm2)
    .ifnb
        _mm_add_ss(xmm2, xmm3)
    .else
        _mm_sub_ss(xmm2, xmm3)
    .endif
    ;
    ; Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
    ;
    _mm_setzero_ps(xmm0)
    _mm_cvt_si2ss(xmm0, _mm_cvtt_ss2si(xmm2))

    _mm_cvtss_sd(xmm0, xmm0)
    _mm_setzero_ps(xmm2)

    _mm_cvtsi64_si128(xmm3, XM_1DIV2PI)
    _mm_mul_sd(xmm0, xmm3)
    _mm_sub_sd(xmm1, xmm0)
    _mm_setzero_ps(xmm0)
    _mm_cvtsd_ss(xmm0, xmm1)
    _mm_cvtss_sd(xmm2, xmm0)

    ucomisd xmm2,xmm3
    .ifa

        mov r8d,-1.0
        _mm_sub_sd(xmm3, xmm2)
        _mm_cvtsd_ss(xmm0, xmm3)

    .else

        _mm_cvtsi64_si128(xmm3, -XM_1DIV2PI)
        ucomisd xmm2,xmm3
        .ifb

            mov r8d,-1.0
            _mm_sub_sd(xmm3, xmm2)
            _mm_cvtsd_ss(xmm0, xmm3)

        .else

            mov r8d,+1.0
        .endif
    .endif

    _mm_store_ps(xmm3, xmm0)
    _mm_store_ps(xmm2, _mm_mul_ss(xmm0, xmm0))
    ;
    ; 11-degree minimax approximation
    ;
    _mm_cvtsi32_si128(xmm0,-2.3889859e-08)
    _mm_add_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 2.7525562e-06))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 0.00019840874))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 0.0083333310))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 0.16666667))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 1.0))
    movss [rcx],_mm_mul_ss(xmm0, xmm3)
    ;
    ; 10-degree minimax approximation
    ;
    _mm_cvtsi32_si128(xmm0, -2.6051615e-07)
    _mm_add_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 2.4760495e-05))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 0.0013888378))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 0.041666638))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 0.5))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm2), _mm_cvtsi32_si128(xmm1, 1.0))
    movd xmm1,r8d
    movss [rdx],_mm_mul_ss(xmm0, xmm1)
    ret

XMScalarSinCos endp

    end
