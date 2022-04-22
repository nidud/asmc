; STRCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strcat proc dst:string_t, src:string_t

    mov     rax,rdi
    xor     ecx,ecx
@@:
    cmp     cl,[rdi]
    je      @F
    add     rdi,1
    jmp     @B
@@:
    mov     cl,[rsi]
    mov     [rdi],cl
    add     rdi,1
    add     rsi,1
    test    ecx,ecx
    jnz     @B
    ret

strcat endp

    end
