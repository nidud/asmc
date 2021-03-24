
    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

t typedef ptr real16

s1 struct
p1 ptr ?
p2 ptr 6+2 dup(?)
p3 ptr ptr ?
p4 ptr ptr 7 dup(?)
p5 ptr byte ?
p6 ptr byte 8 dup(?)
p7 ptr t ?
p8 ptr t 10 dup(?)
s1 ends

    .code

foo proc

    mov eax,sizeof(s1)
    ret

foo endp

    end
