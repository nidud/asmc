;
; v2.32.61 - Indirection -- JK
;

    .486
    .model flat, c


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

    mov p.p.p,ecx
    mov p.p.b.p,ecx

    add p.p.p.b,bl
    sub a.p.p.b,bl
    mov p.p.p.p.p.p.p.p.p.b,cl

    mov p[edi].p[esi*4].p,ecx
    mov ecx,p[edi].p[esi*4].p

    ret

main endp

end
