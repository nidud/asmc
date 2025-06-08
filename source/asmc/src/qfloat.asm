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

; Half precision - binary16 -- REAL2 (half)

define H_SIGBITS   11
define H_EXPBITS   5
define H_EXPMASK   ((1 shl H_EXPBITS) - 1)
define H_EXPBIAS   (H_EXPMASK shr 1)
define H_EXPMAX    (H_EXPMASK - H_EXPBIAS)

; Single precision - binary32 -- REAL4 (float)

define F_SIGBITS   24
define F_EXPBITS   8
define F_EXPMASK   ((1 shl F_EXPBITS) - 1)
define F_EXPBIAS   (F_EXPMASK shr 1)
define F_EXPMAX    (F_EXPMASK - F_EXPBIAS)

; Double precision - binary64 -- REAL8 (double)

define D_SIGBITS   53
define D_EXPBITS   11
define D_EXPMASK   ((1 shl D_EXPBITS) - 1)
define D_EXPBIAS   (D_EXPMASK shr 1)
define D_EXPMAX    (D_EXPMASK - D_EXPBIAS)

; Long Double precision - binary80 -- REAL10 (long double)

define LD_SIGBITS  64
define LD_EXPBITS  15
define LD_EXPMASK  ((1 shl LD_EXPBITS) - 1)
define LD_EXPBIAS  (LD_EXPMASK shr 1)
define LD_EXPMAX   (LD_EXPMASK - LD_EXPBIAS)

; Quadruple precision - binary128 -- real16 (__float128)

define Q_SIGBITS   113
define Q_EXPBITS   15
define Q_EXPMASK   ((1 shl Q_EXPBITS) - 1)
define Q_EXPBIAS   (Q_EXPMASK shr 1)
define Q_EXPMAX    (Q_EXPMASK - Q_EXPBIAS)
define Q_DIGITS    38
define Q_SIGDIG    49

.template U128
    union
     i8         sbyte 16 dup(?)
     i16        sword  8 dup(?)
     i32        sdword 4 dup(?)
     i64        sqword 2 dup(?)
     u8         byte  16 dup(?)
     u16        word   8 dup(?)
     u32        dword  4 dup(?)
     u64        qword  2 dup(?)
     u128       oword  ?
    ends
   .ends


.template EXTFLOAT      ; extended (134-bit, 128+16) float
    l           uint64_t ?
    h           uint64_t ?
    e           short_t ?
   .ends


.template STRFLT
    mantissa    EXTFLOAT <> ; 128-bit mantissa
    flags       int_t ?     ; parsing flags
    exponent    int_t ?     ; exponent of floating point number
    string      string_t ?  ; pointer to buffer or string
   .ends

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

     flt STRFLT { { 0, 0, 0 }, 0, 0, 0 }
     qerrno errno_t 0
     e_space char_t "#not enough space",0

    .code

    option dotname

; 128-bit unsigned integer functions

ifdef _WIN64

__mulo proc __ccall multiplier:ptr uint128_t, multiplicand:ptr uint128_t, highproduct:ptr uint128_t

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

else

    ; ecx:ebx:edx:eax = edx:eax * ecx:ebx

_mulqw proc watcall private a64_l:uint_t, a64_h:uint_t, b64_l:uint_t, b64_h:uint_t

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

_mulqw endp

    assume esi:ptr U128
    assume edi:ptr U128

__mulo proc __ccall uses esi edi ebx multiplier:ptr uint128_t, multiplicand:ptr uint128_t, highproduct:ptr uint128_t

  local n[8]:dword ; 256-bit result

    mov edi,multiplier
    mov esi,multiplicand

    _mulqw( [edi].u32[0], [edi].u32[4], [esi].u32[0], [esi].u32[4] )

    mov n[0x00],eax
    mov n[0x04],edx
    mov n[0x08],ebx
    mov n[0x0C],ecx

    _mulqw( [edi].u32[8], [edi].u32[12], [esi].u32[8], [esi].u32[12] )

    mov n[0x10],eax
    mov n[0x14],edx
    mov n[0x18],ebx
    mov n[0x1C],ecx

    _mulqw( [edi].u32[0], [edi].u32[4], [esi].u32[8], [esi].u32[12] )

    add n[0x08],eax
    adc n[0x0C],edx
    adc n[0x10],ebx
    adc n[0x14],ecx
    adc n[0x18],0
    adc n[0x1C],0

    _mulqw( [edi].u32[8], [edi].u32[12], [esi].u32[0], [esi].u32[4] )

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

    assume esi:nothing
    assume edi:nothing

endif

ifdef _WIN64

__divo proc __ccall dividend:ptr uint128_t, divisor:ptr uint128_t, reminder:ptr uint128_t

    mov     r9,[rcx]
    mov     rcx,[rcx+size_t]
    mov     r10,[rdx]
    mov     r11,[rdx+size_t]
    xor     eax,eax ; quotient
    xor     edx,edx
    test    r10,r10
    jnz     .not_zero
    test    r11,r11
    jnz     .not_zero
    xor     r9d,r9d
    xor     ecx,ecx
    jmp     .done

.not_zero:

    ; if divisor > dividend : reminder = dividend, quotient = 0

    cmp     r11,rcx
    jne     .is_above
    cmp     r10,r9

.is_above:

    ja      .done
    jnz     .divide

.is_equal:  ; if divisor == dividend :

    xor     r9d,r9d  ; reminder = 0
    xor     ecx,ecx
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
    cmp     r10,r9
    jc      .0
    jz      .0
.1:
    rcr     r11,1
    rcr     r10,1
    sub     r9,r10
    sbb     rcx,r11
    cmc
    jc      .4
.2:
    add     rax,rax
    adc     rdx,rdx
    dec     r8d
    jns     .3
    add     r9,r10
    adc     rcx,r11
    jmp     .done
.3:
    shr     r11,1
    rcr     r10,1
    add     r9,r10
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

    mov     [r10],r9
    mov     [r10+8],rcx

.5:
    mov     r10,rax
    mov     rax,dividend
    mov     [rax],r10
    mov     [rax+8],rdx
    ret

__divo endp

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
    mov     ecx,[ecx+4]
    mov     e10,[edx]
    mov     e11,[edx+4]
    mov     e12,[edx+8]
    mov     e13,[edx+12]

    xor     esi,esi
    xor     eax,eax ; quotient
    xor     edx,edx

    cmp     eax,e10
    jnz     .not_zero
    cmp     eax,e11
    jnz     .not_zero
    cmp     eax,e12
    jnz     .not_zero
    cmp     eax,e13
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
    ret

__divo endp

    option stackbase:ebp

endif


ifdef _WIN64

__shlo proc __ccall val:ptr uint128_t, count:int_t, bits:int_t

    mov r10,rcx
    mov ecx,edx

    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 ) )

        xor eax,eax
        xor edx,edx

    .elseif ( r8d == 128 )

        .while ( ecx >= 64 )

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
    mov rax,r10

else

    assume esi:ptr U128

__shlo proc __ccall uses esi edi ebx val:ptr uint128_t, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].u32[0]
    mov edx,[esi].u32[4]
    mov ebx,[esi].u32[8]
    mov edi,[esi].u32[12]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && bits < 128 ) )

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif ( bits == 128 )

        .while ( ecx >= 32 )

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

        .if ( cl < 32 )

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

    assume edi:nothing

endif
    ret

__shlo endp

ifdef _WIN64

__shro proc __ccall val:ptr uint128_t, count:int_t, bits:int_t

    mov r10,rcx
    mov ecx,edx
    mov rax,[r10]
    mov rdx,[r10+8]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && r8d < 128 ) )

        xor edx,edx
        xor eax,eax

    .elseif ( r8d == 128 )

        .while ( ecx > 64 )

            mov rax,rdx
            xor edx,edx
            sub ecx,64
        .endw
        shrd rax,rdx,cl
        shr rdx,cl

    .else

        .if ( eax == -1 && r8d == 32 )

            and eax,eax
        .endif
        shr rax,cl
    .endif

    mov [r10],rax
    mov [r10+8],rdx
    mov rax,r10
    ret

__shro endp

else

    assume esi:ptr U128

__shro proc uses esi edi ebx val:ptr uint128_t, count:int_t, bits:int_t

    mov esi,val
    mov ecx,count

    mov eax,[esi].u32[0]
    mov edx,[esi].u32[4]
    mov ebx,[esi].u32[8]
    mov edi,[esi].u32[12]

    .if ( ( ecx >= 128 ) || ( ecx >= 64 && bits < 128 ) )

        xor edi,edi
        xor ebx,ebx
        xor edx,edx
        xor eax,eax

    .elseif ( bits == 128 )

        .while ( ecx > 32 )

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

        .if ( eax == -1 && bits == 32 )

            xor edx,edx
        .endif

        .if ( ecx < 32 )

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

    assume esi:nothing

endif

__rolo proc __ccall uses rsi rdi rbx val:ptr uint128_t, count:int_t, bits:int_t

    ldr rsi,val
    ldr edi,bits

    .while count

        mov ecx,edi
        shr ecx,3
        movzx ebx,byte ptr [rsi+rcx-1]
        __shlo(rsi, 1, edi)

        shr ebx,7
        or  [rsi],bl
        dec count
    .endw
    mov rax,rsi
    ret

__rolo endp


__roro proc __ccall uses rsi rdi rbx val:ptr uint128_t, count:int_t, bits:int_t

    ldr rsi,val
    ldr edi,bits

    .while count

        mov bl,[rsi]
        __shro(rsi, 1, edi)

        shl ebx,7
        mov ecx,edi
        shr ecx,3
        or  [rsi+rcx-1],bl
        dec count
    .endw
    mov rax,rsi
    ret

__roro endp


    assume rsi:ptr U128

__saro proc __ccall uses rsi rdi rbx val:ptr uint128_t, count:int_t, bits:int_t

    ldr rsi,val
    ldr ecx,count

    mov eax,[rsi].u32[0]
    mov edx,[rsi].u32[4]
    mov ebx,[rsi].u32[8]
    mov edi,[rsi].u32[12]

    .if ( ecx >= 64 && bits <= 64 )

        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor edi,edi

    .elseif ( ecx >= 128 && bits == 128 )

        sar edi,31
        mov ebx,edi
        mov edx,edi
        mov eax,edi

    .elseif ( bits == 128 )

        .while ( ecx > 32 )

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

        .if ( eax == -1 && bits == 32 )

            xor edx,edx
        .endif

        .if ( bits == 32 )

            sar eax,cl

        .elseif ( ecx < 32 )

            shrd eax,edx,cl
            sar edx,cl

        .else

            mov eax,edx
            sar edx,31
            and cl,32-1
            sar eax,cl
        .endif
    .endif

    mov [rsi].u32[0],eax
    mov [rsi].u32[4],edx
    mov [rsi].u32[8],ebx
    mov [rsi].u32[12],edi
    mov rax,rsi
    ret

