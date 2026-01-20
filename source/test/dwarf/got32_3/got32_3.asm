include mylib.inc

.code

main proc

    Increment(GETGOT())
    mov esi,my_func1(1)
    mov edi,my_func2()
    mov ecx,my_data1[ebx]
    printf(
        "my_data1: %d\n"
        "my_data2: %d\n"
        "my_func1: %d\n" [ebx], [ecx], edi, esi)
    xor eax,eax
    ret
    endp

    end

