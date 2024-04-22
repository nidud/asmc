ifndef _INCLUDED_EMM
define _INCLUDED_EMM
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
m128i_i8	sbyte 16 dup(?)
m128i_i16	sword  8 dup(?)
m128i_i32	sdword 4 dup(?)
m128i_i64	sqword 2 dup(?)
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

ifndef _mmopab
_mmopab macro o, a, b
    o a,b
    retm <a>
    endm
endif

_mm_add_sd macro a, b
    exitm<_mmopab(addsd,a,b)>
    endm
_mm_add_pd macro a, b
    exitm<_mmopab(addpd,a,b)>
    endm
_mm_sub_sd macro a, b
    exitm<_mmopab(subsd,a,b)>
    endm
_mm_sub_pd macro a, b
    exitm<_mmopab(subpd,a,b)>
    endm
_mm_mul_sd macro a, b
    exitm<_mmopab(mulsd,a,b)>
    endm
_mm_mul_pd macro a, b
    exitm<_mmopab(mulpd,a,b)>
    endm

_mm_sqrt_sd macro a, b
    exitm<_mmopab(sqrtsd,a,b)>
    endm
_mm_sqrt_pd macro a, b
    exitm<_mmopab(sqrtpd,a,b)>
    endm

_mm_div_sd macro a, b
    exitm<_mmopab(divsd,a,b)>
    endm
_mm_div_pd macro a, b
    exitm<_mmopab(divpd,a,b)>
    endm

_mm_min_sd macro a, b
    exitm<_mmopab(minsd,a,b)>
    endm
_mm_min_pd macro a, b
    exitm<_mmopab(minpd,a,b)>
    endm
_mm_max_sd macro a, b
    exitm<_mmopab(maxsd,a,b)>
    endm
_mm_max_pd macro a, b
    exitm<_mmopab(maxpd,a,b)>
    endm
_mm_and_pd macro a, b
    exitm<_mmopab(andpd,a,b)>
    endm
_mm_andnot_pd macro a, b
    exitm<_mmopab(andnpd,a,b)>
    endm
_mm_or_pd macro a, b
    exitm<_mmopab(orpd,a,b)>
    endm
_mm_xor_pd macro a, b
    exitm<_mmopab(xorpd,a,b)>
    endm

_mm_cmpeq_sd macro a, b
    exitm<_mmopab(cmpeqsd,a,b)>
    endm
_mm_cmpeq_pd macro a, b
    exitm<_mmopab(cmpeqpd,a,b)>
    endm
_mm_cmplt_sd macro a, b
    exitm<_mmopab(cmpltsd,a,b)>
    endm
_mm_cmplt_pd macro a, b
    exitm<_mmopab(cmpltpd,a,b)>
    endm
_mm_cmple_sd macro a, b
    exitm<_mmopab(cmplesd,a,b)>
    endm
_mm_cmple_pd macro a, b
    exitm<_mmopab(cmplepd,a,b)>
    endm

_mm_cmpgt_sd macro x, a, b
ifdif <x>,<b>
    movsd x,b
endif
    exitm<_mm_cmplt_sd(x, a)>
    endm
_mm_cmpgt_pd macro x, a, b
ifdif <x>,<b>
    movapd x,b
endif
    exitm<_mm_cmplt_pd(x, a)>
    endm
_mm_cmpge_sd macro x, a, b
ifdif <x>,<b>
    movsd x,b
endif
    exitm<_mm_cmple_sd(x, a)>
    endm
_mm_cmpge_pd macro x, a, b
ifdif <x>,<b>
    movapd x,b
endif
    exitm<_mm_cmple_pd(x, a)>
    endm

_mm_cmpneq_sd macro a, b
    exitm<_mmopab(cmpneqsd,a,b)>
    endm
_mm_cmpneq_pd macro a, b
    exitm<_mmopab(cmpneqpd, a, b)>
    endm
_mm_cmpnlt_sd macro a, b
    exitm<_mmopab(cmpnltsd, a, b)>
    endm
