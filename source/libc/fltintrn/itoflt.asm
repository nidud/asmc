; ITOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_itoflt proc __ccall p:ptr STRFLT, i:int_t

ifdef _WIN64

    mov eax,edx
    mov rdx,rcx
    mov r8d,Q_EXPBIAS   ; set exponent
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        or  r8d,0x8000
    .endif
    xor r9d,r9d
    .if eax
        bsr r9,rax          ; find most significant non-zero bit
        mov ecx,63
        sub ecx,r9d
        shl rax,cl          ; shift bits into position
        add r9d,r8d         ; calculate exponent
    .endif
    xor ecx,ecx
    mov [rdx].STRFLT.mantissa.l,rcx
    mov [rdx].STRFLT.mantissa.h,rax
    mov [rdx].STRFLT.mantissa.e,r9w
    mov rax,rdx

else

    mov eax,i
    mov edx,Q_EXPBIAS   ; set exponent
    test eax,eax        ; if number is negative
    .ifs
        neg eax         ; negate number
        or  edx,0x8000
    .endif
    xor ecx,ecx
    .if eax
        bsr ecx,eax     ; find most significant non-zero bit
        mov ch,cl
        mov cl,31
        sub cl,ch
        shl eax,cl  ; shift bits into position
        shr ecx,8       ; get shift count
        add ecx,edx     ; calculate exponent
    .endif
    mov edx,eax
    mov eax,p
    mov dword ptr [eax].STRFLT.mantissa.h[4],edx
    mov [eax].STRFLT.mantissa.e,cx
    xor edx,edx         ; zero the rest of the fraction bits
    mov dword ptr [eax].STRFLT.mantissa.l[0],edx
    mov dword ptr [eax].STRFLT.mantissa.l[4],edx
    mov dword ptr [eax].STRFLT.mantissa.h[0],edx
endif
    ret

_itoflt endp

    end
