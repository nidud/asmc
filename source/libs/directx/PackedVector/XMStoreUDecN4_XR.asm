; XMSTOREUDECN4_XR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreUDecN4_XR proc XM_CALLCONV pDestination:ptr XMUDECN4, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    XMVectorMultiplyAdd( xmm0, _mm_get_epi32(510.0, 510.0, 510.0, 3.0), _mm_get_epi32(384.0, 384.0, 384.0, 0.0) )
    XMVectorClamp( xmm0, g_XMZero, _mm_get_epi32(1023.0, 1023.0, 1023.0, 3.0) )
    _mm_extract_epi16(xmm0, 0)
    and eax,0x3FF
    mov edx,eax
    _mm_extract_epi16(xmm0, 2)
    and eax,0x3FF
    shl eax,10
    or  edx,eax
    _mm_extract_epi16(xmm0, 4)
    and eax,0x3FF
    shl eax,20
    or  edx,eax
    _mm_extract_epi16(xmm0, 6)
    shl eax,30
    or  edx,eax
    mov [rcx],edx
    ret

XMStoreUDecN4_XR endp

    end
