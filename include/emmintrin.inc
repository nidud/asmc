ifndef _INCLUDED_EMM
_INCLUDED_EMM equ <>

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

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

_MM_SHUFFLE2 macro x,y
	exitm<(((x) SHL 1) OR (y))>
	endm

ifndef _MM_NOINLINE

_mm_add_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<addsd a, b>
	endm
_mm_add_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<addpd a, b>
	endm
_mm_sub_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<subsd a, b>
	endm
_mm_sub_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<subpd a, b>
	endm
_mm_mul_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<mulsd a, b>
	endm
_mm_mul_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<mulpd a, b>
	endm
_mm_sqrt_sd macro a:=<xmm0>, b:=<xmm1>
	movsd a,b
	exitm<sqrtsd a, a>
	endm
_mm_sqrt_pd macro a:=<xmm0>
	exitm<sqrtpd a, a>
	endm
_mm_div_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<divsd a, b>
	endm
_mm_div_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<divpd a, b>
	endm
_mm_min_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<minsd a, b>
	endm
_mm_min_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<minpd a, b>
	endm
_mm_max_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<maxsd a, b>
	endm
_mm_max_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<maxpd a, b>
	endm
_mm_and_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<andpd a, b>
	endm
_mm_andnot_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<andnpd a, b>
	endm
_mm_or_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<orpd a, b>
	endm
_mm_xor_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<xorpd a, b>
	endm

_mm_cmpeq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpeqsd a, b>
	endm
_mm_cmpeq_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpeqpd a, b>
	endm
_mm_cmplt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpltsd a, b>
	endm
_mm_cmplt_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpltpd a, b>
	endm
_mm_cmple_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmplesd a, b>
	endm
_mm_cmple_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmplepd a, b>
	endm
_mm_cmpgt_sd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmplt_sd(b, a)
	exitm<movsd a, b>
	endm
_mm_cmpgt_pd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmplt_pd(b, a)
	exitm<movapd a, b>
	endm
_mm_cmpge_sd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmplt_sd(b, a)
	exitm<movsd a, b>
	endm
_mm_cmpge_pd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmple_pd(b, a)
	exitm<movapd a, b>
	endm
_mm_cmpneq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpneqsd a, b>
	endm
_mm_cmpneq_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpneqpd a, b>
	endm
_mm_cmpnlt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpnltsd a, b>
	endm
_mm_cmpnlt_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpnltpd a, b>
	endm
_mm_cmpnle_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpnlesd a, b>
	endm
_mm_cmpnle_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpnlepd a, b>
	endm
_mm_cmpngt_sd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnlt_sd(b, a)
	exitm<movsd a, b>
	endm
_mm_cmpngt_pd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnlt_pd(b, a)
	exitm<movapd a, b>
	endm
_mm_cmpnge_sd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnle_sd(b, a)
	exitm<movsd a, b>
	endm
_mm_cmpnge_pd macro a:=<xmm0>, b:=<xmm1>
	_mm_cmpnle_pd(b, a)
	exitm<movapd a, b>
	endm
_mm_cmpord_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpordpd a, b>
	endm
_mm_cmpord_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpordsd a, b>
	endm
_mm_cmpunord_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpunordpd a, b>
	endm
_mm_cmpunord_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cmpunordsd a, b>
	endm

_mm_comisd macro set, a, b
	xor eax,eax
	ucomisd a,b
	set al
	exitm<eax>
	endm

_mm_comieq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(sete, a, b)>
	endm
_mm_comilt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setb, a, b)>
	endm
_mm_comile_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setbe, a, b)>
	endm
_mm_comigt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(seta, a, b)>
	endm
_mm_comige_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setnb, a, b)>
	endm
_mm_comineq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setne, a, b)>
	endm
_mm_ucomieq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(sete, a, b)>
	endm
_mm_ucomilt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setb, a, b)>
	endm
_mm_ucomile_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setbe, a, b)>
	endm
