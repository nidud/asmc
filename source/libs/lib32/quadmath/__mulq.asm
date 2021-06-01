; __MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option dotname

__mulq proc uses esi edi ebx A:ptr, B:ptr

  local multiplier  [4]:dword
  local multiplicand[4]:dword
  local result      [8]:dword

    mov     edx,B           ; A(si:ecx:ebx:edx:eax), B(highword(esi):stack)
    mov     ax,[edx]
    shl     eax,16
    mov     edi,[edx+2]
    mov     ebx,[edx+6]
    mov     ecx,[edx+10]
    mov     multiplicand[0],eax
    mov     multiplicand[4],edi
    mov     multiplicand[8],ebx
    mov     multiplicand[12],ecx

    mov     si,[edx+14]
    shl     esi,16

    mov     ecx,A
    mov     ax,[ecx]
    shl     eax,16
    mov     edx,[ecx+2]
    mov     ebx,[ecx+6]
    mov     edi,[ecx+10]
    mov     si,[ecx+14]

    add     si,1            ; validate..
    jc      .error_nan_a
    jo      .error_nan_a
    add     esi,0xFFFF
    jc      .error_nan_b
    jo      .error_nan_b
    sub     esi,0x10000

.if_zero_a:
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     .if_zero_b
    add     si,si
    jz      .error_zero_a
    rcr     si,1

.if_zero_b:
    mov     ecx,multiplicand[0x0]
    or      ecx,multiplicand[0x4]
    or      ecx,multiplicand[0x8]
    or      ecx,multiplicand[0xC]
    jnz     .init_done
    test    esi,0x7FFF0000
    jz      .error_zero_b

.init_done:

    stc
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
    stc
    rcr     multiplicand[0xC],1
    rcr     multiplicand[0x8],1
    rcr     multiplicand[0x4],1
    rcr     multiplicand[0x0],1

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF

.calculate_exponent:
    add     esi,ecx
    sub     si,0x3FFE
    jc      .if_exponent_too_small
    cmp     si,0x7FFF       ; quit if exponent is negative
    ja      .return_overflow
.if_exponent_too_small:
    cmp     si,-65
    jl      .return_underflow

    mov     multiplier[0x0],eax
    mov     multiplier[0x4],edx
    mov     multiplier[0x8],ebx
    mov     multiplier[0xC],edi

    mul     multiplicand[0x0]
    mov     result[0x0],eax
    mov     result[0x4],edx
    mov     eax,multiplier[0x4]
    mul     multiplicand[0x4]
    mov     result[0x8],eax
    mov     result[0xC],edx
    mov     eax,ebx
    mul     multiplicand[0x08]
    mov     result[0x10],eax
    mov     result[0x14],edx
    mov     eax,edi
    mul     multiplicand[0x0C]
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
        mul multiplicand[edx*4]

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
    js      .overflow
    add     ecx,ecx
    adc     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    dec     si

.overflow:

    ;cmp     result[0x20],0
    ;jz      .rounding

.rounding:

    mov     ecx,eax
    and     ecx,0x7FFF
    cmp     ecx,0x1C00
    jb      .validate

    add     eax,0x8000
    adc     edx,0
    adc     ebx,0
    adc     edi,0
    jnc     .validate

    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
    inc     si
    cmp     si,0x7FFF
    je      .return_infinity

.validate:

    test    si,si
    jng     .return_zero
    add     esi,esi
    rcr     si,1

.done:

    add     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    shr     eax,16

.error:

    mov     ecx,A
    mov     [ecx],ax
    mov     [ecx+2],edx
    mov     [ecx+6],ebx
    mov     [ecx+10],edi
    mov     [ecx+14],si
    mov     eax,ecx
    ret

.error_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      .return_zero
    mov     esi,0x8000
    jmp     .error

.error_zero_b:
    test    esi,0x80008000
    jz      .return_zero
    mov     esi,0x80000000
    jmp     .return_b

.return_nan:
    mov     esi,0xFFFF
    mov     edi,0x80000000
    xor     ebx,ebx
    xor     edx,edx
    xor     eax,eax
    jmp     .error

.return_overflow:

.return_infinity:
    mov     esi,0x7FFF
.return_0:
    xor     eax,eax
    xor     edx,edx
    xor     ebx,ebx
    xor     edi,edi
    jmp     .error

.return_underflow:

.return_zero:
    xor     esi,esi
    jmp     .return_0

.return_b:
    mov     eax,multiplicand[0]
    mov     edx,multiplicand[4]
    mov     ebx,multiplicand[8]
    mov     edi,multiplicand[12]
    shr     esi,16
    jmp     .done

.error_nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     .done
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     .done
    xor     esi,0x8000
    jmp     .error
@@:
    sub     esi,0x10000
    mov     ecx,multiplicand[0x0]
    or      ecx,multiplicand[0x4]
    or      ecx,multiplicand[0x8]
    or      ecx,multiplicand[0xC]
    or      ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     @F
    or      esi,-1
    jmp     .return_nan
@@:
    cmp     edi,multiplicand[0xC]
    jb      .return_b
    ja      .done
    cmp     ebx,multiplicand[0x8]
    jb      .return_b
    ja      .done
    cmp     edx,multiplicand[0x4]
    jb      .return_b
    ja      .done
    cmp     eax,multiplicand[0x0]
    jna     .return_b
    jmp     .done

.error_nan_b:
    sub     esi,0x10000
    mov     ecx,multiplicand[0x0]
    or      ecx,multiplicand[0x4]
    or      ecx,multiplicand[0x8]
    or      ecx,multiplicand[0xC]
    jnz     .return_b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .return_b

__mulq endp

    end
