; STRNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strncmp proc a:string_t, b:string_t, count:size_t
ifndef _WIN64
    push    ebx
    mov     ecx,a
    mov     edx,b
    mov     ebx,count
endif
    mov     eax,1
    dec     rcx
    dec     rdx
.0:
    test    al,al
    jz      .2
ifdef _WIN64
    test    r8d,r8d
    jz      .1
    dec     r8d
else
    test    ebx,ebx
    jz      .1
    dec     ebx
endif
    inc     rcx
    inc     rdx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .0
ifdef _WIN64
    sbb     r8,r8
    sbb     r8,-1
.1:
    mov     rax,r8
.2:
else
    sbb     ebx,ebx
    sbb     ebx,-1
.1:
    mov     eax,ebx
.2:
    pop     ebx
endif
    ret

strncmp endp

    end
