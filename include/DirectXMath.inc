.pragma list(push, 0)

ifndef __DIRECTXMATH_INC
__DIRECTXMATH_INC equ <>

include libc.inc

DIRECTX_MATH_VERSION	equ 312

ifndef __PE__
includelib directxmath.lib
endif

ifdef _MSC_VER
if _MSC_VER LT 1200 ; 1800
 .err <DirectX Math requires Visual C++ 2013 or later.>
endif
endif

if defined(_MSC_VER) and \
   not defined(_M_IX86_FP) and \
   not defined(_XM_NO_INTRINSICS_) and \
   not defined(_XM_VECTORCALL_)
_XM_VECTORCALL_		equ 1
else
_XM_VECTORCALL_		equ 0
endif

if _XM_VECTORCALL_
XM_CALLCONV		equ <vectorcall>
else
XM_CALLCONV		equ <fastcall>
endif

if defined(_MSC_VER) and (_MSC_FULL_VER LT 190023506)
XM_CONST		equ <>
XM_CONSTEXPR		equ <>
else
XM_CONST		equ <>
XM_CONSTEXPR		equ <>
endif

ifndef XM_DEPRECATED
XM_DEPRECATED		equ <__declspec(deprecated("This is deprecated and will be removed in a future version."))>
endif

if not defined(_XM_AVX2_INTRINSICS_) and defined(__AVX2__) and not defined(_XM_NO_INTRINSICS_)
_XM_AVX2_INTRINSICS_	equ <>
endif

