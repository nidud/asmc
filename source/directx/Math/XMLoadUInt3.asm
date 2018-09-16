
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadUInt3 proc XM_CALLCONV pSource:ptr XMUINT3

    .assert( rcx )

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_load_ss(xmm2, [rcx+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_store_ps(xmm1, _mm_movelh_ps(xmm0, xmm2))
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_and_ps(xmm1, g_XMNegativeZero)
    ;;
    ;; Force all values positive
    ;;
    _mm_xor_ps(xmm0, xmm1)
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(xmm0)
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_srai_epi32(xmm1, 31)
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(xmm1, g_XMFixUnsigned)
    _mm_add_ps(xmm0, xmm1)
    ret

XMLoadUInt3 endp

    end
