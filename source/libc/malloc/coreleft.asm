; CORELEFT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

_coreleft proc uses rbx

    .for eax = 0, ; EAX: free memory
         ecx = 0, ; ECX: total allocated
         rbx = _heap_base : rbx : rbx = [rbx].HEAP.next

        .for rdx = rbx : [rdx].HEAP.size : rdx += [rdx].HEAP.size

            add rcx,[rdx].HEAP.size

            .if [rdx].HEAP.type == 0

                add rax,[rdx].HEAP.size
            .endif
        .endf
    .endf
    ret

_coreleft endp

    end