_mm_ucomigt_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(seta, a, b)>
	endm
_mm_ucomige_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(setnb, a, b)>
	endm
_mm_ucomineq_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comisd(sete, a, b)>
	endm

_mm_cvtepi32_pd macro a:=<xmm0>
	exitm<cvtdq2pd a, a>
	endm
_mm_cvtpd_epi32 macro a:=<xmm0>
	exitm<cvtpd2dq a, a>
	endm
_mm_cvttpd_epi32 macro a:=<xmm0>
	exitm<cvttpd2dq a, a>
	endm
_mm_cvtepi32_ps macro a:=<xmm0>
	exitm<cvtdq2ps a, a>
	endm
_mm_cvtps_epi32 macro a:=<xmm0>
	exitm<cvtps2dq a, a>
	endm
_mm_cvttps_epi32 macro a:=<xmm0>
	exitm<cvttps2dq a, a>
	endm
_mm_cvtpd_ps macro a:=<xmm0>
	exitm<cvtpd2ps a, a>
	endm
_mm_cvtps_pd macro a:=<xmm0>
	exitm<cvtps2pd a, a>
	endm
_mm_cvtsd_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<cvtsd2ss a, b>
	endm
_mm_cvtss_sd macro a:=<xmm0>, b:=<xmm1>
	exitm<cvtss2sd a, b>
	endm

_mm_cvtsd_si32 macro a:=<xmm0>
	exitm<cvtsd2si eax,a>
	endm
_mm_cvttsd_si32 macro a:=<xmm0>
	exitm<cvttsd2si eax,a>
	endm
_mm_cvtsi32_sd macro a:=<xmm0>, b
	exitm<cvtsi2sd a,b>
	endm

_mm_unpackhi_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<unpckhpd a,b>
	endm
_mm_unpacklo_pd macro a:=<xmm0>, b:=<xmm1>
	exitm<unpcklpd a,b>
	endm
_mm_movemask_pd macro a:=<xmm0>
	exitm<movmskpd eax,a>
	endm
_mm_shuffle_pd macro a:=<xmm0>, b:=<xmm1>, imm
	exitm<shufpd a,b,imm>
	endm

_mm_load_pd macro reg
	exitm<movapd xmm0,[reg]>
	endm
_mm_load1_pd macro reg
	movsd xmm0,[reg]
	exitm<unpcklpd xmm0,xmm0>
	endm
_mm_loadr_pd macro reg
	_mm_load_pd(reg)
	exitm<_mm_shuffle_pd(xmm0,xmm0,1)>
	endm
_mm_loadu_pd macro reg
	exitm<movupd xmm0,[reg]>
	endm
_mm_load_sd macro reg
	exitm<movq xmm0,[reg]>
	endm
_mm_loadh_pd macro x:=<xmm0>, reg
	exitm<movhpd x,[reg]>
	endm
_mm_loadl_pd macro x:=<xmm0>, reg
	exitm<movlpd x,[reg]>
	endm

_mm_set_sd macro r
	exitm<movq xmm0,r>
	endm
_mm_set1_pd macro r
	exitm<unpcklpd xmm0,r>
	endm
_mm_set_pd macro d0:=<xmm0>, d1:=<xmm1>
	movapd xmm2,d1
	unpcklpd xmm2,d0
	exitm<movapd xmm0,xmm2>
	endm
_mm_setr_pd macro r1:=<xmm0>, r2:=<xmm1>
	exitm<unpcklpd r1,r2>
	endm
_mm_setzero_pd macro
	exitm<pxor xmm0,xmm0>
	endm
_mm_move_sd macro x1, x2
	exitm<movsd x1,x2>
	endm

_mm_store_sd macro p, x0:=<xmm0>
	exitm<movlpd [p],x0>
	endm
_mm_store1_pd macro p, x0:=<xmm0>
	movapd xmm1,x0
	unpcklpd xmm1,x0
	exitm<movaps [p],x0>
	endm
