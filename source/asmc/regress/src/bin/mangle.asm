
    .486
    .model flat
    .code

p1 proto c :ptr, :ptr
p2 proto pascal :ptr, :ptr
p3 proto stdcall :ptr, :ptr
p4 proto fastcall :ptr, :ptr
p5 proto vectorcall :ptr, :ptr
p6 proto syscall :ptr, :ptr

p1  proc c a:ptr, b:ptr
    p1(a, b)
    p2(a, b)
    p3(a, b)
    p4(a, b)
    p5(a, b)
    p6(a, b)
    ret
p1  endp

p2  proc pascal a:ptr, b:ptr
    p1(a, b)
    p2(a, b)
    p3(a, b)
    p4(a, b)
    p5(a, b)
    p6(a, b)
    ret
p2  endp

p3  proc stdcall a:ptr, b:ptr
    p1(a, b)
    p2(a, b)
    p3(a, b)
    p4(a, b)
    p5(a, b)
    p6(a, b)
    ret
p3  endp

p4  proc fastcall a:ptr, b:ptr
    p1(a, b)
    p2(a, b)
    p3(a, b)
    p4(a, b)
    p5(a, b)
    p6(a, b)
    ret
p4  endp

p5  proc vectorcall a:ptr, b:ptr
    p1(a, b)
    p2(a, b)
    p3(a, b)
    p4(a, b)
    p5(a, b)
    p6(a, b)
    ret
p5  endp

p6  proc syscall a:ptr, b:ptr
    p1(a, b)
    p2(a, b)
    p3(a, b)
    p4(a, b)
    p5(a, b)
    p6(a, b)
    ret
p6  endp

    end
