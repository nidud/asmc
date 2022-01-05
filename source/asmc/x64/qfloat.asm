; QFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include errno.inc
include asmc.inc
include qfloat.inc
include expreval.inc

    option dotname

    .data

    _fltpowtable EXTFLOAT \
     { 0x0000000000000000, 0xA000000000000000, 0x4002 },
     { 0x0000000000000000, 0xC800000000000000, 0x4005 },
     { 0x0000000000000000, 0x9C40000000000000, 0x400C },
     { 0x0000000000000000, 0xBEBC200000000000, 0x4019 },
     { 0x0000000000000000, 0x8E1BC9BF04000000, 0x4034 },
     { 0xF020000000000000, 0x9DC5ADA82B70B59D, 0x4069 },
     { 0x3CBF6B71C76B25FE, 0xC2781F49FFCFA6D5, 0x40D3 },
     { 0xC66F336C36B10137, 0x93BA47C980E98CDF, 0x41A8 },
     { 0xDDBB901B98FEEAB7, 0xAA7EEBFB9DF9DE8D, 0x4351 },
     { 0xCC655C54BC505900, 0xE319A0AEA60E91C6, 0x46A3 },
     { 0x650D3D28F18B50D0, 0xC976758681750C17, 0x4D48 },
     { 0xA74D28CE329ACE52, 0x9E8B3B5DC53D5DE4, 0x5A92 },
     { 0xC94C153F804A8000, 0xC46052028A20979A, 0x7525 },
     { 0xCCCCCCCCCCCCCCCC, 0xCCCCCCCCCCCCCCCC, 0x3FFB },
     { 0x3D70A3D70A3D7000, 0xA3D70A3D70A3D70A, 0x3FF8 },
     { 0xD3C36113404EA4A8, 0xD1B71758E219652B, 0x3FF1 },
     { 0xFDC20D2B36BA7C00, 0xABCC77118461CEFC, 0x3FE4 },
     { 0x4C2EBE687989A9B0, 0xE69594BEC44DE15B, 0x3FC9 },
     { 0x67DE18EDA5814A00, 0xCFB11EAD453994BA, 0x3F94 },
     { 0x3F2398D747B36000, 0xA87FEA27A539E9A5, 0x3F2A },
     { 0xAC7CB3F6D05DC000, 0xDDD0467C64BCE4A0, 0x3E55 },
     { 0xFA911155FEFB4000, 0xC0314325637A1939, 0x3CAC },
     { 0x7132D332E3F20000, 0x9049EE32DB23D21C, 0x395A },
     { 0x87A601586BD40000, 0xA2A682A5DA57C0BD, 0x32B5 },
     { 0x492512D4F2EB0000, 0xCEAE534F34362DE4, 0x256B },
     { 0x2DE38123A1C40000, 0xA6DD04C8D2CE9FDE, 0x0AD8 }

     define EXQ_1E16 _fltpowtable[EXTFLOAT*4]

     lflt STRFLT { { 0, 0, 0 }, 0, 0, 0 }

     qerrno errno_t 0
     e_space db "#not enough space",0

    .code

    option win64:rsp noauto

;-------------------------------------------------------------------------------
; 64-bit DIV
;-------------------------------------------------------------------------------

__udiv64 proc watcall dividend:uint64_t, divisor:uint64_t

    mov     rcx,rdx
    xor     edx,edx
    test    rcx,rcx
    jz      .0
    div     rcx
    jmp     .1
.0:
    xor     eax,eax
.1:
    ret

__udiv64 endp

;-------------------------------------------------------------------------------
; 64-bit IDIV
;-------------------------------------------------------------------------------

__div64 proc watcall dividend:int64_t, divisor:int64_t

    test    rax,rax ; dividend signed ?
    js      .0
    test    rdx,rdx ; divisor signed ?
    js      .0
    call    __udiv64
    jmp     .2
.0:
    neg     rax
    test    rdx,rdx
    jns     .1
    neg     rdx
    call    __udiv64
    neg     rdx
    jmp     .2
.1:
    call    __udiv64
    neg     rdx
    neg     rax
.2:
    ret

__div64 endp

;-------------------------------------------------------------------------------
; 64-bit REM
;-------------------------------------------------------------------------------

__rem64 proc watcall dividend:int64_t, divisor:int64_t

    call    __div64
    mov     rax,rdx
    ret

__rem64 endp

;-------------------------------------------------------------------------------
; 128-bit integer
;-------------------------------------------------------------------------------

__mulo proc fastcall multiplier:ptr, multiplicand:ptr, highproduct:ptr

    mov rax,[rcx]
    mov r10,[rcx+8]
    mov r9, [rdx+8]

    .if ( !r10 && !r9 )

        .if ( r8 )

            mov [r8],r9
            mov [r8+8],r9
        .endif
        mul qword ptr [rdx]

    .else
        push rcx
        mov  r11,[rdx]
        mul  r11         ; a * b
        push rax
        xchg rdx,r11
        mov  rax,r10
        mul  rdx         ; a[8] * b
        add  r11,rax
        xchg rcx,rdx
        mov  rax,[rdx]
        mul  r9          ; a * b[8]
        add  r11,rax
        adc  rcx,rdx
        mov  edx,0
        adc  edx,0

        .if ( r8 )

            xchg rdx,r9
            mov  rax,r10
            mul  rdx     ; a[8] * b[8]
            add  rax,rcx
            adc  rdx,r9
            mov  [r8],rax
            mov  [r8+8],rdx
        .endif
        pop rax
        mov rdx,r11
        pop rcx
    .endif
    mov [rcx],rax
    mov [rcx+8],rdx
    mov rax,rcx
    ret

__mulo endp

__divo proc fastcall dividend:ptr, divisor:ptr, reminder:ptr

    mov rax,[rcx]
    mov [r8],rax
    mov rax,[rcx+8]
    mov [r8+8],rax
    xor eax,eax
    mov [rcx],rax
    mov [rcx+8],rax

    or rax,[rdx]
    or rax,[rdx+8]
    .ifz
        mov [r8],rax
        mov [r8+8],rax
        .return rcx
    .endif
    mov rax,[rdx+8]
    .if rax == [r8+8]
        mov rax,[rdx]
        cmp rax,[r8]
    .endif
    .return .ifa            ; if divisor > dividend : reminder = dividend, quotient = 0
    .ifz                    ; if divisor == dividend :
        xor eax,eax         ; reminder = 0
        mov [r8],rax
        mov [r8+8],rax
        inc byte ptr [rcx]  ; quotient = 1
        .return rcx
    .endif

    mov r10,[rdx]           ; divisor
    mov r11,[rdx+8]
    mov r9d,-1
    .while 1
        inc r9d
        add r10,r10
        adc r11,r11
        .break .ifc
        .break .if r11 > [r8+8]
        .continue .ifb
        .break .if r10 > [r8]
        .continue .ifb
    .endw

    .while 1
        rcr r11,1
        rcr r10,1
        sub [r8],r10
        sbb [r8+8],r11
        cmc
        .ifnc
            .repeat
                mov rax,[rcx]
                add [rcx],rax
                mov rax,[rcx+8]
                adc [rcx+8],rax
                dec r9d
                .ifs
                    add [r8],r10
                    adc [r8+8],r11
                    .break(1)
                .endif
                shr r11,1
                rcr r10,1
                add [r8],r10
                adc [r8+8],r11
            .untilb
        .endif
        mov rax,[rcx]
        adc [rcx],rax
        mov rax,[rcx+8]
        adc [rcx+8],rax
        dec r9d
        .break .ifs
    .endw
    mov rax,rcx
    ret

__divo endp

__shlo proc fastcall val:ptr, count:int_t, bits:int_t

    push rcx
    mov r10,rcx
    mov ecx,edx

    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 )

        xor eax,eax
        xor edx,edx

    .elseif r8d == 128

        .while ecx >= 64

            mov rdx,rax
            xor eax,eax
            sub ecx,64
        .endw

        shld rdx,rax,cl
        shl rax,cl

    .else

        shl rax,cl
    .endif

    mov [r10],rax
    mov [r10+8],rdx
    pop rax
    ret

__shlo endp

__shro proc fastcall val:ptr, count:int_t, bits:int_t

    push rcx
    mov r10,rcx
    mov ecx,edx
    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 )

        xor edx,edx
        xor eax,eax

    .elseif r8d == 128

        .while ecx > 64
            mov rax,rdx
            xor edx,edx
            sub ecx,64
        .endw
        shrd rax,rdx,cl
        shr rdx,cl

    .else

        .if eax == -1 && r8d == 32

            and eax,eax
        .endif
        shr rax,cl
    .endif

    mov [r10],rax
    mov [r10+8],rdx
    pop rax
    ret

__shro endp

