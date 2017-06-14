include alloc.inc

    .code

    option win64:2

_aligned_malloc proc uses rdi dwSize:size_t, Alignment:UINT

    mov edi,edx
    lea rcx,[rcx+rdx+sizeof(S_HEAP)]

    .if malloc(rcx)

        dec edi
        .if eax & edi

            lea rdx,[rax-sizeof(S_HEAP)]
            lea rax,[rax+rdi+sizeof(S_HEAP)]
            not rdi
            and rax,rdi
            lea rcx,[rax-sizeof(S_HEAP)]
            mov [rcx].S_HEAP.h_prev,rdx
            mov [rcx].S_HEAP.h_type,3

        .endif
    .endif
    ret

_aligned_malloc ENDP

    END
