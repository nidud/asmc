
    ; public inline

    .x64
    .model flat, fastcall
    .code

    option casemap:none, win64:auto

.template X
    atom byte ?
    .operator A :vararg { nop }
    .ends

.template Y : public X
    .operator B :vararg { nop }
    .ends

.template T : public Y
    .operator T :vararg {}
    .operator C :vararg { nop }
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
