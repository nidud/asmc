; GLOBALSIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include winbase.inc

.code

 GlobalSize proc WINAPI hMem:HGLOBAL
    ldr rax,hMem
    .if ( rax )
        mov rax,[rax-HEAP].HEAP.size
    .endif
    ret
    endp

    end
