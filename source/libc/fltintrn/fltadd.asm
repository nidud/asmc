; FLTADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    option dotname

_lc_fltadd proc __ccall private uses rsi rdi rbx A:ptr STRFLT, B:ptr STRFLT, negate:uint_t

ifdef _WIN64
    mov     r11,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
else
   .new     r9d:dword
   .new     r8d:dword
   .new     b[4]:dword
    mov     edx,B
    mov     b[0x0],[edx+0x0]
    mov     b[0x4],[edx+0x4]
    mov     b[0x8],[edx+0x8]
    mov     b[0xC],[edx+0xC]
endif
    mov     si,[rdx].STRFLT.mantissa.e
    shl     esi,16

ifdef _WIN64
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
else
    mov     ecx,A
    mov     eax,[ecx+0x0]
    mov     edx,[ecx+0x4]
    mov     ebx,[ecx+0x8]
    mov     edi,[ecx+0xC]
endif

    mov     si,[rcx].STRFLT.mantissa.e
    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000
ifdef _WIN64
    xor     esi,r8d         ; flip sign if subtract
    mov     rcx,rax
    or      rcx,rdx
else
    xor     esi,negate
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
endif
    jz      .zero_a

if_zero_b:
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
endif
    jz      .zero_b

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
    jz      .e2
    jnb     .e1
    mov     r9d,esi         ; get larger exponent for result
    neg     cx              ; negate the shift count
ifdef _WIN64
    xchg    rax,rbx         ; flip operands
    xchg    rdx,rdi
else
    push    ecx
    mov     ecx,b[0x0]
    mov     b[0x0],eax
    mov     eax,ecx
    mov     ecx,b[0x4]
    mov     b[0x4],edx
    mov     edx,ecx
    mov     ecx,b[0x8]
    mov     b[0x8],ebx
    mov     ebx,ecx
    mov     ecx,b[0xC]
    mov     b[0xC],edi
    mov     edi,ecx
    pop     ecx
endif
.e1:
    cmp     cx,128          ; if shift count too big
    jna     .e2
    mov     esi,r9d
    shl     esi,1           ; get sign
    rcr     si,1            ; merge with exponent
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
endif
    jmp     .done
.e2:
    mov     esi,r9d         ; zero extend B
    mov     ch,0            ; get bit 0 of sign word - value is 0 if
    test    ecx,ecx         ; both operands have same sign, 1 if not
    jns     .s0             ; if signs are different
    mov     ch,-1           ; - set high part to ones
ifdef _WIN64
    neg     rdi
    neg     rbx
    sbb     rdi,0
else
    neg     b[0xC]
    neg     b[0x8]
    sbb     b[0xC],0
    neg     b[0x4]
    sbb     b[0x8],0
    neg     b[0x0]
    sbb     b[0x4],0
endif
    xor     esi,0x80000000  ; - flip sign
.s0:
    mov     r8d,0           ; get a zero for sticky bits
    test    cl,cl           ; if shifting required
    jz      .m1
    cmp     cl,64           ; if shift count >= 64
    jb      .s4
    test    rax,rax         ; check low order qword for 1 bits
ifndef _WIN64
    jnz     .s1
    test    edx,edx
endif
    jz      .s2
.s1:
    inc     r8d             ; 1 if non zero
.s2:
    cmp     cl,128          ; if shift count is 128
    jne     .s3
ifdef _WIN64
    shr     rdx,32          ; get rest of sticky bits from high part
    or      r8d,edx
    xor     edx,edx         ; zero high part
else
    or      r8d,edi
    xor     ebx,ebx
    xor     edi,edi
endif
.s3:
ifdef _WIN64
    mov     rax,rdx         ; shift right 64
    xor     edx,edx
else
    mov     eax,ebx
    mov     edx,edi
    xor     ebx,ebx
    xor     edi,edi
    jmp     .s7             ; ??
endif
.s4:
ifdef _WIN64
    xor     r9d,r9d
    mov     r10d,eax
    shrd    r9d,r10d,cl     ; get the extra sticky bits
    or      r8d,r9d         ; save them
else
    cmp     cl,32
    jb      .s6
    test    eax,eax         ; check low order qword for 1 bits
    jnz     .s5
    inc     r8d             ; edi=1 if EDX:EAX non zero
.s5:
    mov     eax,edx
    mov     edx,ebx
    mov     ebx,edi
    xor     edi,edi
    jmp     .s7
.s6:
    push    eax             ; get the extra sticky bits
    push    ebx
    xor     ebx,ebx
    shr     eax,15
    shrd    ebx,eax,cl
    or      r8d,ebx         ; save them
    pop     ebx
    pop     eax
endif

.s7:
ifdef _WIN64
    shrd    rax,rdx,cl      ; align the fractions
    shr     rdx,cl
else
    shrd    eax,edx,cl
    shrd    edx,ebx,cl
    shrd    ebx,edi,cl
    shr     edi,cl
