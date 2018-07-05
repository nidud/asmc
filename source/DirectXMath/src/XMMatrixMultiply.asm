
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixMultiply proc XM_CALLCONV XMTHISPTR, M1:FXMMATRIX, M2:CXMMATRIX

    vX equ <xmm2>
    vY equ <xmm3>
    vZ equ <xmm4>
    vW equ <xmm5>
    p1 equ <[rcx]>
    p2 equ <[rdx]>
    ;;
    ;; Splat the component X,Y,Z then W
    ;;
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss(p1.XMFLOAT4X4._11))
    _mm_store_ps(vY, _mm_broadcast_ss(p1.XMFLOAT4X4._12))
    _mm_store_ps(vZ, _mm_broadcast_ss(p1.XMFLOAT4X4._13))
    _mm_store_ps(vW, _mm_broadcast_ss(p1.XMFLOAT4X4._14))
else
    ;;
    ;; Use vW to hold the original row
    ;;
    _mm_shuffle_ps(vX, p1, _MM_SHUFFLE(0,0,0,0))
    _mm_shuffle_ps(vY, p1, _MM_SHUFFLE(1,1,1,1))
    _mm_shuffle_ps(vZ, p1, _MM_SHUFFLE(2,2,2,2))
    _mm_shuffle_ps(vW, p1, _MM_SHUFFLE(3,3,3,3))
endif
    ;;
    ;; Perform the operation on the first row
    ;;
    _mm_mul_ps(vX, p2[0x00])
    _mm_mul_ps(vY, p2[0x10])
    _mm_mul_ps(vZ, p2[0x20])
    _mm_mul_ps(vW, p2[0x30])
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
    _mm_store_ps(vX, _mm_broadcast_ss(p1.XMFLOAT4X4._21))
    _mm_store_ps(vY, _mm_broadcast_ss(p1.XMFLOAT4X4._22))
    _mm_store_ps(vZ, _mm_broadcast_ss(p1.XMFLOAT4X4._23))
    _mm_store_ps(vW, _mm_broadcast_ss(p1.XMFLOAT4X4._24))
else
    _mm_shuffle_ps(vX, p1[0x10], _MM_SHUFFLE(0,0,0,0))
    _mm_shuffle_ps(vY, p1[0x10], _MM_SHUFFLE(1,1,1,1))
    _mm_shuffle_ps(vZ, p1[0x10], _MM_SHUFFLE(2,2,2,2))
    _mm_shuffle_ps(vW, p1[0x10], _MM_SHUFFLE(3,3,3,3))
endif
    _mm_mul_ps(vX, p2[0x00])
    _mm_mul_ps(vY, p2[0x10])
    _mm_mul_ps(vZ, p2[0x20])
    _mm_mul_ps(vW, p2[0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm1, vX)
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss(p1.XMFLOAT4X4._31))
    _mm_store_ps(vY, _mm_broadcast_ss(p1.XMFLOAT4X4._32))
    _mm_store_ps(vZ, _mm_broadcast_ss(p1.XMFLOAT4X4._33))
    _mm_store_ps(vW, _mm_broadcast_ss(p1.XMFLOAT4X4._34))
else
    _mm_shuffle_ps(vX, p1[0x20], _MM_SHUFFLE(0,0,0,0))
    _mm_shuffle_ps(vY, p1[0x20], _MM_SHUFFLE(1,1,1,1))
    _mm_shuffle_ps(vZ, p1[0x20], _MM_SHUFFLE(2,2,2,2))
    _mm_shuffle_ps(vW, p1[0x20], _MM_SHUFFLE(3,3,3,3))
endif
    _mm_mul_ps(vX, p2[0x00])
    _mm_mul_ps(vY, p2[0x10])
    _mm_mul_ps(vZ, p2[0x20])
    _mm_mul_ps(vW, p2[0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps([rsp+8], vX)
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss(p1.XMFLOAT4X4._41))
    _mm_store_ps(vY, _mm_broadcast_ss(p1.XMFLOAT4X4._42))
    _mm_store_ps(vZ, _mm_broadcast_ss(p1.XMFLOAT4X4._43))
    _mm_store_ps(vW, _mm_broadcast_ss(p1.XMFLOAT4X4._44))
else
    _mm_shuffle_ps(vX, p1[0x30], _MM_SHUFFLE(0,0,0,0))
    _mm_shuffle_ps(vY, p1[0x30], _MM_SHUFFLE(1,1,1,1))
    _mm_shuffle_ps(vZ, p1[0x30], _MM_SHUFFLE(2,2,2,2))
    _mm_shuffle_ps(vW, p1[0x30], _MM_SHUFFLE(3,3,3,3))
endif
    _mm_mul_ps(vX, p2[0x00])
    _mm_mul_ps(vY, p2[0x10])
    _mm_mul_ps(vZ, p2[0x20])
    _mm_mul_ps(vW, p2[0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm3, vX)
    _mm_store_ps(xmm2, [rsp+8])

if _XM_VECTORCALL_
else
endif
    ret

XMMatrixMultiply endp

    end
