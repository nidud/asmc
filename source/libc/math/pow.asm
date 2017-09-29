; POW.ASM--
; Copyright (C) 2017 Asmc Developers
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

pow proc __cdecl x:REAL8, y:REAL8

  local z:REAL8

    fld y
    fxam
    fnstsw ax
    mov dl,ah

    .repeat
        .repeat

            and ah,0x45
            .if ah == 0x40  ;; y == 0 ?

                fstp st(0)  ;; pop y

                mov eax,LOW32  1.0
                mov edx,HIGH32 1.0
                .break
            .endif

            .if ah == 5     ;; y == inf ?

                fstp st(0)  ;; pop y
                fld one
                fld x
                fabs        ;; abs(x) : 1
                fucompp     ;; < 1, == 1, or > 1
                fnstsw ax
                and ah,0x45

                .if ah == 0x45 ;; x == NaN ?

                    mov eax,dword ptr x ;; load x == NaN
                    mov edx,dword ptr x[4]
                    .break
                .endif

                .if ah == 0x40

                    mov eax,LOW32  1.0
                    mov edx,HIGH32 1.0
                    .break
                .endif

                shl ah, 1
                xor dl, ah
                and edx, 2
                mov eax,dword ptr inf_zero[edx*4]
                mov edx,dword ptr inf_zero[edx*4][4]
                .break
            .endif

            .if ah == 1     ;; y == NaN ?
                fld x
                fld one
                fucomp st(1)
                fnstsw ax
                sahf
                .ifnz
                    fxch st(1)
                .endif
                fstp st(1)
                .break(1)
            .endif

            fld x
            fxam
            fnstsw ax
            mov dh, ah
            and ah,0x45
            .if ah == 0x40

                fstp st(0)  ;; y

                .if !(dl & 2)

                    .if dh & 2

                        fld   st
                        fistp z
                        fild  z
                        fucompp
                        fnstsw ax
                        sahf
                        .ifz
                            ;;
                            ;; OK, the value is an integer, but is the number of bits small
                            ;; enough so that all are coming from the mantissa?
                            ;;
                            mov eax,dword ptr z
                            mov edx,dword ptr z[4]
                            .if al & 1 && edx < 0xFFE00000

                                mov eax,LOW32  -0.0
                                mov edx,HIGH32 -0.0
                                .break
                            .endif
                        .endif
                    .else
                        fstp st(0)
                    .endif
                    mov eax,LOW32  0.0
                    mov edx,HIGH32 0.0
                    .break

                .endif

                ;; x is 0 and y is < 0.  We must find out whether y is an odd integer.

                .if dh & 2

                    fld   st
                    fistp z
                    fild  z
                    fucompp
                    fnstsw ax
                    sahf
                    .ifz

                        ;; OK, the value is an integer, but is the number of bits small
                        ;; enough so that all are coming from the mantissa?

                        mov eax,dword ptr z
                        mov edx,dword ptr z[4]
                        .if al & 1 && edx > 0xFFE00000

                            ;; It's an odd integer.
                            ;; Raise divide-by-zero exception and get minus infinity value.

                            fld  one
                            fdiv zero
                            fchs
                            .break(1)
                        .endif
                    .endif
                .else

                    fstp st(0)
                .endif

                fld  one
                fdiv zero
                .break(1)
            .endif

            .if ah == 5

                fstp st(0)
                .if !(dh & 2)

                    fcomp  zero
                    fnstsw ax

                    shr eax, 5
                    and eax, 8
                    mov eax,dword ptr inf_zero[eax]
                    mov edx,dword ptr inf_zero[eax][4]

                    .break
                .endif

                ;; We must find out whether y is an odd integer.

                fld   st
                fistp z
                fild  z
                fucompp
                fnstsw ax
                sahf
                .ifz

                    mov eax,dword ptr z
                    mov edx,dword ptr z[4]
                    .if al & 1

                        mov eax,edx
                        or  edx,edx
                        .ifs
                            neg eax
                        .endif
                        .if eax <= 0x200000

                            ;; It's an odd integer.

                            shr edx,31
                            mov eax,dword ptr minf_mzero[edx*8]
                            mov edx,dword ptr minf_mzero[edx*8][4]
                            .break
                        .endif
                    .endif
                .else

                    shl edx,30 ;; sign bit for y in right position
                .endif

                shr edx,31
                mov eax,dword ptr inf_zero[edx*8]
                mov edx,dword ptr inf_zero[edx*8][4]
                .break
            .endif

            fxch   st(1)
            fld    st
            fabs
            fcomp  p63
            fnstsw ax
            sahf
            .ifc
                fld   st
                fistp z
                fild  z
                fucomp st(1)
                fnstsw ax
                sahf
                .ifz
                    mov  eax,dword ptr z
                    mov  edx,dword ptr z[4]
                    or   edx,0
                    fstp st
                    .ifs
                        fdivr one
                        neg eax
                        adc edx, 0
                        neg edx
                    .endif
                    fld  one
                    fxch st(1)
                    .repeat
                        shrd eax,edx,1
                        .ifc
                            fxch st(1)
                            fmul st, st(1)
                            fxch st(1)
                        .endif
                        fmul st,st
                        shr edx,1
                        mov ecx,eax
                        or  ecx,edx
                    .untilz
                    fstp st
                    .break(1)
                .endif
            .endif

            fxch st(1)
            fld  one
            fld  limit
            fld  st(2)
            fsub st,st(2)
            fabs
            fucompp
            fnstsw ax
            fxch st(1)
            sahf
            .ifna
                fsub st, st(1)
                fyl2xp1
            .else
                fyl2x
            .endif
            fmul st,st(1)
            fst  st(1)
            frndint
            fsub st(1),st
            fxch
            f2xm1
            fadd one
            fscale
            fstp st(1)
            .break(1)

        .until 1

        mov dword ptr x,eax
        mov dword ptr x[4],edx
        fld x

    .until 1
    ret

pow endp

    end
