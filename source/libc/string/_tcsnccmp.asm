; _TCSNCCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; int strncmp(const char *string1, const char *string2, size_t count);
; int wcsncmp(const wchar_t *string1, const wchar_t *string2, size_t count);
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcsnccmp proc uses rbx a:tstring_t, b:tstring_t, count:size_t

    ldr     rcx,a
    ldr     rbx,count
    ldr     rdx,b
    mov     eax,1
    sub     rcx,tchar_t
    sub     rdx,tchar_t
.0:
    test    eax,eax
    jz      .2
    test    ebx,ebx
    jz      .1
    dec     rbx
    add     rcx,tchar_t
    add     rdx,tchar_t
    mov     _tal,[rcx]
    cmp     _tal,[rdx]
    je      .0
    sbb     rbx,rbx
    sbb     rbx,-1
.1:
    mov     rax,rbx
.2:
    ret

_tcsnccmp endp

    end
