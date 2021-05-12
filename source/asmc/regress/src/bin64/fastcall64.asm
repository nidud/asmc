
    ; 2.31.54 - Used args - win64:save

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option win64:1

p1  proc a1:ptr
    mov rax,a1
    ret
p1  endp

p2  proc a1:ptr, a2:ptr
    mov rax,a1
    mov rax,a2
    ret
p2  endp

p3  proc a1:ptr, a2:ptr, a3:ptr
    mov rax,a1
    mov rax,a2
    mov rax,a3
    ret
p3  endp

p4  proc a1:ptr, a2:ptr, a3:ptr, a4:ptr
    mov rax,a1
    mov rax,a2
    mov rax,a3
    mov rax,a4
    ret
p4  endp

p5  proc a1:ptr, a2:ptr, a3:ptr, a4:ptr, a5:ptr
    mov rax,a4
    mov rax,a5
    ret
p5  endp

p6  proc a1:ptr, a2:ptr, a3:ptr, a4:ptr, a5:ptr, a6:ptr
    mov rax,a4
    mov rax,a5
    mov rax,a6
    ret
p6  endp

p7  proc a1:ptr, a2:vararg
    ret
p7  endp

    end
