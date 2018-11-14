; SETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    option win64:rsp nosave

setbuf proc fp:LPFILE, buf:LPSTR

    xchg rcx,rdx
    setvbuf(rcx, rdx, _IOFBF, _MINIOBUF)
    ret

setbuf endp

    END