if not defined(_XM_FMA3_INTRINSICS_) and defined(_XM_AVX2_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
_XM_FMA3_INTRINSICS_	equ <>
endif

if not defined(_XM_F16C_INTRINSICS_) and defined(_XM_AVX2_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
_XM_F16C_INTRINSICS_	equ <>
endif

if defined(_XM_FMA3_INTRINSICS_) and not defined(_XM_AVX_INTRINSICS_)
_XM_AVX_INTRINSICS_	equ <>
endif

if defined(_XM_F16C_INTRINSICS_) and not defined(_XM_AVX_INTRINSICS_)
_XM_AVX_INTRINSICS_	equ <>
endif

if not defined(_XM_AVX_INTRINSICS_) and defined(__AVX__) and not defined(_XM_NO_INTRINSICS_)
_XM_AVX_INTRINSICS_	equ <>
endif

if defined(_XM_AVX_INTRINSICS_) and not defined(_XM_SSE4_INTRINSICS_)
_XM_SSE4_INTRINSICS_	equ <>
endif

if defined(_XM_SSE4_INTRINSICS_) and not defined(_XM_SSE3_INTRINSICS_)
_XM_SSE3_INTRINSICS_	equ <>
endif

if defined(_XM_SSE3_INTRINSICS_) and not defined(_XM_SSE_INTRINSICS_)
_XM_SSE_INTRINSICS_	equ <>
endif

if not defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
if defined(_M_IX86) OR defined(_M_X64)
_XM_SSE_INTRINSICS_	equ <>
elseifndef _XM_NO_INTRINSICS_
 .err <DirectX Math does not support this target>
endif
endif

if not defined(_XM_NO_XMVECTOR_OVERLOADS_) and defined(__clang__)
_XM_NO_XMVECTOR_OVERLOADS_ equ 1
endif

include math.inc
include float.inc
include malloc.inc
ifndef _XM_NO_INTRINSICS_
include intrin.inc
ifdef _XM_SSE_INTRINSICS_
include xmmintrin.inc
include emmintrin.inc
ifdef _XM_SSE3_INTRINSICS_
include pmmintrin.inc
endif
ifdef _XM_SSE4_INTRINSICS_
include smmintrin.inc
endif
ifdef _XM_AVX_INTRINSICS_
include immintrin.inc
endif
endif ;; _XM_SSE_INTRINSICS_
endif ;; not _XM_NO_INTRINSICS_

include sal.inc
;include assert.inc
include stdint.inc

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)

ifdef _XM_NO_MOVNT_
XM_STREAM_PS macro p, a
	exitm<_mm_store_ps( p, a )>
	endm
XM_SFENCE() equ 1
else
XM_STREAM_PS macro p, a
	exitm<_mm_stream_ps( p, a )>
	endm
XM_SFENCE macro
	exitm<_mm_sfence()>
	endm
endif

ifdef _XM_AVX_INTRINSICS_
XM_PERMUTE_PS macro v, q
	exitm<_mm_permute_ps( v, q )>
	endm
else
XM_PERMUTE_PS macro v, q
	exitm<_mm_shuffle_ps( v, v, q )>
	endm
endif

endif ;; _XM_SSE_INTRINSICS_ and not _XM_NO_INTRINSICS_

if defined(__XNAMATH_H__) and defined(XM_PI)
undef XM_PI
undef XM_2PI
undef XM_1DIVPI
undef XM_1DIV2PI
undef XM_PIDIV2
undef XM_PIDIV4
undef XM_SELECT_0
undef XM_SELECT_1
undef XM_PERMUTE_0X
undef XM_PERMUTE_0Y
undef XM_PERMUTE_0Z
undef XM_PERMUTE_0W
undef XM_PERMUTE_1X
undef XM_PERMUTE_1Y
undef XM_PERMUTE_1Z
undef XM_PERMUTE_1W
undef XM_CRMASK_CR6
undef XM_CRMASK_CR6TRUE
undef XM_CRMASK_CR6FALSE
undef XM_CRMASK_CR6BOUNDS
undef XM_CACHE_LINE_SIZE
endif

XM_PI		equ 3.141592654
XM_2PI		equ 6.283185307
XM_1DIVPI	equ 0.318309886
XM_1DIV2PI	equ 0.159154943
XM_PIDIV2	equ 1.570796327
XM_PIDIV4	equ 0.785398163

XM_SELECT_0	equ 0x00000000
XM_SELECT_1	equ 0xFFFFFFFF

XM_PERMUTE_0X	equ 0
XM_PERMUTE_0Y	equ 1
XM_PERMUTE_0Z	equ 2
XM_PERMUTE_0W	equ 3
XM_PERMUTE_1X	equ 4
XM_PERMUTE_1Y	equ 5
XM_PERMUTE_1Z	equ 6
XM_PERMUTE_1W	equ 7

XM_SWIZZLE_X	equ 0
XM_SWIZZLE_Y	equ 1
XM_SWIZZLE_Z	equ 2
XM_SWIZZLE_W	equ 3

XM_CRMASK_CR6		equ 0x000000F0
XM_CRMASK_CR6TRUE	equ 0x00000080
XM_CRMASK_CR6FALSE	equ 0x00000020
XM_CRMASK_CR6BOUNDS	equ XM_CRMASK_CR6FALSE

XM_CACHE_LINE_SIZE	equ 64

if defined(__XNAMATH_H__) and defined(XMComparisonAllTrue)
undef XMComparisonAllTrue
undef XMComparisonAnyTrue
undef XMComparisonAllFalse
undef XMComparisonAnyFalse
undef XMComparisonMixed
undef XMComparisonAllInBounds
undef XMComparisonAnyOutOfBounds
endif

;; Unit conversion

XMConvertToRadians macro fDegrees
	exitm<fDegrees * (XM_PI / 180.0)>
	endm
XMConvertToDegrees macro fRadians
	exitm<fRadians * (180.0 / XM_PI)>
	endm

;; Condition register evaluation proceeding a recording (R) comparison

XMComparisonAllTrue macro CR
	exitm<(((CR) & XM_CRMASK_CR6TRUE) == XM_CRMASK_CR6TRUE)>
	endm
XMComparisonAnyTrue macro CR
	exitm<(((CR) & XM_CRMASK_CR6FALSE) != XM_CRMASK_CR6FALSE)>
	endm
XMComparisonAllFalse macro CR
	exitm<(((CR) & XM_CRMASK_CR6FALSE) == XM_CRMASK_CR6FALSE)>
	endm
XMComparisonAnyFalse macro CR
	exitm<(((CR) & XM_CRMASK_CR6TRUE) != XM_CRMASK_CR6TRUE)>
	endm
XMComparisonMixed macro CR
	exitm<(((CR) & XM_CRMASK_CR6) == 0)>
	endm
XMComparisonAllInBounds macro CR
	exitm<(((CR) & XM_CRMASK_CR6BOUNDS) == XM_CRMASK_CR6BOUNDS)>
	endm
XMComparisonAnyOutOfBounds macro CR
	exitm<(((CR) & XM_CRMASK_CR6BOUNDS) != XM_CRMASK_CR6BOUNDS)>
	endm

ifdef _XM_NO_INTRINSICS_
__vector4 struc
union
 vector4_f32	REAL4 4 dup(?)
 vector4_u32	dd 4 dup(?)
ends
__vector4 ends
endif

__n64 union
    n64_u64	dq 1 dup(?)
    n64_u32	dd 2 dup(?)
    n64_u16	dw 4 dup(?)
    n64_u8	db 2 dup(?)
    n64_i64	sqword 1 dup(?)
    n64_i32	sdword 2 dup(?)
    n64_i16	sword 4 dup(?)
    n64_i8	sbyte 8 dup(?)
    n64_f32	real4 2 dup(?)
__n64 ends

__n128 union
     n128_u64	dq 2 dup(?)
     n128_u32	dd 4 dup(?)
     n128_u16	dw 8 dup(?)
     n128_u8	db 16 dup(?)
     n128_i64	sqword 2 dup(?)
     n128_i32	sdword 4 dup(?)
     n128_i16	sword 8 dup(?)
     n128_i8	sbyte 16 dup(?)
     n128_f32	real4 4 dup(?)
     struc
	low64	__n64 <>
	high64	__n64 <>
     ends
__n128 ends

float32x4_t typedef __n128

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
XMVECTOR typedef REAL16
elseifndef _XM_NO_INTRINSICS_
XMVECTOR typedef float32x4_t
else
XMVECTOR typedef __vector4
endif

if ( defined(_M_IX86) OR _XM_VECTORCALL_ ) and not defined(_XM_NO_INTRINSICS_)
FXMVECTOR typedef XMVECTOR
else
FXMVECTOR typedef ptr XMVECTOR
endif

if ( (_XM_VECTORCALL_ and not defined(_M_IX86) ) ) and not defined(_XM_NO_INTRINSICS_)
GXMVECTOR typedef XMVECTOR
else
GXMVECTOR typedef ptr XMVECTOR
endif

if _XM_VECTORCALL_ and not defined(_XM_NO_INTRINSICS_)
HXMVECTOR typedef XMVECTOR
else
HXMVECTOR typedef ptr XMVECTOR
endif

CXMVECTOR typedef ptr XMVECTOR

XMVECTORF32	STRUC
UNION
 f		REAL4 4 dup(?)
ifdef _XM_NO_INTRINSICS_
 v		XMVECTOR <>
else
 v		XMVECTOR ?
endif
ENDS
XMVECTORF32	ENDS

XMVECTORI32	STRUC
UNION
 i		dd 4 dup(?)
ifdef _XM_NO_INTRINSICS_
 v		XMVECTOR <>
else
 v		XMVECTOR ?
endif
ENDS
XMVECTORI32	ENDS

XMVECTORU8	STRUC
UNION
 u		db 16 dup(?)
ifdef _XM_NO_INTRINSICS_
 v		XMVECTOR <>
else
 v		XMVECTOR ?
endif
ENDS
XMVECTORU8	ENDS

XMVECTORU32	STRUC
UNION
 u		dd 4 dup(?)
ifdef _XM_NO_INTRINSICS_
 v		XMVECTOR <>
else
 v		XMVECTOR ?
endif
ENDS
XMVECTORU32	ENDS

int32_t		typedef sdword
uint32_t	typedef dword

XMMATRIX	STRUC
ifdef _XM_NO_INTRINSICS_
UNION
 r		XMVECTOR 4 dup(<>)
 STRUC
  _11		REAL4 ?
  _12		REAL4 ?
  _13		REAL4 ?
  _14		REAL4 ?
  _21		REAL4 ?
  _22		REAL4 ?
  _23		REAL4 ?
  _24		REAL4 ?
  _31		REAL4 ?
  _32		REAL4 ?
  _33		REAL4 ?
  _34		REAL4 ?
  _41		REAL4 ?
  _42		REAL4 ?
  _43		REAL4 ?
  _44		REAL4 ?
 ENDS
 m		REAL4 4*4 dup(?)
ENDS
else
ifdef _XM_NO_INTRINSICS_
r		XMVECTOR 4 dup(<>)
else
r		XMVECTOR 4 dup(?)
endif
endif
XMMATRIX	ENDS
CXMMATRIX	typedef ptr XMMATRIX

if _XM_VECTORCALL_ and not defined(_XM_NO_INTRINSICS_)
FXMMATRIX	typedef XMMATRIX
else
FXMMATRIX	typedef ptr XMMATRIX
endif

XMFLOAT2	STRUC
x		REAL4 ?
y		REAL4 ?
XMFLOAT2	ENDS

XMINT2		STRUC
x		int32_t ?
y		int32_t ?
XMINT2		ENDS

XMUINT2		STRUC
x		uint32_t ?
y		uint32_t ?
XMUINT2		ENDS

XMFLOAT3	STRUC
x		REAL4 ?
y		REAL4 ?
z		REAL4 ?
XMFLOAT3	ENDS

XMINT3		STRUC
x		int32_t ?
y		int32_t ?
z		int32_t ?
XMINT3		ENDS

XMUINT3		STRUC
x		uint32_t ?
y		uint32_t ?
z		uint32_t ?
XMUINT3		ENDS

XMFLOAT4	STRUC
x		REAL4 ?
y		REAL4 ?
z		REAL4 ?
w		REAL4 ?
XMFLOAT4	ENDS

XMINT4		STRUC
x		int32_t ?
y		int32_t ?
z		int32_t ?
w		int32_t ?
XMINT4		ENDS

XMUINT4		STRUC
x		uint32_t ?
y		uint32_t ?
z		uint32_t ?
w		uint32_t ?
XMUINT4		ENDS

XMFLOAT3X3	STRUC
UNION
 STRUC
  _11		REAL4 ?
  _12		REAL4 ?
  _13		REAL4 ?
  _21		REAL4 ?
  _22		REAL4 ?
  _23		REAL4 ?
  _31		REAL4 ?
  _32		REAL4 ?
  _33		REAL4 ?
 ENDS
 m		REAL4 3*3 dup(?)
ENDS
XMFLOAT3X3	ENDS

XMFLOAT4X3	STRUC
UNION
 STRUC
  _11		REAL4 ?
  _12		REAL4 ?
  _13		REAL4 ?
  _21		REAL4 ?
  _22		REAL4 ?
  _23		REAL4 ?
  _31		REAL4 ?
  _32		REAL4 ?
  _33		REAL4 ?
  _41		REAL4 ?
  _42		REAL4 ?
  _43		REAL4 ?
 ENDS
  m		REAL4 4*3 dup(?)
ENDS
XMFLOAT4X3	ENDS

XMFLOAT4X4	STRUC
UNION
 STRUC
  _11		REAL4 ?
  _12		REAL4 ?
  _13		REAL4 ?
  _14		REAL4 ?
  _21		REAL4 ?
  _22		REAL4 ?
  _23		REAL4 ?
  _24		REAL4 ?
  _31		REAL4 ?
  _32		REAL4 ?
  _33		REAL4 ?
  _34		REAL4 ?
  _41		REAL4 ?
  _42		REAL4 ?
  _43		REAL4 ?
  _44		REAL4 ?
 ENDS
 m		REAL4 4*4 dup(?)
ENDS
XMFLOAT4X4	ENDS

XMConvertVectorIntToFloat macro VInt, DivExponent
    ;;
    ;; Convert to floats
    ;;
    _mm_store_ps(xmm1, _mm_cvtepi32_ps(_mm_castps_si128(VInt)))
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uScale = 0x3F800000 - (DivExponent << 23)
    ;;
    ;; Splat the scalar value
    ;;
    _mm_set1_epi32(0x3F800000 - (DivExponent shl 23))
    _mm_mul_ps(_mm_castsi128_ps(xmm0), xmm1)
    retm<xmm0>
    endm

XMConvertVectorFloatToInt macro VFloat, MulExponent
    .assert( MulExponent < 32 )
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
else
    _mm_store_ps(xmm1, VFloat)
    _mm_set_ps1(_mm_cvtsi32_ss(xmm0, (1 shl MulExponent)))
    _mm_store_ps(xmm1, _mm_mul_ps(xmm0, xmm1))
    ;;
    ;; In case of positive overflow, detect it
    ;;
    _mm_store_ps(xmm2, _mm_cmpgt_ps(xmm0, g_XMMaxInt))
    ;;
    ;; Float to int conversion
    ;;
    _mm_cvttps_epi32(xmm1)
    ;;
    ;; If there was positive overflow, set to 0x7FFFFFFF
    ;;
    _mm_and_ps(xmm2, g_XMAbsMask)
    _mm_andnot_ps(xmm0, _mm_castsi128_ps(xmm1))
    _mm_or_ps(xmm0, xmm2)
    retm<xmm0>
endif
    endm

XMConvertVectorUIntToFloat macro VUInt, DivExponent
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

XMConvertVectorFloatToUInt macro VFloat, MulExponent
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

if defined(__XNAMATH_H__) and defined(XMVectorSetBinaryConstant)
undef XMVectorSetBinaryConstant
undef XMVectorSplatConstant
undef XMVectorSplatConstantInt
endif

XMVectorSetBinaryConstant macro C0, C1, C2, C3
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

XMVectorSplatConstant macro IntConstant, DivExponent
    .assert( IntConstant >= -16 && IntConstant <= 15 )
    .assert( DivExponent < 32 )
ifdef _XM_NO_INTRINSICS_
    exitm<XMConvertVectorIntToFloat(_mm_set1_epi32(IntConstant), DivExponent)>
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

XMVectorSplatConstantInt macro IntConstant
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

XMLoadInt macro pSource
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

XMLoadFloat macro pSource
    .assert(pSource)
    .assert(!(pSource & 0xF))
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_load_ss(pSource)
    retm<xmm0>
endif
    endm

XMLoadInt2 macro pSource
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

XMLoadInt2A macro pSource
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

XMLoadFloat2 macro pSource
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

XMLoadFloat2A macro pSource
    .assert(pSource)
ifdef _XM_NO_INTRINSICS_
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_loadl_epi64(pSource)
    _mm_castsi128_ps(xmm0)
    retm<xmm0>
endif
    endm

XMLoadSInt2 macro pSource
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

XMLoadUInt2 macro pSource
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

XMLoadInt3 macro pSource
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

XMLoadInt3A macro pSource
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

XMLoadFloat3 macro pSource
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

XMLoadFloat3A macro pSource
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

XMLoadSInt3 macro pSource
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

XMLoadUInt3 macro pSource
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

XMLoadInt4 macro ptr_uint32_t
    exitm<_mm_castsi128_ps(_mm_loadu_si128(ptr_uint32_t))>
    endm
XMLoadInt4A macro ptr_uint32_t
    exitm<_mm_castsi128_ps(_mm_load_si128(ptr_uint32_t))>
    endm
XMLoadFloat4 macro ptr_XMFLOAT4
    exitm<_mm_loadu_ps(ptr_XMFLOAT4)>
    endm

XMLoadFloat4A macro ptr_XMFLOAT4A
    exitm<_mm_load_ps(ptr_XMFLOAT4A)>
    endm
XMLoadSInt4 macro ptr_XMINT4
    exitm<_mm_cvtepi32_ps(_mm_loadu_si128(ptr_XMINT4))>
    endm
XMLoadUInt4 macro ptr_XMUINT4
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

XMLoadFloat3x3	proto :ptr XMFLOAT3X3
XMLoadFloat4x3	proto :ptr XMFLOAT4X3
XMLoadFloat4x3A proto :ptr XMFLOAT4X3A
XMLoadFloat4x4	proto :ptr XMFLOAT4X4
XMLoadFloat4x4A proto :ptr XMFLOAT4X4A

XMStoreInt	proto :ptr uint32_t, :FXMVECTOR
XMStoreFloat	proto :ptr REAL4, :FXMVECTOR
XMStoreInt2	proto :ptr uint32_t, :FXMVECTOR
XMStoreInt2A	proto :ptr uint32_t, :FXMVECTOR
XMStoreFloat2	proto :ptr XMFLOAT2, :FXMVECTOR
XMStoreFloat2A	proto :ptr XMFLOAT2A, :FXMVECTOR
XMStoreSInt2	proto :ptr XMINT2, :FXMVECTOR
XMStoreUInt2	proto :ptr XMUINT2, :FXMVECTOR
XMStoreInt3	proto :ptr uint32_t, :FXMVECTOR
XMStoreInt3A	proto :ptr uint32_t, :FXMVECTOR
XMStoreFloat3	proto :ptr XMFLOAT3, :FXMVECTOR
XMStoreFloat3A	proto :ptr XMFLOAT3A, :FXMVECTOR
XMStoreSInt3	proto :ptr XMINT3, :FXMVECTOR
XMStoreUInt3	proto :ptr XMUINT3, :FXMVECTOR
XMStoreInt4	proto :ptr uint32_t, :FXMVECTOR
XMStoreInt4A	proto :ptr uint32_t, :FXMVECTOR
XMStoreFloat4	proto :ptr XMFLOAT4, :FXMVECTOR
XMStoreFloat4A	proto :ptr XMFLOAT4A, :FXMVECTOR
XMStoreSInt4	proto :ptr XMINT4, :FXMVECTOR
XMStoreUInt4	proto :ptr XMUINT4, :FXMVECTOR

XMStoreFloat3x3		proto :ptr XMFLOAT3X3, :FXMMATRIX
XMStoreFloat4x3		proto :ptr XMFLOAT4X3, :FXMMATRIX
XMStoreFloat4x3A	proto :ptr XMFLOAT4X3A, :FXMMATRIX
XMStoreFloat4x4		proto :ptr XMFLOAT4X4, :FXMMATRIX
XMStoreFloat4x4A	proto :ptr XMFLOAT4X4A, :FXMMATRIX

XMVectorZero		proto
XMVectorSet macro x, y, z, w
ifdef _XM_NO_INTRINSICS_
    exitm<_mm_set_ps( w, z, y, x )>
elseifdef _XM_ARM_NEON_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    exitm<_mm_set_ps( w, z, y, x )>
endif
    endm

XMVectorSetInt		proto :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorReplicate	proto :float
XMVectorReplicatePtr	proto :ptr float
XMVectorReplicateInt	proto :uint32_t
XMVectorReplicateIntPtr proto :ptr uint32_t
XMVectorTrueInt		proto
XMVectorFalseInt	proto
XMVectorSplatX		proto :FXMVECTOR
XMVectorSplatY		proto :FXMVECTOR
XMVectorSplatZ		proto :FXMVECTOR
XMVectorSplatW		proto :FXMVECTOR
XMVectorSplatOne	proto
XMVectorSplatInfinity	proto
XMVectorSplatQNaN	proto
XMVectorSplatEpsilon	proto
XMVectorSplatSignMask	proto

XMVectorGetByIndex	proto :FXMVECTOR, :size_t
XMVectorGetX		proto :FXMVECTOR
XMVectorGetY		proto :FXMVECTOR
XMVectorGetZ		proto :FXMVECTOR
XMVectorGetW		proto :FXMVECTOR
XMVectorGetByIndexPtr	proto :ptr float, :FXMVECTOR, :size_t
XMVectorGetXPtr		proto :ptr float, :FXMVECTOR
XMVectorGetYPtr		proto :ptr float, :FXMVECTOR
XMVectorGetZPtr		proto :ptr float, :FXMVECTOR
XMVectorGetWPtr		proto :ptr float, :FXMVECTOR

XMVectorGetIntByIndex	proto :FXMVECTOR, :size_t
XMVectorGetIntX		proto :FXMVECTOR
XMVectorGetIntY		proto :FXMVECTOR
XMVectorGetIntZ		proto :FXMVECTOR
XMVectorGetIntW		proto :FXMVECTOR

XMVectorGetIntByIndexPtr proto :ptr uint32_t, :FXMVECTOR, :size_t
XMVectorGetIntXPtr	proto :ptr uint32_t, :FXMVECTOR
XMVectorGetIntYPtr	proto :ptr uint32_t, :FXMVECTOR
XMVectorGetIntZPtr	proto :ptr uint32_t, :FXMVECTOR
XMVectorGetIntWPtr	proto :ptr uint32_t, :FXMVECTOR

XMVectorSetByIndex	proto :FXMVECTOR, :float, :size_t
XMVectorSetX		proto :FXMVECTOR, :float
XMVectorSetY		proto :FXMVECTOR, :float
XMVectorSetZ		proto :FXMVECTOR, :float
XMVectorSetW		proto :FXMVECTOR, :float

XMVectorSetByIndexPtr	proto :FXMVECTOR, :ptr float, :size_t
XMVectorSetXPtr		proto :FXMVECTOR, :ptr float
XMVectorSetYPtr		proto :FXMVECTOR, :ptr float
XMVectorSetZPtr		proto :FXMVECTOR, :ptr float
XMVectorSetWPtr		proto :FXMVECTOR, :ptr float

XMVectorSetIntByIndex	proto :FXMVECTOR, :uint32_t, :size_t
XMVectorSetIntX		proto :FXMVECTOR, :uint32_t
XMVectorSetIntY		proto :FXMVECTOR, :uint32_t
XMVectorSetIntZ		proto :FXMVECTOR, :uint32_t
XMVectorSetIntW		proto :FXMVECTOR, :uint32_t

XMVectorSetIntByIndexPtr proto :FXMVECTOR, :ptr uint32_t, :size_t
XMVectorSetIntXPtr	proto :FXMVECTOR, :ptr uint32_t
XMVectorSetIntYPtr	proto :FXMVECTOR, :ptr uint32_t
XMVectorSetIntZPtr	proto :FXMVECTOR, :ptr uint32_t
XMVectorSetIntWPtr	proto :FXMVECTOR, :ptr uint32_t

if defined(__XNAMATH_H__) and defined(XMVectorSwizzle)
undef XMVectorSwizzle
endif

XMVectorSwizzle		proto :FXMVECTOR, :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorPermute		proto :FXMVECTOR, :FXMVECTOR, :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorSelectControl	proto :uint32_t, :uint32_t, :uint32_t, :uint32_t

XMVectorSelect macro V1:=<xmm0>, V2:=<xmm1>, Control:=<xmm2>
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

XMVectorMergeXY		proto :FXMVECTOR, :FXMVECTOR
XMVectorMergeZW		proto :FXMVECTOR, :FXMVECTOR

if defined(__XNAMATH_H__) and defined(XMVectorShiftLeft)
undef XMVectorShiftLeft
undef XMVectorRotateLeft
undef XMVectorRotateRight
undef XMVectorInsert
endif

XMVectorShiftLeft	proto :FXMVECTOR, :FXMVECTOR, :uint32_t
XMVectorRotateLeft	proto :FXMVECTOR, :uint32_t
XMVectorRotateRight	proto :FXMVECTOR, :uint32_t
XMVectorInsert		proto :FXMVECTOR, :FXMVECTOR, :uint32_t, :uint32_t, :uint32_t, :uint32_t, :uint32_t

XMVectorEqual		proto :FXMVECTOR, :FXMVECTOR
XMVectorEqualR		proto :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorEqualInt	proto :FXMVECTOR, :FXMVECTOR
XMVectorEqualIntR	proto :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorNearEqual	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorNotEqual	proto :FXMVECTOR, :FXMVECTOR
XMVectorNotEqualInt	proto :FXMVECTOR, :FXMVECTOR
XMVectorGreater		proto :FXMVECTOR, :FXMVECTOR
XMVectorGreaterR	proto :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorGreaterOrEqual	proto :FXMVECTOR, :FXMVECTOR
XMVectorGreaterOrEqualR proto :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorLess		proto :FXMVECTOR, :FXMVECTOR
XMVectorLessOrEqual	proto :FXMVECTOR, :FXMVECTOR
XMVectorInBounds	proto :FXMVECTOR, :FXMVECTOR
XMVectorInBoundsR	proto :ptr uint32_t, :FXMVECTOR, :FXMVECTOR

XMVectorIsNaN		proto :FXMVECTOR
XMVectorIsInfinite	proto :FXMVECTOR

XMVectorMin		proto :FXMVECTOR, :FXMVECTOR
XMVectorMax		proto :FXMVECTOR, :FXMVECTOR
XMVectorRound		proto :FXMVECTOR
XMVectorTruncate	proto :FXMVECTOR
XMVectorFloor		proto :FXMVECTOR
XMVectorCeiling		proto :FXMVECTOR
XMVectorClamp		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorSaturate	proto :FXMVECTOR

XMVectorAndInt		proto :FXMVECTOR, :FXMVECTOR
XMVectorAndCInt		proto :FXMVECTOR, :FXMVECTOR
XMVectorOrInt		proto :FXMVECTOR, :FXMVECTOR
XMVectorNorInt		proto :FXMVECTOR, :FXMVECTOR
XMVectorXorInt		proto :FXMVECTOR, :FXMVECTOR

XMVectorNegate macro x:req
    _mm_store_ps(xmm1, x)
    exitm<_mm_sub_ps(_mm_setzero_ps(), xmm1)>
    endm

XMVectorAdd		proto :FXMVECTOR, :FXMVECTOR
XMVectorSum		proto :FXMVECTOR
XMVectorAddAngles	proto :FXMVECTOR, :FXMVECTOR

XMVectorSubtract	equ <_mm_sub_ps>

XMVectorSubtractAngles	proto :FXMVECTOR, :FXMVECTOR
XMVectorMultiply	proto :FXMVECTOR, :FXMVECTOR
XMVectorMultiplyAdd	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorDivide		proto :FXMVECTOR, :FXMVECTOR
XMVectorNegativeMultiplySubtract proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorScale		proto :FXMVECTOR, :float
XMVectorReciprocalEst	proto :FXMVECTOR
XMVectorReciprocal	proto :FXMVECTOR
XMVectorSqrtEst		proto :FXMVECTOR
XMVectorSqrt		proto :FXMVECTOR
XMVectorReciprocalSqrtEst proto :FXMVECTOR
XMVectorReciprocalSqrt	proto :FXMVECTOR
XMVectorExp2		proto :FXMVECTOR
XMVectorExpE		proto :FXMVECTOR
XMVectorExp		proto :FXMVECTOR
XMVectorLog2		proto :FXMVECTOR
XMVectorLogE		proto :FXMVECTOR
XMVectorLog		proto :FXMVECTOR
XMVectorPow		proto :FXMVECTOR, :FXMVECTOR
XMVectorAbs		proto :FXMVECTOR
XMVectorMod		proto :FXMVECTOR, :FXMVECTOR
XMVectorModAngles	proto :FXMVECTOR
XMVectorSin		proto :FXMVECTOR
XMVectorSinEst		proto :FXMVECTOR
XMVectorCos		proto :FXMVECTOR
XMVectorCosEst		proto :FXMVECTOR

XMVectorSinCos		proto :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR
XMVectorSinCosEst	proto :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR

XMVectorTan		proto :FXMVECTOR
XMVectorTanEst		proto :FXMVECTOR
XMVectorSinH		proto :FXMVECTOR
XMVectorCosH		proto :FXMVECTOR
XMVectorTanH		proto :FXMVECTOR
XMVectorASin		proto :FXMVECTOR
XMVectorASinEst		proto :FXMVECTOR
XMVectorACos		proto :FXMVECTOR
XMVectorACosEst		proto :FXMVECTOR
XMVectorATan		proto :FXMVECTOR
XMVectorATanEst		proto :FXMVECTOR
XMVectorATan2		proto :FXMVECTOR, :FXMVECTOR
XMVectorATan2Est	proto :FXMVECTOR, :FXMVECTOR
XMVectorLerp		proto :FXMVECTOR, :FXMVECTOR, :float
XMVectorLerpV		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorHermite		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :float
XMVectorHermiteV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR
XMVectorCatmullRom	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :float
XMVectorCatmullRomV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR
XMVectorBaryCentric	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :float, :float
XMVectorBaryCentricV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR

XMVector2Equal		proto :FXMVECTOR, :FXMVECTOR
XMVector2EqualR		proto :FXMVECTOR, :FXMVECTOR
XMVector2EqualInt	proto :FXMVECTOR, :FXMVECTOR
XMVector2EqualIntR	proto :FXMVECTOR, :FXMVECTOR
XMVector2NearEqual	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2NotEqual	proto :FXMVECTOR, :FXMVECTOR
XMVector2NotEqualInt	proto :FXMVECTOR, :FXMVECTOR
XMVector2Greater	proto :FXMVECTOR, :FXMVECTOR
XMVector2GreaterR	proto :FXMVECTOR, :FXMVECTOR
XMVector2GreaterOrEqual proto :FXMVECTOR, :FXMVECTOR
XMVector2GreaterOrEqualR proto :FXMVECTOR,:FXMVECTOR
XMVector2Less		proto :FXMVECTOR, :FXMVECTOR
XMVector2LessOrEqual	proto :FXMVECTOR, :FXMVECTOR
XMVector2InBounds	proto :FXMVECTOR, :FXMVECTOR

XMVector2IsNaN		proto :FXMVECTOR
XMVector2IsInfinite	proto :FXMVECTOR

XMVector2Dot		proto :FXMVECTOR, :FXMVECTOR
XMVector2Cross		proto :FXMVECTOR, :FXMVECTOR
XMVector2LengthSq	proto :FXMVECTOR
XMVector2ReciprocalLengthEst proto :FXMVECTOR
XMVector2ReciprocalLength proto :FXMVECTOR
XMVector2LengthEst	proto :FXMVECTOR
XMVector2Length		proto :FXMVECTOR
XMVector2NormalizeEst	proto :FXMVECTOR
XMVector2Normalize	proto :FXMVECTOR
XMVector2ClampLength	proto :FXMVECTOR, :float, :float
XMVector2ClampLengthV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2Reflect	proto :FXMVECTOR, :FXMVECTOR
XMVector2Refract	proto :FXMVECTOR, :FXMVECTOR, :float
XMVector2RefractV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2Orthogonal	proto :FXMVECTOR

XMVector2AngleBetweenNormalsEst proto :FXMVECTOR, :FXMVECTOR
XMVector2AngleBetweenNormals	proto :FXMVECTOR, :FXMVECTOR
XMVector2AngleBetweenVectors	proto :FXMVECTOR, :FXMVECTOR
XMVector2LinePointDistance	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2IntersectLine		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR
XMVector2Transform		proto :FXMVECTOR, :FXMMATRIX

XMVector2TransformStream	proto :ptr XMFLOAT4, :size_t, :ptr XMFLOAT2, :size_t, :size_t, :FXMMATRIX
XMVector2TransformCoord		proto :FXMVECTOR, :FXMMATRIX
XMVector2TransformCoordStream	proto :ptr XMFLOAT2, :size_t, :ptr XMFLOAT2, :size_t, :size_t, :FXMMATRIX
XMVector2TransformNormal	proto :FXMVECTOR, :FXMMATRIX
XMVector2TransformNormalStream	proto :ptr XMFLOAT2, :size_t, :ptr XMFLOAT2, :size_t, :size_t, :FXMMATRIX

XMVector3Equal		proto :FXMVECTOR, :FXMVECTOR
XMVector3EqualR		proto :FXMVECTOR, :FXMVECTOR
XMVector3EqualInt	proto :FXMVECTOR, :FXMVECTOR
XMVector3EqualIntR	proto :FXMVECTOR, :FXMVECTOR
XMVector3NearEqual	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector3NotEqual	proto :FXMVECTOR, :FXMVECTOR
XMVector3NotEqualInt	proto :FXMVECTOR, :FXMVECTOR
XMVector3Greater	proto :FXMVECTOR, :FXMVECTOR
XMVector3GreaterR	proto :FXMVECTOR, :FXMVECTOR
XMVector3GreaterOrEqual proto :FXMVECTOR, :FXMVECTOR
XMVector3GreaterOrEqualR proto :FXMVECTOR, :FXMVECTOR
XMVector3Less		proto :FXMVECTOR, :FXMVECTOR
XMVector3LessOrEqual	proto :FXMVECTOR, :FXMVECTOR
XMVector3InBounds	proto :FXMVECTOR, :FXMVECTOR

XMVector3IsNaN		proto :FXMVECTOR
XMVector3IsInfinite	proto :FXMVECTOR

XMVector3Dot macro V1:=<xmm0>, V2:=<xmm1>
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

XMVector3Cross macro V1:=<xmm0>, V2:=<xmm1>
    _mm_store_ps(xmm0, V1)
    _mm_store_ps(xmm1, V2)
    _mm_store_ps(xmm2, XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,2,1)))
    _mm_store_ps(xmm3, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3,1,0,2)))
    _mm_shuffle_ps(xmm3, xmm1, _MM_SHUFFLE(3,1,0,2))
    _mm_shuffle_ps(xmm2, xmm0, _MM_SHUFFLE(3,0,2,1))
    _mm_mul_ps(xmm0, xmm1)
    _mm_mul_ps(xmm2, xmm3)
    _mm_sub_ps(xmm0, xmm2)
    _mm_and_ps(xmm0, g_XMMask3)
    retm<xmm0>
    endm

