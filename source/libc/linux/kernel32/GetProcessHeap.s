; GETPROCESSHEAP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include heapapi.inc

.code

GetProcessHeap proc WINAPI
    mov eax,1 ; Non-NULL dummy process heap handle
    ret
    endp

    end