_mm_cmpnlt_pd macro a, b
    exitm<_mmopab(cmpnltpd, a, b)>
    endm
_mm_cmpnle_sd macro a, b
    exitm<_mmopab(cmpnlesd, a, b)>
    endm
_mm_cmpnle_pd macro a, b
    exitm<_mmopab(cmpnlepd, a, b)>
    endm

_mm_cmpngt_sd macro x, a, b
ifdif <x>,<b>
    movsd x,b
endif
    exitm<_mm_cmpnlt_sd(x, a)>
    endm
_mm_cmpngt_pd macro x, a, b
ifdif <x>,<b>
    movapd x,b
endif
    exitm<_mm_cmpnlt_pd(x, a)>
    endm
_mm_cmpnge_sd macro x, a, b
ifdif <x>,<b>
    movsd x,b
endif
    exitm<_mm_cmpnle_sd(x, a)>
    endm
_mm_cmpnge_pd macro x, a, b
ifdif <x>,<b>
    movapd xmm0,xmm2
endif
    exitm<_mm_cmpnle_pd(xmm0, xmm1)>
    endm

_mm_cmpord_pd macro a, b
    exitm<_mmopab(cmpordpd, a, b)>
    endm
_mm_cmpord_sd macro a, b
    exitm<_mmopab(cmpordsd, a, b)>
    endm
_mm_cmpunord_pd macro a, b
    exitm<_mmopab(cmpunordpd, a, b)>
    endm
_mm_cmpunord_sd macro a, b
    exitm<_mmopab(cmpunordsd, a, b)>
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
	exitm<_mmopab(cvtdq2pd, a, b)>
    else
	exitm<_mmopab(cvtdq2pd, a, a)>
    endif
    endm
_mm_cvtpd_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvtpd2dq, a, b)>
    else
	exitm<_mmopab(cvtpd2dq, a, a)>
    endif
    endm
_mm_cvttpd_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvttpd2dq, a, b)>
    else
	exitm<_mmopab(cvttpd2dq, a, a)>
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
	exitm<_mmopab(cvtps2dq, a, b)>
    else
	exitm<_mmopab(cvtps2dq, a, a)>
    endif
    endm
_mm_cvttps_epi32 macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvttps2dq, a, b)>
    else
	exitm<_mmopab(cvttps2dq, a, a)>
    endif
    endm
_mm_cvtpd_ps macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvtpd2ps, a, b)>
    else
	exitm<_mmopab(cvtpd2ps, a, a)>
    endif
    endm
_mm_cvtps_pd macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvtps2pd, a, b)>
    else
	exitm<_mmopab(cvtps2pd, a, a)>
    endif
    endm
_mm_cvtsd_ss macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvtsd2ss, a, b)>
    else
	exitm<_mmopab(cvtsd2ss, a, a)>
    endif
    endm
_mm_cvtss_sd macro a:=<xmm0>, b
    ifnb <b>
	exitm<_mmopab(cvtss2sd, a, b)>
    else
	exitm<_mmopab(cvtss2sd, a, a)>
    endif
    endm

_mm_cvtsd_si32 macro a:=<xmm0>
    exitm<_mmopab(cvtsd2si, eax, a)>
    endm
_mm_cvttsd_si32 macro a:=<xmm0>
    exitm<_mmopab(cvttsd2si, eax, a)>
    endm

_mm_cvtsi32_sd macro a, b
    ifnb <b>
	exitm<_mmopab(cvtsi2sd, a, b)>
    else
	exitm<_mmopab(cvtsi2sd, a, a)>
    endif
    endm

_mm_unpackhi_pd macro a, b
    ifnb <b>
	exitm<_mmopab(unpckhpd, a, b)>
    else
	exitm<_mmopab(unpckhpd, a, a)>
    endif
    endm
_mm_unpacklo_pd macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(unpcklpd, a, b)>
    endm
