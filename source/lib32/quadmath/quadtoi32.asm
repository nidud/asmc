; QUADTOI32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; quadtoi32() - Quadruple float to long
;
include quadmath.inc
include limits.inc

.code

quadtoi32 proc q:ptr

    mov edx,q
    mov cx,[edx+14]
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor eax,eax
if 0
        .if cx & 0x8000
            dec eax
        .endif
endif
    .elseif eax > 32 + Q_EXPBIAS
        mov qerrno,ERANGE
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
    .else
        mov ecx,eax
        sub ecx,Q_EXPBIAS
        mov edx,[edx+10]
        mov eax,1
        shld eax,edx,cl
        mov ecx,q
        .if byte ptr [ecx+15] & 0x80
            neg eax
        .endif
    .endif
    ret

quadtoi32 endp

    END
