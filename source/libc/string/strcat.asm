; STRCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

strcat proc dst:string_t, src:string_t

ifdef _WIN64
    ldr     rcx,dst
    ldr     rdx,src
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
else
    mov     edx,dst
    xor     eax,eax
    or      ecx,-1
    xchg    edx,edi
    repnz   scasb
    dec     edi
    xchg    edx,edi
    mov     ecx,src
@@:
    mov     al,[ecx]
    mov     [edx],al
    inc     ecx
    inc     edx
    test    al,al
    jnz     @B
    mov     eax,dst
endif
    ret

strcat endp

    end