XMVector3LengthSq	proto :FXMVECTOR
XMVector3ReciprocalLengthEst proto :FXMVECTOR
XMVector3ReciprocalLength proto :FXMVECTOR
XMVector3LengthEst	proto :FXMVECTOR
XMVector3Length		proto :FXMVECTOR
XMVector3NormalizeEst	proto :FXMVECTOR

XMVector3Normalize macro V:=<xmm0>
ifdef _XM_SSE4_INTRINSICS_
elseifdef _XM_SSE3_INTRINSICS_
elseifdef _XM_SSE_INTRINSICS_
    _mm_store_ps(xmm0, V)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, _mm_mul_ps(xmm1, xmm0))
    _mm_shuffle_ps(xmm2, xmm1, _MM_SHUFFLE(2,1,2,1))
    _mm_add_ss(xmm1, xmm2)
    _mm_add_ss(xmm1, XM_PERMUTE_PS(xmm2, _MM_SHUFFLE(1,1,1,1)))
    _mm_sqrt_ps(xmm3, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,0,0,0)))
    _mm_cmpneq_ps(xmm1, g_XMInfinity)
    _mm_div_ps(xmm0, xmm3)
    _mm_cmpneq_ps(xmm2, xmm3)
    _mm_and_ps(xmm0, xmm2)
    _mm_store_ps(xmm2, xmm1)
    _mm_andnot_ps(xmm2, g_XMQNaN)
    _mm_and_ps(xmm1, xmm0)
    _mm_or_ps(xmm0, xmm1)
    retm<xmm0>
