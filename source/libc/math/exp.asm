; EXP.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

exp proc x:REAL8

    fld	  x
    fxam
    fstsw ax
    fwait
    sahf
    jnp not_inf
    jnc not_inf
    test  ah,2
    jz done
    fstp  st
    fldz
    jmp done
not_inf:
    fldl2e
    fmul  st,st(1)
    fst	  st(1)
    frndint
    fxch  st(1)
    fsub  st,st(1)
    f2xm1
    fld1
    faddp st(1),st
    fscale
    fstp  st(1)
done:
    ret

exp endp

    end
