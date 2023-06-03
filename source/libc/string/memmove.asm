; MEMMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

if defined(_AMD64_) and defined(__AVX__)
else
    option dotname

memmove proc uses rsi rdi dst:ptr, src:ptr, count:size_t

    ldr     rax,dst
    ldr     rsi,src
    ldr     rcx,count

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
endif
    end
