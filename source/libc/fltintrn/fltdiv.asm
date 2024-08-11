; FLTDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    option dotname

ifdef _WIN64

    assume rdx:ptr STRFLT
    assume rcx:ptr STRFLT

_fltdiv proc __ccall uses rsi rdi rbx r12 r13 a:ptr STRFLT, b:ptr STRFLT

    mov     rbx,[rdx].mantissa.l
    mov     rdi,[rdx].mantissa.h
    mov     si, [rdx].mantissa.e
    shl     esi,16
    mov     rax,[rcx].mantissa.l
    mov     rdx,[rcx].mantissa.h
    mov     si, [rcx].mantissa.e

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
    mov     r13,rcx

    mov     r12,rbp
    shrd    rax,rdx,BITS
    shr     rdx,BITS
    shrd    rbx,rdi,BITS
    shr     rdi,BITS
    mov     ecx,113 + (16 - BITS)

    mov     rbp,rdi         ; rbp:rbx - ebp:ebx:edx:esi
    mov     r10,rax         ; r11:r10 - reminder
    mov     r11,rdx

    xor     eax,eax         ; rdx:rax - quotient
    xor     edx,edx
    xor     r8d,r8d         ; r9:r8   - divisor
    xor     r9d,r9d
    xor     edi,edi         ; rsi:rdi - dividend
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

    mov     rsi,r13
    mov     rbp,r12
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

    mov     rcx,a
    mov     [rcx].mantissa.l,rax
    mov     [rcx].mantissa.h,rdx
    mov     [rcx].mantissa.e,si
    mov     rax,rcx
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

else

    option stackbase:esp

_fltdiv proc __ccall uses esi edi ebx ebp a:ptr STRFLT, b:ptr STRFLT

    local   exp:dword
    local   dividend[4]:dword
    local   divisor [4]:dword
    local   reminder[4]:dword
    local   quotient[4]:dword

    mov     edx,b
    mov     divisor[0x0],[edx+0x0]
    mov     divisor[0x4],[edx+0x4]
    mov     divisor[0x8],[edx+0x8]
    mov     divisor[0xC],[edx+0xC]

    mov     si, [edx].STRFLT.mantissa.e
    shl     esi,16
    mov     ecx,a
    mov     eax,[ecx+0x0]
    mov     edx,[ecx+0x4]
    mov     ebx,[ecx+0x8]
    mov     edi,[ecx+0xC]
    mov     si, [ecx].STRFLT.mantissa.e
    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000
    mov     ecx,divisor[0x0]
    or      ecx,divisor[0x4]
    or      ecx,divisor[0x8]
    or      ecx,divisor[0xC]
    jz      .zero_b

.if_zero_a:
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
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
    mov     exp,ecx

    shrd    eax,edx,BITS
    shrd    edx,ebx,BITS
    shrd    ebx,edi,BITS
    shr     edi,BITS
    mov     reminder[0x0],eax
    mov     reminder[0x4],edx
    mov     reminder[0x8],ebx
    mov     reminder[0xC],edi

    mov     esi,divisor[0x0]
    mov     edx,divisor[0x4]
    mov     ebx,divisor[0x8]
    mov     ebp,divisor[0xC]
    shrd    esi,edx,BITS
    shrd    edx,ebx,BITS
    shrd    ebx,ebp,BITS
    shr     ebp,BITS
    mov     ecx,113 + (16 - BITS)

    xor     eax,eax
    xor     edi,edi
    mov     quotient[0x0],eax
    mov     quotient[0x4],eax
    mov     quotient[0x8],eax
    mov     divisor [0x0],eax
    mov     divisor [0x4],eax
    mov     divisor [0x8],eax
    mov     divisor [0xC],eax
    mov     dividend[0x0],eax
    mov     dividend[0x4],eax
    mov     dividend[0x8],eax
    mov     dividend[0xC],eax

    add     esi,esi
    adc     edx,edx
    adc     ebx,ebx
    adc     ebp,ebp