__saro endp

    assume rsi:nothing


; Convert HALF, float, double, long double, int, __int64, string

; Quad to half

HFLT_MAX equ 0x7BFF
HFLT_MIN equ 0x0001

__cvtq_h proc __ccall private uses rsi rdi rbx h:ptr half_t, q:ptr qfloat_t

    ldr rsi,q
    ldr rdi,h

    mov eax,[rsi+10]    ; get top part
    mov cx,[rsi+14]     ; get exponent and sign
    shr eax,1

    .if ( ecx & Q_EXPMASK )
        or eax,0x80000000
    .endif

    mov edx,eax         ; duplicate it
    shl edx,H_SIGBITS+1 ; get rounding bit
    mov edx,0xFFE00000  ; get mask of bits to keep

    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if ( dword ptr [rsi+6] == 0 )
                shl edx,1
            .endif
        .endif
        add eax,0x80000000 shr ( H_SIGBITS-1 )
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
            .if ( cx == Q_EXPMASK )

                .if ( eax & 0x7FFFFFFF )

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

            .if ( cx >= H_EXPMASK || ( cx == H_EXPMASK-1 && eax > edx ) )
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

            .break .ifs ( cx || eax >= HFLT_MIN )

            mov ebx,eax
            mov qerrno,ERANGE
            mov eax,ebx
           .break
        .endif
        and eax,edx
    .until 1

    shr eax,16
    mov ecx,eax

    mov rax,rdi
    mov [rax],cx

    .if ( rax == rsi )

        xor ecx,ecx
        mov [rax+2],cx
        mov [rax+4],ecx
        mov [rax+8],ecx
        mov [rax+12],ecx
    .endif
    ret

__cvtq_h endp

; Quad to float
;

DDFLT_MAX equ 0x7F7FFFFF
DDFLT_MIN equ 0x00800000

__cvtq_ss proc __ccall uses rbx s:ptr float_t, q:ptr qfloat_t

    ldr rbx,q

    mov edx,0xFFFFFF00  ; get mask of bits to keep
    mov eax,[rbx+10]    ; get top part
    mov cx,[rbx+14]
    and ecx,Q_EXPMASK
    neg ecx
    rcr eax,1
    mov ecx,eax         ; duplicate it
    shl ecx,F_SIGBITS+1 ; get rounding bit
    mov cx,[rbx+14]     ; get exponent and sign

    .ifc                ; if have to round
        .ifz            ; - if half way between

            .if ( dword ptr [rbx+6] == 0 )

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
        .if ( cx == 0x7FFF )

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

                .ifs ( cx >= 0x00FF )
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

                    .ifs ( !cx && eax < DDFLT_MIN )
                        mov ebx,eax
                        mov qerrno,ERANGE
                        mov eax,ebx
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov ecx,eax

    mov rax,s
    mov [rax],ecx
    .if ( rax == q )

        xor ecx,ecx
        mov [rax+4],ecx
        mov [rax+8],ecx
        mov [rax+12],ecx
    .endif
    ret

__cvtq_ss endp


; Quad to double

__cvtq_sd proc __ccall uses rsi rdi rbx d:ptr double_t, q:ptr qfloat_t

    ldr     rax,q

    movzx   ecx,word ptr [rax+14]
    mov     edx,[rax+10]
    mov     ebx,ecx
    and     ebx,Q_EXPMASK
    mov     edi,ebx
    neg     ebx
    mov     eax,[rax+6]
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
        mov rcx,q
        .if !(!edi && edi == [rcx+6] && edi == [rcx+10])
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

    mov rdi,d
    mov [rdi],eax
    mov [rdi+4],edx
    .if ebx
        mov qerrno,ebx
    .endif

    .if ( rdi == q )

        xor eax,eax
        mov [rdi+8],eax
        mov [rdi+12],eax
    .endif
    .return( rdi )

__cvtq_sd endp


__cvtq_ld proc __ccall uses rsi rdi rbx ld:ptr ldouble_t, q:ptr qfloat_t

    ldr     rax,ld
    ldr     rdi,q

    xor     ecx,ecx
    mov     ebx,[rdi+6]
    mov     edx,[rdi+10]
    mov     cx, [rdi+14]
    mov     esi,ecx
    and     esi,LD_EXPMASK
    neg     esi
    rcr     edx,1
    rcr     ebx,1

    ; round result

    .ifc
        .if ( ebx == -1 && edx == -1 )
            xor ebx,ebx
            mov edx,0x80000000
            inc cx
        .else
            add ebx,1
            adc edx,0
        .endif
    .endif

    mov [rax],ebx
    mov [rax+4],edx
    .if ( rax == rdi )
        mov [rax+8],ecx
        mov dword ptr [rax+12],0
    .else
        mov [rax+8],cx
    .endif
    ret

__cvtq_ld endp


__cvth_q proc __ccall private q:ptr qfloat_t, h:ptr half_t

    ldr     rax,q
    ldr     rdx,h

    movsx   edx,word ptr [rdx]
    mov     ecx,edx             ; get exponent and sign
    shl     edx,H_EXPBITS+16    ; shift fraction into place
    sar     ecx,15-H_EXPBITS    ; shift to bottom
    and     cx,H_EXPMASK        ; isolate exponent

    .if ( cl )
        .if ( cl != H_EXPMASK )
            add cx,Q_EXPBIAS-H_EXPBIAS
        .else
            or cx,0x7FE0
            .if ( edx & 0x7FFFFFFF )
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

    .elseif ( edx )

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

    shl ecx,1
    rcr cx,1
    mov [rax+14],cx
    shl edx,1
    mov [rax+10],edx
    xor edx,edx
    mov [rax],rdx
ifndef _WIN64
    mov [rax+4],edx
endif
    mov [rax+8],edx
    ret

__cvth_q endp


__cvtss_q proc __ccall private q:ptr qfloat_t, f:ptr float_t

    ldr rax,q
    ldr rdx,f

    mov edx,[rdx]
    mov ecx,edx     ; get exponent and sign
    shl edx,8       ; shift fraction into place
    sar ecx,32-9    ; shift to bottom
    xor ch,ch       ; isolate exponent

    .if cl
        .if ( cl != 0xFF )
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

    add ecx,ecx
    rcr cx,1
    mov [rax+14],cx
    shl edx,1
    mov [rax+10],edx
    xor edx,edx
    mov [rax],edx
    mov [rax+4],edx
    mov [eax+8],dx
    ret

__cvtss_q endp


__cvtsd_q proc __ccall private uses rbx q:ptr qfloat_t, d:ptr double_t

    ldr     rbx,q
    ldr     rdx,d

    mov     eax,[rdx]
    mov     edx,[rdx+4]
    mov     ecx,edx
    shld    edx,eax,11
    shl     eax,11
    sar     ecx,32-12
    and     cx,0x7FF

    .ifnz
        .if ( cx != 0x7FF )
            add cx,0x3FFF-0x03FF
        .else
            or ch,0x7F
            .if ( edx & 0x7FFFFFFF || eax )
                ;
                ; Invalid exception
                ;
                or edx,0x40000000
            .endif
        .endif
        or  edx,0x80000000
    .elseif ( edx || eax )
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

    xchg    rax,rbx
    mov     [rax+6],ebx
    mov     [rax+10],edx
    mov     [rax+14],cx
    xor     ebx,ebx
    mov     [rax],ebx
    mov     [rax+4],bx
    ret

__cvtsd_q endp


__cvtld_q proc __ccall private x:ptr qfloat_t, ld:ptr ldouble_t

ifdef _WIN64
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
else
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
endif
    ret

__cvtld_q endp


__cmpq proc __ccall A:ptr qfloat_t, B:ptr qfloat_t

    ldr rcx,A
    ldr rdx,B

    .if ( [rcx].U128.u64[0] == [rdx].U128.u64[0] &&
          [rcx].U128.u64[8] == [rdx].U128.u64[8] )
        .return( 0 )
    .endif
    .if ( [rcx].U128.i8[15] >= 0 && [rdx].U128.i8[15] < 0 )
        .return( 1 )
    .endif
    .if ( [rcx].U128.i8[15] < 0 && [rdx].U128.i8[15] >= 0 )
        .return( -1 )
    .endif
    .if ( [rcx].U128.i8[15] < 0 )
        .if ( [rdx].U128.u64[8] == [rcx].U128.u64[8] )
            cmp [rdx].U128.u64,[rcx].U128.u64
        .endif
    .elseif ( [rcx].U128.u64[8] == [rdx].U128.u64[8] )
        cmp [rcx].U128.u64,[rdx].U128.u64
    .endif
    sbb eax,eax
    sbb eax,-1
    ret

__cmpq endp


_fltunpack proc __ccall private p:ptr STRFLT, q:ptr
ifdef _WIN64
    mov     rax,[rdx]
    mov     r8,[rdx+8]
    shld    r9,r8,16
    shld    r8,rax,16
    shl     rax,16
    mov     [rcx].STRFLT.mantissa.e,r9w
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     r8,1
    rcr     rax,1
    mov     [rcx].STRFLT.mantissa.l,rax
    mov     [rcx].STRFLT.mantissa.h,r8
    mov     rax,rcx
else
    push    esi
    push    edi
    mov     edi,p
    mov     esi,q
    mov     ax,[esi]
    shl     eax,16
    mov     dx,[esi+14]
    mov     [edi].STRFLT.mantissa.e,dx
    and     dx,Q_EXPMASK
    neg     dx
    mov     edx,[esi+2]
    mov     ecx,[esi+6]
    mov     esi,[esi+10]
    rcr     esi,1
    rcr     ecx,1
    rcr     edx,1
    rcr     eax,1
    mov     dword ptr [edi].STRFLT.mantissa.l[0],eax
    mov     dword ptr [edi].STRFLT.mantissa.l[4],edx
    mov     dword ptr [edi].STRFLT.mantissa.h[0],ecx
    mov     dword ptr [edi].STRFLT.mantissa.h[4],esi
    mov     eax,edi
    pop     edi
    pop     esi
endif
    ret

_fltunpack endp


    assume rcx:ptr STRFLT

_fltround proc __ccall private fp:ptr STRFLT

    ldr rcx,fp
ifdef _WIN64
    mov rax,[rcx].mantissa.l
