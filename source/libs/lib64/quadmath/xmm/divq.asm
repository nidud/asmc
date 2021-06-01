; DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option dotname, win64:rsp noauto

divq proc vectorcall uses rsi rdi rbx A:real16, B:real16

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

    add     si,1            ; validate..
    jc      .error_nan_a
    jo      .error_nan_a
    add     esi,0xFFFF
    jc      .error_nan_b
    jo      .error_nan_b
    sub     esi,0x10000

    mov     rcx,rbx
    or      rcx,rdi
    jnz     .if_zero_a

    test    esi,0x7FFF0000
    jz      .error_zero_b

.if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
    jnz     .init_done
    add     si,si
    jz      .error_zero_a
    rcr     si,1

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
    rol     ecx,16
    rol     esi,16
    add     cx,si
    rol     ecx,16
    rol     esi,16

.if_is_a_denormal_a:
    test    cx,cx
    jnz     .if_is_a_denormal_b
.normalize_a:
    dec     cx
    add     rax,rax
    adc     rdx,rdx
    jnc     .normalize_a

.if_is_a_denormal_b:
    test    si,si
    jnz     .calculate_exponent
.normalize_b:
    dec     si
    add     rbx,rbx
    adc     rdi,rdi
    jnc     .normalize_a

.calculate_exponent:
    sub     cx,si
    add     cx,0x3FFF
    js      .if_exponent_is_too_small

    cmp     cx,0x7FFF       ; quit if exponent is negative
    jnb     .return_infinity

.if_exponent_is_too_small:
    cmp     cx,-65
    jl      .return_underflow

.divide:

    push    rbp
    push    rcx

    define  BITS 9
    shrd    rax,rdx,BITS
    shr     rdx,BITS
    shrd    rbx,rdi,BITS
    shr     rdi,BITS

    mov     rbp,rdi
    mov     r10,rax
    mov     r11,rdx
    xor     eax,eax
    xor     edx,edx

    xor     r8d,r8d
    xor     r9d,r9d
    xor     edi,edi
    xor     esi,esi
    mov     ecx,113 + (16-BITS)
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

    pop     rsi
    pop     rbp
    dec     si

    mov     ecx,eax
    and     ecx,0x3F
    cmp     ecx,27;19
    jb      .overflow

    add     rax,0x40
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
    mov     rcx,rax
    or      rcx,rdx
    jnz     .return_infinity
    mov     ecx,esi
    add     cx,cx
    jnz     .return_infinity

.return_nan:
    mov     esi,0xFFFF
    xor     edx,edx
    xor     eax,eax
    stc
    rcr     rdx,1
    jmp     .error

.return_underflow:
    and     cx,0x7FFF
    cmp     cx,0x3FFF
    jae     .return_zero

.return_infinity:
    mov     esi,0x7FFF
    xor     eax,eax
    xor     edx,edx
    jmp     .error

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

divq endp

    end
