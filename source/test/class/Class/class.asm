include stdio.inc
include malloc.inc

.class Class :string_t

    string    string_t ?

    Release   proc
    Print     proc

    .ends

    .data
    vtable ClassVtbl { Class_Release, Class_Print }

    .code

Class::Release proc

    free(rcx)
    ret

Class::Release endp

    assume rcx:LPCLASS

Class::Print proc

    printf( "%s\n", [rcx].string )
    ret

Class::Print endp


Class::Class proc String:string_t

    .if !rcx
        .return .if !malloc(sizeof(Class))
        mov rcx,rax
        mov rdx,String
    .endif
    mov [rcx].string,rdx
    lea rax,vtable
    mov [rcx].lpVtbl,rax
    mov rax,rcx
    ret

Class::Class endp


main proc

    .new p:ptr Class("p:ptr Class")

      ;  lea  rdx,[DS0001]
      ;  xor  ecx,ecx
      ;  call Class_Class
      ;  mov  p,rax          ; [rbp-8]

    p.Print()

      ;  mov  rcx,[rbp-8]
      ;  mov  rax,[rcx]
      ;  call [rax+8]

    p.Release()

      ;  mov  rcx,[rbp-8]
      ;  mov  rax,[rcx]
      ;  call [rax]

    .new s:Class("s:Class")

      ;  lea  rdx,[DS0002]
      ;  lea  rcx,s         ; [rbp-24]
      ;  call Class_Class

    s.Print()

      ;  lea  rcx,s
      ;  mov  rax,[rcx]
      ;  call [rax+8]

    ret

main endp

    end main
