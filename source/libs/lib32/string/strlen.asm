; STRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option dotname

strlen::

    mov     eax,[esp+4]
    mov     ecx,eax
    and     ecx,3
    jz      .1
    sub     eax,ecx
    shl     ecx,3
    mov     edx,-1
    shl     edx,cl
    not     edx
    or      edx,[eax]
    lea     ecx,[edx-0x01010101]
    not     edx
    and     ecx,edx
    and     ecx,0x80808080
    jnz     .2
.0: add     eax,4
.1: mov     edx,[eax]
    lea     ecx,[edx-0x01010101]
    not     edx
    and     ecx,edx
    and     ecx,0x80808080
    jz      .0
.2: bsf     ecx,ecx
    shr     ecx,3
    add     eax,ecx
    sub     eax,[esp+4]
    ret

    end
