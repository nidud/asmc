; _DOS_YEAR.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.code

_dos_year proc

    mov ah,0x2A
    int 0x21
    mov ax,cx
    ret

_dos_year endp

    end
