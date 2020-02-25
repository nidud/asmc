ifndef _DVEC_H_INCLUDED
_DVEC_H_INCLUDED equ <>

include immintrin.inc
include fvec.inc
include vcruntime.inc

.pragma list(push, 0)

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

    .operator = :vec128_t {
        exitm<_mm_store_ps([this], _1)>
        }
    .operator __m128i {
        exitm<_mm_store_ps(xmm0, [this])>
        }
    .operator &= :vec128_t {
        _mm_and_si128(xmm0, _1)
        exitm<_mm_store_ps([this],xmm0)>
        }
    .operator |= :vec128_t {
        _mm_or_si128(xmm0, _1)
        exitm<_mm_store_ps([this],xmm0)>
        }
    .operator ^= :vec128_t {
        _mm_xor_si128(xmm0, _1)
        exitm<_mm_store_ps([this],xmm0)>
        }
    .operator & :vec128_t {
        exitm<_mm_and_si128(xmm0, _1)>
        }
    .operator | :vec128_t {
        exitm<_mm_or_si128(xmm0, _1)>
        }
    .operator ^ :vec128_t {
        exitm<_mm_xor_si128(xmm0, _1)>
        }
    .operator andnot :vec128_t {
        exitm<_mm_andnot_si128(xmm0, _1)>
        }
    .ends
    PM128 typedef ptr M128

M128_OPERATOR macro class
    &class&___m128i macro this
        exitm<M128___m128i(this)>
        endm
    &class&_mequ16 macro this, _1
        exitm<M128_mequ16(this, _1)>
        endm
    &class&_mand16 macro this, _1
        exitm<M128_mand16(this, _1)>
        endm
    &class&_mor16 macro this, _1
        exitm<M128_mor16(this, _1)>
        endm
    &class&_mxor16 macro this, _1
        exitm<M128_mxor16(this, _1)>
        endm
    &class&_rand16 macro this, _1
        exitm<M128_rand16(this, _1)>
        endm
    &class&_ror16 macro this, _1
        exitm<M128_ror16(this, _1)>
        endm
    &class&_rxor16 macro this, _1
        exitm<M128_rxor16(this, _1)>
        endm
    &class&_andnot macro this, _1
        exitm<M128_andnot(this, _1)>
        endm
    exitm<>
    endm


;; 1 element, a __m128i data type

.template I128vec1 : public M128

    M128_OPERATOR(I128vec1)

    .ends


;; 2 elements, each element signed or unsigned 64-bit integer

