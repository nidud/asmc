; _FLTTOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include limits.inc
include errno.inc

    .code

_flttoi64 proc p:ptr STRFLT

    mov edx,p
    mov cx,[edx+16]
    mov eax,ecx
    and eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor edx,edx
        xor eax,eax
        .if cx & 0x8000
            dec eax
            dec edx
        .endif

    .elseif eax > 62 + Q_EXPBIAS

        _set_errno(ERANGE)
        xor eax,eax
        .if cx & 0x8000
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif

    .else
        mov ecx,eax
        xor eax,eax
        sub ecx,Q_EXPBIAS-1
        .if ecx < 32
            mov edx,[edx+12]
            shld eax,edx,cl
            xor edx,edx
        .else
            push esi
            push edi
            mov edi,[edx+12]
            mov esi,[edx+8]
            xor edx,edx
            .while ecx
                add esi,esi
                adc edi,edi
                adc eax,eax
                adc edx,edx
                dec ecx
            .endw
            pop edi
            pop esi
        .endif
        mov ecx,p
        .if byte ptr [ecx+17] & 0x80
            neg edx
            neg eax
            sbb edx,0
        .endif
    .endif
    ret

_flttoi64 endp

    end