_mm_movemask_pd macro a:=<xmm0>
    exitm<_mmopab(movmskpd, eax, a)>
    endm

_mm_shuffle_pd macro a, b, imm
    shufpd a,b,imm
    retm<a>
    endm

_mm_load_pd macro p
    exitm<_mmopab(movapd, xmm0, p)>
    endm
_mm_load1_pd macro p
    exitm<_mmopab(unpcklpd, xmm0, p)>
    endm
_mm_loadr_pd macro p
    exitm<_mm_shuffle_pd(_mm_load_pd(p),xmm0,1)>
    endm
_mm_loadu_pd macro p
    exitm<_mmopab(movupd, xmm0, p)>
    endm
_mm_load_sd macro p
    exitm<_mmopab(movq, xmm0, p)>
    endm

_mm_loadh_pd macro x, p
    exitm<_mmopab(movhpd, x, p)>
    endm
_mm_loadl_pd macro x, p
    exitm<_mmopab(movlpd, x, p)>
    endm

_mm_set_sd proto :real8
_mm_set_sd macro x
    retm<xmm0>
    endm
_mm_set1_pd macro x
    exitm<_mmopab(unpcklpd, x, x)>
    endm
_mm_set_pd macro d0, d1
    exitm<_mmopab(unpckhpd, d0, d1)>
    endm
_mm_setr_pd macro a, b
    exitm<_mmopab(unpcklpd, a, b)>
    endm
_mm_setzero_pd macro x:=<xmm0>
    exitm<_mmopab(pxor, x, x)>
    endm

_mm_move_sd macro a, b
    movsd a,b
    retm<a>
    endm
_mm_move_pd macro a, b
    ifdif <a>,<b>
	movapd a,b
    endif
    retm<a>
    endm

_mm_store_sd macro p, x
    exitm<_mmopab(movlpd, p, x)>
    endm
_mm_store1_pd macro p, x
    unpcklpd x,x
    exitm<_mmopab(movaps, p,,x)>
    endm
_mm_store_pd macro p, x
    exitm<_mmopab(movaps, p, x)>
    endm
_mm_storeu_pd macro p, x
    exitm<_mmopab(movups, p, x)>
    endm
_mm_storer_pd macro p, x
    shufpd x,x,1
    exitm<_mmopab(movaps, p, x)>
    endm
_mm_storeh_pd macro p, x
    exitm<_mmopab(movhpd, p, x)>
    endm
_mm_storel_pd macro p, x
    exitm<_mmopab(movlpd, p, x)>
    endm

_mm_add_epi8 macro a, b
    exitm<_mmopab(paddb, a, b)>
    endm
_mm_add_epi16 macro a, b
    exitm<_mmopab(paddw, a, b)>
    endm
_mm_add_epi32 macro a, b
    exitm<_mmopab(paddd, a, b)>
    endm
_mm_add_epi64 macro a, b
    exitm<_mmopab(paddq, a, b)>
    endm

_mm_adds_epi8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(paddsb, a, b)>
    endm
_mm_adds_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(paddsw, a, b)>
    endm
_mm_adds_epu8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(paddusb, a, b)>
    endm
_mm_adds_epu16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(paddusw, a, b)>
    endm
_mm_avg_epu8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pavgb, a, b)>
    endm
_mm_avg_epu16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pavgw, a, b)>
    endm
_mm_madd_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmaddwd, a, b)>
    endm
_mm_max_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmaxsw, a, b)>
    endm
_mm_max_epu8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmaxub, a, b)>
    endm
_mm_min_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pminsw, a, b)>
    endm
_mm_min_epu8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pminub, a, b)>
    endm
_mm_mulhi_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmulhw, a, b)>
    endm
_mm_mulhi_epu16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmulhuw, a, b)>
    endm
_mm_mullo_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmullw, a, b)>
    endm

_mm_mul_epu32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pmuludq, a, b)>
    endm
_mm_sad_epu8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psadbw, a, b)>
    endm
