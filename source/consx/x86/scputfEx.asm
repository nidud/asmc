; SCPUTFEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include stdio.inc

    .code

scputfEx proc c uses edx ecx x, y, a, l, f:LPSTR, p:VARARG

    ftobufin(f, &p)
    scputsEx(x, y, a, l, &_bufin)
    ret

scputfEx endp

    END
