; CVTQ_I64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvtq_i64() - Quadruple float to long long
;

include quadmath.inc
include errno.inc
include limits.inc

    .code

cvtq_i64 proc vectorcall q:real16

    movq rax,xmm0
    movhlps xmm0,xmm0
    movq rcx,xmm0
    shld rdx,rcx,16
    shld rcx,rax,16

    mov eax,edx
    and eax,Q_EXPMASK

    .if eax < Q_EXPBIAS

        xor eax,eax
        .if edx & 0x8000
            dec rax
        .endif

    .elseif eax > 62 + Q_EXPBIAS

        _set_errno(ERANGE)
        mov rax,_I64_MAX
        .if edx & 0x8000
            mov rax,_I64_MIN
        .endif

    .else
        lea r8,[rax-Q_EXPBIAS]
        mov eax,1
        .while r8d
            add rcx,rcx
            adc rax,rax
            dec r8d
        .endw
        .if edx & 0x8000
            neg rax
        .endif
    .endif
    ret

cvtq_i64 endp

    end
