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

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

__coreleft PROC
    xor rax,rax         ; RAX: free memory
    xor rcx,rcx         ; RCX: total allocated
    mov r9,_heap_base
    .while r9
        mov rdx,r9
        .while [rdx].S_HEAP.h_size
            mov r8,[rdx].S_HEAP.h_size
            add rcx,r8
            .if [rdx].S_HEAP.h_type == _FREE
                add rax,r8
            .endif
            add rdx,r8
        .endw
        mov r9,[r9].S_HEAP.h_next
    .endw
    ret
__coreleft ENDP

    END