__saro proc fastcall val:ptr, count:int_t, bits:int_t

    push rcx
    mov r10,rcx
    mov ecx,edx

    mov rax,[r10]
    mov rdx,[r10+8]

    .if ecx >= 64 && r8d <= 64

        xor eax,eax
        xor edx,edx

    .elseif ecx >= 128 && r8d == 128

        sar rdx,63
        mov rax,rdx

    .elseif r8d == 128

        .while ecx > 64
            mov rax,rdx
            sar rdx,63
            sub ecx,64
        .endw
        shrd rax,rdx,cl
        sar rdx,cl

    .else

        .if eax == -1 && r8d == 32

            and eax,eax
        .endif
        sar rax,cl
    .endif
    mov [r10],rax
    mov [r10+8],rdx
    pop rax
    ret

__saro endp

;-------------------------------------------------------------------------------
; 134-bit (128+16) extended float
;-------------------------------------------------------------------------------

_lc_fltadd proc fastcall private uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT, negate:uint_t

    mov     r11,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000
    xor     esi,r8d         ; flip sign if subtract
    mov     rcx,rax
    or      rcx,rdx
    jz      error_zero_a
if_zero_b:
    mov     rcx,rbx
    or      rcx,rdi
    jz      error_zero_b

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
    jz      E2
    jnb     E1
    mov     r9d,esi         ; get larger exponent for result
    neg     cx              ; negate the shift count
    xchg    rax,rbx         ; flip operands
    xchg    rdx,rdi
E1:
    cmp     cx,128          ; if shift count too big
    jna     E2
    mov     esi,r9d
    shl     esi,1           ; get sign
    rcr     si,1            ; merge with exponent
    mov     rax,rbx
    mov     rdx,rdi
    jmp     done
E2:
    mov     esi,r9d         ; zero extend B
    mov     ch,0            ; get bit 0 of sign word - value is 0 if
    test    ecx,ecx         ; both operands have same sign, 1 if not
    jns     S1              ; if signs are different
    mov     ch,-1           ; - set high part to ones
    neg     rdi
    neg     rbx
    sbb     rdi,0
    xor     esi,0x80000000  ; - flip sign
S1:
    xor     r8d,r8d         ; get a zero for sticky bits
    test    cl,cl           ; if shifting required
    jz      M1
    cmp     cl,64           ; if shift count >= 64
    jb      S4
    test    rax,rax         ; check low order qword for 1 bits
    jz      S2
    inc     r8d             ; 1 if non zero
S2:
    cmp     cl,128          ; if shift count is 128
    jne     S3
    shr     rdx,32          ; get rest of sticky bits from high part
    or      r8d,edx
    xor     edx,edx         ; zero high part
S3:
    mov     rax,rdx         ; shift right 64
    xor     edx,edx
S4:
    xor     r9d,r9d
    mov     r10d,eax
    ;shr     r10d,15
    shrd    r9d,r10d,cl     ; get the extra sticky bits
    or      r8d,r9d         ; save them
    shrd    rax,rdx,cl      ; align the fractions
    shr     rdx,cl
M1:
    add     rax,rbx         ; add the fractions
    adc     rdx,rdi
    adc     ch,0
    jns     M3              ; if is negative
    cmp     cl,128
    jne     M2
    test    r8d,0x7FFFFFFF
    jz      M2
    add     rax,1           ; round up fraction if required
    adc     rdx,0
M2:
    neg     rdx             ; negate the fraction
    neg     rax
    sbb     rdx,0
    xor     ch,ch           ; zero top bits
    xor     esi,0x80000000  ; flip the sign
M3:
    mov     r9d,ecx         ; check for zero
    and     r9d,0xFF00
    or      r9,rax
    or      r9,rdx
    jnz     M4
    xor     esi,esi
M4:
    test    si,si
    jz      done

    test    ch,ch           ; if top bits are 0
    mov     ecx,r8d
    jnz     increment_exponent
    rol     ecx,1           ; set carry from last sticky bit
    rol     ecx,1
decrement_exponent:
    dec     si
    jz      denormal
    adc     rax,rax
    adc     rdx,rdx
    jnc     decrement_exponent
increment_exponent:
    inc     si
    cmp     si,Q_EXPMASK
    je      return_overflow
    stc
    rcr     rdx,1
    rcr     rax,1
    add     ecx,ecx
    jnc     denormal
    adc     rax,0
    adc     rdx,0
    jnc     denormal
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      return_overflow
denormal:
    add     esi,esi
    rcr     si,1

done:

    mov     [r11].STRFLT.mantissa.l,rax
    mov     [r11].STRFLT.mantissa.h,rdx
    mov     [r11].STRFLT.mantissa.e,si
    mov     rax,r11
    ret

error_zero_a:
    shl     si,1            ; place sign in carry
    jnz     error_zero_a_0
    shr     esi,16          ; return B
    mov     rax,rbx
    mov     rdx,rdi
    shl     esi,1
    mov     rcx,rax         ; if not zero
    or      rcx,rdx
    jz      done
    shr     esi,1           ; -> restore sign bit
    jmp     done

error_zero_a_0:
    rcr     si,1            ; put back the sign
    jmp     if_zero_b

error_zero_b:
    test    esi,0x7FFF0000
    jz      done
    jmp     calculate_exponent

return_nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
    xor     eax,eax
    jmp     done

return_overflow:

return_infinity:
    mov     esi,0x7FFF
return_0:
    xor     eax,eax
    xor     edx,edx
    jmp     done

return_underflow:

return_zero:
    xor     esi,esi
    jmp     return_0

return_b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     done

error_nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     done
    mov     rcx,rax
    or      rcx,rdx
    jnz     done
    xor     esi,0x8000
    jmp     done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jnz     @F
    or      esi,-1
    jmp     return_nan
@@:
    cmp     rdx,rdi
    jb      return_b
    ja      done
    cmp     rax,rbx
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    mov     rcx,rbx
    or      rcx,rdi
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_lc_fltadd endp

_fltadd proc fastcall a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(rcx, rdx, 0)
    ret

_fltadd endp

_fltsub proc fastcall a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(rcx, rdx, 0x80000000)
    ret

_fltsub endp


_fltmul proc fastcall uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT

    mov     r10,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    jz      error_zero_a
if_zero_b:
    mov     rcx,rbx
    or      rcx,rdi
    jz      error_zero_b

calculate_exponent:

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    add     esi,ecx
    sub     si,0x3FFE
    jc      if_too_small
    cmp     si,0x7FFF       ; quit if exponent is negative
    ja      return_overflow
if_too_small:
    cmp     si,-65
    jl      return_underflow

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
    js      rounding

    add     rbx,rbx
    adc     rax,rax
    adc     rdx,rdx
    dec     si

rounding:

    add     rbx,rbx
    adc     rax,0
    adc     rdx,0

validate:

    test    si,si
    jng     return_zero
    add     esi,esi
    rcr     si,1

done:

    mov     [r10].STRFLT.mantissa.l,rax
    mov     [r10].STRFLT.mantissa.h,rdx
    mov     [r10].STRFLT.mantissa.e,si
    mov     rax,r10
    ret

error_zero_a:
    add     si,si
    jz      is_zero_a
    rcr     si,1
    jmp     if_zero_b
is_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x8000
    jmp     done

error_zero_b:
    test    esi,0x7FFF0000
    jnz     calculate_exponent
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x80000000
    jmp     return_b

return_nan:
    mov     esi,0xFFFF
    mov     edx,1
    rol     rdx,1
    xor     eax,eax
    jmp     done

return_overflow:

return_infinity:
    mov     esi,0x7FFF
    xor     eax,eax
    xor     edx,edx
    jmp     done

return_underflow:

return_zero:
    xor     esi,esi
    xor     eax,eax
    xor     edx,edx
    jmp     done

return_b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     done

error_nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     done
    test    rax,rax
    jnz     done
    test    rdx,rdx
    jnz     done
    xor     esi,0x8000
    jmp     done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jnz     @F
    or      esi,-1
    jmp     return_nan
@@:
    cmp     rdx,rdi
    jb      return_b
    ja      done
    cmp     rax,rbx
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    test    rbx,rbx
    jnz     return_b
    test    rdi,rdi
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_fltmul endp


_fltdiv proc fastcall uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT

    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      error_nan_a
    jo      error_nan_a
    add     esi,0xFFFF
    jc      error_nan_b
    jo      error_nan_b
    sub     esi,0x10000

    mov     rcx,rbx
    or      rcx,rdi
    jz      error_zero_b
if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
    jz      error_zero_a

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

    test    cx,cx
    jz      normalize_a
if_denormal_b:
    test    si,si
    jz      normalize_b

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

    push    rbp
    push    rcx

    define  BITS 14

    shrd    rax,rdx,BITS
    shr     rdx,BITS
    shrd    rbx,rdi,BITS
    shr     rdi,BITS

    mov     rbp,rdi
    mov     r10,rax
    mov     r11,rdx
    xor     eax,eax
    xor     edx,edx

    xor     r8d,r8d
    xor     r9d,r9d
    xor     edi,edi
    xor     esi,esi
    mov     ecx,113 + (16-BITS)
    add     rbx,rbx
    adc     rbp,rbp