else
    mov eax,dword ptr [ecx].mantissa.l[0]
endif

    .if ( eax & 0x4000)

ifdef _WIN64
        mov rdx,[rcx].mantissa.h
else
        push esi
        push edi

        mov edx,dword ptr [ecx].mantissa.l[4]
        mov edi,dword ptr [ecx].mantissa.h[0]
        mov esi,dword ptr [ecx].mantissa.h[4]
endif
        add rax,0x4000
        adc rdx,0
ifndef _WIN64
        adc edi,0
        adc esi,0
endif
        .ifc

ifndef _WIN64
            rcr esi,1
            rcr edi,1
endif
            rcr rdx,1
            rcr rax,1
            inc [rcx].mantissa.e

            .if ( [rcx].mantissa.e == Q_EXPMASK )

                mov [rcx].mantissa.e,0x7FFF
                xor eax,eax
                xor edx,edx
ifndef _WIN64
                xor edi,edi
                xor esi,esi
endif
            .endif
        .endif
ifdef _WIN64
        mov [rcx].mantissa.l,rax
        mov [rcx].mantissa.h,rdx
else
        mov dword ptr [ecx].mantissa.l[0],eax
        mov dword ptr [ecx].mantissa.l[4],edx
        mov dword ptr [ecx].mantissa.h[0],edi
        mov dword ptr [ecx].mantissa.h[4],esi
        pop edi
        pop esi
endif
    .endif
    .return rcx

_fltround endp

    assume rcx:nothing


ifdef _WIN64

_fltpackfp proc __ccall private dst:ptr, src:ptr STRFLT

    _fltround( rdx )

    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
    mov     cx, [rcx].STRFLT.mantissa.e
    shl     rax,1
    rcl     rdx,1
    shrd    rax,rdx,16
    shrd    rdx,rcx,16
    mov     rcx,dst
    mov     [rcx],rax
    mov     [rcx+8],rdx
    mov     rax,rcx

else

_fltpackfp proc __ccall private uses esi edi ebx q:ptr, p:ptr STRFLT

    mov esi,p
    mov edi,q

    _fltround( esi )

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
endif
    ret

_fltpackfp endp


_lc_fltadd proc __ccall private uses rsi rdi rbx A:ptr STRFLT, B:ptr STRFLT, negate:uint_t

ifdef _WIN64
    mov     r11,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
else
   .new     r9d:dword
   .new     r8d:dword
   .new     b[4]:dword
    mov     edx,B
    mov     b[0x0],[edx+0x0]
    mov     b[0x4],[edx+0x4]
    mov     b[0x8],[edx+0x8]
    mov     b[0xC],[edx+0xC]
endif
    mov     si,[rdx].STRFLT.mantissa.e
    shl     esi,16

ifdef _WIN64
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
else
    mov     ecx,A
    mov     eax,[ecx+0x0]
    mov     edx,[ecx+0x4]
    mov     ebx,[ecx+0x8]
    mov     edi,[ecx+0xC]
endif

    mov     si,[rcx].STRFLT.mantissa.e
    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000
ifdef _WIN64
    xor     esi,r8d         ; flip sign if subtract
    mov     rcx,rax
    or      rcx,rdx
else
    xor     esi,negate
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
endif
    jz      .zero_a

if_zero_b:
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
endif
    jz      .zero_b

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
    jz      .e2
    jnb     .e1
    mov     r9d,esi         ; get larger exponent for result
    neg     cx              ; negate the shift count
ifdef _WIN64
    xchg    rax,rbx         ; flip operands
    xchg    rdx,rdi
else
    push    ecx
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
endif
.e1:
    cmp     cx,128          ; if shift count too big
    jna     .e2
    mov     esi,r9d
    shl     esi,1           ; get sign
    rcr     si,1            ; merge with exponent
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
endif
    jmp     .done
.e2:
    mov     esi,r9d         ; zero extend B
    mov     ch,0            ; get bit 0 of sign word - value is 0 if
    test    ecx,ecx         ; both operands have same sign, 1 if not
    jns     .s0             ; if signs are different
    mov     ch,-1           ; - set high part to ones
ifdef _WIN64
    neg     rdi
    neg     rbx
    sbb     rdi,0
else
    neg     b[0xC]
    neg     b[0x8]
    sbb     b[0xC],0
    neg     b[0x4]
    sbb     b[0x8],0
    neg     b[0x0]
    sbb     b[0x4],0
endif
    xor     esi,0x80000000  ; - flip sign
.s0:
    mov     r8d,0           ; get a zero for sticky bits
    test    cl,cl           ; if shifting required
    jz      .m1
    cmp     cl,64           ; if shift count >= 64
    jb      .s4
    test    rax,rax         ; check low order qword for 1 bits
ifndef _WIN64
    jnz     .s1
    test    edx,edx
endif
    jz      .s2
.s1:
    inc     r8d             ; 1 if non zero
.s2:
    cmp     cl,128          ; if shift count is 128
    jne     .s3
ifdef _WIN64
    shr     rdx,32          ; get rest of sticky bits from high part
    or      r8d,edx
    xor     edx,edx         ; zero high part
else
    or      r8d,edi
    xor     ebx,ebx
    xor     edi,edi
endif
.s3:
ifdef _WIN64
    mov     rax,rdx         ; shift right 64
    xor     edx,edx
else
    mov     eax,ebx
    mov     edx,edi
    xor     ebx,ebx
    xor     edi,edi
endif
.s4:
ifdef _WIN64
    xor     r9d,r9d
    shrd    r9d,eax,cl      ; get the extra sticky bits
    or      r8d,r9d         ; save them
    shrd    rax,rdx,cl      ; align the fractions
    shr     rdx,cl
else
    push    ebx
    xor     ebx,ebx
    shrd    ebx,eax,cl
    or      r8d,ebx
    pop     ebx
    push    ecx
    and     ecx,64-1
    cmp     cl,32           ; MOD 64..
    jb      .s5
    mov     eax,edx
    mov     edx,ebx
    mov     ebx,edi
    xor     edi,edi
.s5:
    shrd    eax,edx,cl
    shrd    edx,ebx,cl
    shrd    ebx,edi,cl
    shr     edi,cl
    pop     ecx
endif
.m1:
ifdef _WIN64
    add     rax,rbx         ; add the fractions
    adc     rdx,rdi
else
    add     eax,b[0x0]
    adc     edx,b[0x4]
    adc     ebx,b[0x8]
    adc     edi,b[0xC]
endif
    adc     ch,0
    jns     .m3             ; if is negative
    cmp     cl,128
    jne     .m2
    test    r8d,0x7FFFFFFF
    jz      .m2
ifdef _WIN64
    add     rax,1           ; round up fraction if required
    adc     rdx,0
else
    adc     eax,1           ; ??
    adc     edx,0
    adc     ebx,0
    adc     edi,0
endif
.m2:
ifdef _WIN64
    neg     rdx             ; negate the fraction
    neg     rax
    sbb     rdx,0
else
    neg     edi
    neg     ebx
    sbb     edi,0
    neg     edx
    sbb     ebx,0
    neg     eax
    sbb     edx,0
endif
    xor     ch,ch           ; zero top bits
    xor     esi,0x80000000  ; flip the sign
.m3:
ifdef _WIN64
    mov     r9d,ecx         ; check for zero
    and     r9d,0xFF00
    or      r9,rax
    or      r9,rdx
else
    push    ecx
    movzx   ecx,ch
    or      ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    pop     ecx
endif
    jnz     .m4
    xor     esi,esi
.m4:
    test    si,si
    jz      .done

    test    ch,ch           ; if top bits are 0
    mov     ecx,r8d
    jnz     .validate
    rol     ecx,1           ; set carry from last sticky bit
    rol     ecx,1

.dec_exponent:
    dec     si              ; preserve the state of the CF flag..
    jz      .denormal
    adc     rax,rax
    adc     rdx,rdx
ifndef _WIN64
    adc     ebx,ebx
    adc     edi,edi
endif
    jnc     .dec_exponent

.validate:

    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow
    stc
ifndef _WIN64
    rcr     edi,1
    rcr     ebx,1
endif
    rcr     rdx,1
    rcr     rax,1
    add     ecx,ecx
    jnc     .denormal
    adc     rax,0
    adc     rdx,0
ifndef _WIN64
    adc     ebx,0
    adc     edi,0
endif
    jnc     .denormal
ifndef _WIN64
    rcr     edi,1
    rcr     ebx,1
endif
    rcr     rdx,1
    rcr     rax,1
    inc     si
    cmp     si,Q_EXPMASK
    je      .overflow

.denormal:
    add     esi,esi
    rcr     si,1

.done:
ifdef _WIN64
    mov     [r11].STRFLT.mantissa.l,rax
    mov     [r11].STRFLT.mantissa.h,rdx
    mov     [r11].STRFLT.mantissa.e,si
    mov     rax,r11
else
    mov     ecx,A
    mov     [ecx+0x0],eax
    mov     [ecx+0x4],edx
    mov     [ecx+0x8],ebx
    mov     [ecx+0xC],edi
    mov     [ecx+16],si
    mov     eax,ecx
endif
    ret

.zero_a:
    shl     si,1            ; place sign in carry
    jnz     .zero_a_0
    shr     esi,16          ; return B
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
endif
    shl     esi,1
ifdef _WIN64
    mov     rcx,rax         ; if not zero
    or      rcx,rdx
else
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
endif
    jz      .done
    shr     esi,1           ; -> restore sign bit
    jmp     .done
.zero_a_0:
    rcr     si,1            ; put back the sign
    jmp     if_zero_b

.zero_b:
    test    esi,0x7FFF0000
    jz      .done
    jmp     calculate_exponent

.nan:
    mov     esi,0xFFFF
ifdef _WIN64
    mov     rdx,0x4000000000000000
else
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
endif
    xor     eax,eax
    jmp     .done

.overflow:
.infinity:
    mov     esi,0x7FFF
    xor     eax,eax
    xor     edx,edx
ifndef _WIN64
    xor     ebx,ebx
    xor     edi,edi
endif
    jmp     .done

.b:
ifdef _WIN64
    mov     rax,rbx
    mov     rdx,rdi
else
    mov     eax,b[0x0]
    mov     edx,b[0x4]
    mov     ebx,b[0x8]
    mov     edi,b[0xC]
endif
    shr     esi,16
    jmp     .done

.nan_a:
    dec     si
    add     esi,0x10000
    jb      .0
    jo      .0
    jns     .done
    mov     rcx,rax
    or      rcx,rdx
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
    jnz     .done
    xor     esi,0x8000
    jmp     .done
