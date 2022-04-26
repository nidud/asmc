; _FLTDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltdiv proc uses rbx r12 a:ptr STRFLT, b:ptr STRFLT

    mov     r12,rdi
    mov     rbx,[rsi].STRFLT.mantissa.l
    mov     rdi,[rsi].STRFLT.mantissa.h
    mov     si, [rsi].STRFLT.mantissa.e
    shl     esi,16
    mov     rax,[r12].STRFLT.mantissa.l
    mov     rdx,[r12].STRFLT.mantissa.h
    mov     si, [r12].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000

    mov     rcx,rbx
    or      rcx,rdi
    jz      error_zero_b
if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
    jz      error_zero_a

init_done:

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
    jz      normalize_a
if_denormal_b:
    test    si,si
    jz      normalize_b

calculate_exponent:
    sub     cx,si
    add     cx,0x3FFF
    js      if_too_small
    cmp     cx,0x7FFF
    ja      return_infinity
if_too_small:
    cmp     cx,-65
    jl      return_underflow

divide:

    push    rbp
    push    rcx

    define  BITS 14

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

divide_1:
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    sub     rdi,r8
    sbb     rsi,r9
    sbb     r10,rbx
    sbb     r11,rbp
    cmc
    jc      divide_3

divide_2:
    add     rax,rax
    adc     rdx,rdx
    dec     ecx
    jz      end_divide
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    add     rdi,r8
    adc     rsi,r9
    adc     r10,rbx
    adc     r11,rbp
    jnc     divide_2

divide_3:
    adc     rax,rax
    adc     rdx,rdx
    dec     ecx
    jnz     divide_1

end_divide:

    pop     rsi
    pop     rbp
    dec     si

rounding:

    bt      rax,0
    adc     rax,0
    adc     rdx,0

overflow:

    bt      rdx,64 - BITS ; overflow bit
    jnc     reset

    rcr     rdx,1
    rcr     rax,1
    add     esi,1

reset:

    shld    rdx,rax,BITS
    shl     rax,BITS

    test    si,si
    jng     return_zero
    add     esi,esi
    rcr     si,1

done:

    mov     [r12].STRFLT.mantissa.l,rax
    mov     [r12].STRFLT.mantissa.h,rdx
    mov     [r12].STRFLT.mantissa.e,si
    mov     rax,r12
    ret

normalize_a:
    dec     cx
    add     rax,rax
    adc     rdx,rdx
    jnc     normalize_a
    jmp     if_denormal_b

normalize_b:
    dec     si
    add     rbx,rbx
    adc     rdi,rdi
    jnc     normalize_b
    jmp     calculate_exponent

error_zero_a:
    add     si,si
    jz      @F
    rcr     si,1
    jmp     init_done
@@:
    rcr     si,1
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x8000
    jmp     done

error_zero_b:
    test    esi,0x7FFF0000
    jnz     if_zero_a
    mov     rcx,rax
    or      rcx,rdx
    jnz     return_infinity
    mov     ecx,esi
    add     cx,cx
    jnz     return_infinity

return_nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
    xor     eax,eax
    jmp     done

return_underflow:
    and     cx,0x7FFF
    cmp     cx,0x3FFF
    jae     return_zero

return_infinity:
    mov     esi,0x7FFF
return_0:
    xor     eax,eax
    xor     edx,edx
    jmp     done

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
    jz      return_nan
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

_fltdiv endp

    end
