ifndef _INCLUDED_MM2
_INCLUDED_MM2 equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
;;
;; Principal header file for Streaming SIMD Extensions intrinsics
;;
;; The intrinsics package can be used in 2 ways, based whether or not
;; _MM_FUNCTIONALITY is defined; if it is, the C/x87 implementation
;; will be used (the "faux intrinsics").
;;
;; Note that the m128 datatype provided using _MM2_FUNCTIONALITY mode is
;;   implemented as struct, will not be 128b aligned, will be passed
;;   via the stack, etc.  MM_FUNCTIONALITY mode is not intended for
;;   performance, just semantics.
;;
ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif

ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif
;;
;; the m64 type is required for the integer Streaming SIMD Extensions intrinsics
;;
ifndef _MMINTRIN_H_INCLUDED
include mmintrin.inc
endif
ifndef __XMMMACROS_INC
include xmmmacros.inc
endif

ifdef _MM2_FUNCTIONALITY
ifndef _MM_FUNCTIONALITY
_MM_FUNCTIONALITY equ <>
endif
endif

ifdef __ICL
ifdef _MM_FUNCTIONALITY
include xmm_func.inc
else
;; using real intrinsics
__m128		typedef sqword
endif
else ;; __ICL
__m128		union
m128_f32	real4 4 dup(?)
m128_u64	dq 2 dup(?)
m128_i8		sbyte 16 dup(?)
m128_i16	sword 8 dup(?)
m128_i32	sdword 4 dup(?)
m128_i64	sqword 2 dup(?)
m128_u8		db 16 dup(?)
m128_u16	dw 8 dup(?)
m128_u32	dd 4 dup(?)
__m128		ends
ifndef _VCRT_BUILD
ifndef _INC_MALLOC
include malloc.inc
endif
endif
endif;; __ICL

ifndef XMVECTOR
XMVECTOR typedef REAL16
endif

;;
;; MACRO for shuffle parameter for _mm_shuffle_ps().
;; Argument fp3 is a digit[0123] that represents the fp
;; from argument "b" of mm_shuffle_ps that will be
;; placed in fp3 of result. fp2 is the same for fp2 in
;; result. fp1 is a digit[0123] that represents the fp
;; from argument "a" of mm_shuffle_ps that will be
;; places in fp1 of result. fp0 is the same for fp0 of
;; result
;;
_MM_SHUFFLE macro fp3, fp2, fp1, fp0
    exitm<(((fp3) SHL 6) OR ((fp2) SHL 4) OR ((fp1) SHL 2) OR ((fp0)))>
    endm

;;
;; MACRO for performing the transpose of a 4x4 matrix
;; of single precision floating point values.
;; Arguments row0, row1, row2, and row3 are __m128
;; values whose elements form the corresponding rows
;; of a 4x4 matrix.  The matrix transpose is returned
;; in arguments row0, row1, row2, and row3 where row0
;; now holds column 0 of the original matrix, row1 now
;; holds column 1 of the original matrix, etc.
;;

_MM_TRANSPOSE4_PS proto :XMVECTOR, :XMVECTOR, :XMVECTOR, :XMVECTOR
_MM_TRANSPOSE4_PS macro row0, row1, row2, row3
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
    exitm<>
    endm

_MM_HINT_NTA		equ 0
_MM_HINT_T0		equ 1
_MM_HINT_T1		equ 2
_MM_HINT_T2		equ 3
_MM_HINT_ENTA		equ 4

_MM_ALIGN16		equ _VCRT_ALIGN(16)

_MM_EXCEPT_MASK		equ 0x003f
_MM_EXCEPT_INVALID	equ 0x0001
_MM_EXCEPT_DENORM	equ 0x0002
_MM_EXCEPT_DIV_ZERO	equ 0x0004
_MM_EXCEPT_OVERFLOW	equ 0x0008
_MM_EXCEPT_UNDERFLOW	equ 0x0010
_MM_EXCEPT_INEXACT	equ 0x0020

