ifndef __DIRECTXMATH_INL
__DIRECTXMATH_INL equ <>

inl_XMConvertVectorIntToFloat macro VInt, DivExponent
    _mm_store_ps(xmm0, VInt)
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uScale = 0x3F800000 - (DivExponent << 23)
    ;;
    ;; Splat the scalar value
    ;;
    mov eax,0x3F800000 - (DivExponent shl 23)
    movd xmm1,eax
    _mm_mul_ps(_mm_cvtepi32_ps(), XM_PERMUTE_PS(xmm1))
    retm<xmm0>
    endm

inl_XMConvertVectorFloatToInt macro VFloat, MulExponent

    .assert( MulExponent < 32 )

ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
else
    mov eax,(1 shl MulExponent)
    _mm_cvt_si2ss(xmm1, eax)
    _mm_mul_ps(xmm0, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,0,0,0)))
    ;;
    ;; In case of positive overflow, detect it
    ;;
    ;; Note: cmpltps xmm2,xmm0
    ;;
    _mm_cmpgt_ps(xmm0, _mm_store_ps(xmm2, g_XMMaxInt))
    ;;
    ;; Float to int conversion
    ;;
    _mm_cvttps_epi32(xmm1, xmm0)
    ;;
    ;; If there was positive overflow, set to 0x7FFFFFFF
    ;;
    _mm_and_ps(_mm_store_ps(xmm0, g_XMAbsMask), xmm2)
    _mm_andnot_ps(xmm2, _mm_castsi128_ps(xmm1))
    _mm_or_ps(xmm0, xmm2)
    retm<xmm0>
endif
    endm

inl_XMConvertVectorUIntToFloat macro VUInt, DivExponent

    .assert(DivExponent < 32)

ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
else
    _mm_store_ps(xmm0, VUInt)
    _mm_store_ps(xmm1, xmm0)
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_and_ps(xmm1, g_XMNegativeZero)
    ;;
    ;; Force all values positive
    ;;
    _mm_xor_ps(xmm0, xmm1)
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_srai_epi32(_mm_castps_si128(xmm1), 31)
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(_mm_castsi128_ps(xmm1), g_XMFixUnsigned)
    _mm_add_ps(xmm1, xmm0)
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uint32_t uScale = 0x3F800000U - (DivExponent << 23);
    ;;
    ;; Splat
    ;;
    _mm_set1_epi32(0x3F800000 - (DivExponent shl 23))
    _mm_mul_ps(_mm_castsi128_ps(xmm0), xmm1)
    retm<xmm0>
endif
    endm

inl_XMConvertVectorFloatToUInt macro VFloat, MulExponent
    .assert(MulExponent < 32)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
else
    _mm_store_ps(xmm1, VFloat)
    _mm_set_ps1(_mm_cvtsi32_ss(xmm0, (1 shl MulExponent)))
    _mm_mul_ps(xmm0, xmm1)
    ;;
    ;; Clamp to >=0
    ;;
    _mm_store_ps(xmm1, _mm_max_ps(xmm0, g_XMZero))
    ;;
    ;; Any numbers that are too big, set to 0xFFFFFFFFU
    ;;
    _mm_cmpgt_ps(xmm0, g_XMMaxUInt)
    _mm_store_ps(xmm3, g_XMUnsignedFix)
    ;;
    ;; Too large for a signed integer?
    ;;
    _mm_store_ps(xmm2, xmm1)
    _mm_cmpge_ps(xmm2, xmm3)
    ;;
    ;; Zero for number's lower than 0x80000000, 32768.0f*65536.0f otherwise
    ;;
    _mm_and_ps(xmm3, xmm2)
    ;;
    ;; Perform fixup only on numbers too large (Keeps low bit precision)
    ;;
    _mm_sub_ps(xmm1, xmm3)
    _mm_cvttps_epi32(xmm1)
    ;;
    ;; Convert from signed to unsigned pnly if greater than 0x80000000
    ;;
    _mm_and_ps(xmm2, g_XMNegativeZero)
    _mm_xor_ps(_mm_castsi128_ps(xmm1), xmm2)
    ;;
    ;; On those that are too large, set to 0xFFFFFFFF
    ;;
    _mm_or_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMVectorSetBinaryConstant macro C0, C1, C2, C3
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
else
 ifndef g_vMask1
    .data
    align 16
    g_vMask1 XMVECTORU32 { { { 1, 1, 1, 1 } } }
    .code
 endif
    ;;
    ;; Move the parms to a vector
    ;;
    _mm_set_epi32(C3, C2, C1, C0)
    ;;
    ;; Mask off the low bits
    ;;
    _mm_and_si128(xmm0, g_vMask1)
    ;;
    ;; 0xFFFFFFFF on true bits
    ;;
    _mm_cmpeq_epi32(xmm0, g_vMask1)
    ;;
    ;; 0xFFFFFFFF -> 1.0f, 0x00000000 -> 0.0f
    ;;
    _mm_and_si128(xmm0, g_XMOne)
    _mm_castsi128_ps(xmm0)
    retm<xmm0>
