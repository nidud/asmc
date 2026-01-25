include mylib.inc

.code

my_func2 proc
    Increment()
ifdef _WIN64
    mov rax,my_data2
else
    mov eax,my_data2[eax]
endif
    ret
    endp

    end
