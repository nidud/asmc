; _ITOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_itoflt proc p:ptr STRFLT, i:int_t

    mov eax,i
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        mov edx,0xBFFF  ; set exponent
    .else
        mov edx,0x3FFF
    .endif
    .if eax
        bsr ecx,eax     ; find most significant non-zero bit
        mov ch,cl
        mov cl,32
        sub cl,ch
        .if cl == 32
            xor eax,eax
        .else
            shl eax,cl  ; shift bits into position
        .endif
        shr ecx,8       ; get shift count
        add ecx,edx     ; calculate exponent
        mov edx,eax     ; get the bits
    .else
        xor ecx,ecx     ; else zero
        xor edx,edx
    .endif
    mov eax,p
    mov [eax+12],edx
    mov [eax+16],cx
    xor edx,edx         ; zero the rest of the fraction bits
    mov [eax],edx
    mov [eax+4],edx
    mov [eax+8],edx
    ret

_itoflt endp

    end
