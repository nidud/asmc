foo_1 proto syscall private :dword, :dword, :dword, :dword, :dword, :dword
foo_2 proto syscall private :dword, :dword, :dword, :dword, :dword, :dword

    .code

main proc fastcall uses rsi rdi

    foo_1(1,2,3,4,5,6)
    ret

main endp

foo_1 proc syscall private a:dword, b:dword, c:dword, d:dword, e:dword, f:dword

    foo_2(a,b,c,d,e,f)
    sub eax,a
    sub eax,b
    sub eax,c
    sub eax,d
    sub eax,e
    sub eax,f
    ret

foo_1 endp

foo_2 proc syscall private a:dword, b:dword, c:dword, d:dword, e:dword, f:dword

    mov eax,a
    add eax,b
    add eax,c
    add eax,d
    add eax,e
    add eax,f
    ret

foo_2 endp

    END
