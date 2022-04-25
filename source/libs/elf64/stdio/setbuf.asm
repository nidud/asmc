; SETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

setbuf proc fp:LPFILE, buf:LPSTR

    xchg rdi,rsi
    setvbuf(rdi, rsi, _IOFBF, _MINIOBUF)
    ret

setbuf endp

    end
