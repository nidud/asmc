; _ITOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_itoflt proc p:ptr STRFLT, i:int_t

    mov eax,esi
    mov esi,Q_EXPBIAS   ; set exponent
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        or  esi,0x8000
    .endif
    xor edx,edx
    bsr rdx,rax         ; find most significant non-zero bit
    mov ecx,63
    sub ecx,edx
    shl rax,cl          ; shift bits into position
    add edx,esi         ; calculate exponent
    xor ecx,ecx
    mov [rdi].STRFLT.mantissa.l,rcx
    mov [rdi].STRFLT.mantissa.h,rax
    mov [rdi].STRFLT.mantissa.e,dx
    mov rax,rdi
    ret

_itoflt endp

    end
