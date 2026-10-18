
; v2.39.15: allow vector assignment for INVOKE

option win64:3

.code

bar proto :real4 {}
baz proto :real8, :real8 {}

foo proc uses xmm6 xmm7 x:real8
    bar( { 1.0, 2.0, 3.0, 4.0 } )
    baz( { 1.0, 2.0 }, { 3.0, 4.0 } )
    ret
    endp

    end

