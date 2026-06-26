
    ; 2.31.54 - Used args - win64:save

    .code

    option win64:1

p1  proc a1:ptr
    mov rax,a1
    ret
    endp

p2  proc a1:ptr, a2:ptr
    mov rax,a1
    mov rax,a2
    ret
    endp

p3  proc a1:ptr, a2:ptr, a3:ptr
    mov rax,a1
    mov rax,a2
    mov rax,a3
    ret
    endp

p4  proc a1:ptr, a2:ptr, a3:ptr, a4:ptr
    mov rax,a1
    mov rax,a2
    mov rax,a3
    mov rax,a4
    ret
    endp

p5  proc a1:ptr, a2:ptr, a3:ptr, a4:ptr, a5:ptr
    mov rax,a4
    mov rax,a5
    ret
    endp

p6  proc a1:ptr, a2:ptr, a3:ptr, a4:ptr, a5:ptr, a6:ptr
    mov rax,a4
    mov rax,a5
    mov rax,a6
    ret
    endp

p7  proc a1:ptr, a2:vararg
    ret
    endp

    end
