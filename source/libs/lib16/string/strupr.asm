; STRUPR.ASM--
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

strupr proc __ctype uses si string:ptr sbyte

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

strupr endp

    end
