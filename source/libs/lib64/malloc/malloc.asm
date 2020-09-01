; MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc

public  _crtheap

    .data

    _crtheap label HANDLE
    _heap_base heap_t 0     ; address of main memory block
    _heap_free heap_t 0     ; address of free memory block

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

; Allocates memory blocks.
;
; void *malloc( size_t size );
;
malloc proc byte_count:size_t

    mov rdx,_heap_free
    add rcx,HEAP+_GRANULARITY-1
    and cl,-(_GRANULARITY)

    .repeat

        .if rdx

            .if [rdx].HEAP.type == _HEAP_FREE
                ;
                ; Use a free block.
                ;
                mov rax,[rdx].HEAP.size
                .if rax >= rcx

                    mov [rdx].HEAP.type,_HEAP_LOCAL

                    .ifnz

                        mov [rdx].HEAP.size,rcx
                        sub rax,rcx
                        mov [rdx+rcx].HEAP.size,rax
                        mov [rdx+rcx].HEAP.type,_HEAP_FREE
                    .endif

                    lea rax,[rdx+HEAP]
                    add rdx,[rdx].HEAP.size
                    mov _heap_free,rdx
                    ret

                .endif
            .endif

            mov eax,_amblksiz
            .if rcx <= rax
                ;
                ; Find a free block.
                ;
                mov rdx,_heap_base
                xor eax,eax

                .while 1

                    add rdx,rax
                    mov rax,[rdx].HEAP.size
                    .if !rax
                        ;
                        ; Last block is zero and points to first block.
                        ;
                        mov rdx,[rdx].HEAP.prev
                        mov rdx,[rdx].HEAP.prev
                        .continue(0) .if rdx
                        .break
                    .endif

                    .continue(0) .if [rdx].HEAP.type != _HEAP_FREE
                    .continue(01) .if rax >= rcx
                    .continue(0) .if [rdx+rax].HEAP.type != _HEAP_FREE
                    .repeat
                        add rax,[rdx+rax].HEAP.size
                        mov [rdx].HEAP.size,rax
                    .until [rdx+rax].HEAP.type != _HEAP_FREE
                    .continue(01) .if rax >= rcx
                .endw
            .endif
        .endif
        ;
        ; Create heap.
        ;
        push rcx
        push rbx
        sub rsp,0x28
        mov ebx,_amblksiz
        add ebx,HEAP
        .if rbx < rcx
            mov rbx,rcx
        .endif
        add rbx,HEAP
        HeapAlloc(GetProcessHeap(), 0, rbx)
        add rsp,0x28
        mov rdx,rbx
        pop rbx
        pop rcx
        .if !rax

            _set_errno(ENOMEM)
            ret
        .endif

        xor r8,r8
        sub rdx,HEAP

        mov [rax].HEAP.size,rdx
        mov [rax+8],r8
        mov [rax].HEAP.next,r8
        mov [rax].HEAP.prev,r8
        mov [rax+rdx].HEAP.size,r8
        mov [rax+rdx].HEAP.type,_HEAP_LOCAL
        mov [rax+rdx].HEAP.prev,rax

        mov rdx,_heap_base
        .if rdx

            .while [rdx].HEAP.next != r8

                mov rdx,[rdx].HEAP.next
            .endw
            mov [rdx].HEAP.next,rax
            mov [rax].HEAP.prev,rdx
        .else
            mov _heap_base,rax
        .endif
        mov _heap_free,rax

        mov rdx,rax
        mov rax,[rdx].HEAP.size
        .continue(0) .if rax >= rcx

        _set_errno(ENOMEM)
        xor eax,eax
    .until 1
    ret

malloc endp

; Deallocates or frees a memory block.
;
; void free( void *memblock );
;
free proc memblock:ptr

    sub rcx,HEAP
    .ifns
        ;
        ; If memblock is NULL, the pointer is ignored. Attempting to free an
        ; invalid pointer not allocated by malloc() may cause errors.
        ;
        .if [rcx].HEAP.type == _HEAP_ALIGNED

            mov rcx,[rcx].HEAP.prev
        .endif

        .if [rcx].HEAP.type == _HEAP_LOCAL

            xor edx,edx
            mov [rcx+8],rdx ; Delete this block.

            .for( r8 = [rcx].HEAP.size,
                : dl == [rcx+r8].HEAP.type,
                : r8 += [rcx+r8].HEAP.size, [rcx].HEAP.size = r8 )
                 ;
                 ; Extend size of block if next block is free.
                 ;
            .endf
            mov _heap_free,rcx

            .if rdx == [rcx+r8].HEAP.size
                ;
                ; This is the last bloc in this chain.
                ;
                mov rcx,[rcx+r8].HEAP.prev ; <= first bloc
                .if dl == [rcx].HEAP.type

                    .for( r8 = [rcx].HEAP.size,
                        : dl == [rcx+r8].HEAP.type,
                        : r8 += [rcx+r8].HEAP.size, [rcx].HEAP.size = r8 )
                    .endf

                    .if rdx == [rcx+r8].HEAP.size

                        push rax
                        push rbx
                        mov  rbx,rcx
                        ;
                        ; unlink the node
                        ;
                        mov rcx,[rbx].HEAP.prev
                        mov rax,[rbx].HEAP.next
                        .if rcx
                            mov [rcx].HEAP.next,rax
                        .endif
                        .if rax
                            mov [rax].HEAP.prev,rcx
                        .endif
                        mov rax,_heap_base
                        .if rax == rbx
                            xor rax,rax
                            mov _heap_base,rax
                        .endif
                        mov _heap_free,rax
                        sub rsp,0x28
                        HeapFree(GetProcessHeap(), 0, rbx)
                        add rsp,0x28
                        pop rbx
                        pop rax
                    .endif
                .endif
            .endif
        .endif
    .endif
    ret

free endp

    END
