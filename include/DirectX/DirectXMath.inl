ifndef __DIRECTXMATH_INL
define __DIRECTXMATH_INL

XMVectorSplatConstantInt proto XM_CALLCONV :int32_t {
    movd     xmm0,_1
    shufps   xmm0,xmm0,0
    }

XMLoadInt proto XM_CALLCONV :ptr uint32_t {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    }

XMLoadFloat proto XM_CALLCONV :ptr float {
    _mm_load_ss(xmm0, [_1])
    }

XMLoadInt2 proto XM_CALLCONV :ptr uint32_t {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    }

XMLoadInt2A proto XM_CALLCONV :ptr uint32_t {
    _mm_loadl_epi64(_1)
    }

XMLoadFloat2 proto XM_CALLCONV :ptr XMFLOAT2 {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    }

XMLoadFloat2A proto XM_CALLCONV :ptr XMFLOAT2A {
    _mm_loadl_epi64(_1)
    }

XMLoadSInt2 proto XM_CALLCONV :ptr XMINT2 {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_cvtepi32_ps(xmm0)
    }

XMLoadInt3 proto XM_CALLCONV :ptr uint32_t {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_load_ss(xmm2, [_1+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    }

XMLoadInt3A proto XM_CALLCONV :ptr uint32_t {
    _mm_load_si128([_1])
    _mm_and_si128(xmm0, g_XMMask3)
    }

XMLoadFloat3 proto XM_CALLCONV :ptr XMFLOAT3 {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_load_ss(xmm2, [_1+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    }

XMLoadFloat3A proto XM_CALLCONV :ptr XMFLOAT3A {
    _mm_load_ps(xmm0, [_1])
    _mm_and_ps(xmm0, g_XMMask3)
    }

XMLoadSInt3 proto XM_CALLCONV :ptr XMINT3 {
    _mm_load_ss(xmm0, [_1])
    _mm_load_ss(xmm1, [_1+4])
    _mm_load_ss(xmm2, [_1+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    }

XMLoadInt4 proto XM_CALLCONV :ptr uint32_t {
    _mm_loadu_si128([_1])
    }
XMLoadInt4A proto XM_CALLCONV :ptr uint32_t {
    _mm_load_si128([_1])
    }
XMLoadFloat4 proto XM_CALLCONV :ptr XMFLOAT4 {
    _mm_loadu_ps([_1])
    }
XMLoadFloat4A proto XM_CALLCONV :ptr XMFLOAT4A {
    _mm_load_ps([_1])
    }
XMLoadSInt4 proto XM_CALLCONV :ptr XMINT4 {
    _mm_loadu_si128([_1])
    }

XMLoadFloat4x4 proto XM_CALLCONV :ptr XMFLOAT4X4 {
    _mm_loadu_ps(xmm0, xmmword ptr [_1].XMFLOAT4X4._11)
    _mm_loadu_ps(xmm1, xmmword ptr [_1].XMFLOAT4X4._21)
    _mm_loadu_ps(xmm2, xmmword ptr [_1].XMFLOAT4X4._31)
    _mm_loadu_ps(xmm3, xmmword ptr [_1].XMFLOAT4X4._41)
    }

XMLoadFloat4x4A proto XM_CALLCONV :ptr XMFLOAT4X4 {
    _mm_load_ps(xmm0, xmmword ptr [_1].XMFLOAT4X4._11)
    _mm_load_ps(xmm1, xmmword ptr [_1].XMFLOAT4X4._21)
    _mm_load_ps(xmm2, xmmword ptr [_1].XMFLOAT4X4._31)
    _mm_load_ps(xmm3, xmmword ptr [_1].XMFLOAT4X4._41)
    }

XMStoreInt proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ss([_1], _2)
    }

XMStoreFloat proto XM_CALLCONV :ptr float, :FXMVECTOR {
    _mm_store_ss([_1], _2)
    }

XMStoreInt2 proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ss([_1], _2)
    _mm_store_ss([_1+4], XM_PERMUTE_PS(_2, _MM_SHUFFLE(1, 1, 1, 1)))
    }

XMStoreInt2A proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_storel_epi64([_1], _2)
    }

XMStoreFloat2 proto XM_CALLCONV :ptr XMFLOAT2, :FXMVECTOR {
    _mm_store_ss([_1][0], _2)
    _mm_store_ss([_1][4], XM_PERMUTE_PS(_2, _MM_SHUFFLE(1, 1, 1, 1)))
    }

XMStoreFloat2A proto XM_CALLCONV :ptr XMFLOAT2, :FXMVECTOR {
    _mm_storel_epi64([_1], _2)
    }

XMStoreInt3 proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ps(xmm2, _2)
    _mm_store_ss([_1][0], _2)
    _mm_store_ss([_1][4], XM_PERMUTE_PS(_2, _MM_SHUFFLE(1, 1, 1, 1)))
    _mm_store_ss([_1][8], XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(2, 2, 2, 2)))
    }

XMStoreInt3A proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_storel_epi64([_1][0], _2)
    _mm_store_ss([_1][8], XM_PERMUTE_PS(_2, _MM_SHUFFLE(2, 2, 2, 2)))
    }

