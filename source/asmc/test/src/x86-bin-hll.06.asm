    .486
    .model flat, c
s1  struc
l1  dd ?
l2  dw ?
s1  ends
    .data
data_label label s1
S   s1 <>
    .code
code_label:
foo proc a1:ptr, a2:ptr
    ret
foo endp

    foo( &foo, &code_label )
    foo( &foo, &data_label )
    foo( &S, &S.l1 )
    foo( &S, &S.l2 )
    foo( &[eax].s1.l1, &[eax].s1.l2 )
    foo( &[eax+edx-10], &S.l2 )

    .if foo(&S, &S)
    .elseif foo(&S, &S)
    .endif

    end
