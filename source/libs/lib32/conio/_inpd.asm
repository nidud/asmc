; _INPD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option stackbase:esp

_inpd proc port

    mov dx,word ptr [esp+4]
    in  eax,dx
    ret

_inpd endp

    end
