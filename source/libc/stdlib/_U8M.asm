; _U8M.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; WATCALL calling convention, C decoration
;
ifndef _WIN64

    .386
    .model flat, c
endif
    .code

ifndef _WIN64

_I8M::
_U8M::

    .if ( !edx && !ecx )

        mul ebx

    .else

        push    eax
        push    edx
        mul     ecx
        mov     ecx,eax
        pop     eax
        mul     ebx
        add     ecx,eax
        pop     eax
        mul     ebx
        add     edx,ecx

    .endif
    ret
else
    int 3
endif
    end
