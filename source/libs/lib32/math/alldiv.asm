; ALLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .486
    .model flat, c
    .code

_U8D proto

_I8D::

alldiv proc watcall dividend:qword, divisor:qword

    or edx,edx          ; hi word of dividend signed ?
    .ifns
        or ecx,ecx      ; hi word of divisor signed ?
        .ifns
            _U8D()
            ret
        .endif
        neg ecx
        neg ebx
        sbb ecx,0
        _U8D()
        neg edx
        neg eax
        sbb edx,0
        ret
    .endif
    neg edx
    neg eax
    sbb edx,0
    or ecx,ecx
    .ifs
        neg ecx
        neg ebx
        sbb ecx,0
        _U8D()
        neg ecx
        neg ebx
        sbb ecx,0
        ret
    .endif
    _U8D()
    neg ecx
    neg ebx
    sbb ecx,0
    neg edx
    neg eax
    sbb edx,0
    ret

alldiv endp

__lldiv::
_alldiv::

    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    _I8D
    pop     ebx
    ret     16

    END