endif
    endm

inl_XMVectorSplatConstant macro IntConstant, DivExponent
    .assert( IntConstant >= -16 && IntConstant <= 15 )
    .assert( DivExponent < 32 )
ifdef _XM_NO_INTRINSICS_
    exitm<inl_XMConvertVectorIntToFloat(_mm_set1_epi32(IntConstant), DivExponent)>
elseifdef _XM_ARM_NEON_INTRINSICS_
else
    ;;
    ;; Splat the int
    ;;
    _mm_store_ps(xmm1, _mm_set1_epi32(IntConstant)))
    ;;
    ;; Convert to a float
    ;;
    _mm_cvtepi32_ps(xmm1)
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uint32_t uScale = 0x3F800000U - (DivExponent << 23);
    ;; Splat the scalar value (It's really a float)
    ;;
    _mm_set1_epi32(0x3F800000 - (DivExponent shl 23))
    ;;
    ;; Multiply by the reciprocal (Perform a right shift by DivExponent)
    ;;
    _mm_mul_ps(_mm_castsi128_ps(xmm0), xmm1)
    retm<xmm0>
endif
    endm

inl_XMVectorSplatConstantInt macro IntConstant
    .assert( IntConstant >= -16 && IntConstant <= 15 )
ifdef _XM_NO_INTRINSICS_
    exitm<_mm_set1_epi32(IntConstant)>
elseifdef _XM_ARM_NEON_INTRINSICS_
else
    _mm_set1_epi32( IntConstant )
    _mm_castsi128_ps(xmm0)
    retm<xmm0>
endif
    endm

inl_XMLoadInt macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_unpacklo_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMLoadFloat macro pSource
    .assert(pSource)
    .assert(!(pSource & 0xF))
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(pSource)
    retm<xmm0>
endif
    endm

inl_XMLoadInt2 macro pSource
    .assert(pSource);
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_unpacklo_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMLoadInt2A macro pSource
    .assert(pSource)
    .assert(!(pSource & 0xF))
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_loadl_epi64(pSource)
    _mm_castsi128_ps(xmm0)
    retm<xmm0>
endif
    endm

inl_XMLoadFloat2 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_unpacklo_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMLoadFloat2A macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_loadl_epi64(pSource)
    _mm_castsi128_ps(xmm0)
    retm<xmm0>
endif
    endm

inl_XMLoadSInt2 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    retm<xmm0>
endif
    endm

inl_XMLoadUInt2 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_store_ps(xmm1, _mm_unpacklo_ps(xmm0, xmm1))
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_and_ps(xmm0, g_XMNegativeZero)
    ;;
    ;; Force all values positive
    ;;
    _mm_xor_ps(xmm1, xmm0)
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(_mm_castps_si128(xmm1))
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_srai_epi32(_mm_castps_si128(xmm0), 31)
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(_mm_castsi128_ps(xmm0), g_XMFixUnsigned)
    _mm_add_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMLoadInt3 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_load_ss(xmm2, pSource+8)
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    retm<xmm0>
endif
    endm

inl_XMLoadInt3A macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    ;;
    ;; Reads an extra integer which is zero'd
    ;;
    _mm_load_si128(xmm0, pSource)
    _mm_and_si128(xmm0, g_XMMask3)
    _mm_castsi128_ps(xmm0)
    retm<xmm0>
endif
    endm

inl_XMLoadFloat3 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_load_ss(xmm2, pSource+8)
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    retm<xmm0>
endif
    endm

inl_XMLoadFloat3A macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    ;;
    ;; Reads an extra float which is zero'd
    ;;
    _mm_load_ps(pSource)
    _mm_and_ps(xmm0, g_XMMask3)
    retm<xmm0>
endif
    endm

inl_XMLoadSInt3 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_load_ss(xmm2, pSource+8)
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    retm<xmm0>
endif
    endm

inl_XMLoadUInt3 macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(xmm0, pSource)
    _mm_load_ss(xmm1, pSource+4)
    _mm_load_ss(xmm2, pSource+8)
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_store_ps(xmm1, _mm_movelh_ps(xmm0, xmm2))
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_and_ps(xmm1, g_XMNegativeZero)
    ;;
    ;; Force all values positive
    ;;
    _mm_xor_ps(xmm0, xmm1)
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_srai_epi32(_mm_castps_si128(xmm1), 31)
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(_mm_castsi128_ps(xmm1), g_XMFixUnsigned)
    _mm_add_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMLoadInt4 macro ptr_uint32_t
    exitm<_mm_castsi128_ps(_mm_loadu_si128(ptr_uint32_t))>
    endm
inl_XMLoadInt4A macro ptr_uint32_t
    exitm<_mm_castsi128_ps(_mm_load_si128(ptr_uint32_t))>
    endm
inl_XMLoadFloat4 macro ptr_XMFLOAT4
    exitm<_mm_loadu_ps(ptr_XMFLOAT4)>
    endm

inl_XMLoadFloat4A macro ptr_XMFLOAT4A
    exitm<_mm_load_ps(ptr_XMFLOAT4A)>
    endm
inl_XMLoadSInt4 macro ptr_XMINT4
    exitm<_mm_cvtepi32_ps(_mm_loadu_si128(ptr_XMINT4))>
    endm
inl_XMLoadUInt4 macro ptr_XMUINT4
ifdef _XM_NO_INTRINSICS_
    exitm<ptr_XMUINT4>
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_store_ps(xmm2, _mm_loadu_si128(ptr_XMUINT4))
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_store_ps(xmm3, _mm_and_ps(_mm_castsi128_ps(xmm0), g_XMNegativeZero))
    ;;
    ;; Force all values positive
    ;;
    _mm_store_ps(xmm1, _mm_xor_ps(_mm_castsi128_ps(xmm2), xmm3))
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(_mm_castps_si128(xmm1))
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_store_ps(xmm0, _mm_srai_epi32(_mm_castps_si128(xmm3), 31))
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(_mm_castsi128_ps(xmm0), g_XMFixUnsigned)
    _mm_add_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

inl_XMVectorSet macro x, y, z, w
ifdef _XM_NO_INTRINSICS_
    exitm<_mm_set_ps( w, z, y, x )>
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    exitm<_mm_set_ps( w, z, y, x )>
endif
    endm

inl_XMVectorSelect macro V1:=<xmm0>, V2:=<xmm1>, Control:=<xmm2>
    ifidn <Control>,<xmm0>
	_mm_andnot_ps(Control, V1)
    else
	if _MM_ISXMM(Control)
	    _mm_store_ps(xmm0, _mm_andnot_ps(Control, V1))
	else
	    _mm_andnot_ps(Control, V1)
	endif
    endif
    ifidn <V2>,<xmm1>
	_mm_and_ps(xmm1, xmm0)
    else
	_mm_store_ps(xmm1, _mm_and_ps(V2, xmm0) )
    endif
    exitm<_mm_or_ps(xmm0, xmm1)>
    endm

inl_XMVectorNegate macro x:req
    _mm_store_ps(xmm1, x)
    exitm<_mm_sub_ps(_mm_setzero_ps(), xmm1)>
    endm

inl_XMVectorSubtract	equ <_mm_sub_ps>

inl_XMVector3Dot macro V1:=<xmm0>, V2:=<xmm1>
ifdef _XM_SSE4_INTRINSICS_
    ifidn <V1>,<xmm0>
	exitm<_mm_dp_ps( V1, V2, 0x7f )>
    endif
    if not _MM_ISXMM(V1)
	exitm<_mm_dp_ps( V1, V2, 0x7f )>
    endif
    _mm_store_ps(xmm0, _mm_dp_ps( V1, V2, 0x7f ) )
elseifdef _XM_SSE3_INTRINSICS_
    ifidn <V1>,<xmm0>
	_mm_mul_ps(V1, V2)
    else
	if _MM_ISXMM(V1)
	    _mm_store_ps(xmm0, _mm_mul_ps(V1, V2))
	else
	    _mm_mul_ps(V1, V2)
	endif
    endif
    _mm_and_ps(xmm0, g_XMMask3)
    _mm_hadd_ps(xmm0, xmm0)
    _mm_hadd_ps(xmm0, xmm0)
elseifdef _XM_SSE_INTRINSICS_
    ifidn <V1>,<xmm0>
	_mm_mul_ps(V1, V2)
    else
	if _MM_ISXMM(V1)
	    _mm_store_ps(xmm0, _mm_mul_ps(V1, V2))
	else
	    _mm_mul_ps(V1, V2)
	endif
    endif
    _mm_store_ps(xmm2, xmm0)
    _mm_shuffle_ps(xmm2, xmm0, _MM_SHUFFLE(2,1,2,1))
    _mm_add_ss(xmm0, xmm2)
    XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(1,1,1,1))
    _mm_add_ss(xmm0, xmm2)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,0,0,0))
