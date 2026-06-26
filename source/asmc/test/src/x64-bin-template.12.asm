
    ; 2.32.58 - inline pointer indirection

   .code

    option casemap:none, win64:auto

.template X
    atom byte ?
    .inline A { nop }
    .ends

.class T
    p ptr X ?
    .inline T {}
    Relase proc
    .ends

main proc
  .new a:ptr T()
    a.p.A() ; nop
    ret
    endp

    end