.0:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
ifndef _WIN64
    or      ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
endif
    jnz     .1
    or      esi,-1
    jmp     .nan
.1:
ifdef _WIN64
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
else
    cmp     edi,b[0xC]
    jb      .b
    ja      .done
    cmp     ebx,b[0x8]
    jb      .b
    ja      .done
    cmp     edx,b[0x4]
    jb      .b
    ja      .done
    cmp     eax,b[0x0]
endif
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,b[0x0]
    or      ecx,b[0x4]
    or      ecx,b[0x8]
    or      ecx,b[0xC]
endif
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_lc_fltadd endp


_fltadd proc fastcall private a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd( rcx, rdx, 0 )
    ret

_fltadd endp


_fltsub proc fastcall private a:ptr STRFLT, b:ptr STRFLT

    _lc_fltadd( rcx, rdx, 0x80000000 )
    ret

_fltsub endp


ifdef _WIN64

    assume rdx:ptr STRFLT
    assume rcx:ptr STRFLT

_fltdiv proc __ccall private uses rsi rdi rbx r12 r13 a:ptr STRFLT, b:ptr STRFLT

    mov     rbx,[rdx].mantissa.l
    mov     rdi,[rdx].mantissa.h
    mov     si, [rdx].mantissa.e
    shl     esi,16
    mov     rax,[rcx].mantissa.l
    mov     rdx,[rcx].mantissa.h
    mov     si, [rcx].mantissa.e

    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000
    mov     rcx,rbx
    or      rcx,rdi
    jz      .zero_b

.if_zero_a:
    mov     rcx,rax
    or      rcx,rdx
    jz      .zero_a

.init_done:

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
    jz      .normalize_a
.if_denormal_b:
    test    si,si
    jz      .normalize_b

.calculate_exponent:
    sub     cx,si
    add     cx,0x3FFF
    js      .too_small
    cmp     cx,0x7FFF
    ja      .infinity
.too_small:
    cmp     cx,-65
    jl      .underflow

.divide:

    define  BITS 14
    mov     r13,rcx

    mov     r12,rbp
    shrd    rax,rdx,BITS
    shr     rdx,BITS
    shrd    rbx,rdi,BITS
    shr     rdi,BITS
    mov     ecx,113 + (16 - BITS)

    mov     rbp,rdi         ; rbp:rbx - ebp:ebx:edx:esi
    mov     r10,rax         ; r11:r10 - reminder
    mov     r11,rdx

    xor     eax,eax         ; rdx:rax - quotient
    xor     edx,edx
    xor     r8d,r8d         ; r9:r8   - divisor
    xor     r9d,r9d
    xor     edi,edi         ; rsi:rdi - dividend
    xor     esi,esi

    add     rbx,rbx
    adc     rbp,rbp

.divide_1:
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    sub     rdi,r8
    sbb     rsi,r9
    sbb     r10,rbx
    sbb     r11,rbp
    cmc
    jc      .divide_3

.divide_2:
    add     rax,rax
    adc     rdx,rdx
    dec     ecx
    jz      .end_divide
    shr     rbp,1
    rcr     rbx,1
    rcr     r9,1
    rcr     r8,1
    add     rdi,r8
    adc     rsi,r9
    adc     r10,rbx
    adc     r11,rbp
    jnc     .divide_2

.divide_3:
    adc     rax,rax
    adc     rdx,rdx
    dec     ecx
    jnz     .divide_1

.end_divide:

    mov     rsi,r13
    mov     rbp,r12
    dec     si

.rounding:

    bt      rax,0
    adc     rax,0
    adc     rdx,0

.overflow:
    bt      rdx,64 - BITS ; overflow bit
    jnc     .reset

    rcr     rdx,1
    rcr     rax,1
    add     esi,1

.reset:
    shld    rdx,rax,BITS
    shl     rax,BITS

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

    mov     rcx,a
    mov     [rcx].mantissa.l,rax
    mov     [rcx].mantissa.h,rdx
    mov     [rcx].mantissa.e,si
    mov     rax,rcx
    ret

.normalize_a:
    dec     cx
    add     rax,rax
    adc     rdx,rdx
    jnc     .normalize_a
    jmp     .if_denormal_b

.normalize_b:
    dec     si
    add     rbx,rbx
    adc     rdi,rdi
    jnc     .normalize_b
    jmp     .calculate_exponent

.zero_a:
    add     si,si
    jz      .za_0
    rcr     si,1
    jmp     .init_done
.za_0:
    rcr     si,1
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x8000
    jmp     .done

.zero_b:
    test    esi,0x7FFF0000
    jnz     .if_zero_a
    mov     rcx,rax
    or      rcx,rdx
    jnz     .infinity
    mov     ecx,esi
    add     cx,cx
    jnz     .infinity

.nan:
    mov     esi,0xFFFF
    mov     rdx,0x4000000000000000
    xor     eax,eax
    jmp     .done

.underflow:
    and     cx,0x7FFF
    cmp     cx,0x3FFF
    jae     .zero

.infinity:
    mov     esi,0x7FFF
.0:
    xor     eax,eax
    xor     edx,edx
    jmp     .done

.zero:
    xor     esi,esi
    jmp     .0

.b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     .done

.nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     .done
    mov     rcx,rax
    or      rcx,rdx
    jnz     .done
    xor     esi,0x8000
    jmp     .done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jz      .nan
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    mov     rcx,rbx
    or      rcx,rdi
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_fltdiv endp

    assume rdx:nothing
    assume rcx:nothing

else

    option stackbase:esp

_fltdiv proc __ccall private uses esi edi ebx ebp a:ptr STRFLT, b:ptr STRFLT

    local   exp:dword
    local   dividend[4]:dword
    local   divisor [4]:dword
    local   reminder[4]:dword
    local   quotient[4]:dword

    mov     edx,b
    mov     divisor[0x0],[edx+0x0]
    mov     divisor[0x4],[edx+0x4]
    mov     divisor[0x8],[edx+0x8]
    mov     divisor[0xC],[edx+0xC]

    mov     si, [edx].STRFLT.mantissa.e
    shl     esi,16
    mov     ecx,a
    mov     eax,[ecx+0x0]
    mov     edx,[ecx+0x4]
    mov     ebx,[ecx+0x8]
    mov     edi,[ecx+0xC]
    mov     si, [ecx].STRFLT.mantissa.e
    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000
    mov     ecx,divisor[0x0]
    or      ecx,divisor[0x4]
    or      ecx,divisor[0x8]
    or      ecx,divisor[0xC]
    jz      .zero_b

.if_zero_a:
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jz      .zero_a

.init_done:

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
    jz      .normalize_a
.if_denormal_b:
    test    si,si
    jz      .normalize_b

.calculate_exponent:
    sub     cx,si
    add     cx,0x3FFF
    js      .too_small
    cmp     cx,0x7FFF
    ja      .infinity
.too_small:
    cmp     cx,-65
    jl      .underflow

.divide:

    define  BITS 14
    mov     exp,ecx

    shrd    eax,edx,BITS
    shrd    edx,ebx,BITS
    shrd    ebx,edi,BITS
    shr     edi,BITS
    mov     reminder[0x0],eax
    mov     reminder[0x4],edx
    mov     reminder[0x8],ebx
    mov     reminder[0xC],edi

    mov     esi,divisor[0x0]
    mov     edx,divisor[0x4]
    mov     ebx,divisor[0x8]
    mov     ebp,divisor[0xC]
    shrd    esi,edx,BITS
    shrd    edx,ebx,BITS
    shrd    ebx,ebp,BITS
    shr     ebp,BITS
    mov     ecx,113 + (16 - BITS)

    xor     eax,eax
    xor     edi,edi
    mov     quotient[0x0],eax
    mov     quotient[0x4],eax
    mov     quotient[0x8],eax
    mov     divisor [0x0],eax
    mov     divisor [0x4],eax
    mov     divisor [0x8],eax
    mov     divisor [0xC],eax
    mov     dividend[0x0],eax
    mov     dividend[0x4],eax
    mov     dividend[0x8],eax
    mov     dividend[0xC],eax

    add     esi,esi
    adc     edx,edx
    adc     ebx,ebx
    adc     ebp,ebp

.divide_1:
    shr     ebp,1
    rcr     ebx,1
    rcr     edx,1
    rcr     esi,1
    rcr     divisor[0xC],1
    rcr     divisor[0x8],1
    rcr     divisor[0x4],1
    rcr     divisor[0x0],1
    sub     dividend[0x0],divisor[0x0]
    sbb     dividend[0x4],divisor[0x4]
    sbb     dividend[0x8],divisor[0x8]
    sbb     dividend[0xC],divisor[0xC]
    sbb     reminder[0x0],esi
    sbb     reminder[0x4],edx
    sbb     reminder[0x8],ebx
    sbb     reminder[0xC],ebp
    cmc
    jc      .divide_3

.divide_2:

    add     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     edi,edi
    dec     ecx
    jz      .end_divide
    shr     ebp,1
    rcr     ebx,1
    rcr     edx,1
    rcr     esi,1
    rcr     divisor[0xC],1
    rcr     divisor[0x8],1
    rcr     divisor[0x4],1
    rcr     divisor[0x0],1
    add     dividend[0x0],divisor[0x0]
    adc     dividend[0x4],divisor[0x4]
    adc     dividend[0x8],divisor[0x8]
    adc     dividend[0xC],divisor[0xC]
    adc     reminder[0x0],esi
    adc     reminder[0x4],edx
    adc     reminder[0x8],ebx
    adc     reminder[0xC],ebp
    jnc     .divide_2

.divide_3:

    adc     quotient[0x0],quotient[0x0]
    adc     quotient[0x4],quotient[0x4]
    adc     quotient[0x8],quotient[0x8]
    adc     edi,edi
    dec     ecx
    jnz     .divide_1

.end_divide:

    mov     esi,exp
    mov     eax,quotient[0x0]
    mov     edx,quotient[0x4]
    mov     ebx,quotient[0x8]
    dec     si

.rounding:

    bt      eax,0
    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0

.overflow:

    bt      edi,32 - BITS
    jnc     .reset
    rcr     edi,1
    rcr     ebx,1
    rcr     edx,1
    rcr     eax,1
    add     esi,1

.reset:
    shld    edi,ebx,BITS
    shld    ebx,edx,BITS
    shld    edx,eax,BITS
    shl     eax,BITS

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

    mov     ecx,a
    mov     dword ptr [ecx].STRFLT.mantissa.l[0],eax
    mov     dword ptr [ecx].STRFLT.mantissa.l[4],edx
    mov     dword ptr [ecx].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [ecx].STRFLT.mantissa.h[4],edi
    mov     [ecx].STRFLT.mantissa.e,si
    mov     eax,ecx
    ret

