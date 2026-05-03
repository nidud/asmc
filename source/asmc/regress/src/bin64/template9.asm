
    ; 2.31.47 - public inline

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option casemap:none, win64:auto

.template X
    atom byte ?
    .inline A :vararg { nop }
    .ends

.template Y : public X
    .inline B :vararg { nop }
    .ends

.template T : public Y
    .inline T :vararg {}
    .inline C :vararg { nop }
    .ends

    .code

main proc

  .new a:T()

    a.A() ; nop
    a.B() ; nop
    a.C() ; nop

    ret

main endp

    end
