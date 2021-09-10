ifndef _DVEC_H_INCLUDED
_DVEC_H_INCLUDED equ <>

include immintrin.inc
include fvec.inc
include vcruntime.inc

.pragma list(push, 0)
.pragma pack(push, 16) ;; Must ensure class & union 16-B aligned

__f64vec2_abs_mask_cheat equ <{-1, 0x7fffffff, -1, 0x7fffffff}>

;;
;; EMM Functionality Intrinsics
;;
;; I8vec16      16 elements, each element a signed or unsigned char data type
;; Is8vec16     16 elements, each element a signed char data type
;; Iu8vec16     16 elements, each element an unsigned char data type
;; I16vec8       8 elements, each element a signed or unsigned short
;; Is16vec8      8 elements, each element a signed short
;; Iu16vec8      8 elements, each element an unsigned short
;; I32vec4       4 elements, each element a signed or unsigned long
;; Is32vec4      4 elements, each element a signed long
;; Iu32vec4      4 elements, each element a unsigned long
;; I64vec2       2 element, each a __m64 data type
;; I128vec1      1 element, a __m128i data type
;;

ifdef M128
undef M128
endif
ifdef PM128
undef PM128
endif

    vec256_t typedef yword

_f64vec2_abs_mask macro x:=<xmm2>
    pcmpeqq x,x
    psrlq   x,1
    exitm  <x>
    endm

get_mask128 macro x:=<xmm2>
    pcmpeqd x,x
    exitm  <x>
    endm


;; 1 element, a __m128i data type

.template M128

    vec __m128i <>

    .inline M128 :vararg {
        ifidn typeid(this),<M128>
            this.Init(_1)
        else
            [rcx].M128.typeid(M128_, this)(_1)
        endif
        }
        .inline M128_imm :vararg {
          local n
           .new n:M128
            n.Init(_1)
            lea rax,n
            }

    .inline Init :abs, :vararg {
        ifnb <_1>
            ifidn typeid(this),<M128>
                lea rcx,this
            endif
            [rcx].M128.typeid(Init_, _1)(_1)
        endif
        }
        .inline Init_flt :abs {
            movaps xmm0,{ _1, _1, _1, _1 }
            }

    .inline __m128i {
        _mm_store_ps(xmm0, [this])
        }
    .inline andnot :vec128_t {
        _mm_andnot_si128(xmm0, _1)
        }
    .ends
    PM128 typedef ptr M128


;; 1 element, a __m128i data type

.template I128vec1 : public M128

    .ends


;; 2 elements, each element signed or unsigned 64-bit integer

.template I64vec2 : public M128

    .inline unpack_low :vec128_t {
        _mm_unpacklo_epi64(xmm0, _1)
        }
    .inline unpack_high :vec128_t {
        _mm_unpackhi_epi64(xmm0, _1)
        }
    .inline sum_abs :vec128_t {
        _mm_sad_epu8(xmm0, _1)
        }
    .ends

.pragma list(push, 1)

;; 4 elements, each element either a signed or unsigned int

.template I32vec4 : public M128

    .inline cmpeq :vec128_t {
        _mm_cmpeq_epi32(xmm0, _1)
        }
    .inline cmpneq :vec128_t {
        _mm_andnot_si128(_mm_cmpeq_epi32(xmm0, _1), get_mask128())
        }
    .inline unpack_low :vec128_t {
        _mm_unpacklo_epi32(xmm0, _1)
        }
    .inline unpack_high :vec128_t {
        _mm_unpackhi_epi32(xmm0, _1)
        }
    .ends


;; 4 elements, each element signed integer

.template Is32vec4 : public I32vec4

    .inline cmpgt :vec128_t { _mm_cmpgt_epi32(xmm0, _1) }
    .inline cmplt :vec128_t { _mm_cmpgt_epi32(xmm0, _1) }

if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        mov r8d,[this+0x0C]
        mov r9d,[this+0x08]
        mov r10d,[this+0x04]
        mov r11d,[this+0x00]
        printf( addr @CStr("%s\n [3]:%d\n [2]:%d\n [1]:%d\n [0]:%d\n"), _1, r8d, r9d, r10d, r11d )
        mov this,this_ptr
        }
