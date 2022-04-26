; _I64TOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_i64toflt proc p:ptr STRFLT, ll:int64_t

    mov rax,rsi
    mov esi,Q_EXPBIAS   ; set exponent
    test rax,rax        ; if number is negative
    .ifs
        neg rax         ; negate number
        or  esi,0x8000
    .endif
    xor edx,edx
    .if rax
        bsr rdx,rax     ; find most significant non-zero bit
        mov ecx,63
        sub ecx,edx
        shl rax,cl      ; shift bits into position
        add edx,esi     ; calculate exponent
    .endif
    xor ecx,ecx
    mov [rdi].STRFLT.mantissa.l,rcx
    mov [rdi].STRFLT.mantissa.h,rax
    mov [rdi].STRFLT.mantissa.e,dx
    mov rax,rdi
    ret

_i64toflt endp

    end
