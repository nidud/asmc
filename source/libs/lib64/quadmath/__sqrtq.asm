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

    assume rcx:ptr __m128i

    mov rax,[rcx].m128i_u64[0]
    or  eax,[rcx].m128i_u32[8]
    or  ax,[rcx].m128i_u16[12]
    mov dx,[rcx].m128i_u16[14]
    and edx,Q_EXPMASK

    .return .if edx == Q_EXPMASK && !eax
    .return .if !edx && !eax

    .if [rcx].m128i_u8[15] & 0x80

        __subq(rcx, rcx)
        __divq(rax, rax)
        .return
    .endif

    assume rcx:nothing

    mov x,[rcx]
    __cvtq_ld(rcx, rcx)
    mov rcx,p
    fld tbyte ptr [rcx]
    fsqrt
    fstp tbyte ptr [rcx]
    __cvtld_q(rcx, rcx)

    mov rdx,p
    mov y,[rdx]
    __subq(&y, __divq(&x, rdx))
    mov x.m128i_u64[0],0
    mov x.m128i_u32[8],0
    mov x.m128i_u32[12],0x3FFE0000 ; 0.5

    __mulq(&y, &x)
    __subq(p, &y)
    ret

__sqrtq endp

    end
