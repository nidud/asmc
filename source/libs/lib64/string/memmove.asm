; MEMMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname
    option win64:rsp noauto

memmove proc uses rsi rdi dst:ptr, src:ptr, z:size_t

    mov     rax,rcx ; return value
    mov     rsi,rdx
    mov     ecx,r8d
    mov     rdi,rax
    cmp     rax,rsi
    ja      .0
    rep     movsb
    jmp     .1
.0:
    lea     rsi,[rsi+rcx-1]
    lea     rdi,[rdi+rcx-1]
    std
    rep     movsb
    cld
.1:
    ret

memmove endp

    end
