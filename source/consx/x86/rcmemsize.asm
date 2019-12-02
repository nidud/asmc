; RCMEMSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcmemsize proc uses ecx edx rc, dflag
    movzx eax,byte ptr rc+2
    movzx edx,byte ptr rc+3
    mov ecx,eax
    mul dl
    add eax,eax
    .if byte ptr dflag & _D_SHADE
        add ecx,edx
        add ecx,edx
        sub ecx,2
        add eax,ecx
    .endif
    ret
rcmemsize endp

    END
