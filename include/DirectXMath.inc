.pragma list(push, 0)

ifndef __DIRECTXMATH_INC
__DIRECTXMATH_INC equ <>

include libc.inc

DIRECTX_MATH_VERSION	equ 312

ifndef __PE__
includelib directxmath.lib
endif

if defined(_MSC_VER) and  _MSC_VER LT 1200 ; 1800
 .err <DirectX Math requires Visual C++ 2013 or later.>
endif

if defined(_MSC_VER) and \
   not defined(_M_IX86_FP) and \
   not defined(_XM_NO_INTRINSICS_) and \
   not defined(_XM_VECTORCALL_)
_XM_VECTORCALL_		equ 1
elseifndef _XM_VECTORCALL_
_XM_VECTORCALL_		equ 0
endif

if _XM_VECTORCALL_
XM_CALLCONV		equ <vectorcall>
else
XM_CALLCONV		equ <>
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
XM_PERMUTE_PS macro v, imm
	exitm<_mm_permute_ps( v, imm )>
	endm
else
XM_PERMUTE_PS macro v:=<xmm0>, imm:=<0>
	shufps v,v,imm
	retm<v>
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
	l64	__n64 <>
	h64	__n64 <>
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
AXMMATRIX	equ <V0:XMVECTOR,V1:XMVECTOR,V2:XMVECTOR,V3:XMVECTOR>
AXMMATRIX3	equ <V0:XMVECTOR,V1:XMVECTOR,V2:XMVECTOR>
XMTHISPTR	equ <>
else
FXMMATRIX	typedef ptr XMMATRIX
AXMMATRIX	equ <M:FXMMATRIX>
AXMMATRIX3	equ <M:FXMMATRIX>
XMTHISPTR	equ <this:ptr>
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

XMConvertVectorIntToFloat	proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMConvertVectorFloatToInt	proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMConvertVectorUIntToFloat	proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMConvertVectorFloatToUInt	proto XM_CALLCONV :FXMVECTOR, :uint32_t

if defined(__XNAMATH_H__) and defined(XMVectorSetBinaryConstant)
undef XMVectorSetBinaryConstant
undef XMVectorSplatConstant
undef XMVectorSplatConstantInt
endif

XMVectorSetBinaryConstant	proto XM_CALLCONV :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorSplatConstant		proto XM_CALLCONV :int32_t, :uint32_t
XMVectorSplatConstantInt	proto XM_CALLCONV :int32_t

XMLoadInt	proto XM_CALLCONV :ptr uint32_t
XMLoadFloat	proto XM_CALLCONV :ptr float

XMLoadInt2	proto XM_CALLCONV :ptr uint32_t
XMLoadInt2A	proto XM_CALLCONV :ptr uint32_t
XMLoadFloat2	proto XM_CALLCONV :ptr XMFLOAT2
XMLoadFloat2A	proto XM_CALLCONV :ptr XMFLOAT2A
XMLoadSInt2	proto XM_CALLCONV :ptr XMINT2
XMLoadUInt2	proto XM_CALLCONV :ptr XMUINT2

XMLoadInt3	proto XM_CALLCONV :ptr uint32_t
XMLoadInt3A	proto XM_CALLCONV :ptr uint32_t
XMLoadFloat3	proto XM_CALLCONV :ptr XMFLOAT3
XMLoadFloat3A	proto XM_CALLCONV :ptr XMFLOAT3A
XMLoadSInt3	proto XM_CALLCONV :ptr XMINT3
XMLoadUInt3	proto XM_CALLCONV :ptr XMUINT3

XMLoadInt4	proto XM_CALLCONV :ptr uint32_t
XMLoadInt4A	proto XM_CALLCONV :ptr uint32_t
XMLoadFloat4	proto XM_CALLCONV :ptr XMFLOAT4
XMLoadFloat4A	proto XM_CALLCONV :ptr XMFLOAT4A
XMLoadSInt4	proto XM_CALLCONV :ptr XMINT4
XMLoadUInt4	proto XM_CALLCONV :ptr XMUINT4

