include stdio.inc
include malloc.inc

.class Class
    string      string_t ?
    Class       proc :string_t
    Release     proc
    Print       proc
   .ends

   .code

Class::Release proc

    free(rdi)
    ret

Class::Release endp


Class::Print proc

    printf("%s\n", [rdi].Class.string)
    ret

Class::Print endp


Class::Class proc string:string_t

    mov rdi,@ComAlloc(Class)
    mov rcx,string
    mov [rdi].Class.string,rcx
    ret

Class::Class endp


main proc

   .new p:ptr Class("Hello Class!")

    p.Print()
    p.Release()
    ret

main endp

    end
