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

define STK_BUF_SIZE     512 ; ANSI-specified minimum is 509
define NDIG             16

define D_CVT_DIGITS     20
define LD_CVT_DIGITS    23
define QF_CVT_DIGITS    33

define E16_EXP          0x4034
define E16_HIGH         0x8E1BC9BF
define E16_LOW          0x04000000
define E32_EXP          0x4069
define E32_HIGH         ( 0x80000000 or ( 0x3B8B5B50 shr 1 ) )
define E32_LOW          ( 0x56E16B3B shr 1 )

define HFLT_MAX         0x7BFF
define HFLT_MIN         0x0001

define DDFLT_MAX        0x7F7FFFFF
define DDFLT_MIN        0x00800000

define MAX_EXP_INDEX    13

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

ifdef _WIN64

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


else ; _WIN64


;-------------------------------------------------------------------------------
; 64-bit MUL  ecx:ebx:edx:eax = edx:eax * ecx:ebx
;-------------------------------------------------------------------------------

__mul64 proc watcall a:int64_t, b:int64_t

    .if !edx && !ecx

        mul ebx
        xor ebx,ebx
       .return
    .endif

    push    ebp
    push    esi
    push    edi
    push    eax
    push    edx
    push    edx
    mul     ebx
    mov     esi,edx
    mov     edi,eax
    pop     eax
    mul     ecx
    mov     ebp,edx
    xchg    ebx,eax
    pop     edx
    mul     edx
    add     esi,eax
    adc     ebx,edx
    adc     ebp,0
    pop     eax
    mul     ecx
    add     esi,eax
    adc     ebx,edx
    adc     ebp,0
    mov     ecx,ebp
    mov     edx,esi
    mov     eax,edi
    pop     edi
    pop     esi
    pop     ebp
    ret

__mul64 endp

;-------------------------------------------------------------------------------
; 64-bit DIV
;-------------------------------------------------------------------------------

__udiv64 proc watcall private dividend:qword, divisor:qword

    .repeat

        .break .if ecx

        dec ebx
        .ifnz

            inc ebx
            .if ebx <= edx
                mov  ecx,eax
                mov  eax,edx
                xor  edx,edx
                div  ebx        ; edx / ebx
                xchg ecx,eax
            .endif
            div ebx             ; edx:eax / ebx
            mov ebx,edx
            mov edx,ecx
            xor ecx,ecx
        .endif
        ret
    .until 1

    .repeat

        .break .if ecx < edx
        .ifz
            .if ebx <= eax
                sub eax,ebx
                mov ebx,eax
                xor ecx,ecx
                xor edx,edx
                mov eax,1
                ret
            .endif
        .endif
        xor  ecx,ecx
        xor  ebx,ebx
        xchg ebx,eax
        xchg ecx,edx
        ret

    .until 1

    push ebp
    push esi
    push edi

    xor ebp,ebp
    xor esi,esi
    xor edi,edi

    .repeat

        add ebx,ebx
        adc ecx,ecx
        .ifnc
            inc ebp
            .continue(0) .if ecx < edx
            .ifna
                .continue(0) .if ebx <= eax
            .endif
            add esi,esi
            adc edi,edi
            dec ebp
            .break .ifs
        .endif
        .while 1
            rcr ecx,1
            rcr ebx,1
            sub eax,ebx
            sbb edx,ecx
            cmc
            .continue(0) .ifc
            .repeat
                add esi,esi
                adc edi,edi
                dec ebp
                .break(1) .ifs
                shr ecx,1
                rcr ebx,1
                add eax,ebx
                adc edx,ecx
            .untilb
            adc esi,esi
            adc edi,edi
            dec ebp
            .break(1) .ifs
        .endw
        add eax,ebx
        adc edx,ecx
    .until 1
    mov ebx,eax
    mov ecx,edx
    mov eax,esi
    mov edx,edi
    pop edi
    pop esi
    pop ebp
    ret
__udiv64 endp

;-------------------------------------------------------------------------------
; 64-bit IDIV
;-------------------------------------------------------------------------------

__div64 proc watcall dividend:int64_t, divisor:int64_t

    or edx,edx     ; hi word of dividend signed ?
    .ifns
        or ecx,ecx ; hi word of divisor signed ?
        .ifns
            jmp __udiv64
        .endif
        neg ecx
        neg ebx
        sbb ecx,0
        __udiv64()
        neg edx
        neg eax
        sbb edx,0
        ret
    .endif
    neg edx
    neg eax
    sbb edx,0
    or ecx,ecx
    .ifs
        neg ecx
        neg ebx
        sbb ecx,0
        __udiv64()
        neg ecx
        neg ebx
        sbb ecx,0
        ret
    .endif
    __udiv64()
    neg ecx
    neg ebx
    sbb ecx,0
    neg edx
    neg eax
    sbb edx,0
    ret

__div64 endp

;-------------------------------------------------------------------------------
; 64-bit REM
;-------------------------------------------------------------------------------

__rem64 proc watcall dividend:int64_t, divisor:int64_t

    __div64()
    mov eax,ebx
    mov edx,ecx
    ret

__rem64 endp

;-------------------------------------------------------------------------------
; 128-bit integer
;-------------------------------------------------------------------------------

    assume esi:ptr U128
    assume edi:ptr U128

__mulo proc uses esi edi ebx multiplier:ptr, multiplicand:ptr, highproduct:ptr

  local n[8]:dword ; 256-bit result

    mov edi,multiplier
    mov esi,multiplicand

    __mul64( [edi].u64[0], [esi].u64[0] )

    mov n[0x00],eax
    mov n[0x04],edx
    mov n[0x08],ebx
    mov n[0x0C],ecx

    __mul64( [edi].u64[8], [esi].u64[8] )

    mov n[0x10],eax
    mov n[0x14],edx
    mov n[0x18],ebx
    mov n[0x1C],ecx

    __mul64( [edi].u64[0], [esi].u64[8] )

    add n[0x08],eax
    adc n[0x0C],edx
    adc n[0x10],ebx
    adc n[0x14],ecx
    adc n[0x18],0
    adc n[0x1C],0

    __mul64( [edi].u64[8], [esi].u64[0] )

    add n[0x08],eax
    adc n[0x0C],edx
    adc n[0x10],ebx
    adc n[0x14],ecx
    adc n[0x18],0
    adc n[0x1C],0

    mov [edi].u32[0x00],n[0x00]
    mov [edi].u32[0x04],n[0x04]
    mov [edi].u32[0x08],n[0x08]
    mov [edi].u32[0x0C],n[0x0C]
    mov esi,highproduct
    .if esi
        mov [esi].u32[0x00],n[0x10]
        mov [esi].u32[0x04],n[0x14]
        mov [esi].u32[0x08],n[0x18]
        mov [esi].u32[0x0C],n[0x1C]
    .endif
    mov eax,edi
    ret

__mulo endp

