ifndef _INCLUDED_EMM
_INCLUDED_EMM equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

;; the __m128 & __m64 types are required for the intrinsics

include xmmintrin.inc

__m128i union
m128i_i8	db 16 dup(?)
m128i_i16	dw 8 dup(?)
m128i_i32	dd 4 dup(?)
m128i_i64	dq 2 dup(?)
m128i_u8	db 16 dup(?)
m128i_u16	dw 8 dup(?)
m128i_u32	dd 4 dup(?)
m128i_u64	dq 2 dup(?)
__m128i ends

__m128d struc
m128d_f64	real8 2 dup(?)
__m128d ends

;; Macro function for shuffle

_MM_SHUFFLE2 macro x,y
	exitm<(((x) SHL 1) OR (y))>
	endm

ifndef __XMMMACROS_INC
include xmmmacros.inc
endif

_mm_add_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(add, sd, a, b)>
	endm
_mm_add_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(add, pd, a, b)>
	endm
_mm_sub_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(sub, sd, a, b)>
	endm
_mm_sub_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(sub, pd, a, b)>
	endm
_mm_mul_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(mul, sd, a, b)>
	endm
_mm_mul_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(mul, pd, a, b)>
	endm

_mm_sqrt_sd macro a:=<xmm0>, b:=<xmm1>
	movsd a,b
	exitm<_MM_OPCSX2(sqrt, sd, a, b)>
	endm
_mm_sqrt_pd macro a:=<xmm0>
	exitm<_MM_OPCSX2(sqrt, pd, a, a)>
	endm
_mm_div_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(div, sd, a, b)>
	endm
_mm_div_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(div, pd, a, b)>
	endm
_mm_min_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(min, sd, a, b)>
	endm
_mm_min_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(min, pd, a, b)>
	endm
_mm_max_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(max, sd, a, b)>
	endm
_mm_max_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(max, pd, a, b)>
	endm
_mm_and_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(and, pd, a, b)>
	endm
_mm_andnot_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(andn, pd, a, b)>
	endm
_mm_or_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(or, pd, a, b)>
	endm
_mm_xor_pd macro a, b
	exitm<_MM_OPCSX2(xor, pd, a, b)>
	endm

_mm_cmpeq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpeq, sd, a, b)>
	endm
_mm_cmpeq_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpeq, pd, a, b)>
	endm
_mm_cmplt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmplt, sd, a, b)>
	endm
_mm_cmplt_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmplt, pd, a, b)>
	endm
_mm_cmple_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmple, sd, a, b)>
	endm
_mm_cmple_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmple, pd, a, b)>
	endm

_mm_cmpgt_sd macro x:req, a:req, b:req
    ifdif <x>,<b>
	movsd x,b
    endif
	_mm_cmplt_sd(x, a)
	retm<x>
	endm
_mm_cmpgt_pd macro x:req, a:req, b:req
    ifdif <x>,<b>
	movapd x,b
    endif
	_mm_cmplt_pd(x, a)
	retm<x>
	endm
_mm_cmpge_sd macro x:req, a:req, b:req
    ifdif <x>,<b>
	movapd x,b
    endif
	_mm_cmplt_sd(x, a)
	retm<x>
	endm
_mm_cmpge_pd macro x:req, a:req, b:req
    ifdif <x>,<b>
	movapd x,b
    endif
	_mm_cmple_pd(x, a)
	retm<x>
	endm

_mm_cmpneq_sd macro a, b
	exitm<_MM_OPCSX2(cmpneq, sd, a, b)>
	endm
_mm_cmpneq_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpneq, pd, a, b)>
	endm
_mm_cmpnlt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpnlt, sd, a, b)>
	endm
_mm_cmpnlt_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpnlt, pd, a, b)>
	endm
_mm_cmpnle_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpnle, sd, a, b)>
	endm
_mm_cmpnle_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpnle, pd, a, b)>
	endm
_mm_cmpngt_sd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnlt_sd(b, a)
	movsd a, b
	retm<a>
	endm
_mm_cmpngt_pd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnlt_pd(b, a)
	movapd a, b
	retm<a>
	endm
_mm_cmpnge_sd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnle_sd(b, a)
	movsd a, b
	retm<a>
	endm
_mm_cmpnge_pd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnle_pd(b, a)
	movapd a, b
	retm<a>
	endm