divide_1:
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    sub     rdi,r8
    sbb     rsi,r9
    sbb     r10,rbx
    sbb     r11,rbp
    cmc
    jc      divide_3

divide_2:
    add     rax,rax
    adc     rdx,rdx
    dec     ecx
    jz      end_divide
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    add     rdi,r8
    adc     rsi,r9
    adc     r10,rbx
    adc     r11,rbp
    jnc     divide_2

divide_3:
    adc     rax,rax
    adc     rdx,rdx
    dec     ecx
    jnz     divide_1

end_divide:

    pop     rsi
    pop     rbp
    dec     si

rounding:

    bt      rax,0
    adc     rax,0
    adc     rdx,0

overflow:

    bt      rdx,64 - BITS ; overflow bit
    jnc     reset

    rcr     rdx,1
    rcr     rax,1
    add     esi,1

reset:

    shld    rdx,rax,BITS
    shl     rax,BITS

    test    si,si
    jng     return_zero
    add     esi,esi
    rcr     si,1

done:

    mov     rcx,a
    mov     [rcx].STRFLT.mantissa.l,rax
    mov     [rcx].STRFLT.mantissa.h,rdx
    mov     [rcx].STRFLT.mantissa.e,si
    mov     rax,rcx
    ret

normalize_a:
    dec     cx
    add     rax,rax
    adc     rdx,rdx
    jnc     normalize_a
    jmp     if_denormal_b

normalize_b:
    dec     si
    add     rbx,rbx
    adc     rdi,rdi
    jnc     normalize_b
    jmp     calculate_exponent

error_zero_a:
    add     si,si
    jz      @F
    rcr     si,1
    jmp     init_done
@@:
    rcr     si,1
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x8000
    jmp     done

error_zero_b:
    test    esi,0x7FFF0000
    jnz     if_zero_a
    mov     rcx,rax
    or      rcx,rdx
    jnz     return_infinity
    mov     ecx,esi
    add     cx,cx
    jnz     return_infinity

return_nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
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
    jmp     done

return_zero:
    xor     esi,esi
    jmp     return_0

return_b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     done

error_nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     done
    mov     rcx,rax
    or      rcx,rdx
    jnz     done
    xor     esi,0x8000
    jmp     done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jz      return_nan
    cmp     rdx,rdi
    jb      return_b
    ja      done
    cmp     rax,rbx
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    mov     rcx,rbx
    or      rcx,rdi
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_fltdiv endp

_flttoi64 proc fastcall p:ptr STRFLT

    mov r10,rcx
    mov dx,[r10+16]
    mov eax,edx
    and eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor eax,eax
        .if dx & 0x8000
            dec rax
        .endif

    .elseif eax > 62 + Q_EXPBIAS

        mov qerrno,ERANGE
        mov rax,_I64_MAX
        .if edx & 0x8000
            mov rax,_I64_MIN
        .endif
    .else
        mov ecx,eax
        xor eax,eax
        sub ecx,Q_EXPBIAS-1
        mov r8,[r10+8]
        shld rax,r8,cl
        .if edx & 0x8000
            neg rax
        .endif
    .endif
    ret

_flttoi64 endp

_i64toflt proc fastcall p:ptr STRFLT, ll:int64_t

    mov rax,rdx
    mov rdx,rcx
    mov r8d,Q_EXPBIAS   ; set exponent
    test rax,rax        ; if number is negative
    .ifs
        neg rax         ; negate number
        or  r8d,0x8000
    .endif
    xor r9d,r9d
    .if rax
        bsr r9,rax      ; find most significant non-zero bit
        mov ecx,63
        sub ecx,r9d
        shl rax,cl      ; shift bits into position
        add r9d,r8d     ; calculate exponent
    .endif
    xor ecx,ecx
    mov [rdx].STRFLT.mantissa.l,rcx
    mov [rdx].STRFLT.mantissa.h,rax
    mov [rdx].STRFLT.mantissa.e,r9w
    mov rax,rdx
    ret

_i64toflt endp

    option win64:rbp auto save

define MAX_EXP_INDEX 13

_fltscale proc fastcall uses rsi rdi rbx r12 fp:ptr STRFLT

    mov rbx,rcx
    mov edi,[rbx].STRFLT.exponent
    lea rsi,_fltpowtable
    .ifs ( edi < 0 )

        neg edi
        add rsi,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if edi

        .for ( r12d = 0 : edi && r12d < MAX_EXP_INDEX : r12d++, edi >>= 1, rsi += EXTFLOAT )

            .if ( edi & 1 )

                _fltmul(rbx, rsi)
            .endif
        .endf

        .if ( edi != 0 )

            ; exponent overflow

            xor eax,eax
            mov [rbx].STRFLT.mantissa.l,rax
            mov [rbx].STRFLT.mantissa.h,rax
            mov [rbx].STRFLT.mantissa.e,0x7FFF
        .endif
    .endif
    mov rax,rbx
    ret

_fltscale endp

    assume rcx:ptr STRFLT

_fltround proc fastcall fp:ptr STRFLT

    mov rax,[rcx].mantissa.l
    .if eax & 0x4000

        mov rdx,[rcx].mantissa.h
        add rax,0x4000
        adc rdx,0
        .ifc
            rcr rdx,1
            rcr rax,1
            inc [rcx].mantissa.e
            .if [rcx].mantissa.e == Q_EXPMASK

                mov [rcx].mantissa.e,0x7FFF
                xor eax,eax
                xor edx,edx
            .endif
        .endif
        mov [rcx].mantissa.l,rax
        mov [rcx].mantissa.h,rdx
    .endif
    .return rcx

_fltround endp

_fltpackfp proc fastcall dst:ptr, src:ptr STRFLT

    _fltround(rdx)

    mov     rax,[rcx].mantissa.l
    mov     rdx,[rcx].mantissa.h
    mov     cx, [rcx].mantissa.e
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    mov     rcx,dst
    mov     [rcx],rax
    mov     [rcx+8],rdx
   .return  rcx

_fltpackfp endp

_fltunpack proc fastcall p:ptr STRFLT, q:ptr

    mov     rax,[rdx]
    mov     r8,[rdx+8]
    shld    r9,r8,16
    shld    r8,rax,16
    shl     rax,16
    mov     [rcx].mantissa.e,r9w
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     r8,1
    rcr     rax,1
    mov     [rcx].mantissa.l,rax
    mov     [rcx].mantissa.h,r8
    mov     rax,rcx
    ret

_fltunpack endp

    assume rcx: nothing
    assume rdi: ptr STRFLT

_fltsetflags proc __ccall uses rsi rdi fp:ptr STRFLT, string:string_t, flags:uint_t

    mov rdi,rcx
    mov rsi,rdx
    xor eax,eax
    mov [rdi].mantissa.l,rax
    mov [rdi].mantissa.h,rax
    mov [rdi].mantissa.e,ax
    mov [rdi].exponent,eax
    mov ecx,r8d
    or  ecx,_ST_ISZERO

    .repeat

        lodsb
        .break .if ( al == 0 )
        .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )
        dec rsi

        mov ecx,r8d
        .if ( al == '+' )

            inc rsi
            or  ecx,_ST_SIGN
        .endif

        .if ( al == '-' )

            inc rsi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or al,0x20
        .if ( al == 'n' )

            mov ax,[rsi]
            or  ax,0x2020

            .if ( ax == 'na' )

                add rsi,2
                or  ecx,_ST_ISNAN
                mov [rdi].mantissa.e,0xFFFF
                movzx eax,byte ptr [rsi]

                .if ( al == '(' )

                    lea rdx,[rsi+1]
                    mov al,[rdx]
                    .switch
                      .case al == '_'
                      .case al >= '0' && al <= '9'
                      .case al >= 'a' && al <= 'z'
                      .case al >= 'A' && al <= 'Z'
                        inc rdx
                        mov al,[rdx]
                        .gotosw
                    .endsw
                    .if al == ')'

                        lea rsi,[rdx+1]
                    .endif
                .endif
            .else
                dec rsi
                or  ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == 'i' )

            mov ax,[rsi]
            or  ax,0x2020

            .if ( ax == 'fn' )

                add rsi,2
                or  ecx,_ST_ISINF
            .else
                dec rsi
                or  ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == '0' )

            mov al,[rsi]
            or  al,0x20
            .if ( al == 'x' )

                or  ecx,_ST_ISHEX
                add rsi,2
            .endif
        .endif
        dec rsi

    .until 1

    mov [rdi].flags,ecx
    mov [rdi].string,rsi
    mov eax,ecx
    ret

_fltsetflags endp

    assume rdi:nothing