endif
    endm

XMMatrixTranspose macro M, O
    ifnb <M>
	_mm_store_ps(xmm0, M.r[0x00])
	_mm_store_ps(xmm1, M.r[0x10])
	_mm_store_ps(xmm2, M.r[0x20])
	_mm_store_ps(xmm3, M.r[0x30])
    endif
    _mm_store_ps(xmm4, xmm0)
    _mm_store_ps(xmm5, xmm2)
    _mm_shuffle_ps(xmm0, xmm1, _MM_SHUFFLE(1,0,1,0))
    _mm_shuffle_ps(xmm4, xmm1, _MM_SHUFFLE(3,2,3,2))
    _mm_shuffle_ps(xmm2, xmm3, _MM_SHUFFLE(1,0,1,0))
    _mm_shuffle_ps(xmm5, xmm3, _MM_SHUFFLE(3,2,3,2))
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm3, xmm2)
    _mm_shuffle_ps(xmm0, xmm4, _MM_SHUFFLE(2,0,2,0))
    _mm_shuffle_ps(xmm1, xmm4, _MM_SHUFFLE(3,1,3,1))
    _mm_shuffle_ps(xmm2, xmm5, _MM_SHUFFLE(2,0,2,0))
    _mm_shuffle_ps(xmm3, xmm5, _MM_SHUFFLE(3,1,3,1))
    ifnb <O>
	_mm_store_ps(O.r[0x00], xmm0)
	_mm_store_ps(O.r[0x10], xmm1)
	_mm_store_ps(O.r[0x20], xmm2)
	_mm_store_ps(O.r[0x30], xmm3)
    endif
    exitm<>
    endm

