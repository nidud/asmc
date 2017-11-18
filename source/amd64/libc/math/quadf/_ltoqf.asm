; _ltoqf() - long to Quadruple float
;
include intn.inc

option win64:rsp nosave noauto

.code

_ltoqf proc fp:ptr, l:dword

    mov  r8,rcx
    mov  eax,edx
    mov  edx,0x3FFF
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
        shl eax,cl      ; shift bits into position
        shr ecx,8       ; get shift count
        add ecx,edx     ; calculate exponent
        mov edx,eax     ; get the bits
    .else
        xor ecx,ecx     ; else zero
        xor edx,edx
    .endif
    mov [r8+10],edx
    mov [r8+14],cx
    xor rdx,rdx         ; zero the rest of the fraction bits
    mov [r8],rdx
    mov [r8+8],dx
    mov rax,r8
    ret

_ltoqf endp

    end