XMStoreFloat3 proto XM_CALLCONV :ptr XMFLOAT3, :FXMVECTOR {
    _mm_store_ss([_1][0], _2)
    _mm_store_ss([_1][8], XM_PERMUTE_PS(_mm_store_ps(xmm2, _2), _MM_SHUFFLE(2, 2, 2, 2)))
    _mm_store_ss([_1][4], XM_PERMUTE_PS(_2, _MM_SHUFFLE(1, 1, 1, 1)))
    }

XMStoreFloat3A proto XM_CALLCONV :ptr XMFLOAT3, :FXMVECTOR {
    _mm_storel_epi64(qword ptr [_1], _2)
    _mm_store_ss([_1][8], XM_PERMUTE_PS(_2, _MM_SHUFFLE(2, 2, 2, 2)))
    }

XMStoreInt4 proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_storeu_si128([_1], _2)
    }

XMStoreInt4A proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_si128([_1], _2)
    }

XMStoreFloat4 proto XM_CALLCONV :ptr XMFLOAT4, :FXMVECTOR {
    _mm_storeu_ps([_1], _2)
    }

XMStoreFloat4A proto XM_CALLCONV :ptr XMFLOAT4, :FXMVECTOR {
    _mm_store_ps([_1], _2)
    }

XMStoreFloat4x4 proto XM_CALLCONV :ptr XMFLOAT4X4, :XMVECTOR, :XMVECTOR, :XMVECTOR, :XMVECTOR {
    _mm_storeu_ps([_1][0x00], _2)
    _mm_storeu_ps([_1][0x10], _3)
    _mm_storeu_ps([_1][0x20], _4)
    _mm_storeu_ps([_1][0x30], _5)
    }

XMStoreFloat4x4A proto XM_CALLCONV :ptr XMFLOAT4X4, :XMVECTOR, :XMVECTOR, :XMVECTOR, :XMVECTOR {
    _mm_store_ps([_1][0x00], _2)
    _mm_store_ps([_1][0x10], _3)
    _mm_store_ps([_1][0x20], _4)
    _mm_store_ps([_1][0x30], _5)
    }

XMVectorZero proto XM_CALLCONV {
    _mm_setzero_ps()
    }

XMVectorReplicate proto XM_CALLCONV :float {
    XM_PERMUTE_PS()
    }

XMVectorReplicatePtr proto XM_CALLCONV :ptr float {
    _mm_load_ps1([_1])
    }

XMVectorReplicateInt proto XM_CALLCONV :uint32_t {
    movd xmm0,_1
    XM_PERMUTE_PS()
    }

XMVectorReplicateIntPtr proto XM_CALLCONV :ptr uint32_t {
    _mm_load_ps1([_1])
    }

XMVectorTrueInt proto XM_CALLCONV {
    mov eax,-1
    movd xmm0,eax
    XM_PERMUTE_PS()
    }

XMVectorFalseInt proto XM_CALLCONV {
    _mm_setzero_ps()
    }

XMVectorSplatX proto XM_CALLCONV :FXMVECTOR {
    XM_PERMUTE_PS()
    }
XMVectorSplatY proto XM_CALLCONV :FXMVECTOR {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(1, 1, 1, 1))
    }
XMVectorSplatZ proto XM_CALLCONV :FXMVECTOR {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(2, 2, 2, 2))
    }
XMVectorSplatW proto XM_CALLCONV :FXMVECTOR {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3, 3, 3, 3))
    }

XMVectorSplatOne proto XM_CALLCONV {
    _mm_store_ps(xmm0, g_XMOne)
    }
XMVectorSplatInfinity proto XM_CALLCONV {
    _mm_store_ps(xmm0, g_XMInfinity)
    }
XMVectorSplatQNaN proto XM_CALLCONV {
    _mm_store_ps(xmm0, g_XMQNaN)
    }
