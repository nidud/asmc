include malloc.inc

    .code

    option win64:rsp nosave noauto

_alloca64 PROC byte_count, res_stack

    lea rax,[rsp+8]     ; start of call
    add rcx,rdx         ; @ReservedStack

    .while rcx > _PAGESIZE_
        sub  rax,_PAGESIZE_
        test [rax],rax
        sub  rcx,_PAGESIZE_
    .endw

    sub rax,rcx
    and rax,-(_GRANULARITY)
    test [rax],rax
    mov rcx,[rsp]
    mov rsp,rax
    add rax,rdx
    jmp rcx

_alloca64 ENDP

    END
