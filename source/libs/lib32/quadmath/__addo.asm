; __ADDO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__addo proc a:ptr, b:ptr

    mov eax,a
    mov edx,b

    mov ecx,[edx]
    add [eax],ecx
    mov ecx,[edx+4]
    adc [eax+4],ecx
    mov ecx,[edx+8]
    adc [eax+8],ecx
    mov ecx,[edx+12]
    adc [eax+12],ecx
    ret

__addo endp

    end
