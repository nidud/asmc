; _DOS_HOUR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.code

_dos_hour proc

    mov ah,0x2C
    int 0x21
    mov al,ch
    mov ah,0
    ret

_dos_hour endp

    end
