; ZMMINTRIN.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _ZMMINTRIN_H_INCLUDED
define _ZMMINTRIN_H_INCLUDED

ifndef _INCLUDED_IMM
.err <Header should only be included from immintrin.h>
endif

__mmask8                typedef byte
__mmask16               typedef word
__mmask32               typedef dword
__mmask64               typedef qword

__m512                  union
m512_f32                real4 16 dup(?)
__m512                  ENDS

__m512d                 STRUC
m512d_f64               real8 8 dup(?)
__m512d                 ENDS

__m512i                 union
m512i_i8                sbyte 64 dup(?)
m512i_i16               sword 32 dup(?)
m512i_i32               sdword 16 dup(?)
m512i_i64               sqword 8 dup(?)
m512i_u8                db 64 dup(?)
m512i_u16               dw 32 dup(?)
m512i_u32               dd 16 dup(?)
m512i_u64               dq 8 dup(?)
__m512i                 ENDS


_mm512_castps512_ps256 macro zmm
    exitm<@CatStr(<ymm>,@SubStr(zmm,4))>
    endm

_mm512_castpd_ps macro zmm
    exitm<zmm>
    endm
_mm512_castps256_ps512 macro ymm
    exitm<@CatStr(<zmm>,@SubStr(ymm,4))>
    endm
_mm512_castsi512_ps macro zmm
    exitm<zmm>
    endm
_mm512_castps128_ps512 macro xmm
    exitm<@CatStr(<zmm>,@SubStr(xmm,4))>
    endm

_mm512_castpd512_pd256 macro zmm
    exitm<@CatStr(<ymm>,@SubStr(zmm,4))>
    endm
_mm512_castpd256_pd512 macro ymm
    exitm<@CatStr(<zmm>,@SubStr(ymm,4))>
    endm
_mm512_castps_pd macro zmm
    exitm<zmm>
    endm
_mm512_castsi512_pd macro zmm
    exitm<zmm>
    endm
_mm512_castpd128_pd512 macro xmm
    exitm<@CatStr(<zmm>,@SubStr(xmm,4))>
    endm

_mm512_castsi512_si256 macro zmm
    exitm<@CatStr(<ymm>,@SubStr(zmm,4))>
    endm
_mm512_castpd_si512 macro zmm
    exitm<zmm>
    endm
_mm512_castps_si512 macro zmm
    exitm<zmm>
    endm
_mm512_castsi256_si512 macro ymm
    exitm<@CatStr(<zmm>,@SubStr(ymm,4))>
    endm

_MM_K0_REG              equ 0xffff
_MM_K0_REG64            equ 0xffffffffffffffff

_MM_BROADCAST32_NONE    equ 0
_MM_BROADCAST_16X16     equ _MM_BROADCAST32_NONE
_MM_BROADCAST_1X16      equ 1
_MM_BROADCAST_4X16      equ 2

_MM_BROADCAST64_NONE    equ 0
_MM_BROADCAST_8X8       equ _MM_BROADCAST64_NONE
_MM_BROADCAST_1X8       equ 1
_MM_BROADCAST_4X8       equ 2

_MM_ROUND_MODE_NEAREST  equ 0
_MM_ROUND_MODE_DOWN     equ 1
_MM_ROUND_MODE_UP       equ 2
_MM_ROUND_MODE_TOWARD_ZERO equ 3
_MM_ROUND_MODE_DEFAULT  equ 4

_MM_EXPADJ_NONE         equ 0
_MM_EXPADJ_4            equ 1
_MM_EXPADJ_5            equ 2
_MM_EXPADJ_8            equ 3
_MM_EXPADJ_16           equ 4
_MM_EXPADJ_24           equ 5
_MM_EXPADJ_31           equ 6
_MM_EXPADJ_32           equ 7

_MM_SCALE_1             equ 1
_MM_SCALE_2             equ 2
_MM_SCALE_4             equ 4
_MM_SCALE_8             equ 8

_MM_FIXUP_NO_CHANGE     equ 0
_MM_FIXUP_NEG_INF       equ 1
_MM_FIXUP_NEG_ZERO      equ 2
_MM_FIXUP_POS_ZERO      equ 3
_MM_FIXUP_POS_INF       equ 4
_MM_FIXUP_NAN           equ 5
_MM_FIXUP_MAX_FLOAT     equ 6
_MM_FIXUP_MIN_FLOAT     equ 7

_MM_FIXUP macro _NegInf, _Neg, _NegZero, _PosZero, _Pos, _PosInf, _Nan
    exitm<((_NegInf) or \
          ((_Neg) shl 3) or \
          ((_NegZero) shl 6) or \
          ((_PosZero) shl 9) or \
          ((_Pos) shl 12) or \
          ((_PosInf) shl 15) or \
          ((_Nan) shl 18))>
    endm

_MM_MANT_NORM_1_2       equ 0
_MM_MANT_NORM_p5_2      equ 1
_MM_MANT_NORM_p5_1      equ 2
_MM_MANT_NORM_p75_1p5   equ 3

_MM_MANT_SIGN_src       equ 0
_MM_MANT_SIGN_zero      equ 1
_MM_MANT_SIGN_nan       equ 2

_MM_CMPINT_EQ           equ 0
_MM_CMPINT_LT           equ 1
_MM_CMPINT_LE           equ 2
_MM_CMPINT_UNUSED       equ 3
_MM_CMPINT_NE           equ 4
_MM_CMPINT_NLT          equ 5
_MM_CMPINT_GE           equ _MM_CMPINT_NLT
_MM_CMPINT_NLE          equ 6
_MM_CMPINT_GT           equ _MM_CMPINT_NLE


_mm512_setzero_ps macro xmm:=<xmm0>
    vxorps xmm,xmm,xmm
    retm<@CatStr(<zmm>,@SubStr(xmm,4))>
    endm
_mm512_setzero_pd macro xmm:=<xmm0>
    vxorpd xmm,xmm,xmm
    retm<@CatStr(<zmm>,@SubStr(xmm,4))>
    endm

_mm512_set_ps macro args:vararg
    exitm<_MM_SET(args)>
    endm
_mm512_set_pd macro args:vararg
    exitm<_MM_SET(args)>
    endm
_mm512_setr_ps macro args:vararg
    exitm<{ args }>
    endm
_mm512_setr_pd macro args:vararg
    exitm<{ args }>
    endm

_mm512_set1_ps macro src, dst:=<zmm0>
    vbroadcastss dst,src
    retm<dst>
    endm
_mm512_set1_pd macro src, dst:=<zmm0>
    vbroadcastsd dst,src
    retm<dst>
    endm

; Load a pointers and mask registers
_mm512_loadp proto asmcall :ptr {}   ; rax | eax
_mm512_loadq proto asmcall :qword {} ; rax | edx:eax

.pragma aux(k1, k2)

; Reversed order of operand size (b <> q)
_mm512_load_kb proto asmcall :byte {}
_mm512_load_kw proto asmcall :word {}
_mm512_load_kd proto asmcall :dword {}
_mm512_load_kq proto asmcall :qword {}

_mm512_load_k2b proto asmcall :byte, :byte {}
_mm512_load_k2w proto asmcall :word, :word {}
_mm512_load_k2d proto asmcall :dword, :dword {}
_mm512_load_k2q proto asmcall :qword, :qword {}

.pragma aux(pop)

; Set modifiers [{k1}[{z}]] and load mask (k1)
; Skip if _MM_K0_REG[64] is used
_mm512_loadk macro mk, kz, cm, m
if @InStr(1, m, <_MM_K0_>)
    mk textequ <>
else
    @CatStr(<_mm512_load_k>, @SubStr(<qdwb>, cm, 1))(m)
    mk textequ @SubStr(<{k1}{z}>, 1, 4 + kz * 3)
endif
    endm

_mm512_mask_load macro cm, kz, m, p, v1
  local mask
    _mm512_loadk mask, kz, cm, m
    _mm512_loadp(p)
    vmovups v1 mask,[rax]
    retm<v1>
    endm
_mm512_mask_load_ps macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(2, 0, m, p, v1)>
    endm
_mm512_maskz_load_ps macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(2, 1, m, p, v1)>
    endm
_mm512_mask_load_pd macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(1, 0, m, p, v1)>
    endm
_mm512_maskz_load_pd macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(1, 1, m, p, v1)>
    endm
_mm512_mask_loadu_ps macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(2, 0, m, p, v1)>
    endm
_mm512_maskz_loadu_ps macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(2, 1, m, p, v1)>
    endm
_mm512_mask_loadu_pd macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(1, 0, m, p, v1)>
    endm
_mm512_maskz_loadu_pd macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load(1, 1, m, p, v1)>
    endm

_mm512_mask_store macro cm, m, p, v1
  local mask
    _mm512_loadk mask, 0, cm, m
    _mm512_loadp(p)
    vmovups [rax] mask,v1
    retm<v1>
    endm
_mm512_mask_store_ps macro p, m, v1
    exitm<_mm512_mask_store(2, m, p, v1)>
    endm
_mm512_mask_store_pd macro p, m, v1
    exitm<_mm512_mask_store(1, m, p, v1)>
    endm
_mm512_mask_storeu_ps macro p, m, v1
    exitm<_mm512_mask_store(2, m, p, v1)>
    endm
_mm512_mask_storeu_pd macro p, m, v1
    exitm<_mm512_mask_store(1, m, p, v1)>
    endm
_mm512_storeu_ps macro p, v1
    exitm<_mm512_mask_store(2, _MM_K0_REG, p, v1)>
    endm
_mm512_storeu_pd macro p, v1
    exitm<_mm512_mask_store(1, _MM_K0_REG, p, v1)>
    endm

; Base types: <2|3>+round, <2|3>+imm, 2+imm+round

_mm512_mask2_round macro kz, inst, cm, m, v1, v2, e3:=<_MM_ROUND_MODE_DEFAULT>
  local mask
    _mm512_loadk mask, kz, cm, m
ifb <v2>
    inst v1 mask, v1 _MM_SAE(e3)
else
    inst v1 mask, v2 _MM_SAE(e3)
endif
    retm <v1>
    endm
_mm512_mask3_round macro kz, inst, cm, m, v1, v2, v3, e4:=<_MM_ROUND_MODE_DEFAULT>
  local mask
    _mm512_loadk mask, kz, cm, m
ifb <v3>
    inst v1 mask, v1, v2 _MM_SAE(e4)
else
    inst v1 mask, v2, v3 _MM_SAE(e4)
endif
    retm <v1>
    endm
_mm512_mask2_imm macro kz, inst, cm, m, v1, v2, i3, e4:=<_MM_ROUND_MODE_DEFAULT>
  local mask
    _mm512_loadk mask, kz, cm, m
ifb <v2>
    inst v1 mask, v1, i3 _MM_SAE(e4)
else
    inst v1 mask, v2, i3 _MM_SAE(e4)
endif
    retm <v1>
    endm
_mm512_mask3_imm macro kz, inst, cm, m, v1, v2, v3, i4
  local mask
    _mm512_loadk mask, kz, cm, m
    inst v1 mask, v2, v3, i4
    retm <v1>
    endm

; Intrinsic entries
_mm512_mask macro inst, cm, v1, m, v2, v3, e4
    exitm<_mm512_mask3_round(0, inst, cm, m, v1, v2, v3, e4)>
    endm
_mm512_maskz macro inst, cm, m, v1, v2, e4
    exitm<_mm512_mask3_round(1, inst, cm, m, v1, v2, , e4)>
    endm
_mm512_mask3 macro inst, cm, v1, v2, v3, m, e4
    exitm<_mm512_mask3_round(0, inst, cm, m, v3, v1, v2, e4)>
    endm
_mm512_maskz3 macro inst, cm, m, v1, v2, v3, e4
    exitm<_mm512_mask3_round(1, inst, cm, m, v1, v3, v2, e4)>
    endm
_mm512_mask2 macro inst, cm, v1, m, v2, e4
    exitm<_mm512_mask2_round(0, inst, cm, m, v1, v2, e4)>
    endm
_mm512_maskz2 macro inst, cm, m, v1, v2, e3
    exitm<_mm512_mask2_round(1, inst, cm, m, v1, v2, e3)>
    endm
_mm512_mask2i macro inst, cm, v1, m, v2, i3, e4
    exitm<_mm512_mask2_imm(0, inst, cm, m, v1, v2, i3, e4)>
    endm
_mm512_maskz2i macro inst, cm, m, v2, i3, v1:=<zmm0>
    exitm<_mm512_mask2_imm(1, inst, cm, m, v1, v2, i3)>
    endm
_mm512_maskz2ir macro inst, cm, m, v1, i3, e4
    exitm<_mm512_mask2_imm(1, inst, cm, m, v1, , i3, e4)>
    endm
_mm512_mask3i macro inst, cm, v1, m, v2, v3, i4
    exitm<_mm512_mask3_imm(0, inst, cm, m, v1, v2, v3, i4)>
    endm
_mm512_maskz3i macro inst, cm, m, v2, v3, i4, v1:=<zmm0>
    exitm<_mm512_mask3_imm(1, inst, cm, m, v1, v2, v3, i4)>
    endm

; Macro slop..

for cm,<add,sub,mul,div,max,min>
    _mm512_maskz_&cm&_round_ps macro args:vararg
        exitm<_mm512_maskz(v&cm&ps, 2, args)>
        endm
    _mm512_maskz_&cm&_round_pd macro args:vararg
        exitm<_mm512_maskz(v&cm&pd, 1, args)>
        endm
    _mm512_mask_&cm&_round_ps macro args:vararg
        exitm<_mm512_mask(v&cm&ps, 2, args)>
        endm
    _mm512_mask_&cm&_round_pd macro args:vararg
        exitm<_mm512_mask(v&cm&pd, 1, args)>
        endm
    endm

for cm,<madd,msub,maddsub,msubadd,nmadd,nmsub>
    _mm512_mask_f&cm&_round_ps macro args:vararg
        exitm<_mm512_mask(vf&cm&213ps, 2, args)>
        endm
    _mm512_mask3_f&cm&_round_ps macro args:vararg
        exitm<_mm512_mask3(vf&cm&213ps, 2, args)>
        endm
    _mm512_maskz_f&cm&_round_ps macro args:vararg
        exitm<_mm512_maskz3(vf&cm&213ps, 2, args)>
        endm
    _mm512_mask_f&cm&_round_pd macro args:vararg
        exitm<_mm512_mask(vf&cm&213pd, 1, args)>
        endm
    _mm512_mask3_f&cm&_round_pd macro args:vararg
        exitm<_mm512_mask3(vf&cm&213pd, 1, args)>
        endm
    _mm512_maskz_f&cm&_round_pd macro args:vararg
        exitm<_mm512_maskz3(vf&cm&213pd, 1, args)>
        endm
    endm


_mm512_maskz_sqrt_round_ps macro m, v1, e1
    exitm<_mm512_maskz2(vsqrtps, 2, m, v1, , e1)>
    endm
_mm512_maskz_sqrt_round_pd macro m, v1, e1
    exitm<_mm512_maskz2(vsqrtpd, 1, m, v1, , e1)>
    endm
_mm512_mask_sqrt_round_ps macro v1, m, v2, e1
    exitm<_mm512_mask2(vsqrtps, 2, v1, m, v2, e1)>
    endm
_mm512_mask_sqrt_round_pd macro v1, m, v2, e1
    exitm<_mm512_mask2(vsqrtpd, 1, v1, m, v2, e1)>
    endm


for cm,<rcp14,rsqrt14>
    _mm512_maskz_&cm&_ps macro m, v1, v2
        exitm<_mm512_maskz2(v&cm&ps, 2, m, v1, v2)>
        endm
    _mm512_maskz_&cm&_pd macro m, v1, v2
        exitm<_mm512_maskz2(v&cm&pd, 1, m, v1, v2)>
        endm
    _mm512_mask_&cm&_ps macro v1, m, v2
        exitm<_mm512_mask2(v&cm&ps, 2, v1, m, v2)>
        endm
    _mm512_mask_&cm&_pd macro v1, m, v2
        exitm<_mm512_mask2(v&cm&pd, 1, v1, m, v2)>
        endm
    endm

; Xeon Phi Instructions

for cm,<rcp28,rsqrt28>
    _mm512_mask_&cm&_round_ps macro v1, m, v2, e1
        exitm<_mm512_mask2(v&cm&ps, 2, v1, m, v2, e1)>
        endm
    _mm512_maskz_&cm&_round_ps macro m, v1, e1
        exitm<_mm512_maskz2(v&cm&ps, 2, m, v1, , e1)>
        endm
    _mm512_mask_&cm&_round_pd macro v1, m, v2, e1
        exitm<_mm512_mask2(v&cm&pd, 1, v1, m, v2, e1)>
        endm
    _mm512_maskz_&cm&_round_pd macro m, v1, e1
        exitm<_mm512_maskz2(v&cm&pd, 1, m, v1, , e1)>
        endm
    endm


_mm512_maskz_cvt_roundps_pd macro m, v1, e2
    exitm<_mm512_maskz2(vcvtps2pd, 1, m, @CatStr(<zmm>,@SubStr(v1,4)), v1, e2)>
    endm
_mm512_maskz_cvt_roundpd_ps macro m, v1, e2
    exitm<_mm512_maskz2(vcvtpd2ps, 2, m, @CatStr(<ymm>,@SubStr(v1,4)), v1, e2)>
    endm
_mm512_mask_cvt_roundps_pd macro v1, m, v2, e2
    exitm<_mm512_mask2(vcvtps2pd, 1, v1, m, v2, e2)>
    endm
_mm512_mask_cvt_roundpd_ps macro v1, m, v2, e2
    exitm<_mm512_mask2(vcvtpd2ps, 2, v1, m, v2, e2)>
    endm

for cm,<2,4,8>
    _mm512_mask_broadcast_f32x&cm& macro v1, m, v2
        exitm<_mm512_mask2(vbroadcastf32x&cm&, 2, v1, m, v2)>
        endm
    _mm512_maskz_broadcast_f32x&cm& macro m, v2, v1:=<zmm0>
        exitm<_mm512_maskz2(vbroadcastf32x&cm&, 2, m, v1, v2)>
        endm
  if cm le 4
    _mm512_mask_broadcast_f64x&cm& macro v1, m, v2
        exitm<_mm512_mask2(vbroadcastf64x&cm&, 1, v1, m, v2)>
        endm
    _mm512_maskz_broadcast_f64x&cm& macro m, v2, v1:=<zmm0>
        exitm<_mm512_maskz2(vbroadcastf64x&cm&, 1, m, v1, v2)>
        endm
  endif
    endm
_mm512_mask_broadcastss_ps macro v1, m, v2
    exitm<_mm512_mask2(vbroadcastss, 2, v1, m, v2)>
    endm
_mm512_mask_broadcastsd_pd macro v1, m, v2
    exitm<_mm512_mask2(vbroadcastsd, 1, v1, m, v2)>
    endm
_mm512_maskz_broadcastss_ps macro m, v2, v1:=<zmm0>
    exitm<_mm512_maskz2(vbroadcastss, 2, m, v1, v2)>
    endm
_mm512_maskz_broadcastsd_pd macro m, v2, v1:=<zmm0>
    exitm<_mm512_maskz2(vbroadcastsd, 1, m, v1, v2)>
    endm

for cm,<4,8>
    _mm512_mask_extractf32x&cm&_ps macro v1, m, v2, e2
        exitm<_mm512_mask3(vextractf32x&cm&, 1, v2, e2, v1, m)>
        endm
    endm
_mm512_maskz_extractf32x4_ps macro m, v1, e2
    exitm<_mm512_maskz3(vextractf32x4, 1, m, xmm0, e2, v1)>
    endm
_mm512_maskz_extractf32x8_ps macro m, v1, e2
    exitm<_mm512_maskz3(vextractf32x8, 1, m, ymm0, e2, v1)>
    endm
for cm,<2,4>
    _mm512_mask_extractf64x&cm&_pd macro v1, m, v2, e2
        exitm<_mm512_mask3(vextractf64x&cm&, 1, v2, e2, v1, m)>
        endm
    endm
_mm512_maskz_extractf64x2_pd macro m, v1, e2
    exitm<_mm512_maskz3(vextractf64x2, 1, m, xmm0, e2, v1)>
    endm
_mm512_maskz_extractf64x4_pd macro m, v1, e2
    exitm<_mm512_maskz3(vextractf64x4, 1, m, ymm0, e2, v1)>
    endm

for cm,<32x4,32x8,64x2,64x4>
    _mm512_mask_insertf&cm& macro v1, m, v2, v3, i4
        exitm<_mm512_mask3i(vinsertf&cm&, 2, v1, m, v2, v3, i4)>
        endm
    _mm512_maskz_insertf&cm& macro m, v2, v3, i4, v1:=<zmm0>
        exitm<_mm512_maskz3i(vinsertf&cm&, 2, m, v2, v3, i4, v1)>
        endm
    endm

_mm512_mask_shuffle_f32x4 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vshuff32x4, 2, v1, m, v2, v3, i4)>
    endm
_mm512_mask_shuffle_f64x2 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vshuff64x2, 1, v1, m, v2, v3, i4)>
    endm
_mm512_mask_shuffle_pd macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vshufpd, 1, v1, m, v2, v3, i4)>
    endm
_mm512_mask_shuffle_ps macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vshufps, 2, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_shuffle_f32x4 macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vshuff32x4, 2, m, v2, v3, i4, v2)>
    endm
_mm512_maskz_shuffle_f64x2 macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vshuff64x2, 1, m, v2, v3, i4, v2)>
    endm
_mm512_maskz_shuffle_pd macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vshufpd, 1, m, v2, v3, i4, v2)>
    endm
_mm512_maskz_shuffle_ps macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vshufps, 2, m, v2, v3, i4, v2)>
    endm


_mm512_setzero macro
        exitm<_mm512_setzero_ps()>
        endm
_mm512_undefined macro
        exitm<_mm512_setzero()>
        endm
_mm512_undefined_pd macro
        exitm<_mm512_setzero_pd()>
        endm
_mm512_undefined_ps macro
        exitm<_mm512_undefined()>
        endm

_mm512_set4_pd macro args:vararg
        exitm<_mm512_set_pd(args, args)>
        endm

_mm512_set4_ps macro args:vararg
        exitm<_mm512_set_ps(args, args, args, args)>
        endm

_mm512_setr_ps macro args:vararg
        exitm<{ args }>
        endm
_mm512_set_16to16_ps macro args:vararg
        exitm<_mm512_set_ps(args)>
        endm

_mm512_setr_pd macro args:vararg
        exitm<{ args }>
        endm

_mm512_set_8to8_pd macro args:vararg
        exitm<_mm512_set_pd(args)>
        endm

_mm512_setr4_ps macro args:vararg
        exitm<_mm512_set_ps(args, args, args, args)>
        endm

_mm512_set_4to16_ps macro a,b,q,d
        exitm<_mm512_set4_ps(d, q, b, a)>
        endm

_mm512_setr4_pd macro a,b,q,d
        exitm<_mm512_set4_pd(d, q, b, a)>
        endm


_mm512_set_4to8_pd macro a,b,q,d
        exitm<_mm512_set4_pd(d, q, b, a)>
        endm

_mm512_set_1to16_ps macro x
        exitm<_mm512_set1_ps(x)>
        endm
_mm512_set_1to8_pd macro x
        exitm<_mm512_set1_pd(x)>
        endm

_mm512_load_ps macro x
        exitm<_mm512_maskz_load_ps(_MM_K0_REG, x)>
        endm
