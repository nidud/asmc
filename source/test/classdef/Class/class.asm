include class.inc

    .data
    virtual_table ClassVtbl { free, Class_Print }

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
        lea rax,virtual_table
        mov [rcx].Class.lpVtbl,rax
        mov rax,rcx
    .until 1
    ret

Class::Class endp

    end
