; _ALLSHR.ASM--
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

ifdef _WIN64

    int 3

else

_I8RS::

    mov     ecx,ebx

_allshr::

    cmp     cl,63
    ja      .1
    cmp     cl,31
    ja      .0
    shrd    eax,edx,cl
    sar     edx,cl
    ret
.0:
    mov     eax,edx
    sar     edx,31
    and     cl,31
    sar     eax,cl
    ret
.1:
    sar     edx,31
    mov     eax,edx
    ret
endif
    end
