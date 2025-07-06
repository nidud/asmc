; _DOS_DATE.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include dos.inc

.code

_dos_date proc

    _dos_time()
    mov ax,dx
    ret

_dos_date endp

    end
