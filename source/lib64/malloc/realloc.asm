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

realloc proc frame uses rsi rdi pblck:ptr, newsize:size_t

    ;
    ; special cases, handling mandated by ANSI
    ;
    ; just do a malloc of newsize bytes and return a pointer to
    ; the new block
    ;
    .return malloc(rdx) .if !rcx

    .if !rdx
        ;
        ; free the block and return NULL
        ;
        free(rcx)
        .return NULL
    .endif
    ;
    ; make newsize a valid allocation block size (i.e., round up to the
    ; nearest granularity)
    ;
    lea rax,[rdx+HEAP+_GRANULARITY-1]
    and rax,-(_GRANULARITY)
    lea r8,[rcx-HEAP]
    mov r9,[r8].HEAP.size

    .return rcx .if rax == r9

    .if [r8].HEAP.type == _LOCAL

        .if rax < r9

            sub r9,rax
            .return rcx .if r9 <= HEAP + _GRANULARITY

            mov [r8].HEAP.size,rax
            mov [r8+rax].HEAP.size,r9
            mov [r8+rax].HEAP.type,0
            .return rcx
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
            .return rcx
        .endif
    .endif

    mov rsi,r8  ; block
    mov rdi,rax ; new size
    .if malloc(rax)

        mov rcx,[rsi].HEAP.size
        sub rcx,HEAP
        add rsi,HEAP
        mov rdx,rsi
        mov rdi,rax
        rep movsb
        free(rdx)
    .endif
    ret

realloc endp

    end
