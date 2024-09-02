; XMVECTORSWIZZLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSwizzle proc XM_CALLCONV V:FXMVECTOR, E0:uint32_t, E1:uint32_t, E2:uint32_t, E3:uint32_t

    mov eax,E3
 ifdef _XM_AVX_INTRINSICS_
    mov dword ptr V[0],eax
    mov dword ptr V[4],edx
    mov dword ptr V[8],r8d
    mov dword ptr V[12],r9d
    _mm_permutevar_ps(xmm0, V)
 else
    mov ecx,dword ptr V[rdx*4]
    mov edx,dword ptr V[r8*4]
    mov r8d,dword ptr V[r9*4]
    mov eax,dword ptr V[rax*4]
    mov dword ptr V[0],ecx
    mov dword ptr V[4],edx
    mov dword ptr V[8],r8d
    mov dword ptr V[12],eax
    _mm_store_ps(xmm0, V)
 endif
    ret

XMVectorSwizzle endp

    end