_mm_sub_epi8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubb, a, b)>
    endm
_mm_sub_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubw, a, b)>
    endm
_mm_sub_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubd, a, b)>
    endm

_mm_sub_epi64 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubq, a, b)>
    endm
_mm_subs_epi8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubsb, a, b)>
    endm
_mm_subs_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubsw, a, b)>
    endm
_mm_subs_epu8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubusb, a, b)>
    endm
_mm_subs_epu16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psubusw, a, b)>
    endm

_mm_and_si128 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pand, a, b)>
    endm
_mm_andnot_si128 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pandn, a, b)>
    endm
_mm_or_si128 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(por, a, b)>
    endm
_mm_xor_si128 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pxor, a, b)>
    endm

_mm_slli_si128 macro a:=<xmm0>, imm
    exitm<_mmopab(pslldq, a, imm)>
    endm
_mm_slli_epi16 macro a:=<xmm0>, imm
    exitm<_mmopab(psllw, a, imm)>
    endm
_mm_sll_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psllw, a, b)>
    endm
_mm_slli_epi32 macro a:=<xmm0>, imm
    exitm<_mmopab(pslld, a, imm)>
    endm
_mm_sll_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pslld, a, b)>
    endm
_mm_slli_epi64 macro a:=<xmm0>, imm
    exitm<_mmopab(psllq, a, imm)>
    endm
_mm_sll_epi64 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psllq, a, b)>
    endm
_mm_srai_epi16 macro a, imm
    exitm<_mmopab(psraw, a, imm)>
    endm
_mm_sra_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psraw, a, b)>
    endm
_mm_srai_epi32 macro a:=<xmm0>, imm
    exitm<_mmopab(psrad, a, imm)>
    endm
_mm_sra_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psrad, a, b)>
    endm
_mm_srli_si128 macro a:=<xmm0>, imm
    exitm<_mmopab(psrldq, a, imm)>
    endm
_mm_srli_epi16 macro a:=<xmm0>, imm
    exitm<_mmopab(psrlw, a, imm)>
    endm
_mm_srl_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psrlw, a, b)>
    endm
_mm_srli_epi32 macro a:=<xmm0>, imm
    exitm<_mmopab(psrld, a, imm)>
    endm
_mm_srl_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psrld, a, b)>
    endm
_mm_srli_epi64 macro a:=<xmm0>, imm
    exitm<_mmopab(psrlq, a, imm)>
    endm
_mm_srl_epi64 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(psrlq, a, b)>
    endm

_mm_cmpeq_epi8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pcmpeqb, a, b)>
    endm
_mm_cmpeq_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pcmpeqw, a, b)>
    endm
_mm_cmpeq_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pcmpeqd, a, b)>
    endm
_mm_cmpgt_epi8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pcmpgtb, a, b)>
    endm
_mm_cmpgt_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pcmpgtw, a, b)>
    endm
_mm_cmpgt_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(pcmpgtd, a, b)>
    endm

_mm_cmplt_epi8 macro x, a, b
ifdif <x>,<b>
    movaps x,b
endif
    exitm<_mmopab(pcmpgtb, x, a)>
    endm
_mm_cmplt_epi16 macro x, a, b
ifdif <x>,<b>
    movaps x,b
endif
    exitm<_mmopab(pcmpgtw, x, a)>
    endm
_mm_cmplt_epi32 macro x, a, b
ifdif <x>,<b>
    movaps x,b
endif
    exitm<_mmopab(pcmpgtd, x, a)>
    endm

_mm_cvtsi32_si128 macro x, d
    ifnb <d>
	if (TYPE d) eq 4 and (opattr d) eq 48
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
    exitm<_mmopab(packsswb, a, b)>
    endm
_mm_packs_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(packssdw, a, b)>
    endm
_mm_packus_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(packuswb, a, b)>
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
    exitm<_mmopab(punpckhbw, a, b)>
    endm
