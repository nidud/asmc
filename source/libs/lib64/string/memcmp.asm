; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

memcmp proc a:ptr, b:ptr, count:size_t

    xchg    rsi,rdx
    xchg    rdi,rcx
    xchg    rcx,r8
    xor     rax,rax
    repe    cmpsb
    jz      @F
    sbb     al,al
    sbb     al,-1
@@:
    mov     rdi,r8
    mov     rsi,rdx
    ret

memcmp endp

    END
