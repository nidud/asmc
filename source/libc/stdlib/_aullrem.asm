; AULLREM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

ifndef _WIN64

    .486
    .model flat, c

_U8D proto

endif
    .code

ifndef _WIN64

__ullmod::
_aullrem::

    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    _U8D
    mov     eax,ebx
    mov     edx,ecx
    pop     ebx
    ret     16

else
    int     3
endif
    end