_MM_MASK_MASK		equ 0x1f80
_MM_MASK_INVALID	equ 0x0080
_MM_MASK_DENORM		equ 0x0100
_MM_MASK_DIV_ZERO	equ 0x0200
_MM_MASK_OVERFLOW	equ 0x0400
_MM_MASK_UNDERFLOW	equ 0x0800
_MM_MASK_INEXACT	equ 0x1000

_MM_ROUND_MASK		equ 0x6000
_MM_ROUND_NEAREST	equ 0x0000
_MM_ROUND_DOWN		equ 0x2000
_MM_ROUND_UP		equ 0x4000
_MM_ROUND_TOWARD_ZERO	equ 0x6000

_MM_FLUSH_ZERO_MASK	equ 0x8000
_MM_FLUSH_ZERO_ON	equ 0x8000
_MM_FLUSH_ZERO_OFF	equ 0x0000

_mm_getcsr macro
    stmxcsr [rsp]
    mov	    eax,[rsp]
    retm    <eax>
    endm

_mm_setcsr macro reg
    mov	    [rsp],reg
    ldmxcsr [rsp]
    retm    <eax>
    endm

_MM_SET_EXCEPTION_STATE macro mask
    and	    _mm_getcsr(),NOT _MM_EXCEPT_MASK
    or	    eax,mask
    exitm   <_mm_setcsr(eax)>
    endm

_MM_GET_EXCEPTION_STATE macro
    and	    _mm_getcsr(),NOT _MM_EXCEPT_MASK
    retm    <eax>
    endm

_MM_SET_EXCEPTION_MASK macro mask
    and	    _mm_getcsr(),NOT _MM_MASK_MASK
    or	    eax,mask
    exitm   <_mm_setcsr(eax)>
    endm

_MM_GET_EXCEPTION_MASK macro
    and	    _mm_getcsr(),_MM_MASK_MASK
    retm    <eax>
    endm

_MM_SET_ROUNDING_MODE macro mode
    and	    _mm_getcsr(),NOT _MM_ROUND_MASK
    or	    eax,mode
    exitm   <_mm_setcsr(eax)>
    endm

_MM_GET_ROUNDING_MODE macro
    and	    _mm_getcsr(),_MM_ROUND_MASK
    retm    <eax>
    endm

_MM_SET_FLUSH_ZERO_MODE macro mode
    and	    _mm_getcsr(),NOT _MM_FLUSH_ZERO_MASK
    or	    eax,mode
    exitm   <_mm_setcsr(eax)>
    endm

_MM_GET_FLUSH_ZERO_MODE macro
    and	    _mm_getcsr(),_MM_FLUSH_ZERO_MASK
    retm    <eax>
    endm

_mm_add_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(add, ss, a, b)>
    endm
_mm_add_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(add, ps, a, b)>
    endm
_mm_sub_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(sub, ss, a, b)>
    endm
_mm_sub_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(sub, ps, a, b)>
    endm
_mm_mul_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(mul, ss, a, b)>
    endm
_mm_mul_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(mul, ps, a, b)>
    endm
_mm_div_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(div, ss, a, b)>
    endm
_mm_div_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(div, ps, a, b)>
    endm

_mm_sqrt_ss macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(sqrt, ss, a, b)>
    else
	exitm<_MM_OPCSX2(sqrt, ss, a, a)>
    endif
    endm
_mm_sqrt_ps macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(sqrt, ps, a, b)>
    else
	exitm<_MM_OPCSX2(sqrt, ps, a, a)>
    endif
    endm
_mm_rcp_ss macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(rcp, ss, a, b)>
    else
	exitm<_MM_OPCSX2(rcp, ss, a, a)>
    endif
    endm
_mm_rcp_ps macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(rcp, ps, a, b)>
    else
	exitm<_MM_OPCSX2(rcp, ps, a, a)>
    endif
    endm
_mm_rsqrt_ss macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(rsqrt, ss, a, b)>
    else
	exitm<_MM_OPCSX2(rsqrt, ss, a, a)>
    endif
    endm
_mm_rsqrt_ps macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(rsqrt, ps, a, b)>
    else
	exitm<_MM_OPCSX2(rsqrt, ps, a, a)>
    endif
    endm
