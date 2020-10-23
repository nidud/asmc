; __SUBO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__subo proc a:ptr, b:ptr

    mov eax,a
    mov edx,b

    mov ecx,[edx+12]
    sub [eax+12],ecx
    mov ecx,[edx+8]
    sbb [eax+8],ecx
    mov ecx,[edx+4]
    sbb [eax+4],ecx
    mov ecx,[edx]
    sbb [eax],ecx
    ret

__subo endp

    end