_mm_store_pd macro p, x0:=<xmm0>
	exitm<movaps [p],x0>
	endm
_mm_storeu_pd macro p, x0:=<xmm0>
	exitm<movups [p],x0>
	endm
_mm_storer_pd macro p, x0:=<xmm0>
	movapd xmm1,x0
	shufpd xmm1,x0,1
	exitm<movaps [p],xmm1>
	endm
_mm_storeh_pd macro p, x0:=<xmm0>
	exitm<movhpd [p],x0>
	endm
_mm_storel_pd macro p, x0:=<xmm0>
	exitm<movlpd [p],x0>
	endm

_mm_add_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddb a,b>
	endm
_mm_add_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddw a,b>
	endm
_mm_add_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddd a,b>
	endm
_mm_add_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddq a,b>
	endm

_mm_adds_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddsb a,b>
	endm
_mm_adds_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddsw a,b>
	endm
_mm_adds_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddusb a,b>
	endm
_mm_adds_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<paddusw a,b>
	endm
_mm_avg_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<pavgb a,b>
	endm
_mm_avg_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pavgw a,b>
	endm
_mm_madd_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmaddwd a,b>
	endm
_mm_max_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmaxsw a,b>
	endm
_mm_max_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmaxub a,b>
	endm
_mm_min_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pminsw a,b>
	endm
_mm_min_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<pminub a,b>
	endm
_mm_mulhi_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmulhw a,b>
	endm
_mm_mulhi_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmulhuw a,b>
	endm
_mm_mullo_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmullw a,b>
	endm

_mm_mul_epu32 macro a:=<xmm0>, b:=<xmm1>
	exitm<pmuludq a,b>
	endm
_mm_sad_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<psadbw a,b>
	endm
_mm_sub_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubb a,b>
	endm
_mm_sub_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubw a,b>
	endm
_mm_sub_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubd a,b>
	endm

_mm_sub_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubq a,b>
	endm
_mm_subs_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubsb a,b>
	endm
_mm_subs_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubsw a,b>
	endm
_mm_subs_epu8 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubusb a,b>
	endm
_mm_subs_epu16 macro a:=<xmm0>, b:=<xmm1>
	exitm<psubusw a,b>
	endm

_mm_and_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<pand a,b>
	endm
_mm_andnot_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<pandn a,b>
	endm
_mm_or_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<por a,b>
	endm
_mm_xor_si128 macro a:=<xmm0>, b:=<xmm1>
	exitm<pxor a,b>
	endm

_mm_slli_si128 macro a:=<xmm0>, imm
	exitm<pslldq a,imm>
	endm
_mm_slli_epi16 macro a:=<xmm0>, imm
	exitm<psllw a,imm>
	endm
_mm_sll_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<psllw a,b>
	endm
_mm_slli_epi32 macro a:=<xmm0>, imm
	exitm<pslld a,b>
	endm
_mm_sll_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<pslld a,b>
	endm
_mm_slli_epi64 macro a:=<xmm0>, imm
	exitm<psllq a,b>
	endm
_mm_sll_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<psllq a,b>
	endm
_mm_srai_epi16 macro a:=<xmm0>, imm
	exitm<psraw a,b>
	endm
_mm_sra_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<psraw a,b>
	endm
_mm_srai_epi32 macro a:=<xmm0>, imm
	exitm<psrad a,b>
	endm
_mm_sra_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<psrad a,b>
	endm
_mm_srli_si128 macro a:=<xmm0>, imm
	exitm<psrldq a,b>
	endm
_mm_srli_epi16 macro a:=<xmm0>, imm
	exitm<psrlw a,b>
	endm
_mm_srl_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<psrlw a,b>
	endm
_mm_srli_epi32 macro a:=<xmm0>, imm
	exitm<psrld a,b>
	endm
_mm_srl_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<psrld a,b>
	endm
_mm_srli_epi64 macro a:=<xmm0>, imm
	exitm<psrlq a,b>
	endm