.divide_1:
    shr     ebp,1
    rcr     ebx,1
    rcr     edx,1
    rcr     esi,1
    rcr     divisor[0xC],1
    rcr     divisor[0x8],1
    rcr     divisor[0x4],1
    rcr     divisor[0x0],1
    sub     dividend[0x0],divisor[0x0]
    sbb     dividend[0x4],divisor[0x4]
    sbb     dividend[0x8],divisor[0x8]
    sbb     dividend[0xC],divisor[0xC]
    sbb     reminder[0x0],esi
    sbb     reminder[0x4],edx
    sbb     reminder[0x8],ebx
    sbb     reminder[0xC],ebp
    cmc
    jc      .divide_3

.divide_2:

    add     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     edi,edi
    dec     ecx
    jz      .end_divide
    shr     ebp,1
    rcr     ebx,1
    rcr     edx,1
    rcr     esi,1
    rcr     divisor[0xC],1
    rcr     divisor[0x8],1
    rcr     divisor[0x4],1
    rcr     divisor[0x0],1
    add     dividend[0x0],divisor[0x0]
    adc     dividend[0x4],divisor[0x4]
    adc     dividend[0x8],divisor[0x8]
    adc     dividend[0xC],divisor[0xC]
    adc     reminder[0x0],esi
    adc     reminder[0x4],edx
    adc     reminder[0x8],ebx
    adc     reminder[0xC],ebp
    jnc     .divide_2

.divide_3:

    adc     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     edi,edi
    dec     ecx
    jnz     .divide_1

.end_divide:

    mov     esi,exp
    mov     eax,quotient[0x0]
    mov     edx,quotient[0x4]
    mov     ebx,quotient[0x8]
    dec     si

.rounding:

    bt      eax,0
    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0

.overflow:

    bt      edi,32 - BITS
    jnc     .reset
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
    add     esi,1

.reset:
    shld    edi,ebx,BITS
    shld    ebx,edx,BITS
    shld    edx,eax,BITS
    shl     eax,BITS

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

    mov     ecx,a
    mov     dword ptr [ecx].STRFLT.mantissa.l[0],eax
    mov     dword ptr [ecx].STRFLT.mantissa.l[4],edx
    mov     dword ptr [ecx].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [ecx].STRFLT.mantissa.h[4],edi
    mov     [ecx].STRFLT.mantissa.e,si
    mov     eax,ecx
    ret

.normalize_a:
    dec     cx
    add     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    jnc     .normalize_a
    jmp     .if_denormal_b

.normalize_b:

    push    eax
.nb:
    dec     si
    add     divisor[0x0],divisor[0x0]
    adc     divisor[0x4],divisor[0x4]
    adc     divisor[0x8],divisor[0x8]
    adc     divisor[0xC],divisor[0xC]
    jnc     .nb
    pop     eax
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
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     .infinity
    mov     ecx,esi
    add     cx,cx
    jnz     .infinity

.nan:
    mov     esi,0xFFFF
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
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
    xor     ebx,ebx
    xor     edi,edi
    jmp     .done

.zero:
    xor     esi,esi
    jmp     .0

.b:
    mov     eax,divisor[0x0]
    mov     edx,divisor[0x4]
    mov     ebx,divisor[0x8]
    mov     edi,divisor[0xC]
    shr     esi,16
    jmp     .done

.nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     .done
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     .done
    xor     esi,0x8000
    jmp     .done
@@:
    sub     esi,0x10000
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    or      ecx,divisor[0x0]
    or      ecx,divisor[0x4]
    or      ecx,divisor[0x8]
    or      ecx,divisor[0xC]
    jz      .nan
    cmp     edi,divisor[0xC]
    jb      .b
    ja      .done
    cmp     ebx,divisor[0x8]
    jb      .b
    ja      .done
    cmp     edx,divisor[0x4]
    jb      .b
    ja      .done
    cmp     eax,divisor[0x0]
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    mov     ecx,divisor[0]
    or      ecx,divisor[4]
    or      ecx,divisor[8]
    or      ecx,divisor[12]
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b
endif

_fltdiv endp

    end