endif
    retm<xmm0>
    endm

inl_XMVector3Cross macro V1:=<xmm0>, V2:=<xmm1>
    _mm_store_ps(xmm0, V1)
    _mm_store_ps(xmm1, V2)
    _mm_store_ps(xmm2, XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,2,1)))
    _mm_store_ps(xmm3, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3,1,0,2)))
    _mm_store_ps(xmm0, xmm2)
    _mm_store_ps(xmm1, xmm3)
    _mm_mul_ps(xmm0, xmm1)
    _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(3,0,2,1))
    _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(3,1,0,2))
    _mm_mul_ps(xmm2, xmm3)
    _mm_sub_ps(xmm0, xmm2)
    _mm_and_ps(xmm0, g_XMMask3)
    retm<xmm0>
    endm

inl_XMVector3Normalize macro V:=<xmm0>
ifdef _XM_SSE4_INTRINSICS_
elseifdef _XM_SSE3_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_store_ps(xmm0, V)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, _mm_mul_ps(xmm1, xmm0))
    _mm_shuffle_ps(xmm2, xmm1, _MM_SHUFFLE(2,1,2,1))
    _mm_add_ss(xmm1, xmm2)
    _mm_add_ss(xmm1, XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(1,1,1,1)))
    _mm_setzero_ps(xmm2)
    _mm_sqrt_ps(xmm3, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,0,0,0)))
    _mm_cmpneq_ps(xmm1, g_XMInfinity)
    _mm_div_ps(xmm0, xmm3)
    _mm_cmpneq_ps(xmm2, xmm3)
    _mm_and_ps(xmm0, xmm2)
    _mm_andnot_ps(_mm_store_ps(xmm2, xmm1), g_XMQNaN)
    _mm_and_ps(xmm1, xmm0)
    _mm_or_ps(_mm_store_ps(xmm0, xmm2), xmm1)
    retm<xmm0>