_mm_srl_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<psrlq a,b>
	endm

_mm_cmpeq_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<pcmpeqb a,b>
	endm
_mm_cmpeq_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pcmpeqw a,b>
	endm
_mm_cmpeq_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<pcmpeqd a,b>
	endm
_mm_cmpgt_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<pcmpgtb a,b>
	endm
_mm_cmpgt_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<pcmpgtw a,b>
	endm
_mm_cmpgt_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<pcmpgtd a,b>
	endm
_mm_cmplt_epi8 macro a:=<xmm0>, b:=<xmm1>
	movdqa xmm2,b
	pcmpgtb xmm2,a
	exitm<movdqa a,xmm2>
	endm
_mm_cmplt_epi16 macro a:=<xmm0>, b:=<xmm1>
	movdqa xmm2,b
	pcmpgtw xmm2,a
	exitm<movdqa a,xmm2>
	endm
_mm_cmplt_epi32 macro a:=<xmm0>, b:=<xmm1>
	movdqa xmm2,b
	pcmpgtd xmm2,a
	exitm<movdqa a,xmm2>
	endm
_mm_cvtsi32_si128 macro a
	local value
	.data
	align 16
	value dq a,0
	.code
	movdqa xmm0,xmmword ptr value
	exitm<>
	endm
_mm_cvtsi128_si32 macro a:=<xmm0>
	exitm<movd eax,a>
	endm

_mm_packs_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<packsswb a,b>
	endm
_mm_packs_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<packssdw a,b>
	endm
_mm_packus_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<packuswb a,b>
	endm
_mm_extract_epi16 macro a:=<xmm0>, imm
	exitm<pextrw eax, a, imm>
	endm
_mm_insert_epi16 macro a:=<xmm0>, reg, imm
	exitm<pinsrw a, reg, imm>
	endm

_mm_movemask_epi8 macro a:=<xmm0>
	exitm<pmovmskb eax,a>
	endm
_mm_shuffle_epi32 macro a:=<xmm0>, imm
	exitm<pshufd a, a, imm>
	endm
_mm_shufflehi_epi16 macro a:=<xmm0>, imm
	exitm<pshufhw a, a, imm>
	endm
_mm_shufflelo_epi16 macro a:=<xmm0>, imm
	exitm<pshuflw a, a, imm>
	endm
_mm_unpackhi_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpckhbw a, b>
	endm
_mm_unpackhi_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpckhwd a, b>
	endm
_mm_unpackhi_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpckhdq a, b>
	endm
_mm_unpackhi_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpckhqdq a, b>
	endm
_mm_unpacklo_epi8 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpcklbw a, b>
	endm
_mm_unpacklo_epi16 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpcklwd a, b>
	endm
_mm_unpacklo_epi32 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpckldq a, b>
	endm
_mm_unpacklo_epi64 macro a:=<xmm0>, b:=<xmm1>
	exitm<punpcklqdq a, b>
	endm

_mm_load_si128 macro reg
	exitm<movdqa xmm0,[reg]>
	endm
_mm_loadu_si128 macro reg
	exitm<movdqu xmm0,[reg]>
	endm
_mm_loadl_epi64 macro p
	exitm<movq xmm0,[reg]>
	endm

_mm_set_epi64x macro a, b
	local value
	.data
	align 16
	value dq a,b
	.code
	movdqa xmm0,xmmword ptr value
	exitm<>
	endm
_mm_set_epi32 macro a, b, c, d
	exitm<_mm_set_epi64x(a or (b shl 32), c or (d shl 32))>
	endm
_mm_set_epi16 macro a, b, c, d, e, f, g, h
	exitm<_mm_set_epi32(a or (b shl 16), c or (d shl 16), e or (f shl 16), g or (h shl 16))>
	endm
