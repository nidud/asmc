; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcmp proc uses rsi rdi a:ptr, b:ptr, count:size_t

    ldr     rdi,a
    ldr     rsi,b
    ldr     rcx,count
    xor     eax,eax
    repe    cmpsb
    jz      @F
    sbb     rax,rax
    sbb     rax,-1
@@:
    ret

memcmp endp

    end