XMMatrixTransposex macro O
    _mm_store_ps(xmm4, xmm0)
    _mm_store_ps(xmm5, xmm2)
    _mm_shuffle_ps(xmm0, xmm1, _MM_SHUFFLE(1,0,1,0))
    _mm_shuffle_ps(xmm4, xmm1, _MM_SHUFFLE(3,2,3,2))
    _mm_shuffle_ps(xmm2, xmm3, _MM_SHUFFLE(1,0,1,0))
    _mm_shuffle_ps(xmm5, xmm3, _MM_SHUFFLE(3,2,3,2))
    _mm_store_ps(xmm1, xmm0)
    _mm_shuffle_ps(xmm0, xmm4, _MM_SHUFFLE(2,0,2,0))
    _mm_shuffle_ps(xmm1, xmm4, _MM_SHUFFLE(3,1,3,1))
    _mm_store_ps(xmm3, xmm2)
    _mm_store_ps(xmm2, xmm4)
    _mm_shuffle_ps(xmm2, xmm5, _MM_SHUFFLE(2,0,2,0))
    _mm_shuffle_ps(xmm3, xmm5, _MM_SHUFFLE(3,1,3,1))
    ifnb <O>
	_mm_store_ps(O.r[0*16], xmm0)
	_mm_store_ps(O.r[1*16], xmm1)
	_mm_store_ps(O.r[2*16], xmm2)
	_mm_store_ps(O.r[3*16], xmm3)
    endif
    exitm<>
    endm

XMMatrixMultiplyTranspose proto :FXMMATRIX, :CXMMATRIX

XMVector3ClampLength	proto :FXMVECTOR, :float, :float
XMVector3ClampLengthV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector3Reflect	proto :FXMVECTOR, :FXMVECTOR
XMVector3Refract	proto :FXMVECTOR, :FXMVECTOR, :float
XMVector3RefractV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector3Orthogonal	proto :FXMVECTOR
XMVector3AngleBetweenNormalsEst proto :FXMVECTOR, :FXMVECTOR
XMVector3AngleBetweenNormals	proto :FXMVECTOR, :FXMVECTOR
XMVector3AngleBetweenVectors	proto :FXMVECTOR, :FXMVECTOR
XMVector3LinePointDistance	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR

XMVector3ComponentsFromNormal	proto :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR, :FXMVECTOR

XMVector3Rotate			proto :FXMVECTOR, :FXMVECTOR
XMVector3InverseRotate		proto :FXMVECTOR, :FXMVECTOR
XMVector3Transform macro V, M
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

XMVector3TransformStream	proto :ptr XMFLOAT4, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :FXMMATRIX
XMVector3TransformCoord		proto :FXMVECTOR, :FXMMATRIX
XMVector3TransformCoordStream	proto :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :FXMMATRIX
XMVector3TransformNormal	proto :FXMVECTOR, :FXMMATRIX
XMVector3TransformNormalStream	proto :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :FXMMATRIX
XMVector3Project		proto :FXMVECTOR, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX
XMVector3ProjectStream		proto :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX
XMVector3Unproject		proto :FXMVECTOR, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX
XMVector3UnprojectStream	proto :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX

XMVector4Equal			proto :FXMVECTOR, :FXMVECTOR
XMVector4EqualR			proto :FXMVECTOR, :FXMVECTOR
XMVector4EqualInt		proto :FXMVECTOR, :FXMVECTOR
XMVector4EqualIntR		proto :FXMVECTOR, :FXMVECTOR
XMVector4NearEqual		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4NotEqual		proto :FXMVECTOR, :FXMVECTOR
XMVector4NotEqualInt		proto :FXMVECTOR, :FXMVECTOR
XMVector4Greater		proto :FXMVECTOR, :FXMVECTOR
XMVector4GreaterR		proto :FXMVECTOR, :FXMVECTOR
XMVector4GreaterOrEqual		proto :FXMVECTOR, :FXMVECTOR
XMVector4GreaterOrEqualR	proto :FXMVECTOR,:FXMVECTOR
XMVector4Less			proto :FXMVECTOR, :FXMVECTOR
XMVector4LessOrEqual		proto :FXMVECTOR, :FXMVECTOR
XMVector4InBounds		proto :FXMVECTOR, :FXMVECTOR
XMVector4IsNaN			proto :FXMVECTOR
XMVector4IsInfinite		proto :FXMVECTOR

XMVector4Dot			proto :FXMVECTOR, :FXMVECTOR
XMVector4Cross			proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4LengthSq		proto :FXMVECTOR
XMVector4ReciprocalLengthEst	proto :FXMVECTOR
XMVector4ReciprocalLength	proto :FXMVECTOR
XMVector4LengthEst		proto :FXMVECTOR
XMVector4Length			proto :FXMVECTOR
XMVector4NormalizeEst		proto :FXMVECTOR
XMVector4Normalize		proto :FXMVECTOR
XMVector4ClampLength		proto :FXMVECTOR, :float, :float
XMVector4ClampLengthV		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4Reflect		proto :FXMVECTOR, :FXMVECTOR
XMVector4Refract		proto :FXMVECTOR, :FXMVECTOR, :float
XMVector4RefractV		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4Orthogonal		proto :FXMVECTOR
XMVector4AngleBetweenNormalsEst proto :FXMVECTOR, :FXMVECTOR
XMVector4AngleBetweenNormals	proto :FXMVECTOR, :FXMVECTOR
XMVector4AngleBetweenVectors	proto :FXMVECTOR, :FXMVECTOR
XMVector4Transform		proto :FXMVECTOR, :FXMMATRIX
XMVector4TransformStream	proto :ptr XMFLOAT4, :size_t, :ptr XMFLOAT4, :size_t, :size_t, :FXMMATRIX

XMMatrixIsNaN			proto :FXMMATRIX
XMMatrixIsInfinite		proto :FXMMATRIX
XMMatrixIsIdentity		proto :FXMMATRIX

XMMatrixMultiply macro M1, M2
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

XMMatrixInverse			proto :ptr XMVECTOR, :FXMMATRIX
XMMatrixDeterminant		proto :FXMMATRIX

XMMatrixDecompose		proto :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :FXMMATRIX

XMMatrixIdentity macro M
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

XMMatrixSet macro m00, m01, m02, m03, m10, m11, m12, m13,
		  m20, m21, m22, m23, m30, m31, m32, m33
    _mm_set_epi32(xmm0, m00, m01, m02, m03)
    _mm_set_epi32(xmm1, m10, m11, m12, m13)
    _mm_set_epi32(xmm2, m20, m21, m22, m23)
    _mm_set_epi32(xmm3, m30, m31, m32, m33)
    exitm<>
    endm

