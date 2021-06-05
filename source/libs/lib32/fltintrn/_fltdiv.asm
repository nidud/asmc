; _FLTDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_fltdiv proc uses esi edi ebx a:ptr STRFLT, b:ptr STRFLT

  local dividend[4]:dword
  local divisor [4]:dword
  local reminder[4]:dword
  local quotient[4]:dword
  local bits:int_t

    mov     ecx,b
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    mov     ebx,[ecx+8]
    mov     edi,[ecx+12]
    mov     divisor[0],eax
    mov     divisor[4],edx
    mov     divisor[8],ebx
    mov     divisor[12],edi
    mov     si,[ecx+16]
    shl     esi,16

    mov     ecx,a
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    mov     ebx,[ecx+8]
    mov     edi,[ecx+12]
    mov     si,[ecx+16]

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000

    mov     ecx,divisor[0]
    or      ecx,divisor[4]
    or      ecx,divisor[8]
    or      ecx,divisor[12]
    jnz     if_zero_a

    test    esi,0x7FFF0000
    jz      error_zero_b

if_zero_a:
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     init_done
    add     si,si
    jz      error_zero_a
    rcr     si,1

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

if_denormal_a:
    test    cx,cx
    jnz     if_denormal_b
normalize_a:
    dec     cx
    add     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    jnc     normalize_a

if_denormal_b:
    test    si,si
    jnz     calculate_exponent
    push    eax
normalize_b:
    dec     si
    mov     eax,divisor[0]
    add     divisor[0],eax
    mov     eax,divisor[4]
    adc     divisor[4],eax
    mov     eax,divisor[8]
    adc     divisor[8],eax
    mov     eax,divisor[12]
    adc     divisor[12],eax
    jnc     normalize_b
    pop     eax

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

    push    ecx

    define  RBITS 14

    shrd    eax,edx,RBITS
    shrd    edx,ebx,RBITS
    shrd    ebx,edi,RBITS
    shr     edi,RBITS
    mov     reminder[0x0],eax
    mov     reminder[0x4],edx
    mov     reminder[0x8],ebx
    mov     reminder[0xC],edi
    mov     ecx,divisor[0x0]
    mov     edx,divisor[0x4]
    mov     ebx,divisor[0x8]
    mov     edi,divisor[0xC]
    shrd    ecx,edx,RBITS
    shrd    edx,ebx,RBITS
    shrd    ebx,edi,RBITS
    shr     edi,RBITS

    xor     eax,eax
    mov     quotient[0x0],eax
    mov     quotient[0x4],eax
    mov     quotient[0x8],eax
    mov     quotient[0xC],eax
    mov     divisor [0x0],eax
    mov     divisor [0x4],eax
    mov     divisor [0x8],eax
    mov     divisor [0xC],eax
    mov     dividend[0x0],eax
    mov     dividend[0x4],eax
    mov     dividend[0x8],eax
    mov     dividend[0xC],eax

    mov     bits,113 + (16 - RBITS)
    xor     esi,esi
    add     ecx,ecx
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi

divide_1:
    shr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     ecx,1
    rcr     esi,1
    rcr     divisor[0x8],1
    rcr     divisor[0x4],1
    rcr     divisor[0x0],1
    sub     dividend[0x0],divisor[0x0]
    sbb     dividend[0x4],divisor[0x4]
    sbb     dividend[0x8],divisor[0x8]
    sbb     dividend[0xC],esi
    sbb     reminder[0x0],ecx
    sbb     reminder[0x4],edx
    sbb     reminder[0x8],ebx
    sbb     reminder[0xC],edi
    cmc
    jc      divide_3

divide_2:
    add     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     quotient[0xC],quotient[0xC]
    dec     bits
    jz      end_divide
    shr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     ecx,1

    rcr     esi,1
    rcr     divisor[0x8],1
    rcr     divisor[0x4],1
    rcr     divisor[0x0],1
    add     dividend[0x0],divisor[0x0]
    adc     dividend[0x4],divisor[0x4]
    adc     dividend[0x8],divisor[0x8]
    adc     dividend[0xC],esi
    adc     reminder[0x0],ecx
    adc     reminder[0x4],edx
    adc     reminder[0x8],ebx
    adc     reminder[0xC],edi
    jnc     divide_2

divide_3:
    adc     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     quotient[0xC],quotient[0xC]
    dec     bits
    jnz     divide_1

end_divide:

    pop     esi
    mov     eax,quotient[0x0]
    mov     edx,quotient[0x4]
    mov     ebx,quotient[0x8]
    mov     edi,quotient[0xC]
    dec     si

rounding:

    bt      eax,0
    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0

overflow:

    bt      edi,32 - RBITS ; overflow bit
    jnc     reset
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
    add     esi,1

reset:

    shld    edi,ebx,RBITS
    shld    ebx,edx,RBITS
    shld    edx,eax,RBITS
    shl     eax,RBITS

    test    si,si
    jng     return_zero
    add     esi,esi
    rcr     si,1

done:

    mov     ecx,a
    mov     [ecx],eax
    mov     [ecx+4],edx
    mov     [ecx+8],ebx
    mov     [ecx+12],edi
    mov     [ecx+16],si
    mov     eax,ecx
    ret

error_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x8000
    jmp     done

error_zero_b:
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     return_infinity
    mov     ecx,esi
    add     cx,cx
    jnz     return_infinity

return_nan:
    mov     esi,0xFFFF
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
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
    xor     ebx,ebx
    xor     edi,edi
    jmp     done

return_zero:
    xor     esi,esi
    jmp     return_0

return_b:
    mov     eax,divisor[0]
    mov     edx,divisor[4]
    mov     ebx,divisor[8]
    mov     edi,divisor[12]
    shr     esi,16
    jmp     done

error_nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     done
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     done
    xor     esi,0x8000
    jmp     done
@@:
    sub     esi,0x10000
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    or      ecx,divisor[0]
    or      ecx,divisor[4]
    or      ecx,divisor[8]
    or      ecx,divisor[12]
    jz      return_nan
    cmp     edi,divisor[12]
    jb      return_b
    ja      done
    cmp     ebx,divisor[8]
    jb      return_b
    ja      done
    cmp     edx,divisor[4]
    jb      return_b
    ja      done
    cmp     eax,divisor[0]
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    mov     ecx,divisor[0]
    or      ecx,divisor[4]
    or      ecx,divisor[8]
    or      ecx,divisor[12]
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_fltdiv endp

    end
