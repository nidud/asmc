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

    mov dx,[rcx+14]
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

        mov r8,[rcx+6]
        lea rcx,[rax-Q_EXPBIAS]
        mov eax,1

        .while ecx
            add r8,r8
            adc rax,rax
            dec ecx
        .endw

        .if edx & 0x8000
            neg rax
        .endif
    .endif
    ret

__cvtq_i64 endp

    end
