;
; qtoi32() - Quadruple float to long
;
include quadmath.inc
include limits.inc

    .code

    option win64:rsp nosave noauto

qtoi32 proc vectorcall Q:XQFLOAT

    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    rcx,rdx,16
    shr     rdx,16
    mov     eax,ecx
    and     eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor eax,eax

    .elseif eax > 32 + Q_EXPBIAS

        mov qerrno,ERANGE
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

qtoi32 endp

    END
