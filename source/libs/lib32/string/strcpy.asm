; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

option dotname

    .code

strcpy::

    push    edi
    mov     edi,[esp+8]
    mov     ecx,[esp+12]
    jmp     .1
.0:
    mov     [edi],eax
    add     edi,4
.1:
    mov     eax,[ecx]
    add     ecx,4
    lea     edx,[eax-0x01010101]
    not     eax
    and     edx,eax
    not     eax
    and     edx,0x80808080
    jz      .0
    mov     [edi],al
    test    al,al
    jz      .2
    mov     [edi+1],ah
    test    ah,ah
    jz      .2
    shr     eax,16
    mov     [edi+2],al
    test    al,al
    jz      .2
    mov     [edi+3],ah
.2:
    mov     eax,[esp+8]
    pop     edi
    ret

    end