__divo proc uses esi edi ebx dividend:ptr, divisor:ptr, reminder:ptr

    mov     esi,dividend
    mov     edi,reminder
    mov     ecx,4
    rep     movsd
    xor     eax,eax
    mov     edi,dividend
    mov     ecx,4
    rep     stosd
    mov     esi,divisor
    mov     edi,reminder
    or      eax,[esi].u32[0]
    or      eax,[esi].u32[4]
    or      eax,[esi].u32[8]
    or      eax,[esi].u32[12]
    .ifz
        mov ecx,4
        rep stosd
        .return
    .endif

    .if [esi].u32[12] == [edi].u32[12]
        .if [esi].u32[8] == [edi].u32[8]
            .if [esi].u32[4] == [edi].u32[4]
                mov eax,[esi].u32[0]
                cmp eax,[edi].u32[0]
            .endif
        .endif
    .endif
    .return .ifa    ; if divisor > dividend : reminder = dividend, quotient = 0
    .ifz            ; if divisor == dividend :
        mov ecx,4
        xor eax,eax         ; reminder = 0
        rep stosd
        mov edi,dividend    ; quotient = 1
        inc byte ptr [edi]
        .return
    .endif

    mov ecx,[esi].u32[12]   ; esi = divisor
    mov ebx,[esi].u32[8]    ; - divisor used as bit-count
    mov edx,[esi].u32[4]
    mov esi,[esi].u32[0]
    mov divisor,-1

    .while 1

        inc divisor

        add esi,esi
        adc edx,edx
        adc ebx,ebx
        adc ecx,ecx
        .break .ifc

        .break .if ecx > [edi].u32[12]
        .continue .ifb
        .break .if ebx > [edi].u32[8]
        .continue .ifb
        .break .if edx > [edi].u32[4]
        .continue .ifb
        .break .if esi > [edi].u32[0]
    .endw

    .while 1

        rcr ecx,1
        rcr ebx,1
        rcr edx,1
        rcr esi,1

        mov edi,reminder
        sub [edi].u32[0],esi
        sbb [edi].u32[4],edx
        sbb [edi].u32[8],ebx
        sbb [edi].u32[12],ecx
        cmc

        .ifnc

            .repeat

                mov edi,dividend
                add [edi].u32[0],[edi].u32[0]
                adc [edi].u32[4],[edi].u32[4]
                adc [edi].u32[8],[edi].u32[8]
                adc [edi].u32[12],[edi].u32[12]

                dec divisor
                mov edi,reminder

                .ifs

                    add [edi].u32[0],esi
                    adc [edi].u32[4],edx
                    adc [edi].u32[8],ebx
                    adc [edi].u32[12],ecx

                    .break(1)
                .endif

                shr ecx,1
                rcr ebx,1
                rcr edx,1
                rcr esi,1

                add [edi].u32[0],esi
                adc [edi].u32[4],edx
                adc [edi].u32[8],ebx
                adc [edi].u32[12],ecx
            .untilb
        .endif

        mov edi,dividend
        adc [edi].u32[0],[edi].u32[0]
        adc [edi].u32[4],[edi].u32[4]
        adc [edi].u32[8],[edi].u32[8]
        adc [edi].u32[12],[edi].u32[12]

        dec divisor
        .break .ifs
    .endw
    mov eax,dividend
    ret

__divo endp

    assume edi:nothing

__shlo proc uses esi edi ebx val:ptr, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].u32[0]
    mov edx,[esi].u32[4]
    mov ebx,[esi].u32[8]
    mov edi,[esi].u32[12]

    .if ( ecx >= 128 ) || ( ecx >= 64 && bits < 128 )

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif bits == 128

        .while ecx >= 32

            mov edi,ebx
            mov ebx,edx
            mov edx,eax
            xor eax,eax
            sub ecx,32
        .endw

        shld edi,ebx,cl
        shld ebx,edx,cl
        shld edx,eax,cl
        shl eax,cl

    .else

        .if cl < 32

            shld edx,eax,cl
            shl eax,cl
        .else

            and ecx,31
            mov edx,eax
            xor eax,eax
            shl edx,cl
        .endif
    .endif

    mov [esi].u32[0],eax
    mov [esi].u32[4],edx
    mov [esi].u32[8],ebx
    mov [esi].u32[12],edi
    mov eax,esi
    ret

__shlo endp

__shro proc uses esi edi ebx val:ptr, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].u32[0]
    mov edx,[esi].u32[4]
    mov ebx,[esi].u32[8]
    mov edi,[esi].u32[12]

    .if ( ecx >= 128 ) || ( ecx >= 64 && bits < 128 )

        xor edi,edi
        xor ebx,ebx
        xor edx,edx
        xor eax,eax

    .elseif bits == 128

        .while ecx > 32

            mov eax,edx
            mov edx,ebx
            mov ebx,edi
            xor edi,edi
            sub ecx,32
        .endw

        shrd eax,edx,cl
        shrd edx,ebx,cl
        shrd ebx,edi,cl
        shr edi,cl

    .else

        .if eax == -1 && bits == 32

            xor edx,edx
        .endif

        .if ecx < 32

            shrd eax,edx,cl
            shr edx,cl
        .else

            mov eax,edx
            xor edx,edx
            and cl,32-1
            shr eax,cl
        .endif
    .endif

    mov [esi].u32[0],eax
    mov [esi].u32[4],edx
    mov [esi].u32[8],ebx
    mov [esi].u32[12],edi
    mov eax,esi
    ret

__shro endp

__saro proc uses esi edi ebx val:ptr, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].u32[0]
    mov edx,[esi].u32[4]
    mov ebx,[esi].u32[8]
    mov edi,[esi].u32[12]

    .if ecx >= 64 && bits <= 64

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif ecx >= 128 && bits == 128

        sar edi,31
        mov ebx,edi
        mov edx,edi
        mov eax,edi

    .elseif bits == 128

        .while ecx > 32

            mov eax,edx
            mov edx,ebx
            mov ebx,edi
            sar edi,31
            sub ecx,32
        .endw

        shrd eax,edx,cl
        shrd edx,ebx,cl
        shrd ebx,edi,cl
        sar edi,cl

    .else

        .if eax == -1 && bits == 32

            xor edx,edx
        .endif

        .if ecx < 32

            shrd eax,edx,cl
            sar edx,cl
        .else

            mov eax,edx
            sar edx,31
            and cl,32-1
            sar eax,cl
        .endif
    .endif

    mov [esi].u32[0],eax
    mov [esi].u32[4],edx
    mov [esi].u32[8],ebx
    mov [esi].u32[12],edi
    mov eax,esi
    ret

__saro endp

    assume esi:nothing

;-------------------------------------------------------------------------------
; 134-bit (128+16) extended float
;-------------------------------------------------------------------------------

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

_fltadd proc private a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(a, b, 0)
    ret

_fltadd endp

_fltsub proc private a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd(a, b, 0x80000000)
    ret

_fltsub endp


_fltmul proc private uses esi edi ebx a:ptr STRFLT, b:ptr STRFLT

  local multiplier[4]:dword
  local result    [8]:dword

    mov     ecx,b
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

    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     if_zero_b
    add     si,si
    jz      error_zero_a
    rcr     si,1

if_zero_b:
    mov     ecx,b
    push    eax
    mov     eax,[ecx+0x0]
    or      eax,[ecx+0x4]
    or      eax,[ecx+0x8]
    or      eax,[ecx+0xC]
    pop     eax
    jnz     init_done
    test    esi,0x7FFF0000
    jz      error_zero_b

init_done:

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    add     esi,ecx
    sub     si,0x3FFE
    jc      if_too_small
    cmp     si,0x7FFF
    ja      return_overflow
if_too_small:
    cmp     si,-65
    jl      return_underflow

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
    js      overflow
    add     ecx,ecx
    adc     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    dec     si

overflow:

rounding:

    add     ecx,ecx
    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0

validate:

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
    test    esi,0x80008000
    jz      return_zero
    mov     esi,0x80000000
    jmp     return_b

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
    mov     ecx,b
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    mov     ebx,[ecx+8]
    mov     edi,[ecx+12]
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
    jnz     @F
    mov     ecx,b
    or      eax,[ecx]
    or      eax,[ecx+4]
    or      eax,[ecx+8]
    or      eax,[ecx+12]
    mov     eax,0
    jnz     @F
    or      esi,-1
    jmp     return_nan
@@:
    mov     ecx,b
    cmp     edi,[ecx+0xC]
    jb      return_b
    ja      done
    cmp     ebx,[ecx+0x8]
    jb      return_b
    ja      done
    cmp     edx,[ecx+0x4]
    jb      return_b
    ja      done
    cmp     eax,[ecx+0x0]
    jna     return_b
    jmp     done

error_nan_b:
    sub     esi,0x10000
    mov     ecx,b
    push    eax
    mov     eax,[ecx+0x0]
    or      eax,[ecx+0x4]
    or      eax,[ecx+0x8]
    or      eax,[ecx+0xC]
    pop     eax
    jnz     return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     return_b

_fltmul endp

_fltdiv proc private uses esi edi ebx a:ptr STRFLT, b:ptr STRFLT

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

