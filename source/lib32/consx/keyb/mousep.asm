; MOUSEP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

mousep proc uses ecx edx

    ReadEvent()
    mov eax,edx
    shr eax,16
    and eax,3
    ret

mousep endp

    END