XMVectorSplatEpsilon proto XM_CALLCONV {
    _mm_store_ps(xmm0, g_XMEpsilon)
    }
XMVectorSplatSignMask proto XM_CALLCONV {
    mov eax,0x80000000
    movd xmm0,eax
    XM_PERMUTE_PS()
    }

XMVectorGetX proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtss_f32(_1)
    }
XMVectorGetY proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtss_f32(XM_PERMUTE_PS(_1, _MM_SHUFFLE(1,1,1,1)))
    }
XMVectorGetZ proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtss_f32(XM_PERMUTE_PS(_1, _MM_SHUFFLE(2,2,2,2)))
    }
XMVectorGetW proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtss_f32(XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,3,3,3)))
    }

XMVectorGetXPtr proto XM_CALLCONV :ptr float, :FXMVECTOR {
    _mm_store_ss([_1], _2)
    }
XMVectorGetYPtr proto XM_CALLCONV :ptr float, :FXMVECTOR {
    _mm_store_ss([_1], XM_PERMUTE_PS(_2, _MM_SHUFFLE(1,1,1,1)))
    }
XMVectorGetZPtr proto XM_CALLCONV :ptr float, :FXMVECTOR {
    _mm_store_ss([_1], XM_PERMUTE_PS(_2, _MM_SHUFFLE(2,2,2,2)))
    }
XMVectorGetWPtr proto XM_CALLCONV :ptr float, :FXMVECTOR {
    _mm_store_ss([_1], XM_PERMUTE_PS(_2, _MM_SHUFFLE(3,3,3,3)))
    }

XMVectorGetIntX proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtsi128_si32(_1)
    }
XMVectorGetIntY proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtsi128_si32(XM_PERMUTE_PS(_1, _MM_SHUFFLE(1,1,1,1)))
    }
XMVectorGetIntZ proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtsi128_si32(XM_PERMUTE_PS(_1, _MM_SHUFFLE(2,2,2,2)))
    }
XMVectorGetIntW proto XM_CALLCONV :FXMVECTOR {
    _mm_cvtsi128_si32(XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,3,3,3)))
    }

XMVectorGetIntXPtr proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ss([_1], _2)
    }
XMVectorGetIntYPtr proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ss([_1], XM_PERMUTE_PS(_2, _MM_SHUFFLE(1,1,1,1)))
    }
XMVectorGetIntZPtr proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ss([_1], XM_PERMUTE_PS(_2, _MM_SHUFFLE(2,2,2,2)))
    }
XMVectorGetIntWPtr proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR {
    _mm_store_ss([_1], XM_PERMUTE_PS(_2, _MM_SHUFFLE(3,3,3,3)))
    }

XMVectorSetX proto XM_CALLCONV :FXMVECTOR, :float {
    _mm_store_ss(_1, _2)
    }
XMVectorSetY proto XM_CALLCONV :FXMVECTOR, :float {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    _mm_move_ss(_1, _2)
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    }
XMVectorSetZ proto XM_CALLCONV :FXMVECTOR, :float {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    _mm_move_ss(_1, _2)
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    }
XMVectorSetW proto XM_CALLCONV :FXMVECTOR, :float {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    _mm_move_ss(_1, _2)
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    }

XMVectorSetXPtr proto XM_CALLCONV :FXMVECTOR, :ptr float {
    _mm_move_ss(_1, [_2])
    }
XMVectorSetYPtr proto XM_CALLCONV :FXMVECTOR, :ptr float {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    _mm_move_ss(_1, [_2])
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    }
XMVectorSetZPtr proto XM_CALLCONV :FXMVECTOR, :ptr float {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    _mm_move_ss(_1, [_2])
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    }
XMVectorSetWPtr proto XM_CALLCONV :FXMVECTOR, :ptr float {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    _mm_move_ss(_1, [_2])
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    }

XMVectorSetIntX proto XM_CALLCONV :FXMVECTOR, :uint32_t {
    _mm_cvtsi32_si128(xmm1, _2)
    _mm_move_ss(_1, xmm1)
    }
XMVectorSetIntY proto XM_CALLCONV :FXMVECTOR, :uint32_t {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    _mm_cvtsi32_si128(xmm1, _2)
    _mm_move_ss(_1, xmm1)
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    }
XMVectorSetIntZ proto XM_CALLCONV :FXMVECTOR, :uint32_t {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    _mm_cvtsi32_si128(xmm1, _2)
    _mm_move_ss(_1, xmm1)
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    }
XMVectorSetIntW proto XM_CALLCONV :FXMVECTOR, :uint32_t {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    _mm_cvtsi32_si128(xmm1, _2)
    _mm_move_ss(_1, xmm1)
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    }

