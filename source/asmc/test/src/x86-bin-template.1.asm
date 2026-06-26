
    .486
    .model flat, fastcall

S1 struct
    m db ?
    a proc
S1 ends

.template T1
    p ptr S1 ?
    a proc
   .ends
.template T2
    p ptr T1 ?
    a proc
   .ends
.template T3
    p ptr T2 ?
    a proc
   .ends
   .code

main proc

  .new a:T3
  .new b:S1
  .new p:ptr T3
  .new q:ptr S1

    a.p.a()
    a.p.p.a()
    a.p.p.p.a()

    q.a()
    p.p.a()
    p.p.p.a()
    p.p.p.p.a()
    ret

main endp

    end
