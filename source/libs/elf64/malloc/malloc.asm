; MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc
include linux/kernel.inc

CALL_MMAP macro s
    exitm<sys_mmap(0, (s), MMAP_PROT, MMAP_FLAGS, -1, 0)>
    endm

public  _crtheap

    .data

    _crtheap label HANDLE
    _heap_base heap_t 0     ; address of main memory block
    _heap_free heap_t 0     ; address of free memory block

    .code

CreateHeap proc private uses rbx r12 s:size_t

    mov r12,rdi
    mov ebx,_amblksiz
    add ebx,HEAP
    .if rbx < rdi
        mov rbx,rdi
    .endif
    add rbx,HEAP

    .if ( CALL_MMAP(rbx) == MAP_FAILED )

        _set_errno(ENOMEM)
       .return( NULL )
    .endif

    mov rdx,rbx
    mov rdi,r12
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
    .if rax < rdi

        _set_errno(ENOMEM)
        xor eax,eax
    .endif
    ret

CreateHeap endp

; Allocates memory blocks.
;
; void *malloc( size_t size );
;
malloc proc byte_count:size_t

    mov rdx,_heap_free
    add rdi,HEAP+_GRANULARITY-1
    and dil,-(_GRANULARITY)

    .repeat

        .if rdx

            .if [rdx].HEAP.type == _HEAP_FREE
                ;
                ; Use a free block.
                ;
                mov rax,[rdx].HEAP.size
                .if rax >= rdi

                    mov [rdx].HEAP.type,_HEAP_LOCAL

                    .ifnz

                        mov [rdx].HEAP.size,rdi
                        sub rax,rdi
                        mov [rdx+rdi].HEAP.size,rax
                        mov [rdx+rdi].HEAP.type,_HEAP_FREE
                    .endif

                    lea rax,[rdx+HEAP]
                    add rdx,[rdx].HEAP.size
                    mov _heap_free,rdx
                   .return

                .endif
            .endif

            mov eax,_amblksiz
            .if rdi <= rax
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
                    .continue(01) .if rax >= rdi
                    .continue(0) .if [rdx+rax].HEAP.type != _HEAP_FREE
                    .repeat
                        add rax,[rdx+rax].HEAP.size
                        mov [rdx].HEAP.size,rax
                    .until [rdx+rax].HEAP.type != _HEAP_FREE
                    .continue(01) .if rax >= rdi
                .endw
            .endif
        .endif

        .if ( CreateHeap(rdi) )

            .continue(0)
        .endif
    .until 1
    ret

malloc endp

; Deallocates or frees a memory block.
;
; void free( void *memblock );
;
free proc memblock:ptr

    sub rdi,HEAP
    .ifns
        ;
        ; If memblock is NULL, the pointer is ignored. Attempting to free an
        ; invalid pointer not allocated by malloc() may cause errors.
        ;
        .if [rdi].HEAP.type == _HEAP_ALIGNED

            mov rdi,[rdi].HEAP.prev
        .endif

        .if [rdi].HEAP.type == _HEAP_LOCAL

            xor edx,edx
            mov [rdi+8],rdx ; Delete this block.

            .for( r8 = [rdi].HEAP.size,
                : dl == [rdi+r8].HEAP.type,
                : r8 += [rdi+r8].HEAP.size, [rdi].HEAP.size = r8 )
                 ;
                 ; Extend size of block if next block is free.
                 ;
            .endf
            mov _heap_free,rdi

            .if rdx == [rdi+r8].HEAP.size
                ;
                ; This is the last bloc in this chain.
                ;
                mov rdi,[rdi+r8].HEAP.prev ; <= first bloc
                .if dl == [rdi].HEAP.type

                    .for( r8 = [rdi].HEAP.size,
                        : dl == [rdi+r8].HEAP.type,
                        : r8 += [rdi+r8].HEAP.size, [rdi].HEAP.size = r8 )
                    .endf

                    .if rdx == [rdi+r8].HEAP.size

                        ;
                        ; unlink the node
                        ;
                        mov rdx,[rdi].HEAP.prev
                        mov rax,[rdi].HEAP.next
                        .if rdx
                            mov [rdx].HEAP.next,rax
                        .endif
                        .if rax
                            mov [rax].HEAP.prev,rdx
                        .endif
                        mov rax,_heap_base
                        .if rax == rdi
                            xor rax,rax
                            mov _heap_base,rax
                        .endif
                        mov _heap_free,rax

                        .if ( rdi )

                            sub rdi,HEAP
                            mov rsi,[rdi]
                            sys_munmap(rdi, rsi)
                        .endif
                    .endif
                .endif
            .endif
        .endif
    .endif
    ret

free endp

    END