.template I64vec2 : public M128

    M128_OPERATOR(I64vec2)

    .operator = :int64_t, :int64_t {
        mov [this+0],_1
        mov [this+8],_2
        exitm<I64vec2___m128i(this)>
        }
    .operator += :vec128_t {
        _mm_add_epi64(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator -= :vec128_t {
        _mm_sub_epi64(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator <<= :vec128_t {
        _mm_sll_epi64(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator >>= :vec128_t {
        _mm_srl_epi64(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator << :vec128_t {
        exitm<_mm_sll_epi64(xmm0, _1)>
        }
    .operator >> :vec128_t {
        exitm<_mm_srl_epi64(xmm0, _1)>
        }
    .operator unpack_low :vec128_t {
        exitm<_mm_unpacklo_epi64(xmm0, _1)>
        }
    .operator unpack_high :vec128_t {
        exitm<_mm_unpackhi_epi64(xmm0, _1)>
        }
    .operator sum_abs :vec128_t {
        exitm<_mm_sad_epu8(xmm0, _1)>
        }
    .operator << :abs {
        exitm<_mm_slli_epi64(xmm0, _1)>
        }
    .operator >> :abs {
        exitm<_mm_srli_epi64(xmm0, _1)>
        }
    .ends


;; 4 elements, each element either a signed or unsigned int

.template I32vec4 : public M128

    M128_OPERATOR(I32vec4)

    .operator = :abs, :abs, :abs, :abs {
        mov dword ptr [this+0x00],_4
        mov dword ptr [this+0x04],_3
        mov dword ptr [this+0x08],_2
        mov dword ptr [this+0x0C],_1
        exitm<I32vec4___m128i(this)>
        }
    .operator += :vec128_t {
        _mm_add_epi32(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator -= :vec128_t {
        _mm_sub_epi32(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator <<= :vec128_t {
        _mm_sll_epi32(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator >>= :vec128_t {
        _mm_srl_epi32(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator << :vec128_t {
        exitm<_mm_sll_epi32(xmm0, _1)>
        }
    .operator >> :vec128_t {
        exitm<_mm_srl_epi32(xmm0, _1)>
        }
    .operator cmpeq :vec128_t {
        exitm<_mm_cmpeq_epi32(xmm0, _1)>
        }
    .operator cmpneq :vec128_t {
        exitm<_mm_andnot_si128(_mm_cmpeq_epi32(xmm0, _1), get_mask128())>
        }
    .operator unpack_low :vec128_t {
        exitm<_mm_unpacklo_epi32(xmm0, _1)>
        }
    .operator unpack_high :vec128_t {
        exitm<_mm_unpackhi_epi32(xmm0, _1)>
        }
    .operator <<= :abs {
        _mm_slli_epi32(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator << :abs {
        exitm<_mm_slli_epi32(xmm0, _1)>
        }
    .ends

I32VEC4_OPERATOR macro class
    M128_OPERATOR(class)
    &class&_mequ888 macro this, _1, _2, _3, _4
        exitm<I32vec4_mequ888(this, _1, _2, _3, _4)>
        endm
    &class&_madd16 macro this, _1
        exitm<I32vec4_madd16(this, _1)>
        endm
    &class&_msub16 macro this, _1
        exitm<I32vec4_msub16(this, _1)>
        endm
    &class&_mshl16 macro this, _1
        exitm<I32vec4_mshl16(this, _1)>
        endm
    &class&_mshl8 macro this, _Count
        exitm<I32vec4_mshl8(this, _Count)>
        endm
    &class&_rshl16 macro this, _1
        exitm<I32vec4_rshl16(this, _1)>
        endm
    &class&_rshl8 macro this, _Count
        exitm<I32vec4_rshl8(this, _Count)>
        endm
    &class&_mshr16 macro this, _1
        exitm<I32vec4_mshr16(this, _1)>
        endm
    &class&_rshr16 macro this, _1
        exitm<I32vec4_rshr16(this, _1)>
        endm
    &class&_cmpeq macro this, _1
        exitm<I32vec4_cmpeq(this, _1)>
        endm
    &class&_cmpneq macro this, _1
        exitm<I32vec4_cmpneq(this, _1)>
        endm
    &class&_unpack_low macro this, _1
        exitm<I32vec4_unpack_low(this, _1)>
        endm
    &class&_unpack_high macro this, _1
        exitm<I32vec4_unpack_high(this, _1)>
        endm
    exitm<>
    endm


;; 4 elements, each element signed integer

.template Is32vec4 : public I32vec4

    I32VEC4_OPERATOR(Is32vec4)

    .operator cmpgt :vec128_t { exitm<_mm_cmpgt_epi32(xmm0, _1)> }
    .operator cmplt :vec128_t { exitm<_mm_cmpgt_epi32(xmm0, _1)> }

if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        mov r8d,[this+0x0C]
        mov r9d,[this+0x08]
        mov r10d,[this+0x04]
        mov r11d,[this+0x00]
        printf( addr @CStr("%s\n [3]:%d\n [2]:%d\n [1]:%d\n [0]:%d\n"), _1, r8d, r9d, r10d, r11d )
        mov this,this_ptr
        exitm<>
        }
endif
    .ends


;; 4 elements, each element unsigned int

.template Iu32vec4 : public I32vec4

    I32VEC4_OPERATOR(Iu32vec4)

    .operator * :vec128_t { exitm<_mm_mul_epu32(xmm0, _1)> }

if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        mov r8d,[this+0x0C]
        mov r9d,[this+0x08]
        mov r10d,[this+0x04]
        mov r11d,[this+0x00]
        printf( addr @CStr("%s\n [3]:%d\n [2]:%d\n [1]:%d\n [0]:%d\n"), _1, r8d, r9d, r10d, r11d )
        mov this,this_ptr
        exitm<>
        }
endif
    .ends


;; 8 elements, each element either unsigned or signed short

.template I16vec8 : public M128

    M128_OPERATOR(I16vec8)

    .operator = :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs {
        mov dword ptr [this+0x00],((_2 shl 16) or _1)
        mov dword ptr [this+0x04],((_4 shl 16) or _3)
        mov dword ptr [this+0x08],((_6 shl 16) or _5)
        mov dword ptr [this+0x0C],((_8 shl 16) or _7)
        exitm<I16vec8___m128i(this)>
        }
    .operator += :vec128_t {
        _mm_add_epi16(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator -= :vec128_t {
        _mm_sub_epi16(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator *= :vec128_t {
        _mm_mullo_epi16(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator <<  :vec128_t {
        exitm<_mm_sll_epi16(xmm0, _1)>
        }
    .operator <<= :vec128_t {
        _mm_sll_epi16(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator << :abs {
        exitm<_mm_slli_epi16(xmm0, _1)>
        }
    .operator <<= :abs {
        exitm<_mm_store_ps([this],_mm_slli_epi16(xmm0, _1))>
        }
    .operator rmul16 :vec128_t {
        exitm<_mm_mullo_epi16(xmm0, _1)>
        }
    .operator cmpeq :vec128_t {
        exitm<_mm_cmpeq_epi16(xmm0, _1)>
        }
    .operator cmpneq :vec128_t {
        exitm<_mm_andnot_si128(_mm_cmpeq_epi16(xmm0, _1), get_mask128())>
        }
    .operator unpack_low :vec128_t {
        exitm<_mm_unpacklo_epi16(xmm0, _1)>
        }
    .operator unpack_high :vec128_t {
        exitm<_mm_unpackhi_epi16(xmm0, _1)>
        }
    .operator pack_sat :vec128_t {
        exitm<_mm_packs_epi32(xmm0, _1)>
        }
    .ends

I16VEC8_OPERATOR macro class
    M128_OPERATOR(class)
    &class&_mequ888 macro this, _S7, _S6, _S5, _S4, _S3, _S2, _S1, _S0
        exitm<I16vec8_mequ888(this, _S7, _S6, _S5, _S4, _S3, _S2, _S1, _S0)>
        endm
    &class&_madd16 macro this, _1
        exitm<I16vec8_madd16(this, _1)>
        endm
    &class&_msub16 macro this, _1
        exitm<I16vec8_msub16(this, _1)>
        endm
    &class&_mmul16 macro this, _1
        exitm<I16vec8_mmul16(this, _1)>
        endm
    &class&_mshl16 macro this, _1
        exitm<I16vec8_mshl16(this, _1)>
        endm
    &class&_mshl8 macro this, _Count
        exitm<I16vec8_mshl8(this, _Count)>
        endm
    &class&_rshl16 macro this, _1
        exitm<I16vec8_rshl16(this, _1)>
        endm
    &class&_rshl8 macro this, _Count
        exitm<I16vec8_rshl8(this, _Count)>
        endm
    &class&_rmul16 macro this, _1
        exitm<I16vec8_rmul16(this, _1)>
        endm
    &class&_cmpeq macro this, _1
        exitm<I16vec8_cmpeq(this, _1)>
        endm
    &class&_cmpneq macro this, _1
        exitm<I16vec8_cmpneq(this, _1)>
        endm
    &class&_unpack_low macro this, _1
        exitm<I16vec8_unpack_low(this, _1)>
        endm
    &class&_unpack_high macro this, _1
        exitm<I16vec8_unpack_high(this, _1)>
        endm
    exitm<>
    endm


;; 8 elements, each element signed short

.template Is16vec8 : public I16vec8

    I16VEC8_OPERATOR(Is16vec8)

    .operator cmpgt     :vec128_t { exitm<_mm_cmpgt_epi16(xmm0, _1)> }
    .operator cmplt     :vec128_t { exitm<_mm_cmpgt_epi16(xmm0, _1)> }
    .operator mul_high  :vec128_t { exitm<_mm_mulhi_epi16(xmm0, _1)> }
    .operator mul_add   :vec128_t { exitm<_mm_madd_epi16 (xmm0, _1)> }
    .operator sat_add   :vec128_t { exitm<_mm_adds_epi16 (xmm0, _1)> }
    .operator sat_sub   :vec128_t { exitm<_mm_subs_epi16 (xmm0, _1)> }
    .operator simd_max  :vec128_t { exitm<_mm_max_epi16  (xmm0, _1)> }
    .operator simd_min  :vec128_t { exitm<_mm_min_epi16  (xmm0, _1)> }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
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
        exitm<>
        }
endif
    .ends

;; 8 elements, each element unsigned short

.template Iu16vec8 : public I16vec8

    I16VEC8_OPERATOR(Iu16vec8)

    .operator >>  :vec128_t { exitm<_mm_srl_epi16(xmm0, _1)> }
    .operator >>= :vec128_t {
        _mm_srl_epi16(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator sat_add   :vec128_t { exitm<_mm_adds_epu16 (xmm0, _1)> }
    .operator sat_sub   :vec128_t { exitm<_mm_subs_epu16 (xmm0, _1)> }
    .operator simd_avg  :vec128_t { exitm<_mm_avg_epu16  (xmm0, _1)> }
    .operator mul_high  :vec128_t { exitm<_mm_mulhi_epu16(xmm0, _1)> }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
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
        exitm<>
        }
endif
    .ends


;; 16 elements, each element either unsigned or signed char

.template I8vec16 : public M128

    M128_OPERATOR(I8vec16)

    .operator = :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs,\
                :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs {
        exitm<I16vec8_mequ888(this,
            ((_16 shl 8) or _15),
            ((_14 shl 8) or _13),
            ((_12 shl 8) or _11),
            ((_10 shl 8) or _9),
            (( _8 shl 8) or _7),
            (( _6 shl 8) or _5),
            (( _4 shl 8) or _3),
            (( _2 shl 8) or _1))>
        }
    .operator += :vec128_t {
        _mm_add_epi8(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator -= :vec128_t {
        _mm_sub_epi8(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)>
        }
    .operator cmpeq :vec128_t {
        exitm<_mm_cmpeq_epi8(xmm0, _1)>
        }
    .operator cmpneq :vec128_t {
        exitm<_mm_andnot_si128(_mm_cmpeq_epi8(xmm0, _1), get_mask128())>
        }
    .operator unpack_low :vec128_t {
        exitm<_mm_unpacklo_epi8(xmm0, _1)>
        }
    .operator unpack_high :vec128_t {
        exitm<_mm_unpackhi_epi8(xmm0, _1)>
        }
    .ends

I8VEC16_OPERATOR macro class
    M128_OPERATOR(class)
    &class&_mequ888 macro this, S15, S14, S13, S12, S11, S10, S9, S8, S7, S6, S5, S4, S3, S2, S1, S0
        exitm<I8vec16_mequ888(this, S15, S14, S13, S12, S11, S10, S9, S8, S7, S6, S5, S4, S3, S2, S1, S0)>
        endm
    &class&_madd16 macro this, _1
        exitm<I8vec16_madd16(this, _1)>
        endm
    &class&_msub16 macro this, _1
        exitm<I8vec16_msub16(this, _1)>
        endm
    &class&_cmpeq macro this, _1
        exitm<I8vec16_cmpeq(this, _1)>
        endm
    &class&_cmpneq macro this, _1
        exitm<I8vec16_cmpneq(this, _1)>
        endm
    &class&_unpack_low macro this, _1
        exitm<I8vec16_unpack_low(this, _1)>
        endm
    &class&_unpack_high macro this, _1
        exitm<I8vec16_unpack_high(this, _1)>
        endm
    exitm<>
    endm


;; 16 elements, each element a signed char

.template Is8vec16 : public I8vec16

    I8VEC16_OPERATOR(Is8vec16)

    .operator cmpgt :vec128_t { exitm<_mm_cmpgt_epi8(xmm0, _1)> }
    .operator cmplt :vec128_t {
        _mm_cmplt_epi8(xmm2, xmm0, _1)
        exitm<_mm_store_ps(xmm0, xmm2)>
        }
    .operator sat_add  :vec128_t { exitm<_mm_adds_epi8  (xmm0, _1)> }
    .operator sat_sub  :vec128_t { exitm<_mm_subs_epi8  (xmm0, _1)> }
    .operator pack_sat :vec128_t { exitm<_mm_packs_epi16(xmm0, _1)> }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
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
        exitm<>
        }
endif
    .ends


;; 16 elements, each element a unsigned char

.template Iu8vec16 : public I8vec16

    I8VEC16_OPERATOR(Iu8vec16)

    .operator sat_add   :vec128_t { exitm<_mm_adds_epu8(xmm0, _1)> }
    .operator sat_sub   :vec128_t { exitm<_mm_subs_epu8(xmm0, _1)> }
    .operator simd_avg  :vec128_t { exitm<_mm_avg_epu8(xmm0, _1)> }
    .operator simd_max  :vec128_t { exitm<_mm_max_epu8(xmm0, _1)> }
    .operator simd_min  :vec128_t { exitm<_mm_min_epu8(xmm0, _1)> }
    .operator packu_sat :vec128_t { exitm<_mm_packus_epi16(xmm0, _1)> }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
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
        exitm<>
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
            exitm<I&vect34&vec&element&_ror16(_A, _B)>
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

    .operator = :real8, :real8 {
        movsd [this+0],_1
        movsd [this+8],_2
        exitm<F64vec2___m128d(this)> }
    .operator = :vec128_t {
        exitm<_mm_store_ps([this], _mm_store_ps(xmm0, _1))> }
    .operator __m128d {
        exitm<_mm_store_ps(xmm0, [this])> }

    .operator & :vec128_t { exitm<_mm_and_pd(xmm0, _1)> }
    .operator | :vec128_t { exitm<_mm_or_pd (xmm0, _1)> }
    .operator ^ :vec128_t { exitm<_mm_xor_pd(xmm0, _1)> }
    .operator + :vec128_t { exitm<_mm_add_pd(xmm0, _1)> }
    .operator - :vec128_t { exitm<_mm_sub_pd(xmm0, _1)> }
    .operator * :vec128_t { exitm<_mm_mul_pd(xmm0, _1)> }
    .operator / :vec128_t { exitm<_mm_div_pd(xmm0, _1)> }

    .operator += :vec128_t {
        _mm_add_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }
    .operator -= :vec128_t {
        _mm_sub_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }
    .operator *= :vec128_t {
        _mm_mul_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }
    .operator /= :vec128_t {
        _mm_div_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }
    .operator &= :vec128_t {
        _mm_and_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }
    .operator |= :vec128_t {
        _mm_or_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }
    .operator ^= :vec128_t {
        _mm_xor_pd(xmm0, _1)
        exitm<_mm_store_ps([this], xmm0)> }

    .operator add_horizontal {
        _mm_move_pd(xmm1, xmm0)
        _mm_shuffle_pd(xmm1, xmm1, 1)
        _mm_add_sd(xmm0, xmm1)
        exitm<_mm_cvtsd_f64(xmm0)> }

    .operator andnot :vec128_t { exitm<_mm_andnot_pd(xmm0, _1)> }
    .operator sqrt { exitm<_mm_sqrt_pd(xmm0, xmm0)> }

    .operator cmpeq  :vec128_t      { exitm<_mm_cmpeq_pd (xmm0, _1)> }
    .operator cmplt  :vec128_t      { exitm<_mm_cmplt_pd (xmm0, _1)> }
    .operator cmple  :vec128_t      { exitm<_mm_cmple_pd (xmm0, _1)> }
    .operator cmpgt  :vec128_t {
        _mm_cmpgt_pd (_1, xmm0, _1)
        exitm<_mm_move_pd(xmm0, _1)>
        }
    .operator cmpge  :vec128_t {
        _mm_cmpge_pd (_1, xmm0, _1)
        exitm<_mm_move_pd(xmm0, _1)>
        }
    .operator cmpngt :vec128_t {
        _mm_cmpngt_pd(_1, xmm0, _1)
        exitm<_mm_move_pd(xmm0, _1)>
        }
    .operator cmpnge :vec128_t      { exitm<_mm_cmpnge_pd(xmm0, _1)> }
    .operator cmpnlt :vec128_t      { exitm<_mm_cmpnlt_pd(xmm0, _1)> }
    .operator cmpnle :vec128_t      { exitm<_mm_cmpnle_pd(xmm0, _1)> }

    .operator simd_min :vec128_t    { exitm<_mm_min_pd(xmm0, _1)> }
    .operator simd_max :vec128_t    { exitm<_mm_max_pd(xmm0, _1)> }
    .operator abs                   { exitm<_mm_and_pd(xmm0, _f64vec2_abs_mask(xmm1))> }

    .operator comieq   :vec128_t    { exitm<_mm_comieq_sd(xmm0, _1)> }
    .operator comilt   :vec128_t    { exitm<_mm_comilt_sd(xmm0, _1)> }
    .operator comile   :vec128_t    { exitm<_mm_comile_sd(xmm0, _1)> }
    .operator comigt   :vec128_t    { exitm<_mm_comigt_sd(xmm0, _1)> }
    .operator comige   :vec128_t    { exitm<_mm_comige_sd(xmm0, _1)> }
    .operator comineq  :vec128_t    { exitm<_mm_comineq_sd(xmm0, _1)> }

    .operator ucomieq  :vec128_t    { exitm<_mm_ucomieq_sd(xmm0, _1)> }
    .operator ucomilt  :vec128_t    { exitm<_mm_ucomilt_sd(xmm0, _1)> }
    .operator ucomile  :vec128_t    { exitm<_mm_ucomile_sd(xmm0, _1)> }
    .operator ucomigt  :vec128_t    { exitm<_mm_ucomigt_sd(xmm0, _1)> }
    .operator ucomige  :vec128_t    { exitm<_mm_ucomige_sd(xmm0, _1)> }
    .operator ucomineq :vec128_t    { exitm<_mm_ucomineq_sd(xmm0, _1)> }

    .operator unpack_low  :vec128_t { exitm<_mm_unpacklo_pd(xmm0, _1)> }
    .operator unpack_high :vec128_t { exitm<_mm_unpackhi_pd(xmm0, _1)> }
    .operator move_mask             { exitm<_mm_movemask_pd(xmm0)> }
    .operator loadu                 { exitm<_mm_loadu_pd([this])> }
    .operator storeu                { exitm<_mm_storeu_pd([this], xmm0)> }
    .operator store_nta             { exitm<_mm_stream_pd([this], xmm0)> }

    F64vec2_SELECT macro op
        .operator select_&op& :vec128_t, :vec128_t, :vec128_t {
            _mm_cmp&op&_pd(xmm0, _1)
            _mm_store_ps(_1, xmm0)
            _mm_and_pd(xmm0, _2)
            _mm_andnot_pd(_1, _3)
            exitm<_mm_or_pd(xmm0, _1)>
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

    .operator select_gt :vec128_t, :vec128_t, :vec128_t {
        _mm_cmpgt_pd(_1, xmm0, _1)
        _mm_store_ps(xmm0, _1)
        _mm_and_pd(xmm0, _2)
        _mm_andnot_pd(_1, _3)
        exitm<_mm_or_pd(xmm0, _1)>
        }
    .operator select_ge :vec128_t, :vec128_t, :vec128_t {
        _mm_cmpge_pd(_1, xmm0, _1)
        _mm_store_ps(xmm0, _1)
        _mm_and_pd(xmm0, _2)
        _mm_andnot_pd(_1, _3)
        exitm<_mm_or_pd(xmm0, _1)>
        }

    .operator ToInt {
        exitm<_mm_cvttsd_si32(xmm0)>
        }
    .operator ToF32vec4 {
        exitm<_mm_cvtpd_ps(xmm0)>
        }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [1]:%f\n [0]:%f\n"),\
            _1,\
            qword ptr [this+0x08],\
            qword ptr [this+0x00] )
        mov this,this_ptr
        exitm<>
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

    .operator = :abs, :abs, :abs, :abs, :abs, :abs, :abs, :abs {
        mov dword ptr [this+0x00],_1
        mov dword ptr [this+0x04],_2
        mov dword ptr [this+0x08],_3
        mov dword ptr [this+0x0C],_4
        mov dword ptr [this+0x10],_5
        mov dword ptr [this+0x14],_6
        mov dword ptr [this+0x18],_7
        mov dword ptr [this+0x1C],_8
        exitm<F32vec8___m256(this)>
        }
    .operator = :real4 {
        movd eax,_1
        mov [this+0x00],eax
        mov [this+0x04],eax
        mov [this+0x08],eax
        mov [this+0x0C],eax
        mov [this+0x10],eax
        mov [this+0x14],eax
        mov [this+0x18],eax
        mov [this+0x1C],eax
        exitm<F32vec8___m256(this)>
        }
    .operator = :real8 {
        _mm_cvtsd_ss(_1, _1)
        exitm<F32vec8_mequ4(this, _1)> }
    .operator = :vec256_t {
        exitm<_mm256_store_ps([this], _mm256_store_ps(ymm0, _1))> }
    .operator __m256 {
        exitm<_mm256_store_ps(ymm0, [this])> }

    .operator add_horizontal {
        _mm256_store_ps(ymm1, ymm0)
        _mm256_add_ps(ymm0, _mm256_permute_ps(ymm1, 0xee))
        _mm256_add_ps(ymm0, _mm256_movehdup_ps(_mm256_store_ps(ymm1, ymm0)))
        _mm_cvtss_f32(_mm_add_ss(_mm256_castps256_ps128(ymm0), _mm256_extractf128_ps(ymm0, 1)))
        retm<ymm0>
        }
    .operator andnot :vec256_t {
        exitm<_mm256_andnot_ps(ymm0, _1)>
        }
    .operator sqrt {
        exitm<_mm256_sqrt_ps(ymm0)>
        }
    .operator rcp {
        exitm<_mm256_rcp_ps(ymm0)>
        }
    .operator rsqrt {
        exitm<_mm256_rsqrt_ps(ymm0)>
        }
    .operator rcp_nr {
        vrcpps ymm1,ymm0
        vmulps ymm0,ymm1,ymm0
        vmulps ymm0,ymm0,ymm1
        vaddps ymm1,ymm1,ymm1
        vsubps ymm0,ymm1,ymm0
        retm <ymm0>
        }
    .operator rsqrt_nr {
        vrsqrtps ymm1,ymm0
        vmulps ymm0,ymm0,ymm1
        vmulps ymm2,ymm0,ymm1
        vmulps ymm0,ymm1,_mm256_set_epi32(5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0)
        _mm256_sub_ps(_mm256_set_epi32(ymm1, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0), ymm2)
        exitm<_mm256_mul_ps(ymm0, ymm1)>
        }

    .operator cmp_eq    :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_EQ_OQ)> }
    .operator cmp_lt    :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_LT_OS)> }
    .operator cmp_le    :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_LE_OS)> }
    .operator cmp_gt    :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_GT_OS)> }
    .operator cmp_ge    :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_GE_OS)> }
    .operator cmp_neq   :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_NEQ_UQ)> }
    .operator cmp_nlt   :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_NLT_US)> }
    .operator cmp_nle   :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_NLE_US)> }
    .operator cmp_ngt   :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_NGT_US)> }
    .operator cmp_nge   :vec256_t { exitm<_mm256_cmp_ps(ymm0, _1, _CMP_NGE_US)> }

    .operator simd_min  :vec256_t { exitm<_mm256_min_ps(ymm0, _1)> }
    .operator simd_max  :vec256_t { exitm<_mm256_max_ps(ymm0, _1)> }
    .operator abs {
        vpcmpeqw ymm1,ymm1,ymm1
        vpsrld ymm1,ymm1,1
        exitm<_mm256_and_ps(ymm0, ymm1)>
        }

    .operator unpack_low    :vec256_t { exitm<_mm256_unpacklo_ps(ymm0, _1)> }
    .operator unpack_high   :vec256_t { exitm<_mm256_unpackhi_ps(ymm0, _1)> }
    .operator move_mask     { exitm<_mm256_movemask_ps(ymm0)> }
    .operator loadu         { exitm<_mm256_loadu_ps([this], ymm0)> }
    .operator storeu        { exitm<_mm256_storeu_ps([this], ymm0)> }
    .operator store_nta     { exitm<_mm256_stream_ps([this], ymm0)> }
    .operator maskload      { exitm<_mm256_maskload_ps([this], ymm0)> }
    .operator maskstore :vec256_t {
        exitm<_mm256_maskstore_ps([this], _1, ymm0)>
        }

    .operator select_eq :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_EQ_OQ))>
        }
    .operator select_lt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_LT_OS))>
        }
    .operator select_le :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_LE_OS))>
        }
    .operator select_gt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_GT_OS))>
        }
    .operator select_ge :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_GE_OS))>
        }
    .operator select_neq :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NEQ_UQ))>
        }
    .operator select_nlt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NLT_US))>
        }
    .operator select_nle :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NLE_US))>
        }
    .operator select_ngt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NGT_US))>
        }
    .operator select_nge :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_ps(_3, _2, _mm256_cmp_ps(ymm0, _1, _CMP_NGE_US))>
        }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
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
        exitm<>
        }