_destoflt proc fastcall fp:ptr STRFLT, buffer:string_t

  local digits:int_t, sigdig:int_t

    mov r10,rcx
    mov r8,rdx
    mov r11,[rcx].STRFLT.string
    mov ecx,[rcx].STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor r9d,r9d
    xor edx,edx

    .repeat

        .while 1

            mov al,[r11]
            inc r11
            .break .if !al

            .if ( al == '.' )

                .break .if ( ecx & _ST_DOT )
                or ecx,_ST_DOT

            .else

                .if ( ecx & _ST_ISHEX )

                    or al,0x20
                    .break .if al < '0' || al > 'f'
                    .break .if al > '9' && al < 'a'
                .else

                    .break .if ( al < '0' || al > '9' )
                .endif

                .if ( ecx & _ST_DOT )

                    inc sigdig
                .endif

                or ecx,_ST_DIGITS
                or edx,eax

                .continue .if edx == '0' ; if a significant digit

                .if r9d < Q_SIGDIG
                    mov [r8],al
                    inc r8
                .endif
                inc r9d
            .endif
        .endw
        mov byte ptr [r8],0
        mov digits,r9d

        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor r8d,r8d ; exponent

            .if ( ( ( ecx & _ST_ISHEX ) && ( al == 'p' || al == 'P' ) ) || \
                al == 'e' || al == 'E' )

                mov al,[r11]
                lea rdx,[r11-1]
                .if al == '+'
                    inc r11
                .endif
                .if al == '-'
                    inc r11
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1

                    movzx eax,byte ptr [r11]
                    .break .if al < '0'
                    .break .if al > '9'

                    .if r8d < 100000000 ; else overflow

                        lea r9,[r8*8]
                        lea r8,[r8*2+r9-'0']
                        add r8,rax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc r11
                .endw

                .if ( ecx & _ST_NEGEXP )
                    neg r8d
                .endif
                .if !( ecx & _ST_DIGITS )
                    mov r11,rdx
                .endif

            .else

                dec r11 ; digits found, but no e or E
            .endif

            mov edx,r8d
            mov eax,sigdig
            mov r9d,digits
            mov r8d,Q_DIGITS

            .if ( ecx & _ST_ISHEX )

                mov r8d,32
                shl eax,2
            .endif
            sub edx,eax

            mov eax,1
            .if ( ecx & _ST_ISHEX )

                mov eax,4
            .endif

            .if ( r9d > r8d )

                add edx,r9d
                mov r9d,r8d
                .if ( ecx & _ST_ISHEX )

                    shl r8d,2
                .endif
                sub edx,r8d
            .endif

            mov r8,buffer
            .while 1

                .break .ifs r9d <= 0
                .break .if byte ptr [r8+r9-1] != '0'

                add edx,eax
                dec r9d
            .endw
            mov digits,r9d
        .else
            mov r11,[r10].STRFLT.string
        .endif

    .until 1

    mov [r10].STRFLT.flags,ecx
    mov [r10].STRFLT.string,r11
    mov [r10].STRFLT.exponent,edx
    mov eax,digits
    ret

_destoflt endp

_strtoflt proc fastcall string:string_t

  local buffer[256]:char_t
  local digits:int_t
  local sign:int_t

    .repeat

        _fltsetflags(&lflt, rcx, 0)
        .break .if eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID

        mov digits,_destoflt(&lflt, &buffer)

        .if ( eax == 0 )

            or lflt.flags,_ST_ISZERO
            .break
        .endif
        mov buffer[rax],0

        ;
        ; convert string to binary
        ;
        lea rdx,buffer
        xor eax,eax
        mov al,[rdx]
        mov sign,eax

        .if ( al == '+' || al == '-' )

            inc rdx
        .endif

        mov r8d,16
        .if !( lflt.flags & _ST_ISHEX )

            mov r8d,10
        .endif
        lea r10,lflt.mantissa
        mov r11,r10
        .while 1

            mov al,[rdx]
            .break .if !al

            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
            .repeat
                movzx r9d,word ptr [r11]
                imul  r9d,r8d
                add   eax,r9d
                mov   [r11],ax
                add   r11,2
                shr   eax,16
            .untilcxz
            sub r11,16
            inc rdx
        .endw

        mov rax,[r10]
        mov rdx,[r10+8]

        xor ecx,ecx
        mov r8d,Q_EXPBIAS

        .if rax || rdx
            .if rdx         ; find most significant non-zero bit
                bsr rcx,rdx
                add ecx,64
            .else
                bsr rcx,rax
            .endif
            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch
            .if cl >= 64
                sub cl,64
                mov rdx,rax
                xor eax,eax
            .endif
            shld rdx,rax,cl
            shl rax,cl
            shr ecx,8       ; get shift count
            add ecx,r8d     ; calculate exponent
            mov [r10],rax
            mov [r10+8],rdx
        .else
            or lflt.flags,_ST_ISZERO
        .endif
        mov r9d,lflt.flags
        .if ( sign == '-' || r9d & _ST_NEGNUM )
            or cx,0x8000
        .endif

        mov r8d,ecx
        and r8d,Q_EXPMASK
        .switch
          .case r9d & _ST_ISNAN or _ST_ISINF or _ST_INVALID or _ST_UNDERFLOW or _ST_OVERFLOW
          .case r8d >= Q_EXPMAX + Q_EXPBIAS
            or  ecx,0x7FFF
            xor eax,eax
            mov lflt.mantissa.l,rax
            mov lflt.mantissa.h,rax
            .if r9d & _ST_ISNAN or _ST_INVALID
                or ecx,0x8000
                or byte ptr lflt.mantissa.h[7],0x80
            .endif
        .endsw
        mov lflt.mantissa.e,cx

        and ecx,Q_EXPMASK
        .if ecx >= 0x7FFF

            mov qerrno,ERANGE

        .elseif ( lflt.exponent && !( lflt.flags & _ST_ISHEX ) )

            _fltscale(&lflt)
        .endif

        mov eax,lflt.exponent
        add eax,digits
        dec eax
        .ifs eax > 4932
            or lflt.flags,_ST_OVERFLOW
        .endif
        .ifs eax < -4932
            or lflt.flags,_ST_UNDERFLOW
        .endif

    .until 1
    _fltpackfp(&lflt, &lflt)
    ret

_strtoflt endp


;-------------------------------------------------------------------------------
; _flttostr() - Converts quad float to string
;-------------------------------------------------------------------------------

define STK_BUF_SIZE    512 ; ANSI-specified minimum is 509
define NDIG            16

define D_CVT_DIGITS    20
define LD_CVT_DIGITS   23
define QF_CVT_DIGITS   33

define E16_EXP         0x4034
define E16_HIGH        0x8E1BC9BF
define E16_LOW         0x04000000
define E32_EXP         0x4069
define E32_HIGH        (0x80000000 or (0x3B8B5B50 shr 1))
define E32_LOW         (0x56E16B3B shr 1)

    assume rbx:ptr FLTINFO