_mm_cmpord_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpord, pd, a, b)>
	endm
_mm_cmpord_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpord, sd, a, b)>
	endm
_mm_cmpunord_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpunord, pd, a, b)>
	endm
_mm_cmpunord_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(cmpunord, sd, a, b)>
	endm

_mm_comieq_sd macro a, b
	comisd a, b
	retm<ZERO?>
	endm
_mm_comilt_sd macro a, b
	comisd a, b
	retm<CARRY?>
	endm
_mm_comile_sd macro a, b
	comisd a, b
	retm<ZERO? || CARRY?>
	endm
_mm_comigt_sd macro a, b
	comisd a, b
	retm<!(ZERO? || CARRY?)>
	endm
_mm_comige_sd macro a, b
	comisd a, b
	retm<!CARRY?>
	endm
_mm_comineq_sd macro a, b
	comisd a, b
	retm<!ZERO?>
	endm

_mm_ucomieq_sd macro a, b
	ucomisd a, b
	retm<ZERO?>
	endm
_mm_ucomilt_sd macro a, b
	ucomisd a, b
	retm<CARRY?>
	endm
_mm_ucomile_sd macro a, b
	ucomisd a, b
	retm<ZERO? || CARRY?>
	endm
_mm_ucomigt_sd macro a, b
	ucomisd a, b
	retm<!(ZERO? || CARRY?)>
	endm
_mm_ucomige_sd macro a, b
	ucomisd a, b
	retm<!CARRY?>
	endm
_mm_ucomineq_sd macro a, b
	ucomisd a, b
	retm<!ZERO?>
	endm

; added for NaN return
_mm_ucominan_sd macro a, b
	ucomisd a, b
	retm<PARITY?>
	endm
_mm_ucominnan_sd macro a, b
	ucomisd a, b
	retm<!PARITY?>
	endm

_mm_cvtepi32_pd macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtdq2, pd, a, b)>
    else
	exitm<_MM_OPCSX2(cvtdq2, pd, a, a)>
    endif
	endm
_mm_cvtpd_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtpd2, dq, a, b)>
    else
	exitm<_MM_OPCSX2(cvtpd2, dq, a, a)>
    endif
	endm
_mm_cvttpd_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvttpd2, dq, a, b)>
    else
	exitm<_MM_OPCSX2(cvttpd2, dq, a, a)>
    endif
	endm
_mm_cvtepi32_ps macro a:=<xmm0>, b
    ifnb <b>
	cvtdq2ps a,b
    else
	cvtdq2ps a,a
    endif
	retm<a>
	endm
_mm_cvtps_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtps2, dq, a, b)>
    else
	exitm<_MM_OPCSX2(cvtps2, dq, a, a)>
    endif
	endm
_mm_cvttps_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvttps2, dq, a, b)>
    else
	exitm<_MM_OPCSX2(cvttps2, dq, a, a)>
    endif
	endm
_mm_cvtpd_ps macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtpd2, ps, a, b)>
    else
	exitm<_MM_OPCSX2(cvtpd2, ps, a, a)>
    endif
	endm
_mm_cvtps_pd macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtps2, pd, a, b)>
    else
	exitm<_MM_OPCSX2(cvtps2, pd, a, a)>
    endif
	endm
_mm_cvtsd_ss macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtsd2, ss, a, b)>
    else
	exitm<_MM_OPCSX2(cvtsd2, ss, a, a)>
    endif
	endm
_mm_cvtss_sd macro a:=<xmm0>, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtss2, sd, a, b)>
    else
	exitm<_MM_OPCSX2(cvtss2, sd, a, a)>
    endif
	endm

_mm_cvtsd_si32 macro a:=<xmm0>
	cvtsd2si eax,a
	retm<eax>
	endm
_mm_cvttsd_si32 macro a:=<xmm0>
	cvttsd2si eax,a
	retm<eax>
	endm
_mm_cvtsi32_sd macro a, b
    ifnb <b>
	exitm<_MM_OPCSX2(cvtsi2, sd, a, b)>
    else
	exitm<_MM_OPCSX2(cvtsi2, sd, a, a)>
    endif
	endm

_mm_unpackhi_pd macro a, b
    ifnb <b>
	exitm<_MM_OPCSX2(unpckh, pd, a, b)>
    else
	exitm<_MM_OPCSX2(unpckh, pd, a, a)>
    endif
	endm