endif
    .ends

.pragma list(pop)

;; 4 elements, each element unsigned int

.template Iu32vec4 : public I32vec4

if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        mov r8d,[this+0x0C]
        mov r9d,[this+0x08]
        mov r10d,[this+0x04]
        mov r11d,[this+0x00]
        printf( addr @CStr("%s\n [3]:%d\n [2]:%d\n [1]:%d\n [0]:%d\n"), _1, r8d, r9d, r10d, r11d )
        mov this,this_ptr
        }
endif
    .ends


;; 8 elements, each element either unsigned or signed short

.template I16vec8 : public M128

    .inline rmul16 :vec128_t {
        _mm_mullo_epi16(xmm0, _1)
        }
    .inline cmpeq :vec128_t {
        _mm_cmpeq_epi16(xmm0, _1)
        }
    .inline cmpneq :vec128_t {
        _mm_andnot_si128(_mm_cmpeq_epi16(xmm0, _1), get_mask128())
        }
    .inline unpack_low :vec128_t {
        _mm_unpacklo_epi16(xmm0, _1)
        }
    .inline unpack_high :vec128_t {
        _mm_unpackhi_epi16(xmm0, _1)
        }
    .inline pack_sat :vec128_t {
        _mm_packs_epi32(xmm0, _1)
        }
    .ends


;; 8 elements, each element signed short

.template Is16vec8 : public I16vec8

    .inline cmpgt     :vec128_t { _mm_cmpgt_epi16(xmm0, _1) }
    .inline cmplt     :vec128_t { _mm_cmpgt_epi16(xmm0, _1) }
    .inline mul_high  :vec128_t { _mm_mulhi_epi16(xmm0, _1) }
    .inline mul_add   :vec128_t { _mm_madd_epi16 (xmm0, _1) }
    .inline sat_add   :vec128_t { _mm_adds_epi16 (xmm0, _1) }
    .inline sat_sub   :vec128_t { _mm_subs_epi16 (xmm0, _1) }
    .inline simd_max  :vec128_t { _mm_max_epi16  (xmm0, _1) }
    .inline simd_min  :vec128_t { _mm_min_epi16  (xmm0, _1) }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [7]:%d\n [6]:%d\n [5]:%d\n [4]:%d\n [3]:%d\n [2]:%d\n [1]:%d\n [0]:%d\n"),\
            _1,\
            word ptr [this+0x0E],\
            word ptr [this+0x0C],\
            word ptr [this+0x0A],\
            word ptr [this+0x08],\
            word ptr [this+0x06],\
            word ptr [this+0x04],\
            word ptr [this+0x02],\
            word ptr [this+0x00] )
        mov this,this_ptr
        }
endif
    .ends

;; 8 elements, each element unsigned short

.template Iu16vec8 : public I16vec8

    .inline sat_add   :vec128_t { _mm_adds_epu16 (xmm0, _1) }
    .inline sat_sub   :vec128_t { _mm_subs_epu16 (xmm0, _1) }
    .inline simd_avg  :vec128_t { _mm_avg_epu16  (xmm0, _1) }
    .inline mul_high  :vec128_t { _mm_mulhi_epu16(xmm0, _1) }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [7]:%u\n [6]:%u\n [5]:%u\n [4]:%u\n [3]:%u\n [2]:%u\n [1]:%u\n [0]:%u\n"),\
            _1,\
            word ptr [this+0x0E],\
            word ptr [this+0x0C],\
            word ptr [this+0x0A],\
            word ptr [this+0x08],\
            word ptr [this+0x06],\
            word ptr [this+0x04],\
            word ptr [this+0x02],\
            word ptr [this+0x00] )
        mov this,this_ptr
        }
endif
    .ends


;; 16 elements, each element either unsigned or signed char

