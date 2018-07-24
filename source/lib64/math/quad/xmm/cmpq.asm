
include quadmath.inc

    .code

    option win64:rsp nosave noauto

cmpq proc vectorcall A:XQFLOAT, B:XQFLOAT

    xor     eax,eax
    movq    rcx,xmm0
    shufps  xmm0,xmm0,01001110B
    movq    rdx,xmm0
    shufps  xmm0,xmm0,01001110B
    movq    r10,xmm1
    shufps  xmm1,xmm1,01001110B
    movq    r11,xmm1
    shufps  xmm1,xmm1,01001110B
    cmp     rcx,r10
    jne     @F
    cmp     rdx,r11
    jz      toend
@@:
    test    rdx,rdx
    js      a_signed
    test    r11,r11
    js      b_signed
unsigned:
    cmp     rdx,r11
    sbb     rax,rax
    jnz     toend
    cmp     rcx,r10
    sbb     rax,rax
    jnz     toend
    inc     eax
    ret
a_signed:
    test    r11,r11
    js      b_signed
    dec     rax
    ret
b_signed:
    xchg    rcx,r10
    xchg    rdx,r11
    jmp     unsigned
toend:
    ret

cmpq endp

    end
