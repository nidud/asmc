; _STRUPR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

_strupr proc uses si string:string_t

    pushl   ds
    ldsl    si,string
.0:
    mov     al,[si]
    test    al,al
    jz      .1
    inc     si
    cmp     al,'a'
    jb      .0
    cmp     al,'z'
    ja      .0
    and     byte ptr [si-1],not 0x20
    jmp     .0
.1:
    movl    dx,ds
    mov     ax,word ptr string
    popl    ds
    ret

_strupr endp

    end
