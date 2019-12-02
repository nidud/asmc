; __CORELEFT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc
include malloc.inc

    .code

__coreleft proc uses ebx

    .for eax = 0, ; EAX: free memory
        ecx = 0, ; ECX: total allocated
        ebx = _heap_base : ebx : ebx = [ebx].HEAP.next

        .for edx = ebx : [edx].HEAP.size : edx += [edx].HEAP.size

            add ecx,[edx].HEAP.size

            .if [edx].HEAP.type == 0

                add eax,[edx].HEAP.size
            .endif
        .endf
    .endf
    ret

__coreleft endp

    end