.template I8vec16 : public M128

    .inline cmpeq :vec128_t {
        _mm_cmpeq_epi8(xmm0, _1)
        }
    .inline cmpneq :vec128_t {
        _mm_andnot_si128(_mm_cmpeq_epi8(xmm0, _1), get_mask128())
        }
    .inline unpack_low :vec128_t {
        _mm_unpacklo_epi8(xmm0, _1)
        }
    .inline unpack_high :vec128_t {
        _mm_unpackhi_epi8(xmm0, _1)
        }
    .ends


;; 16 elements, each element a signed char

.template Is8vec16 : public I8vec16

    .inline cmpgt :vec128_t { _mm_cmpgt_epi8(xmm0, _1) }
    .inline cmplt :vec128_t {
        _mm_cmplt_epi8(xmm2, xmm0, _1)
        _mm_store_ps(xmm0, xmm2)
        }
    .inline sat_add  :vec128_t { _mm_adds_epi8  (xmm0, _1) }
    .inline sat_sub  :vec128_t { _mm_subs_epi8  (xmm0, _1) }
    .inline pack_sat :vec128_t { _mm_packs_epi16(xmm0, _1) }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [15]:%u\n [14]:%u\n [13]:%u\n [12]:%u\n [11]:%u\n [10]:%u\n [9]:%u\n [8]:%u\n [7]:%u\n [6]:%u\n [5]:%u\n [4]:%u\n [3]:%u\n [2]:%u\n [1]:%u\n [0]:%u\n"),\
            _1,\
            byte ptr [this+0x0F],\
            byte ptr [this+0x0E],\
            byte ptr [this+0x0D],\
            byte ptr [this+0x0C],\
            byte ptr [this+0x0B],\
            byte ptr [this+0x0A],\
            byte ptr [this+0x09],\
            byte ptr [this+0x08],\
            byte ptr [this+0x07],\
            byte ptr [this+0x06],\
            byte ptr [this+0x05],\
            byte ptr [this+0x04],\
            byte ptr [this+0x03],\
            byte ptr [this+0x02],\
            byte ptr [this+0x01],\
            byte ptr [this+0x00] )
        mov this,this_ptr
        }
endif
    .ends


;; 16 elements, each element a unsigned char

.template Iu8vec16 : public I8vec16

    .inline sat_add   :vec128_t { _mm_adds_epu8(xmm0, _1) }
    .inline sat_sub   :vec128_t { _mm_subs_epu8(xmm0, _1) }
    .inline simd_avg  :vec128_t { _mm_avg_epu8(xmm0, _1) }
    .inline simd_max  :vec128_t { _mm_max_epu8(xmm0, _1) }
    .inline simd_min  :vec128_t { _mm_min_epu8(xmm0, _1) }
    .inline packu_sat :vec128_t { _mm_packus_epi16(xmm0, _1) }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [15]:%u\n [14]:%u\n [13]:%u\n [12]:%u\n [11]:%u\n [10]:%u\n [9]:%u\n [8]:%u\n [7]:%u\n [6]:%u\n [5]:%u\n [4]:%u\n [3]:%u\n [2]:%u\n [1]:%u\n [0]:%u\n"),\
            _1,\
            byte ptr [this+0x0F],\
            byte ptr [this+0x0E],\
            byte ptr [this+0x0D],\
            byte ptr [this+0x0C],\
            byte ptr [this+0x0B],\
            byte ptr [this+0x0A],\
            byte ptr [this+0x09],\
            byte ptr [this+0x08],\
            byte ptr [this+0x07],\
            byte ptr [this+0x06],\
            byte ptr [this+0x05],\
            byte ptr [this+0x04],\
            byte ptr [this+0x03],\
            byte ptr [this+0x02],\
            byte ptr [this+0x01],\
            byte ptr [this+0x00] )
        mov this,this_ptr
        }
