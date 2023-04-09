; MEMCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

memcpy proc dst:ptr, src:ptr, z:size_t

    mov     rcx,rdx
    mov     rax,rdi
    rep     movsb
    ret

memcpy endp

    end