endif
    endm

inl_XMMatrixTranspose macro M, O
    ifnb <M>
	movaps xmm2,M.r[0x00]
	movaps xmm3,M.r[0x20]
	movaps xmm0,M.r[0x00]
	shufps xmm0,M.r[0x10],_MM_SHUFFLE(3,2,3,2)
	movaps xmm1,M.r[0x20]
	shufps xmm1,M.r[0x30],_MM_SHUFFLE(3,2,3,2)
	movhps xmm2,QWORD PTR M.r[0x10]
	movhps xmm3,QWORD PTR M.r[0x30]
	movaps xmm4,xmm2
	shufps xmm2,xmm3,_MM_SHUFFLE(3,1,3,1)
	ifnb <O>
	    movaps O.r[0x10],xmm2
	else
	    movaps xmm5,xmm2
	endif
	movaps xmm2,xmm0
	shufps xmm4,xmm3,_MM_SHUFFLE(2,0,2,0)
	shufps xmm2,xmm1,_MM_SHUFFLE(2,0,2,0)
	shufps xmm0,xmm1,_MM_SHUFFLE(3,1,3,1)
	ifnb <O>
	    movaps O.r[0x00],xmm4
	    movaps O.r[0x20],xmm2
	    movaps O.r[0x30],xmm0
	else
	    movaps xmm3,xmm0
	    movaps xmm0,xmm4
	    movaps xmm1,xmm5
	endif
    else
	movaps xmm4,xmm2
	movaps xmm5,xmm0
	movlhps xmm0,xmm1
	movlhps xmm2,xmm3
	shufps xmm5,xmm1,_MM_SHUFFLE(3,2,3,2)
	shufps xmm4,xmm3,_MM_SHUFFLE(3,2,3,2)
	movaps xmm1,xmm0
	shufps xmm1,xmm2,_MM_SHUFFLE(3,1,3,1)
	shufps xmm0,xmm2,_MM_SHUFFLE(2,0,2,0)
	movaps xmm3,xmm5
	shufps xmm5,xmm4,_MM_SHUFFLE(2,0,2,0)
	shufps xmm3,xmm4,_MM_SHUFFLE(3,1,3,1)
	movaps xmm2,xmm5
    endif
    exitm<>
    endm

inl_XMVector3Transform macro V, M
    _mm_store_ps(xmm0, V)
    _mm_store_ps(xmm2, xmm0)
    _mm_store_ps(xmm0, XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0,0,0,0)))
    _mm_store_ps(xmm4, _mm_mul_ps(xmm0, M.r[0*16]))
    _mm_store_ps(xmm3, xmm2)
    _mm_store_ps(xmm3, XM_PERMUTE_PS(xmm3, _MM_SHUFFLE(1,1,1,1)))
    _mm_store_ps(xmm3, _mm_mul_ps(xmm3, M.r[1*16]))
    _mm_store_ps(xmm4, _mm_add_ps(xmm4, xmm3))
    _mm_store_ps(xmm3, XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(2,2,2,2)))
    _mm_store_ps(xmm3, _mm_mul_ps(xmm3, M.r[2*16]))
    _mm_store_ps(xmm4, _mm_add_ps(xmm4, xmm3))
    _mm_store_ps(xmm0, _mm_add_ps(xmm4, M.r[3*16]))
    retm<xmm0>
    endm

