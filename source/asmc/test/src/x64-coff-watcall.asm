
    ; 2.34.30 watcall64 -- reserved fastcall stack

    .code

foo proc fastcall p:ptr
    ret
foo endp

w0  proc watcall
    ret     ; ok
w0  endp

w1  proc watcall
    foo(0)  ; fail
    ret
w1  endp

w2  proc watcall a:ptr, b:ptr, c:ptr, d:ptr
    foo(0)  ; fail
    ret
w2  endp

w3  proc watcall a:ptr, b:ptr, c:ptr, d:ptr, e:ptr
    foo(0)  ; ok
    ret
w3  endp

w4  proc watcall
    local l[10]:byte
    foo(0)  ; ok
    ret
w4  endp

w5  proc watcall a:ptr, b:ptr, c:ptr, d:ptr
    local l[10]:byte
    foo(0)  ; ok
    ret
w5  endp

w6  proc watcall a:ptr, b:ptr, c:ptr, d:ptr, e:ptr
    local l[10]:byte
    foo(0)  ; ok
    ret
w6  endp

    option win64:auto

a0  proc watcall
    ret
a0  endp

a1  proc watcall
    foo(0)
    ret
a1  endp

a2  proc watcall a:ptr, b:ptr, c:ptr, d:ptr
    foo(0)
    ret
a2  endp

a3  proc watcall a:ptr, b:ptr, c:ptr, d:ptr, e:ptr
    foo(0)
    ret
a3  endp

a4  proc watcall
    local l[10]:byte
    foo(0)
    ret
a4  endp

a5  proc watcall a:ptr, b:ptr, c:ptr, d:ptr
    local l[10]:byte
    foo(0)
    ret
a5  endp

a6  proc watcall a:ptr, b:ptr, c:ptr, d:ptr, e:ptr
    local l[10]:byte
    foo(0)
    ret
a6  endp

    end
