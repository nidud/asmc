; REALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

realloc proc uses rsi rdi pblck:ptr, newsize:size_t

    ldr rcx,pblck
    ldr rdx,newsize

    ;
    ; special cases, handling mandated by ANSI
    ;
    ; just do a malloc of newsize bytes and return a pointer to
    ; the new block
    ;
    .if ( rcx == NULL )
        .return malloc( rdx )
    .endif

    .if ( rdx == NULL )
        ;
        ; free the block and return NULL
        ;
        free( rcx )
       .return NULL
    .endif
    ;
    ; make newsize a valid allocation block size (i.e., round up to the
    ; nearest granularity)
    ;
    lea rax,[rdx+HEAP+_GRANULARITY-1]
    and rax,-(_GRANULARITY)
    lea rdi,[rcx-HEAP]
    mov rsi,[rdi].HEAP.size

    .if ( rax == rsi )
        .return( rcx )
    .endif

    .if ( [rdi].HEAP.type == _HEAP_LOCAL )

        .if ( rax < rsi )

            sub rsi,rax
            .if ( rsi <= HEAP + _GRANULARITY )
                .return( rcx )
            .endif

            mov [rdi].HEAP.size,rax
            mov [rdi+rax].HEAP.size,rsi
            mov [rdi+rax].HEAP.type,0
           .return( rcx )
        .endif
        ;
        ; see if block is big enough already, or can be expanded
        ;
        mov rdx,rsi  ; add up free blocks
        .while ( [rdi+rdx].HEAP.type == _HEAP_FREE && rsi )

            mov rsi,[rdi+rdx].HEAP.size
            add rdx,rsi
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

    mov rsi,rdi  ; block
    .if malloc( rax )

        mov rcx,[rsi].HEAP.size
        sub rcx,HEAP
        add rsi,HEAP
        mov rdx,rsi
        mov rdi,rax
        rep movsb
        mov rsi,rax

        free( rdx )
        mov rax,rsi
    .endif
    ret

realloc endp

    end
