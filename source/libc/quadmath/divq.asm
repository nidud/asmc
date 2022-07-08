; DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ifdef _WIN64

    option dotname

divq proc uses rsi rdi rbx dest:real16, src:real16

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movq    rbx,xmm1
    movhlps xmm1,xmm1
    movq    rdi,xmm1

    shld    rsi,rdi,16
    shld    rdi,rbx,16
    shl     rbx,16
    mov     r9d,esi
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     rdi,1
    rcr     rbx,1
    shld    rsi,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     r9d,esi
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     rdx,1
    rcr     rax,1

    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000

    mov     rcx,rbx
    or      rcx,rdi
    jz      .zero_b

.if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
    jz      .zero_a

.init_done:

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    rol     ecx,16
    rol     esi,16
    add     cx,si
    rol     ecx,16
    rol     esi,16

    test    cx,cx
    jz      .normalize_a
.if_denormal_b:
    test    si,si
    jz      .normalize_b

.calculate_exponent:
    sub     cx,si
    add     cx,0x3FFF
    js      .too_small
    cmp     cx,0x7FFF
    ja      .infinity
.too_small:
    cmp     cx,-65
    jl      .underflow

.divide:

    define  BITS 14

    push    rcx
    push    rbp

    shrd    rax,rdx,BITS
    shr     rdx,BITS
    shrd    rbx,rdi,BITS
    shr     rdi,BITS

    mov     ecx,113 + (16 - BITS)

    mov     rbp,rdi         ; rbp:rbx
    mov     r10,rax         ; r11:r10
    mov     r11,rdx

    xor     eax,eax         ; rdx:rax
    xor     edx,edx
    xor     r8d,r8d         ; r9:r8
    xor     r9d,r9d
    xor     edi,edi         ; rsi:rdi
    xor     esi,esi

    add     rbx,rbx
    adc     rbp,rbp


.divide_1:
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    sub     rdi,r8
    sbb     rsi,r9
    sbb     r10,rbx
    sbb     r11,rbp
    cmc
    jc      .divide_3

.divide_2:
    add     rax,rax
    adc     rdx,rdx
    dec     ecx
    jz      .end_divide
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    add     rdi,r8
    adc     rsi,r9
    adc     r10,rbx
    adc     r11,rbp
    jnc     .divide_2

.divide_3:
    adc     rax,rax
    adc     rdx,rdx
    dec     ecx
    jnz     .divide_1

.end_divide:

    pop     rbp
    pop     rsi
    dec     si

.rounding:

    bt      rax,0
    adc     rax,0
    adc     rdx,0

.overflow:

    bt      rdx,64 - BITS ; overflow bit
    jnc     .reset
    rcr     rdx,1
    rcr     rax,1
    add     esi,1

.reset:

    shld    rdx,rax,BITS
    shl     rax,BITS

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rsi,16
    movq    xmm0,rax
    movq    xmm1,rdx
    movlhps xmm0,xmm1
    ret

.normalize_a:
    dec     cx
    add     rax,rax
    adc     rdx,rdx
    jnc     .normalize_a
    jmp     .if_denormal_b

.normalize_b:
    dec     si
    add     rbx,rbx
    adc     rdi,rdi
    jnc     .normalize_b
    jmp     .calculate_exponent

.zero_a:
    add     si,si
    jz      .za_0
    rcr     si,1
    jmp     .init_done
.za_0:
    rcr     si,1
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x8000
    jmp     .done

.zero_b:
    test    esi,0x7FFF0000
    jnz     .if_zero_a
    mov     rcx,rax
    or      rcx,rdx
    jnz     .infinity
    mov     ecx,esi
    add     cx,cx
    jnz     .infinity

.nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
    xor     eax,eax
    jmp     .done

.underflow:
    and     cx,0x7FFF
    cmp     cx,0x3FFF
    jae     .zero

.infinity:
    mov     esi,0x7FFF
.0:
    xor     eax,eax
    xor     edx,edx
    jmp     .done

.zero:
    xor     esi,esi
    jmp     .0

.b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     .done

.nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     .done
    mov     rcx,rax
    or      rcx,rdx
    jnz     .done
    xor     esi,0x8000
    jmp     .done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jz      .nan
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    mov     rcx,rbx
    or      rcx,rdi
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

divq endp
else
    int     3
endif
    end