_mm_unpacklo_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(unpckl, pd, a, b)>
	endm
_mm_movemask_pd macro a:=<xmm0>
	movmskpd eax,a
	retm<eax>
	endm

_mm_shuffle_pd macro a:=<xmm0>, b:=<xmm1>, imm
	exitm<_MM_SHUFXX(pd, a, b, imm)>
	endm

_mm_load_pd macro p
	movapd xmm0,_MM_MREG(p)
	retm<xmm0>
	endm
_mm_load1_pd macro p
	movsd xmm0,_MM_MREG(p)
	exitm<_mm_unpacklo_pd(xmm0, xmm0)>
	endm
_mm_loadr_pd macro reg
	_mm_load_pd(reg)
	exitm<_mm_shuffle_pd(xmm0,xmm0,1)>
	endm
_mm_loadu_pd macro p
	movupd xmm0,_MM_MREG(p)
	retm<xmm0>
	endm
_mm_load_sd macro p
	movq xmm0,_MM_MREG(p)
	retm<xmm0>
	endm
_mm_loadh_pd macro x:=<xmm0>, p
	movhpd x,_MM_MREG(p)
	retm<x>
	endm
_mm_loadl_pd macro x:=<xmm0>, p
	movlpd x,_MM_MREG(p)
	retm<x>
	endm

_mm_set_sd macro r
	movq xmm0,r
	retm<xmm0>
	endm
_mm_set1_pd macro r
	unpcklpd xmm0,r
	retm<xmm0>
	endm
_mm_set_pd macro d0:=<xmm0>, d1:=<xmm1>
	movapd xmm2,d1
	unpcklpd xmm2,d0
	movapd xmm0,xmm2
	retm<xmm0>
	endm
_mm_setr_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(unpckl, pd, a, b)>
	endm
_mm_setzero_pd macro x:=<xmm0>
	pxor x,x
	retm<x>
	endm
_mm_move_sd macro a, b
    ifdif <a>,<b>
	exitm<movsd a, b>
    else
	retm<>
    endif
	endm
_mm_move_pd macro a, b
    ifdif <a>,<b>
	exitm<movapd a, b>
    else
	retm<>
    endif
	endm

_mm_store_sd macro p, x:=<xmm0>
	movlpd _MM_MREG(p),x
	retm<p>
	endm
_mm_store1_pd macro p, x:=<xmm0>
	movapd xmm1,x
	unpcklpd xmm1,x
	movaps _MM_MREG(p),x
	retm<p>
	endm
_mm_store_pd macro p, x:=<xmm0>
	movaps _MM_MREG(p),x
	retm<p>
	endm
_mm_storeu_pd macro p, x:=<xmm0>
	movups _MM_MREG(p),x
	retm<p>
	endm
_mm_storer_pd macro p, x:=<xmm0>
	movapd xmm1,x
	shufpd xmm1,x,1
	movaps _MM_MREG(p),xmm1
	retm<p>
	endm
_mm_storeh_pd macro p, x:=<xmm0>
	movhpd _MM_MREG(p),x
	retm<p>
	endm
_mm_storel_pd macro p, x:=<xmm0>
	movlpd _MM_MREG(p),x
	retm<p>
	endm

_mm_add_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pad, db, a, b)>
	endm
_mm_add_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pad, dw, a, b)>
	endm
_mm_add_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pad, dd, a, b)>
	endm
_mm_add_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pad, dq, a, b)>
	endm

_mm_adds_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(padd, sb, a, b)>
	endm
_mm_adds_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(padd, sw, a, b)>
	endm
_mm_adds_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(paddu, sb, a, b)>
	endm
_mm_adds_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(paddu, sw, a, b)>
	endm
_mm_avg_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pav, gb, a, b)>
	endm
_mm_avg_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pav, gw, a, b)>
	endm
_mm_madd_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmadd, wd, a, b)>
	endm
_mm_max_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmax, sw, a, b)>
	endm
_mm_max_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmax, ub, a, b)>
	endm
_mm_min_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmin, sw, a, b)>
	endm
_mm_min_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmin, ub, a, b)>
	endm
_mm_mulhi_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmul, hw, a, b)>
	endm
_mm_mulhi_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmulh, uw, a, b)>
	endm
_mm_mullo_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmul, lw, a, b)>
	endm

