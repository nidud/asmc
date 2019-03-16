; STRMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc
include string.inc

    .code

    option win64:rsp

strmove proc frame dst:LPSTR, src:LPSTR

    memmove(dst, src, &[strlen(rdx)+1])
    ret

strmove endp

    END
