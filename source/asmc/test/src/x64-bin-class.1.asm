;
; v2.30.10 - Name order..
;
ptr_t typedef ptr

.class C
    ;C   ptr_t ?
    Class   ptr_t ?
    C       proc :ptr
    Class   proc :ptr
    .ends

    .code

    option win64:2

    assume rcx:ptr C

foo proc

  local p:ptr C

    C(0)
    p.Class(1)
    [rcx].Class(3)
    mov rax,[rcx].Class
    ret
    endp

C::C proc x:ptr
    ret
    endp

    end
