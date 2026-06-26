;
; v2.36.21 - Indirection .data
;

.class t1
    foo proc
   .ends
.class t2
    tp ptr t1 ?
    bar proc
   .ends
   .data
    p ptr t2 ?
   .code

main proc q:ptr t2

    mov edx,p.tp.foo()
    mov edx,q.tp.foo()
    ret
    endp

    end
