; _ALLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef _WIN64
    .486
    .model flat, c
endif
    .code

ifdef _WIN64
    int     3
else

_I8D proto

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

endif

    end
