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

    mov p.p.p,rcx
    mov p.p.b.p,rcx

    add p.p.p.b,bl
    sub a.p.p.b,bl
    mov p.p.p.p.p.p.p.p.p.b,cl

    mov p[rdi].p[rsi*8].p,rcx
    mov rcx,p[rdi].p[rsi*8].p

    ret

main endp

end
