; STRCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

strcat proc dst:string_t, src:string_t

    mov     rax,rcx
    xor     r8d,r8d
@@:
    cmp     r8b,[rcx]
    je      @F
    add     rcx,1
    jmp     @B
@@:
    mov     r8b,[rdx]
    mov     [rcx],r8b
    add     rcx,1
    add     rdx,1
    test    r8d,r8d
    jnz     @B
    ret

strcat endp

    end
