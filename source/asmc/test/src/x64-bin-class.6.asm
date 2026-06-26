
    ; 2.31.55 - allow class.pointer.method(...)

   .code

    option win64:3

.class c1
    d db ?
    a proc :ptr
   .ends

.class c2
    d ptr c1 ?
    a proc :ptr
   .ends

    .code

main proc a:ptr c2

  local l:c2
  local p:ptr c2

    l.a(0)
    l.d.a(0)
    p.a(0)
    p.d.a(0)
    a.a(0)
    a.d.a(0)
    ret
    endp

    end