XMVectorSetIntXPtr proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t {
    _mm_move_ss(_1, [_2])
    }
XMVectorSetIntYPtr proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    _mm_move_ss(_1, [_2])
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,2,0,1))
    }
XMVectorSetIntZPtr proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    _mm_move_ss(_1, [_2])
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(3,0,1,2))
    }
XMVectorSetIntWPtr proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t {
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    _mm_move_ss(_1, [_2])
    XM_PERMUTE_PS(_1, _MM_SHUFFLE(0,2,1,3))
    }

XMVectorSelect proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR {
    _mm_and_ps(xmm1, xmm2)
    _mm_andnot_ps(xmm2, xmm0)
    _mm_or_ps(xmm2, xmm1)
    _mm_store_ps(xmm0, xmm2)
    }

XMVectorSet proto XM_CALLCONV :float, :float, :float, :float {
    unpcklps xmm0,xmm1
    unpcklps xmm2,xmm3
    movlhps  xmm0,xmm2
    }

ifdef _XM_SSE4_INTRINSICS_
XMVectorRound proto XM_CALLCONV :FXMVECTOR {
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    }
endif

XMVectorMergeXY proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_unpacklo_ps(xmm0, xmm1)
    }
XMVectorMergeZW proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_unpackhi_ps(xmm0, xmm1)
    }

XMVectorEqual proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmpeq_ps(xmm0, xmm1)
    }
XMVectorEqualInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmpeq_epi32(xmm0, xmm1)
    }
XMVectorNearEqual proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR {
    _mm_sub_ps(xmm0, xmm1)
    _mm_setzero_ps(xmm1)
    _mm_sub_ps(xmm1, xmm0)
    _mm_max_ps(xmm0, xmm1)
    _mm_cmple_ps(xmm0, xmm2)
    }
XMVectorNotEqual proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmpneq_ps(xmm0, xmm1)
    }
XMVectorNotEqualInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmpeq_epi32(xmm0, xmm1)
    _mm_xor_ps(xmm0, g_XMNegOneMask)
    }
XMVectorGreater proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmpgt_ps(xmm1, xmm0, xmm1)
    _mm_store_ps(xmm0, xmm1)
    }
XMVectorGreaterOrEqual proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmpge_ps(xmm1, xmm0, xmm1)
    _mm_store_ps(xmm0, xmm1)
    }
XMVectorLess proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_cmple_ps(xmm0, xmm1)
    }

XMVectorInBounds proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_store_ps(xmm2, xmm0)
    _mm_cmple_ps(xmm0, xmm1)
    _mm_mul_ps(xmm1, g_XMNegativeOne)
    _mm_cmple_ps(xmm1, xmm2)
    _mm_and_ps(xmm0, xmm1)
    }

XMVectorIsNaN proto XM_CALLCONV :FXMVECTOR {
    _mm_cmpneq_ps(xmm0, xmm0)
    }
XMVectorIsInfinite proto XM_CALLCONV :FXMVECTOR {
    _mm_and_ps(xmm0, g_XMAbsMask)
    _mm_cmpeq_ps(xmm0, g_XMInfinity)
    }

XMVectorMin proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_min_ps(xmm0, xmm1)
    }
XMVectorMax proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_max_ps(xmm0, xmm1)
    }

ifdef _XM_SSE4_INTRINSICS_
XMVectorRound proto XM_CALLCONV :FXMVECTOR {
    _mm_round_ps(xmm0, _MM_FROUND_TO_NEAREST_INT or _MM_FROUND_NO_EXC)
    }
XMVectorTruncate proto XM_CALLCONV :FXMVECTOR {
    _mm_round_ps(xmm0, _MM_FROUND_TO_ZERO or _MM_FROUND_NO_EXC)
    }
XMVectorFloor proto XM_CALLCONV :FXMVECTOR {
    _mm_floor_ps(xmm0)
    }
XMVectorCeiling proto XM_CALLCONV :FXMVECTOR {
    _mm_ceil_ps(xmm0)
    }
XMVector3Dot proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_dp_ps(xmm0, xmm1, 0x7f)
    }
endif

XMVectorClamp proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR {
    _mm_max_ps(xmm0, xmm1)
    _mm_min_ps(xmm0, xmm2)
    }
