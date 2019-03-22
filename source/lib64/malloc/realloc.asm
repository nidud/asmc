; REALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include errno.inc

_FREE   equ 0
_LOCAL  equ 1
_GLOBAL equ 2

    .code

realloc proc frame uses rsi rdi pblck:ptr, newsize:size_t

    .repeat
        ;
        ; special cases, handling mandated by ANSI
        ;
        .if !rcx
            ;
            ; just do a malloc of newsize bytes and return a pointer to
            ; the new block
            ;
            malloc(rdx)
            .break
        .endif

        .if !rdx
            ;
            ; free the block and return NULL
            ;
            free(rcx)
            xor rax,rax
            .break
        .endif
        ;
        ; make newsize a valid allocation block size (i.e., round up to the
        ; nearest granularity)
        ;
        lea rax,[rdx+sizeof(S_HEAP)+_GRANULARITY-1]
        and rax,-(_GRANULARITY)
        lea r8,[rcx-sizeof(S_HEAP)]
        mov r9,[r8].S_HEAP.h_size

        .if rax == r9

            mov rax,rcx
            .break
        .endif

        .if [r8].S_HEAP.h_type == _LOCAL

            .if rax < r9

                sub r9,rax
                .if r9 <= sizeof(S_HEAP) + _GRANULARITY

                    mov rax,rcx
                    .break
                .endif
                mov [r8].S_HEAP.h_size,rax
                add rax,r8
                mov [rax].S_HEAP.h_size,r9
                mov [rax].S_HEAP.h_type,0
                mov rax,rcx
                .break
            .endif
            ;
            ; see if block is big enough already, or can be expanded
            ;
            mov r10,r9  ; add up free blocks
            mov r11,r9
            .while [r8+r10].S_HEAP.h_type == _FREE && r11

                mov r11,[r8+r10].S_HEAP.h_size
                add r10,r11
            .endw

            .if r10 >= rax
                ;
                ; expand block
                ;
                sub r10,rax
                .if r10 >= sizeof(S_HEAP)

                    mov [r8].S_HEAP.h_size,rax
                    mov [r8+rax].S_HEAP.h_size,r10
                    mov [r8+rax].S_HEAP.h_type,_FREE
                .else

                    mov [r8].S_HEAP.h_size,r10
                .endif
                mov rax,rcx
                .break
            .endif
        .endif

        mov rsi,r8  ; block
        mov rdi,rax ; new size
        .if malloc(rax)

            mov rcx,[rsi].S_HEAP.h_size
            sub rcx,sizeof(S_HEAP)
            add rsi,sizeof(S_HEAP)
            mov rdx,rsi
            mov rdi,rax
            rep movsb
            free(rdx)
        .endif

    .until 1
    ret

realloc ENDP

    END
