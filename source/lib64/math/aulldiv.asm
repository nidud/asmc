
    .code

_aulldiv::  ; rdx::rcx / r9::r8
__udivti3::

    mov     rax,rcx
    test    r9,r9
    jnz     noteasy
    dec     r8
    jz      quit
    inc     r8
    cmp     r8,rdx
    ja      @F

    mov     r9,rcx
    mov     rax,rdx
    xor     edx,edx
    div     r8
    xchg    r9,rax
@@:
    div     r8
    mov     r8,rdx
    mov     rdx,r9
    xor     r9,r9
quit:
    ret

noteasy:
    cmp     r9,rdx
    jb      thehardway
    jne     @F
    cmp     r8,rax
    ja      @F
    sub     rax,r8
    mov     r8,rax
    xor     r9,r9
    xor     edx,edx
    mov     eax,1
    ret
@@:
    xor     r9,r9
    xor     r8,r8
    xchg    r8,rax
    xchg    r9,rdx
    ret

thehardway:

    xor     r10,r10
    xor     r11,r11
    xor     rcx,rcx
@@:
    add     r8,r8
    adc     r9,r9
    jc      L009
    inc     rcx
    cmp     r9,rdx
    jc      @B
    ja      @F
    cmp     r8,rax
    jbe     @B
@@:
    clc
lupe:
    adc     r10,r10
    adc     r11,r11
    dec     rcx
    js      toend
L009:
    rcr     r9,1
    rcr     r8,1
    sub     rax,r8
    sbb     rdx,r9
    cmc
    jc      lupe
@@:
    add     r10,r10
    adc     r11,r11
    dec     rcx
    js      done
    shr     r9,1
    rcr     r8,1
    add     rax,r8
    adc     rdx,r9
    jnc     @B
    jmp     lupe
done:
    add     rax,r8
    adc     rdx,r9
toend:
    mov     r8,rax
    mov     r9,rdx
    mov     rax,r10
    mov     rdx,r11
    ret

    END