XMLoadFloat3x3	proto XM_CALLCONV XMTHISPTR, :ptr XMFLOAT3X3
XMLoadFloat4x3	proto XM_CALLCONV XMTHISPTR, :ptr XMFLOAT4X3
XMLoadFloat4x3A proto XM_CALLCONV XMTHISPTR, :ptr XMFLOAT4X3;A
XMLoadFloat4x4	proto XM_CALLCONV XMTHISPTR, :ptr XMFLOAT4X4
XMLoadFloat4x4A proto XM_CALLCONV XMTHISPTR, :ptr XMFLOAT4X4;A

XMStoreInt	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreFloat	proto XM_CALLCONV :ptr REAL4, :FXMVECTOR
XMStoreInt2	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreInt2A	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreFloat2	proto XM_CALLCONV :ptr XMFLOAT2, :FXMVECTOR
XMStoreFloat2A	proto XM_CALLCONV :ptr XMFLOAT2, :FXMVECTOR
XMStoreSInt2	proto XM_CALLCONV :ptr XMINT2, :FXMVECTOR
XMStoreUInt2	proto XM_CALLCONV :ptr XMUINT2, :FXMVECTOR
XMStoreInt3	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreInt3A	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreFloat3	proto XM_CALLCONV :ptr XMFLOAT3, :FXMVECTOR
XMStoreFloat3A	proto XM_CALLCONV :ptr XMFLOAT3, :FXMVECTOR
XMStoreSInt3	proto XM_CALLCONV :ptr XMINT3, :FXMVECTOR
XMStoreUInt3	proto XM_CALLCONV :ptr XMUINT3, :FXMVECTOR
XMStoreInt4	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreInt4A	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMStoreFloat4	proto XM_CALLCONV :ptr XMFLOAT4, :FXMVECTOR
XMStoreFloat4A	proto XM_CALLCONV :ptr XMFLOAT4, :FXMVECTOR
XMStoreSInt4	proto XM_CALLCONV :ptr XMINT4, :FXMVECTOR
XMStoreUInt4	proto XM_CALLCONV :ptr XMUINT4, :FXMVECTOR

XMStoreFloat3x3 proto XM_CALLCONV :ptr XMFLOAT3X3, AXMMATRIX3
XMStoreFloat4x3 proto XM_CALLCONV :ptr XMFLOAT4X3, AXMMATRIX
XMStoreFloat4x3A proto XM_CALLCONV :ptr XMFLOAT4X3, AXMMATRIX
XMStoreFloat4x4 proto XM_CALLCONV :ptr XMFLOAT4X4, AXMMATRIX
XMStoreFloat4x4A proto XM_CALLCONV :ptr XMFLOAT4X4, AXMMATRIX

XMVectorZero	proto XM_CALLCONV
XMVectorSet	proto XM_CALLCONV :float, :float, :float, :float

XMVectorSetInt		proto XM_CALLCONV :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorReplicate	proto XM_CALLCONV :float
XMVectorReplicatePtr	proto XM_CALLCONV :ptr float
XMVectorReplicateInt	proto XM_CALLCONV :uint32_t
XMVectorReplicateIntPtr proto XM_CALLCONV :ptr uint32_t
XMVectorTrueInt		proto XM_CALLCONV
XMVectorFalseInt	proto XM_CALLCONV
XMVectorSplatX		proto XM_CALLCONV :FXMVECTOR
XMVectorSplatY		proto XM_CALLCONV :FXMVECTOR
XMVectorSplatZ		proto XM_CALLCONV :FXMVECTOR
XMVectorSplatW		proto XM_CALLCONV :FXMVECTOR
XMVectorSplatOne	proto XM_CALLCONV
XMVectorSplatInfinity	proto XM_CALLCONV
XMVectorSplatQNaN	proto XM_CALLCONV
XMVectorSplatEpsilon	proto XM_CALLCONV
XMVectorSplatSignMask	proto XM_CALLCONV

