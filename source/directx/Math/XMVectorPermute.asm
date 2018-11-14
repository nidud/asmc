; XMVECTORPERMUTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:nosave noauto

XMVectorPermute proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR,
    PermuteX:uint32_t, PermuteY:uint32_t, PermuteZ:uint32_t, PermuteW:uint32_t

  local v:XMFLOAT4X4,result:XMFLOAT4

if _XM_VECTORCALL_
 ifdef _XM_AVX_INTRINSICS_
 else

    lea r10,v

    _mm_store_ps([r10], xmm0)
    _mm_store_ps([r10+16], xmm1)

    mov ecx,r8d
    mov eax,r8d
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.x,ecx

    mov ecx,r9d
    mov eax,r9d
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.y,ecx

    mov ecx,PermuteZ
    mov eax,ecx
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.z,ecx

    mov ecx,PermuteW
    mov eax,ecx
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.w,ecx
    _mm_store_ps(xmm0, result)
 endif
else
    lea r10,v

    _mm_store_ps([xmm0, [rcx])
    _mm_store_ps([xmm1, [rdx])
    _mm_store_ps([r10], xmm0)
    _mm_store_ps([r10+16], xmm1)

    mov ecx,r8d
    mov eax,r8d
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.x,ecx

    mov ecx,r9d
    mov eax,r9d
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.y,ecx

    mov ecx,PermuteZ
    mov eax,ecx
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.z,ecx

    mov ecx,PermuteW
    mov eax,ecx
    and ecx,3
    shl ecx,2
    shr eax,2
    shl eax,4
    add eax,ecx
    mov ecx,[r10+rax]
    mov result.w,ecx
    _mm_store_ps(xmm0, result)
endif
    ret

XMVectorPermute endp

    end
