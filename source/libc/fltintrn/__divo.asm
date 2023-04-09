; __DIVO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    option dotname

    .code

ifdef _WIN64

    option win64:noauto

__divo proc __ccall uses rbx dividend:ptr uint128_t, divisor:ptr uint128_t, reminder:ptr uint128_t

    mov     rbx,[rcx]
    mov     rcx,[rcx+size_t]
    mov     r10,[rdx]
    mov     r11,[rdx+size_t]
    xor     eax,eax ; quotient
    xor     edx,edx
    test    r10,r10
    jnz     .not_zero
    test    r11,r11
    jnz     .not_zero
    xor     rbx,rbx
    xor     rcx,rcx
    jmp     .done

.not_zero:

    ; if divisor > dividend : reminder = dividend, quotient = 0

    cmp     r11,rcx
    jne     .is_above
    cmp     r10,rbx

.is_above:

    ja      .done
    jnz     .divide

.is_equal:  ; if divisor == dividend :

    xor     rbx,rbx ; reminder = 0
    xor     rcx,rcx
    inc     eax     ; quotient = 1
    jmp     .done

.divide:

    mov     r8d,-1

.0:
    inc     r8d
    shl     r10,1
    rcl     r11,1
    jc      .1
    cmp     r11,rcx
    ja      .1
    jc      .0
    cmp     r10,rbx
    jc      .0
    jz      .0
.1:
    rcr     r11,1
    rcr     r10,1
    sub     rbx,r10
    sbb     rcx,r11
    cmc
    jc      .4
.2:
    add     rax,rax
    adc     rdx,rdx
    dec     r8d
    jns     .3
    add     rbx,r10
    adc     rcx,r11
    jmp     .done
.3:
    shr     r11,1
    rcr     r10,1
    add     rbx,r10
    adc     rcx,r11
    jnc     .2
.4:
    adc     rax,rax
    adc     rdx,rdx
    dec     r8d
    jns     .1

.done:
    mov     r10,reminder
    test    r10,r10
    jz      .5

    mov     [r10],rbx
    mov     [r10+8],rcx

.5:
    mov     r10,rax
    mov     rax,dividend
    mov     [rax],r10
    mov     [rax+8],rdx

else

    option stackbase:esp

__divo proc __ccall uses esi edi ebx ebp dividend:ptr uint128_t, divisor:ptr uint128_t, reminder:ptr uint128_t

  local     e8d:dword
  local     e9d:dword
  local     e10:dword
  local     e11:dword
  local     e12:dword
  local     e13:dword

    mov     e9d,0
    mov     ecx,dividend
    mov     edx,divisor
    mov     ebp,[ecx+8]
    mov     edi,[ecx+12]

    mov     ebx,[ecx]
    mov     ecx,[ecx+size_t]
    mov     e10,[edx]
    mov     e11,[edx+size_t]
    mov     e12,[edx+8]
    mov     e13,[edx+12]

    xor     esi,esi
    xor     eax,eax ; quotient
    xor     edx,edx

    cmp     e10,0
    jnz     .not_zero
    cmp     e11,0
    jnz     .not_zero
    cmp     e12,0
    jnz     .not_zero
    cmp     e13,0
    jnz     .not_zero

    xor     ebx,ebx
    xor     ecx,ecx
    xor     ebp,ebp
    xor     edi,edi
    jmp     .done

.not_zero:

    ; if divisor > dividend : reminder = dividend, quotient = 0

    cmp     e13,edi
    jne     .is_above
    cmp     e12,ebp
    jne     .is_above
    cmp     e11,ecx
    jne     .is_above
    cmp     e10,ebx

.is_above:

    ja      .done
    jnz     .divide

.is_equal:  ; if divisor == dividend :

    xor     ebx,ebx ; reminder = 0
    xor     ecx,ecx
    xor     ebp,ebp
    xor     edi,edi
    inc     eax     ; quotient = 1
    jmp     .done

.divide:

    mov     e8d,-1

.0:
    inc     e8d
    shl     e10,1
    rcl     e11,1
    rcl     e12,1
    rcl     e13,1
    jc      .1
    cmp     e13,edi
    ja      .1
    jc      .0
    cmp     e12,ebp
    ja      .1
    jc      .0
    cmp     e11,ecx
    ja      .1
    jc      .0
    cmp     e10,ebx
    jc      .0
    jz      .0
.1:
    rcr     e13,1
    rcr     e12,1
    rcr     e11,1
    rcr     e10,1
    sub     ebx,e10
    sbb     ecx,e11
    sbb     ebp,e12
    sbb     edi,e13
    cmc
    jc      .4
.2:
    add     eax,eax
    adc     edx,edx
    adc     esi,esi
    rcl     e9d,1
    dec     e8d
    jns     .3
    add     ebx,e10
    adc     ecx,e11
    adc     ebp,e12
    adc     edi,e13
    jmp     .done
.3:
    shr     e13,1
    rcr     e12,1
    rcr     e11,1
    rcr     e10,1
    add     ebx,e10
    adc     ecx,e11
    adc     ebp,e12
    adc     edi,e13
    jnc     .2
.4:
    adc     eax,eax
    adc     edx,edx
    adc     esi,esi
    rcl     e9d,1
    dec     e8d
    jns     .1

.done:

    mov     e8d,eax
    mov     eax,reminder
    test    eax,eax
    jz      .5

    mov     [eax],ebx
    mov     [eax+4],ecx
    mov     [eax+8],ebp
    mov     [eax+12],edi

.5:
    mov     ecx,e8d
    mov     ebx,e9d

    mov     eax,dividend
    mov     [eax],ecx
    mov     [eax+4],edx
    mov     [eax+8],esi
    mov     [eax+12],ebx

endif
    ret

__divo endp

    end
