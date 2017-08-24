; _qftoll() - Quadruple float to long
;
include intn.inc
include limits.inc
include errno.inc

option win64:rsp nosave noauto

.code

_qftol proc fp:ptr

    mov dx,[rcx+14]
    mov eax,edx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor eax,eax
        .if dx & 0x8000
            dec eax
        .endif
    .elseif eax > 32 + Q_EXPBIAS
        mov errno,ERANGE
        mov eax,INT_MAX
        .if dx & 0x8000
            mov eax,INT_MIN
        .endif
    .else
        mov edx,eax
        sub edx,Q_EXPBIAS
        mov r8d,[rcx+10]
        mov eax,1
        .while edx
            shl r8d,1
            rcl eax,1
            dec edx
        .endw
        .if byte ptr [rcx+15] & 0x80
            neg eax
        .endif
    .endif
    ret

_qftol endp

    END
