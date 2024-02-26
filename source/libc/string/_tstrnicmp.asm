; _TSTRNICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tmacro.inc

    .code

_tcsncicmp proc uses rbx a:LPTSTR, b:LPTSTR, size:size_t

    ldr     rbx,a
    ldr     rcx,size
    ldr     rdx,b

    sub     rbx,TCHAR
    sub     rdx,TCHAR
    mov     eax,1
.0:
    test    eax,eax
    jz      .3
    add     rbx,TCHAR
    add     rdx,TCHAR
    xor     eax,eax
    test    ecx,ecx
    jz      .3
    dec     ecx
    mov     __a,[rbx]
    cmp     __a,[rdx]
    je      .0
    cmp     __a,'A'
    jb      .1
    cmp     __a,'Z'
    ja      .1
    or      al,0x20
    cmp     __a,[rdx]
    je      .0
    jmp     .2
.1:
    mov     __a,[rdx]
    cmp     __a,'A'
    jb      .2
    cmp     __a,'Z'
    ja      .2
    or      al,0x20
    cmp     __a,[rbx]
    je      .0
.2:
    mov     __a,[rbx]
    cmp     __a,[rdx]
    sbb     rax,rax
    sbb     rax,-1
.3:
    ret

_tcsncicmp endp

    end
