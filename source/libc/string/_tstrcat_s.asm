; _TSTRCAT_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc
include tmacro.inc

    .code

    assume rcx:ptr TCHAR

_tcscat_s proc uses rbx dst:LPTSTR, cnt:size_t, src:LPTSTR

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
    cmp     __a,[rcx]
    je      .1
    add     rcx,TCHAR
    dec     rbx
    jnz     .0
    jmp     .4
.1:
    mov     [rcx],[rdx]
.2:
    dec     rbx
    jz      .7
    test    eax,eax
    jz      .3
    add     rcx,TCHAR
    add     rdx,TCHAR
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
    mov     [rcx],__b
    invoke  _set_errno,ERANGE
    mov     eax,ERANGE
    jmp     .3

_tcscat_s endp

    end
