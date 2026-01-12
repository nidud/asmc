include stdio.inc

my_func1 proto :sdword
my_func2 proto

extern my_data1:dword

.code

 main proc

    my_func2()
    inc my_data1

    printf("my_func1(1)=%d\n", my_func1(1))
    printf("my_data1=%u\n", my_data1)
    xor eax,eax
    ret
    endp

    end

