; _ITOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_itoflt proc p:ptr STRFLT, i:int_t

    mov eax,edx
    mov rdx,rcx
    mov r8d,Q_EXPBIAS   ; set exponent
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        or  r8d,0x8000
    .endif
    xor r9d,r9d
    bsr r9,rax          ; find most significant non-zero bit
    mov ecx,63
    sub ecx,r9d
    shl rax,cl          ; shift bits into position
    add r9d,r8d         ; calculate exponent
    xor ecx,ecx
    mov [rdx].STRFLT.mantissa.l,rcx
    mov [rdx].STRFLT.mantissa.h,rax
    mov [rdx].STRFLT.mantissa.e,r9w
    mov rax,rdx
    ret

_itoflt endp

    end