.normalize_a:
    dec     cx
    add     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
    jnc     .normalize_a
    jmp     .if_denormal_b

.normalize_b:

    push    eax
.nb:
    dec     si
    add     divisor[0x0],divisor[0x0]
    adc     divisor[0x4],divisor[0x4]
    adc     divisor[0x8],divisor[0x8]
    adc     divisor[0xC],divisor[0xC]
    jnc     .nb
    pop     eax
    jmp     .calculate_exponent

.zero_a:
    add     si,si
    jz      .za_0
    rcr     si,1
    jmp     .init_done
.za_0:
    rcr     si,1
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x8000
    jmp     .done

.zero_b:
    test    esi,0x7FFF0000
    jnz     .if_zero_a
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    jnz     .infinity
    mov     ecx,esi
    add     cx,cx
    jnz     .infinity

.nan:
    mov     esi,0xFFFF
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
    xor     eax,eax
    jmp     .done

.underflow:
    and     cx,0x7FFF
    cmp     cx,0x3FFF
    jae     .zero

.infinity:
    mov     esi,0x7FFF
.0:
    xor     eax,eax
    xor     edx,edx
    xor     ebx,ebx
    xor     edi,edi
    jmp     .done

.zero:
    xor     esi,esi
    jmp     .0

.b:
    mov     eax,divisor[0x0]
    mov     edx,divisor[0x4]
    mov     ebx,divisor[0x8]
    mov     edi,divisor[0xC]
    shr     esi,16
    jmp     .done

.nan_a:
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
    jmp     .done
@@:
    sub     esi,0x10000
    mov     ecx,eax
    or      ecx,edx
    or      ecx,ebx
    or      ecx,edi
    or      ecx,divisor[0x0]
    or      ecx,divisor[0x4]
    or      ecx,divisor[0x8]
    or      ecx,divisor[0xC]
    jz      .nan
    cmp     edi,divisor[0xC]
    jb      .b
    ja      .done
    cmp     ebx,divisor[0x8]
    jb      .b
    ja      .done
    cmp     edx,divisor[0x4]
    jb      .b
    ja      .done
    cmp     eax,divisor[0x0]
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    mov     ecx,divisor[0]
    or      ecx,divisor[4]
    or      ecx,divisor[8]
    or      ecx,divisor[12]
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_fltdiv endp

    option stackbase:ebp

endif


_fltmul proc __ccall private uses rsi rdi rbx a:ptr STRFLT, b:ptr STRFLT

ifdef _WIN64
    mov     r10,rcx
    mov     rbx,[rdx].STRFLT.mantissa.l
    mov     rdi,[rdx].STRFLT.mantissa.h
else
   .new     multiplier[4]:dword
   .new     result    [8]:dword
    mov     edx,b
endif
    mov     si, [rdx].STRFLT.mantissa.e
    shl     esi,16
ifdef _WIN64
    mov     rax,[rcx].STRFLT.mantissa.l
    mov     rdx,[rcx].STRFLT.mantissa.h
else
    mov     ecx,a
    mov     eax,dword ptr [ecx].STRFLT.mantissa.l[0]
    mov     edx,dword ptr [ecx].STRFLT.mantissa.l[4]
    mov     ebx,dword ptr [ecx].STRFLT.mantissa.h[0]
    mov     edi,dword ptr [ecx].STRFLT.mantissa.h[4]
endif
    mov     si, [rcx].STRFLT.mantissa.e

    add     si,1
    jc      .nan_a
    jo      .nan_a
    add     esi,0xFFFF
    jc      .nan_b
    jo      .nan_b
    sub     esi,0x10000

    mov     rcx,rax
    or      rcx,rdx
ifndef _WIN64
    or      ecx,ebx
    or      ecx,edi
endif
    jz      .zero_a

.if_zero_b:
ifdef _WIN64
    mov     rcx,rbx
    or      rcx,rdi
else
    mov     ecx,b
    push    eax
    mov     eax,[ecx+0x0]
    or      eax,[ecx+0x4]
    or      eax,[ecx+0x8]
    or      eax,[ecx+0xC]
    pop     eax
endif
    jz      .zero_b

.calculate_exponent:

    mov     ecx,esi
    rol     ecx,16
    sar     ecx,16
    sar     esi,16
    and     ecx,0x80007FFF
    and     esi,0x80007FFF
    add     esi,ecx
    sub     si,0x3FFE
    jc      .too_small
    cmp     si,0x7FFF       ; quit if exponent is negative
    ja      .overflow
.too_small:
    cmp     si,-65
    jl      .underflow

ifdef _WIN64
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
    js      .rounding

    add     rbx,rbx
    adc     rax,rax
    adc     rdx,rdx
else
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

        lea ecx,[ebx+ebx]

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
    js      .rounding
    add     ecx,ecx
    adc     eax,eax
    adc     edx,edx
    adc     ebx,ebx
    adc     edi,edi
endif

    dec     si

.rounding:

ifdef _WIN64
    add     rbx,rbx
    adc     rax,0
    adc     rdx,0
else
    add     ecx,ecx
    adc     eax,0
    adc     edx,0
    adc     ebx,0
    adc     edi,0
endif

.validate:

    test    si,si
    jng     .zero
    add     esi,esi
    rcr     si,1

.done:

ifdef _WIN64
    mov     [r10].STRFLT.mantissa.l,rax
    mov     [r10].STRFLT.mantissa.h,rdx
    mov     [r10].STRFLT.mantissa.e,si
    mov     rax,r10
else
    mov     ecx,a
    mov     dword ptr [ecx].STRFLT.mantissa.l[0],eax
    mov     dword ptr [ecx].STRFLT.mantissa.l[4],edx
    mov     dword ptr [ecx].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [ecx].STRFLT.mantissa.h[4],edi
    mov     [ecx].STRFLT.mantissa.e,si
    mov     eax,ecx
endif
    ret

.zero_a:
    add     si,si
    jz      .is_zero_a
    rcr     si,1
    jmp     .if_zero_b
.is_zero_a:
    rcr     si,1
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x8000
    jmp     .done

.zero_b:
    test    esi,0x7FFF0000
    jnz     .calculate_exponent
    test    esi,0x80008000
    jz      .zero
    mov     esi,0x80000000
    jmp     .b

.nan:
    mov     esi,0xFFFF
ifdef _WIN64
    mov     edx,1
    rol     rdx,1
else
    mov     edi,0x40000000
    xor     ebx,ebx
    xor     edx,edx
endif
    xor     eax,eax
    jmp     .done

.overflow:

.infinity:
    mov     esi,0x7FFF
.0:
    xor     eax,eax
    xor     edx,edx
ifndef _WIN64
    xor     ebx,ebx
    xor     edi,edi
endif
    jmp     .done

.underflow:

.zero:
    xor     esi,esi
    jmp     .0

.b:
    mov     rax,rbx
    mov     rdx,rdi
    shr     esi,16
    jmp     .done

.nan_a:
    dec     si
    add     esi,0x10000
    jb      @F
    jo      @F
    jns     .done
    test    rax,rax
    jnz     .done
    test    rdx,rdx
    jnz     .done
    xor     esi,0x8000
    jmp     .done
@@:
    sub     esi,0x10000
    mov     rcx,rax
    or      rcx,rdx
    or      rcx,rbx
    or      rcx,rdi
    jnz     @F
    or      esi,-1
    jmp     .nan
@@:
    cmp     rdx,rdi
    jb      .b
    ja      .done
    cmp     rax,rbx
    jna     .b
    jmp     .done

.nan_b:
    sub     esi,0x10000
    test    rbx,rbx
    jnz     .b
    test    rdi,rdi
    jnz     .b
    mov     ecx,esi
    shl     ecx,16
    xor     esi,ecx
    and     esi,0x80000000
    jmp     .b

_fltmul endp


__addq proc __ccall dest:ptr qfloat_t, src:ptr qfloat_t

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltadd(&a, &b)
    _fltpackfp(dest, &a)
    ret

__addq endp


__subq proc __ccall dest:ptr qfloat_t, src:ptr qfloat_t

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltsub(&a, &b)
    _fltpackfp(dest, &a)
    ret

__subq endp


__mulq proc __ccall dest:ptr qfloat_t, src:ptr qfloat_t

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltmul(&a, &b)
    _fltpackfp(dest, &a)
    ret

__mulq endp


__divq proc __ccall dest:ptr qfloat_t, src:ptr qfloat_t

  local a:STRFLT
  local b:STRFLT

    _fltunpack(&a, dest)
    _fltunpack(&b, src)
    _fltdiv(&a, &b)
    _fltpackfp(dest, &a)
    ret

__divq endp


__sqrtq proc __ccall p:ptr qfloat_t

  local x:U128
  local y:U128
  local t:U128

    ldr rcx,p

    assume rcx:ptr U128

ifdef _WIN64
    mov rax,[rcx].u64[0]
else
    mov eax,[ecx].u32[0]
    or  eax,[ecx].u32[4]
endif
    or  eax,[rcx].u32[8]
    or  ax,[rcx].u16[12]
    mov dx,[rcx].u16[14]
    and edx,Q_EXPMASK

    .return .if edx == Q_EXPMASK && !eax
    .return .if !edx && !eax

    .if [rcx].u8[15] & 0x80

        __subq(rcx, rcx)
        __divq(rax, rax)
        .return
    .endif

    assume rcx:nothing

    mov x,[rcx]
    __cvtq_ld(rcx, rcx)
    mov rcx,p
    fld tbyte ptr [rcx]
    fsqrt
    fstp tbyte ptr [rcx]
    __cvtld_q(rcx, rcx)

    mov rdx,p
    mov y,[rdx]
    __subq(&y, __divq(&x, rdx))
ifdef _WIN64
    mov x.u64[0],0
else
    mov x.u32[0],0
    mov x.u32[4],0
endif
    mov x.u32[8],0
    mov x.u32[12],0x3FFE0000 ; 0.5

    __mulq(&y, &x)
    __subq(p, &y)
    ret

__sqrtq endp


    assume rdi: ptr STRFLT

_fltsetflags proc __ccall private uses rsi rdi fp:ptr STRFLT, string:string_t, flags:uint_t

    ldr rdi,fp
    ldr rsi,string
    ldr ecx,flags

    xor eax,eax
ifdef _WIN64
    mov [rdi].mantissa.l,rax
    mov [rdi].mantissa.h,rax