_mm_set_epi8 macro a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p
	exitm<_mm_set_epi16(a or (b shl 8), c or (d shl 8), e or (f shl 8), g or (h shl 8) \
		i or (j shl 8), k or (l shl 8), m or (n shl 8), o or (p shl 8))>
	endm
_mm_set1_epi64x macro a
	local value
	.data
	align 16
	value dq a,a
	.code
	movdqa xmm0,xmmword ptr value
	exitm<>
	endm
_mm_set1_epi32 macro a
	exitm<_mm_set1_epi64x((a) or ((a) shl 32))>
	endm
_mm_set1_epi16 macro a
	exitm<_mm_set1_epi32(a or (a shl 16))>
	endm
_mm_set1_epi8 macro a
	exitm<_mm_set1_epi16(a or (a shl 8))>
	endm

ifdef _M_X64
_mm_set1_epi64 macro a:=<xmm0>
	exitm<punpcklqdq a, a>
	endm
endif

_mm_setr_epi32 macro a, b, c, d
	exitm<_mm_set_epi64x(a or (b shl 32), c or (d shl 32))>
	endm
_mm_setr_epi16 macro a, b, c, d, e, f, g, h
	exitm<_mm_setr_epi32(a or (b shl 16), c or (d shl 16), e or (f shl 16), g or (h shl 16))>
	endm
_mm_setr_epi8 macro a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p
	exitm<_mm_setr_epi16(a or (b shl 8), c or (d shl 8), e or (f shl 8), g or (h shl 8) \
		i or (j shl 8), k or (l shl 8), m or (n shl 8), o or (p shl 8))>
	endm
_mm_setzero_si128 macro
	exitm<pxor xmm0, xmm0>
	endm

_mm_store_si128 macro reg, x:=<xmm0>
	exitm<movaps [reg], x>
	endm
_mm_storeu_si128 macro reg, x:=<xmm0>
	exitm<movups [reg], x>
	endm
_mm_storel_epi64 macro reg, x:=<xmm0>
	exitm<movq [reg], x>
	endm
_mm_maskmoveu_si128 macro a:=<xmm0>, b:=<xmm1>, reg
	exitm<maskmovdqu a,b>
	endm

_mm_move_epi64 macro a:=<xmm0>
	exitm<movq xmm0,a>
	endm

_mm_stream_pd macro reg, x:=<xmm0>
	exitm<movntpd [reg], x>
	endm
_mm_stream_si128 macro reg, x:=<xmm0>
	exitm<movntdq [reg], x>
	endm
_mm_clflush macro reg
	exitm<clflush [reg]>
	endm
_mm_lfence macro
	exitm<lfence>
	endm
_mm_mfence macro
	exitm<mfence>
	endm
_mm_stream_si32 macro r1, r2
	exitm<movnti [r1],r2>
	endm
_mm_pause macro
	exitm<nop>
	endm

_mm_cvtsd_f64 macro x:=<xmm0>
	exitm<xmm0>
	endm

_mm_castpd_ps macro x:=<xmm0>
	exitm<x>
	endm
_mm_castpd_si128 macro x:=<xmm0>
	exitm<x>
	endm
_mm_castps_pd macro x:=<xmm0>
	exitm<x>
	endm
_mm_castps_si128 macro x:=<xmm0>
	exitm<x>
	endm
_mm_castsi128_ps macro x:=<xmm0>
	exitm<x>
	endm
_mm_castsi128_pd macro x:=<xmm0>
	exitm<x>
	endm

ifdef _M_X64
_mm_cvtsd_si64 macro x:=<xmm0>
	exitm<cvtsd2si rax,x>
	endm
_mm_cvttsd_si64 macro x:=<xmm0>
	exitm<cvttsd2si rax,x>
	endm
_mm_cvtsi64_sd macro x:=<xmm0>, reg
	exitm<cvtsi2sdq x,reg>
	endm
_mm_cvtsi64_si128 macro imm
	exitm<_mm_set_epi64x(imm, 0)>
	endm

_mm_cvtsi128_si64 macro x:=<xmm0>
	exitm<movq rax,x>
	endm

