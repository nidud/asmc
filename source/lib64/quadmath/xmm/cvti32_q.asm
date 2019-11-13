; CVTI32_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

cvti32_q proc vectorcall l:long_t

    mov rax,rcx
    mov edx,0x3FFF
    xor ecx,ecx
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        mov edx,0xBFFF  ; set exponent
    .endif
    .if eax
        bsr ecx,eax     ; find most significant non-zero bit
        mov ch,cl
        mov cl,32
        sub cl,ch
        shl rax,cl      ; shift bits into position
        shr ecx,8       ; get shift count
        add ecx,edx     ; calculate exponent
    .endif
    shl rax,32
    shld rcx,rax,64-16
    movq xmm0,rcx
    shufpd xmm0,xmm0,1
    ret

cvti32_q endp

    end

