; _FLTADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    option win64:noauto

_lc_fltadd proc private uses rbx a:ptr STRFLT, b:ptr STRFLT, negate:uint_t

    mov     r11,rdi
    mov     rbx,[rsi].STRFLT.mantissa.l
    mov     rdi,[rsi].STRFLT.mantissa.h
    mov     si, [rsi].STRFLT.mantissa.e
    shl     esi,16
    mov     rax,[r11].STRFLT.mantissa.l
    mov     rdx,[r11].STRFLT.mantissa.h
    mov     si, [r11].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000
    xor     esi,r8d         ; flip sign if subtract
    mov     rcx,rax
    or      rcx,rdx
    jz      error_zero_a
if_zero_b:
    mov     rcx,rbx
    or      rcx,rdi
    jz      error_zero_b

calculate_exponent:

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
    jz      E2
    jnb     E1
    mov     r9d,esi         ; get larger exponent for result
    neg     cx              ; negate the shift count
    xchg    rax,rbx         ; flip operands
    xchg    rdx,rdi
E1:
    cmp     cx,128          ; if shift count too big
    jna     E2
    mov     esi,r9d
    shl     esi,1           ; get sign
    rcr     si,1            ; merge with exponent
    mov     rax,rbx
    mov     rdx,rdi
    jmp     done
E2:
    mov     esi,r9d         ; zero extend B
    mov     ch,0            ; get bit 0 of sign word - value is 0 if
    test    ecx,ecx         ; both operands have same sign, 1 if not
    jns     S1              ; if signs are different
    mov     ch,-1           ; - set high part to ones
    neg     rdi
    neg     rbx
    sbb     rdi,0
    xor     esi,0x80000000  ; - flip sign
S1:
    xor     r8d,r8d         ; get a zero for sticky bits
    test    cl,cl           ; if shifting required
    jz      M1
    cmp     cl,64           ; if shift count >= 64
    jb      S4
    test    rax,rax         ; check low order qword for 1 bits
    jz      S2
    inc     r8d             ; 1 if non zero
S2:
    cmp     cl,128          ; if shift count is 128
    jne     S3
    shr     rdx,32          ; get rest of sticky bits from high part
    or      r8d,edx
    xor     edx,edx         ; zero high part
S3:
    mov     rax,rdx         ; shift right 64
    xor     edx,edx
S4:
    xor     r9d,r9d
    mov     r10d,eax
    ;shr     r10d,15
    shrd    r9d,r10d,cl     ; get the extra sticky bits
    or      r8d,r9d         ; save them
    shrd    rax,rdx,cl      ; align the fractions
    shr     rdx,cl
M1:
    add     rax,rbx         ; add the fractions
    adc     rdx,rdi
    adc     ch,0
    jns     M3              ; if is negative
    cmp     cl,128
    jne     M2
    test    r8d,0x7FFFFFFF
    jz      M2
    add     rax,1           ; round up fraction if required
    adc     rdx,0
M2:
    neg     rdx             ; negate the fraction
    neg     rax
    sbb     rdx,0
    xor     ch,ch           ; zero top bits
    xor     esi,0x80000000  ; flip the sign
M3:
    mov     r9d,ecx         ; check for zero
    and     r9d,0xFF00
    or      r9,rax
    or      r9,rdx
    jnz     M4
    xor     esi,esi
M4:
    test    si,si
    jz      done

    test    ch,ch           ; if top bits are 0
    mov     ecx,r8d
    jnz     increment_exponent
    rol     ecx,1           ; set carry from last sticky bit
    rol     ecx,1
decrement_exponent:
    dec     si
    jz      denormal
    adc     rax,rax
    adc     rdx,rdx
    jnc     decrement_exponent
increment_exponent:
    inc     si
    cmp     si,Q_EXPMASK
    je      return_overflow
    stc
    rcr     rdx,1
    rcr     rax,1
    add     ecx,ecx
    jnc     denormal
    adc     rax,0
    adc     rdx,0
    jnc     denormal
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      return_overflow
denormal:
    add     esi,esi
    rcr     si,1

done:

    mov     [r11].STRFLT.mantissa.l,rax
    mov     [r11].STRFLT.mantissa.h,rdx
    mov     [r11].STRFLT.mantissa.e,si
    mov     rax,r11
    ret

error_zero_a:
    shl     si,1            ; place sign in carry
    jnz     error_zero_a_0
    shr     esi,16          ; return B
    mov     rax,rbx
    mov     rdx,rdi
    shl     esi,1
    mov     rcx,rax         ; if not zero
    or      rcx,rdx
    jz      done
    shr     esi,1           ; -> restore sign bit
    jmp     done

error_zero_a_0:
    rcr     si,1            ; put back the sign
    jmp     if_zero_b

error_zero_b:
    test    esi,0x7FFF0000
    jz      done
    jmp     calculate_exponent

return_nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
    xor     eax,eax
    jmp     done

return_overflow:

return_infinity:
    mov     esi,0x7FFF
return_0:
    xor     eax,eax
    xor     edx,edx
    jmp     done

return_underflow:

return_zero:
    xor     esi,esi
    jmp     return_0

return_b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     done

error_nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     done
    mov     rcx,rax
    or      rcx,rdx
    jnz     done
    xor     esi,0x8000
    jmp     done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jnz     @F
    or      esi,-1
    jmp     return_nan
@@:
    cmp     rdx,rdi
    jb      return_b
    ja      done
    cmp     rax,rbx
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    mov     rcx,rbx
    or      rcx,rdi
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_lc_fltadd endp

_fltadd proc a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(rdi, rsi, 0)
    ret

_fltadd endp

_fltsub proc a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(rdi, rsi, 0x80000000)
    ret

_fltsub endp

    end
