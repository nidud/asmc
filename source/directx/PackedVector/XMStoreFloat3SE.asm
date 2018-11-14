; XMSTOREFLOAT3SE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

    option win64:rsp noauto nosave

XMStoreFloat3SE proc vectorcall pDestination:ptr XMFLOAT3SE, V:FXMVECTOR

    _mm_setzero_ps()
    .if _mm_comige_ss(xmm1, xmm0)
        .if _mm_comigt_ss(xmm1, FLT4(0x477F8000))
            _mm_store_ss(xmm0, FLT4(0x477F8000))
        .else
            _mm_store_ss(xmm0, xmm1)
        .endif
    .endif
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0, 3, 2, 1))
    _mm_setzero_ps(xmm2)
    .if _mm_comige_ss(xmm1, xmm2)
        .if _mm_comigt_ss(xmm1, FLT4(0x477F8000))
            _mm_store_ss(xmm2, FLT4(0x477F8000))
        .else
            _mm_store_ss(xmm2, xmm1)
        .endif
    .endif
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0, 3, 2, 1))
    _mm_setzero_ps(xmm3)
    .if _mm_comige_ss(xmm1, xmm3)
        .if _mm_comigt_ss(xmm1, FLT4(0x477F8000))
            _mm_store_ss(xmm3, FLT4(0x477F8000))
        .else
            _mm_store_ss(xmm3, xmm1)
        .endif
    .endif

    _mm_store_ss(xmm1, xmm0)
    _mm_max_ss(xmm1, xmm2)
    _mm_store_ss(xmm4, xmm3)
    .if _mm_comigt_ss(xmm1, xmm3)
        _mm_store_ss(xmm4, xmm1)
    .endif

    mov eax,0x37800000
    .if _mm_comigt_ss(xmm4, FLT4(0x37800000))

        movd eax,xmm4
    .endif

    add eax,0x00004000 ; round up leaving 9 bits in fraction (including assumed 1)
    mov edx,eax
    sub edx,0x37800000
    shr edx,23
    shl edx,27
    mov [rcx],edx

    mov edx,0x83000000
    sub edx,eax
    movd xmm1,edx

    mulss xmm0,xmm1
    mulss xmm2,xmm1
    mulss xmm3,xmm1

    roundf(xmm0)
    cvtss2si eax,xmm0
    and eax,0x1FF
    or  [rcx],eax
    roundf(xmm2)
    cvtss2si eax,xmm0
    and eax,0x1FF
    shl eax,9
    or  [rcx],eax
    roundf(xmm3)
    cvtss2si eax,xmm0
    and eax,0x1FF
    shl eax,18
    or  [rcx],eax
    ret

XMStoreFloat3SE endp

    end
