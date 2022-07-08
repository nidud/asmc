; POWQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .data
     zero        real8 0.0
     one         real8 1.0
     limit       real8 0.29
     p63         real8 9.223372e+018

    .code

    option dotname

powq proc _x:real16, y:real16

ifdef _WIN64

  local z:int64_t
  local x:real10

    qtofpu( xmm0 )
    fstp    x
    qtofpu( xmm1 )

    fxam
    fnstsw  ax
    mov     dl,ah
    and     ah,0x45
    cmp     ah,0x40         ; y == 0 ?
    jne     .0
    fstp    st(0)           ; pop y
    jmp     .one

.0:
    cmp     ah,5            ; y == inf ?
    jne     .1
    fstp    st(0)           ; pop y
    fld     one
    fld     x
    fabs                    ; abs(x) : 1
    fucompp                 ; < 1, == 1, or > 1
    fnstsw  ax
    and     ah,0x45
    cmp     ah,0x45         ; x == NaN ?
    je      .nan            ; load x == NaN
    cmp     ah,0x40
    je      .one
    shl     ah,1
    xor     dl,ah
    and     edx,2
    jz      .inf
    jmp     .minf
.1:
    cmp     ah,1            ; y == NaN ?
    jne     .3
    fld     x
    fld     one
    fucomp  st(1)
    fnstsw  ax
    sahf
    jz      .2
    fxch    st(1)
.2:
    fstp    st(1)
    jmp     .fpu

.3:
    fld     x
    fxam
    fnstsw  ax
    mov     dh, ah
    and     ah,0x45
    cmp     ah,0x40
    jne     .7
    fstp    st(0)           ; y
    test    dl,2
    jnz     .5
    test    dh,2
    jz      .4

    fld     st
    fistp   z
    fild    z
    fucompp
    fnstsw  ax
    sahf
    jnz     .zero

    ;
    ; OK, the value is an integer, but is the number of bits small
    ; enough so that all are coming from the mantissa?
    ;
    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    test    al,1
    jz      .zero
    cmp     edx,0xFFE00000
    jae     .zero
    jmp     .mzero
.4:
    fstp    st(0)
    jmp     .zero

.5:
    ;
    ; x is 0 and y is < 0.  We must find out whether y is an odd integer.
    ;
    test    dh,2
    jz      .6

    fld     st
    fistp   z
    fild    z
    fucompp
    fnstsw  ax
    sahf
    jnz     .inf

    ;
    ; OK, the value is an integer, but is the number of bits small
    ; enough so that all are coming from the mantissa?
    ;

    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    test    al,1
    jz      .inf
    cmp     edx,0xFFE00000
    jbe     .inf
    ;
    ; It's an odd integer.
    ; return minus infinity value.
    ;
    jmp     .minf
.6:
    fstp    st(0)
    jmp     .inf

.7:
    cmp     ah,5
    jne     .c
    fstp    st(0)
    test    dh,2
    jnz     .8
    fcomp   zero
    fnstsw  ax
    shr     eax,5
    and     eax,8
    jz      .inf
    jmp     .zero

.8:
    ;
    ; We must find out whether y is an odd integer.
    ;
    fld     st
    fistp   z
    fild    z
    fucompp
    fnstsw  ax
    sahf
    jnz     .a
    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    test    al,1
    jz      .b
    mov     eax,edx
    or      edx,edx
    jns     .9
    neg     eax
.9:
    cmp     eax,0x200000
    ja      .b
    ;
    ; It's an odd integer.
    ;
    shr     edx,31
    jz      .inf
    jmp     .zero
.a:
    shl     edx,30          ; sign bit for y in right position
.b:
    shr     edx,31
    jz      .inf
    jmp     .zero

.c:
    fxch    st(1)
    fld     st
    fabs
    fcomp   p63
    fnstsw  ax
    sahf
    jnc     .g

    fld     st
    fistp   z
    fild    z
    fucomp  st(1)
    fnstsw  ax
    sahf
    jnz     .g

    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    or      edx,0
    fstp    st
    jns     .d

    fdivr   one
    neg     eax
    adc     edx,0
    neg     edx

.d:
    fld     one
    fxch    st(1)
.e:
    shrd    eax,edx,1
    jnc     .f
    fxch    st(1)
    fmul    st, st(1)
    fxch    st(1)
.f:
    fmul    st,st
    shr     edx,1
    mov     ecx,eax
    or      ecx,edx
    jnz     .e
    fstp    st
    jmp     .fpu

.g:
    fxch    st(1)
    fld     one
    fld     limit
    fld     st(2)
    fsub    st,st(2)
    fabs
    fucompp
    fnstsw  ax
    fxch    st(1)
    sahf
    ja      .h
    fsub    st, st(1)
    fyl2xp1
    jmp     .i
.h:
    fyl2x
.i:
    fmul    st,st(1)
    fst     st(1)
    frndint
    fsub    st(1),st
    fxch
    f2xm1
    fadd    one
    fscale
    fstp    st(1)
    jmp     .fpu

.zero:
    .return real16(0.0)
.mzero:
    .return real16(-0.0)
.one:
    .return real16(1.0)
.inf:
    .return(INFINITY)
.minf:
    .return(MINFINITY)
.nan:
    .return(NAN)
.fpu:
    fputoq()
else
    int     3
endif
    ret
powq endp

    end
