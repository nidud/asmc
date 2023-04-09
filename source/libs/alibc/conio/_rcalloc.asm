; _RCALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

.code

_rcalloc proc rc:TRECT, shade:int_t

    malloc(_rcmemsize(edi, esi))
    ret

_rcalloc endp

    end