XMVectorGetByIndex	proto XM_CALLCONV :FXMVECTOR, :size_t
XMVectorGetX		proto XM_CALLCONV :FXMVECTOR
XMVectorGetY		proto XM_CALLCONV :FXMVECTOR
XMVectorGetZ		proto XM_CALLCONV :FXMVECTOR
XMVectorGetW		proto XM_CALLCONV :FXMVECTOR
XMVectorGetByIndexPtr	proto XM_CALLCONV :ptr float, :FXMVECTOR, :size_t
XMVectorGetXPtr		proto XM_CALLCONV :ptr float, :FXMVECTOR
XMVectorGetYPtr		proto XM_CALLCONV :ptr float, :FXMVECTOR
XMVectorGetZPtr		proto XM_CALLCONV :ptr float, :FXMVECTOR
XMVectorGetWPtr		proto XM_CALLCONV :ptr float, :FXMVECTOR

XMVectorGetIntByIndex	proto XM_CALLCONV :FXMVECTOR, :size_t
XMVectorGetIntX		proto XM_CALLCONV :FXMVECTOR
XMVectorGetIntY		proto XM_CALLCONV :FXMVECTOR
XMVectorGetIntZ		proto XM_CALLCONV :FXMVECTOR
XMVectorGetIntW		proto XM_CALLCONV :FXMVECTOR

XMVectorGetIntByIndexPtr proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR, :size_t
XMVectorGetIntXPtr	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMVectorGetIntYPtr	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMVectorGetIntZPtr	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR
XMVectorGetIntWPtr	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR

XMVectorSetByIndex	proto XM_CALLCONV :FXMVECTOR, :float, :size_t
XMVectorSetX		proto XM_CALLCONV :FXMVECTOR, :float
XMVectorSetY		proto XM_CALLCONV :FXMVECTOR, :float
XMVectorSetZ		proto XM_CALLCONV :FXMVECTOR, :float
XMVectorSetW		proto XM_CALLCONV :FXMVECTOR, :float

XMVectorSetByIndexPtr	proto XM_CALLCONV :FXMVECTOR, :ptr float, :size_t
XMVectorSetXPtr		proto XM_CALLCONV :FXMVECTOR, :ptr float
XMVectorSetYPtr		proto XM_CALLCONV :FXMVECTOR, :ptr float
XMVectorSetZPtr		proto XM_CALLCONV :FXMVECTOR, :ptr float
XMVectorSetWPtr		proto XM_CALLCONV :FXMVECTOR, :ptr float

XMVectorSetIntByIndex	proto XM_CALLCONV :FXMVECTOR, :uint32_t, :size_t
XMVectorSetIntX		proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMVectorSetIntY		proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMVectorSetIntZ		proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMVectorSetIntW		proto XM_CALLCONV :FXMVECTOR, :uint32_t

XMVectorSetIntByIndexPtr proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t, :size_t
XMVectorSetIntXPtr	proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t
XMVectorSetIntYPtr	proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t
XMVectorSetIntZPtr	proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t
XMVectorSetIntWPtr	proto XM_CALLCONV :FXMVECTOR, :ptr uint32_t

if defined(__XNAMATH_H__) and defined(XMVectorSwizzle)
undef XMVectorSwizzle
endif

XMVectorSwizzle		proto XM_CALLCONV :FXMVECTOR, :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorPermute		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorSelectControl	proto XM_CALLCONV :uint32_t, :uint32_t, :uint32_t, :uint32_t
XMVectorSelect		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorMergeXY		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorMergeZW		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR

if defined(__XNAMATH_H__) and defined(XMVectorShiftLeft)
undef XMVectorShiftLeft
undef XMVectorRotateLeft
undef XMVectorRotateRight
undef XMVectorInsert
endif

XMVectorShiftLeft	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :uint32_t
XMVectorRotateLeft	proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMVectorRotateRight	proto XM_CALLCONV :FXMVECTOR, :uint32_t
XMVectorInsert		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :uint32_t, :uint32_t, :uint32_t, :uint32_t, :uint32_t

XMVectorEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorEqualR		proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorEqualInt	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorEqualIntR	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorNearEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorNotEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorNotEqualInt	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorGreater		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorGreaterR	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorGreaterOrEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorGreaterOrEqualR proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR, :FXMVECTOR
XMVectorLess		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorLessOrEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorInBounds	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorInBoundsR	proto XM_CALLCONV :ptr uint32_t, :FXMVECTOR, :FXMVECTOR

