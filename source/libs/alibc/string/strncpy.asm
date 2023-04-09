; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strncpy proc dst:string_t, src:string_t, count:size_t

    mov     ecx,edx
    mov     rdx,rdi
.0:
    test    ecx,ecx
    jz      .1
    dec     ecx
    mov     al,[rsi]
    mov     [rdi],al
    add     rsi,1
    add     rdi,1
    test    al,al
    jnz     .0
    rep     stosb
.1:
    mov     rax,rdx
    ret

strncpy endp

    end

