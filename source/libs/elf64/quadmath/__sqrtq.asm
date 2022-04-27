; SQRTQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc
include intrin.inc

    .code

__sqrtq proc uses rbx p:ptr

  local x:__m128i
  local y:__m128i
  local t:__m128i

    assume rdi:ptr __m128i

    mov rbx,rdi
    mov rax,[rdi].m128i_u64[0]
    or  eax,[rdi].m128i_u32[8]
    or  ax,[rdi].m128i_u16[12]
    mov dx,[rdi].m128i_u16[14]
    and edx,Q_EXPMASK

    .return .if ( edx == Q_EXPMASK && !eax )
    .return .if ( !edx && !eax )

    .if ( [rdi].m128i_u8[15] & 0x80 )

        __subq(rdi, rdi)
        __divq(rax, rax)
        .return
    .endif

    assume rdi:nothing

    mov x,[rdi]
    __cvtq_ld(rdi, rdi)
    fld tbyte ptr [rbx]
    fsqrt
    fstp tbyte ptr [rbx]
    __cvtld_q(rbx, rbx)

    mov y,[rbx]
    __subq(&y, __divq(&x, rbx))
    mov x.m128i_u64[0],0
    mov x.m128i_u32[8],0
    mov x.m128i_u32[12],0x3FFE0000 ; 0.5
    __mulq(&y, &x)
    __subq(rbx, &y)
    ret

__sqrtq endp

    end
