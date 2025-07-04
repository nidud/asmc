; _TCSNCICMP.ASM--
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
define rga <r10>
define use_regs <>
else
define rgd <edi>
define rgq <edi>
define reg <esi>
define rga <ebx>
define use_regs <uses esi edi ebx>
endif

    .code

    option dotname

_tcsncicmp proc use_regs a:tstring_t, b:tstring_t, size:size_t

    ldr     rga,a
    ldr     rcx,size
    ldr     rdx,b

    mov     reg,_pclmap
    mov     eax,1
.0:
    test    eax,eax
    jz      .1
    mov     eax,ecx
    test    ecx,ecx
    jz      .1
    dec     ecx
    movzx   eax,tchar_t ptr [rga]
    movzx   rgd,tchar_t ptr [rdx]
    add     rga,tchar_t
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
    jz      .0
    sub     rax,rgq
    jmp     .1
endif

_tcsncicmp endp

    end
