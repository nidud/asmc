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

    mov dx,[rdi+16]
    mov eax,edx
    and eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor eax,eax
        .if dx & 0x8000
            dec rax
        .endif

    .elseif eax > 62 + Q_EXPBIAS

        _set_errno(ERANGE)
        mov rax,_I64_MAX
        .if edx & 0x8000
            mov rax,_I64_MIN
        .endif
    .else
        mov ecx,eax
        xor eax,eax
        sub ecx,Q_EXPBIAS-1
        mov r8,[rdi+8]
        shld rax,r8,cl
        .if edx & 0x8000
            neg rax
        .endif
    .endif
    ret

_flttoi64 endp

    end