_flttostr proc fastcall uses rsi rdi rbx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local i      :int_t
  local n      :int_t
  local nsig   :int_t
  local xexp   :int_t
  local maxsize:int_t
  local digits :int_t
  local flt    :STRFLT
  local tmp    :STRFLT
  local stkbuf[STK_BUF_SIZE]:char_t
  local endbuf :ptr

    mov rbx,cvt
    mov eax,[rbx].bufsize
    add rax,buf
    dec rax
    mov endbuf,rax
    mov eax,D_CVT_DIGITS
    .if r9d & _ST_LONGDOUBLE
        mov eax,LD_CVT_DIGITS
    .elseif r9d & _ST_QUADFLOAT
        mov eax,QF_CVT_DIGITS
    .endif
    mov digits,eax

    mov rbx,rdx
    xor eax,eax
    mov [rbx].n1,eax
    mov [rbx].nz1,eax
    mov [rbx].n2,eax
    mov [rbx].nz2,eax
    mov [rbx].dec_place,eax

    _fltunpack(&flt, q)

    mov ax,flt.mantissa.e
    bt  eax,15
    sbb ecx,ecx
    mov [rbx].sign,ecx
    and eax,Q_EXPMASK   ; make number positive
    mov flt.mantissa.e,ax

    movzx ecx,ax
    lea rdi,flt
    xor eax,eax
    mov flt.flags,eax

    .if ecx == Q_EXPMASK

        ; NaN or Inf

        or rax,flt.mantissa.l
        or rax,flt.mantissa.h
        .ifz

            ; INFINITY

            mov eax,'fni'
            or  [rbx].flags,_ST_ISINF
        .else

            ; NaN

            mov eax,'nan'
            or  [rbx].flags,_ST_ISNAN
        .endif

        .if flags & _ST_CAPEXP

            and eax,NOT 0x202020
        .endif
        mov rcx,buf
        mov [rcx],eax
        mov [rbx].n1,3
       .return 64
    .endif

    .if !ecx

        ; ZERO/DENORMAL

        mov [rbx].sign,eax ; force sign to +0.0
        mov xexp,eax
        mov flt.flags,_ST_ISZERO

    .else

        mov  esi,ecx
        sub  ecx,0x3FFE
        mov  eax,30103
        imul ecx
        mov  ecx,100000
        idiv ecx
        sub  eax,NDIG / 2
        mov  xexp,eax

        .if eax

            .ifs

                ; scale up

                neg eax
                add eax,NDIG / 2 - 1
                and eax,NOT (NDIG / 2 - 1)
                neg eax
                mov xexp,eax
                neg eax
                mov flt.exponent,eax

                _fltscale(&flt)

            .else

                mov eax,[rdi+8]
                mov edx,[rdi+12]

                .if ( esi < E16_EXP || ( ( esi == E16_EXP && ( edx < E16_HIGH || \
                    ( edx == E16_HIGH && eax < E16_LOW ) ) ) ) )

                    ; number is < 1e16

                    mov xexp,0

                .else
                    .if ( esi < E32_EXP || ( ( esi == E32_EXP && ( edx < E32_HIGH || \
                        ( edx == E32_HIGH && eax < E32_LOW ) ) ) ) )

                        ; number is < 1e32

                        mov xexp,16
                    .endif

                    ; scale number down

                    mov eax,xexp
                    and eax,NOT (NDIG / 2 - 1)
                    mov xexp,eax
                    neg eax
                    mov flt.exponent,eax
                    _fltscale(&flt)
                .endif
            .endif
        .endif
    .endif

    mov eax,[rbx].ndigits
    .if [rbx].flags & _ST_F
        add eax,xexp
        add eax,2 + NDIG
        .ifs [rbx].scale > 0
            add eax,[rbx].scale
        .endif
    .else
        add eax,NDIG + NDIG / 2 ; need at least this for rounding
    .endif
    .if eax > STK_BUF_SIZE-1-NDIG
        mov eax,STK_BUF_SIZE-1-NDIG
    .endif
    mov n,eax

    mov ecx,digits
    add ecx,NDIG / 2
    mov maxsize,ecx

    ; convert quad into string of digits
    ; put in leading '0' in case we round 99...99 to 100...00

    lea rdi,stkbuf
    mov word ptr [rdi],'0'
    inc rdi
    xor esi,esi
    mov i,esi

    .while ( n > 0 )

        sub n,NDIG

        .if ( rsi == 0 )

            ; get value to subtract

            mov rsi,_flttoi64(&flt)
            .ifs ( n > 0 )
                _i64toflt(&tmp, rsi)
                _fltsub(&flt, &tmp)
                _fltmul(&flt, &EXQ_1E16)
            .endif
        .endif

        mov ecx,NDIG
        .if rsi
            .for ( rax = rsi, r8d = 10 : ecx : ecx-- )
                xor edx,edx
                div r8
                add dl,'0'
                mov [rdi+rcx-1],dl
            .endf
            add rdi,NDIG
        .else
            mov al,'0'
            rep stosb
        .endif
        add i,NDIG
        xor esi,esi
    .endw

    ; get number of characters in buf

    ; skip over leading zeros

    .for ( eax = i,
           edx = STK_BUF_SIZE-2,
           rsi = &stkbuf[1],
           ecx = xexp,
           ecx += NDIG-1 : edx && byte ptr [rsi] == '0' : eax--, ecx--, edx--, rsi++ )
    .endf

    mov n,eax
    mov rbx,cvt
    mov edx,[rbx].ndigits

    .if ( [rbx].flags & _ST_F )
        add ecx,[rbx].scale
        lea edx,[rdx+rcx+1]
    .elseif ( [rbx].flags & _ST_E )
        .ifs ( [rbx].scale > 0 )
            inc edx
        .else
            add edx,[rbx].scale
        .endif
        inc ecx             ; xexp = xexp + 1 - scale
        sub ecx,[rbx].scale
    .endif

    .ifs ( edx >= 0 )       ; round and strip trailing zeros
        .ifs edx > eax
            mov edx,eax     ; nsig = n
        .endif
        mov eax,digits
        .ifs edx > eax
            mov edx,eax
        .endif
        mov maxsize,eax
        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [rsi+rdx] >= '5' ) || \
            ( edx == digits && byte ptr [rsi+rdx-1] == '9' ) )
            mov al,'9'
        .endif

        mov r8d,[rbx].scale
        add r8d,[rbx].ndigits
        .if ( al == '9' && edx == r8d && \
            byte ptr [rsi+rdx] != '9' &&  byte ptr [rsi+rdx-1] == '9' )
            .while r8d
                dec r8d
                .break .if byte ptr [rsi+r8] != '9'
            .endw
            .if byte ptr [rsi+r8] == '9'
                 mov al,'0'
            .endif
        .endif

        lea rdi,[rsi+rdx-1]
        xchg ecx,edx
        inc ecx
        std
        repz scasb
        cld
        xchg ecx,edx
        inc rdi
        .if al == '9'       ; round up
            inc byte ptr [rdi]
        .endif
        sub rdi,rsi
        .ifs
            dec rsi         ; repeating 9's rounded up to 10000...
            inc edx
            inc ecx
        .endif
    .endif

    .ifs edx <= 0 || flt.flags == _ST_ISZERO

        mov edx,1           ; nsig = 1
        xor ecx,ecx         ; xexp = 0
        mov stkbuf,'0'
        mov [rbx].sign,ecx
        lea rsi,stkbuf
    .endif

    mov i,0
    mov eax,[rbx].flags
    mov r9,buf
    xor r8d,r8d
    mov r10d,[rbx].ndigits

    .ifs ( eax & _ST_F || ( eax & _ST_G && ( ( ecx >= -4 && ecx < r10d ) || eax & _ST_CVT ) ) )

        mov rdi,r9
        inc ecx
        mov r11d,eax

        .if eax & _ST_G
            .ifs ( edx < r10d && !( eax & _ST_DOT ) )
                mov r10d,edx
            .endif
            sub r10d,ecx
            .ifs ( r10d < 0 )
                mov r10d,0
            .endif
        .endif

        .ifs ( ecx <= 0 ) ; digits only to right of '.'

            .if !( eax & _ST_CVT )

                mov byte ptr [rdi],'0'
                inc r8d

                .ifs ( r10d > 0 || eax & _ST_DOT )
                    mov byte ptr [rdi+1],'.'
                    inc r8d
                .endif
            .endif

            mov [rbx].n1,r8d
            mov eax,ecx
            neg eax
            .ifs ( r10d < eax )
                mov ecx,r10d
                neg ecx
            .endif
            mov eax,ecx
            neg eax
            mov [rbx].dec_place,eax
            mov [rbx].nz1,eax
            add r10d,ecx
            .ifs ( r10d < edx )
                mov edx,r10d
            .endif
            mov [rbx].n2,edx
            sub edx,r10d
            neg edx
            mov [rbx].nz2,edx
            mov ecx,[rbx].n1    ; number of leading characters
            add rdi,rcx

            mov ecx,[rbx].nz1   ; followed by this many '0's
            mov eax,[rbx].n2
            add eax,[rbx].nz2
            add eax,ecx
            lea rax,[rdi+rax]
            cmp rax,endbuf
            ja  overflow

            add r8d,ecx
            mov al,'0'
            rep stosb
            mov ecx,[rbx].n2    ; followed by these characters
            add r8d,ecx
            rep movsb
            mov ecx,[rbx].nz2   ; followed by this many '0's
            add r8d,ecx
            rep stosb

        .elseifs ( edx < ecx )  ; zeros before '.'

            add r8d,edx
            mov [rbx].n1,edx
            mov eax,ecx
            sub eax,edx
            mov [rbx].nz1,eax
            mov [rbx].dec_place,ecx
            mov ecx,edx
            rep movsb

            lea rcx,[rdi+rax+2]
            cmp rcx,endbuf
            ja  overflow
            mov ecx,eax
            mov eax,'0'
            add r8d,ecx
            rep stosb

            mov ecx,r10d
            .if !( r11d & _ST_CVT )

                .ifs ( ecx > 0 || r11d & _ST_DOT )

                    mov byte ptr [rdi],'.'
                    inc rdi
                    inc r8d
                    mov [rbx].n2,1
                .endif
            .endif

            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow
            mov [rbx].nz2,ecx
            add r8d,ecx
            rep stosb

        .else ; enough digits before '.'

            mov [rbx].dec_place,ecx
            add r8d,ecx
            sub edx,ecx
            rep movsb
            mov rdi,r9
            mov ecx,[rbx].dec_place

            .if !( r11d & _ST_CVT )

                .ifs ( r10d > 0 || r11d & _ST_DOT )

                    mov byte ptr [rdi+r8],'.'
                    inc r8d
                .endif

            .elseif byte ptr [rdi] == '0' ; ecvt or fcvt with 0.0

                mov [rbx].dec_place,0
            .endif

            .ifs ( r10d < edx )

                mov edx,r10d
            .endif

            add rdi,r8
            mov ecx,edx
            rep movsb
            add r8d,edx
            mov [rbx].n1,r8d
            mov eax,edx
            mov ecx,r10d
            add edx,ecx
            mov [rbx].nz1,edx
            sub ecx,eax
            add r8d,ecx
            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow
            mov eax,'0'
            rep stosb

        .endif
        mov byte ptr [r9+r8],0
        mov [rbx].ndigits,r10d

    .else

        mov eax,[rbx].ndigits
        .ifs [rbx].scale <= 0
            add eax,[rbx].scale   ; decrease number of digits after decimal
        .else
            sub eax,[rbx].scale   ; adjust number of digits (see fortran spec)
            inc eax
        .endif

        xor r8d,r8d

        .if [rbx].flags & _ST_G

            ; fixup for 'G'
            ; for 'G' format, ndigits is the number of significant digits
            ; cvt->scale should be 1 indicating 1 digit before decimal place
            ; so decrement ndigits to get number of digits after decimal place

            .if ( edx < eax && !( [rbx].flags & _ST_DOT) )
                mov eax,edx
            .endif
            dec eax
            .ifs eax < 0
                xor eax,eax
            .endif
        .endif

        mov [rbx].ndigits,eax
        mov xexp,ecx
        mov r10d,edx
        mov rdi,r9

        .ifs [rbx].scale <= 0

            mov byte ptr [r9],'0'
            inc r8d
            .if ecx >= maxsize
                inc xexp
            .endif

        .else

            mov eax,[rbx].scale
            .if eax > edx
                mov eax,edx
            .endif

            mov edx,eax
            add rdi,r8          ; put in leading digits
            mov ecx,eax
            mov rax,rsi
            rep movsb
            mov rsi,rax
            add r8d,edx
            add rsi,rdx
            sub r10d,edx
            .ifs edx < [rbx].scale    ; put in zeros if required
                mov ecx,[rbx].scale
                sub ecx,edx
                add r8d,ecx
                lea rdi,[r9+r8]
                mov al,'0'
                rep stosb
            .endif
        .endif
        mov [rbx].dec_place,r8d

        mov eax,[rbx].ndigits
        .if !( [rbx].flags & _ST_CVT )

            .ifs ( eax > 0 || [rbx].flags & _ST_DOT )

                mov byte ptr [r9+r8],'.'
                inc r8d
            .endif
        .endif

        mov ecx,[rbx].scale
        .ifs ecx < 0
            neg ecx
            lea rdi,[r9+r8]
            add r8d,ecx
            mov al,'0'
            rep stosb
        .endif
        mov ecx,r10d
        mov eax,[rbx].ndigits

        .ifs eax > 0        ; put in fraction digits

            .ifs eax < ecx
                mov ecx,eax
                mov r10d,eax
            .endif
            .if ecx
                lea rdi,[r9+r8]
                add r8d,ecx
                rep movsb
            .endif
            mov [rbx].n1,r8d
            mov ecx,[rbx].ndigits
            sub ecx,r10d
            mov [rbx].nz1,ecx
            lea rdi,[r9+r8]
            add r8d,ecx
            mov eax,'0'
            rep stosb
        .endif
        mov eax,[rbx].expchar
        .if al
            mov [r9+r8],al
            inc r8d
        .endif
        mov edi,xexp
        .ifs edi >= 0
            mov byte ptr [r9+r8],'+'
        .else
            mov byte ptr [r9+r8],'-'
            neg edi
        .endif
         inc r8d
         mov eax,edi

         mov ecx,[rbx].expwidth
         .switch ecx
          .case 0           ; width unspecified
            mov ecx,3
            .ifs eax >= 1000
                mov ecx,4
            .endif
            .endc
          .case 1
            .ifs eax >= 10
                mov ecx,2
            .endif
          .case 2
            .ifs eax >= 100
                mov ecx,3
            .endif
          .case 3
            .ifs eax >= 1000
                mov ecx,4
            .endif
            .endc
         .endsw
         mov [rbx].expwidth,ecx    ; pass back width actually used

         .if ecx >= 4
            xor esi,esi
            .if eax >= 1000
                mov ecx,1000
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub edi,eax
                mov ecx,[rbx].expwidth
            .endif
            lea eax,[rsi+'0']
            mov [r9+r8],al
            inc r8d
         .endif

         .if ecx >= 3
            xor esi,esi
            mov eax,edi
            .ifs edi >= 100
                mov ecx,100
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub edi,eax
                mov ecx,[rbx].expwidth
            .endif
            lea rax,[rsi+'0']
            mov [r9+r8],al
            inc r8d
         .endif

         .if ecx >= 2
            xor esi,esi
            mov eax,edi
            .ifs edi >= 10
                mov ecx,10
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub edi,eax
                mov ecx,[rbx].expwidth
            .endif
            lea rax,[rsi+'0']
            mov [r9+r8],al
            inc r8d
         .endif

         lea rax,[rdi+'0']
         mov [r9+r8],al
         inc r8d
         mov eax,r8d
         sub eax,[rbx].n1
         mov [rbx].n2,eax
         xor eax,eax
         mov [r9+r8],al
    .endif
