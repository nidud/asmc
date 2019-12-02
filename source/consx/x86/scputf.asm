; SCPUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include stdio.inc

    .code

scputf proc c uses edx ecx x, y, a, l, f:LPSTR, p:VARARG

    ftobufin(f, &p)
    scputs(x, y, a, l, &_bufin)
    ret

scputf endp

    END