_mm_unpackhi_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpckhwd, a, b)>
    endm
_mm_unpackhi_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpckhdq, a, b)>
    endm
_mm_unpackhi_epi64 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpckhqdq, a, b)>
    endm
_mm_unpacklo_epi8 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpcklbw, a, b)>
    endm
_mm_unpacklo_epi16 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpcklwd, a, b)>
    endm
_mm_unpacklo_epi32 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpckldq, a, b)>
    endm
_mm_unpacklo_epi64 macro a:=<xmm0>, b:=<xmm1>
    exitm<_mmopab(punpcklqdq, a, b)>
    endm

_mm_load_si128 macro x, p
    ifnb <p>
	exitm<_mmopab(movdqa, x, p)>
    endif
    exitm<_mmopab(movdqa, xmm0, x)>
    endm
_mm_loadu_si128 macro x, p
    ifnb <p>
	exitm<_mmopab(movdqu, x, p)>
    endif
    exitm<_mmopab(movdqu, xmm0, x)>
    endm
_mm_loadl_epi64 macro x, p
    ifnb <p>
	exitm<_mmopab(movq, x, p)>
    endif
    exitm<_mmopab(movq, xmm0, x)>
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

_mm_set_epix macro xmm, op, args:vararg
.data
    align 16
    @@ label oword
    op &args
.code
    movaps xmm,@B
    retm<xmm>
    endm

_mm_set_epi64x macro x, Q1, Q2
    exitm<_mm_set_epix(x, dq, Q1, Q2)>
    endm

_mm_set_epi32 macro x, D1, D2, D3, D4
    ifnb <D4>
	exitm<_mm_set_epix(x, dd, D4, D3, D2, D1)>
    endif
    exitm<_mm_set_epix(xmm0, dd, D3, D2, D1, x)>
    endm
_mm_set_epi16 macro x, _1, _2, _3, _4, _5, _6, _7, _8
    exitm<_mm_set_epi32(x, ((_1 shl 16) or _2), ((_3 shl 16) or _4),
	((_5 shl 16) or _6), ((_7 shl 16) or _8))>
    endm
_mm_set_epi8 macro x, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16
    exitm<_mm_set_epi16(x, ((_1 shl 8) or _2), ((_3 shl 8) or _4), ((_5 shl 8) or _6),
	((_7 shl 8) or _8), ((_9 shl 8) or _10), ((_11 shl 8) or _12),
	((_13 shl 8) or _14), ((_15 shl 8) or _16))>
    endm

_mm_set1_epi64x macro xmm, imm
    mov	     rax,imm
    movq     xmm,rax
    unpcklpd xmm,xmm
    retm    <xmm>
    endm
_mm_set1_epi32 macro xmm, imm
    mov	     eax,imm
    movd     xmm,eax
    shufps   xmm,xmm,0
    retm    <xmm>
    endm
_mm_set1_epi16 macro xmm, imm
    exitm<_mm_set1_epi32(xmm, ((imm shl 16) or imm))>
    endm
_mm_set1_epi8 macro xmm, imm
    exitm<_mm_set1_epi16(xmm, ((imm shl 8) or imm))>
    endm
ifdef _M_X64
_mm_set1_epi64 macro a:=<xmm0>
    exitm<_mmopab(punpcklqdq, a, a)>
    endm
endif

_mm_setr_epi32 macro D1, D2, D3, D4
    exitm<_mm_set_epi32(xmm0, D1, D2, D3, D4)>
    endm
_mm_setr_epi16 macro _1, _2, _3, _4, _5, _6, _7, _8
    exitm<_mm_set_epi16(xmm0, _1, _2, _3, _4, _5, _6, _7, _8)>
    endm
_mm_setr_epi8 macro _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16
    exitm<_mm_set_epix(xmm0, db, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16)>
    endm
_mm_setzero_si128 macro x:=<xmm0>
    exitm<_mmopab(xorps, x, x)>
    endm

