; _OUTPW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option stackbase:esp

_outpw proc port, w

    mov dx,WORD PTR port
    mov ax,WORD PTR w
    out dx,ax
    ret

_outpw endp

    end
