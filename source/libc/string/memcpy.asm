; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcpy proc uses rdi dst:ptr, src:ptr, z:size_t

ifdef _WIN64
    mov     rax,rcx
    xchg    rsi,rdx
    mov     ecx,r8d
else
    mov     eax,dst
    mov     edx,esi
    mov     esi,src
    mov     ecx,z
endif
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

memcpy endp

    end
