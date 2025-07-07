; _TCSSTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strstr(string1, string2) - search for string2 in string1
;
include string.inc
include tchar.inc

option dotname

    .code

_tcsstr proc uses rbx s1:tstring_t, s2:tstring_t

    ldr     rcx,s1
    ldr     rdx,s2

    movzx   eax,tchar_t ptr [rdx]
    test    eax,eax
    jz      .3
.0:
    mov     _tal,[rcx]
    test    _tal,_tal
    jz      .3
    add     rcx,tchar_t
    cmp     _tal,[rdx]
    jne     .0
    xor     ebx,ebx
.1:
    mov     _tal,[rdx+rbx+tchar_t]
    test    _tal,_tal
    jz      .2
    cmp     _tal,[rcx+rbx]
    jne     .0
    add     ebx,tchar_t
    jmp     .1
.2:
    lea     rax,[rcx-tchar_t]
.3:
    ret

_tcsstr endp

    end