endif
    .ends


    IVEC128_SELECT macro vect12, vect34, element, selop
        I&vect34&vec&element&_select_&selop& proto :vec128_t, :vec128_t, :vec128_t, :vec128_t
        I&vect34&vec&element&_select_&selop& macro _A, _B, _C, _D
            I&vect34&vec&element&_cmp&selop&(_A, _B)
             _mm_store_ps(_B, _A)
            I&vect34&vec&element&_rand16(_A, _C)
            _mm_andnot_si128(_B, _D)
            I&vect34&vec&element&_ror16(_A, _B)
            exitm<>
            endm
        exitm<>
        endm

    IVEC128_SELECT(8,s8,16,eq)
    IVEC128_SELECT(8,u8,16,eq)
    IVEC128_SELECT(8,8,16,eq)
    IVEC128_SELECT(8,s8,16,neq)
    IVEC128_SELECT(8,u8,16,neq)
    IVEC128_SELECT(8,8,16,neq)

    IVEC128_SELECT(16,s16,8,eq)
    IVEC128_SELECT(16,u16,8,eq)
    IVEC128_SELECT(16,16,8,eq)
    IVEC128_SELECT(16,s16,8,neq)
    IVEC128_SELECT(16,u16,8,neq)
    IVEC128_SELECT(16,16,8,neq)

    IVEC128_SELECT(32,s32,4,eq)
    IVEC128_SELECT(32,u32,4,eq)
    IVEC128_SELECT(32,32,4,eq)
    IVEC128_SELECT(32,s32,4,neq)
    IVEC128_SELECT(32,u32,4,neq)
    IVEC128_SELECT(32,32,4,neq)

    IVEC128_SELECT(s8,s8,16,gt)
    IVEC128_SELECT(s8,u8,16,gt)
    IVEC128_SELECT(s8,8,16,gt)
    IVEC128_SELECT(s8,s8,16,lt)
    IVEC128_SELECT(s8,u8,16,lt)
    IVEC128_SELECT(s8,8,16,lt)

    IVEC128_SELECT(s16,s16,8,gt)
    IVEC128_SELECT(s16,u16,8,gt)
    IVEC128_SELECT(s16,16,8,gt)
    IVEC128_SELECT(s16,s16,8,lt)
    IVEC128_SELECT(s16,u16,8,lt)
    IVEC128_SELECT(s16,16,8,lt)
    undef IVEC128_SELECT