_flttoi64 proc private p:ptr STRFLT

    mov edx,p
    mov cx,[edx+16]
    mov eax,ecx
    and eax,Q_EXPMASK

    .ifs eax < Q_EXPBIAS

        xor edx,edx
        xor eax,eax
        .if cx & 0x8000
            dec eax
            dec edx
        .endif

    .elseif eax > 62 + Q_EXPBIAS

        mov qerrno,ERANGE
        xor eax,eax
        .if cx & 0x8000
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif

    .else
        mov ecx,eax
        xor eax,eax
        sub ecx,Q_EXPBIAS-1
        .if ecx < 32
            mov edx,[edx+12]
            shld eax,edx,cl
            xor edx,edx
        .else
            push esi
            push edi
            mov edi,[edx+12]
            mov esi,[edx+8]
            xor edx,edx
            .while ecx
                add esi,esi
                adc edi,edi
                adc eax,eax
                adc edx,edx
                dec ecx
            .endw
            pop edi
            pop esi
        .endif
        mov ecx,p
        .if byte ptr [ecx+17] & 0x80
            neg edx
            neg eax
            sbb edx,0
        .endif
    .endif
    ret

_flttoi64 endp

_i64toflt proc private uses ebx p:ptr STRFLT, ll:int64_t

    mov eax,dword ptr ll
    mov edx,dword ptr ll[4]
    mov ebx,Q_EXPBIAS   ; set exponent

    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        neg eax
        sbb edx,0
        or  ebx,0x8000
    .endif

    .if eax || edx
        .if edx         ; find most significant non-zero bit
            bsr ecx,edx
            add ecx,32
        .else
            bsr ecx,eax
        .endif
        mov ch,cl
        mov cl,64
        sub cl,ch
        .if cl <= 64     ; shift bits into position
            dec cl
            .if cl >= 32
                sub cl,32
                mov edx,eax
                xor eax,eax
            .endif
            shld edx,eax,cl
            shl eax,cl
        .else
            xor eax,eax
            xor edx,edx
        .endif
        shr ecx,8       ; get shift count
        add ecx,ebx     ; calculate exponent
    .else
        xor ecx,ecx     ; else zero
    .endif

    mov     ebx,p
    xchg    eax,ebx
    mov     [eax+8],ebx
    mov     [eax+12],edx
    mov     [eax+16],cx
    xor     edx,edx     ; zero the rest of the fraction bits
    mov     [eax],edx
    mov     [eax+4],edx
    ret

_i64toflt endp


_fltscale proc private uses esi edi ebx p:ptr STRFLT

    mov ebx,p
    mov edi,[ebx].STRFLT.exponent

    lea esi,_fltpowtable
    .ifs ( edi < 0 )

        neg edi
        add esi,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if edi

        .for ( ebx = 0 : edi && ebx < MAX_EXP_INDEX : ebx++, edi >>= 1, esi += EXTFLOAT )

            .if ( edi & 1 )

                _fltmul(p, esi)
            .endif
        .endf

        .if ( edi != 0 )

            ; exponent overflow

            xor eax,eax
            mov ebx,p
            mov [ebx],eax
            mov [ebx+4],eax
            mov [ebx+8],eax
            mov [ebx+12],eax
            mov word ptr [ebx+16],0x7FFF
        .endif
    .endif
    mov eax,p
    ret

_fltscale endp

    assume ebx: ptr STRFLT

_fltround proc private uses esi edi ebx p:ptr STRFLT

    mov ebx,p
    mov eax,[ebx]
    .if eax & 0x4000

        mov edx,[ebx+4]
        mov edi,[ebx+8]
        mov esi,[ebx+12]

        add eax,0x4000
        adc edx,0
        adc edi,0
        adc esi,0
        .ifc
            rcr esi,1
            rcr edi,1
            rcr edx,1
            rcr eax,1
            inc [ebx].mantissa.e
            .if [ebx].mantissa.e == Q_EXPMASK

                mov [ebx].mantissa.e,0x7FFF
                xor eax,eax
                xor edx,edx
                xor edi,edi
                xor esi,esi
            .endif
        .endif
        mov [ebx],eax
        mov [ebx+4],edx
        mov [ebx+8],edi
        mov [ebx+12],esi
    .endif
    mov eax,p
    ret

_fltround endp

    assume ebx: nothing

_fltpackfp proc private uses esi edi ebx q:ptr, p:ptr STRFLT

    mov esi,p
    mov edi,q

    _fltround(esi)

    mov eax,[esi]
    mov edx,[esi+4]
    mov ebx,[esi+8]
    mov ecx,[esi+12]
    shl eax,1
    rcl edx,1
    rcl ebx,1
    rcl ecx,1
    shr eax,16
    mov [edi],ax
    mov [edi+2],edx
    mov [edi+6],ebx
    mov [edi+10],ecx
    mov ax,[esi+16]
    mov [edi+14],ax
    mov eax,edi
    ret

_fltpackfp endp

_fltunpack proc private uses esi edi ebx p:ptr STRFLT, q:ptr

    mov edi,p
    mov esi,q
    mov ax,[esi]
    shl eax,16
    mov dx,[esi+14]
    mov [edi+16],dx
    and dx,Q_EXPMASK
    neg dx
    mov edx,[esi+2]
    mov ebx,[esi+6]
    mov ecx,[esi+10]
    rcr ecx,1
    rcr ebx,1
    rcr edx,1
    rcr eax,1
    mov [edi],eax
    mov [edi+4],edx
    mov [edi+8],ebx
    mov [edi+12],ecx
    mov eax,edi
    ret

_fltunpack endp

    assume edi: ptr STRFLT

_fltsetflags proc private uses esi edi fp:ptr STRFLT, string:string_t, flags:uint_t

    mov edi,fp
    mov esi,string
    xor eax,eax
    mov [edi],eax
    mov [edi+4],eax
    mov [edi+8],eax
    mov [edi+12],eax
    mov [edi+16],ax
    mov [edi].exponent,eax
    mov ecx,flags
    or  ecx,_ST_ISZERO

    .repeat

        lodsb
        .break .if ( al == 0 )
        .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )
        dec esi

        mov ecx,flags
        .if ( al == '+' )

            inc esi
            or  ecx,_ST_SIGN
        .endif

        .if ( al == '-' )

            inc esi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or al,0x20
        .if ( al == 'n' )

            mov ax,[esi]
            or  ax,0x2020

            .if ( ax == 'na' )

                add esi,2
                or  ecx,_ST_ISNAN
                mov [edi].mantissa.e,0xFFFF
                movzx eax,byte ptr [esi]

                .if ( al == '(' )

                    lea edx,[esi+1]
                    mov al,[edx]
                    .switch
                      .case al == '_'
                      .case al >= '0' && al <= '9'
                      .case al >= 'a' && al <= 'z'
                      .case al >= 'A' && al <= 'Z'
                        inc edx
                        mov al,[edx]
                        .gotosw
                    .endsw
                    .if al == ')'

                        lea esi,[edx+1]
                    .endif
                .endif
            .else
                dec esi
                or ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == 'i' )

            mov ax,[esi]
            or  ax,0x2020

            .if ( ax == 'fn' )

                add esi,2
                or ecx,_ST_ISINF
            .else
                dec esi
                or ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == '0' )

            mov al,[esi]
            or  al,0x20
            .if ( al == 'x' )

                or  ecx,_ST_ISHEX
                add esi,2
            .endif
        .endif
        dec esi

    .until 1

    mov [edi].flags,ecx
    mov [edi].string,esi
    mov eax,ecx
    ret

_fltsetflags endp

    assume edi:nothing