toend:
    ret
overflow:
    mov rdi,buf
    lea rsi,e_space
    mov ecx,sizeof(e_space)
    rep movsb
    jmp toend

_flttostr endp

    assume rbx:nothing

__addq proc fastcall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, rcx)
    _fltunpack(&b, src)
    _fltadd(&a, &b)
    _fltpackfp(dest, &a)
    ret

__addq endp

__subq proc fastcall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, rcx)
    _fltunpack(&b, src)
    _fltsub(&a, &b)
    _fltpackfp(dest, &a)
    ret

__subq endp

__mulq proc fastcall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, rcx)
    _fltunpack(&b, src)
    _fltmul(&a, &b)
    _fltpackfp(dest, &a)
    ret

__mulq endp

__divq proc fastcall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, rcx)
    _fltunpack(&b, src)
    _fltdiv(&a, &b)
    _fltpackfp(dest, &a)
    ret

__divq endp

    assume rcx:ptr U128
    assume rdx:ptr U128

__cmpq proc fastcall A:ptr, B:ptr

    .return 0 .if ( [rcx].u64[0] == [rdx].u64[0] && \
                    [rcx].u64[8] == [rdx].u64[8] )
    .return 1 .if ( [rcx].i8[15] >= 0 && [rdx].i8[15] < 0 )
    .return -1 .if( [rcx].i8[15] < 0 && [rdx].i8[15] >= 0 )

    .if ( [rcx].i8[15] < 0 && [rdx].i8[15] < 0 )
        .if ( [rdx].u64[8] == [rcx].u64[8] )
            mov rax,[rcx].u64
            cmp [rdx].u64,rax
        .endif
    .elseif ( [rcx].u64[8] == [rdx].u64[8] )
        mov rax,[rdx].u64
        cmp [rcx].u64,rax
    .endif
    sbb eax,eax
    sbb eax,-1
    ret

__cmpq endp

    assume rcx:nothing
    assume rdx:nothing

; Convert HALF, float, double, long double, string

__cvta_q proc fastcall number:ptr, strptr:string_t, endptr:ptr string_t

    _strtoflt(rdx)
    mov rcx,endptr
    .if rcx
        mov rdx,[rax].STRFLT.string
        mov [rcx],rdx
    .endif
    mov rcx,[rax].STRFLT.mantissa.l
    mov rdx,[rax].STRFLT.mantissa.h
    mov rax,number
    mov [rax],rcx
    mov [rax+8],rdx
    ret

__cvta_q endp

