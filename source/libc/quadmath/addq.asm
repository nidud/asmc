; ADDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

ifdef _WIN64

    option dotname

_lc_add proc private uses rsi a:real16, b:real16, negate:uint_t

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movq    r10,xmm1
    movhlps xmm1,xmm1
    movq    r11,xmm1

    shld    rsi,r11,16
    shld    r11,r10,16
    shl     r10,16
    mov     r9d,esi
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     r11,1
    rcr     r10,1
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
    xor     esi,r8d         ; flip sign if subtract
    mov     rcx,rax
    or      rcx,rdx
    jz      .zero_a
.if_zero_b:
    mov     rcx,r10
    or      rcx,r11
    jz      .zero_b

.calculate_exponent:

    mov     ecx,esi
    rol     esi,16
    sar     esi,16
    sar     ecx,16
    and     esi,0x80007FFF
    and     ecx,0x80007FFF
    mov     r9d,ecx
    rol     esi,16
    rol     ecx,16
    add     cx,si
    rol     esi,16
    rol     ecx,16
    sub     cx,si
    jz      .e2
    jnb     .e1
    mov     r9d,esi         ; get larger exponent for result
    neg     cx              ; negate the shift count
    xchg    rax,r10         ; flip operands
    xchg    rdx,r11
.e1:
    cmp     cx,128          ; if shift count too big
    jna     .e2
    mov     esi,r9d
    shl     esi,1           ; get sign
    rcr     si,1            ; merge with exponent
    mov     rax,r10
    mov     rdx,r11
    jmp     .done
.e2:
    mov     esi,r9d         ; zero extend B
    mov     ch,0            ; get bit 0 of sign word - value is 0 if
    test    ecx,ecx         ; both operands have same sign, 1 if not
    jns     .s1             ; if signs are different
    mov     ch,-1           ; - set high part to ones
    neg     r11
    neg     r10
    sbb     r11,0
    xor     esi,0x80000000  ; - flip sign
.s1:
    xor     r8d,r8d         ; get a zero for sticky bits
    test    cl,cl           ; if shifting required
    jz      .m1
    cmp     cl,64           ; if shift count >= 64
    jb      .s4
    test    rax,rax         ; check low order qword for 1 bits
    jz      .s2
    inc     r8d             ; 1 if non zero
.s2:
    cmp     cl,128          ; if shift count is 128
    jne     .s3
    shr     rdx,32          ; get rest of sticky bits from high part
    or      r8d,edx
    xor     edx,edx         ; zero high part
.s3:
    mov     rax,rdx         ; shift right 64
    xor     edx,edx
.s4:
    xor     r9d,r9d
    shrd    r9d,eax,cl     ; get the extra sticky bits
    or      r8d,r9d         ; save them
    shrd    rax,rdx,cl      ; align the fractions
    shr     rdx,cl
.m1:
    add     rax,r10         ; add the fractions
    adc     rdx,r11
    adc     ch,0
    jns     .m3              ; if is negative
    cmp     cl,128
    jne     .m2
    test    r8d,0x7FFFFFFF
    jz      .m2
    add     rax,1           ; round up fraction if required
    adc     rdx,0
.m2:
    neg     rdx             ; negate the fraction
    neg     rax
    sbb     rdx,0
    xor     ch,ch           ; zero top bits
    xor     esi,0x80000000  ; flip the sign
.m3:
    mov     r9d,ecx         ; check for zero
    and     r9d,0xFF00
    or      r9,rax
    or      r9,rdx
    jnz     .m4
    xor     esi,esi
.m4:
    test    si,si
    jz      .done

    test    ch,ch           ; if top bits are 0
    mov     ecx,r8d
    jnz     .increment
    rol     ecx,1           ; set carry from last sticky bit
    rol     ecx,1
.decrement:
    dec     si
    jz      .denormal
    adc     rax,rax
    adc     rdx,rdx
    jnc     .decrement
.increment:
    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow
    stc
    rcr     rdx,1
    rcr     rax,1
    add     ecx,ecx
    jnc     .denormal
    adc     rax,0
    adc     rdx,0
    jnc     .denormal
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow
.denormal:
    add     esi,esi
    rcr     si,1
if 1
    test    eax,0x4000
    jz      .done
    add     rax,0x4000
    adc     rdx,0
    jnc     .done
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow
endif
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
    shl     si,1            ; place sign in carry
    jnz     .zero_a_0
    shr     esi,16          ; return B
    mov     rax,r10
    mov     rdx,r11
    shl     esi,1
    mov     rcx,rax         ; if not zero
    or      rcx,rdx
    jz      .done
    shr     esi,1           ; -> restore sign bit
    jmp     .done

.zero_a_0:
    rcr     si,1            ; put back the sign
    jmp     .if_zero_b

.zero_b:
    test    esi,0x7FFF0000
    jz      .done
    jmp     .calculate_exponent

.nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
    xor     eax,eax
    jmp     .done

.overflow:
.infinity:
    mov     esi,0x7FFF
.null:
    xor     eax,eax
    xor     edx,edx
    jmp     .done

.underflow:

.zero:
    xor     esi,esi
    jmp     .null

.b:
    mov     rax,r10
    mov     rdx,r11
    shr     esi,16
    jmp     .done

.nan_a:
    dec     si
    add     esi,0x10000
    jb      .0
    jo      .0
    jns     .done
    mov     rcx,rax
    or      rcx,rdx
    jnz     .done
    xor     esi,0x8000
    jmp     .done
.0:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,r10
    or      rcx,r11
    jnz     .1
    or      esi,-1
    jmp     .nan
.1:
    cmp     rdx,r11
    jb      .b
    ja      .done
    cmp     rax,r10
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    mov     rcx,r10
    or      rcx,r11
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_lc_add endp

addq proc dest:real16, src:real16

    _lc_add( xmm0, xmm1, 0 )
    ret

addq endp

subq proc dest:real16, src:real16

    _lc_add( xmm0, xmm1, 0x80000000 )
    ret

subq endp
else
    int     3
endif
    end
