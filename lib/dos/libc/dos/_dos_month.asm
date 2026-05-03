; _DOS_MONTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.code

_dos_month proc

    mov ah,0x2A
    int 0x21
    mov ah,0
    mov al,dh
    ret

_dos_month endp

    end
