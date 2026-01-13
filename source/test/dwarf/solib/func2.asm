externdef my_data1 export :dword
externdef my_data2 :dword
.code
 my_func2 proc export
    mov rax,qword ptr my_data1
    inc dword ptr [rax]
    mov eax,my_data2
    ret
    endp

    end
