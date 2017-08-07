include intn.inc
include errno.inc
include limits.inc

.code

_qftoi64 proc uses esi edi fp:ptr

    mov edx,fp
    mov cx,[edx+14]
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < EXPONENT_BIAS
        xor edx,edx
        xor eax,eax
        .if cx & 0x8000
            dec eax
            dec edx
        .endif
    .elseif eax > 62 + EXPONENT_BIAS
        mov errno,ERANGE
        xor eax,eax
        .if cx & 0x8000
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif
    .else
        mov ecx,eax
        sub ecx,EXPONENT_BIAS
        mov edi,[edx+10]
        mov esi,[edx+6]
        mov eax,1
        xor edx,edx
        .while ecx
            shl esi,1
            rcl edi,1
            rcl eax,1
            rcl edx,1
            dec ecx
        .endw
        mov ecx,fp
        .if byte ptr [ecx+15] & 0x80
            neg edx
            neg eax
            sbb edx,0
        .endif
    .endif
    ret

_qftoi64 endp

    END
