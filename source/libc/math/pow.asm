; POW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include math.inc

    .data
     inf_zero    label qword
     infinity    dq 0x7FF0000000000000
     zero        dq 0.0
     minf_mzero  label qword
     minfinity   dq 0xFFF0000000000000
     mzero       dq 0x8000000000000000
     one         dq 1.0
     limit       dq 0.29
     p63         dq 0x43E0000000000000

    .code

    option dotname

pow proc _x:double, _y:double
  local     z:double
ifdef __SSE__
  local     a:double
  local     b:double
    movsd   a,xmm0
    movsd   b,xmm1
    define  x <a>
    define  y <b>
else
    define  x <_x>
    define  y <_y>
endif
    fld     y
    fxam
    fnstsw  ax
    mov     dl,ah

    and     ah,0x45
    cmp     ah,0x40         ; y == 0 ?
    jne     .0

    fstp    st(0)           ; pop y
    xor     eax,eax
    mov     edx,0x3FF00000
    jmp     .n

.0:
    cmp     ah,5            ; y == inf ?
    jne     .3

    fstp    st(0)           ; pop y
    fld     one
    fld     x
    fabs                    ; abs(x) : 1
    fucompp                 ; < 1, == 1, or > 1
    fnstsw  ax
    and     ah,0x45

    cmp     ah,0x45         ; x == NaN ?
    jne     .1

    mov     eax,dword ptr x ; load x == NaN
    mov     edx,dword ptr x[4]
    jmp     .n

.1:
    cmp     ah,0x40
    jne     .2

    xor     eax,eax
    mov     edx,0x3FF00000
    jmp     .n

.2:
    shl     ah,1
    xor     dl,ah
    and     edx,2

    lea     rcx,inf_zero
    mov     eax,[rcx+rdx*8]
    mov     edx,[rcx+rdx*8][4]
    jmp     .n
.3:

    cmp     ah,1            ; y == NaN ?
    jne     .5
    fld     x
    fld     one
    fucomp  st(1)
    fnstsw  ax
    sahf
    jz      .4
    fxch    st(1)
.4:
    fstp    st(1)
    jmp     .o
.5:

    fld     x
    fxam
    fnstsw  ax
    mov     dh, ah
    and     ah,0x45

    cmp     ah,0x40
    jne     .b

    fstp    st(0)           ; y

    test    dl,2
    jnz     .8
    test    dh,2
    jz      .6

    fld     st
    fistp   z
    fild    z
    fucompp
    fnstsw  ax
    sahf
    jnz     .7

    ;
    ; OK, the value is an integer, but is the number of bits small
    ; enough so that all are coming from the mantissa?
    ;
    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]

    test    al,1
    jz      .7
    cmp     edx,0xFFE00000
    jae     .7

    xor     eax,eax
    mov     edx,0x80000000
    jmp     .n
.6:
    fstp    st(0)
.7:
    xor     eax,eax
    xor     edx,edx
    jmp     .n
.8:

    ;
    ; x is 0 and y is < 0.  We must find out whether y is an odd integer.
    ;

    test    dh,2
    jz      .9

    fld     st
    fistp   z
    fild    z
    fucompp
    fnstsw  ax
    sahf
    jnz     .a

    ;
    ; OK, the value is an integer, but is the number of bits small
    ; enough so that all are coming from the mantissa?
    ;

    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    test    al,1
    jz      .a
    cmp     edx,0xFFE00000
    jbe     .a

    ;
    ; It's an odd integer.
    ; Raise divide-by-zero exception and get minus infinity value.
    ;

    fld     one
    fdiv    zero
    fchs
    jmp     .o
.9:
    fstp    st(0)
.a:
    fld     one
    fdiv    zero
    jmp     .o

.b:

    cmp     ah,5
    jne     .g

    fstp    st(0)
    test    dh,2
    jnz     .c

    fcomp   zero
    fnstsw  ax

    shr     eax,5
    and     eax,8
    lea     rcx,inf_zero
    mov     edx,[rcx+rax*8][4]
    mov     eax,[rcx+rax*8]
    jmp     .n

.c:

    ;
    ; We must find out whether y is an odd integer.
    ;

    fld     st
    fistp   z
    fild    z
    fucompp
    fnstsw  ax
    sahf
    jnz     .e

    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    test    al,1
    jz      .f

    mov     eax,edx
    or      edx,edx
    jns     .d
    neg     eax
.d:
    cmp     eax,0x200000
    ja      .f
    ;
    ; It's an odd integer.
    ;

    shr     edx,31
    lea     rcx,minf_mzero
    mov     eax,[rcx+rdx*8]
    mov     edx,[rcx+rdx*8][4]
    jmp     .n
.e:
    shl     edx,30          ; sign bit for y in right position
.f:
    shr     edx,31
    lea     rcx,inf_zero
    mov     eax,[rcx+rdx*8]
    mov     edx,[rcx+rdx*8][4]
    jmp     .n

.g:
    fxch    st(1)
    fld     st
    fabs
    fcomp   p63
    fnstsw  ax
    sahf
    jnc     .k

    fld     st
    fistp   z
    fild    z
    fucomp  st(1)
    fnstsw  ax
    sahf
    jnz     .k

    mov     eax,dword ptr z
    mov     edx,dword ptr z[4]
    or      edx,0
    fstp    st
    jns     .h

    fdivr   one
    neg     eax
    adc     edx,0
    neg     edx

.h:
    fld     one
    fxch    st(1)
.i:

    shrd    eax,edx,1
    jnc     .j

    fxch    st(1)
    fmul    st, st(1)
    fxch    st(1)
.j:
    fmul    st,st
    shr     edx,1
    mov     ecx,eax
    or      ecx,edx
    jnz     .i
    fstp    st
    jmp     .o

.k:
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
    ja      .l
    fsub    st, st(1)
    fyl2xp1
    jmp     .m
.l:
    fyl2x
.m:
    fmul    st,st(1)
    fst     st(1)
    frndint
    fsub    st(1),st
    fxch
    f2xm1
    fadd    one
    fscale
    fstp    st(1)
    jmp     .o
.n:
    mov     dword ptr x,eax
    mov     dword ptr x[4],edx
    fld     x
.o:
ifdef __SSE__
    fstp    x
    movsd   xmm0,x
endif
    ret

pow endp

    end
