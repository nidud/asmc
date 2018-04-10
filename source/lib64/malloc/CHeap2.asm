include string.inc
include errno.inc
include CHeap.inc

_FREE   equ 0
_USED   equ 1
_ALIGN  equ 3

MBLOCK  STRUC
bsize   dd ?
flags   dd ?
prev    dq ?
MBLOCK  ENDS

    .code

    option cstack:on, win64:rsp nosave noauto

    assume rcx:LPCHEAP
    assume rdx:ptr MBLOCK

;
; void *CHeap::Alloc( unsigned int byte_count );
;
CHeap::Alloc proc byte_count:UINT

    mov eax,edx
    add eax,sizeof(MBLOCK) + _GRANULARITY - 1
    and al,-(_GRANULARITY)

    mov rdx,[rcx].heap_free

    .repeat

        .if rdx

            .if [rdx].flags == _FREE
                ;
                ; Use a free block.
                ;
                mov r8d,[rdx].bsize
                .if r8d >= eax

                    mov [rdx].flags,_USED

                    .ifnz

                        mov [rdx].bsize,eax
                        sub r8d,eax
                        mov [rdx+rax].bsize,r8d
                        mov [rdx+rax].flags,_FREE
                        mov r8d,eax
                    .endif
                    lea rax,[rdx+sizeof(MBLOCK)]
                    add rdx,r8
                    mov [rcx].heap_free,rdx
                    ret
                .endif
            .endif
            ;
            ; Find a free block.
            ;
            mov rdx,[rcx].heap_base
            xor r8d,r8d

            .while 1

                add rdx,r8
                mov r8d,[rdx].bsize

                .break .if !r8d
                .continue(0) .if [rdx].flags != _FREE
                .continue(01) .if r8d >= eax
                .continue(0) .if [rdx+r8].flags != _FREE
                .repeat
                    add r8d,[rdx+r8].bsize
                    mov [rdx].bsize,r8d
                .until [rdx+r8].flags != _FREE
                .continue(01) .if r8d >= eax
            .endw
        .endif
        ;
        ; No heap.
        ;
        mov errno,ENOMEM
        xor eax,eax
    .until 1
    ret

CHeap::Alloc endp

;
; void CStack::Free( void *memblock );
;
CHeap::Free proc memblock:PVOID

    sub rdx,sizeof(MBLOCK)
    .ifns
        ;
        ; If memblock is NULL, the pointer is ignored. Attempting to free an
        ; invalid pointer not allocated by ::Alloc() may cause errors.
        ;
        .if [rdx].flags == _ALIGN

            mov rdx,[rdx].prev
        .endif

        .if [rdx].flags == _USED

            mov [rdx].flags,_FREE   ; Delete this block.
            mov [rcx].heap_free,rdx
            ;
            ; Extend size if next block is free.
            ;
            .for r8d=[rdx].bsize : [rdx+r8].flags == _FREE : r8d+=[rdx+r8].bsize,
                [rdx].bsize=r8d
            .endf
        .endif
    .endif
    ret

CHeap::Free endp

CHeap::Coreleft proc

    mov rdx,[rcx].heap_base

    xor eax,eax ; RAX: free memory
    xor ecx,ecx ; RCX: total allocated

    .while [rdx].bsize

        mov r8d,[rdx].bsize
        lea rcx,[rcx+r8-sizeof(MBLOCK)]

        .if [rdx].flags == _FREE

            lea rax,[rax+r8-sizeof(MBLOCK)]
        .endif
        add rdx,r8
    .endw
    ret

CHeap::Coreleft endp

    option win64:rbp nosave

CHeap::Aligned proc dwSize:UINT, Alignment:UINT

    mov r9d,r8d
    lea rdx,[rdx+r8+sizeof(MBLOCK)]

    .if [rcx].Alloc(edx)

        dec r9d
        .if eax & r9d

            lea r8,[rax-sizeof(MBLOCK)]
            lea rax,[rax+r9+sizeof(MBLOCK)]
            not r9
            and rax,r9
            lea rdx,[rax-sizeof(MBLOCK)]
            mov [rdx].prev,r8
            mov [rdx].flags,_ALIGN
        .endif
    .endif
    ret

CHeap::Aligned endp

CHeap::Realloc proc uses rsi rdi rbx pblck:ptr, newsize:size_t

    .repeat
        ;
        ; special cases, handling mandated by ANSI
        ;
        .if !rdx
            ;
            ; just do a malloc of newsize bytes and return a pointer to
            ; the new block
            ;
            [rcx].Alloc(r8d)
            .break
        .endif

        .if !r8d
            ;
            ; free the block and return NULL
            ;
            [rcx].Free(rdx)
            xor eax,eax
            .break
        .endif
        ;
        ; make newsize a valid allocation block size (i.e., round up to the
        ; nearest granularity)
        ;
        lea rax,[r8+sizeof(MBLOCK)+_GRANULARITY-1]
        and al,-(_GRANULARITY)

        lea r9,[rdx-sizeof(MBLOCK)]
        mov r10d,[r9].MBLOCK.bsize

        .if eax == r10d

            mov rax,rdx
            .break
        .endif

        .if [r9].MBLOCK.flags == _USED

            .if eax < r10d

                sub r10d,eax
                .if r10d > sizeof(MBLOCK) + _GRANULARITY

                    mov [r9].MBLOCK.bsize,eax
                    mov [r9+rax].MBLOCK.bsize,r10d
                    mov [r9+rax].MBLOCK.flags,_FREE
                .endif

                mov rax,rdx
                .break
            .endif
            ;
            ; see if block is big enough already, or can be expanded
            ;
            .while [r9+r10].MBLOCK.flags == _FREE

                mov r11d,[r9+r10].MBLOCK.bsize
                add r10d,r11d
            .endw

            .if r10d >= eax
                ;
                ; expand block
                ;
                sub r10d,eax
                .if r10d >= sizeof(MBLOCK)

                    mov [r9].MBLOCK.bsize,eax
                    mov [r9+rax].MBLOCK.bsize,r10d
                    mov [r9+rax].MBLOCK.flags,_FREE
                .else

                    mov [r9].MBLOCK.bsize,r10d
                .endif
                mov rax,rcx
                .break
            .endif
        .endif

        mov rbx,rcx
        mov rsi,r9  ; block
        mov edi,eax ; new size
        .if [rcx].Alloc(eax)

            mov ecx,[rsi].MBLOCK.bsize
            sub ecx,sizeof(MBLOCK)
            add rsi,sizeof(MBLOCK)
            mov rdx,rsi
            mov rdi,rax
            rep movsb
            [rbx].CStack.Free(rdx)
        .endif
    .until 1
    ret

CHeap::Realloc endp

CHeap::NewString proc uses rsi rbx string:LPSTR

    mov rbx,rcx
    mov rsi,rdx
    .if strlen(rdx)

        .if [rbx].CHeap.Alloc( &[rax+1] )

            strcpy(rax, rsi)
        .endif
    .endif
    ret

CHeap::NewString endp

    end