endif

else

_mm_add_sd		proto :oword, :oword
_mm_add_pd		proto :oword, :oword
_mm_sub_sd		proto :oword, :oword
_mm_sub_pd		proto :oword, :oword
_mm_mul_sd		proto :oword, :oword
_mm_mul_pd		proto :oword, :oword
_mm_sqrt_sd		proto :oword, :oword
_mm_sqrt_pd		proto :oword
_mm_div_sd		proto :oword, :oword
_mm_div_pd		proto :oword, :oword

_mm_min_sd		proto :oword, :oword
_mm_min_pd		proto :oword, :oword
_mm_max_sd		proto :oword, :oword
_mm_max_pd		proto :oword, :oword

_mm_and_pd		proto :oword, :oword
_mm_andnot_pd		proto :oword, :oword
_mm_or_pd		proto :oword, :oword
_mm_xor_pd		proto :oword, :oword

_mm_cmpeq_sd		proto :oword, :oword
_mm_cmpeq_pd		proto :oword, :oword
_mm_cmplt_sd		proto :oword, :oword
_mm_cmplt_pd		proto :oword, :oword
_mm_cmple_sd		proto :oword, :oword
_mm_cmple_pd		proto :oword, :oword
_mm_cmpgt_sd		proto :oword, :oword
_mm_cmpgt_pd		proto :oword, :oword
_mm_cmpge_sd		proto :oword, :oword
_mm_cmpge_pd		proto :oword, :oword

_mm_cmpneq_sd		proto :oword, :oword
_mm_cmpneq_pd		proto :oword, :oword
_mm_cmpnlt_sd		proto :oword, :oword
_mm_cmpnlt_pd		proto :oword, :oword
_mm_cmpnle_sd		proto :oword, :oword
_mm_cmpnle_pd		proto :oword, :oword
_mm_cmpngt_sd		proto :oword, :oword
_mm_cmpngt_pd		proto :oword, :oword
_mm_cmpnge_sd		proto :oword, :oword
_mm_cmpnge_pd		proto :oword, :oword
_mm_cmpord_pd		proto :oword, :oword
_mm_cmpord_sd		proto :oword, :oword

_mm_cmpunord_pd		proto :oword, :oword
_mm_cmpunord_sd		proto :oword, :oword
_mm_comieq_sd		proto :oword, :oword
_mm_comilt_sd		proto :oword, :oword
_mm_comile_sd		proto :oword, :oword
_mm_comigt_sd		proto :oword, :oword
_mm_comige_sd		proto :oword, :oword
_mm_comineq_sd		proto :oword, :oword
_mm_ucomieq_sd		proto :oword, :oword
_mm_ucomilt_sd		proto :oword, :oword
_mm_ucomile_sd		proto :oword, :oword
_mm_ucomigt_sd		proto :oword, :oword
_mm_ucomige_sd		proto :oword, :oword
_mm_ucomineq_sd		proto :oword, :oword

_mm_cvtepi32_pd		proto :oword
_mm_cvtpd_epi32		proto :oword
_mm_cvttpd_epi32	proto :oword
_mm_cvtepi32_ps		proto :oword
_mm_cvtps_epi32		proto :oword
_mm_cvttps_epi32	proto :oword
_mm_cvtpd_ps		proto :oword
_mm_cvtps_pd		proto :oword
_mm_cvtsd_ss		proto :oword, :oword
_mm_cvtss_sd		proto :oword, :oword

_mm_cvtsd_si32		proto :oword
_mm_cvttsd_si32		proto :oword
_mm_cvtsi32_sd		proto :oword, :dword

_mm_unpackhi_pd		proto :oword, :oword
_mm_unpacklo_pd		proto :oword, :oword
_mm_movemask_pd		proto :oword
_mm_shuffle_pd		proto :oword, :oword, :dword

