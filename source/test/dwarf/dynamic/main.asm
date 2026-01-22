include stdio.inc

my_func1 proto :sdword
externdef export my_data1:dword
.code
 main proc
    printf("my_func1(1)=%d\n", my_func1(1))
    mov rcx,qword ptr my_data1
    printf("my_data1=%u\n", [rcx])
    xor eax,eax
    ret
    endp

    end

