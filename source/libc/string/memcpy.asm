; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcpy proc uses rsi rdi dst:ptr, src:ptr, size:size_t

    ldr rax,dst
    ldr rsi,src
    ldr rcx,size
    mov rdi,rax
    rep movsb
    ret

memcpy endp

    end
