ifndef _INCLUDED_MM2
_INCLUDED_MM2 equ <>

ifndef _M_IX86
ifndef _M_X64
.err <This header is specific to X86 and X64 targets>
endif
endif
ifdef _M_CEE_PURE
.err <ERROR: EMM intrinsics not supported in the pure mode>
endif

ifndef _MMINTRIN_H_INCLUDED
include mmintrin.inc
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
__m128			typedef oword
endif
else ;; __ICL

__m128			union
m128_f32		real4 4 dup(?)
m128_u64		dq 2 dup(?)
m128_i8			sbyte 16 dup(?)
m128_i16		sword 8 dup(?)
m128_i32		sdword 4 dup(?)
m128_i64		sqword 2 dup(?)
m128_u8			db 16 dup(?)
m128_u16		dw 8 dup(?)
m128_u32		dd 4 dup(?)
__m128			ends

ifndef _VCRT_BUILD
ifndef _INC_MALLOC
include malloc.inc
endif
endif

endif;; __ICL

_MM_SHUFFLE macro fp3,fp2,fp1,fp0
	exitm<(((fp3) SHL 6) OR ((fp2) SHL 4) OR ((fp1) SHL 2) OR ((fp0)))>
	endm

_MM_TRANSPOSE4_PS macro row0, row1, row2, row3
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

_MM_SET_EXCEPTION_STATE macro mask
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_EXCEPT_MASK) | (mask))>
	endm

_MM_GET_EXCEPTION_STATE macro
	exitm<(_mm_getcsr() & _MM_EXCEPT_MASK)>
	endm

_MM_SET_EXCEPTION_MASK macro mask
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_MASK_MASK) | (mask))>
	endm

_MM_GET_EXCEPTION_MASK macro
	exitm<(_mm_getcsr() & _MM_MASK_MASK)>
	endm

_MM_SET_ROUNDING_MODE macro mode
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_ROUND_MASK) | (mode))>
	endm

_MM_GET_ROUNDING_MODE macro
	exitm<(_mm_getcsr() & _MM_ROUND_MASK)>
	endm

_MM_SET_FLUSH_ZERO_MODE macro mode
	exitm<_mm_setcsr((_mm_getcsr() & ~_MM_FLUSH_ZERO_MASK) | (mode))>
	endm

_MM_GET_FLUSH_ZERO_MODE macro
	exitm<(_mm_getcsr() & _MM_FLUSH_ZERO_MASK)>
	endm

ifndef _MM_NOINLINE

ifndef _MM_ISXMM

_MM_ISXMM macro op
    if (type op) eq 16 and (opattr op) eq 48
	exitm<1>
    else
	exitm<0>
    endif
	endm

_MM_MREG macro op
    if (opattr op) eq 48
	exitm<[op]>
    else
	exitm<op>
    endif
	endm

_MM_OPCSX1 macro op, sx, a
    if _MM_ISXMM(a)
	&op&&sx& a
	retm<a>
    else
	ifidni <sx>,<ps>
	    movaps xmm0,_MM_MREG(a)
	else
	    mov&sx& xmm0,_MM_MREG(a)
	endif
	&op&&sx& xmm0
	retm<xmm0>
    endif
	endm

_MM_OPCSX2 macro op, sx, a, b
    if _MM_ISXMM(a) and _MM_ISXMM(b)
	&op&&sx& a,b
	retm<a>
    elseif _MM_ISXMM(a)
	ifidni <sx>,<ps>
	    movaps xmm1,_MM_MREG(b)
	else
	    movss xmm1,_MM_MREG(b)
	endif
	&op&&sx& a,xmm1
	retm<a>
    elseif _MM_ISXMM(b)
	ifidni <sx>,<ps>
	    movaps xmm0,_MM_MREG(a)
	else
	    mov&sx& xmm0,_MM_MREG(a)
	endif
	&op&&sx& xmm0,b
	retm<xmm0>
    else
	ifidni <sx>,<ps>
	    movaps xmm0,_MM_MREG(a)
	    movaps xmm1,_MM_MREG(b)
	else
	    mov&sx& xmm0,_MM_MREG(a)
	    mov&sx& xmm1,_MM_MREG(b)
	endif
	&op&&sx& xmm0,xmm1
	retm<xmm0>
    endif
	endm

_MM_OPCSX2I macro op, sx, a, b, imm
    if _MM_ISXMM(a) and _MM_ISXMM(b)
	&op&&sx& a,b,imm
	retm<a>
    elseif _MM_ISXMM(a)
	mov&sx& xmm1,_MM_MREG(b)
	&op&&sx& a,xmm1,imm
	retm<a>
    elseif _MM_ISXMM(b)
	mov&sx& xmm0,_MM_MREG(a)
	&op&&sx& xmm0,b,imm
	retm<xmm0>
    else
	mov&sx& xmm0,_MM_MREG(a)
	mov&sx& xmm1,_MM_MREG(b)
	&op&&sx& xmm0,xmm1,imm
	retm<xmm0>
    endif
	endm

