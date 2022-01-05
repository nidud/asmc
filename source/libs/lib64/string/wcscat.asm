; WCSCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

wcscat proc dst:wstring_t, src:wstring_t

    mov     rax,rcx
    xor     r8d,r8d
@@:
    cmp     r8w,[rcx]
    je      @F
    add     rcx,2
    jmp     @B
@@:
    mov     r8w,[rdx]
    mov     [rcx],r8w
    add     rcx,2
    add     rdx,2
    test    r8d,r8d
    jnz     @B
    ret

wcscat endp

    end