endif
    .ends


.template F64vec4
    vec __m256d <>

    .operator = :real8, :real8, :real8, :real8 {
        movsd qword ptr [this+0x00],_4
        movsd qword ptr [this+0x08],_3
        movsd qword ptr [this+0x10],_2
        movsd qword ptr [this+0x18],_1
        exitm<F32vec8___m256(this)>
        }
    .operator = :real8 {
        movsd [this+0x00],_1
        movsd [this+0x08],_1
        movsd [this+0x10],_1
        movsd [this+0x18],_1
        exitm<F32vec8___m256(this)>
        }
    .operator = :vec256_t {
        exitm<_mm256_store_ps([this], _mm256_store_ps(ymm0, _1))>
        }
    .operator __m256 {
        exitm<_mm256_store_ps(ymm0, [this])>
        }

    .operator & :vec256_t { exitm<_mm256_and_pd(ymm0, _1)> }
    .operator | :vec256_t { exitm<_mm256_or_pd (ymm0, _1)> }
    .operator ^ :vec256_t { exitm<_mm256_xor_pd(ymm0, _1)> }
    .operator + :vec256_t { exitm<_mm256_add_pd(ymm0, _1)> }
    .operator - :vec256_t { exitm<_mm256_sub_pd(ymm0, _1)> }
    .operator * :vec256_t { exitm<_mm256_mul_pd(ymm0, _1)> }
    .operator / :vec256_t { exitm<_mm256_div_pd(ymm0, _1)> }

    .operator += :vec256_t {
        _mm256_add_pd(ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }
    .operator -= :vec256_t {
        _mm256_sub_pd(ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }
    .operator *= :vec256_t {
        _mm256_mul_pd(ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }
    .operator /= :vec256_t {
        _mm256_div_pd(ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }
    .operator &= :vec256_t {
        _mm256_and_pd(ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }
    .operator |= :vec256_t {
        _mm256_or_pd (ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }
    .operator ^= :vec256_t {
        _mm256_xor_pd(ymm0, _1)
        exitm<_mm256_store_ps([this], ymm0)>
        }


    .operator add_horizontal {
        _mm256_store_pd(ymm1, ymm0)
        _mm256_add_pd(ymm0, _mm256_permute_pd(ymm1, 0x05))
        _mm256_add_pd(ymm0, _mm256_movehdup_ps(_mm256_store_ps(ymm1, ymm0)))
        _mm_cvtsd_f64(_mm_add_sd(_mm256_castps256_ps128(ymm0), _mm256_extractf128_pd(ymm0, 1)))
        retm <xmm0>
        }
    .operator andnot    :vec256_t { exitm<_mm256_andnot_pd(ymm0, _1)> }
    .operator sqrt                { exitm<_mm256_sqrt_pd(ymm0)> }

    .operator cmp_eq    :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_EQ_OQ)> }
    .operator cmp_lt    :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_LT_OS)> }
    .operator cmp_le    :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_LE_OS)> }
    .operator cmp_gt    :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_GT_OS)> }
    .operator cmp_ge    :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_GE_OS)> }
    .operator cmp_neq   :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_NEQ_UQ)> }
    .operator cmp_nlt   :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_NLT_US)> }
    .operator cmp_nle   :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_NLE_US)> }
    .operator cmp_ngt   :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_NGT_US)> }
    .operator cmp_nge   :vec256_t { exitm<_mm256_cmp_pd(ymm0, _1, _CMP_NGE_US)> }

    .operator simd_min  :vec256_t { exitm<_mm256_min_pd(ymm0, _1)> }
    .operator simd_max  :vec256_t { exitm<_mm256_max_pd(ymm0, _1)> }
    .operator abs {
        vpcmpeqd ymm1,ymm1,ymm1
        vpsrlq ymm1,ymm1,1
        exitm<_mm256_and_pd(ymm0, ymm1)>
        }

    .operator unpack_low    :vec256_t { exitm<_mm256_unpacklo_pd(ymm0, _1)> }
    .operator unpack_high   :vec256_t { exitm<_mm256_unpackhi_pd(ymm0, _1)> }
    .operator move_mask     { exitm<_mm256_movemask_pd()> }
    .operator loadu         { exitm<_mm256_loadu_pd   ([this], ymm0)> }
    .operator storeu        { exitm<_mm256_storeu_pd  ([this], ymm0)> }
    .operator store_nta     { exitm<_mm256_stream_pd  ([this], ymm0)> }
    .operator maskload      { exitm<_mm256_maskload_pd([this], ymm0)> }
    .operator maskstore :vec256_t {
        exitm<_mm256_maskstore_pd([this], _1, ymm0)>
        }

    .operator select_eq :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_EQ_OQ))>
        }
    .operator select_lt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_LT_OS))>
        }
    .operator select_le :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_LE_OS))>
        }
    .operator select_gt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_GT_OS))>
        }
    .operator select_ge :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_GE_OS))>
        }
    .operator select_neq :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NEQ_UQ))>
        }
    .operator select_nlt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NLT_US))>
        }
    .operator select_nle :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NLE_US))>
        }
    .operator select_ngt :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NGT_US))>
        }
    .operator select_nge :vec256_t, :vec256_t, :vec256_t {
        exitm<_mm256_blendv_pd(_3, _2, _mm256_cmp_pd(ymm0, _1, _CMP_NGE_US))>
        }
    .operator ToF32vec8 { exitm<_mm256_cvtpd_ps(ymm0)> }
if defined (_ENABLE_VEC_DEBUG)
    .operator cout :string_t {
        .new this_ptr:ptr
        mov this_ptr,this
        printf( addr @CStr("%s\n [3]:%f\n [2]:%f\n [1]:%f\n [0]:%f\n"),\
            _1,\
            qword ptr [this+0x18],\
            qword ptr [this+0x10],\
            qword ptr [this+0x08],\
            qword ptr [this+0x00] )
        mov this,this_ptr
        exitm<>
        }
endif
    .ends


F32vec4ToF64vec4 macro _A
    exitm<_mm256_cvtps_pd(_A)>
    endm

.pragma list(pop)
endif ;; _DVEC_H_INCLUDED
