; _DOS_DAY.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.code

_dos_day proc

    mov ah,0x2A
    int 0x21
    mov ah,0
    mov al,dl
    ret

_dos_day endp

    end
