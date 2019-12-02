;
; v2.30.33 - : public class
;
    .x64
    .model flat, fastcall

    option win64:3

    ; .class name [ : args ] [ : public class ]

.class a : byte
    A    dd ?
    GetA proc
.ends
.class b : public a
    B    dd ?
    GetB proc
.ends
.class c : public b
    C    dd ?
    GetC proc
.ends
.class d : public c
    D    dd ?
    GetD proc
.ends

    ; .comdef name [: public class]

.comdef c1
    C1   dd ?
    Get1 proc
    .ends

.comdef c2 : public c1
    C2   dd ?
    Get2 proc
    .ends

    .code

main proc

  local x:d, q:c2

    mov x.A,a
    mov x.B,b
    mov x.C,c
    mov x.D,d
    mov q.C1,c1
    mov q.C2,c2

    x.GetA()
    x.GetB()
    x.GetC()
    x.GetD()
    q.Get1()
    q.Get2()

    ret

main endp

    end
