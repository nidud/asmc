; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

memchr proc p:ptr, c:int_t, count:size_t

    xchg    rcx,rdi
    xchg    rcx,r8
    mov     eax,edx
    repnz   scasb
    lea     rax,[rdi-1]
    mov     rdi,r8
    cmovnz  rax,rcx
    ret

memchr endp

    end