XMVectorIsNaN		proto XM_CALLCONV :FXMVECTOR
XMVectorIsInfinite	proto XM_CALLCONV :FXMVECTOR

XMVectorMin		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorMax		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorRound		proto XM_CALLCONV :FXMVECTOR
XMVectorTruncate	proto XM_CALLCONV :FXMVECTOR
XMVectorFloor		proto XM_CALLCONV :FXMVECTOR
XMVectorCeiling		proto XM_CALLCONV :FXMVECTOR
XMVectorClamp		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorSaturate	proto XM_CALLCONV :FXMVECTOR

XMVectorAndInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorAndCInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorOrInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorNorInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorXorInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorNegate		proto XM_CALLCONV :FXMVECTOR

XMVectorAdd		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorSum		proto XM_CALLCONV :FXMVECTOR
XMVectorAddAngles	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorSubtract	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR

XMVectorSubtractAngles	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorMultiply	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorMultiplyAdd	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorDivide		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorNegativeMultiplySubtract proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorScale		proto XM_CALLCONV :FXMVECTOR, :float
XMVectorReciprocalEst	proto XM_CALLCONV :FXMVECTOR
XMVectorReciprocal	proto XM_CALLCONV :FXMVECTOR
XMVectorSqrtEst		proto XM_CALLCONV :FXMVECTOR
XMVectorSqrt		proto XM_CALLCONV :FXMVECTOR
XMVectorReciprocalSqrtEst proto XM_CALLCONV :FXMVECTOR
XMVectorReciprocalSqrt	proto XM_CALLCONV :FXMVECTOR
XMVectorExp2		proto XM_CALLCONV :FXMVECTOR
XMVectorExpE		proto XM_CALLCONV :FXMVECTOR
XMVectorExp		proto XM_CALLCONV :FXMVECTOR
XMVectorLog2		proto XM_CALLCONV :FXMVECTOR
XMVectorLogE		proto XM_CALLCONV :FXMVECTOR
XMVectorLog		proto XM_CALLCONV :FXMVECTOR
XMVectorPow		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorAbs		proto XM_CALLCONV :FXMVECTOR
XMVectorMod		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorModAngles	proto XM_CALLCONV :FXMVECTOR
XMVectorSin		proto XM_CALLCONV :FXMVECTOR
XMVectorSinEst		proto XM_CALLCONV :FXMVECTOR
XMVectorCos		proto XM_CALLCONV :FXMVECTOR
XMVectorCosEst		proto XM_CALLCONV :FXMVECTOR

XMVectorSinCos		proto XM_CALLCONV :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR
XMVectorSinCosEst	proto XM_CALLCONV :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR

XMVectorTan		proto XM_CALLCONV :FXMVECTOR
XMVectorTanEst		proto XM_CALLCONV :FXMVECTOR
XMVectorSinH		proto XM_CALLCONV :FXMVECTOR
XMVectorCosH		proto XM_CALLCONV :FXMVECTOR
XMVectorTanH		proto XM_CALLCONV :FXMVECTOR
XMVectorASin		proto XM_CALLCONV :FXMVECTOR
XMVectorASinEst		proto XM_CALLCONV :FXMVECTOR
XMVectorACos		proto XM_CALLCONV :FXMVECTOR
XMVectorACosEst		proto XM_CALLCONV :FXMVECTOR
XMVectorATan		proto XM_CALLCONV :FXMVECTOR
XMVectorATanEst		proto XM_CALLCONV :FXMVECTOR
XMVectorATan2		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorATan2Est	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVectorLerp		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :float
XMVectorLerpV		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVectorHermite		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :float
XMVectorHermiteV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR
XMVectorCatmullRom	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :float
XMVectorCatmullRomV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR
XMVectorBaryCentric	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :float, :float
XMVectorBaryCentricV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR

XMVector2Equal		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2EqualR		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2EqualInt	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2EqualIntR	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2NearEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2NotEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2NotEqualInt	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2Greater	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2GreaterR	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2GreaterOrEqual proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2GreaterOrEqualR proto XM_CALLCONV :FXMVECTOR,:FXMVECTOR
XMVector2Less		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2LessOrEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2InBounds	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR

