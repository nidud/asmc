; WCSCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

wcscat proc uses rbx dst:wstring_t, src:wstring_t

ifndef _WIN64
    mov     ecx,dst
    mov     edx,src
endif
    mov     rax,rcx
    xor     ebx,ebx
.0:
    cmp     bx,[rcx]
    je      .1
    add     rcx,2
    jmp     .0
.1:
    mov     bx,[rdx]
    mov     [rcx],bx
    add     rcx,2
    add     rdx,2
    test    ebx,ebx
    jnz     .1
    ret

wcscat endp

    end