endif

.m1:
ifdef _WIN64
    add     rax,rbx         ; add the fractions
    adc     rdx,rdi
else
    add     eax,b[0x0]
    adc     edx,b[0x4]
    adc     ebx,b[0x8]
    adc     edi,b[0xC]
endif
    adc     ch,0
    jns     .m3             ; if is negative
    cmp     cl,128
    jne     .m2
    test    r8d,0x7FFFFFFF
    jz      .m2
ifdef _WIN64
    add     rax,1           ; round up fraction if required
    adc     rdx,0
else
    adc     eax,1           ; ??
    adc     edx,0
    adc     ebx,0
    adc     edi,0
endif
.m2:
ifdef _WIN64
    neg     rdx             ; negate the fraction
    neg     rax
    sbb     rdx,0
else
    neg     edi
    neg     ebx
    sbb     edi,0
    neg     edx
    sbb     ebx,0
    neg     eax
    sbb     edx,0
endif
    xor     ch,ch           ; zero top bits
    xor     esi,0x80000000  ; flip the sign
.m3:
ifdef _WIN64
    mov     r9d,ecx         ; check for zero
    and     r9d,0xFF00
    or      r9,rax
    or      r9,rdx
else
    push    ecx
    movzx   ecx,ch
    or      ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    pop     ecx
endif
    jnz     .m4
    xor     esi,esi
.m4:
    test    si,si
    jz      .done

    test    ch,ch           ; if top bits are 0
    mov     ecx,r8d
    jnz     .validate
    rol     ecx,1           ; set carry from last sticky bit
    rol     ecx,1

.dec_exponent:
    dec     si              ; preserve the state of the CF flag..
    jz      .denormal
    adc     rax,rax
    adc     rdx,rdx
ifndef _WIN64
    adc     ebx,ebx
    adc     edi,edi
endif
    jnc     .dec_exponent

.validate:

    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow
    stc
ifndef _WIN64
    rcr     edi,1
    rcr     ebx,1
endif
    rcr     rdx,1
    rcr     rax,1
    add     ecx,ecx
    jnc     .denormal
    adc     rax,0
    adc     rdx,0
ifndef _WIN64
    adc     ebx,0
    adc     edi,0
endif
    jnc     .denormal
ifndef _WIN64
    rcr     edi,1
    rcr     ebx,1
endif
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow

.denormal:
    add     esi,esi
    rcr     si,1

.done:
ifdef _WIN64
    mov     [r11].STRFLT.mantissa.l,rax
    mov     [r11].STRFLT.mantissa.h,rdx
    mov     [r11].STRFLT.mantissa.e,si
    mov     rax,r11
else
    mov     ecx,A
    mov     [ecx+0x0],eax
    mov     [ecx+0x4],edx
    mov     [ecx+0x8],ebx
    mov     [ecx+0xC],edi
    mov     [ecx+16],si
    mov     eax,ecx
endif
    ret

.zero_a:
    shl     si,1            ; place sign in carry
    jnz     .zero_a_0
    shr     esi,16          ; return B
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
endif
    shl     esi,1
ifdef _WIN64
    mov     rcx,rax         ; if not zero
    or      rcx,rdx
else
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
endif
    jz      .done
    shr     esi,1           ; -> restore sign bit
    jmp     .done
.zero_a_0:
    rcr     si,1            ; put back the sign
    jmp     if_zero_b

.zero_b:
    test    esi,0x7FFF0000
    jz      .done
    jmp     calculate_exponent

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

.overflow:
.infinity:
    mov     esi,0x7FFF
    xor     eax,eax
    xor     edx,edx
ifndef _WIN64
    xor     ebx,ebx
    xor     edi,edi
endif
    jmp     .done

.b:
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
endif
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
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
    jnz     .done
    xor     esi,0x8000
    jmp     .done
.0:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
ifndef _WIN64
    or      ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
endif
    jnz     .1
    or      esi,-1
    jmp     .nan
.1:
ifdef _WIN64
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
else
    cmp     edi,b[0xC]
    jb      .b
    ja      .done
    cmp     ebx,b[0x8]
    jb      .b
    ja      .done
    cmp     edx,b[0x4]
    jb      .b
    ja      .done
    cmp     eax,b[0x0]
endif
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
endif
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_lc_fltadd endp


_fltadd proc __ccall a:ptr STRFLT, b:ptr STRFLT
ifdef _WIN64
    _lc_fltadd( rcx, rdx, 0 )
else
    _lc_fltadd( a, b, 0 )
endif
    ret
_fltadd endp


_fltsub proc __ccall a:ptr STRFLT, b:ptr STRFLT
ifdef _WIN64
    _lc_fltadd( rcx, rdx, 0x80000000 )
else
    _lc_fltadd( a, b, 0x80000000 )
endif
    ret
_fltsub endp

    end
