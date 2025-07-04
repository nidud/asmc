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

_tcsicmp proc use_regs a:tstring_t, b:tstring_t

    ldr     rcx,a
    ldr     rdx,b
    mov     reg,_pclmap
    mov     eax,1
.0:
    test    eax,eax
    jz      .1
    movzx   eax,tchar_t ptr [rcx]
    movzx   rgd,tchar_t ptr [rdx]
    add     rcx,tchar_t
    add     rdx,tchar_t
ifdef _UNICODE
    test    eax,0xFF00
    jnz     .2
    test    rgd,0xFF00
    jnz     .2
endif
    mov     al,[reg+rax]
    cmp     al,[reg+rgq]
    je      .0
    sub     al,[reg+rgq]
    movsx   rax,al
.1:
    ret
ifdef _UNICODE
.2:
    cmp     eax,rgd
    je      .0
    sub     rax,rgq
    jmp     .1
endif

_tcsicmp endp

    end