__cvth_q proc fastcall q:ptr, h:ptr

    movsx   edx,word ptr [rdx]
    mov     ecx,edx             ; get exponent and sign
    shl     edx,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if (edx & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                mov qerrno,EDOM
                mov ecx,0xFFFF
                mov edx,0x40000000 ; QNaN
            .else
                xor edx,edx
            .endif
        .endif
    .elseif edx
        or cx,Q_EXPBIAS-H_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test edx,edx
            .break .ifs
            shl edx,1
            dec cx
        .endw
    .endif

    shl     ecx,1
    rcr     cx,1
    shl     rdx,33
    shld    rcx,rdx,64-16
    mov     rax,q
    mov     [rax+8],rcx
    xor     edx,edx
    mov     [rax],rdx
    ret

__cvth_q endp

__cvtld_q proc fastcall x:ptr, ld:ptr

    mov     rax,[rdx]
    movzx   edx,word ptr [rdx+8]
    add     dx,dx
    rcr     dx,1
    shl     rax,1
    shld    rdx,rax,64-16
    shl     rax,64-16
    mov     [rcx],rax
    mov     [rcx+8],rdx
    mov     rax,rcx
    ret

__cvtld_q endp

__cvtsd_q proc fastcall q:ptr, d:ptr

    mov     rax,rcx
    mov     r9,[rdx]
    mov     rdx,r9
    shl     r9,11
    sar     rdx,64-12
    and     dx,0x7FF
    jz      .1
    mov     r8,0x8000000000000000
    or      r9,r8
    cmp     dx,0x7FF
    je      .2
    add     dx,0x3FFF-0x03FF
.0:
    add     edx,edx
    rcr     dx,1
    shl     r9,1
    xor     ecx,ecx
    shrd    rcx,r9,16
    shrd    r9,rdx,16
    mov     [rax],rcx
    mov     [rax+8],r9
    ret
.1:
    test    r9,r9
    jz      .0
    or      edx,0x3FFF-0x03FF+1
    bsr     r8,r9
    mov     ecx,63
    sub     ecx,r8d
    shl     r9,cl
    sub     dx,cx
    jmp     .0
.2:
    or      dh,0x7F
    not     r8
    test    r9,r8
    jz      .0
    not     r8
    shr     r8,1
    or      r9,r8
    jmp     .0

__cvtsd_q endp

__cvtss_q proc fastcall q:ptr, f:ptr

    mov rax,rcx
    mov edx,[rdx]
    mov ecx,edx     ; get exponent and sign
    shl edx,8       ; shift fraction into place
    sar ecx,32-9    ; shift to bottom
    xor ch,ch       ; isolate exponent
    .if cl
        .if cl != 0xFF
            add cx,0x3FFF-0x7F
        .else
            or ch,0xFF
            .if !( edx & 0x7FFFFFFF )

                ; Invalid exception

                or edx,0x40000000 ; QNaN
                mov qerrno,EDOM
            .endif
        .endif
        ;or edx,0x80000000
    .elseif edx
        or cx,0x3FFF-0x7F+1 ; set exponent
        .while 1

            ; normalize number

            test edx,edx
            .break .ifs
            shl edx,1
            dec cx
        .endw
    .endif
    shl     rdx,1+32
    add     ecx,ecx
    rcr     cx,1
    shrd    rdx,rcx,16
    xor     ecx,ecx
    mov     [rax],rcx
    mov     [rax+8],rdx
    ret

__cvtss_q endp

define HFLT_MAX 0x7BFF
define HFLT_MIN 0x0001

__cvtq_h proc fastcall private h:ptr, q:ptr

    mov     r8,[rdx+8]
    mov     rdx,[rdx]
    xor     eax,eax
    mov     [rcx],rax
    mov     [rcx+8],rax
    mov     rax,rcx
    shld    rcx,r8,16
    rol     rdx,16
    shl     r8,16
    shld    rdx,r8,16
    shr     r8,32
    shr     r8d,1
    test    ecx,Q_EXPMASK
    jz      .1
    or      r8d,0x80000000
.1:
    mov     r9d,r8d         ; duplicate it
    shl     r9d,H_SIGBITS+1 ; get rounding bit
    mov     r9d,0xFFE00000  ; get mask of bits to keep
    jnc     .3              ; if have to round
    jnz     .2              ; - if half way between
    test    edx,edx
    jnz     .2
    shl     r9d,1
.2:
    add     r8d,0x80000000 shr (H_SIGBITS-1)
    jnc     .3              ; - if exponent needs adjusting
    mov     r8d,0x80000000
    inc     cx
    ;
    ;  check for overflow
    ;
.3:
    mov     edx,ecx         ; save exponent and sign
    and     cx,Q_EXPMASK    ; if number not 0
    jz      .7
    cmp     cx,Q_EXPMASK
    jne     .5
    test    r8d,0x7FFFFFFF
    jz      .4
    mov     r8d,-1
    jmp     .8
.4:
    mov     r8d,0x7C000000 shl 1
    shl     dx,1
    rcr     r8d,1
    jmp     .8
.5:
    add     cx,H_EXPBIAS-Q_EXPBIAS
    js      .underflow
    cmp     cx,H_EXPMASK
    jae     .overflow
    cmp     cx,H_EXPMASK-1
    jne     .6
    cmp     r8d,r9d
    ja      .overflow
.6:
    and     r8d,r9d ; mask off bottom bits
    shl     r8d,1
    shrd    r8d,ecx,H_EXPBITS
    shl     dx,1
    rcr     r8d,1
    test    cx,cx
    jnz     .8
    cmp     r8d,HFLT_MIN
    jl      .error
.7:
    and     r8d,r9d
.8:
    shr     r8d,16
    mov     [rax],r8w
    ret
.underflow:
    mov     r8d,0x00010000
    jmp     .error
.overflow:
    mov     r8d,0x7BFF0000 shl 1
    shl     dx,1
    rcr     r8d,1
.error:
    mov     qerrno,ERANGE
    jmp     .8
__cvtq_h endp

define DDFLT_MAX 0x7F7FFFFF
define DDFLT_MIN 0x00800000

__cvtq_ss proc fastcall f:ptr, q:ptr

    mov     r10,[rdx]
    mov     rax,[rdx+8]
    shld    rdx,rax,16
    shrd    r10,rax,16
    shr     rax,16

    mov     r9d,0xFFFFFF00  ; get mask of bits to keep
    mov     r8w,dx
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     eax,1
    mov     r8d,eax         ; duplicate it
    shl     r8d,25          ; get rounding bit
    mov     r8w,dx          ; get exponent and sign
    jnc     .1              ; if have to round
    jnz     .0              ; - if half way between
    test    r10d,r10d
    jnz     .0
    shl     r9d,1
.0:
    add     eax,0x0100
    jnc     .1              ; - if exponent needs adjusting
    mov     eax,0x80000000
    inc     r8w
.1:
    and     eax,r9d         ; mask off bottom bits
    mov     r9d,r8d         ; save exponent and sign
    and     r8w,0x7FFF      ; if number not 0
    jz      .done
    cmp     r8w,0x7FFF
    jne     .2
    shl     eax,1           ; infinity or NaN
    shr     eax,8
    or      eax,0xFF000000
    shl     r9w,1
    rcr     eax,1
    jmp     .done
.2:
    add     r8w,0x07F-0x3FFF
    js      .underflow
    cmp     r8w,0x00FF
    jge     .overflow
    shl     eax,1
    shrd    eax,r8d,8
    shl     r9w,1
    rcr     eax,1
    test    r8w,r8w
    jnz     .done
    cmp     eax,DDFLT_MIN
    jl      .error
.done:
    mov     [rcx],rax
    xor     eax,eax
    mov     [rcx+8],rax
    mov     rax,rcx
    ret
.underflow:
    xor     eax,eax
.error:
    mov     qerrno,ERANGE
    jmp     .done
.overflow:
    mov     eax,0x7F800000 shl 1
    shl     r9w,1
    rcr     eax,1
    jmp     .error

__cvtq_ss endp

__cvtq_sd proc fastcall d:ptr, q:ptr

    push    rcx
    mov     rax,[rdx+8]
    mov     rdx,[rdx]
    shld    rcx,rax,16
    shld    rax,rdx,16
    movzx   ecx,cx

    mov     r10,rax
    mov     r8d,ecx
    and     r8d,Q_EXPMASK
    mov     r9d,r8d
    neg     r8d
    rcr     rax,1
    mov     rdx,rax
    shr     rdx,32
    mov     r8d,eax
    shl     r8d,22
    jnc     .1
    jnz     .0
    add     r8d,r8d
.0:
    add     eax,0x0800
    adc     edx,0
    jnc     .1
    mov     edx,0x80000000
    inc     cx
.1:
    and     eax,0xFFFFF800
    mov     r8d,ecx
    and     cx,0x7FFF
    add     cx,0x03FF-0x3FFF

    cmp     cx,0x07FF
    jnb     .4
    test    cx,cx
    jnz     .2

    shrd    eax,edx,12
    shl     edx,1
    shr     edx,12
    jmp     .3
.2:
    shrd    eax,edx,11
    shl     edx,1
    shrd    edx,ecx,11
.3:
    shl     r8w,1
    rcr     edx,1
    jmp     .8
.4:
    cmp     cx,0xC400
    jb      .7
    cmp     cx,-52
    jl      .6
    mov     r8d,0xFFFFF800
    sub     cx,12
    neg     cx
    cmp     cl,32
    jb      .5
    sub     cl,32
    mov     r8d,eax
    mov     eax,edx
    xor     edx,edx
.5:
    shrd    r8d,eax,cl
    shrd    eax,edx,cl
    shr     edx,cl
    add     r8d,r8d
    adc     eax,0
    adc     edx,0
    jmp     .8
.6:
    xor     eax,eax
    xor     edx,edx
    shl     r8d,17
    rcr     edx,1
    jmp     .8
.7:
    shrd    eax,edx,11
    shl     edx,1
    shr     edx,11
    shl     r8w,1
    rcr     edx,1
    or      edx,0x7FF00000
.8:
    xor     ecx,ecx
    cmp     r9d,0x3BCC
    jnb     .10
    test    r10,r10
    jnz     .9
    test    r9d,r9d
    jz      .12
.9:
    xor     eax,eax
    xor     edx,edx
    mov     ecx,ERANGE
    jmp     .12
.10:
    cmp     r9d,0x3BCD
    jb      .11
    mov     r9d,edx
    and     r9d,0x7FF00000
    mov     ecx,ERANGE
    jz      .12
    cmp     r9d,0x7FF00000
    je      .12
    xor     ecx,ecx
    jmp     .12
.11:
    cmp     r9d,0x3BCC
    jb      .12
    mov     r9d,edx
    or      r9d,eax
    mov     ecx,ERANGE
    jz      .12
    mov     r9d,edx
    and     r9d,0x7FF00000
    jz      .12
    xor     ecx,ecx
.12:
    shl     rdx,32
    or      rdx,rax
    test    ecx,ecx
    jz      .13
    mov     qerrno,ecx
.13:
    xor     ecx,ecx
    pop     rax
    mov     [rax],rdx
    mov     [rax+8],rcx
    ret

__cvtq_sd endp

__cvtq_ld proc fastcall ld:ptr, q:ptr

    xor     r8d,r8d
    mov     rax,[rdx]
    mov     rdx,[rdx+8]
    shld    r8,rdx,16
    shld    rdx,rax,16
    mov     eax,r8d
    and     eax,LD_EXPMASK
    neg     eax
    mov     rax,rdx
    rcr     rax,1
    jnc     .1
    cmp     rax,-1  ; round result
    jne     .0
    mov     rax,0x8000000000000000
    inc     r8w
    jmp     .1
.0:
    inc     rax
.1:
    mov     [rcx],rax
    mov     [rcx+8],r8
    mov     rax,rcx
    ret

__cvtq_ld endp

_atoow proc fastcall dst:string_t, src:string_t, radix:int_t, bsize:int_t

    push    rcx
    mov     r11,rdx
    xor     edx,edx
    mov     [rcx],rdx
    mov     [rcx+8],rdx
    xor     ecx,ecx

ifdef CHEXPREFIX
    movzx   eax,word ptr [r11]
    or      eax,0x2000
    cmp     eax,'x0'
    jne     .0
    add     r11,2
    sub     r9d,2
.0:
endif

    cmp     r8d,16
    jne     .2

    ; hex value

.1:
    movzx   eax,byte ptr [r11]
    inc     r11
    and     eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
    bt      eax,6           ; digit ?
    sbb     r8d,r8d         ; -1 : 0
    and     r8d,0x37        ; 10 = 0x41 - 0x37
    sub     eax,r8d
    shld    rdx,rcx,4
    shl     rcx,4
    add     rcx,rax
    dec     r9d
    jnz     .1
    jmp     .8

.2:
    cmp     r8d,10
    jne     .5
.3:
    mov     cl,[r11]
    inc     r11
    sub     cl,'0'
.4:
    dec     r9d
    jz      .8

    mov     r8,rdx
    mov     rax,rcx
    shld    rdx,rcx,3
    shl     rcx,3
    add     rcx,rax
    adc     rdx,r8
    add     rcx,rax
    adc     rdx,r8
    movzx   eax,byte ptr [r11]
    inc     r11
    sub     al,'0'
    add     rcx,rax
    adc     rdx,0
    jmp     .4

.5:
    mov     r10,[rsp]
.6:
    movzx   eax,byte ptr [r11]
    and     eax,not 0x30
    bt      eax,6
    sbb     ecx,ecx
    and     ecx,0x37
    sub     eax,ecx
    mov     ecx,8
.7:
    movzx   edx,word ptr [r10]
    imul    edx,r8d
    add     eax,edx
    mov     [r10],ax
    add     r10,2
    shr     eax,16
    dec     ecx
    jnz     .7
    sub     r10,16
    inc     r11
    dec     r9d
    jnz     .6
    pop     rax
    jmp     .9
.8:
    pop     rax
    mov     [rax],rcx
    mov     [rax+8],rdx
.9:
    ret

_atoow endp

atofloat proc fastcall _out:ptr, inp:string_t, size:uint_t, negative:int_t, ftype:uchar_t

    mov qerrno,0

    ;; v2.04: accept and handle 'real number designator'

    .if ( ftype )

        ;; convert hex string with float "designator" to float.
        ;; this is supposed to work with real4, real8 and real10.
        ;; v2.11: use _atoow() for conversion ( this function
        ;;    always initializes and reads a 16-byte number ).
        ;;    then check that the number fits in the variable.

        lea eax,[tstrlen(inp)-1]
        mov negative,eax

        ;; v2.31.24: the size is 2,4,8,10,16
        ;; real4 3ff0000000000000r is allowed: real8 -> real16 -> real4

        .switch eax
        .case 4,8,16,20,32
            .endc
        .case 5,9,17,21,33
            mov rcx,inp
            .if byte ptr [rcx] == '0'
                inc inp
                dec negative
                .endc
            .endif
        .default
            asmerr( 2104, inp )
        .endsw

        _atoow( _out, inp, 16, negative )
        mov eax,size
        .for ( rcx = _out, rdx = rcx, rcx += rax, rdx += 16: rcx < rdx: rcx++ )
            .if ( byte ptr [rcx] != 0 )
                asmerr( 2104, inp )
                .break
            .endif
        .endf

        mov eax,negative
        shr eax,1
        .if eax != size
            .switch eax
            .case 2  : __cvth_q(_out, _out)  : .endc
            .case 4  : __cvtss_q(_out, _out) : .endc
            .case 8  : __cvtsd_q(_out, _out) : .endc
            .case 10 : __cvtld_q(_out, _out) : .endc
            .case 16 : .endc
            .default
                .if ( Parse_Pass == PASS_1 )
                    asmerr( 7004 )
                .endif
                tmemset( _out, 0, size )
            .endsw
            .if qerrno
                asmerr( 2071 )
            .endif
        .endif

    .else

        __cvta_q(_out, inp, NULL)
        .if ( qerrno )
            asmerr( 2104, inp )
        .endif
        .if ( negative )
            mov rcx,_out
            or  byte ptr [rcx+15],0x80
        .endif
        mov eax,size
        .switch al
        .case 2
            __cvtq_h(_out, _out)
            .if ( qerrno )
                asmerr( 2071 )
            .endif
            .endc
        .case 4
            __cvtq_ss(_out, _out)
            .if ( qerrno )
                asmerr( 2071 )
            .endif
            .endc
        .case 8
            __cvtq_sd(_out, _out)
            .if ( qerrno )
                asmerr( 2071 )
            .endif
            .endc
        .case 10
            __cvtq_ld(_out, _out)
        .case 16
            .endc
        .default
            ;; sizes != 4,8,10 or 16 aren't accepted.
            ;; Masm ignores silently, JWasm also unless -W4 is set.
            ;;
            .if ( Parse_Pass == PASS_1 )
                asmerr( 7004 )
            .endif
            tmemset( _out, 0, size )
        .endsw
    .endif
    ret

atofloat endp

    assume rbx:ptr expr

quad_resize proc fastcall uses rsi rbx opnd:ptr expr, size:int_t

    mov qerrno,0
    mov rbx,rcx
    movzx esi,word ptr [rbx+14]
    and esi,0x7FFF

    .switch edx
    .case 10
        __cvtq_ld(rbx, rbx)
        .endc
    .case 8
        .if ( [rbx].chararray[15] & 0x80 )
            or  [rbx].flags,E_NEGATIVE
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_sd(rbx, rbx)
        .if ( [rbx].flags & E_NEGATIVE )
            or [rbx].chararray[7],0x80
        .endif
        mov [rbx].mem_type,MT_REAL8
        .endc
    .case 4
        .if ( [rbx].chararray[15] & 0x80 )
            or  [rbx].flags,E_NEGATIVE
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_ss(rbx, rbx)
        .if ( [rbx].flags & E_NEGATIVE )
            or [rbx].chararray[3],0x80
        .endif
        mov [rbx].mem_type,MT_REAL4
        .endc
    .case 2
        .if ( [rbx].chararray[15] & 0x80 )
            or  [rbx].flags,E_NEGATIVE
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_h(rbx, rbx)
        .if ( [rbx].flags & E_NEGATIVE )
            or [rbx].chararray[1],0x80
        .endif
        mov [rbx].mem_type,MT_REAL2
        .endc
    .endsw

    .if ( qerrno && esi != 0x7FFF )
        asmerr( 2071 )
    .endif
    ret

quad_resize endp

    end
