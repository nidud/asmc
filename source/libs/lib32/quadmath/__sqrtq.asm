; SQRTQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

__sqrtq proc p:ptr

  local x:__m128i
  local y:__m128i
  local t:__m128i

    assume ecx:ptr __m128i

    mov ecx,p
    mov eax,[ecx].m128i_u32[0]
    or  eax,[ecx].m128i_u32[4]
    or  eax,[ecx].m128i_u32[8]
    or  ax,[ecx].m128i_u16[12]
    mov dx,[ecx].m128i_u16[14]
    and edx,Q_EXPMASK

    .return .if edx == Q_EXPMASK && !eax
    .return .if !edx && !eax

    .if [ecx].m128i_u8[15] & 0x80

        __subq(p, p)
        __divq(p, p)
        .return
    .endif

    assume ecx:nothing

    mov x,[ecx]
    __cvtq_ld(ecx, ecx)
    mov ecx,p
    fld tbyte ptr [ecx]
    fsqrt
    fstp tbyte ptr [ecx]
    __cvtld_q(ecx, ecx)

    mov ecx,p
    mov y,[ecx]

    __divq(&x, ecx)
    __subq(&y, &x)

    mov x.m128i_u32[0],0
    mov x.m128i_u32[4],0
    mov x.m128i_u32[8],0
    mov x.m128i_u32[12],0x3FFE0000 ; 0.5
    __mulq(&y, &x)
    __subq(p, &y)
    mov eax,p
    ret

__sqrtq endp

    end
