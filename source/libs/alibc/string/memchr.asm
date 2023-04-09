; MEMCHR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memchr proc p:ptr, c:int_t, count:size_t

    mov     eax,esi
    mov     ecx,edx
    repnz   scasb
    lea     rax,[rdi-1]
    cmovnz  rax,rcx
    ret

memchr endp

    end