XMVector2IsNaN		proto XM_CALLCONV :FXMVECTOR
XMVector2IsInfinite	proto XM_CALLCONV :FXMVECTOR

XMVector2Dot		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2Cross		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2LengthSq	proto XM_CALLCONV :FXMVECTOR
XMVector2ReciprocalLengthEst proto XM_CALLCONV :FXMVECTOR
XMVector2ReciprocalLength proto XM_CALLCONV :FXMVECTOR
XMVector2LengthEst	proto XM_CALLCONV :FXMVECTOR
XMVector2Length		proto XM_CALLCONV :FXMVECTOR
XMVector2NormalizeEst	proto XM_CALLCONV :FXMVECTOR
XMVector2Normalize	proto XM_CALLCONV :FXMVECTOR
XMVector2ClampLength	proto XM_CALLCONV :FXMVECTOR, :float, :float
XMVector2ClampLengthV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2Reflect	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2Refract	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :float
XMVector2RefractV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2Orthogonal	proto XM_CALLCONV :FXMVECTOR

XMVector2AngleBetweenNormalsEst proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2AngleBetweenNormals	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2AngleBetweenVectors	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector2LinePointDistance	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector2IntersectLine		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR
XMVector2Transform		proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX

XMVector2TransformStream	proto XM_CALLCONV :ptr XMFLOAT4, :size_t, :ptr XMFLOAT2, :size_t, :size_t, :FXMMATRIX
XMVector2TransformCoord		proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX
XMVector2TransformCoordStream	proto XM_CALLCONV :ptr XMFLOAT2, :size_t, :ptr XMFLOAT2, :size_t, :size_t, :FXMMATRIX
XMVector2TransformNormal	proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX
XMVector2TransformNormalStream	proto XM_CALLCONV :ptr XMFLOAT2, :size_t, :ptr XMFLOAT2, :size_t, :size_t, :FXMMATRIX

XMVector3Equal		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3EqualR		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3EqualInt	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3EqualIntR	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3NearEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector3NotEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3NotEqualInt	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3Greater	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3GreaterR	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3GreaterOrEqual proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3GreaterOrEqualR proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3Less		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3LessOrEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3InBounds	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR

XMVector3IsNaN		proto XM_CALLCONV :FXMVECTOR
XMVector3IsInfinite	proto XM_CALLCONV :FXMVECTOR
XMVector3Dot		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3Cross		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3LengthSq	proto XM_CALLCONV :FXMVECTOR
XMVector3ReciprocalLengthEst proto XM_CALLCONV :FXMVECTOR
XMVector3ReciprocalLength proto XM_CALLCONV :FXMVECTOR
XMVector3LengthEst	proto XM_CALLCONV :FXMVECTOR
XMVector3Length		proto XM_CALLCONV :FXMVECTOR
XMVector3NormalizeEst	proto XM_CALLCONV :FXMVECTOR
XMVector3Normalize	proto XM_CALLCONV :FXMVECTOR
XMMatrixTranspose	proto XM_CALLCONV XMTHISPTR, AXMMATRIX
XMMatrixMultiplyTranspose proto XM_CALLCONV :FXMMATRIX, :CXMMATRIX

XMVector3ClampLength	proto XM_CALLCONV :FXMVECTOR, :float, :float
XMVector3ClampLengthV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector3Reflect	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3Refract	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :float
XMVector3RefractV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector3Orthogonal	proto XM_CALLCONV :FXMVECTOR
XMVector3AngleBetweenNormalsEst proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3AngleBetweenNormals	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3AngleBetweenVectors	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3LinePointDistance	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR

XMVector3ComponentsFromNormal	proto XM_CALLCONV :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR, :FXMVECTOR

