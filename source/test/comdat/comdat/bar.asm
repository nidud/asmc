include stdio.inc

.code
 bar proc
    option comdat:on
    lea rdx,@CStr("The COMDAT String")
    option comdat:off
    printf("bar: address of %s is %p\n", rdx, rdx)
    ret
    endp

    end
