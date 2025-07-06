; _STRLWR.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

_strlwr proc uses si string:string_t

    pushl   ds
    ldsl    si,string
.0:
    mov     al,[si]
    test    al,al
    jz      .1
    inc     si
    cmp     al,'Z'
    ja      .0
    cmp     al,'A'
    jb      .0
    or      byte ptr [si-1],0x20
    jmp     .0
.1:
    mov     ax,word ptr string
    movl    dx,ds
    popl    ds
    ret

_strlwr endp

    end
