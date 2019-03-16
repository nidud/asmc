; STRSTRI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include strlib.inc

    .code

strstri proc frame uses rsi dst:LPSTR, src:LPSTR

    mov rsi,strlen(rcx)
    memstri(dst, rsi, src, strlen(src))
    ret

strstri endp

    END
