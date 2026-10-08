include stdio.inc

.cdat my_xmm(16)
 my_xmm real4  4 dup(16.0)
.cdat my_ymm(32)
 my_ymm real4  8 dup(32.0)
.cdat my_zmm(64)
 my_zmm real4 16 dup(64.0)

.code
 bar proc
    printf("bar.my_xmm: %p\n", &my_xmm)
    printf("bar.my_ymm: %p\n", &my_ymm)
    printf("bar.my_zmm: %p\n", &my_zmm)
    ret
    endp

    end
