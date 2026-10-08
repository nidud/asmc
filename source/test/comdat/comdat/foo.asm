include stdio.inc

bar proto
.code
 main proc
    bar()
    option comdat:on
    lea rdx,@CStr("The COMDAT String")
    option comdat:off
    printf("foo: address of %s is %p\n", rdx, rdx)
    xor eax,eax
    ret
    endp

    end
