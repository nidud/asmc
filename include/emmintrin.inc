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

ifdef _M_IX86
_mm_cvtpd_pi32		proto :oword
_mm_cvttpd_pi32		proto :oword
_mm_cvtpi32_pd		proto :qword
endif

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
ifdef _M_IX86
_mm_add_si64		proto :qword, :qword
endif
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
ifdef _M_IX86
_mm_mul_su32		proto :qword, :qword
endif
_mm_mul_epu32		proto :oword, :oword
_mm_sad_epu8		proto :oword, :oword
_mm_sub_epi8		proto :oword, :oword
_mm_sub_epi16		proto :oword, :oword
_mm_sub_epi32		proto :oword, :oword
ifdef _M_IX86
_mm_sub_si64		proto :qword, :qword
endif
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

ifdef _M_IX86
_mm_set_epi64		proto :qword, :qword
endif
_mm_set_epi64x		proto :qword, :qword
_mm_set_epi32		proto :sdword, :sdword, :sdword, :sdword
_mm_set_epi16		proto :sword, :sword, :sword, :sword, :sword, :sword, :sword, :sword
_mm_set_epi8		proto :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte,
			      :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte, :sbyte
ifdef _M_X64
_mm_set1_epi64		proto :sqword
endif
 _mm_set1_epi64x	proto :sqword
 _mm_set1_epi32		proto :sdword
 _mm_set1_epi16		proto :sword
 _mm_set1_epi8		proto :sbyte
 _mm_setl_epi64		proto :oword
ifdef _M_IX86
 _mm_setr_epi64		proto :sqword, :sqword
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
ifdef _M_X64
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
_mm_stream_si64		equ <_mm_stream_si64x>
endif

endif
