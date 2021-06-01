; MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option dotname, win64:rsp noauto

mulq proc vectorcall uses rsi rdi rbx A:real16, B:real16

    movq    rax,xmm0        ; unpack to rdx:rax and rdi:rbx
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movq    rbx,xmm1
    movhlps xmm0,xmm1
    movq    rdi,xmm0

    shld    rsi,rdi,16      ; put exponent int esi
    shld    rdi,rbx,16
    shl     rbx,16
    shld    rsi,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     r9d,esi

    add     si,1            ; validate..
    jc      .error_nan_a
    jo      .error_nan_a
    add     esi,0xFFFF
    jc      .error_nan_b
    jo      .error_nan_b
    sub     esi,0x10000

.if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
    jnz     .if_zero_b
    add     si,si
    jz      .error_zero_a   ; return +-0
    rcr     si,1

.if_zero_b:
    mov     rcx,rbx
    or      rcx,rdi
    jnz     .init_done
    test    esi,0x7FFF0000
    jz      .error_zero_b

.init_done:

    stc
    rcr     rdx,1
    rcr     rax,1
    stc
    rcr     rdi,1
    rcr     rbx,1

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    add     esi,ecx

.calculate_exponent:
    sub     si,0x3FFE
    jc      .if_exponent_too_small
    cmp     si,0x7FFF       ; quit if exponent is negative
    ja      .return_overflow
.if_exponent_too_small:
    cmp     si,-65
    jl      .return_underflow

    mov     r10,rbx
    mov     r11,rdi
    mov     r8,rax
    mov     r9,rdi
    mov     rdi,rdx
    mul     r10
    mov     rbx,rdx
    mov     rcx,rax
    mov     rax,rdi
    mul     r11
    mov     r11,rdx
    xchg    r10,rax
    mov     rdx,rdi
    mul     rdx
    add     rbx,rax
    adc     r10,rdx
    adc     r11,0
    mov     rax,r8
    mov     rdx,r9
    mul     rdx
    add     rbx,rax
    adc     r10,rdx
    adc     r11,0
    mov     rax,r10
    mov     rdx,r11

    test    rdx,rdx
    js      .test_overflow

    add     rbx,rbx
    adc     rax,rax
    adc     rdx,rdx
    dec     si

.test_overflow:

    add     rbx,rbx
    jnc     .rounding
    jnz     .overflow
    bt      rax,0

.overflow:

    adc     rax,0
    adc     rdx,0
    jnc     .rounding

    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,0x7FFF
    je      .return_infinity

.rounding:

    mov     ecx,eax
    and     ecx,0x7FFF
    cmp     ecx,0x2000;1900
    jb      .validate

    add     rax,0x8000
    adc     rdx,0
    jnc     .validate

    rcr     rdx,1
    rcr     rax,1
    inc     si

.validate:

    test    si,si
    jng     .return_zero
    add     esi,esi
    rcr     si,1

.done:

    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16

.error:

    shrd    rdx,rsi,16
    movq    xmm0,rax
    movq    xmm1,rdx
    movlhps xmm0,xmm1

.toend:

    ret

.error_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      .return_zero
    mov     esi,0x8000
    jmp     .error

.error_zero_b:
    test    esi,0x80008000
    jz      .return_zero
    mov     esi,0x80000000
    jmp     .return_b

.return_nan:
    mov     esi,0xFFFF
    mov     edx,1
    rol     rdx,1
    xor     eax,eax
    jmp     .error

.return_overflow:

.return_infinity:
    mov     esi,0x7FFF
    xor     eax,eax
    xor     edx,edx
    jmp     .error

.return_underflow:

.return_zero:
    xorps   xmm0,xmm0
    jmp     .toend

.return_b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     .done

.error_nan_a:
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
    jmp     .error
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jnz     @F
    or      esi,-1
    jmp     .return_nan
@@:
    cmp     rdx,rdi
    jb      .return_b
    ja      .done
    cmp     rax,rbx
    jna     .return_b
    jmp     .done

.error_nan_b:
    sub     esi,0x10000
    test    rbx,rbx
    jnz     .return_b
    test    rdi,rdi
    jnz     .return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .return_b

mulq endp

    end