.template F64vec2
    vec __m128d <>

    .inline add_horizontal {
        _mm_move_pd(xmm1, xmm0)
        _mm_shuffle_pd(xmm1, xmm1, 1)
        _mm_add_sd(xmm0, xmm1)
        _mm_cvtsd_f64(xmm0) }

    .inline andnot :vec128_t { _mm_andnot_pd(xmm0, _1) }
    .inline sqrt { _mm_sqrt_pd(xmm0, xmm0) }

    .inline cmpeq  :vec128_t      { _mm_cmpeq_pd (xmm0, _1) }
    .inline cmplt  :vec128_t      { _mm_cmplt_pd (xmm0, _1) }
    .inline cmple  :vec128_t      { _mm_cmple_pd (xmm0, _1) }
    .inline cmpgt  :vec128_t {
        _mm_cmpgt_pd (_1, xmm0, _1)
        _mm_move_pd(xmm0, _1)
        }
    .inline cmpge  :vec128_t {
        _mm_cmpge_pd (_1, xmm0, _1)
        _mm_move_pd(xmm0, _1)
        }
    .inline cmpngt :vec128_t {
        _mm_cmpngt_pd(_1, xmm0, _1)
        _mm_move_pd(xmm0, _1)
        }
    .inline cmpnge :vec128_t      { _mm_cmpnge_pd(xmm0, _1) }
    .inline cmpnlt :vec128_t      { _mm_cmpnlt_pd(xmm0, _1) }
    .inline cmpnle :vec128_t      { _mm_cmpnle_pd(xmm0, _1) }

    .inline simd_min :vec128_t    { _mm_min_pd(xmm0, _1) }
    .inline simd_max :vec128_t    { _mm_max_pd(xmm0, _1) }
    .inline abs                   { _mm_and_pd(xmm0, _f64vec2_abs_mask(xmm1)) }

    .inline comieq   :vec128_t    { _mm_comieq_sd(xmm0, _1) }
    .inline comilt   :vec128_t    { _mm_comilt_sd(xmm0, _1) }
    .inline comile   :vec128_t    { _mm_comile_sd(xmm0, _1) }
    .inline comigt   :vec128_t    { _mm_comigt_sd(xmm0, _1) }
    .inline comige   :vec128_t    { _mm_comige_sd(xmm0, _1) }
    .inline comineq  :vec128_t    { _mm_comineq_sd(xmm0, _1) }

    .inline ucomieq  :vec128_t    { _mm_ucomieq_sd(xmm0, _1) }
    .inline ucomilt  :vec128_t    { _mm_ucomilt_sd(xmm0, _1) }
    .inline ucomile  :vec128_t    { _mm_ucomile_sd(xmm0, _1) }
    .inline ucomigt  :vec128_t    { _mm_ucomigt_sd(xmm0, _1) }
    .inline ucomige  :vec128_t    { _mm_ucomige_sd(xmm0, _1) }
    .inline ucomineq :vec128_t    { _mm_ucomineq_sd(xmm0, _1) }

    .inline unpack_low  :vec128_t { _mm_unpacklo_pd(xmm0, _1) }
    .inline unpack_high :vec128_t { _mm_unpackhi_pd(xmm0, _1) }
    .inline move_mask             { _mm_movemask_pd(xmm0) }
    .inline loadu                 { _mm_loadu_pd([this]) }
    .inline storeu                { _mm_storeu_pd([this], xmm0) }
    .inline store_nta             { _mm_stream_pd([this], xmm0) }

    F64vec2_SELECT macro op
        .inline select_&op& :vec128_t, :vec128_t, :vec128_t {
            _mm_cmp&op&_pd(xmm0, _1)
            _mm_store_ps(_1, xmm0)
            _mm_and_pd(xmm0, _2)
            _mm_andnot_pd(_1, _3)
            _mm_or_pd(xmm0, _1)
            }
        exitm<>
        endm
        F64vec2_SELECT(eq)
        F64vec2_SELECT(lt)
        F64vec2_SELECT(le)
        F64vec2_SELECT(neq)
        F64vec2_SELECT(nlt)
        F64vec2_SELECT(nle)
        F64vec2_SELECT(ngt)
        F64vec2_SELECT(nge)
        undef F64vec2_SELECT

    .inline select_gt :vec128_t, :vec128_t, :vec128_t {
        _mm_cmpgt_pd(_1, xmm0, _1)
        _mm_store_ps(xmm0, _1)
        _mm_and_pd(xmm0, _2)
        _mm_andnot_pd(_1, _3)
        _mm_or_pd(xmm0, _1)
        }
    .inline select_ge :vec128_t, :vec128_t, :vec128_t {
        _mm_cmpge_pd(_1, xmm0, _1)
        _mm_store_ps(xmm0, _1)
        _mm_and_pd(xmm0, _2)
        _mm_andnot_pd(_1, _3)
        _mm_or_pd(xmm0, _1)
        }

    .inline ToInt {
        _mm_cvttsd_si32(xmm0)
        }
    .inline ToF32vec4 {
        _mm_cvtpd_ps(xmm0)
        }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [1]:%f\n [0]:%f\n"),\
            _1,\
            qword ptr [this+0x08],\
            qword ptr [this+0x00] )
        mov this,this_ptr
        }
endif
    .ends


F32vec4ToF64vec2    proto :vec128_t
IntToF64vec2        proto :vec128_t, :int_t

F32vec4ToF64vec2 macro _A
    exitm<_mm_cvtps_pd(_A)>
    endm
IntToF64vec2 macro _A, _B
    exitm<_mm_cvtsi32_sd(_A, _B)>
    endm


;; Interface classes for Intel(R) AVX intrinsics

;; Represents 256-bit vector composed of 8 single precision floating point elements.

