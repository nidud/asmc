; __CVTI32_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

__cvti32_q proc x:ptr, l:long_t

    mov rax,rcx
    mov r8d,0x3FFF
    xor ecx,ecx
    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        mov r8d,0xBFFF  ; set exponent
    .endif
    .if edx
        bsr ecx,edx     ; find most significant non-zero bit
        mov ch,cl
        mov cl,32
        sub cl,ch
        shl rdx,cl      ; shift bits into position
        shr ecx,8       ; get shift count
        add ecx,r8d     ; calculate exponent
    .endif
    shl rdx,32
    shld rcx,rdx,64-16
    xor edx,edx
    mov [rax],rdx
    mov [rax+8],rcx
    ret

__cvti32_q endp

    end

