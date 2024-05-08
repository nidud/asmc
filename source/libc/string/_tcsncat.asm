; _TCSNCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

    option dotname

_tcsncat proc uses rdi rbx dst:LPTSTR, src:LPTSTR, cnt:size_t

    ldr     rcx,dst
    ldr     rdx,src
    ldr     rbx,cnt
    mov     rdi,rcx
    xor     eax,eax
.0:
    cmp     _tal,[rcx]
    je      .1
    add     rcx,TCHAR
    jmp     .0
.1:
    test    ebx,ebx
    jz      .2
    dec     ebx
    mov     _tal,[rdx]
    mov     [rcx],_tal
    add     rcx,TCHAR
    add     rdx,TCHAR
    test    eax,eax
    jnz     .1
    mov     ebx,eax
    sub     rcx,TCHAR
.2:
    mov     [rcx],_tbl
    mov     rax,rdi
    ret

_tcsncat endp

    end