endif

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

_mm_sqrt_ss macro a:=<xmm0>
	exitm<_MM_OPCSX2(sqrt, ss, xmm0, a)>
	endm
_mm_sqrt_ps macro a:=<xmm0>
	exitm<_MM_OPCSX2(sqrt, ps, xmm0, a)>
	endm
_mm_rcp_ss macro a:=<xmm0>
	exitm<_MM_OPCSX2(rcp, ss, xmm0, a)>
	endm
_mm_rcp_ps macro a:=<xmm0>
	exitm<_MM_OPCSX2(rcp, ps, xmm0, a)>
	endm
_mm_rsqrt_ss macro a:=<xmm0>
	exitm<_MM_OPCSX2(rsqrt, ss, xmm0, a)>
	endm
_mm_rsqrt_ps macro a:=<xmm0>
	exitm<_MM_OPCSX2(rsqrt, ps, xmm0, a)>
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

_MM_CMPREV macro move, op, sx, a, b
    if _MM_ISXMM(a)
	&move&&sx& a,_MM_OPCSX2(op, sx, b, a)
	retm<a>
    else
	&move&&sx& xmm0,_MM_OPCSX2(op, sx, b, a)
	retm<xmm0>
    endif
	endm

_mm_cmpgt_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mov, cmplt, ss, a, b)>
	endm
_mm_cmpgt_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mova, cmplt, ps, a, b)>
	endm
_mm_cmpge_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mov, cmple, ss, a, b)>
	endm
_mm_cmpge_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mova, cmple, ps, a, b)>
	endm
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

_mm_cmpngt_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mov, cmpnlt, ss, a, b)>
	endm
_mm_cmpngt_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mova, cmpnlt, ps, a, b)>
	endm
_mm_cmpnge_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mov, cmpnle, ss, a, b)>
	endm
_mm_cmpnge_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_CMPREV(mova, cmpnle, ps, a, b)>
	endm
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

_mm_comiss macro set, a, b
	xor eax,eax
	_MM_OPCSX2(ucomi, ss, a, b)
	set al
	retm<eax>
	endm

_mm_comieq_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(sete, a, b)>
	endm
_mm_comilt_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setb, a, b)>
	endm
_mm_comile_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setbe, a, b)>
	endm
_mm_comigt_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(seta, a, b)>
	endm
_mm_comige_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setnb, a, b)>
	endm
_mm_comineq_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setne, a, b)>
	endm
_mm_ucomieq_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(sete, a, b)>
	endm
_mm_ucomilt_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setb, a, b)>
	endm
_mm_ucomile_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setbe, a, b)>
	endm
_mm_ucomigt_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(seta, a, b)>
	endm
_mm_ucomige_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setnb, a, b)>
	endm
_mm_ucomineq_ss macro a:=<xmm0>, b:=<xmm1>
	exitm<_mm_comiss(setne, a, b)>
	endm

_mm_cvt_ss2si macro a:=<xmm0>
	cvtss2si eax,a
	retm<eax>
	endm
_mm_cvtt_ss2si macro a:=<xmm0>
	cvttss2si eax,a
	retm<eax>
	endm
_mm_cvt_si2ss macro a:=<xmm0>, d
	mov eax,d
	cvtsi2ss a,eax
	retm<a>
	endm
_mm_cvtss_f32 macro a:=<xmm0>
	exitm<>
	endm

ifdef _M_IX86
_mm_cvt_ps2pi macro a:=<xmm0>
	endm
_mm_cvtt_ps2pi macro a:=<xmm0>
	endm
_mm_cvt_pi2ps macro a:=<xmm0>, q
	endm
endif

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

_mm_shuffle_ps macro a:=<xmm0>, b:=<xmm1>, imm
	exitm<_MM_OPCSX2I(shuf, ps, a, b, imm)>
	endm
_mm_unpackhi_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(unpckh, ps, a, b)>
	endm
_mm_unpacklo_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(unpckl, ps, a, b)>
	endm
_mm_loadh_pi macro x:=<xmm0>, p
	movhps x,_MM_MREG(p)
	retm<x>
	endm
_mm_movehl_ps macro a:=<xmm0>, b:=<xmm1>
	exitm<_MM_OPCSX2(movhl, ps, a, b)>
	endm
_mm_movelh_ps macro a:=<xmm0>, b:=<xmm1>
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


