; _FLTMUL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    option win64:rsp noauto

_fltmul proc uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT

    mov     r10,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    jz      error_zero_a
if_zero_b:
    mov     rcx,rbx
    or      rcx,rdi
    jz      error_zero_b

calculate_exponent:

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    add     esi,ecx
    sub     si,0x3FFE
    jc      if_too_small
    cmp     si,0x7FFF       ; quit if exponent is negative
    ja      return_overflow
if_too_small:
    cmp     si,-65
    jl      return_underflow

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
    js      rounding

    add     rbx,rbx
    adc     rax,rax
    adc     rdx,rdx
    dec     si

rounding:

    add     rbx,rbx
    adc     rax,0
    adc     rdx,0

validate:

    test    si,si
    jng     return_zero
    add     esi,esi
    rcr     si,1

done:

    mov     [r10].STRFLT.mantissa.l,rax
    mov     [r10].STRFLT.mantissa.h,rdx
    mov     [r10].STRFLT.mantissa.e,si
    mov     rax,r10
    ret

error_zero_a:
    add     si,si
    jz      is_zero_a
    rcr     si,1
    jmp     if_zero_b
is_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x8000
    jmp     done

error_zero_b:
    test    esi,0x7FFF0000
    jnz     calculate_exponent
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x80000000
    jmp     return_b

return_nan:
    mov     esi,0xFFFF
    mov     edx,1
    rol     rdx,1
    xor     eax,eax
    jmp     done

return_overflow:

return_infinity:
    mov     esi,0x7FFF
    xor     eax,eax
    xor     edx,edx
    jmp     done

return_underflow:

return_zero:
    xor     esi,esi
    xor     eax,eax
    xor     edx,edx
    jmp     done

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
    test    rax,rax
    jnz     done
    test    rdx,rdx
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
    test    rbx,rbx
    jnz     return_b
    test    rdi,rdi
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_fltmul endp

    end
