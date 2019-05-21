; __CVTI64_Q.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; __cvti64_q() - long long to Quadruple float
;

include quadmath.inc

    .code

__cvti64_q proc uses ebx x:ptr, ll:int64_t

    mov  eax,dword ptr ll
    mov  edx,dword ptr ll[4]
    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        neg eax
        sbb edx,0
        mov ebx,Q_EXPBIAS or 0x8000
    .else
        mov ebx,Q_EXPBIAS ; set exponent
    .endif
    .if eax || edx
        .if edx         ; find most significant non-zero bit
            bsr ecx,edx
            add ecx,32
        .else
            bsr ecx,eax
        .endif
        mov ch,cl
        mov cl,64
        sub cl,ch
        .if cl < 64     ; shift bits into position
            .if cl < 32
                shld edx,eax,cl
                shl eax,cl
            .else
                and cl,31
                mov edx,eax
                xor eax,eax
                shl edx,cl
             .endif
       .else
            xor eax,eax
            xor edx,edx
        .endif
        shr ecx,8       ; get shift count
        add ecx,ebx     ; calculate exponent
    .else
        xor ecx,ecx     ; else zero
    .endif
    mov ebx,x
    xchg eax,ebx
    mov [eax+6],ebx
    mov [eax+10],edx
    mov [eax+14],cx
    xor edx,edx         ; zero the rest of the fraction bits
    mov [eax],edx
    mov [eax+4],dx
    ret

__cvti64_q endp

    end

