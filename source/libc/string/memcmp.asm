; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcmp proc a:ptr, b:ptr, count:size_t

ifdef _WIN64
    xchg    rsi,rdx
    xchg    rdi,rcx
    xchg    rcx,r8
else
    mov     edx,esi
    push    edi
    mov     edi,a
    mov     esi,b
    mov     ecx,count
endif
    xor     eax,eax
    repe    cmpsb
    jz      @F
    sbb     rax,rax
    sbb     rax,-1
@@:
ifdef _WIN64
    mov     rdi,r8
else
    pop     edi
endif
    mov     rsi,rdx
    ret

memcmp endp

    end
