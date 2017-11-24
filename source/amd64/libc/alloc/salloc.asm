include alloc.inc
include string.inc

    .code

    option win64:rsp nosave

salloc proc uses rbx string:LPSTR

    mov rbx,rcx
    .if strlen(rcx)

        inc rax
        .if malloc(rax)

            strcpy(rax, rbx)
        .endif
    .endif
    ret

salloc endp

    end
