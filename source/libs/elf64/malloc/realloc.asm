; REALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

_FREE   equ 0
_LOCAL  equ 1
_GLOBAL equ 2

    .code

realloc proc uses rbx pblck:ptr, newsize:size_t

    ;
    ; special cases, handling mandated by ANSI
    ;
    ; just do a malloc of newsize bytes and return a pointer to
    ; the new block
    ;
    .return malloc(rsi) .if !rdi

    .if !rsi
        ;
        ; free the block and return NULL
        ;
        free(rdi)
        .return NULL
    .endif
    ;
    ; make newsize a valid allocation block size (i.e., round up to the
    ; nearest granularity)
    ;
    lea rax,[rsi+HEAP+_GRANULARITY-1]
    and rax,-(_GRANULARITY)
    lea r8,[rdi-HEAP]
    mov r9,[r8].HEAP.size

    .return rdi .if rax == r9

    .if [r8].HEAP.type == _LOCAL

        .if rax < r9

            sub r9,rax
            .return rdi .if r9 <= HEAP + _GRANULARITY

            mov [r8].HEAP.size,rax
            mov [r8+rax].HEAP.size,r9
            mov [r8+rax].HEAP.type,0
            .return rdi
        .endif
        ;
        ; see if block is big enough already, or can be expanded
        ;
        mov r10,r9  ; add up free blocks
        mov r11,r9
        .while [r8+r10].HEAP.type == _FREE && r11

            mov r11,[r8+r10].HEAP.size
            add r10,r11
        .endw

        .if r10 >= rax
            ;
            ; expand block
            ;
            sub r10,rax
            .if r10 >= HEAP

                mov [r8].HEAP.size,rax
                mov [r8+rax].HEAP.size,r10
                mov [r8+rax].HEAP.type,_FREE
            .else

                mov [r8].HEAP.size,r10
            .endif
            .return rdi
        .endif
    .endif

    mov rbx,r8  ; block
    .if malloc(rax)

        mov rcx,[rbx].HEAP.size
        sub rcx,HEAP
        add rbx,HEAP
        mov rsi,rbx
        mov rdi,rax
        rep movsb
        xchg rbx,rax
        free(rax)
        mov rax,rbx
    .endif
    ret

realloc endp

    end
