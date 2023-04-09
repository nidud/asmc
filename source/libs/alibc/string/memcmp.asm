; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcmp proc a:ptr, b:ptr, count:size_t

    mov     rcx,rdx
    xor     eax,eax
    repe    cmpsb
    jz      @F
    sbb     rax,rax
    sbb     rax,-1
@@:
    ret

memcmp endp

    end
