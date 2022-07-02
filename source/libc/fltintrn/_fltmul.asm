; _FLTMUL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    option dotname

_fltmul proc __ccall uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT

ifdef _WIN64
    mov     r10,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
else
   .new     multiplier[4]:dword
   .new     result    [8]:dword
    mov     edx,b
endif
    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16
ifdef _WIN64
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
else
    mov     ecx,a
    mov     eax,dword ptr [ecx].STRFLT.mantissa.l[0]
    mov     edx,dword ptr [ecx].STRFLT.mantissa.l[4]
    mov     ebx,dword ptr [ecx].STRFLT.mantissa.h[0]
    mov     edi,dword ptr [ecx].STRFLT.mantissa.h[4]
endif
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000

    mov     rcx,rax
    or      rcx,rdx
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
    jz      .zero_a

.if_zero_b:
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,b
    push    eax
    mov     eax,[ecx+0x0]
    or      eax,[ecx+0x4]
    or      eax,[ecx+0x8]
    or      eax,[ecx+0xC]
    pop     eax
endif
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

ifdef _WIN64
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
else
    mov     multiplier[0x0],eax
    mov     multiplier[0x4],edx
    mov     multiplier[0x8],ebx
    mov     multiplier[0xC],edi

    mov     ecx,b
    mul     dword ptr [ecx+0x0]
    mov     result[0x0],eax
    mov     result[0x4],edx
    mov     eax,multiplier[0x4]
    mul     dword ptr [ecx+0x4]
    mov     result[0x8],eax
    mov     result[0xC],edx
    mov     eax,ebx
    mul     dword ptr [ecx+0x08]
    mov     result[0x10],eax
    mov     result[0x14],edx
    mov     eax,edi
    mul     dword ptr [ecx+0x0C]
    mov     result[0x18],eax
    mov     result[0x1C],edx

    .for ( ebx = 0 : ebx < 12 : ebx++ )

        lea ecx,[ebx*2]

        ;  b a 9 8 7 6 5 4 3 2 1 0 - index

        ;  3 2 3 1 3 0 2 1 2 0 0 1 - A
        ;  2 3 1 3 0 3 1 2 0 2 1 0 - B

        mov eax,111011011100100110000001B
        mov edx,101101110011011000100100B
        shr eax,cl
        shr edx,cl
        and eax,3
        and edx,3

        mov eax,multiplier[eax*4]
        mov edi,b
        mul dword ptr [edi+edx*4]

        .if ( eax || edx )

            ;  b a 9 8 7 6 5 4 3 2 1 0 - index
            ;  5 5 4 4 3 3 3 3 2 2 1 1

            mov edi,010100001111111110100101B
            shr edi,cl
            and edi,3
            .if ebx > 7
                add edi,4
            .endif
            add result[edi*4],eax
            adc result[edi*4+4],edx
            sbb edx,edx

            .continue .ifz

            .for ( eax = 1, edi += 2: edx, edi < 8: edi++ )

                add result[edi*4],eax
                sbb edx,edx
            .endf
        .endif
    .endf

    mov     ecx,result[0x0C]
    mov     eax,result[0x10]    ; high256
    mov     edx,result[0x14]
    mov     ebx,result[0x18]
    mov     edi,result[0x1C]

    test    edi,edi             ; if not normalized
    js      .rounding
    add     ecx,ecx
    adc     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
endif

    dec     si

.rounding:

ifdef _WIN64
    add     rbx,rbx
    adc     rax,0
    adc     rdx,0
else
    add     ecx,ecx
    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0
endif

.validate:

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

ifdef _WIN64
    mov     [r10].STRFLT.mantissa.l,rax
    mov     [r10].STRFLT.mantissa.h,rdx
    mov     [r10].STRFLT.mantissa.e,si
    mov     rax,r10
else
    mov     ecx,a
    mov     dword ptr [ecx].STRFLT.mantissa.l[0],eax
    mov     dword ptr [ecx].STRFLT.mantissa.l[4],edx
    mov     dword ptr [ecx].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [ecx].STRFLT.mantissa.h[4],edi
    mov     [ecx].STRFLT.mantissa.e,si
    mov     eax,ecx
endif
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
ifdef _WIN64
    mov     edx,1
    rol     rdx,1
else
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
endif
    xor     eax,eax
    jmp     .done

.overflow:

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

_fltmul endp

    end
