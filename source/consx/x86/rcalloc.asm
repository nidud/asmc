; RCALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include malloc.inc

    .code

rcalloc proc rc:S_RECT, shade:UINT

    malloc(rcmemsize(rc, shade))
    ret

rcalloc endp

    END