inl_XMMatrixMultiply macro M1, M2
local vX,vY,vZ,vW
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
ifdifi <M1>,<rcx>
    lea rcx,M1
endif
ifdifi <M2>,<rdx>
    lea rdx,M2
endif
    vX equ <xmm2>
    vY equ <xmm3>
    vZ equ <xmm4>
    vW equ <xmm5>
    ;;
    ;; Splat the component X,Y,Z then W
    ;;
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss([rcx].XMFLOAT4X4._11))
    _mm_store_ps(vY, _mm_broadcast_ss([rcx].XMFLOAT4X4._12))
    _mm_store_ps(vZ, _mm_broadcast_ss([rcx].XMFLOAT4X4._13))
    _mm_store_ps(vW, _mm_broadcast_ss([rcx].XMFLOAT4X4._14))
else
    ;;
    ;; Use vW to hold the original row
    ;;
    _mm_store_ps(vX, XM_PERMUTE_PS([rcx], _MM_SHUFFLE(0,0,0,0)))
    _mm_store_ps(vY, XM_PERMUTE_PS([rcx], _MM_SHUFFLE(1,1,1,1)))
    _mm_store_ps(vZ, XM_PERMUTE_PS([rcx], _MM_SHUFFLE(2,2,2,2)))
    _mm_store_ps(vW, XM_PERMUTE_PS([rcx], _MM_SHUFFLE(3,3,3,3)))
endif
    ;;
    ;; Perform the operation on the first row
    ;;
    _mm_mul_ps(vX, [rdx][0x00])
    _mm_mul_ps(vY, [rdx][0x10])
    _mm_mul_ps(vZ, [rdx][0x20])
    _mm_mul_ps(vW, [rdx][0x30])
    ;;
    ;; Perform a binary add to reduce cumulative errors
    ;;
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm6, vX)
    ;;
    ;; Repeat for the other 3 rows
    ;;
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss([rcx].XMFLOAT4X4._21))
    _mm_store_ps(vY, _mm_broadcast_ss([rcx].XMFLOAT4X4._22))
    _mm_store_ps(vZ, _mm_broadcast_ss([rcx].XMFLOAT4X4._23))
    _mm_store_ps(vW, _mm_broadcast_ss([rcx].XMFLOAT4X4._24))
else
    _mm_store_ps(vX, XM_PERMUTE_PS([rcx][0x10], _MM_SHUFFLE(0,0,0,0)))
    _mm_store_ps(vY, XM_PERMUTE_PS([rcx][0x10], _MM_SHUFFLE(1,1,1,1)))
    _mm_store_ps(vZ, XM_PERMUTE_PS([rcx][0x10], _MM_SHUFFLE(2,2,2,2)))
    _mm_store_ps(vW, XM_PERMUTE_PS([rcx][0x10], _MM_SHUFFLE(3,3,3,3)))
endif
    _mm_mul_ps(vX, [rdx][0x00])
    _mm_mul_ps(vY, [rdx][0x10])
    _mm_mul_ps(vZ, [rdx][0x20])
    _mm_mul_ps(vW, [rdx][0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm7, vX)
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss([rcx].XMFLOAT4X4._31))
    _mm_store_ps(vY, _mm_broadcast_ss([rcx].XMFLOAT4X4._32))
    _mm_store_ps(vZ, _mm_broadcast_ss([rcx].XMFLOAT4X4._33))
    _mm_store_ps(vW, _mm_broadcast_ss([rcx].XMFLOAT4X4._34))
else
    _mm_store_ps(vX,  XM_PERMUTE_PS([rcx][0x20], _MM_SHUFFLE(0,0,0,0)))
    _mm_store_ps(vY,  XM_PERMUTE_PS([rcx][0x20], _MM_SHUFFLE(1,1,1,1)))
    _mm_store_ps(vZ,  XM_PERMUTE_PS([rcx][0x20], _MM_SHUFFLE(2,2,2,2)))
    _mm_store_ps(vW,  XM_PERMUTE_PS([rcx][0x20], _MM_SHUFFLE(3,3,3,3)))