XMVectorSaturate proto XM_CALLCONV :FXMVECTOR {
    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, g_XMOne)
    }
XMVectorAndInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_and_ps(xmm0, xmm1)
    }
XMVectorAndCInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_andnot_si128(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm1)
    }

XMVectorOrInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_or_si128(xmm0, xmm1)
    }
XMVectorNorInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_or_si128(xmm0, xmm1)
    _mm_andnot_si128(xmm0, g_XMNegOneMask)
    }
XMVectorXorInt proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_xor_si128(xmm0, xmm1)
    }

XMVectorNegate proto XM_CALLCONV :FXMVECTOR {
    _mm_store_ps(xmm1, xmm0)
    _mm_sub_ps(_mm_setzero_ps(), xmm1)
    }

XMVectorAdd proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_add_ps(xmm0, xmm1)
    }
XMVectorSubtract proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_sub_ps(xmm0, xmm1)
    }

XMVectorSum proto XM_CALLCONV :FXMVECTOR {
ifdef _XM_SSE3_INTRINSICS_
    _mm_hadd_ps(xmm0, xmm0)
    _mm_hadd_ps(xmm0, xmm0)
else
    _mm_store_ps(xmm1, xmm0)
    _mm_add_ps(xmm0, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(2, 3, 0, 1)))
    _mm_add_ps(xmm0, XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(1, 0, 3, 2)))
endif
    }

XMVectorMultiply proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_mul_ps(xmm0, xmm1)
    }
XMVectorMultiplyAdd proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR {
    _mm_mul_ps(xmm0, xmm1)
    _mm_add_ps(xmm0, xmm2)
    }
XMVectorDivide proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR {
    _mm_div_ps(xmm0, xmm1)
    }

XMVectorNegativeMultiplySubtract proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR {
    _mm_mul_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm2)
    _mm_sub_ps(xmm0, xmm1)
    }

XMVectorScale proto XM_CALLCONV :FXMVECTOR, :float {
    _mm_set_ps1(xmm1)
    _mm_mul_ps(xmm0, xmm1)
    }

XMVectorReciprocalEst proto XM_CALLCONV :FXMVECTOR {
    _mm_rcp_ps(xmm0)
    }

XMVectorReciprocal proto XM_CALLCONV :FXMVECTOR {
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, g_XMOne)
    _mm_div_ps(xmm0, xmm1)
    }

XMVectorSqrtEst proto XM_CALLCONV :FXMVECTOR {
    _mm_sqrt_ps(xmm0)
    }
XMVectorSqrt proto XM_CALLCONV :FXMVECTOR {
    _mm_sqrt_ps(xmm0)
    }
XMVectorReciprocalSqrtEst proto XM_CALLCONV :FXMVECTOR {
    _mm_rsqrt_ps(xmm0)
    }
XMVectorReciprocalSqrt proto XM_CALLCONV :FXMVECTOR {
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, g_XMOne)
    _mm_div_ps(xmm0, xmm1)
    }


XMVectorAbs proto XM_CALLCONV :FXMVECTOR {
    _mm_store_ps(xmm1, xmm0)
    _mm_sub_ps(_mm_setzero_ps(), xmm1)
    _mm_max_ps(xmm0, xmm1)
    }

XMMatrixIdentity proto XM_CALLCONV {
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
    }

XMMatrixTranslation proto XM_CALLCONV :float, :float, :float {
    XMVectorSet(xmm0, xmm1, xmm2, 1.0)
    _mm_store_ps(xmm3, xmm0)
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    }

XMLoadMatrix proto fastcall :ptr XMMATRIX {
    _mm_store_ps(xmm0, [_1][0x00])
    _mm_store_ps(xmm1, [_1][0x10])
    _mm_store_ps(xmm2, [_1][0x20])
    _mm_store_ps(xmm3, [_1][0x30])
    }

XMStoreMatrix proto fastcall :ptr XMMATRIX {
    _mm_store_ps([_1][0x00], xmm0)
    _mm_store_ps([_1][0x10], xmm1)
    _mm_store_ps([_1][0x20], xmm2)
    _mm_store_ps([_1][0x30], xmm3)
    }

XMMatrixTransposeM proto fastcall :ptr XMMATRIX, :ptr XMMATRIX {
    XMLoadMatrix(_1)
    XMMatrixTranspose(xmm0, xmm1, xmm2, xmm3)
    XMStoreMatrix(_2)
    }


endif
