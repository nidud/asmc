; __CVTQ_I32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_i32() - Quadruple float to long
;

include quadmath.inc
include errno.inc
include limits.inc

    .code

__cvtq_i32 proc q:ptr

    mov edx,q
    mov cx,[edx+14]
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor eax,eax
    .elseif eax > 32 + Q_EXPBIAS
        push ecx
        _set_errno(ERANGE)
        pop ecx
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
    .else
        mov edx,[edx+10]
        mov ecx,eax
        sub ecx,Q_EXPBIAS
        mov eax,1
        shld eax,edx,cl
        mov ecx,q
        .if byte ptr [ecx+15] & 0x80
            neg eax
        .endif
    .endif
    ret

__cvtq_i32 endp

    end
