; _FLTADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_lc_fltadd proc private uses esi edi ebx A:ptr STRFLT, B:ptr STRFLT, negate:uint_t

  local x:dword
  local r:dword
  local b[4]:dword

    mov     ecx,B
    mov     b[0x0],[ecx+0x0]
    mov     b[0x4],[ecx+0x4]
    mov     b[0x8],[ecx+0x8]
    mov     b[0xC],[ecx+0xC]
    mov     si,[ecx].STRFLT.mantissa.e
    shl     esi,16
    mov     ecx,A
    mov     eax,[ecx+0x0]
    mov     edx,[ecx+0x4]
    mov     ebx,[ecx+0x8]
    mov     edi,[ecx+0xC]
    mov     si,[ecx].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000
    xor     esi,negate ; flip sign if subtract

    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jz      error_zero_a

if_zero_b:
    mov     ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
    jnz     init_done
    test    esi,0x7FFF0000
    jz      done

init_done:

    mov     ecx,esi
    rol     esi,16
    sar     esi,16
    sar     ecx,16
    and     esi,0x80007FFF
    and     ecx,0x80007FFF
    mov     x,ecx
    rol     esi,16
    rol     ecx,16
    add     cx,si
    rol     esi,16
    rol     ecx,16
    sub     cx,si
    jz      is_equal
    jnb     b_not_below

    mov     x,esi      ; get larger exponent for result
    neg     cx         ; negate the shift count
    push    ecx        ; flip operands
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

b_not_below:
    cmp     cx,128      ; if shift count too big
    jna     is_equal
    mov     esi,x
    shl     esi,1       ; get sign
    rcr     si,1        ; merge with exponent
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
    jmp     done

is_equal:

    mov     esi,x
    mov     ch,0
    or      ecx,ecx
    jns     shifting

    mov     ch,-1
    neg     b[0xC]
    neg     b[0x8]
    sbb     b[0xC],0
    neg     b[0x4]
    sbb     b[0x8],0
    neg     b[0x0]
    sbb     b[0x4],0
    xor     esi,0x80000000  ; - flip sign

shifting:                   ; if shifting required

    mov     r,0
    test    cl,cl
    jz      add_mantissa
    cmp     cl,64
    jb      shift_32
    test    eax,eax         ; check low order qword for 1 bits
    jnz     shift_0
    test    edx,edx
    jz      shift_1
shift_0:
    inc     r
shift_1:
    cmp     cl,128          ; if shift count is 128
    jne     shift_right_64
    or      r,edi           ; get rest of sticky bits from high part
    xor     ebx,ebx         ; zero high part
    xor     edi,edi
shift_right_64:
    mov     eax,ebx
    mov     edx,edi
    xor     ebx,ebx
    xor     edi,edi
    jmp     align_fractions

shift_32:
    cmp     cl,32
    jb      shift_16
    test    eax,eax         ; check low order qword for 1 bits
    jnz     shift_right_32
    inc     r               ; edi=1 if EDX:EAX non zero
shift_right_32:
    mov     eax,edx
    mov     edx,ebx
    mov     ebx,edi
    xor     edi,edi
    jmp     align_fractions

shift_16:
    push    eax             ; get the extra sticky bits
    push    ebx
    xor     ebx,ebx
    shr     eax,15
    shrd    ebx,eax,cl
    or      r,ebx           ; save them
    pop     ebx
    pop     eax

align_fractions:
    shrd    eax,edx,cl
    shrd    edx,ebx,cl
    shrd    ebx,edi,cl
    shr     edi,cl

add_mantissa:

    add     eax,b[0x0]
    adc     edx,b[0x4]
    adc     ebx,b[0x8]
    adc     edi,b[0xC]

    adc     ch,0
    jns     mantissa_zero
    cmp     cl,128
    jne     negate_mantissa
    test    r,0x7FFFFFFF
    jz      negate_mantissa
    adc     eax,1
    adc     edx,0
    adc     ebx,0
    adc     edi,0

negate_mantissa:
    neg     edi
    neg     ebx
    sbb     edi,0
    neg     edx
    sbb     ebx,0
    neg     eax
    sbb     edx,0
    mov     ch,0
    xor     esi,0x80000000

mantissa_zero:

    push    ecx
    movzx   ecx,ch
    or      ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    pop     ecx
    jnz     exponent_zero
    xor     esi,esi

exponent_zero:
    test    si,si
    jz      done

    ; if top bits are 0

    test    ch,ch
    mov     ecx,r
    jnz     validate

    rol     ecx,1       ; set carry from last sticky bit
    rol     ecx,1

    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0

decrement_exponent:

    dec     si
    jz      done
    add     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    jnc     decrement_exponent

validate:

    inc     si
    cmp     si,Q_EXPMASK
    je      return_overflow

    stc
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1

    add     ecx,ecx
    jnc     end_validate

    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0
    jnc     end_validate

    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      return_overflow

end_validate:

    add     esi,esi
    rcr     si,1

done:

    mov     ecx,A
    mov     [ecx+0x0],eax
    mov     [ecx+0x4],edx
    mov     [ecx+0x8],ebx
    mov     [ecx+0xC],edi
    mov     [ecx+16],si
    mov     eax,ecx
    ret

error_zero_a:
    shl     si,1            ; place sign in carry
    jnz     error_zero_a_0
    shr     esi,16          ; return B
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
    shl     esi,1
    mov     ecx,eax         ; if not zero
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jz      done
    shr     esi,1           ; -> restore sign bit
    jmp     done

error_zero_a_0:
    rcr     si,1            ; put back the sign
    jmp     if_zero_b


return_nan:
    mov     esi,0xFFFF
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
    xor     eax,eax
    jmp     done

return_overflow:

return_infinity:
    mov     esi,0x7FFF
return_0:
    xor     eax,eax
    xor     edx,edx
    xor     ebx,ebx
    xor     edi,edi
    jmp     done

return_underflow:

return_zero:
    xor     esi,esi
    jmp     return_0

return_b:
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
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
    or      ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
    jnz     @F
    or      esi,-1
    jmp     return_nan
@@:
    cmp     edi,b[0xC]
    jb      return_b
    ja      done
    cmp     ebx,b[0x8]
    jb      return_b
    ja      done
    cmp     edx,b[0x4]
    jb      return_b
    ja      done
    cmp     eax,b[0x0]
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    mov     ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_lc_fltadd endp

_fltadd proc a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(a, b, 0)
    ret

_fltadd endp

_fltsub proc a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(a, b, 0x80000000)
    ret

_fltsub endp

    end
