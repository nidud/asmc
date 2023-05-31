; REALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

realloc proc uses rsi rdi rbx pblck:ptr, newsize:size_t

    ldr rcx,pblck
    ldr rdx,newsize

    ; special cases, handling mandated by ANSI
    ;
    ; just do a malloc of newsize bytes and return a pointer to
    ; the new block

    .if ( rcx == NULL )
        .return malloc( rdx )
    .endif

    .if ( rdx == NULL )

        ; free the block and return NULL

        free( rcx )
       .return NULL
    .endif

    ; make newsize a valid allocation block size (i.e., round up to the
    ; nearest granularity)

    lea rax,[rdx+HEAP+_GRANULARITY-1]
    and rax,-(_GRANULARITY)
    lea rdi,[rcx-HEAP]
    mov rbx,[rdi].HEAP.size

    .if ( rax == rbx )
        .return( rcx )
    .endif

    .if ( [rdi].HEAP.type == _HEAP_LOCAL )

        .if ( rax < rbx )

            sub rbx,rax
            .if ( rbx <= HEAP + _GRANULARITY )
                .return( rcx )
            .endif

            mov [rdi].HEAP.size,rax
            mov [rdi+rax].HEAP.size,rbx
            mov [rdi+rax].HEAP.type,0
           .return( rcx )
        .endif
        ;
        ; see if block is big enough already, or can be expanded
        ;
        mov rdx,rbx  ; add up free blocks
        .while ( [rdi+rdx].HEAP.type == _HEAP_FREE && rbx )

            mov rbx,[rdi+rdx].HEAP.size
            add rdx,rbx
        .endw

        .if ( rdx >= rax )
            ;
            ; expand block
            ;
            sub rdx,rax
            .if ( rdx >= HEAP )

                mov [rdi].HEAP.size,rax
                mov [rdi+rax].HEAP.size,rdx
                mov [rdi+rax].HEAP.type,_HEAP_FREE
            .else
                mov [rdi].HEAP.size,rdx
            .endif
            .return( rcx )
        .endif
    .endif

    mov rbx,rdi  ; block
    .if malloc( rax )

        mov rcx,[rbx].HEAP.size
        sub rcx,HEAP
        add rbx,HEAP
        mov rsi,rbx
        mov rdi,rax
        rep movsb
        mov rcx,rbx
        mov rbx,rax

        free( rcx )
        mov rax,rbx
    .endif
    ret

realloc endp

    end
