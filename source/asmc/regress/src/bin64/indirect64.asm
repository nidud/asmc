;
; v2.32.61 - Indirection -- JK
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

.template t1
    p ptr t3 ?
    b db ?
   .ends
.template t2
    p ptr t1 ?
    b t1 <>
   .ends
.template t3
    p ptr t2 ?
   .ends

   .code

main proc a:ptr t3

   .new p:ptr t3

    mov rcx,p.p.p
    mov rcx,p.p.b.p

    add bl,p.p.p.b
    sub bl,a.p.p.b
    mov cl,p.p.p.p.p.p.p.p.p.b
    ret

main endp

end
