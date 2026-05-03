include mylib.inc

.data
 my_data1 size_t 1234
 my_data2 size_t 4321

.code

my_func1 proc i:int_t

    Increment()
    imul eax,ldr(i),2
    ret
    endp

    end