_mm512_load_pd macro x
        exitm<_mm512_maskz_load_pd(_MM_K0_REG, x)>
        endm
_mm512_loadu_ps macro x
        exitm<_mm512_maskz_loadu_ps(_MM_K0_REG, x)>
        endm
_mm512_loadu_pd macro x
        exitm<_mm512_maskz_loadu_pd(_MM_K0_REG, x)>
        endm

_mm512_store_ps macro x, v
        exitm<_mm512_mask_store_ps(x, _MM_K0_REG, v)>
        endm
_mm512_store_pd macro x, v
        exitm<_mm512_mask_store_pd(x, _MM_K0_REG, v)>
        endm

_mm512_mov_ps macro x, v:=<zmm0>
ifdif <x>,<v>
    vmovaps x,v
endif
    retm<x>
    endm
_mm512_mov_pd macro x, v:=<zmm0>
ifdif <x>,<v>
    vmovapd x,v
endif
    retm<x>
    endm

_mm512_add_ps macro v1, v2
        exitm<_mm512_maskz_add_round_ps(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_add_round_ps macro v1, v2, e3
        exitm<_mm512_maskz_add_round_ps(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_maskz_add_ps macro _k1, v2, v3
        exitm<_mm512_maskz_add_round_ps(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_add_ps macro v1, _k2, v3, v4
        exitm<_mm512_mask_add_round_ps(v1, _k2, v3, v4, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_add_pd macro v1, v2
        exitm<_mm512_maskz_add_round_pd(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_add_round_pd macro v1, v2, e3
        exitm<_mm512_maskz_add_round_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_maskz_add_pd macro _k1, v2, v3
        exitm<_mm512_maskz_add_round_pd(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_add_pd macro v1, _k2, v3, v4
        exitm<_mm512_mask_add_round_pd(v1, _k2, v3, v4, _MM_FROUND_CUR_DIRECTION)>
        endm


_mm512_sub_ps macro v1, v2
        exitm<_mm512_maskz_sub_round_ps(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_sub_round_ps macro v1, v2, e3
        exitm<>
        endm

_mm512_maskz_sub_ps macro _k1, v2, v3
        exitm<_mm512_maskz_sub_round_ps(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_sub_ps macro v1, _k2, v3, v4
        exitm<_mm512_mask_sub_round_ps(v1, _k2, v3, v4, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_sub_pd macro v1, v2
        exitm<_mm512_maskz_sub_round_pd(_MM_K0_REG,v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_sub_round_pd macro v1, v2, e3
        exitm<_mm512_maskz_sub_round_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_maskz_sub_pd macro _k1, v2, v3
        exitm<_mm512_maskz_sub_round_pd(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_sub_pd macro v1, _k2, v3, v4
        exitm<_mm512_mask_sub_round_pd(v1, _k2, v3, v4, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mul_ps macro v1, v2
        exitm<_mm512_maskz_mul_round_ps(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mul_round_ps macro v1, v2, e3
        exitm<_mm512_maskz_mul_round_ps(_MM_K0_REG,v1, v2, e3)>
        endm

_mm512_maskz_mul_ps macro _k1, v2, v3
        exitm<_mm512_maskz_mul_round_ps(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_mul_ps macro v1, _k2, v3, v4
        exitm<_mm512_mask_mul_round_ps(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mul_pd macro v1, v2
        exitm<_mm512_maskz_mul_round_pd(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mul_round_pd macro v1, v2, e3
        exitm<_mm512_maskz_mul_round_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_maskz_mul_pd macro _k1, v2, v3
        exitm<_mm512_maskz_mul_round_pd(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_mul_pd macro v1, _k2, v3, v4
        exitm<_mm512_mask_mul_round_pd(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_div_ps macro v1, v2
        exitm<_mm512_maskz_div_round_ps(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_div_round_ps macro v1, v2, e3
        exitm<_mm512_maskz_div_round_ps(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_maskz_div_ps macro _k1, v2, v3
        exitm<_mm512_maskz_div_round_ps(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_div_ps macro v1, _k2, v3, v4
        exitm<_mm512_mask_div_round_ps(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_div_pd macro v1, v2
        exitm<_mm512_maskz_div_round_pd(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_div_round_pd macro v1, v2, e3
        exitm<_mm512_maskz_div_round_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_maskz_div_pd macro _k1, v2, v3
        exitm<_mm512_maskz_div_round_pd(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_div_pd macro v1, _k2, v3, v4
        exitm<_mm512_mask_div_round_pd(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fmadd_round_ps macro v1, v2, v3, e4
        exitm<_mm512_maskz_fmadd_round_ps(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fmadd_ps macro v1, v2, v3
        exitm<_mm512_fmadd_round_ps(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fmadd_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmadd_round_ps(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fmadd_ps macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmadd_round_ps(_k1, v1, v2, v3)>
        endm

_mm512_fmadd_round_pd macro v1, v2, v3, e4
        exitm<_mm512_maskz_fmadd_round_pd(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fmadd_pd macro v1, v2, v3
        exitm<_mm512_fmadd_round_pd(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fmadd_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmadd_round_pd(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fmadd_pd macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmadd_round_pd(_k1, v1, v2, v3)>
        endm

_mm512_fmsub_round_ps macro v1, v2, v3, e4
        exitm<_mm512_maskz_fmsub_round_ps(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fmsub_ps macro v1, v2, v3
        exitm<_mm512_fmsub_round_ps(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fmsub_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmsub_round_ps(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fmsub_ps macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmsub_round_ps(_k1, v1, v2, v3)>
        endm

_mm512_fmsub_round_pd macro v1, v2, v3, e4
        exitm<_mm512_maskz_fmsub_round_pd(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fmsub_pd macro v1, v2, v3
        exitm<_mm512_fmsub_round_pd(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fmsub_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmsub_round_pd(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fmsub_pd macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmsub_round_pd(_k1, v1, v2, v3)>
        endm

_mm512_fnmadd_round_ps macro v1, v2, v3, e4
        exitm<_mm512_maskz_fnmadd_round_ps(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fnmadd_ps macro v1, v2, v3
        exitm<_mm512_fnmadd_round_ps(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fnmadd_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_fnmadd_round_ps(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fnmadd_ps macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fnmadd_round_ps(_k1, v1, v2, v3)>
        endm

_mm512_fnmadd_round_pd macro v1, v2, v3, e4
        exitm<_mm512_maskz_fnmadd_round_pd(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fnmadd_pd macro v1, v2, v3
        exitm<_mm512_fnmadd_round_pd(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fnmadd_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_fnmadd_round_pd(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fnmadd_pd macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fnmadd_round_pd(_k1, v1, v2, v3)>
        endm


_mm512_fnmsub_round_ps macro v1, v2, v3, e4
        exitm<_mm512_maskz_fnmsub_round_ps(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fnmsub_ps macro v1, v2, v3
        exitm<_mm512_fnmsub_round_ps(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fnmsub_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_fnmsub_round_ps(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fnmsub_ps macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fnmsub_round_ps(_k1, v1, v2, v3)>
        endm

_mm512_fnmsub_round_pd macro v1, v2, v3, e4
        exitm<_mm512_maskz_fnmsub_round_pd(_MM_K0_REG, v1, v2, v3, e4)>
        endm

_mm512_fnmsub_pd macro v1, v2, v3
        exitm<_mm512_fnmsub_round_pd(v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fnmsub_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_fnmsub_round_pd(v1, _k1, v2, v3)>
        endm

_mm512_maskz_fnmsub_pd macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fnmsub_round_pd(_k1, v1, v2, v3)>
        endm

_mm512_sqrt_ps macro v1
        exitm<_mm512_maskz_sqrt_round_ps(_MM_K0_REG, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_sqrt_round_ps macro v1, e2
        exitm<_mm512_maskz_sqrt_round_ps(_MM_K0_REG, v1, e2)>
        endm

_mm512_mask_sqrt_ps macro v1, _k2, v2
        exitm<_mm512_mask_sqrt_round_ps(v1, _k2, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_sqrt_ps macro _k1, v1
        exitm<_mm512_maskz_sqrt_round_ps(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_sqrt_pd macro v1
        exitm<_mm512_maskz_sqrt_round_pd(_MM_K0_REG, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_sqrt_round_pd macro v1, e2
        exitm<_mm512_maskz_sqrt_round_pd(_MM_K0_REG, v1, e2)>
        endm

_mm512_mask_sqrt_pd macro v1, _k2, v2
        exitm<_mm512_mask_sqrt_round_pd(v1, _k2, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_sqrt_pd macro _k1, v1
        exitm<_mm512_maskz_sqrt_round_pd(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_abs_ps macro m, v1
    exitm<_mm512_maskz(vandps, 2, m, v1, _MM_SET1(0x7FFFFFFF, 16))>
    endm
_mm512_mask_abs_ps macro v1, m, v2
    exitm<_mm512_mask(vandps, 2, v1, m, v2, _MM_SET1(0x7FFFFFFF, 16))>
    endm
_mm512_maskz_abs_pd macro m, v1
    exitm<_mm512_maskz(vandpd, 1, m, v1, _MM_SET1(0x7FFFFFFFFFFFFFFF, 8))>
    endm
_mm512_mask_abs_pd macro v1, m, v2
    exitm<_mm512_mask(vandpd, 1, v1, m, v2, _MM_SET1(0x7FFFFFFFFFFFFFFF, 8))>
    endm

_mm512_abs_ps macro v1
        exitm<_mm512_maskz_abs_ps(_MM_K0_REG, v1)>
        endm

_mm512_abs_pd macro v1
        exitm<_mm512_maskz_abs_pd(_MM_K0_REG, v1)>
        endm

_mm512_max_ps macro v1, v2
        exitm<_mm512_maskz_max_round_ps(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_max_round_ps macro v1, v2, e3
        exitm<_mm512_maskz_max_round_ps(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_mask_max_ps macro v1, _k2, v3, v4
        exitm<_mm512_mask_max_round_ps(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_max_ps macro _k1, v2, v3
        exitm<_mm512_maskz_max_round_ps(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_max_pd macro v1, v2
        exitm<_mm512_maskz_max_round_pd(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_max_round_pd macro v1, v2, e3
        exitm<_mm512_maskz_max_round_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_mask_max_pd macro v1, _k2, v3, v4
        exitm<_mm512_mask_max_round_pd(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_max_pd macro _k1, v2, v3
        exitm<_mm512_maskz_max_round_pd(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_min_ps macro v1, v2
        exitm<_mm512_maskz_min_round_ps(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_min_round_ps macro v1, v2, e3
        exitm<_mm512_maskz_min_round_ps(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_mask_min_ps macro v1, _k2, v3, v4
        exitm<_mm512_mask_min_round_ps(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_min_ps macro _k1, v2, v3
        exitm<_mm512_maskz_min_round_ps(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_min_pd macro v1, v2
        exitm<_mm512_maskz_min_round_pd(_MM_K0_REG, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_min_round_pd macro v1, v2, e3
        exitm<_mm512_maskz_min_round_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_mask_min_pd macro v1, _k2, v3, v4
        exitm<_mm512_mask_min_round_pd(v1, (_k2), v3, (v4), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_min_pd macro _k1, v2, v3
        exitm<_mm512_maskz_min_round_pd(_k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_rcp14_ps macro v1
        exitm<_mm512_maskz_rcp14_ps(_MM_K0_REG, v1)>
        endm

_mm512_rcp14_pd macro v1
        exitm<_mm512_maskz_rcp14_pd(_MM_K0_REG, v1)>
        endm

_mm512_rsqrt14_ps macro v1
        exitm<_mm512_maskz_rsqrt14_ps(_MM_K0_REG, v1)>
        endm

_mm512_rsqrt14_pd macro v1
        exitm<_mm512_maskz_rsqrt14_pd(_MM_K0_REG, v1)>
        endm

_mm512_cvt_roundps_pd macro v1, e2
        exitm<_mm512_maskz_cvt_roundps_pd(_MM_K0_REG, v1, e2)>
        endm

_mm512_cvtps_pd macro v1
        exitm<_mm512_cvt_roundps_pd(v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_cvtps_pd macro _k1, v2
        exitm<_mm512_maskz_cvt_roundps_pd(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtps_pd macro v1, _k2, v3
        exitm<_mm512_mask_cvt_roundps_pd(v1, (_k2), v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvt_roundpd_ps macro v1, e2
        exitm<_mm512_maskz_cvt_roundpd_ps(_MM_K0_REG, v1, e2)>
        endm

_mm512_cvtpd_ps macro v1
        exitm<_mm512_cvt_roundpd_ps(v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_cvtpd_ps macro _k1, v2
        exitm<_mm512_maskz_cvt_roundpd_ps(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtpd_ps macro v1_old, _k1, v2
        exitm<_mm512_mask_cvt_roundpd_ps((v1_old), _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

; Pseudo-Op for VCMP*

for cm,<eq,lt,le,unord,neq,nlt,nle,ord,eq_uq,nge,ngt,false,neq_oq,ge,
    gt,true,eq_os,lt_oq,le_oq,unord_s,neq_us,nlt_uq,nle_uq,
    ord_s,eq_us,nge_uq,ngt_uq,false_os,neq_os,ge_oq,gt_oq,true_us>
    _mm512_cmp&cm&_ps macro a, b
        vcmp&cm&ps k0, a, b
        vpmovm2d a,k0 ; Expand bits to zmm
        retm<a>
        endm
    endm

_mm512_cmp_ps_mask macro v1, v2, i3
        exitm<_mm512_mask_cmp_round_ps_mask(_MM_K0_REG, v1, v2, i3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cmp_round_ps_mask macro v1, v2, i3, e4
        exitm<_mm512_mask_cmp_round_ps_mask(_MM_K0_REG, v1, v2, i3, e4)>
        endm

_mm512_mask_cmp_ps_mask macro _k1, v2, v3, i4
        exitm<_mm512_mask_cmp_round_ps_mask(_k1, v2, v3, i4, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cmp_pd_mask macro v1, v2, i3
        exitm<_mm512_mask_cmp_round_pd_mask(_MM_K0_REG, v1, v2, i3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cmp_round_pd_mask macro v1, v2, i3, e4
        exitm<_mm512_mask_cmp_round_pd_mask(_MM_K0_REG, v1, v2, i3, e4)>
        endm

_mm512_mask_cmp_pd_mask macro _k1, v2, v3, i4
        exitm<_mm512_mask_cmp_round_pd_mask(_k1, v2, v3, i4, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cmpeq_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_EQ_OQ)>
        endm
_mm512_mask_cmpeq_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_EQ_OQ)>
        endm

_mm512_cmplt_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_LT_OS)>
        endm
_mm512_mask_cmplt_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_LT_OS)>
        endm

_mm512_cmple_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_LE_OS)>
        endm
_mm512_mask_cmple_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_LE_OS)>
        endm

_mm512_cmpunord_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_UNORD_Q)>
        endm

_mm512_mask_cmpunord_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_UNORD_Q)>
        endm

_mm512_cmpneq_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_NEQ_UQ)>
        endm

_mm512_mask_cmpneq_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_NEQ_UQ)>
        endm

_mm512_cmpnlt_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_NLT_US)>
        endm

_mm512_mask_cmpnlt_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_NLT_US)>
        endm

_mm512_cmpnle_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_NLE_US)>
        endm

_mm512_mask_cmpnle_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_NLE_US)>
        endm

_mm512_cmpord_ps_mask macro v1, v2
        exitm<_mm512_cmp_ps_mask(v1, v2, _CMP_ORD_Q)>
        endm

_mm512_mask_cmpord_ps_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_ps_mask(_k1, v1, v2, _CMP_ORD_Q)>
        endm

_mm512_cmpeq_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_EQ_OQ)>
        endm
_mm512_mask_cmpeq_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_EQ_OQ)>
        endm

_mm512_cmplt_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_LT_OS)>
        endm
_mm512_mask_cmplt_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_LT_OS)>
        endm

_mm512_cmple_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_LE_OS)>
        endm
_mm512_mask_cmple_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_LE_OS)>
        endm

_mm512_cmpunord_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_UNORD_Q)>
        endm

_mm512_mask_cmpunord_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_UNORD_Q)>
        endm

_mm512_cmpneq_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_NEQ_UQ)>
        endm

_mm512_mask_cmpneq_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_NEQ_UQ)>
        endm

_mm512_cmpnlt_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_NLT_US)>
        endm

_mm512_mask_cmpnlt_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_NLT_US)>
        endm

_mm512_cmpnle_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_NLE_US)>
        endm

_mm512_mask_cmpnle_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_NLE_US)>
        endm

_mm512_cmpord_pd_mask macro v1, v2
        exitm<_mm512_cmp_pd_mask(v1, v2, _CMP_ORD_Q)>
        endm

_mm512_mask_cmpord_pd_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_pd_mask(_k1, v1, v2, _CMP_ORD_Q)>
        endm


_mm512_broadcast_f32x2 macro v1
        exitm<_mm512_maskz_broadcast_f32x2(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_f32x4 macro v1
        exitm<_mm512_maskz_broadcast_f32x4(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_f32x8 macro v1
        exitm<_mm512_maskz_broadcast_f32x8(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_f64x2 macro v1
        exitm<_mm512_maskz_broadcast_f64x2(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_f64x4 macro v1
        exitm<_mm512_maskz_broadcast_f64x4(_MM_K0_REG, v1)>
        endm

_mm512_broadcastsd_pd macro v1
        exitm<_mm512_maskz_broadcastsd_pd(_MM_K0_REG, v1)>
        endm

_mm512_broadcastss_ps macro v1
        exitm<_mm512_maskz_broadcastss_ps(_MM_K0_REG, v1)>
        endm

_mm512_extractf32x4_ps macro v1, e2
        exitm<_mm512_maskz_extractf32x4_ps(_MM_K0_REG, v1, e2)>
        endm

_mm512_extractf32x8_ps macro v1, e2
        exitm<_mm512_maskz_extractf32x8_ps(_MM_K0_REG, v1, e2)>
        endm

_mm512_extractf64x2_pd macro v1, e2
        exitm<_mm512_maskz_extractf64x2_pd(_MM_K0_REG, v1, e2)>
        endm

_mm512_extractf64x4_pd macro v1, e2
        exitm<_mm512_maskz_extractf64x4_pd(_MM_K0_REG, v1, e2)>
        endm


_mm512_insertf32x4 macro v1, v2, e3
        exitm<_mm512_maskz_insertf32x4(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_insertf32x8 macro v1, v2, e3
        exitm<_mm512_maskz_insertf32x8(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_insertf64x2 macro v1, v2, e3
        exitm<_mm512_maskz_insertf64x2(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_insertf64x4 macro v1, v2, e3
        exitm<_mm512_maskz_insertf64x4(_MM_K0_REG, v1, v2, e3)>
        endm


_mm512_shuffle_f32x4 macro v1, v2, e3
        exitm<_mm512_maskz_shuffle_f32x4(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_shuffle_f64x2 macro v1, v2, e3
        exitm<_mm512_maskz_shuffle_f64x2(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_shuffle_pd macro v1, v2, e3
        exitm<_mm512_maskz_shuffle_pd(_MM_K0_REG, v1, v2, e3)>
        endm

_mm512_shuffle_ps macro v1, v2, e3
        exitm<_mm512_maskz_shuffle_ps(_MM_K0_REG, v1, v2, e3)>
        endm


_mm512_kand macro _k1, _k2
        exitm<((_k1 and (_k2)))>
        endm

_mm512_kandn macro _k1, _k2
        exitm<((not _k1 and (_k2)))>
        endm

_mm512_kor macro _k1, _k2
        exitm<((_k1 or (_k2)))>
        endm

_mm512_kxor macro _k1, _k2
        exitm<((_k1 xor (_k2)))>
        endm

_mm512_kxnor macro _k1, _k2
        exitm<((not (_k1 xor (_k2))))>
        endm

_mm512_knot macro _k1
        exitm<not _k1>
        endm


_mm512_setzero_si512 macro z:=<zmm0>
    vxorps z,z,z
    retm<z>
    endm

_mm512_set_epi8 macro args:vararg
    exitm<_MM_SET(args)>
    endm
_mm512_set_epi16 macro args:vararg
    exitm<_MM_SET(args)>
    endm
_mm512_set_epi32 macro args:vararg
    exitm<_MM_SET(args)>
    endm
_mm512_set_epi64 macro args:vararg
    exitm<_MM_SET(args)>
    endm

_mm512_mask_set1 macro cm, kz, v1, m, e2
  local mask
    _mm512_loadk mask, kz, cm, m
    inst textequ @CatStr(<vpbroadcast>, @SubStr(<bwdq>, cm, 1))
if cm eq 4
    _mm512_loadq(m)
 ifdef _WIN64
    inst    v1 mask, rax
 else
    push    edx
    push    eax
    inst    v1 mask, [esp]
    add     esp,8
 endif
else
    mov     eax, e2
    inst    v1 mask, eax
endif
    retm    <v1>
    endm
 for cm,<1,2,3,4>
    for lm,<add,sub>
        @CatStr(<_mm512_mask_&lm&_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
      if cm le 2
        @CatStr(<_mm512_mask_&lm&s_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&s>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&s_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&s>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        @CatStr(<_mm512_mask_&lm&s_epu>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&us>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&s_epu>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&us>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
      endif
        endm
    for lm,<min,max>
        @CatStr(<_mm512_mask_&lm&_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&s>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&s>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        @CatStr(<_mm512_mask_&lm&_epu>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&u>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&_epu>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&u>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        endm
  if cm ge 2
    @CatStr(<_mm512_mask_mullo_epi>, %4 shl cm) macro v1, m, v2, v3
        exitm<_mm512_mask(@CatStr(<vpmull>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2, v3)>
        endm
    @CatStr(<_mm512_maskz_mullo_epi>, %4 shl cm) macro m, v1, v2
        exitm<_mm512_maskz(@CatStr(<vpmull>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
        endm
  endif
    @CatStr(<_mm512_mask_set1_epi>, %4 shl cm) macro v1, m, e1
        exitm<_mm512_mask_set1(cm, 0, v1, m, e1)>
        endm
    @CatStr(<_mm512_maskz_set1_epi>, %4 shl cm) macro m, e1, v1:=<zmm0>
        exitm<_mm512_mask_set1(cm, 1, v1, m, e1)>
        endm
    @CatStr(<_mm512_mask_abs_epi>, %4 shl cm) macro v1, m, v2
        exitm<_mm512_mask2(@CatStr(<vpabs>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2)>
        endm
    @CatStr(<_mm512_maskz_abs_epi>, %4 shl cm) macro m, v1
        exitm<_mm512_maskz2(@CatStr(<vpabs>, @SubStr(<bwdq>, cm, 1)), cm, m, v1)>
        endm
    @CatStr(<_mm512_mask_broadcast>, @SubStr(<bwdq>, cm, 1), <_epi>, %4 shl cm) macro v1, m, v2
        exitm<_mm512_mask2(@CatStr(<vpbroadcast>, @SubStr(<bwdq>, cm, 1)), cm, v1, m, v2)>
        endm
    @CatStr(<_mm512_maskz_broadcast>, @SubStr(<bwdq>, cm, 1), <_epi>, %4 shl cm) macro m, v1, v2:=<zmm0>
        exitm<_mm512_mask2_round(1, @CatStr(<vpbroadcast>, @SubStr(<bwdq>, cm, 1)), cm, m, v2, v1)>
        endm
    endm

for cm,<32x2,32x4,32x8>
    _mm512_mask_broadcast_i&cm& macro v1, m, m128
        exitm<_mm512_mask2(vbroadcasti&cm&, 3, v1, m, m128)>
        endm
    _mm512_maskz_broadcast_i&cm& macro m, m128, v1:=<zmm0>
        exitm<_mm512_mask2_round(1, vbroadcasti&cm&, 3, m, v1, m128)>
        endm
    endm
for cm,<64x2,64x4>
    _mm512_mask_broadcast_i&cm& macro v1, m, m128
        exitm<_mm512_mask2(vbroadcasti&cm&, 4, v1, m, m128)>
        endm
    _mm512_maskz_broadcast_i&cm& macro m, m128, v1:=<zmm0>
        exitm<_mm512_mask2_round(1, vbroadcasti&cm&, 4, m, v1, m128)>
        endm
    endm

_mm512_broadcastmw_epi32 proto __vdecl :word {
    kmovw           k1,ecx
    vpbroadcastmw2d zmm0,k1
    }
_mm512_broadcastmb_epi64 proto __vdecl :byte {
    kmovb           k1,ecx
    vpbroadcastmb2q zmm0,k1
    }

_mm512_mask_mul_epi32 macro v1, m, v2, v3
    exitm<_mm512_mask(vpmuldq, 3, v1, m, v2, v3)>
    endm
_mm512_maskz_mul_epi32 macro m, v1, v2
    exitm<_mm512_maskz(vpmuldq, 3, m, v1, v2)>
    endm
_mm512_mask_mul_epu32 macro v1, m, v2, v3
    exitm<_mm512_mask(vpmuludq, 3, v1, m, v2, v3)>
    endm
_mm512_maskz_mul_epu32 macro m, v1, v2
    exitm<_mm512_maskz(vpmuludq, 3, m, v1, v2)>
    endm
_mm512_mask_mulhi_epi16 macro v1, m, v2, v3
    exitm<_mm512_mask(vpmulhw, 2, v1, m, v2, v3)>
    endm
_mm512_maskz_mulhi_epi16 macro m, v1, v2
    exitm<_mm512_maskz(vpmulhw, 2, m, v1, v2)>
    endm
_mm512_mask_mulhi_epu16 macro v1, m, v2, v3
    exitm<_mm512_mask(vpmulhuw, 2, v1, m, v2, v3)>
    endm
_mm512_maskz_mulhi_epu16 macro m, v1, v2
    exitm<_mm512_maskz(vpmulhuw, 2, m, v1, v2)>
    endm

_mm512_mullox_epi64 proto __vdecl :zword, :zword {
    vpsrlq          zmm3, zmm0, 32
    vpmuludq        zmm5, zmm0, zmm1
    vpsrlq          zmm2, zmm1, 32
    vpmuludq        zmm4, zmm2, zmm0
    vpmuludq        zmm3, zmm3, zmm1
    vpaddq          zmm0, zmm4, zmm3
    vpsllq          zmm1, zmm0, 32
    vpaddq          zmm0, zmm1, zmm5
    }

_mm512_mask_mullox_epi64 proto __vdecl :zword, :byte, :zword, :zword {}

_mm512_mask_mulhrs_epi16 macro v1, m, v2, v3
    exitm<_mm512_mask(vpmulhrsw, 2, v1, m, v2, v3)>
    endm
_mm512_maskz_mulhrs_epi16 macro m, v1, v2
    exitm<_mm512_maskz(vpmulhrsw, 2, m, v1, v2)>
    endm

_mm512_mask_load_epi macro bits, cm, kz, v1, m, p
  local mask
    _mm512_loadk mask, kz, cm, m
    _mm512_loadp(p)
    vmovdqu&bits& v1 mask,[rax]
    retm<v1>
    endm
_mm512_mask_load_epi32 macro v1, m, p
    exitm<_mm512_mask_load_epi(32, 3, 0, v1, m, p)>
    endm
_mm512_maskz_load_epi32 macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load_epi(32, 3, 1, v1, m, p)>
    endm
_mm512_mask_load_epi64 macro v1, m, p
    exitm<_mm512_mask_load_epi(64, 4, 0, v1, m, p)>
    endm
_mm512_maskz_load_epi64 macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load_epi(64, 4, 1, v1, m, p)>
    endm
_mm512_mask_loadu_epi8 macro v1, m, p
    exitm<_mm512_mask_load_epi(8, 1, 0, v1, m, p)>
    endm
_mm512_maskz_loadu_epi8 macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load_epi(8, 1, 1, v1, m, p)>
    endm
_mm512_mask_loadu_epi16 macro v1, m, p
    exitm<_mm512_mask_load_epi(16, 2, 0, v1, m, p)>
    endm
_mm512_maskz_loadu_epi16 macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load_epi(16, 2, 1, v1, m, p)>
    endm
_mm512_mask_loadu_epi32 macro v1, m, p
    exitm<_mm512_mask_load_epi(32, 3, 0, v1, m, p)>
    endm
_mm512_maskz_loadu_epi32 macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load_epi(32, 3, 1, v1, m, p)>
    endm
_mm512_mask_loadu_epi64 macro v1, m, p
    exitm<_mm512_mask_load_epi(64, 4, 0, v1, m, p)>
    endm
_mm512_maskz_loadu_epi64 macro m, p, v1:=<zmm0>
    exitm<_mm512_mask_load_epi(64, 4, 1, v1, m, p)>
    endm

_mm512_mask_store_epi macro bits, cm, kz, p, m, v1
  local mask
    _mm512_loadk mask, kz, cm, m
    _mm512_loadp(p)
    vmovdqu&bits& [rax] mask, v1
    retm<v1>
    endm
_mm512_mask_store_epi32 macro p, m, v1
    exitm<_mm512_mask_store_epi(32, 3, 0, p, m, v1)>
    endm
_mm512_mask_store_epi64 macro p, m, v1
    exitm<_mm512_mask_store_epi(64, 4, 0, p, m, v1)>
    endm
_mm512_mask_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_store_epi(8, 1, 0, p, m, v1)>
    endm
_mm512_mask_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_store_epi(16, 2, 0, p, m, v1)>
    endm
_mm512_mask_storeu_epi32 macro p, m, v1
    exitm<_mm512_mask_store_epi(32, 3, 0, p, m, v1)>
    endm
_mm512_mask_storeu_epi64 macro p, m, v1
    exitm<_mm512_mask_store_epi(64, 4, 0, p, m, v1)>
    endm

_mm512_mask_extracti32x4_epi32 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vextracti32x4, 4, v1, m, v2, i3)>
    endm
_mm512_maskz_extracti32x4_epi32 macro m, v2, i3, v1:=<xmm0>
    exitm<_mm512_maskz2i(vextracti32x4, 4, m, v2, i3, v1)>
    endm
_mm512_mask_extracti32x8_epi32 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vextracti32x8, 4, v1, m, v2, i3)>
    endm
_mm512_maskz_extracti32x8_epi32 macro m, v2, i3, v1:=<ymm0>
    exitm<_mm512_maskz2i(vextracti32x8, 4, m, v2, i3, v1)>
    endm
_mm512_mask_extracti64x2_epi64 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vextracti64x2, 4, v1, m, v2, i3)>
    endm
_mm512_maskz_extracti64x2_epi64 macro m, v2, i3, v1:=<ymm0>
    exitm<_mm512_maskz2i(vextracti64x2, 4, m, v2, i3, v1)>
    endm
_mm512_mask_extracti64x4_epi64 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vextracti64x4, 4, v1, m, v2, i3)>
    endm
_mm512_maskz_extracti64x4_epi64 macro m, v2, i3, v1:=<ymm0>
    exitm<_mm512_maskz2i(vextracti64x4, 4, m, v2, i3, v1)>
    endm

_mm512_mask_inserti32x4 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vinserti32x4, 3, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_inserti32x4 macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vinserti32x4, 3, m, v2, v3, i4)>
    endm
_mm512_mask_inserti32x8 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vinserti32x8, 3, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_inserti32x8 macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vinserti32x8, 3, m, v2, v3, i4)>
    endm
_mm512_mask_inserti64x2 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vinserti64x2, 4, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_inserti64x2 macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vinserti64x2, 4, m, v2, v3, i4)>
    endm
_mm512_mask_inserti64x4 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vinserti64x4, 4, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_inserti64x4 macro m, v2, v3, i4
    exitm<_mm512_maskz3i(vinserti64x4, 4, m, v2, v3, i4)>
    endm

_mm512_mask_shuffle_epi8 macro v1, m, v2, v3
    exitm<_mm512_mask(vpshufb, 1, v1, m, v2, v3)>
    endm
_mm512_maskz_shuffle_epi8 macro m, v2, v3
    exitm<_mm512_maskz(vpshufb, 1, m, v2, v3)>
    endm
_mm512_mask_shuffle_epi32 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vpshufd, 3, v1, m, v2, i3)>
    endm
_mm512_maskz_shuffle_epi32 macro m, v2, i3
    exitm<_mm512_maskz2i(vpshufd, 3, m, v2, i3)>
    endm
_mm512_mask_shuffle_i32x4 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vshufi32x4, 3, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_shuffle_i32x4 macro m, v1, v2, i3
    exitm<_mm512_maskz3i(vshufi32x4, 3, m, v1, v2, i3)>
    endm
_mm512_mask_shuffle_i64x2 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vshufi64x2, 4, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_shuffle_i64x2 macro m, v1, v2, i3
    exitm<_mm512_maskz3i(vshufi64x2, 4, m, v1, v2, i3)>
    endm


_mm512_mask_shufflehi_epi16 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vpshufhw, 2, v1, m, v2, i3)>
    endm
_mm512_maskz_shufflehi_epi16 macro m, v1, i2
    exitm<_mm512_maskz2i(vpshufhw, 2, m, v1, i2)>
    endm
_mm512_mask_shufflelo_epi16 macro v1, m, v2, i3
    exitm<_mm512_mask2i(vpshuflw, 2, v1, m, v2, i3)>
    endm
_mm512_maskz_shufflelo_epi16 macro m, v1, i2
    exitm<_mm512_maskz2i(vpshuflw, 2, m, v1, i2)>
    endm

_mm512_mask_mov_ps macro v1, m, v2
    exitm<_mm512_mask2(vmovaps, 3, v1, m, v2)>
    endm
_mm512_maskz_mov_ps macro m, v1
    exitm<_mm512_maskz2(vmovaps, 3, m, v1)>
    endm
_mm512_mask_mov_pd macro v1, m, v2
    exitm<_mm512_mask2(vmovapd, 4, v1, m, v2)>
    endm
_mm512_maskz_mov_pd macro m, v1
    exitm<_mm512_maskz2(vmovapd, 4, m, v1)>
    endm
_mm512_mask_mov_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vmovdqu8, 1, v1, m, v2)>
    endm
_mm512_maskz_mov_epi8 macro m, v1
    exitm<_mm512_maskz2(vmovdqu8, 1, m, v1)>
    endm
_mm512_mask_mov_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vmovdqu16, 2, v1, m, v2)>
    endm
_mm512_maskz_mov_epi16 macro m, v1
    exitm<_mm512_maskz2(vmovdqu16, 2, m, v1)>
    endm
_mm512_mask_mov_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vmovdqu32, 3, v1, m, v2)>
    endm
_mm512_maskz_mov_epi32 macro m, v1
    exitm<_mm512_maskz2(vmovdqu32, 3, m, v1)>
    endm
_mm512_mask_mov_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vmovdqu64, 4, v1, m, v2)>
    endm
_mm512_maskz_mov_epi64 macro m, v1
    exitm<_mm512_maskz2(vmovdqu64, 4, m, v1)>
    endm
_mm512_mask_movedup_pd macro v1, m, v2
    exitm<_mm512_mask2(vmovddup, 4, v1, m, v2)>
    endm
_mm512_maskz_movedup_pd macro m, v1
    exitm<_mm512_maskz2(vmovddup, 4, m, v1)>
    endm
_mm512_mask_movehdup_ps macro v1, m, v2
    exitm<_mm512_mask2(vmovshdup, 3, v1, m, v2)>
    endm
_mm512_maskz_movehdup_ps macro m, v1
    exitm<_mm512_maskz2(vmovshdup, 3, m, v1)>
    endm
_mm512_mask_moveldup_ps macro v1, m, v2
    exitm<_mm512_mask2(vmovsldup, 3, v1, m, v2)>
    endm
_mm512_maskz_moveldup_ps macro m, v1
    exitm<_mm512_maskz2(vmovsldup, 3, m, v1)>
    endm

_mm512_movm_epi8 macro m, v1:=<zmm0>
    _mm512_load_kq(m)
    vpmovm2b v1,k1
    retm<v1>
    endm
_mm512_movm_epi16 macro m, v1:=<zmm0>
    _mm512_load_kd(m)
    vpmovm2b v1,k1
    retm<v1>
    endm
_mm512_movm_epi32 macro m, v1:=<zmm0>
    _mm512_load_kw(m)
    vpmovm2b v1,k1
    retm<v1>
    endm
_mm512_movm_epi64 macro m, v1:=<zmm0>
    _mm512_load_kb(m)
    vpmovm2b v1,k1
    retm<v1>
    endm

_mm512_movepi8_mask macro v1
    vpmovb2m    k1,v1
    kmovq       rax,k1
    retm        <rax>
    endm
_mm512_movepi16_mask macro v1
    vpmovb2m    k1,v1
    kmovd       eax,k1
    retm        <eax>
    endm
_mm512_movepi32_mask macro v1
    vpmovb2m    k1,v1
    kmovw       eax,k1
    retm        <eax>
    endm
_mm512_movepi64_mask macro v1
    vpmovb2m    k1,v1
    kmovb       eax,k1
    retm        <eax>
    endm

_mm512_mask_alignr_epi8 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(vpalignr, 1, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_alignr_epi8 macro m, v1, v2, i3
    exitm<_mm512_maskz3i(vpalignr, 1, m, v1, v2, i3)>
    endm
_mm512_mask_alignr_epi32 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(valignd, 3, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_alignr_epi32 macro m, v1, v2, i3
    exitm<_mm512_maskz3i(valignd, 3, m, v1, v2, i3)>
    endm
_mm512_mask_alignr_epi64 macro v1, m, v2, v3, i4
    exitm<_mm512_mask3i(valignq, 4, v1, m, v2, v3, i4)>
    endm
_mm512_maskz_alignr_epi64 macro m, v1, v2, i3
    exitm<_mm512_maskz3i(valignq, 4, m, v1, v2, i3)>
    endm

for lm,<and,or,xor>
    for cm,<s,d>
        _mm512_mask_&lm&_p&cm& macro v1, m, v2, v3
            exitm<_mm512_mask(v&lm&p&cm&, @InStr(1,<sd>,cm) + 2, v1, m, v2, v3)>
            endm
        _mm512_maskz_&lm&_p&cm& macro m, v1, v2
            exitm<_mm512_maskz(v&lm&p&cm&, @InStr(1,<sd>,cm) + 2, m, v1, v2)>
            endm
        endm
    for cm,<3,4>
        @CatStr(<_mm512_mask_&lm&_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&>, @SubStr(<dq>, cm-2, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&>, @SubStr(<dq>, cm-2, 1)), cm, m, v1, v2)>
            endm
        endm
    endm

_mm512_mask_andnot_pd macro v1, m, v2, v3
    exitm<_mm512_mask(vandnpd, 4, v1, m, v2, v3)>
    endm
_mm512_maskz_andnot_pd macro m, v1, v2
    exitm<_mm512_maskz(vandnpd, 4, m, v1, v2)>
    endm
_mm512_mask_andnot_ps macro v1, m, v2, v3
    exitm<_mm512_mask(vandnps, 3, v1, m, v2, v3)>
    endm
_mm512_maskz_andnot_ps macro m, v1, v2
    exitm<_mm512_maskz(vandnps, 3, m, v1, v2)>
    endm
_mm512_mask_andnot_epi32 macro v1, m, v2, v3
    exitm<_mm512_mask(vpandnd, 2, v1, m, v2, v3)>
    endm
_mm512_maskz_andnot_epi32 macro m, v1, v2
    exitm<_mm512_maskz(vpandnd, 2, m, v1, v2)>
    endm
_mm512_mask_andnot_epi64 macro v1, m, v2, v3
    exitm<_mm512_mask(vpandnq, 1, v1, m, v2, v3)>
    endm
_mm512_maskz_andnot_epi64 macro m, v1, v2
    exitm<_mm512_maskz(vpandnq, 2, m, v1, v2)>
    endm

_mm512_mask_blend_ps macro m, v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vblendmps, 3, v3, m, v1, v2)>
    endm
_mm512_mask_blend_pd macro m, v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vblendmpd, 4, v3, m, v1, v2)>
    endm
_mm512_mask_blend_epi8 macro m, v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vpblendmb, 1, v3, m, v1, v2)>
    endm
_mm512_mask_blend_epi16 macro m, v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vpblendmw, 2, v3, m, v1, v2)>
    endm
_mm512_mask_blend_epi32 macro m, v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vpblendmd, 3, v3, m, v1, v2)>
    endm
_mm512_mask_blend_epi64 macro m, v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vpblendmq, 4, v3, m, v1, v2)>
    endm

for lm,<sll,srl,sra>
    for cm,<2,3,4>
        @CatStr(<_mm512_mask_&lm&_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&>, @SubStr(<dq>, cm-2, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        @CatStr(<_mm512_mask_&lm&i_epi>, %4 shl cm) macro v1, m, v2, i3
            exitm<_mm512_mask2i(@CatStr(<vp&lm&>, @SubStr(<dq>, cm-2, 1)), cm, v1, m, v2, i3)>
            endm
        @CatStr(<_mm512_maskz_&lm&i_epi>, %4 shl cm) macro m, v1, i2
            exitm<_mm512_maskz2i(@CatStr(<vp&lm&>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, i2)>
            endm
        @CatStr(<_mm512_mask_&lm&v_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&v>, @SubStr(<dq>, cm-2, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&v_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&v>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        endm
    endm

_mm512_bslli_epi128 macro v1, i2, v2:=<zmm0>
    exitm<_mm512_mask2i(vpslldq, 4, v2, _MM_K0_REG, v1, i2)>
    endm
_mm512_bsrli_epi128 macro v1, i2, v2:=<zmm0>
    exitm<_mm512_mask2i(vpsrldq, 4, v2, _MM_K0_REG, v1, i2)>
    endm

for lm,<rol,ror>
    for cm,<3,4>
        @CatStr(<_mm512_mask_&lm&_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&>, @SubStr(<dq>, cm-2, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        @CatStr(<_mm512_mask_&lm&v_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vp&lm&v>, @SubStr(<dq>, cm-2, 1)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_&lm&v_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vp&lm&v>, @SubStr(<bwdq>, cm, 1)), cm, m, v1, v2)>
            endm
        endm
    endm

for lm,<hi,lo>
    for cm,<s,d>
        _mm512_mask_unpack&lm&_p&cm& macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vunpck>, @SubStr(lm,1,1), <p>, cm), @InStr(1,<sd>,cm) + 2, v1, m, v2, v3)>
            endm
        _mm512_maskz_unpack&lm&_p&cm& macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vunpck>, @SubStr(lm,1,1), <p>, cm), @InStr(1,<sd>,cm) + 2, m, v1, v2)>
            endm
        endm
    for cm,<1,2,3,4>
        @CatStr(<_mm512_mask_unpack&lm&_epi>, %4 shl cm) macro v1, m, v2, v3
            exitm<_mm512_mask(@CatStr(<vpunpck>, @SubStr(lm,1,1), @SubStr(<bw wd dq qdq>, cm*3-2, 3)), cm, v1, m, v2, v3)>
            endm
        @CatStr(<_mm512_maskz_unpack&lm&_epi>, %4 shl cm) macro m, v1, v2
            exitm<_mm512_maskz(@CatStr(<vpunpck>, @SubStr(lm,1,1), @SubStr(<bw wd dq qdq>, cm*3-2, 3)), cm, m, v1, v2)>
            endm
        endm
    endm

_mm512_mask_getexp_round_ps macro v1, m, v2, i3
    exitm<_mm512_mask2(vgetexpps, 3, v1, m, v2, i3)>
    endm
_mm512_maskz_getexp_round_ps macro m, v1, i3
    exitm<_mm512_maskz2(vgetexpps, 3, m, v1, , i3)>
    endm
_mm512_mask_getexp_round_pd macro v1, m, v2, i3
    exitm<_mm512_mask2(vgetexppd, 4, v1, m, v2, i3)>
    endm
_mm512_maskz_getexp_round_pd macro m, v1, i3
    exitm<_mm512_maskz2(vgetexppd, 4, m, v1, , i3)>
    endm

_mm512_mask_getmant_round_ps macro v1, m, v2, intv, sgn, r
    exitm<_mm512_mask2i(vgetmantps, 3, v1, m, v2, intv or (sgn shl 2), r)>
    endm
_mm512_maskz_getmant_round_ps macro m, v1, intv, sgn, r
    exitm<_mm512_maskz2ir(vgetmantps, 3, m, v1, intv or (sgn shl 2), r)>
    endm
_mm512_mask_getmant_round_pd macro v1, m, v2, intv, sgn, r
    exitm<_mm512_mask2i(vgetmantpd, 4, v1, m, v2, intv or (sgn shl 2), r)>
    endm
_mm512_maskz_getmant_round_pd macro m, v1, intv, sgn, r
    exitm<_mm512_maskz2ir(vgetmantpd, 4, m, v1, intv or (sgn shl 2), r)>
    endm

_mm512_mask_permute_pd macro v1, m, v2, i3
    exitm<_mm512_mask2i(vpermilpd, 4, v1, m, v2, i3)>
    endm
_mm512_maskz_permute_pd macro m, v2, i3, v1:=<zmm0>
    exitm<_mm512_maskz2i(vpermilpd, 4, m, v2, i3, v1)>
    endm
_mm512_mask_permute_ps macro v1, m, v2, i3
    exitm<_mm512_mask2i(vpermilps, 3, v1, m, v2, i3)>
    endm
_mm512_maskz_permute_ps macro m, v2, i3, v1:=<zmm0>
    exitm<_mm512_maskz2i(vpermilps, 3, m, v2, i3, v1)>
    endm
_mm512_mask_permutevar_pd macro v1, m, v2, v3
    exitm<_mm512_mask(vpermilpd, 4, v1, m, v2, v3)>
    endm
_mm512_maskz_permutevar_pd macro m, v1, v2
    exitm<_mm512_maskz(vpermilpd, 4, m, v1, v2)>
    endm
_mm512_mask_permutevar_ps macro v1, m, v2, v3
    exitm<_mm512_mask(vpermilps, 3, v1, m, v2, v3)>
    endm
_mm512_maskz_permutevar_ps macro m, v1, v2
    exitm<_mm512_maskz(vpermilps, 3, m, v1, v2)>
    endm
_mm512_permutevar_epi32 macro v1, v2, v3:=<zmm0>
    exitm<_mm512_mask(vpermd, 3, v3, _MM_K0_REG, v1, v2)>
    endm
_mm512_mask_permutevar_epi32 macro v1, m, v2, v3
    exitm<_mm512_mask(vpermd, 3, v1, m, v2, v3)>
    endm

.pragma aux(k1, k1, k1)

_mm512_mask_permutex_pd proto asmcall :abs, :byte, :abs, :abs {
    vpermpd     _1 {k1}, _3, _4
    }
_mm512_maskz_permutex_pd proto asmcall :byte, :abs, :abs {
    vpermpd     zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_permutex_epi64 proto asmcall :abs, :byte, :abs, :abs {
    vpermq      _1 {k1}, _3, _4
    }
_mm512_maskz_permutex_epi64 proto asmcall :byte, :abs, :abs {
    vpermq      zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_permutexvar_pd proto asmcall :abs, :byte, :abs, :abs {
    vpermpd     _1 {k1}, _3, _4
    }
_mm512_maskz_permutexvar_pd proto asmcall :byte, :abs, :abs {
    vpermpd     zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_permutexvar_ps proto asmcall :abs, :word, :abs, :abs {
    vpermps     _1 {k1}, _3, _4
    }
_mm512_maskz_permutexvar_ps proto asmcall :word, :abs, :abs {
    vpermps     zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_permutexvar_epi16 proto asmcall :abs, :dword, :abs, :abs {
    vpermw      _1 {k1}, _3, _4
    }
_mm512_maskz_permutexvar_epi16 proto asmcall :dword, :abs, :abs {
    vpermw      zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_permutexvar_epi32 proto asmcall :abs, :word, :abs, :abs {
    vpermd      _1 {k1}, _3, _4
    }
_mm512_maskz_permutexvar_epi32 proto asmcall :word, :abs, :abs {
    vpermd      zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_permutexvar_epi64 proto asmcall :abs, :byte, :abs, :abs {
    vpermq      _1 {k1}, _3, _4
    }
_mm512_maskz_permutexvar_epi64 proto asmcall :byte, :abs, :abs {
    vpermq      zmm0 {k1}{z}, _2, _3
    }

_mm512_mask_permutex2var_pd proto asmcall :abs, :byte, :abs, :abs {
    vpermt2pd   _1 {k1}, _3, _4
    }
_mm512_mask2_permutex2var_pd proto asmcall :abs, :abs, :byte, :abs {
    vpermi2pd   _2 {k1}, _1, _4
    }
_mm512_maskz_permutex2var_pd proto asmcall :byte, :abs, :abs, :abs {
    vpermt2pd   _2 {k1}{z}, _3, _4
    }
_mm512_mask_permutex2var_ps proto asmcall :abs, :word, :abs, :abs {
    vpermt2ps   _1 {k1}, _3, _4
    }
_mm512_mask2_permutex2var_ps proto asmcall :abs, :abs, :word, :abs {
    vpermi2ps   _2 {k1}, _1, _4
    }
_mm512_maskz_permutex2var_ps proto asmcall :word, :abs, :abs, :abs {
    vpermt2ps   _2 {k1}{z}, _3, _4
    }
_mm512_mask_permutex2var_epi16 proto asmcall :abs, :dword, :abs, :abs {
    vpermt2w    _1 {k1}, _3, _4
    }
_mm512_mask2_permutex2var_epi16 proto asmcall :abs, :abs, :dword, :abs {
    vpermt2w    _2 {k1}, _1, _4
    }
_mm512_maskz_permutex2var_epi16 proto asmcall :dword, :abs, :abs, :abs {
    vpermt2w    _2 {k1}{z}, _3, _4
    }
_mm512_mask_permutex2var_epi32  proto asmcall :abs, :word, :abs, :abs {
    vpermt2d    _1 {k1}, _3, _4
    }
_mm512_mask2_permutex2var_epi32 proto asmcall :abs, :abs, :word, :abs {
    vpermt2d    _2 {k1}, _1, _4
    }
_mm512_maskz_permutex2var_epi32 proto asmcall :word, :abs, :abs, :abs {
    vpermt2d    _2 {k1}{z}, _3, _4
    }
_mm512_mask_permutex2var_epi64  proto asmcall :abs, :byte, :abs, :abs {
    vpermt2q    _1 {k1}, _3, _4
    }
_mm512_mask2_permutex2var_epi64 proto asmcall :abs, :abs, :byte, :abs {
    vpermt2q    _2 {k1}, _1, _4
    }
_mm512_maskz_permutex2var_epi64 proto asmcall :byte, :abs, :abs, :abs {
    vpermt2q    _2 {k1}{z}, _3, _4
    }

_mm512_mask_compress_pd proto asmcall :abs, :byte, :abs {
    vcompresspd _1 {k1}, _3
    }
_mm512_maskz_compress_pd proto asmcall :byte, :abs {
    vcompresspd zmm0 {k1}, _2
    }
_mm512_mask_compress_ps proto asmcall :abs, :word, :abs {
    vcompressps _1 {k1}, _3
    }
_mm512_maskz_compress_ps proto asmcall :word, :abs {
    vcompressps zmm0 {k1}, _2
    }
_mm512_mask_compress_epi32 proto asmcall :abs, :word, :abs {
    vpcompressd _1 {k1}, _3
    }
_mm512_maskz_compress_epi32 proto asmcall :word, :abs {
    vpcompressd zmm0 {k1}, _2
    }
_mm512_mask_compress_epi64 proto asmcall :abs, :byte, :abs {
    vpcompressq _1 {k1}, _3
    }
_mm512_maskz_compress_epi64 proto asmcall :byte, :abs {
    vpcompressq zmm0 {k1}, _2
    }

.pragma aux(ax, k1)

_mm512_mask_compressstoreu_pd proto asmcall :ptr, :byte, :abs {
    vcompresspd [_1] {k1}, _3
    }
_mm512_mask_compressstoreu_ps proto asmcall :ptr, :word, :abs {
    vcompressps [_1] {k1}, _3
    }
_mm512_mask_compressstoreu_epi32 proto asmcall :ptr, :word, :abs {
    vpcompressd [_1] {k1}, _3
    }
_mm512_mask_compressstoreu_epi64 proto asmcall :ptr, :byte, :abs {
    vpcompressq [_1] {k1}, _3
    }

.pragma aux(pop)


_mm512_mask_expand_pd proto asmcall :abs, :byte, :abs {
    vexpandpd   _1 {k1}, _3
    }
_mm512_maskz_expand_pd proto asmcall :byte, :zword {
    vexpandpd   zmm0 {k1}{z}, _2
    }
_mm512_mask_expand_ps proto asmcall :abs, :word, :zword {
    vexpandps   _1 {k1}, _3
    }
_mm512_maskz_expand_ps proto asmcall :word, :zword {
    vexpandps   zmm0 {k1}{z}, _2
    }
_mm512_mask_expand_epi32 proto asmcall :abs, :word, :abs {
    vpexpandd   _1 {k1}, _3
    }
_mm512_maskz_expand_epi32 proto asmcall :word, :abs {
    vpexpandd   zmm0 {k1}{z}, _2
    }
_mm512_mask_expand_epi64 proto asmcall :abs, :byte, :abs {
    vpexpandq   _1 {k1}, _3
    }
_mm512_maskz_expand_epi64 proto asmcall :byte, :abs {
    vpexpandq   zmm0 {k1}{z}, _2
    }

.pragma aux(eax, k1, ecx)

_mm512_mask_expandloadu_pd proto asmcall :abs, :byte, :ptr {
    vexpandpd   _1 {k1}, [_3]
    }
_mm512_mask_expandloadu_ps proto asmcall :abs, :word, :ptr {
    vexpandps   _1 {k1}, [_3]
    }
_mm512_mask_expandloadu_epi32 proto asmcall :abs, :word, :ptr {
    vpexpandd   _1 {k1}, [_3]
    }
_mm512_mask_expandloadu_epi64 proto asmcall :abs, :byte, :ptr {
    vpexpandq   _1 {k1}, [_3]
    }

.pragma aux(k1, ecx)

_mm512_maskz_expandloadu_pd proto asmcall :byte, :ptr {
    vexpandpd   zmm0 {k1}, [_2]
    }
_mm512_maskz_expandloadu_ps proto asmcall :word, :ptr {
    vexpandps   zmm0 {k1}, [_2]
    }
_mm512_maskz_expandloadu_epi32 proto asmcall :word, :ptr {
    vpexpandd   zmm0 {k1}, [_2]
    }
_mm512_maskz_expandloadu_epi64 proto asmcall :byte, :ptr {
    vpexpandq   zmm0 {k1}, [_2]
    }

.pragma aux(pop)
.pragma aux(pop)

_mm512_mask_ternarylogic_epi32 proto asmcall :abs, :word, :abs, :abs, :abs {
    vpternlogd  _1 {k1}, _3, _4, _5
    }
_mm512_maskz_ternarylogic_epi32 proto asmcall :word, :abs, :abs, :abs, :abs {
    vpternlogd  _2 {k1}{z}, _3, _4, _5
    }
_mm512_mask_ternarylogic_epi64 proto asmcall :abs, :byte, :abs, :abs, :abs {
    vpternlogq  _1 {k1}, _3, _4, _5
    }
_mm512_maskz_ternarylogic_epi64 proto asmcall :byte, :abs, :abs, :abs, :abs {
    vpternlogq  _2 {k1}{z}, _3, _4, _5
    }

_mm512_mask_conflict_epi32 proto asmcall :abs, :word, :abs {
    vpconflictd _1 {k1}, _3
    }
_mm512_maskz_conflict_epi32 proto asmcall :word, :abs {
    vpconflictd zmm0 {k1}{z}, _2
    }
_mm512_mask_conflict_epi64 proto asmcall :abs, :byte, :abs {
    vpconflictq _1 {k1}, _3
    }
_mm512_maskz_conflict_epi64 proto asmcall :byte, :abs {
    vpconflictq zmm0 {k1}{z}, _2
    }

_mm512_mask_lzcnt_epi32 proto asmcall :abs, :word, :abs {
    vplzcntd    _1 {k1}, _3
    }
_mm512_maskz_lzcnt_epi32 proto asmcall :word, :abs {
    vplzcntd    zmm0 {k1}{z}, _2
    }
_mm512_mask_lzcnt_epi64 proto asmcall :abs, :byte, :abs {
    vplzcntq    _1 {k1}, _3
    }
_mm512_maskz_lzcnt_epi64 proto asmcall :byte, :abs {
    vplzcntq    zmm0 {k1}{z}, _2
    }

_mm512_mask_avg_epu8 proto asmcall :abs, :qword, :abs, :abs {
    vpavgb      _1 {k1}, _3, _4
    }
_mm512_maskz_avg_epu8 proto asmcall :qword, :abs, :abs {
    vpavgb      zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_avg_epu16 proto asmcall :abs, :dword, :abs, :abs {
    vpavgw      _1 {k1}, _3, _4
    }
_mm512_maskz_avg_epu16 proto asmcall :dword, :abs, :abs {
    vpavgw      zmm0 {k1}{z}, _2, _3
    }

_mm512_sad_epu8 proto asmcall :abs, :abs {
    vpsadbw     _1, _1, _2
    }
_mm512_mask_dbsad_epu8  proto asmcall :abs, :dword, :abs, :abs, :abs {
    vdbpsadbw   _1 {k1}, _3, _4, _5
    }
_mm512_maskz_dbsad_epu8 proto asmcall :dword, :abs, :abs, :abs {
    vdbpsadbw   zmm0 {k1}, _2, _3, _4
    }

_mm512_mask_reduce_add_ps proto asmcall :word, :abs {
    vmovups         zmm1 {k1}{z}, _2
    vextractf32x8   ymm0, zmm1, 1
    vaddps          ymm2, ymm0, ymm1
    vextractf128    xmm1, ymm2, 1
    vaddps          xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vaddps          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vaddss          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_add_pd proto asmcall :byte, :abs {
    vmovupd         zmm1 {k1}{z}, _2
    vextractf64x4   ymm0, zmm1, 1
    vaddpd          ymm2, ymm0, ymm1
    vextractf64x2   xmm0, ymm2, 1
    vaddpd          xmm1, xmm0, xmm2
    vpsrldq         xmm0, xmm1, 8
    vaddsd          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_add_epi32 proto asmcall :word, :abs {
    vmovups         zmm1 {k1}{z}, _2
    vextracti32x8   ymm0, zmm1, 1
    vpaddd          ymm2, ymm0, ymm1
    vextracti128    xmm1, ymm2, 1
    vpaddd          xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpaddd          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpaddd          xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_add_epi64 proto asmcall :byte, :abs {
    vmovupd         zmm1 {k1}{z}, _2
    vextracti64x4   ymm0, zmm1, 1
    vpaddq          ymm2, ymm0, ymm1
    vextracti64x2   xmm0, ymm2, 1
    vpaddq          xmm1, xmm0, xmm2
    vpsrldq         xmm0, xmm1, 8
    vpaddq          xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }

_mm512_mask_reduce_mul_ps proto asmcall :word, :zword {
    vbroadcastss    zmm2, 3f800000r
    vmovups         zmm2 {k1}, _2
    vextractf32x8   ymm0, zmm2, 1
    vmulps          ymm2, ymm0, ymm2
    vextractf128    xmm1, ymm2, 1
    vmulps          xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vmulps          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vmulss          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_mul_pd proto asmcall :byte, :zword {
    vbroadcastsd    zmm2, 3ff0000000000000r
    vmovupd         zmm2 {k1}, _2
    vextractf64x4   ymm0, zmm2, 1
    vmulpd          ymm3, ymm0, ymm2
    vextractf64x2   xmm0, ymm3, 1
    vmulpd          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vmulsd          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_mul_epi32 proto asmcall :word, :zword {
    vpbroadcastd    zmm2, 0000000000000001r
    vmovups         zmm2 {k1}, _2
    vextracti32x8   ymm0, zmm2, 1
    vpmulld         ymm2, ymm0, ymm2
    vextracti128    xmm1, ymm2, 1
    vpmulld         xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpmulld         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpmulld         xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_mul_epi64 proto asmcall :byte, :zword {
    vpbroadcastd    zmm2, 0000000000000001r
    vmovupd         zmm2 {k1}, _2
    vextracti64x4   ymm0, zmm2, 1
    vpmuludq        ymm3, ymm0, ymm2
    vextracti64x2   xmm0, ymm3, 1
    vpmuludq        xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vpmuludq        xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }

_mm512_mask_reduce_min_ps proto asmcall :word, :zword {
    vbroadcastss    zmm2, 7f800000r
    vmovups         zmm2 {k1}, _2
    vextractf32x8   ymm0, zmm2, 1
    vminps          ymm2, ymm0, ymm2
    vextractf128    xmm1, ymm2, 1
    vminps          xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vminps          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vminss          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_min_pd proto asmcall :byte, :zword {
    vbroadcastsd    zmm2, 7ff0000000000000r
    vmovupd         zmm2 {k1}, _2
    vextractf64x4   ymm0, zmm2, 1
    vminpd          ymm3, ymm0, ymm2
    vextractf64x2   xmm0, ymm3, 1
    vminpd          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vminsd          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_min_epi32 proto asmcall :word, :zword {
    vpbroadcastd    zmm2, 000000007fffffffr
    vmovups         zmm2 {k1}, _2
    vextracti32x8   ymm0, zmm2, 1
    vpminsd         ymm2, ymm0, ymm2
    vextracti128    xmm1, ymm2, 1
    vpminsd         xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpminsd         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpminsd         xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_min_epi64 proto asmcall :byte, :zword {
    vpbroadcastq    zmm2, 7fffffffffffffffr
    vmovupd         zmm2 {k1}, _2
    vextracti64x4   ymm0, zmm2, 1
    vpminsq         ymm3, ymm0, ymm2
    vextracti64x2   xmm0, ymm3, 1
    vpminsq         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vpminsq         xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }
_mm512_mask_reduce_min_epu32 proto asmcall :word, :zword {
    vpbroadcastd    zmm2, 00000000ffffffffr
    vmovups         zmm2 {k1}, _2
    vextracti32x8   ymm0, zmm2, 1
    vpminud         ymm2, ymm0, ymm2
    vextracti128    xmm1, ymm2, 1
    vpminud         xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpminud         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpminud         xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_min_epu64 proto asmcall :byte, :zword {
    vpbroadcastq    zmm2, 0ffffffffffffffffr
    vmovupd         zmm2 {k1}, _2
    vextracti64x4   ymm0, zmm2, 1
    vpminuq         ymm3, ymm0, ymm2
    vextracti64x2   xmm0, ymm3, 1
    vpminuq         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vpminuq         xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }

_mm512_mask_reduce_max_ps proto asmcall :word, :zword {
    vbroadcastss    zmm2, 0ff800000r
    vmovups         zmm2 {k1}, _2
    vextractf32x8   ymm0, zmm2, 1
    vmaxps          ymm2, ymm0, ymm2
    vextractf128    xmm1, ymm2, 1
    vmaxps          xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vmaxps          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vmaxss          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_max_pd proto asmcall :byte, :zword {
    vbroadcastsd    zmm2, 0fff0000000000000r
    vmovupd         zmm2 {k1}, _2
    vextractf64x4   ymm0, zmm2, 1
    vmaxpd          ymm3, ymm0, ymm2
    vextractf64x2   xmm0, ymm3, 1
    vmaxpd          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vmaxsd          xmm0, xmm0, xmm1
    }
_mm512_mask_reduce_max_epi32 proto asmcall :word, :zword {
    vpbroadcastd    zmm2, 80000000r
    vmovups         zmm2 {k1}, _2
    vextracti32x8   ymm0, zmm2, 1
    vpmaxsd         ymm2, ymm0, ymm2
    vextracti128    xmm1, ymm2, 1
    vpmaxsd         xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpmaxsd         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpmaxsd         xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_max_epi64 proto asmcall :byte, :zword {
    vpbroadcastq    zmm2, 8000000000000000r
    vmovupd         zmm2 {k1}, _2
    vextracti64x4   ymm0, zmm2, 1
    vpmaxsq         ymm3, ymm0, ymm2
    vextracti64x2   xmm0, ymm3, 1
    vpmaxsq         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vpmaxsq         xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }
_mm512_mask_reduce_max_epu32 proto asmcall :word, :zword {
    vmovups         zmm1 {k1}{z}, _2
    vextracti32x8   ymm0, zmm1, 1
    vpmaxud         ymm2, ymm0, ymm1
    vextracti128    xmm1, ymm2, 1
    vpmaxud         xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpmaxud         xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpmaxud         xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_max_epu64 proto asmcall :byte, :zword {
    vmovupd         zmm1 {k1}{z}, _2
    vextracti64x4   ymm0, zmm1, 1
    vpmaxuq         ymm2, ymm0, ymm1
    vextracti64x2   xmm0, ymm2, 1
    vpmaxuq         xmm1, xmm0, xmm2
    vpsrldq         xmm0, xmm1, 8
    vpmaxuq         xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }

_mm512_mask_reduce_and_epi32 proto asmcall :word, :zword {
    vpbroadcastd    zmm2, 0ffffffffr
    vmovups         zmm2 {k1}, _2
    vextracti32x8   ymm0, zmm2, 1
    vpand           ymm2, ymm0, ymm2
    vextracti128    xmm1, ymm2, 1
    vpand           xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpand           xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpand           xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_and_epi64 proto asmcall :byte, :zword {
    vpbroadcastq    zmm2, 0ffffffffffffffffr
    vmovupd         zmm2 {k1}, _2
    vextracti64x4   ymm0, zmm2, 1
    vpandq          ymm3, ymm0, ymm2
    vextracti64x2   xmm0, ymm3, 1
    vpandq          xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 8
    vpandq          xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }

_mm512_mask_reduce_or_epi32 proto asmcall :word, :zword {
    vmovups         zmm1 {k1}{z}, _2
    vextracti32x8   ymm0, zmm1, 1
    vpor            ymm2, ymm0, ymm1
    vextracti128    xmm1, ymm2, 1
    vpor            xmm3, xmm1, xmm2
    vpsrldq         xmm0, xmm3, 8
    vpor            xmm1, xmm0, xmm3
    vpsrldq         xmm0, xmm1, 4
    vpor            xmm1, xmm0, xmm1
    vmovd           eax, xmm1
    }
_mm512_mask_reduce_or_epi64 proto asmcall :byte, :zword {
    vmovupd         zmm1 {k1}{z}, _2
    vextracti64x4   ymm0, zmm1, 1
    vporq           ymm2, ymm0, ymm1
    vextracti64x2   xmm0, ymm2, 1
    vporq           xmm1, xmm0, xmm2
    vpsrldq         xmm0, xmm1, 8
    vporq           xmm1, xmm0, xmm1
    vmovq           rax, xmm1
    }

_mm512_mask_reduce_round_ps proto asmcall :abs, :word, :abs, :abs, :abs {
    vreduceps   _1 {k1}, _3, _4
    }
_mm512_maskz_reduce_round_ps proto asmcall :word, :abs, :abs, :abs {
    vreduceps   zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_reduce_round_pd proto asmcall :abs, :byte, :abs, :abs, :abs {
    vreducepd   _1 {k1}, _3, _4
    }
_mm512_maskz_reduce_round_pd proto asmcall :byte, :abs, :abs, :abs {
    vreducepd   zmm0 {k1}{z}, _2, _3
    }

.pragma aux(pop)

_mm512_reduce_add_ps macro v1
    exitm<_mm512_mask_reduce_add_ps(_MM_K0_REG, v1)>
    endm
_mm512_reduce_add_pd macro v1
    exitm<_mm512_mask_reduce_add_pd(_MM_K0_REG, v1)>
    endm
_mm512_reduce_add_epi32 macro v1
    exitm<_mm512_mask_reduce_add_epi32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_add_epi64 macro v1
    exitm<_mm512_mask_reduce_add_epi64(_MM_K0_REG, v1)>
    endm

_mm512_reduce_mul_ps macro v1
    exitm<_mm512_mask_reduce_mul_ps(_MM_K0_REG, v1)>
    endm
_mm512_reduce_mul_pd macro v1
    exitm<_mm512_mask_reduce_mul_pd(_MM_K0_REG, v1)>
    endm
_mm512_reduce_mul_epi32 macro v1
    exitm<_mm512_mask_reduce_mul_epi32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_mul_epi64 macro v1
    exitm<_mm512_mask_reduce_mul_epi64(_MM_K0_REG, v1)>
    endm

_mm512_reduce_min_ps macro v1
    exitm<_mm512_mask_reduce_min_ps(_MM_K0_REG, v1)>
    endm
_mm512_reduce_min_pd macro v1
    exitm<_mm512_mask_reduce_min_pd(_MM_K0_REG, v1)>
    endm
_mm512_reduce_min_epi32 macro v1
    exitm<_mm512_mask_reduce_min_epi32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_min_epi64 macro v1
    exitm<_mm512_mask_reduce_min_epi64(_MM_K0_REG, v1)>
    endm
_mm512_reduce_min_epu32 macro v1
    exitm<_mm512_mask_reduce_min_epu32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_min_epu64 macro v1
    exitm<_mm512_mask_reduce_min_epu64(_MM_K0_REG, v1)>
    endm

_mm512_reduce_max_ps macro v1
    exitm<_mm512_mask_reduce_max_ps(_MM_K0_REG, v1)>
    endm
_mm512_reduce_max_pd macro v1
    exitm<_mm512_mask_reduce_max_pd(_MM_K0_REG, v1)>
    endm
_mm512_reduce_max_epi32 macro v1
    exitm<_mm512_mask_reduce_max_epi32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_max_epi64 macro v1
    exitm<_mm512_mask_reduce_max_epi64(_MM_K0_REG, v1)>
    endm
_mm512_reduce_max_epu32 macro v1
    exitm<_mm512_mask_reduce_max_epu32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_max_epu64 macro v1
    exitm<_mm512_mask_reduce_max_epu64(_MM_K0_REG, v1)>
    endm

_mm512_reduce_and_epi32 macro v1
    exitm<_mm512_mask_reduce_and_epi32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_and_epi64 macro v1
    exitm<_mm512_mask_reduce_and_epi64(_MM_K0_REG, v1)>
    endm

_mm512_reduce_or_epi32 macro v1
    exitm<_mm512_mask_reduce_or_epi32(_MM_K0_REG, v1)>
    endm
_mm512_reduce_or_epi64 macro v1
    exitm<_mm512_mask_reduce_or_epi64(_MM_K0_REG, v1)>
    endm

_mm512_mask_roundscale_round_pd macro v1, m, v2, i3, e4
    exitm<_mm512_mask2i(vrndscalepd, 4, v1, m, v2, i3, e4)>
    endm
_mm512_maskz_roundscale_round_pd macro m, v1, i3, e4
    exitm<_mm512_maskz2ir(vrndscalepd, 4, m, v1, i3, e4)>
    endm
_mm512_mask_roundscale_round_ps macro v1, m, v2, i3, e4
    exitm<_mm512_mask2i(vrndscaleps, 3, v1, m, v2, i3, e4)>
    endm
_mm512_maskz_roundscale_round_ps macro m, v1, i3, e4
    exitm<_mm512_maskz2ir(vrndscaleps, 3, m, v1, i3, e4)>
    endm

_mm512_mask_scalef_round_pd macro v1, m, v2, v3, r
    exitm<_mm512_mask(vscalefpd, 4, v1, m, v2, v3, r)>
    endm
_mm512_maskz_scalef_round_pd macro m, v1, v2, r
    exitm<_mm512_maskz(vscalefpd, 4, m, v1, v2, r)>
    endm
_mm512_mask_scalef_round_ps macro v1, m, v2, v3, r
    exitm<_mm512_mask(vscalefps, 3, v1, m, v2, v3, r)>
    endm
_mm512_maskz_scalef_round_ps macro m, v1, v2, r
    exitm<_mm512_maskz(vscalefps, 3, m, v1, v2, r)>
    endm

.pragma aux(k1, k1)

_mm512_mask_fixupimm_round_pd proto asmcall :abs, :byte, :abs, :abs, :abs, :abs {
    vfixupimmpd _1 {k1}, _3, _4, _5 _MM_SAE(_6)
    }
_mm512_maskz_fixupimm_round_pd  proto asmcall :byte, :abs, :abs, :abs, :abs, :abs {
    vfixupimmpd _2 {k1}{z}, _3, _4, _5 _MM_SAE(_6)
    }
_mm512_mask_fixupimm_round_ps   proto asmcall :abs, :word, :abs, :abs, :abs, :abs {
    vfixupimmps _1 {k1}, _3, _4, _5 _MM_SAE(_6)
    }
_mm512_maskz_fixupimm_round_ps  proto asmcall :word, :abs, :abs, :abs, :abs, :abs {
    vfixupimmps _2 {k1}{z}, _3, _4, _5 _MM_SAE(_6)
    }

_mm512_stream_pd proto __vdecl :ptr, :abs {
    vmovntpd    [_1], _2
    }
_mm512_stream_ps proto __vdecl :ptr, :abs {
    vmovntps    [_1], _2
    }
_mm512_stream_si512 proto __vdecl :ptr, :abs {
    vmovntdq    [_1], _2
    }
_mm512_stream_load_si512 proto __vdecl :ptr {
    vmovntdqa   zmm0, [_1]
    }

_mm512_castpd512_pd128 macro v1
    retm<@CatStr(<xmm>,@SubStr(zmm,4))>
    endm
_mm512_castps512_ps128 macro v1
    retm<@CatStr(<xmm>,@SubStr(zmm,4))>
    endm
_mm512_castsi512_si128 macro v1
    retm<@CatStr(<xmm>,@SubStr(zmm,4))>
    endm
_mm512_castsi128_si512 macro v1
    retm<@CatStr(<zmm>,@SubStr(xmm,4))>
    endm

_mm512_mask_exp2a23_round_ps proto asmcall :abs, :word, :abs, :abs {
    vexp2ps     _1 {k1}, _3 _MM_SAE(_4)
    }
_mm512_maskz_exp2a23_round_ps proto asmcall :word, :abs, :abs {
    vexp2ps     zmm0 {k1}, _2 _MM_SAE(_3)
    }
_mm512_mask_exp2a23_round_pd proto asmcall :abs, :byte, :abs, :abs {
    vexp2pd     _1 {k1}, _3 _MM_SAE(_4)
    }
_mm512_maskz_exp2a23_round_pd proto asmcall :byte, :abs, :abs {
    vexp2pd     zmm0 {k1}, _2 _MM_SAE(_3)
    }

_mm512_mask_fpclass_ps_mask proto asmcall :word, :abs, :abs {
    vfpclassps  k2 {k1}, _2, _3
    kmovw       eax,k2
    }
_mm512_mask_fpclass_pd_mask proto asmcall :byte, :abs, :abs {
    vfpclasspd  k2 {k1}, _2, _3
    kmovb       eax,k2
    }

_mm512_mask_range_round_ps proto asmcall :abs, :word, :abs, :abs, :abs, :abs {
    vrangeps    _1 {k1}, _3, _4, _5 _MM_SAE(_6)
    }
_mm512_maskz_range_round_ps proto asmcall :word, :abs, :abs, :abs, :abs {
    vrangeps    zmm0 {k1}, _2, _3, _4 _MM_SAE(_5)
    }
_mm512_mask_range_round_pd proto asmcall :abs, :byte, :abs, :abs, :abs, :abs {
    vrangepd    _1 {k1}, _3, _4, _5 _MM_SAE(_6)
    }
_mm512_maskz_range_round_pd proto asmcall :byte, :abs, :abs, :abs, :abs {
    vrangepd    zmm0 {k1}, _2, _3, _4 _MM_SAE(_5)
    }

_mm512_mask_madd_epi16 proto asmcall :abs, :word, :abs, :abs {
    vpmaddwd    _1 {k1}, _3, _4
    }
_mm512_maskz_madd_epi16 proto asmcall :word, :abs, :abs {
    vpmaddwd    zmm0 {k1}{z}, _2, _3
    }
_mm512_mask_maddubs_epi16 proto asmcall :abs, :dword, :abs, :abs {
    vpmaddubsw  _1 {k1}, _3, _4
    }
_mm512_maskz_maddubs_epi16 proto asmcall :dword, :abs, :abs {
    vpmaddubsw  zmm0 {k1}{z}, _2, _3
    }

_mm512_mask_packs_epi16 proto asmcall :abs, :qword, :abs, :abs {
    vpacksswb   _1 {k1}, _3, _4
    }
_mm512_maskz_packs_epi16 proto asmcall :qword, :abs, :abs {
    vpacksswb   zmm0 {k1}, _2, _3
    }
_mm512_mask_packs_epi32 proto asmcall :abs, :dword, :abs, :abs {
    vpackssdw   _1 {k1}, _3, _4
    }
_mm512_maskz_packs_epi32 proto asmcall :dword, :abs, :abs {
    vpackssdw   zmm0 {k1}, _2, _3
    }
_mm512_mask_packus_epi16 proto asmcall :abs, :qword, :abs, :abs {
    vpackuswb   _1 {k1}, _3, _4
    }
_mm512_maskz_packus_epi16 proto asmcall :qword, :abs, :abs {
    vpackuswb   zmm0 {k1}, _2, _3
    }
_mm512_mask_packus_epi32 proto asmcall :abs, :dword, :abs, :abs {
    vpackusdw   _1 {k1}, _3, _4
    }
_mm512_maskz_packus_epi32 proto asmcall :dword, :abs, :abs {
    vpackusdw   zmm0 {k1}, _2, _3
    }

_mm512_mask_cmp_epi8_mask proto asmcall :qword, :abs, :abs, :abs {
    vpcmpb      k2 {k1}, _2, _3, _4
    kmovq       rax,k2
    }
_mm512_mask_cmp_epi16_mask proto asmcall :dword, :abs, :abs, :abs {
    vpcmpw      k2 {k1}, _2, _3, _4
    kmovd       eax,k2
    }
_mm512_mask_cmp_epi32_mask proto asmcall :word, :abs, :abs, :abs {
    vpcmpd      k2 {k1}, _2, _3, _4
    kmovw       eax,k2
    }
_mm512_mask_cmp_epi64_mask proto asmcall :byte, :abs, :abs, :abs {
    vpcmpuq     k2 {k1}, _2, _3, _4
    kmovb       eax,k2
    }

_mm512_mask_cmp_epu8_mask proto asmcall :qword, :abs, :abs, :abs {
    vpcmpub     k2 {k1}, _2, _3, _4
    kmovq       rax,k2
    }
_mm512_mask_cmp_epu16_mask proto asmcall :dword, :abs, :abs, :abs {
    vpcmpuw     k2 {k1}, _2, _3, _4
    kmovd       eax,k2
    }
_mm512_mask_cmp_epu32_mask proto asmcall :word, :abs, :abs, :abs {
    vpcmpud     k2 {k1}, _2, _3, _4
    kmovw       eax,k2
    }
_mm512_mask_cmp_epu64_mask proto asmcall :byte, :abs, :abs, :abs {
    vpcmpuq     k2 {k1}, _2, _3, _4
    kmovb       eax,k2
    }

_mm512_mask_cmp_round_ps_mask proto asmcall :word, :abs, :abs, :abs, :abs {
    vcmpps      k2 {k1}, _2, _3, _4 _MM_SAE(_5)
    kmovw       eax,k2
    }

_mm512_mask_cmp_round_pd_mask proto asmcall :byte, :abs, :abs, :abs, :abs {
    vcmppd      k2 {k1}, _2, _3, _4 _MM_SAE(_5)
    kmovb       eax,k2
    }

_mm512_mask_test_epi8_mask proto asmcall :qword, :abs, :abs {
    vptestmb    k2 {k1}, _2, _3
    kmovq       rax,k2
    }
_mm512_mask_test_epi16_mask proto asmcall :dword, :abs, :abs {
    vptestmw    k2 {k1}, _2, _3
    kmovd       eax,k2
    }
_mm512_mask_test_epi32_mask proto asmcall :word, :abs, :abs {
    vptestmd    k2 {k1}, _2, _3
    kmovw       eax,k2
    }
_mm512_mask_test_epi64_mask proto asmcall :byte, :abs, :abs {
    vptestmq    k2 {k1}, _2, _3
    kmovb       eax,k2
    }

_mm512_mask_testn_epi8_mask proto asmcall :qword, :abs, :abs {
    vptestnmb   k2 {k1}, _2, _3
    kmovq       rax,k2
    }
_mm512_mask_testn_epi16_mask proto asmcall :dword, :abs, :abs {
    vptestnmw   k2 {k1}, _2, _3
    kmovd       eax,k2
    }
_mm512_mask_testn_epi32_mask proto asmcall :word, :abs, :abs {
    vptestnmd   k2 {k1}, _2, _3
    kmovw       eax,k2
    }
_mm512_mask_testn_epi64_mask proto asmcall :byte, :abs, :abs {
    vptestnmq   k2 {k1}, _2, _3
    kmovb       eax,k2
    }

.pragma aux(pop)
.pragma aux(k1, k2)

_mm512_kunpackb proto asmcall :word, :word {
    kunpckbw    k2,k1,k2
    kmovw       eax,k2
    }
_mm512_kunpackw proto asmcall :dword, :dword {
    kunpckwd    k2,k1,k2
    kmovd       eax,k2
    }
_mm512_kunpackd proto asmcall :qword, :qword {
    kunpckdq    k2,k1,k2
    kmovq       rax,k2
    }

_mm512_testz_and_mask8 proto asmcall :byte, :byte {
    ktestb      k1, k2
    sete        al
    }
_mm512_testz_and_mask16 proto asmcall :word, :word {
    ktestw      k1, k2
    sete        al
    }
_mm512_testz_and_mask32 proto asmcall :dword, :dword {
    ktestd      k1, k2
    sete        al
    }
_mm512_testz_and_mask64 proto asmcall :qword, :qword {
    ktestq      k1, k2
    sete        al
    }
_mm512_testz_andn_mask8 proto asmcall :byte, :byte {
    ktestb      k1, k2
    setb        al
    }
_mm512_testz_andn_mask16 proto asmcall :word, :word {
    ktestw      k1, k2
    setb        al
    }
_mm512_testz_andn_mask32 proto asmcall :dword, :dword {
    ktestd      k1, k2
    setb        al
    }
_mm512_testz_andn_mask64 proto asmcall :qword, :qword {
    ktestq      k1, k2
    setb        al
    }
_mm512_testz_or_mask8 proto asmcall :byte, :byte {
    kortestb    k1, k2
    sete        al
    }
_mm512_testz_or_mask16 proto asmcall :word, :word {
    kortestw    k1, k2
    sete        al
    }
_mm512_testz_or_mask32 proto asmcall :dword, :dword {
    kortestd    k1, k2
    sete        al
    }
_mm512_testz_or_mask64 proto asmcall :qword, :qword {
    kortestq    k1, k2
    sete        al
    }
_mm512_testz_nor_mask8 proto asmcall :byte, :byte {
    kortestb    k1, k2
    setb        al
    }
_mm512_testz_nor_mask16 proto asmcall :word, :word {
    kortestw    k1, k2
    setb        al
    }
_mm512_testz_nor_mask32 proto asmcall :dword, :dword {
    kortestd    k1, k2
    setb        al
    }
_mm512_testz_nor_mask64 proto asmcall :qword, :qword {
    kortestq    k1, k2
    setb        al
    }

.pragma aux(pop)

.pragma aux(eax, k1, ecx, edx)

_mm512_mask_i32gather_ps proto asmcall :abs, :word, :abs, :ptr, :abs {
    vgatherdps  _1 {k1},[_4+_3*_5]
    }
_mm512_mask_i32gather_pd proto asmcall :abs, :byte, :abs, :ptr, :abs {
    vgatherdpd  _1 {k1},[_4+_3*_5]
    }
_mm512_mask_i32gather_epi32 proto asmcall :abs, :word, :abs, :ptr, :abs {
    vpgatherdd  _1 {k1},[_4+_3*_5]
    }
_mm512_mask_i32gather_epi64 proto asmcall :abs, :byte, :abs, :ptr, :abs {
    vpgatherdq  _1 {k1},[_4+_3*_5]
    }
_mm512_mask_i64gather_ps proto asmcall :abs, :byte, :abs, :ptr, :abs {
    vgatherqps  ymm0 {k1},[_4+_3*_5]
    }
_mm512_mask_i64gather_pd proto asmcall :abs, :byte, :abs, :ptr, :abs {
    vgatherqpd  _1 {k1},[_4+_3*_5]
    }
_mm512_mask_i64gather_epi32 proto asmcall :abs, :byte, :abs, :ptr, :abs {
    vpgatherqd  _1 {k1},[_4+_3*_5]
    }
_mm512_mask_i64gather_epi64 proto asmcall :abs, :byte, :abs, :ptr, :abs {
    vpgatherqq  _1 {k1},[_4+_3*_5]
    }

_mm512_mask_i32scatter_ps proto asmcall :ptr, :word, :abs, :abs, :abs {
    vscatterdps [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i32scatter_pd proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vscatterdpd [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i32scatter_epi32 proto asmcall :ptr, :word, :abs, :abs, :abs {
    vpscatterdd [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i32scatter_epi64 proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vpscatterdq [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i64scatter_ps proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vscatterqps [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i64scatter_pd proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vscatterqpd [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i64scatter_epi32 proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vpscatterqd [_1+_3*_5] {k1}, _4
    }
_mm512_mask_i64scatter_epi64 proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vpscatterqq [_1+_3*_5] {k1}, _4
    }

_mm512_mask_prefetch_i32gather_ps proto asmcall :abs, :word, :ptr, :abs, :abs {
    vgatherpf0dps [_3+_1*_4] {k1}
    }
_mm512_mask_prefetch_i32gather_pd proto asmcall :abs, :byte, :ptr, :abs, :abs {
    vgatherpf0dpd [_3+_1*_4] {k1}
    }
_mm512_mask_prefetch_i64gather_ps proto asmcall :abs, :byte, :ptr, :abs, :abs {
    vgatherpf0qps [_3+_1*_4] {k1}
    }
_mm512_mask_prefetch_i64gather_pd proto asmcall :abs, :byte, :ptr, :abs, :abs {
    vgatherpf0qpd [_3+_1*_4] {k1}
    }
_mm512_mask_prefetch_i32scatter_ps proto asmcall :ptr, :word, :abs, :abs, :abs {
    vscatterpf0dps [_1+_3*_4] {k1}
    }
_mm512_mask_prefetch_i32scatter_pd proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vscatterpf0dpd [_1+ymm2*_4] {k1}
    }
_mm512_mask_prefetch_i64scatter_pd proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vscatterpf0qpd [_1+_3*_4] {k1}
    }
_mm512_mask_prefetch_i64scatter_ps proto asmcall :ptr, :byte, :abs, :abs, :abs {
    vscatterpf0qps [_1+_3*_4] {k1}
    }

.pragma aux(pop)

_mm512_i32gather_ps macro v1, p, i
    exitm<_mm512_mask_i32gather_ps(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i32gather_pd macro v1, p, i
    exitm<_mm512_mask_i32gather_pd(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i32gather_epi32 macro v1, p, i
    exitm<_mm512_mask_i32gather_epi32(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i32gather_epi64 macro v1, p, i
    exitm<_mm512_mask_i32gather_epi64(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i64gather_ps macro v1, p, i
    exitm<_mm512_mask_i64gather_ps(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i64gather_pd macro v1, p, i
    exitm<_mm512_mask_i64gather_pd(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i64gather_epi32 macro v1, p, i
    exitm<_mm512_mask_i64gather_epi32(zmm0, _MM_K0_REG, v1, p, i)>
    endm
_mm512_i64gather_epi64 macro v1, p, i
    exitm<_mm512_mask_i64gather_epi64(zmm0, _MM_K0_REG, v1, p, i)>
    endm

_mm512_i32scatter_ps macro p, v1, v2, i
    exitm<_mm512_mask_i32scatter_ps(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i32scatter_pd macro p, v1, v2, i
    exitm<_mm512_mask_i32scatter_pd(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i32scatter_epi32 macro p, v1, v2, i
    exitm<_mm512_mask_i32scatter_epi32(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i32scatter_epi64 macro p, v1, v2, i
    exitm<_mm512_mask_i32scatter_epi64(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i64scatter_ps macro p, v1, v2, i
    exitm<_mm512_mask_i64scatter_ps(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i64scatter_pd macro p, v1, v2, i
    exitm<_mm512_mask_i64scatter_pd(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i64scatter_epi32 macro p, v1, v2, i
    exitm<_mm512_mask_i64scatter_epi32(p, _MM_K0_REG, v1, v2, i)>
    endm
_mm512_i64scatter_epi64 macro p, v1, v2, i
    exitm<_mm512_mask_i64scatter_epi64(p, _MM_K0_REG, v1, v2, i)>
    endm


_mm512_prefetch_i32gather_ps macro v1, p, scale, hint
    exitm<_mm512_mask_prefetch_i32gather_ps(v1, _MM_K0_REG, p, scale, hint)>
    endm
_mm512_prefetch_i32gather_pd macro v1, p, scale, hint
    exitm<_mm512_mask_prefetch_i32gather_pd(v1, _MM_K0_REG, p, scale, hint)>
    endm
_mm512_prefetch_i64gather_ps macro v1, p, scale, hint
    exitm<_mm512_mask_prefetch_i64gather_ps(v1, _MM_K0_REG, p, scale, hint)>
    endm
_mm512_prefetch_i64gather_pd macro v1, p, scale, hint
    exitm<_mm512_mask_prefetch_i64gather_pd(v1, _MM_K0_REG, p, scale, hint)>
    endm

_mm512_prefetch_i32scatter_ps macro p, v1, scale, hint
    exitm<_mm512_mask_prefetch_i32scatter_ps(p, _MM_K0_REG, v1, scale, hint)>
    endm
_mm512_prefetch_i32scatter_pd macro p, v1, scale, hint
    exitm<_mm512_mask_prefetch_i32scatter_pd(p, _MM_K0_REG, v1, scale, hint)>
    endm
_mm512_prefetch_i64scatter_ps macro p, v1, scale, hint
    exitm<_mm512_mask_prefetch_i64scatter_ps(p, _MM_K0_REG, v1, scale, hint)>
    endm
_mm512_prefetch_i64scatter_pd macro p, v1, scale, hint
    exitm<_mm512_mask_prefetch_i64scatter_pd(p, _MM_K0_REG, v1, scale, hint)>
    endm

_mm512_cvtpslo_pd macro v2, v1:=<zmm0>
    exitm<_mm512_mask2(vcvtps2pd, 4, v1, _MM_K0_REG, v2)>
    endm
_mm512_mask_cvtpslo_pd macro v1, m, v2
    exitm<_mm512_mask2(vcvtps2pd, 4, v1, m, v2)>
    endm
_mm512_cvtepi32lo_pd macro v2, v1:=<zmm0>
    exitm<_mm512_mask2(vcvtdq2pd, 4, v1, _MM_K0_REG, v2)>
    endm

_mm512_mask_cvtepi32lo_pd macro v1, m, v2
    exitm<_mm512_mask2(vcvtdq2pd, 4, v1, m, v2)>
    endm
_mm512_cvtepu32lo_pd macro v2, v1:=<zmm0>
    exitm<_mm512_mask2(vcvtudq2pd, 4, v1, _MM_K0_REG, v2)>
    endm
_mm512_mask_cvtepu32lo_pd macro v1, m, v2
    exitm<_mm512_mask2(vcvtudq2pd, 4, v1, m, v2)>
    endm
_mm512_mask_cvtepi32_pd macro v1, m, v2
    exitm<_mm512_mask2(vcvtdq2pd, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi32_pd macro m, v1
    exitm<_mm512_maskz2(vcvtdq2pd, 4, m, v1)>
    endm
_mm512_mask_cvtepu32_pd macro v1, m, v2
    exitm<_mm512_mask2(vcvtudq2pd, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepu32_pd macro m, v1
    exitm<_mm512_maskz2(vcvtudq2pd, 4, m, v1)>
    endm

_mm512_mask_cvt_roundepi32_ps macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtdq2ps, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundepi32_ps macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtdq2ps, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundepu32_ps macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtudq2ps, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundepu32_ps macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtudq2ps, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundph_ps macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtph2ps, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundph_ps macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtph2ps, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundps_ph macro v1, m, v2, i3, r
    exitm<_mm512_mask2i(vcvtps2ph, 3, v1, m, v2, i3, r)>
    endm
_mm512_maskz_cvt_roundps_ph macro m, v2, i3, v1:=<ymm0>
    exitm<_mm512_maskz2i(vcvtps2ph, 3, m, v2, i3, v1)>
    endm
_mm512_mask_cvt_roundepi64_ps macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtqq2ps, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundepi64_ps macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtqq2ps, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundepu64_ps macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtuqq2ps, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundepu64_ps macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtuqq2ps, 3, m, v1, v2, r)>
    endm

_mm512_mask_cvtepi8_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsxbd, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtepi8_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovsxbd, 3, m, v1)>
    endm
_mm512_mask_cvtepi8_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsxbq, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi8_epi64 macro m, v1
    exitm<_mm512_maskz2(vpmovsxbq, 4, m, v1)>
    endm
_mm512_mask_cvtepi16_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsxbd, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtepi16_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovsxbd, 3, m, v1)>
    endm
_mm512_mask_cvtepi16_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsxbq, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi16_epi64 macro m, v1
    exitm<_mm512_maskz2(vpmovsxbq, 4, m, v1)>
    endm
_mm512_mask_cvtepi32_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vpmovdb, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtepi32_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovdb, 3, m, v1)>
    endm

_mm512_mask_storeu macro inst, cm, p, m, v1
  local mask
    _mm512_loadk mask, 0, cm, m
    _mm512_loadp(p)
    inst [rax] mask, v1
    exitm<>
    endm
_mm512_mask_cvtepi32_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovdb, 3, p, m, v1)>
    endm
_mm512_mask_cvtsepi32_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovsdb, 3, p, m, v1)>
    endm
_mm512_mask_cvtusepi32_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovusdb, 3, p, m, v1)>
    endm
_mm512_mask_cvtepi32_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovdw, 3, p, m, v1)>
    endm
_mm512_mask_cvtsepi32_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovsdw, 3, p, m, v1)>
    endm
_mm512_mask_cvtusepi32_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovusdw, 3, p, m, v1)>
    endm
_mm512_mask_cvtepi64_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovqb, 4, p, m, v1)>
    endm
_mm512_mask_cvtsepi64_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovsqb, 4, p, m, v1)>
    endm
_mm512_mask_cvtusepi64_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovusqb, 4, p, m, v1)>
    endm
_mm512_mask_cvtepi64_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovqw, 4, p, m, v1)>
    endm
_mm512_mask_cvtsepi64_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovsqw, 4, p, m, v1)>
    endm
_mm512_mask_cvtusepi64_storeu_epi16 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovusqw, 4, p, m, v1)>
    endm
_mm512_mask_cvtepi64_storeu_epi32 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovqd, 4, p, m, v1)>
    endm
_mm512_mask_cvtsepi64_storeu_epi32 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovsqd, 4, p, m, v1)>
    endm
_mm512_mask_cvtusepi64_storeu_epi32 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovusqd, 4, p, m, v1)>
    endm
_mm512_mask_cvtepi16_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovwb, 2, p, m, v1)>
    endm
_mm512_mask_cvtsepi16_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovswb, 2, p, m, v1)>
    endm
_mm512_mask_cvtusepi16_storeu_epi8 macro p, m, v1
    exitm<_mm512_mask_storeu(vpmovuswb, 2, p, m, v1)>
    endm

_mm512_mask_cvtsepi32_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsdb, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtsepi32_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovsdb, 3, m, v1)>
    endm
_mm512_mask_cvtusepi32_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vpmovusdb, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtusepi32_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovusdb, 3, m, v1)>
    endm
_mm512_mask_cvtepi32_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovdw, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtepi32_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovdw, 3, m, v1)>
    endm
_mm512_mask_cvtsepi32_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsdw, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtsepi32_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovsdw, 3, m, v1)>
    endm
_mm512_mask_cvtusepi32_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovusdw, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtusepi32_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovusdw, 3, m, v1)>
    endm
_mm512_mask_cvtepi32_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsxdq, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi32_epi64 macro m, v1
    exitm<_mm512_maskz2(vpmovsxdq, 4, m, v1)>
    endm
_mm512_mask_cvtepi64_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vpmovqb, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi64_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovqb, 4, m, v1)>
    endm
_mm512_mask_cvtsepi64_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsqb, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtsepi64_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovsqb, 4, m, v1)>
    endm
_mm512_mask_cvtusepi64_epi8 macro v1, m, v2
    exitm<_mm512_mask2(vpmovusqb, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtusepi64_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovusqb, 4, m, v1)>
    endm
_mm512_mask_cvtepi64_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovqw, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi64_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovqw, 4, m, v1)>
    endm
_mm512_mask_cvtsepi64_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsqw, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtsepi64_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovsqw, 4, m, v1)>
    endm
_mm512_mask_cvtusepi64_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovusqw, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtusepi64_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovusqw, 4, m, v1)>
    endm
_mm512_mask_cvtepi64_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovqd, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepi64_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovqd, 4, m, v1)>
    endm
_mm512_mask_cvtsepi64_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovsqd, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtsepi64_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovsqd, 4, m, v1)>
    endm
_mm512_mask_cvtusepi64_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovusqd, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtusepi64_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovusqd, 4, m, v1)>
    endm
_mm512_mask_cvtepu8_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovzxbd, 1, v1, m, v2)>
    endm
_mm512_maskz_cvtepu8_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovzxbd, 1, m, v1)>
    endm
_mm512_mask_cvtepu8_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vpmovzxbq, 1, v1, m, v2)>
    endm
_mm512_maskz_cvtepu8_epi64 macro m, v1
    exitm<_mm512_maskz2(vpmovzxbq, 1, m, v1)>
    endm
_mm512_mask_cvtepu16_epi32 macro v1, m, v2
    exitm<_mm512_mask2(vpmovzxwd, 3, v1, m, v2)>
    endm
_mm512_maskz_cvtepu16_epi32 macro m, v1
    exitm<_mm512_maskz2(vpmovzxwd, 3, m, v1)>
    endm
_mm512_mask_cvtepu16_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vpmovzxwq, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepu16_epi64 macro m, v1
    exitm<_mm512_maskz2(vpmovzxwq, 4, m, v1)>
    endm
_mm512_mask_cvtepu32_epi64 macro v1, m, v2
    exitm<_mm512_mask2(vpmovzxdq, 4, v1, m, v2)>
    endm
_mm512_maskz_cvtepu32_epi64 macro m, v1
    exitm<_mm512_maskz2(vpmovzxdq, 4, m, v1)>
    endm

_mm512_mask_cvt_roundps_epi32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtps2dq, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundps_epi32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtps2dq, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundps_epi32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttps2dq, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundps_epi32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttps2dq, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundps_epu32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtps2udq, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundps_epu32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtps2udq, 3, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundps_epu32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttps2udq, 3, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundps_epu32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttps2udq, 3, m, v1, v2, r)>
    endm

_mm512_mask_cvt_roundpd_epi32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtpd2dq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundpd_epi32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtpd2dq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundpd_epi32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttpd2dq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundpd_epi32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttpd2dq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundpd_epu32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtpd2udq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundpd_epu32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtpd2udq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundpd_epu32 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttpd2udq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundpd_epu32 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttpd2udq, 4, m, v1, v2, r)>
    endm

_mm512_mask_cvtepi8_epi16 macro v1, m, v2
    exitm<_mm512_mask2(vpmovzxbw, 2, v1, m, v2)>
    endm
_mm512_maskz_cvtepi8_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovzxbw, 2, m, v1)>
    endm
_mm512_mask_cvtepu8_epi16 macro v1, m, v2
    exitm<_mm512_maskz2(vpmovzxbw, 2, m, v1)>
    endm
_mm512_maskz_cvtepu8_epi16 macro m, v1
    exitm<_mm512_maskz2(vpmovzxbw, 2, m, v1)>
    endm
_mm512_mask_cvtepi16_epi8 macro v1, m, v2
    exitm<_mm512_maskz2(vpmovwb, 2, m, v1)>
    endm
_mm512_maskz_cvtepi16_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovwb, 2, m, v1)>
    endm
_mm512_mask_cvtsepi16_epi8 macro v1, m, v2
    exitm<_mm512_maskz2(vpmovswb, 2, m, v1)>
    endm
_mm512_maskz_cvtsepi16_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovswb, 2, m, v1)>
    endm
_mm512_mask_cvtusepi16_epi8 macro v1, m, v2
    exitm<_mm512_maskz2(vpmovuswb, 2, m, v1)>
    endm
_mm512_maskz_cvtusepi16_epi8 macro m, v1
    exitm<_mm512_maskz2(vpmovuswb, 2, m, v1)>
    endm

_mm512_mask_cvt_roundepi64_pd macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtqq2pd, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundepi64_pd macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtqq2pd, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundepu64_pd macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtuqq2pd, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundepu64_pd macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtuqq2pd, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundpd_epi64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtpd2qq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundpd_epi64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtpd2qq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundpd_epu64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtpd2uqq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundpd_epu64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtpd2uqq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundpd_epi64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttpd2qq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundpd_epi64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttpd2qq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundpd_epu64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttpd2uqq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundpd_epu64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttpd2uqq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundps_epi64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtps2qq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundps_epi64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtps2qq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvt_roundps_epu64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvtps2uqq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvt_roundps_epu64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvtps2uqq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundps_epi64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttps2qq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundps_epi64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttps2qq, 4, m, v1, v2, r)>
    endm
_mm512_mask_cvtt_roundps_epu64 macro v1, m, v2, r
    exitm<_mm512_mask2(vcvttps2uqq, 4, v1, m, v2, r)>
    endm
_mm512_maskz_cvtt_roundps_epu64 macro m, v2, r, v1:=<zmm0>
    exitm<_mm512_maskz2(vcvttps2uqq, 4, m, v1, v2, r)>
    endm

_mm512_setzero_epi32 macro z:=<zmm0>
    vxorps z,z,z
    retm<z>
    endm

_mm512_set1_epi8 macro e1
        exitm<_mm512_maskz_set1_epi8(_MM_K0_REG64, e1)>
        endm

_mm512_set1_epi16 macro e1
        exitm<_mm512_maskz_set1_epi16(_MM_K0_REG64, e1)>
        endm

_mm512_set1_epi32 macro e1
        exitm<_mm512_maskz_set1_epi32(_MM_K0_REG, e1)>
        endm

_mm512_set1_epi64 macro e1
        exitm<_mm512_maskz_set1_epi64(_MM_K0_REG, e1)>
        endm

_mm512_set_1to8_pq macro x
        exitm<_mm512_set1_epi64(x)>
        endm
_mm512_set_1to8_epi64 macro x
        exitm<_mm512_set1_epi64(x)>
        endm
_mm512_set_1to16_pi macro x
        exitm<_mm512_set1_epi32(x)>
        endm
_mm512_set_1to16_epi32 macro x
        exitm<_mm512_set1_epi32(x)>
        endm
_mm512_set4_epi64 macro args:vararg
        exitm<_mm512_set_epi64(args, args)>
        endm

_mm512_set4_epi32 macro args:vararg
        exitm<_mm512_set_epi32(args, args, args, args)>
        endm

_mm512_setr4_epi64 macro args:vararg
        exitm<{ args, args }>
        endm
_mm512_set_4to8_pq macro args:vararg
        exitm<_mm512_setr4_epi64(args)>
        endm
_mm512_set_4to8_epi64 macro args:vararg
        exitm<_mm512_setr4_epi64(args)>
        endm
_mm512_setr4_epi32 macro args:vararg
        exitm<{ args }>
        endm
_mm512_set_4to16_pi macro args:vararg
        exitm<_mm512_setr4_epi32(args)>
        endm
_mm512_set_4to16_epi32 macro args:vararg
        exitm<_mm512_setr4_epi32(args)>
        endm
_mm512_set_16to16_pi macro args:vararg
        exitm<_mm512_set_epi32(args)>
        endm
_mm512_set_16to16_epi32 macro args:vararg
        exitm<_mm512_set_epi32(args)>
        endm
_mm512_setr_epi32 macro args:vararg
        exitm<{ args }>
        endm
_mm512_setr_epi64 macro args:vararg
        exitm<{ args }>
        endm
_mm512_set_8to8_pq macro args:vararg
        exitm<_mm512_set_epi64(args)>
        endm
_mm512_set_8to8_epi64 macro args:vararg
        exitm<_mm512_set_epi64(args)>
        endm

_mm512_add_epi8 macro v1, v2
        exitm<_mm512_maskz_add_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_add_epi16 macro v1, v2
        exitm<_mm512_maskz_add_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_add_epi32 macro v1, v2
        exitm<_mm512_maskz_add_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_add_epi64 macro v1, v2
        exitm<_mm512_maskz_add_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_adds_epi8 macro v1, v2
        exitm<_mm512_maskz_adds_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_adds_epi16 macro v1, v2
        exitm<_mm512_maskz_adds_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_adds_epu8 macro v1, v2
        exitm<_mm512_maskz_adds_epu8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_adds_epu16 macro v1, v2
        exitm<_mm512_maskz_adds_epu16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_abs_epi8 macro v1
        exitm<_mm512_maskz_abs_epi8(_MM_K0_REG64, v1)>
        endm

_mm512_abs_epi16 macro v1
        exitm<_mm512_maskz_abs_epi16(_MM_K0_REG64, v1)>
        endm

_mm512_abs_epi32 macro v1
        exitm<_mm512_maskz_abs_epi32(_MM_K0_REG, v1)>
        endm

_mm512_abs_epi64 macro v1
        exitm<_mm512_maskz_abs_epi64(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_i32x2 macro v1
        exitm<_mm512_maskz_broadcast_i32x2(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_i32x4 macro v1
        exitm<_mm512_maskz_broadcast_i32x4(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_i32x8 macro v1
        exitm<_mm512_maskz_broadcast_i32x8(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_i64x2 macro v1
        exitm<_mm512_maskz_broadcast_i64x2(_MM_K0_REG, v1)>
        endm

_mm512_broadcast_i64x4 macro v1
        exitm<_mm512_maskz_broadcast_i64x4(_MM_K0_REG, v1)>
        endm

_mm512_broadcastb_epi8 macro v1
        exitm<_mm512_maskz_broadcastb_epi8(_MM_K0_REG64, v1)>
        endm

_mm512_broadcastw_epi16 macro v1
        exitm<_mm512_maskz_broadcastw_epi16(_MM_K0_REG64, v1)>
        endm

_mm512_broadcastd_epi32 macro v1
        exitm<_mm512_maskz_broadcastd_epi32(_MM_K0_REG, v1)>
        endm

_mm512_broadcastq_epi64 macro v1
        exitm<_mm512_maskz_broadcastq_epi64(_MM_K0_REG, v1)>
        endm

_mm512_sub_epi8 macro v1, v2
        exitm<_mm512_maskz_sub_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_sub_epi16 macro v1, v2
        exitm<_mm512_maskz_sub_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_sub_epi32 macro v1, v2
        exitm<_mm512_maskz_sub_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_sub_epi64 macro v1, v2
        exitm<_mm512_maskz_sub_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_subs_epi8 macro v1, v2
        exitm<_mm512_maskz_subs_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_subs_epi16 macro v1, v2
        exitm<_mm512_maskz_subs_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_subs_epu8 macro v1, v2
        exitm<_mm512_maskz_subs_epu8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_subs_epu16 macro v1, v2
        exitm<_mm512_maskz_subs_epu16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_max_epi8 macro v1, v2
        exitm<_mm512_maskz_max_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_max_epi16 macro v1, v2
        exitm<_mm512_maskz_max_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_max_epi32 macro v1, v2
        exitm<_mm512_maskz_max_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_max_epi64 macro v1, v2
        exitm<_mm512_maskz_max_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_max_epu8 macro v1, v2
        exitm<_mm512_maskz_max_epu8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_max_epu16 macro v1, v2
        exitm<_mm512_maskz_max_epu16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_max_epu32 macro v1, v2
        exitm<_mm512_maskz_max_epu32(_MM_K0_REG, v1, v2)>
        endm

_mm512_max_epu64 macro v1, v2
        exitm<_mm512_maskz_max_epu64(_MM_K0_REG, v1, v2)>
        endm

_mm512_min_epi8 macro v1, v2
        exitm<_mm512_maskz_min_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_min_epi16 macro v1, v2
        exitm<_mm512_maskz_min_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_min_epi32 macro v1, v2
        exitm<_mm512_maskz_min_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_min_epi64 macro v1, v2
        exitm<_mm512_maskz_min_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_min_epu8 macro v1, v2
        exitm<_mm512_maskz_min_epu8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_min_epu16 macro v1, v2
        exitm<_mm512_maskz_min_epu16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_min_epu32 macro v1, v2
        exitm<_mm512_maskz_min_epu32(_MM_K0_REG, v1, v2)>
        endm

_mm512_min_epu64 macro v1, v2
        exitm<_mm512_maskz_min_epu64(_MM_K0_REG, v1, v2)>
        endm

_mm512_mul_epi32 macro v1, v2
        exitm<_mm512_maskz_mul_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_mul_epu32 macro v1, v2
        exitm<_mm512_maskz_mul_epu32(_MM_K0_REG, v1, v2)>
        endm

_mm512_mulhi_epi16 macro v1, v2
        exitm<_mm512_maskz_mulhi_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_mulhi_epu16 macro v1, v2
        exitm<_mm512_maskz_mulhi_epu16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_mullo_epi16 macro v1, v2
        exitm<_mm512_maskz_mullo_epi16(_MM_K0_REG64,v1, v2)>
        endm

_mm512_mullo_epi32 macro v1, v2
        exitm<_mm512_maskz_mullo_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_mullo_epi64 macro v1, v2
        exitm<_mm512_maskz_mullo_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_mulhrs_epi16 macro v1, v2
        exitm<_mm512_maskz_mulhrs_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_load_epi32 macro p1
        exitm<_mm512_maskz_load_epi32(_MM_K0_REG, p1)>
        endm

_mm512_load_si512       equ <_mm512_load_epi32>
_mm512_load_epi64 macro p1
        exitm<_mm512_maskz_load_epi64(_MM_K0_REG, p1)>
        endm

_mm512_loadu_epi8 macro p1
        exitm<_mm512_maskz_loadu_epi8(_MM_K0_REG64, p1)>
        endm

_mm512_loadu_epi16 macro p1
        exitm<_mm512_maskz_loadu_epi16(_MM_K0_REG64, p1)>
        endm

_mm512_loadu_epi32 macro p1, v1:=<zmm0>
        exitm<_mm512_maskz_loadu_epi32(_MM_K0_REG, p1, v1)>
        endm

_mm512_loadu_si512 macro p1, v1:=<zmm0>
        exitm<_mm512_maskz_loadu_epi32(_MM_K0_REG, p1, v1)>
        endm
_mm512_loadu_epi64 macro p1
        exitm<_mm512_maskz_loadu_epi64(_MM_K0_REG, p1)>
        endm

_mm512_store_epi32 macro p1, v1
        exitm<_mm512_mask_store_epi32(p1, _MM_K0_REG, v1)>
        endm
_mm512_store_si512 macro p1, v1
        exitm<_mm512_mask_store_epi32(p1, _MM_K0_REG, v1)>
        endm
_mm512_store_epi64 macro p1, v1
        exitm<_mm512_mask_store_epi64(p1,_MM_K0_REG, v1)>
        endm

_mm512_storeu_epi8 macro p1, v1
        exitm<_mm512_mask_storeu_epi8(p1, _MM_K0_REG64, v1)>
        endm

_mm512_storeu_epi16 macro p1, v1
        exitm<_mm512_mask_storeu_epi16(p1,_MM_K0_REG64, v1)>
        endm

_mm512_storeu_epi32 macro p1, v1
        exitm<_mm512_mask_storeu_epi32(p1, _MM_K0_REG, v1)>
        endm

_mm512_storeu_si512     equ <_mm512_storeu_epi32>
_mm512_storeu_epi64 macro p1, v1
        exitm<_mm512_mask_storeu_epi64(p1,_MM_K0_REG, v1)>
        endm

_mm512_extracti32x4_epi32 macro v1, e1
        exitm<_mm512_maskz_extracti32x4_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_extracti32x8_epi32 macro v1, e1
        exitm<_mm512_maskz_extracti32x8_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_extracti64x2_epi64 macro v1, e1
        exitm<_mm512_maskz_extracti64x2_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_extracti64x4_epi64 macro v1, e1
        exitm<_mm512_maskz_extracti64x4_epi64(_MM_K0_REG, v1, e1)>
        endm


_mm512_inserti32x4 macro v1, v2, e1
        exitm<_mm512_maskz_inserti32x4(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_inserti32x8 macro v1, v2, e1
        exitm<_mm512_maskz_inserti32x8(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_inserti64x2 macro v1, v2, e1
        exitm<_mm512_maskz_inserti64x2(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_inserti64x4 macro v1, v2, e1
        exitm<_mm512_maskz_inserti64x4(_MM_K0_REG, v1, v2, e1)>
        endm


_mm512_shuffle_epi8 macro v1, v2
        exitm<_mm512_maskz_shuffle_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_shuffle_epi32 macro v1, e1
        exitm<_mm512_maskz_shuffle_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_shuffle_i32x4 macro v1, v2, e1
        exitm<_mm512_maskz_shuffle_i32x4(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_shuffle_i64x2 macro v1, v2, e1
        exitm<_mm512_maskz_shuffle_i64x2(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_shufflehi_epi16 macro v1, e1
        exitm<_mm512_maskz_shufflehi_epi16(_MM_K0_REG64, v1, e1)>
        endm

_mm512_shufflelo_epi16 macro v1, e1
        exitm<_mm512_maskz_shufflelo_epi16(_MM_K0_REG64, v1, e1)>
        endm

_mm512_movedup_pd macro v1
        exitm<_mm512_maskz_movedup_pd(_MM_K0_REG, v1)>
        endm

_mm512_movehdup_ps macro v1
        exitm<_mm512_maskz_movehdup_ps(_MM_K0_REG, v1)>
        endm

_mm512_moveldup_ps macro v1
        exitm<_mm512_maskz_moveldup_ps(_MM_K0_REG,v1)>
        endm


_mm512_alignr_epi8 macro v1, v2, e1
        exitm<_mm512_maskz_alignr_epi8(_MM_K0_REG64, v1, v2, e1)>
        endm

_mm512_alignr_epi32 macro v1, v2, e1
        exitm<_mm512_maskz_alignr_epi32(_MM_K0_REG,v1, v2, e1)>
        endm

_mm512_alignr_epi64 macro v1, v2, e1
        exitm<_mm512_maskz_alignr_epi64(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_and_pd macro v1, v2
        exitm<_mm512_maskz_and_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_and_ps macro v1, v2
        exitm<_mm512_maskz_and_ps(_MM_K0_REG, v1, v2)>
        endm

_mm512_and_epi32 macro v1, v2
        exitm<_mm512_maskz_and_epi32(_MM_K0_REG,v1, v2)>
        endm

_mm512_and_si512        equ <_mm512_and_epi32>
_mm512_and_epi64 macro v1, v2
        exitm<_mm512_maskz_and_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_andnot_pd macro v1, v2
        exitm<_mm512_maskz_andnot_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_andnot_ps macro v1, v2
        exitm<_mm512_maskz_andnot_ps(_MM_K0_REG, v1, v2)>
        endm

_mm512_andnot_epi32 macro v1, v2
        exitm<_mm512_maskz_andnot_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_andnot_si512     equ <_mm512_andnot_epi32>
_mm512_andnot_epi64 macro v1, v2
        exitm<_mm512_maskz_andnot_epi64(_MM_K0_REG, v1, v2)>
        endm


_mm512_or_pd macro v1, v2
        exitm<_mm512_maskz_or_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_or_ps macro v1, v2
        exitm<_mm512_maskz_or_ps(_MM_K0_REG,v1, v2)>
        endm

_mm512_or_epi32 macro v1, v2
        exitm<_mm512_maskz_or_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_or_si512         equ <_mm512_or_epi32>
_mm512_or_epi64 macro v1, v2
        exitm<_mm512_maskz_or_epi64(_MM_K0_REG, v1, v2)>
        endm


_mm512_xor_pd macro v1, v2
        exitm<_mm512_maskz_xor_pd(_MM_K0_REG,v1, v2)>
        endm

_mm512_xor_ps macro v1, v2
        exitm<_mm512_maskz_xor_ps(_MM_K0_REG,v1, v2)>
        endm

_mm512_xor_epi32 macro v1, v2
        exitm<_mm512_maskz_xor_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_xor_si512        equ <_mm512_xor_epi32>
_mm512_xor_epi64 macro v1, v2
        exitm<_mm512_maskz_xor_epi64(_MM_K0_REG, v1, v2)>
        endm


_mm512_sll_epi16 macro v1, v2
        exitm<_mm512_maskz_sll_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_sll_epi32 macro v1, v2
        exitm<_mm512_maskz_sll_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_sll_epi64 macro v1, v2
        exitm<_mm512_maskz_sll_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_slli_epi16 macro v1, e1
        exitm<_mm512_maskz_slli_epi16(_MM_K0_REG64, v1, e1)>
        endm

_mm512_slli_epi32 macro v1, e1
        exitm<_mm512_maskz_slli_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_slli_epi64 macro v1, e1
        exitm<_mm512_maskz_slli_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_sllv_epi16 macro v1, v2
        exitm<_mm512_maskz_sllv_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_sllv_epi32 macro v1, v2
        exitm<_mm512_maskz_sllv_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_sllv_epi64 macro v1, v2
        exitm<_mm512_maskz_sllv_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_srl_epi16 macro v1, v2
        exitm<_mm512_maskz_srl_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_srl_epi32 macro v1, v2
        exitm<_mm512_maskz_srl_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_srl_epi64 macro v1, v2
        exitm<_mm512_maskz_srl_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_srli_epi16 macro v1, e1
        exitm<_mm512_maskz_srli_epi16(_MM_K0_REG64, v1, e1)>
        endm

_mm512_srli_epi32 macro v1, e1
        exitm<_mm512_maskz_srli_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_srli_epi64 macro v1, e1
        exitm<_mm512_maskz_srli_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_srlv_epi16 macro v1, v2
        exitm<_mm512_maskz_srlv_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_srlv_epi32 macro v1, v2
        exitm<_mm512_maskz_srlv_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_srlv_epi64 macro v1, v2
        exitm<_mm512_maskz_srlv_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_sra_epi16 macro v1, v2
        exitm<_mm512_maskz_sra_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_sra_epi32 macro v1, v2
        exitm<_mm512_maskz_sra_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_sra_epi64 macro v1, v2
        exitm<_mm512_maskz_sra_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_srai_epi16 macro v1, e1
        exitm<_mm512_maskz_srai_epi16(_MM_K0_REG64, v1, e1)>
        endm

_mm512_srai_epi32 macro v1, e1
        exitm<_mm512_maskz_srai_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_srai_epi64 macro v1, e1
        exitm<_mm512_maskz_srai_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_srav_epi16 macro v1, v2
        exitm<_mm512_maskz_srav_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_srav_epi32 macro v1, v2
        exitm<_mm512_maskz_srav_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_srav_epi64 macro v1, v2
        exitm<_mm512_maskz_srav_epi64(_MM_K0_REG, v1, v2)>
        endm


_mm512_rol_epi32 macro v1, e1
        exitm<_mm512_maskz_rol_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_rol_epi64 macro v1, e1
        exitm<_mm512_maskz_rol_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_rolv_epi32 macro v1, v2
        exitm<_mm512_maskz_rolv_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_rolv_epi64 macro v1, v2
        exitm<_mm512_maskz_rolv_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_ror_epi32 macro v1, e1
        exitm<_mm512_maskz_ror_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_ror_epi64 macro v1, e1
        exitm<_mm512_maskz_ror_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_rorv_epi32 macro v1, v2
        exitm<_mm512_maskz_rorv_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_rorv_epi64 macro v1, v2
        exitm<_mm512_maskz_rorv_epi64(_MM_K0_REG, v1, v2)>
        endm


_mm512_unpackhi_pd macro v1, v2
        exitm<_mm512_maskz_unpackhi_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpackhi_ps macro v1, v2
        exitm<_mm512_maskz_unpackhi_ps(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpacklo_pd macro v1, v2
        exitm<_mm512_maskz_unpacklo_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpacklo_ps macro v1, v2
        exitm<_mm512_maskz_unpacklo_ps(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpackhi_epi8 macro v1, v2
        exitm<_mm512_maskz_unpackhi_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_unpackhi_epi16 macro v1, v2
        exitm<_mm512_maskz_unpackhi_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_unpackhi_epi32 macro v1, v2
        exitm<_mm512_maskz_unpackhi_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpackhi_epi64 macro v1, v2
        exitm<_mm512_maskz_unpackhi_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpacklo_epi8 macro v1, v2
        exitm<_mm512_maskz_unpacklo_epi8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_unpacklo_epi16 macro v1, v2
        exitm<_mm512_maskz_unpacklo_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_unpacklo_epi32 macro v1, v2
        exitm<_mm512_maskz_unpacklo_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_unpacklo_epi64 macro v1, v2
        exitm<_mm512_maskz_unpacklo_epi64(_MM_K0_REG, v1, v2)>
        endm


_mm512_mask_getexp_ps macro v1, _k1, v2
        exitm<_mm512_mask_getexp_round_ps(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_getexp_ps macro _k1, v1
        exitm<_mm512_maskz_getexp_round_ps(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm


_mm512_getexp_round_ps macro v1, e1
        exitm<_mm512_maskz_getexp_round_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_getexp_ps macro v1
        exitm<_mm512_maskz_getexp_ps(_MM_K0_REG, v1)>
        endm

_mm512_mask_getexp_pd macro v1, _k1, v2
        exitm<_mm512_mask_getexp_round_pd(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_getexp_pd macro _k1, v1
        exitm<_mm512_maskz_getexp_round_pd(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_getexp_round_pd macro v1, e1
        exitm<_mm512_maskz_getexp_round_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_getexp_pd macro v1
        exitm<_mm512_maskz_getexp_pd(_MM_K0_REG, v1)>
        endm


_mm512_mask_getmant_ps macro v1, _k1, v2, e1, e2
        exitm<_mm512_mask_getmant_round_ps(v1, _k1, v2, e1, e2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_getmant_ps macro _k1, v1, e1, e2
        exitm<_mm512_maskz_getmant_round_ps(_k1, v1, e1, e2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_getmant_round_ps macro v1, e1, e2, e3
        exitm<_mm512_maskz_getmant_round_ps(_MM_K0_REG, v1, e1, e2, e3)>
        endm

_mm512_getmant_ps macro v1, e1, e2
        exitm<_mm512_maskz_getmant_ps(_MM_K0_REG, v1, e1, e2)>
        endm

_mm512_mask_getmant_pd macro v1, _k1, v2, e1, e2
        exitm<_mm512_mask_getmant_round_pd(v1, _k1, v2, e1, e2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_getmant_pd macro _k1, v1, e1, e2
        exitm<_mm512_maskz_getmant_round_pd(_k1, v1, e1, e2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_getmant_round_pd macro v1, e1, e2, e3
        exitm<_mm512_maskz_getmant_round_pd(_MM_K0_REG, v1, e1, e2, e3)>
        endm

_mm512_getmant_pd macro v1, e1, e2
        exitm<_mm512_maskz_getmant_pd(_MM_K0_REG, v1, e1, e2)>
        endm


_mm512_permute_pd macro v1, e1
        exitm<_mm512_maskz_permute_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_permute_ps macro v1, e1
        exitm<_mm512_maskz_permute_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_permutevar_pd macro v1, v2
        exitm<_mm512_maskz_permutevar_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_permutevar_ps macro v1, v2
        exitm<_mm512_maskz_permutevar_ps(_MM_K0_REG, v1, v2)>
        endm

_mm512_permutex_pd macro v1, e1
        exitm<_mm512_maskz_permutex_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_permutex_epi64 macro v1, e1
        exitm<_mm512_maskz_permutex_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_permutexvar_pd macro v1, v2
        exitm<_mm512_maskz_permutexvar_pd(_MM_K0_REG, v1, v2)>
        endm

_mm512_permutexvar_ps macro v1, v2
        exitm<_mm512_maskz_permutexvar_ps(_MM_K0_REG, v1, v2)>
        endm

_mm512_permutexvar_epi16 macro v1, v2
        exitm<_mm512_maskz_permutexvar_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_permutexvar_epi32 macro v1, v2
        exitm<_mm512_maskz_permutexvar_epi32(_MM_K0_REG, v1, v2)>
        endm

_mm512_permutexvar_epi64 macro v1, v2
        exitm<_mm512_maskz_permutexvar_epi64(_MM_K0_REG, v1, v2)>
        endm

_mm512_permutex2var_pd macro v1, v2, v3
        exitm<_mm512_maskz_permutex2var_pd(_MM_K0_REG, v1, v2, v3)>
        endm

_mm512_permutex2var_ps macro v1, v2, v3
        exitm<_mm512_maskz_permutex2var_ps(_MM_K0_REG, v1, v2, v3)>
        endm

_mm512_permutex2var_epi16 macro v1, v2, v3
        exitm<_mm512_maskz_permutex2var_epi16(_MM_K0_REG64, v1, v2, v3)>
        endm

_mm512_permutex2var_epi32 macro v1, v2, v3
        exitm<_mm512_maskz_permutex2var_epi32(_MM_K0_REG, v1, v2, v3)>
        endm

_mm512_permutex2var_epi64 macro v1, v2, v3
        exitm<_mm512_maskz_permutex2var_epi64(_MM_K0_REG, v1, v2, v3)>
        endm

if 0
_mm512_ternarylogic_epi32 proto __vdecl :abs, :abs, :abs, :abs {
    vpternlogd  _1, _2, _3, _4
    }
endif
_mm512_ternarylogic_epi32 macro v1, v2, v3, e1
        exitm<_mm512_maskz_ternarylogic_epi32(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_ternarylogic_epi64 macro v1, v2, v3, e1
        exitm<_mm512_maskz_ternarylogic_epi64(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_conflict_epi32 macro v1
        exitm<_mm512_maskz_conflict_epi32(_MM_K0_REG, v1)>
        endm

_mm512_conflict_epi64 macro v1
        exitm<_mm512_maskz_conflict_epi64(_MM_K0_REG, v1)>
        endm

_mm512_lzcnt_epi32 macro v1
        exitm<_mm512_maskz_lzcnt_epi32(_MM_K0_REG, v1)>
        endm

_mm512_lzcnt_epi64 macro v1
        exitm<_mm512_maskz_lzcnt_epi64(_MM_K0_REG,v1)>
        endm

_mm512_avg_epu8 macro v1, v2
        exitm<_mm512_maskz_avg_epu8(_MM_K0_REG64, v1, v2)>
        endm

_mm512_avg_epu16 macro v1, v2
        exitm<_mm512_maskz_avg_epu16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_dbsad_epu8 macro v1, v2, e1
        exitm<_mm512_maskz_dbsad_epu8(_MM_K0_REG64, v1, v2, e1)>
        endm

_mm512_reduce_round_pd macro v1, e1, e2
        exitm<_mm512_maskz_reduce_round_pd(_MM_K0_REG, v1, e1, e2)>
        endm

_mm512_mask_reduce_pd macro v1, _k1, v2, e1
        exitm<_mm512_mask_reduce_round_pd(v1, _k1, v2, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_reduce_pd macro _k1, v1, e1
        exitm<_mm512_maskz_reduce_round_pd(_k1, v1, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_reduce_pd macro v1, e1
        exitm<_mm512_maskz_reduce_pd(_MM_K0_REG, v1, e1)>
        endm
_mm512_reduce_round_ps macro v1, e1, e2
        exitm<_mm512_maskz_reduce_round_ps(_MM_K0_REG, v1, e1, e2)>
        endm

_mm512_mask_reduce_ps macro v1, _k1, v2, e1
        exitm<_mm512_mask_reduce_round_ps(v1, _k1, v2, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_reduce_ps macro _k1, v1, e1
        exitm<_mm512_maskz_reduce_round_ps(_k1, v1, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_reduce_ps macro v1, e1
        exitm<_mm512_maskz_reduce_ps(_MM_K0_REG,v1, e1)>
        endm

_mm512_roundscale_round_pd macro v1, e1, e2
        exitm<_mm512_maskz_roundscale_round_pd(_MM_K0_REG, v1, e1, e2)>
        endm

_mm512_mask_roundscale_pd macro v1, _k1, v2, e1
        exitm<_mm512_mask_roundscale_round_pd(v1, _k1, v2, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_roundscale_pd macro _k1, v1, e1
        exitm<_mm512_maskz_roundscale_round_pd(_k1, v1, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_roundscale_pd macro v1, e1
        exitm<_mm512_maskz_roundscale_pd(_MM_K0_REG, v1, e1)>
        endm


_mm512_roundscale_round_ps macro v1, e1, e2
        exitm<_mm512_maskz_roundscale_round_ps(_MM_K0_REG, v1, e1, e2)>
        endm

_mm512_mask_roundscale_ps macro v1, _k1, v2, e1
        exitm< _mm512_mask_roundscale_round_ps(v1, _k1, v2, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_roundscale_ps macro _k1, v1, e1
        exitm<_mm512_maskz_roundscale_round_ps(_k1, v1, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_roundscale_ps macro v1, e1
        exitm<_mm512_maskz_roundscale_ps(_MM_K0_REG, v1, e1)>
        endm


_mm512_scalef_round_pd macro v1, v2, e1
        exitm<_mm512_maskz_scalef_round_pd(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_mask_scalef_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_scalef_round_pd(v1, _k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_scalef_pd macro _k1, v1, v2
        exitm<_mm512_maskz_scalef_round_pd(_k1, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_scalef_pd macro v1, v2
        exitm<_mm512_maskz_scalef_pd(_MM_K0_REG, v1, v2)>
        endm


_mm512_scalef_round_ps macro v1, v2, e1
        exitm<_mm512_maskz_scalef_round_ps(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_mask_scalef_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_scalef_round_ps(v1, _k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_scalef_ps macro _k1, v1, v2
        exitm<_mm512_maskz_scalef_round_ps(_k1, v1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_scalef_ps macro v1, v2
        exitm<_mm512_maskz_scalef_ps(_MM_K0_REG, v1, v2)>
        endm


_mm512_fixupimm_round_pd macro v1, v2, v3, e1, e2
        exitm<_mm512_maskz_fixupimm_round_pd(_MM_K0_REG, v1, v2, v3, e1, e2)>
        endm

_mm512_mask_fixupimm_pd macro v1, _k1, v2, v3, e1
        exitm<_mm512_mask_fixupimm_round_pd(v1, _k1, v2, v3, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_fixupimm_pd macro _k1, v1, v2, v3, e1
        exitm<_mm512_maskz_fixupimm_round_pd(_k1, v1, v2, v3, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fixupimm_pd macro v1, v2, v3, e1
        exitm<_mm512_maskz_fixupimm_pd(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_fixupimm_round_ps macro v1, v2, v3, e1, e2
        exitm<_mm512_maskz_fixupimm_round_ps(_MM_K0_REG, v1, v2, v3, e1, e2)>
        endm

_mm512_mask_fixupimm_ps macro v1, _k1, v2, v3, e1
        exitm<_mm512_mask_fixupimm_round_ps(v1, _k1, v2, v3, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_fixupimm_ps macro _k1, v1, v2, v3, e1
        exitm<_mm512_maskz_fixupimm_round_ps(_k1, v1, v2, v3, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fixupimm_ps macro v1, v2, v3, e1
        exitm<_mm512_maskz_fixupimm_ps(_MM_K0_REG,v1, v2, v3, e1)>
        endm

_mm512_exp2a23_round_ps macro v1, e1
        exitm<_mm512_maskz_exp2a23_round_ps(_MM_K0_REG,v1, e1)>
        endm

_mm512_mask_exp2a23_ps macro v1, _k1, v2
        exitm<_mm512_mask_exp2a23_round_ps(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_exp2a23_ps macro _k1, v1
        exitm<_mm512_maskz_exp2a23_round_ps(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_exp2a23_ps macro v1
        exitm<_mm512_maskz_exp2a23_ps(_MM_K0_REG, v1)>
        endm

_mm512_exp2a23_round_pd macro v1, e1
        exitm<_mm512_maskz_exp2a23_round_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_mask_exp2a23_pd macro v1, _k1, v2
        exitm<_mm512_mask_exp2a23_round_pd(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_exp2a23_pd macro _k1, v1
        exitm<_mm512_maskz_exp2a23_round_pd(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_exp2a23_pd macro v1
        exitm<_mm512_maskz_exp2a23_pd(_MM_K0_REG, v1)>
        endm

_mm512_fpclass_ps_mask macro v1, e1
        exitm<_mm512_mask_fpclass_ps_mask(_MM_K0_REG, v1, e1)>
        endm

_mm512_fpclass_pd_mask macro v1, e1
        exitm<_mm512_mask_fpclass_pd_mask(_MM_K0_REG, v1, e1)>
        endm

_mm512_range_round_pd macro v1, v2, e1, e2
        exitm<_mm512_maskz_range_round_pd(_MM_K0_REG, v1, v2, e1, e2)>
        endm

_mm512_mask_range_pd macro v1, _k1, v2, v3, e1
        exitm<_mm512_mask_range_round_pd(v1, _k1, v2, v3, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_range_pd macro _k1, v1, v2, e1
        exitm<_mm512_maskz_range_round_pd(_k1, v1, v2, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_range_pd macro v1, v2, e1
        exitm<_mm512_maskz_range_pd(_MM_K0_REG, v1, v2, e1)>
        endm


_mm512_range_round_ps macro v1, v2, e1, e2
        exitm<_mm512_maskz_range_round_ps(_MM_K0_REG, v1, v2, e1, e2)>
        endm

_mm512_mask_range_ps macro v1, _k1, v2, v3, e1
        exitm<_mm512_mask_range_round_ps(v1, _k1, v2, v3, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_range_ps macro _k1, v1, v2, e1
        exitm<_mm512_maskz_range_round_ps(_k1, v1, v2, e1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_range_ps macro v1, v2, e1
        exitm<_mm512_maskz_range_ps(_MM_K0_REG, v1, v2, e1)>
        endm


_mm512_madd_epi16 macro v1, v2
        exitm<_mm512_maskz_madd_epi16(_MM_K0_REG, v1, v2)>
        endm

_mm512_maddubs_epi16 macro v1, v2
        exitm<_mm512_maskz_maddubs_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_packs_epi16 macro v1, v2
        exitm<_mm512_maskz_packs_epi16(_MM_K0_REG64, v1, v2)>
        endm

_mm512_packs_epi32 macro v1, v2
        exitm<_mm512_maskz_packs_epi32(_MM_K0_REG64,v1, v2)>
        endm

_mm512_packus_epi16 macro v1, v2
        exitm<_mm512_maskz_packus_epi16(_MM_K0_REG64,v1, v2)>
        endm

_mm512_packus_epi32 macro v1, v2
        exitm<_mm512_maskz_packus_epi32(_MM_K0_REG64, v1, v2)>
        endm


_mm512_mask_rcp28_ps macro v1, _k1, v2
        exitm<_mm512_mask_rcp28_round_ps(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_rcp28_ps macro _k1, v1
        exitm<_mm512_maskz_rcp28_round_ps(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_rcp28_round_ps macro v1, e1
        exitm<_mm512_maskz_rcp28_round_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_rcp28_ps macro v1
        exitm<_mm512_maskz_rcp28_ps(_MM_K0_REG, v1)>
        endm

_mm512_mask_rcp28_pd macro v1, _k1, v2
        exitm<_mm512_mask_rcp28_round_pd(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_rcp28_pd macro _k1, v1
        exitm<_mm512_maskz_rcp28_round_pd(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_rcp28_round_pd macro v1, e1
        exitm<_mm512_maskz_rcp28_round_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_rcp28_pd macro v1
        exitm<_mm512_maskz_rcp28_pd(_MM_K0_REG, v1)>
        endm

_mm512_mask_rsqrt28_ps macro v1, _k1, v2
        exitm<_mm512_mask_rsqrt28_round_ps(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_rsqrt28_ps macro _k1, v1
        exitm<_mm512_maskz_rsqrt28_round_ps(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_rsqrt28_round_ps macro v1, e1
        exitm<_mm512_maskz_rsqrt28_round_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_rsqrt28_ps macro v1
        exitm<_mm512_maskz_rsqrt28_ps(_MM_K0_REG, v1)>
        endm

_mm512_mask_rsqrt28_pd macro v1, _k1, v2
        exitm<_mm512_mask_rsqrt28_round_pd(v1, _k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_rsqrt28_pd macro _k1, v1
        exitm<_mm512_maskz_rsqrt28_round_pd(_k1, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_rsqrt28_round_pd macro v1, e1
        exitm<_mm512_maskz_rsqrt28_round_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_rsqrt28_pd macro v1
        exitm<_mm512_maskz_rsqrt28_pd(_MM_K0_REG, v1)>
        endm

_mm512_mask3_fmadd_ps macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmadd_round_ps(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmadd_pd macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmadd_round_pd(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmsub_ps macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmsub_round_ps(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmsub_pd macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmsub_round_pd(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fnmadd_ps macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fnmadd_round_ps(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fnmadd_pd macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fnmadd_round_pd(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fnmsub_ps macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fnmsub_round_ps(v1, v2, v3, _k3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fnmsub_pd macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fnmsub_round_pd(v1, v2, v3, (_k3), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmaddsub_ps macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmaddsub_round_ps(v1, v2, v3, (_k3), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmaddsub_pd macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmaddsub_round_pd(v1, v2, v3, (_k3), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmsubadd_ps macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmsubadd_round_ps(v1, v2, v3, (_k3), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask3_fmsubadd_pd macro v1, v2, v3, _k3
        exitm<_mm512_mask3_fmsubadd_round_pd(v1, v2, v3, (_k3), _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_fmaddsub_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmaddsub_round_ps(v1, _k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_fmaddsub_ps macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmaddsub_round_ps(_k1, v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fmaddsub_round_ps macro v1, v2, v3, e1
        exitm<_mm512_maskz_fmaddsub_round_ps(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_fmaddsub_ps macro v1, v2, v3
        exitm<_mm512_maskz_fmaddsub_ps(_MM_K0_REG, v1, v2, v3)>
        endm

_mm512_mask_fmaddsub_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmaddsub_round_pd(v1, _k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_fmaddsub_pd macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmaddsub_round_pd(_k1, v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fmaddsub_round_pd macro v1, v2, v3, e1
        exitm<_mm512_maskz_fmaddsub_round_pd(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_fmaddsub_pd macro v1, v2, v3
        exitm<_mm512_maskz_fmaddsub_pd(_MM_K0_REG, v1, v2, v3)>
        endm

_mm512_mask_fmsubadd_ps macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmsubadd_round_ps(v1, _k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_fmsubadd_ps macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmsubadd_round_ps(_k1, v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fmsubadd_round_ps macro v1, v2, v3, e1
        exitm<_mm512_maskz_fmsubadd_round_ps(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_fmsubadd_ps macro v1, v2, v3
        exitm<_mm512_maskz_fmsubadd_ps(_MM_K0_REG,v1, v2, v3)>
        endm

_mm512_mask_fmsubadd_pd macro v1, _k1, v2, v3
        exitm<_mm512_mask_fmsubadd_round_pd(v1, _k1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_fmsubadd_pd macro _k1, v1, v2, v3
        exitm<_mm512_maskz_fmsubadd_round_pd(_k1, v1, v2, v3, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_fmsubadd_round_pd macro v1, v2, v3, e1
        exitm<_mm512_maskz_fmsubadd_round_pd(_MM_K0_REG, v1, v2, v3, e1)>
        endm

_mm512_fmsubadd_pd macro v1, v2, v3
        exitm<_mm512_maskz_fmsubadd_pd(_MM_K0_REG, v1, v2, v3)>
        endm

_mm512_cmp_epi8_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epi8_mask(_MM_K0_REG64, v1, v2, e1)>
        endm

_mm512_cmp_epi16_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epi16_mask(_MM_K0_REG64, v1, v2, e1)>
        endm

_mm512_cmp_epi32_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epi32_mask(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_cmp_epi64_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epi64_mask(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_cmp_epu8_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epu8_mask(_MM_K0_REG64, v1, v2, e1)>
        endm

_mm512_cmp_epu16_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epu16_mask(_MM_K0_REG64, v1, v2, e1)>
        endm

_mm512_cmp_epu32_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epu32_mask(_MM_K0_REG,v1, v2, e1)>
        endm

_mm512_cmp_epu64_mask macro v1, v2, e1
        exitm<_mm512_mask_cmp_epu64_mask(_MM_K0_REG, v1, v2, e1)>
        endm

_mm512_cmpeq_epi32_mask macro v1, v2
        exitm<_mm512_cmp_epi32_mask(v1,v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epi32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi32_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epi32_mask macro v1, v2
        exitm<_mm512_cmp_epi32_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epi32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi32_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epi32_mask macro v1, v2
        exitm<_mm512_cmp_epi32_mask(v1,v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epi32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi32_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpneq_epi32_mask macro v1, v2
        exitm<_mm512_cmp_epi32_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epi32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi32_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_cmpge_epi32_mask macro v1, v2
        exitm<_mm512_cmp_epi32_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epi32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi32_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpgt_epi32_mask macro v1, v2
        exitm<_mm512_cmp_epi32_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epi32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi32_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpeq_epu32_mask macro v1, v2
        exitm<_mm512_cmp_epu32_mask(v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epu32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu32_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epu32_mask macro v1, v2
        exitm<_mm512_cmp_epu32_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epu32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu32_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epu32_mask macro v1, v2
        exitm<_mm512_cmp_epu32_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epu32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu32_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpneq_epu32_mask macro v1, v2
        exitm<_mm512_cmp_epu32_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epu32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu32_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_cmpge_epu32_mask macro v1, v2
        exitm<_mm512_cmp_epu32_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epu32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu32_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpgt_epu32_mask macro v1, v2
        exitm<_mm512_cmp_epu32_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epu32_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu32_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpeq_epi64_mask macro v1, v2
        exitm<_mm512_cmp_epi64_mask(v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epi64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi64_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epi64_mask macro v1, v2
        exitm<_mm512_cmp_epi64_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epi64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi64_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epi64_mask macro v1, v2
        exitm<_mm512_cmp_epi64_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epi64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi64_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpgt_epi64_mask macro v1, v2
        exitm<_mm512_cmp_epi64_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epi64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi64_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpge_epi64_mask macro v1, v2
        exitm<_mm512_cmp_epi64_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epi64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi64_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpneq_epi64_mask macro v1, v2
        exitm<_mm512_cmp_epi64_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epi64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi64_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_cmpeq_epu64_mask macro v1, v2
        exitm<_mm512_cmp_epu64_mask(v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epu64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu64_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epu64_mask macro v1, v2
        exitm<_mm512_cmp_epu64_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epu64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu64_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epu64_mask macro v1, v2
        exitm<_mm512_cmp_epu64_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epu64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu64_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpgt_epu64_mask macro v1, v2
        exitm<_mm512_cmp_epu64_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epu64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu64_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpge_epu64_mask macro v1, v2
        exitm<_mm512_cmp_epu64_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epu64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu64_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpneq_epu64_mask macro v1, v2
        exitm<_mm512_cmp_epu64_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epu64_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu64_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm


_mm512_cmpeq_epi8_mask macro v1, v2
        exitm<_mm512_cmp_epi8_mask(v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epi8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi8_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epi8_mask macro v1, v2
        exitm<_mm512_cmp_epi8_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epi8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi8_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epi8_mask macro v1, v2
        exitm<_mm512_cmp_epi8_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epi8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi8_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpgt_epi8_mask macro v1, v2
        exitm<_mm512_cmp_epi8_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epi8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi8_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpge_epi8_mask macro v1, v2
        exitm<_mm512_cmp_epi8_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epi8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi8_mask(_k1,v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpneq_epi8_mask macro v1, v2
        exitm<_mm512_cmp_epi8_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epi8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi8_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_cmpeq_epu8_mask macro v1, v2
        exitm<_mm512_cmp_epu8_mask(v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epu8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu8_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epu8_mask macro v1, v2
        exitm<_mm512_cmp_epu8_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epu8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu8_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epu8_mask macro v1, v2
        exitm<_mm512_cmp_epu8_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epu8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu8_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpgt_epu8_mask macro v1, v2
        exitm<_mm512_cmp_epu8_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epu8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu8_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpge_epu8_mask macro v1, v2
        exitm<_mm512_cmp_epu8_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epu8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu8_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpneq_epu8_mask macro v1, v2
        exitm<_mm512_cmp_epu8_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epu8_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu8_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_cmpeq_epi16_mask macro v1, v2
        exitm<_mm512_cmp_epi16_mask(v1,v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epi16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi16_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epi16_mask macro v1, v2
        exitm<_mm512_cmp_epi16_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epi16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi16_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epi16_mask macro v1, v2
        exitm<_mm512_cmp_epi16_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epi16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi16_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpgt_epi16_mask macro v1, v2
        exitm<_mm512_cmp_epi16_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epi16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi16_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpge_epi16_mask macro v1, v2
        exitm<_mm512_cmp_epi16_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epi16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi16_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpneq_epi16_mask macro v1, v2
        exitm<_mm512_cmp_epi16_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epi16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epi16_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_cmpeq_epu16_mask macro v1, v2
        exitm<_mm512_cmp_epu16_mask(v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_mask_cmpeq_epu16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu16_mask(_k1, v1, v2, _MM_CMPINT_EQ)>
        endm

_mm512_cmplt_epu16_mask macro v1, v2
        exitm<_mm512_cmp_epu16_mask(v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_mask_cmplt_epu16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu16_mask(_k1, v1, v2, _MM_CMPINT_LT)>
        endm

_mm512_cmple_epu16_mask macro v1, v2
        exitm<_mm512_cmp_epu16_mask(v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_mask_cmple_epu16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu16_mask(_k1, v1, v2, _MM_CMPINT_LE)>
        endm

_mm512_cmpgt_epu16_mask macro v1, v2
        exitm<_mm512_cmp_epu16_mask(v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_mask_cmpgt_epu16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu16_mask(_k1, v1, v2, _MM_CMPINT_GT)>
        endm

_mm512_cmpge_epu16_mask macro v1, v2
        exitm<_mm512_cmp_epu16_mask(v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_mask_cmpge_epu16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu16_mask(_k1, v1, v2, _MM_CMPINT_GE)>
        endm

_mm512_cmpneq_epu16_mask macro v1, v2
        exitm<_mm512_cmp_epu16_mask(v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_mask_cmpneq_epu16_mask macro _k1, v1, v2
        exitm<_mm512_mask_cmp_epu16_mask(_k1, v1, v2, _MM_CMPINT_NE)>
        endm

_mm512_test_epi8_mask macro v1, v2
        exitm<_mm512_mask_test_epi8_mask(_MM_K0_REG64, v1, v2)>
        endm

_mm512_test_epi16_mask macro v1, v2
        exitm<_mm512_mask_test_epi16_mask(_MM_K0_REG64, v1, v2)>
        endm

_mm512_testn_epi8_mask macro v1, v2
        exitm<_mm512_mask_testn_epi8_mask(_MM_K0_REG64, v1, v2)>
        endm

_mm512_testn_epi16_mask macro v1, v2
        exitm<_mm512_mask_testn_epi16_mask(_MM_K0_REG64, v1, v2)>
        endm

_mm512_test_epi32_mask macro v1, v2
        exitm<_mm512_mask_test_epi32_mask(_MM_K0_REG, v1, v2)>
        endm

_mm512_test_epi64_mask macro v1, v2
        exitm<_mm512_mask_test_epi64_mask(_MM_K0_REG, v1, v2)>
        endm

_mm512_testn_epi32_mask macro v1, v2
        exitm<_mm512_mask_testn_epi32_mask(_MM_K0_REG, v1, v2)>
        endm

_mm512_testn_epi64_mask macro v1, v2
        exitm<_mm512_mask_testn_epi64_mask(_MM_K0_REG, v1, v2)>
        endm

_cvtu32_mask16 macro i
        exitm<_mm512_load_kw(i)>
        endm
_cvtmask16_u32 macro m
        exitm<_mm512_load_kw(m)>
        endm

_mm512_kmov macro m
        exitm<_mm512_load_kw(m)>
        endm
_mm512_mask2int macro m
        exitm<_cvtmask16_u32(m)>
        endm
_mm512_int2mask macro i
        exitm<_cvtu32_mask16(i)>
        endm
_mm512_kortestz macro m1, m2
        exitm<_mm512_testz_or_mask16(m1, m2)>
        endm
_mm512_kortestc macro m1, m2
        exitm<_mm512_testz_nor_mask16(m1, m2)>
        endm
_mm512_undefined_epi32 macro
        exitm<_mm512_castps_si512(_mm512_undefined())>
        endm

_mm512_i32logather_epi64 macro index, ad, scale
        exitm<_mm512_i32gather_epi64(_mm512_castsi512_si256(index), ad, scale)>
        endm

_mm512_mask_i32logather_epi64 macro v1, _k1, index, _addr, scale
        exitm<_mm512_mask_i32gather_epi64(v1, _k1, _mm512_castsi512_si256(index), _addr, scale)>
        endm

_mm512_i32logather_pd macro index, _addr, scale
        exitm<_mm512_i32gather_pd(_mm512_castsi512_si256(index), _addr, scale)>
        endm

_mm512_mask_i32logather_pd macro v1, _k1, index, _addr, scale
        exitm<_mm512_mask_i32gather_pd(v1,_k1, _mm512_castsi512_si256(index), _addr, scale)>
        endm

_mm512_i32loscatter_pd macro _addr, index, v1, scale
        exitm<_mm512_i32scatter_pd(_addr, _mm512_castsi512_si256(index), v1, scale)>
        endm

_mm512_mask_i32loscatter_pd macro _addr, _k1, index, v1, scale
        exitm<_mm512_mask_i32scatter_pd(_addr, _k1, _mm512_castsi512_si256(index), v1, scale)>
        endm


_mm512_cvtepi32_pd macro v1
        exitm<_mm512_maskz_cvtepi32_pd(_MM_K0_REG, v1)>
        endm

_mm512_cvtepu32_pd macro v1
        exitm<_mm512_maskz_cvtepu32_pd(_MM_K0_REG, v1)>
        endm


_mm512_cvt_roundepi32_ps macro v1, e1
        exitm<_mm512_maskz_cvt_roundepi32_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundepu32_ps macro v1, e1
        exitm<_mm512_maskz_cvt_roundepu32_ps(_MM_K0_REG,v1, e1)>
        endm

_mm512_cvt_roundph_ps macro v1, e1
        exitm<_mm512_maskz_cvt_roundph_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundps_ph macro v1, e1
        exitm<_mm512_maskz_cvt_roundps_ph(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundepi64_ps macro v1, e1
        exitm<_mm512_maskz_cvt_roundepi64_ps(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundepu64_ps macro v1, e1
        exitm<_mm512_maskz_cvt_roundepu64_ps(_MM_K0_REG, v1, e1)>
        endm


_mm512_cvtepi8_epi32 macro v1
        exitm<_mm512_maskz_cvtepi8_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi8_epi64 macro v1
        exitm<_mm512_maskz_cvtepi8_epi64(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi16_epi32 macro v1
        exitm<_mm512_maskz_cvtepi16_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi16_epi64 macro v1
        exitm<_mm512_maskz_cvtepi16_epi64(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi32_epi8 macro v1
        exitm<_mm512_maskz_cvtepi32_epi8(_MM_K0_REG, v1)>
        endm

_mm512_cvtsepi32_epi8 macro v1
        exitm<_mm512_maskz_cvtsepi32_epi8(_MM_K0_REG, v1)>
        endm

_mm512_cvtusepi32_epi8 macro v1
        exitm<_mm512_maskz_cvtusepi32_epi8(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi32_epi16 macro v1
        exitm<_mm512_maskz_cvtepi32_epi16(_MM_K0_REG, v1)>
        endm

_mm512_cvtsepi32_epi16 macro v1
        exitm<_mm512_maskz_cvtsepi32_epi16(_MM_K0_REG, v1)>
        endm

_mm512_cvtusepi32_epi16 macro v1
        exitm<_mm512_maskz_cvtusepi32_epi16(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi32_epi64 macro v1
        exitm<_mm512_maskz_cvtepi32_epi64(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi64_epi8 macro v1
        exitm<_mm512_maskz_cvtepi64_epi8(_MM_K0_REG, v1)>
        endm

_mm512_cvtsepi64_epi8 macro v1
        exitm<_mm512_maskz_cvtsepi64_epi8(_MM_K0_REG, v1)>
        endm

_mm512_cvtusepi64_epi8 macro v1
        exitm<_mm512_maskz_cvtusepi64_epi8(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi64_epi16 macro v1
        exitm<_mm512_maskz_cvtepi64_epi16(_MM_K0_REG, v1)>
        endm

_mm512_cvtsepi64_epi16 macro v1
        exitm<_mm512_maskz_cvtsepi64_epi16(_MM_K0_REG, v1)>
        endm

_mm512_cvtusepi64_epi16 macro v1
        exitm<_mm512_maskz_cvtusepi64_epi16(_MM_K0_REG, v1)>
        endm

_mm512_cvtepi64_epi32 macro v1
        exitm<_mm512_maskz_cvtepi64_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtsepi64_epi32 macro v1
        exitm<_mm512_maskz_cvtsepi64_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtusepi64_epi32 macro v1
        exitm<_mm512_maskz_cvtusepi64_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtepu8_epi32 macro v1
        exitm<_mm512_maskz_cvtepu8_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtepu8_epi64 macro v1
        exitm<_mm512_maskz_cvtepu8_epi64(_MM_K0_REG, v1)>
        endm

_mm512_cvtepu16_epi32 macro v1
        exitm<_mm512_maskz_cvtepu16_epi32(_MM_K0_REG, v1)>
        endm

_mm512_cvtepu16_epi64 macro v1
        exitm<_mm512_maskz_cvtepu16_epi64(_MM_K0_REG, v1)>
        endm

_mm512_cvtepu32_epi64 macro v1
        exitm<_mm512_maskz_cvtepu32_epi64(_MM_K0_REG, v1)>
        endm

_mm512_cvt_roundps_epi32 macro v1, e1
        exitm<_mm512_maskz_cvt_roundps_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundps_epi32 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundps_epi32(_MM_K0_REG,v1, e1)>
        endm

_mm512_cvt_roundps_epu32 macro v1, e1
        exitm<_mm512_maskz_cvt_roundps_epu32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundps_epu32 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundps_epu32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundpd_epi32 macro v1, e1
        exitm<_mm512_maskz_cvt_roundpd_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundpd_epi32 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundpd_epi32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundpd_epu32 macro v1, e1
        exitm<_mm512_maskz_cvt_roundpd_epu32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundpd_epu32 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundpd_epu32(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtepi8_epi16 macro v1
        exitm<_mm512_maskz_cvtepi8_epi16(_MM_K0_REG64, v1)>
        endm

_mm512_cvtepu8_epi16 macro v1
        exitm<_mm512_maskz_cvtepu8_epi16(_MM_K0_REG64, v1)>
        endm

_mm512_cvtepi16_epi8 macro v1
        exitm<_mm512_maskz_cvtepi16_epi8(_MM_K0_REG64, v1)>
        endm

_mm512_cvtsepi16_epi8 macro v1
        exitm<_mm512_maskz_cvtsepi16_epi8(_MM_K0_REG64, v1)>
        endm

_mm512_cvtusepi16_epi8 macro v1
        exitm<_mm512_maskz_cvtusepi16_epi8(_MM_K0_REG64, v1)>
        endm

_mm512_cvt_roundepi64_pd macro v1, e1
        exitm<_mm512_maskz_cvt_roundepi64_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundepu64_pd macro v1, e1
        exitm<_mm512_maskz_cvt_roundepu64_pd(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundpd_epi64 macro v1, e1
        exitm<_mm512_maskz_cvt_roundpd_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundpd_epu64 macro v1, e1
        exitm<_mm512_maskz_cvt_roundpd_epu64(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundpd_epi64 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundpd_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundpd_epu64 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundpd_epu64(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundps_epi64 macro v1, e1
        exitm<_mm512_maskz_cvt_roundps_epi64(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvt_roundps_epu64 macro v1, e1
        exitm<_mm512_maskz_cvt_roundps_epu64(_MM_K0_REG, v1, e1)>
        endm

_mm512_cvtt_roundps_epi64 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundps_epi64(_MM_K0_REG,v1, e1)>
        endm

_mm512_cvtt_roundps_epu64 macro v1, e1
        exitm<_mm512_maskz_cvtt_roundps_epu64(_MM_K0_REG, v1, e1)>
        endm


_mm512_cvtepi32_ps macro v
        exitm<_mm512_cvt_roundepi32_ps(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtepi32_ps macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundepi32_ps(v1, _k1, v2)>
        endm

_mm512_maskz_cvtepi32_ps macro _k1, v2
        exitm<_mm512_maskz_cvt_roundepi32_ps(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtepu32_ps macro v
        exitm<_mm512_cvt_roundepu32_ps(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtepu32_ps macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundepu32_ps(v1, _k1, v2)>
        endm

_mm512_maskz_cvtepu32_ps macro _k1, v2
        exitm<_mm512_maskz_cvt_roundepu32_ps(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtps_epi32 macro v
        exitm<_mm512_cvt_roundps_epi32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtps_epi32 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundps_epi32(v1, _k1, v2)>
        endm

_mm512_maskz_cvtps_epi32 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundps_epi32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttps_epi32 macro v
        exitm<_mm512_cvtt_roundps_epi32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttps_epi32 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundps_epi32(v1, _k1, v2)>
        endm

_mm512_maskz_cvttps_epi32 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundps_epi32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtps_epu32 macro v
        exitm<_mm512_cvt_roundps_epu32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtps_epu32 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundps_epu32(v1, _k1, v2)>
        endm

_mm512_maskz_cvtps_epu32 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundps_epu32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttps_epu32 macro v
        exitm<_mm512_cvtt_roundps_epu32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttps_epu32 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundps_epu32(v1, _k1, v2)>
        endm

_mm512_maskz_cvttps_epu32 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundps_epu32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtpd_epi32 macro v
        exitm<_mm512_cvt_roundpd_epi32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtpd_epi32 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundpd_epi32(v1, _k1, v2)>
        endm

_mm512_maskz_cvtpd_epi32 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundpd_epi32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttpd_epi32 macro v
        exitm<_mm512_cvtt_roundpd_epi32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttpd_epi32 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundpd_epi32(v1, _k1, v2)>
        endm

_mm512_maskz_cvttpd_epi32 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundpd_epi32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtpd_epu32 macro v
        exitm<_mm512_cvt_roundpd_epu32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtpd_epu32 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundpd_epu32(v1,_k1, v2)>
        endm

_mm512_maskz_cvtpd_epu32 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundpd_epu32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttpd_epu32 macro v
        exitm<_mm512_cvtt_roundpd_epu32(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttpd_epu32 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundpd_epu32(v1, _k1, v2)>
        endm

_mm512_maskz_cvttpd_epu32 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundpd_epu32(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtph_ps macro v1
        exitm<_mm512_cvt_roundph_ps(v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtph_ps macro v1, k, v2
        exitm<_mm512_mask_cvt_roundph_ps(v1, k, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_maskz_cvtph_ps macro k, v1
        exitm<_mm512_maskz_cvt_roundph_ps(k, v1, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtps_ph macro v1, a
        exitm<_mm512_cvt_roundps_ph(v1, a)>
        endm

_mm512_mask_cvtps_ph macro v1, k, v2, a
        exitm<_mm512_mask_cvt_roundps_ph(v1, k, v2, a)>
        endm

_mm512_maskz_cvtps_ph macro k, v2, a
        exitm<_mm512_maskz_cvt_roundps_ph(k, v2, a)>
        endm

_mm512_cvtepi64_pd macro v
        exitm<_mm512_cvt_roundepi64_pd(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtepi64_pd macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundepi64_pd(v1, _k1, v2)>
        endm

_mm512_maskz_cvtepi64_pd macro _k1, v2
        exitm<_mm512_maskz_cvt_roundepi64_pd(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtepu64_pd macro v
        exitm<_mm512_cvt_roundepu64_pd(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtepu64_pd macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundepu64_pd(v1, _k1, v2)>
        endm

_mm512_maskz_cvtepu64_pd macro _k1, v2
        exitm<_mm512_maskz_cvt_roundepu64_pd(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtpd_epi64 macro v
        exitm<_mm512_cvt_roundpd_epi64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtpd_epi64 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundpd_epi64(v1, _k1, v2)>
        endm

_mm512_maskz_cvtpd_epi64 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundpd_epi64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtpd_epu64 macro v
        exitm<_mm512_cvt_roundpd_epu64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtpd_epu64 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundpd_epu64(v1, _k1, v2)>
        endm

_mm512_maskz_cvtpd_epu64 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundpd_epu64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttpd_epi64 macro v
        exitm<_mm512_cvtt_roundpd_epi64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttpd_epi64 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundpd_epi64(v1, _k1, v2)>
        endm

_mm512_maskz_cvttpd_epi64 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundpd_epi64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm


_mm512_cvttpd_epu64 macro v
        exitm<_mm512_cvtt_roundpd_epu64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttpd_epu64 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundpd_epu64(v1, _k1, v2)>
        endm

_mm512_maskz_cvttpd_epu64 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundpd_epu64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtps_epi64 macro v
        exitm<_mm512_cvt_roundps_epi64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtps_epi64 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundps_epi64(v1, _k1, v2)>
        endm

_mm512_maskz_cvtps_epi64 macro _k1, v2
        exitm<_mm512_maskz_cvt_roundps_epi64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtps_epu64 macro v
        exitm<_mm512_cvt_roundps_epu64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtps_epu64 macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundps_epu64(v1, _k1, v2)>
        endm

_mm512_maskz_cvtps_epu64 macro _k1, v2
        exitm< _mm512_maskz_cvt_roundps_epu64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtepi64_ps macro v
        exitm< _mm512_cvt_roundepi64_ps(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtepi64_ps macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundepi64_ps(v1, _k1, v2)>
        endm

_mm512_maskz_cvtepi64_ps macro _k1, v2
        exitm<_mm512_maskz_cvt_roundepi64_ps(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvtepu64_ps macro v
        exitm<_mm512_cvt_roundepu64_ps(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvtepu64_ps macro v1, _k1, v2
        exitm<_mm512_mask_cvt_roundepu64_ps(v1, _k1, v2)>
        endm

_mm512_maskz_cvtepu64_ps macro _k1, v2
        exitm<_mm512_maskz_cvt_roundepu64_ps(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttps_epi64 macro v
        exitm<_mm512_cvtt_roundps_epi64(v, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_mask_cvttps_epi64 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundps_epi64(v1, _k1, v2)>
        endm

_mm512_maskz_cvttps_epi64 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundps_epi64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

_mm512_cvttps_epu64 macro v
        exitm<>
        endm

_mm512_mask_cvttps_epu64 macro v1, _k1, v2
        exitm<_mm512_mask_cvtt_roundps_epu64(v1, _k1, v2)>
        endm

_mm512_maskz_cvttps_epu64 macro _k1, v2
        exitm<_mm512_maskz_cvtt_roundps_epu64(_k1, v2, _MM_FROUND_CUR_DIRECTION)>
        endm

endif