_mm_load_pd		proto :ptr
_mm_load1_pd		proto :ptr
_mm_loadr_pd		proto :ptr
_mm_loadu_pd		proto :ptr
_mm_load_sd		proto :ptr
_mm_loadh_pd		proto :oword, :ptr
_mm_loadl_pd		proto :oword, :ptr

_mm_set_sd		proto :real8
_mm_set1_pd		proto :real8
_mm_set_pd		proto :real8, :real8
_mm_setr_pd		proto :real8, :real8
_mm_setzero_pd		proto
_mm_move_sd		proto :oword, :oword

_mm_store_sd		proto :ptr, :oword
_mm_store1_pd		proto :ptr, :oword
_mm_store_pd		proto :ptr, :oword
_mm_storeu_pd		proto :ptr, :oword
_mm_storer_pd		proto :ptr, :oword
_mm_storeh_pd		proto :ptr, :oword
_mm_storel_pd		proto :ptr, :oword

_mm_add_epi8		proto :oword, :oword
_mm_add_epi16		proto :oword, :oword
_mm_add_epi32		proto :oword, :oword
_mm_add_epi64		proto :oword, :oword

_mm_adds_epi8		proto :oword, :oword
_mm_adds_epi16		proto :oword, :oword
_mm_adds_epu8		proto :oword, :oword
_mm_adds_epu16		proto :oword, :oword
_mm_avg_epu8		proto :oword, :oword
_mm_avg_epu16		proto :oword, :oword
_mm_madd_epi16		proto :oword, :oword
_mm_max_epi16		proto :oword, :oword
_mm_max_epu8		proto :oword, :oword
_mm_min_epi16		proto :oword, :oword
_mm_min_epu8		proto :oword, :oword
_mm_mulhi_epi16		proto :oword, :oword
_mm_mulhi_epu16		proto :oword, :oword
_mm_mullo_epi16		proto :oword, :oword

_mm_mul_epu32		proto :oword, :oword
_mm_sad_epu8		proto :oword, :oword
_mm_sub_epi8		proto :oword, :oword
_mm_sub_epi16		proto :oword, :oword
_mm_sub_epi32		proto :oword, :oword

_mm_sub_epi64		proto :oword, :oword
_mm_subs_epi8		proto :oword, :oword
_mm_subs_epi16		proto :oword, :oword
_mm_subs_epu8		proto :oword, :oword
_mm_subs_epu16		proto :oword, :oword

_mm_and_si128		proto :oword, :oword
_mm_andnot_si128	proto :oword, :oword
_mm_or_si128		proto :oword, :oword
_mm_xor_si128		proto :oword, :oword

_mm_slli_si128		proto :oword, :sdword
_mm_slli_epi16		proto :oword, :sdword
_mm_sll_epi16		proto :oword, :oword
_mm_slli_epi32		proto :oword, :sdword
_mm_sll_epi32		proto :oword, :oword
_mm_slli_epi64		proto :oword, :sdword
_mm_sll_epi64		proto :oword, :oword
_mm_srai_epi16		proto :oword, :sdword
_mm_sra_epi16		proto :oword, :oword
_mm_srai_epi32		proto :oword, :sdword
_mm_sra_epi32		proto :oword, :oword
_mm_srli_si128		proto :oword, :sdword
_mm_srli_epi16		proto :oword, :sdword
_mm_srl_epi16		proto :oword, :oword
_mm_srli_epi32		proto :oword, :sdword
_mm_srl_epi32		proto :oword, :oword
_mm_srli_epi64		proto :oword, :sdword
_mm_srl_epi64		proto :oword, :oword

_mm_cmpeq_epi8		proto :oword, :oword
_mm_cmpeq_epi16		proto :oword, :oword
_mm_cmpeq_epi32		proto :oword, :oword
_mm_cmpgt_epi8		proto :oword, :oword
_mm_cmpgt_epi16		proto :oword, :oword
_mm_cmpgt_epi32		proto :oword, :oword
_mm_cmplt_epi8		proto :oword, :oword
_mm_cmplt_epi16		proto :oword, :oword
_mm_cmplt_epi32		proto :oword, :oword

