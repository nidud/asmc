; _I64TOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_i64toflt proc uses ebx p:ptr STRFLT, ll:int64_t

    mov eax,dword ptr ll
    mov edx,dword ptr ll[4]
    mov ebx,Q_EXPBIAS   ; set exponent

    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        neg eax
        sbb edx,0
        or  ebx,0x8000
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
        .if cl <= 64     ; shift bits into position
            dec cl
            .if cl >= 32
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
    .else
        xor ecx,ecx     ; else zero
    .endif

    mov     ebx,p
    xchg    eax,ebx
    mov     [eax+8],ebx
    mov     [eax+12],edx
    mov     [eax+16],cx
    xor     edx,edx     ; zero the rest of the fraction bits
    mov     [eax],edx
    mov     [eax+4],edx
    ret

_i64toflt endp

    end