XMMatrixTranslation macro OffsetX, OffsetY, OffsetZ, M
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

XMMatrixScaling macro ScaleX, ScaleY, ScaleZ, M
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

XMMatrixTranslationFromVector macro V, M
    _mm_store_ps(xmm1, V)
    _mm_store_ps(xmm0, g_XMIdentityR3.v)
    _mm_store_ps(xmm2, g_XMSelect1110.v)
    _mm_store_ps(xmm3, XMVectorSelect(xmm0, xmm1, xmm2))
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

XMMatrixScalingFromVector	proto :FXMVECTOR

XMMatrixRotationX		proto :float
XMMatrixRotationY		proto :float
XMMatrixRotationZ		proto :float
XMMatrixRotationRollPitchYaw	proto :float, :float, :float
XMMatrixRotationRollPitchYawFromVector proto :FXMVECTOR
XMMatrixRotationNormal		proto :FXMVECTOR, :float
XMMatrixRotationAxis		proto :FXMVECTOR, :float
XMMatrixRotationQuaternion	proto :FXMVECTOR
XMMatrixTransformation2D	proto :FXMVECTOR, :float, :FXMVECTOR, :FXMVECTOR, :float, :GXMVECTOR
XMMatrixTransformation		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR
XMMatrixAffineTransformation2D	proto :FXMVECTOR, :FXMVECTOR, :float, :FXMVECTOR
XMMatrixAffineTransformation	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR
XMMatrixReflect			proto :FXMVECTOR
XMMatrixShadow			proto :FXMVECTOR, :FXMVECTOR

XMMatrixLookAtLH macro EyePosition, FocusPosition, UpDirection
    _mm_store_ps(xmm0, EyePosition)
    _mm_store_ps(xmm1, FocusPosition)
    _mm_store_ps(xmm2, UpDirection)
    _mm_store_ps(xmm3, xmm0)
    _mm_store_ps(xmm0, xmm3)
    _mm_sub_ps(xmm0, xmm1)
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm3)
    XMMatrixLookToLH(xmm0, xmm1, xmm2)
    retm<xmm0>
    endm

XMMatrixLookAtRH macro EyePosition, FocusPosition, UpDirection
    _mm_store_ps(xmm0, EyePosition)
    _mm_store_ps(xmm1, FocusPosition)
    _mm_store_ps(xmm2, UpDirection)
    _mm_store_ps(xmm3 xmm0)
    XMVectorSubtract(xmm3, xmm1)
    XMMatrixLookToLH(xmm0, xmm3, xmm2)
    retm<xmm0>
    endm

XMMatrixLookToLH macro EyePosition, EyeDirection, UpDirection
    _mm_store_ps(xmm0, EyePosition)
    _mm_store_ps(xmm1, EyeDirection)
    _mm_store_ps(xmm2, UpDirection)
    _mm_store_ps(xmm6, xmm0)
    _mm_store_ps(xmm7, xmm2)
    _mm_store_ps(xmm5, XMVector3Normalize(xmm1))
    _mm_store_ps(xmm0, xmm7)
    _mm_store_ps(xmm1, xmm5)
    _mm_store_ps(xmm4, XMVector3Normalize(XMVector3Cross(xmm0, xmm1)))
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm0, xmm5)
    _mm_store_ps(xmm3, XMVector3Cross(xmm0, xmm1))
    _mm_store_ps(xmm6, _mm_sub_ps( _mm_setzero_ps(), xmm6 ))
    _mm_store_ps(xmm7, XMVector3Dot(_mm_store_ps(xmm0, xmm4), _mm_store_ps(xmm1, xmm6)))
    _mm_store_ps(xmm1, XMVector3Dot(_mm_store_ps(xmm0, xmm3), _mm_store_ps(xmm1, xmm6)))
    _mm_store_ps(xmm6, XMVector3Dot(_mm_store_ps(xmm0, xmm5), _mm_store_ps(xmm1, xmm6)))
    _mm_store_ps(xmm3, XMVectorSelect(xmm1, xmm3, g_XMSelect1110.v))
    _mm_store_ps(xmm7, XMVectorSelect(xmm7, xmm4, g_XMSelect1110.v))
    _mm_store_ps(xmm6, XMVectorSelect(xmm6, xmm5, g_XMSelect1110.v))
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

XMMatrixLookToRH		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMMatrixPerspectiveLH		proto :float, :float, :float, :float
XMMatrixPerspectiveRH		proto :float, :float, :float, :float

XMMatrixPerspectiveFovLH	proto :float, :float, :float, :float

XMMatrixPerspectiveFovRH	proto :float, :float, :float, :float
XMMatrixPerspectiveOffCenterLH	proto :float, :float, :float, :float, :float, :float
XMMatrixPerspectiveOffCenterRH	proto :float, :float, :float, :float, :float, :float
XMMatrixOrthographicLH		proto :float, :float, :float, :float
XMMatrixOrthographicRH		proto :float, :float, :float, :float
XMMatrixOrthographicOffCenterLH proto :float, :float, :float, :float, :float, :float
XMMatrixOrthographicOffCenterRH proto :float, :float, :float, :float, :float, :float

XMQuaternionEqual	proto :FXMVECTOR, :FXMVECTOR
XMQuaternionNotEqual	proto :FXMVECTOR, :FXMVECTOR
XMQuaternionIsNaN	proto :FXMVECTOR
XMQuaternionIsInfinite	proto :FXMVECTOR
XMQuaternionIsIdentity	proto :FXMVECTOR

XMQuaternionDot		proto :FXMVECTOR, :FXMVECTOR
XMQuaternionMultiply	proto :FXMVECTOR, :FXMVECTOR
XMQuaternionLengthSq	proto :FXMVECTOR
XMQuaternionReciprocalLength proto :FXMVECTOR
XMQuaternionLength	proto :FXMVECTOR
XMQuaternionNormalizeEst proto :FXMVECTOR
XMQuaternionNormalize	proto :FXMVECTOR
XMQuaternionConjugate	proto :FXMVECTOR
XMQuaternionInverse	proto :FXMVECTOR
XMQuaternionLn		proto :FXMVECTOR
XMQuaternionExp		proto :FXMVECTOR
XMQuaternionSlerp	proto :FXMVECTOR, :FXMVECTOR, :float
XMQuaternionSlerpV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMQuaternionSquad	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :float
XMQuaternionSquadV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR

XMQuaternionSquadSetup	proto :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR,
				:FXMVECTOR, :FXMVECTOR, :GXMVECTOR

XMQuaternionBaryCentric		proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :float, :float
XMQuaternionBaryCentricV	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR

XMQuaternionIdentity		proto
XMQuaternionRotationRollPitchYaw proto :float, :float, :float
XMQuaternionRotationRollPitchYawFromVector proto :FXMVECTOR
XMQuaternionRotationNormal	proto :FXMVECTOR, :float
XMQuaternionRotationAxis	proto :FXMVECTOR, :float
XMQuaternionRotationMatrix	proto :FXMMATRIX

XMQuaternionToAxisAngle		proto :ptr XMVECTOR, :ptr float, :FXMVECTOR

XMPlaneEqual		proto :FXMVECTOR, :FXMVECTOR
XMPlaneNearEqual	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMPlaneNotEqual		proto :FXMVECTOR, :FXMVECTOR
XMPlaneIsNaN		proto :FXMVECTOR
XMPlaneIsInfinite	proto :FXMVECTOR

XMPlaneDot		proto :FXMVECTOR, :FXMVECTOR
XMPlaneDotCoord		proto :FXMVECTOR, :FXMVECTOR
XMPlaneDotNormal	proto :FXMVECTOR, :FXMVECTOR
XMPlaneNormalizeEst	proto :FXMVECTOR
XMPlaneNormalize	proto :FXMVECTOR
XMPlaneIntersectLine	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR

XMPlaneIntersectPlane	proto :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR, :FXMVECTOR

XMPlaneTransform	proto :FXMVECTOR, :FXMMATRIX
XMPlaneTransformStream	proto :ptr XMFLOAT4, :size_t, :ptr XFLOAT4, :size_t, :size_t, :FXMMATRIX

XMPlaneFromPointNormal	proto :FXMVECTOR, :FXMVECTOR
XMPlaneFromPoints	proto :FXMVECTOR, :FXMVECTOR, :FXMVECTOR

XMColorEqual		proto :FXMVECTOR, :FXMVECTOR
XMColorNotEqual		proto :FXMVECTOR, :FXMVECTOR
XMColorGreater		proto :FXMVECTOR, :FXMVECTOR
XMColorGreaterOrEqual	proto :FXMVECTOR, :FXMVECTOR
XMColorLess		proto :FXMVECTOR, :FXMVECTOR
XMColorLessOrEqual	proto :FXMVECTOR, :FXMVECTOR

XMColorIsNaN		proto :FXMVECTOR
XMColorIsInfinite	proto :FXMVECTOR

XMColorNegative		proto :FXMVECTOR
XMColorModulate		proto :FXMVECTOR, :FXMVECTOR
XMColorAdjustSaturation proto :FXMVECTOR, :float
XMColorAdjustContrast	proto :FXMVECTOR, :float

XMColorRGBToHSL		proto :FXMVECTOR
XMColorHSLToRGB		proto :FXMVECTOR

XMColorRGBToHSV		proto :FXMVECTOR
XMColorHSVToRGB		proto :FXMVECTOR

XMColorRGBToYUV		proto :FXMVECTOR
XMColorYUVToRGB		proto :FXMVECTOR

