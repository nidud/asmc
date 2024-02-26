; _TSTRNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcsnccmp proc uses rbx a:LPTSTR, b:LPTSTR, count:size_t

    ldr     rcx,a
    ldr     rbx,count
    ldr     rdx,b
    mov     eax,1
    sub     rcx,TCHAR
    sub     rdx,TCHAR
.0:
    test    eax,eax
    jz      .2
    test    ebx,ebx
    jz      .1
    dec     rbx
    add     rcx,TCHAR
    add     rdx,TCHAR
    mov     __a,[rcx]
    cmp     __a,[rdx]
    je      .0
    sbb     rbx,rbx
    sbb     rbx,-1
.1:
    mov     rax,rbx
.2:
    ret

_tcsnccmp endp

    end
