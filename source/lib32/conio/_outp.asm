; _OUTP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option stackbase:esp

_outp proc port, b

    xor eax,eax
    mov dx,WORD PTR port
    mov al,BYTE PTR b
    out dx,al
    ret

_outp endp

    END
