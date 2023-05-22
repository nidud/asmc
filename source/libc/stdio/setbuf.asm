; SETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

setbuf proc fp:LPFILE, buf:LPSTR

    ldr rcx,fp
    ldr rax,buf
    setvbuf( rax, rcx, _IOFBF, _MINIOBUF )
    ret

setbuf endp

    end
