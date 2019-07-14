;
; v2.30.10 - Name order..
;
    .x64
    .model flat, fastcall

    ptr_t typedef ptr

.class C
    ;C   ptr_t ?
    Class   ptr_t ?
    C       proc :ptr
    Class   proc :ptr
    .ends

    .code

    option win64:2

    assume rcx:LPC

foo proc

  local p:LPC

    p.C(0)
    p.Class(1)
    [rcx].C(2)
    [rcx].Class(3)
    mov rax,[rcx].Class

    ret

foo endp

    end
