include malloc.inc
include errno.inc

    .data

    _heap_base LPHEAP 0     ; address of main memory block
    _heap_free LPHEAP 0     ; address of free memory block

    .code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE

; Allocates memory blocks.
;
; void *malloc( size_t size );
;
malloc proc byte_count:size_t

    mov rdx,_heap_free
    add rcx,sizeof(S_HEAP)+_GRANULARITY-1
    and cl,-(_GRANULARITY)

    .repeat

        .if rdx

            .if [rdx].S_HEAP.h_type == _HEAP_FREE
                ;
                ; Use a free block.
                ;
                mov rax,[rdx].S_HEAP.h_size
                .if rax >= rcx

                    mov [rdx].S_HEAP.h_type,_HEAP_LOCAL

                    .ifnz

                        mov [rdx].S_HEAP.h_size,rcx
                        sub rax,rcx
                        mov [rdx+rcx].S_HEAP.h_size,rax
                        mov [rdx+rcx].S_HEAP.h_type,_HEAP_FREE
                    .endif

                    lea rax,[rdx+sizeof(S_HEAP)]
                    add rdx,[rdx].S_HEAP.h_size
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
                    mov rax,[rdx].S_HEAP.h_size
                    .if !rax
                        ;
                        ; Last block is zero and points to first block.
                        ;
                        mov rdx,[rdx].S_HEAP.h_prev
                        mov rdx,[rdx].S_HEAP.h_prev
                        .continue(0) .if rdx
                        .break
                    .endif

                    .continue(0) .if [rdx].S_HEAP.h_type != _HEAP_FREE
                    .continue(01) .if rax >= rcx
                    .continue(0) .if [rdx+rax].S_HEAP.h_type != _HEAP_FREE
                    .repeat
                        add rax,[rdx+rax].S_HEAP.h_size
                        mov [rdx].S_HEAP.h_size,rax
                    .until [rdx+rax].S_HEAP.h_type != _HEAP_FREE
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
        add ebx,sizeof(S_HEAP)
        .if rbx < rcx
            mov rbx,rcx
        .endif
        add rbx,sizeof(S_HEAP)
        HeapAlloc(GetProcessHeap(), 0, rbx)
        add rsp,0x28
        mov rdx,rbx
        pop rbx
        pop rcx
        .if !rax

            mov errno,ENOMEM
            ret
        .endif

        xor r8,r8
        sub rdx,sizeof(S_HEAP)

        mov [rax].S_HEAP.h_size,rdx
        mov [rax+8],r8
        mov [rax].S_HEAP.h_next,r8
        mov [rax].S_HEAP.h_prev,r8
        mov [rax+rdx].S_HEAP.h_size,r8
        mov [rax+rdx].S_HEAP.h_type,_HEAP_LOCAL
        mov [rax+rdx].S_HEAP.h_prev,rax

        mov rdx,_heap_base
        .if rdx

            .while [rdx].S_HEAP.h_next != r8

                mov rdx,[rdx].S_HEAP.h_next
            .endw
            mov [rdx].S_HEAP.h_next,rax
            mov [rax].S_HEAP.h_prev,rdx
        .else
            mov _heap_base,rax
        .endif
        mov _heap_free,rax

        mov rdx,rax
        mov rax,[rdx].S_HEAP.h_size
        .continue(0) .if rax >= rcx

        mov errno,ENOMEM
        xor eax,eax
    .until 1
    ret

malloc endp

; Deallocates or frees a memory block.
;
; void free( void *memblock );
;
free proc memblock:PVOID

    sub rcx,sizeof(S_HEAP)
    .ifns
        ;
        ; If memblock is NULL, the pointer is ignored. Attempting to free an
        ; invalid pointer not allocated by malloc() may cause errors.
        ;
        .if [rcx].S_HEAP.h_type == _HEAP_ALIGNED

            mov rcx,[rcx].S_HEAP.h_prev
        .endif

        .if [rcx].S_HEAP.h_type == _HEAP_LOCAL

            xor edx,edx
            mov [rcx+8],rdx ; Delete this block.

            .for(r8 = [rcx].S_HEAP.h_size: dl == [rcx+r8].S_HEAP.h_type:,
                 r8 += [rcx+r8].S_HEAP.h_size, [rcx].S_HEAP.h_size = r8)
                 ;
                 ; Extend size of block if next block is free.
                 ;
            .endf
            mov _heap_free,rcx

            .if rdx == [rcx+r8].S_HEAP.h_size
                ;
                ; This is the last bloc in this chain.
                ;
                mov rcx,[rcx+r8].S_HEAP.h_prev ; <= first bloc
                .if dl == [rcx].S_HEAP.h_type

                    .for(r8 = [rcx].S_HEAP.h_size: dl == [rcx+r8].S_HEAP.h_type:,
                         r8 += [rcx+r8].S_HEAP.h_size, [rcx].S_HEAP.h_size = r8)
                    .endf

                    .if rdx == [rcx+r8].S_HEAP.h_size

                        push rax
                        push rbx
                        mov  rbx,rcx
                        ;
                        ; unlink the node
                        ;
                        mov rcx,[rbx].S_HEAP.h_prev
                        mov rax,[rbx].S_HEAP.h_next
                        .if rcx
                            mov [rcx].S_HEAP.h_next,rax
                        .endif
                        .if rax
                            mov [rax].S_HEAP.h_prev,rcx
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
