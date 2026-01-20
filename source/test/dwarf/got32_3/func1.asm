include mylib.inc

.data
 my_data1 int_t 1234
 my_data2 int_t 4321

.code

my_func1 proc i:int_t

    Increment(GETGOT())
    imul eax,i,2
    ret
    endp

    end
