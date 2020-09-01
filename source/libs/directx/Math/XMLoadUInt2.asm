; XMLOADUINT2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadUInt2 proc XM_CALLCONV pSource:ptr XMUINT2

    .assert( rcx )

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])

    _mm_store_ps(xmm1, _mm_unpacklo_ps(xmm0, xmm1))
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_and_ps(xmm0, g_XMNegativeZero)
    ;;
    ;; Force all values positive
    ;;
    _mm_xor_ps(xmm1, xmm0)
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(xmm1)
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_srai_epi32(xmm0, 31)
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(xmm0, g_XMFixUnsigned)
    _mm_add_ps(xmm0, xmm1)
    ret

XMLoadUInt2 endp

    end
