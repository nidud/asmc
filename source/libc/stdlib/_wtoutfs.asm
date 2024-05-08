; _WTOUTFS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert Wide string to UTF-8
;
include stdlib.inc

    .code

    option dotname

_wtoutfs proc uses rsi rdi rbx buffer:string_t, wstring:wstring_t

    ldr     rdi,buffer
    ldr     rsi,wstring

    xor     eax,eax
.0:
    lodsw
    cmp     eax,0x7F
    ja      .3
.1:
    stosb
    test    eax,eax
    jnz     .0
.2:
    mov     rax,rdi
    sub     rax,buffer
    ret
.3:
    mov     ebx,eax
    xor     eax,eax
    mov     edx,63
    mov     ecx,128
.4:
    cmp     ebx,0x80
    jbe     .5
    mov     al,bl
    and     al,0x3F
    or      al,0x80
    shl     eax,8
    shr     ebx,6
    lea     ecx,[rcx+rdx+1]
    shr     edx,1
    jmp     .4
.5:
    mov     al,cl
    or      al,bl
    stosb
    shr     eax,8
    jz      .0
    stosb
    shr     eax,8
    jz      .0
    stosb
    jmp     .0

_wtoutfs endp

    end
