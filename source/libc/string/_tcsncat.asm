; _TCSNCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strncat(char *strDest, const char *strSource, size_t count);
; wchar_t *wcsncat(wchar_t *strDest, const wchar_t *strSource, size_t count);
;
include string.inc
include tchar.inc

    .code

    option dotname

_tcsncat proc uses rdi rbx dst:tstring_t, src:tstring_t, cnt:size_t

    ldr     rcx,dst
    ldr     rdx,src
    ldr     rbx,cnt
    mov     rdi,rcx
    xor     eax,eax
.0:
    cmp     _tal,[rcx]
    je      .1
    add     rcx,tchar_t
    jmp     .0
.1:
    test    ebx,ebx
    jz      .2
    dec     ebx
    mov     _tal,[rdx]
    mov     [rcx],_tal
    add     rcx,tchar_t
    add     rdx,tchar_t
    test    eax,eax
    jnz     .1
    mov     ebx,eax
    sub     rcx,tchar_t
.2:
    mov     [rcx],_tbl
    mov     rax,rdi
    ret

_tcsncat endp

    end
