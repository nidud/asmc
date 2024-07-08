; ALLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdlib.inc

    option dotname

    .code

ifndef _WIN64
_I8D::
endif

alldiv proc watcall dividend:int64_t, divisor:int64_t
ifdef _WIN64
    mov     rcx,rdx
    cqo
    idiv    rcx
else
    ;
    ; edx:eax / ecx:ebx --> edx:eax.ecx:ebx
    ;
    test    edx,edx     ; hi word of dividend
    js      .1          ; signed ?
    test    ecx,ecx     ; hi word of divisor
    js      .0          ; signed ?
    call    aulldiv
    jmp     .3
.0:
    neg     ecx
    neg     ebx
    sbb     ecx,0
    call    aulldiv
    neg     edx
    neg     eax
    sbb     edx,0
    jmp     .3
.1:
    neg     edx
    neg     eax
    sbb     edx,0
    test    ecx,ecx
    jns     .2
    neg     ecx
    neg     ebx
    sbb     ecx,0
    call    aulldiv
    neg     ecx
    neg     ebx
    sbb     ecx,0
    jmp     .3
.2:
    call    aulldiv
    neg     ecx
    neg     ebx
    sbb     ecx,0
    neg     edx
    neg     eax
    sbb     edx,0
.3:
endif
    ret

alldiv endp

ifndef _WIN64

__lldiv::
_alldiv::

    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    alldiv
    pop     ebx
    ret     16

endif

    end