ifdef _M_IX86
_m_pextrw	proto :qword, :sdword
_m_pinsrw	proto :qword, :sdword, :sdword
_m_pmaxsw	proto :qword, :qword
_m_pmaxub	proto :qword, :qword
_m_pminsw	proto :qword, :qword
_m_pminub	proto :qword, :qword
_m_pmovmskb	proto :qword
_m_pmulhuw	proto :qword, :qword
_m_pshufw	proto :qword, :sdword
_m_maskmovq	proto :qword, :qword, :ptr
_m_pavgb	proto :qword, :qword
_m_pavgw	proto :qword, :qword
_m_psadbw	proto :qword, :qword
endif

_mm_set_ss macro x:=<xmm0>
	local val
	.data
	val real4 ?
	.code
	movss val,x
	movss x,val
	retm<x>
	endm
_mm_set_ps1 macro x:=<xmm0>
	exitm<shufps x,x,0>
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
_mm_setzero_ps macro
	exitm<pxor xmm0,xmm0>
	endm
_mm_load_ss macro p
	movss xmm0,_MM_MREG(p)
	retm<xmm0>
	endm
_mm_load_ps1 macro p
	movss xmm0,_MM_MREG(p)
	shufps xmm0,xmm0,0
	retm<xmm0>
	endm
_mm_load_ps macro p
	movaps xmm0,_MM_MREG(p)
	retm<xmm0>
	endm
_mm_loadr_ps macro p
	movaps xmm0,_MM_MREG(p)
	shufps xmm0,xmm0,27
	retm<xmm0>
	endm
_mm_loadu_ps macro p
	movups xmm0,_MM_MREG(p)
	retm<xmm0>
	endm
_mm_store_ss macro p, x:=<xmm0>
	movss _MM_MREG(p),x
	retm<p>
	endm
_mm_store_ps1 macro p, x:=<xmm0>
	shufps x,x,0
	movups _MM_MREG(p),x
	retm<p>
	endm
_mm_store_ps macro p, x:=<xmm0>
	movaps _MM_MREG(p),x
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
_mm_prefetch macro p, x:=<xmm0>
	endm
ifdef _M_IX86
_mm_stream_pi macro p, x:=<xmm0>
	endm
endif
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
_mm_getcsr macro
	sub rsp,16
	stmxcsr [rsp]
	mov eax,[rsp]
	exitm<sub rsp-16>
	endm
_mm_setcsr macro reg
	sub rsp,16
	mov [rsp],reg
	ldmxcsr [rsp]
	exitm<sub rsp-16>
	endm

else ;; _MM_NOINLINE

_mm_add_ss	proto :oword, :oword
_mm_add_ps	proto :oword, :oword
_mm_sub_ss	proto :oword, :oword
_mm_sub_ps	proto :oword, :oword
_mm_mul_ss	proto :oword, :oword
_mm_mul_ps	proto :oword, :oword
_mm_div_ss	proto :oword, :oword
_mm_div_ps	proto :oword, :oword
_mm_sqrt_ss	proto :oword
_mm_sqrt_ps	proto :oword
_mm_rcp_ss	proto :oword
_mm_rcp_ps	proto :oword
_mm_rsqrt_ss	proto :oword
_mm_rsqrt_ps	proto :oword
_mm_min_ss	proto :oword, :oword
_mm_min_ps	proto :oword, :oword
_mm_max_ss	proto :oword, :oword
_mm_max_ps	proto :oword, :oword

_mm_and_ps	proto :oword, :oword
_mm_andnot_ps	proto :oword, :oword
_mm_or_ps	proto :oword, :oword
_mm_xor_ps	proto :oword, :oword

_mm_cmpeq_ss	proto :oword, :oword
_mm_cmpeq_ps	proto :oword, :oword
_mm_cmplt_ss	proto :oword, :oword
_mm_cmplt_ps	proto :oword, :oword
_mm_cmple_ss	proto :oword, :oword
_mm_cmple_ps	proto :oword, :oword
_mm_cmpgt_ss	proto :oword, :oword
_mm_cmpgt_ps	proto :oword, :oword
_mm_cmpge_ss	proto :oword, :oword
_mm_cmpge_ps	proto :oword, :oword
_mm_cmpneq_ss	proto :oword, :oword
_mm_cmpneq_ps	proto :oword, :oword
_mm_cmpnlt_ss	proto :oword, :oword
_mm_cmpnlt_ps	proto :oword, :oword
_mm_cmpnle_ss	proto :oword, :oword
_mm_cmpnle_ps	proto :oword, :oword
_mm_cmpngt_ss	proto :oword, :oword
_mm_cmpngt_ps	proto :oword, :oword
_mm_cmpnge_ss	proto :oword, :oword
_mm_cmpnge_ps	proto :oword, :oword
_mm_cmpord_ss	proto :oword, :oword
_mm_cmpord_ps	proto :oword, :oword
_mm_cmpunord_ss proto :oword, :oword
_mm_cmpunord_ps proto :oword, :oword
_mm_comieq_ss	proto :oword, :oword
_mm_comilt_ss	proto :oword, :oword
_mm_comile_ss	proto :oword, :oword
_mm_comigt_ss	proto :oword, :oword
_mm_comige_ss	proto :oword, :oword
_mm_comineq_ss	proto :oword, :oword
_mm_ucomieq_ss	proto :oword, :oword
_mm_ucomilt_ss	proto :oword, :oword
_mm_ucomile_ss	proto :oword, :oword
_mm_ucomigt_ss	proto :oword, :oword
_mm_ucomige_ss	proto :oword, :oword
_mm_ucomineq_ss proto :oword, :oword

