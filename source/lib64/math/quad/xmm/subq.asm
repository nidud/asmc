; SUBQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

subq proc vectorcall uses rsi rdi rbx A:XQFLOAT, B:XQFLOAT

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movaps  xmm0,xmm1
    movq    rbx,xmm0
    movhlps xmm0,xmm0
    movq    rdi,xmm0

    shld    rsi,rdi,16
    shld    rdi,rbx,16
    shl     rbx,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rdi,1
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
    xor     esi,0x80000000

    mov     rcx,rax         ; A is 0 ?
    or      rcx,rdx
    jz      A_zero?
L1:
    mov     rcx,rbx         ; B is 0 ?
    or      rcx,rdi
    jz      B_zero?
L2:
    mov     ecx,esi         ; exponent and sign of A into ECX
    rol     esi,16          ; shift to top
    sar     esi,16          ; duplicate sign
    sar     ecx,16          ; ...
    and     esi,0x80007FFF  ; isolate signs and exponent
    and     ecx,0x80007FFF  ; ...
    mov     r9d,ecx         ; assume A < B
    rol     esi,16          ; rotate signs to bottom
    rol     ecx,16          ; ...
    add     cx,si           ; calc sign of result
    rol     esi,16          ; rotate signs to top
    rol     ecx,16          ; ...
    sub     cx,si           ; calculate difference in exponents
    jz      L3
    jnc     L4
    mov     r9d,esi         ; get larger exponent for result
    neg     cx              ; negate the shift count
    xchg    rbx,rax         ; flip operands
    xchg    rdi,rdx
L4:
    cmp     cx,128
    ja      too_big
L3:
    mov     esi,r9d
    mov     ch,0            ; zero extend B
    or      ecx,ecx         ; get bit 0 of sign word - value is 0 if
                            ; both operands have same sign, 1 if not
    jns     L5              ; if signs are different
    mov     ch,-1           ; - set high part to ones
    neg     rdi             ; - negate the fraction of B
    neg     rbx
    sbb     rdi,0
    xor     esi,0x80000000  ; - flip sign
L5:
    xor     r11d,r11d       ; get a zero for sticky bits
    test    cl,cl           ; if shifting required
    jz      L6
    cmp     cl,64           ; if shift count >= 64
    jb      L7
    test    rax,rax         ; check low order qword for 1 bits
    jz      L8
    inc     r11b            ; r11=1 if RAX non zero
L8:
    cmp     cl,128          ; if shift count is 128
    jne     L9
    or      r11,rdx         ; get rest of sticky bits from high part
    xor     rdx,rdx         ; zero high part
L9:
    mov     rax,rdx         ; shift right 64
    xor     rdx,rdx
L7:
    xor     r8d,r8d
    shrd    r8,rax,cl       ; get the extra sticky bits
    or      r11,r8          ; save them
    shrd    rax,rdx,cl      ; align the fractions
    shr     rdx,cl
L6:
    add     rax,rbx
    adc     rdx,rdi
    adc     ch,0
    jns     L10
    cmp     cl,128
    jne     L11
    xor     r8b,r8b
    mov     r9,0x7FFFFFFFFFFFFFFF
    test    r11,r9
    jz      L12
    inc     r8b             ; make single sticky bit
L12:
    shr     r8b,1
    adc     rax,0           ; round up fraction if required
    adc     rdx,0
L11:
    neg     rdx
    neg     rax
    sbb     rdx,0
    mov     ch,0
    xor     esi,0x80000000
L10:
    test    rax,rax
    jnz     L13
    test    rdx,rdx
    jnz     L13
    test    ch,ch
    jnz     L13
    mov     rsi,rax
L13:
    test    si,si
    jz      done
    test    ch,ch           ; if top bits are 0
    jnz     L14
    rol     r11,1           ; set carry from last sticky bit
    ror     r11,1
L15:
    dec     si              ; decrement exponent
    jz      break
    adc     rax,rax         ; shift fraction left one bit
    adc     rdx,rdx
    jnc     L15
L14:
    inc     si
    cmp     si,0x7FFF
    je      overflow
    stc                     ; set carry
    rcr     rdx,1           ; shift fraction right 1
    rcr     rax,1
    test    eax,0x4000      ; if guard bit is on
    jz      break
    add     r11,r11         ; get top sticky bit
    jnz     L15             ; if no more sticky bits
    bt      eax,14          ; set carry with bit 14 of AX
L16:
    jnc     break           ; round up fraction if required
    add     rax,0x4000
    adc     rdx,0
    jnc     break           ; if we got a carry
    rcr     rdx,1           ; shift fraction right 1
    rcr     rax,1
    inc     si              ; increment exponent
    cmp     si,0x7FFF
    je      overflow
break:
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

too_big:
    mov     esi,r9d
    mov     rax,rbx
    mov     rdx,rdi
    jmp     done

A_zero?:
    add     si,si       ; place sign in carry
    jnz     @F
    shr     esi,16
    mov     rax,rbx     ; return B
    mov     rdx,rdi
    shl     esi,1
    or      rbx,rdi     ; check for 0
    or      bx,si
    jz      done
    shr     esi,1       ; -> restore sign bit
    jmp     done
@@:
    rcr     si,1        ; restore sign of A
    jmp     L1

B_zero?:
    test    esi,0x7FFF0000
    jz      done
    jmp     L1

return_0:
    xorps   xmm0,xmm0
    jmp     toend

overflow:
    mov     esi,0x7FFF
    xor     rax,rax
    xor     rdx,rdx
    jmp     done

er_NaN_B:   ; B is a NaN or infinity
    sub     esi,0x10000
    test    rbx,rbx
    jnz     return_B
    mov     rdx,0x8000000000000000
    cmp     rdx,rdi
    jne     return_B
    xor     esi,r9d
return_B:
    mov     rdx,rdi
    mov     rax,rbx
    shr     esi,16
    jmp     done

er_NaN_A:   ; A is a NaN or infinity
    dec     si
    add     esi,0x10000
    jo      @F
    jnc     done
@@:
    sub     esi,0x10000
    mov     r11,0x8000000000000000
    test    rax,rax
    jnz     @F
    test    rbx,rbx
    jnz     @F
    cmp     rdx,rdi
    jnz     @F
    cmp     rdx,r11
    jnz     @F
    shr     rdx,2
    or      si,-1 ; -NaN - FFFF40 ?
    jmp     done
@@:
    jne     @F
    cmp     rbx,rax
@@:
    jna     return_B
    jmp     done

subq endp

    end