endif
    _mm_mul_ps(vX, [rdx][0x00])
    _mm_mul_ps(vY, [rdx][0x10])
    _mm_mul_ps(vZ, [rdx][0x20])
    _mm_mul_ps(vW, [rdx][0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm1, vX)
ifdef _XM_AVX_INTRINSICS_
    _mm_store_ps(vX, _mm_broadcast_ss([rcx].XMFLOAT4X4._41))
    _mm_store_ps(vY, _mm_broadcast_ss([rcx].XMFLOAT4X4._42))
    _mm_store_ps(vZ, _mm_broadcast_ss([rcx].XMFLOAT4X4._43))
    _mm_store_ps(vW, _mm_broadcast_ss([rcx].XMFLOAT4X4._44))
else
    _mm_store_ps(vX,  XM_PERMUTE_PS([rcx][0x30], _MM_SHUFFLE(0,0,0,0)))
    _mm_store_ps(vY,  XM_PERMUTE_PS([rcx][0x30], _MM_SHUFFLE(1,1,1,1)))
    _mm_store_ps(vZ,  XM_PERMUTE_PS([rcx][0x30], _MM_SHUFFLE(2,2,2,2)))
    _mm_store_ps(vW,  XM_PERMUTE_PS([rcx][0x30], _MM_SHUFFLE(3,3,3,3)))
endif
    _mm_mul_ps(vX, [rdx][0x00])
    _mm_mul_ps(vY, [rdx][0x10])
    _mm_mul_ps(vZ, [rdx][0x20])
    _mm_mul_ps(vW, [rdx][0x30])
    _mm_add_ps(vX, vZ)
    _mm_add_ps(vY, vW)
    _mm_add_ps(vX, vY)
    _mm_store_ps(xmm3, vX)
    _mm_store_ps(xmm2, xmm1)
    _mm_store_ps(xmm0, xmm6)
    _mm_store_ps(xmm1, xmm7)
    exitm<>
endif
    endm

inl_XMMatrixIdentity macro M
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
    ifnb <M>
	_mm_store_ps(M.r[0*16], xmm0)
	_mm_store_ps(M.r[1*16], xmm1)
	_mm_store_ps(M.r[2*16], xmm2)
	_mm_store_ps(M.r[3*16], xmm3)
    endif
    exitm<>
    endm

inl_XMMatrixSet macro m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33
    _mm_set_epi32(xmm0, m00, m01, m02, m03)
    _mm_set_epi32(xmm1, m10, m11, m12, m13)
    _mm_set_epi32(xmm2, m20, m21, m22, m23)
    _mm_set_epi32(xmm3, m30, m31, m32, m33)
    exitm<>
    endm

inl_XMMatrixTranslation macro OffsetX, OffsetY, OffsetZ, M
ifdef _XM_NO_INTRINSICS_
elseif defined(_XM_SSE_INTRINSICS_) or defined(_XM_ARM_NEON_INTRINSICS_)
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_set_epi32(xmm3, OffsetX, OffsetY, OffsetZ, 1.0 )
    ifnb <M>
     _mm_store_ps(M.r[0*16], xmm0)
     _mm_store_ps(M.r[1*16], xmm1)
     _mm_store_ps(M.r[2*16], xmm2)
     _mm_store_ps(M.r[3*16], xmm3)
    endif
    exitm<>
endif
    endm

inl_XMMatrixScaling macro ScaleX, ScaleY, ScaleZ, M
    _mm_set_epi32(xmm0, 0, 0, 0, ScaleX)
    _mm_set_epi32(xmm1, 0, 0, ScaleY, 0)
    _mm_set_epi32(xmm2, 0, ScaleZ, 0, 0)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
    ifnb <M>
     _mm_store_ps(M.r[0*16], xmm0)
     _mm_store_ps(M.r[1*16], xmm1)
     _mm_store_ps(M.r[2*16], xmm2)
     _mm_store_ps(M.r[3*16], xmm3)
    endif
    retm<xmm0>
    endm

inl_XMMatrixTranslationFromVector macro V, M
    _mm_store_ps(xmm1, V)
    _mm_store_ps(xmm0, g_XMIdentityR3.v)
    _mm_store_ps(xmm2, g_XMSelect1110.v)
    _mm_store_ps(xmm3, inl_XMVectorSelect(xmm0, xmm1, xmm2))
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    ifnb <M>
     _mm_store_ps(M.r[0*16], xmm0)
     _mm_store_ps(M.r[1*16], xmm1)
     _mm_store_ps(M.r[2*16], xmm2)
     _mm_store_ps(M.r[3*16], xmm3)
    endif
    retm<xmm0>
    endm

inl_XMMatrixRotationY macro V
    _mm_store_ps(xmm0, V)
    inl_XMScalarSinCos(xmm0)
    _mm_shuffle_ps(xmm0, xmm1, _MM_SHUFFLE(3,0,3,0))
    _mm_store_ps(xmm2, xmm0)
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    _mm_mul_ps(xmm0, g_XMNegateZ)
    _mm_store_ps(xmm1, g_XMIdentityR1)
    _mm_store_ps(xmm3, g_XMIdentityR3)
    retm<>
    endm

inl_XMMatrixLookAtRH macro EyePosition, FocusPosition, UpDirection
    _mm_store_ps(xmm0, EyePosition)
    _mm_store_ps(xmm1, FocusPosition)
    _mm_store_ps(xmm2, UpDirection)
    _mm_store_ps(xmm3 xmm0)
    inl_XMVectorSubtract(xmm3, xmm1)
    inl_XMMatrixLookToLH(xmm0, xmm3, xmm2)
    retm<xmm0>
    endm

inl_XMMatrixLookToLH macro EyePosition, EyeDirection, UpDirection

    _mm_store_ps(xmm0, EyePosition)
    _mm_store_ps(xmm1, EyeDirection)
    _mm_store_ps(xmm2, UpDirection)

    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, xmm2)
    _mm_store_ps(xmm5, inl_XMVector3Normalize(xmm1))
    _mm_store_ps(xmm0, xmm7)
    _mm_store_ps(xmm1, xmm5)
    _mm_store_ps(xmm4, inl_XMVector3Normalize(inl_XMVector3Cross(xmm0, xmm1)))
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm5)
    _mm_store_ps(xmm3, inl_XMVector3Cross(xmm0, xmm1))
    _mm_store_ps(xmm6, _mm_sub_ps( _mm_setzero_ps(), xmm6 ))
    _mm_store_ps(xmm7, inl_XMVector3Dot(_mm_store_ps(xmm0, xmm4), _mm_store_ps(xmm1, xmm6)))
    _mm_store_ps(xmm1, inl_XMVector3Dot(_mm_store_ps(xmm0, xmm3), _mm_store_ps(xmm1, xmm6)))
    _mm_store_ps(xmm6, inl_XMVector3Dot(_mm_store_ps(xmm0, xmm5), _mm_store_ps(xmm1, xmm6)))
    _mm_store_ps(xmm3, inl_XMVectorSelect(xmm1, xmm3, g_XMSelect1110.v))
    _mm_store_ps(xmm7, inl_XMVectorSelect(xmm7, xmm4, g_XMSelect1110.v))
    _mm_store_ps(xmm6, inl_XMVectorSelect(xmm6, xmm5, g_XMSelect1110.v))
    _mm_store_ps(xmm0, xmm7)
    _mm_store_ps(xmm2, _mm_shuffle_ps(xmm0, xmm3, _MM_SHUFFLE(1,0,1,0)))
    _mm_store_ps(xmm3, _mm_shuffle_ps(xmm7, xmm3, _MM_SHUFFLE(3,2,3,2)))
    _mm_store_ps(xmm5, g_XMIdentityR3.v)
    _mm_store_ps(xmm7, xmm6)
    _mm_store_ps(xmm4, _mm_shuffle_ps(xmm6, xmm5, _MM_SHUFFLE(1,0,1,0)))
    _mm_store_ps(xmm5, _mm_shuffle_ps(xmm7, xmm5, _MM_SHUFFLE(3,2,3,2)))
    _mm_store_ps(xmm0, xmm2)
    _mm_shuffle_ps(xmm0, xmm3, _MM_SHUFFLE(2,0,2,0))
    _mm_store_ps(xmm1, _mm_shuffle_ps(xmm2, xmm3,_MM_SHUFFLE(3,1,3,1)))
    _mm_store_ps(xmm2, xmm4)
    _mm_shuffle_ps(xmm2, xmm5, _MM_SHUFFLE(2,0,2,0))
    _mm_store_ps(xmm3, _mm_shuffle_ps(xmm4, xmm5, _MM_SHUFFLE(3,1,3,1)))
    retm<xmm0>
    endm

