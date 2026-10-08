include stdio.inc

bar proto

.cdat my_xmm(16)
 my_xmm real4  4 dup(16.0)
.cdat my_ymm(32)
 my_ymm real4  8 dup(32.0)
.cdat my_zmm(64)
 my_zmm real4 16 dup(64.0)

.code
 main proc
    bar()
    printf("foo.my_xmm: %p\n", &my_xmm)
    printf("foo.my_ymm: %p\n", &my_ymm)
    printf("foo.my_zmm: %p\n", &my_zmm)
    xor eax,eax
    ret
    endp

    end
