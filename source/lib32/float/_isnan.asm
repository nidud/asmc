; _ISNAN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include float.inc

.code

_isnan proc d:REAL8

    mov eax,dword ptr d
    mov edx,dword ptr d[4]
    mov ecx,edx
    shl edx,DBL_EXPBITS
    or  edx,eax
    shr ecx,32 - DBL_EXPBITS - 1
    and ecx,DBL_EXPMASK
    xor eax,eax
    .if ecx == DBL_EXPMASK && edx
        inc eax
    .endif
    ret

_isnan endp

    end
