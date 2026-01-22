include stdio.inc

my_func1 proto :sdword
my_func2 proto

externdef export my_data1:dword

.code

 main proc

    my_func2()
    mov rbx,qword ptr my_data1
    inc dword ptr [rbx]

    printf("my_func1(1)=%d\n", my_func1(1))
    printf("my_data1=%u\n", [rbx])
    xor eax,eax
    ret
    endp

    end

