; _SQRTQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

    .code

__sqrtq proc __ccall p:ptr qfloat_t

  local x:U128
  local y:U128
  local t:U128

    ldr rcx,p

    assume rcx:ptr U128

ifdef _WIN64
    mov rax,[rcx].u64[0]
else
    mov eax,[ecx].u32[0]
    or  eax,[ecx].u32[4]
endif
    or  eax,[rcx].u32[8]
    or  ax,[rcx].u16[12]
    mov dx,[rcx].u16[14]
    and edx,Q_EXPMASK

    .return .if edx == Q_EXPMASK && !eax
    .return .if !edx && !eax

    .if [rcx].u8[15] & 0x80

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
ifdef _WIN64
    mov x.u64[0],0
else
    mov x.u32[0],0
    mov x.u32[4],0
endif
    mov x.u32[8],0
    mov x.u32[12],0x3FFE0000 ; 0.5

    __mulq(&y, &x)
    __subq(p, &y)
    ret

__sqrtq endp

    end
