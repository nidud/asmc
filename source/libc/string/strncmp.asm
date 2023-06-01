; STRNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option dotname

strncmp proc uses rbx a:string_t, b:string_t, count:size_t

    ldr     rcx,a
    ldr     rbx,count
    ldr     rdx,b
    mov     eax,1
    dec     rcx
    dec     rdx
.0:
    test    al,al
    jz      .2
    test    ebx,ebx
    jz      .1
    dec     rbx
    inc     rcx
    inc     rdx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .0
    sbb     rbx,rbx
    sbb     rbx,-1
.1:
    mov     rax,rbx
.2:
    ret

strncmp endp

    end
