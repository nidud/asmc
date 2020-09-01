; CVTI64_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; cvti64_q() - long long to Quadruple float
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

cvti64_q proc vectorcall i:int64_t

    mov rax,rcx
    mov r8d,Q_EXPBIAS
    xor ecx,ecx
    test rax,rax        ; if number is negative
    .ifs
        neg rax         ; negate number
        or  r8d,0x8000
    .endif

    .if rax

        bsr rcx,rax     ; find most significant non-zero bit
        mov ch,cl
        mov cl,64
        sub cl,ch
        .if cl < 64     ; shift bits into position
            shl rax,cl
        .else
            xor eax,eax
        .endif
        shr ecx,8       ; get shift count
        add ecx,r8d     ; calculate exponent
    .endif
    shld rcx,rax,64-16
    shl  rax,64-16
    movq xmm0,rax
    movq xmm1,rcx
    movlhps xmm0,xmm1   ; return result
    ret

cvti64_q endp

    end

