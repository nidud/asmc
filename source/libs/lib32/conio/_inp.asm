; _INP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include libc.inc

    .code

    option stackbase:esp

_inp proc port

    xor eax,eax
    mov dx,word ptr [esp+4]
    in  al,dx
    ret

_inp endp

    end
