; MEMCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcmp proc a:ptr, b:ptr, count:size_t
ifdef _WIN64
ifdef __UNIX__
    mov     rcx,rdx
else
    xchg    rsi,rdx
    xchg    rdi,rcx
    xchg    rcx,r8
endif
else
    push    esi
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
ifndef __UNIX__
    mov     rsi,rdx
    mov     rdi,r8
endif
else
    pop     edi
    pop     esi
endif
    ret

memcmp endp

    end
