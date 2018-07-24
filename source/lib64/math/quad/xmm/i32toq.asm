;
; i32toq() - long to Quadruple float
;
include quadmath.inc

    .code

    option win64:rsp nosave noauto

i32toq proc vectorcall l:SINT
    mov  eax,0x3FFF
    test ecx,ecx        ; if number is negative
    .ifs
        neg ecx         ; negate number
        mov eax,0xBFFF  ; set exponent
    .endif
    .if ecx
        bsr edx,ecx     ; find most significant non-zero bit
        xchg ecx,edx
        mov ch,cl
        mov cl,32
        sub cl,ch
        shl rdx,cl      ; shift bits into position
        shr ecx,8       ; get shift count
        add ecx,eax     ; calculate exponent
        mov eax,edx     ; get the bits
    .else
        xor eax,eax     ; else zero
    .endif
    shl     rax,32
    shrd    rax,rcx,16
    movq    xmm0,rax
    shufps  xmm0,xmm0,01001110B
    ret
i32toq endp

    end
