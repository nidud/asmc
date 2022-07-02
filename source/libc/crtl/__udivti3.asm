; __UDIVTI3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

ifdef _WIN64

    option dotname

__udivti3 proc dividend:uint128_t, divisor:uint128_t

    mov     rax,rcx
    test    r9,r9
    jnz     .2
    dec     r8
    jz      .1
    inc     r8
    cmp     r8,rdx
    ja      .0

    mov     r9,rcx
    mov     rax,rdx
    xor     edx,edx
    div     r8
    xchg    r9,rax
.0:
    div     r8
    mov     r8,rdx
    mov     rdx,r9
    xor     r9,r9
.1:
    ret
.2:
    cmp     r9,rdx
    jb      .4
    jne     .3
    cmp     r8,rax
    ja      .3
    sub     rax,r8
    mov     r8,rax
    xor     r9,r9
    xor     edx,edx
    mov     eax,1
    jmp     .1
.3:
    xor     r9,r9
    xor     r8,r8
    xchg    r8,rax
    xchg    r9,rdx
    jmp     .1

.4: ; the hard way

    xor     r10,r10
    xor     r11,r11
    mov     ecx,-1
.5:
    inc     ecx
    add     r8,r8
    adc     r9,r9
    jc      .6
    cmp     r9,rdx
    jc      .5
    ja      .6
    cmp     r8,rax
    jbe     .5
.6:
    rcr     r9,1
    rcr     r8,1
    sub     rax,r8
    sbb     rdx,r9
    cmc
    jc      .9
.7:
    add     r10,r10
    adc     r11,r11
    dec     ecx
    jns     .8
    add     rax,r8
    adc     rdx,r9
    jmp     .done
.8:
    shr     r9,1
    rcr     r8,1
    add     rax,r8
    adc     rdx,r9
    jnc     .7
.9:
    adc     r10,r10
    adc     r11,r11
    dec     ecx
    jns     .6
.done:
    mov     r8,rax
    mov     r9,rdx
    mov     rax,r10
    mov     rdx,r11
    jmp     .1

__udivti3 endp

else
    int     3
endif
    end
