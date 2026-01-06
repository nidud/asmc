; SETBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

setbuf proc fp:LPFILE, buf:string_t

    setvbuf( buf, ldr(fp), _IOFBF, _MINIOBUF )
    ret

setbuf endp

    end