.template F32vec8
    vec __m256 <>

    .inline __m256 {
        _mm256_store_ps(ymm0, [this]) }

    .inline add_horizontal {
        _mm256_store_ps(ymm1, ymm0)
        _mm256_add_ps(ymm0, _mm256_permute_ps(ymm1, 0xee))
        _mm256_add_ps(ymm0, _mm256_movehdup_ps(_mm256_store_ps(ymm1, ymm0)))
        _mm_cvtss_f32(_mm_add_ss(_mm256_castps256_ps128(ymm0), _mm256_extractf128_ps(ymm0, 1)))
        }
    .inline andnot :vec256_t {
        _mm256_andnot_ps(ymm0, _1)
        }
    .inline sqrt {
        _mm256_sqrt_ps(ymm0)
        }
    .inline rcp {
        _mm256_rcp_ps(ymm0)
        }
    .inline rsqrt {
        _mm256_rsqrt_ps(ymm0)
        }
    .inline rcp_nr {
        vrcpps ymm1,ymm0
        vmulps ymm0,ymm1,ymm0
        vmulps ymm0,ymm0,ymm1
        vaddps ymm1,ymm1,ymm1
        vsubps ymm0,ymm1,ymm0
        }
    .inline rsqrt_nr {
        vrsqrtps ymm1,ymm0
        vmulps ymm0,ymm0,ymm1
        vmulps ymm2,ymm0,ymm1
        vmulps ymm0,ymm1,_mm256_set_epi32(5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0)
        _mm256_sub_ps(_mm256_set_epi32(ymm1, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0), ymm2)
        _mm256_mul_ps(ymm0, ymm1)
        }

    .inline cmp_eq    :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_EQ_OQ) }
    .inline cmp_lt    :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_LT_OS) }
    .inline cmp_le    :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_LE_OS) }
    .inline cmp_gt    :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_GT_OS) }
    .inline cmp_ge    :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_GE_OS) }
    .inline cmp_neq   :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_NEQ_UQ) }
    .inline cmp_nlt   :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_NLT_US) }
    .inline cmp_nle   :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_NLE_US) }
    .inline cmp_ngt   :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_NGT_US) }
    .inline cmp_nge   :vec256_t { _mm256_cmp_ps(ymm0, _1, _CMP_NGE_US) }

    .inline simd_min  :vec256_t { _mm256_min_ps(ymm0, _1) }
    .inline simd_max  :vec256_t { _mm256_max_ps(ymm0, _1) }
    .inline abs {
        vpcmpeqw ymm1,ymm1,ymm1
        vpsrld ymm1,ymm1,1
        _mm256_and_ps(ymm0, ymm1)
        }

    .inline unpack_low    :vec256_t { _mm256_unpacklo_ps(ymm0, _1) }
    .inline unpack_high   :vec256_t { _mm256_unpackhi_ps(ymm0, _1) }
    .inline move_mask     { _mm256_movemask_ps(ymm0) }
    .inline loadu         { _mm256_loadu_ps([this], ymm0) }
    .inline storeu        { _mm256_storeu_ps([this], ymm0) }
    .inline store_nta     { _mm256_stream_ps([this], ymm0) }
    .inline maskload      { _mm256_maskload_ps([this], ymm0) }
    .inline maskstore :vec256_t {
        _mm256_maskstore_ps([this], _1, ymm0)
        }

    .inline select_eq :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_EQ_OQ))
        }
    .inline select_lt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_LT_OS))
        }
    .inline select_le :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_LE_OS))
        }
    .inline select_gt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_GT_OS))
        }
    .inline select_ge :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_GE_OS))
        }
    .inline select_neq :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NEQ_UQ))
        }
    .inline select_nlt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NLT_US))
        }
    .inline select_nle :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NLE_US))
        }
    .inline select_ngt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NGT_US))
        }
    .inline select_nge :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NGE_US))
        }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        movq r8, _mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x1C]))
        movq r9, _mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x18]))
        movq r10,_mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x14]))
        movq r11,_mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x10]))
        printf( addr @CStr("%s\n [7]:%f\n [6]:%f\n [5]:%f\n [4]:%f\n"),\
            _1, r8, r9, r10, r11 )
        mov this,this_ptr
        movq rdx,_mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x0C]))
        movq r8, _mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x08]))
        movq r9, _mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x04]))
        movq r10,_mm_cvtss_sd(_mm_move_ss(xmm0, [this+0x00]))
        printf( addr @CStr(" [3]:%f\n [2]:%f\n [1]:%f\n [0]:%f\n"), rdx, r8, r9, r10 )
        mov this,this_ptr
        }
