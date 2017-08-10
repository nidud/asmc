; _qftoll() - Quadruple float to long long
;
include intn.inc
include errno.inc
include limits.inc

.code

_qftoll proc uses esi edi fp:ptr

    mov edx,fp
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
        sub ecx,Q_EXPBIAS
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

_qftoll endp

    END
