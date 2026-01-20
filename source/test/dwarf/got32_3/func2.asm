include mylib.inc

.code

my_func2 proc

    Increment(GETGOT())
    mov eax,my_data2[eax]
    ret
    endp

    end
