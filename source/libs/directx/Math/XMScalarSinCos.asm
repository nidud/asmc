; XMSCALARSINCOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMScalarSinCos proc XM_CALLCONV pSin:ptr float, pCos:ptr float, Value:float

    ldr rcx,pSin
    ldr rdx,pCos
    ldr xmm0,Value
    ;;
    ;; Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
    ;;
    _mm_setzero_ps(xmm1)
    comiss xmm0,xmm1
    _mm_store_ss(xmm1, xmm0)
    _mm_mul_ss(xmm1, XM_1DIV2PI)
    .ifnb
        _mm_add_ss(xmm1, 0.5)
    .else
        _mm_sub_ss(xmm1, 0.5)
    .endif
    _mm_cvt_si2ss(xmm1, _mm_cvtt_ss2si(xmm1))
    _mm_mul_ss(xmm1, XM_2PI)
    _mm_sub_ss(xmm0, xmm1)
    _mm_move_ss(xmm1, -1.0)
    _mm_move_ss(xmm2, xmm0)
    ;;
    ;; Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
    ;;
    comiss xmm0,XM_PIDIV2
    .ifa
        _mm_move_ss(xmm0, XM_PI)
        _mm_sub_ss(xmm0, xmm2)
    .else
        comiss xmm0,-XM_PIDIV2
        .ifa
            _mm_move_ss(xmm1, 1.0)
        .else
            _mm_move_ss(xmm0, -XM_PI)
            _mm_sub_ss(xmm0, xmm2)
        .endif
    .endif
    _mm_store_ss(xmm3, xmm0)
    _mm_mul_ss(xmm3, xmm3)
    ;;
    ;; 11-degree minimax approximation
    ;;
    _mm_move_ss(xmm2, -2.3889859e-08)
    _mm_add_ss(_mm_mul_ss(xmm2, xmm3), 2.7525562e-06)
    _mm_sub_ss(_mm_mul_ss(xmm2, xmm3), 0.00019840874)
    _mm_add_ss(_mm_mul_ss(xmm2, xmm3), 0.0083333310)
    _mm_sub_ss(_mm_mul_ss(xmm2, xmm3), 0.16666667)
    _mm_add_ss(_mm_mul_ss(xmm2, xmm3), 1.0)
    _mm_mul_ss(xmm0, xmm2)
    ;;
    ;; 10-degree minimax approximation
    ;;
    _mm_move_ss(xmm2, -2.6051615e-07)
    _mm_add_ss(_mm_mul_ss(xmm2, xmm3), 2.4760495e-05)
    _mm_sub_ss(_mm_mul_ss(xmm2, xmm3), 0.0013888378)
    _mm_add_ss(_mm_mul_ss(xmm2, xmm3), 0.041666638)
    _mm_sub_ss(_mm_mul_ss(xmm2, xmm3), 0.5)
    _mm_add_ss(_mm_mul_ss(xmm2, xmm3), 1.0)
    _mm_mul_ss(xmm1, xmm2)
    .if ( rcx )
        _mm_store_ss([rcx], xmm0)
    .endif
    .if ( rdx )
        _mm_store_ss([rdx], xmm1)
    .endif
    ret

XMScalarSinCos endp

    end
