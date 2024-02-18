; AULLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Unsigned binary division of [RAX|EDX:EAX] by [RDX|ECX:EBX]
;
;  dividend / divisor = [quotient.remainder](dividend.divisor)
;
include stdlib.inc

    option dotname

    .code

ifndef _WIN64
_U8D::
endif

aulldiv proc watcall dividend:qword, divisor:qword
ifdef _WIN64
    mov     rcx,rdx
    xor     edx,edx
    div     rcx
    ret
else
    test    ecx,ecx
    jnz     .2
    dec     ebx
    jz      .1
    inc     ebx
    cmp     ebx,edx
    ja      .0
    mov     ecx,eax
    mov     eax,edx
    xor     edx,edx
    div     ebx
    xchg    ecx,eax
.0:
    div     ebx
    mov     ebx,edx
    mov     edx,ecx
    xor     ecx,ecx
.1:
    ret
.2:
    cmp     ecx,edx
    jb      .4
    jne     .3
    cmp     ebx,eax
    ja      .3
    sub     eax,ebx
    mov     ebx,eax
    xor     ecx,ecx
    xor     edx,edx
    mov     eax,1
    jmp     .1
.3:
    xor     ecx,ecx
    xor     ebx,ebx
    xchg    ebx,eax
    xchg    ecx,edx
    jmp     .1

.4: ; the hard way

    push    ebp
    push    esi
    push    edi

    xor     ebp,ebp
    xor     esi,esi
    xor     edi,edi
.5:
    add     ebx,ebx
    adc     ecx,ecx
    jc      .8
    inc     ebp
    cmp     ecx,edx
    jc      .5
    ja      .6
    cmp     ebx,eax
    jbe     .5
.6:
    clc
.7:
    adc     esi,esi
    adc     edi,edi
    dec     ebp
    js      .b
.8:
    rcr     ecx,1
    rcr     ebx,1
    sub     eax,ebx
    sbb     edx,ecx
    cmc
    jc      .7
.9:
    add     esi,esi
    adc     edi,edi
    dec     ebp
    js      .a
    shr     ecx,1
    rcr     ebx,1
    add     eax,ebx
    adc     edx,ecx
    jnc     .9
    jmp     .7
.a:
    add     eax,ebx
    adc     edx,ecx
.b:
    mov     ebx,eax
    mov     ecx,edx
    mov     eax,esi
    mov     edx,edi
    pop     edi
    pop     esi
    pop     ebp
    jmp     .1
endif
aulldiv endp

ifndef _WIN64
_aulldiv::
    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    aulldiv
    pop     ebx
    ret     16
endif

    end
