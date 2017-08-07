include intn.inc
include limits.inc
include errno.inc

.code

_qftol proc uses esi edi fp:ptr

    mov edx,fp
    mov cx,[edx+14]
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < EXPONENT_BIAS
        xor eax,eax
        .if cx & 0x8000
            dec eax
        .endif
    .elseif eax > 32 + EXPONENT_BIAS
        mov errno,ERANGE
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
    .else
        mov ecx,eax
        sub ecx,EXPONENT_BIAS
        mov edx,[edx+10]
        mov eax,1
        .while ecx
            shl edx,1
            rcl eax,1
            dec ecx
        .endw
        mov ecx,fp
        .if byte ptr [ecx+15] & 0x80
            neg eax
        .endif
    .endif
    ret

_qftol endp

    END
