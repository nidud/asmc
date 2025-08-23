; HEAPTERM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

.code

_heap_term proc
ifndef __UNIX__
    mov _crtheap,NULL
endif
    ret
_heap_term endp

    end
