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
        .while [edx].HEAP.size
            add ecx,[edx].HEAP.size
            .if [edx].HEAP.type == 0
                add eax,[edx].HEAP.size
            .endif
            add edx,[edx].HEAP.size
        .endw
        mov ebx,[ebx].HEAP.next
    .endw
    ret
__coreleft endp

    end