endif
    .ends


.template F64vec4
    vec __m256d <>

    .inline __m256 {
        _mm256_store_ps(ymm0, [this])
        }

    .inline add_horizontal {
        _mm256_store_pd(ymm1, ymm0)
        _mm256_add_pd(ymm0, _mm256_permute_pd(ymm1, 0x05))
        _mm256_add_pd(ymm0, _mm256_movehdup_ps(_mm256_store_ps(ymm1, ymm0)))
        _mm_cvtsd_f64(_mm_add_sd(_mm256_castps256_ps128(ymm0), _mm256_extractf128_pd(ymm0, 1)))
        }
    .inline andnot    :vec256_t { _mm256_andnot_pd(ymm0, _1) }
    .inline sqrt                { _mm256_sqrt_pd(ymm0) }

    .inline cmp_eq    :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_EQ_OQ) }
    .inline cmp_lt    :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_LT_OS) }
    .inline cmp_le    :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_LE_OS) }
    .inline cmp_gt    :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_GT_OS) }
    .inline cmp_ge    :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_GE_OS) }
    .inline cmp_neq   :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_NEQ_UQ) }
    .inline cmp_nlt   :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_NLT_US) }
    .inline cmp_nle   :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_NLE_US) }
    .inline cmp_ngt   :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_NGT_US) }
    .inline cmp_nge   :vec256_t { _mm256_cmp_pd(ymm0, _1, _CMP_NGE_US) }

    .inline simd_min  :vec256_t { _mm256_min_pd(ymm0, _1) }
    .inline simd_max  :vec256_t { _mm256_max_pd(ymm0, _1) }
    .inline abs {
        vpcmpeqd ymm1,ymm1,ymm1
        vpsrlq ymm1,ymm1,1
        _mm256_and_pd(ymm0, ymm1)
        }

    .inline unpack_low    :vec256_t { _mm256_unpacklo_pd(ymm0, _1) }
    .inline unpack_high   :vec256_t { _mm256_unpackhi_pd(ymm0, _1) }
    .inline move_mask     { _mm256_movemask_pd() }
    .inline loadu         { _mm256_loadu_pd   ([this], ymm0) }
    .inline storeu        { _mm256_storeu_pd  ([this], ymm0) }
    .inline store_nta     { _mm256_stream_pd  ([this], ymm0) }
    .inline maskload      { _mm256_maskload_pd([this], ymm0) }
    .inline maskstore :vec256_t {
        _mm256_maskstore_pd([this], _1, ymm0)
        }

    .inline select_eq :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_EQ_OQ))
        }
    .inline select_lt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_LT_OS))
        }
    .inline select_le :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_LE_OS))
        }
    .inline select_gt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_GT_OS))
        }
    .inline select_ge :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_GE_OS))
        }
    .inline select_neq :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NEQ_UQ))
        }
    .inline select_nlt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NLT_US))
        }
    .inline select_nle :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NLE_US))
        }
    .inline select_ngt :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NGT_US))
        }
    .inline select_nge :vec256_t, :vec256_t, :vec256_t {
        _mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NGE_US))
        }
    .inline ToF32vec8 { _mm256_cvtpd_ps(ymm0)> }
if defined (_ENABLE_VEC_DEBUG)
    .inline cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [3]:%f\n [2]:%f\n [1]:%f\n [0]:%f\n"),\
            _1,\
            qword ptr [this+0x18],\
            qword ptr [this+0x10],\
            qword ptr [this+0x08],\
            qword ptr [this+0x00] )
        mov this,this_ptr
        }
endif
    .ends


F32vec4ToF64vec4 macro _A
    exitm<_mm256_cvtps_pd(_A)>
    endm

.pragma pack(pop)
.pragma list(pop)
endif ;; _DVEC_H_INCLUDED
