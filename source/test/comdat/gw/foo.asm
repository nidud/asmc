include stdio.inc

bar proto
.code
 main proc
    bar()
    lea rdx,@CStr("The COMDAT String")
    printf("foo: address of %s is %p\n", rdx, rdx)
    xor eax,eax
    ret
    endp

    end
