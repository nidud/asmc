; _OUTPD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option stackbase:esp

_outpd proc port, d

    mov dx,WORD PTR port
    mov eax,d
    out dx,eax
    ret

_outpd endp

    END
