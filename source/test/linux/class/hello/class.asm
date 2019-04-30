include stdio.inc
include malloc.inc
include class.inc

    .code

    assume rdi:LPCLASS

Class::Release proc
    free(_this)
    ret
Class::Release endp

Class::Print proc
    mov rsi,[rdi].string
    printf( "%s\n", rsi )
    ret
Class::Print endp

Class::Class proc uses r12 s:string_t

  local p:LPSTR

    mov p,s
    mov r12,_this

    .if malloc( sizeof(Class) + sizeof(ClassVtbl) )

        mov rdi,rax
        add rax,sizeof(Class)
        mov [rdi],rax
        lea rcx,Class_Release
        mov [rax],rcx
        lea rcx,Class_Print
        mov [rax+8],rcx
        mov rax,p
        mov [rdi].string,rax
        mov rax,rdi
        .if r12
            mov [r12],rax
        .endif
    .endif
    ret

Class::Class endp

    end
