include stdio.inc
include malloc.inc
include class.inc

    .code

Class::Release proc

    free(this)
    ret

Class::Release endp

Class::Print proc

    mov rsi,[rdi].Class.string
    printf( "%s\n", rsi )
    ret

Class::Print endp

Class::Class proc uses rbx r12 s:string_t

    mov r12,s
    mov rbx,this

    @ComAlloc(Class)
    .if rbx
        mov [rbx],rax
    .endif
    mov [rax].Class.string,r12
    ret

Class::Class endp

    end
