
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadUInt4 proc XM_CALLCONV pSource:ptr XMUINT4

    .assert( rcx )

    _mm_store_ps(xmm2, _mm_loadu_si128([rcx]))
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_store_ps(xmm3, _mm_and_ps(xmm0, g_XMNegativeZero))
    ;;
    ;; Force all values positive
    ;;
    _mm_store_ps(xmm1, _mm_xor_ps(xmm2, xmm3))
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(xmm1)
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_store_ps(xmm0, _mm_srai_epi32(xmm3, 31))
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(xmm0, g_XMFixUnsigned)
    _mm_add_ps(xmm0, xmm1)
    ret

XMLoadUInt4 endp

    end
