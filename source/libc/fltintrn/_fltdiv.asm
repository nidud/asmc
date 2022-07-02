; _FLTDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    option dotname
    option stackbase:rsp

ifdef _WIN64
_fltdiv proc __ccall uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT
    local   exp:dword
    local   _bp:qword
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
else
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
endif

    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16

ifdef _WIN64
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
else
    mov     ecx,a
    mov     eax,[ecx+0x0]
    mov     edx,[ecx+0x4]
    mov     ebx,[ecx+0x8]
    mov     edi,[ecx+0xC]
endif
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000

ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,divisor[0x0]
    or      ecx,divisor[0x4]
    or      ecx,divisor[0x8]
    or      ecx,divisor[0xC]
endif
    jz      .zero_b

.if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
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

ifdef _WIN64
    mov     _bp,rbp
    shrd    rax,rdx,BITS
    shr     rdx,BITS
    shrd    rbx,rdi,BITS
    shr     rdi,BITS
else
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
endif

    mov     ecx,113 + (16 - BITS)

ifdef _WIN64

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
else

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
endif
    adc     rbp,rbp


.divide_1:
    shr     rbp,1
    rcr     rbx,1
ifdef _WIN64
    rcr     r9,1
    rcr     r8,1
    sub     rdi,r8
    sbb     rsi,r9
    sbb     r10,rbx
    sbb     r11,rbp
else
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
endif
    cmc
    jc      .divide_3

.divide_2:
ifdef _WIN64
    add     rax,rax
    adc     rdx,rdx
else
    add     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     edi,edi
endif
    dec     ecx
    jz      .end_divide
    shr     rbp,1
    rcr     rbx,1
ifdef _WIN64
    rcr     r9,1
    rcr     r8,1
    add     rdi,r8
    adc     rsi,r9
    adc     r10,rbx
    adc     r11,rbp
else
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
endif
    jnc     .divide_2

.divide_3:
ifdef _WIN64
    adc     rax,rax
    adc     rdx,rdx
else
    adc     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     edi,edi
endif
    dec     ecx
    jnz     .divide_1

.end_divide:

    mov     esi,exp
ifdef _WIN64
    mov     rbp,_bp
else
    mov     eax,quotient[0x0]
    mov     edx,quotient[0x4]
    mov     ebx,quotient[0x8]
endif
    dec     si

.rounding:

    bt      rax,0
    adc     rax,0
    adc     rdx,0
ifndef _WIN64
    adc     ebx,0
    adc     edi,0
endif

.overflow:

ifdef _WIN64
    bt      rdx,64 - BITS ; overflow bit
else
    bt      edi,32 - BITS
endif
    jnc     .reset
ifndef _WIN64
    rcr     edi,1
    rcr     ebx,1
endif
    rcr     rdx,1
    rcr     rax,1
    add     esi,1

.reset:

ifndef _WIN64
    shld    edi,ebx,BITS
    shld    ebx,edx,BITS
endif
    shld    rdx,rax,BITS
    shl     rax,BITS

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

    mov     rcx,a
ifdef _WIN64
    mov     [rcx].STRFLT.mantissa.l,rax
    mov     [rcx].STRFLT.mantissa.h,rdx
else
    mov     dword ptr [ecx].STRFLT.mantissa.l[0],eax
    mov     dword ptr [ecx].STRFLT.mantissa.l[4],edx
    mov     dword ptr [ecx].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [ecx].STRFLT.mantissa.h[4],edi
endif
    mov     [rcx].STRFLT.mantissa.e,si
    mov     rax,rcx
    ret

.normalize_a:
    dec     cx
    add     rax,rax
    adc     rdx,rdx
ifndef _WIN64
    adc     ebx,ebx
    adc     edi,edi
endif
    jnc     .normalize_a
    jmp     .if_denormal_b

.normalize_b:
ifdef _WIN64
    dec     si
    add     rbx,rbx
    adc     rdi,rdi
    jnc     .normalize_b
else
    push    eax
.nb:
    dec     si
    add     divisor[0x0],divisor[0x0]
    adc     divisor[0x4],divisor[0x4]
    adc     divisor[0x8],divisor[0x8]
    adc     divisor[0xC],divisor[0xC]
    jnc     .nb
    pop     eax
endif
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
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
    jnz     .infinity
    mov     ecx,esi
    add     cx,cx
    jnz     .infinity

.nan:
    mov     esi,0xFFFF
ifdef _WIN64
    mov     rdx,0x4000000000000000
else
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
endif
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
ifndef _WIN64
    xor     ebx,ebx
    xor     edi,edi
endif
    jmp     .done

.zero:
    xor     esi,esi
    jmp     .0

.b:
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,divisor[0x0]
    mov     edx,divisor[0x4]
    mov     ebx,divisor[0x8]
    mov     edi,divisor[0xC]
endif
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
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
    jnz     .done
    xor     esi,0x8000
    jmp     .done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
ifndef _WIN64
    or      ecx,divisor[0x0]
    or      ecx,divisor[0x4]
    or      ecx,divisor[0x8]
    or      ecx,divisor[0xC]
endif
    jz      .nan
ifdef _WIN64
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
else
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
endif
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,divisor[0]
    or      ecx,divisor[4]
    or      ecx,divisor[8]
    or      ecx,divisor[12]
endif
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_fltdiv endp

    end
