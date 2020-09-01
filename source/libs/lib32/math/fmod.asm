; FMOD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
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