else
    mov dword ptr [rdi].mantissa.l[0],eax
    mov dword ptr [rdi].mantissa.l[4],eax
    mov dword ptr [rdi].mantissa.h[0],eax
    mov dword ptr [rdi].mantissa.h[4],eax
endif
    mov [rdi].mantissa.e,ax
    mov [rdi].exponent,eax
    or  ecx,_ST_ISZERO

    .repeat

        lodsb
        .break .if ( al == 0 )
        .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )

        dec rsi
        and ecx,not _ST_ISZERO
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
                    .if ( al == ')' )
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

   .return( ecx )

_fltsetflags endp

    assume rdi:nothing


    assume rbx:ptr STRFLT

_destoflt proc __ccall private uses rsi rdi rbx fp:ptr STRFLT, buffer:string_t

   .new digits:int_t = 0
   .new sigdig:int_t = 0

    ldr rbx,fp
    ldr rdi,buffer
    mov rsi,[rbx].string
    mov ecx,[rbx].flags
    xor eax,eax
    xor edx,edx

    .while 1

        lodsb
        .break .if !al

        .if ( al == '.' )

            .break .if ( ecx & _ST_DOT )
            or ecx,_ST_DOT

        .else

            .if ( ecx & _ST_ISHEX )

                or al,0x20
                .break .if ( al < '0' || al > 'f' )
                .break .if ( al > '9' && al < 'a' )
            .else
                .break .if ( al < '0' || al > '9' )
            .endif

            .if ( ecx & _ST_DOT )

                inc sigdig
            .endif

            or ecx,_ST_DIGITS
            or edx,eax

            .continue .if ( edx == '0' ) ; if a significant digit

            .if ( digits < Q_SIGDIG )
                stosb
            .endif
            inc digits
        .endif
    .endw
    mov byte ptr [rdi],0

    ;
    ; Parse the optional exponent
    ;
    xor edx,edx
    .if ( ecx & _ST_DIGITS )

        xor edi,edi ; exponent

        .if ( ( ( ecx & _ST_ISHEX ) &&
              ( al == 'p' || al == 'P' ) ) || al == 'e' || al == 'E' )

            mov al,[rsi]
            lea rdx,[rsi-1]
            .if ( al == '+' )
                inc rsi
            .endif
            .if ( al == '-' )
                inc rsi
                or  ecx,_ST_NEGEXP
            .endif
            and ecx,not _ST_DIGITS

            .while 1

                movzx eax,byte ptr [rsi]
                .break .if ( al < '0' )
                .break .if ( al > '9' )

                .if ( edi < 100000000 ) ; else overflow

                    imul edi,edi,10
                    lea edi,[rdi+rax-'0']
                .endif
                or  ecx,_ST_DIGITS
                inc rsi
            .endw

            .if ( ecx & _ST_NEGEXP )
                neg edi
            .endif
            .if !( ecx & _ST_DIGITS )
                mov rsi,rdx
            .endif
        .else

            dec rsi ; digits found, but no e or E
        .endif

        mov edx,edi
        mov eax,sigdig
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

        .if ( digits > edi )

            add edx,digits
            mov digits,edi
            .if ( ecx & _ST_ISHEX )

                shl edi,2
            .endif
            sub edx,edi
        .endif

        .while 1

            .break .if ( digits <= 0 )
             mov edi,digits
             add rdi,buffer
            .break .if ( byte ptr [rdi-1] != '0' )

            add edx,eax
            dec digits
        .endw
    .else
        mov rsi,[rbx].string
    .endif

    mov [rbx].flags,ecx
    mov [rbx].string,rsi
    mov [rbx].exponent,edx
    mov eax,digits
    ret

_destoflt endp

    assume rbx:nothing


define MAX_EXP_INDEX 13

_fltscale proc __ccall uses rsi rdi rbx fp:ptr STRFLT

    ldr rbx,fp

    mov edi,[rbx].STRFLT.exponent
    lea rsi,_fltpowtable

    .ifs ( edi < 0 )

        neg edi
        add rsi,( EXTFLOAT * MAX_EXP_INDEX )
    .endif

    .if ( edi )

        .for ( ebx = 0 : edi && ebx < MAX_EXP_INDEX : ebx++, edi >>= 1, rsi += EXTFLOAT )

            .if ( edi & 1 )

                _fltmul( fp, rsi )
            .endif
        .endf

        .if ( edi != 0 )

            ; exponent overflow

            xor eax,eax
            mov rbx,fp
ifdef _WIN64
            mov [rbx].STRFLT.mantissa.l,rax
            mov [rbx].STRFLT.mantissa.h,rax
else
            mov dword ptr [rbx].STRFLT.mantissa.l[0],eax
            mov dword ptr [rbx].STRFLT.mantissa.l[4],eax
            mov dword ptr [rbx].STRFLT.mantissa.h[0],eax
            mov dword ptr [rbx].STRFLT.mantissa.h[4],eax
endif
            mov [rbx].STRFLT.mantissa.e,0x7FFF
        .endif
    .endif
    .return( fp )

_fltscale endp


_strtoflt proc __ccall private uses rsi rdi rbx string:string_t

    .new buffer[256]:char_t
    .new digits:int_t
    .new sign:int_t

    .repeat

        _fltsetflags( &flt, string, 0 )
        .break .if ( eax & _ST_ISZERO or _ST_ISNAN or _ST_ISINF or _ST_INVALID )

        mov digits,_destoflt( &flt, &buffer )

        .if ( eax == 0 )

            or flt.flags,_ST_ISZERO
            .break
        .endif
        mov buffer[rax],0

        ; convert string to binary

        lea rdx,buffer
        xor eax,eax
        mov al,[rdx]
        mov sign,eax

        .if ( al == '+' || al == '-' )

            inc rdx
        .endif

        mov ebx,16
        .if !( flt.flags & _ST_ISHEX )

            mov ebx,10
        .endif
        lea rsi,flt.mantissa

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
                movzx edi,word ptr [rsi]
                imul  edi,ebx
                add   eax,edi
                mov   [rsi],ax
                add   rsi,2
                shr   eax,16
            .untilcxz
            sub rsi,16
            inc rdx
        .endw

        xor ecx,ecx

ifdef _WIN64

        mov rax,flt.mantissa.l
        mov rdx,flt.mantissa.h

        .if ( rax || rdx )

            .if ( rdx )     ; find most significant non-zero bit
                bsr rcx,rdx
                add ecx,64
            .else
                bsr rcx,rax
            .endif

            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch

            .if ( cl >= 64 )

                sub cl,64
                mov rdx,rax
                xor eax,eax
            .endif

            shld rdx,rax,cl
            shl rax,cl
            mov flt.mantissa.l,rax
            mov flt.mantissa.h,rdx
else

        mov eax,dword ptr flt.mantissa.l[0]
        mov edx,dword ptr flt.mantissa.l[4]
        mov ebx,dword ptr flt.mantissa.h[0]
        mov esi,dword ptr flt.mantissa.h[4]

        .if ( eax || edx || ebx || esi )

            .if ( esi )
                bsr ecx,esi
                add ecx,96
            .elseif ( ebx )
                bsr ecx,ebx
                add ecx,64
            .elseif ( edx )
                bsr ecx,edx
                add ecx,32
            .else
                bsr ecx,eax
            .endif

            mov ch,cl       ; shift bits into position
            mov cl,127
            sub cl,ch

            .while ( cl >= 32 )

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

            mov dword ptr flt.mantissa.l[0],eax
            mov dword ptr flt.mantissa.l[4],edx
            mov dword ptr flt.mantissa.h[0],ebx
            mov dword ptr flt.mantissa.h[4],esi
endif

            shr ecx,8           ; get shift count
            add ecx,Q_EXPBIAS   ; calculate exponent
            .if ( flt.flags & _ST_ISHEX )
                add ecx,flt.exponent
            .endif
        .else
            or flt.flags,_ST_ISZERO
        .endif

        mov edx,flt.flags
        .if ( sign == '-' || edx & _ST_NEGNUM )
            or cx,0x8000
        .endif

        mov ebx,ecx
        and ebx,Q_EXPMASK
        .switch
          .case edx & _ST_ISNAN or _ST_ISINF or _ST_INVALID or _ST_UNDERFLOW or _ST_OVERFLOW
          .case ebx >= Q_EXPMAX + Q_EXPBIAS
            or  ecx,0x7FFF
            xor eax,eax
ifdef _WIN64
            mov flt.mantissa.l,rax
            mov flt.mantissa.h,rax
else
            mov dword ptr flt.mantissa.l[0],eax
            mov dword ptr flt.mantissa.l[4],eax
            mov dword ptr flt.mantissa.h[0],eax
            mov dword ptr flt.mantissa.h[4],eax
endif
            .if ( edx & _ST_ISNAN or _ST_INVALID )

                or ecx,0x8000
                or byte ptr flt.mantissa.h[7],0x80
            .endif
        .endsw
        mov flt.mantissa.e,cx

        and ecx,Q_EXPMASK
        .if ( ecx >= 0x7FFF )

            mov qerrno,ERANGE

        .elseif ( flt.exponent && !( flt.flags & _ST_ISHEX ) )

            _fltscale( &flt )
        .endif

        mov eax,flt.exponent
        add eax,digits
        dec eax
        .ifs ( eax > 4932 )
            or flt.flags,_ST_OVERFLOW
        .endif
        .ifs ( eax < -4932 )
            or flt.flags,_ST_UNDERFLOW
        .endif
    .until 1
    _fltpackfp( &flt, &flt )
    ret

_strtoflt endp


ifdef _WIN64

;-------------------------------------------------------------------------------
; 64-bit DIV
;-------------------------------------------------------------------------------

__udiv64 proc watcall private dividend:uint64_t, divisor:uint64_t

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

_atoow proc fastcall dst:string_t, src:string_t, radix:int_t, bsize:int_t

    mov     r10,rcx
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
    jmp     .7

.2:
    cmp     r8d,10
    jne     .5
.3:
    mov     cl,[r11]
    inc     r11
    sub     cl,'0'
.4:
    dec     r9d
    jz      .7

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
    movzx   eax,byte ptr [r11]
    and     eax,not 0x30
    bt      eax,6
    sbb     ecx,ecx
    and     ecx,0x37
    sub     eax,ecx
    mov     ecx,8
.6:
    movzx   edx,word ptr [r10]
    imul    edx,r8d
    add     eax,edx
    mov     [r10],ax
    add     r10,2
    shr     eax,16
    dec     ecx
    jnz     .6
    sub     r10,16
    inc     r11
    dec     r9d
    jnz     .5
    mov     rcx,[r10]
    mov     rdx,[r10+8]