_mm_min_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(min, ss, a, b)>
    endm
_mm_min_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(min, ps, a, b)>
    endm
_mm_max_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(max, ss, a, b)>
    endm
_mm_max_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(max, ps, a, b)>
    endm

_mm_and_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(and, ps, a, b)>
    endm
_mm_andnot_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(andn, ps, a, b)>
    endm
_mm_or_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(or, ps, a, b)>
    endm
_mm_xor_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(xor, ps, a, b)>
    endm

_mm_cmpeq_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpeq, ss, a, b)>
    endm
_mm_cmpeq_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpeq, ps, a, b)>
    endm
_mm_cmplt_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmplt, ss, a, b)>
    endm
_mm_cmplt_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmplt, ps, a, b)>
    endm
_mm_cmple_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmple, ss, a, b)>
    endm
_mm_cmple_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmple, ps, a, b)>
    endm

; --- reverse order: result returned in x

_mm_cmpgt_ss macro x:req, a:req, b:req
    ifdif <x>,<b>
	movss x,b
    endif
    exitm<_MM_OPCSX2(cmplt, ss, x, a)>
    endm
_mm_cmpgt_ps macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
    exitm<_MM_OPCSX2(cmplt, ps, x, a)>
    endm
_mm_cmpge_ss macro x:req, a:req, b:req
    ifdif <x>,<b>
	movss x,b
    endif
    exitm<_MM_OPCSX2(cmple, ss, x, a)>
    endm
_mm_cmpge_ps macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
    exitm<_MM_OPCSX2(cmple, ps, x, a)>
    endm

; ---

_mm_cmpneq_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpneq, ss, a, b)>
    endm
_mm_cmpneq_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpneq, ps, a, b)>
    endm
_mm_cmpnlt_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpnlt, ss, a, b)>
    endm
_mm_cmpnlt_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpnlt, ps, a, b)>
    endm
_mm_cmpnle_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpnle, ss, a, b)>
    endm
_mm_cmpnle_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpnle, ps, a, b)>
    endm

; --- reverse order: result returned in B

_mm_cmpngt_ss macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
    exitm<_MM_OPCSX2(cmpnlt, ss, x, a)>
    endm
_mm_cmpngt_ps macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
    exitm<_MM_OPCSX2(cmpnlt, ps, x, a)>
    endm
_mm_cmpnge_ss macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
    exitm<_MM_OPCSX2(cmpnle, ss, x, a)>
    endm
_mm_cmpnge_ps macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
    exitm<_MM_OPCSX2(cmpnle, ps, x, a)>
    endm
; ---

_mm_cmpord_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpord, ss, a, b)>
    endm
_mm_cmpord_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpord, ps, a, b)>
    endm
_mm_cmpunord_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpunord, ss, a, b)>
    endm
_mm_cmpunord_ps macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(cmpunord, ps, a, b)>
    endm

_mm_comieq_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<ZERO?>
    endm
_mm_comilt_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<CARRY?>
    endm
_mm_comile_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<CARRY? || ZERO?>
    endm
_mm_comigt_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<!CARRY? && !ZERO?>
    endm
_mm_comige_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<!CARRY?>
    endm
_mm_comineq_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<!ZERO?>
    endm
_mm_ucomieq_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<ZERO?>
    endm
_mm_ucomilt_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<CARRY?>
    endm
_mm_ucomile_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<CARRY? || ZERO?>
    endm
_mm_ucomigt_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<!CARRY? && !ZERO?>
    endm
_mm_ucomige_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<!CARRY?>
    endm
_mm_ucomineq_ss macro a:=<xmm0>, b:=<xmm1>
    ucomiss a, b
    retm<!ZERO?>
    endm

_mm_cvt_ss2si macro a:=<xmm0>
    cvtss2si eax,a
    retm<eax>
    endm
_mm_cvtt_ss2si macro a:=<xmm0>
    cvttss2si eax,a
    retm<eax>
    endm
