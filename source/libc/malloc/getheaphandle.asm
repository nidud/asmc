; GETHEAPHANDLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

.code

_get_heap_handle proc
ifndef __UNIX__
    mov rax,_crtheap
endif
    ret
_get_heap_handle endp

    end