_mm_mul_epu32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pmulu, dq, a, b)>
	endm
_mm_sad_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psad, bw, a, b)>
	endm
_mm_sub_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psu, bb, a, b)>
	endm
_mm_sub_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psu, bw, a, b)>
	endm
_mm_sub_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psu, bd, a, b)>
	endm

_mm_sub_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psu, bq, a, b)>
	endm
_mm_subs_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psub, sb, a, b)>
	endm
_mm_subs_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psub, sw, a, b)>
	endm
_mm_subs_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psubu, sb, a, b)>
	endm
_mm_subs_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psubu, sw, a, b)>
	endm

_mm_and_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pa, nd, a, b)>
	endm
_mm_andnot_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pan, dn, a, b)>
	endm
_mm_or_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(p, or, a, b)>
	endm
_mm_xor_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(px, or, a, b)>
	endm

_mm_slli_si128 macro a:=<xmm0>, imm
	pslldq a,imm
	retm<a>
	endm
_mm_slli_epi16 macro a:=<xmm0>, imm
	psllw a,imm
	retm<a>
	endm
_mm_sll_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psl, lw, a, b)>
	endm
_mm_slli_epi32 macro a:=<xmm0>, imm
	pslld a,imm
	retm<a>
	endm
_mm_sll_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psl, ld, a, b)>
	endm
_mm_slli_epi64 macro a:=<xmm0>, imm
	psllq a,imm
	retm<a>
	endm
_mm_sll_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psl, lq, a, b)>
	endm
_mm_srai_epi16 macro a, imm
	psraw a,imm
	retm<a>
	endm
_mm_sra_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psr, aw, a, b)>
	endm
_mm_srai_epi32 macro a:=<xmm0>, imm
	psrad a,imm
	retm<a>
	endm
_mm_sra_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psr, ad, a, b)>
	endm
_mm_srli_si128 macro a:=<xmm0>, imm
	psrldq a,imm
	retm<a>
	endm
_mm_srli_epi16 macro a:=<xmm0>, imm
	psrlw a,imm
	retm<a>
	endm
_mm_srl_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psr, lw, a, b)>
	endm
_mm_srli_epi32 macro a:=<xmm0>, imm
	psrld a,imm
	retm<a>
	endm
_mm_srl_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psr, ld, a, b)>
	endm
_mm_srli_epi64 macro a:=<xmm0>, imm
	psrlq a,imm
	retm<a>
	endm
_mm_srl_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(psr, lq, a, b)>
	endm

_mm_cmpeq_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pcmpe, qb, a, b)>
	endm
_mm_cmpeq_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pcmpe, qw, a, b)>
	endm
_mm_cmpeq_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pcmpe, qd, a, b)>
	endm
_mm_cmpgt_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pcmpg, tb, a, b)>
	endm
_mm_cmpgt_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pcmpg, tw, a, b)>
	endm
_mm_cmpgt_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(pcmpg, td, a, b)>
	endm
_mm_cmplt_epi8 macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
	pcmpgtb x,a
	retm<x>
	endm
_mm_cmplt_epi16 macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
	pcmpgtw x,a
	retm<x>
	endm
_mm_cmplt_epi32 macro x:req, a:req, b:req
    ifdif <x>,<b>
	movaps x,b
    endif
	pcmpgtd x,a
	retm<x>
	endm
_mm_cvtsi32_si128 macro x, d
    ifnb <d>
	if (type d) eq 4 and (opattr d) eq 48
	    movd x,d
	else
	    mov eax,d
	    movd x,eax
	endif
	retm<x>
    else
	mov eax,x
	movd xmm0,eax
	retm<xmm0>
    endif
	endm
_mm_cvtsi128_si32 macro a:=<xmm0>
	movd eax,a
	retm<eax>
	endm

_mm_packs_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(packss, wb, a, b)>
	endm
_mm_packs_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(packss, dw, a, b)>
	endm
_mm_packus_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(packus, wb, a, b)>
	endm
_mm_extract_epi16 macro a:=<xmm0>, imm
	pextrw eax, a, imm
	retm<ax>
	endm
_mm_insert_epi16 macro a:=<xmm0>, reg, imm
	pinsrw a, reg, imm
	retm<a>
	endm

_mm_movemask_epi8 macro a:=<xmm0>
	pmovmskb eax,a
	retm<eax>
	endm
