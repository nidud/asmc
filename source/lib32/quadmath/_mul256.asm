; _MUL256.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .data
    r32 db 1,1,2,2,3,3,3,3,4,4,5,5
    a32 db 1,0,0,2,1,2,0,3,1,3,2,3
    b32 db 0,1,2,0,2,1,3,0,3,1,3,2

    .code

_mul256 proc uses esi edi ebx multiplier:ptr, multiplicand:ptr, highproduct:ptr

  local n:__m256i ; 256-bit result

    mov edi,multiplier
    mov esi,multiplicand

    assume esi:ptr __m128i
    assume edi:ptr __m128i

    mov eax,[edi].m128i_u32[0]
    mul [esi].m128i_u32[0]
    mov n.m256i_u32[0],eax
    mov n.m256i_u32[4],edx
    mov eax,[edi].m128i_u32[4]
    mul [esi].m128i_u32[4]
    mov n.m256i_u32[8],eax
    mov n.m256i_u32[12],edx
    mov eax,[edi].m128i_u32[8]
    mul [esi].m128i_u32[8]
    mov n.m256i_u32[16],eax
    mov n.m256i_u32[20],edx
    mov eax,[edi].m128i_u32[12]
    mul [esi].m128i_u32[12]
    mov n.m256i_u32[24],eax
    mov n.m256i_u32[28],edx

    .for ( ebx = 0: ebx < sizeof(r32): ebx++ )

        movzx eax,a32[ebx]
        movzx ecx,b32[ebx]
        mov eax,[edi].m128i_u32[eax*4]
        mul [esi].m128i_u32[ecx*4]

        .if ( eax || edx )

            movzx ecx,r32[ebx]
            add n.m256i_u32[ecx*4],eax
            adc n.m256i_u32[ecx*4+4],edx
            sbb edx,edx
            .continue .ifz
            .for ( eax = 1, ecx += 2: edx, ecx < 8: ecx++ )
                add n.m256i_u32[ecx*4],eax
                sbb edx,edx
            .endf
        .endif
    .endf

    mov eax,n.m256i_u32[0]
    mov edx,n.m256i_u32[4]
    mov ebx,n.m256i_u32[8]
    mov ecx,n.m256i_u32[12]
    mov [edi],eax
    mov [edi+4],edx
    mov [edi+8],ebx
    mov [edi+12],ecx
    mov edi,highproduct
    .if edi
        mov eax,n.m256i_u32[16]
        mov edx,n.m256i_u32[20]
        mov ebx,n.m256i_u32[24]
        mov ecx,n.m256i_u32[28]
        mov [edi],eax
        mov [edi+4],edx
        mov [edi+8],ebx
        mov [edi+12],ecx
    .endif
    ret

_mul256 endp

    end
