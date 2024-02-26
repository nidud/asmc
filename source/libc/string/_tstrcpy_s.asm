; _TSTRCPY_S.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc
include tmacro.inc

    .code

    assume rcx:ptr TCHAR

_tcscpy_s proc uses rbx dst:LPTSTR, cnt:size_t, src:LPTSTR

    ldr     rcx,dst
    ldr     rbx,cnt
    test    rcx,rcx
    jz      .3
    test    rbx,rbx
    jz      .3
    ldr     rdx,src
    xor     eax,eax
    test    rdx,rdx
    jz      .2
ifdef _WIN64
    mov     r8,rcx
endif
    mov     [rcx],[rdx]
.0:
    dec     rbx
    jz      .4
    test    eax,eax
    jz      .1
    add     rcx,TCHAR
    add     rdx,TCHAR
    mov     [rcx],[rdx]
    jmp     .0
.1:
    ret
.2:
    mov     [rcx],__a
.3:
    invoke  _set_errno,EINVAL
    mov     eax,EINVAL
    jmp     .1
.4:
ifdef _WIN64
    mov     rcx,r8
else
    mov     rcx,dst
endif
    mov     [rcx],__b
    invoke  _set_errno,ERANGE
    mov     eax,ERANGE
    jmp     .1

_tcscpy_s endp

    end