.7:
    mov     rax,r10
    mov     [rax],rcx
    mov     [rax+8],rdx
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
           .return( edx )
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

    .elseif ( ebx == 10 && edi <= 20 )

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
           .return( edx )

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

        mov rdx,_strtoflt( inp )
        mov rcx,_out
        mov [rcx],[rdx].U128.u128

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
            mov [rbx].negative,1
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_sd(rbx, rbx)
        .if ( [rbx].negative )
            or [rbx].chararray[7],0x80
        .endif
        mov [rbx].mem_type,MT_REAL8
        .endc
    .case 4
        .if ( [rbx].chararray[15] & 0x80 )
            mov [rbx].negative,1
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_ss(rbx, rbx)
        .if ( [rbx].negative )
            or [rbx].chararray[3],0x80
        .endif
        mov [rbx].mem_type,MT_REAL4
        .endc
    .case 2
        .if ( [rbx].chararray[15] & 0x80 )
            mov [rbx].negative,1
            and [rbx].chararray[15],0x7F
        .endif
        __cvtq_h(rbx, rbx)
        .if ( [rbx].negative )
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

m64 union
struc
 l  int_t ?
 h  int_t ?
ends
v   int64_t ?
m64 ends


_flttoi64 proc __ccall private p:ptr STRFLT

    ldr rcx,p

    mov dx,[rcx+16]
    mov eax,edx
    and eax,Q_EXPMASK

    .ifs ( eax < Q_EXPBIAS )

        xor eax,eax
        .if ( dx & 0x8000 )
            dec rax
        .endif
ifndef _WIN64
        cdq
endif

    .elseif ( eax > 62 + Q_EXPBIAS )

        mov qerrno,ERANGE
ifdef _WIN64
        mov rax,_I64_MAX
        .if ( edx & 0x8000 )
            mov rax,_I64_MIN
        .endif
else
        xor eax,eax
        .if ( edx & 0x8000 )
            mov edx,INT_MIN
        .else
            mov edx,INT_MAX
            dec eax
        .endif
endif

    .else

ifdef _WIN64

        mov r10,[rcx+8]
        mov ecx,eax
        xor eax,eax
        sub ecx,Q_EXPBIAS
        shl r10,1
        adc eax,eax
        shld rax,r10,cl
        .if ( edx & 0x8000 )
            neg rax
        .endif

else

        push    edx
        push    ebx
        push    edi
        mov     ebx,[ecx+8]
        mov     edi,[ecx+12]
        mov     ecx,eax
        xor     eax,eax
        xor     edx,edx
        shld    edi,ebx,1
        adc     eax,eax
        shl     ebx,1
        sub     ecx,Q_EXPBIAS

        .if ( ecx < 32 )

            shld eax,edi,cl

        .else

            .while ecx

                add ebx,ebx
                adc edi,edi
                adc eax,eax
                adc edx,edx
                dec ecx
            .endw
        .endif
        pop edi
        pop ebx
        pop ecx

        .if ( ecx & 0x8000 )

            neg edx
            neg eax
            sbb edx,0
        .endif
endif
    .endif
    ret

_flttoi64 endp


_i64toflt proc __ccall private p:ptr STRFLT, ll:int64_t

ifdef _WIN64

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

else

    push ebx

    mov eax,dword ptr ll[0]
    mov edx,dword ptr ll[4]
    mov ebx,Q_EXPBIAS   ; set exponent

    test edx,edx        ; if number is negative
    .ifs
        neg edx         ; negate number
        neg eax
        sbb edx,0
        or  ebx,0x8000
    .endif

    xor ecx,ecx
    .if ( eax || edx )

        .if edx         ; find most significant non-zero bit
            bsr ecx,edx
            add ecx,32
        .else
            bsr ecx,eax
        .endif

        mov ch,cl
        mov cl,64
        sub cl,ch

        .if ( cl <= 64 ) ; shift bits into position
            dec cl
            .if ( cl >= 32 )
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
    .endif

    mov     ebx,p
    xchg    eax,ebx
    mov     dword ptr [eax].STRFLT.mantissa.h[0],ebx
    mov     dword ptr [eax].STRFLT.mantissa.h[4],edx
    mov     [eax].STRFLT.mantissa.e,cx
    xor     edx,edx ; zero the rest of the fraction bits
    mov     dword ptr [eax].STRFLT.mantissa.l[0],edx
    mov     dword ptr [eax].STRFLT.mantissa.l[4],edx
    pop     ebx
endif
    ret

_i64toflt endp


    assume rbx:ptr FLTINFO

_flttostr proc __ccall uses rsi rdi rbx q:ptr, cvt:ptr FLTINFO, buf:string_t, flags:uint_t

  local i      :int_t
  local n      :int_t
  local nsig   :int_t
  local xexp   :int_t
  local maxsize:int_t
  local digits :int_t
  local qflt   :STRFLT
  local tmp    :STRFLT
  local stkbuf[STK_BUF_SIZE]:char_t
  local endbuf :ptr

    ldr rbx,cvt
    ldr rcx,buf

    mov eax,[rbx].bufsize
    add rax,rcx
    dec rax
    mov endbuf,rax

    mov eax,D_CVT_DIGITS
    .if ( flags & _ST_LONGDOUBLE )
        mov eax,LD_CVT_DIGITS
    .elseif ( flags & _ST_QUADFLOAT )
        mov eax,QF_CVT_DIGITS
    .endif
    mov digits,eax

    xor eax,eax
    mov [rbx].n1,eax
    mov [rbx].nz1,eax
    mov [rbx].n2,eax
    mov [rbx].nz2,eax
    mov [rbx].dec_place,eax

    _fltunpack( &qflt, q )

    mov ax,qflt.mantissa.e
    bt  eax,15
    sbb ecx,ecx
    mov [rbx].sign,ecx
    and eax,Q_EXPMASK   ; make number positive
    mov qflt.mantissa.e,ax

    movzx ecx,ax

    xor eax,eax
    mov qflt.flags,eax

    .if ( ecx == Q_EXPMASK )

        ; NaN or Inf
ifdef _WIN64
        or rax,qflt.mantissa.l
        or rax,qflt.mantissa.h
else
        or eax,dword ptr qflt.mantissa.l[0]
        or eax,dword ptr qflt.mantissa.l[4]
        or eax,dword ptr qflt.mantissa.h[0]
        or eax,dword ptr qflt.mantissa.h[4]
endif
        .ifz

            ; INFINITY

            mov eax,'fni'
            or  [rbx].flags,_ST_ISINF
        .else

            ; NaN

            mov eax,'nan'
            or  [rbx].flags,_ST_ISNAN
        .endif

        .if ( flags & _ST_CAPEXP )

            and eax,NOT 0x202020
        .endif
        mov rcx,buf
        mov [rcx],eax
        mov [rbx].n1,3
       .return( 64 )
    .endif

    .if ( ecx == 0 )

        ; ZERO/DENORMAL

        mov [rbx].sign,eax ; force sign to +0.0
        mov xexp,eax
        mov qflt.flags,_ST_ISZERO

    .else

        mov  esi,ecx
        sub  ecx,0x3FFE
        mov  eax,30103
        imul ecx
        mov  ecx,100000
        idiv ecx
        sub  eax,NDIG / 2
        mov  xexp,eax

        .if ( eax )

            .ifs

                ; scale up

                neg eax
                add eax,NDIG / 2 - 1
                and eax,NOT (NDIG / 2 - 1)
                neg eax
                mov xexp,eax
                neg eax
                mov qflt.exponent,eax

                _fltscale( &qflt )

            .else

                mov eax,dword ptr qflt.mantissa.h[0]
                mov edx,dword ptr qflt.mantissa.h[4]

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
                    mov qflt.exponent,eax

                    _fltscale( &qflt )
                .endif
            .endif
        .endif
    .endif

    mov eax,[rbx].ndigits
    .if ( [rbx].flags & _ST_F )

        add eax,xexp
        add eax,2 + NDIG
        .ifs ( [rbx].scale > 0 )
            add eax,[rbx].scale
        .endif
    .else
        add eax,NDIG + NDIG / 2 ; need at least this for rounding
    .endif
    .if ( eax > STK_BUF_SIZE-1-NDIG )
        mov eax,STK_BUF_SIZE-1-NDIG
    .endif
    mov n,eax

    mov ecx,digits
    add ecx,NDIG / 2
    mov maxsize,ecx

    ; convert quad into string of digits
    ; put in leading '0' in case we round 99...99 to 100...00

   .new value:m64 = {0}
ifndef _WIN64
   .new radix:int_t = 10
endif
    lea rdi,stkbuf
    mov word ptr [rdi],'0'
    inc rdi
    mov i,0

    .while ( n > 0 )

        sub n,NDIG
ifdef _WIN64
        .if ( value.v == 0 )
else
        .if ( value.l == 0 && value.h == 0 )
endif

            ; get value to subtract

            _flttoi64( &qflt )
ifdef _WIN64
            mov value.v,rax
else
            mov value.l,eax
            mov value.h,edx
endif
            .ifs ( n > 0 )

                _i64toflt( &tmp, value )
                _fltsub( &qflt, &tmp )
                _fltmul( &qflt, &_fltpowtable[EXTFLOAT*4] )
            .endif
        .endif

        mov ecx,NDIG

ifdef _WIN64

        mov rax,value.v
        mov value.v,0

        .if ( rax )

            .for ( r8d = 10 : ecx : ecx-- )

                xor edx,edx
                div r8
                add dl,'0'
                mov [rdi+rcx-1],dl