_destoflt proc private uses esi edi ebx fp:ptr STRFLT, buffer:string_t

  local digits:int_t, sigdig:int_t

    mov edx,fp
    mov edi,buffer
    mov esi,[edx].STRFLT.string
    mov ecx,[edx].STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor ebx,ebx
    xor edx,edx

    .repeat

        .while 1

            lodsb
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

                .if ebx < Q_SIGDIG
                    stosb
                .endif
                inc ebx
            .endif
        .endw
        mov byte ptr [edi],0
        mov digits,ebx

        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor edi,edi ; exponent

            .if ( ( ( ecx & _ST_ISHEX ) && ( al == 'p' || al == 'P' ) ) || \
                al == 'e' || al == 'E' )

                mov al,[esi]
                lea edx,[esi-1]
                .if al == '+'
                    inc esi
                .endif
                .if al == '-'
                    inc esi
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1

                    movzx eax,byte ptr [esi]
                    .break .if al < '0'
                    .break .if al > '9'

                    .if edi < 100000000 ; else overflow

                        lea ebx,[edi*8]
                        lea edi,[edi*2+ebx-'0']
                        add edi,eax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc esi
                .endw

                .if ( ecx & _ST_NEGEXP )
                    neg edi
                .endif
                .if !( ecx & _ST_DIGITS )
                    mov esi,edx
                .endif

            .else

                dec esi ; digits found, but no e or E
            .endif

            mov edx,edi
            mov eax,sigdig
            mov ebx,digits
            mov edi,Q_DIGITS

            .if ( ecx & _ST_ISHEX )

                mov edi,32
                shl eax,2
            .endif
            sub edx,eax

            mov eax,1
            .if ( ecx & _ST_ISHEX )

                mov eax,4
            .endif

            .if ( ebx > edi )

                add edx,ebx
                mov ebx,edi
                .if ( ecx & _ST_ISHEX )

                    shl edi,2
                .endif
                sub edx,edi
            .endif

            mov edi,buffer
            .while 1

                .break .ifs ebx <= 0
                .break .if byte ptr [edi+ebx-1] != '0'

                add edx,eax
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov eax,fp
            mov esi,[eax].STRFLT.string
        .endif

    .until 1

    mov eax,fp
    mov [eax].STRFLT.flags,ecx
    mov [eax].STRFLT.string,esi
    mov [eax].STRFLT.exponent,edx
    mov eax,digits
    ret

_destoflt endp

_strtoflt proc private uses esi edi ebx string:string_t

  local buffer[128]:char_t
  local digits:int_t
  local sign:int_t

    .repeat

        _fltsetflags(&lflt, string, 0)
        .break .if eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID

        mov digits,_destoflt(&lflt, &buffer)
        mov edx,lflt.mantissa

        .if ( eax == 0 )

            or lflt.flags,_ST_ISZERO
            .break
        .endif
        mov buffer[eax],0

        ;
        ; convert string to binary
        ;
        lea edx,buffer
        xor eax,eax
        mov al,[edx]
        mov sign,eax

        .if ( al == '+' || al == '-' )

            inc edx
        .endif

        mov ebx,16
        .if !( lflt.flags & _ST_ISHEX )

            mov ebx,10
        .endif
        lea esi,lflt.mantissa

        .while 1

            mov al,[edx]
            .break .if !al

            and eax,not 0x30
            bt  eax,6
            sbb ecx,ecx
            and ecx,55
            sub eax,ecx
            mov ecx,8
            .repeat
                movzx edi,word ptr [esi]
                imul  edi,ebx
                add   eax,edi
                mov   [esi],ax
                add   esi,2
                shr   eax,16
            .untilcxz
            sub esi,16
            inc edx
        .endw

        mov eax,[esi]
        mov edx,[esi+4]
        mov ebx,[esi+8]
        mov esi,[esi+12]
if 0
        .if ( sign == '-' )

            neg esi
            neg ecx
            sbb esi,0
            neg edx
            sbb ecx,0
            neg eax
            sbb edx,0
        .endif
endif
        xor ecx,ecx
        .if eax || edx || ebx || esi
            .if esi
                bsr ecx,esi
                add ecx,96
            .elseif ebx
                bsr ecx,ebx
                add ecx,64
            .elseif edx
                bsr ecx,edx
                add ecx,32
            .else
                bsr ecx,eax
            .endif
            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch
            .while cl >= 32
                sub cl,32
                mov esi,ebx
                mov ebx,edx
                mov edx,eax
                xor eax,eax
            .endw
            shld esi,ebx,cl
            shld ebx,edx,cl
            shld edx,eax,cl
            shl eax,cl
            mov dword ptr lflt.mantissa.l[0],eax
            mov dword ptr lflt.mantissa.l[4],edx
            mov dword ptr lflt.mantissa.h[0],ebx
            mov dword ptr lflt.mantissa.h[4],esi
            shr ecx,8
            add ecx,Q_EXPBIAS
            .if lflt.flags & _ST_NEGNUM
                or ecx,0x8000
            .endif
            .if lflt.flags & _ST_ISHEX
                add ecx,lflt.exponent
            .endif
            mov lflt.mantissa.e,cx
        .else
            or lflt.flags,_ST_ISZERO
        .endif
        mov ebx,ecx
        mov edi,lflt.flags
        mov ax,lflt.mantissa.e
        and eax,Q_EXPMASK

        .switch
          .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID or _ST_UNDERFLOW or _ST_OVERFLOW
          .case eax >= Q_EXPMAX + Q_EXPBIAS
            or  ebx,0x7FFF
            xor eax,eax
            mov dword ptr lflt.mantissa.l[0],eax
            mov dword ptr lflt.mantissa.l[4],eax
            mov dword ptr lflt.mantissa.h[0],eax
            mov dword ptr lflt.mantissa.h[4],eax
            .if edi & _ST_ISNAN or _ST_INVALID
                or ebx,0x8000
                or byte ptr lflt.mantissa.h[7],0x80
            .endif
        .endsw
        mov lflt.mantissa.e,bx
        and ebx,Q_EXPMASK
        .if ebx >= 0x7FFF
            mov qerrno,ERANGE
        .elseif lflt.exponent && !( lflt.flags & _ST_ISHEX )
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

        _fltpackfp(&lflt, &lflt)

    .until 1
    lea eax,lflt
    ret

_strtoflt endp


;-------------------------------------------------------------------------------
; _flttostr() - Converts quad float to string
;-------------------------------------------------------------------------------

    assume ebx:ptr FLTINFO

