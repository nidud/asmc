include stdio.inc

.code
 bar proc
    lea rdx,@CStr("The COMDAT String")
    printf("bar: address of %s is %p\n", rdx, rdx)
    ret
    endp

    end