XMVector3Rotate			proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3InverseRotate		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector3Transform		proto XM_CALLCONV :FXMVECTOR, AXMMATRIX
XMVector3TransformStream	proto XM_CALLCONV :ptr XMFLOAT4, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :FXMMATRIX
XMVector3TransformCoord		proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX
XMVector3TransformCoordStream	proto XM_CALLCONV :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :FXMMATRIX
XMVector3TransformNormal	proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX
XMVector3TransformNormalStream	proto XM_CALLCONV :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :FXMMATRIX
XMVector3Project		proto XM_CALLCONV :FXMVECTOR, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX
XMVector3ProjectStream		proto XM_CALLCONV :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX
XMVector3Unproject		proto XM_CALLCONV :FXMVECTOR, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX
XMVector3UnprojectStream	proto XM_CALLCONV :ptr XMFLOAT3, :size_t, :ptr XMFLOAT3, :size_t, :size_t, :float, :float, :float, :float, :float, :float, :FXMMATRIX, :CXMMATRIX, :CXMMATRIX

XMVector4Equal			proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4EqualR			proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4EqualInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4EqualIntR		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4NearEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4NotEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4NotEqualInt		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4Greater		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4GreaterR		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4GreaterOrEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4GreaterOrEqualR	proto XM_CALLCONV :FXMVECTOR,:FXMVECTOR
XMVector4Less			proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4LessOrEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4InBounds		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4IsNaN			proto XM_CALLCONV :FXMVECTOR
XMVector4IsInfinite		proto XM_CALLCONV :FXMVECTOR

XMVector4Dot			proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4Cross			proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4LengthSq		proto XM_CALLCONV :FXMVECTOR
XMVector4ReciprocalLengthEst	proto XM_CALLCONV :FXMVECTOR
XMVector4ReciprocalLength	proto XM_CALLCONV :FXMVECTOR
XMVector4LengthEst		proto XM_CALLCONV :FXMVECTOR
XMVector4Length			proto XM_CALLCONV :FXMVECTOR
XMVector4NormalizeEst		proto XM_CALLCONV :FXMVECTOR
XMVector4Normalize		proto XM_CALLCONV :FXMVECTOR
XMVector4ClampLength		proto XM_CALLCONV :FXMVECTOR, :float, :float
XMVector4ClampLengthV		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4Reflect		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4Refract		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :float
XMVector4RefractV		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMVector4Orthogonal		proto XM_CALLCONV :FXMVECTOR
XMVector4AngleBetweenNormalsEst proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4AngleBetweenNormals	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4AngleBetweenVectors	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMVector4Transform		proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX
XMVector4TransformStream	proto XM_CALLCONV :ptr XMFLOAT4, :size_t, :ptr XMFLOAT4, :size_t, :size_t, :FXMMATRIX

XMMatrixIsNaN		proto XM_CALLCONV :FXMMATRIX
XMMatrixIsInfinite	proto XM_CALLCONV :FXMMATRIX
XMMatrixIsIdentity	proto XM_CALLCONV :FXMMATRIX
XMMatrixMultiply	proto XM_CALLCONV XMTHISPTR, :CXMMATRIX, :CXMMATRIX
XMMatrixInverse		proto XM_CALLCONV :ptr XMVECTOR, :FXMMATRIX
XMMatrixDeterminant	proto XM_CALLCONV :FXMMATRIX
XMMatrixDecompose	proto XM_CALLCONV :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :FXMMATRIX
XMMatrixIdentity	proto XM_CALLCONV XMTHISPTR
XMMatrixSet		proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float, :float, :float, :float, :float,
			      :float, :float, :float, :float, :float, :float, :float, :float
XMMatrixTranslation	proto XM_CALLCONV XMTHISPTR, :float, :float, :float
XMMatrixScaling		proto XM_CALLCONV XMTHISPTR, :float, :float, :float

