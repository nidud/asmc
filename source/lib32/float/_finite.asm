; _FINITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_finite proc __cdecl d:REAL8

    mov edx,dword ptr d[4]
    shr edx,32 - DBL_EXPBITS - 1
    and edx,DBL_EXPMASK
    xor eax,eax
    .if edx != DBL_EXPMASK
	inc eax
    .endif
    ret

_finite endp

    end