_mm_cvt_si2ss macro x:=<xmm0>, d
    if (typeof d) eq 4 and (opattr d) eq 48
	cvtsi2ss x,d
    else
	mov eax,d
	cvtsi2ss x,eax
    endif
    retm<x>
    endm
_mm_cvtss_f32 macro a:=<xmm0>
    exitm<>
    endm

;ifdef _M_IX86
_mm_cvt_ps2pi macro x:=<xmm0>
    cvtps2pi mm0,x
    retm<mm0>
    endm
_mm_cvtt_ps2pi macro x:=<xmm0>
    cvttps2pi mm0,x
    retm<mm0>
    endm
_mm_cvt_pi2ps macro x:=<xmm0>, m:=<mm0>
    cvtpi2ps x,m
    retm<xmm0>
    endm
;endif

ifdef _M_X64
_mm_cvtss_si64 macro a:=<xmm0>
    cvtss2si rax,a
    retm<rax>
    endm
_mm_cvttss_si64 macro a:=<xmm0>
    cvttss2si rax,a
    retm<rax>
    endm
_mm_cvtsi64_ss macro a:=<xmm0>, p
    cvtsi2ss a,_MM_MREG(p)
    retm<a>
    endm
endif

_mm_shuffle_ps macro a:=<xmm0>, b:=<xmm1>, imm:=<0>
    exitm<_MM_SHUFXX(ps, a, b, imm)>
    endm
_mm_unpackhi_ps macro a, b
    exitm<_MM_OPCSX2(unpckh, ps, a, b)>
    endm
_mm_unpacklo_ps macro a, b
    exitm<_MM_OPCSX2(unpckl, ps, a, b)>
    endm
_mm_loadh_pi macro x:=<xmm0>, p
    movhps x,_MM_MREG(p)
    retm<x>
    endm
_mm_movehl_ps macro a, b
    exitm<_MM_OPCSX2(movhl, ps, a, b)>
    endm
_mm_movelh_ps macro a, b
    exitm<_MM_OPCSX2(movlh, ps, a, b)>
    endm
_mm_storeh_pi macro p, x:=<xmm0>
    movhps _MM_MREG(p),x
    retm<p>
    endm
_mm_loadl_pi macro x:=<xmm0>, p
    movlps x,_MM_MREG(p)
    retm<x>
    endm
_mm_storel_pi macro p, x:=<xmm0>
    movlps _MM_MREG(p),x
    retm<p>
    endm
_mm_movemask_ps macro x:=<xmm0>
    movmskps eax,x
    retm<eax>
    endm

;ifdef _M_IX86
_m_pextrw macro m, imm
   pextrw eax,m,imm
   retm<eax>
   endm
_m_pinsrw macro m, i1, i2
   mov eax,i1
   pextrw m,eax,i2
   retm<m>
   endm
_m_pmaxsw macro a, b
   pmaxsw a,b
   retm<a>
   endm
_m_pmaxub macro a, b
   pmaxub a,b
   retm<a>
   endm
_m_pminsw macro a, b
   pminsw a,b
   retm<a>
   endm
_m_pminub macro a, b
   pminub a,b
   retm<a>
   endm
_m_pmovmskb macro m
   pmovmskb eax,m
   retm<eax>
   endm
_m_pmulhuw macro a, b
   pmulhuw a,b
   retm<a>
   endm
_m_pshufw macro m, imm
   pshufw m,m,imm
   retm<mm0>
   endm
_m_maskmovq macro a, b, p
   push rdi
   mov rdi,p
   movq mm2,a
   movq a,b
   maskmovq mm2,a
   pop rdi
   retm<>
   endm
_m_pavgb macro a, b
   pavgb a,b
   retm<a>
   endm
_m_pavgw macro a, b
   pavgw a,b
   retm<a>
   endm
_m_psadbw macro a, b
   psadbw a,b
   retm<a>
   endm
;endif

_mm_set_ss macro x:=<xmm0>
    movd eax,x
    movd x,eax
    retm<x>
    endm
_mm_set_ps1 macro x:=<xmm0>
    shufps x,x,0
    retm<x>
    endm