_mm_store_si128 macro p, x:=<xmm0>
    exitm<_mmopab(movaps, p, x)>
    endm
_mm_storeu_si128 macro p, x:=<xmm0>
    exitm<_mmopab(movups, p, x)>
    endm
_mm_storel_epi64 macro p, x:=<xmm0>
    exitm<_mmopab(movq, p, x)>
    endm
_mm_maskmoveu_si128 macro a:=<xmm0>, b:=<xmm1>, reg
    exitm<_mmopab(maskmovdqu, a, b)>
    endm

_mm_move_epi64 macro x:=<xmm0>, r:=<rax>
    exitm<_mmopab(movq, x, r)>
    endm

_mm_stream_pd macro p, x:=<xmm0>
    exitm<_mmopab(movntpd, p, x)>
    endm
_mm_stream_si128 macro p, x:=<xmm0>
    exitm<_mmopab(movntdq, p, x)>
    endm
_mm_clflush macro p
    exitm<clflush p>
    endm
_mm_lfence macro
    exitm<lfence>
    endm
_mm_mfence macro
    exitm<mfence>
    endm
_mm_stream_si32 macro p, x
    exitm<_mmopab(movnti, p, x)>
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
    exitm<_mmopab(cvtsd2ss, x, x)>
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
    exitm<_mmopab(cvtsd2si, rax, x)>
    endm
_mm_cvttsd_si64 macro x:=<xmm0>
    exitm<_mmopab(cvttsd2si, rax, x)>
    endm
_mm_cvtsi64_sd macro x:=<xmm0>, reg:=<rax>
    if (opattr(reg)) eq 48
	cvtsi2sd x,reg
    else
	if (TYPE reg) eq 4 and not ((opattr(reg)) eq 48)
	    mov eax,reg
	else
	    mov rax,reg
	endif
	cvtsi2sd x,rax
    endif
    retm<x>
    endm
_mm_cvtsi64_si128 macro x, q
    ifnb <q>
	mov rax,q
	exitm<_mmopab(movq, x, rax)>
    endif
    mov rax,x
    exitm<_mmopab(movq, xmm0, rax)>
    endm
_mm_cvtsi128_si64 macro x:=<xmm0>, r:=<rax>
    exitm<_mmopab(movq, r, x)>
    endm

endif

ifdef _M_IX86
_mm_movpi64_epi64 macro m:=<mm0>
    exitm<_mmopab(movq2dq, xmm0, m)>
    endm
_mm_movepi64_pi64 macro x:=<xmm0>
    exitm<_mmopab(movdq2q, mm0, x)>
    endm
endif

;; Alternate intrinsic name definitions

ifdef _M_X64
_mm_stream_si64 equ <_mm_stream_si64x>
endif

ifdef _M_IX86
_mm_cvtpd_pi32 macro x:=<xmm0>
    exitm<_mmopab(cvtpd2pi, mm0, x)>
    endm
_mm_cvttpd_pi32 macro x:=<xmm0>
    exitm<_mmopab(cvttpd2pi, mm0, x)>
    endm
_mm_cvtpi32_pd macro m:=<mm0>
    exitm<_mmopab(cvtpi2pd, xmm0, x)>
    endm
_mm_add_si64 macro m1, m2
    exitm<_mmopab(paddq, m1, m2)>
    endm
_mm_mul_su32 macro m1, m2
    exitm<_mmopab(pmuludq, m1, m2)>
    endm
_mm_sub_si64 macro m1, m2
    exitm<_mmopab(psubq, m1, m2)>
    endm
_mm_set_epi64 macro m1, m2
    movq2dq xmm0,m1
    movq2dq xmm1,m2
    exitm<_mmopab(punpcklqdq, xmm0, xmm1)>
    endm
_mm_setr_epi64 macro m1, m2
    movq2dq xmm0,m2
    movq2dq xmm1,m1
    exitm<_mmopab(punpcklqdq, xmm0, xmm1)>
    endm
endif

.pragma list(pop)
endif
