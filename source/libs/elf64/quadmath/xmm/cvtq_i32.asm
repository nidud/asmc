; CVTQ_I32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvtq_i32() - Quadruple float to long
;

include quadmath.inc
include errno.inc
include limits.inc

    .code

    option win64:noauto

cvtq_i32 proc q:real16

    movhlps xmm0,xmm0
    movq rdx,xmm0
    shld rcx,rdx,16
    shr  rdx,16
    mov  eax,ecx
    and  eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS
        xor eax,eax
    .elseif eax > 32 + Q_EXPBIAS
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
        _set_errno(ERANGE)
    .else
        mov r8,rcx
        mov ecx,eax
        sub ecx,Q_EXPBIAS
        mov eax,1
        shld eax,edx,cl
        .if r8w & 0x8000
            neg eax
        .endif
    .endif
    ret

cvtq_i32 endp

    end
