; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

memcpy proc uses rdi dst:ptr, src:ptr, z:size_t

    mov     rax,rcx
    xchg    rsi,rdx
    mov     ecx,r8d
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

memcpy endp

    end