XMColorRGBToYUV_HD	proto :FXMVECTOR
XMColorYUVToRGB_HD	proto :FXMVECTOR

XMColorRGBToXYZ		proto :FXMVECTOR
XMColorXYZToRGB		proto :FXMVECTOR

XMColorXYZToSRGB	proto :FXMVECTOR
XMColorSRGBToXYZ	proto :FXMVECTOR

XMColorRGBToSRGB	proto :FXMVECTOR
XMColorSRGBToRGB	proto :FXMVECTOR

XMVerifyCPUSupport	proto

XMFresnelTerm		proto :FXMVECTOR, :FXMVECTOR

XMScalarNearEqual	proto :float, :float, :float
XMScalarModAngle	proto :float
XMScalarSin		proto :float
XMScalarSinEst		proto :float
XMScalarCos		proto :float
XMScalarCosEst		proto :float

XMScalarSinCos		proto :ptr float, :ptr float, :float
XMScalarSinCosEst	proto :ptr float, :ptr float, :float
XMScalarASin		proto :float
XMScalarASinEst		proto :float

XMScalarACos		proto :float
XMScalarACosEst		proto :float

if defined(__XNAMATH_H__) and defined(XMMin)
undef XMMin
undef XMMax
endif

XMMin macro a, b
    if a < b
	exitm<a>
    endif
    exitm<b>
    endm

XMMax macro a, b
    if a > b
	exitm<a>
    endif
    exitm<b>
    endm

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
endif

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
else
endif

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
endif

