; SCPUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

scpush proc lcount

    mov eax,lcount
    mov ah,80
    shl eax,16
    rcopen(eax, 0, 0, 0, 0)
    ret

scpush endp

scpop proc wp, lc

    mov eax,lc
    mov ah,80
    shl eax,16
    rcclose(eax, _D_DOPEN or _D_ONSCR, wp)
    ret

scpop endp

    END