_flttostr proc uses esi edi ebx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local i      :int_t
  local n      :int_t
  local nsig   :int_t
  local xexp   :int_t
  local value[2]:int_t
  local maxsize:int_t
  local digits :int_t
  local radix  :int_t
  local flt    :STRFLT
  local tmp    :STRFLT
  local stkbuf[STK_BUF_SIZE]:char_t
  local endbuf :ptr

    mov ebx,cvt
    mov eax,buf
    add eax,[ebx].bufsize
    dec eax
    mov endbuf,eax
    mov eax,flags
    mov ecx,D_CVT_DIGITS
    .if eax & _ST_LONGDOUBLE
        mov ecx,LD_CVT_DIGITS
    .elseif eax & _ST_QUADFLOAT
        mov ecx,QF_CVT_DIGITS
    .endif
    mov digits,ecx
    mov radix,10

    xor eax,eax
    mov [ebx].n1,eax
    mov [ebx].nz1,eax
    mov [ebx].n2,eax
    mov [ebx].nz2,eax
    mov [ebx].dec_place,eax
    mov value,eax
    mov value[4],eax

    _fltunpack(&flt, q)
    mov ax,flt.mantissa.e
    bt  eax,15
    sbb ecx,ecx
    mov [ebx].sign,ecx
    and eax,Q_EXPMASK   ; make number positive
    mov flt.mantissa.e,ax

    movzx ecx,ax
    lea edi,flt
    xor eax,eax
    mov flt.flags,eax

    .if ecx == Q_EXPMASK

        ; NaN or Inf

        or eax,[edi]
        or eax,[edi+4]
        or eax,[edi+8]
        or eax,[edi+12]

        .ifz
            mov eax,'fni'
            or  [ebx].flags,_ST_ISINF
        .else
            mov eax,'nan'
            or  [ebx].flags,_ST_ISNAN
        .endif
        .if flags & _ST_CAPEXP
            and eax,NOT 0x202020
        .endif
        mov edx,buf
        mov [edx],eax
        mov [ebx].n1,3

        .return 0
    .endif

    .if !ecx

        ; ZERO/DENORMAL

        mov [ebx].sign,eax ; force sign to +0.0
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

                mov eax,[edi+8]
                mov edx,[edi+12]

                .if ( esi < E16_EXP || ( ( esi == E16_EXP && ( edx < E16_HIGH ||
                    ( edx == E16_HIGH && eax < E16_LOW ) ) ) ) )

                    ; number is < 1e16

                    mov xexp,0

                .else
                    .if ( esi < E32_EXP || ( ( esi == E32_EXP && ( edx < E32_HIGH ||
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

    mov eax,[ebx].ndigits
    .if [ebx].flags & _ST_F
        add eax,xexp
        add eax,2 + NDIG
        .ifs [ebx].scale > 0
            add eax,[ebx].scale
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

    lea edi,stkbuf
    mov word ptr [edi],'0'
    inc edi
    mov i,0

    .while ( n > 0 )

        sub n,NDIG

        .if ( value == 0 && value[4] == 0 )
            ;
            ; get value to subtract
            ;
            _flttoi64(&flt)
            mov value,eax
            mov value[4],edx
            _i64toflt(&tmp, edx::eax)
            _fltsub(&flt, &tmp)
            .ifs ( n > 0 )
                _fltmul(&flt, &EXQ_1E16)
            .endif
        .endif

        mov eax,value
        mov edx,value[4]
        mov ecx,NDIG
        .if ( eax || edx )

            add edi,ecx
            mov esi,ecx
            .fors ( : eax || edx || esi > 0 : esi-- )

                .if !edx
                    div radix
                    mov ecx,edx
                    xor edx,edx
                .else
                    push esi
                    push edi
                    .for ecx = 64, esi = 0, edi = 0 : ecx : ecx--
                        add eax,eax
                        adc edx,edx
                        adc esi,esi
                        adc edi,edi
                        .if edi || esi >= radix
                            sub esi,radix
                            sbb edi,0
                            inc eax
                        .endif
                    .endf
                    mov ecx,esi
                    pop edi
                    pop esi
                .endif
                add cl,'0'
                dec edi
                mov [edi],cl
            .endf
            add edi,NDIG

        .else
            or al,'0'
            rep stosb
        .endif
        add i,NDIG
        mov value,0
        mov value[4],0
    .endw

    ; get number of characters in buf

    .for ( eax = i, ; skip over leading zeros
           edx = STK_BUF_SIZE-2,
           esi = &stkbuf[1],
           ecx = xexp,
           ecx += NDIG-1 : edx && byte ptr [esi] == '0' : eax--, ecx--, edx--, esi++ )
    .endf

    mov n,eax
    mov ebx,cvt
    mov edx,[ebx].ndigits

    .if ( [ebx].flags & _ST_F )
        add ecx,[ebx].scale
        lea edx,[edx+ecx+1]
    .elseif ( [ebx].flags & _ST_E )
        .ifs ( [ebx].scale > 0 )
            inc edx
        .else
            add edx,[ebx].scale
        .endif
        inc ecx ; xexp = xexp + 1 - scale
        sub ecx,[ebx].scale
    .endif

    .ifs ( edx >= 0 ) ; round and strip trailing zeros
        .ifs edx > eax
            mov edx,eax ; nsig = n
        .endif
        mov eax,digits
        .ifs edx > eax
            mov edx,eax
        .endif
        mov maxsize,eax

        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [esi+edx] >= '5' ) || \
            ( edx == digits && byte ptr [esi+edx-1] == '9' ) )
            mov al,'9'
        .endif

        mov edi,[ebx].scale
        add edi,[ebx].ndigits
        .if ( al == '9' && edx == edi && \
            byte ptr [esi+edx] != '9' &&  byte ptr [esi+edx-1] == '9' )
            .while edi
                dec edi
                .break .if byte ptr [esi+edi] != '9'
            .endw
            .if byte ptr [esi+edi] == '9'
                 mov al,'0'
            .endif
        .endif

        lea edi,[esi+edx-1]
        xchg ecx,edx
        inc ecx
        std
        repz scasb
        cld
        xchg ecx,edx
        inc edi
        .if al == '9' ; round up
            inc byte ptr [edi]
        .endif
        sub edi,esi
        .ifs
            dec esi ; repeating 9's rounded up to 10000...
            inc edx
            inc ecx
        .endif
    .endif

    .ifs edx <= 0 || flt.flags == _ST_ISZERO

        mov edx,1    ; nsig = 1
        xor ecx,ecx  ; xexp = 0
        mov stkbuf,'0'
        mov [ebx].sign,ecx
        lea esi,stkbuf
    .endif

    mov i,0
    mov eax,[ebx].flags

    .ifs ( eax & _ST_F || ( eax & _ST_G && ( ( ecx >= -4 && ecx < [ebx].ndigits ) \
          || eax & _ST_CVT ) ) )

        mov edi,buf
        inc ecx

        .if eax & _ST_G
            .ifs ( edx < [ebx].ndigits && !( eax & _ST_DOT ) )
                mov [ebx].ndigits,edx
            .endif
            sub [ebx].ndigits,ecx
            .ifs ( [ebx].ndigits < 0 )
                mov [ebx].ndigits,0
            .endif
        .endif

        .ifs ( ecx <= 0 ) ; digits only to right of '.'

            .if !( eax & _ST_CVT )

                mov byte ptr [edi],'0'
                inc i

                .ifs ( [ebx].ndigits > 0 || eax & _ST_DOT )
                    mov byte ptr [edi+1],'.'
                    inc i
                .endif
            .endif

            mov [ebx].n1,i
            mov eax,ecx
            neg eax
            .ifs ( [ebx].ndigits < eax )
                mov ecx,[ebx].ndigits
                neg ecx
            .endif
            mov eax,ecx
            neg eax
            mov [ebx].dec_place,eax ; position of '.'
            mov [ebx].nz1,eax
            add [ebx].ndigits,ecx
            .ifs ( [ebx].ndigits < edx )
                mov edx,[ebx].ndigits
            .endif
            mov [ebx].n2,edx
            sub edx,[ebx].ndigits
            neg edx
            mov [ebx].nz2,edx
            add edi,[ebx].n1    ; number of leading characters

            mov ecx,[ebx].nz1   ; followed by this many '0's
            lea eax,[edi+ecx]
            add eax,[ebx].n2
            add eax,[ebx].nz2
            cmp eax,endbuf
            ja  overflow
            add i,ecx
            mov al,'0'
            rep stosb
            mov ecx,[ebx].n2    ; followed by these characters
            add i,ecx
            rep movsb
            mov ecx,[ebx].nz2   ; followed by this many '0's
            add i,ecx
            rep stosb

        .elseifs ( edx < ecx ) ; zeros before '.'

            add i,edx
            mov [ebx].n1,edx
            mov eax,ecx
            sub eax,edx
            mov [ebx].nz1,eax
            mov [ebx].dec_place,ecx
            mov ecx,edx
            rep movsb

            lea ecx,[edi+eax+2]
            cmp ecx,endbuf
            ja  overflow
            mov ecx,eax
            mov eax,'0'
            add i,ecx
            rep stosb

            mov ecx,[ebx].ndigits
            .if !( [ebx].flags & _ST_CVT )

                .ifs ( ecx > 0 || [ebx].flags & _ST_DOT )

                    mov byte ptr [edi],'.'
                    inc edi
                    inc i
                    mov [ebx].n2,1
                .endif
            .endif

            lea edx,[edi+ecx]
            cmp edx,endbuf
            ja  overflow
            mov [ebx].nz2,ecx
            add i,ecx
            rep stosb

        .else ; enough digits before '.'

            mov [ebx].dec_place,ecx
            add i,ecx
            sub edx,ecx
            rep movsb
            mov edi,buf
            mov ecx,[ebx].dec_place

            .if !( [ebx].flags & _ST_CVT )
                .ifs [ebx].ndigits > 0 || [ebx].flags & _ST_DOT

                    mov eax,edi
                    add eax,i
                    mov byte ptr [eax],'.'
                    inc i
                .endif
            .elseif byte ptr [edi] == '0' ; ecvt or fcvt with 0.0
                mov [ebx].dec_place,0
            .endif
            .ifs [ebx].ndigits < edx
                mov edx,[ebx].ndigits
            .endif

            add edi,i
            mov ecx,edx
            rep movsb
            add i,edx
            mov [ebx].n1,i
            mov eax,edx
            mov ecx,[ebx].ndigits
            add edx,ecx
            mov [ebx].nz1,edx
            sub ecx,eax
            lea eax,[edi+ecx]
            cmp eax,endbuf
            ja  overflow
            add i,ecx
            mov eax,'0'
            rep stosb

        .endif

        mov edi,buf
        add edi,i
        mov byte ptr [edi],0

    .else

        mov eax,[ebx].ndigits
        .ifs [ebx].scale <= 0
            add eax,[ebx].scale   ; decrease number of digits after decimal
        .else
            sub eax,[ebx].scale   ; adjust number of digits (see fortran spec)
            inc eax
        .endif

        mov i,0
        .if [ebx].flags & _ST_G

            ; fixup for 'G'
            ; for 'G' format, ndigits is the number of significant digits
            ; cvt->scale should be 1 indicating 1 digit before decimal place
            ; so decrement ndigits to get number of digits after decimal place

            .if ( edx < eax && !( [ebx].flags & _ST_DOT ) )
                mov eax,edx
            .endif
            dec eax
            .ifs eax < 0
                xor eax,eax
            .endif
        .endif

        mov [ebx].ndigits,eax
        mov xexp,ecx
        mov nsig,edx
        mov edi,buf

        .ifs ( [ebx].scale <= 0 )

            mov byte ptr [edi],'0'
            inc i
            .if ( ecx >= maxsize )
                inc xexp
            .endif
        .else

            mov eax,[ebx].scale
            .if ( eax > edx )
                mov eax,edx
            .endif

            mov n,eax
            add edi,i ; put in leading digits
            mov ecx,eax
            mov eax,esi
            rep movsb
            mov esi,eax
            mov eax,n
            add i,eax
            add esi,eax
            sub nsig,eax

            .ifs ( eax < [ebx].scale ) ; put in zeros if required

                mov ecx,[ebx].scale
                sub ecx,eax
                mov n,ecx
                add i,ecx
                mov edi,buf
                add edi,i
                mov al,'0'
                rep stosb
            .endif
        .endif

        mov ecx,i
        mov edi,buf
        mov [ebx].dec_place,ecx
        mov eax,[ebx].ndigits

        .if !( [ebx].flags & _ST_CVT )
            .ifs ( eax > 0 || [ebx].flags & _ST_DOT )

                mov byte ptr [edi+ecx],'.'
                inc i
            .endif
        .endif

        mov ecx,[ebx].scale
        .ifs ( ecx < 0 )

            neg ecx
            mov n,ecx
            add edi,i
            mov al,'0'
            rep stosb
            mov eax,n
            add i,eax
        .endif

        mov ecx,nsig
        mov eax,[ebx].ndigits

        .ifs ( eax > 0 ) ; put in fraction digits

            .ifs eax < ecx
                mov ecx,eax
                mov nsig,eax
            .endif
            .if ecx
                mov edi,buf
                add edi,i
                add i,ecx
                rep movsb
            .endif

            mov eax,i
            mov [ebx].n1,eax
            mov ecx,[ebx].ndigits
            sub ecx,nsig
            mov [ebx].nz1,ecx
            mov edi,buf
            add edi,i
            add i,ecx
            mov eax,'0'
            rep stosb
        .endif

        mov edi,buf
        mov eax,[ebx].expchar
        .if al
            mov ecx,i
            mov [edi+ecx],al
            inc i
        .endif

        mov eax,xexp
        mov ecx,i
        .ifs eax >= 0
            mov byte ptr [edi+ecx],'+'
        .else
            mov byte ptr [edi+ecx],'-'
            neg eax
        .endif
        inc i

        mov xexp,eax
        mov ecx,[ebx].expwidth
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
        mov [ebx].expwidth,ecx    ; pass back width actually used

        .if ecx >= 4
            xor esi,esi
            .if eax >= 1000
                mov ecx,1000
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub xexp,eax
                mov ecx,[ebx].expwidth
            .endif
            lea eax,[esi+'0']
            mov edx,i
            mov [edi+edx],al
            inc i
        .endif

        .if ecx >= 3
            xor esi,esi
            mov eax,xexp
            .ifs eax >= 100
                mov ecx,100
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub xexp,eax
                mov ecx,[ebx].expwidth
            .endif
            lea eax,[esi+'0']
            mov edx,i
            mov [edi+edx],al
            inc i
        .endif

        .if ecx >= 2
            xor esi,esi
            mov eax,xexp
            .ifs eax >= 10
                mov ecx,10
                xor edx,edx
                div ecx
                mov esi,eax
                mul ecx
                sub xexp,eax
                mov ecx,[ebx].expwidth
            .endif
            lea eax,[esi+'0']
            mov edx,i
            mov [edi+edx],al
            inc i
        .endif

        mov eax,xexp
        add al,'0'
        mov edx,i
        mov [edi+edx],al
        inc edx
        mov eax,edx
        sub eax,[ebx].n1
        mov [ebx].n2,eax
        xor eax,eax
        mov [edi+edx],al
    .endif
toend:
    ret
overflow:
    mov edi,buf
    lea esi,e_space
    mov ecx,sizeof(e_space)
    rep movsb
    jmp toend

_flttostr endp

    assume ebx:nothing

    assume ecx:ptr U128
    assume edx:ptr U128

__cmpq proc A:ptr, B:ptr

    mov ecx,A
    mov edx,B

    .repeat

        .if ( [ecx].u32[0]  == [edx].u32[0] &&
              [ecx].u32[4]  == [edx].u32[4] &&
              [ecx].u32[8]  == [edx].u32[8] &&
              [ecx].u32[12] == [edx].u32[12] )

            xor eax,eax
            .break
        .endif

        .if ( [ecx].i8[15] >= 0 && [edx].i8[15] < 0 )

            mov eax,1
            .break
        .endif

        .if ( [ecx].i8[15] < 0 && [edx].i8[15] >= 0 )

            mov eax,-1
            .break
        .endif

        .if ( [ecx].i8[15] < 0 && [edx].i8[15] < 0 )
            .if ( [edx].u32[12] == [ecx].u32[12] )
                .if ( [edx].u32[8] == [ecx].u32[8] )
                    .if ( [edx].u32[4] == [ecx].u32[4] )
                        mov eax,[ecx].u32
                        cmp [edx].u32,eax
                    .endif
                .endif
            .endif
        .else
            .if ( [ecx].u32[12] == [edx].u32[12] )
                .if ( [ecx].u32[8] == [edx].u32[8] )
                    .if ( [ecx].u32[4] == [edx].u32[4] )
                        mov eax,[edx].u32
                        cmp [ecx].u32,eax
                    .endif
                .endif
            .endif
        .endif
        sbb eax,eax
        sbb eax,-1
    .until 1
    ret

__cmpq endp

    assume ecx:nothing
    assume edx:nothing

; Convert HALF, float, double, long double, string

__cvta_q proc private number:ptr, string:string_t, endptr:ptr string_t

    _strtoflt(string)

    mov ecx,endptr
    .if ecx

        mov edx,[eax].STRFLT.string
        mov [ecx],edx
    .endif

    lea edx,[eax].STRFLT.mantissa
    mov ecx,number
    mov dword ptr [ecx+0x00],[edx+0x00]
    mov dword ptr [ecx+0x04],[edx+0x04]
    mov dword ptr [ecx+0x08],[edx+0x08]
    mov dword ptr [ecx+0x0C],[edx+0x0C]
    mov eax,ecx
    ret

__cvta_q endp


__cvth_q proc private x:ptr, h:ptr

    mov     ecx,h               ; get half value
    movsx   eax,word ptr [ecx]
    mov     ecx,eax             ; get exponent and sign
    shl     eax,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if cl
        .if cl != H_EXPMASK
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if ( eax & 0x7FFFFFFF )
                ;
                ; Invalid exception
                ;
                mov qerrno,EDOM
                mov ecx,0xFFFF
                mov eax,0x40000000 ; QNaN
            .else
                xor eax,eax
            .endif
        .endif
    .elseif eax
        or cx,Q_EXPBIAS-H_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif

    mov     edx,x
    shl     eax,1
    xchg    eax,edx
    mov     [eax+10],edx
    xor     edx,edx
    mov     [eax],edx
    mov     [eax+4],edx
    mov     [eax+8],dx
    shl     ecx,1
    rcr     cx,1
    mov     [eax+14],cx
    ret

__cvth_q endp


__cvtld_q proc private x:ptr, ld:ptr

    mov     eax,x
    mov     ecx,ld
    mov     dx,[ecx+8]
    mov     [eax+14],dx
    mov     edx,[ecx+4]
    mov     ecx,[ecx]
    shl     ecx,1
    rcl     edx,1
    mov     [eax+6],ecx
    mov     [eax+10],edx
    xor     ecx,ecx
    mov     [eax],ecx
    mov     [eax+4],cx
    ret

__cvtld_q endp


__cvtsd_q proc private x:ptr, d:ptr

    mov     ecx,d
    mov     eax,[ecx]
    mov     edx,[ecx+4]
    mov     ecx,edx
    shld    edx,eax,11
    shl     eax,11
    sar     ecx,32-12
    and     cx,0x7FF

    .ifnz
        .if cx != 0x7FF
            add cx,0x3FFF-0x03FF
        .else
            or ch,0x7F
            .if edx & 0x7FFFFFFF || eax
                ;
                ; Invalid exception
                ;
                or edx,0x40000000
            .endif
        .endif
        or  edx,0x80000000
    .elseif edx || eax
        or ecx,0x3FFF-0x03FF+1
        .if !edx
            xchg edx,eax
            sub cx,32
        .endif
        .repeat
            test edx,edx
            .break .ifs
            shl eax,1
            rcl edx,1
        .untilcxz
    .endif
    add     ecx,ecx
    rcr     cx,1
    shl     eax,1
    rcl     edx,1
    push    ebx
    mov     ebx,x
    xchg    eax,ebx
    mov     [eax+6],ebx
    mov     [eax+10],edx
    mov     [eax+14],cx
    xor     ebx,ebx
    mov     [eax],ebx
    mov     [eax+4],bx
    pop     ebx
    ret

__cvtsd_q endp


__cvtss_q proc private x:ptr, f:ptr

    mov ecx,f               ; get float value
    mov eax,[ecx]
    mov ecx,eax             ; get exponent and sign
    shl eax,F_EXPBITS       ; shift fraction into place
    sar ecx,F_SIGBITS-1     ; shift to bottom
    xor ch,ch               ; isolate exponent

    .if cl
        .if cl != 0xFF
            add cx,Q_EXPBIAS-F_EXPBIAS
        .else
            or ch,0x7F
            .if !(eax & 0x7FFFFFFF)
                ;
                ; Invalid exception
                ;
                mov qerrno,EDOM
                or  eax,0x40000000 ; QNaN
            .endif
        .endif
        or eax,0x80000000
    .elseif eax
        or cx,Q_EXPBIAS-F_EXPBIAS+1 ; set exponent
        .while 1
            ;
            ; normalize number
            ;
            test eax,eax
            .break .ifs
            shl eax,1
            dec cx
        .endw
    .endif

    mov     edx,x
    shl     eax,1
    xchg    eax,edx
    mov     [eax+10],edx
    xor     edx,edx
    mov     [eax],edx
    mov     [eax+4],edx
    mov     [eax+8],dx
    shl     ecx,1
    rcr     cx,1
    mov     [eax+14],cx
    ret

__cvtss_q endp


__cvtq_h proc private uses ebx x:ptr, q:ptr

    mov ebx,q
    mov eax,[ebx+10]    ; get top part
    mov cx,[ebx+14]     ; get exponent and sign
    shr eax,1
    .if ecx & Q_EXPMASK
        or eax,0x80000000
    .endif
    mov edx,eax         ; duplicate it
    shl edx,H_SIGBITS+1 ; get rounding bit
    mov edx,0xFFE00000  ; get mask of bits to keep
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [ebx+6] == 0
                shl edx,1
            .endif
        .endif
        add eax,0x80000000 shr (H_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    mov ebx,ecx         ; save exponent and sign
    and cx,Q_EXPMASK    ; if number not 0

    .repeat

        .ifnz
            .if cx == Q_EXPMASK
                .if (eax & 0x7FFFFFFF)
                    mov eax,-1
                    .break
                .endif
                mov eax,0x7C000000 shl 1
                shl bx,1
                rcr eax,1
                .break
            .endif

            add cx,H_EXPBIAS-Q_EXPBIAS
            .ifs
                ;
                ; underflow
                ;
                mov qerrno,ERANGE
                mov eax,0x00010000
                .break
            .endif

            .if cx >= H_EXPMASK || ( cx == H_EXPMASK-1 && eax > edx )
                ;
                ; overflow
                ;
                mov qerrno,ERANGE
                mov eax,0x7BFF0000 shl 1
                shl bx,1
                rcr eax,1
                .break
            .endif

            and  eax,edx ; mask off bottom bits
            shl  eax,1
            shrd eax,ecx,H_EXPBITS
            shl  bx,1
            rcr  eax,1

            .break .ifs cx || eax >= HFLT_MIN
            mov qerrno,ERANGE
            .break
        .endif
        and eax,edx
    .until 1
    shr eax,16
    mov ecx,eax
    mov eax,x
    mov [eax],cx
    .if eax == q
        xor ecx,ecx
        mov [eax+2],cx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
    .endif
    ret
__cvtq_h endp


__cvtq_ss proc uses ebx x:ptr, q:ptr

    mov ebx,q
    mov edx,0xFFFFFF00  ; get mask of bits to keep
    mov eax,[ebx+10]    ; get top part
    mov cx,[ebx+14]
    and ecx,Q_EXPMASK
    neg ecx
    rcr eax,1
    mov ecx,eax         ; duplicate it
    shl ecx,F_SIGBITS+1 ; get rounding bit
    mov cx,[ebx+14]     ; get exponent and sign
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [ebx+6] == 0
                shl edx,1
            .endif
        .endif
        add eax,0x80000000 shr (F_SIGBITS-1)
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc cx
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and eax,edx         ; mask off bottom bits
    mov ebx,ecx         ; save exponent and sign
    and cx,0x7FFF       ; if number not 0
    .ifnz
        .if cx == 0x7FFF
            shl eax,1   ; infinity or NaN
            shr eax,8
            or  eax,0xFF000000
            shl bx,1
            rcr eax,1
        .else
            add cx,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                mov qerrno,ERANGE
                xor eax,eax
            .else
                .ifs cx >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov qerrno,ERANGE
                    mov eax,0x7F800000 shl 1
                    shl bx,1
                    rcr eax,1
                .else
                    shl eax,1
                    shrd eax,ecx,8
                    shl bx,1
                    rcr eax,1
                    .ifs !cx && eax < DDFLT_MIN
                        mov qerrno,ERANGE
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov ecx,eax
    mov eax,x
    mov [eax],ecx
    .if eax == q
        xor ecx,ecx
        mov [eax+4],ecx
        mov [eax+8],ecx
        mov [eax+12],ecx
    .endif
    ret

__cvtq_ss endp


__cvtq_sd proc uses esi edi ebx x:ptr, q:ptr

    mov     eax,q
    movzx   ecx,word ptr [eax+14]
    mov     edx,[eax+10]
    mov     ebx,ecx
    and     ebx,Q_EXPMASK
    mov     edi,ebx
    neg     ebx
    mov     eax,[eax+6]
    rcr     edx,1
    rcr     eax,1
    mov     esi,0xFFFFF800
    mov     ebx,eax
    shl     ebx,22
    .ifc
        .ifz
            shl ebx,1
        .endif
        add eax,0x0800
        adc edx,0
        .ifc
            mov edx,0x80000000
            inc cx
        .endif
    .endif
    and eax,esi
    mov ebx,ecx
    and cx,0x7FFF
    add cx,0x03FF-0x3FFF
    .if cx < 0x07FF
        .if !cx
            shrd eax,edx,12
            shl  edx,1
            shr  edx,12
        .else
            shrd eax,edx,11
            shl  edx,1
            shrd edx,ecx,11
        .endif
        shl bx,1
        rcr edx,1
    .else
        .if cx >= 0xC400
            .ifs cx >= -52
                sub cx,12
                neg cx
                .if cl >= 32
                    sub cl,32
                    mov esi,eax
                    mov eax,edx
                    xor edx,edx
                .endif
                shrd esi,eax,cl
                shrd eax,edx,cl
                shr edx,cl
                add esi,esi
                adc eax,0
                adc edx,0
            .else
                xor eax,eax
                xor edx,edx
                shl ebx,17
                rcr edx,1
            .endif
        .else
            shrd eax,edx,11
            shl edx,1
            shr edx,11
            shl bx, 1
            rcr edx,1
            or  edx,0x7FF00000
        .endif
    .endif
    xor ebx,ebx
    .if edi < 0x3BCC
        mov ecx,q
        .if !(!edi && edi == [ecx+6] && edi == [ecx+10])
            xor eax,eax
            xor edx,edx
            mov ebx,ERANGE
        .endif
    .elseif edi >= 0x3BCD
        mov edi,edx
        and edi,0x7FF00000
        mov ebx,ERANGE
        .ifnz
            .if edi != 0x7FF00000
                xor ebx,ebx
            .endif
        .endif
    .elseif edi >= 0x3BCC
        mov edi,edx
        or  edi,eax
        mov ebx,ERANGE
        .ifnz
            mov edi,edx
            and edi,0x7FF00000
            .ifnz
                xor ebx,ebx
            .endif
        .endif
    .endif
    .if ebx
        mov qerrno,ebx
    .endif
    mov ebx,x
    mov [ebx],eax
    mov [ebx+4],edx
    .if ebx == q
        xor eax,eax
        mov [ebx+8],eax
        mov [ebx+12],eax
    .endif
    mov eax,ebx
    ret

__cvtq_sd endp


__cvtq_ld proc uses ebx x:ptr, q:ptr

    xor ecx,ecx
    mov eax,q
    mov cx,[eax+14]
    mov edx,[eax+10]
    mov ebx,ecx
    and ebx,LD_EXPMASK
    neg ebx
    mov ebx,[eax+6]
    rcr edx,1
    rcr ebx,1

    ; round result

    .ifc
        .if ebx == -1 && edx == -1
            xor ebx,ebx
            mov edx,0x80000000
            inc cx
        .else
            add ebx,1
            adc edx,0
        .endif
    .endif
    mov eax,x
    mov [eax],ebx
    mov [eax+4],edx
    .if eax == q
        mov [eax+8],ecx
        mov dword ptr [eax+12],0
    .else
        mov [eax+8],cx
    .endif
    ret

__cvtq_ld endp


_atoow proc uses esi edi ebx dst:string_t, src:string_t, radix:int_t, bsize:int_t

    mov esi,src
    mov edx,dst
    mov ebx,radix
    mov edi,bsize

ifdef CHEXPREFIX
    movzx eax,word ptr [esi]
    or eax,0x2000
    .if eax == 'x0'
        add esi,2
        sub edi,2
    .endif
endif

    xor eax,eax
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],eax
    mov [edx+12],eax

    .repeat

        .if ebx == 16 && edi <= 16

            ; hex value <= qword

            xor ecx,ecx

            .if edi <= 8

                ; 32-bit value

                .repeat
                    mov al,[esi]
                    add esi,1
                    and eax,not 0x30    ; 'a' (0x61) --> 'A' (0x41)
                    bt  eax,6           ; digit ?
                    sbb ebx,ebx         ; -1 : 0
                    and ebx,0x37        ; 10 = 0x41 - 0x37
                    sub eax,ebx
                    shl ecx,4
                    add ecx,eax
                    dec edi
                .untilz

                mov [edx],ecx
                mov eax,edx
                .break
            .endif

            ; 64-bit value

            xor edx,edx

            .repeat
                mov  al,[esi]
                add  esi,1
                and  eax,not 0x30
                bt   eax,6
                sbb  ebx,ebx
                and  ebx,0x37
                sub  eax,ebx
                shld edx,ecx,4
                shl  ecx,4
                add  ecx,eax
                adc  edx,0
                dec  edi
            .untilz

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx
            .break

        .elseif ebx == 10 && edi <= 20

            xor ecx,ecx

            mov cl,[esi]
            add esi,1
            sub cl,'0'

            .if edi < 10

                .while 1

                    ; FFFFFFFF - 4294967295 = 10

                    dec edi
                    .break .ifz

                    mov al,[esi]
                    add esi,1
                    sub al,'0'
                    lea ebx,[ecx*8+eax]
                    lea ecx,[ecx*2+ebx]
                .endw

                mov [edx],ecx
                mov eax,edx
                .break

            .endif

            xor edx,edx

            .while 1

                ; FFFFFFFFFFFFFFFF - 18446744073709551615 = 20

                dec edi
                .break .ifz

                mov  al,[esi]
                add  esi,1
                sub  al,'0'
                mov  ebx,edx
                mov  bsize,ecx
                shld edx,ecx,3
                shl  ecx,3
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,bsize
                adc  edx,ebx
                add  ecx,eax
                adc  edx,0
            .endw

            mov eax,dst
            mov [eax],ecx
            mov [eax+4],edx

        .else

            mov bsize,edi
            mov edi,edx
            .repeat
                mov al,[esi]
                and eax,not 0x30
                bt  eax,6
                sbb ecx,ecx
                and ecx,0x37
                sub eax,ecx
                mov ecx,8
                .repeat
                    movzx edx,word ptr [edi]
                    imul  edx,ebx
                    add   eax,edx
                    mov   [edi],ax
                    add   edi,2
                    shr   eax,16
                .untilcxz
                sub edi,16
                add esi,1
                dec bsize
            .untilz
            mov eax,dst
        .endif
    .until 1
    ret

_atoow endp

endif

_atoqw proc fastcall uses rbx string:string_t

    xor     edx,edx
    xor     eax,eax
.0:
    mov     dl,[rcx]
    inc     rcx
    cmp     dl,' '
    je      .0
    mov     bl,dl
    cmp     dl,'+'
    je      .1
    cmp     dl,'-'
    jne     .2
.1:
    mov     dl,[rcx]
    inc     rcx
.2:
    sub     dl,'0'
    jb      .3
    cmp     dl,9
    ja      .3
    imul    eax,eax,10
    add     eax,edx
    mov     dl,[rcx]
    inc     rcx
    jmp     .2
.3:
    cmp     bl,'-'
    jne     .4
    neg     eax
.4:
    ret

_atoqw endp


__addq proc __ccall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltadd(&a, &b)
    _fltpackfp(dest, &a)
    ret

__addq endp


__subq proc __ccall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltsub(&a, &b)
    _fltpackfp(dest, &a)
    ret

__subq endp


__mulq proc __ccall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltmul(&a, &b)
    _fltpackfp(dest, &a)
    ret

__mulq endp


__divq proc __ccall dest:ptr, src:ptr

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltdiv(&a, &b)
    _fltpackfp(dest, &a)
    ret

__divq endp


atofloat proc __ccall _out:ptr, inp:string_t, size:uint_t, negative:int_t, ftype:uchar_t

    mov qerrno,0

    ; v2.04: accept and handle 'real number designator'

    .if ( ftype )

        ; convert hex string with float "designator" to float.
        ; this is supposed to work with real4, real8 and real10.
        ; v2.11: use _atoow() for conversion ( this function
        ;    always initializes and reads a 16-byte number ).
        ;    then check that the number fits in the variable.

        lea eax,[tstrlen(inp)-1]
        mov negative,eax

        ; v2.31.24: the size is 2,4,8,10,16
        ; real4 3ff0000000000000r is allowed: real8 -> real16 -> real4

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
            ;
            ; sizes != 4,8,10 or 16 aren't accepted.
            ; Masm ignores silently, JWasm also unless -W4 is set.
            ;
            .if ( Parse_Pass == PASS_1 )
                asmerr( 7004 )
            .endif
            tmemset( _out, 0, size )
        .endsw
    .endif
    ret

atofloat endp


    assume rbx:ptr expr

quad_resize proc __ccall uses rsi rbx opnd:ptr expr, size:int_t

    mov     qerrno,0
    mov     rbx,opnd
    movzx   esi,word ptr [rbx+14]
    and     esi,0x7FFF
    mov     eax,size

    .switch eax
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