_mm_set_ps macro x0:=<xmm0>, x1:=<xmm1>, x2:=<xmm2>, x3:=<xmm3>
    unpcklps x3,x2
    unpcklps x1,x0
    movaps x0,x3
    movlhps x0,x1
    retm<x0>
    endm
_mm_setr_ps macro x0:=<xmm0>, x1:=<xmm1>, x2:=<xmm2>, x3:=<xmm3>
    unpcklps x2,x3
    unpcklps x0,x1
    movlhps x0,x2
    retm<x0>
    endm
_mm_setzero_ps macro x:=<xmm0>
    xorps x,x
    retm<x>
    endm
_mm_movemm_ps macro a, b
    movaps xmm0,oword ptr _MM_MREG(b)
    movaps oword ptr _MM_MREG(a),xmm0
    retm<xmm0>
    endm

_mm_load_ss macro x, p
    ifnb <p>
	movss x,_MM_MREG(p)
	retm<x>
    else
	movss xmm0,_MM_MREG(x)
	retm<xmm0>
    endif
    endm
_mm_load_ps1 macro x, p
    ifnb <p>
	movss x,_MM_MREG(p)
	shufps x,x,0
	retm<x>
    else
	movss xmm0,_MM_MREG(x)
	shufps xmm0,xmm0,0
	retm<xmm0>
    endif
    endm
_mm_load_ps macro x, p
    ifnb <p>
	movaps x,_MM_MREG(p)
	retm<x>
    else
	movaps xmm0,_MM_MREG(x)
	retm<xmm0>
    endif
    endm
_mm_loadr_ps macro x, p
    ifnb <p>
	movaps x,_MM_MREG(p)
	shufps x,x,27
	retm<x>
    else
	movaps xmm0,_MM_MREG(x)
	shufps xmm0,xmm0,27
	retm<xmm0>
    endif
    endm
_mm_loadu_ps macro x, p
    ifnb <p>
	movups x,_MM_MREG(p)
	retm<x>
    else
	movups xmm0,_MM_MREG(x)
	retm<xmm0>
    endif
    endm
_mm_store_ss macro p, x:=<xmm0>
    ifdif <p>,<x>
	movss _MM_MREG(p),x
    endif
    retm<p>
    endm
_mm_store_ps1 macro p, x:=<xmm0>
    shufps x,x,0
    movups _MM_MREG(p),x
    retm<p>
    endm
_mm_store_ps macro p, x:=<xmm0>
    ifdif <p>,<x>
	movaps _MM_MREG(p),x
    endif
    retm<p>
    endm
_mm_storer_ps macro p, x:=<xmm0>
    shufps x,x,27
    movaps _MM_MREG(p),x
    retm<p>
    endm
_mm_storeu_ps macro p, x:=<xmm0>
    movups _MM_MREG(p),x
    retm<p>
    endm
_mm_prefetch macro p, imm
  local i
    _mm_loadreg(rax, p)
    i = imm - 1
    @CatStr(prefetcht, %i) byte ptr [rax]
    retm<>
    endm
;ifdef _M_IX86
_mm_stream_pi macro p, m:=<mm0>
    _mm_loadreg(rax, p)
    movntq [rax],m
    retm<rax>
    endm
;endif
_mm_stream_ps macro p, x:=<xmm0>
    movntps _MM_MREG(p),x
    retm<p>
    endm
_mm_move_ss macro a:=<xmm0>, b:=<xmm1>
    exitm<_MM_OPCSX2(mov, ss, a, b)>
    endm

_mm_sfence macro
    exitm<sfence>
    endm

ifdef __ICL
_mm_malloc		equ <_aligned_malloc>
_mm_free		equ <free>
endif

