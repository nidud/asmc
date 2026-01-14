
public export my_data1
public my_data2
.data
 my_data1 dd 1234
 my_data2 dd 4321
.code
 my_func1 proc export i:sdword
    mov rax,qword ptr my_data1
    inc dword ptr [rax]
    imul eax,ldr(i),2
    ret
    endp

    end