XMMatrixTranslationFromVector	proto XM_CALLCONV XMTHISPTR, :FXMVECTOR
XMMatrixScalingFromVector	proto XM_CALLCONV XMTHISPTR, :FXMVECTOR
XMMatrixRotationX		proto XM_CALLCONV XMTHISPTR, :float
XMMatrixRotationY		proto XM_CALLCONV XMTHISPTR, :float
XMMatrixRotationZ		proto XM_CALLCONV XMTHISPTR, :float
XMMatrixRotationRollPitchYaw	proto XM_CALLCONV XMTHISPTR, :float, :float, :float
XMMatrixRotationRollPitchYawFromVector proto XM_CALLCONV XMTHISPTR, :FXMVECTOR
XMMatrixRotationNormal		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :float
XMMatrixRotationAxis		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :float
XMMatrixRotationQuaternion	proto XM_CALLCONV XMTHISPTR, :FXMVECTOR
XMMatrixTransformation2D	proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :float, :FXMVECTOR, :FXMVECTOR, :float, :GXMVECTOR
XMMatrixTransformation		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR, :HXMVECTOR
XMMatrixAffineTransformation2D	proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :float, :FXMVECTOR
XMMatrixAffineTransformation	proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR
XMMatrixReflect			proto XM_CALLCONV XMTHISPTR, :FXMVECTOR
XMMatrixShadow			proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR

XMMatrixLookAtLH		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMMatrixLookAtRH		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMMatrixLookToLH		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMMatrixLookToRH		proto XM_CALLCONV XMTHISPTR, :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMMatrixPerspectiveLH		proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float
XMMatrixPerspectiveRH		proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float
XMMatrixPerspectiveFovLH	proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float
XMMatrixPerspectiveFovRH	proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float
XMMatrixPerspectiveOffCenterLH	proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float, :float, :float
XMMatrixPerspectiveOffCenterRH	proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float, :float, :float
XMMatrixOrthographicLH		proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float
XMMatrixOrthographicRH		proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float
XMMatrixOrthographicOffCenterLH proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float, :float, :float
XMMatrixOrthographicOffCenterRH proto XM_CALLCONV XMTHISPTR, :float, :float, :float, :float, :float, :float

XMQuaternionEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMQuaternionNotEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMQuaternionIsNaN	proto XM_CALLCONV :FXMVECTOR
XMQuaternionIsInfinite	proto XM_CALLCONV :FXMVECTOR
XMQuaternionIsIdentity	proto XM_CALLCONV :FXMVECTOR

XMQuaternionDot		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMQuaternionMultiply	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMQuaternionLengthSq	proto XM_CALLCONV :FXMVECTOR
XMQuaternionReciprocalLength proto XM_CALLCONV :FXMVECTOR
XMQuaternionLength	proto XM_CALLCONV :FXMVECTOR
XMQuaternionNormalizeEst proto XM_CALLCONV :FXMVECTOR
XMQuaternionNormalize	proto XM_CALLCONV :FXMVECTOR
XMQuaternionConjugate	proto XM_CALLCONV :FXMVECTOR
XMQuaternionInverse	proto XM_CALLCONV :FXMVECTOR
XMQuaternionLn		proto XM_CALLCONV :FXMVECTOR
XMQuaternionExp		proto XM_CALLCONV :FXMVECTOR
XMQuaternionSlerp	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :float
XMQuaternionSlerpV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMQuaternionSquad	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :float
XMQuaternionSquadV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR

XMQuaternionSquadSetup	proto XM_CALLCONV :ptr XMVECTOR, :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR,
				:FXMVECTOR, :FXMVECTOR, :GXMVECTOR

XMQuaternionBaryCentric		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :float, :float
XMQuaternionBaryCentricV	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR, :GXMVECTOR, :HXMVECTOR

XMQuaternionIdentity		proto XM_CALLCONV
XMQuaternionRotationRollPitchYaw proto XM_CALLCONV :float, :float, :float
XMQuaternionRotationRollPitchYawFromVector proto XM_CALLCONV :FXMVECTOR
XMQuaternionRotationNormal	proto XM_CALLCONV :FXMVECTOR, :float
XMQuaternionRotationAxis	proto XM_CALLCONV :FXMVECTOR, :float
XMQuaternionRotationMatrix	proto XM_CALLCONV :FXMMATRIX

XMQuaternionToAxisAngle		proto XM_CALLCONV :ptr XMVECTOR, :ptr float, :FXMVECTOR

XMPlaneEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMPlaneNearEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR
XMPlaneNotEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMPlaneIsNaN		proto XM_CALLCONV :FXMVECTOR
XMPlaneIsInfinite	proto XM_CALLCONV :FXMVECTOR

