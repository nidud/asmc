
    ; 2.32.58 - inline pointer indirection

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
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

    .code

main proc

  .new a:ptr T()

    a.p.A() ; nop
    ret

main endp

    end

