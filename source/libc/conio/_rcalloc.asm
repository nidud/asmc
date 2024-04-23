; _RCALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

.code

_rcalloc proc rc:TRECT, flags:uint_t

    ldr ecx,rc
    ldr edx,flags
    or  edx,W_UTF16

    malloc(_rcmemsize(ecx, edx))
    ret

_rcalloc endp

    end
