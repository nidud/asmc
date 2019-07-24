; __CORELEFT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

_FREE   equ 0
_USED   equ 1
_ALIGN  equ 3

    .code

    option win64:rsp noauto

__coreleft proc

    xor rax,rax         ; RAX: free memory
    xor rcx,rcx         ; RCX: total allocated
    mov r9,_heap_base

    .while r9

        .for ( rdx = r9 : [rdx].HEAP.size : rdx += r8 )

            mov r8,[rdx].HEAP.size
            add rcx,r8

            .if [rdx].HEAP.type == _FREE

                add rax,r8
            .endif
        .endf
        mov r9,[r9].HEAP.next
    .endw
    ret

__coreleft endp

    end
