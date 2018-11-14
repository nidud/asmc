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
    shl edx,D_EXPBITS
    or  edx,eax
    shr ecx,32 - D_EXPBITS - 1
    and ecx,D_EXPMASK
    xor eax,eax
    .if ecx == D_EXPMASK && edx
        inc eax
    .endif
    ret

_isnan endp

    end
