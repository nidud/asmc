; __CVTQ_I64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvtq_i64() - Quadruple float to long long
;

include quadmath.inc
include errno.inc
include limits.inc

    .code

__cvtq_i64 proc q:ptr

    mov edx,q
    mov cx,[edx+14]
    mov eax,ecx
    and eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor edx,edx
        xor eax,eax
        .if cx & 0x8000
            dec eax
            dec edx
        .endif

    .elseif eax > 62 + Q_EXPBIAS

        _set_errno(ERANGE)
        xor eax,eax
        .if cx & 0x8000
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif

    .else

        mov ecx,eax
        sub ecx,Q_EXPBIAS
        push esi
        push edi
        mov edi,[edx+10]
        mov esi,[edx+6]
        mov eax,1
        xor edx,edx
        .while ecx
            add esi,esi
            adc edi,edi
            adc eax,eax
            adc edx,edx
            dec ecx
        .endw
        pop edi
        pop esi
        mov ecx,q
        .if byte ptr [ecx+15] & 0x80
            neg edx
            neg eax
            sbb edx,0
        .endif
    .endif
    ret

__cvtq_i64 endp

    end
