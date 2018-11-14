; DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

divq proc vectorcall uses rsi rdi rbx r12 r13 r14 A:XQFLOAT, B:XQFLOAT

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movaps  xmm0,xmm1
    movq    rbx,xmm0
    movhlps xmm0,xmm0
    movq    rcx,xmm0

    shld    rsi,rcx,16
    shld    rcx,rbx,16
    shl     rbx,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rcx,1
    rcr     rbx,1

    shld    rsi,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rdx,1
    rcr     rax,1

    add     si,1
    jc      er_NaN_A
    jo      er_NaN_A
    add     esi,0xFFFF
    jc      er_NaN_B
    jo      er_NaN_B
    sub     esi,0x10000

    mov     rdi,rbx
    or      rdi,rcx
    jz      B_zero?
L1:
    mov     rdi,rax
    or      rdi,rdx
    jz      A_zero?
L2:
    mov     edi,esi
    rol     edi,16
    sar     edi,16
    sar     esi,16
    and     edi,0x80007FFF
    and     esi,0x80007FFF
    rol     edi,16
    rol     esi,16
    add     di,si
    rol     edi,16
    rol     esi,16
    test    di,di
    jnz     L4
L5:
    dec     di
    add     rax,rax
    adc     rdx,rdx
    jnc     L5
L4:
    test    si,si
    jnz     L6
L7:
    dec     si
    add     rbx,rbx
    adc     rcx,rcx
    jnc     L7
L6:
    sub     di,si
    add     di,Q_EXPBIAS
    js      L8
    cmp     di,Q_EXPMASK
    jnb     overflow
L8:
    cmp     di,-65
    jl      return_0

    mov     r10,rbx
    mov     r11,rcx
    mov     r13,rax
    mov     r14,rdx
    xor     eax,eax
    xor     edx,edx
    xor     ebx,ebx
    or      rcx,r10
    jz      D4

    xor     r8d,r8d
    xor     r9d,r9d
    xor     ecx,ecx
    xor     r12d,r12d
    mov     esi,127
D0:
    inc     esi
    add     r10,r10
    adc     r11,r11
    jc      D1
    cmp     r11,r14
    jb      D0
    ja      D1
    cmp     r10,r13
    jbe     D0
D1:
    rcr     r11,1
    rcr     r10,1
    rcr     r9,1
    rcr     r8,1
    sub     rcx,r8
    sbb     r12,r9
    sbb     r13,r10
    sbb     r14,r11
    cmc
    jc      D3
D2:
    add     rax,rax
    adc     rdx,rdx
    adc     rbx,rbx
    dec     esi
    js      D4
    shr     r11,1
    rcr     r10,1
    rcr     r9,1
    rcr     r8,1
    add     rcx,r8
    adc     r12,r9
    adc     r13,r10
    adc     r14,r11
    jnc     D2
D3:
    adc     rax,rax
    adc     rdx,rdx
    adc     rbx,rbx
    dec     esi
    jns     D1
D4:
    mov     esi,edi
    dec     si
    shr     bl,1
    jnc     L9
    rcr     rdx,1
    rcr     rax,1
    inc     esi
L9:
    or      si,si
    jg      L10
    jnz     L11
    mov     cl,1
    jmp     L12
L11:
    neg     si
    mov     ecx,esi
L12:
    shrd    rax,rdx,cl
    shr     rdx,cl
    xor     esi,esi
L10:
    add     esi,esi
    rcr     si,1
done:
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rsi,16
    mov     qword ptr A[0],rax
    mov     qword ptr A[8],rdx
    movaps  xmm0,A
toend:
    ret

A_zero?:
    add     si,si
    jz      done
    rcr     si,1
    jmp     L2

B_zero?:
    test    esi,0x7FFF0000
    jnz     L1
    mov     edi,esi
    mov     esi,0xFFFF
    or      rax,rdx
    jnz     return_m0
    add     di,di
    jnz     done
    mov     rdx,0x4000000000000000
    mov     esi,0x7FFF
    jmp     done

return_0:
    xorps   xmm0,xmm0
    jmp     toend

exp_too_small:
    dec     si
    jmp     return_si0

overflow:
    mov     esi,0x7FFF
return_si0:
    add     esi,esi
    rcr     si,1
return_m0:
    xor     rax,rax
    xor     rdx,rdx
    jmp     done
er_NaN_B:
    sub     esi,0x10000
    mov     rdi,rbx
    or      edi,ecx
    jnz     return_B
    mov     r8,0x8000000000000000
    cmp     rcx,r8
    jne     return_B
    mov     rdi,rax
    or      rdi,rdx
    jnz     @F
    mov     esi,-1
    jmp     return_B
@@:
    or      si,si
    jns     return_B
    xor     esi,0x80000000

return_B:
    mov     rdx,rcx
    mov     rax,rbx
    shr     esi,16
    jmp     done

er_NaN_A:
    mov     r8,0x8000000000000000
    mov     rdi,rax
    or      edi,edx
    jnz     @F
    cmp     rdx,r8
    jne     @F
    mov     rdi,rbx
    or      rdi,rcx
    jnz     @F
    mov     esi,-1
    jmp     done
@@:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    mov     rdi,rax
    or      edi,edx
    jnz     done
    cmp     rdx,r8
    jne     done
    or      esi,esi
    jns     done
    xor     esi,0x8000
    jmp     done
@@:
    sub     esi,0x10000
    cmp     rdx,rcx
    jne     @F
    cmp     rax,rbx
@@:
    ja      done
    jnz     return_B
    mov     rdi,rax
    or      edi,edx
    jnz     done
    cmp     rdx,r8
    jne     done
    or      si,si
    jns     return_B
    xor     esi,0x80000000
    jmp     return_B

divq endp

    end
