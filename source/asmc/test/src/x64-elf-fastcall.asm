; v 2.23 - proto fastcall :type
; v 2.27 - error removed..

S1  struc
l1  dd ?
l2  dd ?
S1  ends

foo proto :ptr S1

.code

foo proc a:ptr S1

    mov eax,[rdi].S1.l1
    ret
foo endp

    end
