; _TCSCAT_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc
include tchar.inc

    .code

    option dotname
    assume rcx:ptr tchar_t

_tcscat_s proc uses rbx dst:tstring_t, cnt:size_t, src:tstring_t

    ldr     rcx,dst
    ldr     rbx,cnt
    test    rcx,rcx
    jz      .6
    test    rbx,rbx
    jz      .6
    ldr     rdx,src
    xor     eax,eax
    test    rdx,rdx
    jz      .5
ifdef _WIN64
    mov     r8,rcx
endif
.0:
    cmp     _tal,[rcx]
    je      .1
    add     rcx,tchar_t
    dec     rbx
    jnz     .0
    jmp     .4
.1:
    mov     [rcx],[rdx]
.2:
    test    eax,eax
    jz      .3
    dec     rbx
    jz      .7
    add     rcx,tchar_t
    add     rdx,tchar_t
    mov     [rcx],[rdx]
    jmp     .2
.3:
    ret
.4:
ifdef _WIN64
    mov     rcx,r8
else
    mov     rcx,dst
endif
.5:
    mov     [rcx],0
.6:
    invoke  _set_errno,EINVAL
    mov     eax,EINVAL
    jmp     .3
.7:
ifdef _WIN64
    mov     rcx,r8
else
    mov     rcx,dst
endif
    mov     [rcx],_tbl
    invoke  _set_errno,ERANGE
    mov     eax,ERANGE
    jmp     .3

_tcscat_s endp

    end
