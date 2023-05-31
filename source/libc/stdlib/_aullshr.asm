; _AULLSHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef _WIN64
    .486
    .model flat, c
endif
    .code

    option dotname

ifndef _WIN64

_U8RS::

    mov     ecx,ebx

_aullshr::
__ullshr::

    cmp     cl,63
    ja      .1
    cmp     cl,31
    ja      .0
    shrd    eax,edx,cl
    shr     edx,cl
    ret
.0:
    mov     eax,edx
    xor     edx,edx
    and     cl,31
    shr     eax,cl
    ret
.1:
    xor     eax,eax
    xor     edx,edx
    ret
else
    int     3
endif
    end