_mm_cvtsi32_si128	proto :sdword
_mm_cvtsi128_si32	proto :oword

_mm_packs_epi16		proto :oword, :oword
_mm_packs_epi32		proto :oword, :oword
_mm_packus_epi16	proto :oword, :oword
_mm_extract_epi16	proto :oword, :sdword
_mm_insert_epi16	proto :oword, :sdword, :sdword
_mm_movemask_epi8	proto :oword
_mm_shuffle_epi32	proto :oword, :sdword
_mm_shufflehi_epi16	proto :oword, :sdword
_mm_shufflelo_epi16	proto :oword, :sdword
_mm_unpackhi_epi8	proto :oword, :oword
_mm_unpackhi_epi16	proto :oword, :oword
_mm_unpackhi_epi32	proto :oword, :oword
_mm_unpackhi_epi64	proto :oword, :oword
_mm_unpacklo_epi8	proto :oword, :oword
_mm_unpacklo_epi16	proto :oword, :oword
_mm_unpacklo_epi32	proto :oword, :oword
_mm_unpacklo_epi64	proto :oword, :oword

_mm_load_si128		proto :ptr
_mm_loadu_si128		proto :ptr
_mm_loadl_epi64		proto :ptr

_mm_set_epi64x		proto :qword, :qword
_mm_set_epi32		proto :sdword, :sdword, :sdword, :sdword
_mm_set_epi16		proto :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword
_mm_set_epi8		proto :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte

_mm_set1_epi64x		proto :sqword
_mm_set1_epi32		proto :sdword
_mm_set1_epi16		proto :sword
_mm_set1_epi8		proto :sbyte
_mm_setl_epi64		proto :oword

ifdef _M_X64
_mm_set1_epi64		proto :sqword
endif

_mm_setr_epi32		proto :sdword, :sdword, :sdword, :sdword
_mm_setr_epi16		proto :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword
_mm_setr_epi8		proto :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte
_mm_setzero_si128	proto

_mm_store_si128		proto :ptr, :oword
_mm_storeu_si128	proto :ptr, :oword
_mm_storel_epi64	proto :ptr, :oword
_mm_maskmoveu_si128	proto :ptr, :oword, :ptr

_mm_move_epi64		proto :oword
ifdef _M_IX86
_mm_movpi64_epi64	proto :qword
_mm_movepi64_pi64	proto :oword
endif

_mm_stream_pd		proto :ptr, :oword
_mm_stream_si128	proto :ptr, :oword
_mm_clflush		proto :ptr
_mm_lfence		proto
_mm_mfence		proto
_mm_stream_si32		proto :ptr, :sdword
_mm_pause		proto

_mm_cvtsd_f64		proto :oword

_mm_castpd_ps		proto :oword
_mm_castpd_si128	proto :oword
_mm_castps_pd		proto :oword
_mm_castps_si128	proto :oword
_mm_castsi128_ps	proto :oword
_mm_castsi128_pd	proto :oword

ifdef _M_X64
_mm_cvtsd_si64		proto :oword
_mm_cvttsd_si64		proto :oword
_mm_cvtsi64_sd		proto :oword, :qword
_mm_cvtsi64_si128	proto :qword
_mm_cvtsi128_si64	proto :oword
endif

endif

ifdef _M_X64
_mm_stream_si64		equ <_mm_stream_si64x>
endif

ifdef _M_IX86
_mm_cvtpd_pi32		proto :oword
_mm_cvttpd_pi32		proto :oword
_mm_cvtpi32_pd		proto :qword
_mm_add_si64		proto :qword, :qword
_mm_mul_su32		proto :qword, :qword
_mm_sub_si64		proto :qword, :qword
_mm_set_epi64		proto :qword, :qword
_mm_setr_epi64		proto :sqword, :sqword
endif
endif
