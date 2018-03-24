include class.inc

    .data
    virtual_table PVOID 0

    .code

Class::Print proc

    printf( "%s\n", [rcx].Class.string )
    ret

Class::Print endp

Class::Class proc String:LPSTR

    .repeat

        .if !rcx

            .break .if !malloc( sizeof(Class) )
            mov rcx,rax
            mov rdx,String
        .endif
        mov [rcx].Class.string,rdx
        mov rax,virtual_table
        mov [rcx].Class.lpVtbl,rax
        mov rax,rcx
    .until 1
    ret

Class::Class endp

Install proc private

    .if malloc( sizeof(ClassVtbl) )

        mov virtual_table,rax
        lea rcx,free
        mov [rax].ClassVtbl.Release,rcx
        lea rcx,Class@Print
        mov [rax].ClassVtbl.Print,rcx
    .endif
    ret
Install endp

.pragma init Install 50

    end
