; WCSNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

wcsncmp proc a:wstring_t, b:wstring_t, count:size_t

    ldr     rcx,a
    ldr     rdx,b

ifndef _WIN64
    push    ebx
    mov     ebx,count
endif
    mov     eax,1
    sub     rcx,2
    sub     rdx,2
.0:
    test    ax,ax
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
    add     rcx,2
    add     rdx,2
    mov     ax,[rcx]
    cmp     ax,[rdx]
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

wcsncmp endp

    end
