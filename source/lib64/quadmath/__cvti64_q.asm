; __CVTI64_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvti64_q() - long long to Quadruple float
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

__cvti64_q proc x:ptr, ll:int64_t

    mov rax,rcx
    mov r8d,Q_EXPBIAS
    xor ecx,ecx
    test rdx,rdx        ; if number is negative
    .ifs
        neg rdx         ; negate number
        or  r8d,0x8000
    .endif

    .if rdx

        bsr rcx,rdx     ; find most significant non-zero bit
        mov ch,cl
        mov cl,64
        sub cl,ch
        .if cl < 64     ; shift bits into position
            shl rdx,cl
        .else
            xor edx,edx
        .endif
        shr ecx,8       ; get shift count
        add ecx,r8d     ; calculate exponent
    .endif
    shld rcx,rdx,64-16
    shl rdx,64-16
    mov [rax],rdx
    mov [rax+8],rcx
    ret

__cvti64_q endp

    end

