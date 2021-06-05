; _FLTTOI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include limits.inc
include errno.inc

    .code

    option win64:rsp noauto

_flttoi proc p:ptr STRFLT

    mov r8,rcx
    mov cx,[r8+16]
    mov eax,ecx
    and eax,Q_EXPMASK
    .ifs eax < Q_EXPBIAS
        xor eax,eax
    .elseif eax > 32 + Q_EXPBIAS
        _set_errno(ERANGE)
        mov eax,INT_MAX
        .if cx & 0x8000
            mov eax,INT_MIN
        .endif
    .else
        mov edx,[r8+12]
        mov ecx,eax
        sub ecx,Q_EXPBIAS-1
        xor eax,eax
        shld eax,edx,cl
        .if byte ptr [r8+16] & 0x80
            neg eax
        .endif
    .endif
    ret

_flttoi endp

    end
