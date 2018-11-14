; SCPUTBG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

scputbg proc uses eax edx x, y, l, a

    mov edx,a
    mov ecx,l
    and dl,0xF0
    .repeat
        getxya(x, y)
        and al,0x0F
        or  al,dl
        scputa(x, y, 1, eax)
        inc x
    .untilcxz
    ret

scputbg endp

    END
