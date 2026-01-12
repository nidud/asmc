
public my_data1
.data
 my_data1 dd 1234
.code
 my_func1 proc i:sdword
    mov rax,qword ptr my_data1
    inc dword ptr [rax]
    imul eax,ldr(i),2
    ret
    endp

    end