_mm_cvt_ss2si	proto :oword
_mm_cvtt_ss2si	proto :oword
_mm_cvt_si2ss	proto :oword, :sdword
_mm_cvtss_f32	proto :oword

ifdef _M_IX86
_mm_cvt_ps2pi	proto :oword
_mm_cvtt_ps2pi	proto :oword
_mm_cvt_pi2ps	proto :oword, :qword
endif

ifdef _M_X64
_mm_cvtss_si64	proto :oword
_mm_cvttss_si64 proto :oword
_mm_cvtsi64_ss	proto :oword, :qword
endif

_mm_shuffle_ps	proto :oword, :oword, :sdword
_mm_unpackhi_ps proto :oword, :oword
_mm_unpacklo_ps proto :oword, :oword
_mm_loadh_pi	proto :oword, :ptr
_mm_movehl_ps	proto :oword, :oword
_mm_movelh_ps	proto :oword, :oword
_mm_storeh_pi	proto :ptr, :oword
_mm_loadl_pi	proto :oword, :ptr
_mm_storel_pi	proto :ptr, :oword
_mm_movemask_ps proto :oword


ifdef _M_IX86
_m_pextrw	proto :qword, :sdword
_m_pinsrw	proto :qword, :sdword, :sdword
_m_pmaxsw	proto :qword, :qword
_m_pmaxub	proto :qword, :qword
_m_pminsw	proto :qword, :qword
_m_pminub	proto :qword, :qword
_m_pmovmskb	proto :qword
_m_pmulhuw	proto :qword, :qword
_m_pshufw	proto :qword, :sdword
_m_maskmovq	proto :qword, :qword, :ptr
_m_pavgb	proto :qword, :qword
_m_pavgw	proto :qword, :qword
_m_psadbw	proto :qword, :qword
endif

_mm_set_ss	proto :real4
_mm_set_ps1	proto :real4
_mm_set_ps	proto :real4, :real4, :real4, :real4
_mm_setr_ps	proto :real4, :real4, :real4, :real4
_mm_setzero_ps	proto
_mm_load_ss	proto :ptr
_mm_load_ps1	proto :ptr
_mm_load_ps	proto :ptr
_mm_loadr_ps	proto :ptr
_mm_loadu_ps	proto :ptr
_mm_store_ss	proto :ptr, :oword
_mm_store_ps1	proto :ptr, :oword
_mm_store_ps	proto :ptr, :oword
_mm_storer_ps	proto :ptr, :oword
_mm_storeu_ps	proto :ptr, :oword
_mm_prefetch	proto :ptr, :sdword
ifdef _M_IX86
_mm_stream_pi	proto :ptr, :qword
endif
_mm_stream_ps	proto :ptr, :oword
_mm_move_ss	proto :oword, :oword

_mm_sfence	proto
_mm_getcsr	proto
_mm_setcsr	proto :sdword

endif ;;  _MM_NOINLINE

ifdef __ICL
_mm_malloc	proto __cdecl :size_t, :size_t
_mm_free	proto __cdecl :ptr
endif

ifdef _M_IX86
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
endif
_mm_cvtss_si32		equ <_mm_cvt_ss2si>
_mm_cvttss_si32		equ <_mm_cvtt_ss2si>
_mm_cvtsi32_ss		equ <_mm_cvt_si2ss>
_mm_set1_ps		equ <_mm_set_ps1>
_mm_load1_ps		equ <_mm_load_ps1>
_mm_store1_ps		equ <_mm_store_ps1>

ifdef _M_IX86
_mm_cvtpi16_ps macro a:=<xmm0>
	endm
_mm_cvtpu16_ps macro a:=<xmm0>
	endm
_mm_cvtps_pi16 macro a:=<xmm0>
	endm
_mm_cvtpi8_ps macro a:=<xmm0>
	endm
_mm_cvtpu8_ps macro a:=<xmm0>
	endm
_mm_cvtps_pi8 macro a:=<xmm0>
	endm
_mm_cvtpi32x2_ps macro a:=<xmm0>, b:=<xmm1>
	cvtpi2ps xmm2,b
	cvtpi2ps xmm0,a
	exitm<movlhps xmm0,xmm2>
	endm
endif

endif
