
public my_data1 export
.data
 my_data1 dd 1234
.code
 my_func1 proc export i:sdword
    imul eax,ldr(i),2
    ret
    endp

    end
