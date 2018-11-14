; MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

mulq proc vectorcall uses rsi rdi rbx A:XQFLOAT, B:XQFLOAT

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

    add     si,1            ; add 1 to exponent
    jc      er_NaN_A        ; quit if NaN
    jo      er_NaN_A        ; ...
    add     esi,0xFFFF      ; readjust low exponent and inc high word
    jc      er_NaN_B        ; quit if NaN
    jo      er_NaN_B        ; ...
    sub     esi,0x10000     ; readjust high exponent

    mov     rdi,rax         ; A is 0 ?
    or      rdi,rdx
    jz      A_zero?
L1:
    mov     rdi,rbx         ; B is 0 ?
    or      rdi,rcx
    jz      B_zero?
L2:
    mov     edi,esi         ; exponent and sign of A into EDI
    rol     edi,16          ; shift to top
    sar     edi,16          ; duplicate sign
    sar     esi,16          ; ...
    and     edi,0x80007FFF  ; isolate signs and exponent
    and     esi,0x80007FFF  ; ...
    add     esi,edi         ; determine exponent of result and sign
    sub     si,Q_EXPBIAS-1  ; remove extra bias
    jc      L3              ; exponent negative ?
    cmp     si,Q_EXPMASK    ; overflow ?
    ja      overflow
L3:
    cmp     si,-64          ; exponent too small ?
    jl      exp_too_small

    mov     r10,rbx
    mov     r11,rcx
    mov     r8,rax
    mov     r9,rcx
    mov     rcx,rdx

    mul     r10
    mov     rbx,rdx
    mov     rdi,rax
    mov     rax,rcx
    mul     r11
    mov     r11,rdx
    xchg    r10,rax
    mov     rdx,rcx
    mul     rdx
    add     rbx,rax
    adc     r10,rdx
    adc     r11,0
    mov     rax,r8
    mov     rdx,r9
    mul     rdx
    add     rbx,rax
    adc     r10,rdx
    adc     r11,0
    mov     rdx,rbx
    mov     rax,rdi

    mov     rdi,rdx
    mov     rax,r10
    mov     rdx,r11
    test    rdx,rdx
    js      L4
    shl     rdi,1           ; if not normalized
    rcl     rax,1
    rcl     rdx,1
    dec     si
L4:
    shl     rdi,1
    jnc     L5
    jnz     L6
    test    edi,edi
    jz      L7
    stc
    jmp     L6
L7:
    bt      eax,0
L6:
    adc     rax,0
    adc     rdx,0
    jnc     L5
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,0x7FFF
    jz      overflow
L5:
    or      si,si
    jg      L8
    jnz     L9
    and     si,0xFF00
    inc     si
    jmp     LA
L9:
    neg     si
LA:
    movzx   ecx,si
    shrd    rax,rdx,cl
    shr     rdx,cl
    xor     si,si
L8:
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
    add     si,si       ; place sign in carry
    jz      done        ; return 0
    rcr     si,1        ; restore sign of A
    jmp     L1

B_zero?:
    test    esi,0x7FFF0000
    jz      return_0
    jmp     L1

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

er_NaN_B:   ; B is a NaN or infinity
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
    mov     esi,-1          ; -NaN
    jmp     return_B
@@:
    or      si,si
    jns     return_B
    xor     esi,0x80000000   ; flip sign bit

return_B:
    mov     rdx,rcx
    mov     rax,rbx
    shr     esi,16
    jmp     done

er_NaN_A:   ; A is a NaN or infinity
    mov     r8,0x8000000000000000
    mov     rdi,rax
    or      edi,edx
    jnz     @F
    cmp     rdx,r8
    jne     @F
    mov     rdi,rbx
    or      rdi,rcx
    jnz     @F
    mov     esi,-1 ; -NaN
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

mulq endp

    end
