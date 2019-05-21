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

    option win64:rsp nosave noauto

__cvtq_i32 proc q:ptr

    mov  rdx,[rcx+8]
    shld rcx,rdx,16
    shr  rdx,16
    mov  eax,ecx
    and  eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS
        xor eax,eax
    .elseif eax > 32 + Q_EXPBIAS
        mov errno,ERANGE
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
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

__cvtq_i32 endp

    end
