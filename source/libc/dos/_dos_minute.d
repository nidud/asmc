; _DOS_MINUTE.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.code

_dos_minute proc

    mov ah,0x2C
    int 0x21
    mov al,cl
    mov ah,0
    ret

_dos_minute endp

    end