else
        mov eax,value.l
        mov edx,value.h
        mov value.l,0
        mov value.h,0

        .if ( eax || edx )

            add edi,ecx
            mov esi,ecx

            .fors ( : eax || edx || esi > 0 : esi-- )

                .if ( edx == 0 )

                    div radix
                    mov ecx,edx
                    xor edx,edx

                .else

                    push esi
                    push edi

                    .for ( ecx = 64, esi = 0, edi = 0 : ecx : ecx-- )

                        add eax,eax
                        adc edx,edx
                        adc esi,esi
                        adc edi,edi

                        .if ( edi || esi >= radix )

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
endif
            .endf
            add rdi,NDIG

        .else

            mov al,'0'
            rep stosb
        .endif

        add i,NDIG
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

        .ifs ( edx > eax )
            mov edx,eax     ; nsig = n
        .endif
        mov eax,digits
        .ifs ( edx > eax )
            mov edx,eax
        .endif
        mov maxsize,eax

        mov eax,'0'
        .ifs ( ( n > edx && byte ptr [rsi+rdx] >= '5' ) ||
               ( edx == digits && byte ptr [rsi+rdx-1] == '9' ) )
            mov al,'9'
        .endif

        mov edi,[rbx].scale
        add edi,[rbx].ndigits

        .if ( al == '9' && edx == edi &&
              byte ptr [rsi+rdx] != '9' &&  byte ptr [rsi+rdx-1] == '9' )

            .while edi

                dec edi
               .break .if ( byte ptr [rsi+rdi] != '9' )
            .endw

            .if ( byte ptr [rsi+rdi] == '9' )
                 mov al,'0'
            .endif
        .endif

        lea     rdi,[rsi+rdx-1]
        xchg    ecx,edx
        inc     ecx
        std
        repz    scasb
        cld
        xchg    ecx,edx
        inc     rdi

        .if ( al == '9' ) ; round up
            inc byte ptr [rdi]
        .endif
        sub rdi,rsi
        .ifs
            dec rsi ; repeating 9's rounded up to 10000...
            inc edx
            inc ecx
        .endif
    .endif

    .ifs ( edx <= 0 || qflt.flags == _ST_ISZERO )

        mov edx,1   ; nsig = 1
        xor ecx,ecx ; xexp = 0

        mov stkbuf,'0'
        mov [rbx].sign,ecx
        lea rsi,stkbuf
    .endif

    mov i,0
    mov eax,[rbx].flags

    .ifs ( eax & _ST_F || ( eax & _ST_G && ( ( ecx >= -1 && ecx < [rbx].ndigits ) || eax & _ST_CVT ) ) )

        mov rdi,buf
        inc ecx

        .if ( eax & _ST_G )

            .ifs ( edx < [rbx].ndigits && !( eax & _ST_DOT ) )

                mov [rbx].ndigits,edx
            .endif

            sub [rbx].ndigits,ecx
            .ifs ( [rbx].ndigits < 0 )
                mov [rbx].ndigits,0
            .endif
        .endif

        .ifs ( ecx <= 0 ) ; digits only to right of '.'

            .if !( eax & _ST_CVT )

                mov byte ptr [rdi],'0'
                inc i

                .ifs ( [rbx].ndigits > 0 || eax & _ST_DOT )

                    mov byte ptr [rdi+1],'.'
                    inc i
                .endif
            .endif

            mov [rbx].n1,i
            mov eax,ecx
            neg eax

            .ifs ( [rbx].ndigits < eax )

                mov ecx,[rbx].ndigits
                neg ecx
            .endif

            mov eax,ecx
            neg eax
            mov [rbx].dec_place,eax
            mov [rbx].nz1,eax
            add [rbx].ndigits,ecx

            .ifs ( [rbx].ndigits < edx )
                mov edx,[rbx].ndigits
            .endif
            mov [rbx].n2,edx

            sub edx,[rbx].ndigits
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

            add i,ecx
            mov al,'0'
            rep stosb
            mov ecx,[rbx].n2    ; followed by these characters
            add i,ecx
            rep movsb

            mov ecx,[rbx].nz2   ; followed by this many '0's
            add i,ecx
            rep stosb

        .elseifs ( edx < ecx )  ; zeros before '.'

            add i,edx
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
            add i,ecx
            rep stosb

            mov ecx,[rbx].ndigits
            .if !( [rbx].flags & _ST_CVT )

                .ifs ( ecx > 0 || [rbx].flags & _ST_DOT )

                    mov byte ptr [rdi],'.'
                    inc rdi
                    inc i
                    mov [rbx].n2,1
                .endif
            .endif

            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow
            mov [rbx].nz2,ecx
            add i,ecx
            rep stosb

        .else ; enough digits before '.'

            mov [rbx].dec_place,ecx
            add i,ecx
            sub edx,ecx
            rep movsb

            mov rdi,buf
            mov ecx,[rbx].dec_place

            .if !( [rbx].flags & _ST_CVT )

                .ifs ( [rbx].ndigits > 0 || [rbx].flags & _ST_DOT )


                    mov eax,i
                    mov byte ptr [rdi+rax],'.'
                    inc i
                .endif

            .elseif ( byte ptr [rdi] == '0' ) ; ecvt or fcvt with 0.0

                mov [rbx].dec_place,0
            .endif

            .ifs ( [rbx].ndigits < edx )

                mov edx,[rbx].ndigits
            .endif

            mov eax,i
            add rdi,rax
            mov ecx,edx
            rep movsb

            add i,edx
            mov [rbx].n1,i
            mov eax,edx
            mov ecx,[rbx].ndigits
            add edx,ecx
            mov [rbx].nz1,edx
            sub ecx,eax
            add i,ecx

            lea rdx,[rdi+rcx]
            cmp rdx,endbuf
            ja  overflow

            mov eax,'0'
            rep stosb

        .endif

        mov edi,i
        add rdi,buf
        mov byte ptr [rdi],0

    .else

        mov eax,[rbx].ndigits
        .ifs ( [rbx].scale <= 0 )
            add eax,[rbx].scale   ; decrease number of digits after decimal
        .else
            sub eax,[rbx].scale   ; adjust number of digits (see fortran spec)
            inc eax
        .endif

        mov i,0
        .if ( [rbx].flags & _ST_G )

            ; fixup for 'G'
            ; for 'G' format, ndigits is the number of significant digits
            ; cvt->scale should be 1 indicating 1 digit before decimal place
            ; so decrement ndigits to get number of digits after decimal place

            .if ( edx < eax && !( [rbx].flags & _ST_DOT) )
                mov eax,edx
            .endif
            dec eax
            .ifs ( eax < 0 )
                xor eax,eax
            .endif
            .ifs ( ecx > -5 && ecx < 0 )

                neg ecx
                add eax,ecx
                add edx,ecx
                sub rsi,rcx
                xor ecx,ecx
            .endif
        .endif
        mov [rbx].ndigits,eax
        mov xexp,ecx
        mov nsig,edx
        mov rdi,buf

        .ifs ( [rbx].scale <= 0 )

            mov byte ptr [rdi],'0'
            inc i
            .if ( ecx >= maxsize )
                inc xexp
            .endif

        .else

            mov eax,[rbx].scale
            .if ( eax > edx )
                mov eax,edx
            .endif

            mov edx,eax
            mov ecx,i
            add rdi,rcx  ; put in leading digits
            mov ecx,eax
            mov rax,rsi
            rep movsb
            mov rsi,rax

            add i,edx
            add rsi,rdx
            sub nsig,edx

            .ifs ( edx < [rbx].scale ) ; put in zeros if required

                mov ecx,[rbx].scale
                sub ecx,edx
                add i,ecx
                mov edi,i
                add rdi,buf
                mov al,'0'
                rep stosb
            .endif
        .endif

        mov edx,i
        mov rdi,buf
        mov [rbx].dec_place,edx
        mov eax,[rbx].ndigits

        .if !( [rbx].flags & _ST_CVT )

            .ifs ( eax > 0 || [rbx].flags & _ST_DOT )

                mov byte ptr [rdi+rdx],'.'
                inc i
            .endif
        .endif

        mov ecx,[rbx].scale
        .ifs ( ecx < 0 )

            neg ecx
            add rdi,rdx
            add i,ecx
            mov al,'0'
            rep stosb
        .endif

        mov ecx,nsig
        mov eax,[rbx].ndigits

        .ifs ( eax > 0 ) ; put in fraction digits

            .ifs ( eax < ecx )

                mov ecx,eax
                mov nsig,eax
            .endif

            .if ( ecx )

                mov edi,i
                add rdi,buf
                add i,ecx
                rep movsb
            .endif

            mov [rbx].n1,i
            mov ecx,[rbx].ndigits
            sub ecx,nsig
            mov [rbx].nz1,ecx

            mov edi,i
            add rdi,buf
            add i,ecx
            mov eax,'0'
            rep stosb
        .endif

        mov edi,xexp
        mov rsi,buf
        mov ecx,i

        .if ( [rbx].flags & _ST_G && edi == 0 )

            mov edx,ecx
        .else

            mov eax,[rbx].expchar
            .if ( al )

                mov [rsi+rcx],al
                inc i
                inc ecx
            .endif

            .ifs ( edi >= 0 )
                mov byte ptr [rsi+rcx],'+'
            .else
                mov byte ptr [rsi+rcx],'-'
                neg edi
            .endif

            inc i
            mov eax,edi
            mov ecx,[rbx].expwidth

            .switch ecx
            .case 0           ; width unspecified
                mov ecx,3
                .ifs ( eax >= 1000 )
                    mov ecx,4
                .endif
                .endc
            .case 1
                .ifs ( eax >= 10 )
                    mov ecx,2
                .endif
            .case 2
                .ifs ( eax >= 100 )
                    mov ecx,3
                .endif
            .case 3
                .ifs ( eax >= 1000 )
                    mov ecx,4
                .endif
                .endc
            .endsw
            mov [rbx].expwidth,ecx    ; pass back width actually used

            .if ( ecx >= 4 )

                xor edx,edx

                .if ( eax >= 1000 )

                    mov  ecx,1000
                    div  ecx
                    mov  edx,eax
                    imul eax,eax,1000
                    sub  edi,eax
                    mov  ecx,[rbx].expwidth
                .endif

                lea eax,[rdx+'0']
                mov edx,i
                mov [rsi+rdx],al
                inc i
            .endif

            .if ( ecx >= 3 )

                xor edx,edx
                .ifs ( edi >= 100 )

                    mov  eax,edi
                    mov  ecx,100
                    div  ecx
                    mov  edx,eax
                    imul eax,eax,100
                    sub  edi,eax
                    mov  ecx,[rbx].expwidth
                .endif

                lea eax,[rdx+'0']
                mov edx,i
                mov [rsi+rdx],al
                inc i
            .endif

            .if ( ecx >= 2 )

                xor edx,edx
                .ifs ( edi >= 10 )

                    mov  eax,edi
                    mov  ecx,10
                    div  ecx
                    mov  edx,eax
                    imul eax,eax,10
                    sub  edi,eax
                    mov  ecx,[rbx].expwidth
                .endif

                lea eax,[rdx+'0']
                mov edx,i
                mov [rsi+rdx],al
                inc i
            .endif

            mov edx,i
            lea eax,[rdi+'0']
            mov [rsi+rdx],al
            inc edx
         .endif

         mov eax,edx
         sub eax,[rbx].n1
         mov [rbx].n2,eax
         xor eax,eax
         mov [rsi+rdx],al
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

    end