inl_XMMatrixLookAtLH macro EyePosition, FocusPosition, UpDirection
    _mm_store_ps(xmm0, EyePosition)
    _mm_store_ps(xmm1, FocusPosition)
    _mm_store_ps(xmm2, UpDirection)
    _mm_sub_ps(xmm1, xmm0)
    inl_XMMatrixLookToLH(xmm0, xmm1, xmm2)
    retm<xmm0>
    endm

inl_XMScalarSinCos macro Value
    ;
    ; uses xmm0..3
    ;
    _mm_store_ps(xmm0, Value)
    ;
    ; Map Value to y in [-pi,pi], x = 2*pi*quotient + remainder.
    ;
    _mm_move_sd(xmm2, FLT8(XM_1DIV2PI))
    _mm_setzero_ps(xmm1)
    comiss xmm0,xmm1

    _mm_cvtss_sd(xmm1, xmm0)
    _mm_mul_sd(xmm2, xmm1)
    _mm_cvtsd_ss(xmm2, xmm2)

    _mm_move_ss(xmm3, FLT4(0.5))
    .ifnb
	_mm_add_ss(xmm2, xmm3)
    .else
	_mm_sub_ss(xmm2, xmm3)
    .endif
    _mm_setzero_ps(xmm0)
    _mm_cvt_si2ss(xmm0, _mm_cvtt_ss2si(xmm2))

    _mm_cvtss_sd(xmm0, xmm0)
    _mm_mul_sd(xmm0, FLT8(XM_2PI))
    _mm_setzero_ps(xmm2)
    _mm_sub_sd(xmm1, xmm0)
    _mm_setzero_ps(xmm0)
    _mm_cvtsd_ss(xmm0, xmm1)
    _mm_cvtss_sd(xmm2, xmm0)
    ;
    ; Map y to [-pi/2,pi/2] with sin(y) = sin(Value).
    ;
    comisd xmm2,FLT8(XM_PIDIV2)
    .ifa
	_mm_move_sd(xmm1, FLT8(XM_PI))
	_mm_setzero_ps(xmm0)
	_mm_sub_sd(xmm1, xmm2)
	_mm_move_ss(xmm3, FLT4(-1.0))
	_mm_cvtsd_ss(xmm0, xmm1)
    .else
	_mm_move_sd(xmm1, FLT8(-XM_PIDIV2))
	comisd xmm1,xmm2
	.ifna
	    _mm_move_ss(xmm3, FLT4(1.0))
	    _mm_store_ps(xmm2, xmm3)
	.else
	    _mm_move_sd(xmm1, FLT8(-XM_PI))
	    _mm_setzero_ps(xmm0)
	    _mm_move_ss(xmm3, FLT4(-1.0))
	    _mm_sub_sd(xmm1, xmm2)
	    _mm_cvtsd_ss(xmm0, xmm1)
	.endif
    .endif
    _mm_store_ps(xmm2, xmm0)
    _mm_store_ps(xmm1, _mm_mul_ss(xmm0, xmm0))
    ;
    ; 11-degree minimax approximation
    ;
    _mm_move_ss(xmm0, FLT4(-2.3889859e-08))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), FLT4(2.7525562e-06))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm1), FLT4(0.00019840874))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), FLT4(0.0083333310))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm1), FLT4(0.16666667))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), FLT4(1.0))
    _mm_store_ps(xmm2,_mm_mul_ss(xmm0, xmm2))
    ;
    ; 10-degree minimax approximation
    ;
    _mm_move_ss(xmm0, FLT4(-2.6051615e-07))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), FLT4(2.4760495e-05))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm1), FLT4(0.0013888378))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), FLT4(0.041666638))
    _mm_sub_ss(_mm_mul_ss(xmm0, xmm1), FLT4(0.5))
    _mm_add_ss(_mm_mul_ss(xmm0, xmm1), FLT4(1.0))

    _mm_store_ps(xmm1, xmm3)
    _mm_mul_ss(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm2)
    retm<>
    endm