if defined(_XM_SSE4_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
endif

if not defined(_XM_NO_INTRINSICS_)
endif

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
else
endif

if defined(_XM_SSE_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
endif

if defined(_XM_SSE3_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
endif

if defined(_XM_AVX2_INTRINSICS_) and not defined(_XM_NO_INTRINSICS_)
endif

ifndef _XM_NO_INTRINSICS_
endif

ifndef XMGLOBALCONST
XMGLOBALCONST		equ <extern __declspec(selectany)>
endif

externdef g_XMSinCoefficients0	:XMVECTORF32
externdef g_XMSinCoefficients1	:XMVECTORF32
externdef g_XMCosCoefficients0	:XMVECTORF32
externdef g_XMCosCoefficients1	:XMVECTORF32
externdef g_XMTanCoefficients0	:XMVECTORF32
externdef g_XMTanCoefficients1	:XMVECTORF32
externdef g_XMTanCoefficients2	:XMVECTORF32
externdef g_XMArcCoefficients0	:XMVECTORF32
externdef g_XMArcCoefficients1	:XMVECTORF32
externdef g_XMATanCoefficients0 :XMVECTORF32
externdef g_XMATanCoefficients1 :XMVECTORF32
externdef g_XMATanEstCoefficients0:XMVECTORF32
externdef g_XMATanEstCoefficients1:XMVECTORF32
externdef g_XMTanEstCoefficients:XMVECTORF32
externdef g_XMArcEstCoefficients:XMVECTORF32
externdef g_XMPiConstants0	:XMVECTORF32
externdef g_XMIdentityR0	:XMVECTORF32
externdef g_XMIdentityR1	:XMVECTORF32
externdef g_XMIdentityR2	:XMVECTORF32
externdef g_XMIdentityR3	:XMVECTORF32
externdef g_XMNegIdentityR0	:XMVECTORF32
externdef g_XMNegIdentityR1	:XMVECTORF32
externdef g_XMNegIdentityR2	:XMVECTORF32
externdef g_XMNegIdentityR3	:XMVECTORF32

externdef g_XMNegativeZero	:XMVECTORU32
externdef g_XMNegate3		:XMVECTORU32
externdef g_XMMaskXY		:XMVECTORU32
externdef g_XMMask3		:XMVECTORU32
externdef g_XMMaskX		:XMVECTORU32
externdef g_XMMaskY		:XMVECTORU32
externdef g_XMMaskZ		:XMVECTORU32
externdef g_XMMaskW		:XMVECTORU32

externdef g_XMOne		:XMVECTORF32
externdef g_XMOne3		:XMVECTORF32
externdef g_XMZero		:XMVECTORF32
externdef g_XMTwo		:XMVECTORF32
externdef g_XMFour		:XMVECTORF32
externdef g_XMSix		:XMVECTORF32
externdef g_XMNegativeOne	:XMVECTORF32
externdef g_XMOneHalf		:XMVECTORF32
externdef g_XMNegativeOneHalf	:XMVECTORF32
externdef g_XMNegativeTwoPi	:XMVECTORF32
externdef g_XMNegativePi	:XMVECTORF32
externdef g_XMHalfPi		:XMVECTORF32
externdef g_XMPi		:XMVECTORF32
externdef g_XMReciprocalPi	:XMVECTORF32
externdef g_XMTwoPi		:XMVECTORF32
externdef g_XMReciprocalTwoPi	:XMVECTORF32
externdef g_XMEpsilon		:XMVECTORF32

externdef g_XMInfinity		:XMVECTORI32
externdef g_XMQNaN		:XMVECTORI32
externdef g_XMQNaNTest		:XMVECTORI32
externdef g_XMAbsMask		:XMVECTORI32
externdef g_XMFltMin		:XMVECTORI32
externdef g_XMFltMax		:XMVECTORI32

externdef g_XMNegOneMask	:XMVECTORU32
externdef g_XMMaskA8R8G8B8	:XMVECTORU32
externdef g_XMFlipA8R8G8B8	:XMVECTORU32

externdef g_XMFixAA8R8G8B8	:XMVECTORF32
externdef g_XMNormalizeA8R8G8B8 :XMVECTORF32

externdef g_XMMaskA2B10G10R10	:XMVECTORU32
externdef g_XMFlipA2B10G10R10	:XMVECTORU32

externdef g_XMFixAA2B10G10R10	:XMVECTORF32
externdef g_XMNormalizeA2B10G10R10:XMVECTORF32
externdef g_XMMaskX16Y16	:XMVECTORU32
externdef g_XMFlipX16Y16	:XMVECTORI32
externdef g_XMFixX16Y16		:XMVECTORF32
externdef g_XMNormalizeX16Y16	:XMVECTORF32
externdef g_XMMaskX16Y16Z16W16	:XMVECTORU32
externdef g_XMFlipX16Y16Z16W16	:XMVECTORI32
externdef g_XMFixX16Y16Z16W16	:XMVECTORF32
externdef g_XMNormalizeX16Y16Z16W16:XMVECTORF32
externdef g_XMNoFraction	:XMVECTORF32
externdef g_XMMaskByte		:XMVECTORI32
externdef g_XMNegateX		:XMVECTORF32
externdef g_XMNegateY		:XMVECTORF32
externdef g_XMNegateZ		:XMVECTORF32
externdef g_XMNegateW		:XMVECTORF32
externdef g_XMSelect0101	:XMVECTORU32
externdef g_XMSelect1010	:XMVECTORU32
externdef g_XMOneHalfMinusEpsilon:XMVECTORI32
externdef g_XMSelect1000	:XMVECTORU32
externdef g_XMSelect1100	:XMVECTORU32
externdef g_XMSelect1110	:XMVECTORU32
externdef g_XMSelect1011	:XMVECTORU32
externdef g_XMFixupY16		:XMVECTORF32
externdef g_XMFixupY16W16	:XMVECTORF32
externdef g_XMFlipY		:XMVECTORU32
externdef g_XMFlipZ		:XMVECTORU32
externdef g_XMFlipW		:XMVECTORU32
externdef g_XMFlipYZ		:XMVECTORU32
externdef g_XMFlipZW		:XMVECTORU32
externdef g_XMFlipYW		:XMVECTORU32
externdef g_XMMaskDec4		:XMVECTORI32
externdef g_XMXorDec4		:XMVECTORI32
externdef g_XMAddUDec4		:XMVECTORF32
externdef g_XMAddDec4		:XMVECTORF32
externdef g_XMMulDec4		:XMVECTORF32
externdef g_XMMaskByte4		:XMVECTORU32
externdef g_XMXorByte4		:XMVECTORI32
externdef g_XMAddByte4		:XMVECTORF32
externdef g_XMFixUnsigned	:XMVECTORF32
externdef g_XMMaxInt		:XMVECTORF32
externdef g_XMMaxUInt		:XMVECTORF32
externdef g_XMUnsignedFix	:XMVECTORF32
externdef g_XMsrgbScale		:XMVECTORF32
externdef g_XMsrgbA		:XMVECTORF32
externdef g_XMsrgbA1		:XMVECTORF32
externdef g_XMExponentBias	:XMVECTORI32
externdef g_XMSubnormalExponent :XMVECTORI32
externdef g_XMNumTrailing	:XMVECTORI32
externdef g_XMMinNormal		:XMVECTORI32
externdef g_XMNegInfinity	:XMVECTORU32
externdef g_XMNegQNaN		:XMVECTORU32
externdef g_XMBin128		:XMVECTORI32
externdef g_XMBinNeg150		:XMVECTORU32
externdef g_XM253		:XMVECTORI32
externdef g_XMExpEst1		:XMVECTORF32
externdef g_XMExpEst2		:XMVECTORF32
externdef g_XMExpEst3		:XMVECTORF32
externdef g_XMExpEst4		:XMVECTORF32
externdef g_XMExpEst5		:XMVECTORF32
externdef g_XMExpEst6		:XMVECTORF32
externdef g_XMExpEst7		:XMVECTORF32
externdef g_XMLogEst0		:XMVECTORF32
externdef g_XMLogEst1		:XMVECTORF32
externdef g_XMLogEst2		:XMVECTORF32
externdef g_XMLogEst3		:XMVECTORF32
externdef g_XMLogEst4		:XMVECTORF32
externdef g_XMLogEst5		:XMVECTORF32
externdef g_XMLogEst6		:XMVECTORF32
externdef g_XMLogEst7		:XMVECTORF32
externdef g_XMLgE		:XMVECTORF32
externdef g_XMInvLgE		:XMVECTORF32
externdef g_UByteMax		:XMVECTORF32
externdef g_ByteMin		:XMVECTORF32
externdef g_ByteMax		:XMVECTORF32
externdef g_ShortMin		:XMVECTORF32
externdef g_ShortMax		:XMVECTORF32
externdef g_UShortMax		:XMVECTORF32

externdef RGBA_AliceBlue	:XMVECTORF32
externdef RGBA_AntiqueWhite	:XMVECTORF32
externdef RGBA_Aqua		:XMVECTORF32
externdef RGBA_Aquamarine	:XMVECTORF32
externdef RGBA_Azure		:XMVECTORF32
externdef RGBA_Beige		:XMVECTORF32
externdef RGBA_Bisque		:XMVECTORF32
externdef RGBA_Black		:XMVECTORF32
externdef RGBA_BlanchedAlmond	:XMVECTORF32
externdef RGBA_Blue		:XMVECTORF32
externdef RGBA_BlueViolet	:XMVECTORF32
externdef RGBA_Brown		:XMVECTORF32
externdef RGBA_BurlyWood	:XMVECTORF32
externdef RGBA_CadetBlue	:XMVECTORF32
externdef RGBA_Chartreuse	:XMVECTORF32
externdef RGBA_Chocolate	:XMVECTORF32
externdef RGBA_Coral		:XMVECTORF32
externdef RGBA_CornflowerBlue	:XMVECTORF32
externdef RGBA_Cornsilk		:XMVECTORF32
externdef RGBA_Crimson		:XMVECTORF32
externdef RGBA_Cyan		:XMVECTORF32
externdef RGBA_DarkBlue		:XMVECTORF32
externdef RGBA_DarkCyan		:XMVECTORF32
externdef RGBA_DarkGoldenrod	:XMVECTORF32
externdef RGBA_DarkGray		:XMVECTORF32
externdef RGBA_DarkGreen	:XMVECTORF32
externdef RGBA_DarkKhaki	:XMVECTORF32
externdef RGBA_DarkMagenta	:XMVECTORF32
externdef RGBA_DarkOliveGreen	:XMVECTORF32
externdef RGBA_DarkOrange	:XMVECTORF32
externdef RGBA_DarkOrchid	:XMVECTORF32
externdef RGBA_DarkRed		:XMVECTORF32
externdef RGBA_DarkSalmon	:XMVECTORF32
externdef RGBA_DarkSeaGreen	:XMVECTORF32
externdef RGBA_DarkSlateBlue	:XMVECTORF32
externdef RGBA_DarkSlateGray	:XMVECTORF32
externdef RGBA_DarkTurquoise	:XMVECTORF32
externdef RGBA_DarkViolet	:XMVECTORF32
externdef RGBA_DeepPink		:XMVECTORF32
externdef RGBA_DeepSkyBlue	:XMVECTORF32
externdef RGBA_DimGray		:XMVECTORF32
externdef RGBA_DodgerBlue	:XMVECTORF32
externdef RGBA_Firebrick	:XMVECTORF32
externdef RGBA_FloralWhite	:XMVECTORF32
externdef RGBA_ForestGreen	:XMVECTORF32
externdef RGBA_Fuchsia		:XMVECTORF32
externdef RGBA_Gainsboro	:XMVECTORF32
externdef RGBA_GhostWhite	:XMVECTORF32
externdef RGBA_Gold		:XMVECTORF32
externdef RGBA_Goldenrod	:XMVECTORF32
externdef RGBA_Gray		:XMVECTORF32
externdef RGBA_Green		:XMVECTORF32
externdef RGBA_GreenYellow	:XMVECTORF32
externdef RGBA_Honeydew		:XMVECTORF32
externdef RGBA_HotPink		:XMVECTORF32
externdef RGBA_IndianRed	:XMVECTORF32
externdef RGBA_Indigo		:XMVECTORF32
externdef RGBA_Ivory		:XMVECTORF32
externdef RGBA_Khaki		:XMVECTORF32
externdef RGBA_Lavender		:XMVECTORF32
externdef RGBA_LavenderBlush	:XMVECTORF32
externdef RGBA_LawnGreen	:XMVECTORF32
externdef RGBA_LemonChiffon	:XMVECTORF32
externdef RGBA_LightBlue	:XMVECTORF32
externdef RGBA_LightCoral	:XMVECTORF32
externdef RGBA_LightCyan	:XMVECTORF32
externdef RGBA_LightGoldenrodYellow :XMVECTORF32
externdef RGBA_LightGreen	:XMVECTORF32
externdef RGBA_LightGray	:XMVECTORF32
externdef RGBA_LightPink	:XMVECTORF32
externdef RGBA_LightSalmon	:XMVECTORF32
externdef RGBA_LightSeaGreen	:XMVECTORF32
externdef RGBA_LightSkyBlue	:XMVECTORF32
externdef RGBA_LightSlateGray	:XMVECTORF32
externdef RGBA_LightSteelBlue	:XMVECTORF32
externdef RGBA_LightYellow	:XMVECTORF32
externdef RGBA_Lime		:XMVECTORF32
externdef RGBA_LimeGreen	:XMVECTORF32
externdef RGBA_Linen		:XMVECTORF32
externdef RGBA_Magenta		:XMVECTORF32
externdef RGBA_Maroon		:XMVECTORF32
externdef RGBA_MediumAquamarine :XMVECTORF32
externdef RGBA_MediumBlue	:XMVECTORF32
externdef RGBA_MediumOrchid	:XMVECTORF32
externdef RGBA_MediumPurple	:XMVECTORF32
externdef RGBA_MediumSeaGreen	:XMVECTORF32
externdef RGBA_MediumSlateBlue	:XMVECTORF32
externdef RGBA_MediumSpringGreen:XMVECTORF32
externdef RGBA_MediumTurquoise	:XMVECTORF32
externdef RGBA_MediumVioletRed	:XMVECTORF32
externdef RGBA_MidnightBlue	:XMVECTORF32
externdef RGBA_MintCream	:XMVECTORF32
externdef RGBA_MistyRose	:XMVECTORF32
externdef RGBA_Moccasin		:XMVECTORF32
externdef RGBA_NavajoWhite	:XMVECTORF32
externdef RGBA_Navy		:XMVECTORF32
externdef RGBA_OldLace		:XMVECTORF32
externdef RGBA_Olive		:XMVECTORF32
externdef RGBA_OliveDrab	:XMVECTORF32
externdef RGBA_Orange		:XMVECTORF32
externdef RGBA_OrangeRed	:XMVECTORF32
externdef RGBA_Orchid		:XMVECTORF32
externdef RGBA_PaleGoldenrod	:XMVECTORF32
externdef RGBA_PaleGreen	:XMVECTORF32
externdef RGBA_PaleTurquoise	:XMVECTORF32
externdef RGBA_PaleVioletRed	:XMVECTORF32
externdef RGBA_PapayaWhip	:XMVECTORF32
externdef RGBA_PeachPuff	:XMVECTORF32
externdef RGBA_Peru		:XMVECTORF32
externdef RGBA_Pink		:XMVECTORF32
externdef RGBA_Plum		:XMVECTORF32
externdef RGBA_PowderBlue	:XMVECTORF32
externdef RGBA_Purple		:XMVECTORF32
externdef RGBA_Red		:XMVECTORF32
externdef RGBA_RosyBrown	:XMVECTORF32
externdef RGBA_RoyalBlue	:XMVECTORF32
externdef RGBA_SaddleBrown	:XMVECTORF32
externdef RGBA_Salmon		:XMVECTORF32
externdef RGBA_SandyBrown	:XMVECTORF32
externdef RGBA_SeaGreen		:XMVECTORF32
externdef RGBA_SeaShell		:XMVECTORF32
externdef RGBA_Sienna		:XMVECTORF32
externdef RGBA_Silver		:XMVECTORF32
externdef RGBA_SkyBlue		:XMVECTORF32
externdef RGBA_SlateBlue	:XMVECTORF32
externdef RGBA_SlateGray	:XMVECTORF32
externdef RGBA_Snow		:XMVECTORF32
externdef RGBA_SpringGreen	:XMVECTORF32
externdef RGBA_SteelBlue	:XMVECTORF32
externdef RGBA_Tan		:XMVECTORF32
externdef RGBA_Teal		:XMVECTORF32
externdef RGBA_Thistle		:XMVECTORF32
externdef RGBA_Tomato		:XMVECTORF32
externdef RGBA_Transparent	:XMVECTORF32
externdef RGBA_Turquoise	:XMVECTORF32
externdef RGBA_Violet		:XMVECTORF32
externdef RGBA_Wheat		:XMVECTORF32
externdef RGBA_White		:XMVECTORF32
externdef RGBA_WhiteSmoke	:XMVECTORF32
externdef RGBA_Yellow		:XMVECTORF32
externdef RGBA_YellowGreen	:XMVECTORF32

if defined(_XM_NO_INTRINSICS_)
else
endif
if defined(_XM_NO_INTRINSICS_)
else
endif

.pragma list(pop)
endif
