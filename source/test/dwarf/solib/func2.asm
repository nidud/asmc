extern my_data1:dword
.code
 my_func2 proc
    mov rax,qword ptr my_data1
    inc dword ptr [rax]
    ret
    endp

    end