inl_XMMatrixPerspectiveFovLH macro FovAngleY, AspectRatio, NearZ, FarZ, M

    _MM_STORE_SS(xmm0, FovAngleY)
    _MM_STORE_SS(xmm5, AspectRatio)
    _MM_STORE_SS(xmm7, NearZ)
    _MM_STORE_SS(xmm6, FarZ)

    inl_XMScalarSinCos(_mm_mul_ss(xmm0, _MM_STORE_SS(xmm4, 0.5)))

    _mm_move_ss(xmm3, xmm0)
    _mm_div_ss(xmm3, xmm1)
    _mm_store_ps(xmm0, xmm6)
    _mm_sub_ss(xmm0, xmm7)
    _mm_div_ss(xmm6, xmm0)
    _mm_store_ps(xmm0, xmm3)
    _mm_div_ss(xmm0, xmm5)
    _mm_store_ps(xmm1, xmm6)
    _mm_xor_ps(xmm1, _mm_get_epi32(0x80000000, 0, 0, 0))
    _mm_mul_ss(xmm1, xmm7)
    _mm_unpacklo_ps(xmm6, xmm1)
    _mm_setzero_ps(xmm1)
    _mm_store_ps(xmm2, xmm1)
    _mm_unpacklo_ps(xmm0, xmm3)
    _mm_movelh_ps(xmm0, xmm6)
    _mm_move_ss(xmm2, xmm0)
    ifnb <M>
	_mm_store_ps(M.r[0*16], xmm2)
    else
	_mm_store_ps(xmm4, xmm2)
    endif
    _mm_store_ps(xmm2, g_XMMaskY)
    _mm_and_ps(xmm2, xmm0)
    _mm_shuffle_ps(xmm0, g_XMIdentityR3, _MM_SHUFFLE(3,2,3,2))
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(3,0,0,0))
    ifnb <M>
	_mm_store_ps(M.r[1*16], xmm2)
	_mm_store_ps(M.r[2*16], xmm1)
    else
	_mm_store_ps(xmm5, xmm1)
    endif
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(2,1,0,0))
    ifnb <M>
	_mm_store_ps(M.r[3*16], xmm1)
    else
	_mm_store_ps(xmm3, xmm1)
	_mm_store_ps(xmm0, xmm4)
	_mm_store_ps(xmm1, xmm2)
	_mm_store_ps(xmm2, xmm5)
    endif
    exitm<>
    endm


endif
