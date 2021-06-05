; _I64TOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_i64toflt proc p:ptr STRFLT, ll:int64_t

    mov rax,rdx
    mov rdx,rcx
    mov r8d,Q_EXPBIAS   ; set exponent
    test rax,rax        ; if number is negative
    .ifs
        neg rax         ; negate number
        or  r8d,0x8000
    .endif
    xor r9d,r9d
    .if rax
        bsr r9,rax      ; find most significant non-zero bit
        mov ecx,63
        sub ecx,r9d
        shl rax,cl      ; shift bits into position
        add r9d,r8d     ; calculate exponent
    .endif
    xor ecx,ecx
    mov [rdx].STRFLT.mantissa.l,rcx
    mov [rdx].STRFLT.mantissa.h,rax
    mov [rdx].STRFLT.mantissa.e,r9w
    mov rax,rdx
    ret

_i64toflt endp

    end
