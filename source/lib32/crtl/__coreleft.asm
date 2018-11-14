; __CORELEFT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

__coreleft proc uses ebx
    xor eax,eax  ; EAX: free memory
    xor ecx,ecx  ; ECX: total allocated
    mov ebx,_heap_base
    .while ebx
        mov edx,ebx
        .while [edx].S_HEAP.h_size
            add ecx,[edx].S_HEAP.h_size
            .if [edx].S_HEAP.h_type == 0
                add eax,[edx].S_HEAP.h_size
            .endif
            add edx,[edx].S_HEAP.h_size
        .endw
        mov ebx,[ebx].S_HEAP.h_next
    .endw
    ret
__coreleft endp

    end
