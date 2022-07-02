; __DIVO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    option dotname, win64:noauto
    option stackbase:rsp

    .code

ifdef _WIN64

__divo proc __ccall uses rbx dividend:ptr uint128_t, divisor:ptr uint128_t, reminder:ptr uint128_t

else

__divo proc __ccall uses esi edi ebx ebp dividend:ptr uint128_t, divisor:ptr uint128_t, reminder:ptr uint128_t

  local     r8d:dword
  local     r9d:dword
  local     r10:dword
  local     r11:dword
  local     r12:dword
  local     r13:dword

    mov     r9d,0
    mov     ecx,dividend
    mov     edx,divisor
    mov     ebp,[rcx+8]
    mov     edi,[rcx+12]

endif

    mov     rbx,[rcx]
    mov     rcx,[rcx+size_t]
    mov     r10,[rdx]
    mov     r11,[rdx+size_t]
ifndef _WIN64
    mov     r12,[rdx+8]
    mov     r13,[rdx+12]
    xor     esi,esi
endif
    xor     eax,eax ; quotient
    xor     edx,edx

ifdef _WIN64
    test    r10,r10
    jnz     .not_zero
    test    r11,r11
    jnz     .not_zero
else
    cmp     r10,0
    jnz     .not_zero
    cmp     r11,0
    jnz     .not_zero
    cmp     r12,0
    jnz     .not_zero
    cmp     r13,0
    jnz     .not_zero
endif
    xor     rbx,rbx
    xor     rcx,rcx
ifndef _WIN64
    xor     ebp,ebp
    xor     edi,edi
endif
    jmp     .done

.not_zero:

; if divisor > dividend : reminder = dividend, quotient = 0

ifndef _WIN64
    cmp     r13,edi
    jne     .is_above
    cmp     r12,ebp
    jne     .is_above
endif
    cmp     r11,rcx
    jne     .is_above
    cmp     r10,rbx

.is_above:

    ja      .done
    jnz     .divide

.is_equal:  ; if divisor == dividend :

    xor     rbx,rbx ; reminder = 0
    xor     rcx,rcx
ifndef _WIN64
    xor     ebp,ebp
    xor     edi,edi
endif
    inc     eax     ; quotient = 1
    jmp     .done

.divide:

    mov     r8d,-1

.0:
    inc     r8d
    shl     r10,1
    rcl     r11,1
ifndef _WIN64
    rcl     r12,1
    rcl     r13,1
endif
    jc      .1
ifndef _WIN64
    cmp     r13,edi
    ja      .1
    jc      .0
    cmp     r12,ebp
    ja      .1
    jc      .0
endif
    cmp     r11,rcx
    ja      .1
    jc      .0
    cmp     r10,rbx
    jc      .0
    jz      .0
.1:
ifndef _WIN64
    rcr     r13,1
    rcr     r12,1
endif
    rcr     r11,1
    rcr     r10,1
    sub     rbx,r10
    sbb     rcx,r11
ifndef _WIN64
    sbb     ebp,r12
    sbb     edi,r13
endif
    cmc
    jc      .4
.2:
    add     rax,rax
    adc     rdx,rdx
ifndef _WIN64
    adc     esi,esi
    rcl     r9d,1
endif
    dec     r8d
    jns     .3
    add     rbx,r10
    adc     rcx,r11
ifndef _WIN64
    adc     ebp,r12
    adc     edi,r13
endif
    jmp     .done
.3:
ifndef _WIN64
    shr     r13,1
    rcr     r12,1
    rcr     r11,1
else
    shr     r11,1
endif
    rcr     r10,1
    add     rbx,r10
    adc     rcx,r11
ifndef _WIN64
    adc     ebp,r12
    adc     edi,r13
endif
    jnc     .2
.4:
    adc     rax,rax
    adc     rdx,rdx
ifndef _WIN64
    adc     esi,esi
    rcl     r9d,1
endif
    dec     r8d
    jns     .1

.done:

ifndef _WIN64

    mov     r8d,eax
    mov     eax,reminder
    test    eax,eax
    jz      .5

    mov     [eax],ebx
    mov     [eax+4],ecx
    mov     [eax+8],ebp
    mov     [eax+12],edi

.5:
    mov     ecx,r8d
    mov     ebx,r9d

    mov     eax,dividend
    mov     [eax],ecx
    mov     [eax+4],edx
    mov     [eax+8],esi
    mov     [eax+12],ebx

else

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

endif
    ret

__divo endp

    end
