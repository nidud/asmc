; _INPW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option stackbase:esp

_inpw proc port

    mov dx,word ptr [esp+4]
    in  ax,dx
    ret

_inpw endp

    END
