; FMOD.ASM--
; Copyright (C) 2017 Asmc Developers
;
include math.inc

.code

fmod proc __cdecl x:double, y:double

    fld x
    fld y
    fxch st(1)
    .repeat
	fprem
	fstsw ax
	sahf
    .untilnp
    fstp st(1)
    ret

fmod endp

    end