XMPlaneDot		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMPlaneDotCoord		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMPlaneDotNormal	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMPlaneNormalizeEst	proto XM_CALLCONV :FXMVECTOR
XMPlaneNormalize	proto XM_CALLCONV :FXMVECTOR
XMPlaneIntersectLine	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR

XMPlaneIntersectPlane	proto XM_CALLCONV :ptr XMVECTOR, :ptr XMVECTOR, :FXMVECTOR, :FXMVECTOR

XMPlaneTransform	proto XM_CALLCONV :FXMVECTOR, :FXMMATRIX
XMPlaneTransformStream	proto XM_CALLCONV :ptr XMFLOAT4, :size_t, :ptr XFLOAT4, :size_t, :size_t, :FXMMATRIX

XMPlaneFromPointNormal	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMPlaneFromPoints	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR, :FXMVECTOR

XMColorEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMColorNotEqual		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMColorGreater		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMColorGreaterOrEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMColorLess		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMColorLessOrEqual	proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR

XMColorIsNaN		proto XM_CALLCONV :FXMVECTOR
XMColorIsInfinite	proto XM_CALLCONV :FXMVECTOR

XMColorNegative		proto XM_CALLCONV :FXMVECTOR
XMColorModulate		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR
XMColorAdjustSaturation proto XM_CALLCONV :FXMVECTOR, :float
XMColorAdjustContrast	proto XM_CALLCONV :FXMVECTOR, :float

XMColorRGBToHSL		proto XM_CALLCONV :FXMVECTOR
XMColorHSLToRGB		proto XM_CALLCONV :FXMVECTOR

XMColorRGBToHSV		proto XM_CALLCONV :FXMVECTOR
XMColorHSVToRGB		proto XM_CALLCONV :FXMVECTOR

XMColorRGBToYUV		proto XM_CALLCONV :FXMVECTOR
XMColorYUVToRGB		proto XM_CALLCONV :FXMVECTOR

XMColorRGBToYUV_HD	proto XM_CALLCONV :FXMVECTOR
XMColorYUVToRGB_HD	proto XM_CALLCONV :FXMVECTOR

XMColorRGBToXYZ		proto XM_CALLCONV :FXMVECTOR
XMColorXYZToRGB		proto XM_CALLCONV :FXMVECTOR

XMColorXYZToSRGB	proto XM_CALLCONV :FXMVECTOR
XMColorSRGBToXYZ	proto XM_CALLCONV :FXMVECTOR

XMColorRGBToSRGB	proto XM_CALLCONV :FXMVECTOR
XMColorSRGBToRGB	proto XM_CALLCONV :FXMVECTOR

XMVerifyCPUSupport	proto XM_CALLCONV

XMFresnelTerm		proto XM_CALLCONV :FXMVECTOR, :FXMVECTOR

XMScalarNearEqual	proto XM_CALLCONV :float, :float, :float
XMScalarModAngle	proto XM_CALLCONV :float
XMScalarSin		proto XM_CALLCONV :float
XMScalarSinEst		proto XM_CALLCONV :float
XMScalarCos		proto XM_CALLCONV :float
XMScalarCosEst		proto XM_CALLCONV :float
XMScalarSinCos		proto XM_CALLCONV :ptr float, :ptr float, :float
XMScalarSinCosEst	proto XM_CALLCONV :ptr float, :ptr float, :float
XMScalarASin		proto XM_CALLCONV :float
XMScalarASinEst		proto XM_CALLCONV :float
XMScalarACos		proto XM_CALLCONV :float
XMScalarACosEst		proto XM_CALLCONV :float

;; Internals

XMVECTOR_GetLeadingBit proto vectorcall :XMVECTOR
XMVECTOR_multi_sll_epi32 proto vectorcall :XMVECTOR, :XMVECTOR
XMVECTOR_multi_srl_epi32 proto vectorcall :XMVECTOR, :XMVECTOR

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

if defined(_XM_NO_INTRINSICS_)
else
endif
if defined(_XM_NO_INTRINSICS_)
else
endif

include DirectXMath.inl

.pragma list(pop)
endif
