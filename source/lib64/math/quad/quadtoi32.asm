;
; quadtoi32() - Quadruple float to long
;
include quadmath.inc
include limits.inc

option win64:rsp nosave noauto

.code

quadtoi32 proc q:ptr

    mov dx,[rcx+14]
    mov eax,edx
    and eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor eax,eax

    .elseif eax > 32 + Q_EXPBIAS

        mov qerrno,ERANGE
        mov eax,INT_MAX
        .if dx & 0x8000
            mov eax,INT_MIN
        .endif

    .else
        mov r8,rcx
        mov ecx,eax
        sub ecx,Q_EXPBIAS
        mov edx,[r8+10]
        mov eax,1
        shld eax,edx,cl
        .if byte ptr [r8+15] & 0x80
            neg eax
        .endif
    .endif
    ret

quadtoi32 endp

    END
