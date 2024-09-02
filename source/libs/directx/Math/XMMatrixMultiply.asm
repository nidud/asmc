; XMMATRIXMULTIPLY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMMatrixMultiply proc XM_CALLCONV uses xmm6 M1:CXMMATRIX, M2:CXMMATRIX

    ldr rcx,M1
    ldr rdx,M2

    vX equ <xmm3>
    vY equ <xmm4>
    vZ equ <xmm5>
    vW equ <xmm6>

ifdef _XM_AVX_INTRINSICS_
    A  equ <real4 ptr [rcx]>
else
    A  equ <xmmword ptr [rcx]>
endif
    B  equ <xmmword ptr [rdx]>
    ;;
    ;; Splat the component X,Y,Z then W
    ;;
ifdef _XM_AVX_INTRINSICS_
    _mm_broadcast_ss(A[0x00], vX)
    _mm_broadcast_ss(A[0x04], vY)
    _mm_broadcast_ss(A[0x08], vZ)
    _mm_broadcast_ss(A[0x0C], vW)
else
    ;;
    ;; Use vW to hold the original row
    ;;
    _mm_store_ps(vW, A[0x00])
    XM_PERMUTE_PS(_mm_store_ps(vX, vW), _MM_SHUFFLE(0,0,0,0))
    XM_PERMUTE_PS(_mm_store_ps(vY, vW), _MM_SHUFFLE(1,1,1,1))
    XM_PERMUTE_PS(_mm_store_ps(vZ, vW), _MM_SHUFFLE(2,2,2,2))
    XM_PERMUTE_PS(vW, _MM_SHUFFLE(3,3,3,3))
endif
    ;;
    ;; Perform the operation on the first row
    ;;
    _mm_mul_ps(vX, B[0x00])
    _mm_mul_ps(vY, B[0x10])
    _mm_mul_ps(vZ, B[0x20])
    _mm_mul_ps(vW, B[0x30])
    ;;
    ;; Perform a binary add to reduce cumulative errors
    ;;
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm0, vX)
    ;;
    ;; Repeat for the other 3 rows
    ;;
ifdef _XM_AVX_INTRINSICS_
    _mm_broadcast_ss(A[0x10], vX)
    _mm_broadcast_ss(A[0x14], vY)
    _mm_broadcast_ss(A[0x18], vZ)
    _mm_broadcast_ss(A[0x1C], vW)
else
    _mm_store_ps(vW, A[0x10])
    XM_PERMUTE_PS(_mm_store_ps(vX, vW), _MM_SHUFFLE(0,0,0,0))
    XM_PERMUTE_PS(_mm_store_ps(vY, vW), _MM_SHUFFLE(1,1,1,1))
    XM_PERMUTE_PS(_mm_store_ps(vZ, vW), _MM_SHUFFLE(2,2,2,2))
    XM_PERMUTE_PS(vW, _MM_SHUFFLE(3,3,3,3))
endif
    _mm_mul_ps(vX, B[0x00])
    _mm_mul_ps(vY, B[0x10])
    _mm_mul_ps(vZ, B[0x20])
    _mm_mul_ps(vW, B[0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm1, vX)
ifdef _XM_AVX_INTRINSICS_
    _mm_broadcast_ss(A[0x20], vX)
    _mm_broadcast_ss(A[0x24], vY)
    _mm_broadcast_ss(A[0x28], vZ)
    _mm_broadcast_ss(A[0x2C], vW)
else
    _mm_store_ps(vW, A[0x20])
    XM_PERMUTE_PS(_mm_store_ps(vX, vW), _MM_SHUFFLE(0,0,0,0))
    XM_PERMUTE_PS(_mm_store_ps(vY, vW), _MM_SHUFFLE(1,1,1,1))
    XM_PERMUTE_PS(_mm_store_ps(vZ, vW), _MM_SHUFFLE(2,2,2,2))
    XM_PERMUTE_PS(vW, _MM_SHUFFLE(3,3,3,3))
endif
    _mm_mul_ps(vX, B[0x00])
    _mm_mul_ps(vY, B[0x10])
    _mm_mul_ps(vZ, B[0x20])
    _mm_mul_ps(vW, B[0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm2, vX)
ifdef _XM_AVX_INTRINSICS_
    _mm_broadcast_ss(A[0x30], vX)
    _mm_broadcast_ss(A[0x34], vY)
    _mm_broadcast_ss(A[0x38], vZ)
    _mm_broadcast_ss(A[0x3C], vW)
else
    _mm_store_ps(vW, A[0x30])
    XM_PERMUTE_PS(_mm_store_ps(vX, vW), _MM_SHUFFLE(0,0,0,0))
    XM_PERMUTE_PS(_mm_store_ps(vY, vW), _MM_SHUFFLE(1,1,1,1))
    XM_PERMUTE_PS(_mm_store_ps(vZ, vW), _MM_SHUFFLE(2,2,2,2))
    XM_PERMUTE_PS(vW, _MM_SHUFFLE(3,3,3,3))
endif
    _mm_mul_ps(vX, B[0x00])
    _mm_mul_ps(vY, B[0x10])
    _mm_mul_ps(vZ, B[0x20])
    _mm_mul_ps(vW, B[0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    ret

XMMatrixMultiply endp

    end