_mm_shuffle_epi32 macro a:=<xmm0>, imm
	pshufd a, a, imm
	retm<a>
	endm
_mm_shufflehi_epi16 macro a:=<xmm0>, imm
	pshufhw a, a, imm
	retm<a>
	endm
_mm_shufflelo_epi16 macro a:=<xmm0>, imm
	pshuflw a, a, imm
	retm<a>
	endm
_mm_unpackhi_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckh, bw, a, b)>
	endm
_mm_unpackhi_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckh, wd, a, b)>
	endm
_mm_unpackhi_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckh, dq, a, b)>
	endm
_mm_unpackhi_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckhq, dq, a, b)>
	endm
_mm_unpacklo_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckl, bw, a, b)>
	endm
_mm_unpacklo_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckl, wd, a, b)>
	endm
_mm_unpacklo_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpckl, dq, a, b)>
	endm
_mm_unpacklo_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(punpcklq, dq, a, b)>
	endm

_mm_load_si128 macro x, p
    ifnb <p>
	movdqa x,_MM_MREG(p)
    else
	movdqa xmm0,_MM_MREG(x)
    endif
	retm<x>
	endm
_mm_loadu_si128 macro x, p
    ifnb <p>
	movdqu x,_MM_MREG(p)
    else
	movdqu xmm0,_MM_MREG(x)
    endif
    retm<xmm0>
    endm
_mm_loadl_epi64 macro x, p
    ifnb <p>
	movq x,_MM_MREG(p)
    else
	movq xmm0,_MM_MREG(x)
    endif
    retm<xmm0>
    endm

_mm_set_epix macro x, op, args:vararg
    local v
.data
    align 16
    v label xmmword
    op &args
.code
    movdqa x,v
    retm<x>
    endm

_mm_set_epi64x macro x, a, b
    ifnb <b>
	_mm_set_epix(x, dq, b, a)
	retm<x>
    else
	_mm_set_epix(xmm0, dq, a, x)
	retm<xmm0>
    endif
    endm

_mm_set_epi32 macro x, _1, _2, _3, _4
    ifnb <_4>
	_mm_set_epix(x, dd, _4, _3, _2, _1)
	retm<x>
    else
	_mm_set_epix(xmm0, dd, _3, _2, _1, x)
	retm<xmm0>
    endif
    endm

_mm_get_epi32 macro args:vararg
    local v
.data
    align 16
    v label oword
    dd &args
.code
    exitm<v>
    endm

_mm_set_epi16 macro _1, _2, _3, _4, _5, _6, _7, _8
    _mm_set_epix(xmm0, dw, _8,_7,_6,_5,_4,_3,_2,_1)
    retm<xmm0>
    endm
_mm_set_epi8 macro _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16
    _mm_set_epix(xmm0, db, _16,_15,_14,_13,_12,_11,_10,_9,_8,_7,_6,_5,_4,_3,_2,_1)
    retm<xmm0>
    endm
_mm_set1_epi64x macro a
    _mm_set_epix(xmm0, dq, a, a)
    retm<xmm0>
    endm
_mm_set1_epi32 macro a
    _mm_set_epix(xmm0, dd, a, a, a, a)
    retm<xmm0>
    endm
_mm_set1_epi16 macro a
    _mm_set1_epi32((a or (a shl 16)))
    retm<xmm0>
    endm
_mm_set1_epi8 macro a
    _mm_set1_epi16((a or (a shl 8)))
    retm<xmm0>
    endm
ifdef _M_X64
_mm_set1_epi64 macro a:=<xmm0>
    punpcklqdq a,a
    retm<a>
    endm
endif

_mm_setr_epi32 macro args:vararg
    _mm_set_epix(xmm0, dd, args)
    retm<xmm0>
    endm
_mm_setr_epi16 macro args:vararg
    _mm_set_epix(xmm0, dw, args)
    retm<xmm0>
    endm
_mm_setr_epi8 macro args:vararg
    _mm_set_epix(xmm0, db, args)
    retm<xmm0>
    endm
_mm_setzero_si128 macro x:=<xmm0>
    xorps x, x
    retm<x>
    endm

_mm_store_si128 macro p, x:=<xmm0>
    exitm<movaps _MM_MREG(p), x>
    endm
_mm_storeu_si128 macro p, x:=<xmm0>
    exitm<movups _MM_MREG(p), x>
    endm
