; _TCSICMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include ctype.inc
include tchar.inc

ifdef _WIN64
define rgd <r8d>
define rgq <r8>
define reg <r9>
define use_regs <>
else
define rgd <edi>
define rgq <edi>
define reg <esi>
define use_regs <uses esi edi>
endif

    .code

    option dotname

_tcsicmp proc use_regs a:LPTSTR, b:LPTSTR

    ldr     rcx,a
    ldr     rdx,b
    mov     reg,_pclmap
    mov     eax,1
.0:
    test    eax,eax
    jz      .2
    movzx   eax,TCHAR ptr [rcx]
    movzx   rgd,TCHAR ptr [rdx]
    add     rcx,TCHAR
    add     rdx,TCHAR
ifdef _UNICODE
    cmp     eax,255
    ja      .3
    cmp     rgd,255
    ja      .3
endif
    mov     al,[reg+rax]
    cmp     al,[reg+rgq]
    je      .0
.1:
    sbb     rax,rax
    sbb     rax,-1
.2:
    ret
ifdef _UNICODE
.3:
    cmp     eax,rgd
    je      .0
    jmp     .1
endif

_tcsicmp endp

    end
