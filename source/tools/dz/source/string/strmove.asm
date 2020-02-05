; STRMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include string.inc

    .code

strmove PROC dst:LPSTR, src:LPSTR

    inc strlen(src)
    memmove(dst, src, eax)
    ret

strmove ENDP

    END
