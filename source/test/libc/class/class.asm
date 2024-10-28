include stdio.inc
include malloc.inc
include tchar.inc

.class Class

    string      tstring_t ?

    Class       proc :tstring_t
    Release     proc
    Print       proc
   .ends

   .code

Class::Release proc

    free(this)
    ret

Class::Release endp


Class::Print proc

    ldr rcx,this

    _tprintf("%s\n", [rcx].Class.string)
    ret

Class::Print endp


Class::Class proc string:tstring_t

    @ComAlloc(Class)

    mov rcx,string
    mov [rax].Class.string,rcx
    ret

Class::Class endp


_tmain proc

   .new p:ptr Class("Hello Class!")

    p.Print()
    p.Release()

    xor eax,eax
    ret

_tmain endp

    end