_mm_storel_epi64 macro p, x:=<xmm0>
    exitm<movq _MM_MREG(p), x>
    endm
_mm_maskmoveu_si128 macro a:=<xmm0>, b:=<xmm1>, reg
    exitm<maskmovdqu a,b>
    endm

_mm_move_epi64 macro x:=<xmm0>, r:=<rax>
	movq x,r
	retm<x>
	endm

_mm_stream_pd macro reg, x:=<xmm0>
	exitm<movntpd _MM_MREG(p), x>
	endm
_mm_stream_si128 macro reg, x:=<xmm0>
	exitm<movntdq _MM_MREG(p), x>
	endm
_mm_clflush macro reg
	exitm<clflush _MM_MREG(p)>
	endm
_mm_lfence macro
	exitm<lfence>
	endm
_mm_mfence macro
	exitm<mfence>
	endm
_mm_stream_si32 macro p, x
	movnti _MM_MREG(p),x
	retm<p>
	endm
if 0
_mm_pause macro
	exitm<nop>
	endm
endif
;;
;; New convert to float
;;
_mm_cvtsd_f64 macro x:=<xmm0>
	cvtsd2ss x,x
	retm<x>
	endm

;;
;; Support for casting between various SP, DP, INT vector types.
;; Note that these do no conversion of values, they just change
;; the type.
;;
_mm_castpd_ps macro x:=<xmm0>
	retm<x>
	endm
_mm_castpd_si128 macro x:=<xmm0>
	retm<x>
	endm
_mm_castps_pd macro x:=<xmm0>
	retm<x>
	endm
_mm_castps_si128 macro x:=<xmm0>
	retm<x>
	endm
_mm_castsi128_ps macro x:=<xmm0>
	retm<x>
	endm
_mm_castsi128_pd macro x:=<xmm0>
	retm<x>
	endm

;;
;; Support for 64-bit extension intrinsics
;;
ifdef _M_X64
_mm_cvtsd_si64 macro x:=<xmm0>
	cvtsd2si rax,x
	retm<rax>
	endm
_mm_cvttsd_si64 macro x:=<xmm0>
	cvttsd2si rax,x
	retm<rax>
	endm
_mm_cvtsi64_sd macro x:=<xmm0>, reg:=<rax>
	cvtsi2sd x,reg
	retm<x>
	endm
_mm_cvtsi64_si128 macro x, q
    ifnb <q>
	mov rax,q
	movq x,rax
	retm<x>
    else
	mov rax,x
	movq xmm0,rax
	retm<xmm0>
    endif
	endm
_mm_cvtsi128_si64 macro x:=<xmm0>
	movq rax,x
	retm<rax>
	endm

endif

;ifdef _M_IX86
_mm_movpi64_epi64 macro m:=<mm0>
    movq2dq xmm0,m
    retm<xmm0>
    endm
_mm_movepi64_pi64 macro x:=<xmm0>
    movdq2q mm0,x
    retm<mm0>
    endm
;endif

;; Alternate intrinsic name definitions

ifdef _M_X64
_mm_stream_si64		equ <_mm_stream_si64x>
endif

;ifdef _M_IX86
_mm_cvtpd_pi32 macro x:=<xmm0>
	cvtpd2pi mm0,x
	retm<mm0>
	endm
_mm_cvttpd_pi32 macro x:=<xmm0>
	cvttpd2pi mm0,x
	retm<mm0>
	endm
_mm_cvtpi32_pd macro m:=<mm0>
	cvtpi2pd xmm0,x
	retm<xmm0>
	endm
_mm_add_si64 macro m1, m2
	paddq m1,m2
	retm<m1>
	endm
_mm_mul_su32 macro m1, m2
	pmuludq m1,m2
	retm<m1>
	endm
_mm_sub_si64 macro m1, m2
	psubq m1,m2
	retm<m1>
	endm
_mm_set_epi64 macro m1, m2
	movq2dq xmm0,m1
	movq2dq xmm1,m2
	punpcklqdq xmm0,xmm1
	retm<xmm0>
	endm
_mm_setr_epi64 macro m1, m2
	movq2dq xmm0,m2
	movq2dq xmm1,m1
	punpcklqdq xmm0,xmm1
	retm<xmm0>
	endm
;endif

.pragma list(pop)
endif
