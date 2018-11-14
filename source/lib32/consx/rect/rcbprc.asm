; RCBPRC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rcbprc proc uses ebx edx rc, wbuf:PVOID, cols

    mov     eax,cols
    add     eax,eax
    movzx   ebx,rc.S_RECT.rc_y
    mul     ebx
    movzx   ebx,rc.S_RECT.rc_x
    add     eax,ebx
    add     eax,ebx
    add     eax,wbuf
    ret

rcbprc endp

    END