;ifdef _M_IX86
_mm_cvtps_pi32		equ <_mm_cvt_ps2pi>
_mm_cvttps_pi32		equ <_mm_cvtt_ps2pi>
_mm_cvtpi32_ps		equ <_mm_cvt_pi2ps>
_mm_extract_pi16	equ <_m_pextrw>
_mm_insert_pi16		equ <_m_pinsrw>
_mm_max_pi16		equ <_m_pmaxsw>
_mm_max_pu8		equ <_m_pmaxub>
_mm_min_pi16		equ <_m_pminsw>
_mm_min_pu8		equ <_m_pminub>
_mm_movemask_pi8	equ <_m_pmovmskb>
_mm_mulhi_pu16		equ <_m_pmulhuw>
_mm_shuffle_pi16	equ <_m_pshufw>
_mm_maskmove_si64	equ <_m_maskmovq>
_mm_avg_pu8		equ <_m_pavgb>
_mm_avg_pu16		equ <_m_pavgw>
_mm_sad_pu8		equ <_m_psadbw>
;endif
_mm_cvtss_si32		equ <_mm_cvt_ss2si>
_mm_cvttss_si32		equ <_mm_cvtt_ss2si>
_mm_cvtsi32_ss		equ <_mm_cvt_si2ss>
_mm_set1_ps		equ <_mm_set_ps1>
_mm_load1_ps		equ <_mm_load_ps1>
_mm_store1_ps		equ <_mm_store_ps1>

;ifdef _M_IX86
_mm_cvtpi16_ps macro m:=<mm0>
    movq	mm3,m
    pxor	mm1,mm1
    movq	mm2,mm1
    xorps	xmm0,xmm0
    pcmpgtw	mm2,mm3
    punpckhwd	mm0,mm2
    cvtpi2ps	xmm0,mm0
    movq	mm0,mm3
    punpcklwd	mm0,mm2
    movlhps	xmm0,xmm0
    cvtpi2ps	xmm0,mm0
    retm<xmm0>
    endm
_mm_cvtpu16_ps macro m:=<mm0>
    movq	mm3,m
    pxor	mm0,mm0
    xorps	xmm0,xmm0
    movq	mm1,mm3
    punpckhwd	mm1,mm0
    cvtpi2ps	xmm0,mm1
    movq	mm1,mm3
    punpcklwd	mm1,mm0
    movq	mm0,mm1
    movlhps	xmm0,xmm0
    cvtpi2ps	xmm0,mm0
    retm<xmm0>
    endm
_mm_cvtps_pi16 macro x:=<xmm0>
    cvtps2pi	mm0,x
    movhlps	x,x
    cvtps2pi	mm1,x
    packssdw	mm0,mm1
    retm<mm0>
    endm
_mm_cvtpi8_ps macro m:=<mm0>
    movq	mm4,m
    pxor	mm1,mm1
    xorps	xmm0,xmm0
    movq	mm3,mm1
    pcmpgtb	mm1,mm4
    punpcklbw	mm4,mm1
    movq	mm2,mm3
    pcmpgtw	mm2,mm4
    movq	mm0,mm4
    punpckhwd	mm0,mm2
    cvtpi2ps	xmm0,mm0
    movq	mm0,mm4
    punpcklwd	mm0,mm2
    movlhps	xmm0,xmm0
    cvtpi2ps	xmm0,mm0
    retm<mm0>
    endm
_mm_cvtpu8_ps macro m:=<mm0>
    movq	mm3,m
    pxor	mm1,mm1
    pxor	mm2,mm2
    xorps	xmm0,xmm0
    punpcklbw	mm3,mm2
    movq	mm0,mm3
    punpckhwd	mm0,mm2
    cvtpi2ps	xmm0,mm0
    movq	mm0,mm3
    punpcklwd	mm0,mm2
    movlhps	xmm0,xmm0
    cvtpi2ps	xmm0,mm0
    retm<xmm0>
    endm
_mm_cvtps_pi8 macro x:=<xmm0>
    cvtps2pi	mm1,x
    movhlps	x,x
    cvtps2pi	mm0,x
    packssdw	mm1,mm0
    movq	mm0,mm1
    pxor	mm1,mm1
    packsswb	mm0,mm1
    retm<mm0>
    endm
_mm_cvtpi32x2_ps macro a:=<xmm0>, b:=<xmm1>
    cvtpi2ps	xmm2,b
    cvtpi2ps	xmm0,a
    movlhps	xmm0,xmm2
    retm<xmm0>
    endm
;endif

.pragma list(pop)
endif
