include mylib.inc

.code

 main proc

   .new func1:int_t
   .new func2:int_t

    Increment()
    mov func1,my_func1(1)
    mov func2,my_func2()
    mov rax,my_data1[GOT]
    printf(
        "my_data1: %d\n"
        "my_data2: %d\n"
        "my_func1: %d\n" [GOT], [rax], func2, func1)
    xor eax,eax
    ret
    endp

    end

