;
; v2.34.63 - Indirection.proc(...)
;

    .486
    .model flat, c


.class t1
    p ptr t3 ?
    b proc :ptr, :ptr
   .ends
.template t2
    p ptr t1 ?
    b proc local :ptr, :ptr
   .ends
.template t3
    p ptr t2 ?
   .ends

   .code

main proc a:ptr t3

   .new p:ptr t3

    p.p.b(1, 2)
    p.p.p.b(1, 2)
    a.p.p.b(1, 2)
    p.p.p.p.p.p.p.p.p.b(1, 2)

    ret

main endp

end
