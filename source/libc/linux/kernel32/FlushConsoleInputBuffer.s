; FLUSHCONSOLEINPUTBUFFER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

.code

 FlushConsoleInputBuffer proc WINAPI hConsoleInput:HANDLE
    ret
    endp

    end
