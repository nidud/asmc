; MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ifdef _WIN64

    option dotname

mulq proc uses rsi rdi rbx dest:real16, src:real16

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

    mov     rcx,rax
    or      rcx,rdx
    jz      .zero_a

.if_zero_b:
    mov     rcx,rbx
    or      rcx,rdi
    jz      .zero_b

.calculate_exponent:

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    add     esi,ecx
    sub     si,0x3FFE
    jc      .too_small
    cmp     si,0x7FFF       ; quit if exponent is negative
    ja      .overflow
.too_small:
    cmp     si,-65
    jl      .underflow

    mov     rcx,rbx
    mov     r11,rdi
    mov     r8,rax
    mov     r9,rdi
    mov     rdi,rdx
    mul     rcx
    mov     rbx,rdx
    mov     rax,rdi
    mul     r11
    mov     r11,rdx
    xchg    rcx,rax
    mov     rdx,rdi
    mul     rdx
    add     rbx,rax
    adc     rcx,rdx
    adc     r11,0
    mov     rax,r8
    mov     rdx,r9
    mul     rdx
    add     rbx,rax
    adc     rcx,rdx
    adc     r11,0
    mov     rax,rcx
    mov     rdx,r11

    test    rdx,rdx
    js      .rounding

    add     rbx,rbx
    adc     rax,rax
    adc     rdx,rdx
    dec     si

.rounding:

    add     rbx,rbx
    adc     rax,0
    adc     rdx,0

.validate:

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

.zero_a:
    add     si,si
    jz      .is_zero_a
    rcr     si,1
    jmp     .if_zero_b
.is_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x8000
    jmp     .done

.zero_b:
    test    esi,0x7FFF0000
    jnz     .calculate_exponent
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x80000000
    jmp     .b

.nan:
    mov     esi,0xFFFF
    mov     edx,1
    rol     rdx,1
    xor     eax,eax
    jmp     .done

.overflow:

.infinity:
    mov     esi,0x7FFF
.0:
    xor     eax,eax
    xor     edx,edx
    jmp     .done

.underflow:

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
    test    rax,rax
    jnz     .done
    test    rdx,rdx
    jnz     .done
    xor     esi,0x8000
    jmp     .done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jnz     @F
    or      esi,-1
    jmp     .nan
@@:
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    test    rbx,rbx
    jnz     .b
    test    rdi,rdi
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

mulq endp
else
    int     3
endif
    end
