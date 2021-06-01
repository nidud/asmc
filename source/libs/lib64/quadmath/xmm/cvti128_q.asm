; CVTI128_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvti128_q() - __int128 to Quadruple float
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

cvti128_q proc vectorcall o:int128_t

    movq rax,xmm0
    movhlps xmm0,xmm0
    movq rdx,xmm0
    xor ecx,ecx
    mov r8d,Q_EXPBIAS

    test rdx,rdx        ; if number is negative
    .ifs
        neg rdx         ; negate number
        neg rax
        sbb rdx,0
        or  r8d,0x8000
    .endif

    .if rax || rdx

        .if rdx         ; find most significant non-zero bit
            bsr rcx,rdx
            add ecx,64
        .else
            bsr rcx,rax
        .endif
        mov ch,cl       ; shift bits into position
        mov cl,127
        sub cl,ch
        .if cl >= 64
            sub cl,64
            mov rdx,rax
            xor eax,eax
        .endif
        shld rdx,rax,cl
        shl rax,cl
        shr ecx,8       ; get shift count
        add ecx,r8d     ; calculate exponent
    .endif
    shl rax,1
    rcl rdx,1
    shrd rax,rdx,16
    shrd rdx,rcx,16
    movq xmm0,rax
    movq xmm1,rdx
    movlhps xmm0,xmm1   ; return result
    ret

cvti128_q endp

    end

