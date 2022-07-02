; _I64TOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_i64toflt proc __ccall p:ptr STRFLT, ll:int64_t

ifdef _WIN64

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

else

    push ebx

    mov eax,dword ptr ll[0]
    mov edx,dword ptr ll[4]
    mov ebx,Q_EXPBIAS   ; set exponent

    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        neg eax
        sbb edx,0
        or  ebx,0x8000
    .endif

    xor ecx,ecx
    .if ( eax || edx )

        .if edx         ; find most significant non-zero bit
            bsr ecx,edx
            add ecx,32
        .else
            bsr ecx,eax
        .endif

        mov ch,cl
        mov cl,64
        sub cl,ch

        .if ( cl <= 64 ) ; shift bits into position
            dec cl
            .if ( cl >= 32 )
                sub cl,32
                mov edx,eax
                xor eax,eax
            .endif
            shld edx,eax,cl
            shl eax,cl
        .else
            xor eax,eax
            xor edx,edx
        .endif
        shr ecx,8       ; get shift count
        add ecx,ebx     ; calculate exponent
    .endif

    mov     ebx,p
    xchg    eax,ebx
    mov     dword ptr [eax].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [eax].STRFLT.mantissa.h[4],edx
    mov     [eax].STRFLT.mantissa.e,cx
    xor     edx,edx ; zero the rest of the fraction bits
    mov     dword ptr [eax].STRFLT.mantissa.l[0],edx
    mov     dword ptr [eax].STRFLT.mantissa.l[4],edx
    pop     ebx
endif
    ret

_i64toflt endp

    end
